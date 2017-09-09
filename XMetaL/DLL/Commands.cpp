/*
 * Implementation of CCdrApp and DLL registration.
 *
 * To do: rationalize error return codes for automation commands.
 *
 * BZIssue::4767
 * BZIssue::5172 - Add support for pasting fragment ref into Target attribute.
 * JIRA::OCECDR-3732 - custom support for genetics syndrome picklist
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
#include "Glossify.h"
#include "ReviewMarkup.h"
#include "resource.h"
#include "DiagnosisSets.h"
#include "CommentDialog.h"
#include "RevisionLevel.h"

// System headers
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <process.h>
#include <direct.h>
#include <wchar.h>
#include <windows.h>
#include <atlenc.h>
#include ".\commands.h"

// Prevent annoying warning from compiler about Microsoft's own bugs.
#pragma warning(disable : 4503)

// Local functions.
static void     getDocTypeStrings(CString& err);
static void     messageLoop();
static void     removeDoc(const CString& docId);
static bool     openDoc(const CString& resp, const CString& docId,
                        BOOL checkOut,
                        const CString& version = _T("Current"));
static CString& fixDoc(CString& doc, const CString& ctl,
                       const CString& docType, bool readOnly);
static CString getBlobExtension(const CString& doc, const CString& type);
static void     clearErrorList();

// Local data.
static cdr::StringList      docTypeStrings;
static cdr::ValidValueSets  validValueSets;
static cdr::ElementSets     linkingElements;
CString CCommands::username;
bool    CCommands::invokedFromClientRefreshTool = false;
static std::map<CString, CString> diagnosisTermSets;
static cdr::StringList diagnosisTermSetNames;

static CString getFullDocPath(_Document* doc) {
    return doc->GetPath() + _T("\\") + doc->GetName();
}

static void set_title_bar() {
    CString title;
    title.Format(_T("CDR Editor (%s)"), CdrSocket::getHostTier());
    //::AfxMessageBox(title);
    CWnd* w = ::AfxGetMainWnd();
    if (w) {
        w->SetWindowText(title);
        //::AfxMessageBox(_T("set window title to ") + title);
    }
    //else
        //::AfxMessageBox(_T("can't set window title bar"));
}

void debugLogWrite(const CString& what, const CString& who) {
    if (who != _T("rmk"))
        return;
    FILE* logFile = fopen("c:/tmp/debug.log", "a");
    static bool warned = true; // false;
    if (!logFile) {
        if (!warned) {
            warned = true;
            ::AfxMessageBox(_T("Can't open log file"));
        }
        return;
    }
    fprintf(logFile, "%s\n", cdr::cStringToUtf8(what).c_str());
    fclose(logFile);
}

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
                CString value = vvElement.getString();
                value = cdr::decode(value);
                vvList.push_back(value);
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
    CString rulesPath = cdr::getUserPath() + _T("\\Rules");
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
    CString omitDtd;
    if (CCommands::invokedFromClientRefreshTool)
        omitDtd = _T("OmitDtd='Y' ");
    cmd.Format(_T("<CdrGetDocType Type='%s' %sGetEnumValues='Y'/>"),
               (LPCTSTR)docType, (LPCTSTR)omitDtd);
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

    // Synchronize the client's copy of the DTD if appropriate.
    if (!CCommands::invokedFromClientRefreshTool) {
        cdr::Element dtd = cdr::Element::extractElement(resp, _T("DocDtd"));
        if (dtd)
            syncDtd(dtd.getCdataSection(), docType);
        else
            ::AfxMessageBox(_T("Unable to find DTD for document type ")
                    + docType, MB_ICONEXCLAMATION);
    }
}

bool getCssFiles(LogonDialog* dialog, CLogonProgress& progressDialog)
{
    cdr::StringList files;
    _Application app = cdr::getApp();
    CString displayPath = cdr::getUserPath() + _T("\\Display");
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
        if (dialog && !dialog->keepGoing()) {
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

bool getDocTypes(LogonDialog* dialog, CLogonProgress& progressDialog)
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
        if (dialog && !dialog->keepGoing()) {
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
        progressDialog.m_progressBar.SetPos((100 * ++i) / nameCount);
    }
    return true;
}

static bool getDocTypesLocal(CString info) {

    // Populate these maps.
    docTypeStrings.clear();
    validValueSets.clear();
    docTypeStrings.push_back(_T("Any Type"));

    // Loop through the document types.
    CString name = _T("CdrGetDocTypeResp");
    cdr::Element elem = cdr::Element::extractElement(info, name);
    while (elem) {
        if (elem.getAttribute(_T("Format")) == _T("xml")) {
            CString docType = elem.getAttribute(_T("Type"));
            docTypeStrings.push_back(docType);
            cdr::ValidValueSet vvSet;
            extractValidValueSet(elem.getString(), vvSet);
            validValueSets[docType] = vvSet;
            cdr::StringSet elemSet;
            extractLinkingElements(elem.getString(), elemSet);
            linkingElements[docType] = elemSet;
            elem = cdr::Element::extractElement(info, name, elem.getEndPos());
        }
    }
    return true;
}

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

    cdr::trace_log("logon");
    try {

        // Make sure the user isn't already logged on.
        if (CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is already logged into the CDR"),
                            MB_ICONEXCLAMATION);
            *pRet = 1;
            return S_OK;
        }

        // See if the client machine has the refresh utility installed.
        CString oldManifest  = cdr::getUserPath() + _T("\\CDR_MANIFEST.XML");
        CString manifestName = cdr::getUserPath() + _T("\\CdrManifest.xml");
        invokedFromClientRefreshTool = false;
        //::AfxMessageBox(_T("Looking for ") + manifestName);
        if (!_waccess((LPCTSTR)manifestName, 0) ||
            !_waccess((LPCTSTR)oldManifest, 0)) {
            //::AfxMessageBox(_T("Found it!"));
            invokedFromClientRefreshTool = true;
            doLogon(NULL);
            *pRet = 0;
            return S_OK;
        }

        // Get the user's CDR credentials.
        //::AfxMessageBox(_T("Couldn't find ") + manifestName);
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
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
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

    cdr::trace_log("retrieve");
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
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
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
 * Submits a search request (obtained from the user) to the CDR server
 * and allows the user to retrieve one of the documents found.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::search(int *pRet)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    cdr::trace_log("search");
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
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
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
 * Load bytes for a document BLOB from the specified file.
 */
static void getBlobFromFile(char* buf, CFile& file, int len) {
    int totalRead = 0;
    while (totalRead < len) {
        int bytesRead = file.Read(buf + totalRead, len - totalRead);
        if (bytesRead < 1)
            throw _T("Failure reading from blob file");
        totalRead += bytesRead;
    }
}

static bool replaceAudioSeconds(::DOMNode& docElement, CString seconds) {
    ::DOMElement& elem = (::DOMElement&)docElement;
    ::DOMNodeList nodeList = elem.getElementsByTagName(_T("SoundData"));
    if (nodeList == 0 || nodeList.GetLength() < 1)
        return false;
    ::DOMElement dimElem = nodeList.item(0);
    ::DOMElement child = dimElem.GetFirstChild();
    while (child != 0) {
        if (child.GetNodeName() == _T("RunSeconds")) {
            cdr::replaceElementContent(child, seconds);
            return true;
        }
        child = child.GetNextSibling();
    }
    return false;
}

