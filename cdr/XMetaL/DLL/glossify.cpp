// Glossify.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "Glossify.h"
#include <stack>

// CGlossify dialog

IMPLEMENT_DYNAMIC(CGlossify, CDialog)
CGlossify::CGlossify(CWnd* pParent /*=NULL*/)
	: CDialog(CGlossify::IDD, pParent), curChain(0)
{
    _Application app = cdr::getApp();
    doc = app.GetActiveDocument();
	range = doc.GetRange();
    DOMNode docElement = doc.GetDocumentElement();
    docType = docElement.GetNodeName();
}

CGlossify::~CGlossify()
{
}

void CGlossify::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_phrase);
    DDX_Control(pDX, IDC_EDIT2, m_markup);
}


BEGIN_MESSAGE_MAP(CGlossify, CDialog)
    ON_BN_CLICKED(IDOK2, OnSkip)
    ON_BN_CLICKED(IDCANCEL, OnDone)
    ON_BN_CLICKED(IDOK, OnMarkup)
END_MESSAGE_MAP()


// CGlossify message handlers

void CGlossify::OnSkip()
{
    if (!findNextMatch()) {
        ::AfxMessageBox(_T("No more glossary phrases found"));
        OnOK();
    }
}

void CGlossify::OnDone()
{
    OnCancel();
}

void CGlossify::OnMarkup()
{
    CString val;
    m_markup.GetWindowText(val);
    range.Surround(_T("GlossaryTermRef"));

    range.SetContainerAttribute(_T("cdr:href"), val);
    if (!findNextMatch()) {
        ::AfxMessageBox(_T("No more glossary phrases found"));
        OnOK();
    }
}

void CGlossify::findChains(DOMNode& docElem)
{
    if (docType == _T("Summary")) {
        ::DOMNode c = docElem.GetFirstChild();
        while (c) {
            if (c.GetNodeName() == _T("SummarySection"))
                chains.push_back(WordChain(c, doc));
            c = c.GetNextSibling();
        }
    }
    else if (docType == _T("InScopeProtocol") || 
             docType == _T("ScientificProtocolInfo")) 
    {
         ::DOMNode c = docElem.GetFirstChild();
         while (c) {
             if (c.GetNodeName() == _T("ProtocolAbstract")) {
                 ::DOMNode gc = c.GetFirstChild();
                 while (gc) {
                     if (gc.GetNodeName() == _T("Patient")) {
                         ::DOMNode ggc = gc.GetFirstChild();
                         while (ggc) {
                             ::CString name = ggc.GetNodeName();
                             if (name == _T("Rationale") ||
                                 name == _T("Purpose") ||
                                 name == _T("EligibilityText") ||
                                 name == _T("TreatmentIntervention"))
                                 chains.push_back(WordChain(ggc, doc));
                             ggc = ggc.GetNextSibling();
                         }
                     }
                     gc = gc.GetNextSibling();
                 }
             }
             c = c.GetNextSibling();
         }
    }
}

CGlossify::WordChain::WordChain(::DOMNode node, ::_Document doc)
{
    ::Range range = doc.GetRange();
    ::Range end   = doc.GetRange();
    ::Find find = range.GetFind();
    range.SelectBeforeNode(node);
    end.SelectAfterNode(node);
    while (find.Execute(_T("[A-Za-z0-9]+"), _T(""), _T(""), 
                        FALSE, TRUE, TRUE, TRUE, FALSE, 0, FALSE)) 
    {
        if (!range.GetIsLessThan(end, FALSE))
            break;
        ::Range r = range.GetDuplicate();
        Word w = Word(r);
        words.push_back(w);
    }
    curWord = 0;
}

bool CGlossify::findNextMatch()
{
	// We're done if there are no more word chains to look at.
    if (curChain >= static_cast<int>(chains.size()))
        return false;

	// Try to match the phrases in the document with those in the glossary.
	cdr::GlossaryTree* gt = cdr::getGlossaryTree();

	// Pick up where we left off in the current word chain from the doc.
    WordChain* chain = &chains[curChain];

	// Remember the path in the glossary tree for the current phrase.
	std::stack<cdr::GlossaryNode*> phrase;

	// Keep looking until we run out of word chains.
	while (chain) {

        // Start at the root of the tree.
    	cdr::GlossaryNodeMap* currentNodeMap = &gt->nodeMap;

		// If we're finished with the current chain, move to the next one.
		int wordsLeft = static_cast<int>(chain->words.size()) - chain->curWord;
		while (wordsLeft < 1) {
			if (++curChain >= static_cast<int>(chains.size()))
				return false;
			chain = &chains[curChain];
			wordsLeft = chains.size();
		}

		// Build the longest matching phrase we can from the current position.
		while (static_cast<int>(phrase.size()) < wordsLeft) {
            Word& w = chain->words[chain->curWord + phrase.size()];
			cdr::GlossaryNodeMap::iterator i = currentNodeMap->find(w.w);
			if (i == currentNodeMap->end())
				break;
			phrase.push(i->second);
            currentNodeMap = &i->second->nodeMap;
		}

		// Look for a match with a complete glossary phrase.
		while (!phrase.empty()) {

			// Last word has a doc ID if this is a complete phrase; skip
			// over it if we've already marked it up for this chain.
			cdr::GlossaryNode* n = phrase.top();
			if (n->docId && !n->markedUp) {

				// Position the range object to include the phrase.
                Word& firstWord = chain->words[chain->curWord];
                Word& lastWord  = chain->words[chain->curWord + 
                                               phrase.size() - 1];
                range = firstWord.r.GetDuplicate();
                if (range.ExtendTo(lastWord.r)) {

				    // Make sure the phrase can be marked up.
				    if (range.GetCanSurround(_T("GlossaryTermRef"))) {

					    // Populate the controls of the dialog box.
					    CString cdrId;
                        CString phraseText = range.GetText();
					    cdrId.Format(_T("CDR%010d"), n->docId);
					    m_phrase.SetWindowText(phraseText);
					    m_markup.SetWindowText(cdrId);
                        range.Select();

					    // Skip past the current phrase.
					    chain->curWord += phrase.size();
                        n->markedUp = true;
					    return true;
				    }
			    }
            }

			// Shrink the phrase by one word.
			phrase.pop();
		}

		// Can't use the current word in a glossary phrase; skip past it.
		++chain->curWord;
	}

	// Make lint happy (but we'll never reach here).
	return false;
}

BOOL CGlossify::OnInitDialog()
{
    CDialog::OnInitDialog();

    DOMNode docElement = doc.GetDocumentElement();
    cdr::getGlossaryTree()->clearFlags();
    findChains(docElement);

    if (chains.empty()) {
        ::AfxMessageBox(_T("No glossifiable sections found"));
        OnCancel();
    }
    if (!findNextMatch()) {
        ::AfxMessageBox(_T("No glossifiable phrases found"));
        OnCancel();
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
