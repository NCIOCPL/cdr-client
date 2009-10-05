// LogonProgress.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Cdr.h"
#include "Commands.h"
#include "LogonProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogonProgress dialog


CLogonProgress::CLogonProgress(CWnd* pParent /*=NULL*/)
: CDialog(CLogonProgress::IDD, pParent), userCancelled(false), created(false)
{
	//{{AFX_DATA_INIT(CLogonProgress)
	//}}AFX_DATA_INIT
}


void CLogonProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogonProgress)
	DDX_Control(pDX, ID_CURRENT_ACTIVITY_TEXT, m_currentActivityText);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogonProgress, CDialog)
	//{{AFX_MSG_MAP(CLogonProgress)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogonProgress message handlers

void CLogonProgress::OnCancel() 
{
    userCancelled = true;
    //m_generalProgressText.SetWindowText(_T("Cancelling CDR Logon ..."));
	//CDialog::OnCancel();
}

int CLogonProgress::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    created = true;
	return 0;
}
