/*****************************************************************************
 * $Workfile: Check.cpp $
 * $Revision: 2 $
 * $Modtime: 18-10-99 14:57 $
 * $Author: Mn $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <string>

using namespace std;

#include "Check.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//					============
					Check::Check()
//					============
{
}

// Destructor
//					=============
					Check::~Check()
//					=============
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//					==============
bool  				Check::Compare 
//					==============
(
	const string& strFirst,
	const string& strSecond
)
{
	bool bResult = false;

	if (strFirst == strSecond)
	{ bResult = true; }

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation


///////////////////////////////////////////////////////////////////////////////