#include "StdAfx.h"
#include "cdrinidata.h"

#include <stdio.h>

const CString CDRIniData::CURRENT_VERSION( "1.1" );

CDRIniData::CDRIniData(void)
{
	servers[ CDR_SRV_PROD ].ticket_Server = "";
	servers[ CDR_SRV_PROD ].ticket_Port = "";
	servers[ CDR_SRV_PROD ].cdr_Server = "";
	servers[ CDR_SRV_PROD ].cdr_Port = "";

	servers[ CDR_SRV_TEST ].ticket_Server = "";
	servers[ CDR_SRV_TEST ].ticket_Port = "";
	servers[ CDR_SRV_TEST ].cdr_Server = "";
	servers[ CDR_SRV_TEST ].cdr_Port = "";

	servers[ CDR_SRV_DEV ].ticket_Server = "";
	servers[ CDR_SRV_DEV ].ticket_Port = "";
	servers[ CDR_SRV_DEV ].cdr_Server = "";
	servers[ CDR_SRV_DEV ].cdr_Port = "";

	last_User = "";
	default_Server = "PRODUCTION";
}

CDRIniData::~CDRIniData(void)
{
}

int CDRIniData::GetCurrentServer( void )
{
	int ret_val = CDR_SRV_PROD;

	if ( ! default_Server.CompareNoCase( _T( "PRODUCTION" ) ) )
	{
		ret_val = CDR_SRV_PROD;
	}
	else if ( ! default_Server.CompareNoCase( _T( "TEST" ) ) )
	{
		ret_val = CDR_SRV_TEST;
	}
	else if ( ! default_Server.CompareNoCase( _T( "DEV" ) ) )
	{
		ret_val = CDR_SRV_DEV;
	}

	return ret_val;
}

void CDRIniData::SetCurrentServer( int cs )
{
	switch ( cs )
	{
		case 0:
		{
			default_Server = _T( "PRODUCTION" );
		}
		break;
		case 1:
		{
			default_Server = _T( "TEST" );
		}
		break;
		case 2:
		{
			default_Server = _T( "DEV" );
		}
		break;
	}
}


void CDRIniData::ReadOptions( void )
{
	// if the file's not there start with blanks.
	CFileStatus fs;
	if ( ! CFile::GetStatus( _T( "CDRLoader.ini" ), fs ) )
		return;

	CStdioFile	ini_file( _T( "CDRLoader.ini" ), CFile::modeRead  );

	CString in_str;

	int srv_ndx = 0;

	while ( ini_file.ReadString( in_str ) )
	{
		CString t = in_str.Trim();
		// ignore comments
		if ( t.GetAt( 0 ) != '#' )
		{
			int pos = 0;
			CString name = t.Tokenize( _T( " " ), pos );
			CString value;
			if ( pos < t.GetLength() )
			{
				value = t.Mid( pos );
				if ( value.GetLength() > 0 )
				{
					value = value.Trim();
				}
			}

			if ( ! name.CompareNoCase( _T( "INI_VERSION" ) ) )
			{
				CString ini_version = value;
				if ( ini_version.CompareNoCase( CURRENT_VERSION ) )
				{
					// what do we do if we can't read the INI???
					// read what we can hope it hasn't changed
				}
			}

			if ( ! name.CompareNoCase( _T( "DEFAULT_SERVER" ) ) )
			{
				default_Server = value;
			}

			if ( ! name.CompareNoCase( _T( "SECTION" ) ) )
			{
				if ( ! value.CompareNoCase( _T( "PRODUCTION" ) ) )
				{
					srv_ndx = CDR_SRV_PROD;
				}
				else if ( ! value.CompareNoCase( _T( "TEST" ) ) )
				{
					srv_ndx = CDR_SRV_TEST;
				}
				else if ( ! value.CompareNoCase( _T( "DEV" ) ) )
				{
					srv_ndx = CDR_SRV_DEV;
				}
				else
				{
					// unknown section, asssume default
					srv_ndx = CDR_SRV_PROD;
				}
			}


			if ( ! name.CompareNoCase( _T( "TICKET_SERVER" ) ) )
			{
				servers[ srv_ndx ].ticket_Server = value;
			}
			if ( ! name.CompareNoCase( _T( "TICKET_PORT" ) ) )
			{
				servers[ srv_ndx ].ticket_Port = value;
			}
			if ( ! name.CompareNoCase( _T( "CDR_SERVER" ) ) )
			{
				servers[ srv_ndx ].cdr_Server = value;
			}
			if ( ! name.CompareNoCase( _T( "CDR_PORT" ) ) )
			{
				servers[ srv_ndx ].cdr_Port = value;
			}

			if ( ! name.CompareNoCase( _T( "LAST_USER" ) ) )
			{
				last_User = value;
			}

		}
	}

	ini_file.Close();

}

void CDRIniData::WriteOptions( void )
{
	CStdioFile	ini_file( _T( "CDRLoader.ini" ), CFile::modeWrite | CFile::modeCreate  );

	ini_file.WriteString( _T( "# CDRLoader.ini - holds options\n" ) );

	ini_file.WriteString( _T( "INI_VERSION " ) );
	ini_file.WriteString( CURRENT_VERSION.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "DEFAULT_SERVER " ) );
	ini_file.WriteString( default_Server.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "LAST_USER " ) );
	ini_file.WriteString( last_User.GetString() );
	ini_file.WriteString( _T( "\n" ) );
	
	////
	ini_file.WriteString( _T( "SECTION PRODUCTION\n" ) );

	ini_file.WriteString( _T( "TICKET_SERVER " ) );
	ini_file.WriteString( servers[ CDR_SRV_PROD ].ticket_Server.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "TICKET_PORT " ) );
	ini_file.WriteString( servers[ CDR_SRV_PROD ].ticket_Port.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "CDR_SERVER " ) );
	ini_file.WriteString( servers[ CDR_SRV_PROD ].cdr_Server.GetString() ); 
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "CDR_PORT " ) );
	ini_file.WriteString( servers[ CDR_SRV_PROD ].cdr_Port.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	////
	ini_file.WriteString( _T( "SECTION TEST\n" ) );

	ini_file.WriteString( _T( "TICKET_SERVER " ) );
	ini_file.WriteString( servers[ CDR_SRV_TEST ].ticket_Server.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "TICKET_PORT " ) );
	ini_file.WriteString( servers[ CDR_SRV_TEST ].ticket_Port.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "CDR_SERVER " ) );
	ini_file.WriteString( servers[ CDR_SRV_TEST ].cdr_Server.GetString() ); 
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "CDR_PORT " ) );
	ini_file.WriteString( servers[ CDR_SRV_TEST ].cdr_Port.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	////
	ini_file.WriteString( _T( "SECTION DEV\n" ) );

	ini_file.WriteString( _T( "TICKET_SERVER " ) );
	ini_file.WriteString( servers[ CDR_SRV_DEV ].ticket_Server.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "TICKET_PORT " ) );
	ini_file.WriteString( servers[ CDR_SRV_DEV ].ticket_Port.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "CDR_SERVER " ) );
	ini_file.WriteString( servers[ CDR_SRV_DEV ].cdr_Server.GetString() ); 
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "CDR_PORT " ) );
	ini_file.WriteString( servers[ CDR_SRV_DEV ].cdr_Port.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.Flush();
	ini_file.Close();
}
