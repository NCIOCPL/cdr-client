#include "StdAfx.h"
#include <afxinet.h> 
#include <iostream>
#include <direct.h>
#include <atlenc.h>	// i hope this isn't managed code!

#include "cdrticketstub.h"
#include "DRProgress.h"


	const CString CDRTicketStub::REQ_TEMPLATE = 
		_T("<?xml version = \"1.0\" encoding = \"UTF-8\"?>\n")
		_T("<env:Envelope        xmlns:env = \"http://schemas.xmlsoap.org/soap/envelope/\"\n")
		_T("			env:encodingStyle = \"http://schemas.xmlsoap.org/soap/encoding/\">\n")
		_T("<env:Body>\n")
		_T("%s\n")
		_T("</env:Body>\n")
		_T("</env:Envelope>");

CDRTicketStub::CDRTicketStub(void)
{
	ErrorLog = "";
}

CDRTicketStub::~CDRTicketStub(void)
{
}

CString CDRTicketStub::GetErrorLog( void )
{
	return ErrorLog;
}

void CDRTicketStub::InitializeFileLocation( CString manifest_file )
{
	wchar_t base_path[ _MAX_PATH ];
	wchar_t drive[ _MAX_DRIVE ];
	wchar_t dir[ _MAX_DIR ];
	wchar_t file[ _MAX_FNAME ];
	wchar_t ext[ _MAX_EXT ];

	_tsplitpath( manifest_file.GetString(), drive, dir, file, ext );
	_tmakepath( base_path, drive, dir, NULL, NULL );
	CDR_CLIENT_PATH = CString( base_path );


	_tmakepath( base_path, NULL, NULL, file, ext );
	CDR_MANIFEST_FILE = base_path;
}

CString CDRTicketStub::GetLocalTicket( CString manifest_xml )
{
	CString tic_start = _T( "<TICKET>"  );
	CString tic_end   = _T( "</TICKET>" );

	CString ticket_xml = _T( "<TICKET/>" );

	// extract the ticket portion of the manifest
	// locat the begining of the ticket tag
	int pos = manifest_xml.Find( tic_start );
	if ( pos != -1 )
	{
		// find out where the ticket end tag is
		int e_pos = manifest_xml.Find( tic_end, pos );
		if ( e_pos != -1 )
		{
			ticket_xml = manifest_xml.Mid( pos, e_pos + tic_end.GetLength() - pos );
		}
		else
		{
			ErrorLog += _T( "<XML_ERR doc=LOCAL>Local MANIFEST has unbalanced TICKET tag.</XML_ERR>\n" );
		}
	}
	else
	{
		ErrorLog += _T( "<XML_ERR doc=LOCAL>Local MANIFEST missing TICKET tag.</XML_ERR>\n" );
	}

	return ticket_xml;
}

CString CDRTicketStub::LoadFile( CString fname )
{
	CString lt = _T("");

	CStdioFile	ticket_file;

	char cwd[ 1024 ];
	_getcwd( cwd, 1023 );

	CFileException e;
	int r = ticket_file.Open( fname, CFile::modeRead, &e );
	if (  r )
	{
		char * buffer = new char [ ticket_file.GetLength() + 32 ];
		ULONG len = ticket_file.Read( buffer, ticket_file.GetLength() );
		buffer[ len ] = '\0';
		lt = CString( buffer );
		delete buffer;
	}
	else
	{
		_TCHAR  errmsg[ 1024 ];
		int len = 1000;
		e.GetErrorMessage( errmsg, len );
		
		ErrorLog += _T("<FILE_ERR name=\"") 
						+ fname 
						+ _T("\" cwd=\"") 
						+ CString( cwd ) 
						+ _T("\">")
						+ CString( errmsg ) 
						+ _T("</FILE_ERR>\n");
	}

	return lt;
}

