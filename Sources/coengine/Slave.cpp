/*****************************************************************************
 * $Workfile: Slave.cpp $
 * $Revision: 1 $
 * $Modtime: 12/03/99 12:24p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <string>

using namespace std;

#include "Slave.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//					============
					Slave::Slave()
//					============
{
}

		
// Other constructor
//					============
					Slave::Slave
//					============
(
	const int		nID,
	const string	strName,
	const int		nMode,
	const int		nStatus
)
{
	// Init members
	m_nID = nID;
	m_strName = strName;
	m_nMode = nMode;
	m_nStatus = nStatus;
}


// Destructor
//					=============
					Slave::~Slave()
//					=============
{
}


///////////////////////////////////////////////////////////////////////////////
// Implementation


///////////////////////////////////////////////////////////////////////////////