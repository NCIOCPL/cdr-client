<?xml version="1.0"?>

<!--
     Javascript macros implementing customized behavior of XMetaL for the CDR.
  -->

<!DOCTYPE MACROS SYSTEM "macros.dtd">
<MACROS>

<MACRO  name="On_Macro_File_Load"
        lang="JScript">
  <![CDATA[

    //------------------------------------------------------------------
    // GLOBAL VARIABLES
    //------------------------------------------------------------------
    var CdrWebServer = "https://cdr-dev.cancer.gov";
    var CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
    var lastMarkupLevel = '';
    var CdrUserPath = '';

    var blobLinkElementNames = [
        "MediaLink",
        "SupplementaryInfo"
    ];

    // To be overridden by successful logon.
    var CdrUserName = "";
    var CdrSession  = "";
    var CdrHostName = "";
    try {
        if (cdrObj) {
            try {
                CdrUserPath  = cdrObj.userPath;
            }
            catch (e) {
                // Older versions of the DLL don't have the userPath
                // attribute.  Only users running with the client
                // files stored in the Program Files area next to
                // the XMetaL software will have the older CDR DLL.
                CdrUserPath = Application.Path;
            }
            CdrHostName  = cdrObj.hostname;
            CdrSession   = cdrObj.session;
            CdrUserName  = cdrObj.username;
            if (CdrHostName) {
                CdrWebServer = "https://" + CdrHostName;
                CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
            }
        }
    }
    catch (ignoreMe) {}


    // Clipboard for CDR links and blocks.
    var CdrFragLinkClipboard = "";
    var CdrFragIdClipboard = "";
    var CdrOrgAddressClipboard = null;

    /*
     * Find the path of the element enclosing the caller's selection.
     */
    function getSelectionPath(sel) {
        var path = '';
        var sep = '';
        for (var depth = 0; depth < 999; ++depth) {
            name = sel.ElementName(depth);
            if (!name) return "/" + path;
            path = name + sep + path;
            sep = "/";
        }
    }

    function padNumber(number, length, padChar) {
        var str = '' + number;
        while (str.length < length)
            str = padChar + str;
        return str;
    }

    /*
     * Find a singly-occurring element under a specified node.
     * Can also be used for multiply-occurring elements by
     * specifying a target value for one of the element's attributes.
     */
    function getSingleElement(node, name, attrName, attrValue) {
        var elems = node.getElementsByTagName(name);
        for (var i = 0; i < elems.length; ++i) {
            var elem = elems.item(i);
            if (!attrName || elem.getAttribute(attrName) == attrValue)
                return elem;
        }
        return null;
    }

    /*
     * Produce a string representation of a Javascript object.  The
     * optional indent argument is used by the recursive calls for
     * nested levels of the object.
     */
    function dump(me, indent) {
        if (!indent) indent = "";
        var more = "    ";
        switch (me.constructor) {
        case Array:
            result = "[\n";
            for (var i = 0; i < me.length; i++)
                result += indent + more + dump(me[i], indent + more) + "\n";
            return result + indent + "]";
        case Object:
            result = "{\n";
            for (var i in me) {
                result += indent + more + i + ": " +
                    dump(me[i], indent + more) + "\n";
            }
            return result + indent + "}";
        default:
            return me;
        }
    }

    /*
     * Oddly, Javascript doesn't have a builtin way to determine whether
     * a particular value is present in an array.  This function fills
     * gap.
     */
    function inArray(needle, haystack) {
        for (var i = 0; i < haystack.length; ++i)
            if (haystack[i] == needle)
                return true;
        return false;
    }

    /*
     * Load an XML parser for external documents, if one is available.
     */
    function getXmlParser() {
        var versions = ["MSXML2.DOMDocument.6.0", "MSXML2.DOMDocument.4.0",
                        "MSXML2.DOMDocument", "MSXML.DOMDocument"];
        for (var i = 0; i < versions.length; ++i) {
            try { return new ActiveXObject(versions[i]); }
            catch (e) { ; }
        }
        throw new Error("no parser available");
    }

    /*
     * Fetch XML document from an HTTP(S) call for a URL.  Construct a
     * Javascript object for the document.  See objectFromNode() below
     * for a description of the optional forceArray argument.
     */
    function objectFromUrl(url, forceArray) {
        var response = cdrObj.fetchFromUrl(url);
        if (!response)
            throw "failure fetching from " + url;
        return objectFromXml(response, forceArray);
    }

    /*
     * Parse a serialized XML document and construct a Javascript object
     * from the resulting DOM tree.  See objectFromNode() below for a
     * description of the optional forceArray argument.
     */
    function objectFromXml(xml, forceArray) {
        var parser = getXmlParser();
        parser.loadXML(xml);
        if (parser.parseError.errorCode != 0) {
            var err = parser.parseError;
            throw new Error("parse failure: " + err.reason);
        }
        return objectFromNode(parser.documentElement, forceArray);
    }

    /*
     * Recursively extract values from an XML DOM element node, building up
     * and returning a Javascript object containing those values.  An optional
     * array of element names can be passed, to force values for that name
     * to be returned as an array instead of a single instance, even if there
     * is only one occurrence of the name found.
     */
    function objectFromNode(node, forceArray) {
        if (typeof(forceArray) === "undefined")
            forceArray = [];
        var values = {};
        var count = 0;
        var attrs = node.attributes;
        for (var i = 0; i < attrs.length; ++i) {
            var item = attrs.item(i);
            values[item.name] = [item.text];
            ++count;
        }
        var children = node.childNodes;
        for (var i = 0; i < children.length; ++i) {
            var child = children.item(i);
            if (child.nodeType == 1) {
                var name = child.nodeName;
                if (values[name] === undefined) {
                    values[name] = [];
                }
                values[name].push(objectFromNode(child, forceArray));
                ++count;
            }
        }
        if (!count)
            return node.text;
        for (name in values) {
            if (!inArray(name, forceArray) && values[name].length == 1)
                values[name] = values[name][0];
        }
        return values;
    }

    /*
     * Extracts the document ID from the current document.
     */
    function getDocId() {
        elem = getSingleElement(Application.ActiveDocument, 'DocId');
        if (!elem) return null;
        var val  = getTextContent(elem);
        if (val.length < 1) { return null; }
        return val;
    }

    /*
     * Extracts the CDR fragment ID for the enclosing block.
     */
    function getFragId() {
        var node   = Selection.ContainerNode;
        var depth  = 5;
        while (node) {
            if (depth-- < 1)
                return null;
            if (node.nodeType == 1) {
                var fragId = node.getAttribute("cdr:id");
                if (fragId.length > 0)
                    return fragId;
            }
            node = node.parentNode;
        }
        return null;
    }

    /*
     * Clone an node from one document for use in another.
     * Typically you have to turn off validation checking to use the
     * results of this function (for example, if only one instance of
     * a given element is allowed by the DTD/schema at a certain
     * location, and you're replacing the existing instance with
     * one cloned from another document using this function,
     * XMetaL's implementation of replaceChild() isn't intelligent
     * enough to know that the result of replacing one element node with
     * another element node of the same type will still be valid.
     * 2009-03-04 (RMK): added optional argument newName.
     * 2009-03-06 (RMK): added more information to exception thrown.
     */
    function cloneFor(newDoc, node, newName) {

        // Clone element (recursively).
        var n = newName ? newName : node.nodeName;
        // Application.Alert("name is '" + n + "'");
        var e = null;
        try {
            e = newDoc.createElement(n);
        }
        catch (ex) {
            throw new Error("Failure cloning " + n + ": " + ex.message);
        }

        // Pop in the attributes from the source element.
        for (var i = 0; i < node.attributes.length; ++i) {
           var attr = node.attributes.item(i);
           if (attr.name != 'cdr:id')
               e.setAttribute(attr.name, attr.value)
        }

        // Copy in clones of the child nodes.
        var child = node.firstChild;
        while (child) {
            var clone = null;
            if (child.nodeType == 1)
                clone = cloneFor(newDoc, child)
            else if (child.nodeType == 3)
                clone = newDoc.createTextNode(child.nodeValue);
            else if (child.nodeType == 4)
                clone = newDoc.createCDATASection(child.nodeValue);
            else if (child.nodeType == 7)
                clone = newDoc.createProcessingInstruction(child.target,
                                                           child.data);
            else if (child.nodeType == 8)
                clone = newDoc.createComment(node.nodeValue);
            if (clone)
                e.appendChild(clone);
            child = child.nextSibling;
        }
        return e;
    }

    /*
     * Remove unwanted attributes from an element (and optionally
     * recursively from its children).  Prevents problems with
     * cloning between different document types.  The parameter
     * attrsToStrip is an object whose attributes represent names
     * of attributes to be dropped.  For example:
     * { "cdr:id": 1, PdqKey: 1 }
     */
    function stripAttributes(elem, attrsToStrip, recurse) {

        // Pop in the attributes from the source element.
        for (var i = 0; i < elem.attributes.length; ++i) {
           var attr = elem.attributes.item(i);
           if (attr.name in attrsToStrip)
               elem.removeAttribute(attr.name)
        }

        // Do this recursively if we're asked to.
        if (recurse) {
            var child = elem.firstChild;
            while (child) {
                if (child.nodeType == 1)
                    stripAttributes(child, attrsToStrip, true);
                child = child.nextSibling;
            }
        }
    }

    /*
     * Set selected attributes in selection to a new value.
     */
    function setNewAttrVal(selection, e_name, a_name, a_val) {
        var count = 0;
        var cursor = selection.Duplicate;
        cursor.Collapse();
        var moved = cursor.MoveToElement(e_name);
        while (moved) {
            if (selection.Contains(cursor)) {
                count++;
                var elem = cursor.ContainerNode;
                elem.setAttribute(a_name, a_val);
            }
            moved = cursor.MoveToElement(e_name);
        }
        return count;
    }

    /*
     * Set selected attributes in selection's revision markup elements
     * to a new value.
     */
    function setRevMarkupAttrs(selection, name, val) {
        return setNewAttrVal(selection, "Insertion", name, val) +
               setNewAttrVal(selection, "Deletion", name, val);
    }

    /*
     * Extracts the version number (if any) from the open document.
     */
    function getDocVersion() {
        if (!Application.ActiveDocument) { return null; }
        var name = Application.ActiveDocument.Name;
        var pos  = name.indexOf('-V');
        if (pos > 0) {
            var period = name.indexOf('.', pos + 2);
            var ver    = name.substring(pos + 2, period);
            if (ver) return ver;
        }
        return null;
    }

    /*
     * Returns boolean flag indicating whether document has been blocked.
     */
    function docIsBlocked() {
        var doc = Application.ActiveDocument;
        if (!doc)
            return false;
        var nodes = doc.getElementsByTagName("CdrDocCtl");
        if (nodes.length < 1)
            return false;
        var elem = nodes.item(0);
        return elem.getAttribute('blocked') == 'Y';
    }

    /*
     * Produce string containing current date as YYYY-MM-DD string.
     */
     function getCurDateString() {
        var d = new Date();
        var str = padNumber(d.getFullYear(), 4, '0') + '-'
                + padNumber(d.getMonth() + 1, 2, '0') + '-'
                + padNumber(d.getDate(), 2, '0');
        return str;
    }

    /*
     * Produce string containing current time as hh:mm:ss string.
     */
    function getCurTimeString() {
        var d = new Date();
        var str = padNumber(d.getHours(), 2, '0') + ':'
                + padNumber(d.getMinutes(), 2, '0') + ':'
                + padNumber(d.getSeconds(), 2, '0');
        return str;
    }

    /*
     * Produce string containing current date/time in XSD format.
     */
    function getCurDateTimeString() {
        var d = new Date();
        var str = padNumber(d.getFullYear(), 4, '0') + '-'
                + padNumber(d.getMonth() + 1, 2, '0') + '-'
                + padNumber(d.getDate(), 2, '0') + 'T'
                + padNumber(d.getHours(), 2, '0') + ':'
                + padNumber(d.getMinutes(), 2, '0') + ':'
                + padNumber(d.getSeconds(), 2, '0');
        return str;
    }

    /*
     * Utility function to extract the text content of an element.
     */
    function getTextContent(elem) {
        var textContent = "";
        var child = elem.firstChild;
        while (child) {
            if (child.nodeType == 3) { // Text node
                textContent += child.nodeValue;
            }
            child = child.nextSibling;
        }
        return textContent;
    }

    /*
     * Obtains account credentials from the user and submits them to the CDR
     * server to establish a logged in session.
     */
    function cdrLogon() {
        CdrUserName = "";
        cdrObj = new ActiveXObject("Cdr.Commands");
        if (cdrObj == null) {
            Application.Alert("Unable to find CDR DLL.");
        }
        else {
            //Application.Alert("Sorry, doing a little debugging here ...");
            cdrObj.logon();
            CdrUserName = cdrObj.username;
            CdrSession  = cdrObj.session;
            CdrHostName = cdrObj.hostname;
            if (CdrHostName) {
                CdrWebServer = "https://" + CdrHostName;
                CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
            }
            try {
                CdrUserPath  = cdrObj.userPath;
            }
            catch (e) {
                // Older versions of the DLL don't have the userPath
                // attribute.  Only users running with the client
                // files stored in the Program Files area next to
                // the XMetaL software will have the older CDR DLL.
                CdrUserPath = Application.Path;
            }
            cdrObj.setTitleBar();
        }
    }

    /*
     * Log the user out of the CDR server.
     */
    function cdrLogoff() {
        CdrUserName = "";
        CdrSession  = "";
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            var rc  = cdrObj.logoff();
            if (rc == 0) {
                Application.Alert("Session successfully logged off.");
                cdrObj = null;
            }
        }
    }

    /*
     * Determine whether the document is read-only.
     */
    function cdrDocReadOnly() {
        if (ActiveDocument == null)                   { return 0; }
        if (ActiveDocument.documentElement == null)   { return 0; }
        if (ActiveDocument.documentElement.getAttribute("readonly") == "yes")
                                                      { return 1; }
        return 0;
    }

    /*
     * Determine whether the current element should be read-only.
     */
    function cdrIsReadOnly() {
        if (gEditingCdrLink)                          { return 0; }
        if (ActiveDocument == null)                   { return 0; }
        if (ActiveDocument.documentElement == null)   { return 0; }
        if (ActiveDocument.documentElement.getAttribute("readonly") == "yes")
                                                      { return 1; }
        if (ActiveDocument.doctype == null)           { return 0; }
        if (Selection.ContainerNode == null)          { return 0; }
        if (Selection.ContainerNode.nodeName == null) { return 0; }
        if (Selection == null)                        { return 0; }
        if (cdrObj == null)                           { return 0; }
        var dtName = ActiveDocument.doctype.name;
        var elName = Selection.ContainerNode.nodeName;
        if (elName == "DocId" || elName == "DocType") { return 1; }
        if (dtName == "Mailer") {
            //Application.Alert('[' + elName + ']');
            if (elName == "Received" ||
                elName == "ChangesCategory" ||
                elName == "Response" ||
                elName == "Comment"  ||
                elName == "CallLog"  ||
                elName == "Resolution")
                return 0;
            return 1;
        }
        /*
         * XXX We cannot use the following DLL method to block
         *     editing of linking elements without disabling the
         *     feature of inserting a new occurrence of a repeating
         *     element by pressing the Enter key.  Lakshmi has
         *     agreed that it is preferable to keep the latter
         *     feature.
         */
        // return cdrObj.isReadOnly(dtName, elName);

        return 0;
    }

    function switchCSS(from, to) {
        try {
            var fso = new ActiveXObject("Scripting.FileSystemObject");
        }
        catch (exception) {
            Application.Alert("SwitchCSS Failure: " +
                    "\nFailed to invoke Scripting.FileSystemObject" +
                    "\nWindows Scripting Host needs to be installed.");
        }
        try {
            var xmPath   = CdrUserPath;
            var fromPath = xmPath + "/display/" + from;
            var toPath   = xmPath + "/display/" + to;
            if (fso.FileExists(fromPath)) {
                var sourceFile = fso.GetFile(fromPath);
                sourceFile.Copy(toPath);
                ActiveDocument.RefreshCssStyle();
            }
            else {
                Application.Alert("SwitchCSS Failure: " +
                        from + " does not exist");
            }
        }
        catch (exception) {
            Application.Alert("SwitchCSS Failure: " + exception +
                    "\nFailed to switch to " + from);
        }
    }

    /*
     * Allows the user to modify a linking element.
     */
    function cdrEdit() {
        if (cdrDocReadOnly()) {
            Application.Alert("Document retrieved as read-only.");
        }
        else if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {

            // Prevent On_Update_UI macro from blocking our editing.
            gEditingCdrLink = true;
            oldFlag = Selection.ReadOnlyContainer;
            Selection.ReadOnlyContainer = false;
            var rc  = cdrObj.edit();
            if (!rc) {
                dumpXmPis();
                Selection.SelectContainerContents();
                Selection.MoveRight(0);
            }
            Selection.ReadOnlyContainer = oldFlag;
            gEditingCdrLink = false;
        }
    }

    /*
     * Allows the user to abandon changes to the current document.
     */
    function cdrCheckIn() {
        if (cdrObj == null)
            Application.Alert("You are not logged on to the CDR");
        else
            cdrObj.checkIn();
    }

    /*
     * Remove any XMetaL processing instructions for placeholder data.
     */
    function dumpXmPis() {
        if (Selection) {
            if (Selection.ContainerNode) {
                var elem = Selection.ContainerNode;
                var child = elem.firstChild;
                while (child) {
                    var nextChild = child.nextSibling;
                    if (child.nodeType == 7) {
                        if (child.target == "xm-replace_text") {
                            elem.removeChild(child);
                        }
                    }
                    child = child.nextSibling;
                }
            }
        }
    }

    function getElemRange(elemName) {

        // Find out where we are.
        var rng = ActiveDocument.Range;

        // Make sure what we find is an ancestor of the current element.
        if (!rng.IsParentElement(elemName))
            return null;

        // Move.
        if (!rng.MoveToElement(elemName, false))
            return null;
        else
            return rng;
    }

    function insertAnother(parentName, elemName, str) {
        var rng = getElemRange(parentName);
        if (!rng) { return false; }
        rng.SelectElement();
        rng.Collapse(0);
        if (!rng.FindInsertLocation(elemName, false)) { return false; }
        if (!str) {
            str = "<" + elemName + "/>";
        }
        rng.PasteString(str);
        rng.MoveToElement(elemName, false);
        rng.SelectElement();
        rng.Collapse(1);
        rng.MoveRight();
        rng.Select();
        return true;
    }

    function publishPreview(flavor) {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "PublishPreview.py?Session="
                + CdrSession + "&DocId=" + docId;
        if (flavor)
            url += "&Flavor=" + flavor;
        var ver = getDocVersion();
        if (ver)
            url += "&Version=" + ver;
        else
            url += "&Version=cwd";

        if (ActiveDocument.doctype.name == "Summary")
            url += "#section/all";

        cdrObj.showPage(url);
    }

  ]]>
