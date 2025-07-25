// OmniRIG_Client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "OmniRIG_Client.h"
#include "OmniRIG_ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COmniRIG_ClientApp

BEGIN_MESSAGE_MAP(COmniRIG_ClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// COmniRIG_ClientApp construction

COmniRIG_ClientApp::COmniRIG_ClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only COmniRIG_ClientApp object

COmniRIG_ClientApp theApp;


// COmniRIG_ClientApp initialization

BOOL COmniRIG_ClientApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	SetRegistryKey(_T("OmniRig Client Demo"));

	COmniRIG_ClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}
