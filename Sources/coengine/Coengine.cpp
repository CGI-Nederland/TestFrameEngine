/*****************************************************************************
 * $Workfile: Coengine.cpp $
 * $Revision: 43 $
 * $Modtime: 10/29/01 10:29a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifdef	UNIX
#else

	// Windows
	#define WIN32_LEAN_AND_MEAN			// Exclude rarely-used stuff from Windows headers
	#include <windows.h>				//
#endif

#include "Coengine.h"				// Definition of function calls
#include "EngineDebug.h"			// Engine debug facilities
#include "NavigationInterface.h"	// Interface of the navigation
#include "GuiInterface.h"			// Interface of GUI
#include "Command.h"				// Definition of Command

#define MAXSTRINGSIZE	4096

// Prototype private functions
void ClearStringBuffer();

// Global pointers
NavigationInterface*	g_pNavigation	= 0; 
GuiInterface*			g_pGUI			= 0;
Command*				g_pCommand		= 0;

// String output buffers
static char g_pszGetActionWordBuffer[MAXSTRINGSIZE];
static char g_pszGetActionWordFunctionBuffer[MAXSTRINGSIZE];
static char g_pszGetTestCaseBuffer[MAXSTRINGSIZE];
static char g_pszGetTestConditionBuffer[MAXSTRINGSIZE];
static char g_pszGetSectionBuffer[MAXSTRINGSIZE];
static char g_pszGetScenarioBuffer[MAXSTRINGSIZE];
static char g_pszGetClusterFileBuffer[MAXSTRINGSIZE];
static char g_pszGetCopyrightBuffer[MAXSTRINGSIZE];
static char g_pszGetVersionBuffer[MAXSTRINGSIZE];
static char g_pszGetBuildBuffer[MAXSTRINGSIZE];
static char g_pszGetLogFileBuffer[MAXSTRINGSIZE];

// Non volatile string buffer (ActionWord execution scope)
vector<string*>	g_vpstrBuffer;

#ifdef	UNIX
#else
///////////////////////////////////////////////////////////////////////////////
// Dll initialisation

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
			EngineDebugOutput("DLL_PROCESS_ATTACH", INTERFACE, 0);
			
			// Instantiate the engine
			tfe_CreateEngine();
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			EngineDebugOutput("DLL_THREAD_ATTACH", INTERFACE, 0);
			break;
		}
		case DLL_THREAD_DETACH:
		{
			EngineDebugOutput("DLL_THREAD_DETACH", INTERFACE, 0);
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			EngineDebugOutput("DLL_PROCES_DETACH", INTERFACE, 0);
			
			// Destroy the engine
			tfe_DeleteEngine();
			break;
		}
	}

	// All ok
    return TRUE;
}
#endif

//						================
extern "C" int			tfe_CreateEngine()
//						================
{
	int	nResult = 0;	// Result of tfe_CreateEngine

	EngineDebugOutput("tfe_CreateEngine", INTERFACE, 0);

	// Clear string buffer
	ClearStringBuffer();

	// We only create a new engine if there is no engine available
	if (g_pCommand == 0)
	{
		// Instantiate engine
		g_pCommand = new Command();

		// Get the navigation interface reference
		g_pNavigation = g_pCommand->GetNavigationInterface();
	
		// Get GUI interface reference
		g_pGUI = g_pCommand->GetGUInterface();

		nResult = 1;
	}

	return nResult;
}

//						================
extern "C" int			tfe_DeleteEngine()
//						================
{
	int	nResult = 0;	// Result of tfe_DeleteEngine

	EngineDebugOutput("tfe_DeleteEngine", INTERFACE, 0);
	
	// Clear string buffer
	ClearStringBuffer();

	// Only delete the engine if it exists
	if (g_pCommand != 0)
	{
		delete g_pCommand;
		g_pCommand = 0;

		nResult = 1;
	}

	return nResult;
}

//						=================
void					ClearStringBuffer()
//						=================
{
	int nElement;

	// Delete buffers
	for (nElement = 0; nElement < g_vpstrBuffer.size(); nElement++)
	{ delete g_vpstrBuffer[nElement]; }

	// Clear string buffer
	g_vpstrBuffer.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Dll exports

///////////////////////////////////////////////////////////////////////////////
// NEW INTERFACE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//						ACTION WORD REGISTRATION
///////////////////////////////////////////////////////////////////////////////

//						======================
extern "C" int			tfe_RegisterActionWord
//						======================
(
	const char*			pszActionWord, 
	const char*			pszActionWordFunction
)
{
	int nResult = 0;	// result of tfe_RegisterActionWord

	EngineDebugOutput("tfe_RegisterActionWord", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszActionWord != 0) && (pszActionWordFunction != 0) )
	{
		if (g_pNavigation->RegisterActionWord(string(pszActionWord), string(pszActionWordFunction)))
		{
			nResult = 1;
		}
	}
	return nResult;
}


//						======================
extern "C" int			tfe_RegisterHeaderWord
//						======================
(
	const char*			pszHeaderWord, 
	const char*			pszReportTag
)
{
	int nResult = 0;	// result of tfe_RegisterHeaderWord

	EngineDebugOutput("tfe_RegisterHeaderWord", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszHeaderWord != 0) && (pszReportTag != 0) )
	{
		if (g_pNavigation->RegisterHeaderWord(string(pszHeaderWord), string(pszReportTag)))
		{
			nResult = 1;
		}
	}

	return nResult;
}

//						===========================
extern "C" int			tfe_CreateActionWordSynonym
//						===========================
(
	const char*			pszActionWord,	// action word name
	const char*			pszSynonym		// synonym for action word name 
)
{
	int nResult = 0;	// result of tfe_CreateActionWordSynonym

	EngineDebugOutput("tfe_CreateActionWordSynonym", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszActionWord != 0) && (pszSynonym != 0) )
	{
		if (g_pNavigation->CreateActionWordSynonym(string(pszActionWord), string(pszSynonym)))
		{
			nResult = 1;
		}
	}

	return nResult;
}

//						========================
extern "C" int			tfe_UnregisterActionWord
//						========================
(
	const char*			pszActionWord
)
{
	int nResult = 0;	// result of tfe_UnregisterActionWord

	EngineDebugOutput("tfe_UnregisterActionWord", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszActionWord != 0 )
	{
		if (g_pNavigation->UnregisterActionWord(string(pszActionWord)))
		{
			nResult = 1;
		}
	}

	return nResult;
}

//						========================
extern "C" int			tfe_UnregisterHeaderWord
//						========================
(
	const char*				pszHeaderWord
)
{
	int nResult = 0;	// result of tfe_UnregisterHeaderWord

	EngineDebugOutput("tfe_UnregisterHeaderWord", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszHeaderWord != 0 )
	{
		if (g_pNavigation->UnregisterHeaderWord(string(pszHeaderWord)))
		{
			nResult = 1;
		}
	}
	
	return nResult;
}

//						============================
extern "C" int			tfe_UnregisterAllActionWords()
//						============================
{
	int nResult = 0;	// result of tfe_UnregisterAllActionWords

	EngineDebugOutput("tfe_UnregisterAllActionWords", INTERFACE, 0);
	nResult = g_pNavigation->UnregisterAllActionWords();

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
//						STATE CONTROL
///////////////////////////////////////////////////////////////////////////////

//						===============
extern "C" int			tfe_StartEngine
//						===============
(
	const char*			pszClusterFilename, 
	const char*			pszReportFilename, 
	const char*			pszIniFile
)
{
	int nResult = 0;	// result of operation

	EngineDebugOutput("tfe_StartEngine", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszClusterFilename != 0 ) && (pszReportFilename != 0) && (pszIniFile != 0) )
	{
		if (g_pNavigation->StartEngine(string(pszClusterFilename), string(pszReportFilename),
								string(pszIniFile)))
		{ nResult = 1; }
	}

	return nResult;
}


//						==============
extern "C" int			tfe_StopEngine()
//						==============
{
	int nResult = 1;
	EngineDebugOutput("tfe_StopEngine", INTERFACE, 0);

	// Clear string buffer
	ClearStringBuffer();

	// Stop the engine
	g_pNavigation->StopEngine();

	// always returns 1
	return nResult;
}


//						===============
extern "C" int			tfe_ResetEngine()
//						===============
{
	EngineDebugOutput("tfe_ResetEngine", INTERFACE, 0);

	// Log the reset.
	if ( g_pCommand != 0 )
	{
		g_pCommand->LogEngineReset();
	}

	// First clean up
	tfe_DeleteEngine();

	// Create a new engine
	tfe_CreateEngine();

	return (1);
}

///////////////////////////////////////////////////////////////////////////////
//						REPORT GENERATING
///////////////////////////////////////////////////////////////////////////////

//						==================
extern "C" int			tfe_GenerateReport()
//						==================
{
	EngineDebugOutput("tfe_GenerateReport", INTERFACE, 0);

	int nResult = 0;

	// Call the navigation interface
	nResult = g_pNavigation->GenerateReport();

	return nResult;
}

//						=========================
extern "C" int			tfe_GenerateReportFromLog
//						=========================
(
	const char*			pszLogFilename,
	const char*			pszReportName,
	const char*			pszIniFile
)
{
	int nResult = 0;

	EngineDebugOutput("tfe_GenerateReportFromLog", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszLogFilename != 0) && (pszReportName != 0) && (pszIniFile != 0) )
	{
		// Call the navigation interface
		nResult = g_pNavigation->GenerateReportFromLog(string(pszLogFilename),
			string(pszReportName), string(pszIniFile));
	}

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
//						TEST FLOW
///////////////////////////////////////////////////////////////////////////////

//						===================
extern "C" int			tfe_ProcessNextLine()
//						===================
{
	EngineDebugOutput("tfe_ProcessNextLine", INTERFACE, 0);

	int nResult = 0;

	// Clear string buffer
	ClearStringBuffer();
	
	// check if another line can be processed
	if (g_pNavigation->ProcessNextLine())
	{ nResult = 1; }

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
//						RUN TIME INFORMATION
///////////////////////////////////////////////////////////////////////////////

//						=================
extern "C" const char*	tfe_GetActionWord()
//						=================
{
	EngineDebugOutput("tfe_GetActionWord", INTERFACE, 0);

	string strResult = g_pNavigation->GetActionWord();

	// Copy string to output buffer
	strcpy(g_pszGetActionWordBuffer, strResult.c_str());
	
	return g_pszGetActionWordBuffer;
}


//						=========================
extern "C" const char*	tfe_GetActionWordFunction()
//						=========================
{
	EngineDebugOutput("tfe_GetActionWordFunction", INTERFACE, 0);

	// todo: rewrite g_pNavigation->Action, so no parameter is needed
	string strResult = g_pNavigation->GetActionWordFunction("");

	// Copy string to output buffer
	strcpy(g_pszGetActionWordFunctionBuffer, strResult.c_str());
	
	return g_pszGetActionWordFunctionBuffer;
}


//						===============
extern "C" const char*	tfe_GetArgument
//						===============
(
	int					nIndex
)
{
	EngineDebugOutput("tfe_GetArgument", INTERFACE, 0);

	// Indexed enginecall, so get a non volatile char pointer
	string* pstrResult = new string();

	// Store buffer into buffer container
	g_vpstrBuffer.push_back(pstrResult);

	*pstrResult = g_pNavigation->GetArgument(nIndex);
	
	return pstrResult->c_str();
}


//						================
extern "C" const char*	tfe_GetParameter
//						================
(
	int					nIndex
)
{
	EngineDebugOutput("tfe_GetParameter", INTERFACE, 0);

	// Indexed enginecall, so get a non-volatile char pointer.
	string* pstrResult = new string();

	// Store char pointer in the buffer.
	g_vpstrBuffer.push_back( pstrResult );

	*pstrResult = g_pNavigation->GetParameter( nIndex );
	
	return pstrResult->c_str();
}


//						========================
extern "C" int			tfe_GetNumberOfArguments()
//						========================
{
	EngineDebugOutput("tfe_GetNumberOfArguments", INTERFACE, 0);

	return g_pNavigation->GetNumberOfArguments();
}


//						=========================
extern "C" int			tfe_GetNumberOfParameters()
//						=========================
{
	EngineDebugOutput("tfe_GetNumberOfParameters", INTERFACE, 0);

	return g_pNavigation->GetNumberOfParameters();
}


//						===============
extern "C" const char*	tfe_GetTestCase()
//						===============
{
	EngineDebugOutput("tfe_GetTestCase", INTERFACE, 0);

	string strResult = g_pNavigation->GetTestCase();

	// Copy string to output buffer
	strcpy(g_pszGetTestCaseBuffer, strResult.c_str());
	
	return g_pszGetTestCaseBuffer;
}

//						====================
extern "C" const char*	tfe_GetTestCondition()
//						====================
{
	EngineDebugOutput("tfe_GetTestCondition", INTERFACE, 0);

	string strResult = g_pNavigation->GetTestCondition();

	// Copy string to output buffer
	strcpy(g_pszGetTestConditionBuffer, strResult.c_str());
	
	return g_pszGetTestConditionBuffer;
}

//						==============
extern "C" const char*	tfe_GetSection()
//						==============
{
	EngineDebugOutput("tfe_GetSection", INTERFACE, 0);

	string strResult = g_pNavigation->GetSection();

	// Copy string to output buffer
	strcpy(g_pszGetSectionBuffer, strResult.c_str());
	
	return g_pszGetSectionBuffer;
}

//						===============
extern "C" const char*	tfe_GetScenario()
//						===============
{
	EngineDebugOutput("tfe_GetScenario", INTERFACE, 0);

	string strResult = g_pNavigation->GetScenario();

	// Copy string to output buffer
	strcpy(g_pszGetScenarioBuffer, strResult.c_str());
	
	return g_pszGetScenarioBuffer;
}

//						==================
extern "C" const char*	tfe_GetClusterFile()
//						==================
{
	EngineDebugOutput("tfe_GetClusterFile", INTERFACE, 0);

	string strResult = g_pNavigation->GetClusterFile();

	// Copy string to output buffer
	strcpy(g_pszGetClusterFileBuffer, strResult.c_str());
	
	return g_pszGetClusterFileBuffer;
}


//						=================
extern "C" int			tfe_GetLineNumber()
//						=================
{
	EngineDebugOutput("tfe_GetLineNumber", INTERFACE, 0);

	return g_pNavigation->GetLineNumber();
}


//						=====================
extern "C" int			tfe_GetNumberOfErrors()
//						=====================
{
	EngineDebugOutput("tfe_GetNumberOfErrors", INTERFACE, 0);

	return g_pNavigation->GetNumberOfErrors();
}


//						==================
extern "C" const char*	tfe_GetLatestError()
//						==================
{
	EngineDebugOutput("tfe_GetLatestError", INTERFACE, 0);
	
	// Indexed enginecall, so get a non volatile char pointer
	string* pstrResult = new string();

	*pstrResult = g_pNavigation->GetLatestError();

	// Store buffer into buffer container
	g_vpstrBuffer.push_back(pstrResult);
	
	return pstrResult->c_str();
}


//						==========================
extern "C" const char*	tfe_GetArgumentDescription
//						==========================
(
	int					nIndex
)
{
	EngineDebugOutput("tfe_GetArgumentDescription", INTERFACE, 0);

	// Indexed enginecall, so get a non volatile char pointer
	string* pstrResult = new string();

	*pstrResult = g_pNavigation->GetArgumentDescription(nIndex); 

	// Store buffer into buffer container
	g_vpstrBuffer.push_back(pstrResult);

	return pstrResult->c_str();
}


//						===========================
extern "C" const char*	tfe_GetParameterDescription
//						===========================
(
	int					nIndex
)
{
	EngineDebugOutput("tfe_GetParameterDescription", INTERFACE, 0);

	// Indexed enginecall, so get a non volatile char pointer
	string* pstrResult = new string();

	*pstrResult = g_pNavigation->GetParameterDescription(nIndex); 

	// Store buffer into buffer container
	g_vpstrBuffer.push_back(pstrResult);

	return pstrResult->c_str();
}


//						================
extern "C" const char*	tfe_GetCopyright()
//						================
{
	EngineDebugOutput("tfe_GetCopyright", INTERFACE, 0);

	string strResult = g_pNavigation->GetCopyright();

	// Copy string to output buffer
	strcpy(g_pszGetCopyrightBuffer, strResult.c_str());
	
	return g_pszGetCopyrightBuffer;
}


//						==============
extern "C" const char*	tfe_GetVersion()
//						==============
{
	EngineDebugOutput("tfe_GetVersion", INTERFACE, 0);

	string strResult = g_pNavigation->GetVersion();

	// Copy string to output buffer
	strcpy(g_pszGetVersionBuffer, strResult.c_str());
	
	return g_pszGetVersionBuffer;
}


//						============
extern "C" const char*	tfe_GetBuild()
//						============
{
	EngineDebugOutput("tfe_GetBuild", INTERFACE, 0);

	string strResult = g_pNavigation->GetBuild();

	// Copy string to output buffer
	strcpy( g_pszGetBuildBuffer, strResult.c_str() );
	
	return g_pszGetBuildBuffer;
}


//						==============
extern "C" const char*	tfe_GetLogFile()
//						==============
{
	EngineDebugOutput("tfe_GetLogFile", INTERFACE, 0);

	string strResult = g_pNavigation->GetLogFile();

	// Copy string to output buffer
	strcpy(g_pszGetLogFileBuffer, strResult.c_str());
	
	return g_pszGetLogFileBuffer;
}

///////////////////////////////////////////////////////////////////////////////
//						REPORTING
///////////////////////////////////////////////////////////////////////////////

//						=================
extern "C" int			tfe_ReportComment
//						=================
(
	const char*				pszComment
)
{
	int nResult = 0;

	EngineDebugOutput("tfe_ReportComment", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszComment != 0 )
	{
		g_pNavigation->ReportComment(string(pszComment));
		nResult = 1;
	}

	return nResult;
}

//						===============
extern "C" int			tfe_ReportError
//						===============
(
	const char*			pszErrorText, 
	int					nErrorTypeCode
)
{
	int nResult = 0;

	EngineDebugOutput("tfe_ReportError", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszErrorText != 0 )
	{
		nResult = g_pNavigation->ReportError(string(pszErrorText), nErrorTypeCode);
	}

	return nResult;
}

//						===============
extern "C" int			tfe_ReportCheck
//						=============== 
(
	const char*			pszDescription, 
	const char*			pszExpected, 
	const char*			pszRecorded,
	int					nCheckResult /* = 1*/
)
{
	int nResult = 0;
	
	EngineDebugOutput("tfe_ReportCheck", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszDescription != 0) && (pszExpected != 0) && (pszRecorded != 0) )
	{
		nResult = g_pNavigation->ReportCheck(string(pszDescription), string(pszExpected),
										string(pszRecorded), nCheckResult);
	}

	return nResult;
}



