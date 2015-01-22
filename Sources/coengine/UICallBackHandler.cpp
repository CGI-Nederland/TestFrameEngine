/*****************************************************************************
 * $Workfile: UICallBackHandler.cpp $
 * $Revision: 4 $
 * $Modtime: 12/17/99 1:22p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include <string>
#include <iostream>

using namespace std;

#include "TcpHandler.h"
#include "UICallBackHandler.h"
#include "GuiInterface.h"
#include "UIHandler.h"

#define BASECLASS TcpHandler

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

UICallBackHandler::UICallBackHandler
(
	GuiInterface* pGuiInterface,
	UIHandler*	  pUIHandler
)
{
	// Store as member
	m_pGuiInterface = pGuiInterface;
	m_pUIHandler    = pUIHandler;
}

// Destructor
UICallBackHandler::~UICallBackHandler()
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//			==================================
void		UICallBackHandler::MessageReceived
//			==================================
(
	const string& strMessage,
	const int	  nID
) 
{
	int nPosition = 0;			// command-argument delimiter

	nPosition = static_cast<int>(strMessage.find_first_of(":"));

	// parse message
	if (nPosition != static_cast<int>(string::npos))
	{
		string strCommand;
		string strArgument;
		strCommand	= strMessage.substr(0,nPosition);

		// Cut the argument, minus 2 to lose to newline character
		strArgument = strMessage.substr(nPosition + 1, (strMessage.length()-nPosition)-2);

		// Execute command
		if (strCommand == "Stop") 
		{
			// Call stop
			m_pGuiInterface->Stop();
		} 
		else if (strCommand == "Pause")
		{
			// Call resume
			m_pGuiInterface->Pause();
		}
		else if (strCommand == "Resume")
		{
			// Call resume
			m_pGuiInterface->Resume();
		}
		else if (strCommand == "Register")
		{
			// Send all currently available UI data to fresh connected UI client
			m_pUIHandler->ShowAll(nID);
		}
	}
}

//			=============================
void		UICallBackHandler::Disconnect
//			=============================
(
	const int	  nID				// NOT USED
) 
{
	// Do nothing, the UIServer does not care if a GUI is connected or not.
}
