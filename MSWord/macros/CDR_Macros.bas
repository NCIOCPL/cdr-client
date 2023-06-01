Attribute VB_Name = "NewMacros"
Sub ATimeStamp()
    MsgBox "Last Modified:  2016-05-26"
End Sub
Sub AutoFitTableWidth()
'
' AutoFitTableWidth Macro
'
'
    Selection.HomeKey Unit:=wdStory
    For Each aTable In ActiveDocument.Tables
       aTable.AutoFitBehavior (wdAutoFitWindow)
       aTable.Range.Font.Name = "Arial"
    Next aTable
    Selection.HomeKey Unit:=wdStory
    
End Sub
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
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 10pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
    
'    WordBasic.ViewFooterOnly
'    WordBasic.ViewFooterOnly
'    NormalTemplate.BuildingBlockEntries("Plain Number 2").Insert Where:=Selection. _
'        Range, RichText:=True
'    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
'        BuildingBlockEntries("CDR Footer").Insert Where:=Selection.Range, _
'        RichText:=True
'    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument

End Sub
Sub ChangeFontSize()
'
' ChangeFontSize Macro
'
' Note: Headings that are a different size will stay at their size
'
    Selection.Find.ClearFormatting
    Selection.Find.Font.Size = 12
    With Selection.Find
        .Text = ""
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = True
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
    Selection.Font.Size = 10
End Sub
Sub ChangeFontSizeLoopTo10()
'
' ChangeFontSize Macro
'
' Searching for any text that's 12pt and changing it to 10pt throughout
' the document.
' Note: Headings that are at a different size will stay at their size
'
Dim i As Long
With ActiveDocument
For i = 0 To ActiveDocument.Sentences.Count + 1
    Selection.Find.ClearFormatting
    Selection.Find.Font.Size = 12
    With Selection.Find
        .Text = ""
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = True
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
    Selection.Font.Size = 10
    Next i
End With

Selection.HomeKey Unit:=wdStory

End Sub
Sub ChangeFontSizeLoopTo11()
'
' ChangeFontSize Macro
'
' Searching for any text that's 12pt and changing it to 10pt throughout
' the document.
' Note: Headings that are at a different size will stay at their size
'
Dim i As Long
With ActiveDocument
' For i = 1 To 1000 '' How to identify the number of finds in the document
For i = 0 To ActiveDocument.Sentences.Count + 1
    Selection.Find.ClearFormatting
    Selection.Find.Font.Size = 12
    With Selection.Find
        .Text = ""
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = True
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
    Selection.Font.Size = 11
    Next i
End With

Selection.HomeKey Unit:=wdStory

End Sub
Sub CreateWordToc()
'
' CreateToc Macro
' This macro creates a table of contents (TOC) at the position of the cursor
'
    Selection.MoveDown Unit:=wdLine, Count:=0
    With ActiveDocument.Styles("TOC 1")
        .AutomaticallyUpdate = True
        .BaseStyle = "Normal"
        .NextParagraphStyle = "Normal"
    End With
    With ActiveDocument.Styles("TOC 1").ParagraphFormat
        .LeftIndent = InchesToPoints(0)
        .RightIndent = InchesToPoints(0)
        .SpaceBefore = 0
        .SpaceBeforeAuto = False
        .SpaceAfter = 0
        .SpaceAfterAuto = False
        .LineSpacingRule = wdLineSpaceMultiple
        .LineSpacing = LinesToPoints(1.15)
        .Alignment = wdAlignParagraphLeft
        .WidowControl = True
        .KeepWithNext = False
        .KeepTogether = False
        .PageBreakBefore = False
        .NoLineNumber = False
        .Hyphenation = True
        .FirstLineIndent = InchesToPoints(0)
        .OutlineLevel = wdOutlineLevelBodyText
        .CharacterUnitLeftIndent = 0
        .CharacterUnitRightIndent = 0
        .CharacterUnitFirstLineIndent = 0
        .LineUnitBefore = 0
        .LineUnitAfter = 0
        .MirrorIndents = False
        .TextboxTightWrap = wdTightNone
    End With
    ActiveDocument.Styles("TOC 1").NoSpaceBetweenParagraphsOfSameStyle = False
