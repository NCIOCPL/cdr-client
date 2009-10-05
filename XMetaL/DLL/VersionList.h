#if !defined(AFX_VERSIONLIST_H__9E7832DC_AA07_4D16_82AA_99B736947E27__INCLUDED_)
#define AFX_VERSIONLIST_H__9E7832DC_AA07_4D16_82AA_99B736947E27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VersionList.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CVersionList dialog

class CVersionList : public CDialog
{
// Construction
public:
	CVersionList(const CString& docId, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CVersionList)
	enum { IDD = IDD_VERSION_LIST };
	CListBox	m_choiceList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVersionList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
    CString docId;

protected:

	// Generated message map functions
	//{{AFX_MSG(CVersionList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERSIONLIST_H__9E7832DC_AA07_4D16_82AA_99B736947E27__INCLUDED_)
