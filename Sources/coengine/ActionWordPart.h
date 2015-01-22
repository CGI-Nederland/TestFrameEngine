/*****************************************************************************
 * $Workfile: ActionWordPart.h $
 * $Revision: 2 $
 * $Modtime: 9-03-00 14:30 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ACTIONWORDPART_H
#define ACTIONWORDPART_H

#undef BASECLASS
#define BASECLASS Interpreter

#include "Interpreter.h"		// Baseclass definition


////////////////////////////////////////////////////////////////////////////////
// class ActionWordPart

class ActionWordPart : public BASECLASS  
{
	// Construction and destruction
public:
	ActionWordPart();								// Default constructor

	~ActionWordPart();								// Destructor

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: Interpret
	//
	// description	: This function checks if a specified argument value is, when
	//				  trimmed, equal to the name of a valid action word. If so, its
	//				  attributes type and associated function are stored.
	//					
	// parameters	: strActionWordArgument		argument to check for action word
	//
	// returns		: TRUE						valid action word found
	//				  FALSE						valid action word not found
	///////////////////////////////////////////////////////////////////////////////
	bool Interpret(const string& strActionWordArgument);
};

#undef BASECLASS
#endif // !ACTIONWORDPART_H

