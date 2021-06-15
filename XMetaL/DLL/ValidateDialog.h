#if !defined(AFX_VALIDATEDIALOG_H__3C8584D7_1A92_404F_B9E8_A087ADDFFE1E__INCLUDED_)
#define AFX_VALIDATEDIALOG_H__3C8584D7_1A92_404F_B9E8_A087ADDFFE1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ValidateDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CValidateDialog dialog

class CValidateDialog : public CDialog
{
// Construction
public:
	CValidateDialog(CWnd* parent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CValidateDialog)
	enum { IDD = IDD_VALIDATE_DIALOG };
	BOOL	m_schema_validation;
	BOOL	m_link_validation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValidateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* dx);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CValidateDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_include_approved_markup;
	BOOL m_include_proposed_and_approved_markup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALIDATEDIALOG_H__3C8584D7_1A92_404F_B9E8_A087ADDFFE1E__INCLUDED_)