</MACRO>

<MACRO  name="On_Update_UI"
        hide="true"
        lang="JScript">
  <![CDATA[

    // This workaround is being used because SoftQuad is unable or
    // unwilling to fix the bug which is wiping out our setting of
    // the Visible property of the document-specific toolbar in the
    // On_Document_Activate event.
    function adjustToolbars2() {
        var docType = ActiveDocument.doctype;
        if (toolbars[docType.name] != null) {
            toolbars[docType.name].Visible = true;
        }
    }
    if (Application.VersionNumber < 4.5)
        adjustToolbars2();

    // this will only work if no On_Update_UI macro is defined for the DTD
    if (Selection.IsInsertionPoint && ActiveDocument.ViewType == 1) {
        // this should only apply to the tags-on view, and allow selection
        // of the top-level element
       if (Selection.ContainerNode == null) {
          Selection.MoveRight();
       }
       if (Selection.ContainerNode == null) {
          Selection.MoveLeft();
       }
    }

    if (Selection) {
        if (cdrIsReadOnly()) {
            Selection.ReadOnlyContainer = true;
        }
        else {
            Selection.ReadOnlyContainer = false;
            Selection.WritePermittedContainer = true;
        }
    }


    if (ActiveDocument == null
    ||  ActiveDocument.documentElement == null
    ||  ActiveDocument.documentElement.getAttribute("readonly") == "yes")
        Application.DisableMacro("Cdr Save");

    if (Documents.Count > 0 && cdrObj) cdrObj.setTitleBar();
  ]]>
</MACRO>

<MACRO  name="Refresh Macros"
        key="Ctrl+Alt+R"
        lang="JScript"
        id="1270"
        tooltip=""
        desc="">
  <![CDATA[
    Application.RefreshMacros();
    Application.Alert("Macros have been refreshed");
  ]]>
</MACRO>

<MACRO  lang="JScript"
        name="Open Document Macros"
        id="1272">
  <![CDATA[
    var count = Application.Documents.Count;
    if (count == 0) {
        Application.Alert("No Open Document");
    }
    else {
        var mpath = ActiveDocument.MacroFile;
        Documents.Open(mpath, 1);  // open in tags on view
    }
  ]]>
</MACRO>

<MACRO  name="Open Application Macros"
        lang="JScript"
        id="1274">
  <![CDATA[
    var mpath = Application.MacroFile;
    Documents.Open(mpath, 1); // open in tags on view
  ]]>
</MACRO>

<MACRO  name="On_Application_Open"
        hide="true"
        lang="JScript">
    /*
     * Initialize global variables for CDR macros.
     */
    var gEditingCdrLink = false;
    var cdrObj = null;
    cdrLogon();
    //Application.DisablePlainTextView();
</MACRO>

<MACRO  name="On_Application_Open_Complete"
        hide="true"
        lang="JScript">
    turnOffStandardToolbars();
    if (cdrObj != null)
        cdrObj.setTitleBar();
</MACRO>

<MACRO  name="On_Application_Close"
        hide="true"
        lang="JScript">
    /*
     * Close the connection to the CDR Server.
     */
    if (cdrObj != null) {
        cdrObj.logoff();
    }
</MACRO>

<MACRO  name="On_Mouse_Over"
        lang="JScript"
        hide="true">
  <![CDATA[
    // Reset the Status Text and the Cursor in case a different
    // document changed them and they are stuck.
    function OnMouseOver()
    {
        Application.SetStatusText("");
        Application.SetCursor(0);
    }
    OnMouseOver();
  ]]>
</MACRO>

<MACRO name="On_DTD_Open_Complete"
       key=""
       hide="false"
       lang="JScript">
         <![CDATA[

    function doAddElements() {

        // In this macro the new document is not yet the active document,
        // so this is how we get to its document type.
        docType  = Application.NewDocumentType;
        rootElem = docType.name;

        // Add a new attribute for CDR issue #2730.
        docType.addEnumeratedAttribute("CdrDocCtl", "blocked",
            "Indicates whether the document has been marked 'Inactive'",
            9, // ordinary enumeration
            2, // default value is explicitly specified
            "N", "N", "Y");
        // Add the Deletion element.
        docType.addElement("Deletion", "Deletion", true , false);
        docType.addAttribute("Deletion", "UserName", "", 0, 0);
        docType.addAttribute("Deletion", "Time", "", 0, 0);
        docType.addEnumeratedAttribute("Deletion", "RevisionLevel",
            "Indicates status of proposed deletion", 9, // ordinary enumeration
            2, // default value is explicitly specified
            "approved", "approved", "proposed", "publish", "rejected");
        docType.addEnumeratedAttribute("Deletion", "Source",
            "Used to tag deletions submitted by an Advisory Board member",
            9, 0, // attribute is optional (#IMPLIED)
            "advisory-board", // this is ignored because attr-type is 0
            "advisory-board", "editorial-board");

        // Add the Insertion element.
        docType.addElement("Insertion", "Insertion", true , false);
        docType.addAttribute("Insertion", "UserName", "", 0, 0);
        docType.addAttribute("Insertion", "Time", "", 0, 0);
        docType.addEnumeratedAttribute("Insertion", "RevisionLevel",
            "Indicates status of proposed insertion", 9, //ordinary enumeration
            2, // default value is explicity specified
            "approved", "approved", "proposed", "publish", "rejected");
        docType.addEnumeratedAttribute("Insertion", "Source",
            "Used to tag insertions submitted by an Advisory Board member",
            9, 0, // attribute is optional (#IMPLIED)
            "advisory-board", // this is ignored because attr-type is 0
            "advisory-board", "editorial-board");

        // Add the element to markup up unwanted private use characters.
        docType.addElement("cdr:PrivateUseCharacter", "cdr:PrivateUseCharacter",
                           true, false);

        // Allow these elements anywhere.
        if (docType.hasElementType(rootElem)) {
            if (docType.hasElementType("Deletion")) {
                docType.addElementToInclusions("Deletion", rootElem);
            }
            if (docType.hasElementType("Insertion")) {
                docType.addElementToInclusions("Insertion", rootElem);
            }
            if (docType.hasElementType("cdr:PrivateUseCharacter")) {
                docType.addElementToInclusions("cdr:PrivateUseCharacter",
                                               rootElem);
            }
        }

        // Allow the cdr-eid attribute everywhere.
        var n = docType.elementTypes.ubound();
        for (var i = 0; i < n; ++i) {
            docType.addAttribute(docType.elementType(i), "cdr-eid", "", 1, 0);
        }
    }

    doAddElements();

  ]]>
</MACRO>

<MACRO  name="On_Document_Open_Complete"
        hide="true"
        lang="JScript">
<![CDATA[
    //Application.Alert("entering On_Document_Open_Complete");

    /* Request #2730
     */
    if (!docIsBlocked()) {

    Selection.GotoNext(0);
    Selection.GotoNext(0);
    Selection.SelectContainerContents();

    /* } */
    }

    var docProps = ActiveDocument.CustomDocumentProperties;
    docProps.Add("Highlighting", true);
    docProps.Add("ShowOriginal", false);
    docProps.Add("InsNextPrev", false);
    docProps.Add("DelNextPrev", false);
    Application.Run("Init_JScript_Macros");
    //Application.Alert("leaving On_Document_Open_Complete");
]]>
</MACRO>


<MACRO  name="On_Context_Menu" lang="JScript">
  <![CDATA[
    // See comment on Build CDR Context Menu below.
    if (Application.VersionNumber < 9.0)
        Application.Run("Build CDR Context Menu")
]]>
</MACRO>

<MACRO  name="On_Application_Document_Context_Menu" lang="JScript">
  <![CDATA[
    // See comment on Build CDR Context Menu below.
    if (Application.VersionNumber > 4.5)
        Application.Run("Build CDR Context Menu")
]]>
</MACRO>

<MACRO  name="Build CDR Context Menu" lang="JScript">
  <![CDATA[

    // XMetaL 9.0 broke the use of On_Context_Menu, so now we wire
    // this functionality to different macros, depending on which
    // version of XMetaL is running.

    /*
     * Adds a menu option to the popup context menu for custom editing
     * of a link element.
     */
    var container = Selection.ContainerNode;
    var docType = ActiveDocument.doctype;
    var rng = ActiveDocument.Range;
    var isReadOnly = cdrDocReadOnly();
    Application.AppendMacro("-", "");
    Application.AppendMacro("&Edit Element", "Cdr Edit");
    Application.AppendMacro("Linked Fragment Docs Report",
                            "Linked Fragment Docs Report");
    Application.AppendMacro("Copy Fragment Link", "Cdr Copy Fragment Link");
    Application.AppendMacro("Paste Fragment Link", "Cdr Paste Fragment Link");
    if (container && container.nodeType == 1) { // we're in an element?
        if (docType.hasAttribute(container.nodeName, "Public")) {
            if (container.getAttribute("Public") == "No")
                Application.AppendMacro("Remove Public=No", "Set Public");
            else
                Application.AppendMacro("Make Public=No", "Set Non-Public");
        }
        var linkId = container.getAttribute("cdr:ref");
        if (!linkId)
            linkId = container.getAttribute("cdr:href");
        if (linkId && linkId.indexOf("CDR") >= 0) {
            Application.AppendMacro("Open &Link For Editing",
                                    "Open Linked Doc Edit Mode");
            Application.AppendMacro("Open Link &Readonly",
                                    "Open Linked Doc View Mode");
        }
    }
    if (docType.name == "Summary") {
        if (Selection.IsParentElement("GlossaryTermRef"))
            Application.AppendMacro("Add Glossary Phrase",
                                    "Add Glossary Phrase");
    }
    if (docType.name == "Person") {
        Application.AppendMacro("Retrieve Org Postal Address",
                                "CDR Get Org Postal Address");
        Application.AppendMacro("Copy Fragment ID", "Cdr Copy Fragment ID");
    }
    if (docType.name == "Organization") {
        if (Selection.IsParentElement("Location")) {
            Application.AppendMacro("Persons Linking to This Location",
                "CDR Persons Linking to Org Address Fragment");
            Application.AppendMacro("Remember Postal Address",
                                    "Remember Org Postal Address")
        }
    }
    if (docType.name == "PDQBoardMemberInfo") {
        if (rng.IsParentElement("PersonContactID")) {
            Application.AppendMacro("Paste Fragment ID",
                                    "Cdr Paste Fragment ID");
        }
    }
    for (var i in blobLinkElementNames) {
        if (rng.IsParentElement(blobLinkElementNames[i])) {
            Application.AppendMacro("Show Linked Object",
                                    "Show Linked Blob");
            break;
        }
    }
    if (rng.FindInsertLocation("Comment")) {
        Application.AppendMacro("Insert Comment", "Insert Comment");
    }
    if (rng.FindInsertLocation("ResponseToComment")) {
        Application.AppendMacro("Insert ResponseToComment",
                                "Insert ResponseToComment");
    }
    if (docType.name == 'Summary' && (
        Selection.IsParentElement('ProtocolRef') ||
        Selection.IsParentElement('ProtocolLink') ||
        Selection.IsParentElement('CitationRef') ||
        Selection.IsParentElement('CitationLink'))) {
        if (!isReadOnly) {
            Application.AppendMacro("Edit Comment", "Edit Comment");
            Application.AppendMacro("Set Last Reviewed Date Attribute",
                                    "Set Last Reviewed Date");
        }
        else
            Application.AppendMacro("View Comment", "Edit Comment");
    }
    if (!isReadOnly && docType.name == "Summary" && getDocId()) {
        var nodes = ActiveDocument.getElementsByTagName("TranslationOf");
        if (nodes.length == 1) {
            Application.AppendMacro("-", "");
            Application.AppendMacro("Spanish Link ID Swap",
                                    "Spanish Link ID Swap");
        }
    }
    if (!isReadOnly) {
        // OCECDR-3958
        Application.AppendMacro("Set Source to Advisory Board",
                                "Set Source to Advisory Board");
        Application.AppendMacro("Set Source to Editorial Board",
                                "Set Source to Editorial Board");

        Application.AppendMacro("Apply Revision Level", "Apply Revision Level");
    }
    Application.AppendMacro("Character Count", "Count Characters");
  ]]>
</MACRO>

