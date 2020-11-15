// ReviewMarkup.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "ReviewMarkup.h"
#include ".\reviewmarkup.h"


// CReviewMarkup dialog

IMPLEMENT_DYNAMIC(CReviewMarkup, CDialog)
CReviewMarkup::CReviewMarkup(CWnd* pParent /*=NULL*/)
	: CDialog(CReviewMarkup::IDD, pParent)
{
}

CReviewMarkup::~CReviewMarkup()
{
}

void CReviewMarkup::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MARKUP_USER, markupUser);
    DDX_Control(pDX, IDC_MARKUP_DATE, markupDate);
    DDX_Control(pDX, IDC_MARKUP_CONTENT, markupContent);
    DDX_Control(pDX, IDC_ACCEPT, acceptButton);
    DDX_Control(pDX, IDC_REJECT, rejectButton);
    DDX_Control(pDX, IDC_REVIEW_LEVEL, reviewLevel);
    DDX_Control(pDX, IDC_MARKUP_SOURCE, markupSource);
}


BEGIN_MESSAGE_MAP(CReviewMarkup, CDialog)
    ON_BN_CLICKED(IDC_NEXT_MARKUP, OnBnClickedNextMarkup)
    ON_BN_CLICKED(IDC_ACCEPT, OnBnClickedAccept)
    ON_BN_CLICKED(IDC_REJECT, OnBnClickedReject)
END_MESSAGE_MAP()


// CReviewMarkup message handlers

void CReviewMarkup::OnBnClickedNextMarkup()
{
    if (!findNextMarkup() && false)
        EndDialog(IDCANCEL);
}

static CString extractDate(CString& dateTime) {
    if (dateTime.IsEmpty())
        return dateTime;
    int comma = dateTime.Find(L",");
    if (comma == -1)
        return dateTime;
    comma = dateTime.Find(L",", comma + 1);
    if (comma == -1)
        return dateTime;
    return dateTime.Left(comma + 6);
}

bool CReviewMarkup::findNextMarkup() {
    bool result = true;
    _Application app = cdr::get_app();
    ::_Document doc = app.GetActiveDocument();
    ::Range delElem = doc.GetRange();
    ::Range insElem = doc.GetRange();
    CString desiredLevel = L"approved";
    CString user = L"";
    CString date = L"";
    CString content = L"";
    CString markupLevel = L"";
    CString markupSourceValue = L"";
    int levelId = GetCheckedRadioButton(IDC_ALL, IDC_PROPOSED);
    switch (levelId) {
        case IDC_ALL: desiredLevel = L"all"; break;
        case IDC_PUBLISH: desiredLevel = L"publish"; break;
        case IDC_PROPOSED: desiredLevel = L"proposed"; break;
        default: desiredLevel = L"approved"; break;
    }
    BOOL keepGoing = TRUE;
    while (keepGoing) {
        delElem.Collapse(1);
        insElem.Collapse(1);
        BOOL foundDel = delElem.MoveToElement(L"Deletion", TRUE);
        BOOL foundIns = insElem.MoveToElement(L"Insertion", TRUE);
        while (foundDel && desiredLevel != L"all") {
            ::DOMElement e = delElem.GetContainerNode();
            CString lvl = e.getAttribute(L"RevisionLevel");
            if (lvl == desiredLevel)
                break;
            delElem.Collapse(1);
            foundDel = delElem.MoveToElement(L"Deletion", TRUE);
        }
        while (foundIns && desiredLevel != L"all") {
            ::DOMElement e = insElem.GetContainerNode();
            CString lvl = e.getAttribute(L"RevisionLevel");
            if (lvl == desiredLevel)
                break;
            insElem.Collapse(1);
            foundIns = insElem.MoveToElement(L"Insertion", TRUE);
        }
        if (!foundIns && !foundDel) {
            int answer = ::AfxMessageBox(L"End of doc; start from top?", MB_YESNO);
            keepGoing = answer == IDYES;
            if (keepGoing) {
                delElem.MoveToDocumentStart();
                insElem.MoveToDocumentStart();
            }
            else
                result = false;
        }
        else {
            keepGoing = FALSE;
            ::Range* whichRange = NULL;
            if (!foundDel)
                whichRange = &insElem;
            else if (!foundIns)
                whichRange = &delElem;
            else if (insElem.GetIsGreaterThan(delElem, FALSE))
                whichRange = &delElem;
            else
                whichRange = &insElem;
            whichRange->SelectContainerContents();
            whichRange->Select();
            ::DOMElement e = whichRange->GetContainerNode();
            user = e.getAttribute(L"UserName");
            date = extractDate(e.getAttribute(L"Time"));
            markupLevel = e.getAttribute(L"RevisionLevel");
            markupSourceValue = e.getAttribute(L"Source");
            if (markupSourceValue == L"advisory-board")
                markupSourceValue = L"Advisory Board";
            else
                markupSourceValue = L"Editorial Board";
            content = whichRange->GetText();
            if (content.GetLength() > 25)
                content = content.Left(25) + L" ...";
        }
    }
    markupUser.SetWindowText(user);
    markupDate.SetWindowText(date);
    markupSource.SetWindowText(markupSourceValue);
    markupContent.SetWindowText(content);
    reviewLevel.SetWindowText(markupLevel);
    acceptButton.EnableWindow(result);
    rejectButton.EnableWindow(result);
    return result;
}

BOOL CReviewMarkup::OnInitDialog()
{
    CDialog::OnInitDialog();
    CheckRadioButton(IDC_ALL, IDC_PROPOSED, IDC_APPROVED);
    this->markupUser.SetWindowText(L"");
    this->markupDate.SetWindowText(L"");
    this->markupContent.SetWindowText(L"");
    this->reviewLevel.SetWindowText(L"");
    this->markupSource.SetWindowText(L"");
    this->acceptButton.EnableWindow(FALSE);
    this->rejectButton.EnableWindow(FALSE);
    return TRUE;
}

//----------------------------------------------------------------------
// Incorporates the current marked change i.e. if the selection is inside
// an Insertion the contents are merged and if inside an Deletion the
// contents are deleted.
//----------------------------------------------------------------------
void CReviewMarkup::OnBnClickedAccept()
{
    _Application app = cdr::get_app();
    ::_Document doc = app.GetActiveDocument();
    ::Range range = doc.GetRange();
    CString elemName = range.GetElementName(0);
    if (elemName == L"Insertion")
        range.RemoveContainerTags();
    else if (elemName == L"Deletion") {
        range.SelectContainerContents();
        range.Delete();
        range.RemoveContainerTags();
    }
    findNextMarkup();
}

//----------------------------------------------------------------------
// Rejects the current marked change i.e. if the selection is inside an
// Insertion the contents are removed and if the contents are inside an
// Deletion they are merged back with the document.
//----------------------------------------------------------------------
void CReviewMarkup::OnBnClickedReject()
{
    _Application app = cdr::get_app();
    ::_Document doc = app.GetActiveDocument();
    ::Range range = doc.GetRange();
    CString elemName = range.GetElementName(0);
    if (elemName == L"Deletion")
        range.RemoveContainerTags();
    else if (elemName == L"Insertion") {
        range.SelectContainerContents();
        range.Delete();
        range.RemoveContainerTags();
    }
    findNextMarkup();
}
