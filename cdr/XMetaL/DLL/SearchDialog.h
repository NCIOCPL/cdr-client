#if !defined(AFX_SEARCHDIALOG_H__D525FB27_B6F5_4AB4_B039_E56A3240A1BC__INCLUDED_)
#define AFX_SEARCHDIALOG_H__D525FB27_B6F5_4AB4_B039_E56A3240A1BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDialog.h : header file
//

#include <string>
#include <list>

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog dialog

class CSearchDialog : public CDialog
{
// Construction
public:
	CSearchDialog(const std::list<CString>& docTypes,
		          CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchDialog)
	enum { IDD = IDD_SEARCH_DIALOG };
	CComboBox	m_docTypes;
	CListBox	m_docList;
	CButton	m_retrieveButton;
	CButton	m_searchButton;
	CButton	m_cancelButton;
	CButton	m_titleEquals;
	CButton	m_titleContains;
	CButton	m_titleStart;
	CString	m_searchString;
	CString	m_version;
	BOOL	m_checkOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDialog)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchDialog)
	afx_msg void OnRetrieveButton();
	afx_msg void OnSearchButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkDocument();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	const std::list<CString>& docTypes;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDIALOG_H__D525FB27_B6F5_4AB4_B039_E56A3240A1BC__INCLUDED_)
