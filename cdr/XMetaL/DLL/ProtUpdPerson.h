#if !defined(AFX_PROTUPDPERSON_H__03BB27E6_4A41_4514_836A_AAB1841749DF__INCLUDED_)
#define AFX_PROTUPDPERSON_H__03BB27E6_4A41_4514_836A_AAB1841749DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProtUpdPerson.h : header file
//

#include "CdrUtil.h"

/////////////////////////////////////////////////////////////////////////////
// CProtUpdPerson dialog

class CProtUpdPerson : public CDialog
{
// Construction
public:
	CProtUpdPerson(const CString& lo, 
                   CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProtUpdPerson)
	enum { IDD = IDD_PROT_UPD_PERSON };
	CListBox	m_linkList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtUpdPerson)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProtUpdPerson)
	virtual void OnOK();
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CString leadOrg;
    cdr::DocSet docSet;
    void extractChoices(const CString&);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTUPDPERSON_H__03BB27E6_4A41_4514_836A_AAB1841749DF__INCLUDED_)
