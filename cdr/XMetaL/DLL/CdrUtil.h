/*
 * $Id: CdrUtil.h,v 1.4 2001-06-11 18:26:43 bkline Exp $
 *
 * Common utility classes and functions for CDR DLL used to customize XMetaL.
 *
 * $Log: not supported by cvs2svn $
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
#include "xmetal2.h"

// System headers.
#include <string>
#include <map>
#include <list>
#include <set>
#include <winsock.h>

// Information used to populate the CdrDocCtl element.
struct CdrDocCtrlInfo {
	CString docType;
	CString docId;
	CString docTitle;
};

/**
 * Wrapper for socket communication between the CDR client and server.
 */
class CdrSocket {
public:
    static CString sendCommand(const CString& command);
	static void setSessionString(const CString& s) { sessionString = s; }
	static bool loggedOn() { return !sessionString.IsEmpty(); }
private:
    int sock;
    enum { CDR_SOCK = 2019 };
    CdrSocket();
    std::string read();
    struct Init {
        Init();
        ~Init();
        WSAData wsaData;
        static Init init;
    };
	static CString sessionString;
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

    class SearchResult {
    public:
        SearchResult(const CString& id, 
                     const CString& type, 
                     const CString& title) : docId(id),
                                             docType(type),
                                             docTitle(title) {}
        CString getDocId()    const { return docId; }
        CString getDocType()  const { return docType; }
        CString getDocTitle() const { return docTitle; }
    private:
        CString docId;
        CString docType;
        CString docTitle;
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
    DocSet extractSearchResults(const CString& xml);
	bool showErrors(const CString& msg);
    _Application getApp();
    CString getXmetalPath();
    CString encode(CString str, bool fixQuotes = false);
    unsigned long getDocNo(const CString& docString);
    CString extractElementText(DOMNode node);
    CString trim(const CString& s);
    void extractCtlInfo(DOMNode node, CdrDocCtrlInfo& info);
    CString utf8ToCString(const char* s);
    std::string cStringToUtf8(const CString& str);
}

std::basic_ostream<TCHAR>& operator<<(std::basic_ostream<TCHAR>& os, 
									  DOMNode& node);

#endif
