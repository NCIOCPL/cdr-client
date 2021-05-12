/**
 * Test suite to exercise the wrapper around MSXML functionality.
 *
 * Has complete coverage of all of the paths in the code. Takes
 * a single command-line argument to specify the number of runs
 * to perform (default is 1 time). Use with a large number while
 * monitoring memory usage in Task Manager (or a similar tool)
 * to verify that there are no memory leaks (memory usage should
 * not get much higher than a megabyte or two, or at the least
 * should not increase over time). Has been run with a million
 * iterations with no observable increase in memory usage and no
 * exceptions thrown. Takes about 1/2 hour for a run that size.
 */

#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include "cdrdom.h"

static void test1() {

    // Create a DOM object by specifying the root name.
    cdr::DOM dom("a");
    auto root = dom.get_root();

    // Test fetching the node's name.
    assert(dom.get_node_name(root) == L"a");

    // Add some children and test fetching the serialized XML.
    auto b = dom.child_element(root, "b");
    auto c = dom.child_element(root, "c");
    assert(dom.get_xml().Trim() == L"<a><b/><c/></a>");

    // Add a nested child element with text and fetch the text.
    auto bb1 = dom.child_element(b, "bb1", "foo");
    assert(dom.get_text(bb1) == "foo");

    // Create and append an element in separate operations.
    auto d = dom.child_element(root, "d", "dada");
    dom.append(root, d);
    wchar_t* expected = L"<a><b><bb1>foo</bb1></b><c/><d>dada</d></a>";
    assert(dom.get_xml().Trim() == expected);

    // Append text to an existing element node.
    dom.append_text(bb1, "bar");
    expected = L"<a><b><bb1>foobar</bb1></b><c/><d>dada</d></a>";
    assert(dom.get_xml().Trim() == expected);

    // Test finding an element node using XPath.
    auto node = dom.find("//bb1");
    assert(dom.get_xml(node) == L"<bb1>foobar</bb1>");

    // Test multiple-node finds.
    auto nodes = dom.find_all("/a/*");
    assert(nodes.size() == 3);
    assert(dom.get_node_name(nodes[0]) == L"b");
    assert(dom.get_node_name(nodes[1]) == L"c");
    assert(dom.get_node_name(nodes[2]) == L"d");

    // Test setting/reading of attributes.
    dom.set(c, "cc", "C++");
    assert(dom.get(c, "cc") == L"C++");

    // Test inserting a node.
    dom.insert(b, dom.element("bb0"), bb1);
    assert(dom.get_xml(b) == L"<b><bb0/><bb1>foobar</bb1></b>");
}

static void test2() {

    // Test constructing a DOM from the serialized Unicode XML.
    CString xml(
        L"<?xml version=\"1.0\"?>\n"
        L"<!DOCTYPE Country SYSTEM 'Country.dtd'>\n"
        L"<Country xmlns:cdr=\"cips.nci.nih.gov/cdr\">\n"
        L" <CountryFullName>United Kingdom</CountryFullName>\n"
        L" <Continent>Europe</Continent>\n"
        L" <PostalCodePosition>after PoliticalSubUnit_State"
        L"</PostalCodePosition>"
        L"<ISOShortCountryName>UNITED KINGDOM"
        L"</ISOShortCountryName>"
        L"<ISOAlpha2CountryCode>GB</ISOAlpha2CountryCode>\n"
        L" <InternationalDialingCode Type=\"Land\">44"
        L"</InternationalDialingCode><PdqKey>2012</PdqKey>\n"
        L"</Country>");
    cdr::DOM dom(xml);
    assert(dom.get_xml().GetLength() == 471);

    // Change the DOM.
    auto doc_ctl = dom.element("CdrDocCtl");
    dom.set(doc_ctl, "readyForReview", "N");
    dom.set(doc_ctl, "blocked", "N");
    CString docType = L"Country";
    dom.child_element(doc_ctl, "DocId", "CDR0000123456");
    dom.child_element(doc_ctl, "DocTitle", "Count of Monte Cristo");
    auto root = dom.get_root();
    dom.insert(root, doc_ctl, dom.find("*", root));
    assert(dom.get_xml().GetLength() == 595);
    auto children = dom.find_all("/Country/*");
    assert(children.size() == 8);
    assert(dom.get_node_name(children[0]) == L"CdrDocCtl");
    assert(dom.get_node_name(children[1]) == L"CountryFullName");
    assert(dom.get_node_name(children[2]) == L"Continent");
    assert(dom.get_node_name(children[3]) == L"PostalCodePosition");
    assert(dom.get_node_name(children[4]) == L"ISOShortCountryName");
    assert(dom.get_node_name(children[5]) == L"ISOAlpha2CountryCode");
    assert(dom.get_node_name(children[6]) == L"InternationalDialingCode");
    assert(dom.get_node_name(children[7]) == L"PdqKey");
}

