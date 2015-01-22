/*****************************************************************************
 * $Workfile: FileInterface.cpp $
 * $Revision: 7 $
 * $Modtime: 7/14/00 5:09p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <fstream>
#include <sstream>	// used to format error strings
#include <string>
using namespace std;

#include "IOInterface.h"
#include "FileInterface.h"	// Class definition

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
FileInterface::FileInterface()
{
	// Initialise open mode
	m_nOpenMode = IOInterface::IOREAD;
}

// Copy constructor
					
// Other constructors
FileInterface::FileInterface(const string& strFileName) 

{ 
	m_nOpenMode = IOInterface::IOREAD;
	m_strFileName = string(strFileName);
	SetCountable(true);
}

// Destructor


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//					===================
void				FileInterface::Open
//					===================
(
	int nMode
)
{
	Open(m_strFileName, nMode);
}

//					===================
void				FileInterface::Open
//					===================
(
	const string& strFileName,
	int nMode
)
{
	// Store the calling parameters
	m_nOpenMode = nMode;
	m_strFileName = strFileName;

	// opens a filestream in the mode specified by m_nOpenMode
	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:
		{
			m_InputFileStream.open(strFileName.c_str(), ios::in);
			break;
		}
	case IOInterface::IOWRITE:
		{
			m_OutputFileStream.open(strFileName.c_str(), ios::out);
			break;
		}
	case IOInterface::IOAPPEND:
		{
			m_OutputFileStream.open(strFileName.c_str(), ios::out | ios::app);
			break;
		}
	default:
		{
			// error, this should not happen.
			break;
		}
	}

	// In case of errors write debug info to error.log file
	if (!IsOpen())
	{
		// formatting of the error statement.
		ostringstream ossError;
		// type of error.
		ossError << "File: " << m_strFileName << " could not be opened!" << endl;
		// 	state of the different stream flags	
		ossError << "Flagstates: " << endl;
		ossError << "goodbit: " << Good() << "\t";
		ossError << "badbit: " << Bad() << "\t";
		ossError << "eofbit: " << Eof() << "\t";
		ossError << "failbit: " << Fail();

		// Write the error statement to the error.log file
		WriteIOError(string("FileInterface"), ossError.str(), string());

	}

}

//					=====================
bool				FileInterface::IsOpen()
//					=====================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:
		{
			bResult = m_InputFileStream.is_open();
			break;
		}
	case IOInterface::IOWRITE:
		{
			bResult = m_OutputFileStream.is_open();
			break;
		}
	case IOInterface::IOAPPEND:
		{
			bResult = m_OutputFileStream.is_open();
			break;
		}
	default:
		{
			// error, this should not happen.
			break;
		}
	}

	return bResult;
}

//					====================
void				FileInterface::Close()
//					====================
{
	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:
		{
			m_InputFileStream.close();
			break;
		}
	case IOInterface::IOWRITE:
		{
			m_OutputFileStream.close();
			break;
		}
	case IOInterface::IOAPPEND:
		{
			m_OutputFileStream.close();
			break;
		}
	default:
		{
			// error, this should not happen.
			break;
		}
	}
}

//					===================
bool				FileInterface::Read
//					===================
(
	string& strLine
)
{
	bool bResult = false;

	if(m_nOpenMode == IOInterface::IOREAD)
	{
		// Check if line was read from stream.
		getline(m_InputFileStream, strLine);
		bResult = m_InputFileStream.good();
	}
	
	// In case of errors write debug info to error.log file
	if (m_InputFileStream.bad())
	{
		// formatting of the error statement.
		ostringstream ossError;
		// type of error.
		ossError << "File: " << m_strFileName << " could not be read!" << endl;
		// state of the different stream flags
		ossError << "Flagstates: " << endl;
		ossError << "goodbit: " << Good() << "\t";
		ossError << "badbit: " << Bad() << "\t";
		ossError << "eofbit: " << Eof() << "\t";
		ossError << "failbit: " << Fail();

		// Write the error statement to the error.log file
		WriteIOError(string("Class: FileInterface"), ossError.str(), string());
	}

	return bResult;
}

//					====================
bool				FileInterface::Write
//					====================
(
	const string&	strLine
)
{
	bool bResult = false;

	if ((m_nOpenMode == IOInterface::IOWRITE) || (m_nOpenMode == IOInterface::IOAPPEND))
	{
		m_OutputFileStream << strLine << flush;
		bResult = m_OutputFileStream.good();
	}

		// In case of errors write debug info to error.log file
	if (!bResult)
	{
		// formatting of the error statement.
		ostringstream ossError;
		// type of error.
		ossError << "File: " << m_strFileName << " could not be written!" << endl;
		// state of the different stream flags
		ossError << "Flagstates: " << endl;
		ossError << "goodbit: " << Good() << "\t";
		ossError << "badbit: " << Bad() << "\t";
		ossError << "eofbit: " << Eof() << "\t";
		ossError << "failbit: " << Fail();

		// Write the error statement to the error.log file
		WriteIOError(string("Class: FileInterface"), ossError.str(), string());	
	}

	return bResult;
}

//					==================
bool				FileInterface::Bad()	const
//					==================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:			// openmode READ
		{
			bResult = m_InputFileStream.bad();
			break;
		}
	case IOInterface::IOWRITE:			// openmode WRITE
		{
			bResult = m_OutputFileStream.bad();
			break;
		}
	case IOInterface::IOAPPEND:			// openmode APPEND
		{
			bResult = m_OutputFileStream.bad();
			break;
		}
	default:
		{
			// error, this should not happen.
			break;
		}
	}

	return bResult;		// returns badbit of appropriate filestream
}

//					==================
bool				FileInterface::Eof()	const
//					==================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:			// openmode READ
		{
			bResult = m_InputFileStream.eof();
			break;
		}
	case IOInterface::IOWRITE:			// openmode WRITE
		{
			bResult = m_OutputFileStream.eof();
			break;
		}
	case IOInterface::IOAPPEND:			// openmode APPEND
		{
			bResult = m_OutputFileStream.eof();
			break;
		}
	default:							// openmode READ is default
		{
			// error, this should not happen.
			break;
		}
	}

	return bResult;		// returns eofbit of appropriate filestream
}

//					===================
bool				FileInterface::Fail()	const
//					===================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:			// openmode READ
		{
			bResult = m_InputFileStream.fail();
			break;
		}
	case IOInterface::IOWRITE:			// openmode WRITE
		{
			bResult = m_OutputFileStream.fail();
			break;
		}
	case IOInterface::IOAPPEND:			// openmode APPEND
		{
			bResult = m_OutputFileStream.fail();
			break;
		}
	default:							// openmode READ is default
		{
			// error, this should not happen
			break;
		}
	}

	return bResult;		// returns failbit of appropriate filestream
}

//					===================
bool				FileInterface::Good()	const
//					===================
{
	bool bResult = false;

	switch (m_nOpenMode)
	{
	case IOInterface::IOREAD:			// openmode READ
		{
			bResult = m_InputFileStream.good();
			break;
		}
	case IOInterface::IOWRITE:			// openmode WRITE
		{
			bResult = m_OutputFileStream.good();
			break;
		}
	case IOInterface::IOAPPEND:			// openmode APPEND
		{
			bResult = m_OutputFileStream.good();
			break;
		}
	default:							// openmode READ is default
		{
			// error, this should not happen.
			break;
		}
	}

	return bResult;		// returns goodbit of appropriate filestream
}

//					===================
bool				FileInterface::Copy
//					===================
(
	const string&	strSource,
	const string&	strDestination
)
{
	bool bResult = false;
	
	// initialising and opening streams
	ifstream SourceStream(strSource.c_str());
	ofstream DestinationStream(strDestination.c_str());
	
	// Check if both streams are open.
	if (SourceStream.is_open() && DestinationStream.is_open())
	{ 
		DestinationStream << SourceStream.rdbuf();
		bResult = SourceStream.good() && DestinationStream.good();
	}

/*		// In case of errors write debug info to error.log file
	if (!bResult)
	{
		ostringstream ossError;

		ossError << "File: " << strSource << " could not be copied to file: " 
		ossError << strDestination << endl;

		if (!SourceStream.good())
		{
			ossError << "Error in source file: " << strSource << endl;
			ossError << "Flagstates: ";
			ossError << "Goodflag: " << SourceStream.good() << "\t";
			ossError << "Badflag: " << SourceStream.bad() << "\t";
			ossError << "Eofflag: :" << SourceStream.eof() << "\t";
			ossError << "Failflag: " << SourceStream.fail();
		}

		if (!DestinationStream.good())
		{
			ossError << "Error in destination file: " << strDestination << endl;
			ossError << "Flagstates: ";
			ossError << "Goodflag: " << DestinationStream.good() << "\t";
			ossError << "Badflag: " << DestinationStream.bad() << "\t";
			ossError << "Eofflag: :" << DestinationStream.eof() << "\t";
			ossError << "Failflag: " << DestinationStream.fail();
		}

		// Write the error statement to the error.log file
		IOInterface::WriteIOError(string("Class: FileInterface"), ossError.str(), string());
	}
*/
	return bResult;
}

