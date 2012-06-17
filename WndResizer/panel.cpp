#include "stdafx.h"
#include "panel.h"

#include <queue>

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

void CPanel::OnResized()
{
	typedef std::list<CPanel *>::const_iterator iter;
	const RECT& pr = GetRect();
	for(iter it = GetChildren().begin(); it != GetChildren().end(); ++it)
	{
		CPanel * p = (*it);
		const OFFSET& off = p->GetOffset();
		UINT anchor = p->GetAnchor();
		const RECT& cr = p->GetRect();

		RECT r = { 0 };
		if(anchor & ANCHOR_HORZ_CENTERED)
		{
			r.left = pr.left + (static_cast<int>( (GetRectWidth(pr) - GetRectWidth(cr)) / 2));
			r.right = r.left + GetRectWidth(cr);
		}
		else if((anchor & ANCHOR_HORZ) == ANCHOR_HORZ)
		{
			r.left = pr.left + off.left;
			r.right = pr.right - off.right;
		}
		else if(anchor & ANCHOR_RIGHT)
		{
			r.right = pr.right - off.right;
			r.left = r.right - GetRectWidth(cr);
		}
		else if(anchor & ANCHOR_LEFT)
		{
			r.left = pr.left + off.left;
			r.right = r.left + GetRectWidth(cr);
		}
		else
		{
			int origWidth = off.left + off.right + GetRectWidth(cr);
			double ratio = (double)off.left / origWidth;
			r.left = static_cast<int>(pr.left + (ratio * GetRectWidth(pr)));
			r.right = r.left + GetRectWidth(cr);
		}

		if(anchor & ANCHOR_VERT_CENTERED)
		{
			r.top = pr.top + (static_cast<int>( (GetRectWidth(pr) - GetRectWidth(cr)) / 2));
			r.bottom = r.top + GetRectHeight(cr);
		}
		else if((anchor & ANCHOR_VERT) == ANCHOR_VERT)
		{
			r.top = pr.top + off.top;
			r.bottom = pr.bottom - off.bottom;
		}
		else if(anchor & ANCHOR_TOP)
		{
			r.top = pr.top + off.top;
			r.bottom = r.top + GetRectHeight(cr);
		}
		else if(anchor & ANCHOR_BOTTOM)
		{
			r.bottom = pr.bottom - off.bottom;
			r.top = r.bottom - GetRectHeight(cr);
		}
		else
		{
			int origHeight = off.top + off.bottom + GetRectHeight(cr);
			double ratio = (double)off.top / origHeight;
			r.top = static_cast<int>(pr.top + (ratio * GetRectHeight(pr)));
			r.bottom = r.top + GetRectHeight(cr);
		}
		p->SetRect(r);
	}
}