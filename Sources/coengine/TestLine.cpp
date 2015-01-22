/*****************************************************************************
 * $Workfile: TestLine.cpp $
 * $Revision: 2 $
 * $Modtime: 24-11-99 14:46 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <string>
#include <vector>

using namespace std;

#include "TestLine.h"


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=====================
const string&			TestLine::GetTestLine() const
//						=====================
{
	return m_strTestLine;
}


//						===============================
const string&			TestLine::GetActionWordFunction() const
//						===============================
{
	return m_strAction;
}


//						======================
const string&			TestLine::GetSlaveName() const
//						======================
{
	return m_strSlaveName;
}


//						=====================
string					TestLine::GetArgument
//						=====================
(
	int					nIndex	// index of arguments
)
{
	string strArgument;		// specified argument

	if ((nIndex > 0) && (nIndex <= static_cast<int>(m_vstrArguments.size())))
	{
		strArgument = m_vstrArguments[nIndex-1];
	}

	return strArgument;
}


//						===============================
bool					TestLine::GetActionWordValidity() const
//						===============================
{
	return m_bActionValid;
}


//						================================
bool					TestLine::GetMasterSlaveValidity() const
//						================================
{
	return m_bMasterSlaveValid;
}


//						==============================
bool					TestLine::GetArgumentsValidity() const
//						==============================
{
	return m_bArgumentsValid;
}


//						=======================
int						TestLine::GetActionType() const
//						=======================
{
	return m_nActionType;
}


//						===========================
const vector<string>&	TestLine::GetArgumentErrors() const
//						===========================
{
	return m_vstrArgumentErrors;
}


//						============================
bool					TestLine::GetInterpretResult() const
//						============================
{
	return m_bInterpretResult;
}


//						=======================
int						TestLine::ArgumentCount() const
//						=======================
{
	return static_cast<int>(m_vstrArguments.size());
}
