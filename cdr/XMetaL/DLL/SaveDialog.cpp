/*
 * $Id: SaveDialog.cpp,v 1.6 2002-10-16 19:56:27 bkline Exp $
 *
 * Implementation of dialog object for performing a CDR document search.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.5  2002/10/15 22:22:05  bkline
 * Adding code for issue #471.
 *
 * Revision 1.4  2002/07/20 13:45:43  bkline
 * Added automatic setting of dialog controls.
 *
 * Revision 1.3  2001/11/28 21:05:11  bkline
 * Added m_readyForReview member variable.
 *
 * Revision 1.2  2001/06/09 12:42:17  bkline
 * Removed title control; added controls for versioning and status.
 *
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


CSaveDialog::CSaveDialog(bool readyForReview, CWnd* pParent /*=NULL*/)
    : CDialog(CSaveDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CSaveDialog)
    m_validate = FALSE;
    m_checkIn = FALSE;
    m_comment = _T("");
    m_createVersion = FALSE;
    m_versionPublishable = FALSE;
    m_docInactive = FALSE;
    m_readyForReview = FALSE;
    //}}AFX_DATA_INIT
    m_readyForReview = readyForReview;
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
    DDX_Check(pDX, IDC_CHECK6, m_readyForReview);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_CHECK6, m_readyForReviewCheckbox);
}


BEGIN_MESSAGE_MAP(CSaveDialog, CDialog)
    //{{AFX_MSG_MAP(CSaveDialog)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_CHECK4, OnBnClickedCheck4)
    ON_BN_CLICKED(IDC_CHECK3, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveDialog message handlers

void CSaveDialog::OnBnClickedCheck4()
{
    fixCheckBoxes();
}

void CSaveDialog::OnBnClickedCheck3()
{
    fixCheckBoxes();
}

void CSaveDialog::OnBnClickedCheck1()
{
    fixCheckBoxes();
}

void CSaveDialog::fixCheckBoxes()
{
    UpdateData(TRUE);
    if (m_versionPublishable &&
        (!m_createVersion || !m_validate)) {
        m_createVersion = TRUE;
        m_validate = TRUE;
        UpdateData(FALSE);
    }
}

BOOL CSaveDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_readyForReview)
        m_readyForReviewCheckbox.EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
