#include "StdAfx.h"
#include "UIScale.h"

namespace DuiLib {

	CScale* CScale::m_pInst = NULL;
	CScale::CScale(void)
		: m_nScaling(0)
		, m_nResQuarity(kResQuarityTypeNormal) {
	}

	CScale::~CScale(void) {
	}


	int CScale::_getDpi() {
		HWND hWnd = ::GetDesktopWindow();
		HDC hDC = ::GetDC(hWnd);

		if (nullptr == hWnd || nullptr == hDC){
			return kDpiType96;
		}

		auto dpi = ::GetDeviceCaps(hDC, LOGPIXELSX);
		::ReleaseDC(hWnd, hDC);

		return dpi;
	}

	void CScale::_initScale() {
		auto dpi = _getDpi();
		m_nScaling = (dpi * kScreenScalingType100) / kDpiType96;

		if (m_nScaling <= kScreenScalingType125){
			m_nResQuarity = kResQuarityTypeNormal; 
			return;
		} 
		
		if (m_nScaling > kScreenScalingType125 && m_nScaling <= kScreenScalingType150){
			m_nResQuarity = kResQuarityTypeMiddle;
			return;
		} 
		
		if (m_nScaling > kScreenScalingType150){
			m_nResQuarity = kResQuarityTypeHigh;
			return;
		}
	}

	void CScale::RectScale(CDuiRect *pRect) {
		if (kScreenScalingType100 == m_nScaling){
			return;
		}

		pRect->left = XScale(pRect->left);
		pRect->top = XScale(pRect->top);
		pRect->right = XScale(pRect->right);
		pRect->bottom = XScale(pRect->bottom);
	}

	void CScale::RectScale(RECT *pRect) {
		if (kScreenScalingType100 == m_nScaling){
			return;
		}

		pRect->left = XScale(pRect->left);
		pRect->top = XScale(pRect->top);
		pRect->right = XScale(pRect->right);
		pRect->bottom = XScale(pRect->bottom);
	}

	void CScale::SizeScale(SIZE *pSize) {
		if (kScreenScalingType100 == m_nScaling){
			return;
		}

		pSize->cx = XScale(pSize->cx);
		pSize->cy = XScale(pSize->cy);
	}

	void CScale::PointScale(POINTL *pPoint) {
		if (kScreenScalingType100 == m_nScaling){
			return;
		}

		pPoint->x = XScale(pPoint->x);
		pPoint->y = XScale(pPoint->y);
	}

	int CScale::XScale(int x) {
		if (kScreenScalingType100 == m_nScaling){
			return x;
		}

		x = (x * m_nScaling) / kScreenScalingType100;
		return x;
	}

	void CScale::XScale(int *pX) {
		if (kScreenScalingType100 == m_nScaling){
			return;
		}

		auto x = ((*pX) * m_nScaling) / kScreenScalingType100;
		*pX = x;
	}

	CScale* CScale::GetInstance() {
		if (nullptr == m_pInst) {
			m_pInst = new CScale();
			m_pInst->_initScale();
		}

		return m_pInst;
	}
}