<MACRO  name="On_Default_CommandBars_Complete"
        key=""
        lang="JScript">
  <![CDATA[

    /*
     * Make sure none of our doctype-specific toolbars is visible except
     * the ones that match the document type of the active document.
     * Used for XMetaL 9.0 and later.
     */
    function adjustToolbarVisibility() {
        if (!Application.CommandBars)
            return;
        var currentDoctype = "";
        if (ActiveDocument && ActiveDocument.doctype)
            currentDoctype = ActiveDocument.doctype.name;
        var bars = Application.CommandBars;
        for (var i = 1; i <= bars.Count; ++i) {
            var bar = bars.item(i);
            if (bar.name in toolbarNames)
                bar.Visible = currentDoctype in toolbarNames[bar.name];
            else if (bar.name == "Standard" || bar.name == "Repository")
                bar.Visible = false;
            else if (bar.name == "Main Menu")
                bar.Visible = true;
        }
    }

    /*
     * Constructor for a custom menu or toolbar item.
     */
    function CdrCmdItem(label, action, tip, desc, iconSet, row, col, newGroup)
    {
        this.label    = label;
        this.action   = action;
        this.tip      = tip;
        this.desc     = desc;
        this.row      = row;
        this.col      = col;
        this.iconSet  = iconSet;
        this.newGroup = newGroup;
    }

    function addCdrButton(ctrls, item) {

        // Create a new button.
        var newButton = ctrls.Add();

        // Set the new item's attributes.
        if (newButton != null) {
            newButton.OnAction         = item.action;
            newButton.TooltipText      = item.tip;
            newButton.Enabled          = true;
            newButton.DescriptionText  = item.desc;
            newButton.BeginGroup       = item.newGroup;
            if (item.iconSet != null) {
                newButton.FaceId       = Application.MakeFaceId(item.iconSet,
                                                                item.row,
                                                                item.col);
            }
        }
        else {
            Application.Alert("Unable to create \""+action+"\" button.");
        }
        /*
        var faceId = Application.MakeFaceId("CDR", row, col);
        var b = ctrls.add();
        if (sep) { b.BeginGroup = true; }
        b.TooltipText = tip;
        b.DescriptionText = desc;
        b.FaceId = faceId;
        b.OnAction = cmd;
        */
    }

    /*
     * Adds a single CDR menu choice.  Invoked by addCdrMenu() below.
     */
     function addCdrMenuItem(menuControls, item) {

        // Create a new menu item.
        var newItem = menuControls.Add(sqcbcTypePopup);

        // Set the new item's attributes.
        if (newItem != null) {
            newItem.OnAction        = item.action;
            newItem.TooltipText     = item.tip;
            newItem.DescriptionText = item.desc;
            newItem.Caption         = item.label;
            newItem.Enabled         = true;
            newItem.BeginGroup      = item.newGroup;
            if (item.iconSet  != null) {
                newItem.FaceId      = Application.MakeFaceId(item.iconSet,
                                                             item.row,
                                                             item.col);
            }
        }
        else {
            Application.Alert("Unable to create \""+action+"\" menu item.");
        }
    }

    /*
     * Drop any old versions of the menus.
     */
    function dropOldMenu(menuName) {

        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;

        // Get rid of the old menu.
        var menu = menuControls.item(menuName);
        while (menu != null) {
            Application.Alert("deleting menu [" + menuName + "]");
            menu.Delete();
            menu = menuBar.Controls.item(menuName);
        }
        Application.Alert("finished deleting all " + menuName + " menus");
    }

    /*
     * Add main CDR menu.
     */
    function addCdrMenu(menuControls, beforeThis) {

        var menuItems = new Array(
            new CdrCmdItem("&New CDR Document",         // Label.
                           "New CDR Document",          // Macro.
                           "Create New CDR Document",   // Tooltip.
                           "Create New CDR Document",   // Description.
                           "CDR", 3, 9,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem("&Retrieve",
                           "Cdr Retrieve",
                           "Retrieve",
                           "Retrieve an existing CDR document by document ID",
                           "CDR", 4, 7,
                           false),
            new CdrCmdItem("S&earch",
                           "Cdr Search",
                           "Search for CDR Document",
                           "Search for CDR Document",
                           "CDR", 3, 1,
                           false),
            new CdrCmdItem("&Advanced Search",
                           "CDR Advanced Search",
                           "Advanced Search",
                           "Launch browser-based CDR search form",
                           "CDR", 3, 2,
                           false),
            new CdrCmdItem("Prin&t",
                           "Print",
                           "Print",
                           "Print the current document",
                           "CDR", 1, 10,
                           true),
            /*
            new CdrCmdItem("&Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            */
            new CdrCmdItem("&Validate",
                           "Cdr Validate",
                           "Validate",
                           "Validate the current CDR document",
                           "CDR", 4, 1,
                           true),
            new CdrCmdItem("&Save",
                           "Cdr Save",
                           "Save",
                           "Save the current CDR document",
                           "CDR", 3, 10,
                           false),
            new CdrCmdItem("&Unlock",
                           "CDR Check In",
                           "Unlock",
                           "Unlock the current CDR document",
                           "CDR", 6, 6,
                           false),
            new CdrCmdItem("Ad&ministrative Subsystem",
                           "Administrative Subsystem",
                           "Administrative Subsystem",
                           "Invoke the web-based CDR Administration menu",
                           "Databases (Custom)", 2, 10,
                           true),
            new CdrCmdItem("CDR &Help",
                           "CDR Help",
                           "CDR Help",
                           "Launch the CDR Help System",
                           "CDR", 4, 2,
                           true)
        );

        var menu = menuControls.Add(sqcbcTypePopup, null, beforeThis);
        menu.Caption = "&CDR";

        // Add the menu items.
        var controls = menu.Controls;
        for (var i = 0; i < menuItems.length; ++i) {
            addCdrMenuItem(controls, menuItems[i]);
        }
    }

    /*
     * Add CDR style menu.
     */
    function addCdrStyleMenu(menuControls, beforeThis) {

        var menuItems = new Array(
            new CdrCmdItem("&Insertion",                // Label.
                           "Insertion",                 // Macro.
                           "Insertion",                 // Tooltip.
                           "Add Insertion markup",      // Description.
                           "CDR", 1, 6,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem("&Deletion",
                           "Deletion",
                           "Deletion",
                           "Add Deletion markup",
                           "CDR", 1, 7,
                           false),
            new CdrCmdItem("Itemized &List",
                           "Itemized List",
                           "Itemized List",
                           "Insert itemized list",
                           "CDR", 6, 1,
                           true),
            new CdrCmdItem("&Ordered List",
                           "Ordered List",
                           "Ordered List",
                           "Insert ordered list",
                           "CDR", 6, 2,
                           false),
            new CdrCmdItem("&Table",
                           "Table",
                           "Table",
                           "Invoke XMetaL table wizard",
                           "CDR", 5, 9,
                           false),
            new CdrCmdItem("D&ate",
                           "Insert Current Date",
                           "Date",
                           "Insert current date",
                           "CDR", 6, 8,
                           false),
            new CdrCmdItem("&User",
                           "Insert User ID",
                           "User",
                           "Insert user ID",
                           "CDR", 5, 10,
                           false),
            new CdrCmdItem("D&rug Name",
                           "Insert DrugName Element",
                           "Drug Name",
                           "Add DrugName element tags to current selection",
                           null, 0, 0,
                           true),
            new CdrCmdItem("&Foreign Word",
                           "Insert ForeignWord Element",
                           "Foreign Word",
                           "Add ForeignWord element tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("&Gene Name",
                           "Insert GeneName Element",
                           "Gene Name",
                           "Add GeneName element tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("S&cientific Name",
                           "Insert ScientificName Element",
                           "Scientific Name",
                           "Add ScientificName tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("&Emphasis",
                           "Insert Emphasis Element",
                           "Emphasis",
                           "Add Emphasis element tags to current selection",
                           null, 0, 0,
                           true),
            new CdrCmdItem("&Strong",
                           "Insert Strong Element",
                           "Strong",
                           "Add Strong element tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("Su&bscript",
                           "Insert Subscript Element",
                           "Subscript",
                           "Add Subscript element tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("Su&perscript",
                           "Insert Superscript Element",
                           "Superscript",
                           "Add Superscript element tags to current selection",
                           null, 0, 0,
                           false)
        );

        menu = menuControls.Add(sqcbcTypePopup, null, beforeThis);
        menu.Caption = "CDR &Styles";

        // Add the menu items.
        var controls = menu.Controls;
        for (var i = 0; i < menuItems.length; ++i) {
            addCdrMenuItem(controls, menuItems[i]);
        }
    }

    /*
     * Add CDR markup menu.
     */
    function addCdrMarkupMenu(menuControls, beforeThis) {

        var menuItems = new Array(
            new CdrCmdItem("Find &Next Change",         // Label.
                           "Find Next",                 // Macro.
                           "Find Next Change",          // Tooltip.
                           "Find next markup change",   // Description.
                           "CDR", 1, 8,                 // Icon set, row, col.
                           false),                      // Starts new group?
            /*
            new CdrCmdItem("Find &Previous Change",
                           "Find Prev",
                           "Find Previous Change",
                           "Find previous markup change",
                           "CDR", 1, 9,
                           false),
            */
            new CdrCmdItem("&Accept Change",
                           "Accept Change",
                           "Accept Change",
                           "Accept current markup change",
                           "CDR", 2, 6,
                           true),
            new CdrCmdItem("A&ccept All Changes",
                           "Accept Changes",
                           "Accept All Changes",
                           "Accept all markup changes",
                           "CDR", 2, 7,
                           false),
            new CdrCmdItem("&Reject Change",
                           "Reject Change",
                           "Reject Change",
                           "Reject current markup change",
                           "CDR", 2, 8,
                           false),
            new CdrCmdItem("&Back Out Rejected Changes",
                           "Back Out Rejected Markup",
                           "Back Out Rejected Changes",
                           "Back out rejected tracked changes",
                           "Design (Custom)", 4, 10,
                           false),
            new CdrCmdItem("R&eview All Changes",
                           "Review Markup",
                           "Review Markup",
                           "Accept or Reject Changes",
                           null, 0, 0,
                           false)
        );

        menu = menuControls.Add(sqcbcTypePopup, null, beforeThis);
        menu.Caption = "CDR &Markup";

        // Add the menu items.
        var controls = menu.Controls;
        for (var i = 0; i < menuItems.length; ++i) {
            addCdrMenuItem(controls, menuItems[i]);
        }
    }

    function dropOldMenus() {
        // Prepare some local variables.
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;
        var i = 1;
        while (i <= menuControls.Count) {
        //  Application.Alert("menu count: " +
        //                    menuControls.Count + " i: " + i);
            var menu = menuControls.item(i);
            var caption = menu.Caption.toUpperCase();
            var pos = caption.indexOf("CDR");
            if (pos == 0 || pos == 1) {
                menu.Delete();
                //Application.Alert("Deleted " + caption);
            }
            else {
                ++i;
                // Application.Alert("Kept " + caption);
            }
        }
    }

    /*
     * Adds the CDR menus, first removing any old versions.
     */
    function addCdrMenus() {

        // Drop any old versions of the menus.
        //dropOldMenu("Cdr");
        //dropOldMenu("CDR");
        //dropOldMenu("CDR Style");
        //dropOldMenu("CDR Markup");
        dropOldMenus();

        // Prepare some local variables.
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;

        // Find the position of the Window menu
        var windMenu      = menuControls.item("Window");
        var windowMenuPos = menuControls.Count;
        while (windowMenuPos >= 1) {
            if (menuControls.item(windowMenuPos) == windMenu) {
                break;
            }
            windowMenuPos = windowMenuPos - 1;
        }
        if (windowMenuPos == 0) {
            windowMenuPos = menuControls.Count - 1;
        }

        // We have to insert these backwards to get them in the right order.
        addCdrMarkupMenu(menuControls, windowMenuPos);
        addCdrStyleMenu(menuControls, windowMenuPos);
        addCdrMenu(menuControls, windowMenuPos);
    }

    function addCdrToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "New CDR Document",          // Macro.
                           "New CDR Document",          // Tooltip.
                           "Create new CDR document",   // Description
                           "CDR", 3, 9,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Cdr Retrieve",
                           "Retrieve",
                           "Retrieve existing CDR document with document ID",
                           "CDR", 4, 7,
                           false),
            new CdrCmdItem(null,
                           "Cdr Search",
                           "Search",
                           "Search for an existing CDR document",
                           "CDR", 3, 1,
                           false),
            new CdrCmdItem(null,
                           "CDR Advanced Search",
                           "Advanced Search",
                           "Launch browser-based CDR search form",
                           "CDR", 3, 2,
                           false),
            new CdrCmdItem(null,
                           "Document History Report",
                           "Document History",
                           "Show Document History",
                           "CDR", 4, 8,
                           true),
            new CdrCmdItem(null,
                           "Audit Trail Report",
                           "Audit Trail",
                           "Show Audit Trail",
                           "Annotations (Custom)", 1, 6,
                           false),
            new CdrCmdItem(null,
                           "Show Checked Out Docs",
                           "Checked Out",
                           "Show Checked Out Docs",
                           "CDR", 1, 1,
                           false),
            new CdrCmdItem(null,
                           "Print",
                           "Print",
                           "Print the current document",
                           "CDR", 1, 10,
                           false),
            new CdrCmdItem(null,
                           "Cdr Validate",
                           "Validate",
                           "Validate the current CDR document",
                           "CDR", 4, 1,
                           false),
            new CdrCmdItem(null,
                           "Cdr Save",
                           "Save",
                           "Save the current document",
                           "CDR", 3, 10,
                           false),
            new CdrCmdItem(null,
                           "Administrative Subsystem",
                           "Administrative Subsystem",
                           "Invoke the web-based CDR Administration menu",
                           "Databases (Custom)", 2, 10,
                           false),
            /* Bug in XMetaL prevents this from working...
            new CdrCmdItem(null,
                           "Undo Last Edit",
                           "Undo",
                           "Undo Last Action",
                           "Standard", 2, 2,
                           true),
             */
            new CdrCmdItem(null,
                           "Insertion",
                           "Insertion",
                           "Add Insertion markup",
                           "CDR", 1, 6,
                           true),
            new CdrCmdItem(null,
                           "Deletion",
                           "Deletion",
                           "Add Deletion markup",
                           "CDR", 1, 7,
                           false),
            new CdrCmdItem(null,
                           "Find Next",
                           "Find Next",
                           "Find Next Change",
                           "CDR", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Accept Change",
                           "Accept Change",
                           "Accept Change",
                           "CDR", 2, 6,
                           false),
            new CdrCmdItem(null,
                           "Reject Change",
                           "Reject Change",
                           "Reject Change",
                           "CDR", 2, 8,
                           false),
            new CdrCmdItem(null,
                           "Navigate Comments",
                           "Find Comments",
                           "Find Comments",
                           "CDR2", 3, 3,
                           true),
            new CdrCmdItem(null,
                           "Itemized List",
                           "Itemized List",
                           "Insert itemized list",
                           "CDR", 6, 1,
                           true),
            new CdrCmdItem(null,
                           "Ordered List",
                           "Ordered List",
                           "Insert ordered list",
                           "CDR", 6, 2,
                           false),
            new CdrCmdItem(null,
                           "Insert Current Date",
                           "Current Date",
                           "Insert Current Date",
                           "CDR", 6, 8,
                           false),
            new CdrCmdItem(null,
                           "Insert User ID",
                           "User Name",
                           "Insert User ID",
                           "CDR", 5, 10,
                           false),
            /* For OCECDR-4188 */
            new CdrCmdItem(null,
                           "Find Private Use Chars",
                           "Find Private Use Unicode Characters",
                           "Find Private Use Unicode Characters",
                           "General (Custom)", 4, 10,
                           true),
            new CdrCmdItem(null,
                           "CDR Help",
                           "CDR Help",
                           "Launch the CDR Help System",
                           "CDR", 4, 2,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        /*
         XXX DEBUGGING CODE
        var i = 1;
        //Application.Alert("number of bars: " + cmdBars.count);
        while (i <= cmdBars.count) {
            //Application.Alert("looking at bar " + i);
            var bar = cmdBars.item(i);
            //Application.Alert("Found command bar: " + bar.name);
            try {
                if (bar.name == "CDR") {
                    bar.Delete();
                    Application.Alert("Deleted command bar " + bar.name);
                }
                else {
                    i++;
                }
            }
            catch (e) {
                Application.Alert("Failure deleting CDR bar: " + e);
                ++i;
            }
        }
        XXX END DEBUGGING CODE */


        try { cmdBar = cmdBars.item("CDR"); }
        catch (e) {
            //Application.Alert(e.description);
            //Application.Alert("Error number: " + (e.number & 0xFFFF));
            //Application.Alert("Error description: " + e.description);
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR", 2);
        }
        catch (e) {
            Application.Alert("Failure adding CDR toolbar: " + e);
        }
        if (cmdBar) {
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addSymbolToolbar() {
        var buttons = new Array(
    new CdrCmdItem(null, "SC Up", "Up", "Up", "CDR", 7, 2, false),
    new CdrCmdItem(null, "SC Down", "Down", "Down", "CDR", 7, 3, false),
    new CdrCmdItem(null, "SC Right", "Right", "Right", "CDR", 7, 5, false),
    new CdrCmdItem(null, "SC Left", "Left", "Left", "CDR", 7, 4, false),
    new CdrCmdItem(null, "SC alpha", "alpha", "alpha", "CDR", 7, 6, false),
    new CdrCmdItem(null, "SC beta", "beta", "beta", "CDR", 7, 7, false),
    new CdrCmdItem(null, "SC gamma", "gamma", "gamma", "CDR", 7, 8, false),
    new CdrCmdItem(null, "SC delta", "delta", "delta", "CDR", 7, 9, false),
    new CdrCmdItem(null, "SC mu", "mu", "mu", "CDR", 7, 10, false),
    new CdrCmdItem(null, "SC le", "</=", "</=", "CDR", 8, 1, false),
    new CdrCmdItem(null, "SC ge", ">/=", ">/=", "CDR", 8, 2, false),
    new CdrCmdItem(null, "SC copy", "(C)", "(C)", "CDR", 8, 3, false),
    new CdrCmdItem(null, "SC reg", "(R)", "(R)", "CDR", 8, 4, false),
    new CdrCmdItem(null, "SC TM", "TM", "TM", "CDR", 8, 5, false),
    new CdrCmdItem(null, "SC deg", "Degree", "Degree", "CDR", 8, 6, false),
    new CdrCmdItem(null, "SC cross", "Dagger", "Dagger", "CDR", 8, 7, false),
    new CdrCmdItem(null, "SC dblx", "DDagger", "DDagger", "CDR", 8, 8, false),
    new CdrCmdItem(null, "SC mdash", "Em Dash", "Em dash", "CDR", 8, 9, false),
    new CdrCmdItem(null, "SC plusmin", "+/-", "+/-", "CDR", 8, 10, false),
    new CdrCmdItem(null, "SC lapos", "LApos", "LApos", "CDR2", 1, 1, false),
    new CdrCmdItem(null, "SC rapos", "RApos", "RApos", "CDR2", 1, 2, false),
    new CdrCmdItem(null, "SC lquot", "LQuot", "LQuot", "CDR2", 1, 3, false),
    new CdrCmdItem(null, "SC rquot", "RQuot", "RQuot", "CDR2", 1, 4, false),
    new CdrCmdItem(null, "SC quarter", "1/4", "1/4", "CDR2", 1, 5, false),
    new CdrCmdItem(null, "SC half", "1/2", "1/2", "CDR2", 1, 6, false),
    new CdrCmdItem(null, "SC 3quart", "3/4", "3/4", "CDR2", 1, 7, false),
    new CdrCmdItem(null, "SC nbsp", "NBSP", "NBSP", "CDR2", 1, 8, false)
        );

        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        try { cmdBar = cmdBars.item("CDR Symbols"); }
        catch (e) {
            //Application.Alert(e.description);
            //Application.Alert("Error number: " + (e.number & 0xFFFF));
            //Application.Alert("Error description: " + e.description);
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR symbols " +
                                  "toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Symbols", 4);
        }
        catch (e) {
            Application.Alert("Failure adding CDR Symbols toolbar: " + e);
        }
        if (cmdBar) {
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addSummaryToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "New Summary Section",       // Macro.
                           "New Section",               // Tooltip.
                           "Insert new SummarySection", //Description
                           "General (Custom)", 5, 8,    // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Insert CitationLink",
                           "Citation Link",
                           "Insert Citation Link",
                           "CDR", 6, 9,
                           true),
            new CdrCmdItem(null,
                           "Insert DateLastModified",
                           "DateLastModified",
                           "Insert DateLastModified",
                           "CDR", 5, 2,
                           false),
            new CdrCmdItem(null,
                           "Bold Underline Report",
                           "HP B/U",
                           "Bold Underline Report",
                           "CDR", 2, 3,
                           true),
            new CdrCmdItem(null,
                           "Redline Strikeout Report",
                           "HP RLSO",
                           "Redline Strikeout Report",
                           "CDR", 2, 4,
                           false),
            new CdrCmdItem(null,
                           "Patient Summary BU QC Report",
                           "PT B/U",
                           "Patient Summary BU QC Report",
                           "CDR2", 2, 1,
                           false),
            new CdrCmdItem(null,
                           "Patient Summary RS QC Report",
                           "PT RLSO",
                           "Patient Summary RS QC Report",
                           "CDR", 3, 5,
                           false),
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Back Out Rejected Markup",
                           "Back Out Rejected Changes",
                           "Back out rejected tracked changes",
                           "Design (Custom)", 4, 10,
                           false),
            new CdrCmdItem(null,
                           "Find Next Advisory Board Markup",
                           "Find Next Advisory Board Markup",
                           "Find next Advisory Board markup",
                           "Databases (Custom)", 7, 4,
                           true),
            new CdrCmdItem(null,
                           "Open Patient Summary",
                           "Patient",
                           "Open patient version of this summary",
                           "CDR2", 3, 1,
                           true),
            new CdrCmdItem(null,
                           "Open HP Summary",
                           "HP",
                           "Open health professional version of this summary",
                           "CDR2", 3, 2,
                           false),
            new CdrCmdItem(null,
                           "Open Original English Summary",
                           "English",
                           "Open original English summary of which this " +
                           "is a translation",
                           "CDR2", 2, 4,
                           true),
            new CdrCmdItem(null,
                           "Open Translated Summary",
                           "Spanish",
                           "Open Spanish translation of this summary",
                           "CDR2", 2, 3,
                           false),
            new CdrCmdItem(null,
                           "Translation Job",
                           "Translation Job",
                           "Add/edit translation job for this summary",
                           "Databases (Custom)", 4, 1,
                           true),
            new CdrCmdItem(null,
                           "Translation Job Queue",
                           "Translation Job Queue",
                           "Open interface for managing translation job queue",
                           "Databases (Custom)", 4, 8,
                           false),
            new CdrCmdItem(null,
                           "Translation Job Workflow Report",
                           "Translation Job Workflow Report",
                           "Request a report on the translation job queue",
                           "Databases (Custom)", 6, 6,
                           false),
            /* Next 3 for OCECDR-4188 */
            new CdrCmdItem(null,
                           "Glossify Document",
                           "Glossify Document",
                           "Glossify Document",
                           "General (Custom)", 5, 9,
                           true),
            new CdrCmdItem(null,
                           "Glossify Document (dig)",
                           "Glossify Document (include all sections in markup)",
                           "Glossify Document (include all sections in markup)",
                           "General (Custom)", 5, 7,
                           false),
            new CdrCmdItem(null,
                           "Insert TypeOfChange",
                           "Insert Type of Summary Change",
                           "Insert Type of Summary Change",
                           "Revisions (Custom)", 2, 5,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Summary"); }
        catch (e) {
            //Application.Alert(e.description);
            //Application.Alert("Error number: " + (e.number & 0xFFFF));
            //Application.Alert("Error description: " + e.description);
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Summary Toolbar: "
                                  + e);
            }
            cmdBar = null;
        }
        try { cmdBar = cmdBars.item("Summary"); }
        catch (e) {
            // Do nothing.
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old Summary toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Summary", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Summary toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Summary"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Summary": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addPersonToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // label
                           "Generate QC Report",        // macro
                           "QC Report",                 // tooltip
                           "Generate QC Report",        // description
                           "CDR", 3, 4,                 // icon set, row, col
                           false),                      // starts new group?
            new CdrCmdItem(null,
                           "Linked Docs Report",
                           "Linked Docs",
                           "Launch Linked Docs Report",
                           "Integration (Custom)", 3, 9,
                           false),
            new CdrCmdItem(null,
                           "Open Board Member Doc",
                           "Open Board Member Doc",
                           "Open Board Member Doc",
                           "Databases (Custom)", 7, 1,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Person"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Person toolbar: "
                                  + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Person", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Person toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Person"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Person": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addOrganizationToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Linked Docs Report",
                           "Linked Docs",
                           "Launch Linked Docs Report",
                           "Integration (Custom)", 3, 9,
                           false),
            new CdrCmdItem(null,
                           "Insert PDQ Board Info",
                           "PDQ Board",
                           "Insert PDQ Board Info",
                           "Databases (Custom)", 7, 5,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Organization"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Organization " +
                                  "toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Organization", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Organization toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Organization"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Organization": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addTermToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Term Hierarchy",            // Macro.
                           "Hierarchy",                 // Tooltip.
                           "View Hierarchy",            // Description
                           "Databases (Custom)", 6, 3,  // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "QC Report",
                           "Generate QC Report",
                           "CDR", 3, 4,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Term"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
            Application.Alert("Failure deleting old CDR Term toolbar: "
                                + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Term", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Term toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Term"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Term": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addGlossaryTermConceptToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Full Concept QC Report",    // Macro.
                           "Full Concept QC Report",    // Tooltip.
                           "Generate Full QC Report",   // Description
                           "CDR", 4, 3,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "GT Concept QC Report",      // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,                        // Label.
                           "Show Glossary Term Names",  //  Macro.
                           "Term Names",                // Tooltip.
                           "Show Glossary Term Names",  // Description
                           "Integration (Custom)", 7, 1,// Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Make Glossary Term Name Doc",
                           "Glossary Term",
                           "Create Term Name Document",
                           "CDR2", 2, 10,
                           false),
            new CdrCmdItem(null,
                           "View Glossary Term Name Docs",
                           "View GT Name Docs",
                           "View Term Name Documents",
                           "Integration (Custom)", 3, 9,
                           false),
            new CdrCmdItem(null,
                           "Edit Glossary Term Name Docs",
                           "Edit GT Name Docs",
                           "Edit Term Name Documents",
                           "CDR", 5, 3,
                           false),
            new CdrCmdItem(null,
                           "Glossary Translation Job",
                           "Add Translation Job",
                        "Add/edit translation job for this Glossary document",
                           "Databases (Custom)", 4, 1,
                           true),
            new CdrCmdItem(null,
                           "Glossary Translation Job Queue",
                           "Translation Job Queue",
                           "Open interface for managing translation job queue",
                           "Databases (Custom)", 4, 8,
                           false),
            new CdrCmdItem(null,
                           "Glossary Translation Job Workflow Report",
                           "Translation Job Workflow Report",
                           "Request a report on the translation job queue",
                           "Databases (Custom)", 6, 6,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Glossary Term Concept"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert(
                   "Failure deleting old CDR Glossary Term Concept toolbar: "
                                + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Glossary Term Concept", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert(
                "Failure adding CDR Glossary Term Concept toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["GlossaryTermConcept"] = cmdBar;
            toolbarNames[cmdBar.name] = { "GlossaryTermConcept": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addGlossaryTermNameToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,
                           "TermName with Concept QC Report",
                           "GT Name/Concept QC",
                           "Generate QC Report",
                           "CDR", 3, 8,
                           false),
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "GT Name QC Report",         // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,                        // Label.
               "View Linked Glossary Term Concept Doc", // Macro.
                           "View GT Concept",           // Tooltip.
                           "View Concept Document",     // Description
                           "Integration (Custom)", 3, 9,// Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Edit Linked Glossary Term Concept Doc",
                           "Edit GT Concept",
                           "Edit Concept Document",
                           "CDR", 5, 3,
                           false),
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Glossary Phrase Search",
                           "Glossary Phrase Search",
                           "Report on matching GlossaryTermName phrases",
                           "Revisions (Custom)", 2, 2,
                           false),
            new CdrCmdItem(null,
                           "Glossary Translation Job",
                           "Add Translation Job",
                         "Add/edit translation job for this Glossary document",
                           "Databases (Custom)", 4, 1,
                           true),
            new CdrCmdItem(null,
                           "Glossary Translation Job Queue",
                           "Translation Job Queue",
                           "Open interface for managing translation job queue",
                           "Databases (Custom)", 4, 8,
                           false),
            new CdrCmdItem(null,
                           "Glossary Translation Job Workflow Report",
                           "Translation Job Workflow Report",
                           "Request a report on the translation job queue",
                           "Databases (Custom)", 6, 6,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Glossary Term Name"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert(
                    "Failure deleting old CDR Glossary Term Name toolbar: "
                                + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Glossary Term Name", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert(
                "Failure adding CDR Glossary Term Name toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["GlossaryTermName"] = cmdBar;
            toolbarNames[cmdBar.name] = { "GlossaryTermName": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addDrugInfoToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "DrugInfo QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Drug Info"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Drug Info toolbar: "
                                + e);
            }
            cmdBar = null;
        }

        try {
            cmdBar = cmdBars.add("CDR Drug Info", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Drug Info toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["DrugInformationSummary"] = cmdBar;
            toolbarNames[cmdBar.name] = { "DrugInformationSummary": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }


    function addLicenseeToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                      // Label.
                           "Licensee QC Report",      // Macro.
                           "Licensee QC Report",      // Tooltip.
                           "Licensee QC Report",      // Description
                           "CDR", 3, 4,               // Icon set, row, col.
                           false)                     // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Licensee"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Licensee toolbar: "
                                + e);
            }
            cmdBar = null;
        }

        try {
            cmdBar = cmdBars.add("CDR Licensee", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Licensee toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Licensee"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Licensee": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }


    function addCountryToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                      // Label.
                           "Country QC Report",       // Macro.
                           "QC Report",               // Tooltip.
                           "Country QC Report",       // Description
                           "CDR", 3, 4,               // Icon set, row, col.
                           false)                     // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Country"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Drug Info toolbar: "
                                + e);
            }
            cmdBar = null;
        }

        try {
            cmdBar = cmdBars.add("CDR Country", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Country toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Country"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Country": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }


    function addCitationToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Search PubMed",             // Macro.
                           "PubMed",                    // Tooltip.
                           "Search PubMed",             // Description
                           "CDR", 3, 3,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "QC Report",
                           "Generate QC Report",
                           "CDR", 3, 4,
                           true),
            new CdrCmdItem(null,
                           "Make Citation Supplementary Info Doc",
                           "Create SupplementaryInfo doc",
                           "Create SupplementaryInfo document",
                           "CDR2", 2, 6,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Citation"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Citation toolbar: "
                                + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Citation", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Citation toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Citation"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Citation": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addMiscToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false)                       // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Miscellaneous Document"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Miscellaneous " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Miscellaneous Document", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Miscellaneous Document " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["MiscellaneousDocument"] = cmdBar;
            toolbarNames[cmdBar.name] = { "MiscellaneousDocument": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addMailerToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Insert Mailer Response",    // Macro.
                           "Response",                  // Tooltip.
                           "Insert Mailer Response",    // Description
                           "CDR", 6, 5,                 // Icon set, row, col.
                           false)                       // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Mailer"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Mailer " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Mailer", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Mailer " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Mailer"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Mailer": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addTermSetToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                      // Label.
                           "TermSet QC Report",       // Macro.
                           "QC Report",               // Tooltip.
                           "Generate QC Report",      // Description
                           "CDR", 3, 4,               // Icon set, row, col.
                           true)                      // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR TermSet"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR TermSet " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR TermSet", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR TermSet " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["TermSet"] = cmdBar;
            toolbarNames[cmdBar.name] = { "TermSet": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addPDQBoardMemberInfoToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Open Person Doc For Board Member",
                           "Open Person Doc For Board Member",
                           "Open Person Doc For Board Member",
                           "Databases (Custom)", 7, 3,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR PDQBoardMemberInfo"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR " +
                                  "PDQBoardMemberInfo toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR PDQBoardMemberInfo", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR PDQBoardMemberInfo " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["PDQBoardMemberInfo"] = cmdBar;
            toolbarNames[cmdBar.name] = { "PDQBoardMemberInfo": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addMediaToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Show Doc Blob",             // Macro.
                           "Launch Media File",         // Tooltip.
                           "Launch Media File",         // Description
                           "Design (Custom)", 2, 3,     // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "Media QC Report",
                           "Generate QC Report",
                           "CDR2", 1, 10,
                           false),
            new CdrCmdItem(null,
                           "Clone Doc",
                           "Clone Document",
                           "Clone Media Document",
                           "CDR2", 2, 5,
                           true),
            new CdrCmdItem(null,
                           "Media Translation Job",
                           "Add Translation Job",
                           "Add/edit translation job for this Media document",
                           "Databases (Custom)", 4, 1,
                           true),
            new CdrCmdItem(null,
                           "Media Translation Job Queue",
                           "Translation Job Queue",
                           "Open interface for managing translation job queue",
                           "Databases (Custom)", 4, 8,
                           false),
            new CdrCmdItem(null,
                           "Media Translation Job Workflow Report",
                           "Translation Job Workflow Report",
                           "Request a report on the translation job queue",
                           "Databases (Custom)", 6, 6,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Media Document"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Media " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Media Document", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Media Document " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Media"] = cmdBar;
            toolbarNames[cmdBar.name] = { "Media": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addSupplementaryInfoToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Show Doc Blob",             // Macro.
                           "Launch Object File",        // Tooltip.
                           "Launch Object File",        // Description
                           "Databases (Custom)", 2, 6,  // Icon set, row, col.
                           false),                       // Starts new group?
            new CdrCmdItem(null,
                           "Clone Doc",
                           "Clone Document",
                           "Clone SupplementaryInfo Document",
                           "CDR2", 2, 5,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;

        try { cmdBar = cmdBars.item("CDR Supplementary Info Document"); }
        catch (e) {
        }
        if (cmdBar) {
            try {
                cmdBar.Delete();
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Supplementary " +
                                  "Info Document toolbar: " + e);
            }
            cmdBar = null;
        }


        try {
            cmdBar = cmdBars.add("CDR Supplementary Info Document", 2);
            if (Application.VersionNumber > 4.5)
                cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Supplementary Info " +
                              "Document toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["SupplementaryInfo"] = cmdBar;
            toolbarNames[cmdBar.name] = { "SupplementaryInfo": 1 };
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function bugRepro() {
        var cmdBars = Application.CommandBars;
        var i       = 0;
        if (cmdBars) {
            Application.Alert("number of bars: " + cmdBars.count);
            while (i < cmdBars.count) {
                try {
                    var bar = cmdBars.item(i);
                    Application.Alert("Found command bar: " + bar.name);
                }
                catch (e) {
                    Application.Alert("Err number: " + e.number & 0xFFFF);
                    try {
                        Application.Alert("Description: " + e.description);
                    }
                    catch (e2) {
                        Application.Alert("e.description error: " + e2);
                    }
                }
                i++;
            }
        }
    }

    /*
     * Turn off all the document-specific toolbars.
     */
    function hideToolbars() {
        for (var i in toolbars) {
            if (toolbars[i] && toolbars[i].Visible)
                toolbars[i].Visible = false;
        }
    }

    function turnOffStandardToolbars() {
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        var standard = new Array("Standard");
        if (Application.VersionNumber > 4.5)
            standard.push("Repository");
        for (var i in standard) {
            try { cmdBar = cmdBars.item(standard(i)); }
            catch (e) { }
            if (cmdBar)
                cmdBar.Visible = false;
            cmdBar = null;
        }
        try { cmdBar = cmdBars.item("Formatting"); }
        catch (e) { }
        if (cmdBar) {
            cmdBar.Visible = true;
            var controls = cmdBar.Controls;
            for (var i = controls.count; i >= 1; --i) {
                try {
                    item = controls.item(i);
                    var str = item.DescriptionText;
                    if (str.indexOf("List") != -1) {
                        item.Delete();
                    }
                }
                catch (e) {}
            }
        }
    }

    function cleanupOldToolbars() {
        var bars = Application.CommandBars;
        var bar = null;
        var names = [
            "CDR Protocol",
            "CDR Glossary Term",
            "CDR CTGovProtocol"
        ];
        for (var i = 0; i < names.length; ++i) {
            try { bar = bars.item(names[i]); }
            catch (e1) {}
            if (bar) {
                toolbarNames[bar.name] = {}
                try { bar.Delete; }
                catch (e2) {}
            }
            bar = null;
        }
    }

    /*
     * This workaround is needed because, as Softquad admits, there is no way
     * for us to customize our installation in a way which installs the CDR
     * menu as part of a customized default.tbr.
     */
    var toolbars = new Object();
    var toolbarNames = {}; // Needed for XMetaL 9.0 and greater
    addCdrToolbar();
    addSupplementaryInfoToolbar();
    addSymbolToolbar();
    addSummaryToolbar();
    addPersonToolbar();
    addOrganizationToolbar();
    addTermToolbar();
    addGlossaryTermConceptToolbar();
    addGlossaryTermNameToolbar();
    addDrugInfoToolbar();
    addCitationToolbar();
    addMiscToolbar();
    addCountryToolbar();
    addMailerToolbar();
    addTermSetToolbar();
    addPDQBoardMemberInfoToolbar();
    addMediaToolbar();
    addLicenseeToolbar();
    cleanupOldToolbars();
    addCdrMenus();
    if (Application.VersionNumber < 9.0)
        hideToolbars();

  ]]>
</MACRO>

<MACRO  name="Cdr Logon"
        key=""
        lang="JScript"
        tooltip="Log On To CDR"
        id="1342">
  <![CDATA[

    cdrLogon();

  ]]>
</MACRO>

<MACRO  name="Cdr Retrieve"
        key=""
        lang="JScript"
        tooltip="Retrieve Document From CDR"
        id="1221">
  <![CDATA[

    /*
     * Retrieves a document from the CDR.  The user is prompted for a document
     * ID.
     */
    function cdrRetrieve() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            var rc = cdrObj.retrieve();
        }
    }
    cdrRetrieve();

  ]]>
