<?xml version="1.0"?>

<!-- 
     $Id: Cdr.mcr,v 1.4 2001-08-17 14:27:03 bkline Exp $

     $Log: not supported by cvs2svn $
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

    // XXX Temporary.  Need to be replaced with calls to the DLL.
    var UserName = 'rmk';
  
    /*
     * Obtains account credentials from the user and submits them to the CDR
     * server to establish a logged in session.
     */
    function cdrLogon() {
        cdrObj = new ActiveXObject("Cdr.Commands");
        if (cdrObj == null) {
            Application.Alert("Unable to find CDR DLL.");
        }
        else {
            cdrObj.logon();
        }
    }

    /*
     * Log the user out of the CDR server.
     */
    function cdrLogoff() {
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
        if (ActiveDocument == null)                   { return 0; }
        if (ActiveDocument.documentElement == null)   { return 0; }
        if (ActiveDocument.documentElement.getAttribute("readonly") == "yes") 
                                                      { return 1; }
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
            var rc  = cdrObj.edit();
            gEditingCdrLink = false;
        }
    }
  
    function getMarkupStyle(element) {
        var docProps = ActiveDocument.CustomDocumentProperties;
        var highlighting = docProps.item("Highlighting").value;
        var style = "color:black;background-color:white";
        if (highlighting == "True") {
            if (element == "Insertion") {
                style =  "color:red;background-color:white;" +
                         "text-decoration:underline";
            }
            else if (element == "Deletion") {
                style = "color:red;background-color:white;" +
                        "text-decoration:line-through";
            }
        }
        return (style);
    }

  ]]>
</MACRO>

<MACRO  name="Switch to CSS 1" 
        lang="JScript" 
        key="Ctrl+Alt+Shift+A">
    switchCSS("InScopeProtocol-1.css", "InScopeProtocol.css");
</MACRO>

<MACRO  name="Switch to CSS 2" 
        lang="JScript" 
        key="Ctrl+Alt+Shift+B">
    switchCSS("InScopeProtocol-2.css", "InScopeProtocol.css");
</MACRO>

<MACRO  name="MakeReplaceText" 
        key="Ctrl+Alt+Z" 
        lang="VBScript" 
        id="1127">
  <![CDATA[
 ' SoftQuad Script Language VBSCRIPT:
 if Application.Documents.Count = 0 Then
   Application.Alert("No Open Document")
 
 Else 

   If Application.ActiveDocument.ViewType = 2 Then
     Application.Alert("This macro doesn't work in Plain Text mode")
   Else 
     txt = Selection.Text
     Selection.Delete
     Selection.InsertReplaceableText(txt)
   End If
 End If
 
  ]]>
</MACRO>
 
<MACRO  name="On_Update_UI" 
        hide="true" 
        lang="JScript">
  <![CDATA[

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
        // Added to Softquad macro to make link elements read-only.
        //if (Selection.hasAttribute("cdr:ref") && !gEditingCdrLink) {
        //    Selection.ReadOnlyContainer = true;
        //} 

        // Added to Softquad macro to make CdrDocCtl element read-only.
        //else if (Selection.ContainerNode && 
        //        Selection.ContainerNode.nodeName == "CdrDocCtl") {
        //    Selection.CollapsedContainerTags = true;
        //    Selection.ReadOnlyContainer = true;
        //}
        //else {
        //    Selection.ReadOnlyContainer = false;
        //}
    }

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
        //docType  = ActiveDocument.doctype;
        rootElem = docType.name;

        // Add the Deletion element.
        docType.addElement("Deletion", "Deletion", true , false);
        docType.addAttribute("Deletion", "UserName", "", 0, 0);
        docType.addAttribute("Deletion", "Time", "", 0, 0);

        // Add the Insertion element.
        docType.addElement("Insertion", "Insertion", true , false);
        docType.addAttribute("Insertion", "UserName", "", 0, 0);
        docType.addAttribute("Insertion", "Time", "", 0, 0);

        // Allow these elements anywhere.
        if (docType.hasElementType(rootElem)) {
            Application.Alert("Root element is " + rootElem);
            if (docType.hasElementType("Deletion")) {
                docType.addElementToInclusions("Deletion", rootElem);
            }
            if (docType.hasElementType("Insertion")) {
                docType.addElementToInclusions("Insertion", rootElem);
                //Application.Alert("Insertion/Deletion elements added");
            }
        }
        //var i;
        //var elems = docType.elementTypes;
        //var nElems = elems.ubound() + 1;
        //for (i = 0; i < nElems; ++i) {
        //    elem = elems.getItem(i);
        //    if (elem != rootElem && elem != "Deletion" && elem != "Insertion") {
        //        docType.addElementToInclusions(elem, "Deletion");
        //        docType.addElementToInclusions(elem, "Insertion");
        //    }
        //}
    }

    doAddElements();

  ]]>
</MACRO>

<MACRO  name="On_Document_Open_Complete" 
        hide="true" 
        lang="JScript">
<![CDATA[
    Selection.GotoNext(0);
    Selection.GotoNext(0);
    Selection.SelectContainerContents();
    var docProps = ActiveDocument.CustomDocumentProperties;
    docProps.Add("Highlighting", true);
    docProps.Add("ShowOriginal", false);
    docProps.Add("InsNextPrev", false);
    docProps.Add("DelNextPrev", false);
    Application.Run("Init_JScript_Macros");
]]>
</MACRO>

<MACRO  name="On_Context_Menu" 
        lang="JScript">
  <![CDATA[
 
    /*
     * Adds a menu option to the popup context menu for custom editing
     * of a link element.
     */
    Application.AppendMacro("-", "");
    Application.AppendMacro("&Edit Element", "Cdr Edit");
   
  ]]>
