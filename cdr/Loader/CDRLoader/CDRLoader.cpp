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

/*
*	DEBUG Tool
*/
TCHAR *  DEBUG_FILE = _T( "CDRLoad-Debug.txt" );
bool	g_debug_flag = false;
CStdioFile   db_trickle;

void SetDebugFlag( bool f )
{
	g_debug_flag = f;
}

void DebugWrite( char * msg )
{
	if ( ! g_debug_flag )
		return;

	if ( db_trickle.m_hFile != CFile::hFileNull  )
	{
		db_trickle.Write( msg, strlen( msg ) );
		db_trickle.Flush();
	}
}

void DebugWrite( CString msg )
{
	if ( ! g_debug_flag )
		return;

	if ( db_trickle.m_hFile != CFile::hFileNull  )
	{
		CStringA dummy( msg );
		db_trickle.Write( (CString::PCYSTR)dummy, strlen( (CString::PCYSTR)dummy ) );
		db_trickle.Flush();
	}
}

void DebugStart( void )
{
	if ( ! g_debug_flag )
		return;

	if ( db_trickle.m_hFile == CFile::hFileNull  )
	{
		CFileException e;

		if ( ! db_trickle.Open( DEBUG_FILE, CFile::modeCreate | CFile::modeWrite, &e ) )
		{
			_TCHAR  errmsg[ 1024 ];
			int len = 1000;
			e.GetErrorMessage( errmsg, len );
			printf( "Debug file broken: %s", errmsg );
		}
		DebugWrite( "Started Debugging\n" );
	}
}

void DebugResume( void )
{
	if ( ! g_debug_flag )
		return;

	if ( db_trickle.m_hFile == CFile::hFileNull  )
	{
		CFileException e;

		if ( ! db_trickle.Open( DEBUG_FILE, CFile::modeWrite, &e ) )
		{
			_TCHAR  errmsg[ 1024 ];
			int len = 1000;
			e.GetErrorMessage( errmsg, len );
			printf( "Debug file broken: %s", errmsg );
		}
		DebugWrite( "Resumed Debugging\n" );
	}
}

void DebugEnd( void )
{
	if ( ! g_debug_flag )
		return;

	if ( db_trickle.m_hFile != CFile::hFileNull  )
	{
		db_trickle.Flush();
		db_trickle.Close();
	}
}

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
	CString http_server = _T( "mmdb2.nci.nih.gov" );

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
						DebugWrite( "Set manifest_filename\n" );
						DebugWrite( manifest_filename );
						DebugWrite( "\n" );
					}
					break;

					case 'A':
					case 'a':
					{
						cdr_application =  cur_token;
						DebugWrite( "Set cdr_application\n\t" );
						DebugWrite( cdr_application.GetString() );
						DebugWrite( "\n" );
					}
					break;

					case 'D':
					case 'd':
					{
						manifest_directory = cur_token;
						DebugWrite( "Set manifest_directory\n\t" );
						DebugWrite( manifest_directory.GetString() );
						DebugWrite( "\n" );
					}
					break;

					case 'H':
					case 'h':
					{
						http_server = cur_token;
					}
					break;

					case 'B':
					case 'b':
					{
						SetDebugFlag( cur_token[0] != '0' );
						DebugStart();
					}
					break;
				}
			}
			cur_token = cmd_line.Tokenize( space, pos );
		}
    }

	DebugWrite( "Processed command line\n" );


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

	DebugWrite( "Created dummy window\n" );

	INT_PTR nResponse = dlg.DoModal();

	DebugWrite( "Returned from modal dialog\n" );

	if (nResponse == IDOK)
	{
		bool	ok_to_launch = false;
		CString	err = _T("Unknown error.");

		CDRTicketStub ticket_stub;
		ticket_stub.SetHttpServer( http_server );

		CString uid = dlg.UserId;
		CString key = dlg.SessionId;
		if ( true )
		{
			DebugWrite( "Evaluating state.\n" );

			ticket_stub.InitializeFileLocation( manifest_directory + manifest_filename );

			DebugWrite( "Loading local manifest.\n" );

			CString local_manifest = ticket_stub.GetLocalManifest();

			DebugWrite( "Extracting ticket from local manifest.\n" );

			CString	local_ticket = ticket_stub.GetLocalTicket( local_manifest );

			DebugWrite( "Validating Ticket.\n" );

			if ( ! ticket_stub.ValidateTicket( local_ticket ) )
			{

				DebugWrite( "Creating Progress Dialog.\n" );

				CDRProgress p_dlg;
				p_dlg.Create( CDRProgress::IDD, m_pMainWnd );
				
				p_dlg.Init();

				p_dlg.ShowWindow( SW_SHOWNORMAL );

				p_dlg.Advance();

				DebugWrite( "Updating Files\n" );

				// ticket doesn't match, need to update files
				if ( ticket_stub.UpdateFiles( local_manifest, manifest_directory, &p_dlg ) )
				{
					ok_to_launch = true;
				}
				else
				{
					err = ticket_stub.GetErrorLog();
				}

				DebugWrite( "Closing progress dialog.\n" );

				p_dlg.CloseWindow();
			}
			else
			{
				ok_to_launch = true;
			}
		}

		DebugWrite( "Ready to launch\n" );

		if ( ok_to_launch )
		{
			DebugWrite( "Closing debug prior launch.\n" );
			DebugEnd();
			if ( ! ticket_stub.LaunchCDR( cdr_application, uid, key ) )
			{
				// failed after all
				ok_to_launch = false;
				err = ticket_stub.GetErrorLog();

				DebugResume();
				DebugWrite( "Launch failed\n" );
			}
		}

		DebugWrite( "Did not launch\n" );

		if ( ! ok_to_launch )
		{
			/****
			*	!STUPID WINDOWS!
			*	This is the message function that depends on the existance of dummy_win
			****/
			CString e_msg = _T("Unable to launch CDR Client\nError Log:\n\n") + err;
			AfxMessageBox( e_msg, MB_ICONERROR );
		}

		DebugWrite( "User acknowledged failure message\n" );
	}
	else if (nResponse == IDCANCEL)
	{
		DebugWrite( "User Cancelled\n" );
		// They said never mind, leave
		// nothing to do
	}

	DebugWrite( "Finished processing, destroying dummy window.\n" );

	// get rid of our 'main' window
	delete dummy_win;
	m_pMainWnd = 0;
	dummy_win = 0;

	DebugWrite( "Return FALSE when done.\n" );
	DebugEnd();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}