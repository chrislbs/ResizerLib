#include "stdafx.h"
#include "rootwndpanel.h"

namespace df {

CRootWndPanel::CRootWndPanel(HWND hWnd, const SIZE& szMin)
	:CPanel(), m_hwnd(hWnd)
{
	memcpy_s(&m_szMin, sizeof(SIZE), &szMin, sizeof(SIZE));

	RECT cr;
	GetClientRect(hWnd, &cr);
	SetRect(cr);
}

CRootWndPanel::~CRootWndPanel()
{
}

} // end namespace df