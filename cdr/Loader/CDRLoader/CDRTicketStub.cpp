#include "StdAfx.h"
#include <afxinet.h> 
#include <iostream>
#include <direct.h>
#include <atlenc.h>	// i hope this isn't managed code!

#include <sys/types.h>
#include <sys/stat.h>

#include "cdrloader.h"
#include "cdrticketstub.h"
#include "DRProgress.h"
#include "CDRGenerics.h"


extern void DebugWrite( char *  msg );
extern void DebugWrite( CString msg );
extern void DebugResume( void );
extern void DebugEnd( void );
extern bool keepLoader;

const CString CDRTicketStub::REQ_TEMPLATE = 
    _T("<?xml version = \"1.0\" encoding = \"UTF-8\"?>\n")
    _T("<env:Envelope        xmlns:env = ")
    _T("\"http://schemas.xmlsoap.org/soap/envelope/\"\n")
    _T("             env:encodingStyle = ")
    _T("\"http://schemas.xmlsoap.org/soap/encoding/\">\n")
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

void CDRTicketStub::SetHttpServer( CString serv )
{
    http_Server = serv;
}

void CDRTicketStub::SetHttpPort( int port )
{
    http_Port = port;
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

    //DebugWrite( "Set file location\n" );
}

CString CDRTicketStub::GetLocalTicket( CString manifest_xml )
{
    CString tic_start = _T( "<TICKET>"  );
    CString tic_end   = _T( "</TICKET>" );

    CString ticket_xml = _T( "<TICKET/>" );

    //DebugWrite( "Looking for ticket in manifest.\n" );

    // extract the ticket portion of the manifest
    // locat the begining of the ticket tag
    int pos = manifest_xml.Find( tic_start );
    if ( pos != -1 )
    {
        // find out where the ticket end tag is
        int e_pos = manifest_xml.Find( tic_end, pos );
        if ( e_pos != -1 )
        {
            ticket_xml = manifest_xml.Mid( pos, e_pos +
                                           tic_end.GetLength() - pos );
        }
        else
        {
            ErrorLog += _T("<XML_ERR doc=LOCAL>Local MANIFEST has ")
                        _T("unbalanced TICKET tag.</XML_ERR>\n");
            DebugWrite("CDRTicketStub(): malformed manifest document.\n");
        }
    }
    else
    {
        ErrorLog += _T("<XML_ERR doc=LOCAL>Local MANIFEST missing ")
                    _T("TICKET tag.</XML_ERR>\n");

        DebugWrite( "Didn't find ticket.\n" );
    }

    return ticket_xml;
}

CString CDRTicketStub::LoadFile( CString fname )
{
    //DebugWrite( "Loading file, looking for " );
    //DebugWrite( fname );
    //DebugWrite( "\n" );

    CString lt = _T("");

    CStdioFile    ticket_file;

    char cwd[ 1024 ];
    _getcwd( cwd, 1023 );

    CFileException e;
    int r = ticket_file.Open( fname, CFile::modeRead, &e );
    if (  r )
    {
        char * buffer = new char [ (size_t)ticket_file.GetLength() + 32 ];
        ULONG len = (ULONG)ticket_file.Read( buffer, (UINT)ticket_file.GetLength() );
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

        DebugWrite( ErrorLog );
    }

    return lt;
}

bool CDRTicketStub::CheckManifestFiles()
{
    CString fileName = CDR_CLIENT_PATH + CDR_MANIFEST_FILE;
    CString xmlString = LoadFile(fileName);
    if (!xmlString.GetLength()) {
        DebugWrite("CheckManifestFiles(): didn't find manifest file.\n");
        return false;
    }
    return CheckManifestFiles(xmlString);
}
static CString getFileTimestamp(const CString& name) {
    HANDLE h = ::CreateFile((LPCTSTR)name, GENERIC_READ, 0, NULL,
                            OPEN_EXISTING, 0, 0);
    if (!h) {
        CString err;
        err.Format(_T("failure getting timestamp for %s"), name);
        return err;
    }
    FILETIME cre, acc, wri;
    if (!::GetFileTime(h, &cre, &acc, &wri)) {
        CString err;
        err.Format(_T("unable to get timestamp for %s"), name);
        return err;
    }
    SYSTEMTIME s;
    if (!::FileTimeToSystemTime(&wri, &s)) {
        CString err;
        err.Format(_T("failure converting filetime to system time for %s"),
                   name);
        return err;
    }
    CString result;
    result.Format(_T("%04d%02d%02d%02d%02d%02d"), 
                  s.wYear, s.wMonth, s.wDay, 
                  s.wHour, s.wMinute, s.wSecond);
    return result;
}

