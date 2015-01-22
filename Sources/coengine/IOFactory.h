/*****************************************************************************
 * $Workfile: IOFactory.h $
 * $Revision: 4 $
 * $Modtime: 4/21/00 1:14a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef IOFACTORY_H
#define IOFACTORY_H

// Includes
#include <string>
using namespace std;

class IOInterface;

////////////////////////////////////////////////////////////////////////////////
// class IOFactory

class IOFactory
{

// Construction and destruction
public:
	IOFactory(){};			// Default constructor

	// Copy constructor

	~IOFactory(){};			// Destructor

	// Other constructors

// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: CreateIOInterface()
	//
	// description	: Creates an I/O Interface object, specified
	//				  by strIOSource, and returns a pointer to this object.
	//
	// parameters	: strIOSource	location and name of I/O source
	//
	// returns		: IOInterface*
	//
	///////////////////////////////////////////////////////////////////////////////
	IOInterface* CreateIOInterface(const string& strIOSource);

	///////////////////////////////////////////////////////////////////////////////
	// function		: DestroyIOInterface()
	//
	// description	: Destroys the I/O Interface object specified
	//				  by the pointer pIOI.
	//
	// parameters	: pIOI		pointer to an I/O Interface object
	//
	// returns		: void
	//
	///////////////////////////////////////////////////////////////////////////////
	void DestroyIOInterface(IOInterface* pIOI);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Copy()
	//
	// description	: The Copy function copies the content of the I/O source specified
	//				  by strSource to the I/O source specified by strDestiation.
	//				  			  
	// parameters	: strSource			Location and name of source.
	//				  strDestination	Location and name of destination.
	//
	// returns		: TRUE				Operation was succesfull.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Copy(const string& strSource, const string& strDestination) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Exist()
	//
	// description	: The Exist function checks if the I/O source
	//				  specified exists.
	//
	// parameters	: strSource		Location and name of I/O source.
	//
	// returns		: TRUE			Operation was succesfull		
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Exist(const string& strSource) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Rename()
	//
	// description	: The Rename function renames the I/O source specified by strSource
	//				  to the name given by strDestiation.
	//				  
	// parameters	: strOld		Location and old name of I/O source.
	//				  strNew		Location and new name of I/O source.
	//
	// returns		: TRUE			Operation was succesfull
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Rename(const string& strOld, const string& strNew) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Remove()
	//
	// description	: The Remove function deletes the I/O source specified. 
	//				  
	// parameters	: strSource		Location and name of I/O source.
	//
	// returns		: TRUE			Operation was succesfull	
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Remove(const string& strSource) const;

	// Implementation
private:

	// Class constants
private:
	enum PROTOCOL { IO_TMSP, IO_FILE };

	// Member variables
private:

};

////////////////////////////////////////////////////////////////////////////////

#endif // !IOFACTORY_H
