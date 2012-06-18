#ifndef _wndpanel_h_
#define _wndpanel_h_

#include "panel.h"
#include <set>

namespace df {

class CWndPanel : public CPanel
{
	HWND m_hWnd;
	static std::set<CPanel *> m_wndPanels;
	
public:
	CWndPanel(HWND hWnd, UINT anchor = 0);
private:
	CWndPanel();
	CWndPanel(const CWndPanel& rhs);
	CWndPanel& operator=(const CWndPanel& rhs);
protected:
	virtual ~CWndPanel();
public:
	static inline const std::set<CPanel *>& GetWndPanels() { return m_wndPanels; }

	virtual void OnDestroy();

	inline HWND GetHWND() const { return m_hWnd; }
};

} // end namespace df

#endif