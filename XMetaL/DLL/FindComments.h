#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "CdrUtil.h"

// CFindComments dialog

class CFindComments : public CDialog
{
	DECLARE_DYNAMIC(CFindComments)

public:
	CFindComments(CWnd* parent = NULL);   // standard constructor
	virtual ~CFindComments();

// Dialog Data
	enum { IDD = IDD_FIND_COMMENTS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CButton next_button;
    CButton prev_button;
    afx_msg void OnBnClickedNextComment();
    afx_msg void OnBnClickedPrevComment();
    virtual BOOL OnInitDialog();
    virtual void PostNcDestroy();
    virtual void OnOK();
    virtual void OnCancel();

private:
    void find_comment(bool);
};
