// CDRLoader.cpp : Defines the class behaviors for the application.
//

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "stdafx.h"

#include "CDRLoader.h"
#include "CDRLoaderDlg.h"
#include "CDRTicketStub.h"
#include "DRProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCDRLoaderApp

BEGIN_MESSAGE_MAP(CCDRLoaderApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCDRLoaderApp construction

CCDRLoaderApp::CCDRLoaderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCDRLoaderApp object

CCDRLoaderApp theApp;


// CCDRLoaderApp initialization

BOOL CCDRLoaderApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		//AfxMessageBox"Unable to access socket library");
		return FALSE;
	}

	AfxEnableControlContainer();

	// process command line values
	//	m_lpCmdLine
	CString manifest_directory = _T( ".\\" );
	CString	manifest_filename = _T( "CDR_MANIFEST.XML" );
	CString cdr_application = _T( "C:\\Program Files\\SoftQuad\\Xmetal 3\\xmetal3.exe" );
    if (m_lpCmdLine[0] != _T('\0'))
    {
		// user specified the manifest file to use
		CString cmd_line = m_lpCmdLine;
		
		CString space = _T( " " );
		CString quote = _T( "\"" );
		CString trash;
		int pos = 0;
		CString cur_token = cmd_line.Tokenize( space, pos );
		while ( cur_token != "" )
		{
			// if it doesn't start with a flag skip it
			if ( cur_token[ 0 ] == '-' )
			{
				TCHAR flag = cur_token[ 1 ];

				if ( cmd_line [ pos ] == '\"' )
				{
					cur_token = cmd_line.Tokenize( quote, pos );
				}
				else
				{
					cur_token = cmd_line.Tokenize( space, pos );
				}

				switch ( flag )
				{
					case 'M':
					case 'm':
					{
						manifest_filename = cur_token;
					}
					break;

					case 'A':
					case 'a':
					{
						cdr_application =  cur_token;
					}
					break;

					case 'D':
					case 'd':
					{
						manifest_directory = cur_token;
					}
					break;
				}
			}
			cur_token = cmd_line.Tokenize( space, pos );
		}
    }


	/****
	*	!STUPID WINDOWS!
	*	Harumph.  It seems that if I have an app that has a dialog as it's
	*	main window, other functions don't work when that window isn't visible
	*	in this case the problem child is the AtxMessage box I need to display
	*	when an error prevents launching.
	*	In order to get this to work, there needs to be an invisible (ie. off screen)
	*	disabled window (to provide a home for the message pump I guess)
	*	hence I get to create this little dummy window.
	****/
	CWnd * dummy_win = new CWnd();
    dummy_win->CreateEx( WS_EX_TOOLWINDOW, _T("STATIC"), _T("Hidden"), WS_DISABLED, -10, -10, 0, 0, NULL, NULL );

	CCDRLoaderDlg dlg;
	m_pMainWnd = dummy_win;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		bool	ok_to_launch = false;
		CString	err = _T("Unknown error.");

		CDRTicketStub ticket_stub;

		CString uid = dlg.UserId;
		CString key = dlg.SessionId;
		if ( true )
		{
			ticket_stub.InitializeFileLocation( manifest_directory + manifest_filename );
			CString local_manifest = ticket_stub.GetLocalManifest();
			CString	local_ticket = ticket_stub.GetLocalTicket( local_manifest );

			if ( ! ticket_stub.ValidateTicket( local_ticket ) )
			{
				CDRProgress p_dlg;
				p_dlg.Create( CDRProgress::IDD, m_pMainWnd );
				
				p_dlg.Init();

				p_dlg.ShowWindow( SW_SHOWNORMAL );

				p_dlg.Advance();

				// ticket doesn't match, need to update files
				if ( ticket_stub.UpdateFiles( local_manifest, manifest_directory, &p_dlg ) )
				{
					ok_to_launch = true;
				}
				else
				{
					err = ticket_stub.GetErrorLog();
				}

				p_dlg.CloseWindow();
			}
			else
			{
				ok_to_launch = true;
			}
		}

		if ( ok_to_launch )
		{
			if ( ! ticket_stub.LaunchCDR( cdr_application, uid, key ) )
			{
				// failed after all
				ok_to_launch = false;
				err = ticket_stub.GetErrorLog();
			}
		}

		if ( ! ok_to_launch )
		{
			/****
			*	!STUPID WINDOWS!
			*	This is the message function that depends on the existance of dummy_win
			****/
			CString e_msg = _T("Unable to launch CDR Client\nError Log:\n\n") + err;
			AfxMessageBox( e_msg, MB_ICONERROR );
		}
	}
	else if (nResponse == IDCANCEL)
	{
		// They said never mind, leave
		// nothing to do
	}

	// get rid of our 'main' window
	delete dummy_win;
	m_pMainWnd = 0;
	dummy_win = 0;

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
