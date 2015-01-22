#include "windows.h"
#include "Coengine.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
//						ACTION WORD REGISTRATION
///////////////////////////////////////////////////////////////////////////////

//						==========================
int _stdcall			std_tfe_RegisterActionWord
//						==========================
(
	const char*			pszActionWord, 
	const char*			pszActionWordFunction
)
{
	return tfe_RegisterActionWord(pszActionWord, pszActionWordFunction);
}


//						==========================
int _stdcall			std_tfe_RegisterHeaderWord
//						==========================
(
	const char*			pszHeaderWord, 
	const char*			pszReportTag
)
{
	return tfe_RegisterHeaderWord(pszHeaderWord, pszReportTag);
}


//						===============================
int	_stdcall			std_tfe_CreateActionWordSynonym
//						===============================
(
	const char*			pszActionWord,	// action word name
	const char*			pszSynonym		// synonym for action word name 
)
{
	return tfe_CreateActionWordSynonym(pszActionWord, pszSynonym);
}


//						============================
int _stdcall			std_tfe_UnregisterActionWord
//						============================
(
	const char*			pszActionWord
)
{
	return tfe_UnregisterActionWord(pszActionWord);
}


//						============================
int _stdcall			std_tfe_UnregisterHeaderWord
//						============================
(
	const char*			pszHeaderWord
)
{	
	return tfe_UnregisterHeaderWord(pszHeaderWord);
}


//						================================
int	_stdcall			std_tfe_UnregisterAllActionWords()
//						================================
{
	return tfe_UnregisterAllActionWords();
}

///////////////////////////////////////////////////////////////////////////////
//						STATE CONTROL
///////////////////////////////////////////////////////////////////////////////

//						===================
int _stdcall			std_tfe_StartEngine
//						===================
(
	const char*			pszClusterFilename, 
	const char*			pszReportFilename, 
	const char*			pszIniFile
)
{
	return tfe_StartEngine(pszClusterFilename, pszReportFilename, pszIniFile);
}


//						==================
int	_stdcall			std_tfe_StopEngine()
//						==================
{
	return tfe_StopEngine();
}


//						===================
int _stdcall			std_tfe_ResetEngine()
//						===================
{	
	return tfe_ResetEngine();
}

///////////////////////////////////////////////////////////////////////////////
//						REPORT GENERATING
///////////////////////////////////////////////////////////////////////////////

//						======================
int	_stdcall			std_tfe_GenerateReport()
//						======================
{
	return tfe_GenerateReport();
}

//						=============================
int	_stdcall			std_tfe_GenerateReportFromLog
//						=============================
(
 	const char*			pszLogFilename, 
	const char*			pszReportFilename, 
	const char*			pszIniFile
)
{
	return tfe_GenerateReportFromLog(pszLogFilename, pszReportFilename, pszIniFile);
}


///////////////////////////////////////////////////////////////////////////////
//						TEST FLOW
///////////////////////////////////////////////////////////////////////////////

//						=======================
int	_stdcall			std_tfe_ProcessNextLine()
//						=======================
{
	return tfe_ProcessNextLine();
}

///////////////////////////////////////////////////////////////////////////////
//						RUN TIME INFORMATION
///////////////////////////////////////////////////////////////////////////////

//						=====================
const char*	_stdcall	std_tfe_GetActionWord()
//						=====================
{
	return tfe_GetActionWord();
}


//						=============================
const char*	_stdcall    std_tfe_GetActionWordFunction()
//						=============================
{
	return tfe_GetActionWordFunction();
}


//						===================
const char*	_stdcall	std_tfe_GetArgument
//						===================
(
	int					nIndex
)
{
	return tfe_GetArgument(nIndex);
}


//						====================
const char* _stdcall	std_tfe_GetParameter
//						====================
(
	int					nIndex
)
{
	return tfe_GetParameter(nIndex);
}


//						============================
int _stdcall			std_tfe_GetNumberOfArguments()
//						============================
{
	return tfe_GetNumberOfArguments();
}


//						=============================
int _stdcall			std_tfe_GetNumberOfParameters()
//						=============================
{
	return tfe_GetNumberOfParameters();
}


//						===================
const char*	_stdcall	std_tfe_GetTestCase()
//						===================
{	
	return tfe_GetTestCase();
}


//						====================
const char*	_stdcall	std_tfe_GetTestCondition()
//						====================
{
	return tfe_GetTestCondition();
}


//						==================
const char*	_stdcall	std_tfe_GetSection()
//						==================
{	
	return tfe_GetSection();
}


