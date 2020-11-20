/**
 * Wrapper for a subset of Microsoft's MSXML package.
 */

#include "stdafx.h"
#include <vector>

namespace cdr {

    /**
     * You would think we could just use the DOM functionality exposed
     * by SoftQuad, but unfortunately, their implementation is broken.
     * Cloning the document fails, and getting the serialized XML for
     * a DOM node isn't supported. So here is our own wrapper for MSXML.
     */
    class DOM {
    public:

        /**
         * Useful type definitions.
         */
        typedef CComPtr<IXMLDOMDocument> Document;
        typedef CComPtr<IXMLDOMElement> Element;
        typedef CComPtr<IXMLDOMNode> Node;
        typedef CComPtr<IXMLDOMNodeList> NodeList;

        /**
         * Create the DOM object from its serialized XML.
         *
         *  @param xml - Unicode string containing a serialized document
         */
        DOM(const CString& xml);

        /**
         * Create a DOM object with just a root element.
         *
         *  @param root_name - ASCII c-style string for the root element's name
         *                     (don't use wchar_t* or CString, because that
         *                     will route to the previous constructor)
         */
        DOM(const char* root_name);

        /**
         * Prohibit copy construction or assignment by value.
         *
         * If you really need to pass around this object between
         * functions or methods, do it by reference or pointer.
         */
        DOM(const DOM&) = delete;
        DOM& operator=(const DOM&) = delete;

        /**
         * Attach an element to an existing parent.
         *
         *  @param parent - pointer to the parent node we attach to
         *  @param child  - pointer to the node being attached to the parent
         */
        void append(IXMLDOMNode* parent, IXMLDOMNode* child);

        /**
         * Attach a text node to an existing element.
         *
         *  @param parent - pointer to the parent node we attach to
         *  @param text   - Unicode string for the value being attached
         */
        void append_text(IXMLDOMNode* parent, const CString& text);

        /**
         * Create a new element attached to an existing parent.
         *
         *  @param parent - pointer to the parent node we attach to
         *  @param name   - string for the new element's name
         *  @param text   - optional string value to be used to set the
         *                  text content of the new element
         *  @return       - `CComPtr` for newly created element
         */
        Element child_element(IXMLDOMNode* parent,
            const CString& name,
            const CString& text = L"");

        /**
         * Create a new element with optional text content.
         *
         * The new element is not attached to any parent.
         *
         *  @param name   - string for the new element's name
         *  @param text   - optional string value to be used to set the
         *                  text content of the new element
         *  @return       - `CComPtr` for newly created element
         */
        Element element(const CString& name, const CString& text = L"");

        /**
         * Find a single element matching the supplied XPath string.
         *
         * If no element is specified, the search if from the root element.
         *
         *  @param xpath - string for the search
         *  @param from  - optional node from which to start the search
         *  @return      - `CComPtr` for found element or `nullptr` if none
         */
        Element find(const CString& xpath, IXMLDOMElement* from = nullptr);

        /**
         * Find all elements matching the supplied XPath string.
         *
         * If no element is specified, the search if from the root element.
         *
         *  @param xpath - string for the search
         *  @param from  - optional node from which to start the search
         *  @return      - sequence of `CComPtr`s for matching elements
         */
        std::vector<Element> find_all(const CString& xpath,
            IXMLDOMElement* from = nullptr);

        /**
         * Get the value of an element's attribute.
         *
         *  @param elem - pointer to the element whose attribute value we want
         *  @param name - string naming the attribute whose value we want
         *  @return     - string for attribute value
         */
        CString get(IXMLDOMElement* elem, const CString& name);

        /**
         * Get the string for a specific DOM node's name.
         *
         *  @param node - address of the DOM node whose name we want
         *  @return     - node name string
         */
        CString get_node_name(IXMLDOMNode* node);

        /**
         * Give the caller a pointer to the root element.
         *
         *  @return - `CComPtr` for the root element
         */
        Element get_root();

        /**
         * Get the text content string for a specific element.
         *
         *  @param node - address of DOM node whose text content we want
         *  @return     - text content for element node
         */
        CString get_text(IXMLDOMNode* node);

        /**
         * Serialize the document to an XML string.
         *
         *  @param node - address of DOM node whose XML serialization we want
         *  @return     - string for the serialized node
         */
        CString get_xml(IXMLDOMNode* = nullptr) const;

        /**
         * Install a node in front of an existing node.
         *
         *  @param parent   - pointer to the parent node we attach to
         *  @param new_node - pointer to the node we are inserting
         *  @param sibling  - pointer to the node in front of which we insert
         */
        void insert(IXMLDOMNode* parent, IXMLDOMNode* new_node,
            IXMLDOMNode* sibling);

        /**
         * Assign a string value to a named attribute of an element.
         *
         *  @param element - address of the element whose attribute we set
         *  @param name    - string for the name of the attribute to be set
         *  @param value   - string for the value we assign to the attribute
         */
        void set(IXMLDOMElement* element, const CString& name,
            const CString& value);

    protected:

        /**
         * The DOM tree for the XML document.
         */
        Document doc;

        /**
         * The top-level element for the document (the "document element").
         */
        Element root;

    private:
        /**
         * Initialize the DOM.
         */
        DOM();
    };

    /**
     * Shell for a set of commands to be sent to the CDR server.
     *
     * This base class has been factored out so we can add testing for
     * the add_cdr_document method without the need to mock up the Socket
     * class.
     */
    class CommandSetBase : public DOM {
    public:

        /**
         * Create a DOM builder for a CdrCommandSet XML document.
         *
         * @param name - name of the first (likely only) command in the set
         * @param session_id - identifier for the current CDR login session
         */
        CommandSetBase(const char* name, const CString& session_id = L"guest");

        /**
         * Add a modified copy of the active document to the DOM.
         *
         * Modifications include:
         *  - removal of the `CdrDocCtl` block
         *  - stripping of any `readonly` attributes
         *
         *  @param parent   - the node in the `CommandSet` DOM to which a
         *                    CDATA section will be attached with the doc XML
         *  @param original - serialized XML for XMetaL's active document
         */
        void add_cdr_document(IXMLDOMElement* parent, const CString& original);

        // The child of `CdrCommand` node for the specific command.
        Element command;
    };
}
