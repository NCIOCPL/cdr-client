/*
 * $Id: Commands.cpp,v 1.19 2002-05-08 21:20:52 bkline Exp $
 *
 * Implementation of CCdrApp and DLL registration.
 *
 * To do: rationalize error return codes for automation commands.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.18  2002/05/06 18:48:24  bkline
 * Added code to populate comment for version table.
 *
 * Revision 1.17  2002/04/29 11:01:31  bkline
 * Added code to eliminate extra space after CdrDocCtl element.
 *
 * Revision 1.16  2002/04/20 19:19:58  bkline
 * Removed version string from search and retrieve dialogs.  Will replace
 * soon with more sophisticated picklist for most recent versions.
 *
 * Revision 1.15  2002/04/18 21:49:04  bkline
 * Added more sophisticated exception handling.
 *
 * Revision 1.14  2002/03/09 03:24:46  bkline
 * Implemented enhancement for Issue #125.
 *
 * Revision 1.13  2002/03/01 21:13:40  bkline
 * Fixed bug that was causing saved document to be marked readonly.
 *
 * Revision 1.12  2002/02/20 12:23:03  bkline
 * Set edit command to return non-zero on cancelled command.
 *
 * Revision 1.11  2002/02/19 23:14:40  bkline
 * Modified getOrgAddress to pull down and insert SpecificPostalAddress only.
 *
 * Revision 1.10  2002/02/15 23:05:01  bkline
 * Changed save command so that document is not reopened after checkin.
 *
 * Revision 1.9  2002/02/14 01:13:22  bkline
 * Dialog box message changed for new document save.
 *
 * Revision 1.8  2002/02/01 22:01:03  bkline
 * Removed doRetrieve call in checkIn command.  Fixed save command to
 * refresh local copy of document even if validation failed.
 *
 * Revision 1.7  2002/01/22 22:50:53  bkline
 * Some code cleanup.
 *
 * Revision 1.6  2001/11/27 14:21:01  bkline
 * Version used at November 2001 demo.
 *
 * Revision 1.5  2001/06/14 01:21:18  bkline
 * Added code to pull down a fresh copy of the CSS stylesheets for the
 * client.  Added new isReadOnly() command.
 *
 * Revision 1.4  2001/06/11 18:27:18  bkline
 * Snapshot prior to re-working automation support using CCmdTarget.
 *
 * Revision 1.3  2001/06/09 12:33:45  bkline
 * Switched to Unicode; added code to sync client with server.
 *
 * Revision 1.2  2001/04/18 14:46:24  bkline
 * Switched to extracting document types from Type attribute (instead of
 * inferring it from first tag).  Removed some dead code.
 *
 * Revision 1.1  2000/10/16 22:29:27  bkline
 * Initial revision
 */

// Local headers.
#include "stdafx.h"
#include "Cdr.h"
#include "Commands.h"
#include "CdrUtil.h"
#include "LogonDialog.h"
#include "RetrieveDialog.h"
#include "SearchDialog.h"
#include "SaveDialog.h"
#include "ValidateDialog.h"
#include "EditElement.h"
#include "SchemaPicklist.h"
#include "LogonProgress.h"
#include "ProtUpdPerson.h"
#include "ParticOrgs.h"
#include "CheckIn.h"
#include "PassedValidation.h"
#include "resource.h"

// System headers
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <process.h>
#include <direct.h>

// Prevent annoying warning from compiler about Microsoft's own bugs.
#pragma warning(disable : 4503)

// Local functions.
static void     getDocTypeStrings(CString& err);
static void     messageLoop();
static void removeDoc(const CString& docId);
static bool		openDoc(const CString& resp, const CString& docId,
						BOOL checkOut);
static CString& fixDoc(CString& doc, const CString& ctl, 
                       const CString& docType, bool readOnly);

// Local data.
static cdr::StringList      docTypeStrings;
static cdr::ValidValueSets  validValueSets;
static cdr::ElementSets     linkingElements;
CString CCommands::username;

/**
 * Determines whether a given element in a particular document type can
 * link to another document or fragment.  Do this by checking the set of 
 * linking elements we downloaded at startup.
 *
 *  @param  docType     string representing the document type.
 *  @param  elemName    string naming the element.
 *  @return             <code>true</code> iff the element can link to
 *                      another document or fragment.
 */
static bool isLinkingElement(const CString& docType,
                             const CString& elemName)
{
    if (linkingElements.find(docType) == linkingElements.end())
        return false;
    cdr::StringSet& ss = linkingElements[docType];
    return ss.find(elemName) != ss.end();
}

/**
 * Converts a reference to an OLE VARIANT object to an MFC
 * string.  Recurses if necessary to handle additional levels
 * of indirection.
 *
 *  @param  v                   reference to OLE VARIANT object.
 *  @return                     newly created MFC CString object.
 */
static CString stringFromVariant(const VARIANT FAR& v)
{
    switch (v.vt) {
    case VT_BYREF | VT_VARIANT:
        return stringFromVariant(*v.pvarVal);
    case VT_BSTR:
        return CString(v.bstrVal);
    case VT_BYREF | VT_BSTR:
        return CString(*v.pbstrVal);
    default:
        return "";
    }
}

/**
 * Parses a set of schema-controlled enumerated valid values for a data type.
 *
 *  @param  resp        reference to string containing CDR server response.
 *  @param  vvSet       container to be populated.
 */
static void extractValidValueSet(const CString& resp, 
                                 cdr::ValidValueSet& vvSet)
{
    cdr::Element enumSetElem = 
        cdr::Element::extractElement(resp, _T("EnumSet"));
    while (enumSetElem) {
        CString path = enumSetElem.getAttribute(_T("Node"));
        if (vvSet.find(path) == vvSet.end()) {
            cdr::StringList& vvList = vvSet[path] = cdr::StringList();
            CString eString = enumSetElem.getString();
            cdr::Element vvElement = 
                cdr::Element::extractElement(eString, _T("ValidValue"));
            while (vvElement) {
                vvList.push_back(vvElement.getString());
                vvElement = 
                    cdr::Element::extractElement(eString, _T("ValidValue"), 
                                                 vvElement.getEndPos());
            }
        }
        enumSetElem = cdr::Element::extractElement(resp, _T("EnumSet"), 
                                                   enumSetElem.getEndPos());
    }
}

static void messageLoop()
{
    MSG msg;
    while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
}

static bool syncDtd(const CString& dtd, const CString& docType)
{
    if (dtd.IsEmpty()) {
        ::AfxMessageBox(_T("Empty DTD for document type ") + docType,
                MB_ICONEXCLAMATION);
        return false;
    }

    // Find out where to write the DTD.
    CString dtdPath;
	CString rlxPath;
    CString rulesPath = cdr::getXmetalPath() + _T("\\Rules");
    dtdPath.Format(_T("%s\\%s.dtd"), (LPCTSTR)rulesPath, (LPCTSTR)docType);
    //rlxPath.Format(_T("%s\\%s.rlx"), (LPCTSTR)rulesPath, (LPCTSTR)docType);
    std::string pathName = cdr::cStringToUtf8(dtdPath);

#if 0
	// Remove the old RLX (XMetaL doesn't always do the right thing, and
	// sometimes fails to recognize that it has a DTD with a more recent
	// date than the RLX).
	DeleteFile(rlxPath);
	DeleteFile(dtdPath);
#endif

    // Write out the DTD.
    std::ofstream dtdStream(pathName.c_str());
    if (!dtdStream) {
        ::AfxMessageBox(_T("Unable to write DTD at ") + dtdPath,
                MB_ICONEXCLAMATION);
        return false;
    }
    dtdStream << cdr::cStringToUtf8(dtd).c_str();

#if 0
	// Compile the RLX file.
	CString cmpRlx = cdr::getXmetalPath() + _T("%s\\mkrls.exe");
	const char* cmdStr = cdr::cStringToUtf8(cmpRlx).c_str();
	const char* dtdStr = cdr::cStringToUtf8(dtdPath).c_str();
	wchar_t dir[_MAX_PATH];
	CString curDir = _wgetcwd(dir, _MAX_PATH);
	std::string dt = cdr::cStringToUtf8(docType);
	char cmd[1024];
	sprintf(cmd, "mkrls -a -c -x rules\\%s.dtd 2>>\\temp.o", dt.c_str());
	system(cmd);
	//::AfxMessageBox(L"current dir is " + curDir);
	//_spawnl(_P_WAIT, cmdStr, cmdStr, "-a", "-c", "-x", dtdStr, NULL);
	//cdrsystem(cdr::cStringToUtf8(cmpRlx).c_str());
#endif

    return true;
}