CString CDRTicketStub::GetLocalManifest( void )
{
	CString t_name = CDR_CLIENT_PATH + CDR_MANIFEST_FILE;
	CString result = LoadFile( t_name );
	if ( result.GetLength() == 0 )
	{
		result = "<MANIFEST />";
	}
	return result;
}

CString CDRTicketStub::HttpRoundTrip( CString &data )
{
	CInternetSession inet_session;
	CHttpConnection * http_session = inet_session.GetHttpConnection( _T("mmdb2") );
	CString select = _T("/cgi-bin/Ticket/TicketCgi.py");
	CHttpFile * http_page = http_session->OpenRequest( _T("POST"), select );
	CString my_req = REQ_TEMPLATE;
	my_req.Replace( _T("%s"), data );
	DWORD l = my_req.GetLength();
	/***
		// !DEBUG!
		CFile junk4( "REQ-DUMP.txt", CFile::modeCreate | CFile::modeWrite );
		junk4.Write( my_req.GetString(), my_req.GetLength() );
		junk4.Close();
	***/
	// remember to switch out of unicode to talk to TICKET server
	CStringA plain_req = (CStringA )my_req.GetString();
	http_page->SendRequest( _T(""), 0, (void *)plain_req.GetString(), l );
	DWORD result;
	CString http_response_data = _T("");
	http_page->QueryInfoStatusCode( result );
	if (result != HTTP_STATUS_OK)
	{
		char num[32];
		ltoa( result, num, 10 );
		ErrorLog += _T("<HTTP_ERR>") + CString( num ) + _T("</HTTP_ERR>");
	}
	char buff[ 1024 ];
	UINT nRead = http_page->Read( buff, 1000 );
	while ( nRead > 0 )
	{
		buff[ nRead ] = '\0';
		http_response_data += buff;
		nRead = http_page->Read( buff, 1000 );
	}
	

	//*** 
		//!DEBUG!
		CFile junk5( _T("RESP-DUMP.txt"), CFile::modeCreate | CFile::modeWrite );
		junk5.Write( http_response_data.GetString(), http_response_data.GetLength() );
		junk5.Close();
	//***/
	http_page->Close();
	http_session->Close();

	delete http_page;
	delete http_session;

	return http_response_data;
}

bool CDRTicketStub::RecordServerError( CString soap_xml, CString operation )
{
	bool error = false;
	CString	err_start = _T( "<ERROR>"  );
	CString err_end   = _T( "</ERROR>" );

	int epos = soap_xml.Find( err_start );
	if ( epos != -1 )
	{
		epos += err_start.GetLength();
		ErrorLog += _T("<SERVER_ERR op=\"") + operation + _T("\">\n");
		int l_pos = soap_xml.Find( err_end, epos );
		if ( l_pos == -1 )
		{
			ErrorLog += _T("Unbalanced ERROR tag in soap response.");
		}
		else
		{
			CString em = soap_xml.Mid( epos, l_pos - epos );

			ErrorLog += em.Trim();
		}
		ErrorLog += _T("\n</SERVER_ERR>\n");
		error = true;
	}

	int fpos = soap_xml.Find( _T("<env:Fault>") );
	if ( fpos != -1 )
	{
		ErrorLog += _T("<SERVER_FAULT op=\"") + operation + _T("\">\n");
		int l_pos = soap_xml.Find( _T("</env:Fault>") );
		if ( l_pos == -1 )
		{
			ErrorLog += _T("Unbalanced env:Fault tag in soap response.");
		}
		else
		{
			ErrorLog += soap_xml.Mid( fpos, l_pos - fpos );
		}
		ErrorLog += "\n</SERVER_FAULT>\n";
		error = true;
	}

	return error;
}

