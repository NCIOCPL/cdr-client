#include <stdafx.h>
#include "CDRGenerics.h"

// #include <sstream>
/// #include <iostream>

static const size_t  DECODING_TABLE_SIZE = 128;
static const wchar_t PAD_CHAR = L'=';
static const wchar_t INVALID_BITS = L'\xFFC0';

static const wchar_t* getEncodingTable()
{
    return L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
           L"abcdefghijklmnopqrstuvwxyz"
           L"0123456789+/";
}

static const wchar_t* getDecodingTable()
{
    static std::wstring tableString;
    static const wchar_t* decodingTable = 0;
    if (!decodingTable) {
        const wchar_t* codes = getEncodingTable();
        tableString.resize(DECODING_TABLE_SIZE, INVALID_BITS);
        for (wchar_t i = 0; codes[i]; ++i)
            tableString[codes[i]] = i;
        decodingTable = tableString.data();
    }
    return decodingTable;
}

std::string cdr::decodeBase64String(const CString& base64)
{
    // Keep this outside the try block so we can delete it in the catch.
    unsigned char* buf = 0;

    try {

        // This will give us a buffer (not too much) larger than necessary.
        size_t nBytes = base64.GetLength();
        unsigned char* p = buf = new unsigned char[nBytes];

        // Walk through the encoded string.
        const wchar_t* table = getDecodingTable();
        int i = 0;
        wchar_t c = 0;
        int state = 0;
        while ((size_t)i < nBytes) {
            c = base64.GetAt(i++);
            if (iswspace(c))
                continue;
            else if (c == PAD_CHAR)
                break;
            else if (c < 0 || c >= DECODING_TABLE_SIZE) {
                wchar_t err[80];
                swprintf(err, L"Invalid base-64 character: %u", c);
                throw err;
            }
            wchar_t bits = table[c];
            if (bits == INVALID_BITS) {
                wchar_t err[80];
                swprintf(err, L"Invalid base-64 character: %u", c);
                throw err;
            }
            switch (state) {
                case 0:
                    *p    =  bits << 2;
                    ++state;
                    break;
                case 1:
                    *p++ |=  bits >> 4;
                    *p    = (bits & 0x0F) << 4;
                    ++state;
                    break;
                case 2:
                    *p++ |=  bits >> 2;
                    *p    = (bits & 0x03) << 6;
                    ++state;
                    break;
                case 3:
                    *p++ |=  bits;
                    state = 0;
                    break;
            }
        }

        // Verify that we have no invalid trailing garbage.
        if (c == PAD_CHAR) {

            // States 0 and 1 are invalid if we got a padding character.
            if (state < 2)
                throw L"Invalid number of significant "
                      L"characters in base-64 encoding";
  
            // For state 2 there should be two padding characters; get the
            // other one.
            if (state == 2) {
                c = 0;
                while ((size_t)i < nBytes) {
                    c = base64.GetAt(i++);
                    if (c == PAD_CHAR)
                        break;
                    if (iswspace(c))
                        continue;
                    throw L"Invalid character following "
                          L"padding character in base-64 encoding";
                }
                if (c != PAD_CHAR)
                    throw L"Invalid number of significant "
                          L"characters in base-64 encoding";
            }

            // Everything else should be whitespace.
            while ((size_t)i < nBytes) {
                c = base64.GetAt(i++);
                if (!iswspace(c))
                    throw L"Invalid character following "
                          L"padding character in base-64 encoding";
            }

            // Check for invalid trailing bits.
            if (*p)
                throw L"Some hacker is trying to slip in "
                      L"some extra bits at the end of a base-64 encoded "
                      L"value";
        }

        // No padding: we should have come out on an even 4-character boundary.
        else if (state != 0)
            throw L"Invalid number of significant "
                  L"characters in base-64 encoding";

        // All done.
        std::string result((const char*)buf, p - buf);
        delete [] buf;
        return result;
    }
    catch (...) {
        delete [] buf;
        throw;
    }
}

