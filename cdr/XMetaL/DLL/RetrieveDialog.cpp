/*
 * $Id: RetrieveDialog.cpp,v 1.1 2000-10-16 22:29:27 bkline Exp $
 *
 * Implementation of dialog object for performing a CDR document search.
 *
 * $Log: not supported by cvs2svn $
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


RetrieveDialog::RetrieveDialog(CWnd* pParent /*=NULL*/)
	: CDialog(RetrieveDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(RetrieveDialog)
	m_DocId = _T("");
	//}}AFX_DATA_INIT
}


void RetrieveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RetrieveDialog)
	DDX_Text(pDX, IDC_EDIT1, m_DocId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RetrieveDialog, CDialog)
	//{{AFX_MSG_MAP(RetrieveDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RetrieveDialog message handlers