bool CDRTicketStub::SaveZipFile( CString zip_xml, CString &fname )
{
	bool success = false;

	long epos;
	long pos = zip_xml.Find( _T("<ZIPFILE>" ) );
	if ( pos != -1 )
	{
		// look for the inner name tag
		pos = zip_xml.Find( _T("<FNAME>"), pos );
		if ( pos != -1 )
		{
			pos += _tcslen( _T("<FNAME>") );
			epos = zip_xml.Find( _T("</FNAME>"), pos );
			if ( epos != -1 )
			{
				CString zfile_name = zip_xml.Mid( pos, epos - pos );
				// we have the official file name
				// but since it will likely have the server's temp path, 
				// we probably don't want to use it

				CString l_zfile_name = CDR_CLIENT_PATH + _T("CDRUpdate.zip");

				// find the start of the data segment
				pos = zip_xml.Find( _T("<DATA"), epos );
				// skip the encoding attribute, if it isn't base64 we're broke anyway.
				// I'll skip the philosophical discussion about why I included
				// the attribute if I'm not going to actually use it...
				pos = zip_xml.Find( _T(">"), pos );
				if ( pos != -1 )
				{
					pos++;

					epos = zip_xml.Find( _T("</DATA>"), pos );
					if ( epos != -1 )
					{
						CString b64data = zip_xml.Mid( pos, epos - pos - 1 );

						long blen = b64data.GetLength();
						BYTE * bin_buffer = new BYTE [ blen * 2 ];
						/*
							// !DEBUG! dump the base64 data for comparison
							CStdioFile b64file( "B64Dump.txt", CFile::typeBinary | CFile::modeWrite | CFile::modeCreate );
							b64file.Write( b64data.GetBuffer(), blen );
							b64file.Close();
						*/
						int decoded_size = 1;
						CStringA temp( b64data );
						if ( ! Base64Decode( temp.GetString(), blen, bin_buffer, &decoded_size ) )
						{
							// this is a real failure
							ErrorLog += _T("<ZIP_ERR>Unable to decode (base64) binary data.</ZIP_ERR>\n");

							// set things up to carry on.
							bin_buffer[0] = 0;
							decoded_size = 0;
						}
						else
						{
							// this shouldn't happen, but if it does we're OK I guess
							if ( decoded_size > blen )
							{
								ErrorLog += _T("<ZIP_ERR>PANIC! Binary data decode overran buffer.</ZIP_ERR>\n");
								decoded_size = 0;
							}
						}

						// first make sure we have data to write
						if ( decoded_size > 0 )
						{
							CStdioFile	zip_file;

							CFileException fe;
							int r = zip_file.Open( l_zfile_name, CFile::typeBinary | CFile::modeWrite | CFile::modeCreate, &fe );
							if ( !r )
							{
								// couldn't open the file 
								_TCHAR errmsg[ 1024 ];
								int len = 1000;
								fe.GetErrorMessage( errmsg, len );

								ErrorLog += _T("<ZIP_ERR>Unable to create the zip file on disk: ");
								ErrorLog += CString( errmsg );
								ErrorLog += _T("</ZIP_ERR>\n");

								fname = "";
							}
							else
							{
								fname = l_zfile_name;

								// dump our bits into the file
								// don't write the trailing 0
								zip_file.Write( bin_buffer, decoded_size );
								zip_file.Close();

								success = true;
							}
						}

					}
					else
					{
						ErrorLog += "<XML_ERR doc=ZIPFILE>Unbalanced DATA tag.</XML_ERR>\n";
					}
				}
				else
				{
					ErrorLog += "<XML_ERR doc=ZIPFILE>Incomplete DATA start tag.</XML_ERR>\n";
				}
			}
			else
			{
				ErrorLog += "<XML_ERR doc=ZIPFILE>Unbalanced FNAME tag.</XML_ERR>\n";
			}
		}
		else
		{
			ErrorLog += "<XML_ERR doc=ZIPFILE>Missing FNAME tag.</XML_ERR>\n";
		}
	}
	else
	{
		ErrorLog += "<XML_ERR doc=ZIPFILE>Missing payload root.</XML_ERR>\n";
	}

	return success;
}

