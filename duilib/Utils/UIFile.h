#pragma once
#include <string>

namespace DuiLib {

class UILIB_API CXFile
{

public:
	static bool LoadFile(STRINGorID fileName, BYTE*& pData, DWORD& dwSize); //LoadFile��ȥ���ⲿ��Ҫ����FreeData�ͷ�
	static void FreeData(BYTE* pData);
};

}
