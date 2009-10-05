// SchemaPicklist.cpp : implementation file
//

#include "stdafx.h"
#include "afxtempl.h"
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
    int selCount = m_listBox.GetSelCount();
    if (selCount > 0) {
        CWaitCursor wc;
        CArray<int, int> selections;
        selections.SetSize(selCount);
        m_listBox.GetSelItems(selCount, selections.GetData());
        int i = 0;
        int curSel = selections[i];
        CString str;
        m_listBox.GetText(curSel, str);
        ::Selection selection = cdr::getApp().GetSelection();
        selection.SetReadOnlyContainer(FALSE);
		selection.SelectContainerContents();
        ::DOMElement elem = selection.GetContainerNode();
		selection.Delete();
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
                textNode = nextNode;
            }
            if (!found) {
                ::_Document curDoc = cdr::getApp().GetActiveDocument();
                ::DOMText newNode = curDoc.createTextNode(str);
                elem.appendChild(newNode);
                newNode.m_lpDispatch->Release(); // XXX Surprise! We need this!
            }

            // Added in response to request for issue #529.
            if (elemName == _T("ProtocolPhase") ||
                elemName == _T("ProtocolDesign"))
            {
                while (++i < selCount) {
                    ::Selection sel = cdr::getApp().GetSelection();
                    if (!sel.FindInsertLocation(elemName, TRUE)) {
                        ::AfxMessageBox(_T("You selected more items than ")
                                        _T("are allowed at this position."));
                        break;
                    }
                    sel.InsertElement(elemName);
                    sel.MoveToElement(elemName, TRUE);
                    curSel = selections[i];
                    m_listBox.GetText(curSel, str);
                    sel.SelectContainerContents();
					sel.SetReadOnlyContainer(FALSE);
                    sel.SetText(str);
					sel.SetReadOnlyContainer(TRUE);
                }
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
