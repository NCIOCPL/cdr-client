// Glossify.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include <stack>
#include <windows.h>
#include "glossify.h"

// CGlossify dialog

const wchar_t* TAG_NAME = L"GlossaryTermRef";

IMPLEMENT_DYNAMIC(CGlossify, CDialog)
CGlossify::CGlossify(bool dig, bool insertion, const CString dict,
                     const CString aud, CWnd* parent /*=NULL*/)
: CDialog(CGlossify::IDD, parent), cur_chain(0), cur_node(0), m_dig(dig),
    dictionary(dict), audience(aud), m_insertion(insertion) {
    ::CApplication app = cdr::get_app();
    doc = app.get_ActiveDocument();
    range = doc.get_Range();
    ::CDOMNode doc_element = doc.get_documentElement();
    doc_type = doc_element.get_nodeName();
    language = L"en";
    if (doc_type == L"Summary") {
        ::CDOMNode c = doc_element.get_firstChild();
        while (c) {
            if (c.get_nodeName() == L"SummaryMetaData") {
                ::CDOMNode gc = c.get_firstChild();
                while (gc) {
                    if (gc.get_nodeName() == L"SummaryLanguage") {
                        CString value = cdr::extract_element_text(gc);
                        // ::AfxMessageBox(value);
                        if (value == L"Spanish")
                            language = L"es";
                        break;
                    }
                    gc = gc.get_nextSibling();
                }
            }
            c = c.get_nextSibling();
        }
    }
}

CGlossify::~CGlossify() {}

void CGlossify::DoDataExchange(CDataExchange* dx) {
    CDialog::DoDataExchange(dx);
    DDX_Control(dx, IDC_EDIT1, m_phrase);
    DDX_Control(dx, IDC_EDIT2, m_markup);
}


BEGIN_MESSAGE_MAP(CGlossify, CDialog)
    ON_BN_CLICKED(IDOK2, OnSkip)
    ON_BN_CLICKED(IDCANCEL, OnDone)
    ON_BN_CLICKED(IDOK, OnMarkup)
    ON_BN_CLICKED(IDC_GLOSSIFY_SKIP_FIRST, OnBnClickedGlossifySkipFirst)
    ON_BN_CLICKED(IDC_GLOSSIFY_NEXT_SECTION, OnBnClickedGlossifyNextSection)
    ON_BN_CLICKED(IDC_GLOSSIFY_PREVIEW, &CGlossify::OnBnClickedGlossifyPreview)
END_MESSAGE_MAP()


// CGlossify message handlers

void CGlossify::OnSkip() {
    if (cur_node)
        cur_node->marked_up = true;
    if (!find_next_match()) {
        ::AfxMessageBox(L"No more glossary phrases found");
        OnOK();
    }
}

void CGlossify::OnBnClickedGlossifySkipFirst() {
    if (!find_next_match()) {
        ::AfxMessageBox(L"No more glossary phrases found");
        OnOK();
    }
}

void CGlossify::OnDone() {
    OnCancel();
}

void CGlossify::OnMarkup() {
    if (cur_node)
        cur_node->marked_up = true;
    CString val;
    m_markup.GetWindowText(val);
    int semicolon = val.Find(';');
    if (semicolon != -1)
        val = val.Left(semicolon);
    if (m_insertion) {
        range.Surround(L"Insertion");
    }
    range.Surround(TAG_NAME);
    range.put_ContainerAttribute(L"cdr:href", val);
    if (!find_next_match()) {
        ::AfxMessageBox(L"No more glossary phrases found");
        OnOK();
    }
}

/**
 * Added for JIRA ticket OCECDR-3815. Exercises option
 * to dig through the layers of Insertion and Deletion
 * elements to find what would otherwise be top-level
 * SummarySection elements.
 */
