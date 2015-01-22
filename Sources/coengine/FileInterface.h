/*****************************************************************************
 * $Workfile: FileInterface.h $
 * $Revision: 5 $
 * $Modtime: 7/14/00 4:58p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H

#undef BASECLASS
#define BASECLASS IOInterface

// Includes
#include <string>
#include <fstream>

using namespace std;

#include "IOInterface.h"

////////////////////////////////////////////////////////////////////////////////
// class FileInterface

class FileInterface	: public BASECLASS
{

// Construction and destruction
public:
	FileInterface();				// Default constructor

	// Copy constructor

	virtual ~FileInterface(){};		// Destructor

	// Other constructors
	explicit FileInterface(const string& strFileName);


// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: Open()
	//
	// description	: Opens a filestream.
	//				  
	// parameters	: nMode		openmode, default is READ.
	//
	// returns		: TRUE		operation was succesfull.
	//				  FALSE		operation failed.
	//
	///////////////////////////////////////////////////////////////////////////////
	void Open(int nMode = IOInterface::IOREAD);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Open()
	//
	// description	: Opens a filestream.
	//				  
	//
	// parameters	: strIOSource	location and name of file.
	//				  nMode			openmode, default is READ.
	//
	// returns		: TRUE			operation was succesfull.
	//				  FALSE			operation failed.
	//
	///////////////////////////////////////////////////////////////////////////////
	void Open(const string& strIOSource, int nMode = IOInterface::IOREAD);

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsOpen()
	//
	// description	: The member function returns true if the file pointer
	//				  is not a null pointer.
	//
	// parameters	: None.
	//
	// returns		: TRUE		file pointer is not a null pointer	
	//
	///////////////////////////////////////////////////////////////////////////////
	bool IsOpen();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Close()
	//
	// description	: Closes a filestream.
	//				  
	//
	// parameters	: None.
	//
	// returns		: TRUE		operation was succesfull.
	//				  FALSE		operation failed.
	//
	///////////////////////////////////////////////////////////////////////////////
	void Close();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Read()
	//
	// description	: Reads a line from the filestream and stores 
	//				  it in the strLine parameter.
	//
	// parameters	: strLine	parameter containing the line 
	//							read from the filestream.
	//
	// returns		: TRUE		operation was succesfull.
	//				  FALSE		operation failed.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Read(string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Write()
	//
	// description	: Writes a line to the filestream.
	//				  
	// parameters	: strLine	line to be written to the filestream.
	//
	// returns		: TRUE		operation was succesfull.
	//				  FALSE		operation failed.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Write(const string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Bad()
	//
	// description	: The member function returns the state of the badbit.
	//				  
	// parameters	: None.
	//
	// returns		: TRUE		loss of integrity of the stream buffer.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Bad() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Eof()
	//
	// description	: The member function returns the state of the eofbit.
	//				  
	// parameters	: None.
	//
	// returns		: TRUE		end-of-file while extracting from a stream.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Eof() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Fail()
	//
	// description	: The member function returns the state of the failbit.
	//				  
	// parameters	: None.
	//
	// returns		: TRUE		failure to extract a valid field from a stream.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Fail() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Good()
	//
	// description	: The member function returns the state of the goodbit.
	//				  
	// parameters	: None.
	//
	// returns		: TRUE		no state bits are set	
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Good() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Copy()
	//
	// description	: The Copy function copies the content of the file specified
	//				  by strSource to the file specified by strDestiation.
	//				  			  
	// parameters	: strSource			Location and name of source file.
	//				  strDestination	Location and name of destination file.
	//
	// returns		: TRUE				Operation was succesfull.
	//
	///////////////////////////////////////////////////////////////////////////////
	static bool Copy(const string& strSource, const string& strDestination);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Exist()
	//
	// description	: The Exist function checks if the file
	//				  specified exists.
	//
	// parameters	: strSource		Location and name of file.
	//
	// returns		: TRUE			Operation was succesfull		
	//
	///////////////////////////////////////////////////////////////////////////////
	static bool Exist(const string& strSource);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Rename()
	//
	// description	: The Rename function renames the file specified by strSource
	//				  to the name given by strDestiation.
	//				  
	// parameters	: strOld		Location and old name of file.
	//				  strNew		Location and new name of file.
	//
	// returns		: TRUE			Operation was succesfull
	//
	///////////////////////////////////////////////////////////////////////////////
	static bool Rename(const string& strOld, const string& strNew);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Remove()
	//
	// description	: The Remove function deletes the file specified. 
	//				  
	// parameters	: strSource		Location and name of file.
	//
	// returns		: TRUE			Operation was succesfull	
	//
	///////////////////////////////////////////////////////////////////////////////
	static bool Remove(const string& strSource);

	// Implementation
private:

	// Class constants
private:

	// Member variables
private:
	ifstream	m_InputFileStream;		// input file stream
	ofstream	m_OutputFileStream;		// output file stream
	string		m_strFileName;			// location and name of file.
	int			m_nOpenMode;
};

////////////////////////////////////////////////////////////////////////////////

#endif // !FILEINTERFACE_H
