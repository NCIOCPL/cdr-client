/*
 * Implementation of dialog object for editing inter-document links.
 *
 * JIRA::OCECDR-3732 - custom support for genetics picklists
 */

// Local headers.
#include "stdafx.h"
#include "afxtempl.h"
#include "resource.h"
#include "EditElement.h"
#include "OrgLocs.h"
#include "CdrUtil.h"
#include "Cdr.h"
#include "Commands.h"

// System headers.
#include <sstream>
#include <algorithm>
#include <functional>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOOMANY L"You selected more items than are allowed at this position."

/////////////////////////////////////////////////////////////////////////////
// CEditElement dialog


/**
 * Constructs a new dialog object for editing inter-document links.
 *
 *  @param  t           reference to string identifying document type.
 *  @param  e           reference to string containing current element tag.
 *  @param  parent      address of parent window.
 */
CEditElement::CEditElement(const CString& t,
                           const CString& e,
                           Type elem_type,
                           CWnd* parent /*=NULL*/)
    : CDialog(CEditElement::IDD, parent), doc_type(t), element(e),
      type(elem_type) {
    //{{AFX_DATA_INIT(CEditElement)
    m_title = L"";
    //}}AFX_DATA_INIT
}


void CEditElement::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEditElement)
    DDX_Control(pDX, IDC_LINK_TITLE_LABEL, m_label);
    DDX_Control(pDX, IDC_LIST1, m_link_list);
    DDX_Text(pDX, IDC_EDIT1, m_title);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditElement, CDialog)
    //{{AFX_MSG_MAP(CEditElement)
    ON_BN_CLICKED(IDC_BUTTON1, OnSelectButton)
    ON_LBN_DBLCLK(IDC_LIST1, OnDblclkLink)
    ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
    //}}AFX_MSG_MAP
    ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditElement message handlers

/**
 * Asks the server for a list of candidate documents which could be
 * used as link targets from the current element of the active document.
 */
void CEditElement::OnOK() {

    // Transfer the data from the dialog form to this object.
    UpdateData(true);

    // Make sure the user has specified at least a portion of the title.
    if (m_title.IsEmpty()) {
        switch (type) {
            case NORMAL:
                ::AfxMessageBox(L"Title string is empty.");
                break;
            case ORG_LOCATION:
                ::AfxMessageBox(L"Organization name string is empty.");
                break;
        }
        return;
    }

    // Escape underscores and left brackets, but not percent sign.
    m_title.Replace(L"[", L"[[]");
    m_title.Replace(L"_", L"[_]");

    CWaitCursor wc;
    cdr::DOM::Element command;
    CString response_xml;

    if (type == GP_SYNDROME) {
        cdr::CommandSet request("CdrReport");
        command = request.command;
        request.child_element(command, "ReportName", "Genetics Syndromes");
        auto params = request.child_element(command, "ReportParams");
        auto param = request.child_element(params, "ReportParam");
        request.set(param, "Name", "TitlePattern");
        request.set(param, "Value", m_title);
        response_xml = cdr::Socket::send_commands(request);
        cdr::DOM dom(response_xml);
        if (cdr::show_errors(dom)) {
            EndDialog(IDCANCEL);
            return;
        }
        extract_genetics_syndromes(dom);
    }
    else {
        cdr::CommandSet request("CdrSearchLinks");
        command = request.command;
        request.set(command, "MaxDocs", "150");
        request.child_element(command, "SourceDocType", doc_type);
        request.child_element(command, "SourceElementType", element);
        request.child_element(command, "TargetTitlePattern", m_title + L"%");
        response_xml = cdr::Socket::send_commands(request);
        cdr::DOM dom(response_xml);
        if (cdr::show_errors(dom)) {
            EndDialog(IDCANCEL);
            return;
        }
        cdr::extract_search_results(dom, doc_set);
    }

    if (cdr::fill_list_box(m_link_list, doc_set) > 0) {
        m_link_list.SetCurSel(0);
        m_link_list.EnableWindow();
    }
    else
        ::AfxMessageBox(L"No documents match this query");
}

/**
 * Inserts the selected document's link and title into the current element.
 */
