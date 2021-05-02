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
#include "cdrdom.h"

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
     * Wrapper around base class, picking up the session ID.
     *
     * This piece of the functionality was factored out in order to be
     * able to test the base class without introducing dependencies in
     * the test harness on the "Socket" class and its dependencies.
     */
    class CommandSet : public CommandSetBase {
    public:
        CommandSet(const char* name);
    };

    // Forward reference.
    struct GlossaryNode;

    // Map of words in glossary terms to the terms from which they come.
    typedef std::map<CString, GlossaryNode*> GlossaryNodeMap;

    /**
     * Representation of a single word token found in all of the glossary
     * term phrases which share the same N initial words, where this word
     * is the Nth word in those phrases. If there are more words to come
     * in any given phrase, the next word in the phrase will be found as
     * a key in this node's node_map, so the phrases are represented by
     * linked chains of `GlossaryNode` objects. If a given word is the
     * final (possibly only) word in a glossary term phrase, its GlossaryNode
     * object will have the `doc_id` member set to the `GlossaryTermName`
     * document's CDR ID. Otherwise that member will be set to 0.
     *
     * For example, imagine glossary which contained only three terms:
     *   CDR12345 cancer
     *   CDR12346 cancer diagnosis
     *   CDR12346 cancer prevention
     *
     * The `node_map` member of the `GlossaryTree` object for that glossary
     * would have a single entry, indexed by the string "CANCER" (the name
     * tokens are normalized to ignore case). The `GlossaryTerm` value for
     * that entry would have the `doc_id` member set to 12345 (because the
     * first term's final (and only) normalized word is "CANCER"), and its
     * own `node_map` would have two entries, indexed by "DIAGNOSIS" and
     * "PREVENTION" respectively, with the `doc_id` of the `GlossaryNode`
     * values for those entries set to 12346 or 12347, representing the
     * second and third terms in the glossary. The `node_map` members for
     * those two entries would be empty.
     *
     * We also track whether a term has already been used to "glossify"
     * a matching string in the section of a document being edited, so the
     * user can have the software skip over subsequent occurrence of the
     * term within that section of the document. When we move to the next
     * section of the document, or to an entirely different document, we
     * clear out those `marked_up` flags so we can start afresh.
     */
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
        GlossaryTree(const CString& language, const CString& dictionary,
                     const CString& audience);
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
        static GlossaryTree* get_glossary_tree(const CString&, const CString&,
                                               const CString&);
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
    const CString& get_user_path();
    const CString& get_xmetal_path();
    CString serialize(_Document* doc);
    bool replace_element_content(::DOMElement&, const CString&);
    void send_trace_log();
    bool show_errors(DOM& response);
    int show_page(const CString& url);
    void trace_log(const char* what);
    CString trim(const CString& s);
    CString utf8_to_cstring(const char* s);
}

#endif
