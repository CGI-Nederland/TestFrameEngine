/*****************************************************************************
 *$Workfile: CDialogThread.cpp $
 *$Revision: 4 $
 *$Modtime: 29-10-99 15:44 $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <afxwin.h>			// MFC core and standard components

#include "CDialogThread.h"		// Class definition
//#include "CMessageCentre.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Construction and destruction

IMPLEMENT_DYNCREATE(CDialogThread, CWinThread)

//						============================
						CDialogThread::CDialogThread()
//						============================
{
	m_bThreadIsRunning = false;
	m_pDlg = 0;
}

CDialogThread::~CDialogThread()
{
//	delete m_pDlg;
//	m_pDlg=0;
}
/////////////////////////////////////////////////////////////////////////////
// Attributes and operations
						
//						=====================
void					CDialogThread::SetDlg
//						=====================
(
	CDialog*			pDlg
)
{
	m_pDlg = pDlg;
}

//						===========================
BOOL					CDialogThread::InitInstance()
//						===========================
{
	m_bThreadIsRunning = true;
	return TRUE;
}

//						===========================
int						CDialogThread::ExitInstance()
//						===========================
{
//	AFX_MODULE_THREAD_STATE* pState=AfxGetModuleThreadState();
//	CHandleMap* pMap=pState->m_pmapHWND;

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDialogThread, CWinThread)
	//{{AFX_MSG_MAP(CDialogThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

bool CDialogThread::isThreadRunning()
{
	return m_bThreadIsRunning;
}
/////////////////////////////////////////////////////////////////////////////
// CDialogThread message handlers

//						==================
int						CDialogThread::Run()
//						==================
{
	if (m_pDlg != 0)
	{
		//Orig fails in Destroywindow call (pMap=NULL)
		m_pDlg->DoModal(); 
	}

	// Succesfull termination
	::PostQuitMessage(0);

	// Bart Beumer CHANGE: markeer dat thread niet meer draait (niet meest nette manier)
	// en terminate thread.
	m_bThreadIsRunning = false;
	while(1)
	{
		Sleep(10);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
