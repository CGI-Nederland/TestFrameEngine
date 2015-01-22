/*****************************************************************************
 * $Workfile: TcpIpConnection.h $
 * $Revision: 2 $
 * $Modtime: 4/21/00 2:07a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/


#ifndef TCPIPCONNECTION_H
#define TCPIPCONNECTION_H

#include <string>					// STL strings
#include <vector>					// STL vectors
using namespace std;

#include "TcpHandler.h"				// TcpHandler
#include "tcpsocket.h"				// Socket class definition
#include "Thread.h"					// Thread class definition

///////////////////////////////////////////////////////////////////////////////
// Class TcpIpConnection

class TcpIpConnection : public Thread
{
// Construction and destruction
public:
	TcpIpConnection();
	virtual~TcpIpConnection();

// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetPortNumber
	//
	// Description:	Sets the port number
	//					
	// Parameters:	nPortNumber			Number of the tcpip port
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool SetPortNumber(unsigned short nPortNumber);

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
	unsigned int GetPort() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetHost
	//
	// Description:	Sets the host name
	//					
	// Parameters:	strHostName			Name of the host
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool SetHost(const string& strHostName);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetHost
	//
	// Description:	Gets the current host name
	//					
	// Parameters:	None
	//
	// Returns:		string				Name of the current host
	//				  
	///////////////////////////////////////////////////////////////////////////////
	string GetHost() const;

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
	void SetCallbackHandler(TcpHandler*	pCallbackHandler);

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
	// Function:	SendMessage
	//
	// Description:	Sends a message to the server
	//					
	// Parameters:	strMessage			Message to send
	//
	// Returns:		None
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SendMessage(const string& strMessage);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	IsAvailable
	//
	// Description:	Returns if the stream is available
	//					
	// Parameters:	None.
	//
	// Returns:		<void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool IsAvailable();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetID
	//
	// Description:	Sets the callback ID, if this function is not called the default
	//				ID (0) will be used.
	//					
	// Parameters:	int			callback ID
	//
	// Returns:		<void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetID(int nID);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetID
	//
	// Description:	Returns the callback ID
	//
	// Parameters:	None.
	//
	// Returns:		int			callback ID
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int GetID() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Open()
	//
	// Description:	Opens the TCP/IP connection if given host and port are valid.
	//
	// Parameters:	None.
	//
	// Returns:		true		connection opened successful.
	//				false		connection failure.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Open();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Open()
	//
	// Description:	Uses an already open socket connection.
	//
	// Parameters:	tcpsocket	an open socket connection
	//
	// Returns:		true		connection successful.
	//				false		connection failure.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Open(tcpsocket* pSocket);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Run()
	// description	: This is the thread method, after calling the start method this
	//				  method will be executed in a separate thread.
	//
	// parameters	: None
	//
	// returns		: Int		Your own defined thread return code
	//
	///////////////////////////////////////////////////////////////////////////////
	unsigned int Run();


// Member variables
private:
	unsigned short	m_nPortNumber;				// Socket port number
	string			m_strHostName;				// Connection host
	tcpsocket*		m_pSocket;					// Socket object
	bool			m_bConnected;				// Connection state
	int				m_nID;						// Callback ID
	TcpHandler*		m_pCallbackHandler;			// Association to handler
};

///////////////////////////////////////////////////////////////////////////////

#endif //!TCPIPCONNECTION_H
