#pragma once


// RevisionLevel dialog

class RevisionLevel : public CDialogEx
{
    DECLARE_DYNAMIC(RevisionLevel)

public:
    RevisionLevel(CWnd* pParent = NULL);   // standard constructor
    virtual ~RevisionLevel();

// Dialog Data
    enum { IDD = IDD_REVISION_LEVEL };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    int mRevisionLevel;
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};
