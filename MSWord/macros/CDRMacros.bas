Attribute VB_Name = "CDRMacros"
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
Sub ChangeFontSize()
'
' ChangeFontSize Macro
'
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
Sub ChangeFontSizeLoop()
'
' ChangeFontSize Macro
'
' Searching for any text that's 12pt and changing it to 10pt throughout
' the document.
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
    Selection.Font.Size = 10
    Next i
End With

Selection.HomeKey Unit:=wdStory

End Sub
Sub DeleteTypeAudience()
'
' DeleteTypeAudience Macro
'
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
Attribute FormatChanger.VB_ProcData.VB_Invoke_Func = "Normal.NewMacros.FormatChanger"
'
' FormatChanger Macro
'
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
Sub GoToTop()
'
' GoToTop Macro
'
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
Sub HeaderFooter10pt()
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
    Selection.Font.Size = 10
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
    Selection.Font.Size = 10
    ActiveWindow.ActivePane.View.SeekView = wdSeekMainDocument
    Selection.HomeKey Unit:=wdLine
End Sub
Sub HeaderFooterAndText_RH()
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
    Selection.TypeText Text:=" = Proposed text for review" & vbTab & vbTab
    Selection.Font.Size = 12
    Selection.InsertDateTime DateTimeFormat:="M/d/yyyy", InsertAsField:=False, _
         DateLanguage:=wdEnglishUS, CalendarType:=wdCalendarWestern, _
        InsertAsFullWidth:=False

    ' Create the Footer
    '
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
Sub HeaderFooterAndText_SQ()
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
Sub Macro_DB()
'
' Macro for Diana Blais
'
    ' Setting font to Arial
    DocumentArial
    ' Adding normal Header and Footer
    HeaderFooterDefault
    ' Removing the SummaryType and Audience
    DeleteTypeAudience
    ' Removing the entire TOC List
    RemoveTOCList
    ' Setting the margins to 0.5 inches
    MarginNarrow
End Sub
Sub Macro_RB()
'
' Macro for Robin Baldwin
'
    ' Setting font to Arial
    DocumentArial

    ' Adding normal Header and Footer
    HeaderFooterDefault

    ' Removing the entire TOC List and the Changes Section
    RemoveTOCListandChanges

End Sub
Sub Macro_RH()
'
' Macro for Robin Harrison
'
'
    ' Setting font to Arial
    DocumentArial

    ' Removing the Summary type and audience
    DeleteTypeAudience

    ' Remove the TOC links and display in black w/o underline
    RemoveTOCHyperlinks

    ' Adding normal Header and Footer
    HeaderFooterAndText_RH

    ' Delete the Changes to This Summary section
    RemoveChangesSection

End Sub
Sub Macro_SQ()
'
' Macro for Sharon Quint-Kaesner
'
    ' Setting font to Arial
    DocumentArial
    ' Removing the TOC Links
    DeleteTypeAudience
    '
    RemoveTOCHyperlinksNotBold
    ' Adding normal Header and Footer
    HeaderFooterAndText_SQ
    '
    RemoveChangesSection
End Sub
Sub Macro_VD()
'
' Macro for Valerie Dyer
'
    ' Setting font to Arial
    DocumentArial
    ' Adding Header and Footer with special formatted date
    HeaderFooterDateFmt
    ' Removing the TOC Links
    RemoveTOCHyperlinks
End Sub
Sub Macro_VS()
'
' Macro for Victoria Shields
'
    ' Setting font to Arial
    DocumentArial
    ' Removing the TOC Links
    HeaderFooter10pt
    ' Removing the SummaryType and Audience
    DeleteTypeAudience
    RemoveTOCHyperlinks
    RemoveChangesSection
    ChangeFontSizeLoop
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
Sub RemoveChangesSection()
'
' ChangesSection Macro
'
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
    Selection.Font.Color = wdColorBlack

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
Sub RemoveTOCList()
Attribute RemoveTOCList.VB_ProcData.VB_Invoke_Func = "Normal.NewMacros.Macro2"
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
    Selection.MoveUp Unit:=wdScreen, Count:=2, Extend:=wdExtend
    Selection.MoveDown Unit:=wdLine, Count:=1, Extend:=wdExtend
    Selection.HomeKey Unit:=wdLine, Extend:=wdExtend
    Selection.Delete Unit:=wdCharacter, Count:=1
End Sub
Sub RemoveTOCListandChanges()
Attribute RemoveTOCListandChanges.VB_ProcData.VB_Invoke_Func = "Normal.NewMacros.RemoveTOCListandChanges2"
'
' RemoveTOCListandChanges Macro
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
    Selection.HomeKey Unit:=wdLine
    Selection.MoveDown Unit:=wdLine, Count:=1
    Selection.HomeKey Unit:=wdLine, Extend:=wdExtend
    Selection.HomeKey Unit:=wdLine, Extend:=wdExtend
    Selection.HomeKey Unit:=wdStory, Extend:=wdExtend
    Selection.MoveDown Unit:=wdLine, Count:=2, Extend:=wdExtend
    Selection.Delete Unit:=wdCharacter, Count:=1
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
