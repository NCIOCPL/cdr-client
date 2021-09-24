// ReviewMarkup.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "ReviewMarkup.h"
#include ".\reviewmarkup.h"


// CReviewMarkup dialog

IMPLEMENT_DYNAMIC(CReviewMarkup, CDialog)
CReviewMarkup::CReviewMarkup(CWnd* parent /*=NULL*/)
    : CDialog(CReviewMarkup::IDD, parent)
{
}

CReviewMarkup::~CReviewMarkup()
{
}

void CReviewMarkup::DoDataExchange(CDataExchange* dx)
{
    CDialog::DoDataExchange(dx);
    DDX_Control(dx, IDC_MARKUP_USER, markup_user);
    DDX_Control(dx, IDC_MARKUP_DATE, markup_date);
    DDX_Control(dx, IDC_MARKUP_CONTENT, markup_content);
    DDX_Control(dx, IDC_ACCEPT, accept_button);
    DDX_Control(dx, IDC_REJECT, reject_button);
    DDX_Control(dx, IDC_REVIEW_LEVEL, review_level);
    DDX_Control(dx, IDC_MARKUP_SOURCE, markup_source);
}


BEGIN_MESSAGE_MAP(CReviewMarkup, CDialog)
    ON_BN_CLICKED(IDC_NEXT_MARKUP, OnBnClickedNextMarkup)
    ON_BN_CLICKED(IDC_ACCEPT, OnBnClickedAccept)
    ON_BN_CLICKED(IDC_REJECT, OnBnClickedReject)
END_MESSAGE_MAP()


// CReviewMarkup message handlers

void CReviewMarkup::OnBnClickedNextMarkup()
{
    if (!find_next_markup() && false)
        EndDialog(IDCANCEL);
}

static CString extract_date(CString& date_time) {
    if (date_time.IsEmpty())
        return date_time;
    int comma = date_time.Find(L",");
    if (comma == -1)
        return date_time;
    comma = date_time.Find(L",", comma + 1);
    if (comma == -1)
        return date_time;
    return date_time.Left(comma + 6);
}

bool CReviewMarkup::find_next_markup() {
    bool result = true;
    _Application app = cdr::get_app();
    ::_Document doc = app.GetActiveDocument();
    ::Range del_elem = doc.GetRange();
    ::Range ins_elem = doc.GetRange();
    CString desired_level = L"approved";
    CString user = L"";
    CString date = L"";
    CString content = L"";
    CString markup_level = L"";
    CString markup_source_value = L"";
    int level_id = GetCheckedRadioButton(IDC_ALL, IDC_PROPOSED);
    switch (level_id) {
        case IDC_ALL: desired_level = L"all"; break;
        case IDC_PUBLISH: desired_level = L"publish"; break;
        case IDC_PROPOSED: desired_level = L"proposed"; break;
        default: desired_level = L"approved"; break;
    }
    BOOL keep_going = TRUE;
    while (keep_going) {
        del_elem.Collapse(1);
        ins_elem.Collapse(1);
        BOOL found_del = del_elem.MoveToElement(L"Deletion", TRUE);
        BOOL found_ins = ins_elem.MoveToElement(L"Insertion", TRUE);
        while (found_del && desired_level != L"all") {
            ::DOMElement e = del_elem.GetContainerNode();
            CString lvl = e.getAttribute(L"RevisionLevel");
            if (lvl == desired_level)
                break;
            del_elem.Collapse(1);
            found_del = del_elem.MoveToElement(L"Deletion", TRUE);
        }
        while (found_ins && desired_level != L"all") {
            ::DOMElement e = ins_elem.GetContainerNode();
            CString lvl = e.getAttribute(L"RevisionLevel");
            if (lvl == desired_level)
                break;
            ins_elem.Collapse(1);
            found_ins = ins_elem.MoveToElement(L"Insertion", TRUE);
        }
        if (!found_ins && !found_del) {
            int answer = ::AfxMessageBox(L"End of doc; start from top?", MB_YESNO);
            keep_going = answer == IDYES;
            if (keep_going) {
                del_elem.MoveToDocumentStart();
                ins_elem.MoveToDocumentStart();
            }
            else
                result = false;
        }
        else {
            keep_going = FALSE;
            ::Range* which_range = NULL;
            if (!found_del)
                which_range = &ins_elem;
            else if (!found_ins)
                which_range = &del_elem;
            else if (ins_elem.GetIsGreaterThan(del_elem, FALSE))
                which_range = &del_elem;
            else
                which_range = &ins_elem;
            which_range->SelectContainerContents();
            which_range->Select();
            ::DOMElement e = which_range->GetContainerNode();
            user = e.getAttribute(L"UserName");
            date = extract_date(e.getAttribute(L"Time"));
            markup_level = e.getAttribute(L"RevisionLevel");
            markup_source_value = e.getAttribute(L"Source");
            if (markup_source_value == L"advisory-board")
                markup_source_value = L"Advisory Board";
            else
                markup_source_value = L"Editorial Board";
            content = which_range->GetText();
            if (content.GetLength() > 25)
                content = content.Left(25) + L" ...";
        }
    }
    markup_user.SetWindowText(user);
    markup_date.SetWindowText(date);
    markup_source.SetWindowText(markup_source_value);
    markup_content.SetWindowText(content);
    review_level.SetWindowText(markup_level);
    accept_button.EnableWindow(result);
    reject_button.EnableWindow(result);
    return result;
}

BOOL CReviewMarkup::OnInitDialog()
{
    CDialog::OnInitDialog();
    CheckRadioButton(IDC_ALL, IDC_PROPOSED, IDC_APPROVED);
    this->markup_user.SetWindowText(L"");
    this->markup_date.SetWindowText(L"");
    this->markup_content.SetWindowText(L"");
    this->review_level.SetWindowText(L"");
    this->markup_source.SetWindowText(L"");
    this->accept_button.EnableWindow(FALSE);
    this->reject_button.EnableWindow(FALSE);
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
    CString elem_name = range.GetElementName(0);
    if (elem_name == L"Insertion")
        range.RemoveContainerTags();
    else if (elem_name == L"Deletion") {
        range.SelectContainerContents();
        range.Delete();
        range.RemoveContainerTags();
    }
    find_next_markup();
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
    CString elem_name = range.GetElementName(0);
    if (elem_name == L"Deletion")
        range.RemoveContainerTags();
    else if (elem_name == L"Insertion") {
        range.SelectContainerContents();
        range.Delete();
        range.RemoveContainerTags();
    }
    find_next_markup();
}
