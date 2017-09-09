/*
 * Interface for dialog window used to log into the CDR (with controls
 * for adjusting the values used for connecting to the servers).  There
 * are data members for the user id and password controls, and corresponding
 * string data members for both of these.  There is also a pointer to
 * a ServerSettings object, which is passed to the constructor for the
 * dialog object for viewing/adjusting the values used to connect to the
 * CDR servers.
 */
#pragma once
#include "afxwin.h"

struct ServerSettings;

class CdrLoginDlg : public CDialog {
    
	DECLARE_DYNAMIC(CdrLoginDlg)

public:
	CdrLoginDlg(ServerSettings* serverSettings,
                CWnd* pParent = NULL);   // standard constructor
	virtual ~CdrLoginDlg();

// Dialog Data
	enum { IDD = IDD_CDR_CLIENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CEdit userId;
    CEdit password;
    CString uid;
    CString pwd;
    afx_msg void OnBnClickedOptions();

private:
    ServerSettings* ss;

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
};
