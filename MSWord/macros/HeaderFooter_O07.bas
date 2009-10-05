Sub HeaderFooter()
'
' HeaderFooter Macro
'
'
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
         InsertAsFullWidth:=False
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
    Selection.ParagraphFormat.Alignment = wdAlignParagraphRight
    WordBasic.GoToFooter
    WordBasic.ViewFooterOnly
' This is the original code that needs to be replace after the template
' has been renamed and added to normal.dotm
'    ActiveDocument.AttachedTemplate.BuildingBlockEntries("Plain Number 2").
    NormalTemplate.BuildingBlockEntries("CDR Footer"). _
       Insert Where:=Selection.Range, _
       RichText:=True
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub

