/*
 * $Id: Commands.cpp,v 1.4 2001-06-11 18:27:18 bkline Exp $
 *
 * Implementation of CCdrApp and DLL registration.
 *
 * To do: rationalize error return codes for automation commands.
 *
 * $Log: not supported by cvs2svn $
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
#include "resource.h"

// System headers
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

// Prevent annoying warning from compiler about Microsoft's own bugs.
#pragma warning(disable : 4503)

// Local functions.
static void     getDocTypeStrings(CString& err);
static void     messageLoop();
static CString& fixDoc(CString& doc, const CString& ctl, 
                       const CString& docType);

// Local data.
static cdr::StringList      docTypeStrings;
static cdr::ValidValueSets  validValueSets;
static cdr::ElementSets     linkingElements;

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
    CString rulesPath = cdr::getXmetalPath() + _T("\\Rules");
    dtdPath.Format(_T("%s\\%s.dtd"), (LPCTSTR)rulesPath, (LPCTSTR)docType);
    std::string pathName = cdr::cStringToUtf8(dtdPath);

    // Write out the DTD.
    std::ofstream dtdStream(pathName.c_str());
    if (!dtdStream) {
        ::AfxMessageBox(_T("Unable to write DTD at ") + dtdPath,
                MB_ICONEXCLAMATION);
        return false;
    }
    dtdStream << cdr::cStringToUtf8(dtd).c_str();
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
    app.SetStatusText(_T("Document type information loaded."));
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
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."));
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
                               retrieveDialog.m_CheckOut,
                               retrieveDialog.m_Version))
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
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."));
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
					::AfxMessageBox(_T("Internal error"));
					return S_OK;
				}
			}
		}
	}
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."));
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
            ::AfxMessageBox(_T("This session is not logged into the CDR"));
            *pRet = 6;
            return S_OK;
        }

        // Get the currently active document.
        _Document doc = cdr::getApp().GetActiveDocument();
        if (!doc) {
            ::AfxMessageBox(_T("There is no active document."));
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
			   << _T("</Validate>")
               << _T("<DocActiveStatus>")
               << (saveDialog.m_docInactive ? _T("I") : _T("A"))
               << _T("</DocActiveStatus>");
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
			   << _T("</DocTitle></CdrDocCtl>");
			os << _T("<CdrDocXml><![CDATA[") << docElement 
			   << _T("]]></CdrDocXml>");
			os << _T("</CdrDoc></") << (LPCTSTR)cmdTag << _T(">");

            // Submit the save command to the server.
            CString rsp = CdrSocket::sendCommand(os.str().c_str());
            if (rsp.Find(_T("<Error")) != -1) {
                cdr::showErrors(rsp);
                *pRet = 2;
            }
			break;
		}
		case IDCANCEL:
			*pRet = 1;
			break;
		}
	}
	catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."));
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
            ::AfxMessageBox(_T("This session is not logged into the CDR"));
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
            else
                ::AfxMessageBox(_T("Document passes validation."));
            break;
        }
		case IDCANCEL:
			*pRet = 1;
			break;
		}
	}
	catch (...) { 
        ::AfxMessageBox(_T("Unexpected error from validation command."));
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
	*pRet = 0;

    try {

	    // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"));
            *pRet = 1;
            return S_OK;
        }

        // Submit the logoff request to the server.
        CString rsp = CdrSocket::sendCommand(_T("<CdrLogoff/>"));
        if (rsp.Find(_T("<Error")) != -1) {
            cdr::showErrors(rsp);
            *pRet = 2;
        }
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected error from logoff command."));
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
            ::AfxMessageBox(_T("This session is not logged into the CDR"));
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
            std::basic_ofstream<TCHAR> os("c:\\enum.lst");
            if (os) {
                cdr::StringList::const_iterator i = validValues->begin();
                while (i != validValues->end())
                    os << (LPCTSTR)*i++ << std::endl;
            }
            //::AfxMessageBox(_T("Found valid values"));
            CSchemaPicklist schemaPicklist(validValues, _T(""), elemName);
            schemaPicklist.DoModal();
            return S_OK;
        }

        // Most of the real work is done inside this call.
        CEditElement editDialog(docType, elemName);
		editDialog.DoModal();
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected error from edit command."));
        *pRet = 2; 
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
                           BOOL checkOut, 
                           const CString& version)
{
    // Working variables.
    unsigned int docNo = cdr::getDocNo(id);
	CString err;
    CString docPath;
    CString docId;
    CString retrievedDocTitle;
    CString cdrDoc;
	CString docTitle;
    CString cdrPath = cdr::getXmetalPath() + _T("\\Cdr");

    // Build up path strings.
    docPath.Format(_T("%s\\CDR%u.xml"), (LPCTSTR)cdrPath, docNo);
    docId.Format(_T("CDR%010u"), docNo);

    // Ask the server for the document.
    CString request;
    request.Format(_T("<CdrGetDoc>")
                   _T("<DocId>%s</DocId>")
                   _T("<Lock>%s</Lock>")
                   _T("<DocVersion>%s</DocVersion>")
                   _T("</CdrGetDoc>"), docId,
                                       (checkOut ? _T("Y") : _T("N")),
                                       version);
	CString response = CdrSocket::sendCommand(request);

    // Extract the CdrDoc element.
    CString docType;
    cdr::Element cdrDocElem = cdr::Element::extractElement(response, 
                                                           _T("CdrDoc"));
    if (!cdrDocElem) {

        cdr::Element errElem = cdr::Element::extractElement(response, 
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
            retrievedDocTitle.Format(_T("%s (CDR%u)"), 
					                 (LPCTSTR)docTitle, docNo);
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
            CString ctl = _T("\n  <CdrDocCtl>\n    <DocId>")
                            + docId
                            + _T("</DocId>\n    <DocTitle>")
                            + cdr::encode(docTitle, true)
                            + _T("</DocTitle>\n  </CdrDocCtl>\n");
            CString fixedDoc = fixDoc(docXml, ctl, docType);
            xmlStream << cdr::cStringToUtf8(fixedDoc).c_str();
        }
    }

    // Show any bad news to the user.
    if (!err.IsEmpty()) {
        ::AfxMessageBox(err, MB_ICONEXCLAMATION);
        return false;
	}
	else {

        // Open the document and set its title bar string.
        _Application app = cdr::getApp();
        Documents docs = app.GetDocuments();
        _Document doc = docs.Open((LPCTSTR)docPath, 1);
        if (doc) {
            doc.SetTitle(retrievedDocTitle);
            return true;
        }
        return false;
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
 *  @return                 reference to modified document string.
 */
