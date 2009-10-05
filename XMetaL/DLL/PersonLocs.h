#if !defined(AFX_PERSONLOCS_H__603E33AD_F730_49A1_832E_1188F4F5C43F__INCLUDED_)
#define AFX_PERSONLOCS_H__603E33AD_F730_49A1_832E_1188F4F5C43F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonLocs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonLocs dialog

class CPersonLocs : public CDialog
{
// Construction
public:
	CPersonLocs(const CString& docId, CString& newTarg, 
                bool ppOnly = false,
                CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPersonLocs)
	enum { IDD = IDD_PERSON_LOCS };
	CListBox	m_choiceList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonLocs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPersonLocs)
	afx_msg void OnDblclkList1();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CString docId;
    cdr::DocSet docSet;
    CString& newTarget;
    void extractChoices(const CString&);
    bool privatePracticeOnly;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONLOCS_H__603E33AD_F730_49A1_832E_1188F4F5C43F__INCLUDED_)
