#include "stdafx.h"
#include "wndpanel.h"

std::set<CPanel *> CWndPanel::m_wndPanels;

CWndPanel::CWndPanel(HWND hWnd, UINT anchor)
	: CPanel(EMPTY_RECT, anchor), m_hWnd(hWnd)
{
	ASSERT(IsWindow(m_hWnd));

	RECT rect = { 0 };
	GetWindowRect(m_hWnd, &rect);
	SetRect(rect);
	
	HWND hWndParent = ::GetParent(m_hWnd);
	if(hWndParent != NULL)
	{
		POINT tl = { rect.left, rect.top };
		POINT br = { rect.right, rect.bottom };
		ScreenToClient(hWndParent, &tl);
		ScreenToClient(hWndParent, &br);

		RECT r = { tl.x, tl.y, br.x, br.y };
		SetRect(r);
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