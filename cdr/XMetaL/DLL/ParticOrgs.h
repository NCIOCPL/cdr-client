#if !defined(AFX_PARTICORGS_H__F93C850B_95E2_41D1_B046_BED145ACA0E2__INCLUDED_)
#define AFX_PARTICORGS_H__F93C850B_95E2_41D1_B046_BED145ACA0E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParticOrgs.h : header file
//

#include "CdrUtil.h"

/////////////////////////////////////////////////////////////////////////////
// CParticOrgs dialog

class CParticOrgs : public CDialog
{
// Construction
public:
	CParticOrgs(const CString& lo,
                CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParticOrgs)
	enum { IDD = IDD_PARTIC_ORGS };
	CListBox	m_orgList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParticOrgs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParticOrgs)
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CString leadOrg;
    cdr::DocSet docSet;
    void    extractChoices(const CString& rsp);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARTICORGS_H__F93C850B_95E2_41D1_B046_BED145ACA0E2__INCLUDED_)
