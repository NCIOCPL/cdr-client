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
	, test_ticket_Server(_T(""))
	, test_ticket_Port(_T(""))
	, test_cdr_Server(_T(""))
	, test_cdr_Port(_T(""))
	, dev_ticket_Server(_T(""))
	, dev_ticket_Port(_T(""))
	, dev_cdr_Server(_T(""))
	, dev_cdr_Port(_T(""))
	, current_Server( 0 )
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
	DDX_Text(pDX, IDC_ticket_Server2, test_ticket_Server);
	DDX_Text(pDX, IDC_Ticket_Port2, test_ticket_Port);
	DDX_Text(pDX, IDC_Cdr_Server2, test_cdr_Server);
	DDX_Text(pDX, IDC_Cdr_Port2, test_cdr_Port);
	DDX_Text(pDX, IDC_ticket_Server3, dev_ticket_Server);
	DDX_Text(pDX, IDC_Ticket_Port3, dev_ticket_Port);
	DDX_Text(pDX, IDC_Cdr_Server3, dev_cdr_Server);
	DDX_Text(pDX, IDC_Cdr_Port3, dev_cdr_Port);
}


BEGIN_MESSAGE_MAP(CDROptions, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDROptions::OnInitDialog()
{
	CDialog::OnInitDialog();

	CheckRadioButton( IDC_RADIO_P, IDC_RADIO_D, (IDC_RADIO_P + current_Server) );

	// make sure we have the current data
	CDataExchange dx( this, false );
	DoDataExchange( &dx );

	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDROptions::SetCurrentServer( int cs ) 
{ 
	current_Server = cs; 
}


// CDROptions2 message handlers

void CDROptions::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	// make sure we have the current data
	CDataExchange dx( this, true );
	DoDataExchange( &dx );

	current_Server = GetCheckedRadioButton( IDC_RADIO_P, IDC_RADIO_D ) - IDC_RADIO_P;
	OnOK();
}

