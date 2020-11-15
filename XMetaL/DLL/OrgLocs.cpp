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


COrgLocs::COrgLocs(const CString& id, CString& newTarg,
                   CWnd* pParent /*=NULL*/)
	: CDialog(COrgLocs::IDD, pParent), docId(id), newTarget(newTarg) {
	//{{AFX_DATA_INIT(COrgLocs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COrgLocs::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrgLocs)
	DDX_Control(pDX, IDC_LIST1, m_choiceList);
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
    request.set(param, "Value", docId);
    auto document = request.child_element(request.command, "Document");
    request.set(document, "href", docId);

    // Submit the request to the CDR server.
    CWaitCursor wc;
    CString rsp = CdrSocket::send_commands(request);
    cdr::DOM dom(rsp);
    if (cdr::show_errors(dom)) {
        EndDialog(IDCANCEL);
        return TRUE;
    }

    // Populate the list control.
    docSet.clear();
    auto nodes = dom.find_all("//Address");
    for (auto& node : nodes) {
        CString id = dom.get_text(dom.find("Link", node));
        CString title = dom.get_text(dom.find("Data", node));
        docSet.push_back(cdr::SearchResult(id, L"Organization", title));
    }
    if (cdr::fill_list_box(m_choiceList, docSet) > 0) {
		m_choiceList.SetCurSel(0);
		m_choiceList.EnableWindow();
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
	int curSel = m_choiceList.GetCurSel();

    // Don't do anything if there is no selection.
    if (curSel >= 0) {
        CWaitCursor wc;
        CString str;
		m_choiceList.GetText(curSel, str);
        CdrLinkInfo info = cdr::extract_link_info(str);
        newTarget = info.target;
        EndDialog(IDOK);
    }
}

void COrgLocs::OnDblclkList1() {
	OnOK();
}