static void extractLinkingElements(const CString resp, cdr::StringSet& set)
{
    cdr::Element wrapperElem = cdr::Element::extractElement(resp,
            _T("LinkingElements"));
    if (wrapperElem) {
        CString elems = wrapperElem.getString();
        cdr::Element linkingElem = cdr::Element::extractElement(elems,
                _T("LinkingElement"));
        while (linkingElem) {
            CString elemName = linkingElem.getString();
            if (!elemName.IsEmpty())
                set.insert(elemName);
            linkingElem = cdr::Element::extractElement(elems,
                    _T("LinkingElement"), linkingElem.getEndPos());
        }
    }
}

static void getDocType(const CString docType, CLogonProgress& dialog)
{
    // Get the document type information from the CDR Server.
    CString cmd;
    cmd.Format(_T("<CdrGetDocType Type='%s' GetEnumValues='Y'/>"),
               (LPCTSTR)docType);
    CString resp = CdrSocket::sendCommand(cmd);

    // Check for problems.
    cdr::Element err = cdr::Element::extractElement(resp, _T("Err"));
    if (err) {
        ::AfxMessageBox(docType + _T(": ") + err.getString(), 
                MB_ICONEXCLAMATION);
        return;
    }

    // Don't bother with doc types which don't have a format of XML.
    cdr::Element respElem = 
        cdr::Element::extractElement(resp, _T("CdrGetDocTypeResp"));
    if (respElem.getAttribute(_T("Format")) != _T("xml"))
        return;

    // Keep the user from getting impatient.
    dialog.m_currentActivityText.SetWindowText(
        _T("Synchronizing information for document type ")
        + docType);

    // Remember this type for pull-down menus.
    docTypeStrings.push_back(docType);

    // Extract the valid value sets from the response.
    cdr::ValidValueSet vvSet;
    extractValidValueSet(resp, vvSet);
    validValueSets[docType] = vvSet;

    // Extract list of elements for which the server has vvlists.
    cdr::StringSet elemSet;
    extractLinkingElements(resp, elemSet);
    linkingElements[docType] = elemSet;

    // Synchronize the client's copy of the DTD.
    cdr::Element dtd = cdr::Element::extractElement(resp, _T("DocDtd"));
    if (dtd)
        syncDtd(dtd.getCdataSection(), docType);
    else
        ::AfxMessageBox(_T("Unable to find DTD for document type ") + docType,
                MB_ICONEXCLAMATION);
}

bool getCssFiles(LogonDialog& dialog, CLogonProgress& progressDialog)
{
    cdr::StringList files;
    _Application app = cdr::getApp();
    CString displayPath = cdr::getXmetalPath() + _T("\\Display");
    messageLoop();
    CString resp = CdrSocket::sendCommand(_T("<CdrGetCssFiles/>"));
    messageLoop();
    cdr::Element err = cdr::Element::extractElement(resp, _T("Err"));
    if (err) {
        ::AfxMessageBox(err.getString(), MB_ICONEXCLAMATION);
        return false;
    }
    cdr::Element file = cdr::Element::extractElement(resp, _T("File"));
    while (file) {
        messageLoop();
        files.push_back(file.getString());
        file = cdr::Element::extractElement(resp, _T("File"),
                                            file.getEndPos());
    }
    cdr::StringList::const_iterator iter = files.begin();
    while (iter != files.end()) {
        if (!dialog.keepGoing()) {
            app.SetStatusText(_T("Logon cancelled."));
            progressDialog.m_progressBar.SetPos(0);
            progressDialog.UpdateData(FALSE);
            return false;
        }
        messageLoop();
        CString s = *iter++;
        cdr::Element nameElem = cdr::Element::extractElement(s, _T("Name"));
        cdr::Element dataElem = cdr::Element::extractElement(s, _T("Data"));
        CString name = nameElem.getString();
        CString data = dataElem.getString();

        app.SetStatusText(_T("Retrieving CSS stylesheet ") + name);
        CString cssPath;
        cssPath.Format(_T("%s\\%s"), (LPCTSTR)displayPath, (LPCTSTR)name);
        std::string pathName = cdr::cStringToUtf8(cssPath);

        // Write out the stylesheet
        std::basic_ofstream<TCHAR> cssStream(pathName.c_str(),
                std::ios::binary);
        if (!cssStream) {
            ::AfxMessageBox(_T("Unable to write stylesheet at ") + cssPath,
                    MB_ICONEXCLAMATION);
            return false;
        }
        cssStream << (LPCTSTR)data;
    }
    app.SetStatusText(_T("Document type information loaded."));
    return true;
}

bool getDocTypes(LogonDialog& dialog, CLogonProgress& progressDialog)
{
    docTypeStrings.clear();
    validValueSets.clear();
    _Application app = cdr::getApp();
    messageLoop();
    CString resp = CdrSocket::sendCommand(_T("<CdrListDocTypes/>"));
    messageLoop();
    cdr::Element err = cdr::Element::extractElement(resp, _T("Err"));
    if (err) {
        ::AfxMessageBox(err.getString(), MB_ICONEXCLAMATION);
        return false;
    }
    docTypeStrings.push_back(_T("Any Type"));

    // Collect the list of doc type names so we'll know up front
    // how many there are.
    cdr::StringList tempList;
    cdr::Element docType = cdr::Element::extractElement(resp, _T("DocType"));
    while (docType) {
        messageLoop();
        CString name = docType.getString();
        if (!name.IsEmpty())
            tempList.push_back(docType.getString());
        docType = cdr::Element::extractElement(resp, _T("DocType"),
                                               docType.getEndPos());
    }
    size_t nameCount = tempList.size();
    size_t i = 0;

    // Loop through the list of names.
    cdr::StringList::const_iterator iter = tempList.begin();
    while (iter != tempList.end()) {
        if (!dialog.keepGoing()) {
            app.SetStatusText(_T("Logon cancelled."));
            progressDialog.m_progressBar.SetPos(0);
            progressDialog.UpdateData(FALSE);
            return false;
        }
        messageLoop();
        CString name = *iter++;
        app.SetStatusText(_T("Retrieving information for document type ")
                + name);
        getDocType(name, progressDialog);
        //dialog.m_progressBar.SetPos((100 * ++i) / nameCount);
        progressDialog.m_progressBar.SetPos((100 * ++i) / nameCount);
    }
    return true;
}

#if 0
static void getDocTypes()
{
    //CWaitCursor wc;
    CLogonProgress progressDialog;
    CWinThread* thread = AfxBeginThread(&syncInfoFromServer,
        &progressDialog);
    progressDialog.DoModal();
}

static cdr::ValidValueSet* getValidValueSet(const CString docType)
{
    CString cmd;
    cmd.Format(_T("<CdrGetDocType Type='%s' GetEnumValues='Y'/>"),
               (LPCTSTR)docType);
    CString resp = CdrSocket::sendCommand(cmd);
    cdr::Element err = cdr::Element::extractElement(resp, _T("Err"));
    if (err) {
        ::AfxMessageBox(err.getString(), MB_ICONEXCLAMATION);
        return 0;
    }
    return extractValidValueSet(resp);
}
#endif

static cdr::StringList* getSchemaValidValues(const CString docType,
                                             const CString path)
{
    if (validValueSets.find(docType) == validValueSets.end())
        return 0;
    cdr::ValidValueSet& vvSet = validValueSets[docType];
    if (vvSet.find(path) == vvSet.end())
        return 0;
    return &vvSet[path];
}

/////////////////////////////////////////////////////////////////////////////
// This method was generated by a MSVC++ wizard.

