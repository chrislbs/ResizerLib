#include "stdafx.h"
#include "wndpanel.h"

CWndPanel::CWndPanel(HWND hWnd, UINT anchor, const SIZE& szMin, const SIZE& szMax)
	: CPanel(EMPTY_RECT, anchor, szMin, szMax)
{
	ASSERT(IsWindow(m_hWnd));

	RECT& rect = GetRect();
	GetWindowRect(m_hWnd, &rect);

	//DWORD style = GetWindowLong(m_hWnd, GWL_STYLE);
	//DWORD style_ex = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	//
	//AdjustWindowRectEx(&r, style, FALSE, style_ex);
	
	HWND hWndParent = ::GetParent(m_hWnd);
	if(hWndParent != NULL)
	{
		POINT tl = { rect.left, rect.top };
		POINT br = { rect.right, rect.bottom };
		ScreenToClient(hWndParent, &tl);
		ScreenToClient(hWndParent, &br);
		SetRect(&rect, tl.x, tl.y, br.x, br.y);
	}
}

CWndPanel::~CWndPanel()
{
}

void CWndPanel::OnResized()
{
}

void CWndPanel::OnMove(int x, int y)
{
}