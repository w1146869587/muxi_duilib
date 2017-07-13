//
// main.cpp: code by vito in 2017.7.13
// 
//

#include "stdafx.h"
#include "main.h"
#include "AppWnd.h"
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

CComModule m_gComModule;
static HMODULE g_hRes = nullptr;
HWND g_hWnd;
std::shared_ptr<CAppWnd> g_appWnd;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Boot Windows Common Controls (for the ToolTip control)
	INITCOMMONCONTROLSEX ctrlEx;
	ctrlEx.dwSize = sizeof(ctrlEx);
	ctrlEx.dwICC = ICC_WIN95_CLASSES;
	::InitCommonControlsEx(&ctrlEx);
	::LoadLibrary(_T("msimg32.dll"));

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	::CoInitialize(NULL);
	::OleInitialize(NULL);

	m_gComModule.Init(0, hInstance);

	AfxGetModuleState()->m_pCurrentWinApp = new CWinApp;
	AfxGetModuleState()->m_lpszCurrentAppName = _T("");
	AfxGetModuleState()->m_hCurrentInstanceHandle = GetModuleHandle(NULL);

	//Set path and resources path etc.
	CPaintManagerUI::SetInstance(hInstance);
	CDuiString szPath = CPaintManagerUI::GetInstancePath() + _T("skin");
	CPaintManagerUI::SetResourcePath(szPath);

	g_appWnd = std::make_shared<CAppWnd>();
	if (!g_appWnd) {
		return 0;
	}

	g_appWnd->Create(NULL, _T("AppWnd"), UI_WNDSTYLE_FRAME & ~WS_VISIBLE, WS_EX_STATICEDGE | WS_EX_APPWINDOW);
	::ShowWindow(*g_appWnd, SW_SHOW);

	AfxGetApp()->m_pMainWnd = CWnd::FromHandle(g_appWnd->GetHWND());
	g_hWnd = g_appWnd->GetHWND();
	//g_appWnd->OnUIInitEnd();

	ASSERT_VALID(AfxGetMainWnd());

	CPaintManagerUI::MessageLoop();
	CPaintManagerUI::Term();

	m_gComModule.Term();

	GdiplusShutdown(gdiplusToken);

	::OleUninitialize();
	::CoUninitialize();

	return 0;
}