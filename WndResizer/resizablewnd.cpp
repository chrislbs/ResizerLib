#include "stdafx.h"
#include "resizablewnd.h"
#include "wndpanel.h"

#include <stack>
#include <queue>
#include <algorithm>

void ResizeWindow(IResizableWnd * rwnd, int rootWidth, int rootHeight)
{
	if(!rwnd)
		return;

	CWndPanel * root = rwnd->GetRootPanel();

	if(!root)
		return;

	RECT& rect = root->GetRect();
	rect.right = rootWidth;
	rect.bottom = rootHeight;

	typedef std::list<CPanel *>::const_iterator iter;

	std::stack<CPanel *> stack;
	stack.push(root);
	std::queue<CPanel *> panels;
	const std::set<CPanel*>& wndPanels = CWndPanel::GetWndPanels();
	std::list<CWndPanel *> rzPanels;
	while(!stack.empty())
	{
		CPanel * panel = stack.top();
		std::set<CPanel*>::const_iterator search = wndPanels.find(panel);
		if(panel != root && search != wndPanels.end())
			rzPanels.push_back(reinterpret_cast<CWndPanel*>((*search)));

		if(panel->GetChildren().size() > 0)
			panels.push(panel);
		stack.pop();

		for(iter it = panel->GetChildren().begin(); it != panel->GetChildren().end(); ++it)
			stack.push((*it));
	}

	while(!panels.empty())
	{
		CPanel * panel = panels.front();
		panels.pop();

		panel->OnResized();
	}
	if(rzPanels.size() > 0)
	{
		HDWP hdwp = ::BeginDeferWindowPos(rzPanels.size());
		std::for_each(rzPanels.begin(), rzPanels.end(), [&](CWndPanel * wp)
		{
			RECT& r = wp->GetRect();
			::DeferWindowPos(hdwp, wp->GetHWND(), NULL, r.left, r.top, 
				GetRectWidth(r), GetRectHeight(r), SWP_NOACTIVATE | SWP_NOZORDER);
		});
		::EndDeferWindowPos(hdwp);

		::InvalidateRect(root->GetHWND(), &root->GetRect(), FALSE);
		std::for_each(rzPanels.begin(), rzPanels.end(), [&](CWndPanel * wp)
		{
			RECT& r = wp->GetRect();
			::MoveWindow(wp->GetHWND(), r.left, r.top, GetRectWidth(r), GetRectHeight(r), TRUE);
		});
	}
}

void DestroyResizeWindow(IResizableWnd * rwnd)
{
	if(rwnd == NULL)
		return;

	CWndPanel * root = rwnd->GetRootPanel();

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