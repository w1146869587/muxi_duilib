#ifndef __UIRICHEDIT_H__
#define __UIRICHEDIT_H__
#pragma warning(disable : 4251)

#pragma once
#include <textserv.h>
#include "Richedit.h"

namespace DuiLib {

class CRichEditUI;

class UILIB_API CTxtWinHost : public ITextHost
{
public:
	CTxtWinHost();
	BOOL Init(CRichEditUI *re, const CREATESTRUCT *pcs);
	virtual ~CTxtWinHost();

	ITextServices* GetTextServices(void) { return pserv; }
	void SetClientRect(RECT *prc);
	RECT* GetClientRect() { return &rcClient; }
	BOOL GetWordWrap(void) { return fWordWrap; }
	void SetWordWrap(BOOL fWordWrap);
	BOOL GetReadOnly();
	void SetReadOnly(BOOL fReadOnly);
	void SetFont(HFONT hFont);
	void SetColor(DWORD dwColor);
	SIZEL* GetExtent();
	void SetExtent(SIZEL *psizelExtent);
	void LimitText(LONG nChars);
	BOOL IsCaptured();

	BOOL GetAllowBeep();
	void SetAllowBeep(BOOL fAllowBeep);
	WORD GetDefaultAlign();
	void SetDefaultAlign(WORD wNewAlign);
	BOOL GetRichTextFlag();
	void SetRichTextFlag(BOOL fNew);
	LONG GetDefaultLeftIndent();
	void SetDefaultLeftIndent(LONG lNewIndent);
	BOOL SetSaveSelection(BOOL fSaveSelection);
	HRESULT OnTxInPlaceDeactivate();
	HRESULT OnTxInPlaceActivate(LPCRECT prcClient);
	BOOL GetActiveState(void) { return fInplaceActive; }
	BOOL DoSetCursor(RECT *prc, POINT *pt);
	void SetTransparent(BOOL fTransparent);
	void GetControlRect(LPRECT prc);
	LONG SetAccelPos(LONG laccelpos);
	WCHAR SetPasswordChar(WCHAR chPasswordChar);
	void SetDisabled(BOOL fOn);
	LONG SetSelBarWidth(LONG lSelBarWidth);
	BOOL GetTimerState();

	void SetCharFormat(CHARFORMAT2W &c);
	void SetParaFormat(PARAFORMAT2 &p);

	// -----------------------------
	//	IUnknown interface
	// -----------------------------
	virtual HRESULT _stdcall QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG _stdcall AddRef(void);
	virtual ULONG _stdcall Release(void);

	// -----------------------------
	//	ITextHost interface
	// -----------------------------
	virtual HDC TxGetDC();
	virtual INT TxReleaseDC(HDC hdc);
	virtual BOOL TxShowScrollBar(INT fnBar, BOOL fShow);
	virtual BOOL TxEnableScrollBar(INT fuSBFlags, INT fuArrowflags);
	virtual BOOL TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw);
	virtual BOOL TxSetScrollPos(INT fnBar, INT nPos, BOOL fRedraw);
	virtual void TxInvalidateRect(LPCRECT prc, BOOL fMode);
	virtual void TxViewChange(BOOL fUpdate);
	virtual BOOL TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight);
	virtual BOOL TxShowCaret(BOOL fShow);
	virtual BOOL TxSetCaretPos(INT x, INT y);
	virtual BOOL TxSetTimer(UINT idTimer, UINT uTimeout);
	virtual void TxKillTimer(UINT idTimer);
	virtual void TxScrollWindowEx(INT dx, INT dy, LPCRECT lprcScroll, LPCRECT lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate, UINT fuScroll);
	virtual void TxSetCapture(BOOL fCapture);
	virtual void TxSetFocus();
	virtual void TxSetCursor(HCURSOR hcur, BOOL fText);
	virtual BOOL TxScreenToClient(LPPOINT lppt);
	virtual BOOL TxClientToScreen(LPPOINT lppt);
	virtual HRESULT TxActivate(LONG * plOldState);
	virtual HRESULT TxDeactivate(LONG lNewState);
	virtual HRESULT TxGetClientRect(LPRECT prc);
	virtual HRESULT TxGetViewInset(LPRECT prc);
	virtual HRESULT TxGetCharFormat(const CHARFORMATW **ppCF);
	virtual HRESULT TxGetParaFormat(const PARAFORMAT **ppPF);
	virtual COLORREF TxGetSysColor(int nIndex);
	virtual HRESULT TxGetBackStyle(TXTBACKSTYLE *pstyle);
	virtual HRESULT TxGetMaxLength(DWORD *plength);
	virtual HRESULT TxGetScrollBars(DWORD *pdwScrollBar);
	virtual HRESULT TxGetPasswordChar(TCHAR *pch);
	virtual HRESULT TxGetAcceleratorPos(LONG *pcp);
	virtual HRESULT TxGetExtent(LPSIZEL lpExtent);
	virtual HRESULT OnTxCharFormatChange(const CHARFORMATW * pcf);
	virtual HRESULT OnTxParaFormatChange(const PARAFORMAT * ppf);
	virtual HRESULT TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits);
	virtual HRESULT TxNotify(DWORD iNotify, void *pv);
	virtual HIMC TxImmGetContext(void);
	virtual void TxImmReleaseContext(HIMC himc);
	virtual HRESULT TxGetSelectionBarWidth(LONG *lSelBarWidth);

