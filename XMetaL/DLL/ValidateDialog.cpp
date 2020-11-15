/*
 * Implementation of dialog object for validating the currently active
 * document.
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
	, m_includeApprovedMarkup(FALSE)
	, m_includeProposedAndApprovedMarkup(FALSE)
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
	DDX_Check(pDX, IDC_CHECK3, m_includeApprovedMarkup);
	DDX_Check(pDX, IDC_CHECK4, m_includeProposedAndApprovedMarkup);
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
        ::AfxMessageBox(L"No validation type selected");
}
