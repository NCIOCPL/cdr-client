/*
 * Implementation of dialog object for performing a CDR document search.
 */

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "SearchDialog.h"
#include "CdrUtil.h"
#include "Cdr.h"
#include "Commands.h"
#include "VersionList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Remember the previous search.
struct LastSearch {
    enum StringType { BEGINS, CONTAINS, ALL };
    StringType string_type;
    cdr::DocSet doc_set;
    CString search_string;
    BOOL check_out;
    int doc_type;
    int selection;
    bool empty;
    LastSearch() : doc_type(-1), selection(-1), empty(true),
                   check_out(false){}
};
static LastSearch last_search;

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog dialog


CSearchDialog::CSearchDialog(const std::list<CString>& type_list,
                             CWnd* parent /*=NULL*/)
    : CDialog(CSearchDialog::IDD, parent), doc_types(type_list)
{
    //{{AFX_DATA_INIT(CSearchDialog)
    m_search_string = L"";
    m_check_out = FALSE;
    //}}AFX_DATA_INIT
}

void CSearchDialog::DoDataExchange(CDataExchange* dx)
{
    CDialog::DoDataExchange(dx);
    //{{AFX_DATA_MAP(CSearchDialog)
    DDX_Control(dx, IDC_COMBO1, m_doc_types);
    DDX_Control(dx, IDC_LIST1, m_doc_list);
    DDX_Control(dx, IDC_BUTTON1, m_retrieve_button);
    DDX_Control(dx, IDOK, m_search_button);
    DDX_Control(dx, IDCANCEL, m_cancel_button);
    DDX_Control(dx, IDC_RADIO3, m_title_equals);
    DDX_Control(dx, IDC_RADIO2, m_title_contains);
    DDX_Control(dx, IDC_RADIO1, m_title_start);
    DDX_Text(dx, IDC_EDIT1, m_search_string);
    DDX_Check(dx, IDC_CHECK1, m_check_out);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDialog, CDialog)
    //{{AFX_MSG_MAP(CSearchDialog)
    ON_BN_CLICKED(IDC_BUTTON1, OnRetrieveButton)
    ON_BN_CLICKED(IDOK, OnSearchButton)
    ON_LBN_DBLCLK(IDC_LIST1, OnDblclkDocument)
    ON_BN_CLICKED(IDC_BUTTON3, OnVersionsButton)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog message handlers

BOOL CSearchDialog::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    return CDialog::Create(IDD, pParentWnd);
}

/**
 * Ensures that a document selection has been made, then passes control
 * back to the CdrSearch command handler.
 */
void CSearchDialog::OnRetrieveButton()
{
    UpdateData(true);
    int curSel = m_doc_list.GetCurSel();
    if (curSel >= 0) {
        CString str;
        m_doc_list.GetText(curSel, str);
        if (CCommands::doRetrieve(str, m_check_out))
            EndDialog(IDCANCEL);
        last_search.selection = curSel;
        last_search.check_out  = m_check_out;
    }
}

/**
 * Submits a search for CDR documents to the server, and populates
 * the list box with the results.
 */
void CSearchDialog::OnSearchButton()
{
    // In case we blow up, don't leave a live LastSearch object around.
    last_search.empty = true;

    // Transfer the dialog's data to this object.
    UpdateData(true);

    // Build the search request.
    cdr::CommandSet request("CdrSearch");
    auto query = request.child_element(request.command, "Query");
    request.set(query, "MaxDocs", "100");
    int cur_type = m_doc_types.GetCurSel();
    last_search.doc_type = cur_type;

    // Don't do anything unless we have at least a search string or a doc type.
    if (m_search_string.IsEmpty() && cur_type == 0)
        return;
    last_search.search_string = m_search_string;
    CString op = L"eq";
    if (m_title_contains.GetCheck() == 1) {
        op = L"contains";
        last_search.string_type = LastSearch::CONTAINS;
        if (m_search_string.IsEmpty())
            m_search_string = L"%";
    }
    else if (m_title_start.GetCheck() == 1) {
        op = L"begins";
        last_search.string_type = LastSearch::BEGINS;
        if (m_search_string.IsEmpty())
            m_search_string = L"%";
    }
    else
        last_search.string_type = LastSearch::ALL;
    CString test = L"CdrCtl/Title " + op + L" " + m_search_string;
    request.child_element(query, "Test", test);
    if (cur_type > 0) {
        CString val;
        m_doc_types.GetLBText(cur_type, val);
        if (!val.IsEmpty())
            request.child_element(query, "DocType", val);
    }

    // Submit the request to the CDR server.
    CWaitCursor wc;
    cdr::debug_log(request.get_xml());
    CString response_xml = cdr::Socket::send_commands(request);
    cdr::DOM dom(response_xml);
    if (cdr::show_errors(dom)) {
        EndDialog(IDCANCEL);
        return;
    }

    // Populate the dialog's list box with the results.
    m_doc_list.ResetContent();
    cdr::extract_search_results(dom, last_search.doc_set);
    if (cdr::fill_list_box(m_doc_list, last_search.doc_set) > 0) {
        m_doc_list.SetCurSel(0);
        m_doc_list.EnableWindow();
        last_search.selection = 0;
    }
    else {
        ::AfxMessageBox(L"No documents match this query");
        last_search.selection = -1;
    }

    // Remember this search.
    last_search.check_out     = m_check_out;
    last_search.empty        = false;
}

/**
 * Initializes the radio buttons and populates the document type
 * list box.
 *
 *  @return         <code>TRUE</code> since we did not set the
 *                  focust to a control.
 */
BOOL CSearchDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_title_start.SetButtonStyle(BS_AUTORADIOBUTTON);
    m_title_contains.SetButtonStyle(BS_AUTORADIOBUTTON);
    m_title_equals.SetButtonStyle(BS_AUTORADIOBUTTON);
    m_title_start.SetCheck(1);
    std::list<CString>::const_iterator i = doc_types.begin();
    while (i != doc_types.end())
        m_doc_types.AddString((*i++));
    m_doc_types.SetCurSel(0);
    if (!last_search.empty) {
        m_search_string = last_search.search_string;
        m_check_out     = last_search.check_out;
        m_doc_types.SetCurSel(last_search.doc_type);
        m_title_start.SetCheck(0);
        m_title_contains.SetCheck(0);
        m_title_equals.SetCheck(0);
        switch (last_search.string_type) {
        case LastSearch::BEGINS:
        default:
            m_title_start.SetCheck(1);
            break;
        case LastSearch::CONTAINS:
            m_title_contains.SetCheck(1);
            break;
        case LastSearch::ALL:
            m_title_equals.SetCheck(1);
            break;
        }
        int num = cdr::fill_list_box(m_doc_list, last_search.doc_set);
        if (last_search.selection >= 0 && last_search.selection < num)
            m_doc_list.SetCurSel(last_search.selection);
        m_doc_list.EnableWindow();
        UpdateData(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * Allows the user to double-click on a search result as an alternative
 * to the Retrieve button.
 */
void CSearchDialog::OnDblclkDocument()
{
    OnRetrieveButton();
}

void CSearchDialog::OnVersionsButton()
{
    UpdateData(true);
    int cur_sel = m_doc_list.GetCurSel();
    if (cur_sel >= 0) {
        CString str;
        m_doc_list.GetText(cur_sel, str);
        unsigned int doc_no = cdr::get_doc_no(str);

        // Make canonical document ID.
        CString doc_id = cdr::doc_id_string(doc_no);
        CVersionList version_list(doc_id);
        if (version_list.DoModal() == IDOK)
            EndDialog(IDCANCEL);
    }
}
