#include "stdafx.h"
#include "wndpanel.h"

std::set<CPanel *> CWndPanel::m_wndPanels;

CWndPanel::CWndPanel(HWND hWnd, UINT anchor, const SIZE& szMin, const SIZE& szMax)
	: CPanel(EMPTY_RECT, anchor, szMin, szMax), m_hWnd(hWnd)
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
		SetRect(&rect, tl.x, tl.y, br.x, br.y);
	}
	m_wndPanels.insert(this);
}

CWndPanel::~CWndPanel()
{
}

void CWndPanel::OnResized()
{
	typedef std::list<CPanel *>::const_iterator iter;
	RECT& pr = GetRect();
	for(iter it = GetChildren().begin(); it != GetChildren().end(); ++it)
	{
		CPanel * p = (*it);
		OFFSET& off = p->GetOffset();
		UINT anchor = p->GetAnchor();

		RECT r = { 0 };
		if(anchor & ANCHOR_HORZ_CENTERED)
		{
			r.left = pr.left + (static_cast<int>( (GetRectWidth(pr) - GetRectWidth(p->GetRect())) / 2));
			r.right = r.left + GetRectWidth(p->GetRect());
		}
		else if((anchor & ANCHOR_HORZ) == ANCHOR_HORZ)
		{
			r.left = pr.left + off.left;
			r.right = pr.right - off.right;
		}
		else if(anchor & ANCHOR_RIGHT)
		{
			r.right = pr.right - off.right;
			r.left = r.right - GetRectWidth(p->GetRect());
		}
		else if(anchor & ANCHOR_LEFT)
		{
			r.left = pr.left + off.left;
			r.right = r.left + GetRectWidth(p->GetRect());
		}

		if(anchor & ANCHOR_VERT_CENTERED)
		{
			r.top = pr.top + (static_cast<int>( (GetRectWidth(pr) - GetRectWidth(p->GetRect())) / 2));
			r.bottom = r.top + GetRectHeight(p->GetRect());
		}
		else if((anchor & ANCHOR_VERT) == ANCHOR_VERT)
		{
			r.top = pr.top + off.top;
			r.bottom = pr.bottom - off.bottom;
		}
		else if(anchor & ANCHOR_TOP)
		{
			r.top = pr.top + off.top;
			r.bottom = r.top + GetRectHeight(p->GetRect());
		}
		else if(anchor & ANCHOR_BOTTOM)
		{
			r.bottom = pr.bottom - off.bottom;
			r.top = r.bottom - GetRectHeight(p->GetRect());
		}
		memcpy_s(&p->GetRect(), sizeof(RECT), &r, sizeof(RECT));
	}
}

void CWndPanel::OnDestroy()
{
	m_wndPanels.erase(this);
	delete this;
}