void CEditElement::OnSelectButton() {

    // Find out which candidate documents the user selected.
    int sel_count = m_link_list.GetSelCount();
    if (sel_count > 0) {
        CWaitCursor wc;
        CArray<int, int> selections;
        selections.SetSize(sel_count);
        m_link_list.GetSelItems(sel_count, selections.GetData());
        CString str;
        int i = 0;
        int cur_sel = selections[i];
        m_link_list.GetText(cur_sel, str);
        switch (type) {
            case NORMAL:
            case GP_SYNDROME:
                CCommands::doInsertLink(str);
                while (++i < sel_count) {
                    ::Selection selection = cdr::get_app().GetSelection();
                    if (!selection.FindInsertLocation(element, TRUE)) {
                        ::AfxMessageBox(TOOMANY);
                        break;
                    }
                    selection.InsertElement(element);
                    selection.MoveToElement(element, TRUE);
                    cur_sel = selections[i];
                    m_link_list.GetText(cur_sel, str);
                    CCommands::doInsertLink(str);
                }
                break;
            case ORG_LOCATION:
                if (!insert_org_location(str))
                    return;
                break;
        }
        EndDialog(IDOK);
    }
}

bool CEditElement::insert_org_location(const CString& str) {
    CdrLinkInfo link_info = cdr::extract_link_info(str);
    CString new_target;
    COrgLocs org_locs(link_info.target, new_target);
    if (org_locs.DoModal() == IDOK) {
        CCommands::doInsertLink(L"[" + new_target + L"] " + link_info.data);
        return true;
    }
    return false;
}

/**
 * Allows the user to double-click on a link target as an alternate to
 * the "Select" button.
 */
void CEditElement::OnDblclkLink() {
    OnSelectButton();
}

void CEditElement::OnButton2() {
    UpdateData(true);
    COleDispatchDriver ie;
    if (!ie.CreateDispatch(L"InternetExplorer.Application")) {
        ::AfxMessageBox(L"Unable to launch Internet Explorer");
        return;
    }
    int cur_sel = m_link_list.GetCurSel();

    // Don't do anything if there is no selection.
    if (cur_sel < 0)
        return;

    // Parse out the document ID.
    CString info;
    m_link_list.GetText(cur_sel, info);
    int pos = info.Find(L"[");
    if (pos == -1) {
        ::AfxMessageBox(L"Unable to find document ID start delimiter.");
        return;
    }
    int end_pos = info.Find(L"]", ++pos);
    if (end_pos == -1) {
        ::AfxMessageBox(L"Unable to find document ID end delimiter.");
        return;
    }
    CString url = L"https://"
                + cdr::Socket::get_host_name()
                + L"/cgi-bin/cdr/QcReport.py?Session="
                + cdr::Socket::get_session_string()
                + L"&DocId="
                + info.Mid(pos, end_pos - pos);
    DISPID dispid;
    OLECHAR* member = L"Navigate";
    HRESULT hresult = ie.m_lpDispatch->GetIDsOfNames(IID_NULL,
        &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
    if (hresult != S_OK) {
        ::AfxMessageBox(L"Unable to launch Internet Explorer");
        return;
    }
    static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR
                          VTS_PVARIANT VTS_PVARIANT;
    COleVariant dummy;
    ie.InvokeHelper(dispid, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
        url, 0L, L"CdrViewWindow", &dummy, &dummy);
}

void CEditElement::extract_genetics_syndromes(cdr::DOM& dom) {
    doc_set.clear();
    auto nodes = dom.find_all("//ReportRow");
    for (auto& node : nodes) {
        CString id = dom.get_text(dom.find("DocId", node));
        CString title = dom.get_text(dom.find("DocTitle", node));
        doc_set.push_back(cdr::SearchResult(id, L"Term", title));
    }
}

BOOL CEditElement::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Find the source element for the link.
    ::Range selection = cdr::get_app().GetSelection();
    ::DOMElement elem = selection.GetContainerNode();
    while (elem && elem.GetNodeType() != 1) // DOMElement
        elem = elem.GetParentNode();
    if (elem) {

        // Find the text node for the element.
        ::DOMText text_node = elem.GetFirstChild();
        while (text_node && text_node.GetNodeType() != 3) // DOMText
            text_node = text_node.GetNextSibling();
        if (text_node)
            m_title = text_node.GetData();
    }

    /*
     *  CreatePFont(25,  0,  0,  0, 400, FALSE, FALSE, 0,
     *              ANSI_CHARSET, OUT_DEFAULT_PRECIS,
     *              CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
     *              DEFAULT_PITCH | FF_SWISS, "Arial");
     */

    if (bigger_font.CreatePointFont(100, L"Arial"))
        m_link_list.SetFont(&bigger_font);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditElement::OnLbnSelchangeList1()
{
    if (type != NORMAL && type != GP_SYNDROME) {
        int sel = m_link_list.GetCurSel();
        int sel_count = m_link_list.GetSelCount();
        while (sel_count > 1) {
            int selections[2];
            m_link_list.GetSelItems(2, selections);
            for (int i = 0; i < 2; ++i) {
                int j = selections[i];
                if (j != sel)
                    m_link_list.SetSel(j, FALSE);
            }
            sel_count = m_link_list.GetSelCount();
        }
    }
}
