#include "StdAfx.h" 
#include "UIFlash.h"  

///////////////////////////////////////////////////////////////////////////////////////  
DECLARE_HANDLE(HZIP);   // An HZIP identifies a zip file that has been opened  
typedef DWORD ZRESULT;
typedef struct
{
	int index;                 // index of this file within the zip  
	char name[MAX_PATH];       // filename within the zip  
	DWORD attr;                // attributes, as in GetFileAttributes.  
	FILETIME atime, ctime, mtime;// access, create, modify filetimes  
	long comp_size;            // sizes of item, compressed and uncompressed. These  
	long unc_size;             // may be -1 if not yet known (e.g. being streamed in)  
} ZIPENTRY;
typedef struct
{
	int index;                 // index of this file within the zip  
	TCHAR name[MAX_PATH];      // filename within the zip  
	DWORD attr;                // attributes, as in GetFileAttributes.  
	FILETIME atime, ctime, mtime;// access, create, modify filetimes  
	long comp_size;            // sizes of item, compressed and uncompressed. These  
	long unc_size;             // may be -1 if not yet known (e.g. being streamed in)  
} ZIPENTRYW;
#define OpenZip OpenZipU  
#define CloseZip(hz) CloseZipU(hz)  
extern HZIP OpenZipU(void *z, unsigned int len, DWORD flags);
extern ZRESULT CloseZipU(HZIP hz);
#ifdef _UNICODE  
#define ZIPENTRY ZIPENTRYW  
#define GetZipItem GetZipItemW  
#define FindZipItem FindZipItemW  
#else  
#define GetZipItem GetZipItemA  
#define FindZipItem FindZipItemA  
#endif  
extern ZRESULT GetZipItemA(HZIP hz, int index, ZIPENTRY *ze);
extern ZRESULT GetZipItemW(HZIP hz, int index, ZIPENTRYW *ze);
extern ZRESULT FindZipItemA(HZIP hz, const TCHAR *name, bool ic, int *index, ZIPENTRY *ze);
extern ZRESULT FindZipItemW(HZIP hz, const TCHAR *name, bool ic, int *index, ZIPENTRYW *ze);
extern ZRESULT UnzipItem(HZIP hz, int index, void *dst, unsigned int len, DWORD flags);
///////////////////////////////////////////////////////////////////////////////////////  

namespace DuiLib
{

	CFlashUI::CFlashUI(void)
	{
		m_pGifImage = NULL;
		m_pPropertyItem = NULL;
		m_frameCount = 0;
		m_framePosition = 0;
		m_isAutoPlay = true;
		m_isAutoSize = false;
		m_isPlaying = false;

	}


	CFlashUI::~CFlashUI(void)
	{
		_clear();
		m_pManager->KillTimer(this, EVENT_TIEM_ID);

	}

	LPCTSTR CFlashUI::GetClass() const
	{
		return _T("FlashUI");
	}

	LPVOID CFlashUI::GetInterface(LPCTSTR pstrName)
	{
		if (_tcscmp(pstrName, DUI_CTR_FLASH) == 0) return static_cast<CFlashUI*>(this);
		return CControlUI::GetInterface(pstrName);
	}

	void CFlashUI::DoInit()
	{
		_initGifImage();
	}

	void CFlashUI::DoPaint(HDC hDC, const RECT& rcPaint)
	{
		if (!::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem)) return;
		if (NULL == m_pGifImage) {
			_initGifImage();
		}