static void insertAudioSeconds(::DOMNode& docElement, CFile& file) {

    // Start by blanking out the existing value, to prevent leaving
    // invalid information in the event that we're unable to determine
    // the correct new information.  If the element is not already
    // present, we do nothing.
    if (!replaceAudioSeconds(docElement, _T("")))
        return;

    int seconds = cdr::getAudioSeconds(file);
    if (seconds >= 0) {
        CString s;
        s.Format(_T("%d"), seconds);
        replaceAudioSeconds(docElement, s);
    }
}

static bool replaceImageDimensions(::DOMNode& docElement,
                                   CString height, CString width) {
    ::DOMElement& elem = (::DOMElement&)docElement;
    ::DOMNodeList nodeList = elem.getElementsByTagName(_T("ImageDimensions"));
    if (nodeList == 0 || nodeList.GetLength() < 1)
        return false;
    ::DOMElement dimElem = nodeList.item(0);
    ::DOMElement child = dimElem.GetFirstChild();
    bool foundHeight = false, foundWidth = false;
    while (child != 0) {
        if (child.GetNodeName() == _T("HeightPixels")) {
            cdr::replaceElementContent(child, height);
            foundHeight = true;
        }
        else if (child.GetNodeName() == _T("WidthPixels")) {
            cdr::replaceElementContent(child, width);
            foundWidth = true;
        }
        child = child.GetNextSibling();
    }
    return foundHeight && foundWidth;
}

static void insertImageDimensions(::DOMNode& docElement, CFile& file) {

    // Start by blanking out the existing values, to prevent leaving
    // invalid information in the event that we're unable to determine
    // the correct new information.  If the dimension elements are not
    // already present, we do nothing.
    if (!replaceImageDimensions(docElement, _T(""), _T("")))
        return;

    cdr::ImageDimensions dim;
    if (cdr::getImageDimensions(file, dim)) {
        CString height, width;
        height.Format(_T("%ld"), dim.height);
        width.Format(_T("%ld"), dim.width);
        replaceImageDimensions(docElement, height, width);
    }

    // Restore file position for loading the entire blob.
    file.SeekToBegin();
}

/**
 * Save the currently active document in the CDR repository.
 *
 *  @param  pRet    address of value returned for Microsoft Automation.
 */
