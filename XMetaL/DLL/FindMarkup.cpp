// FindMarkup.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "FindMarkup.h"


// CFindMarkup dialog

IMPLEMENT_DYNAMIC(CFindMarkup, CDialog)
CFindMarkup::CFindMarkup(CWnd* pParent /*=NULL*/)
	: CDialog(CFindMarkup::IDD, pParent)
{
}

CFindMarkup::~CFindMarkup()
{
}

void CFindMarkup::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    // DDX_Control(pDX, IDC_MARKUP_CONTENT, markupContent);
    DDX_Control(pDX, IDC_FIND_MARKUP_NEXT, nextButton);
    DDX_Control(pDX, IDC_FIND_MARKUP_PREV, prevButton);
}


BEGIN_MESSAGE_MAP(CFindMarkup, CDialog)
    ON_BN_CLICKED(IDC_FIND_MARKUP_NEXT, OnBnClickedNextMarkup)
    ON_BN_CLICKED(IDC_FIND_MARKUP_PREV, OnBnClickedPrevMarkup)
END_MESSAGE_MAP()


// CFindMarkup message handlers

void CFindMarkup::OnBnClickedNextMarkup() {
    findMarkup(true);
}

void CFindMarkup::OnBnClickedPrevMarkup() {
    findMarkup(false);
}

void CFindMarkup::findMarkup(bool forward) {
    _Application app = cdr::get_app();
    ::_Document doc = app.GetActiveDocument();
    ::Range delElem = doc.GetRange();
    ::Range insElem = doc.GetRange();
    CString desiredLevel = L"approved";
    int levelId = GetCheckedRadioButton(IDC_FIND_MARKUP_PUBLISH,
                                        IDC_FIND_MARKUP_PROPOSED);
    switch (levelId) {
        case IDC_FIND_MARKUP_PUBLISH: desiredLevel = L"publish"; break;
        case IDC_FIND_MARKUP_PROPOSED: desiredLevel = L"proposed"; break;
        default: desiredLevel = L"approved"; break;
    }
    bool keepGoing = true;
    while (keepGoing) {
        delElem.Collapse(1);
        insElem.Collapse(1);
        BOOL foundDel = delElem.MoveToElement(L"Deletion", forward);
        BOOL foundIns = insElem.MoveToElement(L"Insertion", forward);
        while (foundDel) {
            ::DOMElement e = delElem.GetContainerNode();
            CString level = e.getAttribute(L"RevisionLevel");
            if (level == desiredLevel)
                break;
            delElem.Collapse(1);
            foundDel = delElem.MoveToElement(L"Deletion", forward);
        }
        while (foundIns) {
            ::DOMElement e = insElem.GetContainerNode();
            CString level = e.getAttribute(L"RevisionLevel");
            if (level == desiredLevel)
                break;
            insElem.Collapse(1);
            foundIns = insElem.MoveToElement(L"Insertion", forward);
        }
        if (!foundIns && !foundDel) {
            CString prompt = L"End of document; wrap from top?";
            if (!forward)
                prompt = L"Beginning of document; wrap from bottom?";
            int answer = ::AfxMessageBox(prompt, MB_YESNO);
            keepGoing = answer == IDYES;
            if (keepGoing) {
                if (forward) {
                    delElem.MoveToDocumentStart();
                    insElem.MoveToDocumentStart();
                }
                else {
                    delElem.MoveToDocumentEnd();
                    insElem.MoveToDocumentEnd();
                }
            }
        }
        else {
            keepGoing = false;
            ::Range* whichRange = &insElem;
            if (!foundIns)
                whichRange = &delElem;
            else if (foundDel) {
                if (forward && insElem.GetIsGreaterThan(delElem, FALSE))
                    whichRange = &delElem;
                else if (!forward && delElem.GetIsGreaterThan(insElem, FALSE))
                    whichRange = &delElem;
            }
            whichRange->SelectContainerContents();
            whichRange->Select();
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
