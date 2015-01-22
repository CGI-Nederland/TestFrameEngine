/*****************************************************************************
 * $Workfile: SpacesCommand.cpp $
 * $Revision: 2 $
 * $Modtime: 12/14/00 3:37p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "SpacesCommand.h"

#include <sstream>
#include <string>

using namespace std;

#define BASECLASS	ArgumentCommand

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						============================
						SpacesCommand::SpacesCommand
//						============================
(
	Parser*				pTheParser
)
{
	m_pTheParser = pTheParser;
}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=========================
bool					SpacesCommand::Initialize
//						=========================
(
	EngineSetting*		pSetting
)
{
	// get the prefix out of the settings
	m_strPrefix	= pSetting->Get("SYSTEM", "SpacesPrefix");

	// check for parentheses and calculate the length
	GeneralInitializing();
	
	m_bHasParameter = true;
	return true;
}

//						==============================
bool					SpacesCommand::EvaluateCommand()
//						==============================
{
	/*bool bResult =  false;

	if (m_bHasParameter)
	{
		//	interpret parameter: remove parentheses etc. 
		InterpretParameter();
	}

	if (m_pTheParser->Parse(m_strParameter)) 
	{
		// parameter parsed succesfully, replace parameter by parse result
		m_strParameter = m_pTheParser->GetResult();
	}
	// Convert the command parameter to integer
	istringstream	issValue(m_strParameter);		// Create stream
	int				nValue;							// Create test int

	// Try to convert variable to int
	issValue >> nValue;

	// Check if conversion failed
	if (!issValue.fail())
	{
		string strSpace;

		// Create space string
		for (int ncSpace = 0; ncSpace < nValue; ncSpace++)
		{
			strSpace.append(" ");
		}
		
		// output the created parameter
		m_strArgumentValue = m_strArgument; // strSpace;
		bResult = true;
	}
	else
	{
		// Ooops something is wrong, add as literal
		m_strArgumentValue = m_strArgument;
	}
	return bResult;*/
	m_strArgumentValue = m_strArgument;
	return true;
}

//						=================================
void					SpacesCommand::InterpretParameter()
//						=================================
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

//						=================================
string					SpacesCommand::GetParameterString()
//						=================================
{
	return m_strParameter;
}

