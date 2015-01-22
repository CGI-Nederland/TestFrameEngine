/*****************************************************************************
 * $Workfile: TcpInterfaceCallBackHandler.cpp $
 * $Revision: 3 $
 * $Modtime: 12/17/99 11:59a $
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
#include "TcpInterfaceCallBackHandler.h"
#include "TcpInterface.h"

#define BASECLASS TcpHandler

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

TcpInterfaceCallBackHandler::TcpInterfaceCallBackHandler
(
	TcpInterface* pTcpInterface
)
{
	// Store as member
 	m_pTcpInterface = pTcpInterface;
}

// Destructor
TcpInterfaceCallBackHandler::~TcpInterfaceCallBackHandler()
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//			============================================
void		TcpInterfaceCallBackHandler::MessageReceived
//			============================================
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
		strArgument = strMessage.substr(nPosition + 1);

		// Execute command
		if (strCommand == "Execute") 
		{
			m_pTcpInterface->PushLine(strArgument);
		} 
		else if (strCommand == "Disconnect")
		{
			// Send EOT (0x004)
			m_pTcpInterface->PushLine("\x004");
		}
	}
}

//			=======================================
void		TcpInterfaceCallBackHandler::Disconnect
//			=======================================
(
	const int	  nID
) 
{
	// Send EOT (0x004)
	m_pTcpInterface->PushLine("\x004");

	// NOTE: this is a forced disconnect by the server
}
