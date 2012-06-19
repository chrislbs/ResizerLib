#ifndef _resizing_dlg_h_
#define _resizing_dlg_h_

#ifdef _AFXDLL

#include "resizablewnd.h"

namespace df {

class CResizingDlg : public CDialog, public IResizableWnd
{
	CRootWndPanel * m_rootPanel;

public:
	CResizingDlg(UINT IDD, CWnd * pParent = NULL);

	inline virtual CRootWndPanel * GetRootPanel() { return m_rootPanel; }

public:
	virtual void PreSubclassWindow();
	virtual BOOL DestroyWindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);

	DECLARE_MESSAGE_MAP()
};

} // end namespace df

#endif // is def _AFXDLL

#endif