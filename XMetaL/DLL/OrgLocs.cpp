// OrgLocs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "OrgLocs.h"
#include "CdrUtil.h"
#include "Cdr.h"
#include "Commands.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrgLocs dialog


COrgLocs::COrgLocs(const CString& id, CString& new_targ,
                   CWnd* parent /*=NULL*/)
	: CDialog(COrgLocs::IDD, parent), doc_id(id), new_target(new_targ) {
	//{{AFX_DATA_INIT(COrgLocs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COrgLocs::DoDataExchange(CDataExchange* dx) {
	CDialog::DoDataExchange(dx);
	//{{AFX_DATA_MAP(COrgLocs)
	DDX_Control(dx, IDC_LIST1, m_choice_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrgLocs, CDialog)
	//{{AFX_MSG_MAP(COrgLocs)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrgLocs message handlers

BOOL COrgLocs::OnInitDialog() {
	CDialog::OnInitDialog();

    // Create the command.
    cdr::CommandSet request("CdrFilter");
    auto filter = request.child_element(request.command, "Filter");
    request.set(filter, "Name", "Org Locations Picklist");
    auto params = request.child_element(request.command, "Params");
    auto param = request.child_element(request.command, "Param");
    request.set(param, "Name", "docId");
    request.set(param, "Value", doc_id);
    auto document = request.child_element(request.command, "Document");
    request.set(document, "href", doc_id);

    // Submit the request to the CDR server.
    CWaitCursor wc;
    CString rsp = cdr::Socket::send_commands(request);
    cdr::DOM dom(rsp);
    if (cdr::show_errors(dom)) {
        EndDialog(IDCANCEL);
        return TRUE;
    }

    // Populate the list control.
    doc_set.clear();
    auto nodes = dom.find_all("//Address");
    for (auto& node : nodes) {
        CString id = dom.get_text(dom.find("Link", node));
        CString title = dom.get_text(dom.find("Data", node));
        doc_set.push_back(cdr::SearchResult(id, L"Organization", title));
    }
    if (cdr::fill_list_box(m_choice_list, doc_set) > 0) {
		m_choice_list.SetCurSel(0);
		m_choice_list.EnableWindow();
	}
	else {
		::AfxMessageBox(L"No locations found");
        EndDialog(IDCANCEL);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COrgLocs::OnOK() {

	// Find out which candidate document the user selected.
	int cur_sel = m_choice_list.GetCurSel();

    // Don't do anything if there is no selection.
    if (cur_sel >= 0) {
        CWaitCursor wc;
        CString str;
		m_choice_list.GetText(cur_sel, str);
        CdrLinkInfo info = cdr::extract_link_info(str);
        new_target = info.target;
        EndDialog(IDOK);
    }
}

void COrgLocs::OnDblclkList1() {
	OnOK();
}
