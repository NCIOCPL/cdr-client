// CommentDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Cdr.h"
#include "CommentDialog.h"
#include "Commands.h"
#include "CdrUtil.h"


// CCommentDialog dialog

IMPLEMENT_DYNAMIC(CCommentDialog, CDialog)
CCommentDialog::CCommentDialog(BOOL ro /*=false*/, CWnd* pParent /*=NULL*/)
	: CDialog(CCommentDialog::IDD, pParent)
{
    readOnly = ro;
}

CCommentDialog::~CCommentDialog()
{
}

void CCommentDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMMENT_BOX, m_comment);
}


BEGIN_MESSAGE_MAP(CCommentDialog, CDialog)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCommentDialog message handlers

void CCommentDialog::OnBnClickedOk()
{
    if (!readOnly) {
        CString comment;
        m_comment.GetWindowText(comment);

        // Find the linking element.
        ::Range selection = cdr::getApp().GetSelection();
        ::DOMElement elem = selection.GetContainerNode();
        while (elem && elem.GetNodeType() != 1) // DOMElement
            elem = elem.GetParentNode();
        if (elem) {

            // Set the comment attribute.
            elem.setAttribute(_T("comment"), comment);
        }
    }
    OnOK();
}

BOOL CCommentDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Find the linking element.
    ::Range selection = cdr::getApp().GetSelection();
    ::DOMElement elem = selection.GetContainerNode();
    while (elem && elem.GetNodeType() != 1) // DOMElement
        elem = elem.GetParentNode();
    if (elem) {

        // Find the comment attribute.
        CString comment = elem.getAttribute(_T("comment"));
        m_comment.SetWindowText(comment);
        if (readOnly)
            m_comment.SetReadOnly();
    }

    return TRUE;
}
