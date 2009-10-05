/*
 * $Id: ServerSettingsDlg.cpp,v 1.3 2009-09-23 18:35:29 bkline Exp $
 *
 * Implementation for object used to track and manipulate values for
 * connecting with the CDR servers.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/11/08 22:11:02  bkline
 * Cleanup of initial CVS comments.
 *
 * Revision 1.1  2005/11/08 21:30:22  bkline
 * Rewrite of CDR loader.
 */
#include "stdafx.h"
#include "CdrClient.h"
#include "ServerSettingsDlg.h"

/*
 * Constructor for the dialog object.  Populates the data members
 * of the class's object using values passed in with the
 * ServerSettings object, which in turn was created from the
 * XML document in which this information is remembered between
 * runs of the program.
 *
 * See the comments in the header file for this object's interface
 * for more information on the data members.  See CdrClient.h
 * for an explanation of the ServerSettings type.
 */
IMPLEMENT_DYNAMIC(ServerSettingsDlg, CDialog)
ServerSettingsDlg::ServerSettingsDlg(ServerSettings* settings, 
                                     CWnd* pParent /*=NULL*/)
	: CDialog(ServerSettingsDlg::IDD, pParent)
    , prodUpdateServer(_T(""))
    , prodUpdatePort(_T(""))
    , prodCdrServer(_T(""))
    , prodCdrPort(_T(""))
    , testUpdateServer(_T(""))
    , testUpdatePort(_T(""))
    , testCdrServer(_T(""))
    , testCdrPort(_T(""))
    , devUpdateServer(_T(""))
    , devUpdatePort(_T(""))
    , devCdrServer(_T(""))
    , devCdrPort(_T(""))
    , ss(settings) {

    ServerSettings::ServerGroup* sg = ss->findGroup(PROD_GROUP);
    if (sg) {
        prodUpdateServer = sg->updateServer;
        prodUpdatePort   = sg->updatePort;
        prodCdrServer    = sg->cdrServer;
        prodCdrPort      = sg->cdrPort;
    }
    sg = ss->findGroup(TEST_GROUP);
    if (sg) {
        testUpdateServer = sg->updateServer;
        testUpdatePort   = sg->updatePort;
        testCdrServer    = sg->cdrServer;
        testCdrPort      = sg->cdrPort;
    }
    sg = ss->findGroup(DEV_GROUP);
    if (sg) {
        devUpdateServer  = sg->updateServer;
        devUpdatePort    = sg->updatePort;
        devCdrServer     = sg->cdrServer;
        devCdrPort       = sg->cdrPort;
    }
}

ServerSettingsDlg::~ServerSettingsDlg() {}

void ServerSettingsDlg::DoDataExchange(CDataExchange* pDX) {
    
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_PROD_UPDATE_SERVER, prodUpdateServer);
    DDX_Text(pDX, IDC_PROD_UPDATE_PORT, prodUpdatePort);
    DDX_Text(pDX, IDC_PROD_CDR_SERVER, prodCdrServer);
    DDX_Text(pDX, IDC_PROD_CDR_PORT, prodCdrPort);
    DDX_Text(pDX, IDC_TEST_UPDATE_SERVER, testUpdateServer);
    DDX_Text(pDX, IDC_TEST_UPDATE_PORT, testUpdatePort);
    DDX_Text(pDX, IDC_TEST_CDR_SERVER, testCdrServer);
    DDX_Text(pDX, IDC_TEST_CDR_PORT, testCdrPort);
    DDX_Text(pDX, IDC_DEV_UPDATE_SERVER, devUpdateServer);
    DDX_Text(pDX, IDC_DEV_UPDATE_PORT, devUpdatePort);
    DDX_Text(pDX, IDC_DEV_CDR_SERVER, devCdrServer);
    DDX_Text(pDX, IDC_DEV_CDR_PORT, devCdrPort);
}


BEGIN_MESSAGE_MAP(ServerSettingsDlg, CDialog)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


/*
 * If the user clicks the OK button, remember the (possibly) changed
 * values by refreshing the ServerSettings object passed into the
 * constructor for this object.
 */
void ServerSettingsDlg::OnBnClickedOk() {
	CDataExchange dx(this, true);
	DoDataExchange(&dx);
    ServerSettings::ServerGroup* sg = ss->findGroup(PROD_GROUP);
    if (sg) {
        sg->updateServer = prodUpdateServer;
        sg->updatePort   = prodUpdatePort;
        sg->cdrServer    = prodCdrServer;
        sg->cdrPort      = prodCdrPort;
    }
    sg = ss->findGroup(TEST_GROUP);
    if (sg) {
        sg->updateServer = testUpdateServer;
        sg->updatePort   = testUpdatePort;
        sg->cdrServer    = testCdrServer;
        sg->cdrPort      = testCdrPort;
    }
    sg = ss->findGroup(DEV_GROUP);
    if (sg) {
        sg->updateServer = devUpdateServer;
        sg->updatePort   = devUpdatePort;
        sg->cdrServer    = devCdrServer;
        sg->cdrPort      = devCdrPort;
    }
    switch (GetCheckedRadioButton(IDC_PROD, IDC_DEV)) {
        case IDC_PROD:
            ss->currentGroup = PROD_GROUP;
            break;
        case IDC_TEST:
            ss->currentGroup = TEST_GROUP;
            break;
        case IDC_DEV:
            ss->currentGroup = DEV_GROUP;
            break;
        default:
            ss->currentGroup = _T("");
            break;
    }
    OnOK();
}

/*
 * Check the correct radio button for the currently selected server
 * group.
 */
BOOL ServerSettingsDlg::OnInitDialog() {
    
    CDialog::OnInitDialog();

    if (ss->currentGroup == PROD_GROUP)
        CheckRadioButton(IDC_PROD, IDC_DEV, IDC_PROD);
    else if (ss->currentGroup == TEST_GROUP)
        CheckRadioButton(IDC_PROD, IDC_DEV, IDC_TEST);
    else if (ss->currentGroup == DEV_GROUP)
        CheckRadioButton(IDC_PROD, IDC_DEV, IDC_DEV);
    return TRUE;  // return TRUE unless you set the focus to a control
}
