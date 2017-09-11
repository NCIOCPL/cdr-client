#pragma once
#include "afxwin.h"


// CCommentDialog dialog

class CCommentDialog : public CDialog
{
	DECLARE_DYNAMIC(CCommentDialog)

public:
	CCommentDialog(BOOL ro = false, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCommentDialog();

// Dialog Data
	enum { IDD = IDD_COMMENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CEdit m_comment;
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
private:
    BOOL readOnly;
};
