/*****************************************************************************
 * $Workfile: SnapCommand.cpp $
 * $Revision: 2 $
 * $Modtime: 12/14/00 3:37p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 - 2013 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "SnapCommand.h"

#include <string>

using namespace std;

#define BASECLASS	ArgumentCommand

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// only default construction

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=======================
bool					SnapCommand::Initialize
//						=======================
(
	EngineSetting*		pSetting
)
{
	// get the prefix out of the settings
	m_strPrefix	= pSetting->Get("SYSTEM", "SnapPrefix");

	// check for parentheses and calculate the length
	GeneralInitializing();
	
	m_bHasParameter = true;
	return true;
}

//						============================
bool					SnapCommand::EvaluateCommand()
//						============================
{
	if (m_bHasParameter)
	{
		//	interpret parameter: remove parentheses etc. 
		InterpretParameter();
	}

	// output string = input string
	m_strArgumentValue = m_strArgument;
	return true;
}

//						===============================
void					SnapCommand::InterpretParameter()
//						===============================
{
	// get the characters behind the prefix and
	// store parameter of the command in m_strParameter
	m_strParameter = m_strArgument.substr(m_nPrefixLength);

	// check for parentheses
	if (m_bHasParentheses)
	{
		// Change the parameter to the string between parentheses.
		m_strParameter = GetParameterBetweenParentheses(m_strParameter);
	}
}

//						===============================
string					SnapCommand::GetParameterString()
//						===============================
{
	return m_strParameter;
}