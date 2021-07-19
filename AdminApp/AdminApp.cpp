
// AdminApp.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "AdminApp.h"
#include "AdminAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdminAppApp

BEGIN_MESSAGE_MAP(CAdminAppApp, CWinApp)
END_MESSAGE_MAP()


// CAdminAppApp construction

CAdminAppApp::CAdminAppApp()
{
}


// The one and only CAdminAppApp object

CAdminAppApp theApp;


// CAdminAppApp initialization

BOOL CAdminAppApp::InitInstance()
{
	CWinApp::InitInstance();

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CAdminAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
	return FALSE;
}



