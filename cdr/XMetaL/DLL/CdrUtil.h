/*
 * $Id: CdrUtil.h,v 1.14 2004-02-26 01:57:25 bkline Exp $
 *
 * Common utility classes and functions for CDR DLL used to customize XMetaL.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.13  2004/02/26 01:47:16  bkline
 * Added glossifier support; upgraded to XMetaL 4 APIs.
 *
 * Revision 1.12  2004/02/26 00:46:33  bkline
 * Added code for suppressing/expanding leading zeros in document IDs.
 *
 * Revision 1.11  2002/10/15 22:22:05  bkline
 * Adding code for issue #471.
 *
 * Revision 1.10  2002/10/04 16:42:42  bkline
 * Added my own showPage method, to get around the buggy version in XMetaL.
 *
 * Revision 1.9  2002/08/12 20:19:51  bkline
 * Added destructor for CdrSocket class to close the socket.
 *
 * Revision 1.8  2002/07/18 00:52:13  bkline
 * Added decode() and getShortHostName().
 *
 * Revision 1.7  2002/06/13 18:48:48  bkline
 * Added hostname property.
 *
 * Revision 1.6  2002/04/18 21:47:53  bkline
 * Replaced include statement for xmetal2.h with xmetal3.h.
 *
 * Revision 1.5  2001/11/27 14:18:57  bkline
 * New utility methods; modified extraction methods.
 *
 * Revision 1.4  2001/06/11 18:26:43  bkline
 * Snapshot prior to re-working automation support using CCmdTarget.
 *
 * Revision 1.3  2001/06/09 12:29:47  bkline
 * Switched to Unicode strings; added more sophisticated XML parsing.
 *
 * Revision 1.2  2001/04/18 14:44:19  bkline
 * Added insertion operator for DOM node.
 *
 * Revision 1.1  2000/10/16 22:31:48  bkline
 * CDR client header
 */

#ifndef CDR_UTIL_H_
#define CDR_UTIL_H_

// Local headers.
#include "stdafx.h"
#include "xmetal4.h"

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
 */
class CdrSocket {
public:
    static CString sendCommand(const CString& command);
	static void setSessionString(const CString& s) { sessionString = s; }
	static bool loggedOn() { return !sessionString.IsEmpty(); }
    static const CString getSessionString() { return sessionString; }
    static const CString getHostName() { return hostName; }
    static CString getShortHostName() {
        int dot = hostName.Find(TCHAR('.'));
        if (dot != -1 && !_istdigit(hostName[0]))
            return hostName.Left(dot);
        return hostName;
    }
private:
    int sock;
    enum { CDR_SOCK = 2019 };
    CdrSocket();
    ~CdrSocket() { closesocket(sock); }
    std::string read();
    struct Init {
        Init();
        ~Init();
        WSAData wsaData;
        static Init init;
    };
	static CString sessionString;
    static CString hostName;
};

/**
 * XML parsing on the cheap.  Replace with the real thing if necessary.
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
        GlossaryTree();
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
    };
    GlossaryTree* getGlossaryTree();

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

    // Common utility functions.
    int fillListBox(CListBox& listBox, const DocSet& docSet);
    void extractSearchResults(const CString& xml, DocSet& docSet);
	bool showErrors(const CString& msg);
    _Application getApp();
    CString getXmetalPath();
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
}

std::basic_ostream<TCHAR>& operator<<(std::basic_ostream<TCHAR>& os, 
									  DOMNode& node);

#endif
