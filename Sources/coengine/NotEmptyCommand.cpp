/*****************************************************************************
 * $Workfile: NotEmptyCommand.cpp $
 * $Revision: 1 $
 * $Modtime: 5/11/00 3:29p $
 * $Author: Aa $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "NotEmptyCommand.h"

#include <string>

using namespace std;

#define BASECLASS	ArgumentCommand

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction


// only default construction


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===========================
bool					NotEmptyCommand::Initialize
//						===========================
(
	EngineSetting*		pSetting
)
{
	// get the prefix out of the settings
	m_strPrefix	= pSetting->Get("SYSTEM", "NotEmptyPrefix");

	// check for parentheses and calculate the length
	GeneralInitializing();
	
	m_bHasParameter = false;
	return true;
}

//						================================
bool					NotEmptyCommand::EvaluateCommand()
//						================================
{
	// output string = input string
	m_strArgumentValue = m_strArgument;
	return true;
}

