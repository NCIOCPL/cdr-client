<?xml version="1.0"?>

<!-- 
     $Id: Cdr.mcr,v 1.85 2002-10-10 16:34:18 bkline Exp $

     $Log: not supported by cvs2svn $
     Revision 1.84  2002/10/09 14:11:54  bkline
     Lifted read-only block for PUP.

     Revision 1.83  2002/10/07 11:45:17  bkline
     Eliminated more dead code.

     Revision 1.82  2002/09/26 15:30:51  bkline
     Eliminated dead code.

     Revision 1.81  2002/09/24 20:41:32  bkline
     Added Mailer toolbar/macro.

     Revision 1.80  2002/09/24 15:30:47  bkline
     Plugged in toolbar buttons for new macros.

     Revision 1.79  2002/09/23 20:17:21  bkline
     Added macro to move to next lead org block.

     Revision 1.78  2002/09/23 20:10:20  bkline
     Added macro to insert participating org.

     Revision 1.77  2002/09/23 19:58:25  bkline
     Added new org status change macro to popup menu.

     Revision 1.76  2002/09/23 19:51:21  bkline
     Added Change Participating Org Status macro.

     Revision 1.75  2002/08/27 18:45:56  bkline
     Added patient publish preview.  Moved publish preview commands from menus
     and from general CDR toolbar to protocol and summary toolbars.  Changed
     patient publish preview icon at Eileen's request.  Added comment explaining
     why readonly settings are not imposed on linking elements.

     Revision 1.74  2002/08/22 13:12:21  bkline
     Turned on Publish Preview.

     Revision 1.73  2002/07/26 16:29:09  bkline
     Removed DatedAction from Insert ProtocolAmendmentInformation (Issue #346).

     Revision 1.72  2002/07/26 16:20:01  bkline
     Removed dead code.  Added code to disable CDR Save macro for readonly
     documents.  Disabled extra On_Update_UI macro.  Added hotkey for CDR
     Save.

     Revision 1.71  2002/07/19 22:07:14  bkline
     Replaced buggy SoftQuad code for Accept/Reject Change macros.  Added
     hotkey for macro to insert current date.

     Revision 1.70  2002/07/17 13:55:19  bkline
     Fixed Move Next/Prev macros.

     Revision 1.69  2002/07/15 22:39:22  bkline
     Switched to Normal view before saving.

     Revision 1.68  2002/07/02 20:47:02  bkline
     Fixed icon number for doc version history report button.

     Revision 1.67  2002/07/02 19:52:06  bkline
     Added document history report macro.

     Revision 1.66  2002/06/26 21:48:37  bkline
     Modified Insertion macro to implement simpler logic as requested by users.

     Revision 1.65  2002/06/13 21:50:22  bkline
     Fixed Insert DateLastModified macro.

     Revision 1.64  2002/06/13 19:01:16  bkline
     Replaced hardcoded host name with COM property.

     Revision 1.63  2002/06/11 13:33:11  bkline
     Moved new NHL Text button.

     Revision 1.62  2002/06/11 13:26:30  bkline
     Plugged in new icon for NHL Text Macro button.

     Revision 1.61  2002/06/07 20:48:41  bkline
     Added NHL macro and button; replace some Filter.py URLs with QcReport.py.

     Revision 1.60  2002/06/06 14:57:37  bkline
     Unplugged Undo macro; added Bold/Underline QC report.

     Revision 1.59  2002/06/03 20:22:43  bkline
     Fixed CitationLink macro button; plugged in help index.

     Revision 1.58  2002/05/31 13:00:45  bkline
     Added published version report button and stub macro.

     Revision 1.57  2002/05/20 15:41:00  bkline
     Replaced SoftQuad macros for inserting lists with code that works all
     the time.  New macros and buttons for inserting various elements.

     Revision 1.56  2002/05/16 02:51:28  bkline
     Added macro for inserting protocol amendment elements.

     Revision 1.55  2002/05/13 19:49:07  bkline
     Removed value from StatusName element when adding new org status for
     protocol.

     Revision 1.54  2002/05/11 03:01:05  bkline
     Implemented several newly requested enhancements.

     Revision 1.53  2002/05/08 20:28:19  bkline
     Removed HTML Summary button.

     Revision 1.52  2002/05/08 20:04:38  bkline
     Renamed filters; rearranged buttons on Protocol toolbar.

     Revision 1.51  2002/05/06 18:55:28  bkline
     Turned on redline/strikeout report.

     Revision 1.50  2002/04/26 23:08:32  bkline
     Added MiscellaneousDocument toolbar.

     Revision 1.49  2002/04/24 23:53:00  bkline
     Replaced stub for Generate Mailers macro.

     Revision 1.48  2002/04/24 21:18:04  bkline
     Replaced some stubs for Protocol and Organization toolbar buttons.

     Revision 1.47  2002/04/24 19:57:14  bkline
     Plugged in Terminology hierarchy view.

     Revision 1.46  2002/04/24 17:40:28  bkline
     Plugged in filters for Protocol Admin QC Report.

     Revision 1.45  2002/04/22 13:42:18  bkline
     Shifted QC macros to the right buttons.  Brought toolbar code in line
     with Eileen's Access tables.

     Revision 1.44  2002/04/20 02:44:05  bkline
     Added readonly protection for selected Mailer document elements.

     Revision 1.43  2002/04/15 02:37:41  bkline
     Added code to switch from text-only view when validating.

     Revision 1.42  2002/04/12 01:34:09  bkline
     Replaced stub for QC button.

     Revision 1.41  2002/04/05 14:15:05  bkline
     Added toolbar button for Checked Out Docs report.

     Revision 1.40  2002/04/05 14:05:38  bkline
     Added separator to Person toolbar between first and second buttons.

     Revision 1.39  2002/04/03 20:44:51  bkline
     Plugged in the filters for the Summary Markup report.

     Revision 1.38  2002/03/26 21:48:06  bkline
     Replaced hardwired filter number with filter name for Summary revision
     markup.

     Revision 1.37  2002/03/21 13:20:10  bkline
     Added summary macros.

     Revision 1.36  2002/03/07 22:29:55  bkline
     Added macros for PatientCharacteristics and PriorConcurrentTherapy.

     Revision 1.35  2002/03/07 20:49:34  bkline
     Fixed icon for CDR Markup/View Original menu item.

     Revision 1.34  2002/03/02 14:08:40  bkline
     Added macro for report of checked-out documents.

     Revision 1.33  2002/03/01 21:29:38  bkline
     Adjusted CdrEdit function to remove XMetaL PIs earlier.

     Revision 1.32  2002/02/26 21:38:18  bkline
     Fixed bug in RevisionLevel default setting.

     Revision 1.31  2002/02/21 22:33:12  bkline
     Switched icons for Find Next and Find Previous macros.

     Revision 1.30  2002/02/21 22:28:56  bkline
     Changed RevisionLevel attribute default from proposed to approved.

     Revision 1.29  2002/02/21 02:24:07  bkline
     Added code to modify the standard toolbars.

     Revision 1.28  2002/02/20 18:32:27  bkline
     Added new toolbar buttons for Find Next Change, Accept Change, and
     Reject Change.

     Revision 1.27  2002/02/20 04:12:21  bkline
     Removed Get Org Address from main CDR toolbar.

     Revision 1.26  2002/02/19 23:15:41  bkline
     Enabled code to pull down Org postal address into person document.

     Revision 1.25  2002/02/19 13:36:01  bkline
     Disabled code to move to newly inserted table's Title element.  Fixed
     typo in macro name Show Original.

     Revision 1.24  2002/02/14 19:29:54  bkline
     Made macro for getting person address conditional on popup menu.
     Commented out macro for getting org address.

     Revision 1.23  2002/02/14 00:56:15  bkline
     Removed dialog box display from save function.

     Revision 1.22  2002/02/14 00:54:18  bkline
     Added Publish Preview macro.  Changed Advanced Search macro to invoke
     the URL directly, rather than having this done in the DLL.

     Revision 1.21  2002/02/12 20:12:50  bkline
     Added remaining toolbars.  Renamed doctype-specific toolbars.
     Added stubs for missing toolbar macros.

     Revision 1.20  2002/02/08 15:07:16  bkline
     Fixed protocol tag names in attempt to keep up with schema changes.

     Revision 1.19  2002/02/05 23:00:50  bkline
     Aligned Insert User ID command with Eileen's requirements.

     Revision 1.18  2002/02/05 18:52:52  bkline
     Added toolbar macro and hotkey for Insert User Name.

     Revision 1.17  2002/02/05 14:38:46  bkline
     Hooked in Org status change to context menu.

     Revision 1.16  2002/02/05 14:19:53  bkline
     Added New Current Org Status macro for protocols.

     Revision 1.15  2002/02/02 18:57:45  bkline
     Hooked in Insert Current Date macro to toolbar.

     Revision 1.14  2002/01/31 14:21:35  bkline
     Added enumerated valid values for RevisionLevel attribute.

     Revision 1.13  2002/01/31 13:51:36  bkline
     Issue #63: moved cursor to end of enumerated value instead of beginning.

     Revision 1.12  2002/01/23 19:02:41  bkline
     Added hotkey (Ctrl+Enter) for cdr field editing.

     Revision 1.11  2001/12/19 14:10:05  bkline
     Added macros for publish preview, jump before/after element, etc.

     Revision 1.10  2001/10/25 02:30:06  bkline
     Moved all custom menu and toolbar building into the macro file.

     Revision 1.9  2001/10/23 21:46:34  bkline
     Added code to remove XMetaL placeholder processing instructions.
     Folded in macros from Eileen.

     Revision 1.8  2001/10/23 13:55:01  bkline
     Added Insert Current Date macro.

     Revision 1.7  2001/10/23 13:47:52  bkline
     Added new macros:
        Insert Lead Org
        CDR Get OrgAddress
        CDR Persons Linking to Org Address Fragment
        CDR Terminology Hierarchy Display
        CDR Terminology Usage Report
        CDR Copy Fragment Link
        CDR Paste Fragment Link

     Revision 1.6  2001/09/20 14:44:40  bkline
     Snapshot before switch to new workstation. (Bob)
     Added macros for toolbar separator, itemized list, ordered list, and
     stubs. (Eileen)

     Revision 1.5  2001/08/27 19:09:43  bkline
     Added "CDR Advanced Search" macro.

     Revision 1.4  2001/08/17 14:27:03  bkline
     Added test for HTML data entry form; added Insertion/Deletion macros.

     Revision 1.3  2001/06/12 02:21:44  bkline
     Added code to check readonly status for entire document.

     Revision 1.2  2001/06/11 21:19:40  bkline
     Added call to isReadOnly().

     Revision 1.1  2000/10/17  14:46:55  bobk
     Initial revision
 
  -->

<!DOCTYPE MACROS SYSTEM "macros.dtd">
<MACROS> 

<MACRO  name="On_Macro_File_Load" 
        lang="JScript">
  <![CDATA[

    //------------------------------------------------------------------
    // GLOBAL VARIABLES
    //------------------------------------------------------------------
    var CdrWebServer = "http://mmdb2.nci.nih.gov";
    var CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
    
    //"Summary", "Person", "Organization",
    //                             "InScopeProtocol", "Term",
    //                             "Citation", "GlossaryTerm");

    // To be overridden by successful logon.
    var CdrUserName = "";
    var CdrSession  = "";
    try {
        if (cdrObj) {
            CdrUserName  = cdrObj.username;
            CdrSession   = cdrObj.session;
            if (cdrObj.hostname) {
                CdrWebServer = "http://" + cdrObj.hostname;
                CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
            }
        }
    }
    catch (ignoreMe) {}


    // Clipboard for CDR links.
    var CdrDocLinkClipboard = "";
    var CdrFragLinkClipboard = "";

    function padNumber(number, length, padChar) {
        var str = '' + number;
        while (str.length < length)
            str = padChar + str;
        return str;
    }
    
    /*
     * Extracts the document ID from the current document.
     */
    function getDocId() {
        if (!Application.ActiveDocument) { return null; }
        var nodes = Application.ActiveDocument.getElementsByTagName("DocId");
        if (nodes.length < 1) { return null; }
        var elem = nodes.item(0);
        var val  = getTextContent(elem);
        if (val.length < 1) { return null; }
        return val;
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
            if (cdrObj.hostname) {
                CdrWebServer = "http://" + cdrObj.hostname;
                CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
            }
            //Application.Alert("User Name is " + CdrUserName);
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
        if (ActiveDocument.doctype.name == "Mailer") {
            var elName = Selection.ContainerNode.nodeName;
            if (elName == "Received" ||
                elName == "ChangesCategory" ||
                elName == "Response" ||
                elName == "Comment")
                return 0;
            return 1;
        }
        /*
         * XXX We cannot use the rest of this function to block
         *     editing of linking elements without disabling the
         *     feature of inserting a new occurrence of a repeating
         *     element by pressing the Enter key.  Lakshmi has
         *     agreed that it is preferable to keep the latter
         *     feature.
         */
        // return 0;
        if (cdrObj == null)                           { return 0; }
        if (Selection == null)                        { return 0; }
        if (Selection.ContainerNode == null)          { return 0; }
        if (Selection.ContainerNode.nodeName == null) { return 0; }
        if (ActiveDocument.doctype == null)           { return 0; }
        var dtName = ActiveDocument.doctype.name;
        var elName = Selection.ContainerNode.nodeName;
        //Application.Alert("dtName=" + dtName + " elName=" + elName);
        return cdrObj.isReadOnly(dtName, elName);
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
            var xmPath   = Application.Path;
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
    
    /*
     * Allows the user to pick a protocol update person.
     */
    function protUpdPerson() {
        if (cdrDocReadOnly()) {
            Application.Alert("Document retrieved as read-only.");
        }
        else if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {

            // Prevent On_Update_UI macro from blocking our editing.
            var whatItWas = Selection.ReadOnlyContainer;
            Selection.ReadOnlyContainer = false;
            gEditingCdrLink = true;
            var rc  = cdrObj.protUpdPerson();
            gEditingCdrLink = false;
            Selection.ReadOnlyContainer = whatItWas;
        }
    }
  
    function getMarkupStyle(element) {
        var docProps = ActiveDocument.CustomDocumentProperties;
        var highlighting = docProps.item("Highlighting").value;
        var style = "color:black;background-color:white";
        if (highlighting == "True") {
            if (element == "Insertion") {
                style =  "color:red;background-color:white";
            }
            else if (element == "Deletion") {
                style = "color:red;background-color:white;" +
                        "text-decoration:line-through";
            }
        }
        return (style);
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
        Application.Alert("*** WARNING ***\n" +
                          "This service is still under development.\n" +
                          "Formatting and content may be significantly\n" +
                          "different in final version of software.");
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
        Application.ShowPage(url);
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
        }
    }

    if (ActiveDocument == null
    ||  ActiveDocument.documentElement == null
    ||  ActiveDocument.documentElement.getAttribute("readonly") == "yes")
        Application.DisableMacro("Cdr Save");


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

        // Add the Deletion element.
        docType.addElement("Deletion", "Deletion", true , false);
        docType.addAttribute("Deletion", "UserName", "", 0, 0);
        docType.addAttribute("Deletion", "Time", "", 0, 0);
        docType.addEnumeratedAttribute("Deletion", "RevisionLevel",
            "Indicates status of proposed deletion", 9, // ordinary enumeration
            2, // default value is explicity specified
            "approved", "approved", "proposed", "publish", "rejected");

        // Add the Insertion element.
        docType.addElement("Insertion", "Insertion", true , false);
        docType.addAttribute("Insertion", "UserName", "", 0, 0);
        docType.addAttribute("Insertion", "Time", "", 0, 0);
        docType.addEnumeratedAttribute("Insertion", "RevisionLevel",
            "Indicates status of proposed insertion", 9, // ordinary enumeration
            2, // default value is explicity specified
            "approved", "approved", "proposed", "publish", "rejected");

        // Allow these elements anywhere.
        if (docType.hasElementType(rootElem)) {
            if (docType.hasElementType("Deletion")) {
                docType.addElementToInclusions("Deletion", rootElem);
            }
            if (docType.hasElementType("Insertion")) {
                docType.addElementToInclusions("Insertion", rootElem);
            }
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
    Selection.GotoNext(0);
    Selection.GotoNext(0);
    Selection.SelectContainerContents();
    var docProps = ActiveDocument.CustomDocumentProperties;
    docProps.Add("Highlighting", true);
    docProps.Add("ShowOriginal", false);
    docProps.Add("InsNextPrev", false);
    docProps.Add("DelNextPrev", false);
    Application.Run("Init_JScript_Macros");
    //Application.Alert("leaving On_Document_Open_Complete");
]]>
</MACRO>

<MACRO  name="On_Context_Menu" 
        lang="JScript">
  <![CDATA[
 
    /*
     * Adds a menu option to the popup context menu for custom editing
     * of a link element.
     */
    var docType = ActiveDocument.doctype;
    Application.AppendMacro("-", "");
    Application.AppendMacro("&Edit Element", "Cdr Edit");
    Application.AppendMacro("Copy Document Link", "Cdr Copy Document Link");
    Application.AppendMacro("Copy Fragment Link", "Cdr Copy Fragment Link");
    Application.AppendMacro("Paste Document Link", "Cdr Paste Document Link");
    Application.AppendMacro("Paste Fragment Link", "Cdr Paste Fragment Link");
    if (docType.name == "InScopeProtocol") {
        Application.AppendMacro("-", "");
        Application.AppendMacro("Insert Lead Org", "Insert Lead Org");
        Application.AppendMacro("Prot Update Person", "Protocol Update Person");
        Application.AppendMacro("New Current Org Status", 
                                "New Current Org Status");
        Application.AppendMacro("Add Participating Orgs", 
                                "CDR Participating Orgs");
        Application.AppendMacro("Retrieve Person Address", 
                                "CDR Get Person Address");
        var rng = ActiveDocument.Range;
        if (rng.IsParentElement("ProtocolLeadOrg"))
            Application.AppendMacro("Change Org Statuses",
                    "Change Participating Org Status");
    }
    if (docType.name == "Person") {
        Application.AppendMacro("Retrieve Org Postal Address", 
                                "CDR Get Org Postal Address");
    }
    if (docType.name == "Organization") {
        if (Selection.IsParentElement("Location")) {
            Application.AppendMacro("Persons Linking to This Location",
                "CDR Persons Linking to Org Address Fragment");
        }
    }
   
  ]]>
</MACRO>

<MACRO  name="On_Default_CommandBars_Complete" 
        key="" 
        lang="JScript">
  <![CDATA[

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
            new CdrCmdItem("Find &Previous Change",
                           "Find Prev",
                           "Find Previous Change",
                           "Find previous markup change",
                           "CDR", 1, 9,
                           false),
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
            new CdrCmdItem("Re&ject All Changes",
                           "Reject Changes",
                           "Reject All Changes",
                           "Reject all markup changes",
                           "CDR", 2, 9,
                           false),
            new CdrCmdItem("Vie&w Changes With Highlighting",
                           "Show Changes With Highlighting",
                           "View Changes With Highlighting",
                           "View markup changes with highlighting",
                           "CDR", 2, 1,
                           true),
            new CdrCmdItem("View Changes With&out Highlighting",
                           "Show Changes Without Highlighting",
                           "View Changes Without Highlighting",
                           "View markup changes without highlighting",
                           "CDR", 2, 2,
                           false),
            new CdrCmdItem("&View Original",
                           "Show Original",
                           "View Original",
                           "View document before markup",
                           "CDR", 2, 10,
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
            /*
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            */
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
            new CdrCmdItem(null,
                           "Jump Before Element",
                           "Jump Before Element",
                           "Position cursor in front of current element's" +
                           " start tag",
                           "CDR", 6, 3,
                           true),
            new CdrCmdItem(null,
                           "Jump Past Element",
                           "Jump Past Element",
                           "Position cursor beyond current element's" +
                           " start tag",
                           "CDR", 6, 4,
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
        */
        
        
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

    function addSummaryToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "New Summary Section",       // Macro.
                           "New Section",               // Tooltip.
                           "Insert new SummarySection", //Description
                           "General (Custom)", 5, 8,    // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Next Summary Section",
                           "Next Section",
                           "Move to next SummarySection",
                           "CDR", 4, 4,
                           true),
            new CdrCmdItem(null,
                           "Previous Summary Section",
                           "Previous Section",
                           "Move to previous SummarySection",
                           "CDR", 4, 5,
                           false),
            new CdrCmdItem(null,
                           "Higher Summary Section",
                           "Higher Section",
                           "Move to higher SummarySection",
                           "CDR", 4, 6,
                           false),
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
                           "Bold Underline",
                           "Bold Underline Report",
                           "CDR", 2, 3,
                           true),
            new CdrCmdItem(null,
                           "Redline Strikeout Report",
                           "Redline Strikeout",
                           "Redline Strikeout Report",
                           "CDR", 2, 4,
                           false),
            new CdrCmdItem(null,
                           "Published Version Report",
                           "Published Version",
                           "Published Version Report",
                           "CDR", 5, 1,
                           false),
            new CdrCmdItem(null,
                           "Patient Summary QC Report",
                           "Patient QC",
                           "Patient Summary QC Report",
                           "CDR", 3, 5,
                           false),
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Generate Mailer",
                           "Mailer",
                           "Generate Mailer",
                           "CDR", 5, 8,
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
                Application.Alert("Failure deleting old CDR Summary Toolbar: " + e);
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
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Summary toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Summary"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addPersonToolbar() {

        var buttons = new Array(
            /*
            new CdrCmdItem(null,                        // Label.
                           "Reset Contact Information", // Macro.
                           "Reset Contact",             // Tooltip.
                           "Reset Contact Information", // Description
                           "CDR", 4, 9,                 // Icon set, row, col.
                           true),                       // Starts new group?
            */
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "QC Report",
                           "Generate QC Report",
                           "CDR", 3, 4,
                           false),
            new CdrCmdItem(null,
                           "Generate Mailer",
                           "Mailer",
                           "Generate Mailer",
                           "CDR", 5, 8,
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
                Application.Alert("Failure deleting old CDR Person toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Person", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Person toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Person"] = cmdBar;
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
                           "Generate Mailer",
                           "Mailer",
                           "Generate Mailer",
                           "CDR", 5, 8,
                           false)
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
                Application.Alert("Failure deleting old CDR Organization toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Organization", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Organization toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Organization"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addProtocolToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Go To Admin Info Section",  // Macro.
                           "Admin Info",                // Tooltip.
                           "Go To Admin Info Section",  // Description
                           "General (Custom)", 7, 1,    // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Go To Scientific Info Section",
                           "Scientific Info",
                           "Go To Scientific Info Section",
                           "CDR", 6, 7,
                           false),
            new CdrCmdItem(null,
                           "Next Lead Org",
                           "Go To Next Lead Org",
                           "Go To Next Lead Org",
                           "CDR", 1, 4,
                           false),
            new CdrCmdItem(null,
                           "Insert PatientCharacteristics",
                           "Patient Characteristics",
                           "Patient Characteristics",
                           "CDR", 1, 2,
                           true),
            new CdrCmdItem(null,
                           "Insert PriorConcurrentTherapy",
                           "Prior Concurrent Therapy",
                           "Prior Concurrent Therapy",
                           "CDR", 1, 3,
                           false),
            new CdrCmdItem(null,
                           "NHL Text",
                           "NHL Text",
                           "NHL Text",
                           "CDR", 5, 7,
                           false),
            new CdrCmdItem(null,
                           "Insert ProtocolAmendmentInformation",
                           "Amendment",
                           "Insert ProtocolAmendmentInformation",
                           "CDR", 5, 4,
                           false),
            new CdrCmdItem(null,
                           "Insert Participating Org",
                           "Insert Participating Org",
                           "Insert Participating Org",
                           "CDR", 5, 6,
                           false),
            new CdrCmdItem(null,
                           "Protocol Merge",
                           "Merge",
                           "Protocol Merge",
                           "Integration (Custom)", 8, 4,
                           true),
            new CdrCmdItem(null,
                           "New Current Org Status",
                           "New Current Org Status",
                           "Change Organization Status",
                           "CDR", 6, 10,
                           false),
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "Full QC",
                           "Full QC Report",
                           "CDR", 4, 3,
                           true),
            new CdrCmdItem(null,
                           "Protocol HP QC Report",
                           "Health Professional QC",
                           "Health Professional QC Report",
                           "CDR", 3, 6,
                           false),
            new CdrCmdItem(null,
                           "Protocol Patient QC Report",
                           "Patient QC",
                           "Patient QC Report",
                           "CDR", 3, 5,
                           false),
            new CdrCmdItem(null,
                           "Protocol Admin QC Report",
                           "Administrative QC",
                           "Administrative QC Report",
                           "CDR", 3, 7,
                           false),
            new CdrCmdItem(null,
                           "Protocol Citations QC Report",
                           "Citations QC",
                           "Citations QC Report",
                           "CDR", 3, 8,
                           false),
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Patient Publish Preview",
                           "Patient Publish Preview",
                           "Patient Publish Preview",
                           "Structure (Custom)", 1, 9,
                           false),
            new CdrCmdItem(null,
                           "Generate Mailer",
                           "Mailer",
                           "Generate Mailer",
                           "CDR", 5, 8,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Protocol"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old " + 
                    "CDR Protocol toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Protocol", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
        Application.Alert("Failure adding CDR Protocol toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["InScopeProtocol"] = cmdBar;
            toolbars["OutOfScopeProtocol"] = cmdBar;
            toolbars["ScientificProtocolInfo"] = cmdBar;
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
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Term toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Term"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addGlossaryToolbar() {

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
        
        try { cmdBar = cmdBars.item("CDR Glossary Term"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Glossary Term toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Glossary Term", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Glossary Term toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["GlossaryTerm"] = cmdBar;
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
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Citation toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Citation"] = cmdBar;
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
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Miscellaneous Document " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["MiscellaneousDocument"] = cmdBar;
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
                           "CDR", 5, 8,                 // Icon set, row, col.
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
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Mailer " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Mailer"] = cmdBar;
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
            if (toolbars[i])
                toolbars[i].Visible = false;
        }
    }

    function turnOffStandardToolbars() {
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("Standard"); }
        catch (e) { }
        if (cmdBar) {
            cmdBar.Visible = false;
        }
        cmdBar = null;
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

    /*
     * This workaround is needed because, as Softquad admits, there is no way
     * for us to customize our installation in a way which installs the CDR
     * menu as part of a customized default.tbr.
     */
    var toolbars = new Array();
    addCdrToolbar();
    addSummaryToolbar();
    addPersonToolbar();
    addOrganizationToolbar();
    addProtocolToolbar();
    addTermToolbar();
    addGlossaryToolbar();
    addCitationToolbar();
    addMiscToolbar();
    addMailerToolbar();
    addCdrMenus();
    hideToolbars();
    // turnOffStandardToolbars(); Doesn't work here!!!  SoftQuad Bug!
    //bugRepro();

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
            cdrObj.validate();
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
        else
            cdrObj.save();
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

<MACRO  name="Protocol Update Person" 
        key="" 
        lang="JScript" 
        tooltip="Pick a protocol update person" >
  <![CDATA[
    protUpdPerson();
  ]]>
</MACRO>

<MACRO  name="Cdr Copy Document Link"
        key="" 
        lang="JScript" 
        tooltip="Copy Document Link to CDR Clipboard">
  <![CDATA[
    function copyDocumentLink() {
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("This is a new document without a document ID.");
        }
        CdrDocLinkClipboard = docId;
    }
    copyDocumentLink();
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

<MACRO  name="Cdr Paste Document Link"
        key="" 
        lang="JScript" 
        tooltip="Paste Document Link From CDR Clipboard">
 <![CDATA[
    function pasteDocumentLink() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        if (CdrDocLinkClipboard == "") {
            Application.Alert("CDR Document Link Clipboard is empty");
            return;
        }
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (!docType.hasAttribute(container.nodeName, "cdr:ref")) {
            Application.Alert("Current element cannot accept links.");
            return;
        }
        
        Selection.ReadOnlyContainer = false;
        gEditingCdrLink = true;
        cdrObj.pasteDocLink(CdrDocLinkClipboard);
        gEditingCdrLink = false;
        Selection.ReadOnlyContainer = true;
    }

    pasteDocumentLink();
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
        if (!docType.hasAttribute(container.nodeName, "cdr:ref")) {
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

<MACRO  name="Test Schema Validation" 
        lang="JScript" 
        key="Ctrl+Alt+Shift+V">
  <![CDATA[

    /*
     * Launches external schema validation app.  This is likely to be used
     * by Aspen for validation of temporary documents created with XMetaL
     * before the CDR system has gone into production.
     */
    function testSchemaValidation() {
        Application.ActiveDocument.Save();
        var WSHShell = new ActiveXObject("WScript.Shell");
        WSHShell.run("macros\\tValidate.cmd \"" + 
                     Application.ActiveDocument.FullName + "\"", 1, 1);
    }
    testSchemaValidation();

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

<!--
<MACRO  name="On_Double_Click" 
        lang="JScript" 
        key="Ctrl+Shift+E">
  <![CDATA[
    cdrEdit();
  ]]>
</MACRO>
 -->

<!--
<MACRO  name="PersonNameInfo_OnInitialize" 
        hide="true" 
        lang="JScript">
<![CDATA[

    var ipeg = Application.ActiveInPlaceControl;
    var browser = ipeg.Control;
    var form    = Application.Path + "/Forms/PersonNameInfo.html";
    ipeg.Height = 200;
    ipeg.Width  = 580;
    browser.Navigate2(form, 2);

]]>
</MACRO>
-->

<MACRO name="xOn_Update_UI"
       lang="JScript"
       hide="true"
       id="144x">
         <![CDATA[
       
    function refreshStyles() {

        var docProps = ActiveDocument.CustomDocumentProperties;
        if (docProps.count == 0) return;
        if (docProps.item("Highlighting").value == "True") {
            var rng = ActiveDocument.Range;
            rng.MoveToDocumentStart();
            while(rng.MoveToElement("Insertion")) {
                rng.ContainerStyle = "color:red";
            }
            rng.MoveToDocumentStart();
            while (rng.MoveToElement("Deletion")) {
                rng.ContainerStyle = "color:red; text-decoration:line-through";
            }
            rng = null;
        }
    }

    // This causes too much flickering since On_Update_UI is called so 
    // frequently.  However without it, if you press <Enter> while in
    // an Insertion or Deletion, the styles aren't set correctly.
    if (ActiveDocument.IsXML &&
       (ActiveDocument.ViewType == sqViewNormal ||
        ActiveDocument.ViewType == sqViewTagsOn)) {
        refreshStyles();
    }

    // function to disable Version Control Macros
    function disableVCMacros() {


        var insList = ActiveDocument.getElementsByTagName("Insertion");
        var delList = ActiveDocument.getElementsByTagName("Deletion");

        // if no changes have been made disable some macros
        if (insList.length == 0 && delList.length == 0) {

            if (Selection.IsInsertionPoint) {
                Application.DisableMacro("Deletion");
            }
            else if (!Selection.CanSurround("Deletion")) {
                Application.DisableMacro("Deletion");
            }
            
            Application.DisableMacro("Accept Change");
            Application.DisableMacro("Reject Change");
            Application.DisableMacro("Reject Changes");
            Application.DisableMacro("Accept Changes");
            Application.DisableMacro("Accept or Reject Changes");
            Application.DisableMacro("Show Original");
            Application.DisableMacro("Find Prev");
            Application.DisableMacro("Find Next");
            Application.DisableMacro("Show Changes With Highlighting");
            Application.DisableMacro("Show Changes Without Highlighting");
        }
        else {

            if (Selection.ContainerNode) {
                if (!Selection.CanSurround("Deletion") ||
                    Selection.IsInsertionPoint ||
                    Selection.IsParentElement("Deletion")) {
                        Application.DisableMacro("Deletion");
                }
                if (!Selection.CanInsert("Insertion") ||
                    Selection.IsParentElement("Deletion") ||
                    Selection.IsParentElement("Insertion")) {
                        Application.DisableMacro("Insertion");
                }
        
                // if the current Selection is neither Insertion nor Deletion
                if (!Selection.isParentElement("Insertion") &&
                    !Selection.IsParentElement("Deletion")) {
                        Application.DisableMacro("Accept Change");
                        Application.DisableMacro("Reject Change");
                }
                
                var docProps = ActiveDocument.CustomDocumentProperties;
                var highlight;
                var showoriginal;
                if (docProps.count == 0) {
                    highlight = "True";
                    showoriginal = "False";
                }
                else {
                    highlight = docProps.item("Highlighting").value;
                    showoriginal = docProps.item("ShowOriginal").value;
                }
                if (highlight == "True") {
                    Application.DisableMacro("Show Changes With Highlighting");
                }
                else if (showoriginal == "True") {
                    Application.DisableMacro("Show Original");
                }
                else {
                    Application.DisableMacro(
                        "Show Changes Without Highlighting");
                }
            }
        }
        else {
            Application.DisableMacro("Insertion");
            Application.DisableMacro("Deletion");
            Application.DisableMacro("Accept Change");
            Application.DisableMacro("Reject Change");
            Application.DisableMacro("Reject Changes");
            Application.DisableMacro("Accept Changes");
            Application.DisableMacro("Accept or Reject Changes");
            Application.DisableMacro("Show Original");
            Application.DisableMacro("Find Prev");
            Application.DisableMacro("Find Next");
            Application.DisableMacro("Show Changes With Highlighting");
            Application.DisableMacro("Show Changes Without Highlighting");
        } 

        // Check if the view is Tags On and if so, adjust the selection 
        // out of the top-level
        if (Selection.IsInsertionPoint &&
            ActiveDocument.ViewType == sqViewTagsOn) {

            if (Selection.ContainerNode == null) {
                Selection.MoveRight();
            }
            if (Selection.ContainerNode == null) {
                Selection.MoveLeft();
            }
        }

        // Disable most macros if in Plain Text view or if the document is not XML
        if (!ActiveDocument.IsXML ||
            (ActiveDocument.ViewType != sqViewNormal &&
             ActiveDocument.ViewType != sqViewTagsOn)) {
                Application.DisableMacro("Insertion");
                Application.DisableMacro("Deletion");
                Application.DisableMacro("Accept Change");
                Application.DisableMacro("Reject Change");
                Application.DisableMacro("Reject Changes");
                Application.DisableMacro("Accept Changes");
                Application.DisableMacro("Accept or Reject Changes");
                Application.DisableMacro("Show Original");
                Application.DisableMacro("Find Prev");
                Application.DisableMacro("Find Next");
                Application.DisableMacro("Show Changes With Highlighting");
                Application.DisableMacro("Show Changes Without Highlighting");
        }
    }
  
    // Disable some macros if the view is Normal or Tags On
    if (ActiveDocument.ViewType == sqViewNormal ||
        ActiveDocument.ViewType == sqViewTagsOn) {

        // call function to disable Version Control Macros
        disableVCMacros();
    }

  ]]>
</MACRO>

<MACRO name="On_View_Change"
       lang="JScript">
         <![CDATA[

    // refreshes the Insertion and Deletion element container styles on 
    // view change fromplain text to Normal or Tags on
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
    //------------------------------------------------------------------
    function doDeletion()
    {
        var del = ActiveDocument.Range;
        var date = new Date();
        
        // If some text is selected:
        if (!del.IsInsertionPoint) {

            // If the selection is inside an Insertion element:
            if (Selection.isParentElement("Insertion")) {
                var del_txt = Selection.Text;

                // Delete it temporarily.
                Selection.Delete();

                // Split the container into two Insertion elements 
                Selection.SplitContainer();
                Selection.ContainerStyle = getMarkupStyle("Insertion");
                Selection.SelectBeforeContainer();
                if (!Selection.IsParentElement("Deletion")) {
                    if (Selection.CanInsert("Deletion")) {
                        Selection.InsertElement("Deletion");
                        Selection.ContainerAttribute("UserName") = CdrUserName;
                        Selection.ContainerAttribute("Time") = 
                            date.toLocaleString();
                        Selection.ContainerAttribute("RevisionLevel") = 
                            "approved";
                        Selection.ContainerStyle = getMarkupStyle("Deletion");
                        Selection.Text = del_txt;
                    }
                }
            }
            else if (!Selection.isParentElement("Deletion")) {
                if (Selection.CanSurround("Deletion")) {
                    Selection.Surround("Deletion");
                    Selection.ContainerStyle = getMarkupStyle("Deletion");
                    Selection.ContainerAttribute("UserName") = CdrUserName;
                    Selection.ContainerAttribute("Time") =
                                                    date.toLocaleString();
                    Selection.ContainerAttribute("RevisionLevel") = 
                        "approved";
                    var rng = ActiveDocument.Range;
                    rng.SelectContainerContents();
                    var start = rng.Duplicate;
                    start.Collapse(1);
                    var end = rng.Duplicate;
                    end.Collapse(0);
                    readtree(start, end);
                    //Application.Alert("Did it!");
                }
                else {
                    //Application.Alert("Can't do it!");
                }
            }
        }
        del = null;
    }

    function readtree(startRng, endRng) {

        // If the node represents an "Insertion" element, remove it
        while(true) {
            var tempRng = startRng.Duplicate;
            startRng.GoToNext(0);
            if (tempRng.isEqual(startRng)) {
                tempRng = null;
                break;
            }
            else {
                if (startRng.isLessThan(endRng)) {
                    if (startRng.ContainerNode) {
                        var element = startRng.ContainerNode.nodeName;
                        if (element == "Deletion") {
                            startRng.RemoveContainerTags();
                        }
                        else if (element == "Insertion") {
                            startRng.SelectContainerContents();
                            startRng.Delete();
                            startRng.RemoveContainerTags();
                        }
                        else {
                            startRng.ContainerStyle = getMarkupStyle("Deletion");
                            element = "";
                        }
                    }
                } else {
                    break;
                }
            }
        }
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
    //
    // XXX Lakshmi decided she doesn't want the fancier approach used by
    //     SoftQuad.
    //----------------------------------------------------------------------
    function getInsertion() {
        if (Selection.IsInsertionPoint) {
            doInsertion();  
        }
        else {
            if (Selection.CanSurround("Deletion")) {
                if (Selection.IsParentElement("Insertion")) {
                    var temp_text = Selection.Text;
                    Selection.Delete();
                    Selection.SplitContainer();
                    Selection.ContainerStyle = getMarkupStyle("Insertion");
                    Selection.SelectBeforeContainer();
                    if (Selection.CanInsert("Deletion")) {
                        Selection.InsertElement("Deletion");
                        Selection.ContainerStyle = getMarkupStyle("Deletion");
                        Selection.Text = temp_text;
                    }
                    Selection.MoveToElement("Insertion");
                }
                else {  
                    Selection.Surround("Deletion");
                    Selection.ContainerAttribute("UserName") = CdrUserName;
                    var date = new Date();
                    Selection.ContainerAttribute("Time") = 
                        date.toLocaleString();
                    Selection.ContainerAttribute("RevisionLevel") = "approved";
                    Selection.ContainerStyle = getMarkupStyle("Deletion");
                    Selection.SelectAfterContainer();
                    doInsertion();
                }
            }
        }
    }

    function doInsertion() {
        if (Selection.ContainerNode) {
            if (!Selection.isParentElement("Insertion")) {
                if (Selection.CanInsert("Insertion")) {
                    if (Selection.isParentElement("Deletion")) {
                        Selection.SplitContainer();
                        Selection.ContainerStyle = getMarkupStyle("Deletion");
                        Selection.SelectBeforeContainer();
                    }

                    // Insert "Insertion"
                    Selection.InsertElement("Insertion");
                    Selection.InsertReplaceableText("Insert text here");
                    Selection.ContainerAttribute("UserName") = CdrUserName;
                    var date = new Date();
                    Selection.ContainerAttribute("Time") = 
                        date.toLocaleString();
                    Selection.ContainerAttribute("RevisionLevel") = "approved";
                    Selection.ContainerStyle = getMarkupStyle("Insertion");
              
                    // Merge if the previous tag name and its user are the
                    // same as this 
                    if (Selection.ContainerNode) {
                        var prevSibling =
                            Selection.ContainerNode.previousSibling;
                        var nextSibling =
                            Selection.ContainerNode.nextSibling; 
                        if (prevSibling &&
                            prevSibling.nodeName == "Insertion") {
                                Selection.JoinElementToPreceding();
                        }
                        else if (nextSibling &&
                            nextSibling.nodeName == "Insertion") {
                                Selection.MoveToElement("Insertion");
                                Selection.JoinElementToPreceding();
                        }
                    }
                }
                else {
                    Application.Alert("Cannot insert 'Insertion' element " +
                                      "here.");
                }
            }
        }
    }

    // Replacement function for the above two.  Keep those in case the
    // users change their minds back.
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
        Selection.ContainerAttribute("RevisionLevel") = "approved";
        Selection.ContainerStyle = getMarkupStyle("Insertion");
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
        var r = Selection.Duplicate;
        r.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            r.SelectContainerContents();
            r.Delete();
            r.RemoveContainerTags();
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            r.SelectContainerContents();
            if (r.Text == "<?xm-replace_text Insert text here?>") {
                r.Delete();
            }
            r.RemoveContainerTags();
        }
    }

    if (CanRunMacros()) {
        var confirm =
            Application.Confirm("Do you want to merge all changes " +
                                "without reviewing them?");
        if (confirm) {
            mergeChanges();
        }
    }
    
  ]]>
</MACRO>
 
<MACRO  name="Accept or Reject Changes"
        lang="JScript"
        id="1904"
        key="Ctrl+Alt+A"
        desc="Accept or Reject Changes..."
        tooltip="Accept or Reject Changes... (Ctrl+Alt+A)">
  <![CDATA[
        
    //----------------------------------------------------------------------
    // Enables the Reviewers to Incorporates the changes from a dialog box.
    //----------------------------------------------------------------------
    function doAcceptOrReject() {
        var Accept, Reject, AcceptAll, RejectAll, Undo,
            FindPrev, FindNext, Insertion_list, Deletion_list;
        Accept = true;
        Reject = true;
        AcceptAll = true;
        RejectAll = true;
        Undo = false;
        FindPrev = true;
        FindNext = true;
        var AcceptOrReject_Dlg = CreateFormDlg(Application.Path + 
                "\\Cdr\\AcceptOrReject.hhf");
        var rng = ActiveDocument.Range;
        Insertion_list = ActiveDocument.getElementsByTagName("Insertion");
        Deletion_list = ActiveDocument.getElementsByTagName("Deletion");
        if (Insertion_list.length == 0 && Deletion_list.length == 0) {
            Accept = false;
            Reject = false;
            AcceptAll = false;
            RejectAll = false;
            Undo = false;
            FindPrev = false;
            FindNext = false;
        }
        else if (!Selection.IsParentElement("Insertion") &&
                 !Selection.IsParentElement("Deletion")) {
            Accept = false;
            Reject = false;
        }

        AcceptOrReject_Dlg.cmdAccept.Enabled = Accept;
        AcceptOrReject_Dlg.cmdReject.Enabled = Reject;
        AcceptOrReject_Dlg.cmdAcceptAll.Enabled = AcceptAll;
        AcceptOrReject_Dlg.cmdRejectAll.Enabled = RejectAll;
        AcceptOrReject_Dlg.cmdUndo.Enabled = Undo;
        AcceptOrReject_Dlg.cmdFindPrev.Enabled = FindPrev;
        AcceptOrReject_Dlg.cmdFindNext.Enabled = FindNext;

        var docProps = ActiveDocument.CustomDocumentProperties;
        if (docProps.item("Highlighting").value == "True") {
            AcceptOrReject_Dlg.opt_ChangesWH.Value = true;
        }
        else if (docProps.item("ShowOriginal").value == "True") {
            AcceptOrReject_Dlg.opt_Original.Value = true;
        }
        else {
            AcceptOrReject_Dlg.opt_ChangesWOH.Value = true;
        }
        if (Selection.ContainerNode.nodeName == "Insertion") {
            AcceptOrReject_Dlg.lblUser.Caption =
                Selection.ContainerAttribute("UserName");
            AcceptOrReject_Dlg.lblAction.Caption = "Insertion";
            AcceptOrReject_Dlg.lblTime.Caption =
                Selection.ContainerAttribute("Time");
        }
        else if (Selection.ContainerNode.nodeName == "Deletion") {
            AcceptOrReject_Dlg.lblUser.Caption =
                Selection.ContainerAttribute("UserName");
                AcceptOrReject_Dlg.lblAction.Caption = "Deletion";
                AcceptOrReject_Dlg.lblTime.Caption =
                    Selection.ContainerAttribute("Time");
        }

        AcceptOrReject_Dlg.DoModal();
    }

    if (CanRunMacros()) {
        doAcceptOrReject();
    }

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
    // XXX This SoftQuad is buggy.  Replace it!
    //----------------------------------------------------------------------
    function doAcceptChange()
    {
        if (Selection.isParentElement("Insertion")) {
            Selection.SelectContainerContents();
            if (Selection.Text == "<?xm-replace_text Insert text here?>") {
                Selection.Delete();
            }
            if (Selection.ElementName(0) != "Insertion") {
                if (Selection.MoveToElement("Insertion", false)) {
                    Selection.SelectContainerContents();
                    var containerContents = Selection.Text;
                    Selection.Delete();
                    Selection.RemoveContainerTags();
                    Selection.Text = containerContents;
                    containerContents = "";
                }
            }
            else {
                Selection.RemoveContainerTags();
            }
    
        }
        else if (Selection.isParentElement("Deletion")) {
            if (Selection.ElementName(0) == "Deletion") {
                Selection.SelectContainerContents();
                Selection.Delete();
                Selection.RemoveContainerTags();
            }
            else {
                while (Selection.isParentElement("Deletion")) {
                    Selection.MoveToElement("Deletion", false);
                    Selection.SelectContainerContents();
                    Selection.Delete();
                    Selection.RemoveContainerTags();
                }
            }
        }
    }

    // XXX This doesn't make sense.  How does rng_temp get set?
    function readtree(node, parent) {
    
        // If the node represents an "Insertion" element, remove it
        if (node.nodeName == "Deletion" && !parent) {
            rng_temp.MoveToElement("Deletion");
            rng_temp.ReadOnlyContainer = false;
            rng_temp.RemoveContainerTags();
            return;
        } 
        else if (node.hasChildNodes()) {
            var children = node.childNodes;
            for (var i=0; i<children.length; i++) {
                readtree(children.item(i), false);
            }
            return; 
        }
    }
    var rng_temp;

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

    if (CanRunMacros()) {
        //doAcceptChange();
        doAcceptChangeWithoutSoftQuadBugs();
    }
    
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
    // XXX This SoftQuad code is buggy.  Replace it.
    //----------------------------------------------------------------------
    function doRejectChange() {
        if (Selection.IsParentElement("Insertion")) {
            if (Selection.ElementName(0) != "Insertion") {
                Selection.MoveToElement("Insertion", false);
            }
            Selection.SelectContainerContents();
            Selection.Delete();
            Selection.RemoveContainerTags();
            return;
        } 
        else if (Selection.IsParentElement("Deletion")) {
            var rng_reject = ActiveDocument.Range;
            if (Selection.ElementName(0) != "Deletion") {
                rng_reject.MoveToElement("Deletion", false);
            }
            rng_reject.SelectContainerContents();
            start = rng_reject.Duplicate;
            start.Collapse(1);  // set the starting boundary for the search
            end = rng_reject.Duplicate;
            end.Collapse(0);  // set the ending boundary for the search
            rng_reject.RemoveContainerTags();
            rng_reject = readtree(start, end);
            rng_reject= null;
            return;
        }
    }


    function readtree(startRng, endRng) {
        while(true) {  // Move to next element
            var tempRng = startRng.Duplicate;
            startRng.GoToNext(0);
            if (tempRng.isEqual(startRng)) {
                tempRng = null;
                break;
            } 
            else {
                // if it is with in the range of the selected parent
                if (startRng.IsLessThan(endRng)) {
                    element = startRng.ContainerNode.nodeName;
                    startRng.ContainerStyle = getMarkupStyle(element);
                } 
                else {
                    break;
                }
            }
        }
        startRng = null;
        return(endRng);
    }

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

    if (CanRunMacros()) {
        //doRejectChange();
        doRejectChangeCorrectly();
    }

  ]]>
</MACRO>
 
<MACRO  name="Reject Changes" 
        key="" 
        lang="JScript" 
        id="1909" 
        desc="Deletes all marked changes">
  <![CDATA[

    //----------------------------------------------------------------------
    // Drop marked changes.
    //----------------------------------------------------------------------
    function doRejectAllChanges()
    {
        var r = ActiveDocument.Range;
        r.MoveToDocumentStart();
        Selection.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            Selection.MoveToElement("Deletion");
            //Selection.RemoveContainerTags();
            var rng = r.Duplicate;
            doRejectDelChange(r);
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            r.SelectContainerContents();
            r.Delete();
            r.RemoveContainerTags();
        }
        r = null;
    }


    function doRejectDelChange(rng_reject) {
        rng_reject.SelectContainerContents();
        start = rng_reject.Duplicate;
        start.Collapse(1);  // set the starting boundary for the search
        end = rng_reject.Duplicate;
        end.Collapse(0);  // set the ending boundary for the search
        rng_reject.RemoveContainerTags();
        rng_reject = readtree(start, end);
        rng_reject= null;
        return;
    }

    function readtree(startRng, endRng) {  

        while (true) {  

            // Move to next element
            var tempRng = startRng.Duplicate;
            startRng.GoToNext(0);
            if (tempRng.isEqual(startRng)) {
                tempRng = null;
                break;
            } 
            else {
                // if it is with in the range of the selected parent
                if (startRng.IsLessThan(endRng)) {
                    element = startRng.ContainerNode.nodeName;
                    startRng.ContainerStyle = getMarkupStyle(element);
                } 
                else {
                    break;
                }
            }
        }
        startRng = null;
        return(endRng);
    }

    if (CanRunMacros()) {
        var confirm = Application.Confirm("Do you want to reject all " +
                                          "changes without reviewing them?");
        if (confirm) {
            doRejectAllChanges();
        }
    }

  ]]>
</MACRO>
 
<MACRO  name="Show Original" 
        key="" 
        lang="JScript" 
        id="20207" 
        desc="Displays the document without any marked changes">
  <![CDATA[

    //----------------------------------------------------------------------
    // Displays the original document (i.e., without any tracked changes).
    //----------------------------------------------------------------------
    function doShowOriginal()
    {
        var docProps = ActiveDocument.CustomDocumentProperties;
        docProps.item("Highlighting").value = false;
        docProps.item("ShowOriginal").value = true;
        var r = ActiveDocument.Range;
        r.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            //    r.HiddenContainer = false;
            r.ContainerStyle = "";

            //r.ReadOnlyContainer = false;
            //r.ContainerAttribute("display") = "showNormal";
            //r.ReadOnlyContainer = true;
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            if (!r.HiddenContainer) {
                r.HiddenContainer = true;
            }
        }
        r = null;
    }

    if (CanRunMacros()) {
        doShowOriginal();
    }

  ]]>
</MACRO>

<MACRO  name="Show Changes With Highlighting" 
        key="" 
        lang="JScript" 
        id="1908" 
        desc="Displays all marked changes with highlighting">
  <![CDATA[

    //----------------------------------------------------------------------
    // Highlights all the marked changes by setting the container style of all 
    // Insertion and Deletion Elements
    //----------------------------------------------------------------------
    function doShowChangesWithHL() {
        var docProps = ActiveDocument.CustomDocumentProperties;
        docProps.item("Highlighting").value = true;
        docProps.item("ShowOriginal").value = false;
        var rng_HL = ActiveDocument.Range;
        rng_HL.MoveToDocumentStart();
        while (rng_HL.MoveToElement("Insertion")) {
            rng_HL.HiddenContainer = false;
            rng_HL.ContainerStyle = getMarkupStyle("Insertion");
            var rng2 = rng_HL.Duplicate;
            rng2.SelectElement();
            txt = rng2.ContainerStyle;
            rng2.ContainerStyle = txt;
            rng2 = null;
        }
        rng_HL.MoveToDocumentStart();
        while (rng_HL.MoveToElement("Deletion")) {
            rng_HL.SelectContainerContents();
            start = rng_HL.Duplicate;
            start.Collapse(1);  // set the starting boundary for the search
            end = rng_HL.Duplicate;
            end.Collapse(0);  // set the ending boundary for the search
            rng_HL.ContainerStyle = getMarkupStyle("Deletion");
            rng_HL = readtree(start, end);
        }
        rng_HL= null;
    }

    function readtree(startRng, endRng) {

        while (true) {  

            // Move to next element
            var tempRng = startRng.Duplicate;
            startRng.GoToNext(0);
            if (tempRng.isEqual(startRng)) {
                tempRng = null;
                break;
            } 
            else {  
                // if it is with in the range of the selected parent
                if (startRng.IsLessThan(endRng)) {
                    element = startRng.ContainerNode.nodeName;
                    element = "Deletion";
                    startRng.ContainerStyle = getMarkupStyle(element);
                } 
                else {
                    break;
                }
            }
        }
        startRng = null;
        return endRng;
    }

    // XXX This looks to be pretty buggy!
    var element;
    if (CanRunMacros()) {
        doShowChangesWithHL();
    }

  ]]>
</MACRO>

<MACRO  name="Show Changes Without Highlighting" 
        key="" 
        lang="JScript" 
        id="1907" 
        desc="Displays all marked changes without highlighting">
  <![CDATA[


    //----------------------------------------------------------------------
    // Displays the document with marked changes but without highlighting 
    //----------------------------------------------------------------------
    function doShowChangesWOH() {
        var docProps = ActiveDocument.CustomDocumentProperties;
        docProps.item("Highlighting").value = false;
        docProps.item("ShowOriginal").value = false;
        var rng_HL = ActiveDocument.Range;
        rng_HL.MoveToDocumentStart();
        while (rng_HL.MoveToElement("Insertion")) {
            rng_HL.HiddenContainer = false;
            rng_HL.ContainerStyle = getMarkupStyle("Insertion");
            rng2 = null;  // clean up
        }
        rng_HL.MoveToDocumentStart();
        while (rng_HL.MoveToElement("Deletion")) {
            rng_HL.SelectContainerContents();
            start = rng_HL.Duplicate;
            start.Collapse(1);  // set the starting boundary for the search
            end = rng_HL.Duplicate;
            end.Collapse(0);  // set the ending boundary for the search
            rng_HL.ContainerStyle = getMarkupStyle("Deletion");
            rng_HL = readtree(start, end);
        }
        rng_HL= null;
    }

    function readtree(startRng, endRng) {

        while (true) {

            // Move to next element
            var tempRng = startRng.Duplicate;
            startRng.GoToNext(0);
            if (tempRng.isEqual(startRng)) {
                tempRng = null;
                break;
            } 
            else {
                if (startRng.IsLessThan(endRng)) {  
                
                    // if it is with in the range of the selected parent
                    startRng.ContainerStyle = getMarkupStyle("Deletion");
                } 
                else {
                    break;
                }
            }
        }
        startRng = null;
        return endRng;
    }

    if (CanRunMacros()) {
        doShowChangesWOH();
    }

  ]]>
</MACRO>

<MACRO  name="Find Next" 
        key="" 
        lang="JScript" 
        id="1911" 
        desc="Moves the selection to the next marked change if any" 
        tooltip="Find Next Change">
  <![CDATA[


    //----------------------------------------------------------------------
    // Moves the selection to the next Marked change in the document
    // If the end of the document is reached the search is resumed from 
    // the beginning of the document 
    // XXX This is SoftQuad's code.  Very complicated and impressive,
    //     but it doesn't work.  Replaced below.
    //----------------------------------------------------------------------
    function doFindNext() {

        var docProps = ActiveDocument.CustomDocumentProperties;
        var parentName = "";
        if (Selection.ContainerNode) {
            parentName = Selection.ContainerNode.parentNode.nodeName;
        }
        if (docProps.item("InsNextPrev").value == "True") {
            if (Selection.ContainerNode) {
                if (parentName == "Insertion") {
                    Application.Run("Find Prev");
                }
                else {
                    docProps.item("InsNextPrev").value = false;
                    doFindNext();
                }
            }
            docProps.item("InsNextPrev").value = false;
        }
        else {
            if (docProps.item("DelNextPrev").value == "True") {
                if (Selection.ContainerNode) {
                    if (parentName == "Deletion") {
                        Application.Run("Find Prev");
                    }
                    else {
                        docProps.item("DelNextPrev").value = false;
                        doFindNext();
                    }
                }
                docProps.item("DelNextPrev").value = false;
            }
            else {
                var rng1 = ActiveDocument.Range;
                var rng2 = rng1.Duplicate;
            
                var Insertion = rng1.MoveToElement("Insertion");
                var Deletion = rng2.MoveToElement("Deletion");
                if (Insertion && Deletion) {
                    if (rng1.IsLessThan(rng2)) {
                        if (hasChildren(rng1.Duplicate, "Insertion")) {
                            Selection.MoveToElement("Insertion");
                            Selection.SelectAfterContainer();
                            docProps.item("InsNextPrev").value = true;
                            Application.Run("Find Prev");
                        }
                        else {
                            Selection.MoveToElement("Insertion");
                            Selection.SelectContainerContents();
                        }
                    }
                    else {
                        if (hasChildren(rng1.Duplicate, "Deletion")) {
                            Selection.MoveToElement("Deletion");
                            Selection.SelectAfterContainer();
                            docProps.item("DelNextPrev").value = true;
                            Application.Run("Find Prev");
                        }
                        else {
                            Selection.MoveToElement("Deletion");
                            Selection.SelectContainerContents();
                        }
                    }
                }
                else {
                    if (Insertion) {
                        if (hasChildren(rng1.Duplicate, "Insertion")) {
                            Selection.MoveToElement("Insertion");
                            Selection.SelectAfterContainer();
                            docProps.item("InsNextPrev").value = true;
                            Application.Run("Find Prev");
                        }
                        else {
                            Selection.MoveToElement("Insertion");
                            Selection.SelectContainerContents();
                        }
                    }
                    else {
                        if (Deletion) {
                            if (hasChildren(rng1.Duplicate, "Deletion")) {
                                Selection.MoveToElement("Deletion");
                                Selection.SelectAfterContainer();
                                docProps.item("DelNextPrev").value = true;
                                Application.Run("Find Prev");
                            }
                            else {
                                Selection.MoveToElement("Deletion");
                                Selection.SelectContainerContents();
                            }
                        }
                        else {
                            var ad = ActiveDocument;
                            var InsertionList = 
                                ad.getElementsByTagName("Insertion"); 
                            var DeletionList = 
                                ad.getElementsByTagName("Deletion"); 
                            if (InsertionList.length != 0 || 
                                DeletionList.length != 0) {
                                var search = Application.Confirm(
                                    "Reached the end of the Document.  " +
                                    "Do you want to continue searching " +
                                    "from the beginning of the document?");
                                if (search) {
                                    Selection.MoveToDocumentStart();
                                    var rng = ActiveDocument.Range;
                                    rng.MoveToDocumentStart();
                                    doFindNext();
                                }
                            }
                            else {
                                Application.Alert("Found no tracked changes");
                            }
                        }
                    }
                }
                rng1 = null;
                rng2 = null;
            }
        }
    }

    function hasChildren(rng_chld, elemName) {
        if (rng_chld.ContainerNode) {
            if (rng_chld.ContainerNode.hasChildNodes()) { 
                var children = rng_chld.ContainerNode.childNodes;
                for (var i=0; i < children.length; i++) {
                    if (children.item(i).nodeName == elemName) {
                        return true;
                    }
                }
                return false;
            }
            else {
                return false;
            }
        }
    }
  
    //----------------------------------------------------------------------
    // Rewritten to fix SoftQuad's buggy approach in response to CDR issue
    // report #330.
    //----------------------------------------------------------------------
    function findNextInsertionOrDeletion() {
        var delElem = ActiveDocument.Range;
        var insElem = ActiveDocument.Range;
        var keepGoing = true;
        while (keepGoing) {
            delElem.Collapse();
            insElem.Collapse();
            var foundDel = delElem.MoveToElement('Deletion', true);
            var foundIns = insElem.MoveToElement('Insertion', true);
            if (!foundDel && !foundIns) {
                keepGoing = Application.Confirm(
                    "Reached the end of the Document.  " +
                    "Do you want to continue searching " +
                    "from the beginning of the document?");
                if (keepGoing) {
                    delElem.MoveToDocumentStart();
                    insElem.MoveToDocumentStart();
                }
            }
            else {
                keepGoing = false;
                var whichRange = null;
                if (!foundDel)
                    whichRange = insElem;
                else if (!foundIns)
                    whichRange = delElem;
                else if (insElem.IsGreaterThan(delElem))
                    whichRange = delElem;
                else
                    whichRange = insElem;
                whichRange.SelectContainerContents();
                whichRange.Select();
            }
        }
    }

    if (CanRunMacros()) {
        //doFindNext();
        findNextInsertionOrDeletion();
    }

  ]]>
</MACRO>

<MACRO  name="Find Prev" 
        key="" 
        lang="JScript" 
        id="1910" 
        desc="Moves the selection to the previous marked change if any">
        <![CDATA[

    //----------------------------------------------------------------------
    // Moves the selection to the previous Marked change in the document
    // If the beginning of the document is reached the search is resumed 
    // from the end of the document 
    // XXX Buggy SoftQuad code.  See note on doFindNext() above.
    //----------------------------------------------------------------------
    function doFindPrev() {

        var rng1 = ActiveDocument.Range;
        var rng2 = rng1.Duplicate;

        var Insertion = rng1.MoveToElement("Insertion", false);
        var Deletion = rng2.MoveToElement("Deletion", false);
        if (Insertion && Deletion) {
            if (rng1.IsGreaterThan(rng2)) {
                Selection.MoveToElement("Insertion", false);
                Selection.SelectContainerContents();
            }
            else {
                Selection.MoveToElement("Deletion", false);
                Selection.SelectContainerContents();
            }
        } 
        else if (Insertion) {
            Selection.MoveToElement("Insertion", false);
            Selection.SelectContainerContents();
        } 
        else if (Deletion) {
            Selection.MoveToElement("Deletion", false);
            Selection.SelectContainerContents();
        } 
        else {
            var ad = ActiveDocument;
            var InsertionList = ad.getElementsByTagName("Insertion"); 
            var DeletionList = ad.getElementsByTagName("Deletion"); 
            if (InsertionList.length != 0 || DeletionList.length != 0) {
                var search = Application.Confirm(
                    "Reached the beginning of the Document.  " +
                    "Do you want to continue searching from the " +
                    "end of the document?");
                if (search) {
                    Selection.MoveToDocumentEnd();
                    doFindPrev();
                }
            }
            else {
                Application.Alert("Found no tracked changes");
            }
        }
        rng1 = null;
        rng2 = null;
    }

    //----------------------------------------------------------------------
    // Rewritten to fix SoftQuad's buggy approach in response to CDR issue
    // report #330.
    //----------------------------------------------------------------------
    function findPrevInsertionOrDeletion() {
        var delElem = ActiveDocument.Range;
        var insElem = ActiveDocument.Range;
        var keepGoing = true;
        while (keepGoing) {
            //delElem.Collapse();
            //insElem.Collapse();
            var foundDel = delElem.MoveToElement('Deletion', false);
            var foundIns = insElem.MoveToElement('Insertion', false);
            if (!foundDel && !foundIns) {
                keepGoing = Application.Confirm(
                    "Reached the beginning of the Document.  " +
                    "Do you want to continue searching " +
                    "from the end of the document?");
                if (keepGoing) {
                    delElem.MoveToDocumentEnd();
                    insElem.MoveToDocumentEnd();
                }
            }
            else {
                keepGoing = false;
                var whichRange = null;
                if (!foundDel)
                    whichRange = insElem;
                else if (!foundIns)
                    whichRange = delElem;
                else if (insElem.IsGreaterThan(delElem))
                    whichRange = insElem;
                else
                    whichRange = delElem;
                whichRange.SelectContainerContents();
                whichRange.Select();
            }
        }
    }

    if (CanRunMacros()) {
        //doFindPrev();
        findPrevInsertionOrDeletion();
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
        Application.ShowPage(url);
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
        Application.ShowPage(url);
    }
    checkedOutDocs();

  ]]>
</MACRO>

<MACRO name="Published Version Report" 
       lang="JScript">
  <![CDATA[
    Application.Alert("This report depends on the Publish Preview interface" +
                      "\nwith Cancer.Gov, which is still under development");
  ]]>
</MACRO>

<MACRO name="Publish Preview" 
       lang="JScript">
  <![CDATA[
    publishPreview("");
  ]]>
</MACRO>

<MACRO name="Patient Publish Preview" 
       lang="JScript">
  <![CDATA[
    publishPreview("protocol_patient");
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

<MACRO  name="CDR Get Person Address"
        lang="JScript" 
        desc="Retrieve address from fragment link"
        hide="false">
  <![CDATA[

    if (cdrObj == null) {
        Application.Alert("You are not logged on to the CDR");
    }
    else {
        cdrObj.getPersonAddress();
    }

  ]]>
</MACRO>

<MACRO  name="CDR Participating Orgs"
        lang="JScript" 
        desc="Select Participating Organizations for Protocol"
        hide="false">
  <![CDATA[

    if (cdrObj == null) {
        Application.Alert("You are not logged on to the CDR");
    }
    else {
        cdrObj.particOrgs();
    }

  ]]>
</MACRO>

<MACRO  name="Insert Lead Org"
        lang="JScript" 
        desc="Insert new Protocol lead organization"
        hide="false">
  <![CDATA[

    if (!insertAnother("ProtocolAdminInfo", "ProtocolLeadOrg",
        "<ProtocolLeadOrg>" +
        "<LeadOrganizationID>Select Organization Here</LeadOrganizationID>" +
        "<LeadOrgRole/>" +
        "<LeadOrgProtocolID/>" +
        "<LeadOrgProtocolStatuses>" +
        "<CurrentOrgStatus>" +
        "<StatusName/>" +
        "<StatusDate/><EnteredBy/><EntryDate/>" +
        "</CurrentOrgStatus>" +
        "</LeadOrgProtocolStatuses>" +
        "<LeadOrgPersonnel>" +
        "<Person cdr:ref=''>Person Name Here</Person>" +
        "<PersonRole/>" +
        "</LeadOrgPersonnel>" +
        "</ProtocolLeadOrg>")) {
        Application.Alert("Unable to insert ProtocolLeadOrg");
    }
  ]]>
</MACRO>

<MACRO  name="Insert Participating Org"
        lang="JScript" 
        key="Ctrl+Alt+Z" 
        desc="Insert new Protocol participating organization"
        hide="false">
  <![CDATA[
    function insertParticipatingOrg() {
        var rng = ActiveDocument.Range;
        if (!rng.FindInsertLocation("OrgSite", true)) {
            if (!rng.FindInsertLocation("OrgSite", false)) {
                Application.Alert("Can't insert OrgSite element");
                return; 
            }
        }
        rng.InsertWithTemplate("OrgSite");
        rng.Select();
    }
    insertParticipatingOrg();
  ]]>
</MACRO>

<MACRO  name="Next Lead Org"
        lang="JScript" 
        desc="Move to the next lead organization in the protocol"
        hide="false">
  <![CDATA[
    function nextLeadOrg() {
        var rng = ActiveDocument.Range;
        if (!rng.MoveToElement("ProtocolLeadOrg", true)) {
            Application.Alert("No more ProtocolLeadOrg elements found.");
            return;
        }
        rng.Select();
    }
    nextLeadOrg();
  ]]>
</MACRO>

<MACRO  name="Test Me"
        lang="JScript" 
        desc="dummy test macro"
        key="Ctrl+Alt+T" 
        hide="false">
  <![CDATA[
    function xturnOffStandardToolbars() {
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("Standard"); }
        catch (e) { }
        if (cmdBar)
            cmdBar.Visible = false;
        cmdBar = null;
        try { cmdBar = cmdBars.item("Formatting"); }
        catch (e) { }
        if (cmdBar) {
            cmdBar.Visible = true;
            var controls = cmdBar.Controls;
            Application.Alert("count=" + controls.count);
            for (var i = controls.count; i >= 1; --i) {
                try {
                    item = controls.item(i);
                    var str = item.DescriptionText;
                    if (str.indexOf("List") != -1) {
                        Application.Alert("deleting " + str);
                        item.Delete();
                    }
                }
                catch (e) {}
            }
        }
    }
    function testMe() {

        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("Formatting"); }
        catch (e) { }
        if (cmdBar) {
            cmdBar.Visible = true;
            var controls = cmdBar.Controls;
            Application.Alert("Count: " + controls.count);
            for (var i = 1; i <= controls.count; ++i) {
                item = controls.item(i);
                try {
                    var str = item.DescriptionText;
                    Application.Alert("Desc(" + i + "): " + str);
                    Application.Alert("OnAction(" + i + "): " + item.OnAction);
                    Application.Alert("TT(" + i + "): " + item.TooltipText);
                }
                catch (e) {}
            }
        }
        return;
        Application.Alert("control: " + controls.item(i).TooltipText);
        Application.Alert("file menu has " + controls.Count + " controls");
        var printItem    = controls.item("Print...");
        Application.Alert("printItem is [" + printItem + "]");
        var printAction  = printItem.OnAction;
        Application.Alert("Print action name is [" + printAction + "]");
        return;
    }
    //testMe();
    xturnOffStandardToolbars();
    //var testElem = Selection.ContainerNode;
    //Application.Alert("container name is " + testElem.nodeName
    //    + "; container type is " + testElem.nodeType)
    //Selection.ReadOnlyContainer = false;
    //var testNode = ActiveDocument.createTextNode("foobar");
    //testElem.appendChild(testNode);
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
                    Application.ShowPage(url);
                }
            }
        }
    }

    personsLinkingToOrgLoc();

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
        Application.ShowPage(url);
    }

    termHierarchyDisplay();

  ]]>
</MACRO>

<MACRO  name="CDR Terminology Usage Report"
        lang="JScript" 
        desc="Report listing documents which are indexed by this term"
        hide="false">
  <![CDATA[

    function termUsageReport() {
        if (ActiveDocument && ActiveDocument.doctype.name == "Term") {
            var nodes = 
                Application.ActiveDocument.getElementsByTagName("DocId");
            if (nodes.length > 0) {
                var elem  = nodes.item(0);
                var docId = getTextContent(elem);
                var url = CdrCgiBin + "TermUsage.py?DocId=" + docId;
                Application.ShowPage(url);
            }
            else {
                Application.Alert("This is a new document.");
            }
        }
        else {
            Application.Alert("No Term document found.");
        }
    }

    termUsageReport();

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
        Application.ShowPage(url);
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

<MACRO name="PubMed Browse" 
       lang="JScript" 
       id="2022">
  <![CDATA[
    function searchPubMed() {
        var url = "http://www.ncbi.nlm.nih.gov/entrez/";
        Application.ShowPage(url);
    }
    searchPubMed();
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
    Selection.ElementAttribute("Style", "ItemizedList", 0) = "simple";
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
    Application.ShowPage(CdrCgiBin + "Help.py")
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
            //Application.Alert("Just turned on toolbar for " + docType.name);
        }
    }
    adjustToolbars();
  ]]>
</MACRO>

<MACRO name="On_Document_Close"
       lang="JScript">
  <![CDATA[
    hideToolbars();
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

<MACRO name="New Current Org Status" 
       lang="JScript">
  <![CDATA[
    function newCurrentOrgStatus() {
        Selection.MoveRight();
        Selection.MoveLeft();
        var rng = ActiveDocument.Range;
        var savePos = ActiveDocument.Range;
        rng.SelectElement();
        var oldStatusElem = rng.ContainerNode;
        if (oldStatusElem.nodeName != "CurrentOrgStatus") {
            Application.Alert("Not in CurrentOrgStatus");
            return;
        }
        rng.SelectElement();
        elemText = rng.Text;
        elemText = elemText.replace("<CurrentOrgStatus", "<PreviousOrgStatus");
        elemText = elemText.replace("</CurrentOrgStatus>", 
                                    "</PreviousOrgStatus>");
        var rulesChecking = ActiveDocument.RulesChecking;
        ActiveDocument.RulesChecking = false;
        var newElem = "<CurrentOrgStatus>"
                    + "<StatusName></StatusName>"
                    + "<StatusDate>" + getCurDateString() + "</StatusDate>"
                    + "<Comment>Your comment here ...</Comment>"
                    + "<EnteredBy>" + CdrUserName + "</EnteredBy>"
                    + "<EntryDate>" + getCurDateString() + "</EntryDate>"
                    + "</CurrentOrgStatus>";
        rng.PasteString(newElem + elemText);
        savePos.Select();
        Selection.MoveRight();
        Selection.MoveLeft();
        ActiveDocument.RulesChecking = rulesChecking;
    }
    newCurrentOrgStatus();
  ]]>
</MACRO>

<MACRO name="Insert PatientCharacteristics" 
       lang="JScript">
  <![CDATA[
    function insertPatientCharacteristics() {
        //Selection.MoveRight();
        //Selection.MoveLeft();
        var rng = ActiveDocument.Range;
        var savePos = ActiveDocument.Range;
        var rulesChecking = ActiveDocument.RulesChecking;
        ActiveDocument.RulesChecking = false;
        var newElems = "<ItemizedList>"
                     + "<ListTitle>Age</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Performance status</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Life expectancy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Hematopoietic</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Hepatic</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Renal</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Cardiovascular</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Pulmonary</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Other</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>";
  
        rng.PasteString(newElems);
        savePos.Select();
        ActiveDocument.RulesChecking = rulesChecking;
    }
    insertPatientCharacteristics();
  ]]>
</MACRO>

<MACRO name="Insert PriorConcurrentTherapy" 
       lang="JScript">
  <![CDATA[
    function insertPriorConcurrentTherapy() {
        //Selection.MoveRight();
        //Selection.MoveLeft();
        var rng = ActiveDocument.Range;
        var savePos = ActiveDocument.Range;
        var rulesChecking = ActiveDocument.RulesChecking;
        ActiveDocument.RulesChecking = false;
        var newElems = "<ItemizedList>"
                     + "<ListTitle>Biologic therapy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Chemotherapy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Endocrine therapy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Radiotherapy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Surgery</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList>"
                     + "<ListTitle>Other</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>";
        rng.PasteString(newElems);
        savePos.Select();
        ActiveDocument.RulesChecking = rulesChecking;
    }
    insertPriorConcurrentTherapy();
  ]]>
</MACRO>

<MACRO name="Reset Contact Information" 
       lang="JScript">
  <![CDATA[
    Application.Alert("Stub for Reset Contact Information Macro");
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
        Application.ShowPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="Protocol HP QC Report" 
       lang="JScript">
  <![CDATA[
    function protocolHpQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "ProtocolHpQcReport.py?Session="
                + CdrSession + "&DocId=" + docId;
        Application.ShowPage(url);
    }
    protocolHpQcReport();
  ]]>
</MACRO>

<MACRO name="Protocol Patient QC Report" 
       lang="JScript">
  <![CDATA[
    function protocolPatientQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "ProtocolPatientQcReport.py?Session="
                + CdrSession + "&DocId=" + docId;
        Application.ShowPage(url);
    }
    protocolPatientQcReport();
  ]]>
</MACRO>

<MACRO name="Protocol Admin QC Report" 
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
                + CdrSession + "&DocId=" + docId +
                "&Filter=name:Denormalization+Filter+(1/1):+InScope+Protocol" +
                "&Filter1=name:InScope+Protocol+Administrative+Report+Filter";
        Application.ShowPage(url);
    }
    protocolAdminQcReport();
  ]]>
