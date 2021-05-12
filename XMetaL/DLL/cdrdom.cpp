#include "stdafx.h"
#include "cdrdom.h"

/**
 * Initialize the DOM for a new XML document.
 *
 * Invoked by the other two overloaded constructors.
 */
cdr::DOM::DOM() {
    HRESULT hr = doc.CoCreateInstance(__uuidof(DOMDocument));
    if (FAILED(hr))
        throw L"Unable to initialize DOM";
    doc->put_async(VARIANT_FALSE);
    doc->put_validateOnParse(VARIANT_FALSE);
    doc->put_resolveExternals(VARIANT_FALSE);
    doc->put_preserveWhiteSpace(VARIANT_TRUE);
}

/**
 * Create the DOM object from its serialized XML.
 *
 * Heavily used throught the DLL code, including by every
 * method which needs to parse a command response returned
 * by the CDR server.
 *
 * @param xml - serialized XML from which the DOM object is generated
 */
cdr::DOM::DOM(const CString& xml) : DOM() {
    VARIANT_BOOL succeeded = VARIANT_FALSE;
    CComBSTR bstr(xml);
    if (FAILED(doc->loadXML(bstr, &succeeded)))
        throw L"loadXml() failed";
    if (succeeded == VARIANT_FALSE) {
        CComPtr<IXMLDOMParseError> parse_error;
        if (FAILED(doc->get_parseError(&parse_error)))
            throw L"XML parse failed but can't get parse error";
        CComBSTR reason;
        if (FAILED(parse_error->get_reason(&reason)))
            throw L"XML parse failed but can't get failure reason";
        CString why(reason);
        static wchar_t error[1024];
        wcsncpy(error, why.GetString(), 1023);
        throw error;
    }
}

/**
 * Create a DOM object with just a root element.
 *
 * Invoked by the cdr::CommandSet constructor.
 *
 * @param root_name - name of the element to use as the document element.
 */
cdr::DOM::DOM(const char* root_name) : DOM() {
    root = child_element(doc, root_name);
}

/**
 * Attach an element to an existing parent.
 *
 * Called by:
 *   cdr::CommandSet::add_cdr_document()
 *   cdr::DOM::append_text()
 *   cdr::DOM::child_element()
 *   cdr::DOM::set_root()
 *   CCommands::getOrgAddress()
 *
 *  @param parent - pointer to the parent node we attach to
 *  @param child  - pointer to the node being attached to the parent
 */
void cdr::DOM::append(IXMLDOMNode* parent, IXMLDOMNode* child) {
    Node out;
    HRESULT hr = parent->appendChild(child, &out);
    if (FAILED(hr))
        throw L"appendChild() failed";
}

/**
 * Attach a text node to an existing element.
 *
 * Called by:
 *   cdr::DOM::element()
 *
 *  @param parent - pointer to the parent node we attach to
 *  @param text   - Unicode string for the value being attached
 */
void cdr::DOM::append_text(IXMLDOMNode* parent, const CString& text) {
    CComBSTR bstr(text);
    CComPtr<IXMLDOMText> text_node;
    if (FAILED(doc->createTextNode(bstr, &text_node)))
        throw L"createTextNode() failed";
    append(parent, text_node);
}

/**
 * Create a new element attached to an existing parent.
 *
 * Called by dozens of methods throughout the DLL code.
 *
 *  @param parent - pointer to the parent node we attach to
 *  @param name   - string for the new element's name
 *  @param text   - optional string value to be used to set the
 *                  text content of the new element
 *  @return       - `CComPtr` for newly created element
 */
cdr::DOM::Element cdr::DOM::child_element(IXMLDOMNode* parent,
    const CString& name,
    const CString& text) {
    Element e = element(name, text);
    append(parent, e);
    return e;
}

/**
 * Create a new element with optional text content.
 *
 * The new element is not attached to any parent.
 *
 * Called by:
 *   cdr::DOM::child_element()
 *   open_doc() in Commands.cpp
 *
 *  @param name   - string for the new element's name
 *  @param text   - optional string value to be used to set the
 *                  text content of the new element
 *  @return       - `CComPtr` for newly created element
 */
cdr::DOM::Element cdr::DOM::element(const CString& name, const CString& text) {
    Element e;
    CComBSTR bstr(name);
    if (FAILED(doc->createElement(bstr, &e)))
        throw L"createElement() failed";
    if (!text.IsEmpty())
        append_text(e, text);
    return e;
}

