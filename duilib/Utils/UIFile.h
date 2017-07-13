#pragma once
#include <string>

namespace DuiLib {

class UILIB_API CXFile
{

public:
	static bool LoadFile(STRINGorID fileName, BYTE*& pData, DWORD& dwSize); //LoadFile出去后，外部需要调用FreeData释放
	static void FreeData(BYTE* pData);
};

}
