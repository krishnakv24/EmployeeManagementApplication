#pragma once
#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"	

class CEDataDisplayApp : public CWinApp
{
public:
	CEDataDisplayApp();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()	
private:
	HANDLE              m_hOneExeMutex = NULL;

	GdiplusStartupInput  gdiplusStartupInput;
	ULONG_PTR            gdiplusToken;
	CuiProgressBarDlg    *m_pDlgLoadProgress;
private:
	bool IsSameProgramExecuted();
public:
	wstring GetExePath();
	void ShowPopupInitialize();
	void HidePopupInitialize();
};
extern CEDataDisplayApp theApp;