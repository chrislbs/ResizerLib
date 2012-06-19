#include "stdafx.h"
#include "resizablewnd.h"
#include "rootwndpanel.h"

#include <stack>
#include <algorithm>

namespace df {

void ResizePanels(IResizableWnd * rwnd, int rootWidth, int rootHeight)
{
	if(!rwnd)
		return;

	CRootWndPanel * root = rwnd->GetRootPanel();

	if(!root)
		return;

	RECT rect = { 0, 0, rootWidth, rootHeight };

	bool resizeVert = GetRectHeight(rect) > root->GetMinSize().cy;
	bool resizeHorz = GetRectWidth(rect) > root->GetMinSize().cx;

	if(!resizeVert)
		rect.bottom = GetRectHeight(root->GetRect());
	if(!resizeHorz)
		rect.right = GetRectWidth(root->GetRect());

	root->SetRect(rect);

	typedef std::list<CPanel *>::iterator iter;

	std::stack<CPanel *> panels;
	panels.push(root);
	while(!panels.empty())
	{
		CPanel * panel = panels.top();
		ResizeChildPanels(panel, resizeVert, resizeHorz);

		panels.pop();
		for(iter it = panel->GetChildren().begin(); it != panel->GetChildren().end(); ++it)
			panels.push(*it);
	}
}

void ResizeChildPanels(CPanel * parent, bool resizeVert, bool resizeHorz)
{
	if(!parent || !(resizeVert || resizeHorz))
		return;

	typedef std::list<CPanel *>::iterator iter;
	
	const RECT& pr = parent->GetRect();
	for(iter it = parent->GetChildren().begin(); it != parent->GetChildren().end(); ++it)
	{
		CPanel * p = (*it);
		const CPanel::OFFSET& off = p->GetOffset();
		UINT anchor = p->GetAnchor();
		const RECT& cr = p->GetRect();

		RECT r = { 0 };
		if(resizeHorz)
		{
			if((anchor & ANCHOR_HORZ) == ANCHOR_HORZ)
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
				int diff = GetRectWidth(pr) - origWidth;
				CPanel::OFFSET o = off;
				o.left += diff / 2;
				o.right += diff / 2;
				if(diff % 2 == 1)
					o.left += (diff / std::abs(diff)) * 1;

				r.left = pr.left + o.left;
				r.right = r.left + GetRectWidth(cr);
				p->SetOffset(o);
			}
		}
		else
		{
			r.left = cr.left;
			r.right = cr.right;
		}

		if(resizeVert)
		{
			if((anchor & ANCHOR_VERT) == ANCHOR_VERT)
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
				int diff = GetRectHeight(pr) - origHeight;
				CPanel::OFFSET o = off;
				o.top += diff / 2;
				o.bottom += diff / 2;
				if(diff % 2 == 1)
					o.top += (diff / std::abs(diff)) * 1;

				r.top = pr.top + o.top;
				r.bottom = r.top + GetRectHeight(cr);
				p->SetOffset(o);
			}
		}
		else
		{
			r.bottom = cr.bottom;
			r.top = cr.top;
		}
		p->SetRect(r);
	}

}

void ResizeWndPanels(IResizableWnd * rwnd)
{
	if(!rwnd)
		return;

	CRootWndPanel * root = rwnd->GetRootPanel();

	if(!root)
		return;

	const std::set<CPanel*>& wndPanels = CWndPanel::GetWndPanels();

	std::stack<CPanel *> panels;
	panels.push(root);
	std::list<CWndPanel *> rzpanels;
	while(!panels.empty())
	{
		CPanel * panel = panels.top();
		std::set<CPanel *>::const_iterator search = wndPanels.find(panel);
		if(panel != root && search != wndPanels.end())
			rzpanels.push_back(reinterpret_cast<CWndPanel*>(*search));

		panels.pop();

		typedef std::list<CPanel *>::iterator iter;
		for(iter it = panel->GetChildren().begin(); it != panel->GetChildren().end(); ++it)
			panels.push(*it);
	}

	if(rzpanels.size() > 0)
	{
		HDWP hdwp = ::BeginDeferWindowPos(rzpanels.size());
		std::for_each(rzpanels.begin(), rzpanels.end(), [&](CWndPanel * wp)
		{
			const RECT& r = wp->GetRect();
			::DeferWindowPos(hdwp, wp->GetHWND(), NULL, r.left, r.top, 
				GetRectWidth(r), GetRectHeight(r), SWP_NOACTIVATE | SWP_NOZORDER);
		});
		::EndDeferWindowPos(hdwp);

		::InvalidateRect(root->GetHWND(), &root->GetRect(), FALSE);
		std::for_each(rzpanels.begin(), rzpanels.end(), [&](CWndPanel * wp)
		{
			const RECT& r = wp->GetRect();
			::MoveWindow(wp->GetHWND(), r.left, r.top, GetRectWidth(r), GetRectHeight(r), TRUE);
		});
	}
}

