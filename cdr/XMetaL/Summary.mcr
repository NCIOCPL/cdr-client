<?xml version="1.0"?>
<!DOCTYPE MACROS SYSTEM "macros.dtd">
<MACROS>

    <MACRO name="New Summary Section" 
           key ="Alt+S" 
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
        var url = CdrCgiBin + "Filter.py?Filter=CDR266308&DocId=" + docId;
        Application.ShowPage(url);
    }
    createSummaryMarkupReport();
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

</MACROS>