</MACRO>

<MACRO  name="Cdr Search"
        key=""
        lang="JScript"
        tooltip="Search for Document in CDR"
        id="20103">
  <![CDATA[

    /*
     * Searches the CDR repository and retrieves a selected document.
     */
    function cdrSearch() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            var rc  = cdrObj.search();
        }
    }
    cdrSearch();

  ]]>
</MACRO>

<MACRO  name="Cdr Validate"
        key=""
        lang="JScript"
        tooltip="Ask CDR to Validate Document">
  <![CDATA[

    /*
     * Perform CDR validation (schema and/or links) on the currently active
     * document.
     */
    function cdrValidate() {
        if (ActiveDocument.ViewType != sqViewNormal &&
            ActiveDocument.ViewType != sqViewTagsOn) {
            try {
                ActiveDocument.ViewType = sqViewNormal;
            }
            catch (e) {
                Application.Alert("Switch to normal or tags-on view " +
                                  "to validate documents.");
                return;
            }
        }
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            var result = cdrObj.validate();
            if (result > 0) {
                Application.Alert("Found " + result +
                                  " validation errors/warnings");
            }
        }
    }
    cdrValidate();

  ]]>
</MACRO>

<MACRO  name="Cdr Save"
        key="Ctrl+Shift+S"
        lang="JScript"
        tooltip="Store Document in the CDR"
        id="1365">
  <![CDATA[


    /*
     * Saves the currently active document in the CDR repository.
     */
    function cdrSave() {
        if (ActiveDocument.ViewType != sqViewNormal &&
            ActiveDocument.ViewType != sqViewTagsOn) {
            try {
                ActiveDocument.ViewType = sqViewNormal;
            }
            catch (e) {
                Application.Alert("Switch to normal or tags-on view " +
                                  "to save documents.");
                return;
            }
        }
        if (cdrObj == null)
            Application.Alert("You are not logged on to the CDR");
        else {
            var answer = true;
            var docType = ActiveDocument.doctype;
            // Application.Alert(docType.name);
            if (docType && docType.name == "InScopeProtocol") {
                var doc = Application.ActiveDocument;
                var nodes = doc.getElementsByTagName("Outcome");
                // for (var node in nodes) {
                if (nodes.length > 0) {
                    var elem = nodes.item(0);
                    var val = getTextContent(elem);
                    //Application.Alert(val.length);
                    if (val.length > 254) {
                        var msg = "Outcome text has " + val.length
                                + " characters.\nSave anyway?"
                        answer = Application.Confirm(msg);
                   }
                }
            }
            if (answer) {
                var result = cdrObj.save();
                if (result > 0) {
                    Application.Alert("Found " + result +
                                      " validation errors/warnings");
                }
            }
        }
    }
    cdrSave();


  ]]>
</MACRO>

<MACRO  name="Cdr Logoff"
        key=""
        lang="JScript"
        tooltip="Log out of the CDR"
        id="20307">
  <![CDATA[
    cdrLogoff();
  ]]>
</MACRO>

<MACRO  name="Cdr Edit"
        key="Ctrl+Enter"
        lang="JScript"
        tooltip="Store Document in the CDR"
        id="1919">
 <![CDATA[
    cdrEdit();
  ]]>
</MACRO>

<MACRO  name="Cdr Copy Fragment Link"
        key=""
        lang="JScript"
        tooltip="Copy Fragment Link to CDR Clipboard">
  <![CDATA[
    function copyFragmentLink() {
        CdrFragLinkClipboard = "";
        var nodes = Application.ActiveDocument.getElementsByTagName("DocId");
        if (nodes.length < 1) {
            Application.Alert("This is a new document without a document ID.");
        }
        else {
            var docIdElem = nodes.item(0);
            var docId     = getTextContent(docIdElem);
            var node      = Selection.ContainerNode;
            var depth     = 5;
            var fragId    = "";
            while (node && !fragId) {
                if (depth-- < 1) {
                    Application.Alert("No fragment ID found");
                    return;
                }
                if (node.nodeType != 1) {
                    node = node.parentNode;
                    continue;
                }
                fragId = node.getAttribute("cdr:id");
                if (!fragId) {
                    node = node.parentNode;
                }
            }
            CdrFragLinkClipboard = docId + "#" + fragId;
            Application.Alert("CdrFragLinkClipboard=" + CdrFragLinkClipboard);
        }
    }
    copyFragmentLink();
  ]]>
</MACRO>

<MACRO  name="Cdr Copy Fragment ID"
        key=""
        lang="JScript"
        tooltip="Copy Fragment ID to CDR Clipboard">
  <![CDATA[
    function copyFragmentId() {
        CdrFragIdClipboard = "";
        var fragId = getFragId();
        if (!fragId)
            Application.Alert("No fragment ID found");
        else {
            CdrFragIdClipboard = fragId;
            Application.Alert("CdrFragIdClipboard=" + CdrFragIdClipboard);
        }
    }
    copyFragmentId();
  ]]>
