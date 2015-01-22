/*****************************************************************************
 * $Workfile: TcpIpConnection.cpp $
 * $Revision: 6 $
 * $Modtime: 8-02-01 11:35 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "TcpIpConnection.h"		// Class definition

//#include <string>
//using namespace std;

#include "EngineDebug.h"		// Engine debug facilities
#include "EngineUtil.h"			// Engine utilities
#include "tcpsocket.h"			// Sockets
#include "tcperror.h"			// Socket errors
#include "Thread.h"				// Thread class definition

// Send and receive buffer for TcpIp communication
#define BUFFER_SIZE				500
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and desctruction

TcpIpConnection::TcpIpConnection()
{
	// For debugging purposes
	EngineDebugOutput("TcpIpConnection::TcpIpConnection()", THREAD, 0);
	
	// Initialise connnection state
	m_bConnected	= false;
	// Initialise callback ID
	m_nID			= 0;
	m_pSocket		= NULL;
	m_strHostName	= "";
	m_nPortNumber	= 0;
	m_pCallbackHandler = NULL;
}

TcpIpConnection::~TcpIpConnection()
{
	// For debugging purposes
	EngineDebugOutput("TcpIpConnection::~TcpIpConnection()", THREAD, 0);

	// Stop the thread
	Stop();
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						======================
void					TcpIpConnection::SetID
//						======================
(
	int		nID
)
{
	m_nID = nID;
}

//						====================
int						TcpIpConnection::GetID() const
//						====================
{
	return m_nID;
}

//						=====================
bool					TcpIpConnection::Open()
//						=====================
{
	// Set connection state to not connected
	m_bConnected = false;

	// Create a socket
	m_pSocket = new tcpsocket();

	try
	{
		// Try to connect
		m_pSocket->connect(m_strHostName.c_str(), m_nPortNumber);

		// Set connection state to connected
		m_bConnected = true;
	}
	catch (tcperror& e)
	{ 
		// For debugging purposes
		string strError("Socket error ");
		strError += e.what();
			
		EngineDebugOutput(strError, THREAD, 0);
	}

	return m_bConnected;
}

//						=====================
bool					TcpIpConnection::Open
//						=====================
(
	tcpsocket*	pSocket
)
{
	// Set socket
	m_pSocket = pSocket;

	// Set connection status
	m_bConnected = true;

	return m_bConnected;
}

//						==============================
bool					TcpIpConnection::SetPortNumber
//						==============================
(
	unsigned short		nPortNumber
)
{
	bool bResult = false;

	// Please note that normally you should not use port numbers below 1024.
	// We do not test it because for example under Windows 95 you are alowed
	// to use these restricted port numbers.

	if ((nPortNumber > 0) && (nPortNumber < 65536))
	{ 
		bResult = true;
		m_nPortNumber = nPortNumber;
	}

	return bResult;
}

//						========================
unsigned int			TcpIpConnection::GetPort() const
//						========================
{
	return m_nPortNumber;
}

//						========================
bool					TcpIpConnection::SetHost
//						========================
(
	const string&		strHostName
)
{
	bool bResult = false;

	// We do not accept an empty host name
	if (!strHostName.empty())
	{ 
		bResult = true;
		m_strHostName = strHostName;
	}

	return bResult;
}

//						========================
string					TcpIpConnection::GetHost() const
//						========================
{
	return m_strHostName;
}

//						======================
bool					TcpIpConnection::Start()
//						======================
{
	bool bResult = false;

	// Only start if callbackhandler is set
	if (m_pCallbackHandler != 0)
	{		
		// Start client thread
		if (Thread::Start())
		{ 
			// Number of retries
			int nRetry = 20;

			// Block until stream becomes available, max 10 sec
			while (!IsAvailable() && (nRetry != 0))
			{
				// Sleep 0.5 seconds
				EngineSleep(500);

				nRetry--;
			}

			bResult = IsAvailable();	
		}
	}

	return bResult;
}

//						=====================
bool					TcpIpConnection::Stop()
//						=====================
{
	// Signal the client thread to stop
	Thread::Stop();

	// Wait for thread to terminate
	WaitForThreadReturn();

	return true;
}

//						===================================
void					TcpIpConnection::SetCallbackHandler
//						===================================
(
	TcpHandler*			pCallbackHandler
)
{
	m_pCallbackHandler = pCallbackHandler;
}

//						============================
void					TcpIpConnection::SendMessage
//						============================
(
	const string&				strMessage
)
{
	// Send buffer
	char chBuffer[BUFFER_SIZE];
	
	// Make a copy of the message
	string strMessageToSend = strMessage;
	
	// Truncate the message to make it fit in the buffer
	if (strMessage.length() > BUFFER_SIZE-1) 
	{
		// Place substring of string in variable
		strMessageToSend = strMessage.substr(0,BUFFER_SIZE-1);
	}

	// Copy the message to the buffer
	strcpy(chBuffer, strMessageToSend.c_str());

	// Terminate the string
	chBuffer[strMessageToSend.length()]= 0;

	if (m_pSocket != 0)
	{	
		try
		{
			// Send packet
			if (IsAvailable())
			{ m_pSocket->send(&chBuffer, BUFFER_SIZE); }
		}
		catch (tcperror& e)
		{ 
			// For debugging purposes
			string strError("Socket error ");
			strError += e.what();
				
			EngineDebugOutput(strError, THREAD, 0);
		}
	}
}

//						============================
bool					TcpIpConnection::IsAvailable()
//						============================
{
	return m_bConnected;
}


//						====================
unsigned int			TcpIpConnection::Run()
//						====================
{

	// For debugging purposes
	EngineDebugOutput("TCP/IP connection thread starts", THREAD, 0);

	if (m_pSocket != 0)
	{
		try
		{
			// Receive buffer
			char	chBuffer[BUFFER_SIZE];

			// Loop until the someone askes for suicide
			while ((!m_bStop) && (m_bConnected))
			{	

				// Check if any data is available
				if (m_pSocket->recv_ready(40))
				{	
					// Read the data
					int nActual;
					int nLeft	= BUFFER_SIZE;
					int nIndex	= 0;

					while (nLeft > 0)
					{
						// Receive the data
						nActual = m_pSocket->recv(&chBuffer[nIndex],nLeft);

						if (nActual == 0)
						{
							
							// Set connection state to not connected
							m_bConnected = false;
							break;
						}

						nIndex += nActual;
						nLeft  -= nActual;
					}

					// If we are not connected anymore this is a false alert
					if (m_bConnected)
					{
						// Call the message handler
						m_pCallbackHandler->MessageReceived(string(chBuffer), m_nID);
					}
				}
			}

			// disconnect now
		m_pSocket->disconnect();

		}
		catch (tcperror& e)
		{ 
			// For debugging purposes
			string strError("Socket error ");
			strError += e.what();
			
			EngineDebugOutput(strError, THREAD, 0);
		}

		delete m_pSocket;
		m_pSocket = 0;
	}
	// For debugging purposes
	EngineDebugOutput("TCP/IP connection thread stops", THREAD, 0);

	// Notify callback handler that the connection is closed
	if(m_nID)
	{
		m_pCallbackHandler->Disconnect(m_nID);
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
