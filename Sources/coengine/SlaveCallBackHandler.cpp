/*****************************************************************************
 * $Workfile: SlaveCallBackHandler.cpp $
 * $Revision: 3 $
 * $Modtime: 12/17/99 11:58a $
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
#include "SlaveCallBackHandler.h"
#include "SlaveList.h"
#include "Slave.h"

#define BASECLASS TcpHandler

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

SlaveCallBackHandler::SlaveCallBackHandler
(
	SlaveList* pSlaveList
)
{
	// Store as member
 	m_pSlaveList = pSlaveList;
}

// Destructor
SlaveCallBackHandler::~SlaveCallBackHandler()
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//			=====================================
void		SlaveCallBackHandler::MessageReceived
//			=====================================
(
	const string& strMessage,
	const int	  nID
) 
{
	int nPosition = 0;			// command-argument delimiter
	
	nPosition = strMessage.find_first_of(":");
	// parse message
	if (nPosition != string::npos)
	{
		string strCommand;
		string strArgument;
		strCommand	= strMessage.substr(0,nPosition);
		strArgument = strMessage.substr(nPosition + 1);

		// Execute command
		if (strCommand == "Register") 
		{
			m_pSlaveList->Add(strArgument, new Slave(nID, strArgument, Slave::SYNC, Slave::READY));			
		} 
		else if (strCommand == "Ready")
		{
			(m_pSlaveList->FindByID(nID))->SetStatus(Slave::READY);
		}
		else if (strCommand == "Busy")
		{
			(m_pSlaveList->FindByID(nID))->SetStatus(Slave::BUSY);
		}
	}
}

//			================================
void		SlaveCallBackHandler::Disconnect
//			================================
(
	const int	  nID
) 
{
	// Remove slave from slave list
	m_pSlaveList->Remove((m_pSlaveList->FindByID(nID))->GetName());
}
