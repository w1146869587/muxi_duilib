#pragma once
namespace DuiLib
{
	class UILIB_API CUIShadowWnd : public CWindowWnd {
	public:
		CUIShadowWnd(const CDuiString&	shadowImg);
		virtual ~CUIShadowWnd();

	public:
		virtual LPCTSTR GetWindowClassName() const;
		virtual UINT GetClassStyle() const;
		virtual void OnFinalMessage(HWND hWnd);
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		void SetWndPos();
		bool Init(CPaintManagerUI* pManager);

	private:
		HBITMAP _createBGBitmap(HDC hDC, int cx, int cy);
		void _rePaint();

	private:
		CDuiString	m_shadowImg;
		CPaintManagerUI* m_pManager;
		HWND m_hPWnd;
	};
}

