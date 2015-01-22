/*****************************************************************************
 * $Workfile: MessageCentre.cpp $
 * $Revision: 1 $
 * $Modtime: 21/11/05 16:38 $
 * $Author: MdJ $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2007 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "CommandLine.h"				// CommandLine
#include "EngineInterface.h"			// EngineInterface
#include "EngineCallbackHandler.h"		// EngineCallbackHandler
#include "EngineDebug.h"				// Engine debug facilities
#include "TcpIpConnection.h"			// TcpIpConnection

/////////////////////////////////////////////////////////////////////////////
// Global variables

// Client, Interface and handler
TcpIpConnection* g_pClient;
EngineInterface* g_pEngine;
EngineCallBackHandler* g_pHandler;

/////////////////////////////////////////////////////////////////////////////
// Exports
//						========
extern "C" int			emc_Stop()
//						========
{
	EngineDebugOutput("emc_Stop", CORE, 0);

	///////////////////////////////////////////////////////////////////////////
	// Notify deactivation
//	g_pClient->Stop();

	g_pClient->Post();

	///////////////////////////////////////////////////////////////////////////
	// Free allocated memory

	delete g_pEngine;
	delete g_pClient;
	delete g_pHandler;

	g_pEngine=0;
	g_pClient=0;
	g_pHandler=0;

	EngineDebugOutput("GUI client exits", CORE, 0);

	// Return result
	return true;
}

//						=========
extern "C" int			emc_Start
//						=========
( 
    const char *lpCmdLine 
)
{
	EngineDebugOutput("GUI client starts", CORE, 0);

	///////////////////////////////////////////////////////////////////////////
	// Initialise variables

	// Result to return
	bool bResult = false;
	
	// Name of the engine host
	string strHostName;
	
	// Port number for the GUI protocol
	unsigned short nPortNumber = 0;

	// Client, Interface and handler
	g_pClient = 0;
	g_pEngine = 0;
	g_pHandler = 0;

	///////////////////////////////////////////////////////////////////////////
	// Parse the command line

	CommandLine cmd(lpCmdLine);
	if (!cmd.GetString("-h", strHostName) || !cmd.GetInteger("-p", nPortNumber))
	{
		// One of them was not defined, use defaults instead
		EngineDebugOutput("GUI client: Using default command line parameters", CORE, 0);

		strHostName = "localhost";
		nPortNumber = 4000;
	}

	///////////////////////////////////////////////////////////////////////////
	// Create user interface and tcpip client

	g_pClient = new TcpIpConnection();

	if (g_pClient != 0)
	{ 
		g_pEngine = new EngineInterface(g_pClient);
	}
	if (g_pEngine != 0)
	{ 
		g_pHandler = new EngineCallBackHandler(g_pEngine); 
	}

	// Set host, port and handler
	if ((g_pClient != 0) && (g_pHandler != 0))
	{
		g_pClient->SetHost(strHostName);
		g_pClient->SetPortNumber(nPortNumber);
		g_pClient->SetCallbackHandler(g_pHandler);

		// Open the connection
		g_pClient->Open();

		// Start listening to tcp/ip port
		bResult = g_pClient->Start();

		// Register GUI at the engine
		g_pEngine->Register();
	}	
	
	///////////////////////////////////////////////////////////////////////////
	// Wait while the GUI is working

	if (bResult)
	{
		while (g_pHandler->Active())
		{ 
			Sleep(1000); 
		}

		// Stop listening
		g_pClient->Stop();
	}

	// Return result
	return static_cast<int>(bResult);
}
	
//						=======
BOOL APIENTRY			DllMain
//						=======
(
 HANDLE					hModule,			// Handle to DLL module
 DWORD					ul_reason_for_call,	// Reason for calling function
 LPVOID					lpReserved			// Reserved
)
{
	// Check reason for calling

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			EngineDebugOutput("DLL_PROCESS_ATTACH", CORE, 0);
					
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			EngineDebugOutput("DLL_THREAD_ATTACH", CORE, 0);
			break;
		}
		case DLL_THREAD_DETACH:
		{
			EngineDebugOutput("DLL_THREAD_DETACH", CORE, 0);
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			EngineDebugOutput("DLL_PROCES_DETACH", CORE, 0);
			emc_Stop();		
			break;
		}
	}

	// All ok
    return TRUE;
}
	