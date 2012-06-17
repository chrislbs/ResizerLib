#include "stdafx.h"
#include "resizablewnd.h"
#include "rootwndpanel.h"

#include <stack>
#include <queue>
#include <algorithm>

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
				double ratio = (double)off.left / origWidth;
				r.left = static_cast<int>(pr.left + (ratio * GetRectWidth(pr)));
				r.right = r.left + GetRectWidth(cr);
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
				double ratio = (double)off.top / origHeight;
				r.top = static_cast<int>(pr.top + (ratio * GetRectHeight(pr)));
				r.bottom = r.top + GetRectHeight(cr);
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