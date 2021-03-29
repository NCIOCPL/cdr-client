/*
 * Implementation of dialog object for saving the current CDR document.
 */

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "SaveDialog.h"

#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSaveDialog dialog


CSaveDialog::CSaveDialog(bool ready_for_review,
                         bool blob_possible /*=false*/,
                         CWnd* parent /*=NULL*/)
    : CDialog(CSaveDialog::IDD, parent)
{
    //{{AFX_DATA_INIT(CSaveDialog)
    m_validate = FALSE;
    m_checkIn = FALSE;
    m_comment = L"";
    m_create_version = FALSE;
    m_version_publishable = FALSE;
    m_doc_inactive = FALSE;
    m_ready_for_review = FALSE;
    //}}AFX_DATA_INIT
    m_ready_for_review = ready_for_review;
    m_blob_possible = blob_possible;
}


void CSaveDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSaveDialog)
    DDX_Check(pDX, IDC_CHECK1, m_validate);
    DDX_Check(pDX, IDC_CHECK2, m_checkIn);
    DDX_Text(pDX, IDC_EDIT2, m_comment);
    DDV_MaxChars(pDX, m_comment, 4000);
    DDX_Check(pDX, IDC_CHECK3, m_create_version);
    DDX_Check(pDX, IDC_CHECK4, m_version_publishable);
    DDX_Check(pDX, IDC_CHECK5, m_doc_inactive);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_MEDIA_FILENAME, m_blob_filename);
    DDX_Control(pDX, IDC_MEDIA_FILE_BROWSE, m_browse_button);
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
    fix_checkboxes();
}

void CSaveDialog::OnBnClickedCheck3()
{
    fix_checkboxes();
}

void CSaveDialog::OnBnClickedCheck1()
{
    fix_checkboxes();
}

void CSaveDialog::fix_checkboxes()
{
    UpdateData(TRUE);
    if (m_version_publishable &&
        (!m_create_version || !m_validate)) {
        m_create_version = TRUE;
        m_validate = TRUE;
        UpdateData(FALSE);
    }
}

BOOL CSaveDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_ready_for_review)
        m_ready_for_review_checkbox.EnableWindow(FALSE);

    if (!m_blob_possible) {
        m_browse_button.EnableWindow(FALSE);
        this->m_blob_filename.EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveDialog::OnBnClickedMediaFileBrowse()
{
    CFileDialog fileDialog(TRUE);
    if (fileDialog.DoModal() == IDOK) {
        m_blob_filename_string = fileDialog.GetPathName();
        m_blob_filename.SetWindowText(m_blob_filename_string);
    }
}