</MACRO>

<MACRO  name="Cdr Paste Fragment Link"
        key=""
        lang="JScript"
        tooltip="Paste Fragment Link From CDR Clipboard">
 <![CDATA[
    function pasteFragmentLink() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        if (CdrFragLinkClipboard == "") {
            Application.Alert("CDR Fragment Link Clipboard is empty");
            return;
        }
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (!docType.hasAttribute(container.nodeName, "cdr:ref") &&
            !docType.hasAttribute(container.nodeName, "Target") &&
            !docType.hasAttribute(container.nodeName, "cdr:href")) {
            Application.Alert("Current element cannot accept links.");
            return;
        }

        Selection.ReadOnlyContainer = false;
        gEditingCdrLink = true;
        cdrObj.pasteDocLink(CdrFragLinkClipboard);
        gEditingCdrLink = false;
        Selection.ReadOnlyContainer = true;
    }

    pasteFragmentLink();
  ]]>
</MACRO>

<MACRO  name="Cdr Paste Fragment ID"
        key=""
        lang="JScript"
        tooltip="Paste Fragment ID From CDR Clipboard">
 <![CDATA[
    function pasteFragmentId() {
        if (CdrFragIdClipboard == "") {
            Application.Alert("CDR Fragment ID Clipboard is empty");
            return;
        }
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (docType.name != "PDQBoardMemberInfo") {
            Application.Alert("Wrong doctype for ID paste target");
            return;
        }
        if (container.nodeName != "PersonContactID") {
            Application.Alert("Current element is not PersonContactID");
            return;
        }
        Selection.SelectContainerContents();
        if (Selection.ReadOnly) {
            Application.Alert("Cannot modify current element");
            return;
        }
        Selection.Text = CdrFragIdClipboard;
    }

    pasteFragmentId();
  ]]>
</MACRO>

<MACRO  name="PrevElement"
        key="Shift+Tab"
        lang="JScript">
  <![CDATA[
    Selection.GotoPrevious(0);
    Selection.SelectContainerContents();
  ]]>
</MACRO>

<MACRO  name="NextElement"
        key="Tab"
        lang="JScript">
  <![CDATA[
    Selection.GotoNext(0);
    Selection.SelectContainerContents();
  ]]>
</MACRO>

<MACRO  name="ReloadCSS"
        key="Ctrl+Alt+S"
        lang="JScript">
  <![CDATA[
    ActiveDocument.RefreshCssStyle();
  ]]>
</MACRO>

<MACRO name="On_View_Change"
       lang="JScript">
         <![CDATA[

    // refreshes the Insertion and Deletion element container styles on
    // view change fromplain text to Normal or Tags on
/*
    function refreshStyles() {
        var docProps = ActiveDocument.CustomDocumentProperties;
        if (docProps.item("Highlighting").value == "True") {
            var rng = ActiveDocument.Range;
            rng.MoveToDocumentStart();
            while (rng.MoveToElement("Insertion")) {
                rng.ContainerStyle = "color:red";
            }
            rng.MoveToDocumentStart();
            while (rng.MoveToElement("Deletion")) {
                rng.ContainerStyle = "color:red; text-decoration:line-through";
            }
            rng = null;
        }
    }

    if ((ActiveDocument.ViewType==sqViewNormal ||
        ActiveDocument.ViewType==sqViewTagsOn) &&
        ActiveDocument.PreviousViewType==sqViewPlainText) {
            refreshStyles();
    }
*/
  ]]>
</MACRO>

<MACRO name="Deletion"
       key="Ctrl+Alt+F1"
       lang="JScript" id="1913"
       desc="Surround the selected text with Deletion element">
         <![CDATA[

    //------------------------------------------------------------------
    // Macro for Revision Control
    // Surrounds the selected text with Deletion element and sets the
    // container style accordingly if highlighting  is true then the
    // selected text color is red and style is strike through.  If the
    // selected text has an Deletion inside then it merges it with the
    // current parent.  If the selected text has an Insertion element
    // inside then it deletes the elemetn and its contents.
    //
    // NOTE: Logic drastically simplified in keeping with request #1163.
    //------------------------------------------------------------------
    function doDeletion() {

        // If some text is selected:
        if (!ActiveDocument.Range.IsInsertionPoint) {

            if (Selection.CanSurround("Deletion")) {
                var date = new Date();
                Selection.Surround("Deletion");
                Selection.ContainerAttribute("UserName") = CdrUserName;
                Selection.ContainerAttribute("Time") = date.toLocaleString();
                Selection.ContainerAttribute("RevisionLevel") = "proposed";
            }
            else
                Application.Alert("Deletion markup not allowed here.");
        }
        else
            Application.Alert("The current selection is empty.");
    }

    if (CanRunMacros()) {
        doDeletion();
    }

  ]]>
</MACRO>

<MACRO  name="Insertion"
        key="Ctrl+Alt+I"
        lang="JScript"
        id="1914"
        desc="Marks the Insertions">
  <![CDATA[

    //----------------------------------------------------------------------
    // Allows the users to track changes while inserting any text in the
    // document.  If the user selects some text and clicks on insertion
    // toolbar button the selected text is surrounded by deletion element
    //----------------------------------------------------------------------
    function simpleInsertion() {
        var date = new Date();
        if (!Selection.IsInsertionPoint) {
            if (!Selection.CanSurround("Insertion")) {
                Application.Alert("Unable to apply Insertion markup");
                return;
            }
            Selection.Surround("Insertion");
        }
        else {
            if (!Selection.CanInsert("Insertion")) {
                Application.Alert("Unable to apply Insertion markup");
                return;
            }
            Selection.InsertElement("Insertion");
            Selection.InsertReplaceableText("Insert text here");
        }
        Selection.ContainerAttribute("UserName") = CdrUserName;
        Selection.ContainerAttribute("Time") = date.toLocaleString();
        Selection.ContainerAttribute("RevisionLevel") = "proposed";
    }

    if (CanRunMacros()) {
        simpleInsertion();
    }

  ]]>
</MACRO>

<MACRO  name="Accept Changes"
        key=""
        lang="JScript"
        id="1912"
        desc="Includes all changes in the document">
  <![CDATA[

    //----------------------------------------------------------------------
    // Incorporates Reviewer's changes i.e deletes all text surrounded by
    // Deletion element including the tags and merges the contents of
    // Insertion element with the document.
    //----------------------------------------------------------------------
    function mergeChanges()
    {
        var frm = CdrUserPath + "/Forms/CDR/AcceptAllChanges.xft";
        var dlg = Application.CreateFormDlg(frm);
        dlg.ApprovedButton.Value = true;
        var rc = dlg.DoModal();
        if (rc != 1)
            return; // User cancelled.
        var levels = "";
        if (dlg.PublishButton.Value)
            levels = "[publish]";
        if (dlg.ApprovedButton.Value)
            levels += "[approved]";
        if (dlg.ProposedButton.Value)
            levels += "[proposed]";
        if (!levels) {
            Application.Alert("No levels selected.");
            return;
        }
        var r = Selection.Duplicate;
        r.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            var lvl = r.ContainerNode.getAttribute("RevisionLevel");
            //Application.Alert("revision level = " + lvl);
            if (levels.indexOf(lvl) != -1) {
                r.SelectContainerContents();
                r.Delete();
                r.RemoveContainerTags();
            }
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            var lvl = r.ContainerNode.getAttribute("RevisionLevel");
            //Application.Alert("revision level = " + lvl);
            if (levels.indexOf(lvl) != -1) {
                r.SelectContainerContents();
                if (r.Text == "<?xm-replace_text Insert text here?>") {
                    r.Delete();
                }
                r.RemoveContainerTags();
            }
        }
    }

    if (CanRunMacros()) {
        var confirm = true;/*
            Application.Confirm("Do you want to merge all changes " +
                                "without reviewing them?");*/
        if (confirm) {
            mergeChanges();
        }
    }

  ]]>
</MACRO>

<MACRO  name="Navigate Comments"
        lang="JScript"
        key="Ctrl+Alt+C"
        desc="Navigate Comments..."
        tooltip="Navigate Comments... (Ctrl+Alt+C)">
  <![CDATA[
    function navigateComments() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        cdrObj.navigateComments();
    }
    navigateComments();
  ]]>
</MACRO>

<MACRO  name="Review Markup"
        lang="JScript"
        id="1948"
        key="Ctrl+Alt+A"
        desc="Accept or Reject Changes..."
        tooltip="Accept or Reject Changes... (Ctrl+Alt+A)">
  <![CDATA[
    if (cdrDocReadOnly())
        Application.Alert("Document is not checked out for editing.");
    else if (CanRunMacros())
        cdrObj.acceptOrRejectMarkup();
  ]]>
</MACRO>

<MACRO  name="Accept Change"
        key=""
        lang="JScript"
        id="1905"
        desc="Accept the current marked change">
  <![CDATA[

    //----------------------------------------------------------------------
    // Incorporates the current marked change i.e. if the selection is inside
    // an Insertion the contents are merged and if inside an Deletion the
    // contents are deleted.
    //----------------------------------------------------------------------

    //----------------------------------------------------------------------
    // Replacement for buggy SoftQuad code.
    //----------------------------------------------------------------------
    function doAcceptChangeWithoutSoftQuadBugs() {
        if (cdrDocReadOnly())
            Application.Alert("Document is not checked out for editing.");
        else if (Selection) {
            var elemName = Selection.ElementName(0);
            if (elemName == "Insertion")
                Selection.RemoveContainerTags();
            else if (elemName == "Deletion") {
                Selection.SelectContainerContents();
                Selection.Delete();
                Selection.RemoveContainerTags();
            }
            else
                Application.Alert("Accept Change can only be used " +
                                  "within Insertion or Deletion markup.");
        }
    }

    if (CanRunMacros())
        doAcceptChangeWithoutSoftQuadBugs();

  ]]>
</MACRO>

<MACRO  name="Reject Change"
        key=""
        lang="JScript"
        id="1902"
        desc="Rejects the current marked change">
  <![CDATA[
    //----------------------------------------------------------------------
    // Rejects the current marked change i.e. if the selection is inside an
    // Insertion the contents are removed and if the contents are inside an
    // Deletion they are merged back with the document.
    //----------------------------------------------------------------------
    //----------------------------------------------------------------------
    // Replacement for buggy SoftQuad code.
    //----------------------------------------------------------------------
    function doRejectChangeCorrectly() {
        if (cdrDocReadOnly())
            Application.Alert("Document is not checked out for editing.");
        else if (Selection) {
            var elemName = Selection.ElementName(0);
            if (elemName == "Deletion")
                Selection.RemoveContainerTags();
            else if (elemName == "Insertion") {
                Selection.SelectContainerContents();
                Selection.Delete();
                Selection.RemoveContainerTags();
            }
            else
                Application.Alert("Reject Change can only be used " +
                                  "within Insertion or Deletion markup.");
        }
    }

    if (CanRunMacros())
        doRejectChangeCorrectly();

  ]]>
</MACRO>

<MACRO  name="Find Next"
        key="Ctrl+Alt+N"
        lang="JScript"
        id="1911"
        desc="Moves the selection to the next marked change if any"
        tooltip="Find Next Change">
  <![CDATA[

    //----------------------------------------------------------------------
    // Rewritten to fix SoftQuad's buggy approach in response to CDR issue
    // report #330.
    // Rewritten again for JIRA ticket OCECDR-4485
    //----------------------------------------------------------------------
    function findNextInsertionOrDeletion() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        cdrObj.navigateMarkup();
    }

    if (CanRunMacros()) {
        findNextInsertionOrDeletion();
    }

  ]]>
</MACRO>

<MACRO  name="Init_JScript_Macros"
        lang="JScript"
        desc="initialize JScript macros"
        hide="true">
  <![CDATA[

    function CanRunMacros() {
        if (ActiveDocument.ViewType != sqViewNormal &&
            ActiveDocument.ViewType != sqViewTagsOn) {
            Application.Alert("Change to Tags On or Normal " +
                              "view to run macros.");
            return false;
        }

        if (!ActiveDocument.IsXML) {
            Application.Alert("Cannot run macros because document " +
                              "is not XML.");
            return false;
        }
        return true;
    }

  ]]>
</MACRO>

<MACRO  name="CDR Advanced Search"
        lang="JScript"
        desc="Launch browser menu for advanced CDR searching"
        hide="false">
  <![CDATA[

    function advancedSearch() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "AdvancedSearch.py?Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    advancedSearch();

  ]]>
</MACRO>

<MACRO  name="Show Checked Out Docs"
        lang="JScript"
        desc="Bring up report showing documents checked out by this user."
        hide="false">
  <![CDATA[

    function checkedOutDocs() {
        if (!CdrSession || !CdrUserName) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "CheckedOutDocs.py?Session=" + CdrSession
                            + "&User=" + CdrUserName;
        cdrObj.showPage(url);
    }
    checkedOutDocs();

  ]]>
</MACRO>

<MACRO name="Publish Preview"
       lang="JScript">
  <![CDATA[
    publishPreview("");
  ]]>
</MACRO>

<MACRO name="Patient Summary Publish Preview"
       lang="JScript">
  <![CDATA[
    publishPreview("Summary_Patient");
  ]]>
</MACRO>

<MACRO  name="CDR Check In"
        lang="JScript"
        desc="Releases CDR lock, abandoning any changes to current document."
        hide="false">
  <![CDATA[

    if (cdrObj == null) {
        Application.Alert("You are not logged on to the CDR");
    }
    else {
        cdrCheckIn();
    }

  ]]>
</MACRO>

<MACRO  name="CDR Get Org Postal Address"
        lang="JScript"
        desc="Retrieve org address from fragment link"
        hide="false">
  <![CDATA[

    if (cdrObj == null) {
        Application.Alert("You are not logged on to the CDR");
    }
    else {
        cdrObj.getOrgAddress();
    }

  ]]>
</MACRO>

<MACRO  name="CDR Persons Linking to Org Address Fragment"
        lang="JScript"
        desc="Finds Person documents linking to current Org location."
        hide="false">
  <![CDATA[

    function personsLinkingToOrgLoc() {
        var rng = ActiveDocument.Range
        var elem = rng.ContainerNode;
        if (elem) {
            if (elem.nodeName != "Location") {
                if (rng.IsParentElement("Location")) {
                    if (rng.MoveToElement("Location", false)) {
                        elem = rng.ContainerNode;
                    }
                }
            }
            if (elem.nodeName == "Location") {
                var id = elem.getAttribute("cdr:id");
                var nodes =
                    Application.ActiveDocument.getElementsByTagName("DocId");
                if (nodes.length < 1) {
                    Application.Alert(
                        "This is a new document without a document ID.");
                    return;
                }
                else {
                    var elem = nodes.item(0);
                    var val  = getTextContent(elem);
                    var url = CdrCgiBin + "PersonOrgLocLinks.py?FragLink=" +
                              val + "%23" + id;
                    cdrObj.showPage(url);
                }
            }
        }
    }

    personsLinkingToOrgLoc();

  ]]>
</MACRO>

<MACRO  name="Remember Org Postal Address"
        lang="JScript"
        desc="Stores org postal address in an internal clipboard."
        hide="false">
  <![CDATA[

    function rememberOrgPostalAddress() {
        var rng = getElemRange("Location");
        if (!rng) {
            Application.Alert(
                "Current position is not within an org location.");
            return;
        }
        locElem = rng.ContainerNode;
        addrList = locElem.getElementsByTagName("PostalAddress");
        if (!addrList.length) {
            Application.Alert("No PostalAddress element found.");
            return;
        }
        //CdrOrgAddressClipboard = addrList.item(0);
        rng.MoveToElement("PostalAddress");
        rng.SelectElement();
        CdrOrgAddressClipboard = rng.Text;
        //Application.Alert("CB: " + CdrOrgAddressClipboard);
    }

    rememberOrgPostalAddress();

  ]]>
</MACRO>

<MACRO  name="Term Hierarchy"
        lang="JScript"
        desc="Web interface for displaying Term document hierarchies"
        hide="false">
  <![CDATA[

    function termHierarchyDisplay() {
        var url = CdrCgiBin + "TermHierarchy.py";
        if (ActiveDocument && ActiveDocument.doctype.name == "Term") {
            var nodes =
                Application.ActiveDocument.getElementsByTagName("DocId");
            if (nodes.length > 0) {
                var elem  = nodes.item(0);
                var docId = getTextContent(elem);
                url += "?DocId=" + docId;
            }
        }
        cdrObj.showPage(url);
    }

    termHierarchyDisplay();

  ]]>
</MACRO>

<MACRO  name="Insert Current Date"
        lang="JScript"
        key="Alt+D"
        desc="Inserts the current date as text content of current elem"
        hide="false">
  <![CDATA[

    function insCurrentDate() {
        if (Selection != null) {
            // Selection.SelectContainerContents();
            str = getCurDateString();
            Selection.Text = str;
        }
    }
    insCurrentDate();

  ]]>
</MACRO>

<MACRO  name="Insert User ID"
        lang="JScript"
        desc="Inserts the login name as text content of current elem"
        key="Alt+U"
        hide="false">
  <![CDATA[

    function insUserName() {
        if (Selection != null) {
            Selection.Text = CdrUserName;
        }
    }
    insUserName();

  ]]>
</MACRO>

<MACRO  name="Insert DrugName Element"
        lang="JScript"
        desc="Wraps the current selection with DrugName tags"
        hide="false">
    Selection.InsertElement("DrugName");
</MACRO>

<MACRO  name="Insert ForeignWord Element"
        lang="JScript"
        desc="Wraps the current selection with ForeignWord tags"
        hide="false">
    Selection.InsertElement("ForeignWord");
</MACRO>

<MACRO  name="Insert GeneName Element"
        lang="JScript"
        desc="Wraps the current selection with GeneName tags"
        hide="false">
    Selection.InsertElement("GeneName");
</MACRO>

<MACRO  name="Insert ScientificName Element"
        lang="JScript"
        desc="Wraps the current selection with ScientificName tags"
        hide="false">
    Selection.InsertElement("ScientificName");
</MACRO>

<MACRO  name="Insert Emphasis Element"
        lang="JScript"
        desc="Wraps the current selection with Emphasis tags"
        hide="false">
    Selection.InsertElement("Emphasis");
</MACRO>

<MACRO  name="Insert Strong Element"
        lang="JScript"
        desc="Wraps the current selection with Strong tags"
        hide="false">
    Selection.InsertElement("Strong");
</MACRO>

<MACRO  name="Insert Subscript Element"
        lang="JScript"
        desc="Wraps the current selection with Subscript tags"
        hide="false">
    Selection.InsertElement("Subscript");
