/*****************************************************************************
 * $Workfile: EmptyCommand.h $
 * $Revision: 1 $
 * $Modtime: 5/11/00 3:20p $
 * $Author: Aa $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#ifndef EMPTYCOMMAND_H
#define EMPTYCOMMAND_H

#include "EngineSetting.h"			// EngineSetting definition
#include "ArgumentCommand.h"		// Base class

#undef BASECLASS
#define BASECLASS	ArgumentCommand

////////////////////////////////////////////////////////////////////////////////
// class EmptyCommand
class EmptyCommand : public BASECLASS
{
	// Construction and destruction

public:
	EmptyCommand() {};						// Default constructor

	virtual ~EmptyCommand() {};				// Destructor


	// Implementation

	///////////////////////////////////////////////////////////////////////////////
	// function		: Initialize
	//
	// description	: This function initializes the AnythingCommand Object
	//					by reading the EngineSetting from the ini file.
	//					
	// parameters	: EngineSetting*	pointer to the Settings Object to find the prefix
	//				  
	//
	// returns		: TRUE			initialization successful
	//				  FALSE			initialization failed
	///////////////////////////////////////////////////////////////////////////////
	bool Initialize(EngineSetting* pSetting);

	///////////////////////////////////////////////////////////////////////////////
	// function		: EvaluateCommand
	//
	// description	: This function evaluates the command by filling the
	//					argument value part of the command string with the Argument string
	//
	// parameters	: none
	//
	// returns		: TRUE			evaluation successful
	//				  FALSE			evaluation failed
	///////////////////////////////////////////////////////////////////////////////
	bool EvaluateCommand();

};

#undef BASECLASS
#endif // EMPTYCOMMAND_H
