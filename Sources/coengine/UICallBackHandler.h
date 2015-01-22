/*****************************************************************************
 * $Workfile: UICallBackHandler.h $
 * $Revision: 3 $
 * $Modtime: 12/17/99 1:19p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef UICALLBACKHANDLER_H
#define UICALLBACKHANDLER_H

#undef BASECLASS
#define BASECLASS TcpHandler

#include "TcpHandler.h"

// Forward declarations
class GuiInterface;
class UIHandler;

class UICallBackHandler : public TcpHandler
{
	// Construction and destruction
private:
	UICallBackHandler();							// Default constructor
	
	UICallBackHandler(const UICallBackHandler& right);	// Copy constructor

	// Other constructors
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		: UICallBackHandler
	//
	// description	: Constructs a user interface callback handler
	//					
	// parameters	: GuiInterface*				a pointer to the GUI interface
	//				  UIHandler*				a pointer to the UIHandler
	//
	// returns		: None (constructor).
	//				  
	///////////////////////////////////////////////////////////////////////////////
	UICallBackHandler(GuiInterface* pGuiInterface, UIHandler* pUIHandler);

	virtual ~UICallBackHandler();					// Destructor

	///////////////////////////////////////////////////////////////////////////////
	// function		: MessageReceived
	//
	// description	: request for processing by UIServer.
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

	GuiInterface*				m_pGuiInterface;		// Association to GuiInterface
	UIHandler*					m_pUIHandler;			// Association to UIHandler

};

#undef BASECLASS
#endif //!UICALLBACKHANDLER_H