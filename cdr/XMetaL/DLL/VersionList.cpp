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
    std::basic_ostringstream<TCHAR> cmd;
    cmd << _T("<CdrListVersions><DocId>")
        << (LPCTSTR)docId
        << _T("</DocId><NumVersions>5</NumVersions></CdrListVersions>");

    // Submit the request to the CDR server.
    CWaitCursor wc;
    CString rsp = CdrSocket::sendCommand(cmd.str().c_str());
    int pos = rsp.Find(_T("<Errors"));
    if (pos != -1) {
        if (!cdr::showErrors(rsp))
            ::AfxMessageBox(_T("Unknown failure retrieving versions"),
                            MB_ICONEXCLAMATION);
        EndDialog(IDCANCEL);
        return TRUE;
    }

    // Populate the list control.
    int numVersions = 0;
    cdr::Element v = cdr::Element::extractElement(rsp, _T("Version"));
    while (v) {
        cdr::Element num      = v.extractElement(v.getString(), _T("Num"));
        cdr::Element comment  = v.extractElement(v.getString(), _T("Comment"));
        CString commentString = comment ? comment.getString() : _T("No comment");
        commentString.Replace(_T("\r"), _T(" "));
        commentString.Replace(_T("\n"), _T(" "));
        while (commentString.Replace(_T("  "), _T(" ")) > 0)
            ;
        CString str           = _T("[") 
                              + num.getString()
                              + _T("] ")
                              + commentString;
        m_choiceList.AddString(str);
        ++numVersions;
        v = v.extractElement(rsp, _T("Version"), v.getEndPos());
    }

    // Make sure we have at least one version.
	if (!numVersions) {
		::AfxMessageBox(_T("No versions found"));
        EndDialog(IDCANCEL);
    }
    else {
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