//						===================
const char*	_stdcall	std_tfe_GetScenario()
//						===================
{
	return tfe_GetScenario();
}


//						======================
const char*	_stdcall	std_tfe_GetClusterFile()
//						======================
{
	return tfe_GetClusterFile();
}


//						=====================
int	_stdcall			std_tfe_GetLineNumber()
//						=====================
{
	return tfe_GetLineNumber();
}


//						=========================
int	_stdcall			std_tfe_GetNumberOfErrors()
//						=========================
{
	return tfe_GetNumberOfErrors();
}


//						======================
const char*	_stdcall	std_tfe_GetLatestError()
//						======================
{
	return tfe_GetLatestError();
}


//						==============================
const char*	_stdcall	std_tfe_GetArgumentDescription
//						==============================
(
	int					nIndex
)
{
	return tfe_GetArgumentDescription(nIndex);
}


//						===============================
const char* _stdcall	std_tfe_GetParameterDescription
//						===============================
(
	int					nIndex
)
{
	return tfe_GetParameterDescription(nIndex);
}


//						====================
const char*	_stdcall	std_tfe_GetCopyright()
//						====================
{
	return tfe_GetCopyright();
}


//						==================
const char*	_stdcall	std_tfe_GetVersion()
//						==================
{
	return tfe_GetVersion();
}


//						================
const char* _stdcall	std_tfe_GetBuild()
//						================
{
	return tfe_GetBuild();
}


//						==================
const char* _stdcall	std_tfe_GetLogFile()
//						==================
{
	return tfe_GetLogFile();
}

///////////////////////////////////////////////////////////////////////////////
//						REPORTING
///////////////////////////////////////////////////////////////////////////////

//						=====================
int _stdcall			std_tfe_ReportComment
//						=====================
(
	const char*				pszComment
)
{
	return tfe_ReportComment(pszComment);
}


//						===================
int _stdcall			std_tfe_ReportError
//						===================
(
	const char*			pszErrorText, 
	int					nErrorTypeCode
)
{
	return tfe_ReportError(pszErrorText, nErrorTypeCode);
}


//						===================
int _stdcall			std_tfe_ReportCheck
//						=================== 
(
	const char*			pszDescription, 
	const char*			pszExpected, 
	const char*			pszRecorded,
	int					nCheckResult
)
{
	return tfe_ReportCheck(pszDescription, pszExpected, pszRecorded, nCheckResult);
}


///////////////////////////////////////////////////////////////////////////////
//						CHECKING
///////////////////////////////////////////////////////////////////////////////

//						===================
int _stdcall			std_tfe_CheckString
//						=================== 
(
	const char*			pszDescription, 
	const char*			pszExpected, 
	const char*			pszRecorded
)
{
	return tfe_CheckString(pszDescription, pszExpected, pszRecorded);
}


//						=====================
int _stdcall			std_tfe_CheckArgument
//						=====================
(
	int					nIndex,			// argument index
	const char*			pszRecorded		// string to be compared with argument
)
{
	return tfe_CheckArgument(nIndex, pszRecorded);
}


//						======================
int _stdcall			std_tfe_CheckParameter
//						======================
(
	int					nIndex,
	const char*			pszRecorded
)
{
	return tfe_CheckParameter(nIndex, pszRecorded);
}

///////////////////////////////////////////////////////////////////////////////
//						Cluster Variables
///////////////////////////////////////////////////////////////////////////////

//						====================
int	_stdcall			std_tfe_KeepArgument
//						====================
(
	int					nIndex,		// index number
	const char*			pszValue	// value to be kept
)
{
	return tfe_KeepArgument(nIndex, pszValue);
}


//						=====================
int _stdcall			std_tfe_KeepParameter
//						=====================
(
	int					nIndex,
	const char*			pszValue
)
{
	return tfe_KeepParameter(nIndex, pszValue);
}

///////////////////////////////////////////////////////////////////////////////
//						GUI
///////////////////////////////////////////////////////////////////////////////

//						======================
int _stdcall 			std_tfe_DisplayMessage
//						======================
(
	const char*			pszMessage
)
{
	return tfe_DisplayMessage(pszMessage);
}

// char* to BSTR
BSTR _stdcall std_ChartoBSTR(char* string)
{
	int a = lstrlenA(string);
	BSTR unicodestr = SysAllocStringLen(NULL, a);
	::MultiByteToWideChar(CP_ACP, 0, string, a, unicodestr, a);
	return unicodestr;
}
