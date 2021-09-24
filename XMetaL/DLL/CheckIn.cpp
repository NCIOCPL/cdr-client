// CheckIn.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CheckIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckIn dialog


CCheckIn::CCheckIn(CWnd* pParent /*=NULL*/)
    : CDialog(CCheckIn::IDD, pParent)
{
    //{{AFX_DATA_INIT(CCheckIn)
    m_comment = L"";
    //}}AFX_DATA_INIT
}


void CCheckIn::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCheckIn)
    DDX_Text(pDX, IDC_EDIT1, m_comment);
    DDV_MaxChars(pDX, m_comment, 255);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckIn, CDialog)
    //{{AFX_MSG_MAP(CCheckIn)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckIn message handlers
