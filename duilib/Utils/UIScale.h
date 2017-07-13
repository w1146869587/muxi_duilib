
#pragma once
namespace DuiLib {

/*
借鉴Win7的不同的DPI等级对字体的拉伸比例：
DPI:96	拉伸：100%
DPI:120	拉伸：125%
DPI:144	拉伸：150%
DPI:192 拉伸：200%
*/
enum E_RES_QUARITY_TYPE{ //资源文件类似
	kResQuarityTypeNormal = 0,  // [96, 132]
	kResQuarityTypeMiddle = 1,  // [133, 192]
	kResQuarityTypeHigh = 2	 // [193, max]
};

enum E_DPI_TYPE { //Dpi等级
	kDpiType96 = 96,
	kDpiType120 = 120,
	kDpiType144 = 144,
	kDpiType192 = 192
};

enum E_SCREEN_SCALING_TYPE  { //字体拉伸比例
	kScreenScalingType100 = 100,
	kScreenScalingType125 = 125,
	kScreenScalingType150 = 150,
	kScreenScalingType200 = 200
};

class UILIB_API CScale
{
private:
	CScale(void);

public:
	virtual ~CScale(void);

public:
	int XScale(int x);
	void XScale(int *pX);
	void SizeScale(SIZE *pSize);
	void PointScale(POINTL *pPoint);
	void RectScale(CDuiRect *pRect);
	void RectScale(RECT *pRect);

public:
	static CScale* GetInstance();

private:
	int _getDpi();
	void _initScale();

private:
	static CScale* m_pInst;

	int  m_nScaling; //修改unsigned-->int vito
	int  m_nResQuarity;
};

}