bool CDRTicketStub::CheckManifestFiles(const CString &xmlString)
{
    //DebugWrite("Checking manifest files.\n");
    
    // Make sure the manifest is still accurate.  We check by comparing
    // timestamps for the files listed in the manifest.  Takes less than
    // 1/20 of a second on my workstation, so Jeff's concerns about
    // the impact on performance seem to be groundless.
    cdr::Element e = cdr::Element::extractElement(xmlString, _T("FILELIST"));
    if (!e) {
        DebugWrite("CheckManifestFiles(): Unable to find FILELIST element.\n");
        return false;
    }

    CString fileList = e.getString();
    for (e = cdr::Element::extractElement(fileList, _T("FILE"));
         e;
         e = cdr::Element::extractElement(fileList, _T("FILE"),
                                          e.getEndPos())) {
            
        CString f = e.getString();
        cdr::Element nameElem = cdr::Element::extractElement(f, _T("NAME"));
        cdr::Element timeElem = cdr::Element::extractElement(f, 
                                                             _T("TIMESTAMP"));
        if (nameElem && timeElem) {
            struct _stat s;
            CString name = nameElem.getString();
            CString serverTimestamp = timeElem.getString();
            //DebugWrite(_T("Checking manifest file ") + name + _T("\n"));

            CString upperName = name;
            upperName.MakeUpper();

            // This one doesn't count, because we delete it.
            if (upperName.Find(_T("CDRLOADERUPDATED.CMD")) != -1)
                continue;
            
            int rc = (int)_tstat((LPCTSTR)name, &s);
            if (rc) {
                DebugWrite(_T("CheckManifestFiles(): ") + name +
                           _T(" not found.\n"));
                return false;
            }

            // Don't bother with directories.
            else if (s.st_mode & _S_IFREG) {

                CString clientTimestamp = getFileTimestamp(name);
                if (serverTimestamp != clientTimestamp) {

                    DebugWrite(_T("CheckManifestFiles() checking ") + name +
                               _T(".\n"));
                    DebugWrite(_T("Server: ") + serverTimestamp);
                    DebugWrite(_T("Client: ") + clientTimestamp);
                    return false;
                }
            }
        }
    }
    return true;
}

CString CDRTicketStub::GetLocalManifest( void )
{
    //DebugWrite( "Looking For Manifest.\n" );

    CString emptyManifest = _T("<MANIFEST />");
    CString t_name = CDR_CLIENT_PATH + CDR_MANIFEST_FILE;
    CString result = LoadFile( t_name );
    if ( result.GetLength() == 0 )
    {
        result = emptyManifest;
        DebugWrite("Manifest file not present.\n");
    }
    else if (!CheckManifestFiles( result ))
    {
        DebugWrite("Manifest mismatch; we will tell the SOAP server we have"
                   " no manifest.\n");
        result = emptyManifest;
    }

    return result;
}

