// PassedValidation.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PassedValidation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassedValidation dialog


CPassedValidation::CPassedValidation(const CString& id,
                                     CWnd* parent /*=NULL*/)
    : CDialog(CPassedValidation::IDD, parent), doc_id(id)
{
    //{{AFX_DATA_INIT(CPassedValidation)
    //}}AFX_DATA_INIT
}


void CPassedValidation::DoDataExchange(CDataExchange* dx)
{
    CDialog::DoDataExchange(dx);
    //{{AFX_DATA_MAP(CPassedValidation)
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPassedValidation, CDialog)
    //{{AFX_MSG_MAP(CPassedValidation)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassedValidation message handlers

BOOL CPassedValidation::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetWindowText(L"Validation for " + doc_id);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