STDMETHODIMP CCommands::save(int *pRet)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    cdr::trace_log("save");
    *pRet = 0;
    try {

        // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"),
                            MB_ICONEXCLAMATION);
            *pRet = -6;
            return S_OK;
        }

        // Get the currently active document.
        _Document doc = cdr::getApp().GetActiveDocument();
        if (!doc) {
            ::AfxMessageBox(_T("There is no active document."),
                            MB_ICONEXCLAMATION);
            *pRet = -3;
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
        bool blobPossible = false;
        if (ctrlInfo.docType == _T("Media") ||
            ctrlInfo.docType == _T("SupplementaryInfo"))
            blobPossible = true;
        CSaveDialog saveDialog(ctrlInfo.readyForReview, blobPossible);
        switch (saveDialog.DoModal()) {
        case IDOK:
        {
            // Use a local buffer type to ensure memory release even if an
            // exception occurs.
            struct Buf {
                Buf(size_t n) : buf(new char[n]) { memset(buf, 0, n); }
                ~Buf() { delete [] buf; }
                char* buf;
            };

            CWaitCursor wc;
            clearErrorList();
            cdr::ValidationErrors* valErrors = NULL;

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
            os << _T("<Validate ErrorLocators='Y'>")
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
            if (saveDialog.m_docInactive)
                os << _T("<DocActiveStatus>I</DocActiveStatus>");
            os << _T("<DocNeedsReview>")
               << (saveDialog.m_readyForReview ? _T("Y") : _T("N"))
               << _T("</DocNeedsReview>");
            if (!saveDialog.m_comment.IsEmpty())
                os << _T("<DocComment>" )
                   << (LPCTSTR)cdr::encode(saveDialog.m_comment)
                   << _T("</DocComment>");
            os << _T("</CdrDocCtl>");

            // Handle blob if present.
            int blobSize = 0;
            CFile blobFile;
            CString blobFilename = saveDialog.m_blobFilenameString;
            if (!blobFilename.IsEmpty()) {
                if (!blobFile.Open((LPCTSTR)blobFilename,
				   CFile::modeRead|CFile::shareDenyNone)) {
		    CString msg;
		    msg.Format(_T("Failure loading %s"), blobFilename);
                    *pRet = -7;
                    return S_OK;
		}
                blobSize = (int)blobFile.GetLength();
                if (ctrlInfo.docType == _T("Media")) {
                    try {
                        // Harmless if blob isn't an image.
                        insertImageDimensions(docElement, blobFile);
                    }
                    catch (...) {
                        TCHAR* msg = _T("Unable to set image dimensions");
                        ::AfxMessageBox(msg);
                    }
                    try {
                        // Shouldn't be a problem if this isn't an audio file.
                        insertAudioSeconds(docElement, blobFile);
                    }
                    catch (...) {
                        TCHAR* msg = _T("Unable to set RunSeconds");
                        ::AfxMessageBox(msg);
                    }
                }
            }
            Buf blobBuf(blobSize);
            if (blobSize > 0) {
                try {
                    getBlobFromFile(blobBuf.buf, blobFile, blobSize);
                }
                catch (::CException* e) {
                    CString msg;
                    msg.Format(_T("Failure loading %s"), blobFilename);
                    ::AfxMessageBox(msg);
                    e->ReportError();
                    e->Delete();
                    *pRet = -7;
                    return S_OK;
                }
                catch (...) {
                    CString msg;
                    msg.Format(_T("Unknown failure loading %s"), blobFilename);
                    ::AfxMessageBox(msg);
                    *pRet = -7;
                    return S_OK;
                }
            }

            // Add the XML for the document.
            os << _T("<CdrDocXml><![CDATA[") << docElement
               << _T("]]></CdrDocXml>");

            //------------------------------------------------------------
            // This has been rewritten to work around a bug in the Microsoft
            // runtime, which fails to request additional memory from the
            // operating system when the heap which it is managing itself
            // is unable to fulfil a memory allocation request.  We need
            // to calculate the amount of memory to allocate for the
            // save command's buffer and only create a single copy of
            // that command.  If even this fails, we may resort to
            // using our own base-64 encoding directly from the blob
            // file instead of reading the blob's bytes into a separate
            // buffer.  We allocate an additional kilobyte for the
            // buffer to provide room for the sendCommand() method
            // to wrap the command in the CdrCommandSet element.
            //------------------------------------------------------------
            int encodedBlobSize = 0;
            CString back;
            if (blobSize) {
                os << _T("<CdrDocBlob>");
                back = _T("</CdrDocBlob>");
                encodedBlobSize = Base64EncodeGetRequiredLength(blobSize);
            }
            CString front = os.str().c_str();
            std::string f = cdr::cStringToUtf8(front);
            back += _T("</CdrDoc></") + cmdTag + _T(">");
            std::string b = cdr::cStringToUtf8(back);

            // Calculate how much memory we need (with 1KB padding).
            int commandSize = f.length() + encodedBlobSize + b.length() + 1024;
            Buf commandBuf(commandSize);
            memcpy(commandBuf.buf, f.c_str(), f.length());
            char* p = commandBuf.buf + f.length();

            // Add the blob if we have one.
            if (encodedBlobSize) {
                int written = encodedBlobSize;
                BOOL ok = Base64Encode((const BYTE*)blobBuf.buf, blobSize,
                                       p, &written);
                if (!ok) {
                    ::AfxMessageBox(_T("failure encoding blob"));
                    *pRet = -9;
                    return S_OK;
                }
                int actualLen = strlen(p);
                p += written;
            }

            // Tack on the end of the command and null terminate the string.
            memcpy(p, b.c_str(), b.length());
            p += b.length();
            *p = '\0';

            // Submit the save command to the server.
            CString dummy;
            CString rsp = CdrSocket::sendCommand(dummy, false, commandBuf.buf);
            cdr::Element responseElem =
                cdr::Element::extractElement(rsp, _T("CdrResponse"));
            CString status = responseElem.getAttribute(_T("Status"));
            if (status != _T("success")) {
                *pRet = -2;
                if (rsp.Find(_T("<Error")) != -1)
                    cdr::showErrors(rsp);
                else
                    ::AfxMessageBox(_T("Failure without explanation"),
                                    MB_ICONEXCLAMATION);
            }

            if (!*pRet) {

                // Show the user any validation errors.
                cdr::Element errors =
                    cdr::Element::extractElement(rsp, _T("Errors"));
                if (errors) {
                    valErrors = new cdr::ValidationErrors(errors);
                    CString version = _T("Current");
                    if (valErrors->errors.size() > 0) {
                        // Right now we're doing this just from the Javascript.
                        //cdr::showValidationErrors(*valErrors);
                        *pRet = (int)valErrors->errors.size();
                    }
                    else if (saveDialog.m_validate) {
                        CPassedValidation dlg(ctrlInfo.docId);
                        dlg.DoModal();
                    }
                }
                cdr::Element docId =
                    cdr::Element::extractElement(rsp, _T("DocId"));
                if (!docId) {
                    delete valErrors;
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
                    if (!saveDialog.m_checkIn) {
                        openDoc(rsp, docId.getString(), true);
                        if (valErrors) {
                            doc = cdr::getApp().GetActiveDocument();
                            CString path = getFullDocPath(&doc);
                            cdr::validationErrorSets[path] = valErrors;
                        }
                    }
                    else {
                        delete valErrors;
                        removeDoc(docId.getString());
                    }
                }
            }
            break;
        }
        case IDCANCEL:
            *pRet = -1;
            break;
        }
    }
    catch (::COleDispatchException* ode) {
        CString msg;
        msg.Format(_T("Dispatch Exception; error code: %lu\n")
                   _T("From application: %s\n")
                   _T("Description: %s"), ode->m_wCode, ode->m_strSource,
                                          ode->m_strDescription);
        ::AfxMessageBox(msg);
        ode->Delete();
        *pRet = -6;
    }
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
        *pRet = -6;
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."),
            MB_ICONEXCLAMATION);
        *pRet = -6;
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

    cdr::trace_log("validate");
    *pRet = 0;

    // Find the currently active document.
    _Document doc = cdr::getApp().GetActiveDocument();

    // Extract the document's control information.
    DOMNode docElement = doc.GetDocumentElement();
    CdrDocCtrlInfo ctrlInfo;
    cdr::extractCtlInfo(docElement, ctrlInfo);
    if (ctrlInfo.docId.IsEmpty()) {
        *pRet = -8;
        ::AfxMessageBox(_T("Document has never been saved"),
            MB_ICONEXCLAMATION);
        return S_OK;
    }

    try {

        // Make sure the user is logged on to the CDR.
        if (!CdrSocket::loggedOn()) {
            ::AfxMessageBox(_T("This session is not logged into the CDR"),
                            MB_ICONEXCLAMATION);
            *pRet = -6;
            return S_OK;
        }

        // Ask the user for options to be used during validation.
        CValidateDialog validateDialog;
        switch (validateDialog.DoModal()) {
        case IDOK:
        {
            CWaitCursor wc;

            clearErrorList();

            CString docType = docElement.GetNodeName();

            // Build the validate command.
            std::basic_ostringstream<TCHAR> os;
            os << _T("<CdrValidateDoc DocType='") << (LPCTSTR)docType
               << _T("' ErrorLocators='Y' ValidationTypes='");

            // Dialog box ensures that at least one is true.
            LPCTSTR separator = _T("");
            if (validateDialog.m_schemaValidation) {
                os << _T("Schema");
                separator = _T(" ");
            }
            if (validateDialog.m_linkValidation)
                os << separator << _T("Links");
            int filterLevel = 3;
            if (validateDialog.m_includeProposedAndApprovedMarkup)
                filterLevel = 1;
            else if (validateDialog.m_includeApprovedMarkup)
                filterLevel = 2;
                os << _T("' Id='") << (LPCTSTR)ctrlInfo.docId;
            os << _T("'><CdrDoc Type='") << (LPCTSTR)docType
               << _T("' RevisionFilterLevel='") << filterLevel
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
            cdr::Element errors =
                cdr::Element::extractElement(rsp, _T("Errors"));
            if (errors) {
                cdr::ValidationErrors *valErrs =
                    new cdr::ValidationErrors(errors);
                CString path = getFullDocPath(&doc);
                cdr::validationErrorSets[path] = valErrs;
                CString version = _T("Current");
                if (valErrs->errors.size() > 0) {
                    bool checkOut = path.Find(_T("Checkout")) != -1;
                    int verPos = path.Find(_T("-V"));
                    if (verPos != -1) {
                        version = path.Mid(verPos + 2);
                        version = version.Left(version.GetLength() - 4);
                    }
                    doc.Close(2); // 2=don't save changes.
                    openDoc(rsp, ctrlInfo.docId, checkOut, version);

                    // Right now we're doing this just from the Javascript.
                    //cdr::showValidationErrors(*valErrs);

                    *pRet = (int)valErrs->errors.size();
                }
                else {
                    CPassedValidation dlg(ctrlInfo.docId);
                    dlg.DoModal();
                }
            }
            else {
                CPassedValidation dlg(ctrlInfo.docId);
                dlg.DoModal();
            }
            break;
        }
        case IDCANCEL:
            *pRet = -1;
            break;
        }
    }
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
        *pRet = -2;
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected error from validation command."),
                        MB_ICONEXCLAMATION);
        *pRet = -2;
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

    cdr::trace_log("logoff");
    // Show the user the list of documents she still has checked out.
    if (!username.IsEmpty()) {
        CString cmd = _T("<CdrReport>")
                      _T("<ReportName>Locked Documents</ReportName>")
                      _T("<ReportParams><ReportParam Name='UserId' Value='")
                    + username
                    + _T("'/></ReportParams></CdrReport>");
        CString rsp = CdrSocket::sendCommand(cmd);
        cdr::StringList docIds;
        cdr::Element r = cdr::Element::extractElement(rsp, _T("ReportRow"));
        while (r) {
            cdr::Element docId = r.extractElement(r.getString(), _T("DocId"));
            docIds.push_back(docId.getString());
            r = r.extractElement(rsp, _T("ReportRow"), r.getEndPos());
        }
        if (docIds.size() > 0) {
            CString separator = _T("");
            CString warning = _T("The following documents are still ")
                              _T("locked by your CDR account:\n");
            cdr::StringList::const_iterator i = docIds.begin();
            while (i != docIds.end()) {
                warning += separator + *i++;
                separator = _T(", ");
            }
            ::AfxMessageBox(warning, MB_ICONEXCLAMATION);
        }
    }

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
        //  MB_ICONEXCLAMATION);
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

    cdr::trace_log("edit");
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
            else if (elemName == _T("PrivatePracticeSiteID"))
                editType = CEditElement::PRIV_PRACTICE;
            else if (elemName == _T("Organization")) {
                LPCTSTR respOrg = _T("ResponsibleOrganization");
                if (selection.GetIsParentElement(respOrg))
                    editType = CEditElement::ORG_LOCATION;
            }
        }
        else if (docType == _T("Person")) {
            if (elemName  == _T("OrganizationLocation")) {
                if (selection.GetIsParentElement(_T("OtherPracticeLocation")))
                    editType = CEditElement::ORG_LOCATION;
            }
            else if (elemName == _T("FamilialCancerSyndrome"))
                editType = CEditElement::GP_SYNDROME;
        }

        // Most of the real work is done inside this call.
        CEditElement editDialog(docType, elemName, editType);
        if (editDialog.DoModal() != IDOK)
            *pRet = 2;
    }
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
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
                           BOOL checkOut,
                           const CString& version)
{
    debugLogWrite(_T("Top of doRetrieve"), username);
    // Make sure the document isn't already open.
    _Application app = cdr::getApp();
    debugLogWrite(_T("Got app"), username);
    Documents docs = app.GetDocuments();
    debugLogWrite(_T("Got documents"), username);
    unsigned int docNo = cdr::getDocNo(id);
    CString match;
    if (version != _T("Current"))
        match.Format(_T("CDR%u-V%s "), docNo, version);
    else
        match.Format(_T("CDR%u "), docNo);
    int matchLen = match.GetLength();
    debugLogWrite(match, username);
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
    request.Format(_T("<CdrGetDoc includeBlob='N'>")
                   _T("<DocId>%s</DocId>")
                   _T("<Lock>%s</Lock>")
                   _T("<DocVersion>%s</DocVersion>")
                   _T("</CdrGetDoc>"), docId,
                                       (checkOut ? _T("Y") : _T("N")),
                                       version);
    debugLogWrite(request, username);
    CString response = CdrSocket::sendCommand(request);

    return openDoc(response, docId, checkOut, version);
}

