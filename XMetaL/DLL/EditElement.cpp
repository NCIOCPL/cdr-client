/*
 * $Id$
 *
 * Implementation of dialog object for editing inter-document links.
 *
 * JIRA::OCECDR-3732 - custom support for genetics picklists
 */

// Local headers.
#include "stdafx.h"
#include "afxtempl.h"
#include "resource.h"
#include "EditElement.h"
#include "PersonLocs.h"
#include "OrgLocs.h"
#include "CdrUtil.h"
#include "Cdr.h"
#include "Commands.h"

// System headers.
#include <sstream>
#include <algorithm>
#include <functional>

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
                           Type elemType,
                           CWnd* pParent /*=NULL*/)
    : CDialog(CEditElement::IDD, pParent), docType(t), element(e),
      type(elemType)
{
    //{{AFX_DATA_INIT(CEditElement)
    m_title = _T("");
    //}}AFX_DATA_INIT
}


void CEditElement::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEditElement)
    DDX_Control(pDX, IDC_LINK_TITLE_LABEL, m_label);
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
    ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
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
        switch (type) {
            case NORMAL:
                ::AfxMessageBox(_T("Title string is empty."));
                break;
            case LEAD_ORG:
            case ORG_LOCATION:
                ::AfxMessageBox(_T("Organization name string is empty."));
                break;
        }
        return;
    }

    // Escape underscores and left brackets, but not percent sign.
    m_title.Replace(_T("["), _T("[[]"));
    m_title.Replace(_T("_"), _T("[_]"));

    std::basic_ostringstream<TCHAR> cmd;
    CString rsp;
    CWaitCursor wc;
    int pos = 0;
    switch (type) {
        case NORMAL:
        case PROT_PERSON:
        case PRIV_PRACTICE:
        case ORG_LOCATION:

            // Build the command to request the list of documents.
            cmd << _T("<CdrSearchLinks MaxDocs='150'><SourceDocType>")
                << (LPCTSTR)docType
                << _T("</SourceDocType><SourceElementType>")
                << (LPCTSTR)element
                << _T("</SourceElementType><TargetTitlePattern>")
                << (LPCTSTR)m_title
                << _T("%</TargetTitlePattern></CdrSearchLinks>");

            // Submit the request to the CDR server.
            rsp = CdrSocket::sendCommand(cmd.str().c_str());
            pos = rsp.Find(_T("<QueryResults"));
            if (pos == -1) {
                if (!cdr::showErrors(rsp))
                    ::AfxMessageBox(_T("Unknown failure from search"),
                                    MB_ICONEXCLAMATION);
                EndDialog(IDCANCEL);
                return;
            }

            // Extract the document information from the response.
            cdr::extractSearchResults(rsp, docSet);
            break;

        case LEAD_ORG:

            cmd << _T("<CdrReport>")
                   _T("<ReportName>Lead Organization Picklist</ReportName>")
                   _T("<ReportParams><ReportParam Name='SearchTerm' Value=\"")
                << (LPCTSTR)m_title
                << _T("\"/></ReportParams></CdrReport>");
            rsp = CdrSocket::sendCommand(cmd.str().c_str());
            pos = rsp.Find(_T("<ReportBody"));
            if (pos == -1) {
                if (!cdr::showErrors(rsp))
                    ::AfxMessageBox(_T("Unknown failure from search"),
                                    MB_ICONEXCLAMATION);
                EndDialog(IDCANCEL);
                return;
            }

            extractLeadOrgs(rsp);
            break;

        case GP_SYNDROME:

            cmd << _T("<CdrReport>")
                   _T("<ReportName>Genetics Syndromes</ReportName>")
                   _T("<ReportParams><ReportParam Name='TitlePattern' Value=\"")
                << (LPCTSTR)m_title
                << _T("\"/></ReportParams></CdrReport>");
            rsp = CdrSocket::sendCommand(cmd.str().c_str());
            pos = rsp.Find(_T("<ReportBody"));
            if (pos == -1) {
                if (!cdr::showErrors(rsp))
                    ::AfxMessageBox(_T("Unknown failure from search"),
                                    MB_ICONEXCLAMATION);
                EndDialog(IDCANCEL);
                return;
            }

            extractGeneticsSyndromes(rsp);
            break;
    }

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
    // Find out where we are.


    // Find out which candidate documents the user selected.
    int selCount = m_linkList.GetSelCount();
    if (selCount > 0) {
        CWaitCursor wc;
        CArray<int, int> selections;
        selections.SetSize(selCount);
        m_linkList.GetSelItems(selCount, selections.GetData());
        CString str;
        int i = 0;
        int curSel = selections[i];
        m_linkList.GetText(curSel, str);
        switch (type) {
            case NORMAL:
            case GP_SYNDROME:
                CCommands::doInsertLink(str);
                while (++i < selCount) {
                    ::Selection selection = cdr::getApp().GetSelection();
                    if (!selection.FindInsertLocation(element, TRUE)) {
                        ::AfxMessageBox(_T("You selected more items than ")
                                        _T("are allowed at this position."));
                        break;
                    }
                    selection.InsertElement(element);
                    selection.MoveToElement(element, TRUE);
                    curSel = selections[i];
                    m_linkList.GetText(curSel, str);
                    CCommands::doInsertLink(str);
                }
                break;
            case LEAD_ORG:
                insertLeadOrg(str);
                break;
            case PROT_PERSON:
            case PRIV_PRACTICE:
                if (!insertProtPerson(str))
                    return;
                break;
            case ORG_LOCATION:
                if (!insertOrgLocation(str))
                    return;
                break;
        }
        EndDialog(IDOK);
    }
}