STDMETHODIMP CCommands::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICommands,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/**
 * Log on to the CDR.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::logon(int *pRet)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try {

        // Make sure the user isn't already logged on.
		if (CdrSocket::loggedOn()) {
			::AfxMessageBox(_T("This session is already logged into the CDR"),
							MB_ICONEXCLAMATION);
			*pRet = 1;
			return S_OK;
		}

        // Get the user's CDR credentials.
		LogonDialog logonDialog;
		int rc = logonDialog.DoModal();
		switch (rc) {
		case IDOK:
			//::AfxMessageBox(_T("CDR Logon Successful"));
            *pRet = 0;
            return S_OK;
		case IDCANCEL:
			*pRet = 2;
			return S_OK;
		case -1:
		default:
			::AfxMessageBox(_T("Internal failure"), MB_ICONEXCLAMATION);
			*pRet = 3;
			return S_OK;
		}
	}

    // Handle any extraordinary error conditions.
    catch (::CException &e) {
        e.ReportError();
        *pRet = 6;
    }
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."), 
			MB_ICONEXCLAMATION);
        *pRet = 6;
    }
    *pRet = 5;
    return S_OK;
}

/**
 * Retrieves the CDR document represented by the document ID obtained
 * from the user.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::retrieve(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try {

		// Working variables.
		CString err;
		RetrieveDialog retrieveDialog;

		// Make sure the user is logged on to the CDR.
		if (!CdrSocket::loggedOn())
			err = "This session is not logged into the CDR";

		// Ask the user which document to retrieve.
		if (err.IsEmpty()) {
			int rc = retrieveDialog.DoModal();
			switch (rc) {
			case IDOK:
				if (doRetrieve(retrieveDialog.m_DocId,
                               retrieveDialog.m_CheckOut))
					*pRet = 0;
				else
					*pRet = 2;
				break;
			case IDCANCEL:
				*pRet = 1;
				break;
			case -1:
			default:
				*pRet = 2;
				err = _T("Internal failure");
				break;
			}
		}

		// Give the user any bad news.
		if (!err.IsEmpty())
			::AfxMessageBox(err, MB_ICONEXCLAMATION);
	}
    catch (::CException &e) {
        e.ReportError();
        *pRet = 6;
    }
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."), MB_ICONEXCLAMATION);
        *pRet = 6;
    }
    return S_OK;
}

/**
 * Submits a search request (obtained from the user) to the CDR server
 * and allows the user to retrieve one of the documents found.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::search(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try {

		// Working variables.
		CString err;

		// Make sure the user is logged on to the CDR.
		if (!CdrSocket::loggedOn())
			err = "This session is not logged into the CDR";

		// Put up the dialog window.
		if (err.IsEmpty() && docTypeStrings.empty())
			getDocTypeStrings(err);
		if (err.IsEmpty()) {
			CSearchDialog searchDialog(docTypeStrings);

			*pRet = 0;
			while (err.IsEmpty()) {

                // All the heavy lifting is done in this call.
				int rc = searchDialog.DoModal();
				switch (rc) {
				case IDCANCEL:
					return S_OK;
				case -1:
				default:
					::AfxMessageBox(_T("Internal error"), MB_ICONEXCLAMATION);
					return S_OK;
				}
			}
		}
	}
    catch (::CException &e) {
        e.ReportError();
        *pRet = 6;
    }
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."), 
			MB_ICONEXCLAMATION);
        *pRet = 6;
    }

	return S_OK;
}

/**
 * Save the currently active document in the CDR repository.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::save(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pRet = 0;
	try {

        // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"), 
				MB_ICONEXCLAMATION);
            *pRet = 6;
            return S_OK;
        }

        // Get the currently active document.
        _Document doc = cdr::getApp().GetActiveDocument();
        if (!doc) {
            ::AfxMessageBox(_T("There is no active document."), 
				MB_ICONEXCLAMATION);
            *pRet = 3;
            return S_OK;
        }

        // Extract control information from the document.
		DOMNode docElement = doc.GetDocumentElement();
		CdrDocCtrlInfo ctrlInfo;
        cdr::extractCtlInfo(docElement, ctrlInfo);
		CString docTitle = ctrlInfo.docTitle;
        if (docTitle.IsEmpty())
            docTitle = _T("Server will replace this dummy title");

        // Ask the user for options to be used for the operation.
		CSaveDialog saveDialog(0);
		switch (saveDialog.DoModal()) {
		case IDOK:
		{
            CWaitCursor wc;

            // Build the save command.
        	std::basic_ostringstream<TCHAR> os;
            CString cmdTag = ctrlInfo.docId.IsEmpty() ? _T("CdrAddDoc")
                                                      : _T("CdrRepDoc");
			os << _T("<") << (LPCTSTR)cmdTag << _T("><CheckIn>")
			   << (saveDialog.m_checkIn ? _T("Y") : _T("N"))
			   << _T("</CheckIn>");
            if (saveDialog.m_createVersion)
                os << _T("<Version Publishable='")
                   << (saveDialog.m_versionPublishable ? _T("Y") : _T("N"))
                   << _T("'>Y</Version>");
            else
                os << _T("<Version>N</Version>");
            os << _T("<Validate>")
			   << (saveDialog.m_validate ? _T("Y") : _T("N"))
			   << _T("</Validate><Echo>Y</Echo>");
			if (!saveDialog.m_comment.IsEmpty())
				os << _T("<Reason>" )
                   << (LPCTSTR)cdr::encode(saveDialog.m_comment)
				   << _T("</Reason>");
			os << _T("<CdrDoc Type='") << (LPCTSTR)ctrlInfo.docType << _T("'");
            if (!ctrlInfo.docId.IsEmpty())
                os << _T(" Id='") << (LPCTSTR)ctrlInfo.docId << _T("'");
			os << _T("><CdrDocCtl>");
            if (!ctrlInfo.docId.IsEmpty())
                os << _T("<DocId>") << (LPCTSTR)ctrlInfo.docId 
                   << _T("</DocId>");
			os << _T("<DocType>") << (LPCTSTR)ctrlInfo.docType 
               << _T("</DocType>");
			os << _T("<DocTitle>") << (LPCTSTR)ctrlInfo.docTitle 
			   << _T("</DocTitle>");
            os << _T("<DocActiveStatus>")
               << (saveDialog.m_docInactive ? _T("I") : _T("A"))
               << _T("</DocActiveStatus><DocNeedsReview>")
			   << (saveDialog.m_readyForReview ? _T("Y") : _T("N"))
			   << _T("</DocNeedsReview>");
			if (!saveDialog.m_comment.IsEmpty())
				os << _T("<DocComment>" )
                   << (LPCTSTR)cdr::encode(saveDialog.m_comment)
				   << _T("</DocComment>");
            os << _T("</CdrDocCtl>");
			os << _T("<CdrDocXml><![CDATA[") << docElement 
			   << _T("]]></CdrDocXml>");
			os << _T("</CdrDoc></") << (LPCTSTR)cmdTag << _T(">");

            // Submit the save command to the server.
            CString rsp = CdrSocket::sendCommand(os.str().c_str());
            cdr::Element responseElem = 
                cdr::Element::extractElement(rsp, _T("CdrResponse"));
            CString status = responseElem.getAttribute(_T("Status"));
            if (status != _T("success"))
                *pRet = 2;

            if (rsp.Find(_T("<Error")) != -1) {
                cdr::showErrors(rsp);
            }
            else if (*pRet == 2)
                ::AfxMessageBox(_T("Failure without explanation"), 
					MB_ICONEXCLAMATION);
			if (!*pRet) {
				cdr::Element docId = 
					cdr::Element::extractElement(rsp, _T("DocId"));
				if (!docId) {
					::AfxMessageBox(_T("Unable to find document ID"), 
						MB_ICONEXCLAMATION);
				}
				else {
					doc.Close(2); // 2=don't save changes.
                    CString msg = _T("Document stored successfully.");
                    if (ctrlInfo.docId.IsEmpty())
                        msg += _T("\nIt is now checked out to you.\n")
                           _T("Please check in when processing is complete.");
                    ::AfxMessageBox(msg, MB_ICONINFORMATION);
                    if (!saveDialog.m_checkIn)
					    openDoc(rsp, docId.getString(), true);
                    else
                        removeDoc(docId.getString());
				}
			}
			break;
		}
		case IDCANCEL:
			*pRet = 1;
			break;
		}
	}
    catch (::COleDispatchException &ode) {
        CString msg;
        msg.Format(_T("Dispatch Exception; error code: %lu\n")
                   _T("From application: %s\n")
                   _T("Description: %s"), ode.m_wCode, ode.m_strSource, 
                                          ode.m_strDescription);
        ::AfxMessageBox(msg);
        *pRet = 6;
    }
    catch (::CException &e) {
        e.ReportError();
        *pRet = 6;
    }
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."), 
			MB_ICONEXCLAMATION);
        *pRet = 6;
    }
	return S_OK;
}

/**
 * Ask the CDR server to validate the currently active document.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::validate(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pRet = 0;
    
	try {

        // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"), 
				MB_ICONEXCLAMATION);
            *pRet = 6;
            return S_OK;
        }

        // Ask the user for options to be used during validation.
		CValidateDialog validateDialog;
		switch (validateDialog.DoModal()) {
		case IDOK:
		{
            CWaitCursor wc;

            // Find the currently active document.
            _Document doc = cdr::getApp().GetActiveDocument();

            // Extract the document's control information.
		    DOMNode docElement = doc.GetDocumentElement();
		    CdrDocCtrlInfo ctrlInfo;
            cdr::extractCtlInfo(docElement, ctrlInfo);
            CString docType = docElement.GetNodeName();

            // Build the validate command.
            std::basic_ostringstream<TCHAR> os;
            os << _T("<CdrValidateDoc DocType='") << (LPCTSTR)docType 
               << _T("' ValidationTypes='");

            // Dialog box ensures that at least one is true.
            LPCTSTR separator = _T("");
            if (validateDialog.m_schemaValidation) {
                os << _T("Schema");
                separator = _T(" ");
            }
            if (validateDialog.m_linkValidation)
                os << separator << _T("Links");
            os << _T("'><CdrDoc Type='") << (LPCTSTR)docType 
               << _T("'><CdrDocCtl>");
            if (!ctrlInfo.docId.IsEmpty())
                os << _T("<DocId>") << (LPCTSTR)ctrlInfo.docId 
                   << _T("</DocId>");
            os << _T("<DocTitle>") << (LPCTSTR)ctrlInfo.docTitle 
			   << _T("</DocTitle></CdrDocCtl><CdrDocXml><![CDATA[") 
			   << docElement 
			   << _T("]]></CdrDocXml></CdrDoc></CdrValidateDoc>");
            CString cmd = os.str().c_str();

            // Submit the validate command to the server.
            //::AfxMessageBox(cmd.c_str());
            CString rsp = CdrSocket::sendCommand(cmd);
            if (rsp.Find(_T("<Error")) != -1) {
                cdr::showErrors(rsp);
                *pRet = 1;
            }
            else {
				CPassedValidation dlg(ctrlInfo.docId);
				dlg.DoModal();
			}
            break;
        }
		case IDCANCEL:
			*pRet = 1;
			break;
		}
	}
    catch (::CException &e) {
        e.ReportError();
        *pRet = 2;
    }
	catch (...) { 
        ::AfxMessageBox(_T("Unexpected error from validation command."), 
			MB_ICONEXCLAMATION);
        *pRet = 2; 
    }
	return S_OK;
}

/**
 * Log out of the CDR server.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::logoff(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    // Initial optimism.
    username = _T("");
	*pRet = 0;

    try {

	    // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            //::AfxMessageBox(_T("This session is not logged into the CDR"));
            *pRet = 1;
            return S_OK;
        }

        // Submit the logoff request to the server.
        CString rsp = CdrSocket::sendCommand(_T("<CdrLogoff/>"));
#if 0
        if (rsp.Find(_T("<Error")) != -1) {
            cdr::showErrors(rsp);
            *pRet = 2;
        }
#endif
    }
    catch (...) {
        //::AfxMessageBox(_T("Unexpected error from logoff command."), 
		//	MB_ICONEXCLAMATION);
        *pRet = 3; 
    }

    // Clear the session string so we'll know that we're no longer logged in.
    CdrSocket::setSessionString("");
	return S_OK;
}

/**
 * Allows user to edit the current node, which represents a link to
 * another CDR document, or a value controlled by the schema for this document
 * type.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::edit(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    // Initial optimism.
	*pRet = 0;

    try {

	    // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"), 
				MB_ICONEXCLAMATION);
            *pRet = 1;
            return S_OK;
        }

        // Find the currently active document.
        _Document doc = cdr::getApp().GetActiveDocument();

        // Extract the control information from the document.
		DOMNode docElement = doc.GetDocumentElement();
		CdrDocCtrlInfo ctrlInfo;
        cdr::extractCtlInfo(docElement, ctrlInfo);
        CString docType = docElement.GetNodeName();

        // Find the element with the current focus.
        ::Selection selection = cdr::getApp().GetSelection();
        CString elemName = selection.GetContainerName();

        // XXX May move this into separate command; depends on what
        //     happens with the client requirements.
        const cdr::StringList* validValues = getSchemaValidValues(docType, 
                                                                  elemName);
        if (validValues) {
            //std::basic_ofstream<TCHAR> os("c:\\enum.lst");
            //if (os) {
            //    cdr::StringList::const_iterator i = validValues->begin();
            //    while (i != validValues->end())
            //        os << (LPCTSTR)*i++ << std::endl;
            //}
            //::AfxMessageBox(_T("Found valid values"));
            CSchemaPicklist schemaPicklist(validValues, _T(""), elemName);
            if (schemaPicklist.DoModal() != IDOK)
                *pRet = 2;
            return S_OK;
        }

        // Check for custom flavors of this command.
        CEditElement::Type editType = CEditElement::NORMAL;
        if (docType == _T("InScopeProtocol")) {
            if (elemName == _T("ProtocolLeadOrg"))
                editType = CEditElement::LEAD_ORG;
            else if (elemName == _T("LeadOrganizationID")) {
                if (selection.GetIsParentElement(_T("ProtocolLeadOrg")))
                    editType = CEditElement::LEAD_ORG;
            }
            else if (elemName == _T("Person"))
                editType = CEditElement::PROT_PERSON;
        }
        else if (docType == _T("Person")) {
            if (elemName  == _T("OrganizationLocation")) {
                if (selection.GetIsParentElement(_T("OtherPracticeLocation")))
                    editType = CEditElement::ORG_LOCATION;
            }
        }

        // Most of the real work is done inside this call.
        CEditElement editDialog(docType, elemName, editType);
        if (editDialog.DoModal() != IDOK)
            *pRet = 2;
    }
    catch (::CException &e) {
        e.ReportError();
        *pRet = 3;
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected error from edit command."), 
                        MB_ICONEXCLAMATION);
        *pRet = 3; 
    }
    return S_OK;
}

static int findFirst(const CString& str, LPCTSTR chars, int offset)
{
    int strLen = str.GetLength();
    int numChars = _tcslen(chars);
    while (offset < strLen) {
        TCHAR ch = str[offset];
        for (int i = 0; i < numChars; ++i) {
            if (ch == chars[i])
                return offset;
        }
    }
    return -1;
}

    
/**
 * Common public method which factors out the code to retrieve and
 * open a CDR document.
 *
 *  @param  id              reference to CDR document ID.
 *  @return                 <code>true</code> if document retrieved
 *                          successfully.
 */
