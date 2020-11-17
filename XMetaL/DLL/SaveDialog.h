#include "afxwin.h"
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
    CSaveDialog(bool ready_for_review, bool blob_possible = false,
                CWnd* parent = NULL);

// Dialog Data
    //{{AFX_DATA(CSaveDialog)
    enum { IDD = IDD_SAVE_DIALOG };
    BOOL    m_validate;
    BOOL    m_checkIn;
    CString m_comment;
    BOOL    m_create_version;
    BOOL    m_version_publishable;
    BOOL    m_doc_inactive;
    BOOL    m_ready_for_review;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSaveDialog)
    protected:
    virtual void DoDataExchange(CDataExchange* dx);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CSaveDialog)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCheck4();
    afx_msg void OnBnClickedCheck3();
    afx_msg void OnBnClickedCheck1();
private:
    void fix_checkboxes();
public:
    virtual BOOL OnInitDialog();
private:
    CButton m_ready_for_review_checkbox;
    bool    m_blob_possible;
public:
    afx_msg void OnBnClickedMediaFileBrowse();
    CEdit m_blob_filename;
    CString m_blob_filename_string;
    CButton m_browse_button;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEDIALOG_H__A7704207_A1DB_4D11_8325_B0876F2DA135__INCLUDED_)
