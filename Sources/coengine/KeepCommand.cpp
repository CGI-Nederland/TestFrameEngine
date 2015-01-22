/*****************************************************************************
 * $Workfile: KeepCommand.cpp $
 * $Revision: 3 $
 * $Modtime: 1/30/01 3:02p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "KeepCommand.h"

#include <string>

#include "Parser.h"
#include "StrUtil.h"	// Needed for trimming the keep parameter

using namespace std;

#define BASECLASS	ArgumentCommand

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

KeepCommand::KeepCommand( Parser* pTheParser )
{
	m_pTheParser = pTheParser;
}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=======================
bool					KeepCommand::Initialize
//						=======================
(
	EngineSetting*		pSetting
)
{
	// get the prefix out of the settings
	m_strPrefix	= pSetting->Get("SYSTEM", "KeepPrefix");

	// check for parentheses and calculate the length
	GeneralInitializing();
	
	m_bHasParameter = true;
	return true;
}

//						============================
bool					KeepCommand::EvaluateCommand()
//						============================
{
	bool bResult = false;
	
	if (m_bHasParameter)
	{
		//	interpret parameter: remove parentheses etc. 
		InterpretParameter();
	}

	// Let the Parser determine if the found parameter is a valid 
	// variable name
	if ( m_pTheParser->ParseVariable( m_strParameter ) )
	{
		bResult = true;
	}
	
	// output string = input string
	m_strArgumentValue = m_strArgument;
	
	return bResult;
}

//						===============================
void					KeepCommand::InterpretParameter()
//						===============================
{
	// Take as parameter of the keep command the string behind
	// the prefix.
	m_strParameter = m_strArgument.substr( m_nPrefixLength );

	// Check for parentheses in the newly found parameter.
	if ( m_bHasParentheses )
	{
		// Change the parameter to the string between the parentheses.
		m_strParameter = GetParameterBetweenParentheses( m_strParameter );
	}

	// Trim leading and trailing spaces from the parameter.
	m_strParameter = trim( m_strParameter );
}

//						===============================
string					KeepCommand::GetParameterString()
//						===============================
{
	return m_strParameter;
}

