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
    enum Type { NORMAL, LEAD_ORG, PROT_PERSON, ORG_LOCATION };
    CEditElement(const CString&, const CString&, Type = NORMAL,
                 CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditElement)
	enum { IDD = IDD_LINK_EDIT_DIALOG };
	CStatic	m_label;
	CListBox	m_linkList;
	CString	m_title;
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
    CString         docType;
    CString         element;
    Type            type;
    cdr::DocSet     docSet;
    void            insertLeadOrg(const CString& str);
    bool            insertProtPerson(const CString& str);
    bool            insertOrgLocation(const CString& str);
    void            extractLeadOrgs(const CString& str);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITELEMENT_H__EE520FAC_5378_48F2_AF25_8BC96F4F531B__INCLUDED_)
