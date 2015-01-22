/*****************************************************************************
 * $Workfile: AnythingCommand.cpp $
 * $Revision: 1 $
 * $Modtime: 5/11/00 3:23p $
 * $Author: Aa $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "AnythingCommand.h"

#include <string>

using namespace std;

#define BASECLASS	ArgumentCommand

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// only default construction


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===========================
bool					AnythingCommand::Initialize
//						===========================
(
	EngineSetting*		pSetting
)
{
	// get the prefix out of the settings
	if(pSetting)
	{
		m_strPrefix	= pSetting->Get("SYSTEM", "AnythingPrefix");
	}

	// check for parentheses and calculate the length
	GeneralInitializing();
	
	m_bHasParameter = false;
	return true;
}

//						================================
bool					AnythingCommand::EvaluateCommand()
//						================================
{
	// output string = input string
	m_strArgumentValue = m_strArgument;
	return true;
}