bool CDRTicketStub::ExecuteZipFile( CString client_dir, CString fname )
{
	bool success = false;

	// we now have a zipfile on the disk in (hopefully)
	// the directory that is both current and correct
	// now we need to unzip that file...

	// _spawn also flickers a command window on screen so effectively no difference
	// between that and system() other than system being easier to debug.

	CString unzip_cmd = _T(".\\unzip -o -d ") + client_dir + _T( " " ) + fname + _T( " > ") + fname + _T(".err"); 
	CStringA temp( unzip_cmd );
	if ( system( temp.GetString() ) != -1) 
	{
		// file unzipped without detected error
		// yea.
		success = true;
	}
	else
	{
		ErrorLog += _T("<EXEC_ERR>");
		ErrorLog += _T("Unable to execute ") + unzip_cmd + _T(" : ");
		ErrorLog += CString( strerror( errno ) );
		ErrorLog += _T("</EXEC_ERR>\n");
	}


	return success;
}

bool CDRTicketStub::ProcessZipFile( CString client_dir, CString manifest_xml, CDRProgress * pb )
{
	bool success = false;

	long pos = manifest_xml.Find( _T("<ZIPFILE/>") );
	if ( pos != -1 )
	{
		// zipfile item is empty
		// no file to get all is happy
		success = true;
	}
	else
	{
		pos = manifest_xml.Find( _T("<ZIPFILE>") );
		if ( pos != -1 )
		{
			// having found the zipfile tag, 
			// advance pointer to end of tag
			pos += _tcslen( _T("<ZIPFILE>") );
			long epos = manifest_xml.Find( _T("</ZIPFILE>"), pos );
			if ( epos != -1 )
			{
				CString zip_name = manifest_xml.Mid( pos, epos - pos );
				CString zip_req = _T("<ZIPREQ>") + zip_name + _T("</ZIPREQ>");
				
				pb->Advance();

				CString zip_response = HttpRoundTrip( zip_req );

				pb->Advance();

				if ( ! RecordServerError( zip_response, _T("ZIPREQ") ) )
				{
					// we got the zip file as base64 encoded data in an xml file
					CString fname;
                    if ( SaveZipFile( zip_response, fname ) )
					{
						pb->Advance();

						// can only execute if we saved it successfully
						if( ExecuteZipFile( client_dir, fname ) )
						{
							success = true;
						}

						pb->Advance();
					}
				}
			}
			else
			{
				ErrorLog += _T("<XML_ERR doc=DELTA>Unbalanced ZIPFILE tag.</XML_ERR>\n");
			}
		}
		else
		{
			// Hmmm, Zipfile tag is missing completely!
			// v. bad, shouldn't happen
			ErrorLog += _T("<XML_ERR doc=DELTA>Missing ZIPFILE tag.</XML_ERR>\n");
		}
	}

	return success;
}

