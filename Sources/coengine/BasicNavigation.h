/*****************************************************************************
 * $Workfile: BasicNavigation.h $
 * $Revision: 3 $
 * $Modtime: 8/10/01 12:27p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef BASICNAVIGATION_H
#define BASICNAVIGATION_H

// Includes
#include <string>

using namespace std;

// Forward declarations
class Check;

////////////////////////////////////////////////////////////////////////////////
// class BasicNavigation

class BasicNavigation
{
	// Construction and destruction
public:
	BasicNavigation();								// Constructor

private:
	BasicNavigation(const BasicNavigation& src);	// Copy contructor
	BasicNavigation& operator=(BasicNavigation&);

public:
	~BasicNavigation();								// Destructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Compare()
	//
	// description	:	This function compares two string values, and returns true
	//					if they are considered to be equal.
	//				  	
	// parameters	:	strFirst		first string value
	//					strSecond		second string value
	//
	// returns		:	true	the strings are equal
	//					false	the strings are different
	///////////////////////////////////////////////////////////////////////////////
	bool Compare( const string& strFirst, const string& strSecond );

// Member variables
private:
	Check* m_pCheck;	// pointer to Check object
};

////////////////////////////////////////////////////////////////////////////////

#endif // !BASICNAVIGATION_H