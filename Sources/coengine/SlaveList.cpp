/*****************************************************************************
 * $Workfile: SlaveList.cpp $
 * $Revision: 3 $
 * $Modtime: 8/14/01 5:17p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <string>

using namespace std;

#include "Log.h"
#include "Slave.h"
#include "SlaveList.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//					====================
					SlaveList::SlaveList()
//					====================
{
	// Get or create the only allowed instance of Log.
	m_pLog = Log::Instance();
}

// Destructor
//					=====================
					SlaveList::~SlaveList()
//					=====================
{
	// Remove all objects
	Clear();
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						==============
void  					SlaveList::Add
//						==============
(
	const string&		strName,
	Slave*				pSlave
)
{
	map<string, Slave*>::iterator	SlaveIterator;	// Create iterator
	Slave*							pSlaveResult;	// Lookup result

	// check if entry exists
	SlaveIterator = m_mpSlave.find(strName);

	if (SlaveIterator != m_mpSlave.end())
	{
		// Defined 
		pSlaveResult = SlaveIterator->second;

		// Delete entry
		delete pSlaveResult;
		pSlaveResult=0;
	}
		
	// Add to slave list
	m_mpSlave[strName] = pSlave;

	// Log that the slave is connected.
	if ( m_pLog->Good() )
	{
		m_pLog->SlaveConnected( strName, true );
	}
}


//						=====================
Slave*  				SlaveList::FindByName
//						=====================
(
	const string&		strName
)
{
	map<string, Slave*>::iterator	SlaveIterator;	// Create iterator
	Slave*							pSlaveResult;	// Lookup result

	// check if entry exists
	SlaveIterator = m_mpSlave.find(strName);

	if (SlaveIterator != m_mpSlave.end())
	{
		// Defined return
		pSlaveResult = SlaveIterator->second;
	}
	else
	{
		// Not found return null
		pSlaveResult = NULL;
	}

	return pSlaveResult;
}

//						===================
Slave*  				SlaveList::FindByID
//						===================
(
	const int			nID
)
{
	Slave*							pSlaveResult;	// Lookup result
	map<string, Slave*>::iterator   iSlave;			// Slave interator
	bool							bFound;			// Search result

	// Set iterator to begin
	iSlave = m_mpSlave.begin();

	// Set search result to not found 
	bFound = false; 

	// check if entry exists
	while ((iSlave != m_mpSlave.end()) && !bFound)
	{
		// Compare ID
		if ((iSlave->second)->GetID() == nID) 
		{
			bFound = true;
		}

		// Increment iterator
		iSlave++;
	}

	// if result found
	if (bFound)
	{
		// Decrement iterator
		iSlave--;

		// set slave pointer
		pSlaveResult = iSlave->second;
	}
	else
	{
		// Not found
		pSlaveResult = NULL;
	}

	return pSlaveResult;
}


//						================
void  					SlaveList::Clear()
//						================
{

	// Clear and delete all entries
	for (map<string, Slave*>::iterator	p = m_mpSlave.begin(); p != m_mpSlave.end(); ++p)
	{
		delete p->second;
		p->second=0;
	}

	// Clear map
	m_mpSlave.clear();
}


//						=================
void  					SlaveList::Remove
//						=================
(
	const string&		strSlaveName
)
{
	Slave* pSlave;							// pointer to slave object

	// Get a pointer the slave object
	pSlave = FindByName(strSlaveName);

	if ( pSlave != 0 )
	{
		// Remove slave entry from map
		m_mpSlave.erase(strSlaveName);

		// Log that the specified slave has been disconnected.
		m_pLog->SlaveDisconnected( strSlaveName );

		// Delete slave object
		delete pSlave;
		pSlave=0;
	}
}


///////////////////////////////////////////////////////////////////////////////