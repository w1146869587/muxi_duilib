#include "StdAfx.h"
#include "AppWnd.h"

CAppWnd::CAppWnd(void) {
}

CAppWnd::~CAppWnd(void) {
}

LRESULT CAppWnd::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {
	__super::OnCreate(uMsg, wParam, lParam, bHandled);
	this->CenterWindow();

	return 0;
}

DuiLib::CDuiString CAppWnd::GetSkinFolder() {
	return _T("appwnd");
}

DuiLib::CDuiString CAppWnd::GetSkinFile() {
	return _T("app_wnd.xml");
}

UILIB_RESOURCETYPE CAppWnd::GetResourceType() const {
#ifdef _DEBUG
	return UILIB_FILE;
#else
	return UILIB_ZIPRESOURCE;
#endif
}

LPCTSTR CAppWnd::GetResourceID() const {
	return MAKEINTRESOURCE(IDR_ZIPRES1);
}

LPCTSTR CAppWnd::GetWindowClassName( void ) const {
	return _T("JGAppWnd");
}

LRESULT CAppWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
 	return NULL;
}

LRESULT CAppWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) {
	return NULL;
}



