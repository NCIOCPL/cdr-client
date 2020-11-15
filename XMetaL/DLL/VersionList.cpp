// VersionList.cpp : implementation file
//

#include "stdafx.h"
#include "cdr.h"
#include "VersionList.h"
#include "CdrUtil.h"
#include "Commands.h"

// System headers.
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVersionList dialog


CVersionList::CVersionList(const CString& id, CWnd* pParent /*=NULL*/)
	: docId(id), CDialog(CVersionList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVersionList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVersionList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVersionList)
	DDX_Control(pDX, IDC_LIST1, m_choiceList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVersionList, CDialog)
	//{{AFX_MSG_MAP(CVersionList)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVersionList message handlers

BOOL CVersionList::OnInitDialog()
{
	CDialog::OnInitDialog();

    // Create the command.
    cdr::CommandSet request("CdrListVersions");
    auto command = request.command;
    request.child_element(command, "DocId", docId);

    // Submit the request to the CDR server.
    CWaitCursor wc;
    CString response_xml = CdrSocket::sendCommands(request);
    cdr::DOM dom(response_xml);
    if (cdr::showErrors(dom)) {
        EndDialog(IDCANCEL);
        return TRUE;
    }

    // Populate the list control.
    auto nodes = dom.find_all("//Version");
    if (!nodes.size()) {
        ::AfxMessageBox(L"No versions found");
        EndDialog(IDCANCEL);
    }
    else {
        for (auto& node : nodes) {
            CString num = dom.get_text(dom.find("Num", node));
            CString cmt = dom.get_text(dom.find("Comment", node));
            CString dat = dom.get_text(dom.find("Date", node)).Left(11);
            if (cmt.IsEmpty())
                cmt = L"No comment";
            else {
                cmt.Replace(L"\r", L" ");
                cmt.Replace(L"\n", L" ");
                while (cmt.Replace(L"  ", L" ") > 0)
                    ;
            }
            m_choiceList.AddString(L"[" + num + L"] " + dat + cmt);
        }
		m_choiceList.SetCurSel(0);
		m_choiceList.EnableWindow();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVersionList::OnOK()
{
	// Find out which version the user selected.
	int curSel = m_choiceList.GetCurSel();

    // Don't do anything if there is no selection.
    if (curSel >= 0) {
        CWaitCursor wc;
        CString str;
		m_choiceList.GetText(curSel, str);
        //::AfxMessageBox(str);

        // Find the delimiters.
        int left = str.Find(_T("["));
        if (left == -1) {
            ::AfxMessageBox(_T("Unable to find left version delimiter."));
            return;
        }
        int right = str.Find(_T("]"), ++left);
        if (right == -1) {
            ::AfxMessageBox(_T("Unable to find right version delimiter."));
            return;
        }
        CString version = str.Mid(left, right - left);

        // Retrieve the version as read-only.
        if (CCommands::doRetrieve(docId, FALSE, version))
            EndDialog(IDOK);
    }
}

/**
 * Allows the user to double-click on a search result as an alternative
 * to the Retrieve button.
 */
void CVersionList::OnDblclkList1()
{
	OnOK();
}