bool CEditElement::insertProtPerson(const CString& str)
{
    CdrLinkInfo linkInfo = cdr::extractLinkInfo(str);
    CString newTarget;
    CPersonLocs personLocs(linkInfo.target, newTarget, type == PRIV_PRACTICE);
    if (personLocs.DoModal() == IDOK) {
        CCommands::doInsertLink(_T("[") + newTarget + _T("] ")
            + linkInfo.data);
        return true;
    }
    return false;
}

bool CEditElement::insertOrgLocation(const CString& str)
{
    CdrLinkInfo linkInfo = cdr::extractLinkInfo(str);
    CString newTarget;
    COrgLocs orgLocs(linkInfo.target, newTarget);
    if (orgLocs.DoModal() == IDOK) {
        CCommands::doInsertLink(_T("[") + newTarget + _T("] ")
            + linkInfo.data);
        return true;
    }
    return false;
}

/**
 * Set LeadOrganizationID under current ProtocolLeadOrg element to match 
 * user's selection.  Set Group attribute with the proper value (Yes or No).
 */
void CEditElement::insertLeadOrg(const CString& str)
{
    // Pull the pieces from the picklist string.
    CdrLinkInfo info = cdr::extractLinkInfo(str);

    // Find the matching record in the docSet list.
    cdr::DocSet::iterator i = std::find_if(docSet.begin(), docSet.end(),
            std::bind2nd(std::equal_to<cdr::SearchResult>(), info.target));
    if (i == docSet.end()) {
        ::AfxMessageBox(_T("Internal error: can't find ") + 
                info.target + _T(" in result set info"));
        return;
    }

    // Find the ProtocolLeadOrg element's position.
    ::Range leadOrgElemPos = cdr::getElemRange(_T("ProtocolLeadOrg"));

    if (!leadOrgElemPos)
        return;

    // Set the Group attribute appropriately.
    ::DOMElement leadOrgElem = leadOrgElemPos.GetContainerNode();
    leadOrgElem.setAttribute(_T("Group"), i->isGroup() ? _T("Yes") : _T("No"));

    // Find or create the LeadOrganizationID child.
    ::Range orgIdPos = cdr::findOrCreateChild(leadOrgElemPos, 
                                              _T("LeadOrganizationID"));
    if (orgIdPos) {
        orgIdPos.SetReadOnlyContainer(FALSE);
        ::DOMElement elem = orgIdPos.GetContainerNode();

        // Plug in the link attribute.
        elem.setAttribute(_T("cdr:ref"), info.target);

        // Find the text node for the element.
        ::DOMText textNode = elem.GetFirstChild();
        while (textNode && textNode.GetNodeType() != 3) // DOMText
            textNode = textNode.GetNextSibling();
        if (textNode)
            textNode.SetData(info.data);
        else {
            ::_Document curDoc = cdr::getApp().GetActiveDocument();
            textNode = curDoc.createTextNode(info.data);
            ::DOMNode dummy = elem.appendChild(textNode);
        }        
        orgIdPos.SetReadOnlyContainer(TRUE);
        orgIdPos.Select();
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
    CString url = _T("http://")
                + CdrSocket::getHostName()
                + _T("/cgi-bin/cdr/QcReport.py?Session=")
                + CdrSocket::getSessionString()
                + _T("&DocId=") 
                + info.Mid(pos, endPos - pos);
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

void CEditElement::extractLeadOrgs(const CString& rsp)
{
    docSet.clear();
    cdr::Element r = cdr::Element::extractElement(rsp, _T("ReportRow"));
    while (r) {
        cdr::Element id      = r.extractElement(r.getString(), _T("DocId"));
        cdr::Element title   = r.extractElement(r.getString(), _T("DocTitle"));
        cdr::Element group   = r.extractElement(r.getString(), _T("Group"));
        cdr::SearchResult qr = cdr::SearchResult(
                id.getString(), _T("Organization"), title.getString(), 
                group.getString() == _T("Yes"));
        docSet.push_back(qr);
        r = r.extractElement(rsp, _T("ReportRow"), r.getEndPos());
    }
}

void CEditElement::extractGeneticsSyndromes(const CString& rsp)
{
    docSet.clear();
    cdr::Element r = cdr::Element::extractElement(rsp, _T("ReportRow"));
    while (r) {
        cdr::Element id      = r.extractElement(r.getString(), _T("DocId"));
        cdr::Element title   = r.extractElement(r.getString(), _T("DocTitle"));
        cdr::SearchResult qr = cdr::SearchResult(
            id.getString(), _T("Term"), title.getString());
        docSet.push_back(qr);
        r = r.extractElement(rsp, _T("ReportRow"), r.getEndPos());
    }
}

BOOL CEditElement::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // Find the source element for the link.
    ::Range selection = cdr::getApp().GetSelection();
    ::DOMElement elem = selection.GetContainerNode();
    while (elem && elem.GetNodeType() != 1) // DOMElement
        elem = elem.GetParentNode();
    if (elem) {

        // Find the text node for the element.
        ::DOMText textNode = elem.GetFirstChild();
        while (textNode && textNode.GetNodeType() != 3) // DOMText
            textNode = textNode.GetNextSibling();
        if (textNode)
            m_title = textNode.GetData();
    }

    if (type == LEAD_ORG) {
        SetWindowText(_T("Lead Organization"));
        m_label.SetWindowText(_T("Name"));
    }
    /*
     *  CreatePFont(25,  0,  0,  0, 400, FALSE, FALSE, 0,
     *              ANSI_CHARSET, OUT_DEFAULT_PRECIS,
     *              CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
     *              DEFAULT_PITCH | FF_SWISS, "Arial"); 
     */

    if (biggerFont.CreatePointFont(100, _T("Arial")))
        m_linkList.SetFont(&biggerFont);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditElement::OnLbnSelchangeList1()
{
    if (type != NORMAL && type != GP_SYNDROME) {
        int sel = m_linkList.GetCurSel();
        int selCount = m_linkList.GetSelCount();
        //CString msg;
        //msg.Format(L"cursel is %d; selcount is %d", sel, selCount);
        //::AfxMessageBox((LPCTSTR)msg);
        while (selCount > 1) {
            int selections[2];
            m_linkList.GetSelItems(2, selections);
            for (int i = 0; i < 2; ++i) {
                int j = selections[i];
                if (j != sel)
                    m_linkList.SetSel(j, FALSE);
            }
            selCount = m_linkList.GetSelCount();
            //msg.Format(L"now selcount is %d", selCount);
            //::AfxMessageBox((LPCTSTR)msg);
        }
    }
}
