#ifndef _resizing_dlg_h_
#define _resizing_dlg_h_

#ifdef _AFXDLL

#include "resizablewnd.h"

class CResizingDlg : public CDialog, public IResizableWnd
{
	CRootWndPanel * m_rootPanel;

public:
	CResizingDlg(UINT IDD, CWnd * pParent = NULL);

	inline virtual CRootWndPanel * GetRootPanel() { return m_rootPanel; }

protected:
	virtual void PreSubclassWindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
};

#endif // is def _AFXDLL

#endif