bool CCommands::doRetrieve(const CString& id, 
                           BOOL checkOut)
{
    // Make sure the document isn't already open.
    _Application app = cdr::getApp();
    Documents docs = app.GetDocuments();
    unsigned int docNo = cdr::getDocNo(id);
    CString match;
    match.Format(_T("CDR%u "), docNo);
    int matchLen = match.GetLength();
    for (long i = docs.GetCount(); i > 0; --i) {
        COleVariant vi;
        vi = i;
        _Document doc = docs.item(&vi);
        if (doc.GetTitle().Left(matchLen) == match) {
            if (!doc.GetSaved()) {
                int rc = ::AfxMessageBox(_T("A modified copy of ") + match +
                    _T("is already open.\n") +
                    _T("Do you want to abandon the changes?"),
                    MB_YESNO);
                if (rc != IDYES)
                    return false;
            }
            doc.Close(2); // 2=Don't save changes.
        }
    }

    // Make canonical document ID.
    CString docId = cdr::docIdString(docNo);

    // Ask the server for the document.
    CString request;
    request.Format(_T("<CdrGetDoc>")
                   _T("<DocId>%s</DocId>")
                   _T("<Lock>%s</Lock>")
                   _T("<DocVersion>Current</DocVersion>")
                   _T("</CdrGetDoc>"), docId,
                                       (checkOut ? _T("Y") : _T("N")));
    CString response = CdrSocket::sendCommand(request);

    return openDoc(response, docId, checkOut);
}

void removeDoc(const CString& docId)
{
    unsigned int docNo = cdr::getDocNo(docId);
    CString cdrPath = cdr::getXmetalPath() + _T("\\Cdr");
    CString docPath;
    docPath.Format(_T("%s\\Checkout\\CDR%u.xml"), (LPCTSTR)cdrPath, docNo);
    try {
        CFile::Remove((LPCTSTR)docPath);
    }
    catch (CFileException&) { /* ignore */ }
}

