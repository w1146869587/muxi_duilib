// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma warning(disable : 4099)

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>
#include <atlwin.h> // for CWindowImpl

#include <afxcoll.h>

// Windows Header Files:
#include <windows.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>
#include <atlimage.h>
// TODO: reference additional headers your program requires here

#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

#include "UIlib.h"
using namespace DuiLib;

extern HWND g_hWnd;
#include "AppWnd.h"
extern std::shared_ptr<CAppWnd> g_appWnd;

#include "Resource.h"


// #ifdef _DEBUG  
//     #pragma comment(lib, "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win32\\vld.lib")
// #endif
