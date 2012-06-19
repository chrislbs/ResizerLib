#ifndef _resizing_wnd_h_
#define _resizing_wnd_h_

#ifdef _AFXDLL

#include "resizablewnd.h"

namespace df {

class CResizingWnd : public CWnd, public IResizableWnd
{
	DECLARE_DYNAMIC(CResizingWnd)

	CRootWndPanel * m_rootPanel;

public:
	static const TCHAR CLASS_NAME[];
	static BOOL RegisterWindowClass();

	CResizingWnd();
	virtual ~CResizingWnd();

	inline virtual CRootWndPanel * GetRootPanel() { return m_rootPanel; }

	// CWnd Overrides
	virtual void PreSubclassWindow();

	// MFC Messages
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);

private:

protected:
	DECLARE_MESSAGE_MAP()
};

} // end namespace df

#endif // is def _AFXDLL

#endif