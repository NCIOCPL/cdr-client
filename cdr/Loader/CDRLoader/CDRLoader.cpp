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

CString	VERSION_STR = _T( "Version 20020916 1241\n" );

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

		if ( ! db_trickle.Open( DEBUG_FILE, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone, &e ) )
		{
			_TCHAR  errmsg[ 1024 ];
			int len = 1000;
			e.GetErrorMessage( errmsg, len );
			printf( "Debug file broken: %s", errmsg );
		}
		DebugWrite( "Started Debugging\n" );
		DebugWrite( VERSION_STR );
		time_t t = time(NULL);
		DebugWrite( ctime( &t ) );
		DebugWrite( "\n" );
	}
}

void DebugResume( void )
{
	if ( ! g_debug_flag )
		return;

	if ( db_trickle.m_hFile == CFile::hFileNull  )
	{
		CFileException e;

		if ( ! db_trickle.Open( DEBUG_FILE, CFile::modeReadWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyNone, &e ) )
		{
			_TCHAR  errmsg[ 1024 ];
			int len = 1000;
			e.GetErrorMessage( errmsg, len );
			printf( "Debug file broken: %s", errmsg );
		}

		db_trickle.SeekToEnd();

		DebugWrite( "**********************\n" );
		DebugWrite( "Resumed Debugging\n" );
		DebugWrite( VERSION_STR );
		time_t t = time(NULL);
		DebugWrite( ctime( &t ) );
		DebugWrite( "\n" );
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

	ini_Data.ReadOptions();

	// process command line values
	//	m_lpCmdLine
	CString manifest_directory = _T( ".\\" );
	CString	manifest_filename = _T( "CDR_MANIFEST.XML" );
	CString cdr_application = _T( "C:\\Program Files\\SoftQuad\\Xmetal 3\\xmetal3.exe" );

	// give this the value fromt he file, override from the command line if set
	CString default_http_server = _T( "mmdb2.nci.nih.gov" );
	CString http_server = _T( "" );

    if (m_lpCmdLine[0] != _T('\0'))
    {
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

					case 'B':
					case 'b':
					{
						SetDebugFlag( cur_token[0] != '0' );
						if ( cur_token[0] == '1' )
						{
                            DebugStart();
						}
						else
						{
							DebugResume();
						}
					}
					break;

					case 'U':
					case 'u':
					{
						DebugWrite( "Removing CDRLoaderUpdated.cmd\n" );
						int err = remove( "CDRLoaderUpdated.cmd" );
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

	dlg.UserId = ini_Data.last_User;
	dlg.SetInit( &ini_Data );

	//DebugBreak();

	int cur_server_ndx = ini_Data.GetCurrentServer();

	INT_PTR nResponse;
	TCHAR * cdr_s_id = _wgetenv( _T( "CDRSession" ) );
	if ( cdr_s_id == NULL )
	{
 		nResponse = dlg.DoModal();
		DebugWrite( "Returned from modal dialog, setting environment.\n" );

		CString uid = dlg.UserId;
		ini_Data.last_User = uid;

		CString key = dlg.SessionId;

		cur_server_ndx = ini_Data.GetCurrentServer();

		CDRTicketStub::BequeathEnvironment( uid, 
							 key, 
							 ini_Data.servers[ cur_server_ndx ].cdr_Server, 
							 ini_Data.servers[ cur_server_ndx ].cdr_Port );
	}
	else
	{
		// we logged in earlier, don't repeat
		nResponse = IDOK;
		DebugWrite( "Skipped modal dialog Session Id already set, leaving environment as it was.\n" );
		DebugWrite( "Session Id was " );
		DebugWrite( cdr_s_id );
		DebugWrite( "\n" );
	}

	if (nResponse == IDOK)
	{
		bool	ok_to_launch = false;
		CString	err = _T("Unknown error.");

		CString http_server;
		if ( ini_Data.servers[ cur_server_ndx ].ticket_Server.GetLength() > 0 )
		{
			http_server = ini_Data.servers[ cur_server_ndx ].ticket_Server;

			if ( ini_Data.servers[ cur_server_ndx ].ticket_Port.GetLength() > 0 )
			{
				http_server += _T( ":" ) + ini_Data.servers[ cur_server_ndx ].ticket_Port;
			}
		}
		else
		{
			http_server = default_http_server;
		}
		CDRTicketStub ticket_stub;
		DebugWrite( "Http Server is " );
		DebugWrite( http_server );
		DebugWrite( "\n" );
		ticket_stub.SetHttpServer( http_server );

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
			DebugWrite( "Saving INI options prior launch.\n" );
			ini_Data.WriteOptions();

			DebugWrite( "Closing debug prior launch.\n" );
			DebugEnd();

			if ( ! ticket_stub.LaunchCDR( cdr_application ) )
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

	DebugWrite( "Saving INI options.\n" );

	ini_Data.WriteOptions();

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
