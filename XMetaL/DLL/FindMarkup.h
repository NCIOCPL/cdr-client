#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "CdrUtil.h"

// CFindMarkup dialog

class CFindMarkup : public CDialog
{
	DECLARE_DYNAMIC(CFindMarkup)

public:
	CFindMarkup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFindMarkup();

// Dialog Data
	enum { IDD = IDD_FIND_MARKUP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CButton nextButton;
    CButton prevButton;
    afx_msg void OnBnClickedNextMarkup();
    afx_msg void OnBnClickedPrevMarkup();
    virtual BOOL OnInitDialog();
    virtual void PostNcDestroy();
    virtual void OnOK();
    virtual void OnCancel();

private:
    void findMarkup(bool);
};