</MACRO>

<MACRO  name="Insert Superscript Element"
        lang="JScript"
        desc="Wraps the current selection with Superscript tags"
        hide="false">
    Selection.InsertElement("Superscript");
</MACRO>

<MACRO name="Administrative Subsystem"
       lang="JScript"
       id="1019">
  <![CDATA[
    function administrativeSubsystem() {

        var url = CdrCgiBin + "Admin.py?Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    administrativeSubsystem();
  ]]>
</MACRO>

<MACRO name="New CDR Document"
       lang="JScript"
       id="2028">
  <![CDATA[
    Documents.Add();
  ]]>
</MACRO>

<MACRO name="Print"
       lang="JScript"
       id="2009">
  <![CDATA[
        // This didn't work
        //Application.RunKeyedMacro("Ctrl+P");
    function doPrint() {
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;
        var fileMenu     = menuControls.item("File");
        var controls     = fileMenu.Controls;
        var printCtrl    = null;
        for (i = 1; i < controls.Count; ++i) {
            if (controls.item(i).TooltipText.indexOf("Ctrl+P") != -1) {
                printCtrl = controls.item(i);
                break;
            }
        }
        if (printCtrl) {
            Application.Alert("got a live one!");
            printCtrl.Execute();
        }
        return;
    }
    // This doesn't work, either.  Confirmed by Derek of SoftQuad Technical
    // Support email 24 Oct 2001.  He has filed a bug report.
    // doPrint();
    Application.Alert("Sorry.  Due to a bug in XMetaL, you must invoke the\n"
        + "Print dialog box from the File menu or using Control+P.");
  ]]>
</MACRO>

<MACRO name="Insert CitationLink"
       lang="JScript" >
  <![CDATA[
    Selection.InsertWithTemplate("CitationLink")
  ]]>
</MACRO>

<MACRO name="Itemized List"
       key="Alt+L"
       lang="JScript"
       id="20404">
  <![CDATA[
    Selection.InsertElement("ItemizedList");
    Selection.ElementAttribute("Style", "ItemizedList", 0) = "bullet";
    Selection.InsertWithTemplate("ListTitle");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Selection.MoveUp();
    Selection.MoveUp();
  ]]>
</MACRO>

<MACRO name="Ordered List"
       key="Alt+O"
       lang="JScript"
       id="20412">
  <![CDATA[
    Selection.InsertElement("OrderedList");
    Selection.ElementAttribute("Style", "OrderedList", 0) = "Arabic";
    Selection.InsertWithTemplate("ListTitle");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Selection.MoveUp();
    Selection.MoveUp();
  ]]>
</MACRO>

<MACRO name="Table"
       lang="JScript">
  <![CDATA[
    function doTable() {
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;
        var tableMenu    = menuControls.item("Table");
        var controls     = tableMenu.Controls;
        var tableWizard  = controls.item(1);
        tableWizard.Execute();
        /*
         * Don't do this, because the Execute() method above happens
         * asynchronously, which means that if there's already a Title
         * element somewhere above, the cursor will jump to it before
         * the table insertion has finished.
         *
         * if (ActiveDocument) {
         *     var rng = ActiveDocument.Range;
         *     if (rng) {
         *         rng.MoveToElement('Title', false);
         *         rng.Select();
         *     }
         * }
         */
    }
    doTable();
    //Application.Alert("Sorry.  Due to a bug in XMetaL, you must invoke the\n"
    //    + "Table Wizard from the Table menu.");
  ]]>
</MACRO>

<MACRO name="CDR Help"
       lang="JScript">
  <![CDATA[
    cdrObj.showPage(CdrCgiBin + "Help.py")
  ]]>
</MACRO>

<MACRO name="Jump Past Element"
       key="Ctrl+Alt+Shift+P"
       lang="JScript">
  <![CDATA[
    function jumpPastElement() {
        try {
            if (ActiveDocument) {
                var rng = ActiveDocument.Range;
                if (rng) {
                    rng.SelectAfterContainer();
                    rng.Select();
                }
            }
        }
        catch (e) {}
    }
    jumpPastElement();
  ]]>
</MACRO>

<MACRO name="Jump Before Element"
       key="Ctrl+Alt+Shift+B"
       lang="JScript">
  <![CDATA[
    function jumpBeforeElement() {
        try {
            if (ActiveDocument) {
                var rng = ActiveDocument.Range;
                if (rng) {
                    rng.SelectBeforeContainer();
                    rng.Select();
                }
            }
        }
        catch (e) {}
    }
    jumpBeforeElement();
  ]]>
</MACRO>

<MACRO name="On_Document_Activate"
       lang="JScript">
  <![CDATA[
    function adjustToolbars() {
        hideToolbars();
        var docType = ActiveDocument.doctype;
        if (toolbars[docType.name] != null) {
            toolbars[docType.name].Visible = true;
        }
    }
    if (Application.VersionNumber < 4.5)
        adjustToolbars();
  ]]>
</MACRO>

<MACRO name="On_Document_Close"
       lang="JScript">
  <![CDATA[
    if (Application.VersionNumber < 4.5)
        hideToolbars();
    //cdrObj.setTitleBar();
  ]]>
</MACRO>

<MACRO name="On_Document_Open_View"
       lang="JScript">
  <![CDATA[
    //Application.Alert("entering On_Document_Open_View");
    // Always open documents in Normal view
    if (ActiveDocument.ViewType != 0) {
        ActiveDocument.ViewType = 0;
    }
    //Application.Alert("leaving On_Document_Open_View");
  ]]>
</MACRO>

<MACRO name="Licensee QC Report"
       lang="JScript">
  <![CDATA[
    function qcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId
                + "&Filter=name:Licensee QC Report Filter";
        cdrObj.showPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="Country QC Report"
       lang="JScript">
  <![CDATA[
    function qcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId
                + "&Filter=name:Country QC Report Filter";
        cdrObj.showPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="TermSet QC Report"
       lang="JScript">
  <![CDATA[
    function qcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId
                + "&Filter=name:TermSet QC Report Filter";
        cdrObj.showPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="DrugInfo QC Report"
       lang="JScript">
  <![CDATA[
    function qcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?DocType=DrugInformationSummary"
                            + "&DocId="
                            + docId
                            + "&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="Generate QC Report"
       lang="JScript">
  <![CDATA[
    function qcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?Session="
                + CdrSession + "&DocId=" + docId;
        //Application.Alert(url);
        cdrObj.showPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="TermName with Concept QC Report"
       lang="JScript">
  <![CDATA[
    function protocolAdminQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId + "&isqc=true" +
                "&Filter=set:QC GlossaryTermName with Concept Set";
        cdrObj.showPage(url);
    }
    protocolAdminQcReport();
  ]]>
</MACRO>

<MACRO name="Search PubMed"
       lang="JScript">
  <![CDATA[
    function searchPubMed() {
        var url = "https://www.ncbi.nlm.nih.gov/entrez/";
        cdrObj.showPage(url);
    }
    searchPubMed();
  ]]>
</MACRO>

<MACRO name="New Summary Section"
       key =""
       lang="JScript"
       id  ="1247">
  <![CDATA[
    function newSection() {
        try {
            if (!cdrObj) {
                Application.Alert("Not logged on to the CDR");
                return;
            }
            if (ActiveDocument) {
                var rng = ActiveDocument.Range;
                var i = 0; // Safety measure...
                if (rng) { rng.Collapse(); }
                while (rng && i < 50) {
                    if (rng.CanInsert("SummarySection")) {
                        if (cdrIsReadOnly()) {
                            var msg = "Can't insert into readonly document";
                            Application.Alert(msg);
                            break;
                        }
                        rng.InsertWithTemplate("SummarySection");
                        rng.Select();
                        break;
                    }
                    if (!rng.ContainerNode) {
                        var msg = "Can't find a place to insert Section";
                        Application.Alert(msg);
                        break;
                    }
                    rng.SelectAfterContainer();
                    i++;
                }
            }
        }
        catch (e) { }
    }
    newSection();
  ]]>
</MACRO>

<MACRO name="Bold Underline Report"
       lang="JScript">
  <![CDATA[
    function boldUnderlineReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&ReportType=bu&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    boldUnderlineReport();
  ]]>
</MACRO>

<MACRO name="Redline Strikeout Report"
       lang="JScript">
  <![CDATA[
    function redlineStrikeoutReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&ReportType=rs&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    redlineStrikeoutReport();
  ]]>
</MACRO>

<MACRO name="Full Concept QC Report"
       lang="JScript">
  <![CDATA[
    function qcFullReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "GlossaryConceptFull.py?Session="
                + CdrSession + "&DocId=" + docId;
        cdrObj.showPage(url);
    }
    qcFullReport();
  ]]>
</MACRO>

<MACRO name="Patient Summary RS QC Report"
       lang="JScript">
  <![CDATA[
    function patientSummaryRsQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        /*
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId +
                "&Filter=name:Summary-Copy+XML+for+Patient+Summary+Report" +
                "&Filter1=name:Patient+Summary+QC+Report+Filter";
        */
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&ReportType=pat&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    patientSummaryRsQcReport();
  ]]>
</MACRO>

<MACRO name="Patient Summary BU QC Report"
       lang="JScript">
  <![CDATA[
    function patientSummaryBuQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        /*
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId +
                "&Filter=name:Summary-Copy+XML+for+Patient+Summary+Report" +
                "&Filter1=name:Patient+Summary+QC+Report+Filter";
        */
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&ReportType=patbu&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    patientSummaryBuQcReport();
  ]]>
</MACRO>

<MACRO name="Document History Report"
       lang="JScript">
  <![CDATA[
    function documentHistoryReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "DocVersionHistory.py?Session="
                + CdrSession
                + "&DocId="
                + docId;
        cdrObj.showPage(url);
    }
    documentHistoryReport();
  ]]>
</MACRO>

<MACRO name="Insert DateLastModified"
       lang="JScript" >
  <![CDATA[
    function insertDateLastModified() {
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.MoveToElement("DateLastModified", false)) {
            if (!rng.FindInsertLocation("DateLastModified", false)) {
                Application.Alert("Can't insert DateLastModified element");
                return;
            }
            rng.InsertWithTemplate("DateLastModified");
        }
        rng.Select();
    }
    insertDateLastModified();
  ]]>
</MACRO>

<MACRO name="Undo Last Edit"
       lang="JScript" >
  <![CDATA[
    if (ActiveDocument)
        ActiveDocument.Undo();
  ]]>
</MACRO>

<MACRO name="Insert Mailer Response"
       lang="JScript" >
  <![CDATA[
    function insertMailerResponse() {
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("Response", false)) {
            Application.Alert(
                    "Can't insert Response element");
                return;
        }
        rng.InsertWithTemplate("Response");
        rng.Select();
    }
    insertMailerResponse();
  ]]>
</MACRO>

<MACRO name="Insert PDQ Board Info"
       lang="JScript" >
  <![CDATA[
    function insertPdqBoardInfo() {
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("PDQBoardInformation", false)) {
            Application.Alert(
                    "Can't insert PDQBoardInformation element");
                return;
        }
        var newElems = "<PDQBoardInformation>"
                     + "<BoardManager>"
                     + "<?xm-replace_text {Enter Board Manager name} ?>"
                     + "</BoardManager>"
                     + "<BoardManagerPhone>"
                     + "<?xm-replace_text {Enter Board Manager phone} ?>"
                     + "</BoardManagerPhone>"
                     + "<BoardManagerEmail>"
                     + "<?xm-replace_text {Enter Board Manager e-mail} ?>"
                     + "</BoardManagerEmail>"
                     + "<BoardMeetingDate>"
                     + "<Year>"
                     + "<?xm-replace_text {Enter year for set of meeting "
                     + "dates} ?></Year>"
                     + "<Date>"
                     + "<?xm-replace_text {Enter each meeting date for the"
                     + " year as a separate occurrence} ?>"
                     + "</Date>"
                     + "<DayTime>"
                     + "<?xm-replace_text {Enter meeting day and time}"
                     + " ?></DayTime>"
                     + "</BoardMeetingDate>"
                     + "</PDQBoardInformation>";
        rng.PasteString(newElems);
        rng.Select();
    }
    insertPdqBoardInfo();
  ]]>
</MACRO>

<MACRO name="Set Non-Public"
       lang="JScript" >
  <![CDATA[
    function setNonPublic() {
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (!docType.hasAttribute(container.nodeName, "Public")) {
            Application.Alert(
                "Current element does not have a Public attribute.");
            return;
        }

        var holdFlag = Selection.ReadOnlyContainer;
        Selection.ReadOnlyContainer = false;
        gEditingCdrLink = true;
        container.setAttribute("Public", "No");
        gEditingCdrLink = false;
        Selection.ReadOnlyContainer = holdFlag;
    }
    setNonPublic();
  ]]>
</MACRO>

<MACRO name="Set Public"
       lang="JScript" >
  <![CDATA[
    function setPublic() {
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (!docType.hasAttribute(container.nodeName, "Public")) {
            Application.Alert(
                "Current element does not have a Public attribute.");
            return;
        }

        var holdFlag = Selection.ReadOnlyContainer;
        Selection.ReadOnlyContainer = false;
        gEditingCdrLink = true;
        container.removeAttribute("Public");
        gEditingCdrLink = false;
        Selection.ReadOnlyContainer = holdFlag;
    }
    setPublic();
  ]]>
</MACRO>

<MACRO name="Linked Docs Report"
       lang="JScript" >
  <![CDATA[
    function linkedDocsReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "LinkedDocs.py?Session="
                + CdrSession
                + "&DocId="
                + docId
                + "&LinkingDocType=Any+Type";
        cdrObj.showPage(url);
    }
    linkedDocsReport();
  ]]>
</MACRO>

<MACRO name="Linked Fragment Docs Report"
       lang="JScript" >
  <![CDATA[
    function linkedFragmentDocsReport() {
        var docId = getDocId();
        var fragId = getFragId();
        if (!fragId) {
            Application.Alert("Unable to find fragment ID for current " +
                              "location");
            return;
        }
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "LinkedDocs.py?Session="
                + CdrSession
                + "&DocId="
                + docId
                + "&FragId="
                + fragId
                + "&LinkingDocType=Any+Type";
        cdrObj.showPage(url);
    }
    linkedFragmentDocsReport();
  ]]>
</MACRO>

<MACRO name="Audit Trail Report"
       lang="JScript" >
  <![CDATA[
    function auditTrailReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "AuditTrail.py?id=" + docId;
        cdrObj.showPage(url);
    }
    auditTrailReport();
  ]]>
</MACRO>

<MACRO name="Back Out Rejected Markup"
       lang="JScript" >
  <![CDATA[

    //----------------------------------------------------------------------
    // Drop marked changes.
    //----------------------------------------------------------------------
    function backOutRejectedMarkup()
    {
        var r = ActiveDocument.Range;
        r.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            var elem = r.ContainerNode;
            var revLevel = elem.getAttribute("RevisionLevel");
            if (revLevel == "rejected")
                r.RemoveContainerTags();
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            var elem = r.ContainerNode;
            var revLevel = elem.getAttribute("RevisionLevel");
            if (revLevel == "rejected") {
                r.SelectContainerContents();
                r.Delete();
                r.RemoveContainerTags();
            }
        }
        r = null;
    }

    if (CanRunMacros()) {
        var confirm = Application.Confirm("Do you want to back out all " +
                                          "rejected changes without " +
                                          "reviewing them?");
        if (confirm) {
            backOutRejectedMarkup();
        }
    }

  ]]>
</MACRO>

<MACRO name="Glossary Phrase Search"
       lang="JScript" >
  <![CDATA[
    function glossaryPhraseSearch() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "GlossaryTermPhrases.py?Session="
                + CdrSession
                + "&Id=" + docId;
        cdrObj.showPage(url);
    }
    glossaryPhraseSearch();
  ]]>
</MACRO>

<MACRO name="Glossify Document"
       lang="JScript" >
  <![CDATA[
    if (!cdrDocReadOnly()) {
        cdrObj.glossify(false);
        ActiveDocument.FormattingUpdating = true;
    }
  ]]>
</MACRO>

<MACRO name="Glossify Document (dig)"
       lang="JScript" >
  <![CDATA[
    if (!cdrDocReadOnly()) {
        cdrObj.glossify(true);
        ActiveDocument.FormattingUpdating = true;
    }
  ]]>
</MACRO>

<MACRO name="Add Glossary Phrase"
       lang="JScript" >
  <![CDATA[
    cdrObj.addGlossaryPhrase();
  ]]>
</MACRO>

<MACRO name="On_Application_ElementList_Insert"
       lang="JScript">
  <![CDATA[
    function onElementListInsert() {
        var name = Application.ElementList.SelectedName;
        var dt = ActiveDocument.doctype.name;
        if (dt == 'GlossaryTermConcept' || dt == 'GlossaryTermName') {
            if (name == 'ProcessingStatus' || name == 'ProcessingStatuses' ||
                name == 'ProcessingStatusValue') {
                var newElem = "<ProcessingStatusValue user='"
                            + CdrUserName
                            + "' date='"
                            + getCurDateString()
                            + "'><?xm-replace_text { Select a "
                            + "processing status value (required) }?>"
                            + "</ProcessingStatusValue>";
                if (name != 'ProcessingStatusValue')
                    newElem = '<ProcessingStatus>' + newElem
                            + '</ProcessingStatus>';
                if (name == 'ProcessingStatuses')
                    newElem = '<ProcessingStatuses>'
                            + newElem
                            + '</ProcessingStatuses>';
                //Application.Alert("selected name is " + name);
                if (Selection.CanPaste(newElem))
                    Selection.PasteString(newElem);
                else
                    Application.Alert("can't paste " + name);
                Selection.GotoPrevious(2);
                return;
            }
            Selection.InsertWithTemplate(name);
        }
        //Selection.InsertWithTemplate(name);
    }
    onElementListInsert()
  ]]>
</MACRO>

<MACRO name="On_CommandBars_Activate"
       lang="JScript">
  <![CDATA[
    function showToolbarForDoctype() {
        var docType = ActiveDocument.doctype;
        if (docType) {
            var bar = toolbars[docType.name];
            if (bar != null && !bar.Visible) {
                bar.Visible = true;
            }
        }
    }
    if (Application.VersionNumber > 4.5)
        adjustToolbarVisibility();
    else {
        try { showToolbarForDoctype(); }
        catch (e) {}
    }
  ]]>
</MACRO>

<!-- Doesn't work as documented; suppressed at Derek's suggestion 2015-04-19
<MACRO name="On_CommandBars_DeActivate"
       lang="JScript">
  <![CDATA[
    if (Application.VersionNumber > 4.5)
        adjustToolbarVisibility();
    else {
        try { hideToolbars(); }
        catch (e) {}
    }
  ]]>
</MACRO
-->

<MACRO name="On_Document_Save"
       lang="JScript">
    function onDocumentSave() {
        var desc = 'Save("' + ActiveDocument.FullName + '")';
        if (cdrObj) {
            var eventId = cdrObj.logClientEvent(desc);
            // Application.Alert("logged event " + eventId);
        }
        else
            Application.Alert(desc + ": not logged into the CDR")
    }
    onDocumentSave();
</MACRO>

<MACRO name="On_Document_SaveAs"
       lang="JScript">
    function onDocumentSaveAs() {
        var desc = 'SaveAs("' + ActiveDocument.FullName + '")';
        if (cdrObj) {
            var eventId = cdrObj.logClientEvent(desc);
            // Application.Alert("logged event " + eventId);
        }
        else
            Application.Alert(desc + ": not logged into the CDR")
    }
    onDocumentSaveAs();
</MACRO>

<MACRO name="ShowCDRServer"
       lang="JScript">
    if (cdrObj)
        cdrObj.setTitleBar();
    else
        Application.Alert("no cdrObj");
</MACRO>

<MACRO name="Show Doc Blob"
       lang="JScript" >
  <![CDATA[
    function showDocBlob() {
        var docId  = getDocId();
        var docVer = getDocVersion();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!cdrObj) {
            Application.Alert("Not logged into CDR");
            return;
        }
        // cdrObj.launchBlob(docId, docVer ? docVer : "");
        var url = CdrCgiBin + "GetCdrBlob.py?id=" + docId;
        if (docVer)
            url += "&ver=" + docVer;
        cdrObj.showPage(url);
    }
    showDocBlob();
  ]]>
