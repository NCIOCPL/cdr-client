#pragma once
#include "afxcmn.h"
#include "Resource.h"


// CDRProgress dialog

class CDRProgress : public CDialog
{
	DECLARE_DYNAMIC(CDRProgress)

public:
	CDRProgress(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDRProgress();

	void Advance( void );
	void Init( void );

// Dialog Data
	enum { IDD = IDD_PleaseWait };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl ProgressBar;
};
