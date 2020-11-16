#pragma once


// RevisionLevel dialog

class RevisionLevel : public CDialogEx
{
    DECLARE_DYNAMIC(RevisionLevel)

public:
    RevisionLevel(CWnd* parent = NULL);   // standard constructor
    virtual ~RevisionLevel();

// Dialog Data
    enum { IDD = IDD_REVISION_LEVEL };

protected:
    virtual void DoDataExchange(CDataExchange* dx);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    int m_revision_level;
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};
