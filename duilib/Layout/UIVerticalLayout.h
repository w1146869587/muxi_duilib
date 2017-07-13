#ifndef __UIVERTICALLAYOUT_H__
#define __UIVERTICALLAYOUT_H__

#pragma once

namespace DuiLib
{
	class UILIB_API CVerticalLayoutUI : public CContainerUI
	{
	public:
		CVerticalLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		void SetSepHeight(int iHeight);
		int GetSepHeight() const;
		void SetSepImmMode(bool bImmediately);
		bool IsSepImmMode() const;

		/*void SetSepNormalImage(LPCTSTR pstrImage);
		LPCTSTR GetSepNormalImage();
		void SetSepHotImage(LPCTSTR pstrImage);
		LPCTSTR GetSepHotImage();
		void SetSepPushedImage(LPCTSTR pstrImage);
		LPCTSTR GetSepPushedImage();
		void SetSepDisabledImage(LPCTSTR pstrImage);
		LPCTSTR GetSepDisabledImage();

		void SetSepImageHeight(int iHeight);
		int GetSepImageHeight() const;

		void SetSepImageWidth(int iWidth);
		int GetSepImageWidth() const;*/

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoEvent(TEventUI& event);

		void SetPos(RECT rc, bool bNeedInvalidate = true);
		void DoPostPaint(HDC hDC, const RECT& rcPaint);

		RECT GetThumbRect(bool bUseNew = false) const;

		//virtual void PaintStatusImage(HDC hDC) override;

	protected:
		int m_iSepHeight;
		UINT m_uButtonState;
		POINT ptLastMouse;
		RECT m_rcNewPos;
		bool m_bImmMode;

		/*TDrawInfo m_diSepNormalImage;
		TDrawInfo m_diSepHotImage;
		TDrawInfo m_diSepPushedImage;
		TDrawInfo m_diSepDisabledImage;

		int m_iSepImageHeight;
		int m_iSepImageWidth;*/

	};
}
#endif // __UIVERTICALLAYOUT_H__
