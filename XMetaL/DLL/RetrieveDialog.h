#if !defined(AFX_RETRIEVEDIALOG_H__C48BA5B6_D520_4A16_8B3B_1A6163490A50__INCLUDED_)
#define AFX_RETRIEVEDIALOG_H__C48BA5B6_D520_4A16_8B3B_1A6163490A50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RetrieveDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RetrieveDialog dialog

class RetrieveDialog : public CDialog
{
// Construction
public:
	RetrieveDialog(CWnd* parent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RetrieveDialog)
	enum { IDD = IDD_RETRIEVE_DIALOG };
	CString	m_doc_id;
	BOOL	m_check_out;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RetrieveDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* dx);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RetrieveDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RETRIEVEDIALOG_H__C48BA5B6_D520_4A16_8B3B_1A6163490A50__INCLUDED_)
