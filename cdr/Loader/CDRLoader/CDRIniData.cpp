#include "StdAfx.h"
#include "cdrinidata.h"

#include <stdio.h>

const CString CDRIniData::CURRENT_VERSION( "1.1" );

CDRIniData::CDRIniData(void)
{
	ticket_Server = "";
	ticket_Port = "";
	cdr_Server = "";
	cdr_Port = "";
	last_User = "";
}

CDRIniData::~CDRIniData(void)
{
}

void CDRIniData::ReadOptions( void )
{
	// if the file's not there start with blanks.
	CFileStatus fs;
	if ( ! CFile::GetStatus( _T( "CDRLoader.ini" ), fs ) )
		return;

	CStdioFile	ini_file( _T( "CDRLoader.ini" ), CFile::modeRead  );

	CString in_str;

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
			if ( ! name.CompareNoCase( _T( "TICKET_SERVER" ) ) )
			{
				ticket_Server = value;
			}
			if ( ! name.CompareNoCase( _T( "TICKET_PORT" ) ) )
			{
				ticket_Port = value;
			}
			if ( ! name.CompareNoCase( _T( "CDR_SERVER" ) ) )
			{
				cdr_Server = value;
			}
			if ( ! name.CompareNoCase( _T( "CDR_PORT" ) ) )
			{
				cdr_Port = value;
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

	ini_file.WriteString( _T( "TICKET_SERVER " ) );
	ini_file.WriteString( ticket_Server.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "TICKET_PORT " ) );
	ini_file.WriteString( ticket_Port.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "CDR_SERVER " ) );
	ini_file.WriteString( cdr_Server.GetString() ); 
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "CDR_PORT " ) );
	ini_file.WriteString( cdr_Port.GetString() );
	ini_file.WriteString( _T( "\n" ) );

	ini_file.WriteString( _T( "LAST_USER " ) );
	ini_file.WriteString( last_User.GetString() );
	ini_file.WriteString( _T( "\n" ) );
	
	ini_file.Flush();
	ini_file.Close();
}