///////////////////////////////////////////////////////////////////////////////
//						CHECKING
///////////////////////////////////////////////////////////////////////////////

//						===============
extern "C" int			tfe_CheckString
//						=============== 
(
	const char*			pszDescription, 
	const char*			pszExpected, 
	const char*			pszRecorded
)
{
	int nResult = 0;

	EngineDebugOutput("tfe_CheckString", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszDescription != 0) && (pszExpected != 0) && (pszRecorded != 0) )
	{
		if ( g_pNavigation->CheckString(string(pszDescription), string(pszExpected),
										string(pszRecorded)) )
		{ nResult = 1; }
	}

	return nResult;
}


//						=================
extern "C" int			tfe_CheckArgument
//						=================
(
	int					nIndex,			// argument index
	const char*			pszRecorded		// string to be compared with argument
)
{
	int nResult = 0;
	
	EngineDebugOutput("tfe_CheckArgument", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszRecorded != 0 )
	{
		if (g_pNavigation->CheckArgument(nIndex, string(pszRecorded), false))
		{ nResult = 1; }
	}

	return nResult;
}


//						==================
extern "C" int			tfe_CheckParameter
//						==================
(
	int					nIndex,
	const char*			pszRecorded
)
{
	int nResult = 0;
	
	EngineDebugOutput("tfe_CheckParameter", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszRecorded != 0 )
	{
		if ( g_pNavigation->CheckParameter( nIndex, string(pszRecorded) ) )
		{ nResult = 1; }
	}

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
//						Cluster Variables
///////////////////////////////////////////////////////////////////////////////

//						================
extern "C" int			tfe_KeepArgument
//						================
(
	int					nIndex,		// index number
	const char*			pszValue	// value to be kept
)
{
	int nResult = 0;

	EngineDebugOutput("tfe_KeepArgument", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszValue != 0 )
	{
		if ( g_pNavigation->KeepArgument(nIndex, string(pszValue)) )
		{ nResult = 1; }
	}

	return nResult;
}


//						=================
extern "C" int			tfe_KeepParameter
//						=================
(
	int					nIndex,
	const char*			pszValue
)
{
	int nResult = 0;

	EngineDebugOutput("tfe_KeepParameter", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszValue != 0 )
	{
		if ( g_pNavigation->KeepParameter(nIndex, string(pszValue)) )
		{ nResult = 1; }
	}

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
//						GUI
///////////////////////////////////////////////////////////////////////////////

//						==================
extern "C" int			tfe_DisplayMessage
//						==================
(
	const char*			pszMessage
)
{
	int nResult = 0;

	EngineDebugOutput("tfe_DisplayMessage", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszMessage != 0 )
	{
		g_pNavigation->DisplayMessage( string(pszMessage) );
		nResult = 1;
	}

	return nResult;	
}


///////////////////////////////////////////////////////////////////////////////
//						LICENSE
///////////////////////////////////////////////////////////////////////////////

//						================
extern "C" int			tfe_CheckLicense
//						================
(
	const char*			pszComponentName
)
{
	int nResult = 0;

	EngineDebugOutput("tfe_CheckLicense", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszComponentName != 0 )
	{
		if (g_pNavigation->CheckLicense(string(pszComponentName)))
		{ nResult = 1; }
	}

	return nResult;	
}

///////////////////////////////////////////////////////////////////////////////
// OLD INTERFACE
//
// todo: make old interface dependent upon new one as much as possible
///////////////////////////////////////////////////////////////////////////////

//						=========
extern "C" int			eng_start
//						========= 
(
	const char*			pszClusterFilename, 
	const char*			pszReportFilename, 
	const char*			pszIniFile
)
{
	EngineDebugOutput("eng_start", INTERFACE, 0);

	// redirect to new interface
	return tfe_StartEngine(pszClusterFilename, pszReportFilename, pszIniFile);
}

//						========
extern "C" int			eng_stop()
//						========
{
	EngineDebugOutput("eng_stop", INTERFACE, 0);

	// redirect to new interface
	tfe_StopEngine();
	// redirect to new interface
	tfe_GenerateReport();

	// always returns 1
	return (1);
}

//						================
extern "C" int			eng_read_setting
//						================ 
(
	char*				pszDest, 
	const char*			pszIniFile, 
	const char*			pszSection, 
	const char*			pszOption
)
{
	int nResult = 0;

	EngineDebugOutput("eng_read_setting", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszDest != 0) && (pszIniFile != 0) && (pszSection != 0) && (pszOption != 0) )
	{
		string strDest = g_pNavigation->ReadSetting(string(pszIniFile), string(pszSection), string(pszOption));

		// copy return string to destination char*
		strcpy( pszDest, strDest.c_str() );

		nResult = 1;
	}

	return nResult;
}


//						=================
extern "C" int			eng_write_setting
//						================= 
(
	const char*			pszIniFile,
	const char*			pszSection, 
	const char*			pszOption, 
	const char*			pszValue
)
{
	int nResult = 0;

	EngineDebugOutput("eng_write_setting", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszIniFile != 0) && (pszSection != 0) && (pszOption != 0) && (pszValue != 0) )
	{
		g_pNavigation->WriteSetting(string(pszIniFile), string(pszSection),
									string(pszOption), string(pszValue));
		nResult = 1;
	}

	return nResult;
}