CString& fixDoc(CString& doc, const CString& ctl,
                    const CString& docType)
{
	// Skip leading whitespace.
    doc.TrimLeft();

    // Find the document element.
    CString startTag = _T("<") + docType;
	int pos = doc.Find(startTag);
	if (pos == -1)
		return doc;

    // Insert the DOCTYPE declaration.
    CString dtd = _T("<!DOCTYPE ") + docType 
                    + _T(" SYSTEM '") + docType 
                    + _T(".dtd'>\n");

    // Insert the CdrDocCtl element.
    doc.Insert(pos, dtd);
    pos = doc.Find(_T(">"), pos + dtd.GetLength() + 1);
	if (pos == -1)
		return doc;
    doc.Insert(pos + 1, ctl);

    // Add the 'cdr' namespace declaration if it's not already present.
	if (doc.Find(_T(" xmlns:cdr")) == -1)
		doc.Insert(pos, _T(" xmlns:cdr='cdr:cips.nci.nih.gov'"));

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

    // Submit the command to the CDR server.
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
        CLogonProgress progressDialog;
        progressDialog.Create(progressDialog.IDD /*, &logonDialog*/);
        //CRect dim;
        //dim.Height();
        //dim.Width();
        progressDialog.SetWindowPos(&CWnd::wndTop, 10, 10, 0, 0, SWP_NOSIZE);
        progressDialog.ShowWindow(SW_SHOW);
        bool gotDocTypes = getDocTypes(logonDialog, progressDialog);
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
    // Parse out the document ID and text content.
    int pos = info.Find(_T("["));
    if (pos == -1) {
        ::AfxMessageBox(_T("Unable to find document ID start delimiter."));
        return false;
    }
    int endPos = info.Find(_T("]"), ++pos);
    if (endPos == -1) {
        ::AfxMessageBox(_T("Unable to find document ID end delimiter."));
        return false;
    }
    CString targetDocId = info.Mid(pos, endPos - pos);
    pos = endPos + 1;
    while (pos < info.GetLength() && info[pos] == _T(' '))
        ++pos;
    CString targetDocTitle = info.Mid(pos);

    // Find the source element for the link.
    ::Selection selection = cdr::getApp().GetSelection();
    selection.SetReadOnlyContainer(FALSE);
    ::DOMNode node = selection.GetContainerNode();
    while (node && node.GetNodeType() != 1) // DOMElement
        node = node.GetParentNode();
    if (node) {

        // This is the MS Automation equivalent of 'casting'.  It is
        // necessary to turn off the auto-release flag for the second
        // object to prevent too many invocations of IUnknown::Release().
        ::DOMElement elem(node);
        elem.m_bAutoRelease = 0;

        // Plug in the link attribute.
        elem.setAttribute(_T("cdr:ref"), targetDocId);

        // Find the text node for the element.
        ::DOMNode child = node.GetFirstChild();
        while (child && child.GetNodeType() != 3) // DOMText
            child = child.GetNextSibling();
        if (child) {

            // See note above about "casting".
            ::DOMText textNode(child);
            textNode.m_bAutoRelease = 0;

            // Replace the text node with the linked document's title.
            long len = textNode.GetLength();
            //const char* pTitle = targetDocTitle.c_str();
            textNode.replaceData(0, len, targetDocTitle);
        }
    }

    // The user cannot edit the element directly.
    selection.SetReadOnlyContainer(TRUE);
    return true;
}

#if 0
STDMETHODIMP CCommands::xisReadOnly(BOOL *pRet, 
                                    VARIANT docType, 
                                    VARIANT elemName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())


	return S_OK;
}
#endif

STDMETHODIMP CCommands::isReadOnly(BOOL *pRet, 
                                   const VARIANT& docType, 
                                   const VARIANT& elemName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// Initial assumption: the element is not read-only.
    CString dt = stringFromVariant(docType);
    CString el = stringFromVariant(elemName);
    ::AfxMessageBox(_T("doc type is ") + dt + _T(" and element name is ") + el);
    *pRet = FALSE;

	return S_OK;
}