void removeDoc(const CString& docId)
{
    unsigned int docNo = cdr::getDocNo(docId);
    CString cdrPath = cdr::getUserPath() + _T("\\Cdr");
    CString docPath;
    docPath.Format(_T("%s\\Checkout\\CDR%u.xml"), (LPCTSTR)cdrPath, docNo);
    try {
        CFile::Remove((LPCTSTR)docPath);
    }
    // catch (CFileException&) { /* ignore */ }
    catch (...) { /* ignore this, too; MFC docs are incorrect about which
                  exception will be thrown. */ }
}

bool openDoc(const CString& resp, const CString& docId, BOOL checkOut,
                const CString& version)
{
    // Extract the CdrDoc element.
    _Application app = cdr::getApp();
    Documents docs = app.GetDocuments();
    unsigned int docNo = cdr::getDocNo(docId);
    CString err;
    CString blocked = _T("N");
    CString docType;
    CString docPath;
    CString retrievedDocTitle;
    CString cdrDoc;
    CString docTitle;
    CString cdrPath = cdr::getUserPath() + _T("\\Cdr");
    cdr::Element cdrDocElem = cdr::Element::extractElement(resp,
                                                           _T("CdrDoc"));

    // Find out if the document has been marked ReadyForReview.
    CString readyForReview = _T("N");
    cdr::Element docCtlElem = cdr::Element::extractElement(resp,
            _T("ReadyForReview"));
    if (docCtlElem && docCtlElem.getString() == _T("Y"))
        readyForReview = _T("Y");

    // Build up path string.
    CString verPart = _T("");
    if (version != _T("Current"))
        verPart.Format(_T("-V%s"), version);
    docPath.Format(_T("%s\\%s\\CDR%u%s.xml"),
                   (LPCTSTR)cdrPath,
                   checkOut ? _T("Checkout") : _T("ReadOnly"),
                   docNo,
                   (LPCTSTR)verPart);

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
            CString titleStart = docTitle.Left(15); // OCECDR-3914
            if (titleStart.GetLength() < docTitle.GetLength())
                titleStart += L'\x2026';
            retrievedDocTitle.Format(_T("CDR%u%s%s - %s"), docNo,
                                     (LPCTSTR)verPart,
                                     checkOut ? _T("") : _T(" [RO]"),
                                     (LPCTSTR)cdr::decode(titleStart));
        }
        cdr::Element statusElem = cdr::Element::extractElement(cdrDoc,
                                                 _T("DocActiveStatus"));
        if (statusElem && statusElem.getString() == _T("I")) {
            blocked = _T("Y");
        }
    }

    // Extract the DocXml.
    CString docXml;
    if (err.IsEmpty() && docType.IsEmpty())
        err = _T("Missing Type attribute in CdrDoc element");
    if (err.IsEmpty()) {
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
            CString ctl = _T("\n <CdrDocCtl readyForReview='")
                            + readyForReview
                            + _T("' blocked='")
                            + blocked
                            + _T("'>\n  <DocId>")
                            + docId
                            + _T("</DocId>\n  <DocTitle>")
                            + docTitle
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
                //CString tier = CdrSocket::getHostTier();
                doc.SetTitle(//_T("[") + tier + _T("] ") +
                             retrievedDocTitle);
                return true;
            }
            return false;
        }
        catch (::COleDispatchException* ode) {
            CString msg;
            msg.Format(_T("Dispatch Exception; error code: %lu\n")
                       _T("From application: %s\n")
                       _T("Description: %s"), ode->m_wCode, ode->m_strSource,
                                              ode->m_strDescription);
            ::AfxMessageBox(msg);
            ode->Delete();
            return false;
        }
        catch (::CException* e) {
            e->ReportError();
            e->Delete();
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

static CString getLocalDocTypeInfo() {
    // Use a local buffer type to ensure memory release even if an
    // exception occurs.
    struct Buf {
        Buf(size_t n) : buf(new char[n]) { memset(buf, 0, n); }
        ~Buf() { delete [] buf; }
        char* buf;
    };
    try {
        CFile file;
        CString path = cdr::getUserPath() + _T("\\CdrDocTypes.xml");
        file.Open((LPCTSTR)path, CFile::modeRead);
        int nBytes = (int)file.GetLength();

        Buf b((size_t)nBytes);
        int totalRead = 0;
        while (totalRead < nBytes) {
            int bytesRead = file.Read(b.buf + totalRead, nBytes - totalRead);
            if (bytesRead < 1) {
                ::AfxMessageBox(_T("Failure reading CdrDocTypes.xml"));
                throw _T("Failure reading from CdrDocTypes.xml");
            }
            totalRead += bytesRead;
        }
        CString fileContents = cdr::utf8ToCString(b.buf);
        return fileContents;
    }
    catch(...) {}
    return _T("");
}

bool CCommands::doLogon(LogonDialog* logonDialog)
{
    // Make the document directories if they aren't already there.
    CString cdrPath = cdr::getUserPath() + _T("\\Cdr");
    CString roPath  = cdrPath + _T("\\ReadOnly");
    CString coPath  = cdrPath + _T("\\Checkout");
    CString mePath  = cdrPath + _T("\\Media");
    _wmkdir((LPCTSTR)cdrPath);
    _wmkdir((LPCTSTR)roPath);
    _wmkdir((LPCTSTR)coPath);
    _wmkdir((LPCTSTR)mePath);
    set_title_bar();
    // Clear out the username.
    username = _T("");

    // If we were invoked directly, get the logon info from the environment.
    if (!logonDialog) {
        const char* sessId = getenv("CDRSession");
        const char* userId = getenv("CDRUser");

        // If the environment variables aren't set, the user wants to
        // run XMetaL in a standalone session.
        if (!sessId || !userId)
            return false;

        username = userId;
        CdrSocket::setSessionString(sessId);
    }

    // Otherwise, log on to the CDR server directly.
    else {

        // Create the logon command.
        CString request = _T("<CdrLogon><UserName>")
                        + logonDialog->m_UserId
                        + _T("</UserName><Password>")
                        + logonDialog->m_Password
                        + _T("</Password></CdrLogon>");

        // Submit the command to the CDR server.
        CString response = CdrSocket::sendCommand(request);
        if (response.IsEmpty())
            return false;

        TinyXmlParser p(response);
        CdrSocket::setSessionString(p.extract(_T("SessionId")));
        if (!CdrSocket::loggedOn()) {
            CString err = p.extract(_T("Err"));
            if (err.IsEmpty())
                err = _T("Unknown failure logging on to the CDR");
            ::AfxMessageBox(err, MB_ICONEXCLAMATION);
            return false;
        }
        username = logonDialog->m_UserId;
    }

    // Get the document type information we need.
    CString localDocTypeInfo = getLocalDocTypeInfo();
    bool gotDocTypes = false;
    if (!localDocTypeInfo.IsEmpty())
        gotDocTypes = getDocTypesLocal(localDocTypeInfo);
    else {
        CLogonProgress progressDialog;
        progressDialog.Create(progressDialog.IDD);
        progressDialog.SetWindowPos(&CWnd::wndTop, 10, 10, 0, 0, SWP_NOSIZE);
        progressDialog.ShowWindow(SW_SHOW);
        gotDocTypes = getDocTypes(logonDialog, progressDialog);
        if (!invokedFromClientRefreshTool)
            getCssFiles(logonDialog, progressDialog);
        progressDialog.DestroyWindow();
    }

    // Populate the strings for creating diagnosis macros.
    CString termSetRequest =
        _T("<CdrReport><ReportName>Term Sets</ReportName>")
        _T("<ReportParams>")
        _T("<ReportParam Name='SetType' Value='diagnosis macro'/>")
        _T("</ReportParams></CdrReport>");
    CString tsResponse = CdrSocket::sendCommand(termSetRequest);
    cdr::Element tsElem =
        cdr::Element::extractElement(tsResponse, _T("TermSet"));
    while (tsElem) {
        cdr::Element nameElem = cdr::Element::extractElement(
            tsElem.getString(), _T("Name"));
        cdr::Element membersElem = cdr::Element::extractElement(
            tsElem.getString(), _T("Members"));
        CString name = nameElem.getString();
        CString members = membersElem.getString();
        diagnosisTermSetNames.push_back(nameElem.getString());
        diagnosisTermSets[name] = members;
        tsElem = cdr::Element::extractElement(tsResponse,
            _T("TermSet"), tsElem.getEndPos());
    }
    return gotDocTypes;
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

    cdr::trace_log("isReadOnly");
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

    cdr::trace_log("advancedSearch");
    COleDispatchDriver ie;
    if (!ie.CreateDispatch(_T("InternetExplorer.Application"))) {
        ::AfxMessageBox(_T("Unable to launch Internet Explorer"),
            MB_ICONEXCLAMATION);
        return S_OK;
    }
    CString url = _T("http://")
                + CdrSocket::getHostName()
                + _T("/cgi-bin/cdr/AdvancedSearch.py?Session=")
                + CdrSocket::getSessionString();
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

    cdr::trace_log("get_username");
    username.SetSysString(pVal);

    return S_OK;
}

STDMETHODIMP CCommands::protUpdPerson(int *pRet)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    cdr::trace_log("protUpdPerson");
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
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
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

    cdr::trace_log("getPersonAddress");
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
        // Change requested May 2002 by LG: only import PostalAddress.
        cdr::Element paElement =
            cdr::Element::extractElement(rsp, _T("PostalAddress"));
        if (!paElement) {
            if (!cdr::showErrors(rsp))
                ::AfxMessageBox(_T("Unknown failure from search"),
                                MB_ICONEXCLAMATION);
            return S_OK;
        }

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
        CString pscData = _T("<ProtocolSpecificContact><PostalAddress>")
                        + paElement.getString()
                        + _T("</PostalAddress></ProtocolSpecificContact>");
        //::AfxMessageBox(pscData);
        if (!pscLoc.GetCanPaste(pscData, FALSE))
            ::AfxMessageBox(_T("Unable to insert ") + pscData,
                MB_ICONEXCLAMATION);
        else
            pscLoc.PasteString(pscData);

    }
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
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

    cdr::trace_log("particOrgs");
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
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
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

    cdr::trace_log("getOrgAddress");
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
        CString aType = postalAddressElement.getAttribute(_T("AddressType"));
        if (aType.IsEmpty())
            aType = _T("US");

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
        CString spaData = _T("<SpecificPostalAddress AddressType='")
                        + aType
                        + _T("'>")
                        + paStr
                        + _T("</SpecificPostalAddress>");
        //::AfxMessageBox(pscData);
        if (!spaLoc.GetCanPaste(spaData, FALSE))
            ::AfxMessageBox(_T("Unable to insert ") + spaData,
                    MB_ICONEXCLAMATION);
        else
            spaLoc.PasteString(spaData);

    }
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
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

    cdr::trace_log("pasteDocLink");
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

            // Determine whether this is a cdr:ref or cdr:href link.
            ::DOMDocumentType dt = doc.GetDoctype();
            if (dt.GetHasAttribute(elem.GetNodeName(), _T("cdr:href"))) {

                // If this is a cdr:href link, this is all we need to do.
                elem.setAttribute(_T("cdr:href"), docLink);
                *pRet = 0;
                return S_OK;
            }

            // BZIssue::5172 - Add support for Target attribute.
            if (dt.GetHasAttribute(elem.GetNodeName(), _T("Target"))) {

                // If this is a Target link, this is all we need to do.
                elem.setAttribute(_T("Target"), docLink);
                *pRet = 0;
                return S_OK;
            }

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
        catch (::CException* e) {
            e->ReportError();
            e->Delete();
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

    cdr::trace_log("get_session");
    CString session = CdrSocket::getSessionString();
    session.SetSysString(pVal);

    return S_OK;
}