</MACRO>

<MACRO name="Show Linked Blob"
       lang="JScript" >
  <![CDATA[
    function showLinkedBlob() {
        if (!cdrObj) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var docId    = null;
        var elemName = null;
        var rng      = ActiveDocument.Range;
        for (var i in blobLinkElementNames) {
            if (rng.IsParentElement(blobLinkElementNames[i])) {
                elemName = elemNames[i];
                break;
            }
        }
        if (elemName) {
            if (rng.MoveToElement(elemName, false)) {
                var elem = rng.ContainerNode;
                docId = elem.GetAttribute("cdr:ref");
            }
        }
        if (docId)
            cdrObj.launchBlob(docId, "");
        else
            Application.Alert("No link found to a viewable object.");
    }
    showLinkedBlob();
  ]]>
</MACRO>

<MACRO name="Open Translated Summary"
       lang="JScript" >
  <![CDATA[
    function openTranslatedSummary() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        //Application.Alert("My ID: " + docId);
        var translatedSummaryId = cdrObj.getTranslatedDocId(docId);
        if (!translatedSummaryId)
            return;
        //Application.Alert("translation ID: " + translatedSummaryId);
        cdrObj.openCdrDoc(translatedSummaryId, "Current", false);
    }
    openTranslatedSummary();
  ]]>
</MACRO>

<MACRO name="Open Original English Summary"
       lang="JScript" >
  <![CDATA[
    function openOriginalEnglishSummary() {
        if (!Application.ActiveDocument) { return null; }
        var name = "TranslationOf";
        var nodes = Application.ActiveDocument.getElementsByTagName(name);
        if (nodes.length < 1) {
            Application.Alert("TranslationOf element not found");
            return;
        }
        var elem = nodes.item(0);
        var originalId = elem.getAttribute("cdr:ref");
        if (!originalId) {
            Application.Alert("ID of original summary not found");
            return;
        }
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        cdrObj.openCdrDoc(originalId, "Current", false);
    }
    openOriginalEnglishSummary();
  ]]>
</MACRO>

<MACRO name="Open Patient Summary"
       lang="JScript" >
  <![CDATA[
    function openPatientSummary() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var patientSummaryId = cdrObj.getPatientDocId(docId);
        if (!patientSummaryId)
            return;
        cdrObj.openCdrDoc(patientSummaryId, "Current", false);
    }
    openPatientSummary();
  ]]>
</MACRO>

<MACRO name="Open HP Summary"
       lang="JScript" >
  <![CDATA[
    function openHPSummary() {
        if (!Application.ActiveDocument) { return null; }
        var name = "PatientVersionOf";
        var nodes = Application.ActiveDocument.getElementsByTagName(name);
        if (nodes.length < 1) {
            Application.Alert("PatientVersionOf element not found");
            return;
        }
        var elem = nodes.item(0);
        var hpId = elem.getAttribute("cdr:ref");
        if (!hpId) {
            Application.Alert("ID of health professional summary not found");
            return;
        }
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        cdrObj.openCdrDoc(hpId, "Current", false);
    }
    openHPSummary();
  ]]>
</MACRO>

<MACRO name="Open Board Member Doc"
       lang="JScript" >
  <![CDATA[
    function openBoardMemberDoc() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var boardMemberId = cdrObj.getBoardMemberId(docId);
        if (!boardMemberId)
            return;
        cdrObj.openCdrDoc(boardMemberId, "Current", false);
    }
    openBoardMemberDoc();
  ]]>
</MACRO>

<MACRO name="Open Person Doc For Board Member"
       lang="JScript" >
  <![CDATA[
    function openPersonDocForBoardMember() {
        if (!Application.ActiveDocument) { return null; }
        var name = "BoardMemberName";
        var nodes = Application.ActiveDocument.getElementsByTagName(name);
        if (nodes.length < 1) {
            Application.Alert("BoardMemberName element not found");
            return;
        }
        var elem = nodes.item(0);
        var personId = elem.getAttribute("cdr:ref");
        if (!personId) {
            Application.Alert("ID for person document not found");
            return;
        }
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        cdrObj.openCdrDoc(personId, "Current", false);
    }
    openPersonDocForBoardMember();
  ]]>
</MACRO>

<MACRO name="Open Linked Doc Edit Mode"
       lang="JScript" >
  <![CDATA[
    function openLinkedDocEditMode() {
        var container = Selection.ContainerNode;
        var linkedDocId = container.getAttribute("cdr:ref");
        if (!linkedDocId)
            linkedDocId = container.getAttribute("cdr:href");
        // No need to strip fragment portion; DLL does that.
        cdrObj.openCdrDoc(linkedDocId, "Current", true);
    }
    openLinkedDocEditMode();
  ]]>
</MACRO>

<MACRO name="Open Linked Doc View Mode"
       lang="JScript" >
  <![CDATA[
    function openLinkedDocViewMode() {
        var container = Selection.ContainerNode;
        var linkedDocId = container.getAttribute("cdr:ref");
        if (!linkedDocId)
            linkedDocId = container.getAttribute("cdr:href");
        // No need to strip fragment portion; DLL does that.
        cdrObj.openCdrDoc(linkedDocId, "Current", false);
    }
    openLinkedDocViewMode();
  ]]>
</MACRO>

<MACRO name="View Linked Glossary Term Concept Doc"
       lang="JScript" >
  <![CDATA[
    function viewLinkedGlossaryTermConceptDoc() {
        var doc = Application.ActiveDocument;
        var conceptElems = doc.getElementsByTagName("GlossaryTermConcept");
        if (!conceptElems.length)
            Application.Alert("Can't find GlossaryTermConcept element");
        else {
            var conceptElem = conceptElems.item(0);
            var docId = conceptElem.getAttribute("cdr:ref");
            cdrObj.openCdrDoc(docId, "Current", false);
        }
    }
    viewLinkedGlossaryTermConceptDoc();
  ]]>
</MACRO>

<MACRO name="Edit Linked Glossary Term Concept Doc"
       lang="JScript" >
  <![CDATA[
    function editLinkedGlossaryTermConceptDoc() {
        var doc = Application.ActiveDocument;
        var conceptElems = doc.getElementsByTagName("GlossaryTermConcept");
        if (!conceptElems.length)
            Application.Alert("Can't find GlossaryTermConcept element");
        else {
            var conceptElem = conceptElems.item(0);
            var docId = conceptElem.getAttribute("cdr:ref");
            cdrObj.openCdrDoc(docId, "Current", true);
        }
    }
    editLinkedGlossaryTermConceptDoc();
  ]]>
</MACRO>

<MACRO name="Show Glossary Term Names"
       lang="JScript" >
  <![CDATA[
    function showGlossaryTermNames() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var termNames = cdrObj.getGlossaryTermNames(docId);
        if (!termNames)
            Application.Alert("No term name documents found");
        else
            Application.Alert("Term names:\n" + termNames);
    }
    showGlossaryTermNames();
  ]]>
</MACRO>

<MACRO name="View Glossary Term Name Docs"
       lang="JScript" >
  <![CDATA[
    function viewGlossaryTermNameDocs() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var termIds = cdrObj.getGlossaryTermNameIds(docId);
        if (!termIds)
            Application.Alert("No term name documents found");
        else {
            var pieces = termIds.split(' ');
            for (var i in pieces) {
                var termId = pieces[i];
                cdrObj.openCdrDoc(termId, "Current", false);
            }
        }
    }
    viewGlossaryTermNameDocs();
  ]]>
</MACRO>

<MACRO name="Edit Glossary Term Name Docs"
       lang="JScript" >
  <![CDATA[
    function editGlossaryTermNameDocs() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var termIds = cdrObj.getGlossaryTermNameIds(docId);
        if (!termIds)
            Application.Alert("No term name documents found");
        else {
            var pieces = termIds.split(' ');
            for (var i in pieces) {
                var termId = pieces[i];
                cdrObj.openCdrDoc(termId, "Current", true);
            }
        }
    }
    editGlossaryTermNameDocs();
  ]]>
</MACRO>

<MACRO name="Clone Doc"
       lang="JScript">
  <![CDATA[
    function stripCdrIdAttrs(elemNode) {
        if (elemNode.hasAttribute("cdr:id"))
            elemNode.removeAttribute("cdr:id");
        var child = elemNode.firstChild;
        while (child) {
            if (child.nodeType == 1) // DOMElement
                stripCdrIdAttrs(child);
            child = child.nextSibling;
        }
    }
    // function stripDocId(docElem) {
    //     var target = "xm-replace_text";
    //     var data   = "{The document ID will be assigned automatically} ";
    //     var newPI  = ActiveDocument.createProcessingInstruction(target, data);
    //     var node   = docElem.firstChild;
    //     while (node) {
    //         if (node.nodeName == 'CdrDocCtl') {
    //             var child = node.firstChild;
    //             while (child) {
    //                 if (child.nodeName == 'DocId') {
    //                     gEditingCdrLink = true;
    //                     var grandchild = child.firstChild;
    //                     while (grandchild) {
    //                         var nextGrandchild = grandchild.nextSibling;
    //                         child.removeChild(grandchild);
    //                         grandchild = nextGrandchild;
    //                     }
    //                     grandchild.appendChild(newPI);
    //                     gEditingCdrLink = false;
    //                 }
    //                 child = child.nextSibling;
    //             }
    //         }
    //         node = node.nextSibling;
    //     }
    // }

    function mediaTitle() {
        var nodes = ActiveDocument.getElementsByTagName("MediaTitle");
        var title = "";
        if (nodes.length > 0) {
            var elem = nodes.item(0);
            title = getTextContent(elem);
        }
        return title;
    }
    // Extracting the CDR-ID of the parent document
    //function getDocId(docText) {
    //    var sourceId = docText.match(/CDR\d+/);
    //    return sourceId;
    //}
    function getDocIdNew() {
        var nodes = ActiveDocument.getElementsByTagName("DocId");
        var cdrId = "";
        if (nodes.length > 0) {
            var elem = nodes.item(0);
            cdrId = getTextContent(elem);
        }
        return cdrId;
    }
    // Set language attribute for element(s) to "es"
    function chgLabelLanguage(doc, languageElem) {
        var elemName = languageElem;
        var labelElems = doc.getElementsByTagName(elemName);

        if (!labelElems.length) {
             Application.Alert("No Labels found");
             return;
        }

        for (var i = 0; i < labelElems.length; ++i) {
            var labelElement = labelElems.item(i);
            labelElement.setAttribute("language", "es");
        }

    }
    function fixDocId(docText) {
        var docId = "<DocId><?xm-replace_text {The document ID will be "
                  + "assigned automatically} ?></DocId>";
        return docText.replace(/<DocId[^>]*>CDR\d+<\/DocId>/, docId);
    }
    // Comments from the original document should not be copied to
    // the cloned document.
    // Note: The regex works because the Comment and Media elements
    //       are on one line.
    function removeComment(docText) {
        return docText.replace(/<Comment.+<\/Comment><\/Media>/, "<\/Media>");
    }
    // Adding new TranslationOf element with CDR-ID from parent
    // document.
    function addTranslationOf(docText, CdrId, title) {
        var enCdrId = CdrId;
        var transElem = "<TranslationOf cdr:ref=\""
                  + enCdrId
                  + "\">"
                  + title
                  + "</TranslationOf>";
        return docText.replace(/<\/Media>/, transElem + "<\/Media>");
    }
    // Main function to clone the document
    function cloneDoc() {
        var docType = ActiveDocument.doctype;

        // Extract CDR-ID and document title to populate
        // TranslationOf element.
        var docCdrId = getDocIdNew();
        var title = mediaTitle();

        if (docType) {
            var rng = ActiveDocument.Range;
            rng.SelectAll();
            rng.Copy();
            var curDoc = Application.Clipboard.Text;
            var newDoc = fixDocId(curDoc);
            newDoc = removeComment(newDoc);
            newDoc = addTranslationOf(newDoc, docCdrId, title);
            var xmlText = "<?xml version='1.0'?>\n<!DOCTYPE "
                        + docType.name
                        + " SYSTEM '"
                        + docType.name
                        + ".dtd'>\n"
                        + newDoc;
            var doc = Application.Documents.OpenString(xmlText, 0,
                                                       "newdoc.xml",
                                                       true, true, false);
            var docElem = doc.documentElement;
            if (docElem.hasAttribute("readonly"))
                docElem.removeAttribute("readonly");
            stripCdrIdAttrs(docElem);
            // Change language attribute for these elements
            chgLabelLanguage(docElem, "LabelName");
            chgLabelLanguage(docElem, "ContentDescription");
            chgLabelLanguage(docElem, "MediaCaption");
        }
    }
    cloneDoc();
  ]]>
</MACRO>

<MACRO name="Make Citation Supplementary Info Doc"
       lang="JScript">
  <![CDATA[
    function stripCdrIdAttrs(elemNode) {
        if (elemNode.hasAttribute("cdr:id"))
            elemNode.removeAttribute("cdr:id");
        var child = elemNode.firstChild;
        while (child) {
            if (child.nodeType == 1) // DOMElement
                stripCdrIdAttrs(child);
            child = child.nextSibling;
        }
    }
    function getDocTitle() {
        var node = ActiveDocument.documentElement.firstChild;
        while (node) {
            if (node.nodeName == 'CdrDocCtl') {
                var child = node.firstChild;
                while (child) {
                    if (child.nodeName == 'DocTitle')
                        return getTextContent(child);
                    child = child.nextSibling;
                }
            }
            node = node.nextSibling;
        }
        return "*** DocTitle not found ***";
    }
    function insertCitationTitle(doc, title) {
        var nodes = doc.getElementsByTagName('Title');
        if (nodes.length < 1) {
            Application.Alert("Title element not found");
            return;
        }
        var elem = nodes.item(0);
        var child = elem.firstChild;
        while (child) {
            var nextChild = child.nextSibling;
            elem.removeChild(child);
            child = nextChild;
        }
        var textNode = doc.createTextNode(title);
        elem.appendChild(textNode);
    }
    function makeCitationSupplementaryInfoDoc() {

        var title = getDocTitle();
        var template = CdrUserPath
              + "\\Template\\Cdr\\CitationSupplementaryInfo.xml";
        var doc = Application.Documents.OpenTemplate(template);
        insertCitationTitle(doc, title);
    }
    makeCitationSupplementaryInfoDoc();
  ]]>
</MACRO>

<MACRO name="PI Bug Repro"
       lang="JScript"
       key="Ctrl+Alt+O">
  <![CDATA[
    function piBugRepro() {

        // Create a new document.
        var xml = "<?xml version='1.0' ?>\n"
                + "<!DOCTYPE Article SYSTEM 'journalist.dtd'>\n"
                + "<Article>\n <Title>PI Bug Repro</Title>\n"
                + " <Para><?xm-replace_text { Riveting prose here }?></Para>\n"
                + "</Article>";
        var doc = Application.Documents.OpenString(xml);
        var elem = doc.createElement('Para');
        var prompt = '{ Boring stuff here }';
        var pi = doc.createProcessingInstruction('xm-replace_text', prompt);
        elem.appendChild(pi);
        doc.documentElement.appendChild(elem);
    }
    piBugRepro();
  ]]>
</MACRO>

<MACRO name="Make Glossary Term Name Doc"
       lang="JScript">
  <![CDATA[
    function makeGlossaryTermNameDoc() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var template = CdrUserPath
                     + "\\Template\\Cdr\\GlossaryTermName.xml";
        var doc = Application.Documents.OpenTemplate(template);
        var docIdElems = doc.getElementsByTagName('GlossaryTermConcept');
        if (!docIdElems.length) {
            Application.Alert("InScopeDocID element not found");
            return;
        }
        var docIdElem = docIdElems.item(0);
        var child = docIdElem.firstChild;
        while (child) {
            var nextChild = child.nextSibling;
            docIdElem.removeChild(child);
            child = nextChild;
        }
        docIdElem.setAttribute("cdr:ref", docId);
    }
    makeGlossaryTermNameDoc();
  ]]>
</MACRO>

<MACRO name="Bug Repro" lang="JScript">
  <![CDATA[
    function bugRepro() {
        var elemName = Application.Prompt("Element to replace?");
        var doc      = Application.ActiveDocument;
        var newElem  = doc.createElement(elemName);
        var textNode = doc.createTextNode("foo");
        var oldElem  = doc.getElementsByTagName(elemName).item(0);
        newElem.appendChild(textNode);
        oldElem.parentNode.replaceChild(newElem, oldElem);
    }
    bugRepro();
  ]]>
</MACRO>

