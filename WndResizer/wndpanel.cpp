#include "stdafx.h"
#include "wndpanel.h"

std::set<CPanel *> CWndPanel::m_wndPanels;

CWndPanel::CWndPanel(HWND hWnd, UINT anchor)
	: CPanel(EMPTY_RECT, anchor), m_hWnd(hWnd)
{
	ASSERT(IsWindow(m_hWnd));

	RECT& rect = GetRect();
	GetWindowRect(m_hWnd, &rect);
	
	HWND hWndParent = ::GetParent(m_hWnd);
	if(hWndParent != NULL)
	{
		POINT tl = { rect.left, rect.top };
		POINT br = { rect.right, rect.bottom };
		ScreenToClient(hWndParent, &tl);
		ScreenToClient(hWndParent, &br);
		SetRect(&rect, tl.x, tl.y, br.x, br.y);
	}
	m_wndPanels.insert(this);
}

CWndPanel::~CWndPanel()
{
}

void CWndPanel::OnDestroy()
{
	m_wndPanels.erase(this);
	delete this;
}