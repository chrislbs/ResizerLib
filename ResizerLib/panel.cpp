#include "stdafx.h"
#include "panel.h"

CPanel::CPanel(const RECT& rect, UINT anchor)
	:m_anchor(anchor)
{
	memcpy_s(&m_rect, sizeof(RECT), &rect, sizeof(RECT));
	memset(&m_offset, 0, sizeof(OFFSET));
}

CPanel::~CPanel()
{
}

void CPanel::AddChild(CPanel * panel)
{
	const RECT& crect = panel->GetRect();
	OFFSET off = 
	{
		crect.left - m_rect.left,
		crect.top - m_rect.top,
		m_rect.right - crect.right,
		m_rect.bottom - crect.bottom
	};
	panel->SetOffset(off);

	m_children.push_back(panel);
}