#ifndef _wndpanel_h_
#define _wndpanel_h_

#include "panel.h"
#include <set>

class CWndPanel : public CPanel
{
	HWND m_hWnd;
	
public:
	CWndPanel(
		HWND hWnd, 
		UINT anchor = ANCHOR_TOP | ANCHOR_LEFT, 
		const SIZE& szMin = EMPTY_SIZE,
		const SIZE& szMax = EMPTY_SIZE);
private:
	CWndPanel();
	CWndPanel(const CWndPanel& rhs);
	CWndPanel& operator=(const CWndPanel& rhs);
	virtual ~CWndPanel();

	static std::set<CPanel *> m_wndPanels;
public:
	static inline const std::set<CPanel *>& GetWndPanels() { return m_wndPanels; }

	virtual void OnDestroy();

	inline HWND GetHWND() const { return m_hWnd; }
};

#endif