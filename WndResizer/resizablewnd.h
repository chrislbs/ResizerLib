#ifndef _resizablewnd_h_
#define _resizablewnd_h_

class CRootWndPanel;

class IResizableWnd
{
public:
	virtual CRootWndPanel * GetRootPanel() = 0;
};

void ResizeWindow(IResizableWnd * rwnd, int rootWidth, int rootHeight);
void DestroyResizeWindow(IResizableWnd * rwnd);

#endif