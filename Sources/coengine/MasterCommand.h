/*****************************************************************************
 * $Workfile: MasterCommand.h $
 * $Revision: 3 $
 * $Modtime: 6/15/01 6:29p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef MASTERCOMMAND_H
#define MASTERCOMMAND_H

// Includes
#include <string>
#include <vector>

// Forward declarations
class Log;
class SlaveList;
class TcpIpServer;

////////////////////////////////////////////////////////////////////////////////
// class MasterCommand

class MasterCommand
{
	// Construction and destruction
public:
	explicit MasterCommand(SlaveList* pSlaveList);

private:
	MasterCommand();							// Constructor
	MasterCommand(const MasterCommand& src);	// Copy contructor

	// Other constructors
public:
	~MasterCommand();							// Destructor

	// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	WaitForSlaveRegistration()
	//
	// description	:	Waits for slave registration
	//				  	
	// parameters	:	vstrSlaveName		vector of slave names
	//
	// returns		:	true	all specified slaves registered in time
	//					false	not all specified slaves registered in time
	///////////////////////////////////////////////////////////////////////////////
	bool WaitForSlaveRegistration( const vector<string>& vstrSlaveName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ProcessOnSlave()
	//
	// description	:	Send the testline to the slave to be processed
	//				  	
	// parameters	:	strSlaveName	slave name
	//					strTestLine		test line
	//					nMode			sync mode -- currently ignored
	//
	// returns		:	always true
	///////////////////////////////////////////////////////////////////////////////
	bool ProcessOnSlave( const string& strSlaveName, const string& strTestLine, 
		                 const int nMode);

	//////////////////////////////////////////////////////////////////////////////
	// function		:	Disconnect()
	//
	// description	:	Disconnect the slave; the slave will receive end of
	//					cluster
	//				  	
	// parameters	:	strSlaveName		slave name
	//
	// returns		:	true	slave disconnected
	//					false	slave could not be disconnected
	///////////////////////////////////////////////////////////////////////////////
	bool Disconnect( const string& strSlaveName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetMasterServer()
	//
	// description	:	Set the master server association
	//				  	
	// parameters	:	pMasterServer		pointer to master server
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void SetMasterServer(TcpIpServer* pMasterServer);

// Member variables
private:
	SlaveList*		m_pSlaveList;		// Association to slave list
	TcpIpServer*	m_pMasterServer;	// Association to master server
	Log*			m_pLog;				// Log object
};

////////////////////////////////////////////////////////////////////////////////

#endif // !MasterCommand_H