bool openDoc(const CString& resp, const CString& docId, BOOL checkOut)
{
    // Extract the CdrDoc element.
    _Application app = cdr::getApp();
    Documents docs = app.GetDocuments();
    unsigned int docNo = cdr::getDocNo(docId);
    CString err;
    CString docType;
    CString docPath;
    CString retrievedDocTitle;
    CString cdrDoc;
    CString docTitle;
    CString cdrPath = cdr::getXmetalPath() + _T("\\Cdr");
    cdr::Element cdrDocElem = cdr::Element::extractElement(resp, 
                                                           _T("CdrDoc"));

    // Build up path string.
    docPath.Format(_T("%s\\%s\\CDR%u.xml"), 
                   (LPCTSTR)cdrPath, 
                   checkOut ? _T("Checkout") : _T("ReadOnly"),
                   docNo);

    if (!cdrDocElem) {

        cdr::Element errElem = cdr::Element::extractElement(resp, 
                                                            _T("Err"));
        if (errElem)
            err = errElem.getString();
        if (err.IsEmpty())
            err = _T("Unknown failure retrieving document from CDR");
    }
    else {

        cdrDoc  = cdrDocElem.getString();
        docType = cdrDocElem.getAttribute(_T("Type"));
        cdr::Element titleElem = cdr::Element::extractElement(cdrDoc,
                                                              _T("DocTitle"));
        if (titleElem) {
            docTitle = titleElem.getString();
            retrievedDocTitle.Format(_T("CDR%u%s - %s"), docNo,
                                     checkOut ? _T("") : _T(" [READ ONLY]"),
                                     (LPCTSTR)docTitle);
        }
    }

    // Extract the DocXml.
    CString docXml;
    if (err.IsEmpty() && docType.IsEmpty())
        err = _T("Missing Type attribute in CdrDoc element");
    else {
        cdr::Element xmlElem = cdr::Element::extractElement(cdrDoc,
                                                            _T("CdrDocXml"));
        if (xmlElem)
            docXml = xmlElem.getCdataSection();
    }

    // Write out the document.
    if (!docXml.IsEmpty()) {
        std::string pathName = cdr::cStringToUtf8(docPath);
        std::ofstream xmlStream(pathName.c_str());
        if (!xmlStream)
            err.Format(_T("Can't write xml document at %s"), (LPCTSTR)docPath);
        else {
            CString fixedDoc;
            CString ctl = _T("\n <CdrDocCtl>\n  <DocId>")
                            + docId
                            + _T("</DocId>\n  <DocTitle>")
                            + cdr::encode(docTitle, true)
                            + _T("</DocTitle>\n </CdrDocCtl>\n ");
            try {
                fixedDoc = fixDoc(docXml, ctl, docType, !checkOut);
            }
            catch (const CString& err) {
                ::AfxMessageBox(err, MB_ICONEXCLAMATION);
                return false;
            }
            xmlStream << "<?xml version='1.0' encoding='UTF-8'?>\n"
                      << cdr::cStringToUtf8(fixedDoc).c_str();
        }
    }

    // Show any bad news to the user.
    if (!err.IsEmpty()) {
        ::AfxMessageBox(err, MB_ICONEXCLAMATION);
        return false;
    }
    else {

        // Open the document and set its title bar string.
        try {
            _Document doc = docs.Open((LPCTSTR)docPath, 1);
            if (doc) {
                doc.SetTitle(retrievedDocTitle);
                return true;
            }
            return false;
        }
        catch (::COleDispatchException &ode) {
            CString msg;
            msg.Format(_T("Dispatch Exception; error code: %lu\n")
                       _T("From application: %s\n")
                       _T("Description: %s"), ode.m_wCode, ode.m_strSource, 
                                              ode.m_strDescription);
            ::AfxMessageBox(msg);
            return false;
        }
        catch (::CException &e) {
            e.ReportError();
            return false;
        }
        catch (...) {
            ::AfxMessageBox(_T("Unexpected exception encountered ")
                            _T("retrieving document"));
            return false;
        }
    }
}

/**
 * Populates the list of document type strings used to narrow a
 * user's CDR document search request.
 *
 *  @param  err         reference to string used to report any problems
 *                      encountered during population of the list.
 */
void getDocTypeStrings(CString& err)
{
    // Ask the user for the list of document types.
    CString response = CdrSocket::sendCommand(_T("<CdrListDocTypes/>"));
    if (response.IsEmpty())
        err = _T("Empty response from server");

    // Parse the type names from the server's response.
    if (err.IsEmpty()) {
        docTypeStrings.push_back(_T("Any Type"));
        int pos = 0;
        while ((pos = response.Find(_T("<DocType>"), pos)) != -1) {
            pos += 9;
            int endPos = response.Find(_T("</DocType>"), pos);
            if (endPos == -1 || endPos == pos) {
                err = _T("Malformed response for document type list");
                break;
            }

            // Add the document type to the list.
            CString typeName = response.Mid(pos, endPos - pos);
            docTypeStrings.push_back(typeName);
            pos = endPos + 10;
        }
    }
}

/**
 * Performs a few cleanup tasks needed to prepare the CDR document
 * for editing inside XMetaL.  This primarily involves the insertion
 * of the CdrDocCtl element.  In addition, a couple of temporary
 * steps are performed if they haven't already happened at data
 * conversion time (stripping out whitespace between elements and
 * adding the namespace declaration for the 'cdr' namespace).
 * XXX remove these extra steps after the next document conversion
 * run is performed.
 *
 *  @param  doc             reference to XML for document retrieved
 *                          from the CDR server.
 *  @param  ctl             reference to string containing CdrDocCtl
 *                          element to be inserted.
 *  @param  docType         string identifying document type.
 *  @param  readOnly        true if user is not checking the document out.
 *  @return                 reference to modified document string.
 */
CString& fixDoc(CString& doc, const CString& ctl,
                    const CString& docType, bool readOnly)
{
    // Skip leading whitespace.
    doc.TrimLeft();

    // Remove the XML declaration.
    int pos = doc.Find(_T("<?xml"));
    if (pos != -1) {
        int endPos = doc.Find(_T("?>"), pos);
        if (endPos > pos)
            doc.Delete(pos, (endPos - pos) + 2);
    }

    // Find the document element.
    CString startTag = _T("<") + docType;
    pos = doc.Find(startTag);
    if (pos == -1) {
        throw L"Unable to find document element " + docType;
    }

    // Insert the DOCTYPE declaration.
    CString dtd = _T("<!DOCTYPE ") + docType 
                + _T(" SYSTEM '") + docType 
                + _T(".dtd'>\n");

    // Insert the CdrDocCtl element.
    doc.Insert(pos, dtd);
    pos = doc.Find(_T(">"), pos + dtd.GetLength() + 1);
    if (pos == -1)
        return doc;
    int ctlPos    = pos + 1;
    int wsCount   = 0;
    int docLength = doc.GetLength();
    while (ctlPos + wsCount < docLength && iswspace(doc[ctlPos + wsCount]))
        wsCount++;
    if (wsCount)
        doc.Delete(ctlPos, wsCount);
    doc.Insert(ctlPos, ctl);

    // Add the 'cdr' namespace declaration if it's not already present.
    if (doc.Find(_T(" xmlns:cdr")) == -1) {
        CString nsDecl = _T(" xmlns:cdr='cips.nci.nih.gov/cdr'");
        doc.Insert(pos, nsDecl);
        pos += nsDecl.GetLength();
    }
    if (readOnly) {
        int roPos = doc.Find(_T("readonly="));
        if (roPos == -1 || roPos > pos)
            doc.Insert(pos, _T(" readonly='yes'"));
    }

    // Strip out whitespace between elements.
#if 0
    while ((pos = doc.find('>', pos)) != doc.npos) {
        ++pos;
        size_t n = 0;
        while (isspace(doc[pos + n]))
            ++n;
        if (n)
            doc.erase(pos, n);
    }
#endif
    return doc;
}

bool CCommands::doLogon(LogonDialog& logonDialog)
{
    // Create the logon command.
    CString request = _T("<CdrLogon><UserName>")
                    + logonDialog.m_UserId 
                    + _T("</UserName><Password>")
                    + logonDialog.m_Password
					+ _T("</Password></CdrLogon>");

    // Make the document directories if they aren't already there.
    CString cdrPath = cdr::getXmetalPath() + _T("\\Cdr");
    CString roPath  = cdrPath + _T("\\ReadOnly");
    CString coPath  = cdrPath + _T("\\Checkout");
    _wmkdir((LPCTSTR)cdrPath);
    _wmkdir((LPCTSTR)roPath);
    _wmkdir((LPCTSTR)coPath);

    // Submit the command to the CDR server.
    username = _T("");
	CString response = CdrSocket::sendCommand(request);
	if (!response.IsEmpty()) {
		TinyXmlParser p(response);
		CdrSocket::setSessionString(p.extract(_T("SessionId")));
		if (!CdrSocket::loggedOn()) {
			CString err = p.extract(_T("Err"));
			if (err.IsEmpty())
				err = _T("Unknown failure logging on to the CDR");
			::AfxMessageBox(err, MB_ICONEXCLAMATION);
			return false;
		}
        username = logonDialog.m_UserId;
        CLogonProgress progressDialog;
        progressDialog.Create(progressDialog.IDD /*, &logonDialog*/);
        //CRect dim;
        //dim.Height();
        //dim.Width();
        progressDialog.SetWindowPos(&CWnd::wndTop, 10, 10, 0, 0, SWP_NOSIZE);
        progressDialog.ShowWindow(SW_SHOW);
        bool gotDocTypes = getDocTypes(logonDialog, progressDialog);
        getCssFiles(logonDialog, progressDialog);
        progressDialog.DestroyWindow();
        return gotDocTypes;
    }
    return false;
}