/**
 * Find a single element matching the supplied XPath string.
 *
 * If no element is specified, the search if from the root element.
 *
 * Called by dozens of methods throughout the DLL code.
 *
 *  @param xpath - string for the search
 *  @param from  - optional node from which to start the search
 *  @return      - `CComPtr` for found element or `nullptr` if none
 */
cdr::DOM::Element cdr::DOM::find(const CString& xpath, IXMLDOMElement* top) {
    if (!top)
        top = get_root();
    CComBSTR bstr(xpath);
    Node node;
    if (FAILED(top->selectSingleNode(bstr, &node)))
        throw L"selectSingleNode() failed";
    if (!node)
        return NULL;
    Element element;
    HRESULT hr = node->QueryInterface(__uuidof(IXMLDOMElement),
        (void**)&element);
    if (FAILED(hr))
        throw L"QueryInterface failed for IXMLDOMElement";
    return element;
}

/**
 * Find all elements matching the supplied XPath string.
 *
 * If no element is specified, the search if from the root element.
 *
 * Called extensively throughout the DLL code.
 *
 *  @param xpath - string for the search
 *  @param from  - optional node from which to start the search
 *  @return      - sequence of `CComPtr`s for matching elements
 */
std::vector<cdr::DOM::Element> cdr::DOM::find_all(const CString& xpath,
    IXMLDOMElement* top) {
    if (!top)
        top = get_root();
    CComBSTR bstr(xpath);
    NodeList list = NULL;
    if (FAILED(top->selectNodes(bstr, &list)))
        throw L"selectNodes() failed";
    std::vector<Element> elements;
    for (;;) {
        Node node;
        if (FAILED(list->nextNode(&node)))
            throw L"nextNode() failed for DOM node list";
        if (!node)
            return elements;
        Element e;
        if (FAILED(node->QueryInterface(__uuidof(IXMLDOMElement), (void**)&e)))
            throw L"QueryInterface failed for IXMLDOMElement";
        elements.push_back(e);
    }
}

/**
 * Get the value of an element's attribute.
 *
 * Called by about a dozen places throughout the DLL code base.
 *
 *  @param elem - pointer to the element whose attribute value we want
 *  @param name - string naming the attribute whose value we want
 *  @return     - string for attribute value
 */
CString cdr::DOM::get(IXMLDOMElement* elem, const CString& name) {
    CComBSTR bstr(name);
    CComVariant variant;
    if (FAILED(elem->getAttribute(bstr, &variant)))
        throw L"getAttribute failed";
    if (variant.vt != VT_BSTR)
        return L"";
    CString value(variant);
    return value;
}

/**
 * Get the string for a specific DOM node's name.
 *
 * Called by:
 *   open_doc() in Commands.cpp
 *
 *  @param node - address of the DOM node whose name we want
 *  @return     - pointer to the root element
 */
CString cdr::DOM::get_node_name(IXMLDOMNode* node) {
    CComBSTR bstr;
    if (FAILED(node->get_nodeName(&bstr)))
        throw L"get_nodeName() failed";
    CString name(bstr);
    return name;
}

/**
 * Give the caller a pointer to the root element.
 *
 * Called by about a dozen places throughout the DLL code.
 *
 *  @return - `CComPtr` for the root element
 */
cdr::DOM::Element cdr::DOM::get_root() {
    if (!root) {
        if (FAILED(doc->get_documentElement(&root)))
            throw L"get_documentElement() failed";
    }
    return root;
}

/**
 * Get the text content string for a specific element.
 *
 * Called many places throughout the code.
 *
 *  @param node - address of the DOM node whose text content we want
 *  @return     - text content for element node
 */
CString cdr::DOM::get_text(IXMLDOMNode* element) {
    if (!element)
        return L"";
    CComBSTR bstr;
    if (FAILED(element->get_text(&bstr)))
        throw L"get_text() failed";
    CString text(bstr);
    return text;
}

/**
 * Serialize the document to an XML string.
 *
 * Called by:
 *   CSearchDialog::OnSearchButton()
 *   cdr::CommandSet::add_cdr_document()
 *   err_response() in CdrUtil.cpp
 *   CCommands::getOrgAddress()
 *   open_doc() in Commands.cpp
 *   cdr::Socket::send_commands()
 *
 *  @param node - address of the DOM node whose XML serialization we want
 *  @return     - string for the serialized node
 */
