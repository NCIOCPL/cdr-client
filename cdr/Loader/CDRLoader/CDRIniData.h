#pragma once

class CDRIniData
{
public:
	CDRIniData(void);
	~CDRIniData(void);

	void ReadOptions( void );
	void WriteOptions( void );


	/*
	*	yes there should be gets & sets
	*	but this is turning into a hack anyway...
	*	( in the traditional way: we need a little utility to do this
	*	while we are developing, no it'll be used after we're in production
	*	whoops add this and that and the other feature... )
	*/
	CString ticket_Server;
	CString ticket_Port;
	CString cdr_Server;
	CString cdr_Port;
	CString last_User;

	static const CString CURRENT_VERSION;
};
