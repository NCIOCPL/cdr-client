/*
 * $Id: ValidateDialog.cpp,v 1.1 2000-10-16 22:29:27 bkline Exp $
 *
 * Implementation of dialog object for validating the currently active 
 * document.
 *
 * $Log: not supported by cvs2svn $
 */

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "ValidateDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValidateDialog dialog


CValidateDialog::CValidateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CValidateDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CValidateDialog)
	m_schemaValidation = TRUE;
	m_linkValidation = FALSE;
	//}}AFX_DATA_INIT
}


void CValidateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValidateDialog)
	DDX_Check(pDX, IDC_CHECK1, m_schemaValidation);
	DDX_Check(pDX, IDC_CHECK2, m_linkValidation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CValidateDialog, CDialog)
	//{{AFX_MSG_MAP(CValidateDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValidateDialog message handlers

/**
 * Ensures that the user has selected at least one validation type, then
 * passes control back to the validation command handler.
 */
void CValidateDialog::OnOK() 
{
  	UpdateData(true);
    if (m_linkValidation || m_schemaValidation)
    	CDialog::OnOK();
    else
        ::AfxMessageBox("No validation type selected");
}
