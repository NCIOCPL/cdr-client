#pragma once
#include "afxwin.h"

#include "CdrUtil.h"

// CDiagnosisSets dialog

class CDiagnosisSets : public CDialog
{
    DECLARE_DYNAMIC(CDiagnosisSets)

public:
    CDiagnosisSets(const cdr::StringList& names, CWnd* pParent = NULL);
    virtual ~CDiagnosisSets();

// Dialog Data
    enum { IDD = IDD_INSERT_DIAGNOSIS_TERMS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

private:
    const cdr::StringList& setNames;
public:
    CButton m_cancelButton;
    CButton m_insertButton;
    CComboBox m_termSetControl;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    virtual BOOL OnInitDialog();
    CString chosenSetName;
};
