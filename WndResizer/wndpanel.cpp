#include "stdafx.h"
#include "wndpanel.h"

CWndPanel::CWndPanel(HWND hWnd, CPanel * parent)
	: CPanel(parent), m_hWnd(hWnd)
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
		SetRect(tl.x, tl.y, br.x, br.y);
	}
}

CWndPanel::~CWndPanel()
{
}

void CWndPanel::OnResize(int l_offset, int t_offset, int r_offset, int b_offset)
{
	CPanel::OnResize(l_offset, t_offset, r_offset, b_offset);

	//RECT& r = GetRect();

	//DWORD style = GetWindowLong(m_hWnd, GWL_STYLE);
	//DWORD style_ex = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	//
	//AdjustWindowRectEx(&r, style, FALSE, style_ex);
}

void CWndPanel::OnMove(int x, int y)
{
	CPanel::OnMove(x, y);
}

void CWndPanel::OnPaint()
{
	//PAINTSTRUCT ps;
	//HDC hdc = BeginPaint(m_hWnd, &ps);
}