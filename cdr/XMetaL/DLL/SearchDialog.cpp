/*
 * $Id: SearchDialog.cpp,v 1.1 2000-10-16 22:29:27 bkline Exp $
 *
 * Implementation of dialog object for performing a CDR document search.
 *
 * $Log: not supported by cvs2svn $
 */

// Local headers.
#include "stdafx.h"
#include "resource.h"
#include "SearchDialog.h"
#include "CdrUtil.h"
#include "Cdr.h"
#include "Commands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog dialog


CSearchDialog::CSearchDialog(const std::list<std::string>& typeList,
							 CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDialog::IDD, pParent), docTypes(typeList)
{
	//{{AFX_DATA_INIT(CSearchDialog)
	m_searchString = _T("");
	//}}AFX_DATA_INIT
}

void CSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDialog)
	DDX_Control(pDX, IDC_COMBO1, m_docTypes);
	DDX_Control(pDX, IDC_LIST1, m_docList);
	DDX_Control(pDX, IDC_BUTTON1, m_retrieveButton);
	DDX_Control(pDX, IDOK, m_searchButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_RADIO3, m_titleEquals);
	DDX_Control(pDX, IDC_RADIO2, m_titleContains);
	DDX_Control(pDX, IDC_RADIO1, m_titleStart);
	DDX_Text(pDX, IDC_EDIT1, m_searchString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDialog, CDialog)
	//{{AFX_MSG_MAP(CSearchDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnRetrieveButton)
	ON_BN_CLICKED(IDOK, OnSearchButton)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkDocument)
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
	int curSel = m_docList.GetCurSel();
	if (curSel >= 0) {
		CString str;
		m_docList.GetText(curSel, str);
		std::string s = str;
        if (CCommands::doRetrieve(s))
    		EndDialog(IDCANCEL);	
    }
}

/**
 * Submits a search for CDR documents to the server, and populates
 * the list box with the results.
 */
void CSearchDialog::OnSearchButton() 
{
    // Transfer the dialog's data to this object.
	UpdateData(true);

    // Build the search request.
	std::string cmd = "<CdrSearch><Query MaxDocs='100'>//CdrDoc[";
	int curType = m_docTypes.GetCurSel();

    // Don't do anything unless we have at least a search string or a doc 
    // type.
	if (m_searchString.IsEmpty()) {
		if (curType == 0)
			return;
	}
	else {
		m_searchString.Replace("'", "\\'");
		std::string str = m_searchString;
		std::string op = "=";
		if (m_titleContains.GetCheck() == 1) {
			op = "contains";
			str = std::string("%") + str + "%";
		}
		else if (m_titleStart.GetCheck() == 1) {
			op = "begins";
			str += "%";
		}
		cmd += "CdrCtl/Title " + op + " '" + str + "'";
	}
	if (curType > 0) {
		CString val;
		m_docTypes.GetLBText(curType, val);
		if (!m_searchString.IsEmpty())
			cmd += " and ";
		cmd += "CdrCtl/DocType = '" + (std::string)val + "'";
	}
	cmd += "]/CdrCtl/DocId</Query></CdrSearch>";

    // Submit the request to the CDR server.
	CWaitCursor wc;
	std::string rsp = CdrSocket::sendCommand(cmd);
	size_t pos = rsp.find("<QueryResults");
	if (pos == rsp.npos) {
		if (!cdr::showErrors(rsp))
			::AfxMessageBox("Unknown failure from search", 
			MB_ICONEXCLAMATION);
		EndDialog(IDCANCEL);
		return;
	}

    // Populate the dialog's list box with the results.
	m_docList.ResetContent();
    if (cdr::fillListBox(m_docList, rsp) > 0) {
		m_docList.SetCurSel(0);
		m_docList.EnableWindow();
	}
	else
		::AfxMessageBox("No documents match this query");
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
	
	m_titleStart.SetButtonStyle(BS_AUTORADIOBUTTON);
	m_titleContains.SetButtonStyle(BS_AUTORADIOBUTTON);
	m_titleEquals.SetButtonStyle(BS_AUTORADIOBUTTON);
    m_titleStart.SetCheck(1);
	std::list<std::string>::const_iterator i = docTypes.begin();
	while (i != docTypes.end())
		m_docTypes.AddString((*i++).c_str());
	m_docTypes.SetCurSel(0);
	
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
