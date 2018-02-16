/*
 * Implementation for object used to track and manipulate values for
 * connecting with the CDR servers.
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
    , prodCDRServer(_T(""))
    , prodAPIServer(_T(""))
    , stageCDRServer(_T(""))
    , stageAPIServer(_T(""))
    , qaCDRServer(_T(""))
    , qaAPIServer(_T(""))
    , devCDRServer(_T(""))
    , devAPIServer(_T(""))
    , ss(settings) {

    ServerSettings::ServerGroup* sg = ss->findGroup(PROD_TIER);
    if (sg) {
        prodCDRServer = sg->cdrServer;
        prodAPIServer = sg->apiServer;
    }
    sg = ss->findGroup(STAGE_TIER);
    if (sg) {
        stageCDRServer = sg->cdrServer;
        stageAPIServer = sg->apiServer;
    }
    sg = ss->findGroup(QA_TIER);
    if (sg) {
        qaCDRServer = sg->cdrServer;
        qaAPIServer = sg->apiServer;
    }
    sg = ss->findGroup(DEV_TIER);
    if (sg) {
        devCDRServer = sg->cdrServer;
        devAPIServer = sg->apiServer;
    }
}

ServerSettingsDlg::~ServerSettingsDlg() {}

void ServerSettingsDlg::DoDataExchange(CDataExchange* pDX) {

    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_PROD_CDR_SERVER, prodCDRServer);
    DDX_Text(pDX, IDC_PROD_API_SERVER, prodAPIServer);
    DDX_Text(pDX, IDC_STAGE_CDR_SERVER, stageCDRServer);
    DDX_Text(pDX, IDC_STAGE_API_SERVER, stageAPIServer);
    DDX_Text(pDX, IDC_QA_CDR_SERVER, qaCDRServer);
    DDX_Text(pDX, IDC_QA_API_SERVER, qaAPIServer);
    DDX_Text(pDX, IDC_DEV_CDR_SERVER, devCDRServer);
    DDX_Text(pDX, IDC_DEV_API_SERVER, devAPIServer);
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
    ServerSettings::ServerGroup* sg = ss->findGroup(PROD_TIER);
    if (sg) {
        sg->cdrServer = prodCDRServer;
        sg->apiServer = prodAPIServer;
    }
    sg = ss->findGroup(STAGE_TIER);
    if (sg) {
        sg->cdrServer = stageCDRServer;
        sg->apiServer = stageAPIServer;
    }
    sg = ss->findGroup(QA_TIER);
    if (sg) {
        sg->cdrServer = qaCDRServer;
        sg->apiServer = qaAPIServer;
    }
    sg = ss->findGroup(DEV_TIER);
    if (sg) {
        sg->cdrServer = devCDRServer;
        sg->apiServer = devAPIServer;
    }
    switch (GetCheckedRadioButton(IDC_PROD_TIER, IDC_DEV_TIER)) {
        case IDC_PROD_TIER:
            ss->currentGroup = PROD_TIER;
            break;
        case IDC_STAGE_TIER:
            ss->currentGroup = STAGE_TIER;
            break;
        case IDC_QA_TIER:
            ss->currentGroup = QA_TIER;
            break;
        case IDC_DEV_TIER:
            ss->currentGroup = DEV_TIER;
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

    if (ss->currentGroup == PROD_TIER)
        CheckRadioButton(IDC_PROD_TIER, IDC_DEV_TIER, IDC_PROD_TIER);
    else if (ss->currentGroup == STAGE_TIER)
        CheckRadioButton(IDC_PROD_TIER, IDC_DEV_TIER, IDC_STAGE_TIER);
    else if (ss->currentGroup == QA_TIER)
        CheckRadioButton(IDC_PROD_TIER, IDC_DEV_TIER, IDC_QA_TIER);
    else if (ss->currentGroup == DEV_TIER)
        CheckRadioButton(IDC_PROD_TIER, IDC_DEV_TIER, IDC_DEV_TIER);
    return TRUE;  // return TRUE unless you set the focus to a control
}
