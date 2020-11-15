/*
 * Common utility classes and functions for CDR DLL used to customize XMetaL.
 *
 * BZIssue::4767
 */

#ifndef CDR_UTIL_H_
#define CDR_UTIL_H_

// Local headers.
#include "stdafx.h"
#include "xmetal90.h"

// System headers.
#include <string>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <winsock.h>

#define BLOB_PLACEHOLDER "@@BLOB-PLACEHOLDER@@"

// Information used to populate the CdrDocCtl element.
struct CdrDocCtrlInfo {
    CString docType;
    CString docId;
    CString docTitle;
    bool    blocked;
    bool    readyForReview;
};

// Link ID, title, etc.
struct CdrLinkInfo {
    CdrLinkInfo(const CString& t, const CString& d) : target(t), data(d) {}
    CdrLinkInfo() {}
    CString target;
    CString data;
};


namespace cdr {

    // Useful types.
    typedef std::list<CString> StringList;
    typedef std::set<CString> StringSet;
    typedef std::map<CString, StringSet> ElementSets;
    typedef std::map<CString, StringList> ValidValueSet;
    typedef std::map<CString, ValidValueSet> ValidValueSets;
    typedef std::list<CdrLinkInfo> LinkInfoList;


    /**
     * You would think we could just use the DOM functionality exposed
     * by SoftQuad, but unfortunately, their implementation is broken.
     * Cloning the document fails, and getting the serialized XML for
     * a DOM node isn't supported. So here is our own wrapper for MSXML.
     */
    class DOM {
    public:

        /**
         * Useful type definitions.
         */
        typedef CComPtr<IXMLDOMDocument> Document;
        typedef CComPtr<IXMLDOMElement> Element;
        typedef CComPtr<IXMLDOMNode> Node;
        typedef CComPtr<IXMLDOMNodeList> NodeList;

        /**
         * Initialize the DOM.
         */
        DOM();

        /**
         * Create the DOM object from its serialized XML.
         */
        DOM(const CString& xml);

        /**
         * Create a DOM object with just a root element.
         */
        DOM(const char* root_name);

        /**
         * Prohibit copy construction or assignment by value.
         *
         * If you really need to pass around this object between
         * functions or methods, do it by reference or pointer.
         */
        DOM(const DOM&) = delete;
        DOM& operator=(const DOM&) = delete;

        /**
         * Attach an element to an existing parent.
         */
        void append(IXMLDOMNode* parent, IXMLDOMNode* child);

        /**
         * Attach a text node to an existing element.
         */
        void append_text(IXMLDOMNode* parent, const CString& text);

        /**
         * Create a new element attached to an existing parent.
         *
         * You can submit an optional third argument to set
         * the new child element's text content.
         */
        Element child_element(IXMLDOMNode* parent,
                              const CString& name,
                              const CString& text = L"");

        /**
         * Create a new element with optional text content.
         *
         * The new element is not attached to any parent.
         */
        Element element(const CString& name, const CString& text = L"");

        /**
         * Find a single element matching the supplied XPath string.
         *
         * If no element is specified, the search if from the root element.
         */
        Element find(const CString& xpath, IXMLDOMElement* from = nullptr);

        /**
         * Find all elements matching the supplied XPath string.
         *
         * If no element is specified, the search if from the root element.
         */
        std::vector<Element> find_all(const CString& xpath,
                                      IXMLDOMElement* from = nullptr);

        /**
         * Get the value of an element's attribute.
         */
        CString get(IXMLDOMElement* elem, const CString& name);

        /**
         * Get the string for a specific DOM node's name.
         */
        CString get_node_name(IXMLDOMNode* node);

        /**
         * Give the caller a pointer to the root element.
         */
        Element get_root();

        /**
         * Get the text content string for a specific element.
         */
        CString get_text(IXMLDOMNode* node);

        /**
         * Serialize the document to an XML string.
         */
        CString get_xml(IXMLDOMNode* = nullptr) const;

        /**
         * Install a node in front of an existing node.
         */
        void insert(IXMLDOMNode* parent, IXMLDOMNode* new_node,
                    IXMLDOMNode* sibling);

        /**
         * Assign a string value to a named attribute of an element.
         */
        void set(IXMLDOMElement* element, const CString& name,
                 const CString& value);

        /**
         * Make an existing element node the new root of the DOM document.
         */
        void set_root(IXMLDOMElement* new_root);

    protected:

        /**
         * Internal values.
         */
        Document doc;
        Element root;
    };

    /**
     * Shell for a set of commands to be sent to the CDR server.
     */
    class CommandSet : public DOM {
    public:

        /**
         * Create a DOM builder for a CdrCommandSet XML document.
         *
         * Pass the name of the first (and likely only) command in the set.
         */
        CommandSet(const char* name);

        /**
         * Add a modified copy of the active document to the DOM.
         *
         *  @param parent   - the node in the `CommandSet` DOM to which a
         *                    CDATA section will be attached with the doc XML
         *  @param original - serialized XML for XMetaL's active document
         */
        void add_cdr_document(IXMLDOMElement* parent, const CString& original);

        // The child of `CdrCommand` node for the specific command.
        Element command;
    };


