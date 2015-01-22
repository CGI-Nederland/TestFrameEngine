/*****************************************************************************
 * $Workfile: Coengine.h $
 * $Revision: 33 $
 * $Modtime: 10/23/01 10:33a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef COENGINE_H
#define COENGINE_H

///////////////////////////////////////////////////////////////////////////////
// Definition of error codes

#define TFE_WARNING 0
#define TFE_ERROR	1
#define TFE_CHECK	2
#define	TFE_FATAL	3

///////////////////////////////////////////////////////////////////////////////
// C++ Specifics

#ifdef __cplusplus
	extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
//	TESTFRAME ENGINE 5.5 INTERFACE FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

//  ENGINE CONSTRUCTION AND DESTRUCTION UNIX USE ONLY
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_CreateEngine()
// description	: Constructs the engine. UNIX ONLY !
//
// parameters	: -
//
// returns		: 1		engine successfully created
//				  0		engine could not be created, another instance exist
///////////////////////////////////////////////////////////////////////////////
int tfe_CreateEngine();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_DeleteEngine()
// description	: Destructs the engine. UNIX ONLY !
//
// parameters	: -
//
// returns		: 1		engine successfully deleted
//				  0		engine could not be deleted, no instance was created
///////////////////////////////////////////////////////////////////////////////
int tfe_DeleteEngine();


//	ACTION WORD REGISTRATION
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_RegisterActionWord
// description	: This function registers an action word with its associated
//				  function.
//
// parameters	: pszActionWord				name of action word
//				  pszActionWordFunction		name of associated function
//
// returns		: 1		action word successfully registered
//				  0		action word could not be registered
///////////////////////////////////////////////////////////////////////////////
int tfe_RegisterActionWord(const char* pszActionWord, 
						   const char* pszActionWordFunction);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_RegisterHeaderWord
// description	: This function registers a header word with its associated
//				  report tag.
//
// parameters	: pszHeaderWord		name of header word
//				  pszReportTag		tag to be placed in the report when the
//										header word is encountered in a cluster
//
// returns		: 1		header word successfully registered
//				  0		header word could not be registered
///////////////////////////////////////////////////////////////////////////////
int tfe_RegisterHeaderWord(const char* pszHeaderWord, 
						   const char* pszReportTag);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_CreateActionWordSynonym
// description	: This function creates a synonym for an action word.
//
// parameters	: pszActionWord		name of action word
//				  pszSynonym		name of synonym
//
// returns		: 1		synonym successfully created
//				  0		synonym could not be created
///////////////////////////////////////////////////////////////////////////////
int tfe_CreateActionWordSynonym(const char* pszActionWord, 
								const char* pszSynonym);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_UnregisterActionWord
// description	: This function unregisters a user defined action word.
//
// parameters	: pszActionWord		name of action word
//
// returns		: 1		action word successfully unregistered
//				  0		action word could not be unregistered
///////////////////////////////////////////////////////////////////////////////
int tfe_UnregisterActionWord(const char* pszActionWord);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_UnregisterHeaderWord
// description	: This function unregisters a user defined header word.
//
// parameters	: pszHeaderWord		name of header word
//
// returns		: 1		header word successfully unregistered
//				  0		header word could not be unregistered
///////////////////////////////////////////////////////////////////////////////
int tfe_UnregisterHeaderWord(const char* pszHeaderWord);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_UnregisterAllActionWords
// description	: This function unregisters all user defined action and header
//				  word.
//
// parameters	: -
//
// returns		: 1		action words successfully unregistered
//				  0		action words could not be unregistered
///////////////////////////////////////////////////////////////////////////////
int tfe_UnregisterAllActionWords();


//	STATE CONTROL
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_StartEngine
// description	: This function starts the engine processing a cluster.
//
// parameters	: pszClusterFilename	name of cluster file
//				  pszReportFilename		name of report file
//				  pszIniFile			name of engine ini file
//
// returns		: 1		engine successfully started
//				  0		engine could not be started
///////////////////////////////////////////////////////////////////////////////
int tfe_StartEngine(const char* pszClusterFilename, 
					const char* pszReportFilename,
					const char* pszIniFile);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_StopEngine
// description	: This function stops the engine processing the cluster it's 
//				  busy with and clears all information that was entered via
//				  this cluster.
//
// parameters	: -
//
// returns		: 1		engine successfully stopped
//				  0		engine could not be stopped
///////////////////////////////////////////////////////////////////////////////
int tfe_StopEngine();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_ResetEngine
// description	: This function resets the engine, which means all information
//				  is deleted (not only externally entered information.) The
//				  result is that the engine is returned to the state after the
//				  first process attach.
//
// parameters	: -
//
// returns		: 1		engine successfully reset
//				  0		engine could not be reset
///////////////////////////////////////////////////////////////////////////////
int tfe_ResetEngine();

//	REPORT GENERATING
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GenerateReport
// description	: This function generates the report for the last processed 
//				  cluster.
//
// parameters	: -
//
// returns		: 1		report successfully generated
//				  0		report could not be generated
///////////////////////////////////////////////////////////////////////////////
int tfe_GenerateReport();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GenerateReportFromLog
// description	: This function generates the report for the given log file
//				  using 
//
// parameters	: pszLogFilename		Name of the logfile to process
//				  pszReportName			Name of the report file to create
//				  pszIniFile			Name of the inifile to use
//
// returns		: 1		report successfully generated
//				  0		report could not be generated
///////////////////////////////////////////////////////////////////////////////
int tfe_GenerateReportFromLog(const char* pszLogFilename, 
							  const char* pszReportName, 
							  const char* pszIniFile);

//	TEST FLOW
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_ProcessNextLine
// description	: This function processes the next test line with a registered, 
//				  user defined action word.
//
// parameters	: -
//
// returns		: 1		next valid test line found
//				  0		no next valid test line found
///////////////////////////////////////////////////////////////////////////////
int tfe_ProcessNextLine();


//	RUN TIME INFORMATION
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetActionWord
// description	: This function returns the name of the action word of the 
//				  current test line.
//
// parameters	: -
//
// returns		: name of the action word of the current test line
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetActionWord();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetActionWordFunction
// description	: This function returns the name of the action word function 
//				  associated with the action word of the current test line.
//
// parameters	: -
//
// returns		: name of the action word function of the current test line
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetActionWordFunction();
	
///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetArgument
// description	: This function returns the argument with the specified index 
//				  from the current test line's argument list.
//
// parameters	: nIndex	index of argument list
//
// returns		: specified argument from the current test line's argument list
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetArgument(int nIndex);
	
///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetParameter
// description	: This function returns the value of the parameter with the
//				  specified index after the action word from the current test
//				  line.
//
// parameters	: nIndex	parameter index
//
// returns		: specified parameter's value
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetParameter(int nIndex);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetNumberOfArguments
// description	: This function returns the number of arguments from the
//				  current test line.
//
// parameters	: -
//
// returns		: number of arguments
///////////////////////////////////////////////////////////////////////////////
int tfe_GetNumberOfArguments();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetNumberOfParameters
// description	: This function returns the number of parameters of the current
//				  action word.
//
// parameters	: -
//
// returns		: number of parameters
///////////////////////////////////////////////////////////////////////////////
int tfe_GetNumberOfParameters();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetTestCase
// description	: This function returns the description of the current test 
//				  case.
//
// parameters	: -
//
// returns		: description of the current test case
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetTestCase();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetTestCondition
// description	: This function returns the description of the current test 
//				  condition.
//
// parameters	: -
//
// returns		: description of the current test condition
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetTestCondition();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetSection
// description	: This function returns the description of the current section.
//
// parameters	: -
//
// returns		: decsription of the current section
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetSection();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetScenario
// description	: This function returns the description of the current 
//				  scenario.
//
// parameters	: -
//
// returns		: description of the current scenario
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetScenario();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetClusterFile
// description	: This function returns the name and path of the current
//				  cluster file.
//
// parameters	: -
//
// returns		: name and path of the current cluster file
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetClusterFile();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetLineNumber
// description	: This function returns the current line number.
//
// parameters	: -
//
// returns		: current line number
///////////////////////////////////////////////////////////////////////////////
int tfe_GetLineNumber();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetNumberOfErrors
// description	: This function returns the number of errors found since the 
//				  engine was started.
//
// parameters	: -
//
// returns		: number of errors found as of yet
///////////////////////////////////////////////////////////////////////////////
int tfe_GetNumberOfErrors();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetLatestError
// description	: This function returns the text of the latest error.
//
// parameters	: -
//
// returns		: text of the latest error
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetLatestError();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetArgumentDescription
// description	: This function returns the description of the argument with 
//				  the specified index.
//
// parameters	: nIndex	index of argument description list
//
// returns		: specified argument's description
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetArgumentDescription(int nIndex);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetParameterDescription
// description	: This function returns the description of the specified
//				  parameter.
//
// parameters	: nIndex	parameter index
//
// returns		: specified parameter's description
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetParameterDescription(int nIndex);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetCopyright
// description	: This function returns the copyright information.
//
// parameters	: -
//
// returns		: copyright information
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetCopyright();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetVersion
// description	: This function returns the version.
//
// parameters	: -
//
// returns		: version string
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetVersion();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetBuild
// description	: This function returns the build number.
//
// parameters	: -
//
// returns		: build number string
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetBuild();

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_GetLogFile
// description	: This function returns the name and path of the current
//				  log file.
//
// parameters	: -
//
// returns		: name and path of the current log file
///////////////////////////////////////////////////////////////////////////////
const char* tfe_GetLogFile();

//	REPORTING
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_ReportComment
// description	: This function sends a string to the log to be written in the
//				  report as comment.
//
// parameters	: pszComment	text to be written in the report as comment
//
// returns		: 1		text successfully written in log
//				  0		text could not be written in log
///////////////////////////////////////////////////////////////////////////////
int tfe_ReportComment(const char* pszComment);
	
///////////////////////////////////////////////////////////////////////////////
// function		: tfe_ReportError
// description	: This function sends a string to the log to be written in 
//				  report as an error.
//
// parameters	: pszErrorText		text to be written in report as error
//				  nErrorTypeCode	error type code
//
// returns		: 1		text successfully written in log
//				  0		text could not be written in log
///////////////////////////////////////////////////////////////////////////////
int tfe_ReportError(const char* pszErrorText, 
					int			nErrorTypeCode);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_ReportCheck
// description	: This function sends a result of a check to the log 
//
// parameters	: pszDescription	description of report check
//				  pszExpected		expected string
//				  pszRecorded		recorded string
//				  nCheckResult		check result value
//
// returns		: 1		check result written in log
//				  0		check result could not be written in log
///////////////////////////////////////////////////////////////////////////////
int tfe_ReportCheck(const char* pszDescription, 
					const char* pszExpected, 
					const char* pszRecorded,
					int			nCheckResult);

//	CHECKING
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_CheckString
// description	: This function checks if the comparison between two strings 
//				  is considered passed or failed and sends the result to the
//				  log to be written in the report as a check.
//
// parameters	: pszDescription	description of check
//				  pszExpected		expected string
//				  pszRecorded		recorded string
//
// returns		: 1		check passed
//				  0		check failed
///////////////////////////////////////////////////////////////////////////////
int tfe_CheckString(const char* pszDescription, 
					const char* pszExpected, 
					const char* pszRecorded);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_CheckArgument
// description	: This function checks if the comparison between a specified
//				  argument and a specified string is considered passed or
//				  failed. If the argument contains a command, this command is
//				  evaluated. In the case of a snap command, a snap operation is
//				  performed and the result will be passed; in the case of a
//				  not-empty command, the result will be passed if the specified
//				  string is not empty. As description of the check is taken the
//				  description of the argument; if this is empty, its index will
//				  be taken.
//				  	
// parameters	: nIndex			index of argument to be compared with string
//				  strRecorded		string to be compared with argument
//
// returns		: 1		check passed
//				  0		check failed
///////////////////////////////////////////////////////////////////////////////
int tfe_CheckArgument(int nIndex, const char* pszRecorded);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_CheckParameter
// description	: This function makes a comparison the same as tfe_CheckArgument,
//				  only the index specifies a parameter instead of an argument.
//				  	
// parameters	: nIndex			index of parameter to be compared with string
//				  strRecorded		string to be compared with argument
//
// returns		: 1		check passed
//				  0		check failed
///////////////////////////////////////////////////////////////////////////////
int tfe_CheckParameter(int nIndex, const char* pszRecorded);

//	CLUSTER VARIABLES
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_KeepArgument
// description	: This function sets the value of a cluster variable in a
//				  specified argument of the current test line. 
//
// parameters	: nIndex	index of the argument containing the cluster
//							variable in a keep command
//				  pszValue	value to which the cluster variable is to be set
//				
// returns		: 1		cluster variable successfully kept
//				  0		cluster variable could not be kept
///////////////////////////////////////////////////////////////////////////////
int tfe_KeepArgument(int nIndex, const char* pszValue);

///////////////////////////////////////////////////////////////////////////////
// function		: tfe_KeepParameter
// description	: This function sets the value of a cluster variable in a
//				  specified parameter of the current action word. 
//
// parameters	: nIndex	index of the parameter containing the cluster
//							variable in a keep command
//				  pszValue	value to which the cluster variable is to be set
//				
// returns		: 1		cluster variable successfully kept
//				  0		cluster variable could not be kept
///////////////////////////////////////////////////////////////////////////////
int tfe_KeepParameter(int nIndex, const char* pszValue);

//	GUI
///////////////////////////////////////////////////////////////////////////////////
	
///////////////////////////////////////////////////////////////////////////////
// function		: tfe_DisplayMessage
// description	: This function sends a string containig a message to be 
//				  displayed on screen to a GUI-window.
//
// parameters	: pszMessage	message to be displayed
//
// returns		: 1		message successfully displayed
//				  0		message could not be displayed
///////////////////////////////////////////////////////////////////////////////
int tfe_DisplayMessage(const char* pszMessage);

//BSTR ChartoBSTR(char* string);

///////////////////////////////////////////////////////////////////////////////////
//	ENGINE 4 STYLE INTERFACE
///////////////////////////////////////////////////////////////////////////////////
	
///////////////////////////////////////////////////////////////////////////////
// function		: eng_start
// description	: same as tfe_StartEngine()
//
// parameters	: pszClusterFilename	name of cluster file
//				  pszReportFilename		name of report file
//				  pszIniFile			name of engine ini file
//
// returns		: 1		engine successfully started
//				  0		engine could not be started
///////////////////////////////////////////////////////////////////////////////
int eng_start(const char* pszClusterFilename, 
			  const char* pszReportFilename,
			  const char* pszIniFile);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_stop
// description	: same as tfe_StopEngine() directly followed by
//				  tfe_GenerateReport()
//
// parameters	: -
//
// returns		: 1		engine successfully stopped and report successfully
//						generated
//				  0		engine could not be stopped or report could not be
//						generated
///////////////////////////////////////////////////////////////////////////////
int eng_stop();

///////////////////////////////////////////////////////////////////////////////
// function		: eng_read_setting
// description	: This function reads a value from a specified key and section
//				  in an ini file.
//
// parameters	: OUT pszDest		string to be filled with the specified value
//									from an ini file
//				  pszIniFile		name and path of ini file
//				  pszSection		specified section in the ini file pszIniFile
//				  pszKey			specified key in the section pszSection
//
// returns		: 1		default return value
//////////////////////////////////////////////////////////////////////////////
int eng_read_setting(char*		 pszDest, 
					 const char* pszIniFile,
					 const char* pszSection, 
					 const char* pszKey);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_write_setting
// description	: This function writes a value to a specified key and section
//				  in an ini file.
//
// parameters	: pszIniFile	name and path of ini file
//				  pszSection	specified section in the ini file pszIniFile
//				  pszKey		specified key in the section pszSection
//				  pszValue		value to write to ini file
//
// returns		: 1		default return value
///////////////////////////////////////////////////////////////////////////////
int eng_write_setting (const char* pszInifile, 
					   const char* pszSection, 
					   const char* pszKey, 
					   const char* pszValue);

//////////////////////////////////////////////////////////////////////////////
// function		: eng_message
// description	: same as tfe_DisplayMessage()
//
// parameters	: pszMessage	message to be displayed
//
// returns		: 1		message successfully displayed
//				  0		message could not be displayed
//////////////////////////////////////////////////////////////////////////////
int eng_message(const char* pszMessage);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_action
// description	: This function returns the name of an action word function
//				  associated with a specified action word. When no action word
//				  is specified, its functionality is the same as that of
//				  tfe_GetActionWordFunction().
//
// parameters	: pszActionWord		name of action word
//
// returns		: name of action word function
///////////////////////////////////////////////////////////////////////////////
const char* eng_action(const char* pszActionWord);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_argument
// description	: same as tfe_GetArgument()
//
// parameters	: nIndex	index of argument list
//
// returns		: specified argument from the current test line's argument list
///////////////////////////////////////////////////////////////////////////////
const char* eng_argument(int nIndex);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_argument_count
// description	: same as tfe_GetNumberOfArguments()
//
// parameters	: -
//
// returns		: number of arguments
///////////////////////////////////////////////////////////////////////////////
int eng_argument_count();

///////////////////////////////////////////////////////////////////////////////
// function		: eng_check_argument
// Description	: This function compares a specified string with the content of
//				  a specified argument of the current test line and sends the
//				  result to the log to be written in the report as a check.
//				  The expected value, recorded value and result are printed
//				  horizontally instead of vertically.
//
// parameters	: pszExpected		expected string
//				  nIndex			index of argument list
//
// returns		: 1		check passed
//				  0		check failed
///////////////////////////////////////////////////////////////////////////////
int eng_check_argument(const char* pszRecorded, int nIndex);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_keep_argument
// description	: same as tfe_KeepArgument(), only with reversed parameters.
//
// parameters	: pszValue	value to which the cluster variable is to be set
//				  nIndex	index of the argument containing the cluster
//							variable in a keep command
//				
// returns		: 1		cluster variable successfully kept
//				  0		cluster variable could not be kept
///////////////////////////////////////////////////////////////////////////////
int eng_keep_argument(const char* pszValue, int nIndex);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_line
// description	: same as tfe_ProcessNextLine()
//
// parameters	: -
//
// returns		: 1		next valid test line found
//				  0		no next valid test line found
///////////////////////////////////////////////////////////////////////////////
int eng_line();

///////////////////////////////////////////////////////////////////////////////
// function		: eng_line_count
// description	: This function returns the total number of lines in the main
//				  cluster file.
//
// parameters	: -
//
// returns		: the number of test lines in the main cluster
///////////////////////////////////////////////////////////////////////////////
int eng_line_count();

///////////////////////////////////////////////////////////////////////////////
// function		: eng_check_value
// description	: same as tfe_CheckString()
//
// parameters	: pszDescription	description of check
//				  pszExpected		expected string
//				  pszRecorded		recorded string
//
// returns		: 1		check passed
//				  0		check failed
///////////////////////////////////////////////////////////////////////////////
int eng_check_value(const char* pszDescription, 
					const char* pszExpected, 
					const char* pszRecorded);

//////////////////////////////////////////////////////////////////////////////
// function		: eng_report
// description	: Special use of tfe_ReportComment:
//				  tfe_ReportComment(pszLabel + " " + pszMessage)
//
// parameters	: pszLabel		label to be placed as first part of comment
//				  pszMessage	message to be placed as second part of comment
//				
// returns		: 1		default return value
//////////////////////////////////////////////////////////////////////////////
int eng_report(const char* pszLabel, const char* pszMessage);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_register_actionword
// description	: same as tfe_RegisterActionWord()
//
// parameters	: pszActionWord				name of action word
//				  pszActionWordFunction		name of associated function
//
// returns		: 1		action word successfully registered
//				  0		action word could not be registered
///////////////////////////////////////////////////////////////////////////////
int eng_register_actionword(const char* pszActionword, 
							const char* pszActionWordFunction);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_status
// description	: This function has no meaningful implementation. Only added
//				  for compliancy's sake.
//
// parameters	: -
//
// returns		: 1		default return value
///////////////////////////////////////////////////////////////////////////////
int eng_status();

///////////////////////////////////////////////////////////////////////////////
// function		: eng_copyright
// description	: same as tfe_GetCopyright()
//
// parameters	: -
//
// returns		: copyright information
///////////////////////////////////////////////////////////////////////////////
const char* eng_copyright();

///////////////////////////////////////////////////////////////////////////////
// function		: eng_version
// description	: same as tfe_GetVersion()
//
// parameters	: -
//
// returns		: version string
///////////////////////////////////////////////////////////////////////////////
const char* eng_version();

//////////////////////////////////////////////////////////////////////////////
// function		: eng_error
// description	: same as tfe_ReportError()
//
// parameters	: pszErrorText		text to be written in report as error
//				  nErrorTypeCode	error type code
//
// returns		: 1		text successfully written in log
//				  0		text could not be written in log
///////////////////////////////////////////////////////////////////////////////
int eng_error(const char* pszErrorText, int nErrorTypeCode);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_date_argument
// description	: Not implemented
//
// returns		: 1		default return value
////////////////////////////////////////////////////////////////////////////////
int eng_date_argument(int nIndex);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_unregister_actionword
// description	: same as tfe_UnregisterActionWord()				  
//
// parameters	: pszActionWord		name of action word
//
// returns		: 1		action word successfully unregistered
//				  0		action word could not be unregistered
///////////////////////////////////////////////////////////////////////////////
int eng_unregister_actionword(const char* pszActionWord);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_register_headerword
// description	: same as tfe_RegisterHeaderWord()
//
// parameters	: pszHeaderWord		name of header word
//				  pszReportTag		tag to be placed in the report when the
//									header word is encountered in a cluster
//
// returns		: 1		header word successfully registered
//				  0		header word could not be registered
///////////////////////////////////////////////////////////////////////////////
int eng_register_headerword(const char* pszHeaderWord, 
							const char* pszReportTag);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_create_synonym
// description	: same as tfe_CreateActionWordSynonym()
//			
// parameters	: pszActionWord		name of action word
//				  pszSynonym		name of synonym
//
// returns		: 1		synonym successfully created
//				  0		synonym could not be created
///////////////////////////////////////////////////////////////////////////////
int eng_create_synonym(const char* pszActionWord, 
					   const char* pszSynonym);

///////////////////////////////////////////////////////////////////////////////
// function		: eng_unregister_all_actionwords
// description	: same as tfe_UnregisterAllActionWords
//			
// parameters	: -
//
// returns		: 1		action words successfully unregistered
//				  0		action words could not be unregistered
///////////////////////////////////////////////////////////////////////////////
int eng_unregister_all_actionwords();

///////////////////////////////////////////////////////////////////////////////
// function		: eng_legend
// description	: same as tfe_GetArgumentDescription()
//
// parameters	: nIndex	index of argument description list
//
// returns		: specified argument description
///////////////////////////////////////////////////////////////////////////////
const char* eng_legend(int nIndex);

///////////////////////////////////////////////////////////////////////////////
// C++ Specifics end

#ifdef __cplusplus
	}
#endif

#endif // !COENGINE_H