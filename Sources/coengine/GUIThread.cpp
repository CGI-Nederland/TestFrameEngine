/*****************************************************************************
 * $Workfile: GUIThread.cpp $
 * $Revision: 2 $
 * $Modtime: 5/04/01 1:51p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "GUIThread.h"		// Class definition

#include <string>

using namespace std;

#include "Thread.h"				// Thread class definition
#include "EngineDebug.h"		// Engine debug facilities
#include "EngineUtil.h"			// Engine utilities

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and desctruction

GUIThread::GUIThread()
{
	// For debugging purposes
	EngineDebugOutput("GUIThread::GUIThread()", THREAD, 0);
	
	// Clear handle
	m_hModule = 0;

	// Clear function pointer
	m_fpStartGUI = 0;

	// Load module
	m_hModule = LoadLibrary("MessageCentre.dll");

	// Resolve function if module loaded correctly
	if (m_hModule != 0)
	{
		m_fpStartGUI = (INT_PCHAR) GetProcAddress(m_hModule, "emc_Start");
		m_fpStopGUI = (INT_VOID) GetProcAddress(m_hModule, "emc_Stop");
	}
}

GUIThread::~GUIThread()
{
	// For debugging purposes
	EngineDebugOutput("GUIThread::~GUIThread()", THREAD, 0);

	// Stop the thread
	Stop();

	// Free the module
	if (m_hModule != 0)
	{
		FreeLibrary(m_hModule); // orgi
		//FreeLibraryAndExitThread(m_hModule,0);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations


//						=========================
void					GUIThread::SetCommandLine
//						=========================
(
	const string&	strCommandLine
)
{
	m_strCommandLine = strCommandLine;
}


//						================
bool					GUIThread::Start()
//						================
{
	bool bResult = false;

	// For debugging purposes
	EngineDebugOutput("Start GUI", THREAD, 0);

	// Start client thread
	if (Thread::Start())
	{
		bResult = true;
	}

	return bResult;
}

//						===============
bool					GUIThread::Stop()
//						===============
{
	// Signal the client thread to stop
	Thread::Stop();

	// Wait for thread to terminate
	WaitForThreadReturn();

	return true;
}


//						================
bool					GUIThread::Reset()
//						================
{
	// For debugging purposes
	EngineDebugOutput("Resetting GUI", THREAD, 0);

	if (m_fpStopGUI != 0)
	{
		// Force the GUI to shutdown
		m_fpStopGUI();
	}
	
	return true;
}



//						==============
unsigned int			GUIThread::Run()
//						==============
{

	// For debugging purposes
	EngineDebugOutput("Launching GUI", THREAD, 0);

	if (m_fpStartGUI != 0)
	{
		char *array=new char[m_strCommandLine.length()+1];
		strcpy(array,m_strCommandLine.c_str());

		// Start GUI and block
		m_fpStartGUI(array);

		delete [] array;
	}
	
	// For debugging purposes
	EngineDebugOutput("Closing GUI", THREAD, 0);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
