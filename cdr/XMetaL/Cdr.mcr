<?xml version="1.0"?>

<!-- 
     $Id: Cdr.mcr,v 1.3 2001-06-12 02:21:44 bkline Exp $

     $Log: not supported by cvs2svn $
     Revision 1.2  2001/06/11 21:19:40  bkline
     Added call to isReadOnly().

     Revision 1.1  2000/10/17  14:46:55  bobk
     Initial revision
 
  -->

<!DOCTYPE MACROS SYSTEM "macros.dtd">
<MACROS> 

<MACRO name="On_Macro_File_Load" lang="JScript"><![CDATA[
  
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
  
]]></MACRO>

<MACRO name="Switch to CSS 1" lang="JScript" key="Ctrl+Alt+Shift+A">
    switchCSS("InScopeProtocol-1.css", "InScopeProtocol.css");
</MACRO>

<MACRO name="Switch to CSS 2" lang="JScript" key="Ctrl+Alt+Shift+B">
    switchCSS("InScopeProtocol-2.css", "InScopeProtocol.css");
</MACRO>

<MACRO name="MakeReplaceText" key="Ctrl+Alt+Z" lang="VBScript" id="1127">
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
 
<MACRO name="On_Update_UI" hide="true" lang="JScript"><![CDATA[

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

]]></MACRO>

<MACRO name="Refresh Macros" key="Ctrl+Alt+R" lang="JScript" id="1270" tooltip="" desc="">
<![CDATA[
 Application.RefreshMacros();
 Application.Alert("Macros have been refreshed");
]]>
</MACRO>

<MACRO lang="JScript" name="Open Document Macros" id="1272">
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

<MACRO name="Open Application Macros" lang="JScript" id="1274">
<![CDATA[
 var mpath = Application.MacroFile;
 Documents.Open(mpath, 1); // open in tags on view
]]>
</MACRO>

<MACRO name="On_Application_Open" hide="true" lang="JScript">
    /*
     * Initialize global variables for CDR macros.
     */
    var gEditingCdrLink = false;
    var cdrObj = null;
    cdrLogon();
    //Application.DisablePlainTextView();
</MACRO>

<MACRO name="On_Application_Close" hide="true" lang="JScript">
    /*
     * Close the connection to the CDR Server.
     */
    if (cdrObj != null) {
        cdrObj.logoff();
    }
</MACRO>

<MACRO name="On_Mouse_Over" lang="JScript" hide="true"><![CDATA[
// Reset the Status Text and the Cursor in case a different document changed them and they are stuck.
function OnMouseOver()
{
   Application.SetStatusText("");
   Application.SetCursor(0);
}
OnMouseOver();
]]></MACRO> 

<MACRO name="On_DTD_Open_Complete" key="" hide="true" lang="VBScript"><![CDATA[
Function doaddElements()
  ' In the macro the new document is NOT the active document
  ' so to get at the document type information do
  Set docType = Application.NewDocumentType

  ' root element
  Dim rootElem
  rootElem = docType.name
' Application.Alert rootElem
  If rootElem = "Article" Then
    ' add Deletion element
    docType.addElement "Deletion", "Deletion", True , False
    ' add attribute UserName
    docType.addAttribute "Deletion", "UserName", "", 0, 0 
    ' add attribute Time
    docType.addAttribute "Deletion", "Time", "", 0, 0 
    
    ' add Insertion element
    docType.addElement "Insertion", "Insertion", True , False
    ' add attribute UserName
    docType.addAttribute "Insertion", "UserName", "", 0, 0 
    ' add attribute Time
    docType.addAttribute "Insertion", "Time", "", 0, 0 
    
    ' add Annotation element
    docType.addElement "Annotation", "Annotation" , True , False
    ' add attribute UserName
    docType.addAttribute "Annotation", "UserName", "", 0, 0 
    ' add attribute Time
    docType.addAttribute "Annotation", "Time", "", 0, 0 
    ' add attribute Initials
    docType.addAttribute "Annotation", "Initials", "", 0, 0 
    ' add attribute Comment
    docType.addAttribute "Annotation", "Comment", "", 0, 0 
    
    'add Deletion element  to the other elements inclusion list 
    If docType.hasElementType("Deletion") And docType.hasElementType("Article") Then
      docType.addElementToInclusions "Deletion", "Article"
    End If
    
    'add Insertion element  to the other elements inclusion list 
    If docType.hasElementType("Insertion") And docType.hasElementType("Article") Then
      docType.addElementToInclusions "Insertion", "Article"
    End If

    'add Annotation element  to the other elements inclusion list 
    If docType.hasElementType("Annotation") And docType.hasElementType("Article") Then
      docType.addElementToInclusions "Annotation", "Article"
    End If
  End If
End Function

doaddElements()
]]></MACRO>

<MACRO name="On_Document_Open_Complete" hide="true" lang="JScript">
<![CDATA[
    Selection.GotoNext(0);
    Selection.GotoNext(0);
    Selection.SelectContainerContents();
]]>
</MACRO>

<MACRO name="On_Context_Menu" lang="JScript">
  <![CDATA[
 
    /*
     * Adds a menu option to the popup context menu for custom editing
     * of a link element.
     */
    Application.AppendMacro("-", "");
    Application.AppendMacro("&Edit Element", "Cdr Edit");
   
  ]]>
</MACRO>

<MACRO name="On_Default_CommandBars_Complete" key="" lang="JScript">
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

<MACRO name="Cdr Logon" key="" lang="JScript" tooltip="Log On To CDR" id="1342">
  <![CDATA[

    cdrLogon();

  ]]>
</MACRO>

<MACRO name="Cdr Retrieve" key="" lang="JScript" tooltip="Retrieve Document From CDR" id="1221">
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

<MACRO name="Cdr Search" key="" lang="JScript" tooltip="Search for Document in CDR" id="20103">
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

<MACRO name="Cdr Validate" key="" lang="JScript" tooltip="Ask CDR to Validate Document">
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

<MACRO name="Cdr Save" key="" lang="JScript" tooltip="Store Document in the CDR" id="1365"><![CDATA[
  

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

<MACRO name="Cdr Logoff" key="" lang="JScript" tooltip="Log out of the CDR" id="20307">
  <![CDATA[
    cdrLogoff();
  ]]>
</MACRO>

<MACRO name="Cdr Edit" key="" lang="JScript" tooltip="Store Document in the CDR" id="1912">
 <![CDATA[
    cdrEdit();
  ]]>
</MACRO>

<MACRO name="Test Schema Validation" lang="JScript" key="Ctrl+Alt+Shift+V">
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


<MACRO name="PrevElement" key="Shift+Tab" lang="JScript"><![CDATA[
    Selection.GotoPrevious(0);
    Selection.SelectContainerContents();
]]></MACRO>

<MACRO name="NextElement" key="Tab" lang="JScript"><![CDATA[
    Selection.GotoNext(0);
    Selection.SelectContainerContents();
]]></MACRO>

<MACRO name="ReloadCSS" key="Ctrl+Alt+S" lang="JScript"><![CDATA[
    ActiveDocument.RefreshCssStyle();
]]></MACRO>

<MACRO name="On_Double_Click" lang="JScript" key="Ctrl+Shift+E"><![CDATA[
    cdrEdit();
]]></MACRO>

</MACROS>
