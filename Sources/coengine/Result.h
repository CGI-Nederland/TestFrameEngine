/*****************************************************************************
 * $Workfile: Result.h $
 * $Revision: 17 $
 * $Modtime: 6/18/01 5:12p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef RESULT_H
#define RESULT_H

#include <string>			// Needed for string handling

using namespace std;

// Forward declarations
class IOInterface;

// Defines
#define	DELIMITER	string("\t")
#define WRITE	1				// mode of opening
#define READ	2
#define CREATE	1
#define CHANGE	2
#define REMOVE	3

////////////////////////////////////////////////////////////////////////////////
// class Result { abstract }
class Result //: public I/O_interface, public File_interface  
{

	// Construction and destruction
public:
	Result()	:	m_pIOInterface(0){};

	///////////////////////////////////////////////////////////////////////////////
	// destructor of Result
	///////////////////////////////////////////////////////////////////////////////
	virtual ~Result();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Read()
	// description	: Reads a line from the input medium
	//
	// parameters	: strLine	Input variable for the line that is read
	//
	// returns		:	true	Line read successfully
	//					false	Line could not be read
	///////////////////////////////////////////////////////////////////////////////
	bool Read(string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Write()
	// description	: Writes a line to the output medium
	//
	// parameters	: strLine is the string to write in the output medium
	//
	// returns		:	true	Line written to the medium successfully
	//					false	Line could not be written
	///////////////////////////////////////////////////////////////////////////////
	bool Write(const string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Open()
	// description	: Open the medium in the specified mode (read or write)
	//
	// parameters	: strFilename is the name of the medium
	//				  nMode is the mode of opening read or write
	//
	// returns		:	true	Medium opened successfully
	//					false	Medium could not be opened
	///////////////////////////////////////////////////////////////////////////////
	bool Open(const string& strFilename, int nMode);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Close()
	// description	: Close the opened medium
	//
	// parameters	: <void>
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void Close(void);

	///////////////////////////////////////////////////////////////////////////////
	// function		: FileExists()
	// description	: Check if the file aleady exists
	//
	// parameters	: strFilenName is the name of the file to be checked.
	//
	// returns		:	true	File exists
	//					false	File does not exist
	///////////////////////////////////////////////////////////////////////////////
	bool FileExists(const string& strFileName);

protected:
	IOInterface* m_pIOInterface;	// file pointer for i/o handling
};

#endif // !RESULT_H
