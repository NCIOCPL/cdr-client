#if !defined(AFX_SCHEMAPICKLIST_H__B6961551_4AC9_11D5_911B_00A0C9EA3906__INCLUDED_)
#define AFX_SCHEMAPICKLIST_H__B6961551_4AC9_11D5_911B_00A0C9EA3906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SchemaPicklist.h : header file
//

#include "CdrUtil.h"

/////////////////////////////////////////////////////////////////////////////
// CSchemaPicklist dialog

class CSchemaPicklist : public CDialog
{
// Construction
public:
    CSchemaPicklist(const cdr::StringList* values,
                    const CString& current_value,
                    const CString& element_name,
                    CWnd* parent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CSchemaPicklist)
    enum { IDD = IDD_SCHEMA_PICKLIST };
    CListBox    m_list_box;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSchemaPicklist)
    protected:
    virtual void DoDataExchange(CDataExchange* dx);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CSchemaPicklist)
    afx_msg void OnDblclkList1();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    const cdr::StringList* vv_set;
    const CString& cur_val;
    const CString& elem_name;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEMAPICKLIST_H__B6961551_4AC9_11D5_911B_00A0C9EA3906__INCLUDED_)
