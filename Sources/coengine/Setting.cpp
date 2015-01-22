/*****************************************************************************
 * $Workfile: Setting.cpp $
 * $Revision: 10 $
 * $Modtime: 8/15/01 5:29p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)
// Disable Visual C++ warning, function name for compiler is truncated
#pragma warning(disable:4503)

#include <locale>
#include <iostream>
#include <sstream>

#include "Setting.h"	// Class definition
#include "IOFactory.h"
#include "IOInterface.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor

//					================
					Setting::Setting()
//					================
{
	m_pIOInterface = 0;
	m_bSaveOnChange = false;		// No automatic save on change allowed
}
// Copy constructor
	
// Other constructors

//					================
					Setting::Setting
//					================
(
	const std::string& strFileName
)	:	m_strFileName(strFileName)
{
	IOFactory Factory;
	m_bSaveOnChange = false;		// No automatic save on change allowed

	m_pIOInterface = Factory.CreateIOInterface(m_strFileName);  
}

// Destructor

//					=================
					Setting::~Setting()
//					=================
{
	IOFactory Factory;

	Factory.DestroyIOInterface(m_pIOInterface);
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//					====================
void				Setting::SetFileName
//					====================
(
	const std::string&	strFileName
)
{
	// check if filename differs
	if (m_strFileName != strFileName)
	{ 

		IOFactory Factory;
		// destroy old IOInterface pointer
		Factory.DestroyIOInterface(m_pIOInterface);

		m_strFileName = strFileName;
		// initialise IOInterface pointer
		m_pIOInterface = Factory.CreateIOInterface(m_strFileName);
	}
}

//					====================
std::string			Setting::GetFileName()	const
//					====================
{
	return m_strFileName;
}

//					===============
bool				Setting::Import()
//					===============
{
	bool bResult =false;

	if ( m_pIOInterface != 0 )
	{
		// open file
		m_pIOInterface->Open(IOInterface::IOREAD);

		// check if file is open
		if (m_pIOInterface->IsOpen())
		{
			// clear contents of container
			m_SettingMap.clear();

			// fill container with data from file
			bResult = WriteFile2Map();

			// close file
			m_pIOInterface->Close(); 
		}
	}

	return bResult;
}

//					===============
bool				Setting::Import
//					===============
(
	const string& strFileName
)
{
	// check if filename differs
	if (m_strFileName != strFileName)
	{ SetFileName(strFileName);	}	

	return Import();
}

//					===============
bool				Setting::Export()
//					===============
{
	bool bResult		= false;

	if ( m_pIOInterface != 0 )
	{
		IOFactory Factory;

		if (!m_strFileName.empty())
		{
			unsigned int nEPos = m_strFileName.find_last_of('.');
			
			// Create Filename for backup file.
			if (nEPos != std::string::npos)
			{
				std::string strTmpFileName;

				strTmpFileName = m_strFileName.substr(0, nEPos);
				strTmpFileName.append(BACKUP);

				bool bBaseFile = false;
				bool bBackUpFile = false;

				// check if file exists
				if (Factory.Exist(m_strFileName))
				{
					bBaseFile = true;
	
					// check if file is renamed to .bak
					if (Factory.Rename(m_strFileName, strTmpFileName))
					{ bBackUpFile = true; }
				}

				// check if there was a basefile and no backup was created
				if (!(bBaseFile && !bBackUpFile))
				{ m_pIOInterface->Open(m_strFileName, IOInterface::IOWRITE); }
				else
				{ return false; }

				// check if file was opened
				if(m_pIOInterface->IsOpen())
				{ 
					// write data to file
					bResult = WriteMap2File();
					m_pIOInterface->Close();
				}


				// Check if new file has been created
				if (bResult)
				{	// Remove backup
					Factory.Remove(strTmpFileName);
				}
				else
				{
					// Remove original
					Factory.Remove(m_strFileName);
					// Restore backup
					Factory.Rename(strTmpFileName, m_strFileName);
				}
			}
		}
	}
	
	return bResult;
}

//					===============
bool				Setting::Export
//					===============
(
	const string& strFileName
)
{
	if (m_strFileName != strFileName)
	{ SetFileName(strFileName);	}
	
	return Export();
}

//					============
std::string			Setting::Get
//					============
(
	const std::string& strSection,
	const std::string& strKey
)
{
	std::string strResult;

	STR2STRPAIR StringPair(ToUpper(strSection), strKey);

	PAIR2STRMAP::iterator Iterator = m_SettingMap.find(StringPair);

	// Check if section-key combination exists
	if (Iterator != m_SettingMap.end())
	{ strResult = Iterator->second; }

	return strResult;
}

//					============
bool				Setting::Set 
//					============
(
	const std::string& strSection,
	const std::string& strKey,
	const std::string& strValue
)
{
	bool bResult = false;

	STR2STRPAIR StringPair(ToUpper(strSection), strKey);

	PAIR2STRMAP::iterator Iterator = m_SettingMap.find(StringPair);

	// Check if section-key combination exists.
	if (Iterator != m_SettingMap.end())
	{
		// Combination exists, change value.
		Iterator->second = strValue;

		bResult = true;
	}
	else
	{
		// Combination does not exist, add combination.
		std::pair<PAIR2STRMAP::iterator , bool> ResultIter = m_SettingMap.insert(PAIR2STRMAP::value_type(StringPair, strValue));

		bResult = ResultIter.second;
	}

	// Check if changes have to be saved.
	if (m_bSaveOnChange && bResult)
	{ Export(); }

	return bResult;
}

//					=============
bool				Setting::Find  
//					=============
(
	const std::string& strSection,
	const std::string& strKey
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


//					===============
bool				Setting::Update  
//					===============
(
	const std::string& strSection,
	const std::string& strKey,
	const std::string& strValue
)
{
	bool bResult = false;

	STR2STRPAIR StringPair(ToUpper(strSection), strKey);

	PAIR2STRMAP::iterator Iterator = m_SettingMap.find(StringPair);

	// Check if section-key combination exists.
	if (Iterator != m_SettingMap.end())
	{
		// Combination exists, change value.
		Iterator->second = strValue;

		bResult = true;

		// Check if changes have to be saved.
		if (m_bSaveOnChange)
		{ Export(); }
	}

	return bResult;
}

//					============
bool				Setting::Add  
//					============
(
	const std::string& strSection,
	const std::string& strKey,
	const std::string& strValue
)
{
	bool bResult = false;

	STR2STRPAIR StringPair(ToUpper(strSection), strKey);

	PAIR2STRMAP::iterator Iterator = m_SettingMap.find(StringPair);

	// Check if section-key combination exists.
	if (Iterator == m_SettingMap.end())
	{
		// Combination does not exist, add combination.
		std::pair<PAIR2STRMAP::iterator , bool> ResultIter = m_SettingMap.insert(PAIR2STRMAP::value_type(StringPair, strValue));

		bResult = ResultIter.second;

		// Check if changes have to be saved.
		if (m_bSaveOnChange && bResult)
		{ Export(); }
	}

	return bResult;
}


//					===============
bool				Setting::Remove 
//					===============
(
	const std::string& strSection,
	const std::string& strKey
)
{
	bool bResult = false;

	STR2STRPAIR StringPair(ToUpper(strSection), strKey);

	// Check if string pair had been erased.
	if ( m_SettingMap.erase(StringPair) > 0 )
	{ 
		bResult = true;

		// Check if changes have to be saved.
		if (m_bSaveOnChange)
		{ Export(); }
	}

	return bResult;
}

//					=====================
void				Setting::SaveOnChange
//					=====================
(
	bool bValue
)
{
	m_bSaveOnChange = bValue;
}

//											=======================
vector<pair<pair<string, string>, string> >	Setting::GetAllSettings()
//											=======================
{
	vector<pair<pair<string, string>, string> > vprResult;

	PAIR2STRMAP::iterator Iterator = m_SettingMap.begin();

	for ( ;Iterator != m_SettingMap.end(); Iterator++ )
	{
		vprResult.push_back( make_pair( Iterator->first, Iterator->second ) );
	}

	return vprResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//					======================
bool				Setting::WriteFile2Map()
//					======================
{
	// Open the ini file.
	bool bResult = m_pIOInterface->IsOpen();
	
	std::string strLine;			// string in which to place the read line
	std::string strSection = "";	// string in which to place the name of the
									// current section; default an empty string

	// If the file could be opened, read each line until none are left
	// or until performing a Set operation fails.
	while (bResult && m_pIOInterface->Read(strLine)) 
	{
		// Determine if the line is not empty.
		if (!strLine.empty())
		{
			// Determine the first character of the line.
			std::string strFirstChar = strLine.substr(0,1);

			// Check if the line starts with a semicolon (;) or a hash (#);
			// this means the line contains comment.
			if (strFirstChar == ";" || strFirstChar == "#")
			{
				// Ignore line.
			}
			// Otherwise, check if the first character is an opening square bracket;
			// this means the line must be a section header.
			else if (strFirstChar == "[")
			{
				// Determine the position of the closing square bracket.
				unsigned int nClosBracket = strLine.find("]");

				// Determine if the line does contain a closing square bracket.
				// If it does not, the line is ignored.
				if (nClosBracket != std::string::npos)
				{
					// Take as current section name the string between the
					// square brackets.
					strSection = strLine.substr(1, nClosBracket - 1);
				}
			}
			else
			{
				// Determine if the equal character (=) is used in the line;
				// this means the line contains a Key-Value pair.
				// If the equal character is not used, the line is ignored.
				unsigned int nEqualPos = strLine.find("=");
				if (nEqualPos != std::string::npos)
				{
					// Take as Key all characters before the equal character.
					std::string strKey = strLine.substr(0, nEqualPos);

					// Take as Value all characters after the equal character.
					std::string strValue = strLine.substr(nEqualPos + 1);

					// Add Section-Key-Value to the map.
					bResult = Set(strSection, strKey, strValue);
				}
			}
		}
	}

	m_pIOInterface->Close(); 

	return bResult;
}

//					======================
bool				Setting::WriteMap2File()
//					======================
{
	bool bResult = m_pIOInterface->IsOpen(); 

	int nSectionCount = 0;

	PAIR2STRMAP::iterator Iterator = m_SettingMap.begin();
	STR2STRPAIR StringPair;

	std::string strSection;

	// Write data in container to file.
	while (bResult && (Iterator != m_SettingMap.end()))
	{
		StringPair = Iterator->first;
		
		// Entry point New Section
		if (strSection != StringPair.first)
		{
			// Insert empty line between Sections, except for the first Section.
			if (nSectionCount != 0)
			{ m_pIOInterface->Write("\n"); }
			// retrieve section from container.
			strSection = StringPair.first;
			std::ostringstream ossSection;
			// format next to be written section
			ossSection << "[" << strSection << "]" << endl;
			// Write New Section to stream.
			m_pIOInterface->Write(ossSection.str());

			nSectionCount++;
		}

		std::ostringstream ossKeyValue;
		// format next to be written key-value pair.
		ossKeyValue << StringPair.second << "=" << Iterator->second << endl;
		// Write New Key-Value pair to stream.
		bResult = m_pIOInterface->Write(ossKeyValue.str());
		// goto next item in container
		Iterator++;
	}

	return bResult;
}

//					================
std::string			Setting::ToUpper
//					================
(
	std::string strSrc
)
{
	// Does not work because of a bug in Microsoft's C++ library?!?!
//	std::locale& loc = std::locale::global();

	// Using the locale of cout...
	const std::locale& loc = std::cout.getloc();

	// The C++ standard header contains a toupper template function.
	// This is a C++ function, not a C function, which converts properly
	// to uppercase with current locale of cout.
	for (unsigned int i = 0; i < strSrc.length(); ++i)
	{ strSrc[i] = std::toupper(strSrc[i], loc); }

	return strSrc;
}

const std::string Setting::BACKUP = ".bak"; 

///////////////////////////////////////////////////////////////////////////////
