#if !defined(AFX_LOGONDIALOG_H__60170240_BAF5_4C15_8223_6CD8751A092D__INCLUDED_)
#define AFX_LOGONDIALOG_H__60170240_BAF5_4C15_8223_6CD8751A092D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogonDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LogonDialog dialog

class LogonDialog : public CDialog
{
// Construction
public:
	LogonDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LogonDialog)
	enum { IDD = IDD_DIALOG1 };
	CString	m_UserId;
	CString	m_Password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LogonDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LogonDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGONDIALOG_H__60170240_BAF5_4C15_8223_6CD8751A092D__INCLUDED_)
