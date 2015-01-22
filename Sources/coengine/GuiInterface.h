/*****************************************************************************
 * $Workfile: GuiInterface.h $
 * $Revision: 3 $
 * $Modtime: 17-11-99 14:55 $
 * $Author: Mn $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

// Includes
#include <string>

// Forward declarations
class Command;

////////////////////////////////////////////////////////////////////////////////
// class Command

class GuiInterface
{
	// Construction and destruction
public:
	GuiInterface();							// Constructor

private:
	GuiInterface(const GuiInterface& right);	// Copy contructor

	// Other constructors
public:
	explicit GuiInterface(Command* pCommand);

	~GuiInterface();							// Destructor

	// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		: Stop()
	//
	// description	: 
	//				  	
	// parameters	: None.
	//
	// returns		: void
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Stop();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Pause()
	//
	// description	: 
	//				  	
	// parameters	: None.
	//
	// returns		: integer
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int Pause();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Resume()
	//
	// description	: 
	//				  	
	// parameters	: None.
	//
	// returns		: integer
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int Resume();

	// Implementation
private:

	// Class constants
public:

	// Member variables
private:
	Command*	m_pCommand; // Pointer to Command object
};

////////////////////////////////////////////////////////////////////////////////

#endif // !GUIIINTERFACE_H