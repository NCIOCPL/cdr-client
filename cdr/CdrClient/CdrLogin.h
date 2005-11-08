/*
 * $Id: CdrLogin.h,v 1.2 2005-11-08 22:11:02 bkline Exp $
 *
 * Interface for dialog window used to log into the CDR (with controls
 * for adjusting the values used for connecting to the servers).  There
 * are data members for the user id and password controls, and corresponding
 * string data members for both of these.  There is also a pointer to
 * a ServerSettings object, which is passed to the constructor for the
 * dialog object for viewing/adjusting the values used to connect to the
 * CDR servers.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/11/08 21:30:21  bkline
 * Rewrite of CDR loader.
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
