/*****************************************************************************
 * $Workfile: TcpInterface.h $
 * $Revision: 3 $
 * $Modtime: 4/20/00 10:02p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TCPINTERFACE_H
#define TCPINTERFACE_H



// Includes
#include <string>
#include <queue>

using namespace std;

#include "IOInterface.h"
#include "TcpIpConnection.h"

#undef BASECLASS
#define BASECLASS IOInterface

// Forward declaration
class TcpInterfaceCallBackHandler;

////////////////////////////////////////////////////////////////////////////////
// class FileInterface

class TcpInterface	: public BASECLASS
{

// Construction and destruction
public:
	TcpInterface() {};				// Default constructor

	// Other constructor
	TcpInterface(const string& strHost, const unsigned int nPort, const string& strSlaveID);

	// Other constructors
	explicit TcpInterface(const string& strConnection) : m_strConnection(strConnection){};

	TcpInterface& operator=(TcpInterface&);

	virtual ~TcpInterface();		// Destructor
// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: Open
	// description	: Opens a tcp connection.
	//				  
	// parameters	: nMode		openmode, default is READ
	//
	// returns		: true		operation was succesfull
	//				  false		operation failed
	///////////////////////////////////////////////////////////////////////////////
	void Open(int nMode = IOInterface::IOREAD);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Open
	// description	: Opens a tcp connection.
	//				  
	// parameters	: strConnection		tcp connect string
	//				  nMode				openmode, default is READ
	//
	// returns		: true			operation was succesfull
	//				  false			operation failed
	///////////////////////////////////////////////////////////////////////////////
	void Open(const string& strConnection, int nMode = IOInterface::IOREAD);

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsOpen
	// description	: This function returns true if the tcp connection is open.
	//
	// parameters	: None.
	//
	// returns		: true		tcp connection is open
	//				  false		tcp connection is not open
	///////////////////////////////////////////////////////////////////////////////
	bool IsOpen();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Close
	// description	: Closes a tcp connection
	//				  
	// parameters	: None
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void Close();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Read
	// description	: 
	//
	// parameters	: strLine	parameter containing the line read from the stream
	//
	// returns		: true		
	//				  false		
	///////////////////////////////////////////////////////////////////////////////
	bool Read(string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Write
	// description	: 
	//				  
	// parameters	: strLine	
	//
	// returns		: true		
	//				  false		
	///////////////////////////////////////////////////////////////////////////////
	bool Write(const string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Bad
	// description	: 
	//				  
	// parameters	: None.
	//
	// returns		: true		
	//				  false
	///////////////////////////////////////////////////////////////////////////////
	bool Bad() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Eof
	// description	: 
	//				  
	// parameters	: None.
	//
	// returns		: true
	//				  false
	///////////////////////////////////////////////////////////////////////////////
	bool Eof() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Fail
	// description	: 
	//				  
	// parameters	: None.
	//
	// returns		: true
	//				  false
	///////////////////////////////////////////////////////////////////////////////
	bool Fail() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Good
	// description	: 
	//				  
	// parameters	: None.
	//
	// returns		: true
	//				  false
	///////////////////////////////////////////////////////////////////////////////
	bool Good() const;

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
	bool SetPortNumber(unsigned int nPortNumber);

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
	// Function:	SetSlaveID
	//
	// Description:	Sets the slave ID
	//					
	// Parameters:	strSlaveName		Name of the slave
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool SetSlaveID(const string& strSlaveID);


	///////////////////////////////////////////////////////////////////////////////
	// Function:	PopLine()
	//
	// Description:	Gets a line from the queue
	//					
	// Parameters:	None;
	//
	// Returns:		string				Requested line
	//				  
	///////////////////////////////////////////////////////////////////////////////
	string PopLine();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	PushLine()
	//
	// Description:	Pushes a line in the queue
	//					
	// Parameters:	string				the line
	//
	// Returns:		None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void PushLine(const string strLine);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Available()
	//
	// Description:	Wait until a line is available
	//					
	// Parameters:	None.
	//
	// Returns:		None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Available();


	// Implementation
protected:
	// Class constants

	// Member variables
private:
	string							m_strConnection;
	int								m_nOpenMode;
	TcpIpConnection					m_TcpIpConnection;		// input file stream
	unsigned int					m_nPort;				// socket port number
	string							m_strHost;				// host name
	string							m_strSlaveID;			// slave ID
	TcpInterfaceCallBackHandler*	m_pCallbackHandler;		// callback handler
	queue<string>					m_qstrBuffer;			// I/O Buffer
};

////////////////////////////////////////////////////////////////////////////////

#undef BASECLASS
#endif // !TCPINTERFACE_H