//						===========
extern "C" int			eng_message
//						=========== 
(
	const char*			pszMessage
)
{
	EngineDebugOutput("eng_message", INTERFACE, 0);

	// redirect to new interface
	return tfe_DisplayMessage(pszMessage);
}

//						==========
extern "C" const char*	eng_action
//						==========
(
	const char*			pszName
)
{
	EngineDebugOutput("eng_action", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( pszName != 0 )
	{
		string strResult = g_pNavigation->GetActionWordFunction(string(pszName));

		// Copy string to output buffer
		strcpy( g_pszGetActionWordFunctionBuffer, strResult.c_str() );
	}
	else
	{
		// Copy empty string to output buffer
		strcpy( g_pszGetActionWordFunctionBuffer, "" );
	}

	return g_pszGetActionWordFunctionBuffer;
}

//						============
extern "C" const char*	eng_argument
//						============ 
(
	int					nIndex
)
{
	EngineDebugOutput("eng_argument", INTERFACE, 0);

	// redirect to new interface
	return tfe_GetArgument(nIndex);
}

//						==================
extern "C" int			eng_argument_count()
//						==================
{
	EngineDebugOutput("eng_argument_count", INTERFACE, 0);

	// redirect to new interface
	return tfe_GetNumberOfArguments();
}

//						==================
extern "C" int			eng_check_argument
//						================== 
(
	const char*			pszRecorded,
	int					nIndex
)
{
	int nResult = 0;	// result of operation

	EngineDebugOutput("eng_check_argument", INTERFACE, 0);
	
	// Determine if no null pointer is given as parameter.
	if ( pszRecorded != 0 )
	{
		if (g_pNavigation->CheckArgument(nIndex, string(pszRecorded), true))
		{ nResult = 1; }
	}

	return nResult;
}

//						=================
extern "C" int			eng_keep_argument
//						================= 
(
	const char*			pszValue, 
	int					nIndex
)
{
	EngineDebugOutput("eng_keep_argument", INTERFACE, 0);

	// redirect to new interface
	return tfe_KeepArgument(nIndex, pszValue);
}

//						========
extern "C" int			eng_line()
//						========
{
	EngineDebugOutput("eng_line", INTERFACE, 0);

	// redirect to new interface
	return tfe_ProcessNextLine();
}


//						==============
extern "C" int			eng_line_count()
//						==============
{
	EngineDebugOutput("eng_line_count", INTERFACE, 0);

	return g_pNavigation->LineCount();
}

//						===============
extern "C" int			eng_check_value
//						=============== 
(
	const char*			pszCheckLabel, 
	const char*			pszExpected, 
	const char*			pszRecorded
)
{
	EngineDebugOutput("eng_check_value", INTERFACE, 0);

	// redirect to new interface
	return tfe_CheckString(pszCheckLabel, pszExpected, pszRecorded);
}

//						==========
extern "C" int			eng_report
//						==========
(
	const char*			pszLabel, 
	const char*			pszMessage
)
{
	int nResult = 0;

	EngineDebugOutput("eng_report", INTERFACE, 0);

	// Determine if no null pointer is given as parameter.
	if ( (pszLabel != 0) && (pszMessage != 0) )
	{
		g_pNavigation->ReportComment(string(pszLabel) + " " + string(pszMessage));
		nResult = 1;
	}

	return nResult;
}

//						=======================
extern "C" int			eng_register_actionword
//						=======================
(
	const char*			pszActionWord, 
	const char*			pszScript
)
{
	EngineDebugOutput("eng_register_actionword", INTERFACE, 0);

	// redirect to new interface
	return tfe_RegisterActionWord(pszActionWord, pszScript);
}

//						==========
extern "C" int			eng_status()
//						==========
{
	EngineDebugOutput("eng_status", INTERFACE, 0);

	return g_pNavigation->Status();
}

//						=============
extern "C" const char*	eng_copyright()
//						=============
{
	EngineDebugOutput("eng_copyright", INTERFACE, 0);

	// redirect to new interface
	return tfe_GetCopyright();
}

//						===========
extern "C" const char*	eng_version()
//						=========== 
{
	EngineDebugOutput("eng_version", INTERFACE, 0);

	// redirect to new interface
	return tfe_GetVersion();
}

//						=========
extern "C" int			eng_error
//						=========
(
	const char*			pszMessages, 
	int					nErrorType
)
{
	EngineDebugOutput("eng_error", INTERFACE, 0);

	// redirect to new interface
	return tfe_ReportError(pszMessages, nErrorType);
}

//						=================
extern "C" int			eng_date_argument
//						=================
(
	int					nIndex
)
{
	EngineDebugOutput("eng_date_argument", INTERFACE, 0);

	g_pNavigation->DateArgument(nIndex);

	// always returns 1
	return (1);
}

//						=========================
extern "C" int			eng_unregister_actionword
//						========================= 
(
	const char*			pszActionWord
)
{
	EngineDebugOutput("eng_unregister_actionword", INTERFACE, 0);

	// redirect to new interface
	return tfe_UnregisterActionWord(pszActionWord);
}

//						=======================
extern "C" int			eng_register_headerword
//						======================= 
(
	const char*			pszHeaderWord,
	const char*			pszReportTag
)
{
	EngineDebugOutput("eng_register_headerword", INTERFACE, 0);

	// redirect to new interface
	return tfe_RegisterHeaderWord(pszHeaderWord, pszReportTag);
}

//						==================
extern "C" int			eng_create_synonym
//						==================
(
	const char*			pszActionWord,	// action word name
	const char*			pszSynonym		// synonym for action word name 
)
{
	EngineDebugOutput("eng_create_synonym", INTERFACE, 0);

	// redirect to new interface
	return 	tfe_CreateActionWordSynonym(pszActionWord, pszSynonym);
}

//						==============================
extern "C" int			eng_unregister_all_actionwords()
//						==============================
{
	EngineDebugOutput("eng_unregister_all_actionwords", INTERFACE, 0);

	// redirect to new interface
	return tfe_UnregisterAllActionWords();
}

//						==========
extern "C" const char*	eng_legend
//						==========
(
	int					nIndex
)
{
	EngineDebugOutput("eng_legend", INTERFACE, 0);

	return tfe_GetArgumentDescription(nIndex);
}

///////////////////////////////////////////////////////////////////////////////
// GUI callback functions
//
// NOTE: These functions are not exported by the .def file

//						=============
void					gui_eng_stop()
//						=============
{
	EngineDebugOutput("gui_eng_stop", INTERFACE, 0);

	g_pGUI->Stop();
}

//						==============
void					gui_eng_resume()
//						==============
{
	EngineDebugOutput("gui_eng_resume", INTERFACE, 0);

	g_pGUI->Resume();
}

//						=============
void					gui_eng_pause()
//						=============
{
	EngineDebugOutput("gui_eng_pause", INTERFACE, 0);

	g_pGUI->Pause();
}

///////////////////////////////////////////////////////////////////////////////