private:
	CRichEditUI *m_re;
	ULONG	cRefs;					// Reference Count
	ITextServices	*pserv;		    // pointer to Text Services object
	// Properties

	DWORD		dwStyle;				// style bits

	unsigned	fEnableAutoWordSel : 1;	// enable Word style auto word selection?
	unsigned	fWordWrap : 1;	// Whether control should word wrap
	unsigned	fAllowBeep : 1;	// Whether beep is allowed
	unsigned	fRich : 1;	// Whether control is rich text
	unsigned	fSaveSelection : 1;	// Whether to save the selection when inactive
	unsigned	fInplaceActive : 1; // Whether control is inplace active
	unsigned	fTransparent : 1; // Whether control is transparent
	unsigned	fTimer : 1;	// A timer is set
	unsigned    fCaptured : 1;

	LONG		lSelBarWidth;			// Width of the selection bar
	LONG  		cchTextMost;			// maximum text size
	DWORD		dwEventMask;			// DoEvent mask to pass on to parent window
	LONG		icf;
	LONG		ipf;
	RECT		rcClient;				// Client Rect for this control
	SIZEL		sizelExtent;			// Extent array
	CHARFORMAT2W cf;					// Default character format
	PARAFORMAT2	pf;					    // Default paragraph format
	LONG		laccelpos;				// Accelerator position
	WCHAR		chPasswordChar;		    // Password character
};


class UILIB_API CRichEditUI : public CContainerUI, public IMessageFilterUI
{
public:
    CRichEditUI();
    ~CRichEditUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;

