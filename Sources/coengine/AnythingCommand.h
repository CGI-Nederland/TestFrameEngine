/*****************************************************************************
 * $Workfile: AnythingCommand.h $
 * $Revision: 1 $
 * $Modtime: 5/11/00 3:22p $
 * $Author: Aa $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#ifndef ANYTHINGCOMMAND_H
#define ANYTHINGCOMMAND_H

#include "EngineSetting.h"				// EngineSetting definition
#include "ArgumentCommand.h"			// Base class

#undef BASECLASS
#define BASECLASS	ArgumentCommand

////////////////////////////////////////////////////////////////////////////////
// class AnythingCommand
class AnythingCommand : public BASECLASS
{
	// Construction and destruction

public:
	AnythingCommand() {};				// Default constructor

	~AnythingCommand() {};				// Destructor


	// Implementation

	///////////////////////////////////////////////////////////////////////////////
	// function		: Initialize
	//
	// description	: This function initializes the AnythingCommand Object
	//				  by reading the EngineSetting from the ini file.
	//					
	// parameters	: EngineSetting*	pointer to the Settings Object to find the prefix
	//				  
	//
	// returns		: TRUE				initialization successful
	//				  FALSE				initialization failed
	///////////////////////////////////////////////////////////////////////////////
	bool Initialize(EngineSetting* pSetting);

	///////////////////////////////////////////////////////////////////////////////
	// function		: EvaluateCommand
	//
	// description	: This function evaluates the command by filling the
	//			      argument value part of the command string with the Argument string
	//
	// parameters	: none
	//
	// returns		: TRUE				evaluation successful
	//				  FALSE				evaluation failed
	///////////////////////////////////////////////////////////////////////////////
	bool EvaluateCommand();


};

#undef BASECLASS
#endif // ANYTHINGCOMMAND_H
