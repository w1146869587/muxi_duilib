#pragma once

class CAppWnd : public WindowImplBase {
public:
	CAppWnd(void);
	~CAppWnd(void);

public:
	void OnUIInitEnd();

private:
	virtual CDuiString GetSkinFolder();
 	virtual CDuiString GetSkinFile();
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual LPCTSTR GetResourceID() const;
	virtual LPCTSTR GetWindowClassName(void) const;	
	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

private:

};