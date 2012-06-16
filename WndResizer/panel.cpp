#include "stdafx.h"
#include "panel.h"

#include <queue>

CPanel::CPanel(const RECT& rect, UINT anchor, const SIZE& szMin, const SIZE& szMax)
	:m_anchor(anchor)
{
	memcpy_s(&m_rect, sizeof(RECT), &rect, sizeof(RECT));
	memcpy_s(&m_szMin, sizeof(SIZE), &szMin, sizeof(SIZE));
	memcpy_s(&m_szMax, sizeof(SIZE), &szMax, sizeof(SIZE));
	memset(&m_offset, 0, sizeof(OFFSET));
}

CPanel::~CPanel()
{
}

void CPanel::AddChild(CPanel * panel)
{
	OFFSET& off = panel->GetOffset();
	RECT& crect = panel->GetRect();

	off.bottom = m_rect.bottom - crect.bottom;
	off.right = m_rect.right - crect.right;
	off.left = crect.left - m_rect.left;
	off.top = crect.top - m_rect.top;

	m_children.push_back(panel);
}