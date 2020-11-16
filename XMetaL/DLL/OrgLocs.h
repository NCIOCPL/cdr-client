#if !defined(AFX_ORGLOCS_H__4337FDAD_0DAA_4E03_844A_2BFD93FBE25E__INCLUDED_)
#define AFX_ORGLOCS_H__4337FDAD_0DAA_4E03_844A_2BFD93FBE25E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OrgLocs.h : header file
//

#include "CdrUtil.h"

/////////////////////////////////////////////////////////////////////////////
// COrgLocs dialog

class COrgLocs : public CDialog
{
// Construction
public:
	COrgLocs(const CString& doc_id, CString& new_targ,
             CWnd* parent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COrgLocs)
	enum { IDD = IDD_ORG_LOCS };
	CListBox	m_choice_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrgLocs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrgLocs)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CString doc_id;
    cdr::DocSet doc_set;
    CString& new_target;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORGLOCS_H__4337FDAD_0DAA_4E03_844A_2BFD93FBE25E__INCLUDED_)
