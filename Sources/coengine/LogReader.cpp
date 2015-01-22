/*****************************************************************************
 * $Workfile: LogReader.cpp $
 * $Revision: 1 $
 * $Modtime: 6/25/01 2:36p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "LogReader.h"		// Class definition

#include <string>
#include <vector>

using namespace std;

#include "StrUtil.h"		// Needed for StrToVector()

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						====================
						LogReader::LogReader
//						====================
(
	const string& strFileName
)
{
	// Set the name of the log file to read.
	m_strFileName = strFileName;

	// Open the specified log file for reading; store the result of
	// this operation as a member stating whether LogReader is ready.
	m_bGood = Open( m_strFileName, READ );

	// Set the last read line and its argument-vector to empty.
	ClearLine();

	// Set the line number to zero.
	m_nLine = 0;
}


//						=====================
						LogReader::~LogReader()
//						=====================
{
	// Close the log file.
	Close();
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						===============
bool					LogReader::Good() const
//						===============
{
	return m_bGood;
}


//						======================
const string&			LogReader::GetFileName() const
//						======================
{
	return m_strFileName;
}


//						===================
bool					LogReader::NextLine()
//						===================
{
	bool bResult = false;

	// Set the last read line and its argument-vector to empty.
	ClearLine();

	// Determine if LogReader is able to read its log file.
	if ( m_bGood )
	{
		string strLine;	// to be filled with log line

		// Read the next line in the log file, and determine if this succeeded.
		if ( Read( strLine ) )
		{
			// Set the members to the values as retrieved from the log file.
			m_strLine = strLine;
			m_vstrArguments = StrToVector( strLine, DELIMITER );
			m_nLine++;
			bResult = true;
		}
	}

	return bResult;
}


//						==================
const string&			LogReader::GetLine() const
//						==================
{
	return m_strLine;
}


//						======================
string					LogReader::GetArgument
//						======================
(
	int					nIndex
) const
{
	// Set the argument value default to an empty string.
	string strArgument;

	// Determine if the specified index lies in the range of possible
	// indices [1..maxarg]
	if ( nIndex > 0 && nIndex <= GetNumberOfArguments() )
	{
		// Get the argument from the argument vector; note that since
		// the first argument has index 1, 1 is subtracted so it correlates
		// with the first element of the vector, which has index 0.
		strArgument = m_vstrArguments[nIndex - 1];
	}

	return strArgument;
}


//						===============================
int						LogReader::GetNumberOfArguments() const
//						===============================
{
	// Set the number of arguments default to zero.
	int nArguments = 0;

	// Determine if there are any arguments; if so, get the size of the
	// argument vector.
	if ( !m_vstrArguments.empty() )
	{
		nArguments = m_vstrArguments.size();
	}

	return nArguments;
}


//						========================
int						LogReader::GetLineNumber() const
//						========================
{
	return m_nLine;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						====================
void					LogReader::ClearLine()
//						====================
{
	// Set the last read line and its argument-vector to empty.
	m_strLine.erase();
	m_vstrArguments.clear();
}
