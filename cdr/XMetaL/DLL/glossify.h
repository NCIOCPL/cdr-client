#pragma once

#include "resource.h"
#include "afxwin.h"
#include "CdrUtil.h"
#include <vector>

#if 0
struct GlossaryPhraseWord {
    CString            w;
    ::Range            r;
    cdr::GlossaryNode* n;
    GlossaryPhraseWord(::Range rng) : r(rng), w(r.GetText()), n(0)
    { w.MakeUpper(); }
    // int level;
    // bool leftEdge, rightEdge;
    // DOMNode node;
    // int startPos;
    // int len;
    /*
    GlossaryPhraseWord(const CString& wd, int lev, int sp, 
        DOMNode& n, int ln, bool le = false, bool re = false)
        : w(wd), level(lev), startPos(sp), node(n), 
		  len(ln), leftEdge(le), rightEdge(re)
	      { w.MakeUpper(); }
    */
};
#endif

// typedef std::vector<GlossaryPhraseWord> GlossaryPhraseChain;
// typedef std::vector<GlossaryPhraseChain> GlossaryPhraseChains;
// typedef std::vector<DOMNode> DomNodeVector;

// CGlossify dialog

class CGlossify : public CDialog
{
	DECLARE_DYNAMIC(CGlossify)

private:
    struct Word {
        CString            w;
        ::Range            r;
        Word(::Range r_)
        { 
            r = r_;
            w = r.GetText();
            w.MakeUpper(); 
        }
    };
    typedef std::vector<Word>    WordVector;
    //typedef WordVector::iterator WordVectorIter;
    struct WordChain {
        WordVector words;
        int        curWord;
        WordChain(::DOMNode node, ::_Document doc);
    };
    typedef std::vector<WordChain> WordChains;

public:
	CGlossify(CWnd* pParent = NULL);   // standard constructor
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
    void                 findChains(DOMNode& n);
    bool                 findNextMatch();
    // GlossaryPhraseChains chains;
    // int                  curWord;
	// ::Range              endRange;
    // DomNodeVector        glossifiableSections;
public:
    afx_msg void OnSkip();
    afx_msg void OnDone();
    afx_msg void OnMarkup();
    virtual BOOL OnInitDialog();
};
