/*****************************************************************************
 * $Workfile: ExpressionCommand.cpp $
 * $Revision: 2 $
 * $Modtime: 12/14/00 3:35p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "ExpressionCommand.h"

#include <string>

using namespace std;

#define BASECLASS	ArgumentCommand


///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						====================================
						ExpressionCommand::ExpressionCommand
//						====================================
(
	Parser*				pTheParser
)
{
	m_pTheParser = pTheParser;
}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=============================
bool					ExpressionCommand::Initialize
//						=============================
(
	EngineSetting* pSetting
)
{
	// get the prefix out of the settings
	m_strPrefix	= pSetting->Get("SYSTEM", "ExpressionPrefix");

	// check for parentheses and calculate the length
	GeneralInitializing();
	
	m_bHasParameter = true;
	return true;
}

//						==================================
bool					ExpressionCommand::EvaluateCommand()
//						==================================
{
	bool bResult = false;

	if (m_bHasParameter)
	{
		//	interpret parameter: remove parentheses etc. 
		InterpretParameter();
	}
	
	// output string = result string of expresion 
	// Parse the argument, remove & first
	if (m_pTheParser->Parse(m_strParameter))
	{
		m_strArgumentValue = m_pTheParser->GetResult();
		bResult =true;
	}
	else
	{
		// Something is wrong, an error has occured
		// Insert the unevaluated parameter in parameterlist
		m_strArgumentValue = m_strArgument;
	}
	return bResult;
}

//						=====================================
void					ExpressionCommand::InterpretParameter()
//						=====================================
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

//						=====================================
string					ExpressionCommand::GetParameterString()
//						=====================================
{
	return m_strParameter;
}

