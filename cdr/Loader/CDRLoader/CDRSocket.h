/***************************************************
*	CDRSocket
*	
*		Extracted (cut & paste) from client/CDRUtil 
*		so it can be used without pulling in all the 
*		references to XMetal's export COM functions
*
***************************************************/

#ifndef CDR_SOCKET_H_
#define CDR_SOCKET_H_

	#include <string>
	#include <winsock.h>

	/**
	* Wrapper for socket communication between the CDR client and server.
	*/
	class CdrSocket 
	{
		public:
			static CString sendCommand(const CString& command);
			static void setSessionString(const CString& s) { sessionString = s; }
			static bool loggedOn() { return !sessionString.IsEmpty(); }
			static const CString getSessionString() { return sessionString; }
			static CString errResponse(const CString& err);

		private:
			int sock;
			enum { CDR_SOCK = 2019 };
			CdrSocket();
			std::string read();
			struct Init 
			{
				Init();
				~Init();
				WSAData wsaData;
				static Init init;
			};
			static CString sessionString;
	};

#endif	// CDR_SOCKET_H_