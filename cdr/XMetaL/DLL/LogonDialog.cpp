// LogonDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LogonDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LogonDialog dialog


LogonDialog::LogonDialog(CWnd* pParent /*=NULL*/)
	: CDialog(LogonDialog::IDD, pParent)
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
	DDX_Text(pDX, IDC_EDIT1, m_UserId);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LogonDialog, CDialog)
	//{{AFX_MSG_MAP(LogonDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LogonDialog message handlers
