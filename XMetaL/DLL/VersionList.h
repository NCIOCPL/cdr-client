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
    CVersionList(const CString& doc_id, CWnd* parent = NULL);

// Dialog Data
    //{{AFX_DATA(CVersionList)
    enum { IDD = IDD_VERSION_LIST };
    CListBox    m_choice_list;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVersionList)
    protected:
    virtual void DoDataExchange(CDataExchange* dx);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
private:
    CString doc_id;

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