    struct GlossaryNode;
    typedef std::map<CString, GlossaryNode*> GlossaryNodeMap;
    struct GlossaryNode {
        int             docId;
        bool            markedUp;
        GlossaryNodeMap nodeMap;
        GlossaryNode() : docId(0), markedUp(false) {}
        ~GlossaryNode() {
            for (auto& n : nodeMap)
                delete n.second;
        }
        void clearFlags() {
            markedUp = false;
            for (auto& n : nodeMap)
                n.second->clearFlags();
        }
    };
    struct GlossaryTree {
        GlossaryTree(const CString& language, const CString& dictionary);
        ~GlossaryTree();
        void clearFlags() {
            for (auto& n : nodeMap)
                n.second->clearFlags();
        }
        GlossaryNodeMap nodeMap;

        // TODO: useless, drop.
        std::vector<int> counts;

        // Map of CDR GlossaryTermName document to preferred name string.
        std::map<int, CString> names;
    };
    GlossaryTree* getGlossaryTree(const CString& language,
                                  const CString& dictionary);

    class SearchResult {
    public:
        SearchResult(const CString& id,
                     const CString& type = L"",
                     const CString& title = L"",
                     bool           grp = false,
                     const CString& cMemb = L"",
                     const LinkInfoList& piList = LinkInfoList()) :
                        docId(id),
                        docType(type),
                        docTitle(title),
                        group(grp),
                        coopMembership(cMemb),
                        principalInvestigators(piList) {}
        CString getDocId()    const { return docId; }
        CString getDocType()  const { return docType; }
        CString getDocTitle() const { return docTitle; }
        bool    isGroup()     const { return group; }
        CString getCoopMemb() const { return coopMembership; }
        const LinkInfoList& getPiList() const { return principalInvestigators; }
        bool    operator==(const SearchResult& sr)  const
            { return sr.docId == docId; }
    private:
        CString         docId;
        CString         docType;
        CString         docTitle;
        bool            group;
        CString         coopMembership;
        LinkInfoList    principalInvestigators;

    };
    typedef std::list<SearchResult> DocSet;

    // Used to find size of image.
    struct ImageDimensions {
        unsigned long height;
        unsigned long width;
    };

    // Set of errors returned from CDR document validation.
    // Document.Path used to index into validation error sets.
    struct ValidationError {
        ValidationError::ValidationError(const CString& m, const CString& id,
                                         const CString& level)
            : message(m), eid(id), elevel(level) {}
        CString message;
        CString eid;
        CString elevel;
    };
    struct ValidationErrors {
        ValidationErrors::ValidationErrors(DOM&);
        size_t currentError;
        std::vector<ValidationError> errors;
        const ValidationError* getNextError() {
            if (currentError >= errors.size())
                return NULL;
            return &errors[currentError++];
        }
    };
    typedef std::map<CString, cdr::ValidationErrors*> ValidationErrorSets;
    extern ValidationErrorSets validationErrorSets;

    // Common utility functions.
    std::string cStringToUtf8(const CString& str);
    CString decode(CString str);
    CString docIdString(int);
    CString expandLeadingZeros(const CString&);
    void extractCtlInfo(DOMNode node, CdrDocCtrlInfo& info);
    CString extractElementText(DOMNode node);
    CdrLinkInfo extractLinkInfo(const CString& str);
    void extractSearchResults(DOM& dom, DocSet& docSet);
    CString fetchFromUrl(const CString&);
    int fillListBox(CListBox& listBox, const DocSet& docSet);
    ::Range findOrCreateChild(::Range parent, const CString& elemName);
    _Application getApp();
    int getAudioSeconds(CFile& file);
    unsigned long getDocNo(const CString& docString);
    ::Range getElemRange(const CString& elemName);
    bool getImageDimensions(CFile& file, ImageDimensions& dim);
    const char* get_cdr_trace_log_path();
    CString getXmetalPath();
    CString getUserPath();
    CString encode(CString str, bool fixQuotes = false);
    bool replaceElementContent(::DOMElement&, const CString&);
    void send_trace_log();
    bool showErrors(DOM& response);
    int showPage(const CString& url);
    bool showValidationErrors(ValidationErrors&);
    CString suppressLeadingZeros(const CString&);
    void trace_log(const char* what);
    CString trim(const CString& s);
    CString utf8ToCString(const char* s);
}

/**
 * Wrapper for socket communication between the CDR client and server.
 *
 * Raw sockets replaced along the way with tunneling through HTTPS (at
 * the insistence of CBIIT), but we kept the name for old times' sake. :-)
 * Now that we're not using sockets directly, we no longer need object
 * instances of this class: everything is static (class-based) now.
 *
 * There are two host names. One (`apiHost`) is used for tunneling
 * CDR client-server commands and the other (`cdrHost`) is used to
 * build links to web admin HTML pages.
 */
class CdrSocket {
public:
    static CString sendCommands(const cdr::CommandSet&, char* = nullptr);
    static void setSessionString(const CString& s) { sessionString = s; }
    static bool loggedOn() { return !sessionString.IsEmpty(); }
    static const CString getSessionString() { return sessionString; }
    static const CString getHostName() { return cdrHost; }
    static const CString getHostTier() { return tier; }
    static CString getShortHostName() {
        int dot = cdrHost.Find(TCHAR('.'));
        if (dot != -1 && !_istdigit(cdrHost[0]))
            return cdrHost.Left(dot);
        return cdrHost;
    }
private:
    struct Init {
        Init();
        ~Init();
        WSAData wsaData;
        static Init init;
    };
    static CString sessionString;
    static CString cdrHost;
    static CString apiHost;
    static CString tier;
};

extern void debug_log(const CString& what, const CString& who = L"bkline");

#if 0
std::basic_ostream<TCHAR>& operator<<(std::basic_ostream<TCHAR>& os,
                                      DOMNode& node);
#endif
#endif