std::wstring cdr::encodeBase64String(const std::string& s)
{
    wchar_t *buf = 0;
    try {
        size_t nBytes = s.size();
        size_t nChars = (nBytes /  3 + 1) * 4   // encoding bloat
                      + (nBytes / 57 + 1) * 2;  // line breaks
        buf = new wchar_t[nChars];
        size_t i = 0;
        wchar_t* p = buf;
        size_t charsInLine = 0;
        const unsigned char* bits = (const unsigned char*)s.data();
        const wchar_t* codes = getEncodingTable();
        while (i < nBytes) {
            switch (nBytes - i) {
            case 1:
                p[0] = codes[(bits[i + 0] >> 2)                    & 0x3F];
                p[1] = codes[(bits[i + 0] << 4)                    & 0x3F];
                p[2] = PAD_CHAR;
                p[3] = PAD_CHAR;
                break;
            case 2:
                p[0] = codes[(bits[i + 0] >> 2)                    & 0x3F];
                p[1] = codes[(bits[i + 0] << 4 | bits[i + 1] >> 4) & 0x3F];
                p[2] = codes[(bits[i + 1] << 2)                    & 0x3F];
                p[3] = PAD_CHAR;
                break;
            default:
                p[0] = codes[(bits[i + 0] >> 2)                    & 0x3F];
                p[1] = codes[(bits[i + 0] << 4 | bits[i + 1] >> 4) & 0x3F];
                p[2] = codes[(bits[i + 1] << 2 | bits[i + 2] >> 6) & 0x3F];
                p[3] = codes[(bits[i + 2])                         & 0x3F];
                break;
            }
            i += 3;
            p += 4;
            charsInLine += 4;
            if (charsInLine >= 76) {
                *p++ = L'\r';
                *p++ = L'\n';
                charsInLine = 0;
            }
        }
        if (charsInLine) {
            *p++ = L'\r';
            *p++ = L'\n';
        }

        // Release buffer and return as string
        std::wstring retval = std::wstring(buf, p - buf);
        delete [] buf;
        return retval;
    }
    catch (...) {
        delete [] buf;
        throw;
    }
}

/**
 * Creates UTF-8 version of CString.  Ignores UCS code points beyond 0xFFFF.
 * If _UNICODE is not defined, we let the server catch any characters we're
 * given which are legal ANSI characters but not legal Unicode characters.
 */

#ifdef _UNICODE
    inline unsigned short charToUnsignedShort(TCHAR c) 
    {
        return static_cast<unsigned short>(c);
    }
#else
    inline unsigned short charToUnsignedShort(TCHAR c) 
    {
        unsigned char uc = static_cast<unsigned char>(c);
        return static_cast<unsigned short>(uc);
    }
#endif

std::string cdr::cStringToUtf8(const CString& str)
{
    // Calculate storage requirement.
    size_t i, len = 0;
    size_t strLen = str.GetLength();
    LPCTSTR wchars = static_cast<LPCTSTR>(str);
    for (i = 0; i < strLen; ++i) {
        unsigned short ch = charToUnsignedShort(wchars[i]);
        if (ch < 0x80)
            ++len;
        else if (ch < 0x800)
            len += 2;
        else
            len += 3;
    }

    // Create string.
    std::string utf8(len, ' ');
    size_t j;

    // Populate string.
    for (i = j = 0; i < strLen; ++i) 
    {
        unsigned short ch = charToUnsignedShort(*wchars++);
        if (ch < 0x80)
            utf8[j++] = (char)(unsigned char)ch;
        else if (ch < 0x800) 
        {
            utf8[j++] = (char)(unsigned char)(0xC0 | ((ch & 0x07C0) >> 6));
            utf8[j++] = (char)(unsigned char)(0x80 |  (ch & 0x003F));
        }
        else 
        {
            utf8[j++] = (char)(unsigned char)(0xE0 | ((ch & 0xF000) >> 12));
            utf8[j++] = (char)(unsigned char)(0x80 | ((ch & 0x0FC0) >> 6));
            utf8[j++] = (char)(unsigned char)(0x80 |  (ch & 0x003F));
        }
    }
    return utf8;
}

/**
 * Converts string from UTF-8 to UTF-16.  Ignores values beyond U+FFFF.
 */
CString cdr::utf8ToCString(const char* s)
{
    // Calculate storage requirement.
    size_t i, len = 0;
    for (i = 0; s[i]; ++i) 
    {
        if (((unsigned char)s[i] & 0x80) == 0)
            ++len;
        else if (((unsigned char)s[i] & 0x40) == 0x40)
            ++len;
    }

    // Make room.
    std::wstring newStr(len, ' ');

    // Populate string.
    for (i = 0; i < len; ++i) 
    {
        unsigned char ch = (unsigned char)*s;
        if (ch < 0x80) 
        {
            newStr[i] = (wchar_t)ch;
            ++s;
        }
        else if ((ch & 0xE0) == 0xC0) 
        {
            newStr[i] = ((ch & 0x1F) << 6)
                      | (((unsigned char)s[1]) & 0x3F);
            s += 2;
        }
        else 
        {
            newStr[i] = ((ch & 0x0F) << 12)
                      | ((((unsigned char)s[1]) & 0x3F) << 6)
                      | (((unsigned char)s[2]) & 0x3F);
            s += 3;
        }
#ifndef _UNICODE
        if ((unsigned short)newStr[j] > 0xFF) 
        {
            CString err;
            err.Format(_T("Received Unicode character U%04X which")
                       _T(" will not fit in the ANSI character set;")
                       _T(" build DLL with _UNICODE defined."),
                       (unsigned short)newStr[i]);
            throw (LPCTSTR)err;
        }
#endif
    }
    return CString(newStr.c_str());
}

