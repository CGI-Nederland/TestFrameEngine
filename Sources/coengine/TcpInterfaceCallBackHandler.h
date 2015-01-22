/*****************************************************************************
 * $Workfile: TcpInterfaceCallBackHandler.h $
 * $Revision: 2 $
 * $Modtime: 12/17/99 11:58a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TCPIPCALLBACKHANDLER_H
#define TCPIPCALLBACKHANDLER_H

#undef BASECLASS
#define BASECLASS TcpHandler

#include "TcpHandler.h"

// Forward declarations
class TcpInterface;

class TcpInterfaceCallBackHandler : public TcpHandler
{
	// Construction and destruction
private:
	TcpInterfaceCallBackHandler();							// Default constructor
	
	TcpInterfaceCallBackHandler(const TcpInterfaceCallBackHandler& right);	// Copy constructor

	// Other constructors
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		: TcpInterfaceCallBackHandler
	//
	// description	: Constructs a user interface callback handler
	//					
	// parameters	: TcpInterface				A pointer to the tcp interface
	//
	// returns		: None (constructor).
	//				  
	///////////////////////////////////////////////////////////////////////////////
	explicit TcpInterfaceCallBackHandler(TcpInterface* pTcpInterface);

	virtual ~TcpInterfaceCallBackHandler();					// Destructor

	//////////////////////////////////////////////////////////////////// ///////////
	// function		: MessageReceived
	//
	// description	: request for processing by MasterServer.
	//					
	// parameters	: string&					the received message
	//				  int						client ID
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void MessageReceived(const string& strMessage, const int nID);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Disconnect
	//
	// description	: This function is called when the TcpIpServer disconnects 
	//				  the client for any reason. Implement this message for 
	//					
	// parameters	: int					client id
	//
	// returns		: <void>				Nothing, nada, niets
	//				  
	///////////////////////////////////////////////////////////////////////////////
	virtual void Disconnect(const int nID);

	// Member variables
private:

	TcpInterface*				m_pTcpInterface;		// Association to tcp interface

};

#undef BASECLASS
#endif //!TCPIPCALLBACKHANDLER_H