STDMETHODIMP CCommands::checkIn(int *pRet)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    cdr::trace_log("checkIn");
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
    catch (::CException* e) {
        e->ReportError();
        e->Delete();
    }
    catch (...) {
        ::AfxMessageBox(_T("Unexpected exception encountered."),
            MB_ICONEXCLAMATION);
    }

    return S_OK;
}

STDMETHODIMP CCommands::get_hostname(BSTR *pVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    cdr::trace_log("get_hostname");
    CString hostname = CdrSocket::getHostName();
    hostname.SetSysString(pVal);

    return S_OK;
}

STDMETHODIMP CCommands::showPage(const BSTR* url,  int* pRet)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("showPage");
    CString urlString(*url);
    *pRet = cdr::showPage(urlString);
    return S_OK;
}

STDMETHODIMP CCommands::glossify(VARIANT_BOOL dig)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    cdr::trace_log("glossify");
    CGlossify glossify(dig != VARIANT_FALSE);
    glossify.DoModal();
    return S_OK;
}

static bool inSpanishSummary() {
    _Application app = cdr::getApp();
    ::_Document doc = app.GetActiveDocument();
    DOMNode docElement = doc.GetDocumentElement();
    CString docType = docElement.GetNodeName();
    if (docType == _T("Summary")) {
        ::DOMNode c = docElement.GetFirstChild();
        while (c) {
            if (c.GetNodeName() == _T("SummaryMetaData")) {
                ::DOMNode gc = c.GetFirstChild();
                while (gc) {
                    if (gc.GetNodeName() == _T("SummaryLanguage")) {
                        CString value = cdr::extractElementText(gc);
                        //::AfxMessageBox(value);
                        if (value == _T("Spanish"))
                            return true;
                    }
                    gc = gc.GetNextSibling();
                }
            }
            c = c.GetNextSibling();
        }
    }
    return false;
}