'
    With ActiveDocument.Styles("TOC 2")
        .AutomaticallyUpdate = True
        .BaseStyle = "Normal"
        .NextParagraphStyle = "Normal"
    End With
    With ActiveDocument.Styles("TOC 2").ParagraphFormat
        .LeftIndent = InchesToPoints(0.15)
        .RightIndent = InchesToPoints(0)
        .SpaceBefore = 0
        .SpaceBeforeAuto = False
        .SpaceAfter = 0
        .SpaceAfterAuto = False
        .LineSpacingRule = wdLineSpaceMultiple
        .LineSpacing = LinesToPoints(1.15)
        .Alignment = wdAlignParagraphLeft
        .WidowControl = True
        .KeepWithNext = False
        .KeepTogether = False
        .PageBreakBefore = False
        .NoLineNumber = False
        .Hyphenation = True
        .FirstLineIndent = InchesToPoints(0)
        .OutlineLevel = wdOutlineLevelBodyText
        .CharacterUnitLeftIndent = 0
        .CharacterUnitRightIndent = 0
        .CharacterUnitFirstLineIndent = 0
        .LineUnitBefore = 0
        .LineUnitAfter = 0
        .MirrorIndents = False
        .TextboxTightWrap = wdTightNone
    End With
    ActiveDocument.Styles("TOC 2").NoSpaceBetweenParagraphsOfSameStyle = False
'
    With ActiveDocument.Styles("TOC 3")
        .AutomaticallyUpdate = True
        .BaseStyle = "Normal"
        .NextParagraphStyle = "Normal"
    End With
    With ActiveDocument.Styles("TOC 3").ParagraphFormat
        .LeftIndent = InchesToPoints(0.31)
        .RightIndent = InchesToPoints(0)
        .SpaceBefore = 0
        .SpaceBeforeAuto = False
        .SpaceAfter = 0
        .SpaceAfterAuto = False
        .LineSpacingRule = wdLineSpaceMultiple
        .LineSpacing = LinesToPoints(1.15)
        .Alignment = wdAlignParagraphLeft
        .WidowControl = True
        .KeepWithNext = False
        .KeepTogether = False
        .PageBreakBefore = False
        .NoLineNumber = False
        .Hyphenation = True
        .FirstLineIndent = InchesToPoints(0)
        .OutlineLevel = wdOutlineLevelBodyText
        .CharacterUnitLeftIndent = 0
        .CharacterUnitRightIndent = 0
        .CharacterUnitFirstLineIndent = 0
        .LineUnitBefore = 0
        .LineUnitAfter = 0
        .MirrorIndents = False
        .TextboxTightWrap = wdTightNone
    End With
    ActiveDocument.Styles("TOC 3").NoSpaceBetweenParagraphsOfSameStyle = False
'
    With ActiveDocument.Styles("TOC 4")
        .AutomaticallyUpdate = True
        .BaseStyle = "Normal"
        .NextParagraphStyle = "Normal"
    End With
    With ActiveDocument.Styles("TOC 4").ParagraphFormat
        .LeftIndent = InchesToPoints(0.46)
        .RightIndent = InchesToPoints(0)
        .SpaceBefore = 0
        .SpaceBeforeAuto = False
        .SpaceAfter = 0
        .SpaceAfterAuto = False
        .LineSpacingRule = wdLineSpaceMultiple
        .LineSpacing = LinesToPoints(1.15)
        .Alignment = wdAlignParagraphLeft
        .WidowControl = True
        .KeepWithNext = False
        .KeepTogether = False
        .PageBreakBefore = False
        .NoLineNumber = False
        .Hyphenation = True
        .FirstLineIndent = InchesToPoints(0)
        .OutlineLevel = wdOutlineLevelBodyText
        .CharacterUnitLeftIndent = 0
        .CharacterUnitRightIndent = 0
        .CharacterUnitFirstLineIndent = 0
        .LineUnitBefore = 0
        .LineUnitAfter = 0
        .MirrorIndents = False
        .TextboxTightWrap = wdTightNone
    End With
    ActiveDocument.Styles("TOC 4").NoSpaceBetweenParagraphsOfSameStyle = False
