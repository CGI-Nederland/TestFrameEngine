/******************************************************************************
 *$Workfile: LocalMessageCentre.cpp $
 *$Revision: 13 $
 *$Modtime: 6/22/00 3:20p $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <afxwin.h>
#include "LocalMessageCentre.h"	// Class definition
#include "MessageCentre.h"		// Baseclass definition
#include "Dialog.h"				// Baseclass definition

#include "CMessageCentre.h"		// Equivalent MFC dialog
#include "CDialogThread.h"		// MFC Thread

#undef BASECLASS
#define BASECLASS MessageCentre

////////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						======================================
						LocalMessageCentre::LocalMessageCentre
//						======================================
(
	bool				bDetail,
	string				strLanguage,
	bool				bAlwaysOnTop,
	bool				bPause
)
{
	// Store the parameters
	m_bDetail = bDetail;
	m_bPaused = bPause;
	m_Texts.SetLanguage(strLanguage);

	hThread=NULL;

	// Empty cluster string
	m_strCluster = "";

	// Clear function pointers
	m_pStop = 0;
	m_pPause = 0;
	m_pResume = 0;

	// Create the MFC implementation of this dialog and thread
	m_pMfcThread = new CDialogThread();

	// We need to duplicate a handle to our thread. This way our child 
	// thread can put us to sleep
	h = ::GetCurrentThread();

	// Bart Beumer NOTE:
	// Deze manier voor gebruik verkrijgen handle is ok, zie
	// http://msdn2.microsoft.com/en-us/library/ms683182(VS.85).aspx
	
	::DuplicateHandle(GetCurrentProcess(), h, GetCurrentProcess(), &hThread,
						0, FALSE, DUPLICATE_SAME_ACCESS);
	
	m_pMfcDlg = new CMessageCentre(this, hThread, bAlwaysOnTop);
	//m_pMfcDlg = new CMessageCentre(this, 0, bAlwaysOnTop);

	// Give the pointer of the dlg to the thread
	m_pMfcThread->SetDlg(m_pMfcDlg);

	// Create a new thread and start the dialog hidden
	if ((m_pMfcDlg != 0) && (m_pMfcThread != 0))
	{
		m_pMfcThread->m_bAutoDelete=FALSE;
		m_pMfcThread->CreateThread();
		m_pMfcDlg->Hide();
	}
}
	
//						=======================================
						LocalMessageCentre::~LocalMessageCentre()
//						=======================================
{
	// Destroy the MFC implementation of this dialog and thread

	//1999//@@ Wilco - Why doesn't this work?
	//2007 AH Fixed
	if(m_pMfcThread)
	{
		delete m_pMfcThread;
		m_pMfcThread=0;
	}

	if(m_pMfcDlg)
	{
		delete m_pMfcDlg;
		m_pMfcDlg=0;
	}

	CloseHandle(h);
	CloseHandle(hThread);
}

/////////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=============================
void					LocalMessageCentre::SetChecks
//						=============================
(
	int					nPassed,	// Number of passed checks
	int					nFailed		// Number of failed checks
)
{
	// Call our MFC equivalent
	if (m_pMfcDlg != 0)
	{
		char pChars[10];
		m_pMfcDlg->SetNumberOfPassedChecks(_itoa(nPassed, pChars,10));
		m_pMfcDlg->SetNumberOfFailedChecks(_itoa(nFailed, pChars,10));
		
		int nPermillage = 0;
		
		if ((nPassed + nFailed) > 0)
		{
			nPermillage = nPassed * 1000;
			nPermillage = nPermillage / (nPassed + nFailed);
			string strPermillage = string(_itoa((nPermillage/10), pChars,10)) + "%";
			m_pMfcDlg->SetSuccessRate(strPermillage.c_str());
		}
	}
}

//						============================
void					LocalMessageCentre::SetError
//						============================
(
	const string&		strError,	// Last error
	int					nErrors		// Number of errors
)
{
	// Call our MFC equivalent
	if (m_pMfcDlg != 0)
	{
		char pChars[10];
		m_pMfcDlg->SetLastError(strError.c_str());
		m_pMfcDlg->SetNumberOfErrors(_itoa(nErrors, pChars,10));
	}
}

//						========================================
void					LocalMessageCentre::SetCurrentActionWord
//						========================================
(
	const string&		strActionWord	// Current action word
)
{
	// Call our MFC equivalent
	if (m_pMfcDlg != 0)
	{ 
		m_pMfcDlg->SetCurrentActionWord(strActionWord.c_str()); 
	}
}

//						===============================
void					LocalMessageCentre::ShowMessage
//						===============================
(
	const string&		strMessage		// String with message
)
{
	// Get the title for the message box
	string strTitle = m_Texts.GetText(MessageCentreList::ID_MESSAGEBOX);

	// Call our MFC equivalent
	if (m_pMfcDlg != 0)
	{ 
		m_pMfcDlg->ShowMessage(strMessage.c_str(), strTitle.c_str()); 
	}

	// Engine is paused now, so resume.
	// First call Pause() to make sure the GUI is still in the paused state. 
	// This is necessary because the engine can be resumed by other GUI's too!
	Pause();
	OnPause();
}

//						=====================================
void					LocalMessageCentre::SetCurrentCluster
//						=====================================
(
	const string&		strCluster	// Current cluster
)
{
	string strText;
	
	// Set the name of the current cluster
	m_strCluster = strCluster;
	strText = m_Texts.GetText(MessageCentreList::ID_TXT_MESSAGE_RUNNING, m_strCluster);

	// Change the text of the message only if the engine is not paused
	if ((!m_bPaused) && (m_pMfcDlg != 0))
	{ 
		m_pMfcDlg->SetMessage(strText.c_str()); 
	}
}

//						===============================
void					LocalMessageCentre::SetProgress
//						===============================
(
	int					nExecuted,	// Number of executed actionwords
	int					nTotal		// Total number of actionwords
)
{
	// Set the progress indicator and the progress text

	char pChars[10];
	int nPermillage = 0;
	
	if (nTotal > 0)
	{
		nPermillage = 1000 * nExecuted;
		nPermillage = nPermillage / nTotal;
	}

	string strText;

	string strExecuted = string(_itoa(nExecuted, pChars, 10));
	string strTotal = string(_itoa(nTotal, pChars, 10));
	string strPermillage = string(_itoa((nPermillage/10), pChars, 10));

	strText = m_Texts.GetText(MessageCentreList::ID_TXT_NUMBER_ACTIONWORDS,
								strExecuted, strTotal, strPermillage);

	// Call our MFC equivalent
	if (m_pMfcDlg != NULL)
	{
		m_pMfcDlg->SetProgress(nPermillage);
		m_pMfcDlg->SetNumberOfActionWords(strText.c_str());
	}
}

//						===================================
void					LocalMessageCentre::SetControlTexts()
//						===================================
{
	string strTmp;

	if (m_pMfcDlg != 0)
	{ 
		///////////////////////////////////////////////////////////////////////
		// Window title
		strTmp = m_Texts.GetText(MessageCentreList::ID_MESS_CENTRE);
		m_pMfcDlg->SetWindowTitle(strTmp.c_str());

		///////////////////////////////////////////////////////////////////////
		// Progress indicator
		strTmp = m_Texts.GetText(MessageCentreList::ID_TXTLBL_NUMBER_ACTIONWORDS);
		m_pMfcDlg->SetNumberOfActionWordsText(strTmp.c_str());
		m_pMfcDlg->SetNumberOfActionWords("");

		///////////////////////////////////////////////////////////////////////
		// Stop button
		strTmp = m_Texts.GetText(MessageCentreList::ID_BTN_STOP);
		m_pMfcDlg->SetButtonStopText(strTmp.c_str());
		
		///////////////////////////////////////////////////////////////////////
		// Pause/Resume button
		if (m_bPaused)
		{ 
			strTmp = m_Texts.GetText(MessageCentreList::ID_BTN_RESUME);
			m_pMfcDlg->SetButtonPauseText(strTmp.c_str());
		}
		else
		{ 
			strTmp = m_Texts.GetText(MessageCentreList::ID_BTN_PAUSE);
			m_pMfcDlg->SetButtonPauseText(strTmp.c_str());
		}

		///////////////////////////////////////////////////////////////////////
		// Detail button
		if (m_bDetail)
		{ 
			strTmp = m_Texts.GetText(MessageCentreList::ID_BTN_DETAIL_LESS);
			m_pMfcDlg->SetButtonDetailText(strTmp.c_str());
		}
		else
		{
			strTmp = m_Texts.GetText(MessageCentreList::ID_BTN_DETAIL_MORE);
			m_pMfcDlg->SetButtonDetailText(strTmp.c_str());

			// Hide detailed part of the window
			m_pMfcDlg->ShowLessDetail();
		}

		///////////////////////////////////////////////////////////////////////
		// Checks group
		strTmp = m_Texts.GetText(MessageCentreList::ID_GRP_CHECKS);
		m_pMfcDlg->SetGroupChecksText(strTmp.c_str());

		strTmp = m_Texts.GetText(MessageCentreList::ID_TXTLBL_CHECKS_PASSED);
		m_pMfcDlg->SetNumberOfPassedChecksText(strTmp.c_str());

		strTmp = m_Texts.GetText(MessageCentreList::ID_TXTLBL_CHECKS_FAILED);
		m_pMfcDlg->SetNumberOfFailedChecksText(strTmp.c_str());

		strTmp = m_Texts.GetText(MessageCentreList::ID_TXTLBL_SUCCESS_RATE);
		m_pMfcDlg->SetSuccessRateText(strTmp.c_str());

		///////////////////////////////////////////////////////////////////////
		// Errors group
		strTmp = m_Texts.GetText(MessageCentreList::ID_GRP_ERRORS);
		m_pMfcDlg->SetGroupErrorsText(strTmp.c_str());

		strTmp = m_Texts.GetText(MessageCentreList::ID_TXTLBL_LAST_ERROR);
		m_pMfcDlg->SetLastErrorText(strTmp.c_str());
		
		strTmp = m_Texts.GetText(MessageCentreList::ID_TXTLBL_ERRORS_FOUND);
		m_pMfcDlg->SetNumberOfErrorsText(strTmp.c_str());

		///////////////////////////////////////////////////////////////////////
		// Message
		strTmp = m_Texts.GetText(MessageCentreList::ID_TXTLBL_MESSAGE);
		m_pMfcDlg->SetMessageText(strTmp.c_str());

		///////////////////////////////////////////////////////////////////////
		// Current actionword
		strTmp = m_Texts.GetText(MessageCentreList::ID_TXTLBL_CURRENT_ACTIONWORD);
		m_pMfcDlg->SetCurrentActionWordText(strTmp.c_str());
	}
}

//						==============================
void					LocalMessageCentre::DoModeless()
//						==============================
{
	// Unhide the dialog
	if ((m_pMfcDlg) && (m_pMfcThread))
	{
		m_pMfcDlg->Show(); 
	}
}

//						================================
void					LocalMessageCentre::RegisterStop
//						================================
(
	void				(*pStop)(void)
)
{
	m_pStop = pStop;
}

//						==========================
void					LocalMessageCentre::OnStop()
//						==========================
{
	// The user pressed 'Stop'
	if (m_pStop != 0)
	{ m_pStop(); }
}

//						==================================
void					LocalMessageCentre:: RegisterPause
//						==================================
(
	void				(*pPause)(void)
)
{
	m_pPause = pPause;
}

//						==================================
void 					LocalMessageCentre::RegisterResume
//						==================================
(
	void				(*pResume)(void)
)
{
	m_pResume = pResume;
}

//						===========================
void					LocalMessageCentre::OnPause()
//						===========================
{
	// The user pressed 'Pause' or 'Resume'
	if (m_bPaused)
	{
		Resume();

		if (m_pResume != 0)
		{ 
			m_pResume(); 
		}
	}
	else
	{
		Pause();

		if (m_pPause != 0)
		{ 
			m_pPause(); 
		}
	}
}

//						=========================
void					LocalMessageCentre::Pause()
//						=========================
{
	string strText;
	if (!m_bPaused)
	{
		// Show the paused message
		strText= m_Texts.GetText(MessageCentreList::ID_TXT_MESSAGE_PAUSED, m_strCluster);
		m_pMfcDlg->SetMessage(strText.c_str());

		// Change the button text
		strText= m_Texts.GetText(MessageCentreList::ID_BTN_RESUME, m_strCluster);
		m_pMfcDlg->SetButtonPauseText(strText.c_str());

		// Change state
		m_bPaused = true;
	}
}

//						==========================
void					LocalMessageCentre::Resume()
//						==========================
{
	string strText;
	if (m_bPaused)
	{
		// Set the 'Running cluster'message
		strText= m_Texts.GetText(MessageCentreList::ID_TXT_MESSAGE_RUNNING, m_strCluster);
		m_pMfcDlg->SetMessage(strText.c_str());

		// Change the button text
		strText= m_Texts.GetText(MessageCentreList::ID_BTN_PAUSE, m_strCluster);
		m_pMfcDlg->SetButtonPauseText(strText.c_str());

		// Change state
		m_bPaused = false;
	}
}

//						============================
void					LocalMessageCentre::OnDetail()
//						============================
{
	// The user pressed 'More Detail' or 'Less Detail'
	
	string strText;

	if (m_bDetail)
	{
		// Hide detailed part of the dialog
		m_pMfcDlg->ShowLessDetail();
		
		// Change the button text
		strText = m_Texts.GetText(MessageCentreList::ID_BTN_DETAIL_MORE);
		m_pMfcDlg->SetButtonDetailText(strText.c_str());
		
		// Change state
		m_bDetail = false;
	}
	else
	{
		// Show detailed part of the dialog
		m_pMfcDlg->ShowMoreDetail();
		
		// Change the button text
		strText = m_Texts.GetText(MessageCentreList::ID_BTN_DETAIL_LESS);
		m_pMfcDlg->SetButtonDetailText(strText.c_str());
		
		// Change state
		m_bDetail = true;
	}
}

//						========================
void 					LocalMessageCentre::Exit()
//						========================
{
	// Send a WM_CLOSE message and wait for the Dialog to close.
	m_pMfcDlg->PostMessage(WM_QUIT,0,0);
	//m_pMfcDlg->PostMessage(WM_CLOSE,0,0);	
	if (m_pMfcThread != 0)
	{
		// Bart Beumer CHANGE (tijdelijk, kan weer worden terugveranderd)
		// LET OP: Dit is nog geen mooie oplossing. Kan Beter!
		while(m_pMfcThread->isThreadRunning())
		{
			Sleep(10);
		}
		//  Bart Beumer CHANGE:
		//  Het gebruik van TerminateThread wordt zeer afgeraden en alleen gebruiken in
		//  zeer uitzonderlijke situaties. zie ook:
		//  http://msdn2.microsoft.com/en-us/library/ms686717(VS.85).aspx
		//
		//  Dit is helaas een zeer uitzonderlijke situatie
		TerminateThread(m_pMfcThread->m_hThread,0);

	}
	
}
/////////////////////////////////////////////////////////////////////////////////
// Implementation

/////////////////////////////////////////////////////////////////////////////////
