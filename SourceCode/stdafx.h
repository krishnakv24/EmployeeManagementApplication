#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN           
#endif

#include "targetver.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS     

#define _AFX_ALL_WARNINGS

#include <afxwin.h>        
#include <afxext.h>        
#include <afxdisp.h>       

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>         
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            
#endif 

#include <afxcontrolbars.h>    
#include <utility>
#include <map>
#include <memory>
#include <fstream> 
#include <algorithm>
#include <set>
#include <string>
#include <mutex>
#include <ctime>
#include <iostream>
#include <gdiplus.h>  
#include <thread>

#pragma comment (lib, "Gdiplus.lib") 
using namespace Gdiplus;
using namespace std;

#include "stEmpData.h"
#include "AppLogger.h"
#include "uiProgressBarDlg.h"

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