'
    With ActiveDocument.Styles("TOC 5").ParagraphFormat
        .LeftIndent = InchesToPoints(0.61)
        .RightIndent = InchesToPoints(0)
        .SpaceBefore = 0
        .SpaceBeforeAuto = False
        .SpaceAfter = 0
        .SpaceAfterAuto = False
        .LineSpacingRule = wdLineSpaceMultiple
        .LineSpacing = LinesToPoints(1.15)
        .Alignment = wdAlignParagraphLeft
        .WidowControl = True
        .KeepWithNext = False
        .KeepTogether = False
        .PageBreakBefore = False
        .NoLineNumber = False
        .Hyphenation = True
        .FirstLineIndent = InchesToPoints(0)
        .OutlineLevel = wdOutlineLevelBodyText
        .CharacterUnitLeftIndent = 0
        .CharacterUnitRightIndent = 0
        .CharacterUnitFirstLineIndent = 0
        .LineUnitBefore = 0
        .LineUnitAfter = 0
        .MirrorIndents = False
        .TextboxTightWrap = wdTightNone
    End With
    ActiveDocument.Styles("TOC 5").NoSpaceBetweenParagraphsOfSameStyle = False
'
    With ActiveDocument
        .TablesOfContents.Add Range:=Selection.Range, RightAlignPageNumbers:= _
            True, UseHeadingStyles:=True, UpperHeadingLevel:=1, _
            LowerHeadingLevel:=5, IncludePageNumbers:=True, AddedStyles:="", _
            UseHyperlinks:=True, HidePageNumbersInWeb:=True, UseOutlineLevels:= _
            True
        .TablesOfContents(1).TabLeader = wdTabLeaderDots
        .TablesOfContents.Format = wdIndexIndent
    End With
End Sub
Sub DeleteSubHeader()
'
' Delete Sub Header Macro to remove the second heading even if it's long
' and goes over multiple lines
'
Dim oRng As Range
With ActiveDocument
  Set oRng = .Paragraphs(2).Range
  oRng.End = .Paragraphs(2).Range.End
  oRng.Select
  oRng.Delete
End With
End Sub
Sub DeleteTypeAudience()
'
' DeleteTypeAudience Macro
'
' This macro deletes the second line of a document which proofed to be a problem
' in cases where the title spanned over multiple lines
' Replaced by DeleteSubHeader()
'
    Selection.MoveDown Unit:=wdLine, Count:=1
    Selection.MoveDown Unit:=wdLine, Count:=1, Extend:=wdExtend
    Selection.Delete Unit:=wdCharacter, Count:=1
    Selection.MoveUp Unit:=wdLine, Count:=1
    Selection.HomeKey Unit:=wdLine
    Selection.HomeKey Unit:=wdStory
End Sub
Sub DocumentArial()
'
' Macro to set the document font to Arial
'
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.HomeKey Unit:=wdStory
End Sub
Sub DocumentArial10pt()
'
' Macro to set the document font to Arial 10pt
'
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
End Sub
Sub DocumentArial12pt()
'
' Macro to set the document font to Arial, 12pt
'
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
End Sub
Sub FormatChanger()
'
' FormatChanger Macro
'
    Selection.Find.ClearFormatting
    With Selection.Find
        .Text = "[I]"
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = False
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
    Selection.Find.ClearFormatting
    With Selection.Find
        .Text = "[I]"
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = False
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
End Sub
Sub GoToEnd()
'
' GoToTop Macro
'
    Selection.EndOf Unit:=wdStory
End Sub
Sub GoToTop()
'
' GoToTop Macro
'
    Selection.HomeKey Unit:=wdStory