#pragma region ValidateWindowSizing Helper Functions
void ValidateLeft(LPRECT pRect, const RECT& rcMin)
{
	int width = GetRectWidth(rcMin);
	if(GetRectWidth(*pRect) < width)
		pRect->left = pRect->right - width;
}

void ValidateRight(LPRECT pRect, const RECT& rcMin)
{
	int width = GetRectWidth(rcMin);
	if(GetRectWidth(*pRect) < width)
		pRect->right = pRect->left + width;
}

void ValidateTop(LPRECT pRect, const RECT& rcMin)
{
	int height = GetRectHeight(rcMin);
	if(GetRectHeight(*pRect) < height)
		pRect->top = pRect->bottom - height;
}

void ValidateBottom(LPRECT pRect, const RECT& rcMin)
{
	int height = GetRectHeight(rcMin);
	if(GetRectHeight(*pRect) < height)
		pRect->bottom = pRect->top + height;
}

#pragma endregion

void ValidateWindowSizing(IResizableWnd * rwnd, UINT fwSide, LPRECT pRect)
{
	if(!rwnd)
		return;

	CRootWndPanel * root = rwnd->GetRootPanel();

	if(!root)
		return;

	RECT rcMin = { 0, 0, root->GetMinSize().cx, root->GetMinSize().cy };

	::AdjustWindowRectEx(
		&rcMin,
		GetWindowLongPtr(root->GetHWND(), GWL_STYLE),
		FALSE, // i don't know where to check for this
		GetWindowLongPtr(root->GetHWND(), GWL_EXSTYLE));

	switch(fwSide)
	{
	case WMSZ_BOTTOM:
		ValidateBottom(pRect, rcMin);
		break;
	case WMSZ_BOTTOMLEFT:
		ValidateBottom(pRect, rcMin);
		ValidateLeft(pRect, rcMin);
		break;
	case WMSZ_BOTTOMRIGHT:
		ValidateBottom(pRect, rcMin);
		ValidateRight(pRect, rcMin);
		break;
	case WMSZ_LEFT:
		ValidateLeft(pRect, rcMin);
		break;
	case WMSZ_RIGHT:
		ValidateRight(pRect, rcMin);
		break;
	case WMSZ_TOP:
		ValidateTop(pRect, rcMin);
		break;
	case WMSZ_TOPLEFT:
		ValidateLeft(pRect, rcMin);
		ValidateTop(pRect, rcMin);
		break;
	case WMSZ_TOPRIGHT:
		ValidateTop(pRect, rcMin);
		ValidateRight(pRect, rcMin);
		break;
	}
}

void DestroyResizeWindow(IResizableWnd * rwnd)
{
	if(rwnd == NULL)
		return;

	CRootWndPanel * root = rwnd->GetRootPanel();

	if(root == NULL)
		return;

	typedef std::list<CPanel *> panel_list;

	std::stack<CPanel*> panels;
	panels.push(root);
	while(!panels.empty())
	{
		CPanel * panel = panels.top();
		panel_list& children = panel->GetChildren();
		if(children.empty())
		{
			panel->OnDestroy();
			panels.pop();
		}
		else
		{
			while(!children.empty())
			{
				panels.push(children.front());
				children.remove(children.front());
			}
		}
	}
}

} // end namespace df