</MACRO>

<MACRO name="Protocol Citations QC Report" 
       lang="JScript">
  <![CDATA[
    function protocolCitationsQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "ProtocolCitationsQcReport.py?Session="
                + CdrSession + "&DocId=" + docId;
        Application.ShowPage(url);
    }
    protocolCitationsQcReport();
  ]]>
</MACRO>

<MACRO name="Generate Mailer" 
       lang="JScript">
  <![CDATA[
    function generateMailer() {
        var url = CdrCgiBin + "Mailers.py?Session=" + CdrSession;
        Application.ShowPage(url);
    }
    generateMailer();
  ]]>
</MACRO>

<MACRO name="Go To Admin Info Section"
       lang="JScript">
  <![CDATA[
    if (Selection != null) {
        Selection.MoveToDocumentStart();
        Selection.MoveToElement("CurrentProtocolStatus");
        Selection.SelectContainerContents();
    }
  ]]>
</MACRO>

<MACRO name="Go To Scientific Info Section"
       lang="JScript">
  <![CDATA[
    if (Selection != null) {
        Selection.MoveToDocumentStart();
        Selection.MoveToElement("ProtocolAbstract");
    }
  ]]>
</MACRO>

<MACRO name="Protocol Merge" 
       lang="JScript">
  <![CDATA[
    function protocolMerge() {
        var url = CdrCgiBin + "MergeProt.py?Session=" + CdrSession;
        Application.ShowPage(url);
    }
    protocolMerge();
  ]]>
