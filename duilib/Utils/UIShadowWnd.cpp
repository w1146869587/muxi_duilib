#include "StdAfx.h"
#include "UIShadowWnd.h"

namespace DuiLib {
	const int kPaddingSize = 10; //相对父窗口上下左右都加7个像素，作为阴影

	CUIShadowWnd::CUIShadowWnd(const CDuiString&	shadowImg)
		:m_shadowImg(shadowImg) {
	}

	CUIShadowWnd::~CUIShadowWnd() {
	}

	bool CUIShadowWnd::Init(CPaintManagerUI* pManager) {
		if (pManager == nullptr) {
			return false;
		}

		m_pManager = pManager;
		m_hPWnd = pManager->GetPaintWindow();

		if (NULL != m_hPWnd) {
			RECT rc = { 0 };
			::GetWindowRect(m_hPWnd, &rc);
			auto left = rc.left - kPaddingSize;
			auto top = rc.top - kPaddingSize;
			auto width = (rc.right - rc.left) + (2 * kPaddingSize); //父窗口宽度加上左右的padding
			auto height = (rc.bottom - rc.top) + (2 * kPaddingSize); //父窗口高度加上上下的padding
			HWND hWnd = Create(m_hPWnd, _T("UIShadowWnd"), WS_POPUP, WS_EX_LAYERED | WS_EX_TOOLWINDOW, left, top, width, height, NULL);
			if (NULL != hWnd) {
				return true;
			}
		}

		return false;
	}

	void CUIShadowWnd::OnFinalMessage(HWND hWnd) {
		delete this;
	}

	LPCTSTR CUIShadowWnd::GetWindowClassName() const {
		return _T("UIShadowWnd");
	}

	UINT CUIShadowWnd::GetClassStyle() const {
		return UI_CLASSSTYLE_FRAME;
	}
	 
	LRESULT CUIShadowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if( uMsg == WM_CREATE )  {
			_rePaint();	
		} else if (uMsg == WM_WINDOWPOSCHANGED) {
			::SetWindowPos(m_hWnd, m_hPWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
		} else if (uMsg == WM_MOUSEACTIVATE) {
			return MA_NOACTIVATE;
		} else if( uMsg == WM_SIZE ) {
			_rePaint();
		} else if(WM_ACTIVATE == uMsg) {
			int iActive = LOWORD(wParam);
			if (WA_CLICKACTIVE == iActive || WA_ACTIVE == iActive) {
				if (NULL != m_hPWnd) {
					::SetWindowPos(m_hWnd, m_hPWnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
					::BringWindowToTop(m_hPWnd);
					::SetForegroundWindow(m_hPWnd);
					return NULL;
				}
			}
		}

		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

	void CUIShadowWnd::SetWndPos() {
		if (NULL != m_hPWnd) {
			RECT rc = {0};
			::GetWindowRect(m_hPWnd, &rc);

			auto left = rc.left - kPaddingSize;
			auto top = rc.top - kPaddingSize;
			auto width = (rc.right - rc.left) + (2 * kPaddingSize); 
			auto height = (rc.bottom - rc.top) + (2 * kPaddingSize); 
			::SetWindowPos(m_hWnd, m_hPWnd, left, top, width, height, SWP_NOACTIVATE);
		}
	}

	void CUIShadowWnd::_rePaint() {
		RECT rc = { 0 };
		if (::GetClientRect(m_hWnd, &rc) == FALSE) {
			return;
		}

		auto width = rc.right - rc.left;
		auto height = rc.bottom - rc.top;
		if (width <= 0 || height <= 0) {
			return;
		}

		auto hDCPaint = ::GetDC(m_hWnd);
		if (NULL == hDCPaint) {
			return;
		}

		auto hDCBackground = ::CreateCompatibleDC(hDCPaint);
		if (NULL == hDCBackground) {
			return;
		}

		HBITMAP hbmpBackground = _createBGBitmap(hDCPaint, width, height);
		if (NULL == hbmpBackground) {
			return;
		}

		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hDCBackground, hbmpBackground);

		CDuiString cornerImage;
		cornerImage.Format(_T("file='%s' corner='17,17,17,17'"), m_shadowImg); // 对于window_border.png进行9宫格切割corner(17, 17, 17, 17)，用于窗口拉伸, 4个角不拉伸
		DuiLib::CRenderEngine::DrawImageString(hDCBackground, m_pManager, rc, rc, cornerImage, NULL);

		RECT rcShadowWnd = { 0 };
		::GetWindowRect(m_hWnd, &rcShadowWnd);

		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		POINT pt = { rcShadowWnd.left, rcShadowWnd.top };
		SIZE sz = { width, height };
		POINT ptSrc = { 0, 0 };
		UpdateLayeredWindow(m_hWnd, hDCPaint, &pt, &sz, hDCBackground, &ptSrc, 0, &bf, ULW_ALPHA);

		::SelectObject(hDCBackground, hOldBitmap);
		if (hDCBackground != NULL) {
			::DeleteDC(hDCBackground);
		}

		if (hbmpBackground != NULL) {
			::DeleteObject(hbmpBackground);
		}

		::ReleaseDC(m_hWnd, hDCPaint);
	}

	HBITMAP CUIShadowWnd::_createBGBitmap(HDC hDC, int cx, int cy) {
		if (NULL == hDC) {
			return NULL;
		}

		BITMAPINFO	bitmapInfo;
		memset(&bitmapInfo, 0, sizeof(BITMAPINFO));
		bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo.bmiHeader.biWidth = cx;
		bitmapInfo.bmiHeader.biHeight = cy;
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biBitCount = 32;
		bitmapInfo.bmiHeader.biSizeImage = 0;
		bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
		bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
		bitmapInfo.bmiHeader.biClrUsed = 0;
		bitmapInfo.bmiHeader.biClrImportant = 0;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;

		HBITMAP hBitmap = ::CreateDIBSection(hDC, &bitmapInfo, DIB_RGB_COLORS, NULL, NULL, NULL);
		return hBitmap;
	}
}

