
#include "stdafx.h"
#include <string>
#include <map>

namespace cdr 
{
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
        operator void*() const { return startPos != endPos ? (void*)this : 0; }
        int  operator!() const { return startPos == endPos; }
    private:
        typedef std::map<CString, CString> Attrs;
        Element() : startPos(0), endPos(0) {}
        Attrs   attrs;
        CString str;
        int     startPos;
        int     endPos;
    };

    CString utf8ToCString(const char* s);
    std::string cStringToUtf8(const CString& str);
};

/**
 * XML parsing on the cheap.  Replace with the real thing if necessary.
 */
class TinyXmlParser 
{
    public:
        TinyXmlParser(const CString& s) : xml(s) {}
        CString extract(const CString& tag) const;
    private:
        CString xml;
};



