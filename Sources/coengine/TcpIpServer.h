/*****************************************************************************
 * $Workfile: TcpIpServer.h $
 * $Revision: 8 $
 * $Modtime: 4/21/00 3:15a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TCPIPSERVER_H
#define TCPIPSERVER_H

#include "Thread.h"

#include <string>					// STL strings
#include <vector>					// STL vectors
using namespace std;

#include "tcpsocket.h"				// tcpSocket

// Forward declarations
class TcpHandler;
class TcpIpConnection;

///////////////////////////////////////////////////////////////////////////////
// Class TcpIpServer

class TcpIpServer : public Thread
{
// Construction and destruction
public:
	TcpIpServer();
	virtual~TcpIpServer();

// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetPort
	//
	// Description:	Sets the port number
	//					
	// Parameters:	nPortNumber			Number of the tcpip port
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool SetPort(unsigned int nPortNumber);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetPort
	//
	// Description:	Gets the current port number
	//					
	// Parameters:	None
	//
	// Returns:		Number of the current tcpip port
	//				Zero when not yet set
	//				  
	///////////////////////////////////////////////////////////////////////////////
	unsigned int GetPort();


	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetNumberOfClients
	//
	// Description:	Return the number of connected clients
	//					
	// Parameters:	None
	//
	// Returns:		int						Number of connected clients
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfClients();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetCallbackHandler
	//
	// Description:	Sets the the callback handler, the handler is called every time
	//				a message is received.
	//					
	// Parameters:	TcpHandler*			callback handler
	//
	// Returns:		<void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetCallbackHandler(TcpHandler* pCallbackHandler);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Start
	//
	// Description:	Starts the server in a separate thread
	//					
	// Parameters:	None
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Start();
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	Stop
	//
	// Description:	Stops the server and waits for all threads involved to stop
	//					
	// Parameters:	None
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Stop();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Broadcast
	//
	// Description:	Broadcasts a message to all clients
	//					
	// Parameters:	strMessage			Message to send
	//
	// Returns:		None
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Broadcast(const string& strMessage);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SendMessage
	//
	// Description:	Sends a message to a specific client
	//					
	// Parameters:	nID					client identification
	//				strMessage			Message to send
	//
	// Returns:		None
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SendMessage(const int nId, const string& strMessage);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Run()
	//
	// description	: This is the thread method, after calling the start method this
	//				  method will be executed in a separate thread.
	//
	// parameters	: None
	//
	// returns		: unsigned int		Your own defined thread return code
	//
	///////////////////////////////////////////////////////////////////////////////
	unsigned int Run();

// Member variables
private:

	TcpHandler*					m_pCallbackHandler;			// Association to handler
	unsigned short				m_nPortNumber;
	vector<TcpIpConnection*>	m_vpChildren;

};

///////////////////////////////////////////////////////////////////////////////

#endif //!TCPIPSERVER_H
