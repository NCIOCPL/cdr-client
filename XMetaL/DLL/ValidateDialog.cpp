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


CValidateDialog::CValidateDialog(CWnd* parent /*=NULL*/)
    : CDialog(CValidateDialog::IDD, parent)
    , m_include_approved_markup(FALSE)
    , m_include_proposed_and_approved_markup(FALSE)
{
    //{{AFX_DATA_INIT(CValidateDialog)
    m_schema_validation = TRUE;
    m_link_validation = FALSE;
    //}}AFX_DATA_INIT
}


void CValidateDialog::DoDataExchange(CDataExchange* dx)
{
    CDialog::DoDataExchange(dx);
    //{{AFX_DATA_MAP(CValidateDialog)
    DDX_Check(dx, IDC_CHECK1, m_schema_validation);
    DDX_Check(dx, IDC_CHECK2, m_link_validation);
    //}}AFX_DATA_MAP
    DDX_Check(dx, IDC_CHECK3, m_include_approved_markup);
    DDX_Check(dx, IDC_CHECK4, m_include_proposed_and_approved_markup);
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
    if (m_link_validation || m_schema_validation)
        CDialog::OnOK();
    else
        ::AfxMessageBox(L"No validation type selected");
}
