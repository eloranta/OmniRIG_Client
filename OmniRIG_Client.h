// OmniRIG_Client.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COmniRIG_ClientApp:
// See OmniRIG_Client.cpp for the implementation of this class
//

class COmniRIG_ClientApp : public CWinApp
{
public:
	COmniRIG_ClientApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern COmniRIG_ClientApp theApp;