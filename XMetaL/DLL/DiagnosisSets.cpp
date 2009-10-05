// DiagnosisSets.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Cdr.h"
#include "DiagnosisSets.h"


// CDiagnosisSets dialog

IMPLEMENT_DYNAMIC(CDiagnosisSets, CDialog)
CDiagnosisSets::CDiagnosisSets(const cdr::StringList& names, 
                               CWnd* pParent /*=NULL*/)
	: setNames(names), CDialog(CDiagnosisSets::IDD, pParent)
{}

CDiagnosisSets::~CDiagnosisSets()
{
}

void CDiagnosisSets::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDCANCEL, m_cancelButton);
    DDX_Control(pDX, IDOK, m_insertButton);
    DDX_Control(pDX, IDC_DIAGNOSIS_SETS, m_termSetControl);
}


BEGIN_MESSAGE_MAP(CDiagnosisSets, CDialog)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDiagnosisSets message handlers

void CDiagnosisSets::OnBnClickedOk()
{
    UpdateData(true);
    int curSel = this->m_termSetControl.GetCurSel();
    if (curSel >= 0) {
        m_termSetControl.GetLBText(curSel, chosenSetName);
        OnOK();
    }
}

void CDiagnosisSets::OnBnClickedCancel()
{
    // TODO: Add your control notification handler code here
    OnCancel();
}

BOOL CDiagnosisSets::OnInitDialog()
{
    CDialog::OnInitDialog();

    cdr::StringList::const_iterator iter = this->setNames.begin();
    while (iter != this->setNames.end()) {
        CString name = *iter++;
        m_termSetControl.AddString(name);
    }
    m_termSetControl.EnableWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
