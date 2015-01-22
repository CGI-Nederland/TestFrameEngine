/*****************************************************************************
 * $Workfile: IniFile.cpp $
 * $Revision: 1 $
 * $Modtime: 4-05-01 11:37 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000, 2001 CMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "IniFile.h"

#include <locale>
#include <iostream>
#include <sstream>

using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						================
						IniFile::IniFile()
//						================
{ /* EMPTY */ }

//						=================
						IniFile::~IniFile()
//						=================
{ /* EMPTY */ }

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=============
bool					IniFile::Find  
//						=============
(
	const string& 		strSection,
	const string& 		strKey
)
{
	bool bResult = false;

	STR2STRPAIR StringPair(ToUpper(strSection), strKey);

	PAIR2STRMAP::iterator Iterator = m_SettingMap.find(StringPair);

	// Check section-key combination exists.
	if (Iterator != m_SettingMap.end())
	{ bResult = true; }
	
	return bResult;
}

//						============
string					IniFile::Get
//						============
(
	const string& 		strSection,
	const string& 		strKey
)
{
	string strResult;

	STR2STRPAIR StringPair(ToUpper(strSection), strKey);

	PAIR2STRMAP::iterator Iterator = m_SettingMap.find(StringPair);

	// Check if section-key combination exists
	if (Iterator != m_SettingMap.end())
	{ strResult = Iterator->second; }

	return strResult;
}

//						===================
SECTION					IniFile::GetSection
//						===================
(
	const string&		strSectionName
)
{
	SECTION	sResult;

	// Get the first entry
	PAIR2STRMAP::iterator Iterator = m_SettingMap.begin();

	while (Iterator != m_SettingMap.end())
	{
		// Retrieve the name of the section
		string strSection = Iterator->first.first;
		
		// See if this is the section asked for
		if (strSection == strSectionName)
		{
			// Retrieve the key and value strings
			string strKey = Iterator->first.second;
			string strValue = Iterator->second;

			// Create a key value pair
			pair<string, string> Pair(strKey, strValue);

			// Store the pair in the vector
			sResult.push_back(Pair);
		}

		// Take the section, key, value pair
		Iterator++;
	}

	return sResult;
}

//						===============
bool					IniFile::Import
//						===============
(
	const string&		strFileName
)
{
	bool bResult = false;

	bResult = Open(strFileName);
	bResult = (bResult && ReadFile());
	bResult = (bResult && Close());

	return bResult;
}


///////////////////////////////////////////////////////////////////////////////
// Implementation

//						=============
bool 					IniFile::Open
//						=============
(
	const string& 		strFileName		// Name of the file to open
)
{
	bool bResult = false;
	
	if (!strFileName.empty())
	{
		// Open the file and check the result
		m_stream.open(strFileName.c_str(), ios::in);
		bResult = m_stream.is_open();
	}
	
	return bResult;
}

//						==============
bool 					IniFile::Close()
//						==============
{
	bool bResult = false;

	// Close the file and check the result
	m_stream.close();
	bResult = !m_stream.is_open();
		
	return bResult;
}

//						=============
bool 					IniFile::Read
//						=============
(
	string& 			strLine			// Variable to store result in
)
{
	bool bResult = false;

	// Read line from file and check the result
	getline(m_stream, strLine);
	bResult = m_stream.good();
	
	return bResult;
}

//						=================
bool					IniFile::ReadFile()
//						=================
{
	bool bResult = m_stream.is_open(); 
	
	string strLine;
	string strSection;

	// Intializing positional variables for use with string-array
	string::size_type nStartPos = 0;	// Startposition
	string::size_type nEndPos = 0;	// Endposition
	string::size_type nSize = 0;		// Size

	while (bResult && Read(strLine)) 
	{
		// Read a line from the stream, this line should be either a Section header,
		// a Key-Value pair or a blank.
		if ((nSize = strLine.length()) != 0 )
		{
			nStartPos = strLine.find('[');
			nEndPos = 	strLine.find(']'); 
				
			// Entry point for a Section
			if((nStartPos != string::npos) && (nEndPos != string::npos)) 
			{
				// Read Section from stream.
				strSection = strLine.substr((nStartPos + 1),(nEndPos - nStartPos - 1));
			}
			else
			{
				// Entry point for a Key-Value pair
				nStartPos = strLine.find('=');

				if (nStartPos != string::npos)
				{
					// Read Key-Value from stream.
					string strKey = strLine.substr(0, (nStartPos));
					string strValue = strLine.substr ((nStartPos + 1),(nSize - (nStartPos + 1)));
					
					// Add Key-Value-Section to the container.				
					bResult = Add(strSection, strKey, strValue);
				}
			}
		}
	}

	return bResult;
}

//						============
bool					IniFile::Add  
//						============
(
	const string& 		strSection,
	const string& 		strKey,
	const string& 		strValue
)
{
	bool bResult = false;

	STR2STRPAIR StringPair(ToUpper(strSection), strKey);

	PAIR2STRMAP::iterator Iterator = m_SettingMap.find(StringPair);

	// Check if section-key combination exists.
	if (Iterator == m_SettingMap.end())
	{
		// Combination does not exist, add combination.
		pair<PAIR2STRMAP::iterator , bool> ResultIter = m_SettingMap.insert(PAIR2STRMAP::value_type(StringPair, strValue));

		bResult = ResultIter.second;
	}

	return bResult;
}

//						================
string					IniFile::ToUpper
//						================
(
	const string&		strSource
)
{
	string strResult = strSource;
	
	// Create a locale
	locale loc(locale::empty(), locale("C"), locale::numeric);
	
	// Convert to uppercase
	string::size_type i = 0;

	for (i = 0; i < strSource.length(); ++i)
	{ strResult[i] = toupper(strSource[i], loc); }

	return strResult;
}

///////////////////////////////////////////////////////////////////////////////
