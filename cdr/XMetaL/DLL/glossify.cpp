// Glossify.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "Glossify.h"
#include <stack>
#include ".\glossify.h"

// CGlossify dialog

const TCHAR* TAG_NAME = _T("GlossaryTermRef");

IMPLEMENT_DYNAMIC(CGlossify, CDialog)
CGlossify::CGlossify(CWnd* pParent /*=NULL*/)
	: CDialog(CGlossify::IDD, pParent), curChain(0), curNode(0)
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
    ON_BN_CLICKED(IDC_GLOSSIFY_SKIP_FIRST, OnBnClickedGlossifySkipFirst)
END_MESSAGE_MAP()


// CGlossify message handlers

void CGlossify::OnSkip()
{
    if (curNode)
        curNode->markedUp = true;
    if (!findNextMatch()) {
        ::AfxMessageBox(_T("No more glossary phrases found"));
        OnOK();
    }
}

void CGlossify::OnBnClickedGlossifySkipFirst()
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
    if (curNode)
        curNode->markedUp = true;
    CString val;
    m_markup.GetWindowText(val);
    range.Surround(TAG_NAME);

    range.SetContainerAttribute(_T("cdr:href"), val);
    if (!findNextMatch()) {
        ::AfxMessageBox(_T("No more glossary phrases found"));
        OnOK();
    }
}

void CGlossify::findChains(DOMNode& docElem)
{
    _Document doc = cdr::getApp().GetActiveDocument();
    doc.SetFormattingUpdating(FALSE);
    try {
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
    catch (...) {}
    doc.SetFormattingUpdating(TRUE);
}
        

// For debugging.
extern void logWrite(const CString& what);

static CString normalizeWord(const CString& s) {
    CString w = s;
    // logWrite(_T("before normalization: '") + w + _T("'"));
    TCHAR* chars = _T("'\".,?!:;()[]{}<>\x201C\x201D");
    for (size_t i = 0; chars[i]; ++i)
        w.Remove(chars[i]);
    w.MakeUpper();
    // logWrite(_T("after normalization: '") + w + _T("'"));
    return w;
}

CGlossify::WordChain::WordChain(::DOMNode node, ::_Document doc)
{
    ::Range range = doc.GetRange();
    ::Range end   = doc.GetRange();
    ::Find find = range.GetFind();
    range.SelectBeforeNode(node);
    end.SelectAfterNode(node);
    while (find.Execute(_T("[^-\n\r\t ]+"), _T(""), _T(""), 
                        TRUE, FALSE, TRUE, TRUE, FALSE, 0, FALSE)) 
    {
        if (!range.GetIsLessThan(end, FALSE))
            break;
        CString s = normalizeWord(range.GetText());
        
        if (!s.IsEmpty()) {
            ::Range r = range.GetDuplicate();
            Word w = Word(r, s);
            words.push_back(w);
            CString logMsg;
            logMsg.Format(L"normalizedWord '%s'", s);
            // logWrite(logMsg);
        }
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
            if (docType == _T("Summary"))
                gt->clearFlags();
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
                bool glossifiable = true;
                if (!range.ExtendTo(lastWord.r))
                    glossifiable = false;
                
                // Make sure the phrase can be marked up.
                if (glossifiable && !range.GetCanSurround(TAG_NAME))
                    glossifiable = false;

                // Populate the controls of the dialog box.
                if (glossifiable) {
                    CString cdrId;
                    CString phraseText = range.GetText();
                    int i = phraseText.GetLength();
                    const TCHAR* endPunct = _T(".;:,");

                    // Back up in front of trailing punctuation.
                    if (i > 0 && _tcschr(endPunct, phraseText[i - 1])) {
                        ::Range endPoint = lastWord.r.GetDuplicate();
                        endPoint.Collapse(0);
                        while (i-- > 0 && _tcschr(endPunct, phraseText[i]))
                            endPoint.MoveLeft(0); // Broken; bug in XMetaL.
                        phraseText.TrimRight(endPunct);
                        range = firstWord.r.GetDuplicate();
                        if (!range.ExtendTo(endPoint))
                            glossifiable = false;
                        else if (!range.GetCanSurround(TAG_NAME))
                            glossifiable = false;
                    }
                    if (glossifiable) {
                        CString name = gt->names[n->docId];
                        cdrId.Format(_T("CDR%010d; %s"), n->docId, name);
                        m_phrase.SetWindowText(phraseText);
                        m_markup.SetWindowText(cdrId);
                        range.Select();
                        
                        // Skip past the current phrase.
                        chain->curWord += phrase.size();
                        curNode = n;
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
