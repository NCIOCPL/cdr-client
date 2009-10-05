// LogonDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LogonDialog.h"
#include "Cdr.h"
#include "Commands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LogonDialog dialog


LogonDialog::LogonDialog(CWnd* pParent /*=NULL*/)
	: CDialog(LogonDialog::IDD, pParent), userCancelled(false),
                                          loggingOn(false)
{
	//{{AFX_DATA_INIT(LogonDialog)
	m_UserId = _T("");
	m_Password = _T("");
	//}}AFX_DATA_INIT
}


void LogonDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LogonDialog)
	DDX_Control(pDX, ID_LOGON_OK, m_okButton);
	DDX_Text(pDX, IDC_EDIT1, m_UserId);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LogonDialog, CDialog)
	//{{AFX_MSG_MAP(LogonDialog)
	ON_BN_CLICKED(ID_LOGON_OK, OnLogonOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LogonDialog message handlers

void LogonDialog::OnCancel() 
{
    if (loggingOn) {
        userCancelled = true;	
        loggingOn = false;
    }
    else
        CDialog::OnCancel();
}

void LogonDialog::OnLogonOk() 
{
    userCancelled = false;
    loggingOn = true;
    UpdateData(true);
    //CWaitCursor wc;
    m_okButton.EnableWindow(FALSE);
    if (CCommands::doLogon(this))
        EndDialog(IDOK);
    m_okButton.EnableWindow(TRUE);
    loggingOn = false;
}