void CGlossify::keep_digging(::CDOMNode& node, ::CDocument0& doc) {
    ::CDOMNode c = node.get_firstChild();
    while (c) {
        CString node_name = c.get_nodeName();
        if (node_name == L"SummarySection")
            chains.push_back(WordChain(c, doc));
        else if (node_name == L"Insertion" ||
                 node_name == L"Deletion")
            keep_digging(c, doc);
        c = c.get_nextSibling();
    }
}

void CGlossify::find_chains(CDOMNode& doc_elem) {
    ::CDocument0 doc = cdr::get_app().get_ActiveDocument();
    doc.put_FormattingUpdating(FALSE);
    try {
        if (doc_type == L"Summary") {
            ::CDOMNode c = doc_elem.get_firstChild();
            while (c) {
                CString node_name = c.get_nodeName();
                if (node_name == L"SummarySection")
                    chains.push_back(WordChain(c, doc));
                else if (m_dig) {
                    if (node_name == L"Insertion" ||
                        node_name == L"Deletion")
                        keep_digging(c, doc);
                }
                c = c.get_nextSibling();
            }
        }
    }
    catch (...) {}
    doc.put_FormattingUpdating(TRUE);
}

/**
 * Strip punctuation and uppercase a word from the document's text.
 *
 * @param word - string found by tokenizing text on whitespace delimiters
 * @return     - normalized string
 */
static CString normalize_word(const CString& word) {
    CString w = word;
    wchar_t* chars = L"'\".,?!:;()[]{}<>\x201C\x201D";
    for (size_t i = 0; chars[i]; ++i)
        w.Remove(chars[i]);
    // MakeUpper is badly broken for Unicode; BAD Microsoft!
    // w.MakeUpper();
    wchar_t* p = w.GetBuffer(w.GetLength());
    CharUpperBuff(p, w.GetLength());
    w.ReleaseBuffer();
    return w;
}

/**
 * Find all the sequences of consecutive non-whitespace characters in a node.
 *
 * @param node - block from the document whose text content we examine
 * @param doc  - XMetaL document object in which the node was found
 */
CGlossify::WordChain::WordChain(::CDOMNode node, ::CDocument0 doc) {
    ::CRange range = doc.get_Range();
    ::CRange end   = doc.get_Range();
    ::CFind find = range.get_Find();
    range.SelectBeforeNode(node);
    end.SelectAfterNode(node);
    while (find.Execute(L"[^-\n\r\t ]+", L"", L"",
                        TRUE, FALSE, TRUE, TRUE, FALSE, 0, FALSE)) {
        if (!range.get_IsLessThan(end, FALSE))
            break;
        CString s = normalize_word(range.get_Text());
        if (!s.IsEmpty()) {
            ::CRange r = range.get_Duplicate();
            Word w = Word(r, s);
            words.push_back(w);
        }
    }
    cur_word = 0;
}

/**
 *
 */
