#if !defined(AFX_SAVEDIALOG_H__A7704207_A1DB_4D11_8325_B0876F2DA135__INCLUDED_)
#define AFX_SAVEDIALOG_H__A7704207_A1DB_4D11_8325_B0876F2DA135__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveDialog dialog

class CSaveDialog : public CDialog
{
// Construction
public:
	CSaveDialog(const CString&, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CSaveDialog)
	enum { IDD = IDD_DIALOG4 };
	BOOL	m_validate;
	BOOL	m_checkIn;
	CString	m_title;
	CString	m_comment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEDIALOG_H__A7704207_A1DB_4D11_8325_B0876F2DA135__INCLUDED_)
