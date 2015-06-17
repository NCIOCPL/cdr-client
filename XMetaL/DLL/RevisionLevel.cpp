// RevisionLevel.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "RevisionLevel.h"
#include "afxdialogex.h"


// RevisionLevel dialog

IMPLEMENT_DYNAMIC(RevisionLevel, CDialogEx)

RevisionLevel::RevisionLevel(CWnd* pParent /*=NULL*/)
    : CDialogEx(RevisionLevel::IDD, pParent)
    , mRevisionLevel(0)
{

}

RevisionLevel::~RevisionLevel()
{
}

void RevisionLevel::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_RADIO1, mRevisionLevel);
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
