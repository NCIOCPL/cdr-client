// ProtUpdPerson.cpp : implementation file
//

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "ProtUpdPerson.h"
#include "PersonLocs.h"
#include "CdrUtil.h"
#include "Cdr.h"
#include "Commands.h"

// System headers.
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtUpdPerson dialog


CProtUpdPerson::CProtUpdPerson(const CString& lo, 
                               CWnd* pParent /*=NULL*/)
	: CDialog(CProtUpdPerson::IDD, pParent), leadOrg(lo)
{
	//{{AFX_DATA_INIT(CProtUpdPerson)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProtUpdPerson::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtUpdPerson)
	DDX_Control(pDX, IDC_LIST1, m_linkList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtUpdPerson, CDialog)
	//{{AFX_MSG_MAP(CProtUpdPerson)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtUpdPerson message handlers

void CProtUpdPerson::OnOK() 
{
    // Find out which candidate document the user selected.
	int curSel = m_linkList.GetCurSel();

    // Don't do anything if there is no selection.
    if (curSel >= 0) {
        //CWaitCursor wc;
        CString str;
		m_linkList.GetText(curSel, str);
        CdrLinkInfo linkInfo = cdr::extractLinkInfo(str);
        CString newTarget;
        CPersonLocs personLocs(linkInfo.target, newTarget);
        if (personLocs.DoModal() == IDOK) {
            CCommands::doInsertLink(_T("[") + newTarget + _T("] ")
                + linkInfo.data);
            EndDialog(IDOK);
        }
    }
}

void CProtUpdPerson::OnDblclkList1() 
{
    OnOK();	
}

BOOL CProtUpdPerson::OnInitDialog() 
{
	CDialog::OnInitDialog();
 
    // Create the command.
    std::basic_ostringstream<TCHAR> cmd;
    cmd << _T("<CdrReport><ReportName>Protocol Update Persons Picklist")
           _T("</ReportName><ReportParams><ReportParam Name='LeadOrg'")
           _T(" Value='")
        << (LPCTSTR)leadOrg
        << _T("'/></ReportParams></CdrReport>");

    // Submit the request to the CDR server.
    CWaitCursor wc;
    CString rsp = CdrSocket::sendCommand(cmd.str().c_str());
    int pos = rsp.Find(_T("<ReportBody"));
    if (pos == -1) {
        if (!cdr::showErrors(rsp))
            ::AfxMessageBox(_T("Unknown failure from search"),
                            MB_ICONEXCLAMATION);
        EndDialog(IDCANCEL);
        return TRUE;
    }

    // Populate the list control.
    extractChoices(rsp);
    if (cdr::fillListBox(m_linkList, docSet) > 0) {
		m_linkList.SetCurSel(0);
		m_linkList.EnableWindow();
	}
	else {
		::AfxMessageBox(_T("No documents match this query"));
        EndDialog(IDCANCEL);
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProtUpdPerson::extractChoices(const CString& rsp)
{
    docSet.clear();
    cdr::Element r = cdr::Element::extractElement(rsp, _T("ReportRow"));
    while (r) {
        cdr::Element id      = r.extractElement(r.getString(), _T("DocId"));
        cdr::Element title   = r.extractElement(r.getString(), _T("DocTitle"));
        cdr::SearchResult qr = cdr::SearchResult(
                id.getString(), _T("Person"), title.getString());
        docSet.push_back(qr);
        r = r.extractElement(rsp, _T("ReportRow"), r.getEndPos());
    }
}
