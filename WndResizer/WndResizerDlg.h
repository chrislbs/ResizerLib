
// WndResizerDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include <ResizingDlg.h>


// CWndResizerDlg dialog
class CWndResizerDlg : public df::CResizingDlg
{
// Construction
public:
	CWndResizerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WNDRESIZER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CButton m_btns[4];
};