CString CDRTicketStub::HttpRoundTrip( CString &data )
{
    
    //DebugWrite( "Starting HTTP calls.\n" );
    
    CInternetSession inet_session;
    CString http_response_data = _T("");
    
    try
    {
        //DebugWrite( "HTTP top of try.\n" );
        CHttpConnection * http_session = inet_session.GetHttpConnection(http_Server,
            (INTERNET_PORT)http_Port );
        //DebugWrite( "HTTP GotConnection.\n" );
        CString select = _T("/cgi-bin/Ticket/TicketCgi.py");
        CHttpFile * http_page = http_session->OpenRequest( _T("POST"), select );
        //DebugWrite( "HTTP Request Open.\n" );
        CString my_req = REQ_TEMPLATE;
        my_req.Replace( _T("%s"), data );
        // remember to switch out of unicode to talk to TICKET server
        CStringA plain_req = (CStringA )my_req.GetString();
        DWORD rlen = plain_req.GetLength();
        //DebugWrite( "HTTP Request is:\n" );
        //DebugWrite( my_req );
        //DebugWrite( "\n" );
        CStringA::PCXSTR t;
        DWORD socket_err = 0;
        CString logMsg;
        logMsg.Format(_T("server=%s port=%d page=%p select=%s req=%s\n"),
                      http_Server, http_Port, http_page, select, my_req);
        DebugWrite(logMsg);
        try
        {
            t = plain_req.GetString();
        }
        catch ( ... )
        {
            DebugWrite("HttpRoundTrip(): exception in string conversion.\n");
        }
        int retry = 0;
        int sr_val = 0;
        while (( sr_val == 0 ) && ( retry++ < 3 ))
        {
            //if (retry)
            //    Sleep(500);
                     
            //DebugWrite( "SendRequest() Retry loop\n" );
            try 
            {
                sr_val = http_page->SendRequest( _T(""), 0, (void *)t, rlen );
            }
            catch ( CInternetException* ee )
            {
                CString msg;
                msg.Format(_T("Request length: %d; HTTP server: [%s]"), rlen, http_Server);
                ::AfxMessageBox(msg);
                _TCHAR  errmsg[ 1024 ];
                int len = 1000;
                ee->GetErrorMessage( errmsg, len );
                ErrorLog += _T("<HTTP_EXCEPTION type=\"SendRequest CIE\">") + CString( errmsg ) + _T("</HTTP_EXCEPTION>");
                
                DebugWrite( "Caught at SendRequest() CInternetException\n" );
                DebugWrite( errmsg );
				ee->Delete();
            }
            catch ( CException* ee )
            {
                CString msg;
                msg.Format(_T("Request length: %d; HTTP server: [%s]"), rlen, http_Server);
                ::AfxMessageBox(msg);
                _TCHAR  errmsg[ 1024 ];
                int len = 1000;
                ee->GetErrorMessage( errmsg, len );
                ErrorLog += _T("<HTTP_EXCEPTION type=\"SendRequest CE\">") + CString( errmsg ) + _T("</HTTP_EXCEPTION>");
                
                DebugWrite( "Caught at SendRequest() CException\n" );
                DebugWrite( errmsg );
				ee->Delete();
            }
            catch ( CObject & )
            {
                DebugWrite( "Caught at SendRequest() CObject\n" );
            }
            catch ( ... )
            {
                CString msg;
                msg.Format(_T("Request length: %d; HTTP server: [%s]"), rlen, http_Server);
                ::AfxMessageBox(msg);
                DebugWrite( "Caught at SendRequest() ...\n" );
                socket_err = GetLastError();
                char se[32];
                ltoa( socket_err, se, 10 );
                ErrorLog += _T("<HTTP_EXCEPTION type=\"SendRequest CE\">")
                            _T("Socket Error ") 
                          + CString( se ) 
                          + _T("</HTTP_EXCEPTION>");
                DebugWrite( "Socket Error is " );
                DebugWrite( se );;
                DebugWrite( "\n" );
            }
        }
        //DebugWrite( "HTTP Request Sent.\n" );
        DWORD result;
        http_page->QueryInfoStatusCode( result );

        //DWORD dwError, cbRead = sizeof(dwError);
        //HttpQueryInfo( http_page->m_hFile, HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER , &dwError, &cbRead, NULL);


        //DebugWrite( "HTTP look at status.\n" );
        if (result != HTTP_STATUS_OK)
        {
            char num[32];
            ltoa( result, num, 10 );
            ErrorLog += _T("<HTTP_ERR>") + CString( num ) + _T("</HTTP_ERR>");
            DebugWrite( "HTTP status from QueryInfoStatusCode(): " );
            DebugWrite( num );

            //        ltoa( dwError, num, 10 );
            //DebugWrite( "HTTP status from HttpQueryInfo()" );
            //DebugWrite( num );
            //DebugWrite( "\n" );
        }
        char buff[ 1024 ];
        UINT nRead = http_page->Read( buff, 1000 );
        //DebugWrite( "HTTP Did first read.\n" );
        while ( nRead > 0 )
        {
            buff[ nRead ] = '\0';
            http_response_data += buff;
            nRead = http_page->Read( buff, 1000 );
            //DebugWrite( "HTTP Did next read.\n" );
        }
        
        //DebugWrite( "HTTP Done reading.\n" );

        http_page->Close();
        //DebugWrite( "HTTP closed page.\n" );
        http_session->Close();
        //DebugWrite( "HTTP closed session.\n" );

        delete http_page;
        //DebugWrite( "HTTP delete page.\n" );
        delete http_session;
        //DebugWrite( "HTTP delete session.\n" );

    }
    catch ( CInternetException* e )
    {
        _TCHAR  errmsg[ 1024 ];
        int len = 1000;
        e->GetErrorMessage( errmsg, len );
        ErrorLog += _T("<HTTP_EXCEPTION type=CInternet>") +
                     CString( errmsg ) + _T("</HTTP_EXCEPTION>");

        DebugWrite( errmsg );
		e->Delete();
    }
    catch ( CException* e )
    {
        _TCHAR  errmsg[ 1024 ];
        int len = 1000;
        e->GetErrorMessage( errmsg, len );
        ErrorLog += _T("<HTTP_EXCEPTION type=CException>") +
            CString( errmsg ) + _T("</HTTP_EXCEPTION>");
        DebugWrite( errmsg );
		e->Delete();
    }
    catch ( ... )
    {
        ErrorLog += _T("<HTTP_EXCEPTION type=Unknown>")
            _T("Exception of Unknown variety.</HTTP_EXCEPTION>");
        DebugWrite( "Unknown Exception!" );
    }

    //DebugWrite( "Finished HTTP calls.\n" );

    return http_response_data;
}

