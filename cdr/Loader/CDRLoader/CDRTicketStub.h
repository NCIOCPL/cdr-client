#pragma once

#include "DRProgress.h"

class CDRTicketStub
{
public:
	CDRTicketStub(void);
	virtual ~CDRTicketStub(void);

	void SetHttpServer( CString serv );

	void InitializeFileLocation( CString manifest_file );

	CString GetLocalTicket( CString manifest_xml );
	CString GetLocalManifest( void );

	CString LoadFile( CString fname );

	CString HttpRoundTrip( CString &data );
	bool ValidateTicket( CString &ticket );
	bool UpdateFiles( CString &manifest, CString client_dir, CDRProgress * pb );

	bool RecordServerError( CString soap_xml, CString operation );

	bool ProcessZipFile( CString client_dir, CString manifest_xml, CDRProgress * pb );
	bool ProcessDeleteList( CString manifest_xml, CDRProgress * pb );
	bool ProcessInvarientDeletes( CDRProgress * pb );

	bool SaveZipFile( CString zip_xml, CString &fname );
	bool ExecuteZipFile( CString client_dir, CString fname );

	CString GetErrorLog( void );

	bool LaunchCDR( CString app );
	static void BequeathEnvironment( CString user, CString session, CString server, CString port );

	CString CDR_CLIENT_PATH;
	CString CDR_MANIFEST_FILE;
	CString ErrorLog;
	CString http_Server;

	static const CString REQ_TEMPLATE;
};
