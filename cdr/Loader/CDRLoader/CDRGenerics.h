
#include <string>

namespace cdr 
{
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



