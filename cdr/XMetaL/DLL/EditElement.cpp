/*
 * $Id: EditElement.cpp,v 1.1 2000-10-16 22:29:27 bkline Exp $
 *
 * Implementation of dialog object for editing inter-document links.
 *
 * $Log: not supported by cvs2svn $
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
CEditElement::CEditElement(const std::string& t,
                           const std::string& e,
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
        ::AfxMessageBox("Title string is empty.");
        return;
    }

    // Escape characters used as SQL Server wildcards.
    m_title.Replace("[", "[[]");
    m_title.Replace("%", "[%]");
    m_title.Replace("_", "[_]");

    // Build the command to request the list of documents.
    std::ostringstream cmd;
    cmd << "<CdrSearchLinks MaxDocs='150'><SourceDocType>"
        << docType
        << "</SourceDocType><SourceElementType>"
        << element
        << "</SourceElementType><TargetTitlePattern>"
        << (const char*)m_title
        << "%</TargetTitlePattern></CdrSearchLinks>"
        << std::ends;

    // Submit the request to the CDR server.
	CWaitCursor wc;
	std::string rsp = CdrSocket::sendCommand(cmd.str());
	size_t pos = rsp.find("<QueryResults");
	if (pos == rsp.npos) {
		if (!cdr::showErrors(rsp))
			::AfxMessageBox("Unknown failure from search", 
			                MB_ICONEXCLAMATION);
		EndDialog(IDCANCEL);
		return;
	}

    // Extract the document information from the response.
    if (cdr::fillListBox(m_linkList, rsp) > 0) {
		m_linkList.SetCurSel(0);
		m_linkList.EnableWindow();
	}
	else
		::AfxMessageBox("No documents match this query");

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
		std::string s = str;
        CCommands::doInsertLink(s);
        EndDialog(IDCANCEL);
    }
}

/**
 * Allows the user to double-click on a link target as an alternate to
 * the "Select" button.
 */
void CEditElement::OnDblclkLink() 
{
    OnSelectButton();
}
