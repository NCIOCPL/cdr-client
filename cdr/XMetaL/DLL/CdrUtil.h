/*
 * $Id: CdrUtil.h,v 1.1 2000-10-16 22:31:48 bkline Exp $
 *
 * Common utility classes and functions for CDR DLL used to customize XMetaL.
 *
 * $Log: not supported by cvs2svn $
 */

#ifndef CDR_UTIL_H_
#define CDR_UTIL_H_

// Local headers.
#include "stdafx.h"
#include "xmetal2.h"

// System headers.
#include <string>
#include <winsock.h>

// Information used to populate the CdrDocCtl element.
struct CdrDocCtrlInfo {
	std::string docType;
	std::string docId;
	std::string docTitle;
};

/**
 * Wrapper for socket communication between the CDR client and server.
 */
class CdrSocket {
public:
    static std::string sendCommand(const std::string& command);
	static void setSessionString(const std::string& s) { sessionString = s; }
	static bool loggedOn() { return !sessionString.empty(); }
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
	static std::string sessionString;
};

/**
 * XML parsing on the cheap.  Replace with the real thing if necessary.
 */
class TinyXmlParser {
public:
    TinyXmlParser(const std::string& s) : xml(s) {}
    std::string extract(const std::string& tag) const;
private:
    std::string xml;
};

// Common utility functions.
namespace cdr {
    int fillListBox(CListBox& listBox, const std::string& xml);
	bool showErrors(const std::string& msg);
    _Application getApp();
    std::string getXmetalPath();
    std::string encode(std::string str, bool fixQuotes = false);
    unsigned long getDocNo(const std::string& docString);
    std::string extractElementText(DOMNode node);
    std::string trim(const std::string& s);
    void extractCtlInfo(DOMNode node, CdrDocCtrlInfo& info);
}
#endif
