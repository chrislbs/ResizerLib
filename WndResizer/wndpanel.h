#ifndef _wndpanel_h_
#define _wndpanel_h_

#include "panel.h"

class CWndPanel : public CPanel
{
private:
	HWND m_hWnd;
	
public:
	CWndPanel(HWND hWnd, CPanel * parent = NULL);
	virtual ~CWndPanel();
private:
	CWndPanel();
	CWndPanel(const CWndPanel& rhs);
	CWndPanel& operator=(const CWndPanel& rhs);

public:
	virtual void OnResize(int l_offset, int t_offset, int r_offset, int b_offset);
	virtual void OnMove(int x, int y);
	virtual void OnPaint();

	inline HWND GetHWND() const { return m_hWnd; }
};

#endif