		_drawFrame(hDC);
	}

	void CFlashUI::DoEvent(TEventUI& event)
	{
		if (event.Type == UIEVENT_TIMER)
			_onTimer((UINT_PTR)event.wParam);
	}

	void CFlashUI::SetVisible(bool bVisible /* = true */)
	{
		CControlUI::SetVisible(bVisible);
		if (bVisible)
			PlayGif();
		else
			StopGif();
	}

	void CFlashUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("bkimage")) == 0) SetBkImage(pstrValue);
		else if (_tcscmp(pstrName, _T("autoplay")) == 0) {
			SetAutoPlay(_tcscmp(pstrValue, _T("true")) == 0);
		}
		else if (_tcscmp(pstrName, _T("autosize")) == 0) {
			SetAutoSize(_tcscmp(pstrValue, _T("true")) == 0);
		}
		else
			CControlUI::SetAttribute(pstrName, pstrValue);
	}

	void CFlashUI::SetBkImage(LPCTSTR pStrImage)
	{
		if (m_bkImage == pStrImage || NULL == pStrImage) {
			return;
		}

		m_bkImage = pStrImage;
		StopGif();
		_clear();

		Invalidate();
	}

	LPCTSTR CFlashUI::GetBkImage()
	{
		return m_bkImage.GetData();
	}

	void CFlashUI::SetAutoPlay(bool bIsAuto)
	{
		m_isAutoPlay = bIsAuto;
	}

	bool CFlashUI::IsAutoPlay() const
	{
		return m_isAutoPlay;
	}

	void CFlashUI::SetAutoSize(bool bIsAuto)
	{
		m_isAutoSize = bIsAuto;
	}

	bool CFlashUI::IsAutoSize() const
	{
		return m_isAutoSize;
	}

	void CFlashUI::PlayGif()
	{
		if (m_isPlaying || m_pGifImage == NULL) {
			return;
		}

		long lPause = ((long*)m_pPropertyItem->value)[m_framePosition] * 10;
		if (lPause == 0) lPause = 100;
		m_pManager->SetTimer(this, EVENT_TIEM_ID, lPause);

		m_isPlaying = true;
	}

	void CFlashUI::PauseGif()
	{
		if (!m_isPlaying || m_pGifImage == NULL) {
			return;
		}

		m_pManager->KillTimer(this, EVENT_TIEM_ID);
		this->Invalidate();
		m_isPlaying = false;
	}

	void CFlashUI::StopGif()
	{
		if (!m_isPlaying) {
			return;
		}

		m_pManager->KillTimer(this, EVENT_TIEM_ID);
		m_framePosition = 0;
		this->Invalidate();
		m_isPlaying = false;
	}

	void CFlashUI::_initGifImage()
	{
		m_pGifImage = _LoadGifFromFile(m_bkImage.GetData());
		if (NULL == m_pGifImage) {
			return;
		}

		auto count = m_pGifImage->GetFrameDimensionsCount();
		GUID* pDimensionIDs = new GUID[count];
		m_pGifImage->GetFrameDimensionsList(pDimensionIDs, count);
		m_frameCount = m_pGifImage->GetFrameCount(&pDimensionIDs[0]);

		auto size = m_pGifImage->GetPropertyItemSize(PropertyTagFrameDelay);
		m_pPropertyItem = (Gdiplus::PropertyItem*) malloc(size);
		m_pGifImage->GetPropertyItem(PropertyTagFrameDelay, size, m_pPropertyItem);
		delete  pDimensionIDs;
		pDimensionIDs = NULL;

		if (m_isAutoSize)
		{
			SetFixedWidth(m_pGifImage->GetWidth());
			SetFixedHeight(m_pGifImage->GetHeight());
		}
		if (m_isAutoPlay) {
			PlayGif();
		}
	}

	void CFlashUI::_clear()
	{
		if (m_pGifImage != NULL) {
			delete m_pGifImage;
			m_pGifImage = NULL;
		}

		if (m_pPropertyItem != NULL) {
			free(m_pPropertyItem);
			m_pPropertyItem = NULL;
		}

		m_frameCount = 0;
		m_framePosition = 0;
	}

	void CFlashUI::_onTimer(UINT_PTR idEvent)
	{
		if (idEvent != EVENT_TIEM_ID) {
			return;
		}
			
		m_pManager->KillTimer(this, EVENT_TIEM_ID);
		this->Invalidate();

		m_framePosition = (++m_framePosition) % m_frameCount;

		long lPause = ((long*)m_pPropertyItem->value)[m_framePosition] * 10;
		if (lPause == 0) lPause = 100;
		m_pManager->SetTimer(this, EVENT_TIEM_ID, lPause);
	}

	void CFlashUI::_drawFrame(HDC hDC)
	{
		if (NULL == hDC || NULL == m_pGifImage) {
			return;
		}

		GUID pageGuid = Gdiplus::FrameDimensionTime;
		Gdiplus::Graphics graphics(hDC);
		graphics.DrawImage(m_pGifImage, m_rcItem.left, m_rcItem.top, m_rcItem.right - m_rcItem.left, m_rcItem.bottom - m_rcItem.top);
		m_pGifImage->SelectActiveFrame(&pageGuid, m_framePosition);
	}

	Gdiplus::Image* CFlashUI::_LoadGifFromFile(LPCTSTR pstrGifPath)
	{
		LPBYTE pData = NULL;
		DWORD dwSize = 0;

		do
		{
			CDuiString sFile = CPaintManagerUI::GetResourcePath();
			CDuiString sFolder = m_pManager->GetSkinFolder();
			CDuiString fileName = sFolder + pstrGifPath;
			if (CPaintManagerUI::GetResourceZip().IsEmpty()) {
				sFile += fileName;
				HANDLE hFile = ::CreateFile(sFile.GetData(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				if (hFile == INVALID_HANDLE_VALUE) break;
				dwSize = ::GetFileSize(hFile, NULL);
				if (dwSize == 0) break;

				DWORD dwRead = 0;
				pData = new BYTE[dwSize];
				::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
				::CloseHandle(hFile);

				if (dwRead != dwSize) {
					delete[] pData;
					pData = NULL;
					break;
				}
			}
			else {
				sFile += CPaintManagerUI::GetResourceZip();
				HZIP hz = NULL;
				if (CPaintManagerUI::IsCachedResourceZip()) hz = (HZIP)CPaintManagerUI::GetResourceZipHandle();
				else hz = OpenZip((void*)sFile.GetData(), 0, 2);
				if (hz == NULL) break;
				ZIPENTRY ze;
				int i;
				if (FindZipItem(hz, fileName, true, &i, &ze) != 0) break;
				dwSize = ze.unc_size;
				if (dwSize == 0) break;
				pData = new BYTE[dwSize];
				int res = UnzipItem(hz, i, pData, dwSize, 3);
				if (res != 0x00000000 && res != 0x00000600) {
					delete[] pData;
					pData = NULL;
					if (!CPaintManagerUI::IsCachedResourceZip()) CloseZip(hz);
					break;
				}
				if (!CPaintManagerUI::IsCachedResourceZip()) CloseZip(hz);
			}

		} while (0);

		while (!pData)
		{
			//读不到图片, 则直接去读取bitmap.m_lpstr指向的路径  
			HANDLE hFile = ::CreateFile(pstrGifPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, \
				FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE) break;
			dwSize = ::GetFileSize(hFile, NULL);
			if (dwSize == 0) break;

			DWORD dwRead = 0;
			pData = new BYTE[dwSize];
			::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
			::CloseHandle(hFile);

			if (dwRead != dwSize) {
				delete[] pData;
				pData = NULL;
			}
			break;
		}
		if (!pData)
		{
			return NULL;
		}

		Gdiplus::Image* pImage = _loadGifFromMemory(pData, dwSize);
		delete pData;
		return pImage;
	}

	Gdiplus::Image* CFlashUI::_loadGifFromMemory(LPVOID pBuf, size_t dwSize)
	{
		HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
		BYTE* pMem = (BYTE*)::GlobalLock(hMem);

		memcpy(pMem, pBuf, dwSize);

		IStream* pStm = NULL;
		::CreateStreamOnHGlobal(hMem, TRUE, &pStm);
		Gdiplus::Image *pImg = Gdiplus::Image::FromStream(pStm);
		if (!pImg || pImg->GetLastStatus() != Gdiplus::Ok)
		{
			pStm->Release();
			::GlobalUnlock(hMem);
			return 0;
		}
		return pImg;
	}


}