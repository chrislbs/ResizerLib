
// WndResizerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WndResizer.h"
#include "WndResizerDlg.h"
#include "afxdialogex.h"

#include <panelfuncs.h>
#include <rootwndpanel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWndResizerDlg dialog




CWndResizerDlg::CWndResizerDlg(CWnd* pParent /*=NULL*/)
	: CResizingDlg(CWndResizerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWndResizerDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btns[0]);
	DDX_Control(pDX, IDC_BUTTON2, m_btns[1]);
	DDX_Control(pDX, IDC_BUTTON3, m_btns[2]);
	DDX_Control(pDX, IDC_BUTTON4, m_btns[3]);
}

BEGIN_MESSAGE_MAP(CWndResizerDlg, CResizingDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CWndResizerDlg message handlers

BOOL CWndResizerDlg::OnInitDialog()
{
	CResizingDlg::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	std::list<df::CWndPanel *> btnPanels;
	df::CreateWndPanels(m_btns, m_btns + _countof(m_btns), std::back_inserter(btnPanels));
	df::SetPanelsParent(GetRootPanel(), btnPanels.begin(), btnPanels.end());


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWndResizerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CResizingDlg::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWndResizerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

