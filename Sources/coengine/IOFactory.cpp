/*****************************************************************************
 * $Workfile: IOFactory.cpp $
 * $Revision: 6 $
 * $Modtime: 7/14/00 4:35p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <sstream>

#include "IOFactory.h"		// Class definition
#include "FileInterface.h"
#include "TcpInterface.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor

// Copy constructor
					
// Other constructors

// Destructor

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//					============================
IOInterface*		IOFactory::CreateIOInterface
//					============================
(
	const string&	strIOSource
)
{
	string	strProtocol;		// IO protocol string
	string	strSource;			// IO source string

	// Special masterslave parameters
	string	strHost;			// IO host
	string	strPort;			// IO port number
	string	strParameter;		// IO parameters

	int		nProtocol;
	int		nPosition;

	// Parse the io source URL
	if ((nPosition = static_cast<int>(strIOSource.find_first_of(":"))) != static_cast<int>(string::npos))
	{
		// Cut the protocol string
		strProtocol = strIOSource.substr(0, nPosition);
		
		// find the corresponding protocol, default to file
		if (strProtocol == "tmsp") 
		{
			// TestFrame masterslave protocol
			nProtocol = IOFactory::IO_TMSP;

			int nHostPortSeparator;
			int nParameterSeparator;
			int nBeginParameter;

			// find host-port separator
			nHostPortSeparator	= static_cast<int>(strIOSource.find_first_of(":", nPosition+3));
			nParameterSeparator = static_cast<int>(strIOSource.find_first_of("?"));
			nBeginParameter		= static_cast<int>(strIOSource.find_first_of("="));

			// Check if separators are valid
			if ((nHostPortSeparator		!= static_cast<int>(string::npos)) &&
				(nParameterSeparator	!= static_cast<int>(string::npos)) &&
				(nBeginParameter		!= static_cast<int>(string::npos)))
			{
				strHost		 = strIOSource.substr(nPosition+3, (nHostPortSeparator - (nPosition +3)));
				strPort		 = strIOSource.substr(nHostPortSeparator+1, (nParameterSeparator - (nHostPortSeparator+1)));
				strParameter = strIOSource.substr(nBeginParameter+1);
			}
			else
			{
				// Error use default
				strProtocol = "Default";
			}
	
		}
		else if (strProtocol == "file")
		{
			// FIle protocol
			nProtocol = IOFactory::IO_FILE;

			// Cut the corresponding source (://)= +3
			strSource = strIOSource.substr(nPosition+3);

			// No parameters
			strParameter = string("");
		}
		else
		{
			// Default to FILE
			nProtocol = IOFactory::IO_FILE;
			strSource = strIOSource;
			strParameter = string("");
		}		
	}
	else
	{
		// Default to FILE
		nProtocol = IOFactory::IO_FILE;
		strSource = strIOSource;
		strParameter = string("");
	}

	IOInterface*	pIOInterface;		// pointer the the io interface object.

	switch (nProtocol)
	{
		case IO_FILE:
		{
			// Create file interface
			pIOInterface = (IOInterface*) new FileInterface(strSource);
			break;
		}

		case IO_TMSP:
		{
			// Convert port number to int
			unsigned int unPort;
			istringstream	issPort(strPort);
			issPort >> unPort;

			// Create tmsp client
			pIOInterface = (IOInterface*) new TcpInterface(strHost, unPort, strParameter);
			break;
		}
		default:
		{
			// Internal error, return file object anyway the error wil show up in error.log
			// Create file interface
			pIOInterface = (IOInterface*) new FileInterface(strSource);
			break;
		}
	}

	return pIOInterface;
}

//					=============================
void				IOFactory::DestroyIOInterface
//					=============================
(
	IOInterface*	pIOInterface
)
{
	if (pIOInterface != 0)
	{
		delete pIOInterface;
		pIOInterface = 0;
	}
}



//					===============
bool				IOFactory::Copy
//					===============
(
	const string&	strSource,
	const string&	strDestination
)	const
{
	bool bResult = false;

	bResult = FileInterface::Copy(strSource, strDestination);

	return bResult;
}

//					================
bool				IOFactory::Exist
//					================
(
	const string&	strSource
)	const
{
	bool bResult = false;

	bResult = FileInterface::Exist(strSource); 

	return bResult;
}

//					=================
bool				IOFactory::Rename
//					=================
(
	const string&	strSource,
	const string&	strDestination
)	const
{
	bool bResult = false;

	bResult = FileInterface::Rename(strSource, strDestination); 

	return bResult;
}

//					=================
bool				IOFactory::Remove
//					=================
(
	const string&	strSource
)	const
{
	bool bResult = false;

	bResult = FileInterface::Remove(strSource); 

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation


///////////////////////////////////////////////////////////////////////////////
