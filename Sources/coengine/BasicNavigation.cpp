/*****************************************************************************
 * $Workfile: BasicNavigation.cpp $
 * $Revision: 3 $
 * $Modtime: 8/10/01 12:27p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include "BasicNavigation.h"	// Class definition

//#include <string>
//using namespace std;

#include "Check.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//					================================
					BasicNavigation::BasicNavigation()
//					================================
{
	m_pCheck = new Check();
}

// Destructor
//					=================================
					BasicNavigation::~BasicNavigation()
//					=================================
{
	delete m_pCheck;

	m_pCheck=0;
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						========================
bool  					BasicNavigation::Compare 
//						========================
(
	const string&		strFirst,
	const string&		strSecond
)
{
	return m_pCheck->Compare( strFirst, strSecond ); 
}

///////////////////////////////////////////////////////////////////////////////
