/*****************************************************************************
 * $Workfile: Log.h $
 * $Revision: 20 $
 * $Modtime: 8/16/01 6:01p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOG_H
#define LOG_H

// Includes
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

#undef BASECLASS
#define BASECLASS Result

#include "LogTag.h"
#include "Mutex.h"
#include "Result.h"			// Baseclass definition

// Forward declarations
class EngineSetting;

////////////////////////////////////////////////////////////////////////////////
// class Log

class Log : public BASECLASS
{
// Constants		
public:
	enum ERRORCODE	{	// enum specifying allowed error codes
						NUM_ERR_WARNING = 0,
						NUM_ERR_ERROR,
						NUM_ERR_CHECK,
						NUM_ERR_FATAL,
					};

	enum CHECKTYPE	{	// enum specifying allowed check types
						CHECK_ARGUMENT = 0,
						CHECK_PARAMETER,
						CHECK_STRING,
						CHECK_REPORT
					};

// Construction and destruction
protected:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor
	///////////////////////////////////////////////////////////////////////////////
	Log();

public:
	///////////////////////////////////////////////////////////////////////////////
	// destructor of Log
	///////////////////////////////////////////////////////////////////////////////
	~Log();

private:
	Log( const Log& src ){};			// Copy constructor

// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Instance()
	//
	// description	:	This function returns the pointer to the only allowed
	//					instance of the Log class.
	//				
	// parameters	:	-
	//
	// returns		:	-
	//
	// remarks		:	This is a static member function.
	///////////////////////////////////////////////////////////////////////////////	
	static Log* Instance();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Initialise()
	//
	// description	:	This function initialise the log, and creates the log file.
	//				
	// parameters	:	pSetting		EngineSetting object
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Initialise( EngineSetting* pSetting );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Good()
	//
	// description	:	This function returns whether or not the Log object is
	//					ready for logging.
	//				
	// parameters	:	-
	//
	// returns		:	true	ready for logging
	//					false	not ready for logging
	///////////////////////////////////////////////////////////////////////////////	
	bool Good() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetLineNumber()
	//
	// description	:	This function sets the current cluster line number.
	//				
	// parameters	:	nLine		line number
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SetLineNumber( int nLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLogName()
	//
	// description	:	This function returns the name of the log file.
	//				
	// parameters	:	-
	//
	// returns		:	name of log file
	///////////////////////////////////////////////////////////////////////////////	
	const string& GetLogName() const;

// Data logging
///////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Copyright()
	//
	// description	:	This function logs the Engine's copyright information.
	//				
	// parameters	:	strCopyright	string specifying copyright information
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Copyright( const string& strCopyright );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EngineVersion()
	//
	// description	:	This function logs the Engine's version.
	//				
	// parameters	:	strVersion	string specifying Engine version
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EngineVersion( const string& strVersion );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EngineBuildNumber()
	//
	// description	:	This function logs the Engine's build number.
	//				
	// parameters	:	strBuild	string specifying Engine build number
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EngineBuildNumber( const string& strBuild );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ComputerName()
	//
	// description	:	This function logs the windows computername
	//				
	// parameters	:	strName	string specifying comnputers name
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ComputerName( const string& strName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	UserName()
	//
	// description	:	This function logs the User Name
	//				
	// parameters	:	strName	string specifying the user name
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void UserName( const string& strName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	License()
	//
	// description	:	This function logs information from the used license file:
	//					name, company, and serial number.
	//				
	// parameters	:	strName				name of license holder
	//					strCompany			company name of license holder
	//					strSerialNumber		serial number of license
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void License( const string& strName, const string& strCompany,
				  const string& strSerialNumber );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	IniFile()
	//
	// description	:	This function logs an Engine setting from the ini-file.
	//				
	// parameters	:	strSection		section
	//					strKey			key
	//					strValue		value
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void IniFile( const string& strSection, const string& strKey,
				  const string& strValue );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	RegisterActionWord()
	//
	// description	:	This function logs the registration of a user-defined
	//					action word and its associated action word function.
	//				
	// parameters	:	strActionWord	registered action word
	//					strFunction		action word function
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void RegisterActionWord( const string& strActionWord, const string& strFunction );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	RegisterHeaderWord()
	//
	// description	:	This function logs the registration of a user-defined
	//					header word and its associated report tag.
	//				
	// parameters	:	strHeaderWord	registered header word
	//					strTag			report tag
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void RegisterHeaderWord( const string& strHeaderWord, const string& strTag );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ActionWordSynonym()
	//
	// description	:	This function logs the registration of an action word
	//					synonym.
	//				
	// parameters	:	strActionWord	action word that is aliased
	//					strSynonym		registered synonym
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ActionWordSynonym( const string& strActionWord, const string& strSynonym );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	UnregisterActionWord()
	//
	// description	:	This function logs the unregistration of a user-defined
	//					action word.
	//				
	// parameters	:	strActionWord	unregistered action word
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void UnregisterActionWord( const string& strActionWord );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	UnregisterHeaderWord()
	//
	// description	:	This function logs the unregistration of a user-defined
	//					header word.
	//				
	// parameters	:	strHeaderWord	unregistered header word
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void UnregisterHeaderWord( const string& strHeaderWord );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	UnregisterAllActionWord()
	//
	// description	:	This function logs the unregistration of all user-defined
	//					action and header words.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void UnregisterAllActionWords();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EngineStart()
	//
	// description	:	This function logs the start of a test run.
	//				
	// parameters	:	strCluster		cluster name
	//					strReport		report name
	//					strIniFile		ini file
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EngineStart( const string& strCluster, const string& strReport,
					  const string& strIniFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EngineStop()
	//
	// description	:	This function logs the stop of a test run.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EngineStop();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EngineReset()
	//
	// description	:	This function logs the reset of a test run.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EngineReset();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EnginePause()
	//
	// description	:	This function logs that the engine is paused.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EnginePause();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EngineResume()
	//
	// description	:	This function logs that the engine is resumed.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EngineResume();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EMCPause()
	//
	// description	:	This function logs the pressing of the pause button on the
	//					Engine Message Centre.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EMCPause();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EMCResume()
	//
	// description	:	This function logs the pressing of the resume button on the
	//					Engine Message Centre.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EMCResume();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EMCStop()
	//
	// description	:	This function logs the pressing of the stop button on the
	//					Engine Message Centre.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EMCStop();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	MessagePause()
	//
	// description	:	This function logs that a message is displayed on a GUI.
	//				
	// parameters	:	strMessage		displayed message
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void DisplayMessage( const string& strMessage );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ClusterLine()
	//
	// description	:	This function logs the uninterpreted arguments of a cluster
	//					line.
	//				
	// parameters	:	vstrArguments	vector of cluster line arguments
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ClusterLine( const vector<string>& vstrArguments );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EmptyLine()
	//
	// description	:	This function logs the interpretation of an empty line.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EmptyLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CommentLine()
	//
	// description	:	This function logs the interpretation of a comment line,
	//					and logs its parameters.
	//				
	// parameters	:	vstrParameters		comment parameters
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void CommentLine( const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ActionWord()
	//
	// description	:	This function logs the interpretation of a test line, i.e.,
	//					a cluster line with an action word; the action word and its
	//					parameters are logged.
	//				
	// parameters	:	strActionWord		action word
	//					vstrParameters		action word parameters
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ActionWord( const string& strActionWord, const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Set()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'set'; its parameters are logged.
	//				
	// parameters	:	vstrParameters		parameters of 'set'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Set( const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Skip()
	//
	// description	:	This function logs the decision of the Engine to skip a
	//					cluster line; this line's arguments are logged.
	//				
	// parameters	:	vstrArguments		arguments of the skipped line
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Skip( const vector<string>& vstrArguments );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ClusterBegin()
	//
	// description	:	This function logs the start of processing a cluster; its
	//					name is logged.
	//				
	// parameters	:	strCluster		name of processed cluster
	//					strReport		name of report starting for this cluster
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ClusterBegin( const string& strCluster, const string& strReport );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ClusterEnd()
	//
	// description	:	This function logs the end of processing a cluster; its
	//					name is logged.
	//				
	// parameters	:	strCluster		name of processed cluster
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ClusterEnd( const string& strCluster );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DoCluster()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'do cluster'; the name of the subcluster to
	//					start, and its report are logged.
	//				
	// parameters	:	strSubcluster	name subcluster to start
	//					strReport		report name for subcluster
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void DoCluster( const string& strSubcluster, const string& strReport );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	TemplateCall()
	//
	// description	:	This function logs the interpretation of a template action
	//					word; its name and parameters are logged.
	//				
	// parameters	:	strTemplate			template name
	//					vstrParameters		template parameters
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void TemplateCall( const string& strTemplate, const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	TemplateBegin()
	//
	// description	:	This function logs the start of processing a template; its
	//					template file is logged.
	//				
	// parameters	:	strFile			template file
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void TemplateBegin( const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	TemplateEnd()
	//
	// description	:	This function logs the end of processing a template; its
	//					template file is logged.
	//				
	// parameters	:	strFile			template file
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void TemplateEnd( const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	TemplatePrototype()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'template prototype'; its name and parameters
	//					are logged.
	//				
	// parameters	:	strTemplate			template name
	//					vstrParameters		template parameters
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void TemplatePrototype( const string& strTemplate,
							const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DefineTemplate()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'define template'; the name of the template
	//					and its parameters are logged.
	//				
	// parameters	:	strTemplate			template name
	//					vstrParameters		template parameters
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void DefineTemplate( const string& strTemplate,
						 const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	LineToTemplate()
	//
	// description	:	This function logs the decision of the Engine to write a
	//					cluster line to a template.
	//				
	// parameters	:	vstrArguments		arguments of the written line
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void LineToTemplate( const vector<string>& vstrArguments );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EndDefineTemplate()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'end template'; the name of the template is
	//					logged.
	//				
	// parameters	:	strTemplate			template name
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EndDefineTemplate( const string& strTemplate );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	TemplateDefined()
	//
	// description	:	This function logs that the Engine has defined a template,
	//					and has written it to a template file.
	//				
	// parameters	:	strTemplate		template name
	//					strFile			template file
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void TemplateDefined( const string& strTemplate, const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DeclareTemplate()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'declare template'; its parameters (name and
	//					file) are logged.
	//				
	// parameters	:	strTemplate		template name
	//					strFile			template file
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void DeclareTemplate( const string& strTemplate, const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	RegisterTemplate()
	//
	// description	:	This function logs the registration of a template action
	//					word; its name and file are logged.
	//				
	// parameters	:	strTemplate		template name
	//					strFile			template file
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void RegisterTemplate( const string& strTemplate, const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HeaderWord()
	//
	// description	:	This function logs the interpretation of a user-defined
	//					header word; its name, registered tag, and interpreted
	//					parameter are logged.
	//				
	// parameters	:	strHeaderWord		header word
	//					strTag				registered tag
	//					strParameter		header word parameter
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void HeaderWord( const string& strHeaderWord, const string& strTag,
					 const string& strParameter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HeaderCluster()
	//
	// description	:	This function logs the interpretation of the built-in
	//					header word 'cluster'.
	//				
	// parameters	:	strParameter	parameter of 'cluster'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void HeaderCluster( const string& strParameter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HeaderDate()
	//
	// description	:	This function logs the interpretation of the built-in
	//					header word 'date'.
	//				
	// parameters	:	strParameter	parameter of 'date'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void HeaderDate( const string& strParameter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HeaderAuthor()
	//
	// description	:	This function logs the interpretation of the built-in
	//					header word 'author'.
	//				
	// parameters	:	strParameter	parameter of 'author'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void HeaderAuthor( const string& strParameter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HeaderVersion()
	//
	// description	:	This function logs the interpretation of the built-in
	//					header word 'version'.
	//				
	// parameters	:	strParameter	parameter of 'version'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void HeaderVersion( const string& strParameter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HeaderDocument()
	//
	// description	:	This function logs the interpretation of the built-in
	//					header word 'document'.
	//				
	// parameters	:	strParameter	parameter of 'document'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void HeaderDocument( const string& strParameter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HeaderSheet()
	//
	// description	:	This function logs the interpretation of the built-in
	//					header word 'sheet'.
	//				
	// parameters	:	strParameter	parameter of 'sheet'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void HeaderSheet( const string& strParameter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Label()
	//
	// description	:	This function logs a label (name and parameters).
	//				
	// parameters	:	strName			label name
	//					strParameters	label parameters
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Label( const string& strName, const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ExportVariable()
	//
	// description	:	This function logs the export of a variable with a certain
	//					value to a keep file.
	//				
	// parameters	:	strVariable		variable name
	//					strValue		value of variable
	//					strFile			keep file to which variable is exported
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ExportVariable( const string& strVariable, const string& strValue,
						 const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ImportVariable()
	//
	// description	:	This function logs the import of a variable with a certain
	//					value from a keep file.
	//				
	// parameters	:	strVariable		variable name
	//					strValue		value of variable
	//					strFile			keep file from which variable is imported
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ImportVariable( const string& strVariable, const string& strValue,
						 const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Keep()
	//
	// description	:	This function logs the keep of a variable with a certain
	//					value; besides variable name and value, also the index of
	//					the argument with the keep command, and the keep file
	//					to which a copy is written, are logged.
	//				
	// parameters	:	strVariable		variable name
	//					strValue		value of variable
	//					nArgument		argument index of the keep command
	//					strFile			keep file to which keep is copied
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Keep( const string& strVariable, const string& strValue,
			   int nArgument, const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Snap()
	//
	// description	:	This function logs the snap of a value; besides identifier
	//					and value, also  the index of the argument with the snap
	//					command, and the snap file to which a copy is written, are
	//					logged.
	//				
	// parameters	:	strIdentifier	identifier
	//					strValue		snapped value
	//					nArgument		argument index of the snap command
	//					strFile			snap file
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Snap( const string& strIdentifier, const string& strValue,
			   int nArgument, const string& strFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Check()
	//
	// description	:	This function logs a check: its result, description,
	//					expected value, recorded value, type, and argument/
	//					parameter index. The result must be either passed (true) or
	//					failed (false); type must be of the CHECKTYPE enum; the
	//					index is only logged if the type is either CHECK_ARGUMENT
	//					or CHECK_PARAMETER.
	//				
	// parameters	:	bResult				check result
	//					strDescription		description
	//					strExpected			expected value
	//					strRecorded			recorded value
	//					nType				check type
	//					nIndex				argument/parameter index
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Check( bool bResult, const string& strDescription, const string& strExpected,
				const string& strRecorded, CHECKTYPE nType, int nIndex );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ReportComment()
	//
	// description	:	This function logs comment sent to the Engine.
	//				
	// parameters	:	strComment		comment
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ReportComment( const string& strComment );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ReportError()
	//
	// description	:	This function logs an error with its specified type, as
	//					sent to the Engine; type must be of ERRORCODE enum.
	//				
	// parameters	:	nType			error type
	//					strMessage		error message
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ReportError( ERRORCODE nType, const string& strMessage );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ClusterError()
	//
	// description	:	This function logs a cluster error.
	//				
	// parameters	:	strMessage		error message
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ClusterError( const string& strMessage );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InternalError()
	//
	// description	:	This function logs an internal error.
	//				
	// parameters	:	strFile		C++ file in which error occurred
	//					nLine		file line number where error occurred
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void InternalError( const string& strFile, int nLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	If()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'if'.
	//				
	// parameters	:	vstrCondition	vector containig the condition parameters
	//					bResult			result of the condition
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void If( const vector<string>& vstrCondition, bool bResult );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ElseIf()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'else if'.
	//				
	// parameters	:	vstrCondition	vector containig the condition parameters
	//					bResult			result of the condition
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ElseIf( const vector<string>& vstrCondition, bool bResult );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Else()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'else'.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Else();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EndIf()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'end if'.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EndIf();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Repeat()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'repeat'.
	//				
	// parameters	:	nTotal		total number of iteration to perform
	//					nCounter	current iteration counter
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Repeat( int nTotal, int nCounter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EndRepeat()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'end repeat'.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EndRepeat();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	While()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'while'.
	//				
	// parameters	:	vstrCondition	vector containig the condition parameters
	//					bResult			result of the condition
	//					nCounter		current iteration counter
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void While( const vector<string>& vstrCondition, bool bResult, int nCounter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EndWhile()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'end while'.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void EndWhile();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SlaveLine()
	//
	// description	:	This function logs the decision of the Engine to send a
	//					cluster to a Slave; the Slave name and the arguments of the
	//					sent line are logged.
	//				
	// parameters	:	strSlave		slave name
	//					vstrArguments	arguments of sent cluster line
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SlaveLine( const string& strSlave, const vector<string>& vstrArguments );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ConnectSlave()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'connect slave'.
	//				
	// parameters	:	vstrParameters		parameters of 'connect slave'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ConnectSlave( const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SlaveConnected()
	//
	// description	:	This function logs whether an attempted connection with a
	//					Slave succeeded or failed (time-out).
	//				
	// parameters	:	strSlave		slave to connect with
	//					bConnected		success or not
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SlaveConnected( const string& strSlave, bool bConnected );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DisconnectSlave()
	//
	// description	:	This function logs the interpretation of the built-in
	//					action word 'disconnect slave'.
	//				
	// parameters	:	vstrParameters		parameters of 'disconnect slave'
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void DisconnectSlave( const vector<string>& vstrParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SlaveDisconnected()
	//
	// description	:	This function logs the Engine disconnecting a Slave
	//				
	// parameters	:	strSlave		slave to disconnect
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SlaveDisconnected( const string& strSlave );

// Implementation		
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteLine()
	//
	// description	:	This function formats a vector of log line arguments to a
	//					log line; date, time, and line number are placed in front,
	//					and a newline character in back; this formatted line is
	//					then written to	the log file.
	//
	// parameters	:	vstrArguments		arguments to format and write
	//
	// returns		:	true	line successfully written to the logfile
	//					false	line could not be written to the logfile
	///////////////////////////////////////////////////////////////////////////////		
	bool WriteLine( const vector<string>& vstrArguments );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EscapeReturns()
	//
	// description	:	This function replaces newline characters in a specified
	//					string by "\n".
	//
	// parameters	:	strLine		line in which to replace returns		OUT
	//
	// returns		:	integer	specifying number of replacements
	///////////////////////////////////////////////////////////////////////////////		
	int	EscapeReturns( string& strLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EscapeTabs()
	//
	// description	:	This function replaces tab characters in a specified
	//					string by "\t".
	//
	// parameters	:	strLine		line in which to replace tabs		OUT
	//
	// returns		:	integer	specifying number of replacements
	///////////////////////////////////////////////////////////////////////////////		
	int EscapeTabs( string& strLine );

// Member variables
private:
	static Log* m_pLog;		// pointer to Log's one allowed instance
	bool m_bGood;			// states whether Log is ready
	string m_strLogName;	// log file name
	int	m_nLineNumber;		// current cluster line number
	LogTag m_LogTag;		// LogTag object 
	Mutex m_Lock;			// mutex to garantuee unique access to log file
};


////////////////////////////////////////////////////////////////////////////////

#endif // !LOG_H
