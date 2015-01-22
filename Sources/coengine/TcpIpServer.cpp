/*****************************************************************************
 * $Workfile: TcpIpServer.cpp $
 * $Revision: 15 $
 * $Modtime: 4/21/00 3:15a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#include "TcpIpServer.h"		// Class definition

#include <sstream>

using namespace std;

#include "EngineDebug.h"		// Engine debug facilities
#include "TcpHandler.h"			// Handler definition
#include "TcpIpConnection.h"	// TcpIpConnection class definition
#include "tcpsocket.h"			// Sockets
#include "tcperror.h"			// Socket errors
#include "Thread.h"				// Thread class definition

///////////////////////////////////////////////////////////////////////////////
// Construction and desctruction

TcpIpServer::TcpIpServer()
	: m_pCallbackHandler(NULL)
{ /* EMPTY */ }

TcpIpServer::~TcpIpServer()
{
	// For debugging purposes
	EngineDebugOutput("TcpIpServer::~TcpIpServer()", THREAD, 0);

	// Stop the server before destroying it
	Stop(); 
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						====================
bool					TcpIpServer::SetPort
//						====================
(
	unsigned int		nPortNumber
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

//						====================
unsigned int			TcpIpServer::GetPort()
//						====================
{
	return m_nPortNumber;
}

//						===============================
int						TcpIpServer::GetNumberOfClients()
//						===============================
{
	return static_cast<int>(m_vpChildren.size());
}


//						==================
bool					TcpIpServer::Start()
//						==================
{
	bool bResult = false;

	// Only start if port number and the callback handler are set.
	if ((m_nPortNumber != 0) && (m_pCallbackHandler != NULL))
	{
		// Check for errors
		if (Thread::Start())
		{ bResult = true; }
	}

	return bResult;
}

//						=================
bool					TcpIpServer::Stop()
//						=================
{
	// Signal the server thread to stop
	Thread::Stop();

	// Wait for the thread to terminate
	WaitForThreadReturn();

	return true;
}

//						======================
void					TcpIpServer::Broadcast
//						======================
(
	const string&		strMessage
)
{
	int cElements = static_cast<int>(m_vpChildren.size());

	for (int i = 0; i < cElements; i++)
	{
		// Only send data if this socket still has a connection
		if (m_vpChildren[i]->IsAvailable())
		{ SendMessage(i, strMessage); }
	}
}


//						========================
void					TcpIpServer::SendMessage
//						========================
(
	const int					nID,
	const string&				strMessage
)
{
	// Check if ID number is valid
	if ((nID >=0) && (nID < static_cast<int>(m_vpChildren.size())))
	{
		// Send message to specific client
		m_vpChildren[nID]->SendMessage(strMessage);
	}
}


//						===============================
void					TcpIpServer::SetCallbackHandler
//						===============================
(
	TcpHandler*			pCallbackHandler
)
{
	m_pCallbackHandler = pCallbackHandler;
}

//						==================
unsigned int			TcpIpServer::Run()
//						==================
{
	// For debugging purposes
	EngineDebugOutput("TCP/IP server thread starts", THREAD, 0);

	try
	{
		// Create a socket to listen on the supplied port number
		tcpsocket srvsock;
		srvsock.listen(m_nPortNumber);

		while (!m_bStop)
		{
			if (srvsock.recv_ready(40))
			{
				try
				{
					// Create new connection
					TcpIpConnection* pTcpIpConnection = new TcpIpConnection();

					// Set callback handler
					pTcpIpConnection->SetCallbackHandler(m_pCallbackHandler);

					// Set callback ID
					pTcpIpConnection->SetID(static_cast<int>(m_vpChildren.size()));

					// Create socket
					tcpsocket* pSocket = new tcpsocket();

					// Accept connection
					pSocket->accept(srvsock);

					// Open connection handler
					pTcpIpConnection->Open(pSocket);
					
					if (pTcpIpConnection->Start())
					{ 
						m_vpChildren.push_back(pTcpIpConnection); 
					}
					else
					{
						delete pTcpIpConnection;
						pTcpIpConnection=0;
					}
				}
				catch (tcperror& e)
				{ 
					// For debugging purposes
					string strError("Socket error in server thread: ");
					strError += e.what();

					EngineDebugOutput(strError, THREAD, 0);
				}
			}
		}

		// For debugging purposes
		EngineDebugOutput("Killing child threads", THREAD, 0);
		
		// Get number of children
		int cElements = static_cast<int>(m_vpChildren.size());
		int i = 0;

		// Signal all child threads to stop
		for (i = 0; i < cElements; i++)
		{ 
			m_vpChildren[i]->Stop(); 
		}

		// Wait for all child threads to stop
		for (i = 0; i < cElements; i++)
		{
			// Wait for the thread to terminate 
			m_vpChildren.back()->WaitForThreadReturn();

			// Free memory and discard pointer
			delete m_vpChildren.back();
			m_vpChildren.pop_back();
		}
	}
	catch (tcperror& e)
	{ 
		// For debugging purposes
		string strError("Socket error in server thread: ");
		strError += e.what();

		EngineDebugOutput(strError, THREAD, 0);
	}

	// For debugging purposes
	EngineDebugOutput("TCP/IP server thread stops", THREAD, 0);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////

