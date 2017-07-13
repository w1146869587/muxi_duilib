#ifndef GifAnimUI_h__  
#define GifAnimUI_h__  

#pragma once  

namespace DuiLib
{
	class CControl;

#define EVENT_TIEM_ID   100  

	class UILIB_API CFlashUI : public CControlUI
	{
	public:
		CFlashUI(void);
		~CFlashUI(void);
		void    SetBkImage(LPCTSTR pStrImage);
		LPCTSTR GetBkImage();
		void    SetAutoPlay(bool bIsAuto = true);
		bool    IsAutoPlay() const;
		void    SetAutoSize(bool bIsAuto = true);
		bool    IsAutoSize() const;
		void    PlayGif();
		void    PauseGif();
		void    StopGif();
		void    SetVisible(bool bVisible = true) override;
	protected:
		LPCTSTR GetClass() const;
		LPVOID  GetInterface(LPCTSTR pstrName);
		void    DoInit() override;
		void    DoPaint(HDC hDC, const RECT& rcPaint) override;
		void    DoEvent(TEventUI& event) override;
		void    SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;

	private:
		void    _initGifImage();
		void    _clear();
		void    _onTimer(UINT_PTR idEvent);
		void    _drawFrame(HDC hDC);       // ����GIFÿ֡  
		Gdiplus::Image* _LoadGifFromFile(LPCTSTR pstrGifPath);
		Gdiplus::Image* _loadGifFromMemory(LPVOID pBuf, size_t dwSize);

	private:
		bool            m_isAutoPlay;              // �Ƿ��Զ�����gif  
		bool            m_isAutoSize;              // �Ƿ��Զ�����ͼƬ���ô�С  
		bool            m_isPlaying;
		UINT            m_frameCount;              // gifͼƬ��֡��  
		UINT            m_framePosition;           // ��ǰ�ŵ��ڼ�֡ 
		CDuiString      m_bkImage;
		Gdiplus::Image  *m_pGifImage;
		Gdiplus::PropertyItem*  m_pPropertyItem;    // ֡��֮֡����ʱ��  
	};
}

#endif // GifAnimUI_h__ 