#if !defined(AFX_LOGONPROGRESS_H__D742A109_5C24_11D5_911C_00A0C9EA3906__INCLUDED_)
#define AFX_LOGONPROGRESS_H__D742A109_5C24_11D5_911C_00A0C9EA3906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogonProgress.h : header file
//
#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CLogonProgress dialog

class CLogonProgress : public CDialog
{

private:
    bool userCancelled;
    bool created;

// Construction
public:
	CLogonProgress(CWnd* pParent = NULL);   // standard constructor
    bool keepGoing() const { return !userCancelled; }
    bool ready() const { return created; }

// Dialog Data
	//{{AFX_DATA(CLogonProgress)
	enum { IDD = IDD_DIALOG8 };
	CStatic	m_generalProgressText;
	CStatic	m_currentActivityText;
	CProgressCtrl	m_progressBar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogonProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogonProgress)
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGONPROGRESS_H__D742A109_5C24_11D5_911C_00A0C9EA3906__INCLUDED_)
