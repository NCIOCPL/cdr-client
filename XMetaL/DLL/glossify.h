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
        CString            w;
        ::Range            r;
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
        int        curWord;
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
    CGlossify(bool dig=false, CWnd* pParent = NULL);
    virtual ~CGlossify();

// Dialog Data
    enum { IDD = IDD_GLOSSIFY_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
private:
    CEdit                m_phrase;
    CEdit                m_markup;
    CString              docType;
    ::_Document          doc;
    ::Range              range;
    WordChains           chains;
    int                  curChain;
    cdr::GlossaryNode*   curNode;
    void                 findChains(DOMNode& n);
    void                 keepDigging(::DOMNode& n, ::_Document& doc);
    bool                 findNextMatch();
    CString              language;
    bool                 m_dig;
public:
    afx_msg void OnSkip();
    afx_msg void OnDone();
    afx_msg void OnMarkup();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedGlossifySkipFirst();
    afx_msg void OnBnClickedGlossifyNextSection();
};
