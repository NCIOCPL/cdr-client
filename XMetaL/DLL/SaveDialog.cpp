/*
 * Implementation of dialog object for performing a CDR document search.
 */

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "SaveDialog.h"
#include ".\savedialog.h"

#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveDialog dialog


CSaveDialog::CSaveDialog(bool readyForReview, 
                         bool blobPossible /*=false*/,
                         CWnd* pParent /*=NULL*/)
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
    m_blobPossible = blobPossible;
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
    DDX_Control(pDX, IDC_MEDIA_FILENAME, m_blobFilename);
    DDX_Control(pDX, IDC_MEDIA_FILE_BROWSE, m_browseButton);
}


BEGIN_MESSAGE_MAP(CSaveDialog, CDialog)
    //{{AFX_MSG_MAP(CSaveDialog)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_CHECK4, OnBnClickedCheck4)
    ON_BN_CLICKED(IDC_CHECK3, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_MEDIA_FILE_BROWSE, OnBnClickedMediaFileBrowse)
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

    if (!m_blobPossible) {
        m_browseButton.EnableWindow(FALSE);
        this->m_blobFilename.EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveDialog::OnBnClickedMediaFileBrowse()
{
    CFileDialog fileDialog(TRUE);
    if (fileDialog.DoModal() == IDOK) {
        m_blobFilenameString = fileDialog.GetPathName();
        m_blobFilename.SetWindowText(m_blobFilenameString);
    }
}
