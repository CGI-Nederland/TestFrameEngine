/*****************************************************************************
 * $Workfile: TcpInterface.cpp $
 * $Revision: 8 $
 * $Modtime: 10/23/01 2:44p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <string>
#include <sstream>
#include <queue>

using namespace std;

#include "EngineUtil.h"
#include "IOInterface.h"
#include "TcpInterface.h"					// Class definition
#include "TcpIpConnection.h"
#include "TcpInterfaceCallBackHandler.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//					==========================
					TcpInterface::TcpInterface
//					==========================
(
	const string&			strHost,
	const unsigned int		nPort,
	const string&			strSlaveID
)
{
	// Store the parameters
	m_nPort			= nPort;
	m_strHost		= strHost;
	m_strSlaveID	= strSlaveID;

	// Create callback interface
	m_pCallbackHandler = new TcpInterfaceCallBackHandler(this);

	// Lines cannot be preread
	SetCountable(false);
}


// Copy constructor
					
// Other constructors

// Destructor
//					===========================
					TcpInterface::~TcpInterface()
//					===========================
{
	delete m_pCallbackHandler;
	m_pCallbackHandler=0;
}
///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//					==================
void				TcpInterface::Open
//					==================
(
	int nMode
)
{
	m_TcpIpConnection.SetCallbackHandler(m_pCallbackHandler);
	Open(m_strConnection, nMode);
}

//					==================
void				TcpInterface::Open
//					==================
(
	const string& strConnection,			// NOTE : not used !
	int nMode
)
{
	if (m_nOpenMode != nMode)
	{ m_nOpenMode = nMode; }
	
	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:
		{
			if ((m_nPort != 0) &&
			    (!m_strHost.empty()) &&
			    (!m_strSlaveID.empty()))
			{
				// Set the information
				m_TcpIpConnection.SetHost(m_strHost);
				m_TcpIpConnection.SetPortNumber(m_nPort);

				// Open the connection
				m_TcpIpConnection.Open();

				// Start the client
				m_TcpIpConnection.Start();

				// Register slave
				m_TcpIpConnection.SendMessage("Register:" + m_strSlaveID);
				
			}
			break;
		}
	case IOInterface::IOWRITE:
		{
			
			break;
		}
	case IOInterface::IOAPPEND:
		{
			
			break;
		}
	default:
		{
			// error, this should not happen.
			break;
		}
	}

	// In case of errors write debug info to error.log file
	if (!IsOpen())
	{
		// formatting of the error statement.
		ostringstream ossError;
		// type of error.
		ossError << "tcp connection: " << m_strConnection << " could not be opened!" << endl;
		// 	state of the different stream flags	
		ossError << "Flagstates: " << endl;
		ossError << "goodbit: " << Good() << "\t";
		ossError << "badbit: " << Bad() << "\t";
		ossError << "eofbit: " << Eof() << "\t";
		ossError << "failbit: " << Fail();

		// Write the error statement to the error.log file
		WriteIOError(string("TcpInterface"), ossError.str(), string());

	}

}

//					====================
bool				TcpInterface::IsOpen()
//					====================
{
	bool bResult = true;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:
		{

			break;
		}
	case IOInterface::IOWRITE:
		{

			break;
		}
	case IOInterface::IOAPPEND:
		{

			break;
		}
	default:
		{
			// error, this should not happen.
			break;
		}
	}

	return bResult;
}

//					===================
void				TcpInterface::Close()
//					===================
{
	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:
	case IOInterface::IOWRITE:
	case IOInterface::IOAPPEND:
		{
			m_TcpIpConnection.Stop();
			break;
		}
	default:
		{
			// error, this should not happen.
			m_TcpIpConnection.Stop();
			break;
		}
	}
}

//					==================
bool				TcpInterface::Read
//					==================
(
	string& strLine
)
{
	bool bResult = false;

	if(m_nOpenMode == IOInterface::IOREAD)
	{
		// Wait for a line to become available
		Available();

		// Read it
		strLine = PopLine();

		// Check for end of transmission (EOT, 0x004)
		if (strLine != "\x004")
		{
			bResult = true;
		}
		else
		{
			// Call the close method
			Close();
		}
	}

/*
	// In case of errors write debug info to error.log file
	if (Bad())
	{
		// formatting of the error statement.
		ostringstream ossError;
		// type of error.
		ossError << "tcp connection: " << m_strConnection << " could not be read!" << endl;
		// state of the different stream flags
		ossError << "Flagstates: " << endl;
		ossError << "goodbit: " << Good() << "\t";
		ossError << "badbit: " << Bad() << "\t";
		ossError << "eofbit: " << Eof() << "\t";
		ossError << "failbit: " << Fail();

		// Write the error statement to the error.log file
		WriteIOError(string("TcpInterface"), ossError.str(), string());
	}
*/

	return bResult;
}

