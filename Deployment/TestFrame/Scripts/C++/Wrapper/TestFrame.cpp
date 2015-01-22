/*****************************************************************************
 * $Workfile: TestFrame.cpp $
 * $Revision: 6 $
 * $Modtime: 14-05-01 14:04 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2007 LogicaCMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "TestFrame.h"			// Function prototypes

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include "Coengine.h"			// Engine exports
#include "IniFile.h"			// Class IniFile
#include "NapiWrapper.h"		// Wrapper NAPI calls

///////////////////////////////////////////////////////////////////////////////

//						=======
int APIENTRY			WinMain
//						=======
(
	HINSTANCE			hInstance,
    HINSTANCE			hPrevInstance,
    LPSTR				lpCmdLine,
    int					nCmdShow
)
{
	string strCluster, strReport, strIniFile, strLibrary;

	// Process the inifile supplied on the command line
	if (ProcessIniFile(lpCmdLine, strCluster, strReport, strIniFile, strLibrary))
	{
		// Load NAPI libraries
		if (LoadLibraries(strLibrary))
		{
			// Process the cluster
			ProcessCluster(strCluster, strReport, strIniFile);
		}
		
		// Free NAPI libraries
		FreeLibraries(strLibrary);
	}	

	return 0;
}

///////////////////////////////////////////////////////////////////////////////

//								==============
bool							ProcessCluster
//								==============
(
	const string&				strClusterFile,		// Cluster file
	const string&				strReportFile,		// Report file
	const string&				strIniFile			// Engine ini file
)
{
	// Start the engine
	if (tfe_StartEngine(strClusterFile.c_str(), strReportFile.c_str(), strIniFile.c_str()) != 1)
	{
		// An error occurred so warn the user
		ShowErrorMessage("TestFrame ConTest Engine could not be started. Please check the error log.");

		// Return unsuccessful result
		return false;
	}

	// Process each test line as long as there are lines left
	while (tfe_ProcessNextLine() == 1) 
	{ 	
		// Execute the action word that was found through the NAPI
		if (napi_ExecuteActionWord(tfe_GetActionWord()) != 1)
		{
			// System error; stop engine
			tfe_StopEngine();

			// Warn the user
			ShowErrorMessage("Error occurred during the processing of a cluster. TestFrame ConTest Engine stopped. Please check the error log.");

			// Return unsuccessful result
			return false;
		}
	}

	// Stop the engine and generate the report
	tfe_StopEngine();
	tfe_GenerateReport();

	// Return successful result
	return true;
}

//						==============
bool					ProcessIniFile
//						==============
(
	const string&		strFileName,
	string&				strCluster,
	string&				strReport,
	string&				strIniFile,
	string&				strLibrary
)
{
	IniFile file;

	// Open the inifile
	bool bResult = file.Import(strFileName);

	if (bResult)
	{
		// Fill the variables
		strCluster = file.Get("TestFrame", "Cluster");
		strReport =	 file.Get("TestFrame", "Report");
		strIniFile = file.Get("TestFrame", "IniFile");
		strLibrary = file.Get("TestFrame", "Library");
	}
	else
	{
		// Error opening inifile
		ShowErrorMessage("Could not open the specified inifile.");
	}

	return bResult;
}


//						=============
bool					LoadLibraries
//						=============
(
	const string&		strLibraryNames
)
{
	bool bResult = false;

	if (!strLibraryNames.empty())
	{
		int nSemiColon = strLibraryNames.find(';');

		if (nSemiColon == string::npos)
		{
			// Only one library name supplied
			bResult = (napi_LoadLibrary(strLibraryNames.c_str()) == 1);
		}
		else
		{
			// More than one library name supplied so split
			string strLeft = strLibraryNames.substr(0, nSemiColon);
			string strRight = strLibraryNames.substr(nSemiColon+1, string::npos);

			// Load the library
			bResult = (napi_LoadLibrary(strLeft.c_str()) == 1);

			// Process the rest of the string if necessary
			if (!strRight.empty())
			{ bResult = bResult && LoadLibraries(strRight); }
		}
	}

	if (!bResult)
	{
		// Show the user a warning
		string strErrorMessage = string("Error loading libraries: ") + strLibraryNames;
		ShowErrorMessage(strErrorMessage);
	}

	return bResult;
}

//						=============
bool					FreeLibraries
//						=============
(
	const string&		strLibraryNames
)
{
	bool bResult = false;

	if (!strLibraryNames.empty())
	{
		int nSemiColon = strLibraryNames.find(';');

		if (nSemiColon == string::npos)
		{
			// Only one library name supplied
			bResult = (napi_FreeLibrary(strLibraryNames.c_str()) == 1);
		}
		else
		{
			// More than one library name supplied so split
			string strLeft = strLibraryNames.substr(0, nSemiColon);
			string strRight = strLibraryNames.substr(nSemiColon+1, string::npos);

			// Free the library
			bResult = (napi_FreeLibrary(strLeft.c_str()) == 1);

			// Process the rest of the string if necessary
			if (!strRight.empty())
			{ bResult = bResult && FreeLibraries(strRight); }
		}
	}

	return bResult;
}

//						================
bool					ShowErrorMessage
//						================
(
	const string&		strError
)
{
	bool bResult = false;

	// Show a message box with a stop sign icon and an 'Ok' button
	if (MessageBox(0, strError.c_str() , "TestFrame", (MB_OK | MB_ICONERROR)) != 0)
	{
		// Message was shown successfully
		bResult = true;
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
