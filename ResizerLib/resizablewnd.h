#ifndef _resizablewnd_h_
#define _resizablewnd_h_

namespace df {

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

void ValidateWindowSizing(IResizableWnd * rwnd, UINT fwSide, LPRECT pRect);

void DestroyResizeWindow(IResizableWnd * rwnd);

} // end namespace df

#endif