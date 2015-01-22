/*****************************************************************************
 * $Workfile: EmptyCommand.cpp $
 * $Revision: 1 $
 * $Modtime: 5/11/00 3:20p $
 * $Author: Aa $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "EmptyCommand.h"

#include <string>

using namespace std;


#include "ArgumentCommand.h"		// Base Class

#define BASECLASS	ArgumentCommand

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// only default construction


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						========================
bool					EmptyCommand::Initialize
//						========================
(
	EngineSetting*		pSetting
)
{
	// get the prefix out of the settings
	m_strPrefix	= pSetting->Get("SYSTEM", "EmptyPrefix");

	// check for parentheses and calculate the length
	GeneralInitializing();
	
	m_bHasParameter = false;
	return true;
}

//						=============================
bool					EmptyCommand::EvaluateCommand()
//						=============================
{
	// output string = empty string
	//m_strArgumentValue = "";
	m_strArgumentValue = m_strArgument; // leave command untouched
	return true;
}

