<?xml version="1.0"?>
<!DOCTYPE MACROS SYSTEM "macros.dtd">
<MACROS>

<MACRO name="New Section" 
       key="Alt+S" 
       lang="VBScript" 
       id="1247">
  <![CDATA[
    Selection.InsertWithTemplate "SummarySection"
  ]]>
</MACRO>

<MACRO name="Next Section" 
       key="Ctrl+Alt+N" 
       lang="VBScript" 
       id="2033">
  <![CDATA[
    Selection.GotoNext("SummarySection");
  ]]>
</MACRO>

<MACRO name="Previous Section" 
       lang="VBScript" 
       id="2034" 
       key="Ctrl+Alt+P">
  <![CDATA[
  ]]>
</MACRO>

<MACRO name="Higher Section" 
       lang="VBScript" 
       id="2035" 
       key="Ctrl+Alt+H">
  <![CDATA[
  ]]>
</MACRO>

</MACROS>
