// FindMarkup.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "FindMarkup.h"


// CFindMarkup dialog

IMPLEMENT_DYNAMIC(CFindMarkup, CDialog)
CFindMarkup::CFindMarkup(CWnd* parent /*=NULL*/)
    : CDialog(CFindMarkup::IDD, parent)
{
}

CFindMarkup::~CFindMarkup()
{
}

void CFindMarkup::DoDataExchange(CDataExchange* dx)
{
    CDialog::DoDataExchange(dx);
    // DDX_Control(dx, IDC_MARKUP_CONTENT, markup_content);
    DDX_Control(dx, IDC_FIND_MARKUP_NEXT, next_button);
    DDX_Control(dx, IDC_FIND_MARKUP_PREV, prev_button);
}


BEGIN_MESSAGE_MAP(CFindMarkup, CDialog)
    ON_BN_CLICKED(IDC_FIND_MARKUP_NEXT, OnBnClickedNextMarkup)
    ON_BN_CLICKED(IDC_FIND_MARKUP_PREV, OnBnClickedPrevMarkup)
END_MESSAGE_MAP()


// CFindMarkup message handlers

void CFindMarkup::OnBnClickedNextMarkup() {
    find_markup(true);
}

void CFindMarkup::OnBnClickedPrevMarkup() {
    find_markup(false);
}

void CFindMarkup::find_markup(bool forward) {
    _Application app = cdr::get_app();
    ::_Document doc = app.GetActiveDocument();
    ::Range del_elem = doc.GetRange();
    ::Range ins_elem = doc.GetRange();
    CString desired_level = L"approved";
    int level_id = GetCheckedRadioButton(IDC_FIND_MARKUP_PUBLISH,
                                        IDC_FIND_MARKUP_PROPOSED);
    switch (level_id) {
        case IDC_FIND_MARKUP_PUBLISH: desired_level = L"publish"; break;
        case IDC_FIND_MARKUP_PROPOSED: desired_level = L"proposed"; break;
        default: desired_level = L"approved"; break;
    }
    bool keep_going = true;
    while (keep_going) {
        del_elem.Collapse(1);
        ins_elem.Collapse(1);
        BOOL found_del = del_elem.MoveToElement(L"Deletion", forward);
        BOOL found_ins = ins_elem.MoveToElement(L"Insertion", forward);
        while (found_del) {
            ::DOMElement e = del_elem.GetContainerNode();
            CString level = e.getAttribute(L"RevisionLevel");
            if (level == desired_level)
                break;
            del_elem.Collapse(1);
            found_del = del_elem.MoveToElement(L"Deletion", forward);
        }
        while (found_ins) {
            ::DOMElement e = ins_elem.GetContainerNode();
            CString level = e.getAttribute(L"RevisionLevel");
            if (level == desired_level)
                break;
            ins_elem.Collapse(1);
            found_ins = ins_elem.MoveToElement(L"Insertion", forward);
        }
        if (!found_ins && !found_del) {
            CString prompt = L"End of document; wrap from top?";
            if (!forward)
                prompt = L"Beginning of document; wrap from bottom?";
            int answer = ::AfxMessageBox(prompt, MB_YESNO);
            keep_going = answer == IDYES;
            if (keep_going) {
                if (forward) {
                    del_elem.MoveToDocumentStart();
                    ins_elem.MoveToDocumentStart();
                }
                else {
                    del_elem.MoveToDocumentEnd();
                    ins_elem.MoveToDocumentEnd();
                }
            }
        }
        else {
            keep_going = false;
            ::Range* which_range = &ins_elem;
            if (!found_ins)
                which_range = &del_elem;
            else if (found_del) {
                if (forward && ins_elem.GetIsGreaterThan(del_elem, FALSE))
                    which_range = &del_elem;
                else if (!forward && del_elem.GetIsGreaterThan(ins_elem, FALSE))
                    which_range = &del_elem;
            }
            which_range->SelectContainerContents();
            which_range->Select();
        }
    }
}

void CFindMarkup::OnOK() {
    this->DestroyWindow();
}

void CFindMarkup::OnCancel() {
    this->DestroyWindow();
}

void CFindMarkup::PostNcDestroy() {
    delete this;
}

BOOL CFindMarkup::OnInitDialog()
{
    CDialog::OnInitDialog();
    CheckRadioButton(IDC_FIND_MARKUP_PUBLISH, IDC_FIND_MARKUP_PROPOSED,
                     IDC_FIND_MARKUP_APPROVED);
    return TRUE;
}
