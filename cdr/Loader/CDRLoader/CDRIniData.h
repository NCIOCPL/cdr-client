#pragma once


class CDRIniData
{
public:
	CDRIniData(void);
	~CDRIniData(void);

	void ReadOptions( void );
	void WriteOptions( void );

	int GetCurrentServer( void );
	void SetCurrentServer( int cs );

	enum SERVER_NDX { CDR_SRV_PROD = 0, CDR_SRV_TEST, CDR_SRV_DEV, CDR_SRV_LEN };

	/*
	*	yes there should be gets & sets
	*	but this is turning into a hack anyway...
	*	( in the traditional way: we need a little utility to do this
	*	while we are developing, no it'll be used after we're in production
	*	whoops add this and that and the other feature... )
	*/
	struct ServerStrings 
	{
		CString ticket_Server;
		CString ticket_Port;
		CString cdr_Server;
		CString cdr_Port;
	};
	CString last_User;
	CString default_Server;
	ServerStrings servers[ CDR_SRV_LEN ];

	static const CString CURRENT_VERSION;
};
