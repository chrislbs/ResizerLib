#include "stdafx.h"
#include "ResizingDlg.h"
#include "rootwndpanel.h"

#ifdef _AFXDLL

namespace df {

CResizingDlg::CResizingDlg(UINT IDD, CWnd * pParent)
	:CDialog(IDD, pParent), m_rootPanel(NULL)
{
}

void CResizingDlg::PreSubclassWindow()
{
	CDialog::PreSubclassWindow();	

	m_rootPanel = new CRootWndPanel(GetSafeHwnd());
}

BEGIN_MESSAGE_MAP(CResizingDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

void CResizingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	ResizePanels(this, cx, cy);
	ResizeWndPanels(this);
}

void CResizingDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);
	ValidateWindowSizing(this, fwSide, pRect);
}

BOOL CResizingDlg::DestroyWindow()
{
	DestroyResizeWindow(this);

	BOOL ret = CDialog::DestroyWindow();
	return ret;
}

} // end namespace df

#endif