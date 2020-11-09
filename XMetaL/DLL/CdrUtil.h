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
    static CString sendCommand(const CString& command, bool = false,
                               char* cmdBuf = NULL);
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

/**
 * XML parsing on the cheap.  Replace with the real thing if necessary.
 * We considered linking in Microsoft's XML DOM libraries, but we were
 * a little apprehensive about problems we might run into if XMetaL is
 * using those libraries underneath its own APIs, and isn't careful
 * about playing nice with other threads and code which might call
 * the Microsoft libraries directly.  Unfortunately, SoftQuad didn't
 * document its use of an underlying XML parser, and didn't expose
 * a parse function we could use for our own XML documents.  At the
 * time this code was first written, Microsoft's XML libraries were
 * young enough, and our own experience with green Microsoft libraries
 * painful enough, that we consciously made the decision to roll
 * our own "parser" and use it for what we get back from the CDR
 * client/server interface.  As cheesy as the results are, this
 * has worked flawlessly for years, and shouldn't involve an enormous
 * amount of work to replace with a real parser in the (now) unlikely
 * event that compelling incentives for doing so come along.
 *
 * In particular, note that a limitation of this parser is that
 * it does not handle nested elements with the same name correctly.
 * The DLL does not currently need support for such constructions,
 * but if we ever do, we'll need to switch to a real XML parser.
 */
class TinyXmlParser {
public:
    TinyXmlParser(const CString& s) : xml(s) {}
    CString extract(const CString& tag) const;
private:
    CString xml;
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
     * Wrapper for DOM approach to building up XML documents.
     *
     * Enapsulates most of the COM ugliness. All of the resources
     * for elements/attributes added to the document are owned
     * and managed by this object.
     */
    class DOMBuilder {
    public:

        /**
         * Create a new COM object for creating a document.
         *
         * If you optionally pass an element name string, it will
         * be used to start the document off with its root element.
         */
        DOMBuilder(const CString& name = _T(""));

        /**
         * Prohibit copy construction or assignment by value.
         *
         * If you really need to pass around this object between
         * functions or methods, do it by reference or pointer.
         * We can't have the resources managed by the object
         * duplicated.
         */
        DOMBuilder(const DOMBuilder&) = delete;
        DOMBuilder& operator=(const DOMBuilder&) = delete;

        /**
         * Clean up the resources, releasing the COM handles we own.
         */
        ~DOMBuilder();

        /**
         * Create a new element with optional text content.
         *
         * The new element is not attached to any parent.
         */
        IXMLDOMElement* element(const CString& name,
                                const CString& text = _T(""));

        /**
         * Assign a string value to a named attribute of an element.
         */
        void set(IXMLDOMElement* element, const CString& name,
                 const CString& value);

        /**
         * Attach an element to an existing parent.
         */
        void append(IXMLDOMNode* parent, IXMLDOMNode* child);

        /**
         * Create a new element attached to an existing parent.
         *
         * You can submit an optional third argument to set
         * the new child element's text content.
         */
        IXMLDOMElement* child_element(IXMLDOMNode* parent,
                                      const CString& name,
                                      const CString& text=_T(""));

        /**
         * Attach a text node to an existing element.
         */
        void append_text(IXMLDOMNode* parent, const CString& text);

        /**
         * Serialize the document to an XML string.
         */
        CString get_xml() const;

        /**
         * Provide the caller with a handle to the document's root element.
         */
        IXMLDOMElement* get_root() { return root; }

    private:

        /**
         * Resources we need to clean up when we're done.
         */
        IXMLDOMDocument* doc;
        IXMLDOMElement* root;
        std::vector<IXMLDOMNode*> nodes;
    };


    /**
     * Wrapper for parsing XML from an in-memory string.
     *
     * Enapsulates most of the COM ugliness. All of the resources
     * for elements/attributes added to the document are owned
     * and managed by this object.
     */
    class ParsedDOM {
    public:

        /**
         * Create the DOM object from its serialized XML.
         */
        ParsedDOM(const CString& xml);

        /**
         * Prohibit copy construction or assignment by value.
         *
         * If you really need to pass around this object between
         * functions or methods, do it by reference or pointer.
         * We can't have the resources managed by the object
         * duplicated.
         */
        ParsedDOM(const ParsedDOM&) = delete;
        ParsedDOM& operator=(const ParsedDOM&) = delete;

        /**
         * Clean up the resources, releasing the COM handles we own.
         */
        ~ParsedDOM();

        /**
         * Find a single element matching the supplied XPath string.
         */
        IXMLDOMElement* find(const CString& xpath);

