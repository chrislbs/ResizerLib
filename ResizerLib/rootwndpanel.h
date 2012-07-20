#ifndef _rootwndpanel_h_
#define _rootwndpanel_h_

#include "wndpanel.h"

namespace df {

const SIZE EMPTY_SIZE = {0};

class CRootWndPanel : public CPanel
{
	SIZE m_szMin;
	HWND m_hwnd;

public:
	CRootWndPanel(HWND hWnd, SIZE szMin = EMPTY_SIZE);
private:
	CRootWndPanel();
	CRootWndPanel(const CRootWndPanel& rhs);
	CRootWndPanel& operator=(const CRootWndPanel& rhs);
	~CRootWndPanel();

public:
	inline const SIZE& GetMinSize() const { return m_szMin; }
	// consider an assert or exception if the new minimum size is greater than current window size
	inline void SetMinSize(const SIZE& szMin) { memcpy_s(&m_szMin, sizeof(SIZE), &szMin, sizeof(SIZE)); }

	inline HWND GetHWND() const { return m_hwnd; }
};

} // end namespace df
#endif