bool CDRTicketStub::ProcessDeleteList( CString manifest_xml, CDRProgress * pb )
{
	bool success = false;

	long epos;
	// yea I know big assumptions about valid sections
	long pos = manifest_xml.Find( _T("<DELETE/>") );
	if ( pos != -1 )
	{
		// empty delete tag, we're done
		success = true;

		pb->Advance();
	}
	else
	{
		// look for the inner name tag
		pos = manifest_xml.Find( _T("<DELETE>" ) );
		if ( pos != -1 )
		{
			pos += _tcslen( _T("<DELETE>") );
			epos = manifest_xml.Find( _T("</DELETE>"), pos );
			if ( epos != -1 )
			{
				CString del_list = manifest_xml.Mid( pos, epos - pos );

				long fpos = del_list.Find( _T("<FILE>") );
				while ( fpos != -1 )
				{
					fpos += _tcslen( _T("<FILE>") );
					long epos = del_list.Find( _T("</FILE>"), fpos );
					if ( epos != -1 )
					{
						CString fname = del_list.Mid( fpos, epos - fpos );

						// delete the file
						CStringA t( fname );

						//!DEBUG!
						int r = remove( t.GetString() );
						
						// non zero means error, 
						// ENOENT means it was already gone, which is OK
						if ( r && ( errno != ENOENT ) )
						{
							success = false;

							ErrorLog += _T("<FILE_ERR>");
							ErrorLog += _T("Unable to delete ") + fname + _T(" : ");
							ErrorLog += CString( strerror( errno ) );
							ErrorLog += _T("</FILE_ERR>\n");
						}
						else
						{
							// we deleted at least one file, hopefully we'll get them all
							success = true;

							pb->Advance();
						}

						// keep looking for more file names
						fpos = del_list.Find( _T("<FILE>"), epos );
					}
					else
					{
						ErrorLog += _T("<XML_ERR doc=DELTA>Unbalanced FILE tag. Ending DELETE operation.</XML_ERR>\n");
						// this is an exception to the rule,
						// since we are having success in increments
						// a failure requires we revert the flag to show failure
						success = false;
					}
				}
			}
			else
			{
				ErrorLog += _T("<XML_ERR doc=DELTA>Unbalanced DELETE tag.</XML_ERR>\n");
			}
		}
		else
		{
			ErrorLog += _T("<XML_ERR doc=DELTA>Missing DELETE tag.</XML_ERR>\n");
		}
	}

	return success;
}


bool CDRTicketStub::ValidateTicket( CString &ticket )
{
	bool valid = false;

	CString validation_response = HttpRoundTrip( ticket );
	if ( ! RecordServerError( validation_response, _T("TICKET") ) )
	{
		int pos = validation_response.Find( _T("<Response>ACK</Response>") );
		if ( pos != -1 )
		{
			valid = true;
		}
	}

	return valid;
}

bool CDRTicketStub::UpdateFiles( CString &manifest, CString client_dir, CDRProgress * pb )
{
	bool valid = false;

	CString manifest_response = HttpRoundTrip( manifest );
	
	pb->Advance();

	if ( ! RecordServerError( manifest_response, _T("MANIFEST") ) )
	{
		int pos = manifest_response.Find( _T("<DELTA/>") );
		if ( pos != -1 )
		{
			// we got a empty delta, we're clean roll out true
			valid = true;
		}
		else
		{
			//	if we got delta info, we need to act on it
			//  only if both actions are successful can we
			//	proceed with a "true" update result
			valid  = ProcessZipFile( client_dir, manifest_response, pb );

			pb->Advance();

			valid &= ProcessDeleteList( manifest_response, pb );

			pb->Advance();
		}
	}

	return valid;
}

bool CDRTicketStub::LaunchCDR( CString app, CString user, CString session )
{
	CStringA aapp( app );
	CStringA uenv = "CDRUser="  + CStringA( user );
	CStringA senv = "CDRSession="  + CStringA( session );

	// these change current environment settings
	_putenv( (CString::PCYSTR)uenv );
	_putenv( (CString::PCYSTR)senv );

	//char * prog = "\"C:\\Program Files\\SoftQuad\\Xmetal 3\\xmetal3.exe\"";
	//char * prog = "C:\\WINNT\\system32\\cmd.exe";

	char prog_name[512];
	strncpy( prog_name, aapp.GetBuffer(), aapp.GetLength() );
	prog_name[ aapp.GetLength() ] = '\0';

	char * my_args[2];

	//my_args[0] = aapp.GetBuffer();
	my_args[0] = "xmetal3.exe";
	my_args[1] = NULL;


	// null pointer for my_env inhierts current
	int err = _execve( aapp.GetBuffer(), my_args, NULL );

	ErrorLog += _T("<EXEC_ERR>");
	ErrorLog += _T("Unable to execute ") + CString( my_args[0] ) + _T(" : ");
	ErrorLog += CString( strerror( errno ) );
	ErrorLog += _T("</EXEC_ERR>\n");

	return false;
}
