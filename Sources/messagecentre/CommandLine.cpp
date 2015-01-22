

#include <iostream>
#include <sstream>
using namespace std;

#include "CommandLine.h"		// Class definition

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

CommandLine::CommandLine(const char* pszCommandLine)
{
	if (pszCommandLine != 0)
	{ 
		// Initialise the string
		m_strCommandLine = string(pszCommandLine);

		// Process the string
		Process();
	}
}

CommandLine::~CommandLine()
{ /* EMPTY */ }

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

bool CommandLine::GetSwitch(const string& strSwitch) const
{
	bool bResult = false;

	// See if this string was present on the commandline
	int nSize = m_vstrCommandLine.size();
	for (int i = 0; i < nSize; i++)
	{
		if (m_vstrCommandLine[i] == strSwitch)
		{ bResult = true; }
	}

	return bResult;
}

bool CommandLine::GetString(const string& strKey, string& strValue) const
{
	bool bResult = false;

	// Search the required key
	int nSize = m_vstrCommandLine.size();
	for (int i = 0; i < nSize; i++)
	{
		if (m_vstrCommandLine[i] == strKey)
		{ 
			// Next string in vector is the required value
			if (i != (nSize-1))
			{
				strValue = m_vstrCommandLine[i+1];
				if (!strValue.empty())
				{ bResult = true; }
			}

			break;
		}
	}

	return bResult;
}

bool CommandLine::GetInteger(const string& strKey, int& nValue) const
{
	bool bResult = false;
	string strValue;

	// First get the required value as a string
	if (GetString(strKey, strValue))
	{
		// Now convert the string to an integer
		istringstream iss(strValue);
		iss >> nValue;

		if (!iss.fail())
		{ bResult = true; }
	}
	return bResult;
}

bool CommandLine::GetInteger(const string& strKey, unsigned short& nValue) const
{
	bool bResult = false;
	string strValue;

	// First get the required value as a string
	if (GetString(strKey, strValue))
	{
		// Now convert the string to an integer
		istringstream iss(strValue);
		iss >> nValue;

		if (!iss.fail())
		{ bResult = true; }
	}
	return bResult;
}

void CommandLine::Dump()
{
	int nSize = m_vstrCommandLine.size();
	for (int i = 0; i < nSize; i++)
	{ cout << m_vstrCommandLine[i] << endl; }
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

bool CommandLine::Process()
{
	bool bResult = false;

	if (!m_strCommandLine.empty())
	{
		int nFirstPosition = 0;
		int nSecondPosition   = 0;

		// Parse the commandline and store elements in a string vector
		do
		{
			nSecondPosition = m_strCommandLine.find(' ', nFirstPosition);
			m_vstrCommandLine.push_back(m_strCommandLine.substr(nFirstPosition, (nSecondPosition - nFirstPosition)));
			nFirstPosition = nSecondPosition;
			nFirstPosition++;
			
		} while (nSecondPosition != string::npos);
		bResult = true;
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
