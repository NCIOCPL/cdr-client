// CDROptions2.cpp : implementation file
//

#include "stdafx.h"
#include "CDRLoader.h"
#include "CDROptions2.h"


// CDROptions2 dialog

IMPLEMENT_DYNAMIC(CDROptions, CDialog)
CDROptions::CDROptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDROptions::IDD, pParent)
	, ticket_Server(_T(""))
	, ticket_Port(_T(""))
	, cdr_Server(_T(""))
	, cdr_Port(_T(""))
{
}

CDROptions::~CDROptions()
{
}

void CDROptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ticket_Server, ticket_Server);
	DDX_Text(pDX, IDC_Ticket_Port, ticket_Port);
	DDX_Text(pDX, IDC_Cdr_Server, cdr_Server);
	DDX_Text(pDX, IDC_Cdr_Port, cdr_Port);
}


BEGIN_MESSAGE_MAP(CDROptions, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDROptions2 message handlers

void CDROptions::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	// make sure we have the current data
	CDataExchange dx( this, true );
	DoDataExchange( &dx );

	OnOK();
}
