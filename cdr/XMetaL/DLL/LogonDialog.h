#if !defined(AFX_LOGONDIALOG_H__60170240_BAF5_4C15_8223_6CD8751A092D__INCLUDED_)
#define AFX_LOGONDIALOG_H__60170240_BAF5_4C15_8223_6CD8751A092D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogonDialog.h : header file
//

#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// LogonDialog dialog

class LogonDialog : public CDialog
{
// Construction
public:
	LogonDialog(CWnd* pParent = NULL);   // standard constructor
    bool keepGoing() const { return !userCancelled; }

// Dialog Data
	//{{AFX_DATA(LogonDialog)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_okButton;
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
	virtual void OnCancel();
	afx_msg void OnLogonOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    bool userCancelled;
    bool loggingOn;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGONDIALOG_H__60170240_BAF5_4C15_8223_6CD8751A092D__INCLUDED_)
