#include "stdafx.h"
#include "panel.h"

#include <queue>

CPanel::CPanel(CPanel * parent)
	:m_pParent(parent)
{
	m_rect.bottom = m_rect.left = m_rect.right = m_rect.top = 0;
}

CPanel::CPanel(const RECT& rect, CPanel * parent)
	:m_rect(rect), m_pParent(parent)
{
}

CPanel::~CPanel()
{
	typedef std::list<CPanel *>::const_iterator piter;

	for(piter it = GetChildren().begin(); it != GetChildren().end(); ++it)
		delete (*it);
}

void CPanel::SetRect(const RECT& rect)
{
	m_rect.left = rect.left;
	m_rect.top = rect.top;
	m_rect.right = rect.right;
	m_rect.bottom = rect.bottom;
}

void CPanel::SetRect(int l, int t, int r, int b)
{
	m_rect.left = l;
	m_rect.top = t;
	m_rect.right = r;
	m_rect.bottom = b;
}

void CPanel::OnResize(int l_offset, int t_offset, int r_offset, int b_offset)
{
	RECT& prect = GetParent()->GetRect();
	SetRect(prect.left + l_offset, prect.top + t_offset, prect.right - r_offset, prect.bottom - b_offset);
}

void CPanel::OnMove(int x, int y)
{
	RECT& r = GetRect();
	SetRect(x, y, x + GetRectWidth(r), y + GetRectHeight(r));
}

void CPanel::OnPaint()
{
}