bool CDRTicketStub::RecordServerError( CString soap_xml, CString operation )
{
    bool error = false;
    CString    err_start = _T( "<ERROR>"  );
    CString err_end   = _T( "</ERROR>" );

    int epos = soap_xml.Find( err_start );
    if ( epos != -1 )
    {
        epos += err_start.GetLength();
        ErrorLog += _T("<SERVER_ERR op=\"") + operation + _T("\">\n");
        int l_pos = soap_xml.Find( err_end, epos );
        if ( l_pos == -1 )
        {
            ErrorLog += _T("Unbalanced ERROR tag in soap response");
            DebugWrite(_T("Malformed ERROR element for operation ") +
                       operation + _T(".\n"));
        }
        else
        {
            CString em = soap_xml.Mid( epos, l_pos - epos );
            DebugWrite(_T("Server error ") + em.Trim() + _T(" for operation ")
                       + operation + _T(".\n"));
            ErrorLog += em;
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
            DebugWrite(_T("Malformed env:Fault in SOAP response for ")
                       _T("operation ") + operation + _T(".\n"));
        }
        else
        {
            CString fault = soap_xml.Mid(fpos, l_pos - fpos);
            DebugWrite(_T("Server fault ") + fault.Trim() +
                       _T(" for operation ") + operation + _T(".\n"));
            ErrorLog += fault;
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
            pos += (long)_tcslen( _T("<FNAME>") );
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
                        CString b64data = zip_xml.Mid( pos, epos - pos );

                        long blen = b64data.GetLength();
                        // BYTE * bin_buffer = new BYTE [ blen * 2 ];
                        /*
                            // !DEBUG! dump the base64 data for comparison
                            CStdioFile b64file( _T("uB64Dump.txt"), CFile::typeBinary | CFile::modeWrite | CFile::modeCreate );
                            b64file.Write( b64data.GetBuffer(), blen * 2);
                            b64file.Close();
                         */
                        int decoded_size = 1;
                        //CStringA temp( b64data );
                        //FILE* fp = fopen("B64Dump.txt", "wb");
                        //if (fp) {
                        //    fwrite((void*)temp.GetString(), blen, 1, fp);
                        //    fclose(fp);
                        //}
                        // if ( ! Base64Decode( temp.GetString(), blen, bin_buffer, &decoded_size ) )
                        std::string binString;
                        try {
                            binString = cdr::decodeBase64String(b64data);
                            decoded_size = (int)binString.size();
                        }
                        catch (const wchar_t* whatHappened) {
                            // this is a real failure
                            ErrorLog += _T("<ZIP_ERR>Unable to decode (base64) binary data.</ZIP_ERR>\n");
                            ::AfxMessageBox(whatHappened);
                            // set things up to carry on.
                            //bin_buffer[0] = 0;
                            //decoded_size = 0;
                            return false;
                        }
                        // this shouldn't happen, but if it does we're OK I guess
                        if ( decoded_size > blen )
                        {
                            ErrorLog += _T("<ZIP_ERR>PANIC! Binary data decode overran buffer.</ZIP_ERR>\n");
                            decoded_size = 0;
                        }

                        // first make sure we have data to write
                        if ( decoded_size > 0 )
                        {
                            CStdioFile    zip_file;

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
                                zip_file.Write( binString.data(), decoded_size );
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
    DebugWrite("Unpacking updated files from the SOAP server.\n");
    
    bool success = false;

    // we now have a zipfile on the disk in (hopefully)
    // the directory that is both current and correct
    // now we need to unzip that file...

    // _spawn also flickers a command window on screen so effectively no difference
    // between that and system() other than system being easier to debug.

    CString unzip_cmd = _T(".\\unzip -o -d ") + client_dir + _T( " " ) + fname + _T( " > ") + fname + _T(".out 2> ") + fname + _T(".err"); 
    CStringA temp( unzip_cmd );
    int rc = system( temp.GetString() );

    // We're not really looking at the return code from unzip, because
    // that process will fail when it's trying to replace this program,
    // which will happen if we tell the server we don't have a valid
    // manifest.  Instead we'll check to make sure that we really have
    // what the manifest says we should have.  All the check of rc
    // does is to make sure we actually launched unzip.
    if (rc != -1)
    {
        // file unzipped without detected error
        // yea.
        DebugWrite("Verifying that the new manifest matches our files.\n");
        success = CheckManifestFiles();
        if (!success)
            DebugWrite("Verification failed; we will bail out.\n");
    }
    else
    {
        ErrorLog += _T("<EXEC_ERR>");
        ErrorLog += _T("Unable to execute ") + unzip_cmd;
        CString errorString;
        if (rc == -1)
            errorString.Format(_T("%S"), strerror(errno));
        else
            errorString.Format(_T("%d"), rc);
        DebugWrite(_T("Failure invoking unzip: ") + errorString + _T(".\n"));
        ErrorLog += _T(" : ") + errorString + _T("</EXEC_ERR>\n");
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
            pos += (long)_tcslen( _T("<ZIPFILE>") );
            long epos = manifest_xml.Find( _T("</ZIPFILE>"), pos );
            if ( epos != -1 )
            {
                CString zip_name = manifest_xml.Mid( pos, epos - pos );
                CString zip_req = _T("<ZIPREQ>") + zip_name + _T("</ZIPREQ>");
                
                pb->Advance();

                DebugWrite("Requesting package of updated client files.\n");
                CString zip_response = HttpRoundTrip( zip_req );

                pb->Advance();

                if ( ! RecordServerError( zip_response, _T("ZIPREQ") ) )
                {
                    // we got the zip file as base64 encoded data in an xml file
                    CString fname;
                    // DebugWrite("Saving the package of updated files.\n");
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
            ErrorLog +=
                _T("<XML_ERR doc=DELTA>Missing ZIPFILE tag</XML_ERR>\n");
            ErrorLog += manifest_xml;
        }
    }

    return success;
}

bool CDRTicketStub::ProcessInvarientDeletes( CDRProgress * pb )
{
    CString keeper_files[] = 
    {
        CString( _T( "macros.rlx" )),
        CString( _T( "tbr.rlx" )),
        CString( _T( "xmetal.rlx" )),
        CString( _T( "ctm.rlx" )),
        CString( _T( "journalist.rlx" )),
        CString( _T( "Meeting.rlx" )),
        CString( _T( "openruleset.rlx" ))
    };

    bool success = true;

    CFileFind rlx_hunter;
    
    BOOL have_more = rlx_hunter.FindFile( _T( ".\\Rules\\*.rlx" ) );
    while ( have_more )
    {
        have_more = rlx_hunter.FindNextFile();
        CString found = rlx_hunter.GetFileName();
        bool keeper = false;
        for ( int i = 0; i < sizeof keeper_files / sizeof *keeper_files; i++  )
        {
            if ( ! found.CompareNoCase( keeper_files[ i ] ) )
            {
                // this one is in the list,
                // check the next in directory
                keeper = true;
                break;
            }
        }
        if ( ! keeper )
        {
            // this is where we delete it!
            CString victim = rlx_hunter.GetFilePath();
            CStringA t( victim );
            keeper = false;
            int r = remove( t.GetString() );
            // non zero means error, 
            // ENOENT means it was already gone, which is OK
            if ( r && ( errno != ENOENT ) )
            {
                success = false;

                CString errnoString;
                errnoString.Format(_T("%S"), strerror(errno));
                ErrorLog += _T("<FILE_ERR>");
                ErrorLog += _T("Unable to delete ") + victim + _T(" : ");
                ErrorLog += errnoString;
                ErrorLog += _T("</FILE_ERR>\n");
                DebugWrite(_T("Failure deleting ") + victim +
                           _T(": ") + errnoString + _T(".\n"));
            }
        }
    }

    pb->Advance();

    return success;
}


bool CDRTicketStub::ProcessDeleteList( CString manifest_xml, CDRProgress * pb )
{
    // Start optimistically.
    bool success = true;

    CString app_name = CString( _T( ".\\" ) ) + AfxGetAppName() +
        CString( _T( ".exe" ) );
    /*
    CString a_name = theApp.m_pszAppName;
    CString b_name = theApp.m_pszExeName; 


    DebugWrite( "Possible Names\n" );
    DebugWrite( app_name );
    DebugWrite( "\n" );
    DebugWrite( a_name );
    DebugWrite( "\n" );
    DebugWrite( b_name );
    DebugWrite( "\n" );
    */

    long epos;
    // yea I know big assumptions about valid sections
    long pos = manifest_xml.Find( _T("<DELETE/>") );
    if ( pos != -1 )
    {
        // empty delete tag, we're done
        pb->Advance();
    }
    else
    {
        // look for the inner name tag
        pos = manifest_xml.Find( _T("<DELETE>" ) );
        if ( pos != -1 )
        {
            pos += (long)_tcslen( _T("<DELETE>") );
            epos = manifest_xml.Find( _T("</DELETE>"), pos );
            if ( epos != -1 )
            {
                CString del_list = manifest_xml.Mid( pos, epos - pos );

                long fpos = del_list.Find( _T("<FILE>") );
                while ( fpos != -1 )
                {
                    fpos += (long)_tcslen( _T("<FILE>") );
                    long epos = del_list.Find( _T("</FILE>"), fpos );
                    if ( epos != -1 )
                    {
                        CString fname = del_list.Mid( fpos, epos - fpos );

                        //DebugWrite( "Comparing for self-deletion, does " );
                        //DebugWrite( app_name );
                        //DebugWrite( " match " );
                        //DebugWrite( fname );
                        //DebugWrite( " ?\n" );

                        if ( fname.CompareNoCase( app_name ) )
                        {
                            //DebugWrite( "No, deleting " );
                            //DebugWrite( fname );
                            //DebugWrite( "\n" );

                            // delete the file
                            CStringA t( fname );

                            //!DEBUG!
                            int r = remove( t.GetString() );
                            
                            // non zero means error, 
                            // ENOENT means it was already gone, which is OK
                            if ( r && ( errno != ENOENT ) )
                            {
                                success = false;
                                CString errnoString;
                                errnoString.Format(_T("%S"), strerror(errno));
                                ErrorLog += _T("<FILE_ERR>");
                                ErrorLog += _T("Unable to delete ")
                                         + fname + _T(" : ");
                                ErrorLog += errnoString;
                                ErrorLog += _T("</FILE_ERR>\n");
                                DebugWrite(_T("Failure deleting ") + fname +
                                           _T(": ") + errnoString + _T(".\n"));
                            }
                            else
                            {
                                // we deleted at least one file, hopefully
                                // we'll get them all
                                // XXX BAD LOGIC! RMK 2003-03-09
                                // success = true;
                                pb->Advance();
                            }
                        }
                        else
                        {
                            //DebugWrite( "Yes, skipping self-delete of " );
                            //DebugWrite( fname );
                            //DebugWrite( "\n" );
                        }

                        // keep looking for more file names
                        fpos = del_list.Find( _T("<FILE>"), epos );
                    }
                    else
                    {
                        ErrorLog += _T("<XML_ERR doc=DELTA>Unbalanced FILE ")
                                    _T("tag. Ending DELETE ")
                                    _T("operation.</XML_ERR>\n");
                        DebugWrite("Malformed XML for FILE element in "
                                   "deletion.\n");
                        // this is an exception to the rule,
                        // since we are having success in increments
                        // a failure requires we revert the flag to show
                        // failure
                        success = false;
                        break;
                    }
                }
            }
            else
            {
                ErrorLog += _T("<XML_ERR doc=DELTA>Unbalanced DELETE ")
                            _T("tag.</XML_ERR>\n");
                DebugWrite("Malformed XML for DELETE element.\n");
                success = false;
            }
        }
        else
        {
            ErrorLog +=
                _T("<XML_ERR doc=DELTA>Missing DELETE tag.</XML_ERR>\n");
            DebugWrite("Missing DELETE tag in manifest.\n");
            success = false;
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

bool CDRTicketStub::UpdateFiles( CString &manifest, CString client_dir,
                                 CDRProgress * pb )
{
    bool valid = false;

    DebugWrite("Telling the SOAP server which files we have.\n");
    CString manifest_response = HttpRoundTrip( manifest );
    
    pb->Advance();

    if ( ! RecordServerError( manifest_response, _T("MANIFEST") ) )
    {
        int pos = manifest_response.Find( _T("<DELTA/>") );
        if ( pos != -1 )
        {
            // we got a empty delta, 
            // we're clean roll out true
            // if we delete the list of always delete...
            valid = ProcessInvarientDeletes( pb );
        }
        else
        {
            //    if we got delta info, we need to act on it
            //  only if both actions are successful can we
            //    proceed with a "true" update result
            if ( ! ProcessZipFile( client_dir, manifest_response, pb ) )
            {
                // something went wrong with the zip file
                // jAH 020917 per BKline, delete/rename the manifest
                struct tm *now;
                time_t ts = time( NULL );
                now = localtime( &ts );
                char t_buf[64];
                strftime( t_buf, 60, "%Y%m%d-%H%M%S", now );
                CString bad_name = CDR_MANIFEST_FILE + _T(".BAD.")
                                                     + CString(t_buf);
                ErrorLog += _T("<ZIP_ERR>Zip file could not be unpacked, ")
                            _T("MANIFEST deleted.</ZIP_ERR>\n");

                if ( _wrename( CDR_MANIFEST_FILE, bad_name ) )
                {
                    int err = errno;
                    if (err != ENOENT)
                        ErrorLog += 
                            _T("<ZIP_ERR>Can't delete CDR_MANIFEST.XML")
                            _T("</ZIP_ERR>");
                }
                                    
            }
            else
            {
                // unzipped files without problem
                valid = true;

                pb->Advance();

                valid &= ProcessInvarientDeletes( pb );
                valid &= ProcessDeleteList( manifest_response, pb );

                pb->Advance();
            }
        }
    }

    return valid;
}

void CDRTicketStub::BequeathEnvironment( CString user, CString session,
                                         CString server, CString port )
{
    CStringA uenv = "CDRUser="  + CStringA( user );
    CStringA senv = "CDRSession="  + CStringA( session );
    CStringA serv_env = "CDR_HOST=" + CStringA( server );
    CStringA port_env = "CDR_PORT=" + CStringA( port );

    // these change current environment settings
    _putenv( (LPCSTR)uenv );
    _putenv( (LPCSTR)senv );
    _putenv( (LPCSTR)serv_env );
    _putenv( (LPCSTR)port_env );

    //DebugWrite( "-- Setting Environment\n" );
    //DebugWrite( (CString)uenv );
    //DebugWrite( "\n" );
    //DebugWrite( (CString)senv );
    //DebugWrite( "\n" );
    //DebugWrite( (CString)serv_env );
    //DebugWrite( "\n" );
    //DebugWrite( (CString)port_env );
    //DebugWrite( "\n" );
    //DebugWrite( "-- Done Setting Environment\n" );
}

bool CDRTicketStub::LaunchCDR( CString app )
{
    char * my_args[3];

    //my_args[0] = aapp.GetBuffer();
    my_args[0] = "dummy_arg";
    my_args[1] = NULL;
    my_args[2] = NULL;

    CStringA aapp( app );

    if ( !keepLoader && PathFileExists( _T( "CDRLoaderUpdated.cmd" ) ) )
    {
        //DebugResume();
        DebugWrite( "Modified CDRLoader installed; "
                    "invoking CDRLoaderUpdate.cmd.\n" );

        // we need to relaunch ourselves to handle new options
        //CStringA reflexive_launch = "C:\\WINNT\\system32\\cmd.exe";
        CStringA reflexive_launch = "CDRLoaderUpdated.cmd";
        my_args[0] = reflexive_launch.GetBuffer();

        //DebugWrite( "Closing debug prior relaunch.\n" );
        DebugEnd();

        // null pointer for my_env inhierts current
        int err = (int)_execve( reflexive_launch.GetBuffer(), my_args, NULL );
        DebugResume();
        CString errString;
        errString.Format(_T("Execution failed: %S.\n"),
                         strerror(errno));
        DebugWrite(errString);

        // failed after all
        ErrorLog += _T("<EXEC_ERR>");
        ErrorLog += _T("Unable to relaunch self ") +
                     CString( reflexive_launch ) + _T(" : ");
        ErrorLog += CString( strerror( errno ) );
        ErrorLog += _T("</EXEC_ERR>\n");

    }
    else
    {
        //char * tprog =
        //    "\"C:\\Program Files\\SoftQuad\\Xmetal 3\\xmetal3.exe\"";
        //char * tprog = "C:\\WINNT\\system32\\cmd.exe";

        char prog_name[512];
        strncpy( prog_name, aapp.GetBuffer(), aapp.GetLength() );
        prog_name[ aapp.GetLength() ] = '\0';


        // null pointer for my_env inhierts current
        DebugWrite(_T("Executing ") + app + _T(".\n"));
        DebugEnd();
        int err = (int)_execve( aapp.GetBuffer(), my_args, NULL );
        DebugResume();
        CString errString;
        errString.Format(_T("Execution failed; errno: %d.\n"), errno);
        DebugWrite(errString);
        //int err = _execve( tprog, my_args, NULL );

        ErrorLog += _T("<EXEC_ERR>");
        ErrorLog += _T("Unable to execute ") + CString( aapp ) + _T(" : ");
        ErrorLog += CString( strerror( errno ) );
        ErrorLog += _T("</EXEC_ERR>\n");

    }
    return false;
}
