#include "stdafx.h"
#include "EDataDisplay.h"
#include "EDataDisplayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CEDataDisplayApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CEDataDisplayApp::CEDataDisplayApp(): m_pDlgLoadProgress(NULL)
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;	
}

CEDataDisplayApp theApp;

/**
* Initializes the application instance.
*
* - Configures the application logger and logs the startup.
* - Ensures that only one instance of the application runs.
* - Initializes common controls and MFC, enabling support for shell controls and setting the visual style.
* - Configures the registry key for application settings.
* - Displays the main dialog and handles user responses.
* - Cleans up resources before exiting.
*
*/
BOOL CEDataDisplayApp::InitInstance()
{
	CAppLogger::getInstance().setLevel(LogLevel::DBUG);
	CAppLogger::getInstance().logToFile(GetExePath().c_str(), L"AppLog.log");
	LOG_INFO(L"Application started");

	if (IsSameProgramExecuted())
		return FALSE;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CShellManager *pShellManager = new CShellManager;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("Employee Management Application"));

	CEDataDisplayDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	return FALSE;
}

/**
* Checks if another instance of the application is already running.
*
* - Creates a named mutex to ensure only one instance of the application runs.
* - If the mutex already exists, shows a warning message and exits.
* - Cleans up the mutex handle if the application is already running.
*
*/
bool CEDataDisplayApp::IsSameProgramExecuted()
{
	m_hOneExeMutex = ::CreateMutex(NULL, FALSE, L"EDataDisplay");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		if (NULL != m_hOneExeMutex)
		{
			if (NULL != m_hOneExeMutex)
			{
				CloseHandle(m_hOneExeMutex);
				m_hOneExeMutex = NULL;
			}
		}
		LOG_ERROR(L"Employee Management Application Already Running");
		MessageBox(NULL, L"Employee Management Application Already Running", L"Warning", MB_ICONEXCLAMATION | MB_OK);
		return true;
	}
	return false;
}

/**
* Initializes and displays the progress bar dialog as a modal window centered on the screen.
*
* - Creates an instance of `CuiProgressBarDlg` and assigns it to `m_pDlgLoadProgress`.
* - Sets the dialog to be system modal using `ModifyStyle` to ensure it remains on top.
* - Centers the dialog on the screen using `CenterWindow`.
* - Displays the dialog with the default show state using `ShowWindow`.
*/
void CEDataDisplayApp::ShowPopupInitialize()
{
	if (m_pDlgLoadProgress == NULL)
	{
		m_pDlgLoadProgress = new CuiProgressBarDlg;
		m_pDlgLoadProgress->Create(IDD_EDATA_PROGRESS_BAR);
		m_pDlgLoadProgress->ModifyStyle(0, DS_SYSMODAL);
		m_pDlgLoadProgress->CenterWindow();
		m_pDlgLoadProgress->ShowWindow(SW_SHOWDEFAULT);
	}
}

/**
* Hides and destroys the progress bar dialog, releasing allocated resources.
*
* - Checks if `m_pDlgLoadProgress` is not null before proceeding to avoid dereferencing null pointers.
* - Destroys the window associated with the progress bar dialog using `DestroyWindow`.
* - Deletes the `m_pDlgLoadProgress` pointer to free up memory.
* - Sets `m_pDlgLoadProgress` to `NULL` to avoid dangling pointers.
*/
void CEDataDisplayApp::HidePopupInitialize()
{
	if (m_pDlgLoadProgress)
	{
		m_pDlgLoadProgress->DestroyWindow();
		delete m_pDlgLoadProgress;
		m_pDlgLoadProgress = NULL;
	}
}

/**
* Cleans up resources before the application exits.
*
* - Closes the mutex handle if it was created to ensure proper cleanup.
* - Calls the base class's `ExitInstance` to perform standard MFC cleanup.
*
*/
int CEDataDisplayApp::ExitInstance()
{
	if (NULL != m_hOneExeMutex)
	{
		CloseHandle(m_hOneExeMutex);
		m_hOneExeMutex = NULL;
	}

	if (gdiplusToken != NULL)
	{
		GdiplusShutdown(gdiplusToken);
	}

	LOG_INFO(L"Application Closed");
	return CWinApp::ExitInstance();
}

/**
* Retrieves the directory path of the executable file.
*
* Obtains the full path of the running executable and extracts the directory
* path by removing the executable's file name. Returns the path as a wide string.
*
*/
wstring CEDataDisplayApp::GetExePath()
{
	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);

	std::wstring exePath(buffer);
	size_t pos = exePath.find_last_of(L"\\/");
	if (pos != std::wstring::npos)
	{
		exePath = exePath.substr(0, pos);
	}
	return exePath;
}

