// CDRLoaderDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CCDRLoaderDlg dialog
class CCDRLoaderDlg : public CDialog
{
// Construction
public:
	CCDRLoaderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CDRLOADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	// Access to the user id edit box contents
	CString UserId;
	// Access to the password edit box contents
	CString UserPwd;
	CString SessionId;
	afx_msg void OnBnClickedOk();
	CEdit UserIDControl;
};