bool CGlossify::find_next_match() {

    // We're done if there are no more word chains to look at.
    if (cur_chain >= static_cast<int>(chains.size()))
        return false;

    // Try to match the phrases in the document with those in the glossary.
    cdr::GlossaryTree* gt = cdr::GlossaryTrees::get_glossary_tree(language,
                                                                  dictionary,
                                                                  audience);

    // Pick up where we left off in the current word chain from the doc.
    WordChain* chain = &chains[cur_chain];

    // Remember the path in the glossary tree for the current phrase.
    std::stack<cdr::GlossaryNode*> phrase;

    // Keep looking until we run out of word chains.
    while (chain) {

        // Start at the root of the tree.
        cdr::GlossaryNodeMap* current_node_map = &gt->node_map;

        // If we're finished with the current chain, move to the next one.
        int words_left = static_cast<int>(chain->words.size()) -
            chain->cur_word;
        while (words_left < 1) {
            if (++cur_chain >= static_cast<int>(chains.size()))
                return false;
            chain = &chains[cur_chain];
            words_left = (int)chain->words.size();
            if (doc_type == L"Summary")
                gt->clear_flags();
        }

        // Build the longest matching phrase we can from the current position.
        while (static_cast<int>(phrase.size()) < words_left) {
            Word& w = chain->words[chain->cur_word + phrase.size()];
            cdr::GlossaryNodeMap::iterator i = current_node_map->find(w.w);
            if (i == current_node_map->end())
                break;
            phrase.push(i->second);
            current_node_map = &i->second->node_map;
        }

        // Look for a match with a complete glossary phrase.
        while (!phrase.empty()) {

            // Last word has a doc ID if this is a complete phrase; skip
            // over it if we've already marked it up for this chain.
            cdr::GlossaryNode* n = phrase.top();
            if (n->doc_id && !n->marked_up) {

                // Position the range object to include the phrase.
                Word& first_word = chain->words[chain->cur_word];
                Word& last_word  = chain->words[chain->cur_word +
                                               phrase.size() - 1];
                range = first_word.r.get_Duplicate();
                bool glossifiable = true;
                if (!range.ExtendTo(last_word.r))
                    glossifiable = false;

                // Make sure the phrase can be marked up.
                if (glossifiable && !range.get_CanSurround(TAG_NAME))
                    glossifiable = false;

                // Populate the controls of the dialog box.
                if (glossifiable) {
                    CString cdr_id;
                    CString phrase_text = range.get_Text();
                    int i = phrase_text.GetLength();
                    const wchar_t* end_punct = L".;:,";

                    // Back up in front of trailing punctuation.
                    if (i > 0 && _tcschr(end_punct, phrase_text[i - 1])) {
                        ::CRange end_point = last_word.r.get_Duplicate();
                        end_point.Collapse(0);
                        while (i-- > 0 && _tcschr(end_punct, phrase_text[i]))
                            end_point.MoveLeft(0); // Broken; bug in XMetaL.
                        phrase_text.TrimRight(end_punct);
                        range = first_word.r.get_Duplicate();
                        if (!range.ExtendTo(end_point))
                            glossifiable = false;
                        else if (!range.get_CanSurround(TAG_NAME))
                            glossifiable = false;
                    }
                    if (glossifiable) {
                        CString name = gt->names[n->doc_id];
                        cdr_id.Format(L"CDR%010d; %s", n->doc_id, name);
                        m_phrase.SetWindowText(phrase_text);
                        m_markup.SetWindowText(cdr_id);
                        range.Select();

                        // Skip past the current phrase.
                        chain->cur_word += (int)phrase.size();
                        cur_node = n;
                        return true;
                    }
                }
            }

            // Shrink the phrase by one word.
            phrase.pop();
        }

        // Can't use the current word in a glossary phrase; skip past it.
        ++chain->cur_word;
    }

    // Make lint happy (but we'll never reach here).
    return false;
}

BOOL CGlossify::OnInitDialog() {
    CDialog::OnInitDialog();

    ::CDOMNode doc_element = doc.get_documentElement();
    cdr::GlossaryTrees::get_glossary_tree(language, dictionary,
                                          audience)->clear_flags();
    find_chains(doc_element);

    if (chains.empty()) {
        ::AfxMessageBox(L"No glossifiable sections found");
        OnCancel();
    }
    if (!find_next_match()) {
        ::AfxMessageBox(L"No glossifiable phrases found");
        OnCancel();
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CGlossify::OnBnClickedGlossifyNextSection() {

    // We're done if there are no more word chains to look at.
    if (cur_chain < static_cast<int>(chains.size()))
        ++cur_chain;
    if (!find_next_match()) {
        ::AfxMessageBox(L"No more glossary phrases found");
        OnOK();
    }
}

void CGlossify::OnBnClickedGlossifyPreview() {
    if (cur_node) {
        CString url;
        const CString host = cdr::Socket::get_host_name();
        url.Format(L"https://%s/cgi-bin/cdr/PublishPreview.py?DocId=%d",
                   host, cur_node->doc_id);
        //::AfxMessageBox(url);
        cdr::show_page(url);
    }
}
