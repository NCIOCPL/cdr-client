/*
 * Implementation of dialog object for performing a CDR document search.
 */

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "RetrieveDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RetrieveDialog dialog


RetrieveDialog::RetrieveDialog(CWnd* parent /*=NULL*/)
	: CDialog(RetrieveDialog::IDD, parent)
{
	//{{AFX_DATA_INIT(RetrieveDialog)
	m_doc_id = _T("");
	m_check_out = FALSE;
	//}}AFX_DATA_INIT
}


void RetrieveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RetrieveDialog)
	DDX_Text(pDX, IDC_EDIT1, m_doc_id);
	DDX_Check(pDX, IDC_CHECK1, m_check_out);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RetrieveDialog, CDialog)
	//{{AFX_MSG_MAP(RetrieveDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RetrieveDialog message handlers