STDMETHODIMP CCommands::addGlossaryPhrase(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("addGlossaryPhrase");
    // Find the element with the current focus.
    ::Selection selection = cdr::getApp().GetSelection();
    ::DOMElement elem = selection.GetContainerNode();

    // Make sure we have a glossary term reference.
    if (!elem || elem.GetNodeName() != _T("GlossaryTermRef")) {
        ::AfxMessageBox(_T("No GlossaryTermRef at current location"),
            MB_ICONEXCLAMATION);
        return S_OK;
    }

    // Extract the document ID (if there is one).
    CString docIdElem;
    CString docId = elem.getAttribute(_T("cdr:href"));
    if (!docId.IsEmpty())
        docIdElem = _T("<CdrId>") + docId + _T("</CdrId>");

    // Extract the text content of the element & determine usage.
    selection.SelectContainerContents();
    CString value = selection.GetText();
    CString usage = _T("GlossaryTerm Phrases");
    CString language = _T("English");
    if (inSpanishSummary()) {
        usage = _T("Spanish GlossaryTerm Phrases");
        language = _T("Spanish");
    }

    // Ask the server to add the phrase.
    CString cmd = _T("<CdrAddExternalMapping>")
                  _T("<Usage>") + usage + _T("</Usage>")
                  _T("<Value>") + value + _T("</Value>")
                + docIdElem
                + _T("</CdrAddExternalMapping>");
    CWaitCursor wc;
    CString rsp = CdrSocket::sendCommand(cmd);
    if (rsp.Find(_T("<Error")) != -1)
        cdr::showErrors(rsp);
    else
        ::AfxMessageBox(language + _T(" glossary phrase added ")
                        _T("to external mapping table."));
    return S_OK;
}

STDMETHODIMP CCommands::setTitleBar(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    //cdr::trace_log("setTitleBar"); XXX too noisy; clutters the log
    CString title;
    title.Format(_T("CDR Editor (%s)"), CdrSocket::getHostTier());
    //::AfxMessageBox(title);
    CWnd* w = ::AfxGetMainWnd();
    if (w) {
        w->SetWindowText(title);
    }

    return S_OK;
}

STDMETHODIMP CCommands::acceptOrRejectMarkup(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("acceptOrRejectMarkup");
    CReviewMarkup markupReviewDialog;
    markupReviewDialog.DoModal();

    return S_OK;
}

CString getBlobExtension(const CString& docXml, const CString& docType) {
    CString extension;
    if (docType == _T("Media")) {
        cdr::Element elem = cdr::Element::extractElement(docXml,
                                                         _T("ImageEncoding"));
        if (!elem)
            elem = cdr::Element::extractElement(docXml, _T("VideoEncoding"));
        if (!elem)
            elem = cdr::Element::extractElement(docXml, _T("SoundEncoding"));
        if (elem)
            extension = _T(".") + elem.getString();
    }
    else if (docType == _T("SupplementaryInfo")) {
        cdr::Element elem = cdr::Element::extractElement(docXml,
                                                         _T("MimeType"));
        CString elemText = elem.getString();
        if (elemText == _T("application/pdf"))
            extension = _T(".pdf");
        else if (elemText == _T("application/msword"))
            extension = _T(".doc");
        else if (elemText == _T("application/vnd.ms-excel"))
            extension = _T(".xls");
        else if (elemText == _T("application/vnd.wordperfect"))
            extension = _T(".wpd");
        else if (elemText == _T("text/html"))
            extension = _T(".html");
        else if (elemText == _T("text/rtf"))
            extension = _T(".rtf");
        else if (elemText == _T("text/plain"))
            extension = _T(".txt");
        else if (elemText == _T("message/rfc822"))
            extension = _T(".txt");
        else if (elemText == _T("image/jpeg"))
            extension = _T(".jpg");
    }
    return extension.MakeLower();
}

