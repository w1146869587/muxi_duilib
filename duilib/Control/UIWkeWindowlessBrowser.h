/************************************************************************/
/* 
    Webkit浏览器控件
*/
/************************************************************************/


#ifndef WKE_WINDOWLESS_BROWSER_H
#define WKE_WINDOWLESS_BROWSER_H
#include <map>

#include "wke\include\wke.h"

namespace DuiLib
{


#pragma once
#include <map>
	class UILIB_API CWkeWindowlessUI : public CControlUI, public _wkeBufHandler
	{
	public:
		CWkeWindowlessUI(void);
		~CWkeWindowlessUI(void);

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		bool IsWantTab();
		void SetWantTab(bool bWantTab = true);
		void DoEvent(TEventUI& event);
		void onBufUpdated(const HDC hdc, int x, int y, int cx, int cy);
		void SetPos(RECT rc, bool bNeedInvalidate = true);
		void PaintBkImage(HDC hDC);
		void InitBrowser(UINT nTimerID);
		void LoadUrl(LPCTSTR szUrl); 
		void SetFile(const wstring& strValue);
		void SetClientHandler(const wkeClientHandler* handler);
		void SetCallbackFunc(std::string funcName, jsNativeFunction callBackFunc, int argCount);
		void SetCallBackMap(const std::map<std::string, std::tuple<jsNativeFunction, int>>& mapCallback);


		void SetParentHwnd(HWND hwnd);
		void RunJs(const utf8* js);

	protected:
		wkeWebView m_webView;
		bool m_bWantTab;
		std::map<std::string, std::tuple<jsNativeFunction, int>> m_mapFunc;

	public:
		static HWND m_hOuterWnd; //通常是某个IM窗口



	};

}

#endif

