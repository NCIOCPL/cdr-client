#pragma once
#include "afxwin.h"


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
	CString test_ticket_Server;
	CString test_ticket_Port;
	CString test_cdr_Server;
	CString test_cdr_Port;
	CString dev_ticket_Server;
	CString dev_ticket_Port;
	CString dev_cdr_Server;
	CString dev_cdr_Port;

	int current_Server;

	afx_msg void OnBnClickedOk();

	BOOL OnInitDialog( void );
	void SetCurrentServer( int cs );
	int GetCurrentServer( void ) { return current_Server; }; 
};
