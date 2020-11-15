// FindComments.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "FindComments.h"


// CFindComments dialog

IMPLEMENT_DYNAMIC(CFindComments, CDialog)
CFindComments::CFindComments(CWnd* pParent /*=NULL*/)
	: CDialog(CFindComments::IDD, pParent)
{
}

CFindComments::~CFindComments()
{
}

void CFindComments::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FIND_COMMENTS_NEXT, nextButton);
    DDX_Control(pDX, IDC_FIND_COMMENTS_PREV, prevButton);
}


BEGIN_MESSAGE_MAP(CFindComments, CDialog)
    ON_BN_CLICKED(IDC_FIND_COMMENTS_NEXT, OnBnClickedNextComment)
    ON_BN_CLICKED(IDC_FIND_COMMENTS_PREV, OnBnClickedPrevComment)
END_MESSAGE_MAP()


// CFindComments message handlers

void CFindComments::OnBnClickedNextComment() {
    findComment(true);
}

void CFindComments::OnBnClickedPrevComment() {
    findComment(false);
}

void CFindComments::findComment(bool forward) {
    _Application app = cdr::get_app();
    ::_Document doc = app.GetActiveDocument();
    ::Range element = doc.GetRange();
    CString name;
    CString value;
    int option = GetCheckedRadioButton(IDC_FIND_COMMENTS_ADVISORY,
                                       IDC_FIND_COMMENTS_PERMANENT);
    switch (option) {
    case IDC_FIND_COMMENTS_ADVISORY:
        name = L"source";
        value = L"advisory-board";
        break;
    case IDC_FIND_COMMENTS_INTERNAL:
        name = L"audience";
        value = L"Internal";
        break;
    case IDC_FIND_COMMENTS_EXTERNAL:
        name = L"audience";
        value = L"External";
        break;
    case IDC_FIND_COMMENTS_PERMANENT:
    default:
        name = L"duration";
        value = L"permanent";
        break;
    }
    bool keepGoing = true;
    while (keepGoing) {
        element.Collapse(1);
        BOOL foundComment = element.MoveToElement(L"Comment", forward);
        while (foundComment) {
            ::DOMElement e = element.GetContainerNode();
            CString v = e.getAttribute(name);
            if (v == value)
                break;
            element.Collapse(1);
            foundComment = element.MoveToElement(L"Comment", forward);
        }
        if (!foundComment) {
            CString prompt = L"End of document; wrap from top?";
            if (!forward)
                prompt = L"Beginning of document; wrap from bottom?";
            int answer = ::AfxMessageBox(prompt, MB_YESNO);
            keepGoing = answer == IDYES;
            if (keepGoing) {
                if (forward)
                    element.MoveToDocumentStart();
                else
                    element.MoveToDocumentEnd();
            }
        }
        else {
            keepGoing = false;
            element.SelectContainerContents();
            element.Select();
        }
    }
}

void CFindComments::OnOK() {
    this->DestroyWindow();
}

void CFindComments::OnCancel() {
    this->DestroyWindow();
}

void CFindComments::PostNcDestroy() {
    delete this;
}

BOOL CFindComments::OnInitDialog()
{
    CDialog::OnInitDialog();
    CheckRadioButton(IDC_FIND_COMMENTS_ADVISORY, IDC_FIND_COMMENTS_PERMANENT,
                     IDC_FIND_COMMENTS_ADVISORY);
    return TRUE;
}