//					====================
bool				FileInterface::Exist
//					====================
(
	const string&	strSource
)
{
	ifstream SourceStream(strSource.c_str());

	return SourceStream.good();
}

//					=====================
bool				FileInterface::Rename
//					=====================
(
	const string&	strOld,
	const string&	strNew
)
{
	bool bResult = false;

	// Check if file was renamed
	if(rename(strOld.c_str(),strNew.c_str()) == 0)
	{ bResult = true; }

/*		// In case of errors write debug info to error.log file
	if (!bResult)
	{
		ostringstream ossError;

		ossError << "ERROR!! File: " << strOld; 
		ossError << " could not be renamed to file: " << strNew;
		ossError << endl;

		// Write the error statement to the error.log file
		IOInterface::WriteIOError(string("Class: FileInterface"), ossError.str(), string());
	}
*/
	return bResult;
}

//					=====================
bool				FileInterface::Remove
//					=====================
(
	const string&	strSource
)
{
	bool bResult = false;

	// Check if file was removed
	if(remove(strSource.c_str()) == 0)
	{ bResult = true; }

/*	if (!bResult)
	{
		ostringstream ossError;

		ossError << "ERROR!! File: " << strSource; 
		ossError << " could not be removed!";
		ossError << endl;
		
		// Write the error statement to the error.log file
		IOInterface::WriteIOError(string("Class: FileInterface"), ossError.str(), string());
	}
*/
	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation


///////////////////////////////////////////////////////////////////////////////
