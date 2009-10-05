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
    
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument

'  Test
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    If Selection.HeaderFooter.IsHeader = True Then
        ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
    Else
        ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    End If
    Selection.HeaderFooter.PageNumbers.Add PageNumberAlignment:= _
        wdAlignPageNumberCenter, FirstPage:=True
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument

End Sub
