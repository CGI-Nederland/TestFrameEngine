/*****************************************************************************
 * $Workfile: TcpHandler.h $
 * $Revision: 5 $
 * $Modtime: 4/20/00 5:34a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TCPHANDLER_H
#define TCPHANDLER_H

#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// class TcpHandler

class TcpHandler
{
// Construction and destruction
public:
	TcpHandler() {};					// Constuctor

	// Abstract class
	virtual ~TcpHandler() {};					// Destructor

// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: Message received
	//
	// description	: This function is called when the TcpIpServer has received
	//				  a message.
	//					
	// parameters	: string				the message string
	//				  int					client id
	//
	// returns		: <void>				Nothing, nada, niets
	//				  
	///////////////////////////////////////////////////////////////////////////////
	virtual void MessageReceived(const string& strMessage, const int nID) = 0;

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
	virtual void Disconnect(const int nID) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetInteger
	//
	// Description:	Get the integer on position: nPosition
	//					
	// Parameters:	strArgument		String containing argument
	//				nPosition		Position of int
	//				nInteger		Variable that will receive the integer
	//
	// Returns:		true			When successful
	//				false			Otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool GetInteger(string strArgument, int nPosition, int& nInteger);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetString
	//
	// Description:	Get the string on position: nPosition
	//					
	// Parameters:	strArgument		String containing argument
	//				nPosition		Position of int
	//				strString		Variable that will receive the string
	//
	// Returns:		true			When successful
	//				false			Otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool GetString(string strArgument, int nPosition, string& strString);


// Class constants

// Member variables
private:

};

///////////////////////////////////////////////////////////////////////////////

#endif // !TCPHANDLER_H