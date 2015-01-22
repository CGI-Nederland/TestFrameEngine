/*****************************************************************************
 * $Workfile: IOInterface.h $
 * $Revision: 9 $
 * $Modtime: 8/17/01 11:50a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef IOINTERFACE_H
#define IOINTERFACE_H

// Includes
#include <fstream>
#include <string>

using namespace std;

#include "DateTime.h"

// Defines
#define ERROR_LOG	string( "error.log" )

////////////////////////////////////////////////////////////////////////////////
// class IOInterface

class IOInterface
{

// Construction and destruction
public:
	IOInterface(){};				// Default constructor

	// Copy constructor

	virtual ~IOInterface(){};		// Destructor

	// Other constructors

// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: Open()
	//
	// description	: Opens an I/O stream.
	//				  
	// parameters	: nMode		openmode, default is READ
	//
	// returns		: TRUE		operation was succesfull
	//				  FALSE		operation failed
	//
	///////////////////////////////////////////////////////////////////////////////
	virtual void Open(int nMode = IOInterface::IOREAD) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Open()
	//
	// description	: Opens an I/O stream.
	//				  
	//
	// parameters	: strIOSource	location and name of I/O source
	//				  nMode			openmode, default is READ
	//
	// returns		: TRUE			operation was succesfull
	//				  FALSE			operation failed
	//
	///////////////////////////////////////////////////////////////////////////////
	virtual void Open(const string& strIOSource, int nMode = IOInterface::IOREAD) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsOpen()
	//
	// description	: The member function returns true if the I/O source pointer
	//				  is not a null pointer.
	//
	// parameters	: None.
	//
	// returns		: TRUE		I/O source pointer is not a null pointer	
	//
	///////////////////////////////////////////////////////////////////////////////
	virtual bool IsOpen() = 0;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Close()
	//
	// description	: Closes an I/O stream.
	//				  
	//
	// parameters	: None
	//
	// returns		: TRUE		operation was succesfull
	//				  FALSE		operation failed
	//
	///////////////////////////////////////////////////////////////////////////////
	virtual void Close() = 0;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Read()
	//
	// description	: Reads a line from the stream and stores 
	//				  it in the strLine parameter.
	//
	// parameters	: strLine	parameter containing the line read from the stream
	//
	// returns		: TRUE		operation was succesfull
	//				  FALSE		operation failed
	//
	///////////////////////////////////////////////////////////////////////////////
	virtual bool Read(string& strLine) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Write()
	//
	// description	: Writes a line to the stream.
	//				  
	// parameters	: strLine	line to be written to the stream
	//
	// returns		: TRUE		operation was succesfull
	//				  FALSE		operation failed
	//
	///////////////////////////////////////////////////////////////////////////////
	virtual bool Write(const string& strLine) = 0;

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
	virtual bool Bad() const = 0;

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
	virtual bool Eof() const = 0;

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
	virtual bool Fail() const = 0;

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
	virtual bool Good() const = 0;


	enum OPENMODE	{
						IOREAD,		// openmode read
						IOWRITE,	// openmode write
						IOAPPEND	// openmode append
					}; 

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsCountable()
	//
	// description	: Return true when the testlines can be preread
	//				  
	// parameters	: None.
	//
	// returns		: bool	
	//
	///////////////////////////////////////////////////////////////////////////////
	bool IsCountable()
	{ return m_bCountable; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: WriteIOError()
	// description	: This function writes an error to the error.log file
	//
	// parameters	: strClassName				classname where the error occurred			
	//				  strError					description of error e.g. file not found
	//				  strArguments				extra information
	//
	// returns		: <none>
	//				
	///////////////////////////////////////////////////////////////////////////////
	static void WriteIOError(const string& strClassName, const string& strError, const string& strArgument)
	{
		// Error filename
		string strFileName = ERROR_LOG;

		// Open error stream
		ofstream ofsError;
		ofsError.open(strFileName.c_str(), ios::out| ios::app);
		
		// check if error.log file is open.
		if (ofsError.is_open())
		{
			// Create a DateTime object for the current machine date and time.
			DateTime dtNow;

			// Write error
			ofsError << "Date : " << dtNow.Get( "DD-MM-YYYY" ) << "\t";
			ofsError << dtNow.Get( "hh:mm" ) << endl;
			ofsError << "Class: " << strClassName << endl;
			ofsError << "Error: " << strError << endl;
			ofsError << "Extra info: "<< strArgument << endl;
			ofsError << endl;

			// Close stream
			ofsError.close();
		}
	}

// Implementation
protected:

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetCountable()
	//
	// description	: Sets the countable property
	//				  
	// parameters	: bool				true, testlined can be preread
	//									false, testlines cannot be preread
	//				
	// returns		: <void>
	//
	///////////////////////////////////////////////////////////////////////////////
	void SetCountable(const bool bCountable)
	{ m_bCountable = bCountable; };

// Member variables
private:
	bool m_bCountable;		// preread property
};

////////////////////////////////////////////////////////////////////////////////

#undef ERROR_LOG

#endif // !IOINTERFACE_H
