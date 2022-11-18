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


CSchemaPicklist::CSchemaPicklist(const cdr::StringList* values,
                                 const CString& current_value,
                                 const CString& element_name,
                                 CWnd* pParent /*=NULL*/)
    : CDialog(CSchemaPicklist::IDD, pParent), vv_set(values),
      cur_val(current_value), elem_name(element_name)
{
    //{{AFX_DATA_INIT(CSchemaPicklist)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CSchemaPicklist::DoDataExchange(CDataExchange* dx)
{
    CDialog::DoDataExchange(dx);
    //{{AFX_DATA_MAP(CSchemaPicklist)
    DDX_Control(dx, IDC_LIST1, m_list_box);
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
    int sel_count = m_list_box.GetSelCount();
    if (sel_count > 0) {
        CWaitCursor wc;
        CArray<int, int> selections;
        selections.SetSize(sel_count);
        m_list_box.GetSelItems(sel_count, selections.GetData());
        int i = 0;
        int current_selection = selections[i];
        CString str;
        m_list_box.GetText(current_selection, str);
        ::CSelection selection = cdr::get_app().get_Selection();
        selection.put_ReadOnlyContainer(FALSE);
        selection.SelectContainerContents();
        ::CDOMElement elem = selection.get_ContainerNode();
        selection.Delete();
        while (elem && elem.get_nodeType() != 1) // DOM element
            elem = elem.get_parentNode();
        if (elem) {
            bool found = false;
            ::CDOMText text_node = elem.get_firstChild();
            while (text_node) {
                ::CDOMText next_node = text_node.get_nextSibling();
                if (text_node.get_nodeType() == 3) { // DOMText
                    text_node.put_data(str);
                    str = L"";
                    found = true;
                }
                text_node = next_node;
            }
            if (!found) {
                ::CDocument0 cur_doc = cdr::get_app().get_ActiveDocument();
                ::CDOMText new_node = cur_doc.createTextNode(str);
                elem.appendChild(new_node);
                new_node.m_lpDispatch->Release();
            }
        }
        selection.put_ReadOnlyContainer(TRUE);
        EndDialog(IDOK);
    }
}

BOOL CSchemaPicklist::OnInitDialog()
{
    CDialog::OnInitDialog();
    SetWindowText(L"Valid Values for Element " + elem_name);
    cdr::StringList::const_iterator i = vv_set->begin();
    while (i != vv_set->end())
        m_list_box.AddString(*i++);
    if (!cur_val.IsEmpty())
        m_list_box.SelectString(-1, cur_val);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
