#if !defined(AFX_CHECKIN_H__33B239E9_9CA6_4516_B2D9_4470D42BBDBA__INCLUDED_)
#define AFX_CHECKIN_H__33B239E9_9CA6_4516_B2D9_4470D42BBDBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckIn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckIn dialog

class CCheckIn : public CDialog
{
// Construction
public:
    CCheckIn(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CCheckIn)
    enum { IDD = IDD_CHECK_IN };
    CString    m_comment;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCheckIn)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CCheckIn)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKIN_H__33B239E9_9CA6_4516_B2D9_4470D42BBDBA__INCLUDED_)