CString cdr::DOM::get_xml(IXMLDOMNode* node) const {
    CComBSTR bstr;
    if (!node)
        node = doc;
    if (FAILED(node->get_xml(&bstr)))
        throw L"get_xml() failed";
    CString xml(bstr);
    return xml;
}

/**
 * Install a node in front of an existing node.
 *
 * Called by:
 *   open_doc() in Commands.cpp
 *
 *  @param parent   - pointer to the parent node we attach to
 *  @param new_node - pointer to the node we are inserting
 *  @param sibling  - pointer to the node in front of which we insert
 */
void cdr::DOM::insert(IXMLDOMNode* parent, IXMLDOMNode* new_node,
    IXMLDOMNode* sibling) {
    Node out;
    CComVariant reference(sibling);
    HRESULT hr = parent->insertBefore(new_node, reference, &out);
    if (FAILED(hr))
        throw L"insertBefore() failed";
}

/**
 * Assign a string value to a named attribute of an element.
 *
 * Used extensively throughout the code.
 *
 *  @param element - address of the element whose attribute we set
 *  @param name    - string for the name of the attribute to be set
 *  @param value   - string for the value we assign to the attribute
 */
void cdr::DOM::set(IXMLDOMElement* elem, const CString& name,
    const CString& value) {
    CComBSTR bstr_name(name);
    CComPtr<IXMLDOMAttribute> attr;
    if (FAILED(doc->createAttribute(bstr_name, &attr)))
        throw L"createAttribute() failed";
    CComBSTR bstr_value(value);
    CComVariant variant(bstr_value);
    if (FAILED(attr->put_value(variant)))
        throw L"put_value() failed for attribute";
    CComPtr<IXMLDOMAttribute> out;
    if (FAILED(elem->setAttributeNode(attr, &out)))
        throw L"setAttributeNode() failed";
}

/**
 * Create a DOM builder for a CdrCommandSet XML document.
 *
 * Called by every method which sends a command to the CDR server.
 *
 * @param name - name of the first (likely only) command in the set
 * @param session_id - identifier for the current CDR login session
 */
cdr::CommandSetBase::CommandSetBase(
    const char* name,
    const CString& session_id
) : DOM("CdrCommandSet") {
    child_element(root, "SessionId", session_id);
    auto wrapper = child_element(root, "CdrCommand");
    command = child_element(wrapper, name);
}

/**
 * Add a modified copy of the active document to the DOM.
 *
 * Called by:
 *   CCommands::save()
 *   CCommands::validate()
 *
 * Modifications include:
 *  - removal of the `CdrDocCtl` block
 *  - stripping of any `readonly` attributes
 *
 *  @param parent   - the node in the `CommandSet` DOM to which a
 *                    CDATA section will be attached with the doc XML
 *  @param original - serialized XML for XMetaL's active document
 */
void cdr::CommandSetBase::add_cdr_document(IXMLDOMElement* parent,
    const CString& original) {

    // Generate a new DOM from the serialized original document.
    DOM new_dom(original);

    // Strip the CdrDocCtl block.
    auto doomed = new_dom.find("CdrDocCtl");
    if (doomed) {
        auto new_root = new_dom.get_root();
        Node out;
        if (FAILED(new_root->removeChild(doomed, &out)))
            throw L"removeChild(CdrDocXml) failed";
    }

    // Strip the 'readonly' attributes.
    auto elements = new_dom.find_all("//*[@readonly]");
    CComBSTR name(L"readonly");
    for (auto& element : elements) {
        if (FAILED(element->removeAttribute(name)))
            throw L"removeAttribute(readonly) failed";
    }

    // Create, populate, and append the CdrDocXml element.
    auto child = child_element(parent, "CdrDocXml");
    CString doc_xml = new_dom.get_xml(new_dom.get_root());
    doc_xml.Remove(L'\r');
    CComBSTR bstr(doc_xml);
    CComPtr<IXMLDOMCDATASection> cdata;
    HRESULT hr = this->doc->createCDATASection(bstr, &cdata);
    if (FAILED(hr))
        throw L"createCDATASection failed";

    // Drop the element into the command document.
    append(child, cdata);
}
