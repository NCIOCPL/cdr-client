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
    StringType stringType;
    cdr::DocSet docSet;
    CString searchString;
    BOOL checkOut;
    int docType;
    int selection;
    bool empty;
    LastSearch() : docType(-1), selection(-1), empty(true),
                   checkOut(false){}
};
static LastSearch lastSearch;

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog dialog


CSearchDialog::CSearchDialog(const std::list<CString>& typeList,
                             CWnd* pParent /*=NULL*/)
    : CDialog(CSearchDialog::IDD, pParent), docTypes(typeList)
{
    //{{AFX_DATA_INIT(CSearchDialog)
    m_searchString = _T("");
    m_checkOut = FALSE;
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
    DDX_Check(pDX, IDC_CHECK1, m_checkOut);
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
    int curSel = m_docList.GetCurSel();
    if (curSel >= 0) {
        CString str;
        m_docList.GetText(curSel, str);
        if (CCommands::doRetrieve(str, m_checkOut))
            EndDialog(IDCANCEL);    
        lastSearch.selection = curSel;
        lastSearch.checkOut  = m_checkOut;
    }
}

/**
 * Submits a search for CDR documents to the server, and populates
 * the list box with the results.
 */
void CSearchDialog::OnSearchButton() 
{
    // In case we blow up, don't leave a live LastSearch object around.
    lastSearch.empty = true;

    // Transfer the dialog's data to this object.
    UpdateData(true);

    // Build the search request.
    CString cmd = _T("<CdrSearch><Query MaxDocs='100'>//CdrDoc[");
    int curType = m_docTypes.GetCurSel();
    lastSearch.docType = curType;

    // Don't do anything unless we have at least a search string or a doc 
    // type.
    if (m_searchString.IsEmpty()) {
        if (curType == 0)
            return;
    }
    else {
        lastSearch.searchString = m_searchString;
        m_searchString.Replace(_T("'"), _T("\\'"));
        CString op = _T("=");
        if (m_titleContains.GetCheck() == 1) {
            op = _T("contains");
            m_searchString = _T("%") + m_searchString + _T("%");
            lastSearch.stringType = LastSearch::CONTAINS;
        }
        else if (m_titleStart.GetCheck() == 1) {
            op = _T("begins");
            m_searchString += _T("%");
            lastSearch.stringType = LastSearch::BEGINS;
        }
        else
            lastSearch.stringType = LastSearch::ALL;
        cmd += _T("CdrCtl/Title ") + op + _T(" '") + 
            cdr::encode(m_searchString) + _T("'");
    }
    if (curType > 0) {
        CString val;
        m_docTypes.GetLBText(curType, val);
        if (!m_searchString.IsEmpty())
            cmd += _T(" and ");
        cmd += _T("CdrCtl/DocType = '") + val + _T("'");
    }
    cmd += "]/CdrCtl/DocId</Query></CdrSearch>";

    // Submit the request to the CDR server.
    CWaitCursor wc;
    CString rsp = CdrSocket::sendCommand(cmd);
    int pos = rsp.Find(_T("<QueryResults"));
    if (pos == -1) {
        if (!cdr::showErrors(rsp))
            ::AfxMessageBox(_T("Unknown failure from search"),
            MB_ICONEXCLAMATION);
        EndDialog(IDCANCEL);
        return;
    }

    // Populate the dialog's list box with the results.
    m_docList.ResetContent();
    cdr::extractSearchResults(rsp, lastSearch.docSet);
    if (cdr::fillListBox(m_docList, lastSearch.docSet) > 0) {
        m_docList.SetCurSel(0);
        m_docList.EnableWindow();
        lastSearch.selection = 0;
    }
    else {
        ::AfxMessageBox(_T("No documents match this query"));
        lastSearch.selection = -1;
    }

    // Remember this search.
    lastSearch.checkOut     = m_checkOut;
    lastSearch.empty        = false;
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
    std::list<CString>::const_iterator i = docTypes.begin();
    while (i != docTypes.end())
        m_docTypes.AddString((*i++));
    m_docTypes.SetCurSel(0);
    if (!lastSearch.empty) {
        m_searchString = lastSearch.searchString;
        m_checkOut     = lastSearch.checkOut;
        m_docTypes.SetCurSel(lastSearch.docType);
        m_titleStart.SetCheck(0);
        m_titleContains.SetCheck(0);
        m_titleEquals.SetCheck(0);
        switch (lastSearch.stringType) {
        case LastSearch::BEGINS:
        default:
            m_titleStart.SetCheck(1);
            break;
        case LastSearch::CONTAINS:
            m_titleContains.SetCheck(1);
            break;
        case LastSearch::ALL:
            m_titleEquals.SetCheck(1);
            break;
        }
        int num = cdr::fillListBox(m_docList, lastSearch.docSet);
        if (lastSearch.selection >= 0 && lastSearch.selection < num)
            m_docList.SetCurSel(lastSearch.selection);
        m_docList.EnableWindow();
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
    int curSel = m_docList.GetCurSel();
    if (curSel >= 0) {
        CString str;
        m_docList.GetText(curSel, str);
        unsigned int docNo = cdr::getDocNo(str);

        // Make canonical document ID.
        CString docId = cdr::docIdString(docNo);
        CVersionList versionList(docId);
        if (versionList.DoModal() == IDOK)
            EndDialog(IDCANCEL);
    }
}
