/*****************************************************************************
 * $Workfile: IniFile.h $
 * $Revision: 1 $
 * $Modtime: 4-05-01 11:24 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000, 2001 CMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef INIFILE_H
#define INIFILE_H

// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)


#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Typedefs

// String pair, to be used for storing section-key combinations
typedef pair<string, string> STR2STRPAIR; 

// Map containing a string pair and a string
typedef map<STR2STRPAIR, string> PAIR2STRMAP;

// Vector containing key value pairs
typedef vector<pair<string,string> > SECTION;


///////////////////////////////////////////////////////////////////////////////
// Class IniFile

class IniFile
{
// Construction and destruction
public:
	IniFile();
	~IniFile();

// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	Find
	//
	// Description:	This function checks if specified section-key combination 
	//				exists.
	//				  
	// Parameters:	strSection		Section to look for
	//				strKey			Key to look for
	//
	// Returns:		true			Section-key combination found.
	//				false			Section-key combination not found.
	///////////////////////////////////////////////////////////////////////////////
	bool Find(const string& strSection, const string& strKey);

	///////////////////////////////////////////////////////////////////////////////
	// Function	:	Get
	//
	// Description: This function retrieves the value belonging to the 
	//				Section-Key combination specified.
	//
	// Parameters:	strSection		Section to look up
	//				strKey			Key to look up
	//
	// Returns:		String			Value of section-key combination
	///////////////////////////////////////////////////////////////////////////////
	string Get(const string& strSection, const string& strKey);

	///////////////////////////////////////////////////////////////////////////////
	// Function	:	GetSection
	//
	// Description: This function retrieves a vector containing all the key-value
	//				pairs of a section.
	//
	// Parameters:	strSectionName	Section to look up
	//
	// Returns:		Vector			Vector containing all key-values pairs of 
	//								a section
	///////////////////////////////////////////////////////////////////////////////
	SECTION GetSection(const string& strSectionName);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Import
	//
	// Description: This function imports all settings from the specified file.
	//					
	// Parameters:	strFileName		Name of the file to open.
	//
	// Returns:		true			Import succesfull.
	//				false			An error ocurred.
	///////////////////////////////////////////////////////////////////////////////
	bool Import(const string& strFileName);


// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	Open
	//
	// Description: This function open a file for reading.
	//					
	// Parameters:	strFileName		Name of the file to open.
	//
	// Returns:		true			Opened succesfully.
	//				false			An error ocurred.
	///////////////////////////////////////////////////////////////////////////////
	bool Open(const string& strFileName);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Close
	//
	// Description: This function imports all settings from the specified file.
	//					
	// Parameters:	strFileName		Name of the file to open.
	//
	// Returns:		true			Import succesfull.
	//				false			An error ocurred.
	///////////////////////////////////////////////////////////////////////////////
	bool Close();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Read
	//
	// Description: This function reads a line from the opened file.
	//					
	// Parameters:	strLine			Variable to fill with line.
	//
	// Returns:		true			Line read succesfully.
	//				false			An error ocurred.
	///////////////////////////////////////////////////////////////////////////////
	bool Read(string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ReadFile
	//
	// Description: This function imports all settings from the opened file.
	//					
	// Parameters:	None.
	//
	// Returns:		true			Import succesfull.
	//				false			An error ocurred.
	///////////////////////////////////////////////////////////////////////////////
	bool ReadFile();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Add
	//
	// Description: This function adds a setting to the internal map.
	//					
	// Parameters:	strSection		Name of the section
	//				strKey			Name of the key
	//				strValue		Name of the value
	//
	// Returns:		true			Setting added
	//				false			Setting not added
	///////////////////////////////////////////////////////////////////////////////
	bool Add(const string& strSection, const string& strKey, const string& strValue);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ToUpper
	//
	// Description: This function converts a string to uppercase.
	//
	// Parameters:	strSource		String to convert to uppercase.
	//
	// Returns:		String			To UPPERCASE converted string.
	///////////////////////////////////////////////////////////////////////////////
	string ToUpper(const string& strSource);
	
// Member variables
private:
	// Input stream to read a the file
	ifstream m_stream;

	// Container of section-key-value combinations
	PAIR2STRMAP m_SettingMap;
};

///////////////////////////////////////////////////////////////////////////////

#endif // !INIFILE_H