<MACRO name="Show Next Validation Error" lang="JScript" key="Alt+E">
  <![CDATA[
    function showNextValidationError() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var result = cdrObj.getNextValidationError();
        var pieces = result.split('|');
        var eid = pieces.shift();
        var message = pieces.join('|');
        Application.Alert(message);
        if (!eid || eid != "0") {
            var xpath = '//*[@cdr-eid="' + eid + '"]';
            var node = null;
            // Alternate approach
            // var nodes = ActiveDocument.getNodesByXPath(xpath);
            // if (nodes.length)
            //     node = nodes.item(0);
            node = ActiveDocument.getElementById(eid);
            if (node) {
                Selection.SelectNodeContents(node);
                Selection.MoveLeft(0);
            }
            else
                Application.Alert("unable to find node '" + eid + "'");
        }
    }
    showNextValidationError();
  ]]>
</MACRO>

/*
 * XMetaL can't find this.  Reported to Derek 2008-04-10.
 */
<MACRO name="xpath bug repro" lang="JScript">
  <![CDATA[
    function xpathBugRepro() {
        var xpath = "//*[@*[namespace-uri()='cips.nci.nih.gov/cdr' " +
                    "and local-name()='eid']='62']";
        var nodes = ActiveDocument.getNodesByXPath(xpath);
        if (nodes.length) {
            Selection.SelectNodeContents(nodes.item(0));
            Selection.MoveLeft(0);
        }
        else {
            Application.Alert("can't find '" + xpath + "'");
        }
    }
    xpathBugRepro();
  ]]>
</MACRO>

<MACRO name="Find Private Use Chars" lang="JScript">
  <![CDATA[
    /*
     * We can't just use rng.MoveRight() repeatedly to check for private
     * use characters one at a time, because the XMetaL API skips over
     * the private use characters.  Shelving work on this, since it's a
     * lower-priority task than some of the other issues I'm working on
     * right now.  When we proceed with implementing this, use the new
     *
     */
    function findPrivateUseChars() {
        var rng = ActiveDocument.Range;
        var found = false;
        rng.SelectAll()
        var text = rng.Text;
        var pos = text.search(/[\uE000-\uF8FF]/);
        while (pos != -1) {
            text = text.substring(0, pos)
                 + "<cdr:PrivateUseCharacter>U+"
                 + text.charCodeAt(pos).toString(16)
                 + "</cdr:PrivateUseCharacter>"
                 + text.substring(pos + 1);
            found = true;
            pos = text.search(/[\uE000-\uF8FF]/);
        }
        if (found) {
            Application.Alert("Replaced private use characters; text is now " +
                              text.length + " characters long");
            var rulesChecking = ActiveDocument.RulesChecking;
            ActiveDocument.RulesChecking = false;
            rng.Delete();
            ActiveDocument.RulesChecking = false;
            rng.PasteString(text);
            ActiveDocument.RulesChecking = rulesChecking;
            rng.MoveToDocumentStart();
            if (rng.MoveToElement("cdr:PrivateUseCharacter")) {
                rng.Select();
                rng.SelectElement();
            }
        }
        if (!found)
            Application.Alert("No private use characters found");
    }
    findPrivateUseChars();
  ]]>
</MACRO>

<MACRO name="Insert Comment"
       lang="JScript">
  <![CDATA[
    function insertComment() {
        var rng = ActiveDocument.Range;
        // rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("Comment")) {
            Application.Alert("Can't insert Comment element " +
                              "under current position.");
            return;
        }
        var newElem = "<Comment user='"
                    + CdrUserName
                    + "' audience='Internal' date='"
                    + getCurDateString()
                    + "'><?xm-replace_text { Your comment here }?></Comment>";
        rng.PasteString(newElem);
        rng.MoveToElement("Comment", false);
        rng.SelectElement();
        rng.Collapse(1);
        rng.MoveRight();
        rng.Select();
    }
    insertComment();
  ]]>
</MACRO>

<MACRO name="Insert ResponseToComment"
       lang="JScript">
  <![CDATA[
    function insertResponseToComment() {
        // This is the same as insertComment, and I considered extracting
        //   the common logic, but the savings is small and I'm not
        //   certain that the required logic for Comment and ResponseToComment
        //   will never diverge.   -- AHM
        var rng = ActiveDocument.Range;
        if (!rng.FindInsertLocation("ResponseToComment")) {
            Application.Alert("Can't insert ResponseToComment element " +
                              "under current position.");
            return;
        }
        var newElem = "<ResponseToComment user='"
            + CdrUserName
            + "' audience='Internal' date='"
            + getCurDateString()
            + "'><?xm-replace_text { Your comment response here }?></ResponseToComment>";
        rng.PasteString(newElem);
        rng.MoveToElement("ResponseToComment", false);
        rng.SelectElement();
        rng.Collapse(1);
        rng.MoveRight();
        rng.Select();
    }
    insertResponseToComment();
  ]]>
</MACRO>

<MACRO name="SC Up"
       lang="JScript">Selection.TypeText("&amp;#x2191;");</MACRO>
<MACRO name="SC Down"
       lang="JScript">Selection.TypeText("&amp;#x2193;");</MACRO>
<MACRO name="SC Right"
       lang="JScript">Selection.TypeText("&amp;#x2192;");</MACRO>
<MACRO name="SC Left"
       lang="JScript">Selection.TypeText("&amp;#x2190;");</MACRO>
<MACRO name="SC alpha"
       lang="JScript">Selection.TypeText("&amp;#x03B1;");</MACRO>
<MACRO name="SC beta"
       lang="JScript">Selection.TypeText("&amp;#x03B2;");</MACRO>
<MACRO name="SC gamma"
       lang="JScript">Selection.TypeText("&amp;#x03B3;");</MACRO>
<MACRO name="SC delta"
       lang="JScript">Selection.TypeText("&amp;#x03B4;");</MACRO>
<MACRO name="SC mu"
       lang="JScript">Selection.TypeText("&amp;#x03BC;");</MACRO>
<MACRO name="SC le"
       lang="JScript">Selection.TypeText("&amp;#x2264;");</MACRO>
<MACRO name="SC ge"
       lang="JScript">Selection.TypeText("&amp;#x2265;");</MACRO>
<MACRO name="SC copy"
       lang="JScript">Selection.TypeText("&amp;#x00A9;");</MACRO>
<MACRO name="SC reg"
       lang="JScript">Selection.TypeText("&amp;#x00AE;");</MACRO>
<MACRO name="SC TM"
       lang="JScript">Selection.TypeText("&amp;#x2122;");</MACRO>
<MACRO name="SC deg"
       lang="JScript">Selection.TypeText("&amp;#x00B0;");</MACRO>
<MACRO name="SC cross"
       lang="JScript">Selection.TypeText("&amp;#x2020;");</MACRO>
<MACRO name="SC dblx"
       lang="JScript">Selection.TypeText("&amp;#x2021;");</MACRO>
<MACRO name="SC mdash"
       lang="JScript">Selection.TypeText("&amp;#x2014;");</MACRO>
<MACRO name="SC plusmin"
       lang="JScript">Selection.TypeText("&amp;#x00B1;");</MACRO>
<MACRO name="SC lquot"
       lang="JScript">Selection.TypeText("&amp;#x201C;");</MACRO>
<MACRO name="SC rquot"
       lang="JScript">Selection.TypeText("&amp;#x201D;");</MACRO>
<MACRO name="SC lapos"
       lang="JScript">Selection.TypeText("&amp;#x2018;");</MACRO>
<MACRO name="SC rapos"
       lang="JScript">Selection.TypeText("&amp;#x2019;");</MACRO>
<MACRO name="SC quarter"
       lang="JScript">Selection.TypeText("&amp;#x00BC;");</MACRO>
<MACRO name="SC half"
       lang="JScript">Selection.TypeText("&amp;#x00BD;");</MACRO>
<MACRO name="SC 3quart"
       lang="JScript">Selection.TypeText("&amp;#x00BE;");</MACRO>
<MACRO name="SC nbsp"
       lang="JScript">Selection.TypeText("&amp;#x00A0;");</MACRO>

<MACRO name="Edit Comment" lang="JScript">
  <![CDATA[
    function editComment() {
        var readOnly = cdrDocReadOnly();
        cdrObj.editComment(readOnly);
    }
    editComment();
  ]]>
</MACRO>

<MACRO name="Set Last Reviewed Date" lang="JScript">
  <![CDATA[
    function setLastReviewedDateAttribute() {
        var today = getCurDateString();
        var node  = Selection.ContainerNode;
        var depth = 5;
        while (node && node.nodeType != 1 && depth-- > 0)
            node = node.parentNode;
        if (node && node.nodeType == 1)
            node.setAttribute("LastReviewedDate", today);
    }
    setLastReviewedDateAttribute();
  ]]>
</MACRO>

<MACRO name="Insert TypeOfChange"
       lang="JScript">
  <![CDATA[
    function insertTypeOfChange() {
        var rng = ActiveDocument.Range;
        // rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("TypeOfSummaryChange")) {
            Application.Alert("Can't insert TypeOfSummaryChange element " +
                              "under current position.");
            return;
        }
        var newElem = "<TypeOfSummaryChange>"
                    + "  <TypeOfSummaryChangeValue"
                    + "><?xm-replace_text { Select a change type }?>"
                    + "</TypeOfSummaryChangeValue>"
                    + "<User>"
                    + CdrUserName
                    + "</User>"
                    + "<Date>"
                    + getCurDateString()
                    + "</Date>"
                    + "<Comment user='"
                    + CdrUserName
                    + "' audience='Internal' date='"
                    + getCurDateString()
                    + "'><?xm-replace_text { Enter a Comment }?></Comment>"
                    + "</TypeOfSummaryChange>";
        rng.PasteString(newElem);
        rng.MoveToElement("Comment", false);
        rng.SelectElement();
        rng.Collapse(1);
        rng.MoveRight();
        rng.Select();
    }
    insertTypeOfChange();
  ]]>
</MACRO>

<MACRO name="Find Next Advisory Board Markup" lang="JScript">
  <![CDATA[
    function findNextAdvisoryBoardMarkup() {
        for (;;) {
           var start = Selection.Duplicate;
           Selection.GotoNext(0);
           if (!start.IsLessThan(Selection.Duplicate)) {
                Application.Alert("No more Advisory Board markup found.");
                break;
            }
            //path = getSelectionPath(Selection);
            var tag = Selection.ContainerName;
            if (tag == 'Deletion' || tag == 'Insertion') {
                var elem = Selection.ContainerNode;
                var attr = elem.getAttribute('Source');
                if (attr == 'advisory-board')
                    break;
            }
        }
    }
    findNextAdvisoryBoardMarkup();
  ]]>
</MACRO>

<MACRO name="Spanish Link ID Swap" lang="JScript">
  <![CDATA[
    function spanishLinkIdSwap() {
        var doc = Application.ActiveDocument;
        var translationOf = getSingleElement(doc, "TranslationOf");
        if (!translationOf) {
            Application.Alert("TranslationOf element not found.");
            return;
        }
        var oldId = translationOf.getAttribute('cdr:ref');
        var newId = getDocId();
        if (!oldId) {
            Application.Alert("TranslationOf document ID not found.");
            return;
        }
        if (oldId.length != 13 || oldId.substr(0, 3) != 'CDR') {
            Application.Alert("Malformed TranslationOf document ID: " + oldId);
            return;
        }
        if (!newId) {
            Application.Alert("Summary has not yet been saved.");
            return;
        }
        if (newId.length != 13 || newId.substr(0, 3) != 'CDR') {
            Application.Alert("Malformed document ID: " + newId);
            return;
        }
        var links = doc.getElementsByTagName("SummaryFragmentRef");
        var replaced = 0;
        for (var i = 0; i < links.length; ++i) {
            var linkElement = links.item(i);
            var linkId = linkElement.getAttribute("cdr:href");
            if (linkId.substr(0, 13) == oldId) {
                var newValue = newId + linkId.substr(13);
                linkElement.setAttribute("cdr:href", newValue);
                ++replaced;
            }
        }
        Application.Alert("Swapped " + replaced + " link(s).");
    }
    spanishLinkIdSwap();
  ]]>
</MACRO>

<MACRO name="Test Env Fetch" lang="JScript">
  <![CDATA[
    function testEnvFetch() {
        try {
            var name = Application.Prompt("Env Variable Name?");
            var wsh = new ActiveXObject("Wscript.Shell");

            //Get the list of environment variables
            var envVars = wsh.Environment("PROCESS");
            var value = envVars.Item(name)
            Application.Alert(value);
            wsh = null;
        }
        catch (e) {
            wsh = null;
            Application.Alert(e);
        }
    }
    testEnvFetch();
  ]]>
</MACRO>

<MACRO name="Apply Revision Level" lang="JScript">
  <![CDATA[
    function applyRevisionLevel() {
        try {
            var level = cdrObj.chooseRevisionLevel();
            if (level) {
                var holdFlag = Selection.ReadOnlyContainer;
                Selection.ReadOnlyContainer = false;
                var sel = ActiveDocument.Range;
                var count = setRevMarkupAttrs(sel, "RevisionLevel", level);
                Selection.ReadOnlyContainer = holdFlag;
                var message = "Marked " + count + " element";
                if (count != 1)
                    message += "s";
                message += " as '" + level + "'.";
                Application.Alert(message);
            }
            else
                Application.Alert("Action canceled.");
        }
        catch (e) {
            Application.Alert(e);
        }
    }
    applyRevisionLevel();
  ]]>
</MACRO>

<MACRO name="Set Source to Advisory Board" lang="JScript">
  <![CDATA[
    function setSourceToAdvisoryBoard() {
        try {
            var holdFlag = Selection.ReadOnlyContainer;
            Selection.ReadOnlyContainer = false;
            var sel = ActiveDocument.Range;
            var count = setRevMarkupAttrs(sel, "Source", "advisory-board");
            Selection.ReadOnlyContainer = holdFlag;
            var message = "Set Source to 'advisory-board' for " + count
                        + " element";
            if (count != 1)
                message += "s";
            message += ".";
            Application.Alert(message);
        }
        catch (e) {
            Application.Alert(e);
        }
    }
    setSourceToAdvisoryBoard();
  ]]>
</MACRO>

<MACRO name="Set Source to Editorial Board" lang="JScript">
  <![CDATA[
    function setSourceToEditorialBoard() {
        try {
            var holdFlag = Selection.ReadOnlyContainer;
            Selection.ReadOnlyContainer = false;
            var sel = ActiveDocument.Range;
            var count = setRevMarkupAttrs(sel, "Source", "editorial-board");
            Selection.ReadOnlyContainer = holdFlag;
            var message = "Set Source to 'editorial-board' for " + count
                        + " element";
            if (count != 1)
                message += "s";
            message += ".";
            Application.Alert(message);
        }
        catch (e) {
            Application.Alert(e);
        }
    }
    setSourceToEditorialBoard();
  ]]>
</MACRO>

<MACRO  name="CDR Browser Launch Test"
        lang="JScript"
        desc="Launch IE lots of times quickly"
        hide="false">
  <![CDATA[

    function launchTest() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "Admin.py?Session=" + CdrSession;
        for (var i = 0; i < 25; ++i)
            cdrObj.showPage(url);
    }
    launchTest();

  ]]>
</MACRO>

<MACRO  name="Translation Job" lang="JScript">
  <![CDATA[
    function translationJob() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var doc = Application.ActiveDocument;
        var docId = "";
        var translationOf = getSingleElement(doc, "TranslationOf");
        if (translationOf)
            docId = translationOf.getAttribute("cdr:ref");
        else
            docId = getDocId();
        if (!docId) {
            Application.Alert("Summary has not yet been saved.");
            return;
        }
        if (docId.length != 13 || docId.substr(0, 3) != "CDR") {
            Application.Alert("Malformed document ID: " + docId);
            return;
        }
        docId = parseInt(docId.substr(4), 10);
        var url = CdrCgiBin + "translation-job.py?Session=" + CdrSession
                            + "&english_id=" + docId;
        cdrObj.showPage(url);
    }
    translationJob();
  ]]>
</MACRO>

<MACRO  name="Translation Job Queue" lang="JScript">
  <![CDATA[
    function translationJobQueue() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "translation-jobs.py?Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    translationJobQueue();
  ]]>
</MACRO>

<MACRO  name="Translation Job Workflow Report" lang="JScript">
  <![CDATA[
    function translationJobWorkflowReport() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "translation-job-report.py?Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    translationJobWorkflowReport();
  ]]>
</MACRO>

<MACRO  name="Media Translation Job" lang="JScript">
  <![CDATA[
    function mediaTranslationJob() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var doc = Application.ActiveDocument;
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Media document has not yet been saved.");
            return;
        }
        if (docId.length != 13 || docId.substr(0, 3) != "CDR") {
            Application.Alert("Malformed document ID: " + docId);
            return;
        }
        docId = parseInt(docId.substr(4), 10);
        var url = CdrCgiBin + "media-translation-job.py?Session=" + CdrSession
                            + "&english_id=" + docId;
        cdrObj.showPage(url);
    }
    mediaTranslationJob();
  ]]>
</MACRO>

<MACRO  name="Media Translation Job Queue" lang="JScript">
  <![CDATA[
    function mediaTranslationJobQueue() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "media-translation-jobs.py?Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    mediaTranslationJobQueue();
  ]]>
</MACRO>

<MACRO  name="Media Translation Job Workflow Report" lang="JScript">
  <![CDATA[
    function mediaTranslationJobWorkflowReport() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "media-translation-job-report.py?Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    mediaTranslationJobWorkflowReport();
  ]]>
</MACRO>

<MACRO  name="Glossary Translation Job" lang="JScript">
  <![CDATA[
    function glossaryTranslationJob() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var doc = Application.ActiveDocument;
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Glossary document has not yet been saved.");
            return;
        }
        if (docId.length != 13 || docId.substr(0, 3) != "CDR") {
            Application.Alert("Malformed document ID: " + docId);
            return;
        }
        docId = parseInt(docId.substr(4), 10);
        var url = CdrCgiBin + "glossary-translation-job.py?Session="
                            + CdrSession
                            + "&doc_id=" + docId;
        cdrObj.showPage(url);
    }
    glossaryTranslationJob();
  ]]>
</MACRO>

<MACRO  name="Glossary Translation Job Queue" lang="JScript">
  <![CDATA[
    function glossaryTranslationJobQueue() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "glossary-translation-jobs.py?Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    glossaryTranslationJobQueue();
  ]]>
</MACRO>

<MACRO  name="Glossary Translation Job Workflow Report" lang="JScript">
  <![CDATA[
    function glossaryTranslationJobWorkflowReport() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "glossary-translation-job-report.py?Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    glossaryTranslationJobWorkflowReport();
  ]]>
</MACRO>

<MACRO  name="Count Characters" lang="JScript">
  <![CDATA[
    function count_characters_in_selection() {
        if (!cdrObj) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var n = cdrObj.selectionCharacterCount;
        Application.Alert("Selection contains " + n + " characters.");
    }
    count_characters_in_selection();
  ]]>
</MACRO>

</MACROS>
