#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "CdrUtil.h"

// CReviewMarkup dialog

class CReviewMarkup : public CDialog
{
	DECLARE_DYNAMIC(CReviewMarkup)

public:
	CReviewMarkup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReviewMarkup();

// Dialog Data
	enum { IDD = IDD_REVIEW_MARKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CStatic markupUser;
    CStatic markupDate;
    CStatic markupContent;
    CButton acceptButton;
    CButton rejectButton;
    afx_msg void OnBnClickedNextMarkup();
    virtual BOOL OnInitDialog();

private:
    bool findNextMarkup();
public:
    CStatic reviewLevel;
    afx_msg void OnBnClickedAccept();
    afx_msg void OnBnClickedReject();
    CStatic markupSource;
};