End Sub
Sub HeaderDate()
'
' HeaderDate Macro
'
'
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.InsertDateTime DateTimeFormat:="dddd, MMMM dd, yyyy", _
        InsertAsField:=False, DateLanguage:=wdEnglishUS, CalendarType:= _
        wdCalendarWestern, InsertAsFullWidth:=False
    Selection.HomeKey Unit:=wdLine
    With Selection.ParagraphFormat
        .LeftIndent = InchesToPoints(0)
        .RightIndent = InchesToPoints(0)
        .SpaceBefore = 0
        .SpaceBeforeAuto = False
        .SpaceAfter = 0
        .SpaceAfterAuto = False
        .LineSpacingRule = wdLineSpaceSingle
        .Alignment = wdAlignParagraphRight
        .WidowControl = True
        .KeepWithNext = False
        .KeepTogether = False
        .PageBreakBefore = False
        .NoLineNumber = False
        .Hyphenation = True
        .FirstLineIndent = InchesToPoints(0)
        .OutlineLevel = wdOutlineLevelBodyText
        .CharacterUnitLeftIndent = 0
        .CharacterUnitRightIndent = 0
        .CharacterUnitFirstLineIndent = 0
        .LineUnitBefore = 0
        .LineUnitAfter = 0
        .MirrorIndents = False
        .TextboxTightWrap = wdTightNone
    End With
End Sub
Sub HeaderFooter()
'
' HeaderFooter Macro (currently not used)
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
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
    
End Sub
Sub HeaderFooter10pt()
'
' Macro to add a date to the header and a page number to the footer
' using Arial, 10pt font
' The footer is added as a building block template that must exist
'
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
    Selection.Font.Size = 10
    Selection.ParagraphFormat.Alignment = wdAlignParagraphRight
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 10pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooter_RJ()
'
' HeaderFooter Macro
'
'
    ' Create the Header
    '
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:="Bold"
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:=" = Proposed text for review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
        
    ' Create the Footer
    '
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooter_Genetics()
'
' HeaderFooter Macro (copy of HeaderFooter_RJ)
'
'
    ' Create the Header
    '
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:="Bold"
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:=" = Proposed text for review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
        
    ' Create the Footer
    '
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooter_SQ()
'
' HeaderFooterAndText Macro
'
'
    ' Create the Header
    '
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:="Bold"
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:=" = Proposed changes for Ed. Bd. review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
        
    ' Create the Footer
    '
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooter_Pediatric()
'
' HeaderFooterAndText Macro (Copy of HeaderFooter_SQ)
'
'
    ' Create the Header
    '
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:="Bold"
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:=" = Proposed changes for Ed. Bd. review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
        
    ' Create the Footer
    '
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooterAndText_RJ()
'
' HeaderFooterAndText Macro (currently not used)
'
'
    ' Create the Header
    '
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:="Bold"
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:=" = Proposed text for review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
        
    ' Create the Footer
    '
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooterAndText_Genetics()
'
' HeaderFooterAndText Macro (currently not used) (Copy of HeaderFooterAndText_RJ)
'
'
    ' Create the Header
    '
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:="Bold"
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:=" = Proposed text for review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
        
    ' Create the Footer
    '
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooterAndText_SQ()
'
' HeaderFooterAndText Macro (currently not used)
'
'
    ' Create the Header
    '
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:="Bold"
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:=" = Proposed changes for Ed. Bd. review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
        
    ' Create the Footer
    '
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooterAndText_Pediatric()
'
' HeaderFooterAndText Macro (currently not used) (Copy of HeaderFooterAndText_SQ)
'
'
    ' Create the Header
    '
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 10
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:="Bold"
    Selection.Font.Bold = wdToggle
    Selection.TypeText Text:=" = Proposed changes for Ed. Bd. review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False
        
    ' Create the Footer
    '
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooterDateFmt()
'
' Macro to add a date to the header and a page number to the footer
' Special formatting for the date
'
    If ActiveWindow.View.SplitSpecial <> wdPaneNone Then
        ActiveWindow.Panes(2).Close
    End If
    If ActiveWindow.ActivePane.View.Type = wdNormalView Or ActiveWindow. _
        ActivePane.View.Type = wdOutlineView Then
        ActiveWindow.ActivePane.View.Type = wdPrintView
    End If
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageHeader
    Selection.InsertDateTime DateTimeFormat:="dddd, MMMM dd, yyyy", _
         InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
         InsertAsFullWidth:=False
    Selection.WholeStory
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 12
    Selection.ParagraphFormat.Alignment = wdAlignParagraphRight
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine

End Sub
Sub HeaderFooterDefault()
'
' Macro to add a date to the header and a page number to the footer
'
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
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
'    MsgBox "Done with Header"
    ActiveWindow.ActivePane.View.SeekView = wdSeekCurrentPageFooter
'    MsgBox "In Footer"
    Application.Templates("C:\CDR\WordStartup\CDR_Macros.dotm"). _
        BuildingBlockEntries("CDR Footer 12pt").Insert Where:=Selection.Range, _
        RichText:=True
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdStory
End Sub

'Sub Macro_DIS()
'
' Macro for Diana Blais (Copy of Marcro_DB)
'
' Christina Norwood is not using this macro. Therefore it does
' not need to be maintained anymore.
    ' Auto adjust table width
    'AutoFitTableWidth
    '
    ' Convert larger text to 12pt
    'ReduceLargerFontSize
    '
    ' Setting font to Arial
    'DocumentArial
    '
    ' Adding normal Header and Footer
    'HeaderFooterDefault
    '
    ' Removing the SummaryType and Audience
    'DeleteSubHeader
    '
    ' Removing the entire TOC List
    'RemoveTOCList
    '
    ' Change the font of the text to 11 pt
    ' ChangeFontSizeLoopTo11
    'ReplaceFontSize12to11
    '
    ' Setting the margins to 0.5 inches
    'MarginNarrow
' End Sub

Sub Macro_Genetics()
'
' Macro for Robin Juthe (Copy of Macro_RJ)
'
'
    ' Auto adjust table width
    AutoFitTableWidth
    
    ' Convert larger text to 12pt
    ReduceLargerFontSize
    
    ' Setting font to Arial
    DocumentArial
    
    ' Removing the Summary type and audience (the second paragraph)
    DeleteSubHeader
    
    ' Adding special Header and Footer
    HeaderFooter_Genetics
    
    ' Remove the TOC links and display in black w/o underline
    RemoveTOCHyperlinks
    
    ' Delete the Changes to This Summary section
    RemoveChangesSection
    
End Sub
Sub Macro_IACT()
'
' Macro for Robin Baldwin (Same as SupportiveCare)
'
    ' Auto adjust table width
    AutoFitTableWidth
    
    ' Convert larger text to 12pt
    ReduceLargerFontSize
    
    ' Setting font to Arial
    DocumentArial
    
    ' Adding normal Header and Footer
    HeaderFooterDefault
    
    ' Removing the entire TOC List and the Changes Section
    RemoveTOCListandChanges
        
End Sub
Sub Macro_Pediatric()
'
' Macro for Sharon Quint-Kaesner (Copy of Macro_SQ)
'
    ' Auto adjust table width
    AutoFitTableWidth
    
    ' Convert larger text to 12pt
    ReduceLargerFontSize
    
    ' Setting font to Arial
    DocumentArial
    
    ' Removing the Summary type and audience (the second paragraph)
    DeleteSubHeader
    
    ' Adding normal Header and Footer
    HeaderFooter_Pediatric
    
    ' Remove the TOC links and display in black w/o underline
    RemoveTOCHyperlinksNotBold
    
    ' Delete the Changes to This Summary Section
    RemoveChangesSection

End Sub
Sub Macro_Screening()
'
' Macro for Leshia Hansen (Copy of Macro_VD)
'
    ' Auto adjust table width
    AutoFitTableWidth
    
    ' Convert larger text to 12pt
    ReduceLargerFontSize
    
    ' Setting font to Arial
    DocumentArial
    
    ' Adding Header and Footer with special formatted date
    HeaderFooterDateFmt
    
    ' Removing the TOC Links
    RemoveTOCHyperlinks
    
