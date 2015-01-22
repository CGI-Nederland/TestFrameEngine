/*****************************************************************************
 * $Workfile: FileName.cpp $
 * $Revision: 1 $
 * $Modtime: 7/19/01 3:30p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

// Includes
#include "FileName.h"		// Class definition

#include <string>
#include <vector>

using namespace std;

#include "StrUtil.h"		// Needed for string-vector conversions

// Defines
#define DIR_SEPARATORS		string( "/\\" )
#define EXT_SEPARATOR		string( "." )
#define DRIVE_SEPARATOR		string( ":" )
#define NOT_ALLOWED_CHARS	string( "/\\:*?\"<>|" )

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						==================
						FileName::FileName()
//						==================
{
	m_bGood = false;
}


//						==================
						FileName::FileName
//						==================
(
	const string&		strFile
)
{
	// Set the file.
	Set( strFile );
}

//						===================
						FileName::~FileName()
//						===================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=============
bool					FileName::Set
//						=============
(
	const string&		strFile
)
{
	// Disect the file into its parts (drive, directories, name, extension).
	m_bGood = DisectFile( strFile );

	// Clear the file name part members if it is not a valid file name.
	if ( !m_bGood )
	{
		Clear();
	}

	return m_bGood;
}


//						==============
bool					FileName::Good() const
//						==============
{
	return m_bGood;
}


//						=================
const string&			FileName::GetName() const
//						=================
{
	// Return the name of the file; no location, no extension.
	return m_strName;
}


//						======================
const string&			FileName::GetExtension() const
//						======================
{
	// Return the file-extension.
	return m_strExtension;
}


//						==================
const string&			FileName::GetDrive() const
//						==================
{
	// Return the drive of the file.
	return m_strDrive;
}


//						========================
const vector<string>&	FileName::GetDirectories() const
//						========================
{
	// Return a vector with the directories; each subdirectory placed after
	// its parent-directory in the vector.
	return m_vstrDir;
}


//						=================
string					FileName::GetFile() const
//						=================
{
	// Return the full file: location, name, and extension.
	string strFile;

	if ( m_bGood )
	{
		// Add location and directory-separator if there is a location.
		string strLocation = GetLocation();
		if ( !strLocation.empty() )
		{
			strFile = strLocation + m_strDirSep;
		}

		// Add the full name (name and extension).
		strFile += GetFullName();
	}

	return strFile;
}


//						=====================
string					FileName::GetFullName() const
//						=====================
{
	// Return the full name of the file: name and extension;
	// no location, though.
	string strFullName;

	if ( m_bGood )
	{
		strFullName = m_strName;
		
		// Add the extension-separator and extension, if there is an extension.
		if ( !m_strExtension.empty() )
		{
			strFullName += EXT_SEPARATOR + m_strExtension;
		}
	}

	return strFullName;
}


//						=====================
string					FileName::GetLocation() const
//						=====================
{
	// Return the location (drive and directories); included in this string
	// are the drive- and directory separators (including the closing one).
	string strLocation;

	if ( m_bGood )
	{
		// Add the drive and drive-separator if there is a drive.
		if ( !m_strDrive.empty() )
		{
			strLocation += m_strDrive + DRIVE_SEPARATOR;
		}

		// Add a directory-separator if there either a drive or directories
		// (or both).
		if ( !m_strDrive.empty() || !m_vstrDir.empty() )
		{
			strLocation += m_strDirSep;
		}

		// Add the (separated) directories if there are any.
		if ( !m_vstrDir.empty() )
		{
			strLocation += VectorToStr( m_vstrDir, m_strDirSep );
		}
	}

	return strLocation;
}


//						====================
bool					FileName::ChangeName
//						====================
(
	const string&		strName
)
{
	bool bResult = false;

	// Only change the name if FileName already contains a valid file.
	if ( m_bGood )
	{
		// Check the name, and, if it is valid, change it.
		bResult = HandleName( strName );
	}

	return bResult;
}


//						=========================
bool					FileName::ChangeExtension
//						=========================
(
	const string&		strExtension
)
{
	bool bResult = false;

	// Only change the extension if FileName already contains a valid file.
	if ( m_bGood )
	{
		// Check the extension, and, if it is valid, change it.
		bResult = HandleExtension( strExtension );
	}

	return bResult;
}


//						========================
bool					FileName::ChangeLocation
//						========================
(
	const string&		strLocation
)
{
	bool bResult = false;

	// Only change the location if FileName already contains a valid file.
	if ( m_bGood )
	{
		// Disect the location, check it, and, if it is valid, change it.
		bResult = DisectLocation( strLocation );
	}

	return bResult;
}


//						=====================
bool					FileName::ChangeDrive
//						=====================
(
	const string&		strDrive
)
{
	bool bResult = false;

	// Only change the drive if FileName already contains a valid file.
	if ( m_bGood )
	{
		// Check the drive, and, if it is valid, change it.
		bResult = HandleDrive( strDrive );
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						====================
bool					FileName::DisectFile
//						====================
(
	const string&		strFile
)
{
	bool bResult = false;

	// Determine the used directory-separator by determining which out of
	// those possible is used first in the file.
	DetermineDirSeparator( strFile );
	
	// Initialise the full name to be the file, and the location to be empty.
	string strFullName = strFile;
	string strLocation;

	// Find the position of the last directory-separator, and determine if
	// there is (at least) one such directory-separator.
	string::size_type nLastDirSep = strFile.find_last_of( DIR_SEPARATORS );
	if ( nLastDirSep != string::npos )
	{
		// Take as full name all characters after this separator; take as
		// the file location all characters before it.
		strFullName = strFile.substr( nLastDirSep + 1 );
		strLocation = strFile.substr( 0, nLastDirSep );
	}

	// Disect the full name into name and extension, and determine if this
	// was successful.
	if ( DisectFullName( strFullName ) )
	{
		// Disect the location into drive and directories, and determine if
		// this was successful.
		if ( DisectLocation( strLocation ) )
		{
			bResult = true;
		}
	}
	
	return bResult;
}


//						========================
bool					FileName::DisectFullName
//						========================
(
	const string&		strFullName
)
{
	bool bResult = false;

	// Determine if the full name is not empty.
	if ( !strFullName.empty() )
	{
		// Initialise the name to be the full name, and the extension to
		// be empty.
		string strName = strFullName;
		string strExtension;

		// Find the position of the last extension-separator in the full name,
		// and determine if there is (at least) one such separator.
		string::size_type nExt = strFullName.find_last_of( EXT_SEPARATOR );
		if ( nExt != string::npos )
		{
			// The name are all characters before the extension-separator,
			// and the extension all characters after it.
			strName = strFullName.substr( 0, nExt );
			strExtension = strFullName.substr( nExt + 1 );
		}

		// Handle both name and extension; they are set, however, only if
		// they are valid.
		bResult = HandleName( strName ) && HandleExtension( strExtension );
	}

	return bResult;
}


//						========================
bool					FileName::DisectLocation
//						========================
(
	const string&		strLocation
)
{
	bool bResult = false;

	// Determine if the location is specified.
	if ( !strLocation.empty() )
	{
		// Initialise the drive to be empty, and the directies to be the
		// location.
		string strDrive;
		string strDir = strLocation;

		// Find the position of the drive-separator, and determine if it is found.
		string::size_type nDriveSep = strLocation.find_first_of( DRIVE_SEPARATOR );
		if ( nDriveSep != string::npos )
		{
			// Take as drive all characters before this separator; take as
			// directories all characters after it.
			strDrive = strLocation.substr( 0, nDriveSep );
			strDir = strLocation.substr( nDriveSep + 1 );
		}

		// Handle both drive and directories; they are set, however, only if
		// they are valid.
		if ( HandleDir( strDir ) )
		{
			bResult = HandleDrive( strDrive );
		}
	}
	else
	{
		// An empty location is allowed; clear the drive and directories.
		m_strDrive.erase();
		m_vstrDir.clear();
		bResult = true;
	}

	return bResult;
}


//						====================
bool					FileName::HandleName
//						====================
(
	const string&		strName
)
{
	bool bResult = false;

	// Check if the name is not empty.
	if ( !strName.empty() )
	{
		// Check if there are no unallowed characters in the name.
		if ( Check( strName ) )
		{
			// Set the name.
			m_strName = strName;
			bResult = true;
		}
	}

	return bResult;
}


//						=========================
bool					FileName::HandleExtension
//						=========================
(
	const string&		strExtension
)
{
	bool bResult = false;

	// Check if there are no unallowed characters in the extension.
	if ( Check( strExtension ) )
	{
		// Set the extension.
		m_strExtension = strExtension;
		bResult = true;
	}

	return bResult;
}


//						=====================
bool					FileName::HandleDrive
//						=====================
(
	const string&		strDrive
)
{
	bool bResult = false;

	// Check if there are no unallowed characters in the drive.
	if ( Check( strDrive ) )
	{
		// Set the drive.
		m_strDrive = strDrive;
		bResult = true;
	}

	return bResult;
}


//						===================
bool					FileName::HandleDir
//						===================
(
	const string&		strDir
)
{
	bool bResult = false;

	// Determine the directory-separator (if it hasn't been already).
	DetermineDirSeparator( strDir );

	// Check if the first character is the directory-separator.
	if ( strDir.substr( 0, 1 ) == m_strDirSep )
	{
		bResult = true;
		
		// Split the directory-string (without the starting separator)
		// into the separate directories.
		vector<string> vstrDir = StrToVector( strDir.substr(1), m_strDirSep );

		// Remove empty elements in front and back.
		vstrDir = TrimVector( vstrDir );

		// Determine if there are directories.
		if ( !vstrDir.empty() )
		{
			// Check all directories for unallowed characters, until none
			// are left or an incorrect one is found.
			vector<string>::size_type nDir = 0;
			for ( ; nDir < m_vstrDir.size() && bResult; nDir++ )
			{
				// Set the result to be the result of the name check;
				// this can be done, since it will not be overwritten once
				// it turns to false.
				bResult = Check( m_vstrDir[nDir] );
			}
		}

		// Determine if all names were found to be correct.
		if ( bResult )
		{
			// Set the vector of directories.
			m_vstrDir = vstrDir;
		}
	}

	return bResult;
}


//						===============
bool					FileName::Check
//						===============
(
	const string&		strName
)
{
	bool bResult = false;

	// Determine if none of the not-allowed characters are present
	// in the specified name.
	if ( strName.find_first_of( NOT_ALLOWED_CHARS ) == string::npos )
	{
		bResult = true;
	}

	return bResult;
}


//						===============
void					FileName::Clear()
//						===============
{
	// Clear all parts of the file name.
	m_strName.erase();
	m_strExtension.erase();
	m_strDrive.erase();
	m_vstrDir.clear();
	m_bGood = false;
}


//						===============================
bool					FileName::DetermineDirSeparator
//						===============================
(
	const string&		strInput
)
{
	bool bResult = false;

	// Determine if there is no directory separator determined as of yet.
	if ( m_strDirSep.empty() )
	{
		// Determine the used directory separator by determining which
		// out of those possible is used first in the input-string.
		string::size_type nFirstDirSep = strInput.find_first_of( DIR_SEPARATORS );
		if ( nFirstDirSep != string::npos )
		{
			m_strDirSep = strInput.substr( nFirstDirSep, 1 );
			bResult = true;
		}
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////

// Undefines
#undef DIR_SEPARATORS
#undef EXT_SEPARATOR
#undef DRIVE_SEPARATOR
#undef NOT_ALLOWED_CHARS
