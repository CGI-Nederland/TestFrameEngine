/*****************************************************************************
 * $Workfile: GuiInterface.cpp $
 * $Revision: 4 $
 * $Modtime: 17-11-99 14:57 $
 * $Author: Mn $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <string>

using namespace std;

#include "GuiInterface.h"
#include "Command.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//					==========================
					GuiInterface::GuiInterface()
//					==========================
{
}

//					==========================
					GuiInterface::GuiInterface
//					==========================
(
	Command*	pCommand
)
{
	// Initializing pointer to Command object.
	m_pCommand = pCommand;
}

// Destructor
//					===========================
					GuiInterface::~GuiInterface()
//					===========================
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//					==================
void				GuiInterface::Stop()
//					==================
{
	m_pCommand->StopASynchronous();
}

//					===================
int					GuiInterface::Pause()
//					===================
{
	return m_pCommand->Pause();
}

//					====================
int					GuiInterface::Resume()
//					====================
{
	return m_pCommand->Resume();
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

///////////////////////////////////////////////////////////////////////////////