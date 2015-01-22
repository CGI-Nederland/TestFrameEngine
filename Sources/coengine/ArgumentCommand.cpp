/*****************************************************************************
 * $Workfile: ArgumentCommand.cpp $
 * $Revision: 2 $
 * $Modtime: 12/14/00 3:03p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

//#include <string>
//using namespace std;

#include "ArgumentCommand.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
// No construction for base class

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						==========================
bool					ArgumentCommand::Interpret
//						==========================
(
	const string&		strArgument			// argument to scan for command
)
{
	bool bResult = false;

	// First check if the argument is a command of the specified type.
	if (IsCommand(strArgument))
	{
		m_strArgument = strArgument;

		// Specific evaluation for each command type; to be overloaded.
		bResult = EvaluateCommand();
	}
	return bResult;
}


//						==========================
string					ArgumentCommand::GetPrefix()
//						==========================
{
	return m_strPrefix;
}


//						================================
int						ArgumentCommand::GetPrefixLength()
//						================================
{
	return m_nPrefixLength;
}

//						==========================
bool					ArgumentCommand::IsCommand
//						==========================
(
	const string&		strArgument
)
{
	// Check if strArgument is a command of the specified command type by checking the 
	// prefix. Here we do not set the m_strArgument because we do not interpret the command.
	m_bIsCommand = false;

	// Check if the first character(s) of the argument are equal to the command prefix.

	string	strBegin = strArgument.substr(0, m_nPrefixLength);

	if (strBegin == m_strPrefix)
	{
		m_bIsCommand = true;
	}
	return m_bIsCommand;
}


//						===============================
bool					ArgumentCommand::HasParentheses
//						===============================
(
	const string&		strText			// string to check for parentheses
)
{
	bool bResult = false;				// result of HasParentheses

	// check if opening and closing parentheses both exist
	if (((strText.find_first_of("({[<")) != string::npos) &&
	 	((strText.find_last_of(")}]>")) != string::npos))
	{
		bResult = true;
	}

	return bResult;
}


//						==================================
string					ArgumentCommand::RemoveParentheses
//						==================================
(
	const string&		strText			// string to remove parentheses from
)
{
	// copy value of strText into string which can be modified
	string strResult = strText;

	// check if both parentheses exist
	if (HasParentheses(strResult))
	{
		// remove outer opening parenthesis
		strResult.erase(strResult.find_first_of("({[<"), 1);
		// remove outer closing parenthesis
		strResult.erase(strResult.find_last_of(")}]>"), 1);
	}

	return strResult;
}


//						===============================================
string					ArgumentCommand::GetParameterBetweenParentheses
//						===============================================
(
	const string&		strText			// string to get parameter from
)
{
	// Set the resulting string default to an empty string.
	string strResult = "";

	// Check if the command has parentheses.
	if ( HasParentheses( strText ) )
	{
		// Determine the positions of the outer opening and closing parentheses
		// in the given text.
		// As opening parentheses are regarded: '(', '{', '[' and '<';
		// as closing parentheses are regarded: ')', '}', ']' and '>'.
		int nPosOpen = strText.find_first_of( "({[<" );
		int nPosClose = strText.find_last_of( ")}]>" );

		// Check if the parentheses  have  been really found.
		if ( nPosOpen != string::npos && nPosClose != string::npos )
		{
			// Take as resulting string the characters between the found opening
			// and closing parentheses.
			strResult = strText.substr( nPosOpen + 1, nPosClose - nPosOpen - 1 );
		}
	}

	return strResult;
}


//						====================================
void					ArgumentCommand::GeneralInitializing()
//						====================================
{
	if (HasParentheses(m_strPrefix))
	{
		m_bHasParentheses = true;
		m_strPrefix = RemoveParentheses(m_strPrefix);
	}
	else
	{
		m_bHasParentheses = false;
	}

	m_nPrefixLength = m_strPrefix.length();
}

//						=================================
string					ArgumentCommand::GetArgumentValue()
//						=================================
{
	return m_strArgumentValue;
}