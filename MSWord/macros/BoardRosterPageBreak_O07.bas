Sub BoardRosterPageBreak()
'
' BoardRosterPageBreak Macro
' Macro recorded 8/14/2008 by Volker Englisch
'
Dim lCount As Long
    lCount = 0
    
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
    Selection.GoTo What:=wdGoToLine, Which:=wdGoToFirst, Count:=1, Name:=""
'
    Do
        lCount = lCount + 1

        Selection.GoTo What:=wdGoToTable, Which:=wdGoToNext, Count:=1, Name:=""
        Selection.Rows.AllowBreakAcrossPages = False
        Selection.Find.ClearFormatting
        With Selection.Tables(1).Rows
            .AllowBreakAcrossPages = False
        End With
        
    Loop Until lCount = 40
    
    Selection.GoTo What:=wdGoToTable, Which:=wdGoToNext, Count:=1, Name:=""
    Selection.GoTo What:=wdGoToTable, Which:=wdGoToNext, Count:=1, Name:=""
    
    WordBasic.ViewFooterOnly
    WordBasic.ViewFooterOnly
    NormalTemplate.BuildingBlockEntries("CDR Footer").Insert Where:=Selection. _
        Range, RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument

End Sub