End Sub
Sub Macro_SupportiveCare()
'
' Macro for Robin Baldwin (Same as IACT)
'
    ' Auto adjust table width
    AutoFitTableWidth
    
    ' Convert larger text to 12pt
    ReduceLargerFontSize
    
    ' Setting font to Arial
    DocumentArial
    
    ' Adding normal Header and Footer
    HeaderFooterDefault
    
    ' Removing the entire TOC List and the Changes Section
    RemoveTOCListandChanges
        
End Sub
Sub Macro_Treatment()
'
' Macro for Victoria Shields (Copy of Macro_VS)
'
    ' Change the font of the text to 10 pt
    ' ChangeFontSizeLoopTo10
    ReplaceFontSize12to10
    
    ' Auto adjust table width
    AutoFitTableWidth
    
    ' Convert larger text to 12pt
    ReduceLargerFontSize
    
    ' Setting font to Arial
    DocumentArial
    
    ' Removing the Summary type and audience (the second paragraph)
    DeleteSubHeader
    
    ' Adding special Header and Footer
    HeaderFooter10pt
    
    ' Removing the TOC Links
    RemoveTOCHyperlinks
    
    ' Delete the Changes to This Summary Section
    RemoveChangesSection
End Sub
Sub MarginNarrow()
'
' Margin Macro
'
'
    With Selection.PageSetup
        .LineNumbering.Active = False
        .Orientation = wdOrientPortrait
        .TopMargin = InchesToPoints(0.5)
        .BottomMargin = InchesToPoints(0.5)
        .LeftMargin = InchesToPoints(0.5)
        .RightMargin = InchesToPoints(0.5)
        .Gutter = InchesToPoints(0)
        .HeaderDistance = InchesToPoints(0.5)
        .FooterDistance = InchesToPoints(0.5)
        .PageWidth = InchesToPoints(8.5)
        .PageHeight = InchesToPoints(11)
        .FirstPageTray = wdPrinterDefaultBin
        .OtherPagesTray = wdPrinterDefaultBin
        .SectionStart = wdSectionNewPage
        .OddAndEvenPagesHeaderFooter = False
        .DifferentFirstPageHeaderFooter = False
        .VerticalAlignment = wdAlignVerticalTop
        .SuppressEndnotes = False
        .MirrorMargins = False
        .TwoPagesOnOne = False
        .BookFoldPrinting = False
        .BookFoldRevPrinting = False
        .BookFoldPrintingSheets = 1
        .GutterPos = wdGutterPosLeft
    End With
End Sub
Sub ReduceLargerFontSize()
'
' ReduceLargerFontSize Macro
'
'
    Selection.HomeKey Unit:=wdStory
    Selection.Find.ClearFormatting
    Selection.Find.Font.Size = 13.5
    Selection.Find.Replacement.ClearFormatting
    Selection.Find.Replacement.Font.Size = 12
    With Selection.Find
        .Text = ""
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = True
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute Replace:=wdReplaceAll
End Sub
Sub RemoveChangesSection()
'
' ChangesSection Macro
' (Remember: The text string appears as a header and a TOC entry
'
    Selection.HomeKey Unit:=wdStory
    Selection.Find.ClearFormatting
    With Selection.Find
        .Text = "Changes To This Summary"
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = False
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
    Selection.EndKey Unit:=wdLine, Extend:=wdExtend
    Selection.Delete Unit:=wdCharacter, Count:=1
    '
    Selection.Find.ClearFormatting
    With Selection.Find
        .Text = "Changes To This Summary"
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = False
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
    Selection.HomeKey Unit:=wdLine
    Selection.EndKey Unit:=wdStory, Extend:=wdExtend
    Selection.Delete Unit:=wdCharacter, Count:=1
    Selection.HomeKey Unit:=wdStory
