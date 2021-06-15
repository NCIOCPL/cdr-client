// RevisionLevel.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "RevisionLevel.h"
#include "afxdialogex.h"


// RevisionLevel dialog

IMPLEMENT_DYNAMIC(RevisionLevel, CDialogEx)

RevisionLevel::RevisionLevel(CWnd* parent /*=NULL*/)
    : CDialogEx(RevisionLevel::IDD, parent)
    , m_revision_level(0)
{

}

RevisionLevel::~RevisionLevel()
{
}

void RevisionLevel::DoDataExchange(CDataExchange* dx)
{
    CDialogEx::DoDataExchange(dx);
    DDX_Radio(dx, IDC_RADIO1, m_revision_level);
}


BEGIN_MESSAGE_MAP(RevisionLevel, CDialogEx)
    ON_BN_CLICKED(IDOK, &RevisionLevel::OnBnClickedOk)
END_MESSAGE_MAP()


// RevisionLevel message handlers


BOOL RevisionLevel::OnInitDialog() {
    CDialog::OnInitDialog();
    UpdateData(false);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void RevisionLevel::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData(true);
    CDialogEx::OnOK();
}
