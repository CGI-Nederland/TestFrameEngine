/*****************************************************************************
 * $Workfile: EngineCallBackHandler.cpp $
 * $Revision: 6 $
 * $Modtime: 6/22/00 2:42p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include <string>
#include <iostream>

using namespace std;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "EngineCallBackHandler.h"
#include "EngineInterface.h"
#include "TcpHandler.h"

#define BASECLASS TcpHandler

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

EngineCallBackHandler::EngineCallBackHandler
(
	EngineInterface* pEngineInterface
)
{
	// Store as member
	m_pEngineInterface = pEngineInterface;

	// Signal we have become active
	m_bActive = true;
}

// Destructor
EngineCallBackHandler::~EngineCallBackHandler()
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						======================================
void					EngineCallBackHandler::MessageReceived
//						======================================
(
	const string& strMessage,
	const int nID
) 
{
	string strCommand;
	string strArgument;

	// Parse message
	if ((m_pEngineInterface != 0) && GetString(strMessage, 0, strCommand)) 
	{
		// Show current action word
		if (strCommand == "ActionWord") 
		{
			// Actionword arguments can have a colon, so do not use GetString
			string::size_type nPos = strMessage.find_first_of(":");
			if (nPos != string::npos)
			{
				strArgument = strMessage.substr(nPos+1);
				m_pEngineInterface->ShowActionword(strArgument.c_str()); 
			}
		}
		// Show current cluster
		else if (strCommand == "Cluster")
		{
			// Filename can have a colon, so do not use GetString
			int nPos = strMessage.find_first_of(":");
			if (nPos != string::npos)
			{
				strArgument = strMessage.substr(nPos+1);
				m_pEngineInterface->ShowCluster(strArgument.c_str());
			}
		}
		// Show last reported error
		else if (strCommand == "Error")
		{
			int nErrors = 0;

			if (GetString(strMessage, 1, strArgument) && (GetInteger(strMessage, 2, nErrors)))
			{ m_pEngineInterface->ShowError(strArgument.c_str(), nErrors); }
		}
		// Update progress bar
		else if (strCommand == "Progress")
		{
			int nExecuted = 0;
			int nTotal = 0;
			
			if ((GetInteger(strMessage, 1, nExecuted)) && (GetInteger(strMessage, 2, nTotal)))
			{ m_pEngineInterface->ShowProgress(nExecuted, nTotal); }
		}
		// Show message center
		else if (strCommand == "Center")
		{
			string strDetail, strLang, strOnTop, strPaused;
			bool bSuccess;

			bSuccess = GetString(strMessage, 1, strDetail);
			bSuccess = bSuccess && GetString(strMessage, 2, strLang);
			bSuccess = bSuccess && GetString(strMessage, 3, strOnTop);
			bSuccess = bSuccess && GetString(strMessage, 4, strPaused);

			if (bSuccess)
			{
				bool bDetail = (strDetail == string("Yes"));
				bool bOnTop = (strOnTop == string("Yes"));
				bool bPaused = (strPaused == string("Yes"));

				m_pEngineInterface->ShowMessagecenter(bDetail, strLang, bOnTop, bPaused);
			}
		}
		// Engine paused or resumed
		else if (strCommand == "Pause")
		{
			string strPaused;
			bool bSuccess;

			bSuccess = GetString(strMessage, 1, strPaused);

			if (bSuccess)
			{
				bool bPaused = (strPaused == string("Yes"));
				if (bPaused)
				{ m_pEngineInterface->EnginePaused(); }
				else
				{ m_pEngineInterface->EngineResumed(); }
			}
		}
		// Show a message box
		else if (strCommand == "Message")
		{
			if (GetString(strMessage, 1, strArgument))
			{ m_pEngineInterface->ShowMessage(strArgument.c_str()); }
		}
		// Update number of checks
		else if (strCommand == "Checks")
		{
			int nPassed = 0;
			int nFailed = 0;
			
			if ((GetInteger(strMessage, 1, nPassed)) && (GetInteger(strMessage, 2, nFailed)))
			{ m_pEngineInterface->ShowChecks(nPassed, nFailed); }
		}
		// Terminate the message centre
		else if (strCommand == "Terminate")
		{
			// Signal we are not active anymore
			m_bActive = false;
		}
		else
		{ 
			string strError("[TFE6] Unknown message: "); 
			strError += strMessage;
			OutputDebugString(strError.c_str());
		}
	}
}

//						=============================
bool					EngineCallBackHandler::Active()
//						=============================
{
	// Just return our member
	return m_bActive;
}

//						=================================
void					EngineCallBackHandler::Disconnect
//						=================================
(
	const int nID
)
{
	/* EMPTY */
}

///////////////////////////////////////////////////////////////////////////////