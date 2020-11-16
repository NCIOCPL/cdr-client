#if !defined(AFX_PASSEDVALIDATION_H__4E5929BC_79DE_4ED6_8267_DB482B9F1FE6__INCLUDED_)
#define AFX_PASSEDVALIDATION_H__4E5929BC_79DE_4ED6_8267_DB482B9F1FE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassedValidation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPassedValidation dialog

class CPassedValidation : public CDialog
{
// Construction
public:
	CPassedValidation(const CString& id,
					  CWnd* parent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassedValidation)
	enum { IDD = IDD_VALIDATION_PASSED };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassedValidation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassedValidation)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString doc_id;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSEDVALIDATION_H__4E5929BC_79DE_4ED6_8267_DB482B9F1FE6__INCLUDED_)
