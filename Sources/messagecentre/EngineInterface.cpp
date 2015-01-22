/*****************************************************************************
 * $Workfile: EngineInterface.cpp $
 * $Revision: 5 $
 * $Modtime: 4/19/00 1:17a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <iostream>
#include <string>
using namespace std;

#include "EngineInterface.h"			// class definition

#include "EngGuiApi.h"					// gui dll
#include "TcpIpConnection.h"			// TcpIpConnection class definition

// Global pointer to EngineInterface
EngineInterface* g_pTheEngineInterface = 0;

///////////////////////////////////////////////////////////////////////////////
// Callback function for enggui.dll

// Stop the engine
void __cdecl stop(void)
{
	if (g_pTheEngineInterface != 0)
	{ g_pTheEngineInterface->Stop(); }
}

// Pause the engine
void __cdecl pause(void)
{
	if (g_pTheEngineInterface != 0)
	{ g_pTheEngineInterface->Pause(); }
}

// Resume the engine
void __cdecl resume(void)
{
	if (g_pTheEngineInterface != 0)
	{ g_pTheEngineInterface->Resume(); }
}

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//					================================
					EngineInterface::EngineInterface
//					================================
(
	TcpIpConnection*		pClient
)
{
	// Remember TcpIpConnection
	if(pClient)
	{
		m_pClient = pClient;
	}
}

//					=================================
					EngineInterface::~EngineInterface()
//					=================================
{
	// Exit GUI dll
	enggui_exit();

	// Set the global pointer to zero again.
	g_pTheEngineInterface = 0;
}


///////////////////////////////////////////////////////////////////////////////
// Engine to GUI

//					==================================
int					EngineInterface::ShowMessagecenter
//					==================================
(
	bool			bDetail,
	const string&	strLanguage,
	bool			bOnTop,
	bool			bPause
)
{
	// Initialise GUI dll
	enggui_init(bDetail, strLanguage.c_str(), bOnTop, bPause);

	// Register stop, pause and resume in the GUI dll
	register_stop(stop);
	register_pause(pause);
	register_resume(resume);
	
	// Initialise global pointer to this object
	g_pTheEngineInterface = this;

	// Show the dialogue
	return show_messagecenter();
}

//					=============================
int					EngineInterface::ShowProgress
//					=============================
(
	int				nExecuted,
	int				nTotal
)
{
	// Call GUI dll
	if(show_progress(nExecuted, nTotal))
	{
		return show_progress(nExecuted, nTotal);
	}
	else
	{
		return 0;
	}
}

//					============================
int					EngineInterface::ShowCluster
//					============================
(
	const char*		pszCluster
)
{
	// Call GUI dll
	return show_cluster(pszCluster);
}

//					===============================
int					EngineInterface::ShowActionword
//					===============================
(
	const char*		pszActionWord
)
{
	// Call GUI dll
	return show_actionword(pszActionWord);
}

//					==========================
int					EngineInterface::ShowError
//					==========================
(
	const char*		pszError,
	int				nErrors
)
{
	// Call GUI dll
	return show_error(pszError, nErrors);
}

//					===========================
int					EngineInterface::ShowChecks
//					===========================
(
	int				nPassed,
	int				nFailed
)
{
	// Call GUI dll
	return	show_checks(nPassed, nFailed);
}

//					============================
int					EngineInterface::ShowMessage
//					============================
(
	const char*		pszMessage
)
{
	// Call GUI dll
	return show_message(pszMessage);
}
//					=============================
void				EngineInterface::EnginePaused()
//					=============================
{
	// Call GUI dll
	engine_paused();
}

//					==============================
void				EngineInterface::EngineResumed()
//					==============================
{
	// Call GUI dll
	engine_resumed();
}


///////////////////////////////////////////////////////////////////////////////
// GUI to Engine

//					=====================
void				EngineInterface::Stop()
//					=====================
{
	if (m_pClient)
	{ 
		m_pClient->SendMessage(string("Stop:"));
	}
}

//					======================
void				EngineInterface::Pause()
//					======================
{
	if (m_pClient)
	{ 
		m_pClient->SendMessage(string("Pause:"));
	}
}

//					=======================
void				EngineInterface::Resume()
//					=======================
{
	if (m_pClient)
	{ 
		m_pClient->SendMessage(string("Resume:"));
	}
}

//					=========================
void				EngineInterface::Register()
//					=========================
{
	if (m_pClient)
	{ 
		m_pClient->SendMessage(string("Register:"));
	}
}
///////////////////////////////////////////////////////////////////////////////