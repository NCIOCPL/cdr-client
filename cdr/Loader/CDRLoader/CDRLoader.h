// CDRLoader.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "CDRIniData.h"


// CCDRLoaderApp:
// See CDRLoader.cpp for the implementation of this class
//

class CCDRLoaderApp : public CWinApp
{
public:
	CCDRLoaderApp();

	CDRIniData	ini_Data;

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCDRLoaderApp theApp;