/**
 * Creates UTF-8 version of CString.  Ignores UCS code points beyond 0xFFFF.
 * If _UNICODE is not defined, we let the server catch any characters we're
 * given which are legal ANSI characters but not legal Unicode characters.
 */
#include "stdafx.h"

#include "CDRGenerics.h"

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
