#ifndef _resizablewnd_h_
#define _resizablewnd_h_

class CPanel;
class CRootWndPanel;

class IResizableWnd
{
public:
	virtual CRootWndPanel * GetRootPanel() = 0;
};

void ResizePanels(IResizableWnd * rwnd, int rootWidth, int rootHeight);
void ResizeChildPanels(CPanel * parent, bool resizeVert, bool resizeHorz);
void ResizeWndPanels(IResizableWnd * rwnd);

void ResizeWindow(IResizableWnd * rwnd, int rootWidth, int rootHeight);
void DestroyResizeWindow(IResizableWnd * rwnd);

#endif