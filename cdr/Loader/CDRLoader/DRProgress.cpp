// DRProgress.cpp : implementation file
//

#include "stdafx.h"
#include "CDRLoader.h"
#include "DRProgress.h"


// CDRProgress dialog

IMPLEMENT_DYNAMIC(CDRProgress, CDialog)
CDRProgress::CDRProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDRProgress::IDD, pParent)
{   
}

CDRProgress::~CDRProgress()
{
}

void CDRProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, ProgressBar);
}

void CDRProgress::Init( void )
{
	CDataExchange dx( this, false );
	DoDataExchange( &dx );

	ProgressBar.SetRange( 1, 11 );
	ProgressBar.SetStep( 1 );
}

BOOL CDRProgress::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

void CDRProgress::Advance( void )
{
	ProgressBar.StepIt();
}

void CDRProgress::OnPaint() 
{
	CDialog::OnPaint();
}


BEGIN_MESSAGE_MAP(CDRProgress, CDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDRProgress message handlers
