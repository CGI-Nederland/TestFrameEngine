/*****************************************************************************
 * $Workfile: SlaveCallBackHandler.h $
 * $Revision: 2 $
 * $Modtime: 12/17/99 11:54a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef SLAVECALLBACKHANDLER_H
#define SLAVECALLBACKHANDLER_H

#undef BASECLASS
#define BASECLASS TcpHandler

#include "TcpHandler.h"

// Forward declarations
class SlaveList;

class SlaveCallBackHandler : public TcpHandler
{
	// Construction and destruction
private:
	SlaveCallBackHandler();							// Default constructor
	
	SlaveCallBackHandler(const SlaveCallBackHandler& right);	// Copy constructor

	// Other constructors
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		: SlaveCallBackHandler
	//
	// description	: Constructs a user interface callback handler
	//					
	// parameters	: GuiInterface*				a pointer to the GUI interface
	//
	// returns		: None (constructor).
	//				  
	///////////////////////////////////////////////////////////////////////////////
	explicit SlaveCallBackHandler(SlaveList* SlaveList);

	virtual ~SlaveCallBackHandler();					// Destructor

	///////////////////////////////////////////////////////////////////////////////
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

	SlaveList*				m_pSlaveList;		// Association to slavelist

};

#undef BASECLASS
#endif //!SLAVECALLBACKHANDLER_H