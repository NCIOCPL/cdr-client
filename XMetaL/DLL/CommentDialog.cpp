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
CCommentDialog::CCommentDialog(BOOL ro /*=false*/, CWnd* parent /*=NULL*/)
    : CDialog(CCommentDialog::IDD, parent)
{
    read_only = ro;
}

CCommentDialog::~CCommentDialog()
{
}

void CCommentDialog::DoDataExchange(CDataExchange* dx)
{
    CDialog::DoDataExchange(dx);
    DDX_Control(dx, IDC_COMMENT_BOX, m_comment);
}


BEGIN_MESSAGE_MAP(CCommentDialog, CDialog)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCommentDialog message handlers

void CCommentDialog::OnBnClickedOk()
{
    if (!read_only) {
        CString comment;
        m_comment.GetWindowText(comment);

        // Find the linking element.
        ::Range selection = cdr::get_app().GetSelection();
        ::DOMElement elem = selection.GetContainerNode();
        while (elem && elem.GetNodeType() != 1) // DOMElement
            elem = elem.GetParentNode();
        if (elem) {

            // Set the comment attribute.
            elem.setAttribute(L"comment", comment);
        }
    }
    OnOK();
}

BOOL CCommentDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Find the linking element.
    ::Range selection = cdr::get_app().GetSelection();
    ::DOMElement elem = selection.GetContainerNode();
    while (elem && elem.GetNodeType() != 1) // DOMElement
        elem = elem.GetParentNode();
    if (elem) {

        // Find the comment attribute.
        CString comment = elem.getAttribute(L"comment");
        m_comment.SetWindowText(comment);
        if (read_only)
            m_comment.SetReadOnly();
    }

    return TRUE;
}
