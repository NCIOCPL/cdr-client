#pragma once


// CDROptions2 dialog

class CDROptions : public CDialog
{
	DECLARE_DYNAMIC(CDROptions)

public:
	CDROptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDROptions();

// Dialog Data
	enum { IDD = IDD_Options };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString ticket_Server;
	CString ticket_Port;
	CString cdr_Server;
	CString cdr_Port;
	afx_msg void OnBnClickedOk();
};