CString cdr::Element::getAttribute(const CString& name) const
{
    Attrs::const_iterator i = attrs.find(name);
    if (i == attrs.end())
        return CString();
    else
        return i->second;
}

cdr::Element cdr::Element::extractElement(const CString& s,
                                          const CString& name,
                                          int pos)
{
    // Start with an element that returns false.
    Element e;

    // Cache some frequently used values.
    int nameLen = name.GetLength();
    int strLen  = s.GetLength();

    // Look for start tag of element.
    int startPos = s.Find(_T("<") + name, pos);
    while (startPos != -1) {
        if (startPos + nameLen + 1 >= strLen)
            return e;
        startPos += nameLen + 1;
        TCHAR ch = s[startPos];

        // Make sure we don't have another tag that starts the same way.
        if (_istspace(ch) || ch == (TCHAR)'>' || ch == (TCHAR)'/')
            break;

        // Try another position.
        startPos = s.Find(_T("<") + name, startPos);
    }
    if (startPos == -1)
        return e;

    // Loop through the start tag extracting all attributes.
    while (startPos < strLen) {
        CString attrName;
        CString attrValue;
        int     attrNameStart;
        int     attrValueStart;
        TCHAR   delim;
        TCHAR   ch = s[startPos];

        // Check for an empty-element tag.
        if (ch == (TCHAR)'/') {
            startPos = s.Find(_T(">"), startPos);
            if (startPos == -1)
                return e;
            e.startPos = e.endPos = startPos + 1;
            e.str = _T("");
            return e;
        }

        // Check for end of tag; move past it if we find it.
        if (ch == (TCHAR)'>') {
            ++startPos;
            break;
        }

        // Skip past whitespace.
        if (_istspace(ch)) {
            startPos++;
            continue;
        }

        // Extract the attribute's name.
        attrNameStart = startPos++;
        while (startPos < strLen) {
            ch = s[startPos];
            if (ch == (TCHAR)'=' || _istspace(ch)) {
                attrName = s.Mid(attrNameStart, startPos++ - attrNameStart);
                if (e.attrs.find(attrName) != e.attrs.end())
                    throw (LPCTSTR)(_T("Duplicate attribute ") + attrName +
                                    _T(" in element ") + name);
                break;
            }
            ++startPos;
        }

        // Find the character delimiting the attribute's string value.
        while (startPos < strLen) {
            ch = s[startPos++];
            if (ch == (TCHAR)'\'' || ch == (TCHAR)'\"') {
                delim = ch;
                attrValueStart = startPos;
                break;
            }
        }

        // Find the matching end delimiter and extract the value.
        while (startPos < strLen) {
            if (s[startPos] == delim) {
                attrValue = s.Mid(attrValueStart, startPos++ - attrValueStart);
                e.attrs[attrName] = attrValue;
                break;
            }
            ++startPos;
        }
    }

    // We now have all the attributes and startPos points just past closing >.
    // XXX Note that this approach fails with nested elements of the same
    // name.  Should not pose a problem for the uses the CDR software makes of
    // this method, but watch out for future uses.  At that point we may need
    // to link in a real XML parser.
    int endPos = s.Find(_T("</") + name + _T(">"), startPos);
    if (endPos == -1)
        return e;
    e.str = s.Mid(startPos, endPos - startPos);
    e.startPos = startPos;
    e.endPos = endPos;
    return e;
}

CString cdr::Element::getCdataSection() const
{
    static CString target = _T("<![CDATA[");
    int pos = str.Find(target);
    if (pos == -1)
        return CString();
    pos += target.GetLength();
    int end = str.Find(_T("]]>"), pos);
    if (end == -1)
        return CString();
    return str.Mid(pos, end - pos);
}

/**
 * Extract the text content from the first occurrence of the specified
 * element.
 *
 *  @param  tag             reference to string object for the element's
 *                          name.
 *  @return                 string object containing the element's text
 *                          content, or an empty string if the element
 *                          is not found.
 */
CString TinyXmlParser::extract(const CString& tag) const 
{
    // Create target strings used in searching for the element's tags.
    CString open = _T("<") + tag + _T(">");
    CString close = _T("</") + tag + _T(">");

    // Find the tags.
    int pos = xml.Find(open);
    if (pos == -1)
        return _T("");
    pos += open.GetLength();
    int endPos = xml.Find(close, pos);

    // Make sure we found the element.
    if (endPos == -1 || endPos == pos)
        return _T("");

    // Pull out the text content.
    return xml.Mid(pos, endPos - pos);
}
