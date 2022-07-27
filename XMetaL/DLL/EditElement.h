#if !defined(AFX_EDITELEMENT_H__EE520FAC_5378_48F2_AF25_8BC96F4F531B__INCLUDED_)
#define AFX_EDITELEMENT_H__EE520FAC_5378_48F2_AF25_8BC96F4F531B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditElement.h : header file
//

#include "CdrUtil.h"
#include <string>

/////////////////////////////////////////////////////////////////////////////
// CEditElement dialog

class CEditElement : public CDialog
{
// Construction
public:
    enum Type { NORMAL, ORG_LOCATION, GP_SYNDROME };
    CEditElement(const CString&, const CString&, Type = NORMAL,
                 CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CEditElement)
    enum { IDD = IDD_LINK_EDIT_DIALOG };
    CStatic    m_label;
    CListBox    m_link_list;
    CString    m_title;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CEditElement)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CEditElement)
    virtual void OnOK();
    afx_msg void OnSelectButton();
    afx_msg void OnDblclkLink();
    afx_msg void OnButton2();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    CString         doc_type;
    CString         element;
    Type            type;
    cdr::DocSet     doc_set;
    bool            insert_org_location(const CString& str);
    void            extract_genetics_syndromes(cdr::DOM& dom);
    CFont           bigger_font;
public:
    afx_msg void OnLbnSelchangeList1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITELEMENT_H__EE520FAC_5378_48F2_AF25_8BC96F4F531B__INCLUDED_)
