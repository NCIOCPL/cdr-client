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
	: CDialog(COrgLocs::IDD, pParent), docId(id), newTarget(newTarg)
{
	//{{AFX_DATA_INIT(COrgLocs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COrgLocs::DoDataExchange(CDataExchange* pDX)
{
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

BOOL COrgLocs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    // Create the command.
    std::basic_ostringstream<TCHAR> cmd;
    cmd << _T("<CdrFilter><Filter Name='Org Locations Picklist'/>")
           _T("<Parms><Parm><Name>docId</Name><Value>")
        << (LPCTSTR)docId
        << _T("</Value></Parm></Parms><Document href='")
        << (LPCTSTR)docId
        << _T("'/></CdrFilter>");

    // Submit the request to the CDR server.
    CWaitCursor wc;
    CString rsp = CdrSocket::sendCommand(cmd.str().c_str());
    int pos = rsp.Find(_T("<Addresses"));
    if (pos == -1) {
        if (!cdr::showErrors(rsp))
            ::AfxMessageBox(_T("Unknown failure from search for locations"),
                            MB_ICONEXCLAMATION);
        EndDialog(IDCANCEL);
        return TRUE;
    }

    // Populate the list control.
    extractChoices(rsp);
    if (cdr::fillListBox(m_choiceList, docSet) > 0) {
		m_choiceList.SetCurSel(0);
		m_choiceList.EnableWindow();
	}
	else {
		::AfxMessageBox(_T("No locations found"));
        EndDialog(IDCANCEL);
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COrgLocs::OnOK() 
{
	// Find out which candidate document the user selected.
	int curSel = m_choiceList.GetCurSel();

    // Don't do anything if there is no selection.
    if (curSel >= 0) {
        CWaitCursor wc;
        CString str;
		m_choiceList.GetText(curSel, str);
        CdrLinkInfo info = cdr::extractLinkInfo(str);
        newTarget = info.target;
        EndDialog(IDOK);
    }
}

void COrgLocs::OnDblclkList1() 
{
	OnOK();
}


void COrgLocs::extractChoices(const CString& rsp)
{
    docSet.clear();
    cdr::Element r = cdr::Element::extractElement(rsp, _T("Address"));
    while (r) {
        cdr::Element id      = r.extractElement(r.getString(), _T("Link"));
        cdr::Element title   = r.extractElement(r.getString(), _T("Data"));
        cdr::SearchResult qr = cdr::SearchResult(
                id.getString(), _T("Organization"), title.getString());
        docSet.push_back(qr);
        r = r.extractElement(rsp, _T("Address"), r.getEndPos());
    }
}
