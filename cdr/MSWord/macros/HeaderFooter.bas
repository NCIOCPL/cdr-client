Attribute VB_Name = "HeaderFooter"

Sub HeaderFooter()
Attribute HeaderFooter.VB_Description = "Macro recorded 12/3/2003 by Volker Englisch"
Attribute HeaderFooter.VB_ProcData.VB_Invoke_Func = "Normal.NewMacros.HeaderFooter"
'
' HeaderFooter Macro
' Macro recorded 12/3/2003 by Volker Englisch
'
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.WholeStory
    Selection.Delete Unit:=wdCharacter, Count:=1
    Selection.ParagraphFormat.Alignment = wdAlignParagraphRight
    Selection.InsertDateTime DateTimeFormat:="MM/dd/yyyy", InsertAsField:= _
        False, DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
    Selection.TypeParagraph
    Selection.ParagraphFormat.Alignment = wdAlignParagraphCenter
    Selection.TypeText Text:=""
    If Selection.HeaderFooter.IsHeader = True Then
        ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
    Else
        ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    End If
    Selection.WholeStory
    Selection.Delete Unit:=wdCharacter, Count:=1
    Selection.ParagraphFormat.Alignment = wdAlignParagraphCenter
    Selection.Fields.Add Range:=Selection.Range, Type:=wdFieldPage
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    With ActiveDocument.Styles("Normal").Font
        .Name = "Arial"
        .Size = 12
        .Bold = False
        .Italic = False
        .Underline = wdUnderlineNone
        .UnderlineColor = wdColorAutomatic
        .StrikeThrough = False
        .DoubleStrikeThrough = False
        .Outline = False
        .Emboss = False
        .Shadow = False
        .Hidden = False
        .SmallCaps = False
        .AllCaps = False
        .Color = wdColorAutomatic
        .Engrave = False
        .Superscript = False
        .Subscript = False
        .Scaling = 100
        .Kerning = 0
        .Animation = wdAnimationNone
    End With
    With ActiveDocument.Styles("Normal")
        .AutomaticallyUpdate = False
        .BaseStyle = ""
        .NextParagraphStyle = "Normal"
    End With
End Sub