</MACRO>

<MACRO name="Search PubMed" 
       lang="JScript">
  <![CDATA[
    function searchPubMed() {
        var url = "http://www.ncbi.nlm.nih.gov/entrez/";
        Application.ShowPage(url);
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

<MACRO name="Next Summary Section" 
       key ="Ctrl+Alt+N" 
       lang="JScript" 
       id  ="2033">
  <![CDATA[
    Selection.MoveToElement("SummarySection");
  ]]>
</MACRO>

<MACRO name="Previous Summary Section" 
       lang="JScript" 
       id  ="2034" 
       key ="Ctrl+Alt+P">
  <![CDATA[
    Selection.MoveToElement("SummarySection", false);
  ]]>
</MACRO>

<MACRO name="Higher Summary Section" 
       lang="JScript" 
       id  ="2035" 
       key ="Ctrl+Alt+H">
  <![CDATA[
    function higherSection() {
        try {
            if (ActiveDocument) {
                var rng = ActiveDocument.Range;
                var foundOne = false;
                var i = 0; // Safety measure...
                while (rng && i < 50) {
                    var node = rng.ContainerNode;
                    if (!node) { 
                        var msg = "Not inside a nested SummarySection";
                        Application.Alert(msg);
                        break; 
                    }
                    if (node.nodeName == "SummarySection") {
                        if (foundOne) {
                            rng.SelectBeforeContainer();
                            rng.Select();
                            break;
                        }
                        foundOne = true;
                    }
                    rng.SelectBeforeContainer();
                    i++;
                }
            }
        }
        catch (e) { }
    }
    higherSection();
  ]]>
</MACRO>

<MACRO name="Create Summary Markup Report" 
       lang="JScript">
  <![CDATA[
    function createSummaryMarkupReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&Session="
                            + CdrSession;
        Application.ShowPage(url);
    }
    createSummaryMarkupReport();
  ]]>
</MACRO>

<MACRO name="Create HTML for Board" 
       lang="JScript">
  <![CDATA[
    function createHtmlForBoard() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "Filter.py?DocId=" + docId;
        Application.ShowPage(url);
    }
    Application.Alert("Don't have filters for this command yet.");
    //createHtmlForBoard();
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
        var url = CdrCgiBin + "QcReport.py?DocType=Summary:bu&DocId="
                            + docId
                            + "&Session="
                            + CdrSession;
        Application.ShowPage(url);
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
        var url = CdrCgiBin + "QcReport.py?DocType=Summary:rs&DocId="
                            + docId
                            + "&Session="
                            + CdrSession;
        Application.ShowPage(url);
    }
    redlineStrikeoutReport();
  ]]>
