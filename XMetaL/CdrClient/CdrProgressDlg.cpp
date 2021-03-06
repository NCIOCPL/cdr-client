/*
 * Implementation for dialog window object with the progress bar.
 * Mostly generated by a Visual Studio wizards, with the addition
 * of a method for initializing the progress bar's original settings.
 */
#include "stdafx.h"
#include "CdrClient.h"
#include "CdrProgressDlg.h"


// CdrProgressDlg dialog

IMPLEMENT_DYNAMIC(CdrProgressDlg, CDialog)
CdrProgressDlg::CdrProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdrProgressDlg::IDD, pParent)
{
}

CdrProgressDlg::~CdrProgressDlg()
{
}

void CdrProgressDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PROGRESS1, progressBar);
}


BEGIN_MESSAGE_MAP(CdrProgressDlg, CDialog)
END_MESSAGE_MAP()


// CdrProgressDlg message handlers

void CdrProgressDlg::Init() {
	CDataExchange dx(this, false);
	DoDataExchange(&dx);
	progressBar.SetRange(1, 11);
	progressBar.SetStep(1);
}
