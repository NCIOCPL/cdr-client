// ParticOrgs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ParticOrgs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <sstream>
#include <algorithm>
#include <functional>

/////////////////////////////////////////////////////////////////////////////
// CParticOrgs dialog


CParticOrgs::CParticOrgs(const CString& lo, 
                         CWnd* pParent /*=NULL*/)
	: CDialog(CParticOrgs::IDD, pParent), leadOrg(lo)
{
	//{{AFX_DATA_INIT(CParticOrgs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CParticOrgs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParticOrgs)
	DDX_Control(pDX, IDC_LIST1, m_orgList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParticOrgs, CDialog)
	//{{AFX_MSG_MAP(CParticOrgs)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParticOrgs message handlers

void CParticOrgs::OnDblclkList1() 
{
    OnOK();	
}

BOOL CParticOrgs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Create the command.
    std::basic_ostringstream<TCHAR> cmd;
    cmd << _T("<CdrReport><ReportName>Participating Organizations Picklist")
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
    if (cdr::fillListBox(m_orgList, docSet) > 0) {
		m_orgList.SetCurSel(0);
		m_orgList.EnableWindow();
	}
	else {
		::AfxMessageBox(_T("No organizations are eligible to ")
                        _T("participate in a protocol with ")
                        _T("this organization"));
        EndDialog(IDCANCEL);
    }
	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParticOrgs::OnOK() 
{
    // Don't bother if no selections have been made
    if (m_orgList.GetSelCount() < 1) {
        ::AfxMessageBox(_T("No organizations selected"));
        return;
    }

    // Find out which items have been selected.
    int* indices = 0;
    try {
        indices = new int[m_orgList.GetSelCount()];
        int n = m_orgList.GetSelItems(m_orgList.GetSelCount(), indices);
        if (n != m_orgList.GetSelCount()) {
            ::AfxMessageBox(_T("MFC list selection mechanism broken"));
            delete[] indices;
            EndDialog(IDCANCEL);
            return;
        }

        // Find the ProtocolSites element location.
        ::Range lopLoc = cdr::getElemRange(_T("ProtocolLeadOrg"));
        if (!lopLoc) {
            ::AfxMessageBox(_T("ProtocolLeadOrg for ")
                            _T("current location not found"));
            delete[] indices;
            EndDialog(IDCANCEL);
            return;
        }
        ::Range psLoc = cdr::findOrCreateChild(lopLoc, _T("ProtocolSites"));
        if (!psLoc) {
            ::AfxMessageBox(_T("Can't find or create ProtocolSites element"));
            delete[] indices;
            EndDialog(IDCANCEL);
            return;
        }

        // Insert each organization selected.
        for (int i = 0; i < n; ++i) {
            CString str;
            m_orgList.GetText(indices[i], str);
            
            // Pull the pieces from the picklist string.
            CdrLinkInfo info = cdr::extractLinkInfo(str);        
            cdr::DocSet::iterator iter = std::find_if(docSet.begin(), 
                docSet.end(),
                std::bind2nd(std::equal_to<cdr::SearchResult>(), info.target));
            if (iter == docSet.end()) {
		        ::AfxMessageBox(_T("Internal error: can't find ") + 
                        info.target + _T(" in result set info"));
                delete[] indices;
                EndDialog(IDCANCEL);
                return;
            }

            // If no principal investigators, offer opportunity to skip org.
            if (iter->getPiList().size() < 1) {
                CString msg;
                msg.Format(_T("Organization %s has no associated ")
                           _T("principal investigators; insert anyway?"), 
                           str);
                int rsp = ::AfxMessageBox(msg, MB_YESNO);
                if (rsp != IDYES)
                    continue;
            }

            // Find a nice spot for the organization.
            psLoc.SelectElement();
            psLoc.Collapse(0);
            if (!psLoc.FindInsertLocation(_T("OrgSite"), FALSE)) {
                ::AfxMessageBox(_T("Unable to insert Site element"));
                delete[] indices;
                EndDialog(IDCANCEL);
                return;
            }

            std::basic_ostringstream<TCHAR> dat;
            CString statString = _T("Active");
            if (iter->getCoopMemb() == _T("Affiliate"))
                statString = _T("Approved-not yet active");
            dat << _T("<OrgSite><OrgSiteID cdr:ref='")
                << (LPCTSTR)info.target
                << _T("'>")
                << (LPCTSTR)info.data
                << _T("</OrgSiteID><OrgSiteStatus>")
                << (LPCTSTR)statString
                << _T("</OrgSiteStatus><OrgSiteContact>");
            cdr::LinkInfoList::const_iterator pi = iter->getPiList().begin();
            while (pi != iter->getPiList().end()) {
                dat << _T("<SpecificPerson><Person cdr:ref='")
                    << (LPCTSTR)pi->target
                    << _T("'>")
                    << (LPCTSTR)pi->data
                    << _T("</Person><Role>Principal investigator</Role>")
                       _T("</SpecificPerson>");
                ++pi;
            }
            dat << _T("</SiteContact></OrgSite>");
            psLoc.PasteString(dat.str().c_str());
        }
        delete[] indices;
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected exception raised"));
        delete[] indices;
    }
	
	EndDialog(IDOK);
}

void CParticOrgs::extractChoices(const CString& rsp)
{
    docSet.clear();
    cdr::Element r = cdr::Element::extractElement(rsp, _T("ReportRow"));
    while (r) {
        cdr::LinkInfoList infoList;
        cdr::Element id       = r.extractElement(r.getString(), _T("DocId"));
        cdr::Element title    = r.extractElement(r.getString(), _T("DocTitle"));
        cdr::Element coopMemb = r.extractElement(r.getString(), _T("CoopMember"));
        cdr::Element pi       = r.extractElement(r.getString(), _T("PI"));
        while (pi) {
            CString link = pi.getAttribute(_T("cdr:ref"));
            CString data = pi.getString();
            if (!link.IsEmpty() && !data.IsEmpty())
                infoList.push_back(CdrLinkInfo(link, data));
            pi = r.extractElement(r.getString(), _T("PI"), pi.getEndPos());
        }
        cdr::SearchResult sr = cdr::SearchResult(
                id.getString(), _T("Organization"), title.getString(), 
                false, coopMemb.getString(), infoList);
        docSet.push_back(sr);
        r = r.extractElement(rsp, _T("ReportRow"), r.getEndPos());
    }
}
