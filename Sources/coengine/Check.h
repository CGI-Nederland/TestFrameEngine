/*****************************************************************************
 * $Workfile: Check.h $
 * $Revision: 2 $
 * $Modtime: 18-10-99 14:56 $
 * $Author: Mn $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CHECK_H
#define CHECK_H

// Includes
#include <string>

// Forward declarations

////////////////////////////////////////////////////////////////////////////////
// class Check

class Check
{
	// Construction and destruction
public:
	Check();					// Constructor

private:
	Check(const Check& src);	// Copy contructor

	// Other constructors
public:
	~Check();					// Destructor

	// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: Compare(const string& strFirst, const string& strSecond)
	//
	// description	: Compares first and second string
	//				  	
	// parameters	: strFirst		const string&
	//				  strSecond		const string&
	//
	// returns		: integer
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Compare(const string& strFirst, const string& strSecond);

	// Implementation
private:

	// Class constants
public:

	// Member variables
private:

};

////////////////////////////////////////////////////////////////////////////////

#endif // !CHECK_H