static void test3() {

    // Test extracting a nested document. Add non-ascii for good measure.
    cdr::DOM dom(L"<a><b><![CDATA[<x><y>&#xE8;foo</y></x>]]></b></a>");
    auto cdata = dom.find("b");
    CString xml = dom.get_text(cdata);
    cdr::DOM inner(xml);
    auto y = inner.find("y");
    assert(inner.get_text(y) == L"\x00e8" L"foo");
}

static void test4() {

    // Test catching an exception.
    CString problem;
    try {
        cdr::DOM bad(L"<foo><bar>");
    }
    catch (const wchar_t* e) {
        problem = L"caught";
    }
    assert(problem == L"caught");
}

static void test5() {

    // Test copying nodes from one DOM to another.
    CString xml = (
        L"<?xml version=\"1.0\"?>\n"
        L"<AddressElements xmlns:cdr=\"cips.nci.nih.gov/cdr\">"
        L"<OrgName>Saint Alphonsus Cancer Care Center - Caldwell"
        L"</OrgName>\n"
        L"<PostalAddress AddressType=\"US\">\n"
        L"<Street>3123 Medical Drive</Street>\n"
        L"<City>Caldwell</City>\n"
        L"<PoliticalSubUnit_State cdr:ref=\"CDR0000043869\">ID"
        L"</PoliticalSubUnit_State>\n"
        L"<Country cdr:ref=\"CDR0000043753\">U.S.A.</Country>\n"
        L"<PostalCode_ZIP>83605</PostalCode_ZIP>\n"
        L"</PostalAddress>\n"
        L"<Phone>208-453-2033</Phone>\n"
        L"<TollFreePhone>866-453-2033</TollFreePhone>"
        L"<WebSite cdr:xref=\"http://www.saintalphonsus.org/"
        L"svc_cancer.html\">Web site for Saint Alphonsus "
        L"Cancer Care Center - Caldwell</WebSite></AddressElements>");
    cdr::DOM src(xml);
    cdr::DOM dst("SpecificPostalAddress");
    assert(src.get_xml().GetLength() == 645);
    assert(src.find_all("PostalAddress/*").size() == 5);
    auto root = dst.get_root();
    dst.set(root, "xmlns:cdr", "cips.nci.nih.gov/cdr");
    for (auto& child : src.find_all("PostalAddress/*")) {
        dst.append(root, child);
    }

    // Confirm that the children are in the new DOM.
    assert(dst.find_all("*").size() == 5);

    // But no long in the original DOM.
    assert(src.find_all("PostalAddress/*").size() == 0);
    assert(src.get_xml().GetLength() == 427);
}