</MACRO>

<MACRO name="Patient Summary QC Report" 
       lang="JScript">
  <![CDATA[
    function patientSummaryQcReport() {
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
                + CdrSession + "&DocId=" + docId +
                "&Filter=name:Summary-Copy+XML+for+Patient+Summary+Report" +
                "&Filter1=name:Patient+Summary+QC+Report+Filter";
        Application.ShowPage(url);
    }
    patientSummaryQcReport();
  ]]>
</MACRO>

<MACRO name="Generate Summary Mailers"
       lang="JScript">
  <![CDATA[
    function generateSummaryMailers() {
        var url = CdrCgiBin + "PDQMailerRequestForm.py?Session="
            + CdrSession;
        Application.ShowPage(url);
    }
    generateSummaryMailers();
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
        Application.ShowPage(url);
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

<MACRO name="Insert ProtocolAmendmentInformation" 
       lang="JScript" >
  <![CDATA[
    function insertProtocolAmendmentInformation() {
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("ProtocolAmendmentInformation", false)) {
            Application.Alert(
                    "Can't insert ProtocolAmendmentInformation element");
                return; 
        }
        rng.InsertElement("ProtocolAmendmentInformation");
        rng.InsertWithTemplate("ProtocolAmendment");
        rng.Select();
    }
    insertProtocolAmendmentInformation();
  ]]>
</MACRO>

<MACRO name="Undo Last Edit" 
       lang="JScript" >
  <![CDATA[
    if (ActiveDocument)
        ActiveDocument.Undo();
  ]]>
</MACRO>

<MACRO name="NHL Text" 
       lang="JScript">
  <![CDATA[
    function nhlText() {
        var rng = ActiveDocument.Range;
        if (!rng.IsParentElement("DiseaseCharacteristics")) {
            Application.Alert("This macro can only be used within the "
                    + "DiseaseCharacteristics element");
            return;
        }
        if (!rng.FindInsertLocation("Para")) {
            Application.Alert("Unable to insert new Para element");
            return;
        }
        rng.InsertElement("Para");
        rng.Text = "A new classification scheme for adult non-Hodgkin's "
                 + "lymphoma has been adopted by PDQ.  The terminology "
                 + "of \"indolent\" or \"aggressive\" lymphoma will "
                 + "replace the former terminology of \"low\", "
                 + "\"intermediate\", or \"high\" grade lymphoma. "
                 + "However, this protocol uses the former terminology.";
    }
    nhlText();
  ]]>
</MACRO>

<MACRO name="Change Participating Org Status" 
       lang="JScript">
  <![CDATA[
    function changePOStatus() {
        var rng = ActiveDocument.Range;
        if (!rng.IsParentElement("ProtocolLeadOrg")) {
            Application.Alert("This macro can only be used within a "
                    + "ProtocolLeadOrg element");
            return;
        }
        if (!rng.MoveToElement("ProtocolLeadOrg", false)) {
            Application.Alert("Can't find ProtocolLeadOrg element.");
            return;
        }
        var node = rng.ContainerNode;
        var elemList = node.getElementsByTagName("CurrentOrgStatus");
        if (!elemList || !elemList.length) {
            Application.Alert("Can't find CurrentOrgStatus element.");
            return;
        }
        elemList = elemList.item(0).getElementsByTagName("StatusName");
        if (!elemList || !elemList.length) {
            Application.Alert("Can't find StatusName element.");
            return;
        }
        var status = getTextContent(elemList.item(0));
        if (!status) {
            Application.Alert("Lead org status has not yet been set.");
            return;
        }
        var yes = 6;
        var no = 7;
        var response = no;
        var displayOkNoCancelButtons = 3;
        var useWarningQueryIcon = 32;
        var dlgConfig = displayOkNoCancelButtons + useWarningQueryIcon;
        var dlgMsg = "Set participating org statuses to " + status + "?";
        var dlgTitle = "Adjust Participating Organization Status";
        response = Application.MessageBox(dlgMsg, dlgConfig, dlgTitle);
        if (response != yes)
            return;
        elemList = node.getElementsByTagName("ProtocolSites");
        if (!elemList || !elemList.length) {
            Application.Alert("Can't find ProtocolSites element.");
            return;
        }
        elemList = elemList.item(0).getElementsByTagName("OrgSite");
        if (!elemList || !elemList.length) {
            Application.Alert("No participating organizations found.");
            return;
        }
        for (var i = 0; i < elemList.length; ++i) {
            var site = elemList.item(i);
            var statusList = site.getElementsByTagName("OrgSiteStatus");
            if (statusList && statusList.length) {
                //var poStatus = getTextContent(statusList.item(0));
                var statusNode = statusList.item(0);
                rng.selectNodeContents(statusNode);
                var oldSetting = rng.WritePermittedContainer;
                rng.WritePermittedContainer = true;
                rng.pasteString(status);
                rng.WritePermittedContainer = oldSetting;
            }
        }
        Application.Alert("Status set for " + elemList.length + 
                " participating organizations.");
    }
    changePOStatus();
  ]]>
</MACRO>

<MACRO name="Insert Mailer Response" 
        key="Alt+Z"
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

</MACROS>
