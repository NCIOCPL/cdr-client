// CDRLoaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDRLoader.h"
#include "CDRLoaderDlg.h"
#include "CDRSocket.h"
#include "CDRGenerics.h"
#include "CDROptions2.h"
#include "CDRIniData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCDRLoaderDlg dialog



CCDRLoaderDlg::CCDRLoaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDRLoaderDlg::IDD, pParent)
	, UserId(_T(""))
	, UserPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_XM_ICON);
	ini_Data = NULL;
}

void CCDRLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, UserIdEdit, UserId);
	DDX_Text(pDX, UserPwdEdit, UserPwd);
	DDX_Control(pDX, UserIdEdit, UserIDControl);
	DDX_Control(pDX, UserPwdEdit, PwdControl);
}

BEGIN_MESSAGE_MAP(CCDRLoaderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_OPTIONS, OnBnClickedOptions)
END_MESSAGE_MAP()


// CCDRLoaderDlg message handlers

BOOL CCDRLoaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if ( UserId.GetLength() > 0 )
	{
		PwdControl.SetFocus();
	}
	else
	{
		UserIDControl.SetFocus();
	}
	
	// make sure we have the current data
	CDataExchange dx( this, false );
	DoDataExchange( &dx );

	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CCDRLoaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCDRLoaderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCDRLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCDRLoaderDlg::OnBnClickedOk()
{
	// make sure we have the current data
	CDataExchange dx( this, true );
	DoDataExchange( &dx );

	//	User said OK, try to login
	// Create the logon command.
	CString request = _T("<CdrLogon><UserName>")
						+ UserId 
						+ _T("</UserName><Password>")
						+ UserPwd
						+ _T("</Password></CdrLogon>");

	// where to go for the cdr stuff
	CdrSocket::SetServer( ini_Data->cdr_Server, ini_Data->cdr_Port );

	// Submit the command to the CDR server.
	CString response = CdrSocket::sendCommand(request);
	CString err;
	if ( ! response.IsEmpty() ) 
	{
		TinyXmlParser p(response);
		CdrSocket::setSessionString( p.extract(_T("SessionId")));
		SessionId = CdrSocket::getSessionString();
		if ( ! CdrSocket::loggedOn() ) 
		{
			err = p.extract(_T("Err"));
			// err = "Unable to link CDRClient dll, test stubs still in place.";
			if (err.IsEmpty())
			{
				err = _T("Unknown failure logging on to the CDR");
			}
		}
		else
		{
			// only do this if we login successfully
			OnOK();
		}
	}
	else
	{
		err = _T("No response from CDR Server, unable to login");
	}

	if ( ! err.IsEmpty() )
	{
		::AfxMessageBox(err, MB_ICONEXCLAMATION);
	}
}

void CCDRLoaderDlg::OnBnClickedOptions()
{
	// TODO: Add your control notification handler code here
	CDROptions	opt_dialog;

	opt_dialog.ticket_Server = ini_Data->ticket_Server;
	opt_dialog.ticket_Port = ini_Data->ticket_Port;
	opt_dialog.cdr_Server = ini_Data->cdr_Server;
	opt_dialog.cdr_Port = ini_Data->cdr_Port;

	INT_PTR nResponse = opt_dialog.DoModal();

	if (nResponse == IDOK)
	{
		// save the user options
		ini_Data->ticket_Server = opt_dialog.ticket_Server;
		ini_Data->ticket_Port = opt_dialog.ticket_Port;
		ini_Data->cdr_Server = opt_dialog.cdr_Server;
		ini_Data->cdr_Port = opt_dialog.cdr_Port;
	}
}