//					===================
bool				TcpInterface::Write
//					===================
(
	const string&	strLine				//NOT USED!!!
)
{
	bool bResult = false;

	if ((m_nOpenMode == IOInterface::IOWRITE) || (m_nOpenMode == IOInterface::IOAPPEND))
	{

	}

		// In case of errors write debug info to error.log file
	if (!bResult)
	{
		// formatting of the error statement.
		ostringstream ossError;
		// type of error.
		ossError << "tcp connection: " << m_strConnection << " could not be written!" << endl;
		// state of the different stream flags
		ossError << "Flagstates: " << endl;
		ossError << "goodbit: " << Good() << "\t";
		ossError << "badbit: " << Bad() << "\t";
		ossError << "eofbit: " << Eof() << "\t";
		ossError << "failbit: " << Fail();

		// Write the error statement to the error.log file
		WriteIOError(string("FileInterface"), ossError.str(), string());	
	}

	return bResult;
}

//					=================
bool				TcpInterface::Bad()	const
//					=================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:			// openmode READ
		{

			break;
		}
	case IOInterface::IOWRITE:			// openmode WRITE
		{

			break;
		}
	case IOInterface::IOAPPEND:			// openmode APPEND
		{

			break;
		}
	default:
		{
			// error, this should not happen.
			break;
		}
	}

	return bResult;		// returns badbit of appropriate filestream
}

//					=================
bool				TcpInterface::Eof()	const
//					=================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:			// openmode READ
		{

			break;
		}
	case IOInterface::IOWRITE:			// openmode WRITE
		{

			break;
		}
	case IOInterface::IOAPPEND:			// openmode APPEND
		{

			break;
		}
	default:							// openmode READ is default
		{
			// error, this should not happen.
			break;
		}
	}

	return bResult;		// returns eofbit of appropriate filestream
}

//					==================
bool				TcpInterface::Fail()	const
//					==================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:			// openmode READ
		{

			break;
		}
	case IOInterface::IOWRITE:			// openmode WRITE
		{

			break;
		}
	case IOInterface::IOAPPEND:			// openmode APPEND
		{

			break;
		}
	default:							// openmode READ is default
		{
			// error, this should not happen
			break;
		}
	}

	return bResult;		// returns failbit of appropriate filestream
}

//					==================
bool				TcpInterface::Good()	const
//					==================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:			// openmode READ
		{

			break;
		}
	case IOInterface::IOWRITE:			// openmode WRITE
		{

			break;
		}
	case IOInterface::IOAPPEND:			// openmode APPEND
		{

			break;
		}
	default:							// openmode READ is default
		{
			// error, this should not happen.
			break;
		}
	}

	return bResult;		// returns goodbit of appropriate filestream
}


//						===========================
bool					TcpInterface::SetPortNumber
//						===========================
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
		m_nPort= nPortNumber;
	}

	return bResult;
}


//						=====================
bool					TcpInterface::SetHost
//						=====================
(
	const string&		strHostName
)
{
	bool bResult = false;

	// We do not accept an empty host name
	if (!strHostName.empty())
	{ 
		bResult = true;
		m_strHost = strHostName;
	}

	return bResult;
}

//						========================
bool					TcpInterface::SetSlaveID
//						========================
(
	const string&		strSlaveID
)
{
	bool bResult = false;

	// We do not accept an empty host name
	if (!strSlaveID.empty())
	{ 
		bResult = true;
		m_strSlaveID = strSlaveID;
	}

	return bResult;
}

//						=====================
string					TcpInterface::PopLine()
//						=====================
{
	string strResult;

	// Wait until line comes available
	Available();

	strResult = m_qstrBuffer.front();

	m_qstrBuffer.pop();

	return strResult;
}

//						======================
void					TcpInterface::PushLine
//						======================
(
	const string strLine
)
{
	// Push line into the queue
	m_qstrBuffer.push(strLine);
}

#pragma optimize( "", off )
//						=======================
void					TcpInterface::Available()
//						=======================
{
    // Blok until there is somthing in the queue
	while ( m_qstrBuffer.size() == 0 ) 
	{ EngineSleep(40); }
}
#pragma optimize( "", on )



///////////////////////////////////////////////////////////////////////////////
// Implementation


///////////////////////////////////////////////////////////////////////////////