    bool IsWantTab();
    void SetWantTab(bool bWantTab = true);
    bool IsWantReturn();
    void SetWantReturn(bool bWantReturn = true);
    bool IsWantCtrlReturn();
    void SetWantCtrlReturn(bool bWantCtrlReturn = true);
    bool IsRich();
    void SetRich(bool bRich = true);
    bool IsReadOnly();
    void SetReadOnly(bool bReadOnly = true);
    bool GetWordWrap();
    void SetWordWrap(bool bWordWrap = true);
    int GetFont();
    void SetFont(int index);
    void SetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
    LONG GetWinStyle();
    void SetWinStyle(LONG lStyle);
    DWORD GetTextColor();
    void SetTextColor(DWORD dwTextColor);
    int GetLimitText();
    void SetLimitText(int iChars);
    long GetTextLength(DWORD dwFlags = GTL_DEFAULT) const;
    CDuiString GetText() const;
    void SetText(LPCTSTR pstrText);
    bool GetModify() const;
    void SetModify(bool bModified = true) const;
    void GetSel(CHARRANGE &cr) const;
    void GetSel(long& nStartChar, long& nEndChar) const;
    int SetSel(CHARRANGE &cr);
    int SetSel(long nStartChar, long nEndChar);
    void ReplaceSel(LPCTSTR lpszNewText, bool bCanUndo);
    void ReplaceSelW(LPCWSTR lpszNewText, bool bCanUndo = false);
    CDuiString GetSelText() const;
    int SetSelAll();
    int SetSelNone();
    WORD GetSelectionType() const;
    bool GetZoom(int& nNum, int& nDen) const;
    bool SetZoom(int nNum, int nDen);
    bool SetZoomOff();
    bool GetAutoURLDetect() const;
    bool SetAutoURLDetect(bool bAutoDetect = true);
    DWORD GetEventMask() const;
    DWORD SetEventMask(DWORD dwEventMask);
    CDuiString GetTextRange(long nStartChar, long nEndChar) const;
    void HideSelection(bool bHide = true, bool bChangeStyle = false);
    void ScrollCaret();
    int InsertText(long nInsertAfterChar, LPCTSTR lpstrText, bool bCanUndo = false);
    int AppendText(LPCTSTR lpstrText, bool bCanUndo = false);
	bool AppendText(LPCTSTR lpstrText, CHARFORMAT2& cf, PARAFORMAT2& pf);
    DWORD GetDefaultCharFormat(CHARFORMAT2 &cf) const;
    bool SetDefaultCharFormat(CHARFORMAT2 &cf);
    DWORD GetSelectionCharFormat(CHARFORMAT2 &cf) const;
    bool SetSelectionCharFormat(CHARFORMAT2 &cf);
    bool SetWordCharFormat(CHARFORMAT2 &cf);
    DWORD GetParaFormat(PARAFORMAT2 &pf) const;
    bool SetParaFormat(PARAFORMAT2 &pf);
    bool Redo();
    bool Undo();
    void Clear();
    void Copy();
    void Cut();
    void Paste();
    int GetLineCount() const;
    CDuiString GetLine(int nIndex, int nMaxLength) const;
	int GetFirstVisibleLine() const;
    int LineIndex(int nLine = -1) const;
    int LineLength(int nLine = -1) const;
    bool LineScroll(int nLines, int nChars = 0);
	CDuiPoint GetCharPos(long lChar) const;
    long LineFromChar(long nIndex) const;
    CDuiPoint PosFromChar(UINT nChar) const;
    int CharFromPos(CDuiPoint pt) const;
    void EmptyUndoBuffer();
    UINT SetUndoLimit(UINT nLimit);
    long StreamIn(int nFormat, EDITSTREAM &es);
    long StreamOut(int nFormat, EDITSTREAM &es);

    void DoInit();

	void UpdateView(); //ʹrichedit�ڲ�ˢ�£����¼��������λ�ã������Զ���������һ�ɼ��С������������һ�ɼ���ΪͼƬ�������ˢ����hunter
	bool GetVScroll(LONG& min, LONG& max, LONG& pos, LONG& page, BOOL& enabled);
	int  GetVScrollThumbPos();
	void SetVScrollThumbPos(int pos); //pos��λΪ���أ���ʾtop(y��)

    // ע�⣺TxSendMessage��SendMessage��������ģ�TxSendMessageû��multibyte��unicode�Զ�ת���Ĺ��ܣ�
    // ��richedit2.0�ڲ�����unicodeʵ�ֵģ���multibyte�����У������Լ�����unicode��multibyte��ת��
	bool SetDropAcceptFile(bool bAccept);
    virtual HRESULT TxSendMessage(UINT msg, WPARAM wparam, LPARAM lparam, LRESULT *plresult) const; 
    IDropTarget* GetTxDropTarget();
    virtual bool OnTxViewChanged();
    virtual void OnTxNotify(DWORD iNotify, void *pv);

    void SetScrollPos(SIZE szPos);
    void LineUp();
    void LineDown();
    void PageUp();
    void PageDown();
    void HomeUp();
    void EndDown();
    void LineLeft();
    void LineRight();
    void PageLeft();
    void PageRight();
    void HomeLeft();
    void EndRight();

    SIZE EstimateSize(SIZE szAvailable);
	void SetPos(RECT rc, bool bNeedInvalidate = true);
	void Move(SIZE szOffset, bool bNeedInvalidate = true);
    void DoEvent(TEventUI& event);
    void DoPaint(HDC hDC, const RECT& rcPaint);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	virtual void OnPosChangeBegin();
	virtual void OnPosChangeEnd();

protected:
    CTxtWinHost* m_pTwh;
    bool m_bVScrollBarFixing;
    bool m_bWantTab;
    bool m_bWantReturn;
    bool m_bWantCtrlReturn;
    bool m_bRich;
    bool m_bReadOnly;
    bool m_bWordWrap;
    DWORD m_dwTextColor;
    int m_iFont;
    int m_iLimitText;
    LONG m_lTwhStyle;
	bool m_bInited;
};

} // namespace DuiLib

#endif // __UIRICHEDIT_H__