/**
 * Parses document ID and denormalized value from string argument
 * and inserts the former as a cdr:ref attribute and the latter
 * as the text content of the current element.  Private support
 * method.
 *
 *  @param  info    string returned by server containing document
 *                  ID and denormalized value for a link target;
 *                  the format of this string is "[id] text-content".
 *  @return         <code>true</code> if link inserted successfully.
 */
bool CCommands::doInsertLink(const CString& info)
{
    bool inserted = false;
    CdrLinkInfo linkInfo = cdr::extractLinkInfo(info);
    if (linkInfo.target.IsEmpty())
        return inserted;

    // Find the source element for the link.
    ::Range selection = cdr::getApp().GetSelection();
    ::DOMElement elem = selection.GetContainerNode();
    //selection.SetReadOnlyContainer(FALSE);
    while (elem && elem.GetNodeType() != 1) // DOMElement
        elem = elem.GetParentNode();
    if (elem) {

        // Determine whether this is a cdr:ref or cdr:href link.
        ::_Document doc = cdr::getApp().GetActiveDocument();
        ::DOMDocumentType docType = doc.GetDoctype();
        CString attrName;
        if (docType.GetHasAttribute(elem.GetNodeName(), _T("cdr:ref")))
            attrName = _T("cdr:ref");
        else
            attrName = _T("cdr:href");

        // Plug in the link attribute.
        elem.setAttribute(attrName, linkInfo.target);

        // If this is a cdr:href link, that's all we need to do.
        if (attrName == _T("cdr:href"))
            return true;

        // Find the text node for the element.
        ::DOMText textNode = elem.GetFirstChild();

        /*
         * XXX Be very careful to do the node removal as done here!
         * There are a couple of nasty bugs in SoftQuad's API.  For one
         * thing, the following sequence should work, but it blows up:
         *
         *  if (piTarget == _T("xm-replace_text")) {
         *      textNode = textNode.GetNextSibling();
         *      elem.removeChild(pi);
         *      ...
         *
         * Also, note that in spite of what SoftQuad told us last
         * fall about the need to set the m_bAutoRelease member to
         * 0, this prevents the process from exiting when the
         * user closes down XMetaL if removeChild(pi) is called
         * and we have set pi.m_bAutoRelease to 0.
         *
         * Finally, note that we have a similar (but worse) problem
         * when we call appendChild().  The child never gets released
         * unless we explicitly call Release() on the object's
         * m_lpDispatch member.
         *
         * Reported to Yas at SoftQuad, September 2001 RMK.
         */
#if 0
        /* 
         * This code fragment should work, but an unhandled exception
         * gets thrown when removeChild is called.
         */
        while (textNode && textNode.GetNodeType() != 3) { // DOMText
            bool moved = false;
            if (textNode.GetNodeType() == 7) { // PI
                ::DOMProcessingInstruction pi(textNode);
                pi.m_bAutoRelease = 0;
                CString piTarget = pi.GetTarget();
                if (piTarget == _T("xm-replace_text")) {
                    textNode = textNode.GetNextSibling();
                    moved = true;
                ::AfxMessageBox(L"fo");
                    ::DOMNode dummy = elem.removeChild(pi); // <-- Blows up here.
                ::AfxMessageBox(L"fum");
                }
                ::AfxMessageBox(L"fo2");
            }
                ::AfxMessageBox(L"fo3");
            if (!moved)
                textNode = textNode.GetNextSibling();
        }
#else
        while (textNode && textNode.GetNodeType() != 3) { // DOMText
            ::DOMText nextNode = textNode.GetNextSibling();
            if (textNode.GetNodeType() == 7) { // PI
                ::DOMProcessingInstruction pi(textNode);
                pi.m_bAutoRelease = 0;
                if (pi.GetTarget() == _T("xm-replace_text"))
                    ::DOMNode dummy = elem.removeChild(pi);
                // else
                    /* If we do this in conjunction with removeChild(),
                     * then XMetaL never closes!  But if we don't do
                     * it here, then XMetaL blows up.
                     */
            }
            textNode = nextNode;
        }
#endif
        if (textNode)
            textNode.SetData(linkInfo.data);
        else {
            ::_Document curDoc = cdr::getApp().GetActiveDocument();
            textNode = curDoc.createTextNode(linkInfo.data);
            ::DOMNode dummy = elem.appendChild(textNode);

            // Without this line, XMetaL never shuts down!!!
            //textNode.m_lpDispatch->Release();
        }
        inserted = true;
    }

    // The user cannot edit the element directly.
    //selection.SetReadOnlyContainer(TRUE);
    return inserted;
}


STDMETHODIMP CCommands::isReadOnly(const BSTR *docType, 
                                   const BSTR *elemName, 
                                   BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// Initial assumption: the element is not read-only.
    *pVal = FALSE;
    CString dt(*docType);
    CString el(*elemName);
    cdr::StringList* vvList = getSchemaValidValues(dt, el);
    if (vvList && !vvList->empty())
        *pVal = TRUE;
    else if (isLinkingElement(dt, el))
        *pVal = TRUE;
    // Stopgap until readonly attributes are in place.
    else if (el == "DocId" || el == "DocType")
        *pVal = TRUE;
#if 0
    if (*pVal)
        ::AfxMessageBox(_T("doc type is ") + dt + 
                        _T(" and READONLY element name is ") + el);
#endif
    return S_OK;
}

