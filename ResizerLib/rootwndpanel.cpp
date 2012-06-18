#include "stdafx.h"
#include "rootwndpanel.h"

namespace df {

CRootWndPanel::CRootWndPanel(HWND hWnd, SIZE szMin)
	:CWndPanel(hWnd)
{
	memcpy_s(&m_szMin, sizeof(SIZE), &szMin, sizeof(SIZE));
}

CRootWndPanel::~CRootWndPanel()
{
}

} // end namespace df