#include "stdafx.h"
#include "ResizingWnd.h"
#include "rootwndpanel.h"

#ifdef _AFXDLL

namespace df {

IMPLEMENT_DYNAMIC(CResizingWnd, CWnd)

const TCHAR CResizingWnd::CLASS_NAME[] = "RESIZING_WINDOW_CLASS";

CResizingWnd::CResizingWnd()
:m_rootPanel(NULL)
{
}

CResizingWnd::~CResizingWnd()
{
	DestroyResizeWindow(this);
}

BOOL CResizingWnd::RegisterWindowClass()
{
	WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, CLASS_NAME, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = CLASS_NAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}

void CResizingWnd::PreSubclassWindow()
{
	CWnd::PreSubclassWindow();
	
	m_rootPanel = new CRootWndPanel(GetSafeHwnd());
}

BEGIN_MESSAGE_MAP(CResizingWnd, CWnd)
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

void CResizingWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	ResizePanels(this, cx, cy);
	ResizeWndPanels(this);
}

void CResizingWnd::OnSizing(UINT fwSide, LPRECT pRect)
{
	CWnd::OnSizing(fwSide, pRect);
	ValidateWindowSizing(this, fwSide, pRect);
}

} // end namespace df

#endif // is def _AFXDLL