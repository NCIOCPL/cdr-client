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
        ::DOMElement elem = selection.GetContainerNode();
        while (elem && elem.GetNodeType() != 1) // DOMElement
            elem = elem.GetParentNode();
        if (elem) {
            bool found = false;
            ::DOMText textNode = elem.GetFirstChild();

            // See warning in Command.cpp for doInsertLink().
            while (textNode) {
                ::DOMText nextNode = textNode.GetNextSibling();
                if (textNode.GetNodeType() == 3) { // DOMText
                    textNode.SetData(str);
                    str = L"";
                    found = true;
                }
#if 0           // Try this in the macro file; it isn't working here
                // (problem turned out to be a SoftQuad bug, fixed in 2.1
                else if (textNode.GetNodeType() == 7) { // PI
                    ::DOMProcessingInstruction pi(textNode);
                    ::AfxMessageBox(L"got PI" + pi.GetTarget());
                    if (pi.GetTarget() == _T("xm-replace_text")) {
                        elem.removeChild(pi);
                    }
                    else
                        pi.m_bAutoRelease = 0;
                }
#endif
                textNode = nextNode;
            }
            if (!found) {
                ::_Document curDoc = cdr::getApp().GetActiveDocument();
                ::DOMText newNode = curDoc.createTextNode(str);
                elem.appendChild(newNode);
                newNode.m_lpDispatch->Release(); // XXX Surprise!  We need this!
            }
        }
        selection.SetReadOnlyContainer(TRUE);
        EndDialog(IDOK);
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
