
#pragma once
namespace DuiLib {

/*
���Win7�Ĳ�ͬ��DPI�ȼ�����������������
DPI:96	���죺100%
DPI:120	���죺125%
DPI:144	���죺150%
DPI:192 ���죺200%
*/
enum E_RES_QUARITY_TYPE{ //��Դ�ļ�����
	kResQuarityTypeNormal = 0,  // [96, 132]
	kResQuarityTypeMiddle = 1,  // [133, 192]
	kResQuarityTypeHigh = 2	 // [193, max]
};

enum E_DPI_TYPE { //Dpi�ȼ�
	kDpiType96 = 96,
	kDpiType120 = 120,
	kDpiType144 = 144,
	kDpiType192 = 192
};

enum E_SCREEN_SCALING_TYPE  { //�����������
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

	int  m_nScaling; //�޸�unsigned-->int vito
	int  m_nResQuarity;
};

}
