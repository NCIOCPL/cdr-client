// SchemaPicklist.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SchemaPicklist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchemaPicklist dialog


CSchemaPicklist::CSchemaPicklist(const cdr::StringList* vvSet_,
                                 const CString& curVal_,
                                 const CString& elemName_,
                                 CWnd* pParent /*=NULL*/)
	: CDialog(CSchemaPicklist::IDD, pParent), vvSet(vvSet_),
      curVal(curVal_), elemName(elemName_)
{
	//{{AFX_DATA_INIT(CSchemaPicklist)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSchemaPicklist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSchemaPicklist)
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSchemaPicklist, CDialog)
	//{{AFX_MSG_MAP(CSchemaPicklist)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchemaPicklist message handlers

void CSchemaPicklist::OnDblclkList1() 
{
    OnOK();	
}

void CSchemaPicklist::OnOK() 
{
	int curSel = m_listBox.GetCurSel();
    if (curSel >= 0) {
        CWaitCursor wc;
        CString str;
        m_listBox.GetText(curSel, str);
        ::Selection selection = cdr::getApp().GetSelection();
        selection.SetReadOnlyContainer(FALSE);
        ::DOMNode node = selection.GetContainerNode();
        while (node && node.GetNodeType() != 1) // DOMElement
            node = node.GetParentNode();
        if (node) {
            ::DOMElement elem(node);
            elem.m_bAutoRelease = 0;
            ::DOMNode child = node.GetFirstChild();
            while (child && child.GetNodeType() != 3) // DOMText
                child = child.GetNextSibling();
            if (child) {
                ::DOMText textNode(child);
                textNode.m_bAutoRelease = 0;
                long len = textNode.GetLength();
                textNode.replaceData(0, len, str);
            }
        }
        selection.SetReadOnlyContainer(TRUE);
        EndDialog(IDCANCEL);
    }
}

BOOL CSchemaPicklist::OnInitDialog() 
{
	CDialog::OnInitDialog();
    SetWindowText(_T("Valid Values for Element ") + elemName);	
    cdr::StringList::const_iterator i = vvSet->begin();
    while (i != vvSet->end())
        m_listBox.AddString(*i++);
    if (!curVal.IsEmpty())
        m_listBox.SelectString(-1, curVal);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