</MACRO>

<MACRO  name="On_Default_CommandBars_Complete" 
        key="" 
        lang="JScript">
  <![CDATA[

    /*
     * Adds a single CDR menu choice.  Invoked by addCdrMenu() below.
     */
    function addCdrMenuItem(menuControls, action, desc, label) {

        // Create a new menu item.
        var newItem = menuControls.Add(sqcbcTypePopup);

        // Set the new item's attributes.
        if (newItem != null) {
            newItem.OnAction        = action;
            newItem.TooltipText     = desc;
            newItem.DescriptionText = desc;
            newItem.Caption         = label;
            newItem.Enabled         = true;
        }
        else {
            Application.Alert("Unable to create \""+action+"\" menu item.");
        }
    }

    /*
     * Adds the CDR menu choices if they are not already present.
     */
    function addCdrMenu() {

        // Prepare some local variables.
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;
        var cdrMenu      = menuControls.item("Cdr");

        // Don't do this if it's already been done.
        if (cdrMenu != null) {
            return;
        }

        // Create the new menu.
        cdrMenu = menuControls.Add(sqcbcTypePopup, null, 2);
        cdrMenu.Caption = "&Cdr";

        // Add the menu items.
        var cdrItems = cdrMenu.Controls;
        //addCdrMenuItem(cdrItems, "Cdr Logon", 
        //               "Log on to the CDR system", "&Logon");
        addCdrMenuItem(cdrItems, "Cdr Retrieve", 
                       "Retrieve document by CDR ID", "&Retrieve");
        addCdrMenuItem(cdrItems, "Cdr Search", 
                       "Search for CDR documents by title", "S&earch");
        addCdrMenuItem(cdrItems, "Cdr Validate", 
                       "Validate current CDR document", "&Validate");
        addCdrMenuItem(cdrItems, "Cdr Save", 
                       "Save current CDR document", "&Save");
        //addCdrMenuItem(cdrItems, "Cdr Logoff", 
        //               "Log out from the CDR system", "Log&off");
    }

    /*
     * This workaround is needed because, as Softquad admits, there is no way
     * for us to customize our installation in a way which installs the CDR
     * menu as part of a customized default.tbr.
     */
    addCdrMenu();

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
        key="" 
        lang="JScript" 
        tooltip="Store Document in the CDR" 
        id="1365">
  <![CDATA[
  

    /*
     * Saves the currently active document in the CDR repository.
     */
    function cdrSave() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            var rc  = cdrObj.save();
            if (rc == 0) {
                Application.Alert("Document stored successfully.");
            }
            else {
                Application.Alert("Error return from save is " + rc);
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
        key="" 
        lang="JScript" 
        tooltip="Store Document in the CDR" 
        id="1912">
 <![CDATA[
    cdrEdit();
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

<MACRO  name="On_Double_Click" 
        lang="JScript" 
        key="Ctrl+Shift+E">
  <![CDATA[
    cdrEdit();
  ]]>
</MACRO>

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

<MACRO name="On_Update_UI"
       lang="JScript"
       hide="true"
       id="144">
         <![CDATA[
       
    function refreshStyles() {

        var docProps = ActiveDocument.CustomDocumentProperties;
        if (docProps.count == 0) return;
        if (docProps.item("Highlighting").value == "True") {
            var rng = ActiveDocument.Range;
            rng.MoveToDocumentStart();
            while(rng.MoveToElement("Insertion")) {
                rng.ContainerStyle = "color:red; text-decoration:underline";
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
                rng.ContainerStyle = "color:red; text-decoration:underline";
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
                        Selection.ContainerAttribute("UserName") = UserName;
                        Selection.ContainerAttribute("Time") = 
                            date.toLocaleString();
                        Selection.ContainerStyle = getMarkupStyle("Deletion");
                        Selection.Text = del_txt;
                    }
                }
            }
            else if (!Selection.isParentElement("Deletion")) {
                if (Selection.CanSurround("Deletion")) {
                    Selection.Surround("Deletion");
                    Selection.ContainerStyle = getMarkupStyle("Deletion");
                    Selection.ContainerAttribute("UserName") = UserName;
                    Selection.ContainerAttribute("Time") =
                                                    date.toLocaleString();
                    var rng = ActiveDocument.Range;
                    rng.SelectContainerContents();
                    var start = rng.Duplicate;
                    start.Collapse(1);
                    var end = rng.Duplicate;
                    end.Collapse(0);
                    readtree(start, end);
                    Application.Alert("Did it!");
                }
                else {
                    Application.Alert("Can't do it!");
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
                Selection.ContainerAttribute("UserName") = UserName;
                var date = new Date();
                    Selection.ContainerAttribute("Time") = date.toLocaleString();
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
                    Selection.ContainerAttribute("UserName") = UserName;
                    var date = new Date();
                    Selection.ContainerAttribute("Time") = 
                        date.toLocaleString();
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

    if (CanRunMacros()) {
        getInsertion();
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
                "\\Forms\\Revision Control\\AcceptOrReject.hhf");
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
    if (CanRunMacros()) {
        doAcceptChange();
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

    if (CanRunMacros()) {
        doRejectChange();
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
        while(rng_HL.MoveToElement("Deletion")) {
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
        while(rng_HL.MoveToElement("Deletion")) {
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
    //----------------------------------------------------------------------
    function doFindNext() {

        var docProps = ActiveDocument.CustomDocumentProperties;
        var parentName = Selection.ContainerNode.parentNode.nodeName;
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
  
    if (CanRunMacros()) {
        doFindNext();
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

    if (CanRunMacros()) {
        doFindPrev();
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

</MACROS>
