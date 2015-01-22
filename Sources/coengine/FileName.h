/*****************************************************************************
 * $Workfile: FileName.h $
 * $Revision: 1 $
 * $Modtime: 8/22/01 10:43a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef FIILENAME_H
#define FIILENAME_H

// Includes
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// class FileName

class FileName
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor
	///////////////////////////////////////////////////////////////////////////////
	FileName();

	///////////////////////////////////////////////////////////////////////////////
	// constructor
	//
	// parameter	:	strFile		name of file
	///////////////////////////////////////////////////////////////////////////////
	explicit FileName( const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// destructor
	///////////////////////////////////////////////////////////////////////////////
	~FileName();

private:
	FileName( const FileName& src ){};	// Copy constructor

// Public interface
public: 
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Set()
	//
	// description	:	This function sets FileName's contents to that of the
	//					specified file, but only if its name is correct.
	//				
	// parameters	:	strFile		file to set
	//
	// returns		:	true	file set
	//					false	file could not be set
	///////////////////////////////////////////////////////////////////////////////	
	bool Set( const string& strFile );
	
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Good()
	//
	// description	:	This function states whether FileName currectly holds a
	//					valid file name.
	//				
	// parameters	:	-
	//
	// returns		:	true	holds valid file name
	//					false	doesn't hold valid file name
	///////////////////////////////////////////////////////////////////////////////	
	bool Good() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetName()
	//
	// description	:	This function returns the name (no location, no extension)
	//					of the file.
	//				
	// parameters	:	-
	//
	// returns		:	string containing name
	///////////////////////////////////////////////////////////////////////////////	
	const string& GetName() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetExtension()
	//
	// description	:	This function returns the extension	of the file.
	//				
	// parameters	:	-
	//
	// returns		:	string containing extension
	///////////////////////////////////////////////////////////////////////////////	
	const string& GetExtension() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetDrive()
	//
	// description	:	This function returns the drive	of the file.
	//				
	// parameters	:	-
	//
	// returns		:	string containing drive
	///////////////////////////////////////////////////////////////////////////////	
	const string& GetDrive() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetDirectories()
	//
	// description	:	This function returns the vector of directories of the
	//					file; each subdirectory placed after its parent-directory
	//					in the vector.
	//				
	// parameters	:	-
	//
	// returns		:	vector of directories
	///////////////////////////////////////////////////////////////////////////////	
	const vector<string>& GetDirectories() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetFile()
	//
	// description	:	This function return the file: location and full name.
	//				
	// parameters	:	-
	//
	// returns		:	string containing file
	///////////////////////////////////////////////////////////////////////////////	
	string GetFile() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetFullName()
	//
	// description	:	This function returns the full name (name and extension)
	//					of the file.
	//				
	// parameters	:	-
	//
	// returns		:	string containing full name
	///////////////////////////////////////////////////////////////////////////////	
	string GetFullName() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLocation()
	//
	// description	:	This function returns the location (drive and directories)
	//					of the file.
	//				
	// parameters	:	-
	//
	// returns		:	string containing location
	///////////////////////////////////////////////////////////////////////////////	
	string GetLocation() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeName()
	//
	// description	:	This function changes the name of the file, but only if
	//					the new one is correct.
	//				
	// parameters	:	strName		new name
	//
	// returns		:	true	name changed
	//					false	name could not be changed
	///////////////////////////////////////////////////////////////////////////////	
	bool ChangeName( const string& strName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeExtension()
	//
	// description	:	This function changes the extension of the file, but only
	//					if the new one is correct.
	//				
	// parameters	:	strExtension	new extension
	//
	// returns		:	true	extension changed
	//					false	extension could not be changed
	///////////////////////////////////////////////////////////////////////////////	
	bool ChangeExtension( const string& strExtension );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeLocation()
	//
	// description	:	This function changes the location of the file, but only
	//					if the new one is correct.
	//				
	// parameters	:	strLocation		new location
	//
	// returns		:	true	location changed
	//					false	location could not be changed
	///////////////////////////////////////////////////////////////////////////////	
	bool ChangeLocation( const string& strLocation );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeDrive()
	//
	// description	:	This function changes the drive of the file, but only if
	//					the new one is correct.
	//				
	// parameters	:	strDrive		new drive
	//
	// returns		:	true	drive changed
	//					false	drive could not be changed
	///////////////////////////////////////////////////////////////////////////////	
	bool ChangeDrive( const string& strDrive );
	
// Implementation		
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	DisectFile()
	//
	// description	:	This function disects the specified file into its parts
	//					(drive, directories, name, and extension), and checks if
	//					these are all correct.
	//				
	// parameters	:	strFile		file to disect
	//
	// returns		:	true	complete file correct
	//					false	complete file not correct
	///////////////////////////////////////////////////////////////////////////////	
	bool DisectFile( const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DisectFullName()
	//
	// description	:	This function disects the specified full name into name and
	//					extension, and checks if both are correct.
	//				
	// parameters	:	strFullName		full name to disect
	//
	// returns		:	true	full name correct
	//					false	full name not correct
	///////////////////////////////////////////////////////////////////////////////	
	bool DisectFullName( const string& strFullName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DisectLocation()
	//
	// description	:	This function disects the specified location into drive and
	//					directories, and checks if all are correct.
	//				
	// parameters	:	strLocation		location to disect
	//
	// returns		:	true	location correct
	//					false	location not correct
	///////////////////////////////////////////////////////////////////////////////	
	bool DisectLocation( const string& strLocation );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HandleName()
	//
	// description	:	This function handles the specified name: checks if it's
	//					not empty and if it's correct, and if so, sets it as a
	//					member.
	//				
	// parameters	:	strName		name to handle
	//
	// returns		:	true	name correct and set
	//					false	name not correct
	///////////////////////////////////////////////////////////////////////////////	
	bool HandleName( const string& strName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HandleExtension()
	//
	// description	:	This function handles the specified extension: checks if
	//					it's correct, and if so, sets it as a member.
	//				
	// parameters	:	strExtension		extension to handle
	//
	// returns		:	true	extension correct and set
	//					false	extension not correct
	///////////////////////////////////////////////////////////////////////////////	
	bool HandleExtension( const string& strExtension );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HandleDrive()
	//
	// description	:	This function handles the specified drive: checks if it's
	//					correct, and if so, sets it as a member.
	//				
	// parameters	:	strDrive		drive to handle
	//
	// returns		:	true	drive correct and set
	//					false	drive not correct
	///////////////////////////////////////////////////////////////////////////////	
	bool HandleDrive( const string& strDrive );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HandleDir()
	//
	// description	:	This function handles the specified directory-string:
	//					checks if it starts with a directory-separator, splits it
	//					up into separate directories; checks each directory, and if
	//					all are correct, sets their vector as a member.
	//				
	// parameters	:	strDir		directory-string to handle
	//
	// returns		:	true	directories correct and set
	//					false	directories not correct
	///////////////////////////////////////////////////////////////////////////////	
	bool HandleDir( const string& strDir );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Check()
	//
	// description	:	This function checks if a specified name does not contain
	//					any of the unallowed characters.
	//				
	// parameters	:	strName		name to check
	//
	// returns		:	true	correct: no unallowed characters
	//					false	incorrect: one or more unallowed characters
	///////////////////////////////////////////////////////////////////////////////	
	bool Check( const string& strName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Clear()
	//
	// description	:	This function clears the members containing name,
	//					extension, drive, and directories.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Clear();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineDirSeparator()
	//
	// description	:	This function determines the value of the directory
	//					separator, if it hasn't already been determined. It
	//					determines which of the possible directory separators
	//					occurs first in the specified input-string.
	//				
	// parameters	:	strInput	string in which to search for directory
	//								separator
	//
	// returns		:	true	directory separator found
	//					false	no directory separator found
	///////////////////////////////////////////////////////////////////////////////	
	bool DetermineDirSeparator( const string& strInput );

// Member variables
private:
	bool m_bGood;				// States whether this object currently holds a
								// correct file name
	string m_strDirSep;			// Used directory-separator
	string m_strName;			// Name of file (no location, no extension)
	string m_strExtension;		// File-extension
	string m_strDrive;			// Drive
	vector<string> m_vstrDir;	// Vector of directories
};

////////////////////////////////////////////////////////////////////////////////

#endif // !FIILENAME_H
 