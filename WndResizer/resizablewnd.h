#ifndef _resizablewnd_h_
#define _resizablewnd_h_

class CWndPanel;

class IResizableWnd
{
public:
	virtual CWndPanel * GetRootPanel() = 0;
};

void ResizeWindow(IResizableWnd * rwnd, int rootWidth, int rootHeight);
void DestroyResizeWindow(IResizableWnd * rwnd);

#endif