/*****************************************************************************
 * $Workfile: enginegui.cpp $
 * $Revision: 8 $
 * $Modtime: 6/22/00 11:25a $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "CommandLine.h"				// CommandLine
#include "EngineInterface.h"			// EngineInterface
#include "EngineCallbackHandler.h"		// EngineCallbackHandler
#include "EngineDebug.h"				// Engine debug facilities
#include "TcpIpConnection.h"			// TcpIpConnection

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
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
	TcpIpConnection* pClient = 0;
	EngineInterface* pEngine = 0;
	EngineCallBackHandler* pHandler = 0;

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

	pClient = new TcpIpConnection();
	if (pClient != 0)
	{ pEngine = new EngineInterface(pClient); }
	if (pEngine != 0)
	{ pHandler = new EngineCallBackHandler(pEngine); }


	// Set host, port and handler
	if ((pClient != 0) && (pHandler != 0))
	{
		pClient->SetHost(strHostName);
		pClient->SetPortNumber(nPortNumber);
		pClient->SetCallbackHandler(pHandler);

		// Open the connection
		pClient->Open();

		// Start listening to tcp/ip port
		bResult = pClient->Start();

		// Register GUI at the engine
		pEngine->Register();
	}	
	
	///////////////////////////////////////////////////////////////////////////
	// Wait while the GUI is working
	
	if (bResult)
	{
		while (pHandler->Active())
		{ 
			Sleep(1000); 
		}

		// Stop listening
		pClient->Stop();
	}

	///////////////////////////////////////////////////////////////////////////
	// Free allocated memory

	delete pEngine;
	delete pClient;
	delete pHandler;

	pEngine=0;
	pClient=0;
	pHandler=0;

	EngineDebugOutput("GUI client exits", CORE, 0);

	// Return result
	return static_cast<int>(bResult);
}
///////////////////////////////////////////////////////////////////////////////