STDMETHODIMP CCommands::advancedSearch(int *retVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
    *retVal = EXIT_FAILURE;

    COleDispatchDriver ie;
    if (!ie.CreateDispatch(_T("InternetExplorer.Application"))) {
        ::AfxMessageBox(_T("Unable to launch Internet Explorer"),
            MB_ICONEXCLAMATION);
        return S_OK;
    }
    CString url = _T("http://mmdb2.nci.nih.gov/cgi-bin/cdr/AdvancedSearch.py?")
        _T("Session=") + CdrSocket::getSessionString();
    DISPID dispid;
    OLECHAR* member = _T("Navigate");
    HRESULT hresult = ie.m_lpDispatch->GetIDsOfNames(IID_NULL, 
        &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
    if (hresult != S_OK) {
        ::AfxMessageBox(_T("Unable to launch Internet Explorer"),
            MB_ICONEXCLAMATION);
        return S_OK;
    }
    static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR 
                          VTS_PVARIANT VTS_PVARIANT;
    COleVariant dummy;
    ie.InvokeHelper(dispid, DISPATCH_METHOD, VT_EMPTY, NULL, parms, 
        url, 0L, _T("CdrAdvSearch"), &dummy, &dummy);
    *retVal = EXIT_SUCCESS;
	return S_OK;
}

STDMETHODIMP CCommands::get_username(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	username.SetSysString(pVal);

	return S_OK;
}

STDMETHODIMP CCommands::protUpdPerson(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    // Initial pessimism.
	*pRet = 1;

    try {

	    // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Find the currently active document.
        _Document doc = cdr::getApp().GetActiveDocument();

        // Extract the control information from the document.
		DOMNode docElement = doc.GetDocumentElement();
		CdrDocCtrlInfo ctrlInfo;
        cdr::extractCtlInfo(docElement, ctrlInfo);
        CString docType = docElement.GetNodeName();

        // Find the element with the current focus.
        ::Selection selection = cdr::getApp().GetSelection();
        CString elemName = selection.GetContainerName();

        // Make sure the command is appropriate here.
        if (docType != _T("InScopeProtocol")) {
            ::AfxMessageBox(_T("This command is intended for ")
                            _T("InScopeProtocol documents"), 
							MB_ICONEXCLAMATION);
            return S_OK;
        }
        else if (elemName != _T("Person")) {
            ::AfxMessageBox(_T("Current element is not Person"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Find the document ID for the lead organization.
        ::Range leadOrgLoc = cdr::getElemRange(_T("ProtocolLeadOrg"));
        if (!leadOrgLoc) {
            ::AfxMessageBox(_T("Unable to find ProtocolLeadOrg"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMElement leadOrgElem = leadOrgLoc.GetContainerNode();
        if (!leadOrgElem || leadOrgElem.GetNodeName() != _T("ProtocolLeadOrg"))
        {
            ::AfxMessageBox(_T("Unable to find ProtocolLeadOrg element"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMNodeList nodeList = 
            leadOrgElem.getElementsByTagName(_T("LeadOrganizationID"));
        if (nodeList.GetLength() < 1) {
            ::AfxMessageBox(_T("Unable to find LeadOrganization ID element"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMElement leadOrgIdElem = nodeList.item(0);
        CString leadOrgId = leadOrgIdElem.getAttribute(_T("cdr:ref"));
        if (leadOrgId.IsEmpty()) {
            ::AfxMessageBox(_T("Missing or empty cdr:ref attribute ")
                            _T("for lead organization ID"), 
							MB_ICONEXCLAMATION);

            return S_OK;
        }

        // Most of the real work is done inside this call.
        CProtUpdPerson pupDialog(leadOrgId);
		pupDialog.DoModal();
    }
    catch (::CException &e) {
        e.ReportError();
        *pRet = 2;
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected error from ")
                        _T("Protocol Update Person command."), 
						MB_ICONEXCLAMATION);
        *pRet = 2; 
    }
    *pRet = 0;
	return S_OK;
}

STDMETHODIMP CCommands::getPersonAddress(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    // Initial pessimism.
	*pRet = 1;

    try {

	    // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Find the LeadOrgPersonnel element location.
        ::Range lopLoc = cdr::getElemRange(_T("LeadOrgPersonnel"));
        if (!lopLoc) {
            ::AfxMessageBox(_T("ProtocolLeadPersonnel for ")
                            _T("current location not found"), 
							MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Find the adddress fragment link.
        ::DOMElement lopElem = lopLoc.GetContainerNode();
        if (!lopElem || lopElem.GetNodeName() != _T("LeadOrgPersonnel"))
        {
            ::AfxMessageBox(_T("Unable to find LeadOrgPersonnel element"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMNodeList nodeList = 
            lopElem.getElementsByTagName(_T("Person"));
        if (nodeList.GetLength() < 1) {
            ::AfxMessageBox(_T("Unable to find Person element"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMElement personElem = nodeList.item(0);
        CString addrLink = personElem.getAttribute(_T("cdr:ref"));
        if (addrLink.IsEmpty()) {
            ::AfxMessageBox(_T("Missing or empty cdr:ref attribute ")
                            _T("for address link"), 
							MB_ICONEXCLAMATION);

            return S_OK;
        }

        // Ask the server for the full address.
        std::basic_ostringstream<TCHAR> cmd;
        cmd << _T("<CdrReport><ReportName>Person Address Fragment")
               _T("</ReportName><ReportParams><ReportParam Name='Link'")
               _T(" Value='")
            << (LPCTSTR)addrLink
            << _T("'/></ReportParams></CdrReport>");

        // Submit the request to the CDR server.
        CWaitCursor wc;
        CString rsp = CdrSocket::sendCommand(cmd.str().c_str());

        // Extract the address elements.
        cdr::Element repBody = 
            cdr::Element::extractElement(rsp, _T("ReportBody"));
        if (!repBody) {
            if (!cdr::showErrors(rsp))
                ::AfxMessageBox(_T("Unknown failure from search"),
                                MB_ICONEXCLAMATION);
            return S_OK;
        }
        CString addrStr = repBody.getCdataSection();

        // Find the proper location for the address.
        ::Range pscLoc = cdr::findOrCreateChild(lopLoc, 
            _T("ProtocolSpecificContact"));
        if (!pscLoc) {
            ::AfxMessageBox(_T("Failure creating ProtocolSpecificContact ")
                            _T("element"), 
							MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Plug in our own data.
        pscLoc.SelectElement();
        pscLoc.Select();
        CString pscData = _T("<ProtocolSpecificContact>") + addrStr +
                          _T("</ProtocolSpecificContact>");
        //::AfxMessageBox(pscData);
        if (!pscLoc.GetCanPaste(pscData, FALSE))
            ::AfxMessageBox(_T("Unable to insert ") + pscData, 
				MB_ICONEXCLAMATION);
        else
            pscLoc.PasteString(pscData);

    }
    catch (::CException &e) {
        e.ReportError();
        *pRet = 2;
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected error retrieving ")
                        _T("contact address information"), 
						MB_ICONEXCLAMATION);
        *pRet = 2; 
    }
    *pRet = 0;
	return S_OK;
}

STDMETHODIMP CCommands::particOrgs(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    // Initial pessimism.
	*pRet = 1;

    try {

	    // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Find the currently active document.
        _Document doc = cdr::getApp().GetActiveDocument();

        // Extract the control information from the document.
		DOMNode docElement = doc.GetDocumentElement();
		CdrDocCtrlInfo ctrlInfo;
        cdr::extractCtlInfo(docElement, ctrlInfo);
        CString docType = docElement.GetNodeName();

        // Make sure the command is appropriate here.
        if (docType != _T("InScopeProtocol")) {
            ::AfxMessageBox(_T("This command is intended for ")
                            _T("InScopeProtocol documents"), 
							MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Find the document ID for the lead organization.
        ::Range leadOrgLoc = cdr::getElemRange(_T("ProtocolLeadOrg"));
        if (!leadOrgLoc) {
            ::AfxMessageBox(_T("Unable to find ProtocolLeadOrg"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMElement leadOrgElem = leadOrgLoc.GetContainerNode();
        if (!leadOrgElem || leadOrgElem.GetNodeName() != _T("ProtocolLeadOrg"))
        {
            ::AfxMessageBox(_T("Unable to find ProtocolLeadOrg element"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMNodeList nodeList = 
            leadOrgElem.getElementsByTagName(_T("LeadOrganizationID"));
        if (nodeList.GetLength() < 1) {
            ::AfxMessageBox(_T("Unable to find LeadOrganization ID element"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMElement leadOrgIdElem = nodeList.item(0);
        CString leadOrgId = leadOrgIdElem.getAttribute(_T("cdr:ref"));
        if (leadOrgId.IsEmpty()) {
            ::AfxMessageBox(_T("Missing or empty cdr:ref attribute ")
                            _T("for lead organization ID"), 
							MB_ICONEXCLAMATION);

            return S_OK;
        }

        // Most of the real work is done inside this call.
        CParticOrgs poDialog(leadOrgId);
		poDialog.DoModal();
    }
    catch (::CException &e) {
        e.ReportError();
        *pRet = 2;
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected error from ")
                        _T("Participating Orgs command."), 
						MB_ICONEXCLAMATION);
        *pRet = 2; 
    }
    *pRet = 0;

	return S_OK;
}

STDMETHODIMP CCommands::getOrgAddress(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

    // Initial pessimism.
	*pRet = 1;

    try {

	    // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Find the LeadOrgPersonnel element location.
        ::Range oplLoc = cdr::getElemRange(_T("OtherPracticeLocation"));
        if (!oplLoc) {
            ::AfxMessageBox(_T("OtherPracticeLocation for ")
                            _T("current location not found"), 
							MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Find the adddress fragment link.
        ::DOMElement oplElem = oplLoc.GetContainerNode();
        if (!oplElem || oplElem.GetNodeName() != _T("OtherPracticeLocation"))
        {
            ::AfxMessageBox(_T("Unable to find OtherPracticeLocation ")
                            _T("element"), 
							MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMNodeList nodeList = 
            oplElem.getElementsByTagName(_T("OrganizationLocation"));
        if (nodeList.GetLength() < 1) {
            ::AfxMessageBox(_T("Unable to find OrganizationLocation element"),
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        ::DOMElement orgLocElem = nodeList.item(0);
        CString addrLink = orgLocElem.getAttribute(_T("cdr:ref"));
        if (addrLink.IsEmpty()) {
            ::AfxMessageBox(_T("Missing or empty cdr:ref attribute ")
                            _T("for address link"), MB_ICONEXCLAMATION);

            return S_OK;
        }

        // Break the link into its two parts.
        int delimPos = addrLink.Find(_T("#"));
        if (delimPos < 1 || delimPos == addrLink.GetLength() - 1) {
            ::AfxMessageBox(_T("Malformed fragment link: ") + addrLink, 
				MB_ICONEXCLAMATION);
            return S_OK;
        }
        CString docId = addrLink.Left(delimPos);
        CString fragId = addrLink.Mid(delimPos + 1);

      // Ask the server for the full address.
        std::basic_ostringstream<TCHAR> cmd;
        cmd << _T("<CdrFilter><Filter Name='Organization Address Fragment'/>")
               _T("<Parms><Parm><Name>fragId</Name><Value>")
            << (LPCTSTR)fragId
            << _T("</Value></Parm></Parms><Document href='")
            << (LPCTSTR)docId
            << _T("'/></CdrFilter>");

        // Submit the request to the CDR server.
        CWaitCursor wc;
        CString cmdString = cmd.str().c_str();
        //::AfxMessageBox(cmdString);
        CString rsp = CdrSocket::sendCommand(cmdString);
        //::AfxMessageBox(rsp);

        // Extract the address elements.
        cdr::Element addressElements = 
            cdr::Element::extractElement(rsp, _T("AddressElements"));
        if (!addressElements) {
            if (!cdr::showErrors(rsp))
                ::AfxMessageBox(_T("Unknown failure from search"),
                                MB_ICONEXCLAMATION);
            return S_OK;
        }
        CString addrStr = addressElements.getString();
        cdr::Element postalAddressElement =
            cdr::Element::extractElement(addrStr, _T("PostalAddress"));
        if (!postalAddressElement) {
            if (!cdr::showErrors(rsp))
                ::AfxMessageBox(_T("Unable to find PostalAddress element"),
                                MB_ICONEXCLAMATION);
            return S_OK;
        }
        CString paStr = postalAddressElement.getString();

        // Find the proper location for the address.
        ::Range spaLoc = cdr::findOrCreateChild(oplLoc, 
                                                _T("SpecificPostalAddress"));
        if (!spaLoc) {
            ::AfxMessageBox(_T("Failure creating ")
                            _T("SpecificPostalAddress element"),
				            MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Plug in our own data.
        spaLoc.SelectElement();
        spaLoc.Select();
        CString spaData = _T("<SpecificPostalAddress>") + paStr +
                          _T("</SpecificPostalAddress>");
        //::AfxMessageBox(pscData);
        if (!spaLoc.GetCanPaste(spaData, FALSE))
            ::AfxMessageBox(_T("Unable to insert ") + spaData,
                    MB_ICONEXCLAMATION);
        else
            spaLoc.PasteString(spaData);

    }
    catch (::CException &e) {
        e.ReportError();
        *pRet = 2;
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected error retrieving ")
                        _T("contact address information"), 
						MB_ICONEXCLAMATION);
        *pRet = 2; 
    }
    *pRet = 0;

	return S_OK;
}

STDMETHODIMP CCommands::pasteDocLink(const BSTR* link, int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pRet = 1;
    CString docLink(*link);

	// Make sure the user is logged on to the CDR.
    if (!CdrSocket::loggedOn()) {
        ::AfxMessageBox(_T("This session is not logged into the CDR"), 
			MB_ICONEXCLAMATION);
        return S_OK;
    }

    // Find the currently active document.
    _Document doc = cdr::getApp().GetActiveDocument();

    // Get the current element and the doc type.
    DOMNode docElement = doc.GetDocumentElement();
    CString docType = docElement.GetNodeName();
    ::Range selection = cdr::getApp().GetSelection();
    ::DOMElement elem = selection.GetContainerNode();
    CString elemName  = elem.GetNodeName();
    while (elem && elem.GetNodeType() != 1) // DOMElement
        elem = elem.GetParentNode(); 
    if (elem) {
        try {

            // Ask the server for the denormalized data.
            CString cmd = _T("<CdrPasteLink><SourceDocType>")
                        + docType
                        + _T("</SourceDocType><SourceElementType>")
                        + elemName
                        + _T("</SourceElementType><TargetDocId>")
                        + docLink
                        + _T("</TargetDocId></CdrPasteLink>");
            CWaitCursor wc;
            CString rsp = CdrSocket::sendCommand(cmd);
            if (rsp.Find(_T("<Error")) != -1) {
                cdr::showErrors(rsp);
                return S_OK;
            }
            cdr::Element denormDataElem = 
                cdr::Element::extractElement(rsp, _T("DenormalizedContent"));
            if (!denormDataElem) {
                ::AfxMessageBox(_T("Server did not return denormalized ")
                                _T("content"), 
								MB_ICONEXCLAMATION);
                return S_OK;
            }
            CString denormData = denormDataElem.getString();
            if (denormData.IsEmpty()) {
                ::AfxMessageBox(_T("Denormalized data empty"), 
					MB_ICONEXCLAMATION);
                return S_OK;
            }

            // Plug in the link attribute.
            elem.setAttribute(_T("cdr:ref"), docLink);

            // Clear out the existing children.
            ::DOMNode child = elem.GetFirstChild();
            while (child) {
                ::DOMNode nextChild = child.GetNextSibling();
                ::DOMNode dummy = elem.removeChild(child);
                child = nextChild;
            }

            // Pop in the new content.
            ::DOMText textNode = doc.createTextNode(denormData);
            ::DOMNode dummy = elem.appendChild(textNode);
        }
        catch (::CException &e) {
            e.ReportError();
            *pRet = 2;
        }
        catch (...) {
            ::AfxMessageBox(_T("Unexpected error pasting doc link"), 
				MB_ICONEXCLAMATION);
            *pRet = 2; 
        }

#if 0 // Save this for pasteFragLink!

        // Break the link into its two parts.
        int delimPos = addrLink.Find(_T("#"));
        if (delimPos < 1 || delimPos == addrLink.GetLength() - 1) {
            ::AfxMessageBox(_T("Malformed fragment link: ") + addrLink);
            return S_OK;
        }
        CString docId = addrLink.Left(delimPos);
        CString fragId = addrLink.Mid(delimPos + 1);

#endif

#if 0 // Save this for pasting in multiple elements!
        // Plug in our own data.
        scLoc.SelectElement();
        scLoc.Select();
        CString scData = _T("<SpecificContact>") + addrStr +
                         _T("</SpecificContact>");
        //::AfxMessageBox(pscData);
        if (!scLoc.GetCanPaste(scData, FALSE))
            ::AfxMessageBox(_T("Unable to insert ") + scData,
                    MB_ICONEXCLAMATION);
        else
            scLoc.PasteString(scData);
#endif
    }
    *pRet = 0;

    return S_OK;
}

STDMETHODIMP CCommands::get_session(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CString session = CdrSocket::getSessionString();
	session.SetSysString(pVal);

	return S_OK;
}

STDMETHODIMP CCommands::checkIn(int *pRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pRet = 1;
	try {

        // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Get the currently active document.
        _Document doc = cdr::getApp().GetActiveDocument();
        if (!doc) {
            ::AfxMessageBox(_T("There is no active document."), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Extract control information from the document.
		DOMNode docElement = doc.GetDocumentElement();
		CdrDocCtrlInfo ctrlInfo;
        cdr::extractCtlInfo(docElement, ctrlInfo);
        if (ctrlInfo.docId.IsEmpty()) {
            ::AfxMessageBox(_T("Document has never been stored in the CDR."), 
				MB_ICONEXCLAMATION);
            return S_OK;
        }

        // Ask the user for confirmation.
		CCheckIn checkIn;
		switch (checkIn.DoModal()) {
		case IDOK:
		{
            CWaitCursor wc;

            // Build the check-in command.
        	std::basic_ostringstream<TCHAR> os;
			os << _T("<CdrCheckIn Abandon='Y' ForceCheckIn='Y'><DocumentId>")
			   << (LPCTSTR)ctrlInfo.docId
			   << _T("</DocumentId>");
			if (!checkIn.m_comment.IsEmpty())
				os << _T("<Comment>") 
				   << (LPCTSTR)checkIn.m_comment << 
				   _T("</Comment>");
			os << _T("</CdrCheckIn>");

            // Submit the check-in command to the server.
            CString rsp = CdrSocket::sendCommand(os.str().c_str());
            cdr::Element responseElem = 
                cdr::Element::extractElement(rsp, _T("CdrResponse"));
            CString status = responseElem.getAttribute(_T("Status"));
            if (status == _T("success"))
                *pRet = 0;

            if (rsp.Find(_T("<Error")) != -1) {
                cdr::showErrors(rsp);
            }
            else if (*pRet)
                ::AfxMessageBox(_T("Failure without explanation"), 
					MB_ICONEXCLAMATION);
			else {
				doc.Close(2); // 2=don't save changes.
                removeDoc(ctrlInfo.docId);
            }

				//doRetrieve(ctrlInfo.docId, FALSE, _T(""));
			break;
		}
		case IDCANCEL:
			break;
		}
	}
    catch (::CException &e) {
        e.ReportError();
    }
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."), 
			MB_ICONEXCLAMATION);
    }

	return S_OK;
}
