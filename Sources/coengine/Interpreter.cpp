/*****************************************************************************
 * $Workfile: Interpreter.cpp $
 * $Revision: 3 $
 * $Modtime: 12/03/99 2:45p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "Interpreter.h"

// Static variables
ComposedInterpreter*	Interpreter::m_pTheComposedInterpreter;
ParameterPart*			Interpreter::m_pTheParameterPart;
MasterSlavePart*		Interpreter::m_pTheMasterSlavePart;
ActionWordPart*			Interpreter::m_pTheActionWordPart;
ActionWord*				Interpreter::m_pTheActionWord;
SlaveList*				Interpreter::m_pTheSlaveList;
