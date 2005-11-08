/*
 * $Id: CdrLogin.cpp,v 1.2 2005-11-08 22:11:02 bkline Exp $
 *
 * Implementation for dialog window object used to connect to the
 * CDR server and obtain a session ID.  Collects user ID and password,
 * and allows the user to invoke a second overlaid dialog window
 * in which the values for connecting to the servers (DNS names and
 * ports) can be modified before connecting.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/11/08 21:30:21  bkline
 * Rewrite of CDR loader.
 */
#include "stdafx.h"
#include "CdrClient.h"
#include "CdrLogin.h"
#include "ServerSettingsDlg.h"

IMPLEMENT_DYNAMIC(CdrLoginDlg, CDialog)
CdrLoginDlg::CdrLoginDlg(ServerSettings* serverSettings,
                         CWnd* pParent /*=NULL*/)
     : CDialog(CdrLoginDlg::IDD, pParent)
      , ss(serverSettings) {}

CdrLoginDlg::~CdrLoginDlg()
{
}

void CdrLoginDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_USER_ID, userId);
    DDX_Control(pDX, IDC_PASSWORD, password);
}

BEGIN_MESSAGE_MAP(CdrLoginDlg, CDialog)
    ON_BN_CLICKED(IDC_OPTIONS, OnBnClickedOptions)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/*
 * Bring up a second dialog window with controls for modifying the
 * values used to connect to the CDR server and the client update
 * server.
 */
void CdrLoginDlg::OnBnClickedOptions() {
    ServerSettingsDlg dlg(ss);
    dlg.DoModal();
}

/*
 * Populate the user ID field from the locally serialized settings,
 * but leave the password blank.
 */
BOOL CdrLoginDlg::OnInitDialog() {
    
    CDialog::OnInitDialog();
    userId.SetWindowText(ss->currentUser);
    return TRUE;  // return TRUE unless you set the focus to a control
}

/*
 * User has confirmed the request to log in.  The actual login command
 * will be submitted by the caller.  All we need to do here is transfer
 * the values from the controls to the string data members.
 */
void CdrLoginDlg::OnBnClickedOk() {

	// Make sure we have the current data.
    CDataExchange dx(this, true);
    DoDataExchange(&dx);
    userId.GetWindowText(uid);
    password.GetWindowText(pwd);
    this->OnOK();
}
