// Glossify.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "Glossify.h"
#include <stack>

#if 0
static void dumpPhraseChain(const GlossaryPhraseChain& pc, const CString& name)
{
    CString msg;
    msg.Format(_T("size of phrase chain: %d"), pc.size());
    ::AfxMessageBox(msg);
    FILE* logFile = fopen("c:/tmp/PhraseChain.log", "a");
    if (!logFile) {
        ::AfxMessageBox(_T("Can't open log file"));
        return;
    }
    fprintf(logFile, "*** CHAIN FOR %s ***\n", 
        cdr::cStringToUtf8(name).c_str());
    GlossaryPhraseChain::const_iterator i = pc.begin();
    while (i != pc.end()) {
        fprintf(logFile, "%d\t%d\t%d\t%s\t%s\t%s\n", i->level, 
            i->startPos, i->len,
            (i->leftEdge ? "true" : "false"),
            (i->rightEdge ? "true" : "false"),
            cdr::cStringToUtf8(i->w).c_str());
        ++i;
    }
    fclose(logFile);
}

static void parseNode(DOMNode& n, GlossaryPhraseChain& pc, int level) {
    CString s;
    const TCHAR* delims = _T(" \r\n\t.,/<>?'\";:[]{}\\|=+-_)(*&^%$#@!~`");
    DOMNode c = n.GetFirstChild();
    while (c) {
        //if (::AfxMessageBox(c.GetNodeName() + _T(" (keep going??)"), MB_YESNO) == IDNO)
        //    break;
        // Text nodes.
        if (c.GetNodeType() == 3) {
            CString s = c.GetNodeValue();
            int nodeLen = s.GetLength();
            int pos = 0;
            CString w = s.Tokenize(delims, pos);
            while (w != _T("")) {
                int end = pos - 1;
                int len = w.GetLength();
                int start = end - len;
                bool rightEdge = end == nodeLen;
                bool leftEdge = start == 0;
                GlossaryPhraseWord pw(w, level, start, c, len, 
                    leftEdge, rightEdge);
                pc.push_back(pw);
                w = s.Tokenize(delims, pos);
            }
        }

        // Element nodes.
        else if (c.GetNodeType() == 1)
            parseNode(c, pc, level + 1);
        c = c.GetNextSibling();
    }
}
#endif

// CGlossify dialog

IMPLEMENT_DYNAMIC(CGlossify, CDialog)
CGlossify::CGlossify(CWnd* pParent /*=NULL*/)
	: CDialog(CGlossify::IDD, pParent), curChain(0)
{
    //::AfxMessageBox(_T("Milestone 2a"));
    _Application app = cdr::getApp();
    doc = app.GetActiveDocument();
    //::AfxMessageBox(_T("Milestone 2b"));
	range = doc.GetRange();
    DOMNode docElement = doc.GetDocumentElement();
    docType = docElement.GetNodeName();
    //::AfxMessageBox(_T("Milestone 2c"));
    // endRange = doc.GetRange();
    //::AfxMessageBox(_T("Milestone 2d"));
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
    // TODO: Add your control notification handler code here
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

#if 0
struct GlossPhraseWord {
    ::Range range;
    cdr::GlossaryNode glossaryNode;
};
typedef std::stack<GlossaryPhraseWord> GlossaryPhrase;
#endif

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
        //if (::AfxMessageBox(range.GetText(), MB_YESNO) == IDNO)
        //    break;
        ::Range r = range.GetDuplicate();
        Word w = Word(r);
        words.push_back(w);
    }
    curWord = 0;
}

bool CGlossify::findNextMatch()
{
    /*
    if (curChain >= static_cast<int>(chains.size()))
        return false;
    DOMNode& n = glossifiableSections[curChain];
    endRange.SelectAfterNode(n);
    range.SelectBeforeNode(n);
    ::Find find = range.GetFind();
    ::_Application app = cdr::getApp();
    GlossaryPhrase phrase;
    std::vector<::Range> words;
    while (find.Execute(_T("[A-Za-z0-9]+"), _T(""), _T(""), FALSE, TRUE, TRUE, TRUE, FALSE, 0, FALSE)) {
        if (!range.GetIsLessThan(endRange, FALSE))
            break;
        if (::AfxMessageBox(range.GetText(), MB_YESNO) == IDNO)
            break;
        words.push_back(range.GetDuplicate());
    }
    CString msg;
    msg.Format(_T("num words: %d"), words.size());
    ::AfxMessageBox(msg);
    for (std::vector<::Range>::iterator i = words.begin(); i != words.end(); ++i) {
        if (i->GetText().Left(2) == _T("<?"))
            continue;
        if (i->GetCanSurround(_T("GlossaryTermRef"))) {
            i->Surround(_T("GlossaryTermRef"));
            i->SetContainerAttribute(_T("cdr:href"), _T("CDR1234567890"));
        }
    }
    return true;

        CString word = range.GetText();
        word.MakeUpper();
        if (range.GetText().Left(2) == _T("<?"))
            continue;
        ::Range r = app.GetSelection();
        CString msg;
        ::DOMNode container = range.GetContainerNode();
        msg.Format(_T("range text: %s; range container: %s (%d); selection text: %s; keep going?"), 
            range.GetText(), container.GetNodeName(), container.GetNodeType(), r.GetText());
        //::AfxMessageBox(_T("range text: " + range.GetText()));
        //::AfxMessageBox(_T("selection text: " + r.GetText()));
        if (::AfxMessageBox(msg, MB_YESNO) == IDNO)
            return false;
        if (range.GetCanSurround(_T("GlossaryTermRef"))) {
            CString w = range.GetText();
            range.Surround(_T("GlossaryTermRef"));
            container = range.GetContainerNode();
            //range.Collapse(1);
            //range.MoveRight(0);
            //range.Select();
            //msg.Format(_T("container: %s"), container.GetNodeName());
            //::AfxMessageBox(msg);
            //range.SetContainerAttribute(_T("GlossaryTermRef"), _T("CDR0000123456"));
            range.SetContainerAttribute(_T("cdr:href"), _T("CDR0000123457"));
            range.Collapse(0);
            //range.MoveRight(0);
            if (w == _T("a")) {
                range.Select();
                return true;
            }
        }
    }
    ::AfxMessageBox(_T("didn't work"));
    return false;
    endRange.SelectAfterNode(n);
    while (!range.GetContains(endRange, FALSE)) {}
    */

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

    // Get the current element and the doc type.
    DOMNode docElement = doc.GetDocumentElement();
    cdr::getGlossaryTree()->clearFlags();
    ::_Application app = cdr::getApp();
    ::Selection sel = app.GetSelection();
    //sel.Collapse(0);
    sel.SelectBeforeNode(docElement);
    sel.SetHiddenContainer(TRUE);
    findChains(docElement);
    //::Range selection = cdr::getApp().GetSelection();
    //::DOMElement elem = selection.GetContainerNode();
    //CString elemName  = elem.GetNodeName();

    if (chains.empty()) { // (chains.empty()) {
        ::AfxMessageBox(_T("No glossifiable sections found"));
        OnCancel();
    }
    //DOMNode& n = glossifiableSections[0];
    //range.SelectBeforeNode(n);
    //range.MoveRight(0);
    if (!findNextMatch()) {
        ::AfxMessageBox(_T("No glossifiable phrases found"));
        OnCancel();
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