static void test6() {

    // Test loading from disk. The test file has ASCII characters only,
    // in order to avoid dependencies on the home-grown utf8->UCS2
    // converter, which we still need because apparently the codecvt
    // library that was added to standard C++ has already been deprecated.
    std::ifstream is("test.xml", std::ifstream::binary);
    std::stringstream buf;
    buf << is.rdbuf();
    CString doc_xml(buf.str().c_str());
    doc_xml.Remove(L'\r');
    cdr::DOM doc(doc_xml);
    auto nodes = doc.find_all("*");
    assert(nodes.size() == 5);
    assert(doc.get_node_name(nodes[0]) == L"CdrDocCtl");
    assert(doc.get_node_name(nodes[1]) == L"MediaTitle");
    assert(doc.get_node_name(nodes[2]) == L"PhysicalMedia");
    assert(doc.get_node_name(nodes[3]) == L"MediaSource");
    assert(doc.get_node_name(nodes[4]) == L"MediaContent");

    // Test attaching the document to a CommandSet object.
    cdr::CommandSetBase request("CdrReplaceDoc");
    auto cdr_doc = request.child_element(request.command, "CdrDoc");
    request.add_cdr_document(cdr_doc, doc_xml);
    CString command_string = request.get_xml();
    assert(command_string.Find(L"<!DOCTYPE Media") == -1);
    assert(command_string.Find(L"<![CDATA[") != -1);
    assert(command_string.GetLength() == 929);
}

static void test7() {

    // Test pulling out a fragment string without the namespace
    // declaration (so XMetaL's fragment pasting won't choke).
    CString xml = (
        L"<?xml version=\"1.0\"?>\n"
        L"<AddressElements xmlns:cdr=\"cips.nci.nih.gov/cdr\">"
        L"<OrgName>NCI - Office of Cancer Content</OrgName>"
        L"<ParentNames OrderParentNameFirst=\"\"/>\n"
        L"<PostalAddress AddressType=\"US\">"
        L"<Street>MSC 9760</Street>\n"
        L"<Street>9609 Medical Center Drive</Street>\n"
        L"<City>Rockville</City>\n"
        L"<PoliticalSubUnit_State cdr:ref=\"CDR0000043877\">MD"
        L"</PoliticalSubUnit_State>\n"
        L"<Country cdr:ref=\"CDR0000043753\">U.S.A.</Country>\n"
        L"<PostalCode_ZIP>20850</PostalCode_ZIP>\n"
        L"</PostalAddress>\n"
        L"<Phone>240-276-6600</Phone>\n"
        L"</AddressElements>");
    cdr::DOM addr_elems(xml);
    auto postal_address = addr_elems.find("PostalAddress");
    assert(postal_address);
    auto children = addr_elems.find_all("*", postal_address);
    CString whatever = addr_elems.get(postal_address, "whatever");
    assert(whatever.IsEmpty());
    CString address_type = addr_elems.get(postal_address, "AddressType");
    cdr::DOM dom("wrapper");
    auto wrapper = dom.get_root();
    dom.set(wrapper, "xmlns:cdr", "cips.nci.nih.gov/cdr");
    CString tag = L"SpecificPostalAddress";
    auto specific_postal_address = dom.child_element(wrapper, tag);
    dom.set(specific_postal_address, "AddressType", address_type);
    for (auto& child : children)
        dom.append(specific_postal_address, child);
    std::wstring s{dom.get_xml().GetString()};
    std::wregex e{L"<SpecificPostalAddress.+</SpecificPostalAddress>"};
    std::wsmatch m;
    assert(std::regex_search(s, m, e));
    CString fragment{m[0].str().c_str()};
    assert(fragment.Find(L" cdr:ref=") != -1);
    assert(fragment.Find(L"xmlns:cdr") == -1);
}

static void run_tests(int iterations) {
    for (auto i = 0; i < iterations; ++i) {
        if ((i + 1) % 1000 == 0)
            std::cout << '.';
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
    }
}

int main(int ac, char** av) {
    assert(sizeof(TCHAR) > 1);
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::cerr << "CoInitialize() failed" << std::endl;
        return EXIT_FAILURE;
    }
    int iterations = ac > 1 ? atoi(av[1]) : 1;
    auto begin = std::chrono::steady_clock::now();
    run_tests(iterations);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - begin;
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(diff);
    auto count = delta.count();
    std::cerr << "\n"
              << iterations
              << " iterations in "
              << std::fixed
              << std::setprecision(3)
              << (count / 1000000.0)
              << " secs\nPress enter to exit the program ...";
    char c;
    std::cin.get(c);
    CoUninitialize();
    return EXIT_SUCCESS;
}