End Sub
Sub RemoveTOCHyperlinks()
'
' Remove Hyperlinks from Table of Content for Summary
'
    Dim i As Long, myRange As Range, n As Long
    n = 0
    
    ' Start at the beginning of the document
    Selection.WholeStory
    Selection.Collapse     ' This sets the entry point to the beginning of the doc
    
    ' The TOC are links and have therefore a different color
    ' Move the selection point to the first occurrence of the link color
    ' and then move to the beginning of the line
    Selection.SelectCurrentColor
    Selection.Collapse (wdCollapseEnd)
    
    ' After this statement the entry point is at the beginning of the TOC list
    Selection.HomeKey Unit:=wdLine, Extend:=wdExtend
    Selection.Collapse
    
    ' Select the entire TOC and change the color to black
    Selection.SelectCurrentFont
    
    ' Removing the following statement in order to keep the colors for insertion/deletion markup
    ' Selection.Font.Color = wdColorBlack

    ' Remove the links from each entry, one at a time beginning from the end
    Set rng = Selection.Range
    
    For i = rng.Hyperlinks.Count To 1 Step -1
        With rng.Hyperlinks(i)
            Set myRange = .Range
            .Delete
        End With
    Next i
End Sub
Sub RemoveTOCHyperlinks_Old()
'
' Remove Hyperlinks from Table of Content for Summary
'
    Dim i As Long, myRange As Range, n As Long
    n = 0
    
    ' Step through all Hyperlinks on the document
    '      Note:  There is a problem with with approach.  VB Word renumbers the elements on
    '             the fly.  This means when given the links [1], [2], and [3], the first one
    '             will be modified but then - since [1] doesn't exist anymore - [2] is now [1].
    '             Updating the link [2] in the second iteration actually modifies link [3] of
    '             the original count.
    '             Typically, this can be handled by modifying the document from the bottom up but
    '             in our situation we need to modify *only* the first few top links.  Therefore,
    '             I'm resetting the counter and introduce a second counter to prevent an endless
    '             loop.
    For i = 1 To ActiveDocument.Hyperlinks.Count Step 1
        With ActiveDocument.Hyperlinks(i)
            ' This needs to be modified if the standard header for the section changes
            If Left(.TextToDisplay, 23) = "Changes to This Summary" Then
                Done = "Yes"
            End If
            
            Set myRange = .Range
            .Delete
            ' myRange.Style = wdStyleHyperlink  ' (keeping the style)
            
            ' Have we hit the last TOC item?  Then we're done.
            If Done = "Yes" Then
                Exit For
            End If
        End With
        
        ' Since we're resetting the counter we need to prevent an infinite loop
        n = n + 1
        If n > ActiveDocument.Hyperlinks.Count Then Exit For
        i = i - 1
    Next i
End Sub
Sub RemoveTOCHyperlinksNotBold()
'
' Remove Hyperlinks from Table of Content for Summary
'
    Dim i As Long, myRange As Range, n As Long
    n = 0
    
    ' Start at the beginning of the document
    Selection.WholeStory
    Selection.Collapse     ' This sets the entry point to the beginning of the doc
    
    ' The TOC are links and have therefore a different color
    ' Move the selection point to the first occurrence of the link color
    ' and then move to the beginning of the line
    Selection.SelectCurrentColor
    Selection.Collapse (wdCollapseEnd)
    
    ' After this statement the entry point is at the beginning of the TOC list
    Selection.HomeKey Unit:=wdLine, Extend:=wdExtend
    Selection.Collapse
    
    ' Select the entire TOC and change the color to black
    Selection.SelectCurrentFont
    Selection.Font.Color = wdColorBlack
    Selection.Font.Bold = wdToggle

    ' Remove the links from each entry, one at a time beginning from the end
    Set rng = Selection.Range
    
    For i = rng.Hyperlinks.Count To 1 Step -1
        With rng.Hyperlinks(i)
            Set myRange = .Range
            .Delete
        End With
    Next i
End Sub
Sub ReplaceTOCList()
'
' Replace TOC List
' First Remove old TOC, then create Word TOC with page numbers
'
     RemoveTOCList
     CreateWordToc