STDMETHODIMP CCommands::launchBlob(const BSTR* docId, const BSTR* docVer)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("launchBlob");
    CString id(*docId);
    CString ver(*docVer);
    CString fileName;
    int intId = cdr::getDocNo(id);
    fileName.Format(_T("CDR%d"), intId);
    if (!ver.IsEmpty())
        fileName += _T("-") + ver;
    else
        ver = _T("Current");

    // Construct the command to retrieve the document with its blob.
    CString cmd;
    cmd.Format(_T("<CdrGetDoc includeXml='Y' includeBlob='Y'>")
               _T("<DocId>%s</DocId>")
               _T("<Lock>N</Lock>")
               _T("<DocVersion>%s</DocVersion>")
               _T("</CdrGetDoc>"), id, ver);
    CString resp = CdrSocket::sendCommand(cmd);

    // Extract the payload.
    cdr::Element docElem = cdr::Element::extractElement(resp, _T("CdrDoc"));
    if (!docElem) {
        cdr::showErrors(resp);
        return S_OK;
    }
    CString cdrDoc  = docElem.getString();
    CString docType = docElem.getAttribute(_T("Type"));

    // Extract the blob.
    cdr::Element blobElem = cdr::Element::extractElement(cdrDoc,
                                                         _T("CdrDocBlob"));
    if (!blobElem) {
        ::AfxMessageBox(_T("Binary object not found"));
        return S_OK;
    }
    CString docBlob = blobElem.getString();

    // Use a local buffer type to ensure memory release even if an
    // exception occurs.
    struct Buf {
        Buf(size_t n) : buf(new char[n]) { memset(buf, 0, n); }
        ~Buf() { delete [] buf; }
        char* buf;
    };
    int dstLen = ::Base64DecodeGetRequiredLength(docBlob.GetLength());
    Buf blob((size_t)dstLen);
    std::string bytes = cdr::cStringToUtf8(docBlob);
    if (!::Base64Decode(bytes.c_str(), docBlob.GetLength(),
                        (BYTE*)blob.buf, &dstLen)) {
        ::AfxMessageBox(_T("Failure decoding blob file"));
        return S_OK;
    }

    // Extract the DocXml.
    cdr::Element xmlElem = cdr::Element::extractElement(cdrDoc,
                                                        _T("CdrDocXml"));
    if (!xmlElem) {
        ::AfxMessageBox(_T("Missing document XML"));
        return S_OK;
    }
    CString docXml = xmlElem.getCdataSection();

    // Save the file.
    CString path = cdr::getUserPath() + _T("\\Cdr\\Media");
    ::CreateDirectory((LPCTSTR)path, NULL);
    path += _T("\\") + fileName;
    CString ext = getBlobExtension(docXml, docType);
    if (ext.IsEmpty()) {
        ::AfxMessageBox(_T("Unable to determine filename extension"));
        return S_OK;
    }
    path += ext;
    std::string pathName = cdr::cStringToUtf8(path);
    std::ofstream xmlStream(pathName.c_str(), std::ios_base::binary |
                                              std::ios_base::out);
    if (!xmlStream) {
        ::AfxMessageBox(_T("Unable to write ") + path);
        return S_OK;
    }
    xmlStream.write(blob.buf, dstLen);
    xmlStream.close();

    // Invoke the application registered by the user for this file type.
    ::ShellExecute(NULL, _T("open"), path, NULL, NULL, SW_SHOWNORMAL);
    return S_OK;
}

STDMETHODIMP CCommands::openCdrDoc(const BSTR* docId, const BSTR* docVer,
                                   VARIANT_BOOL checkOut)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("openCdrDoc");
    CString id(*docId);
    CString ver(*docVer);
    BOOL co(checkOut);
    doRetrieve(id, co, ver);

    return S_OK;
}

STDMETHODIMP CCommands::getTranslatedDocId(const BSTR* originalId,
                                           BSTR* translatedDocId)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("getTranslatedDocId");
    CString id(*originalId);
    CString cmd = _T("<CdrReport>")
                  _T("<ReportName>Translated Summary</ReportName>")
                  _T("<ReportParams><ReportParam Name='EnglishSummary' ")
                  _T("Value='") + id + _T("'/></ReportParams>")
                  _T("</CdrReport>");
    CString r = CdrSocket::sendCommand(cmd);
    //::AfxMessageBox(r);
    cdr::Element e = cdr::Element::extractElement(r, _T("TranslatedSummary"));
    CString translationId;
    if (e)
        translationId = e.getString();
    else
        cdr::showErrors(r);
    //::AfxMessageBox(_T("translationId: ") + translationId);
    translationId.SetSysString(translatedDocId);

    return S_OK;
}

STDMETHODIMP CCommands::getDiagnosisSetTerms(BSTR* termIds)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    cdr::trace_log("getDiagnosisSetTerms");
    CDiagnosisSets dialog(diagnosisTermSetNames);
    int rc = dialog.DoModal();
    CString result = _T("");
    switch (rc) {
    case IDOK:
        //::AfxMessageBox(_T("CDR Logon Successful"));
        if (!dialog.chosenSetName.IsEmpty())
            try {
                diagnosisTermSets[dialog.chosenSetName].SetSysString(termIds);
            }
            catch (...) {
                ::AfxMessageBox(_T("Internal failure"), MB_ICONEXCLAMATION);
            }
        break;
    case IDCANCEL:
        break;
    case -1:
    default:
        ::AfxMessageBox(_T("Internal failure"), MB_ICONEXCLAMATION);
        break;
    }
    return S_OK;
}

STDMETHODIMP CCommands::getGlossaryTermNames(const BSTR* conceptId,
                                             BSTR* termNames)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("getGlossaryTermNames");
    CString id(*conceptId);
    CString cmd = _T("<CdrReport>")
                  _T("<ReportName>Glossary Term Names</ReportName>")
                  _T("<ReportParams><ReportParam Name='ConceptId' ")
                  _T("Value='") + id + _T("'/></ReportParams>")
                  _T("</CdrReport>");
    CString rsp = CdrSocket::sendCommand(cmd);
    CString names = _T("");
    if (rsp.Find(_T("<Error")) != -1) {
        names = _T("ERROR");
        cdr::showErrors(rsp);
    }
    else {
        CString ename  = _T("GlossaryTermName");
        CString sep    = _T("    ");
        cdr::Element e = cdr::Element::extractElement(rsp, ename);
        while (e) {
            CString name = e.getString();
            names += sep + name;
            e = cdr::Element::extractElement(rsp, ename, e.getEndPos());
            sep = _T("\n    ");
        }
    }
    names.SetSysString(termNames);

    return S_OK;
}

STDMETHODIMP CCommands::getGlossaryTermNameIds(const BSTR* conceptId,
                                               BSTR* termNameIds)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("getGlossaryTermNameIds");
    CString id(*conceptId);
    CString cmd = _T("<CdrReport>")
                  _T("<ReportName>Glossary Term Names</ReportName>")
                  _T("<ReportParams><ReportParam Name='ConceptId' ")
                  _T("Value='") + id + _T("'/></ReportParams>")
                  _T("</CdrReport>");
    CString rsp = CdrSocket::sendCommand(cmd);
    CString termIds = _T("");
    if (rsp.Find(_T("<Error")) != -1) {
        termIds = _T("ERROR");
        cdr::showErrors(rsp);
    }
    else {
        CString ename  = _T("GlossaryTermName");
        CString sep    = _T("");
        cdr::Element e = cdr::Element::extractElement(rsp, ename);
        while (e) {
            CString termId = e.getAttribute(_T("ref"));
            termIds += sep + termId;
            e = cdr::Element::extractElement(rsp, ename, e.getEndPos());
            sep = _T(" ");
        }
    }
    termIds.SetSysString(termNameIds);
    return S_OK;
}

