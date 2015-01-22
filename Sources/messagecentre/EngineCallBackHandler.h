/*****************************************************************************
 * $Workfile: EngineCallBackHandler.h $
 * $Revision: 5 $
 * $Modtime: 6/22/00 11:26a $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ENGINECALLBACKHANDLER_H
#define ENGINECALLBACKHANDLER_H

#undef BASECLASS
#define BASECLASS TcpHandler

#include "TcpHandler.h"

// Forward declarations
class EngineInterface;

class EngineCallBackHandler : public TcpHandler
{
// Construction and destruction
public:
	explicit EngineCallBackHandler(EngineInterface* pGuiInterface);
	virtual ~EngineCallBackHandler();

private:
	EngineCallBackHandler();							// Default constructor
	EngineCallBackHandler(const EngineCallBackHandler& right);	// Copy constructor


// Attibutes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		: Message received
	//
	// description	: This function is called when the TcpIpServer has received
	//				  a message.
	//					
	// parameters	: string				the message string
	//
	// returns		: <void>				Nothing, nada, niets
	//				  
	///////////////////////////////////////////////////////////////////////////////
	virtual void MessageReceived(const string& strMessage, const int nID);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Disconnect
	//
	// description	: This function is called when the TcpIpServer disconnects 
	//				  the client for any reason.
	//					
	// parameters	: int					client id
	//
	// returns		: <void>				Nothing, nada, niets
	//				  
	///////////////////////////////////////////////////////////////////////////////
	virtual void Disconnect(const int nID);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Active
	//
	// description	: This function returns the state of the callbackhandler
	//				  active or not.
	//					
	// parameters	: none
	//
	// returns		: true					Callback handler is still active
	//				  false					Callback handler is terminated
	//				  
	///////////////////////////////////////////////////////////////////////////////
	virtual bool Active();

// Member variables
private:

	EngineInterface* m_pEngineInterface;		// Association to EngineInterface
	bool m_bActive;								// State: active (true) or terminated
};

#undef BASECLASS
#endif //!ENGINECALLBACKHANDLER_H