'     RemoveFirstTOCEntry
End Sub
Sub RemoveTOCList()
'
' RemoveTOCList Macro
'
'
    Selection.Find.ClearFormatting
    With Selection.Find
        .Text = "Changes to This Summary"
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = False
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
    Selection.MoveDown Unit:=wdLine, Count:=1
    '
    Selection.HomeKey Unit:=wdLine
    Selection.HomeKey Unit:=wdStory, Extend:=wdExtend
    Selection.MoveDown Unit:=wdLine, Count:=1, Extend:=wdExtend
    '
    ' Selection.MoveUp Unit:=wdScreen, Count:=2, Extend:=wdExtend
    ' Selection.MoveDown Unit:=wdLine, Count:=1, Extend:=wdExtend
    ' Selection.HomeKey Unit:=wdLine, Extend:=wdExtend
    Selection.Delete Unit:=wdCharacter, Count:=1
End Sub
Sub RemoveTOCListandChanges()
'
' RemoveTOCListandChanges Macro
'
'
    Selection.Find.ClearFormatting
' Find "Changes to this Summary" in the TOC
    With Selection.Find
        .Text = "Changes to This Summary"
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = False
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
' Place cursor to beginning of line and move back to top of document
    Selection.HomeKey Unit:=wdLine
    Selection.MoveDown Unit:=wdLine, Count:=1
    Selection.HomeKey Unit:=wdLine, Extend:=wdExtend
    Selection.HomeKey Unit:=wdStory, Extend:=wdExtend
' Move down to paragraphs and delete the remaining selection (TOC)
    Selection.MoveDown Unit:=wdParagraph, Count:=2, Extend:=wdExtend
    Selection.Delete Unit:=wdCharacter, Count:=1
    
' Remove the "Changes to This Summary" section at the bottom of the document
    Selection.Find.ClearFormatting
    With Selection.Find
        .Text = "Changes to This Summary"
        .Replacement.Text = ""
        .Forward = True
        .Wrap = wdFindContinue
        .Format = False
        .MatchCase = False
        .MatchWholeWord = False
        .MatchWildcards = False
        .MatchSoundsLike = False
        .MatchAllWordForms = False
    End With
    Selection.Find.Execute
    Selection.HomeKey Unit:=wdLine
    Selection.EndKey Unit:=wdStory, Extend:=wdExtend
    Selection.Delete Unit:=wdCharacter, Count:=1
    Selection.HomeKey Unit:=wdStory
End Sub
Sub RemoveFirstTOCEntry()
Attribute RemoveFirstTOCEntry.VB_ProcData.VB_Invoke_Func = "Project.NewMacros.RemoveFirstTOCEntry"
'
' RemoveFirstTOCEntry Macro
'
    Selection.HomeKey Unit:=wdStory
    Selection.MoveDown Unit:=wdLine, Count:=1
'    Selection.MoveRight Unit:=wdCharacter, Count:=9, Extend:=wdExtend
    Selection.EndKey Unit:=wdLine, Extend:=wdExtend
'    Selection.Delete Unit:=wdCharacter, Count:=1
End Sub
Sub ReplaceFontSize12to10()
'
' Find all text with FontSize 12pt and replace to 10pt
'
' This will replace the ChangeFontSizeLoop because it is a lot faster (order of magnitude)
'
     With Selection.Find
          .ClearFormatting
          .Font.Size = 12
          .Replacement.ClearFormatting
          .Replacement.Font.Size = 10
          .Execute Replace:=wdReplaceAll, Forward:=True
     End With
End Sub
Sub ReplaceFontSize12to11()
'
' Find all text with FontSize 12pt and replace to 11pt
'
' This will replace the ChangeFontSizeLoop because it is a lot faster (order of magnitude)
'
     With Selection.Find
          .ClearFormatting
          .Font.Size = 12
          .Replacement.ClearFormatting
          .Replacement.Font.Size = 11
          .Execute Replace:=wdReplaceAll, Forward:=True
     End With
End Sub