STDMETHODIMP CCommands::getPatientDocId(const BSTR* hpDocId, BSTR* patientDocId)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("getPatientDocId");
    CString id(*hpDocId);
    CString cmd = _T("<CdrReport>")
                  _T("<ReportName>Patient Summary</ReportName>")
                  _T("<ReportParams><ReportParam Name='HPSummary' ")
                  _T("Value='") + id + _T("'/></ReportParams>")
                  _T("</CdrReport>");
    CString r = CdrSocket::sendCommand(cmd);
    cdr::Element e = cdr::Element::extractElement(r, _T("PatientSummary"));
    CString patientId;
    if (e)
        patientId = e.getString();
    else
        cdr::showErrors(r);
    patientId.SetSysString(patientDocId);

    return S_OK;
}

void clearErrorList() {
    _Document doc = cdr::getApp().GetActiveDocument();
    if (doc) {
        CString path = getFullDocPath(&doc);
        if (!path.IsEmpty()) {
            cdr::ValidationErrorSets::iterator iter =
                cdr::validationErrorSets.find(path);
            if (iter != cdr::validationErrorSets.end()) {
                delete iter->second;
                cdr::validationErrorSets.erase(iter);
            }
        }
    }
}

STDMETHODIMP CCommands::getNextValidationError(BSTR* valError)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("getNextValidationError");
    CString result;
    _Document doc = cdr::getApp().GetActiveDocument();
    if (!doc) {
        result = _T("0|No document is currently active");
        result.SetSysString(valError);
        return S_OK;
    }
    CString path = getFullDocPath(&doc);
    if (path.IsEmpty()) {
        result = _T("0|No validation results available");
        result.SetSysString(valError);
        return S_OK;
    }
    cdr::ValidationErrorSets::iterator iter =
        cdr::validationErrorSets.find(path);
    if (iter == cdr::validationErrorSets.end()) {
        result = _T("0|No validation results available");
        result.SetSysString(valError);
        return S_OK;
    }
    cdr::ValidationErrors* errors = iter->second;
    if (errors->errors.size() < 1) {
        result = _T("0|No validation errors found");
        result.SetSysString(valError);
        return S_OK;
    }
    if (errors->currentError >= errors->errors.size()) {
        result = _T("0|No more validation errors found");
        result.SetSysString(valError);
        return S_OK;
    }
    const cdr::ValidationError* error = errors->getNextError();
    if (!error) {
        result = _T("0|No more validation errors found");
        result.SetSysString(valError);
        return S_OK;
    }
    CString eid = error->eid;
    if (eid.IsEmpty())
        eid = _T("0");
    result = eid + _T("|") + error->message;
    if (!error->elevel.IsEmpty())
        result += _T(" (") + error->elevel + _T(")");
    result.SetSysString(valError);
    return S_OK;
}

STDMETHODIMP CCommands::logClientEvent(const BSTR* description, int* pRet) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("logClientEvent");
    *pRet = 0;
    CString desc(*description);
    CString cmd = _T("<CdrLogClientEvent><EventDescription>")
                + cdr::encode(desc)
                + _T("</EventDescription></CdrLogClientEvent>");
    CString r = CdrSocket::sendCommand(cmd);
    cdr::Element e = cdr::Element::extractElement(r, _T("EventId"));
    if (e) {
        LPCTSTR p = (LPCTSTR)e.getString();
        *pRet = (int)_tcstol(p, 0, 10);
    }
    else
        cdr::showErrors(r);

    return S_OK;
}

STDMETHODIMP CCommands::getBoardMemberId(const BSTR* personId,
                                         BSTR* boardMemberId)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("getBoardMemberId");
    CString id(*personId);
    CString cmd = _T("<CdrReport>")
                  _T("<ReportName>Board Member</ReportName>")
                  _T("<ReportParams><ReportParam ")
                  _T("Name='PersonId' ")
                  _T("Value='") + id + _T("'/></ReportParams>")
                  _T("</CdrReport>");
    CString r = CdrSocket::sendCommand(cmd);
    cdr::Element e = cdr::Element::extractElement(r, _T("BoardMember"));
    CString boardMember;
    if (e)
        boardMember = e.getString();
    else
        cdr::showErrors(r);
    boardMember.SetSysString(boardMemberId);

    return S_OK;
}

STDMETHODIMP CCommands::editComment(VARIANT_BOOL readOnly)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("editComment");
    BOOL ro(readOnly);
    ::CCommentDialog dialog(ro);
    dialog.DoModal();

    return S_OK;
}

/*
 * Ask the CDR Server to find the values found at a specified
 * path in a specific CDR document.  Returns the list of values
 * in a single string, using the ASCII RS (record separator)
 * as delimiter between the values, since this control character
 * is not permitted in XML documents.  If it's possible to
 * return an array of strings from a COM object, I was unable
 * to find documentation for this feature.
 */
STDMETHODIMP CCommands::valuesForPath(const BSTR* docId, const BSTR* path,
                                      BSTR* values)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("valuesForPath");
    CString RS = _T("\x0E");
    CString id(*docId);
    CString p(*path);
    CString request;
    request.Format(
        _T("<CdrReport><ReportName>Values For Path</ReportName>")
        _T("<ReportParams>")
        _T("<ReportParam Name='DocId' Value='%s'/>")
        _T("<ReportParam Name='Path' Value='%s'/>")
        _T("</ReportParams></CdrReport>"), id, p);
    CString resp = CdrSocket::sendCommand(request);
    CString result = _T("");
    CString sep = _T("");
    cdr::Element e = cdr::Element::extractElement(resp, _T("Value"));
    while (e) {
        result += sep + e.getString();
        sep = RS;
        e = cdr::Element::extractElement(resp, _T("Value"), e.getEndPos());
    }
    result.SetSysString(values);

    return S_OK;
}


STDMETHODIMP CCommands::get_userPath(BSTR* pVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("get_userPath");
    CString userPath = cdr::getUserPath();
    userPath.SetSysString(pVal);

    return S_OK;
}

/*
 * Support for fetching information from the CDR web server.  Allows
 * us to implement simpler enhancements which would otherwise require
 * a rebuild of the CDR server.
 */
STDMETHODIMP CCommands::fetchFromUrl(const BSTR* url_, BSTR* response_) {

    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("fetchFromUrl");
    CString url(*url_);
    CString response;
    try {
        response = cdr::fetchFromUrl(url);
    }
    catch (...) {
        ::AfxMessageBox(_T("Unable to open ") + url, MB_ICONEXCLAMATION);
        response = _T("");
    }
    response.SetSysString(response_);

    return S_OK;
}

/*
 * Let the user choose which revision level to apply to the selected
 * elements.
 */
STDMETHODIMP CCommands::chooseRevisionLevel(BSTR* response_) {

    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    cdr::trace_log("chooseRevisionLevel");
    CString level;
    try {
        RevisionLevel dialog;
        if (dialog.DoModal() == IDOK) {
            switch (dialog.mRevisionLevel) {
            case 3:
                level = _T("rejected");
                break;
            case 2:
                level = _T("publish");
                break;
            case 1:
                level = _T("proposed");
                break;
            default:
            case 0:
                level = _T("approved");
            }
        }
    }
    catch (...) {
        ::AfxMessageBox(_T("Internal error selecting revision level"));
    }
    level.SetSysString(response_);

    return S_OK;
}
