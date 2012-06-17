#include "stdafx.h"
#include "rootwndpanel.h"

CRootWndPanel::CRootWndPanel(HWND hWnd, SIZE szMin)
	:CWndPanel(hWnd)
{
	memcpy_s(&m_szMin, sizeof(SIZE), &szMin, sizeof(SIZE));
}

CRootWndPanel::~CRootWndPanel()
{
}