        /**
         * Find all elements matching the supplied XPath string.
         */
        std::vector<IXMLDOMElement*> find_all(const CString& xpath);

        /**
         * Give the caller a pointer to the root element.
         */
        IXMLDOMElement* get_root();

        /**
         * Get the text content string for a specific element.
         */
        CString get_text(IXMLDOMElement* element);

        /**
         * Get the string for a specific DOM node's name.
         */
        CString get_node_name(IXMLDOMNode* node);

        /**
         * Get the value of an element's attribute.
         */
        CString get(IXMLDOMElement* elem, const CString& name);

    private:

        /**
         * Resources we need to clean up when we're done.
         */
        IXMLDOMDocument* doc;
        IXMLDOMElement* root;
        std::vector<IXMLDOMNode*> nodes;
    };

    struct GlossaryNode;
    typedef std::map<CString, GlossaryNode*> GlossaryNodeMap;
    struct GlossaryNode {
        int             docId;
        bool            markedUp;
        GlossaryNodeMap nodeMap;
        GlossaryNode() : docId(0), markedUp(false) {}
        ~GlossaryNode() {
            // std::cout << "~GlossaryNode\n";
            GlossaryNodeMap::iterator i = nodeMap.begin();
            while (i != nodeMap.end()) {
                // std::cout << "deleting node for " << i->first << '\n';
                delete i->second;
                ++i;
            }
        }
        void clearFlags() {
            markedUp = false;
            GlossaryNodeMap::iterator i = nodeMap.begin();
            while (i != nodeMap.end()) {
                i->second->clearFlags();
                ++i;
            }
        }
    };
    struct GlossaryTree {
        GlossaryTree(const CString& command);
        ~GlossaryTree();
        void clearFlags() {
            GlossaryNodeMap::iterator i = nodeMap.begin();
            while (i != nodeMap.end()) {
                i->second->clearFlags();
                ++i;
            }
        }
        GlossaryNodeMap nodeMap;
        std::vector<int> counts;
        std::map<int, CString> names;
    };
    GlossaryTree* getGlossaryTree(const CString& language,
                                  const CString& dictionary);

    class SearchResult {
    public:
        SearchResult(const CString& id,
                     const CString& type = _T(""),
                     const CString& title = _T(""),
                     bool           grp = false,
                     const CString& cMemb = _T(""),
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

    class Element {
    public:
        static Element extractElement(const CString&,
                                      const CString&,
                                      int pos = 0);
        CString getString() const { return str; }
        int     getStartPos() const { return startPos; }
        int     getEndPos() const { return endPos; }
        CString getAttribute(const CString& name) const;
        CString getCdataSection() const;
        operator void*() const { return startPos != endPos ? (void *)this : 0; }
        int  operator!() const { return startPos == endPos; }
    private:
        typedef std::map<CString, CString> Attrs;
        Element() : startPos(0), endPos(0) {}
        Attrs   attrs;
        CString str;
        int     startPos;
        int     endPos;
    };

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
        ValidationErrors::ValidationErrors(const cdr::Element&);
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
    int fillListBox(CListBox& listBox, const DocSet& docSet);
    void extractSearchResults(const CString& xml, DocSet& docSet);
    bool showErrors(const CString& msg);
    bool showValidationErrors(ValidationErrors&);
    _Application getApp();
    CString getXmetalPath();
    CString getUserPath();
    CString encode(CString str, bool fixQuotes = false);
    CString decode(CString str);
    unsigned long getDocNo(const CString& docString);
    CString extractElementText(DOMNode node);
    CString trim(const CString& s);
    void extractCtlInfo(DOMNode node, CdrDocCtrlInfo& info);
    CString utf8ToCString(const char* s);
    std::string cStringToUtf8(const CString& str);
    CdrLinkInfo extractLinkInfo(const CString& str);
    ::Range getElemRange(const CString& elemName);
    ::Range findOrCreateChild(::Range parent, const CString& elemName);
    CString docIdString(int);
    int showPage(const CString& url);
    CString suppressLeadingZeros(const CString&);
    CString expandLeadingZeros(const CString&);
    bool replaceElementContent(::DOMElement&, const CString&);
    bool getImageDimensions(CFile& file, ImageDimensions& dim);
    int getAudioSeconds(CFile& file);
    CString fetchFromUrl(const CString&);
    void trace_log(const char* what);
    void send_trace_log();
    const char* get_cdr_trace_log_path();
}

std::basic_ostream<TCHAR>& operator<<(std::basic_ostream<TCHAR>& os,
                                      DOMNode& node);

#endif
