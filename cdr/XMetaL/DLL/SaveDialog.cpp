/*
 * $Id: SaveDialog.cpp,v 1.2 2001-06-09 12:42:17 bkline Exp $
 *
 * Implementation of dialog object for performing a CDR document search.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2000/10/16 22:29:27  bkline
 * Initial revision
 *
 */

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "SaveDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveDialog dialog


CSaveDialog::CSaveDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveDialog)
	m_validate = FALSE;
	m_checkIn = FALSE;
	m_comment = _T("");
	m_createVersion = FALSE;
	m_versionPublishable = FALSE;
	m_docInactive = FALSE;
	//}}AFX_DATA_INIT
}


void CSaveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveDialog)
	DDX_Check(pDX, IDC_CHECK1, m_validate);
	DDX_Check(pDX, IDC_CHECK2, m_checkIn);
	DDX_Text(pDX, IDC_EDIT2, m_comment);
	DDV_MaxChars(pDX, m_comment, 4000);
	DDX_Check(pDX, IDC_CHECK3, m_createVersion);
	DDX_Check(pDX, IDC_CHECK4, m_versionPublishable);
	DDX_Check(pDX, IDC_CHECK5, m_docInactive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveDialog, CDialog)
	//{{AFX_MSG_MAP(CSaveDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveDialog message handlers
