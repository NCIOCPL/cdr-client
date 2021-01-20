#pragma once

#include "resource.h"
#include "afxwin.h"
#include "CdrUtil.h"
#include <vector>

// CGlossify dialog

class CGlossify : public CDialog
{
    DECLARE_DYNAMIC(CGlossify)

private:
    struct Word {
        CString w;
        ::Range r;
        Word(::Range r_) {
            r = r_;
            w = r.GetText();
            w.MakeUpper();
        }
        Word(::Range r_, CString s_) {
            r = r_;
            w = s_;
        }
    };
    typedef std::vector<Word> WordVector;
    struct WordChain {
        WordVector words;
        int        cur_word;
        WordChain(::DOMNode node, ::_Document doc);
    };
    typedef std::vector<WordChain> WordChains;

public:
    // Added argument 'dig' for JIRA ticket OCECDR-3815.
    // Controls whether we should dig through the layers
    // of Insertion and Deletion elements to find what
    // would otherwise be top-level SummarySection
    // elements. Default is to glossify only SummarySections
    // which are actually top-level children of the
    // document's root element.
    CGlossify(bool dig=false, const CString dictionary = L"",
              const CString audience = L"", CWnd* parent = NULL);
    virtual ~CGlossify();

// Dialog Data
    enum { IDD = IDD_GLOSSIFY_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* dx);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
private:
    CEdit                m_phrase;
    CEdit                m_markup;
    CString              doc_type;
    ::_Document          doc;
    ::Range              range;
    WordChains           chains;
    int                  cur_chain;
    cdr::GlossaryNode*   cur_node;
    void                 find_chains(DOMNode& n);
    void                 keep_digging(::DOMNode& n, ::_Document& doc);
    bool                 find_next_match();
    CString              language;
    CString              dictionary;
    CString              audience;
    bool                 m_dig;
public:
    afx_msg void OnSkip();
    afx_msg void OnDone();
    afx_msg void OnMarkup();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedGlossifySkipFirst();
    afx_msg void OnBnClickedGlossifyNextSection();
};
