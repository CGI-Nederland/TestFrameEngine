/*****************************************************************************
 * $Workfile: MasterSlavePart.h $
 * $Revision: 1 $
 * $Modtime: 11-10-99 16:33 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef MASTERSLAVEPART_H
#define MASTERSLAVEPART_H

#undef BASECLASS
#define BASECLASS Interpreter

// Forward declarations


////////////////////////////////////////////////////////////////////////////////
// class Interpreter
class MasterSlavePart : public BASECLASS 
{
	// Construction and destruction
public:
	MasterSlavePart();								// Constuctor
private:
	MasterSlavePart(const MasterSlavePart& right);	// Copy constructor
public:
	~MasterSlavePart();								// Destructor

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////
	// function		: Interpret
	//
	// description	: Interprets the slavename
	//					
	// parameters	: string						slavename
	//
	// returns		: true							slavename valid
	//				  false							slavename invalid
	//				  
	///////////////////////////////////////////////////////////////////////////////
    bool Interpret(string& strTestLine) const;
};

#undef BASECLASS
#endif // !MASTERSLAVEPART_H