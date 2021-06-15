#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "CdrUtil.h"

// CReviewMarkup dialog

class CReviewMarkup : public CDialog
{
	DECLARE_DYNAMIC(CReviewMarkup)

public:
	CReviewMarkup(CWnd* parent = NULL);   // standard constructor
	virtual ~CReviewMarkup();

// Dialog Data
	enum { IDD = IDD_REVIEW_MARKUP };

protected:
	virtual void DoDataExchange(CDataExchange* dx);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CStatic markup_user;
    CStatic markup_date;
    CStatic markup_content;
    CButton accept_button;
    CButton reject_button;
    afx_msg void OnBnClickedNextMarkup();
    virtual BOOL OnInitDialog();

private:
    bool find_next_markup();
public:
    CStatic review_level;
    afx_msg void OnBnClickedAccept();
    afx_msg void OnBnClickedReject();
    CStatic markup_source;
};
