/*****************************************************************************
 *$Workfile: CMessageCentre.cpp $
 *$Revision: 9 $
 *$Modtime: 6/22/00 3:38p $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <afxwin.h>
#include "CMessageCentre.h"			// Class definition
#include "LocalMessageCentre.h"		// Local Engine Message Centre dialogue definition
#include ".\cmessagecentre.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

/////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						==============================
						CMessageCentre::CMessageCentre
//						==============================
(
	LocalMessageCentre*	pDlg,			// Pointer to non-MFC equivalent
	HANDLE				hThread,		// Our parent thread
	bool				bAlwaysOnTop	// Should we always be on top?
)
	: CDialog(CMessageCentre::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMessageCentre)
	//}}AFX_DATA_INIT
	
	m_nHeightDifference = NULL;

	// Remember our non-MFC equivalent
	if(pDlg)
	{
		m_pDlg = pDlg;
	}

	// Remember our parent thread
	if(hThread)
	{
		m_hThread = hThread;
	}

	// Store the AlwaysOnTop value. We need it in OnInitDialog().
	m_bAlwaysOnTop = bAlwaysOnTop;

	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_bmpDialog.LoadBitmap(IDB_MAC_DIALOG_BMP);
}

CMessageCentre::~CMessageCentre()
{

}

//						==============================
void					CMessageCentre::DoDataExchange
//						==============================
(
	CDataExchange*		pDX
)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageCentre)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_BTN_PAUSE, m_button_pauze);
	DDX_Control(pDX, IDC_BTN_STOP, m_button_stop);
	DDX_Control(pDX, IDC_BTN_DETAIL, m_button_detail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMessageCentre, CDialog)
	//{{AFX_MSG_MAP(CMessageCentre)
	ON_BN_CLICKED(IDC_BTN_DETAIL, OnBtnDetail)
	ON_BN_CLICKED(IDC_BTN_PAUSE, OnBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	//ON_STN_CLICKED(IDC_BMP_NAME, OnStnClickedBmpName)
	//ON_STN_CLICKED(IDC_BMP_COMPANY, OnStnClickedBmpCompany)
	//ON_STN_CLICKED(IDC_BMP_CNAME, OnStnClickedBmpCname)
	//ON_STN_CLICKED(IDC_BMP_TF, OnStnClickedBmpTf)
	//ON_STN_CLICKED(IDC_TXTLBL_CHECKS_FAILED, OnStnClickedTxtlblChecksFailed)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						==============================
void					CMessageCentre::SetWindowTitle
//						==============================
(
	const char* 		pszWindowTitle
)
{
	SetWindowText(CString(pszWindowTitle));
}

//						==========================================
void					CMessageCentre::SetNumberOfActionWordsText
//						==========================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_TXTLBL_NUMBER_ACTIONWORDS, pszText);
}

//						======================================
void					CMessageCentre::SetNumberOfActionWords
//						======================================
(
	const char* 		pszActionWords
)
{
	SetControlText(IDC_TXT_NUMBER_ACTIONWORDS, pszActionWords);
}

//						==================================
void					CMessageCentre::SetButtonPauseText
//						==================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_BTN_PAUSE, pszText);
}

//						=================================
void					CMessageCentre::SetButtonStopText
//						=================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_BTN_STOP, pszText);
}

//						===================================
void					CMessageCentre::SetButtonDetailText
//						===================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_BTN_DETAIL, pszText);
}
	
//						==================================
void					CMessageCentre::SetGroupChecksText
//						==================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_GRP_CHECKS, pszText);
}

//						===========================================
void					CMessageCentre::SetNumberOfPassedChecksText
//						===========================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_TXTLBL_CHECKS_PASSED, pszText);
}

//						=======================================
void					CMessageCentre::SetNumberOfPassedChecks
//						=======================================
(
	const char* 		pszPassedChecks
)
{
	SetControlText(IDC_TXT_CHECKS_PASSED, pszPassedChecks);
}

//						===========================================
void					CMessageCentre::SetNumberOfFailedChecksText
//						===========================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_TXTLBL_CHECKS_FAILED, pszText);
}

//						=======================================
void					CMessageCentre::SetNumberOfFailedChecks
//						=======================================
(
	const char* 		pszFailedChecks
)
{
	SetControlText(IDC_TXT_CHECKS_FAILED, pszFailedChecks);
}

//						==================================
void					CMessageCentre::SetSuccessRateText
//						==================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_TXTLBL_SUCCESS_RATE, pszText);
}

//						==============================
void					CMessageCentre::SetSuccessRate
//						==============================
(
	const char* 		pszSuccesRate
)
{
	SetControlText(IDC_TXT_SUCCESS_RATE, pszSuccesRate);
}

//						==================================
void					CMessageCentre::SetGroupErrorsText
//						==================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_GRP_ERRORS, pszText);
}

//						================================
void					CMessageCentre::SetLastErrorText
//						================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_TXTLBL_LAST_ERROR, pszText);	
}

//						============================
void 					CMessageCentre::SetLastError
//						============================
(
	const char* 		pszLastError
)
{
	SetControlText(IDC_TXT_ERROR, pszLastError);
}

//						=====================================
void					CMessageCentre::SetNumberOfErrorsText
//						=====================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_TXTLBL_ERRORS_FOUND, pszText);
}

//						=================================
void 					CMessageCentre::SetNumberOfErrors
//						=================================
(
	const char* 		pszErrors
)
{
	SetControlText(IDC_TXT_ERRORS_FOUND, pszErrors);
}

//						==============================
void					CMessageCentre::SetMessageText
//						==============================
(
	const char* 		pszText
)
{
	SetControlText(IDC_TXTLBL_MESSAGE, pszText);
}

//						==========================
void 					CMessageCentre::SetMessage
//						==========================
(
	const char* 		pszMessage
)
{
	SetControlText(IDC_TXT_MESSAGE, pszMessage);
}

//						========================================
void					CMessageCentre::SetCurrentActionWordText
//						========================================
(
	const char* 		pszText
)
{
	SetControlText(IDC_TXTLBL_CURRENT_ACTIONWORD, pszText);
}

//						====================================
void 					CMessageCentre::SetCurrentActionWord
//						====================================
(
	const char* 		pszActionword
)
{//IDC_TXT_CURRENT_ACTIONWORD
	SetControlText(IDC_EDIT1, pszActionword);
}

//						===========================
void					CMessageCentre::SetProgress
//						===========================
(
	int					nPermillage
)
{
	// Make sure we are visible
	while (!::IsWindow(m_hWnd))
	{ 
		Sleep(100); 
	}
	if (m_hWnd != NULL)
	{
		// Adjust the progress indicator
		if(m_Progress.m_hWnd != NULL)
		{
			m_Progress.SetPos(nPermillage);
		}
	}
}

//						===========================
void					CMessageCentre::ShowMessage
//						===========================
(
	const char* 		pszMessage,
	const char*			pszTitle
)
{
	// Show a message box with the message
	if ((pszMessage != NULL) && (pszTitle != NULL))
	{ MessageBox(pszMessage, pszTitle); }
}

//						==============================
void					CMessageCentre::ShowMoreDetail()
//						==============================
{
	// Show the user the complete dialog

	// Get the current window size
	CRect wndRect;
	GetWindowRect(&wndRect);

	// Add the difference between the 'More Detail' and 'Less Detail' states
	wndRect.bottom += m_nHeightDifference;

	// Resize and repaint the window
	MoveWindow(&wndRect);
}

//						==============================
void					CMessageCentre::ShowLessDetail()
//						==============================
{
	// Show the user only the progress indicator and the buttons

	// Get the current window size
	CRect wndRect;
	GetWindowRect(&wndRect);

	// Subtract the difference between the 'More Detail' and 'Less Detail' states
	wndRect.bottom -= m_nHeightDifference;

	// Resize and repaint the window
	MoveWindow(&wndRect);
}

//						====================
void					CMessageCentre::Show()
//						====================
{
	// Synchronise threads
	if(m_hWnd)
	{
		while (!::IsWindow(m_hWnd))
		{ 
			Sleep(100); 
		}

		// Unhide the window
		SetWindowPos(m_bAlwaysOnTop ? &wndTopMost : &wndTop, 0, 0, 0, 0, 
					 SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
}

//						====================
void					CMessageCentre::Hide()
//						====================
{
	// Synchronise threads
	if(m_hWnd)
	{
		while (!::IsWindow(m_hWnd))
		{ 
			Sleep(100); 
		}

		// Hide the window
		SetWindowPos(m_bAlwaysOnTop ? &wndTopMost : &wndTop, 0, 0, 0, 0, 
					 SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMessageCentre message handlers

//						============================
BOOL 					CMessageCentre::OnInitDialog() 
//						============================
{
	CDialog::OnInitDialog();

	// Set icon on the dialog
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON2);
	// Make it a small icon
	SetIcon(icon,false);

	// Change the dialog background to yellow
	m_brush.CreateSolidBrush(RGB(255,204,0));

	// Calculate the difference in height for 'Less Detail' en 'More Detail'
	// states of this dialog
	WINDOWPLACEMENT wp;
	CRect Recto;
	CWnd* pMore;
	CWnd* pLess;
	int nCaptionHeight = ::GetSystemMetrics(SM_CYCAPTION);

	m_nHeightDifference = 0;
	pMore = GetDlgItem(IDC_MORE_DETAIL_SIZE);
	pLess = GetDlgItem(IDC_LESS_DETAIL_SIZE);

	if ((pMore != 0) && (pLess != 0))
	{
		//pMore->GetWindowPlacement(&wp);
		//m_nHeightDifference = wp.rcNormalPosition.bottom;
		GetClientRect(&Recto);
		m_nHeightDifference = Recto.bottom; // + nCaptionHeight;

		pLess->GetWindowPlacement(&wp);
		m_nHeightDifference = m_nHeightDifference - wp.rcNormalPosition.bottom;


	}

//	m_button_pauze.SubclassDlgItem(IDC_BTN_PAUSE,this);
//	m_button_stop.SubclassDlgItem(IDC_BTN_STOP,this);
//	m_button_detail.SubclassDlgItem(IDC_BTN_DETAIL,this);
//	m_Progress.SubclassDlgItem(IDC_PROGRESS,this);

	// Set the texts of all controls
	m_pDlg->SetControlTexts();

	// Set the range of the progress indicator (0 ... 1000)
	m_Progress.SetRange(0, 1000);

	// Return TRUE unless you set the focus to a control
	return TRUE;
}

//						===========================
void 					CMessageCentre::OnBtnDetail() 
//						===========================
{
	// Call our non-MFC equivalent
	if(m_pDlg)
	{
		m_pDlg->OnDetail();
	}
}

//						==========================
void 					CMessageCentre::OnBtnPause() 
//						==========================
{
	// Call our non-MFC equivalent
	if(m_pDlg)
	{
		m_pDlg->OnPause();
	}
}

//						=========================
void 					CMessageCentre::OnBtnStop()
//						=========================
{
	// Call our non-MFC equivalent
	if(m_pDlg)
	{
		m_pDlg->OnStop();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						==============================
void					CMessageCentre::SetControlText
//						==============================
(
	int 				nControlID,
	const char* 		pszText
)
{
	// Make sure we are visible
	if (m_hWnd != 0)
	{
		// Retrieve a pointer to the dialog item
		CWnd* pWnd = GetDlgItem(nControlID);
		
		// First check if the pointers are not null
		if ((pWnd != 0) && (pszText != 0))
		{ 
			pWnd->SetWindowText(CString(pszText));
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/*
void CMessageCentre::OnStnClickedBmpName()
{
	// TODO: Add your control notification handler code here
}

void CMessageCentre::OnStnClickedBmpCompany()
{
	// TODO: Add your control notification handler code here
}

void CMessageCentre::OnStnClickedBmpCname()
{
	// TODO: Add your control notification handler code here
}

void CMessageCentre::OnStnClickedBmpTf()
{
	// TODO: Add your control notification handler code here
}

void CMessageCentre::OnStnClickedTxtlblChecksFailed()
{
	// TODO: Add your control notification handler code here
}
*/

//HBRUSH CMessageCentre::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// Set the background mode for text to transparent 
//	// so background will show through.
//	pDC->SetBkMode(TRANSPARENT);
//
//	return m_brush;
//}

void CMessageCentre::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}

void CMessageCentre::OnClose()
{
	// TODO: Add your message handler code here and/or call default
//	MessageBox("test","test",MB_OK);
	
	// Call our non-MFC equivalent
	//if(m_pDlg)
	//{
	//	m_pDlg->OnStop();
	//}
	//m_pDlg->Exit();
	//delete this;
	::exit(0);

	CDialog::OnClose();
}
