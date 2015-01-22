/*****************************************************************************
 * $Workfile: MasterCommand.cpp $
 * $Revision: 5 $
 * $Modtime: 8/15/01 5:22p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#pragma warning(disable:4786)

#include <set>
#include <string>
#include <vector>

using namespace std;

#include "EngineUtil.h"
#include "Log.h"
#include "MasterCommand.h"
#include "Slave.h"
#include "SlaveList.h"
#include "StrUtil.h"
#include "TcpIpServer.h"

#define TRIALS_BEFORE_TIMEOUT	600

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
MasterCommand::MasterCommand
(
	SlaveList*		pSlaveList
)
{
	m_pSlaveList = pSlaveList;
	m_pMasterServer = 0;
	m_pLog = Log::Instance();
}

// Destructor
MasterCommand::~MasterCommand()
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=======================================
bool					MasterCommand::WaitForSlaveRegistration
//						=======================================
(
	const vector<string>&	vstrSlaveList
)
{
	bool bResult = false;

	// Set the number of trials before time-out.
	int	nRetry = TRIALS_BEFORE_TIMEOUT;

	// Place the names of all unconnected slaves in a set; each name
	// appears now only once.
	set<string> sstrSlaves = VectorToSet( vstrSlaveList );

	// Loop as long as there are still slaves unconnected and there has
	// been no time-out.
	for ( ; !sstrSlaves.empty() && (nRetry > 0); nRetry-- )
	{
		// Go passed all slaves in the set.
		set<string>::iterator Iterator = sstrSlaves.begin();
		while ( Iterator != sstrSlaves.end() )
		{
			// Determine the next iterator.
			set<string>::iterator nextIterator = Iterator;
			nextIterator++;

			// Determine if the specified slave is present in the SlaveList.
			if ( m_pSlaveList->FindByName( *Iterator ) != 0 )
			{
				// Since the slave is connected, remove its name from the
				// set of unconnected slaves.
				sstrSlaves.erase( Iterator );
			}

			// Set the iterator to the next one.
			Iterator = nextIterator;
		}

		// Wait 0.5 second.
		EngineSleep( 500 );
	}

	// Determine if there are still unconnected slaves.
	if ( !sstrSlaves.empty() )
	{
		// Log for all these unconnected slaves that their connection
		// timed out.
		set<string>::iterator Iterator = sstrSlaves.begin();
		for ( ; Iterator != sstrSlaves.end(); Iterator++ )
		{
			m_pLog->SlaveConnected( *Iterator, false );
		}
	}
	else
	{
		// All specified slaves have been connected in time; success.
		bResult = true;
	}

	return bResult;
}


//						=============================
bool					MasterCommand::ProcessOnSlave
//						=============================
(
	const string&		strSlaveName,
	const string&		strTestLine,
	const int			nMode
)
{
	Slave* pSlave;					// Slave object

	pSlave = m_pSlaveList->FindByName(strSlaveName);
	// Search slave ID
	if (pSlave != 0)
	{
		// Send test line
		if ( m_pMasterServer != 0 )
		{
			m_pMasterServer->SendMessage(pSlave->GetID(),"Execute:" + strTestLine);
		}
	}

	//@@ todo sync async

	return true;
}

//						=========================
bool					MasterCommand::Disconnect
//						=========================
(
	const string&		strSlaveName
)
{
	bool bResult = false;

	// Get the Slave object for the specified slave from the SlaveList.
	Slave* pSlave = m_pSlaveList->FindByName( strSlaveName );

	// Determine if this slave is present in the SlaveList.
	if ( pSlave != 0 )
	{
		// Request slave to disconnect
		if ( m_pMasterServer != 0 )
		{
			m_pMasterServer->SendMessage(pSlave->GetID(),"Disconnect:");
		}

		// Remove slave from slavelist
		m_pSlaveList->Remove(strSlaveName);

		bResult = true;
	}

	return bResult;
}


//						==============================
void					MasterCommand::SetMasterServer
//						==============================
(
	TcpIpServer*		pMasterServer
)
{
	m_pMasterServer = pMasterServer;
}
