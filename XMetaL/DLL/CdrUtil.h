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
    CString doc_type;
    CString doc_id;
    CString doc_title;
    bool    blocked;
    bool    ready_for_review;
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
         *
         *  @param xml - Unicode string containing a serialized document
         */
        DOM(const CString& xml);

        /**
         * Create a DOM object with just a root element.
         *
         *  @param root_name - ASCII c-style string for the root element's name
         *                     (don't use wchar_t* or CString, because that
         *                     will route to the previous constructor)
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
         *
         *  @param parent - pointer to the parent node we attach to
         *  @param child  - pointer to the node being attached to the parent
         */
        void append(IXMLDOMNode* parent, IXMLDOMNode* child);

        /**
         * Attach a text node to an existing element.
         *
         *  @param parent - pointer to the parent node we attach to
         *  @param text   - Unicode string for the value being attached
         */
        void append_text(IXMLDOMNode* parent, const CString& text);

        /**
         * Create a new element attached to an existing parent.
         *
         *  @param parent - pointer to the parent node we attach to
         *  @param name   - string for the new element's name
         *  @param text   - optional string value to be used to set the
         *                  text content of the new element
         *  @return       - `CComPtr` for newly created element
         */
        Element child_element(IXMLDOMNode* parent,
                              const CString& name,
                              const CString& text = L"");

        /**
         * Create a new element with optional text content.
         *
         * The new element is not attached to any parent.
         *
         *  @param name   - string for the new element's name
         *  @param text   - optional string value to be used to set the
         *                  text content of the new element
         *  @return       - `CComPtr` for newly created element
         */
        Element element(const CString& name, const CString& text = L"");

        /**
         * Find a single element matching the supplied XPath string.
         *
         * If no element is specified, the search if from the root element.
         *
         *  @param xpath - string for the search
         *  @param from  - optional node from which to start the search
         *  @return      - `CComPtr` for found element or `nullptr` if none
         */
        Element find(const CString& xpath, IXMLDOMElement* from = nullptr);

        /**
         * Find all elements matching the supplied XPath string.
         *
         * If no element is specified, the search if from the root element.
         *
         *  @param xpath - string for the search
         *  @param from  - optional node from which to start the search
         *  @return      - sequence of `CComPtr`s for matching elements
         */
        std::vector<Element> find_all(const CString& xpath,
                                      IXMLDOMElement* from = nullptr);

        /**
         * Get the value of an element's attribute.
         *
         *  @param elem - pointer to the element whose attribute value we want
         *  @param name - string naming the attribute whose value we want
         *  @return     - string for attribute value
         */
        CString get(IXMLDOMElement* elem, const CString& name);

        /**
         * Get the string for a specific DOM node's name.
         *
         *  @param node - address of the DOM node whose name we want
         *  @return     - node name string
         */
        CString get_node_name(IXMLDOMNode* node);

        /**
         * Give the caller a pointer to the root element.
         *
         *  @return - `CComPtr` for the root element
         */
        Element get_root();

        /**
         * Get the text content string for a specific element.
         *
         *  @param node - address of DOM node whose text content we want
         *  @return     - text content for element node
         */
        CString get_text(IXMLDOMNode* node);

        /**
         * Serialize the document to an XML string.
         *
         *  @param node - address of DOM node whose XML serialization we want
         *  @return     - string for the serialized node
         */
        CString get_xml(IXMLDOMNode* = nullptr) const;

        /**
         * Install a node in front of an existing node.
         *
         *  @param parent   - pointer to the parent node we attach to
         *  @param new_node - pointer to the node we are inserting
         *  @param sibling  - pointer to the node in front of which we insert
         */
        void insert(IXMLDOMNode* parent, IXMLDOMNode* new_node,
                    IXMLDOMNode* sibling);

        /**
         * Assign a string value to a named attribute of an element.
         *
         *  @param element - address of the element whose attribute we set
         *  @param name    - string for the name of the attribute to be set
         *  @param value   - string for the value we assign to the attribute
         */
        void set(IXMLDOMElement* element, const CString& name,
                 const CString& value);

        /**
         * Make an existing element node the new root of the DOM document.
         *
         *  @param new_root - address of the element which will be the new root
         */
        void set_root(IXMLDOMElement* new_root);

    protected:

        /**
         * The DOM tree for the XML document.
         */
        Document doc;

        /**
         * The top-level element for the document (the "document element").
         */
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
         * Modifications include:
         *  - removal of the `CdrDocCtl` block
         *  - stripping of any `readonly` attributes
         *
         *  @param parent   - the node in the `CommandSet` DOM to which a
         *                    CDATA section will be attached with the doc XML
         *  @param original - serialized XML for XMetaL's active document
         */
        void add_cdr_document(IXMLDOMElement* parent, const CString& original);

        // The child of `CdrCommand` node for the specific command.
        Element command;
    };

    // Forward reference.
    struct GlossaryNode;

    // Map of words in glossary terms to the terms from which they come.
    typedef std::map<CString, GlossaryNode*> GlossaryNodeMap;
    struct GlossaryNode {
        int             doc_id;
        bool            marked_up;
        GlossaryNodeMap node_map;
        GlossaryNode() : doc_id(0), marked_up(false) {}
        ~GlossaryNode() {
            for (auto& n : node_map)
                delete n.second;
        }
        void clear_flags() {
            marked_up = false;
            for (auto& n : node_map)
                n.second->clear_flags();
        }
    };
    struct GlossaryTree {
        GlossaryTree(const CString& language, const CString& dictionary);
        ~GlossaryTree();
        void clear_flags() {
            for (auto& n : node_map)
                n.second->clear_flags();
        }
        GlossaryNodeMap node_map;

        // Map of CDR GlossaryTermName document to preferred name string.
        std::map<int, CString> names;
    };

    /**
     * Cached glossary tree maps.
     */
    struct GlossaryTrees {
        typedef std::map<CString, cdr::GlossaryTree*> Cache;
        ~GlossaryTrees();
        static GlossaryTree* get_glossary_tree(const CString&, const CString&);
        static Cache cache;
    };

    class SearchResult {
    public:
        SearchResult(const CString& id,
                     const CString& type = L"",
                     const CString& title = L"",
                     bool           grp = false,
                     const CString& memb = L"",
                     const LinkInfoList& pi_list = LinkInfoList()) :
                        doc_id(id),
                        doc_type(type),
                        doc_title(title),
                        group(grp),
                        coop_membership(memb),
                        principal_investigators(pi_list) {}
        CString get_doc_id()              const { return doc_id; }
        CString get_doc_type()            const { return doc_type; }
        CString get_doc_title()           const { return doc_title; }
        bool    is_group()                const { return group; }
        CString get_coop_membership()     const { return coop_membership; }
        const LinkInfoList& get_pi_list() const
            { return principal_investigators; }
        bool operator==(const SearchResult& sr) const
            { return sr.doc_id == doc_id; }
    private:
        CString         doc_id;
        CString         doc_type;
        CString         doc_title;
        bool            group;
        CString         coop_membership;
        LinkInfoList    principal_investigators;

    };
    typedef std::list<SearchResult> DocSet;

    // Used to find size of image.
    struct ImageDimensions {
        unsigned long height;
        unsigned long width;
    };

    /**
     * Wrapper for socket communication between the CDR client and server.
     *
     * Raw sockets replaced along the way with tunneling through HTTPS (at
     * the insistence of CBIIT), but we kept the name for old times' sake. :-)
     * Now that we're not using sockets directly, we no longer need object
     * instances of this class: everything is static (class-based) now.
     *
     * There are two host names. One (`api_host`) is used for tunneling
     * CDR client-server commands and the other (`cdr_host`) is used to
     * build links to web admin HTML pages.
     */
    class Socket {
    public:
        static CString send_commands(const CommandSet&, char* = nullptr);
        static void set_session_string(const CString& s) { session_string = s; }
        static bool logged_on() { return !session_string.IsEmpty(); }
        static const CString get_session_string() { return session_string; }
        static const CString get_host_name() { return cdr_host; }
        static const CString get_host_tier() { return tier; }
        static CString get_short_host_name() {
            int dot = cdr_host.Find(L'.');
            if (dot != -1 && !iswdigit(cdr_host[0]))
                return cdr_host.Left(dot);
            return cdr_host;
        }
    private:
        struct Init {
            Init();
            ~Init();
            WSAData wsa_data;
            static Init init;
        };
        static CString session_string;
        static CString cdr_host;
        static CString api_host;
        static CString tier;
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
        size_t current_error;
        std::vector<ValidationError> errors;
        const ValidationError* get_next_error() {
            if (current_error >= errors.size())
                return NULL;
            return &errors[current_error++];
        }
    };
    typedef std::map<CString, cdr::ValidationErrors*> ValidationErrorSets;
    extern ValidationErrorSets validation_error_sets;

    // Common utility functions.
    std::string cstring_to_utf8(const CString& str);
    void debug_log(const CString& what, const CString& who = L"bkline");
    CString doc_id_string(int);
    CString expand_leading_zeros(const CString&);
    void extract_ctl_info(DOMNode node, CdrDocCtrlInfo& info);
    CString extract_element_text(DOMNode node);
    CdrLinkInfo extract_link_info(const CString& str);
    void extract_search_results(DOM& dom, DocSet& docSet);
    CString fetch_from_url(const CString&);
    int fill_list_box(CListBox& listBox, const DocSet& docSet);
    ::Range find_or_create_child(::Range parent, const CString& elemName);
    _Application get_app();
    int get_audio_seconds(CFile& file);
    const char* get_cdr_trace_log_path();
    unsigned long get_doc_no(const CString& docString);
    ::Range get_elem_range(const CString& elemName);
    bool get_image_dimensions(CFile& file, ImageDimensions& dim);
    CString get_user_path();
    CString get_xmetal_path();
    bool replace_element_content(::DOMElement&, const CString&);
    void send_trace_log();
    bool show_errors(DOM& response);
    int show_page(const CString& url);
    bool show_validation_errors(ValidationErrors&);
    CString suppress_leading_zeros(const CString&);
    void trace_log(const char* what);
    CString trim(const CString& s);
    CString utf8_to_cstring(const char* s);
}

#endif
