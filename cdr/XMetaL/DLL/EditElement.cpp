/*
 * $Id: EditElement.cpp,v 1.3 2001-06-09 12:35:21 bkline Exp $
 *
 * Implementation of dialog object for editing inter-document links.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2001/04/18 14:45:01  bkline
 * Removed std::ends (no longer using obsolete strstream).
 *
 * Revision 1.1  2000/10/16 22:29:27  bkline
 * Initial revision
 *
 */

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "EditElement.h"
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
// CEditElement dialog


/**
 * Constructs a new dialog object for editing inter-document links.
 *
 *  @param  t           reference to string identifying document type.
 *  @param  e           reference to string containing current element tag.
 *  @param  pParent     address of parent window.
 */
CEditElement::CEditElement(const CString& t,
                           const CString& e,
                           CWnd* pParent /*=NULL*/)
	: CDialog(CEditElement::IDD, pParent), docType(t), element(e)
{
	//{{AFX_DATA_INIT(CEditElement)
	m_title = _T("");
	//}}AFX_DATA_INIT
}


void CEditElement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditElement)
	DDX_Control(pDX, IDC_LIST1, m_linkList);
	DDX_Text(pDX, IDC_EDIT1, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditElement, CDialog)
	//{{AFX_MSG_MAP(CEditElement)
	ON_BN_CLICKED(IDC_BUTTON1, OnSelectButton)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkLink)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditElement message handlers

/**
 * Asks the server for a list of candidate documents which could be
 * used as link targets from the current element of the active document.
 */
void CEditElement::OnOK() 
{
    // Transfer the data from the dialog form to this object.
	UpdateData(true);

    // Make sure the user has specified at least a portion of the title.
    if (m_title.IsEmpty()) {
        ::AfxMessageBox(_T("Title string is empty."));
        return;
    }

    // Escape characters used as SQL Server wildcards.
    m_title.Replace(_T("["), _T("[[]"));
    m_title.Replace(_T("%"), _T("[%]"));
    m_title.Replace(_T("_"), _T("[_]"));

    // Build the command to request the list of documents.
    std::basic_ostringstream<TCHAR> cmd;
    cmd << _T("<CdrSearchLinks MaxDocs='150'><SourceDocType>")
        << (LPCTSTR)docType
        << _T("</SourceDocType><SourceElementType>")
        << (LPCTSTR)element
        << _T("</SourceElementType><TargetTitlePattern>")
        << (LPCTSTR)m_title
        << _T("%</TargetTitlePattern></CdrSearchLinks>");

    // Submit the request to the CDR server.
	CWaitCursor wc;
	CString rsp = CdrSocket::sendCommand(cmd.str().c_str());
	int pos = rsp.Find(_T("<QueryResults"));
	if (pos == -1) {
		if (!cdr::showErrors(rsp))
			::AfxMessageBox(_T("Unknown failure from search"),
			                MB_ICONEXCLAMATION);
		EndDialog(IDCANCEL);
		return;
	}

    // Extract the document information from the response.
    cdr::DocSet docSet = cdr::extractSearchResults(rsp);
    if (cdr::fillListBox(m_linkList, docSet) > 0) {
		m_linkList.SetCurSel(0);
		m_linkList.EnableWindow();
	}
	else
		::AfxMessageBox(_T("No documents match this query"));

}

/**
 * Inserts the selected document's link and title into the current element.
 */
void CEditElement::OnSelectButton() 
{
    // Find out which candidate document the user selected.
	int curSel = m_linkList.GetCurSel();

    // Don't do anything if there is no selection.
    if (curSel >= 0) {
        CWaitCursor wc;
        CString str;
		m_linkList.GetText(curSel, str);
        CCommands::doInsertLink(str);
        EndDialog(IDCANCEL);
    }
}

#define SERVER_SIDE_OF_LINK_PICKLISTS_WORKING 1

/**
 * Allows the user to double-click on a link target as an alternate to
 * the "Select" button.
 */
void CEditElement::OnDblclkLink() 
{
    OnSelectButton();
}

void CEditElement::OnButton2() 
{
    UpdateData(true);
    COleDispatchDriver ie;
    if (!ie.CreateDispatch(_T("InternetExplorer.Application"))) {
        ::AfxMessageBox(_T("Unable to launch Internet Explorer"),
            MB_ICONEXCLAMATION);
        return;
    }
#if SERVER_SIDE_OF_LINK_PICKLISTS_WORKING
	int curSel = m_linkList.GetCurSel();

    // Don't do anything if there is no selection.
    if (curSel < 0)
        return;

    // Parse out the document ID.
    CString info;
	m_linkList.GetText(curSel, info);
    int pos = info.Find(_T("["));
    if (pos == -1) {
        ::AfxMessageBox(_T("Unable to find document ID start delimiter."));
        return;
    }
    int endPos = info.Find(_T("]"), ++pos);
    if (endPos == -1) {
        ::AfxMessageBox(_T("Unable to find document ID end delimiter."));
        return;
    }
    CString url = _T("http://mmdb2.nci.nih.gov/cgi-bin/cdr/ShowDocXml.py?")
                  _T("DocId=") + info.Mid(pos, endPos - pos);
#else // just proof-of-concept demo
    CString url = m_title;
    if (url.IsEmpty())
        //url = _T("http://mmdb2.nci.nih.gov/cgi-bin/cdr/Filter.py?DocId=CDR106085&Filter=CDR190703");
        url = _T("http://mmdb2.nci.nih.gov/cgi-bin/cdr/ShowDocXml.py?DocId=CDR100000");
#endif
    DISPID dispid;
    OLECHAR* member = _T("Navigate");
    HRESULT hresult = ie.m_lpDispatch->GetIDsOfNames(IID_NULL, 
        &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
    if (hresult != S_OK) {
        ::AfxMessageBox(_T("Unable to launch Internet Explorer"),
            MB_ICONEXCLAMATION);
        return;
    }
    static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR 
                          VTS_PVARIANT VTS_PVARIANT;
    COleVariant dummy;
    ie.InvokeHelper(dispid, DISPATCH_METHOD, VT_EMPTY, NULL, parms, 
        url, 0L, _T("CdrViewWindow"), &dummy, &dummy);
}
