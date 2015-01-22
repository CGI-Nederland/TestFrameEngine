/*****************************************************************************
 * $Workfile: ActionServer.h $
 * $Revision: 31 $
 * $Modtime: 11/13/01 6:48p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ACTIONSERVER_H
#define ACTIONSERVER_H

//#include <map>
//#include <string>
//#include <vector>

// Defines.
#define MAXIMUMCLUSTERS		50

#include <map>
#include <sstream>
#include <string>
#include <vector>

class ActionWord;
class Cluster;
class ComposedInterpreter;
class Condition;
class EngineSetting;
class ErrorList;
class IOInterface;
class Log;
class MasterCommand;
class Setting;
class Template;
class UIHandler;

using namespace std;

class ActionServer 
{
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of ActionServer
	//
	// parameters	: pInterpreter		pointer to ComposedInterpreter
	//				  pActionWord		pointer to ActionWord
	//				  pUIHandler		pointer to UIHandler
	//				  pKeepSetting		pointer to Setting object for keep-file
	//				  pMasterCommand	pointer to MasterCommand
	///////////////////////////////////////////////////////////////////////////////
	ActionServer(ComposedInterpreter* pInterpreter, ActionWord* pActionWord, 
		         UIHandler* pUIHandler, Setting* pKeepSetting,
				 MasterCommand* pMasterCommand);

	////// AH ///////
	ActionServer(ActionServer&);
	ActionServer& operator=(ActionServer&);
	////// AH ///////

	///////////////////////////////////////////////////////////////////////////////
	// destructor of ActionServer
	///////////////////////////////////////////////////////////////////////////////
	~ActionServer();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Initialise()
	// 
	// description	: This function initialises the settings for ActionServer,
	//				  makes the main cluster object and places it in vector of
	//				  clusters.
	//
	// parameters	: pSetting	pointer to EngineSetting
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void Initialise( EngineSetting* pSetting );

	///////////////////////////////////////////////////////////////////////////////
	// function		: Clear()
	// description	: This function clears the vector of clusters and makes the
	//					action server ready for a new main cluster.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void Clear();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Good()
	//
	// description	: This function states whether or not the ActionServer is
	//				  initialised correctly.
	//
	// parameters	: -
	//
	// returns		: true		ActionServer is initialised correctly
	//				  false		ActionServer is not initialised correctly
	///////////////////////////////////////////////////////////////////////////////
	bool Good() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Next()
	// description	: This function reads the next line with a valid action word
	//					and returns true, or if no such line can be found, returns
	//					false.
	//
	// parameters	: -
	//
	// returns		: true		a line has been read
	//				  false		no valid test line could be read
	///////////////////////////////////////////////////////////////////////////////
	bool Next();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWord()
	//
	// description	: This function returns the name of the action word.
	//
	// parameters	: -
	//
	// returns		: string containing the name of the action word
	///////////////////////////////////////////////////////////////////////////////
	string GetActionWord() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Action()
	//
	// description	: This function returns the name of action word function.
	//
	// parameters	: -
	//
	// returns		: name of the action word function
	///////////////////////////////////////////////////////////////////////////////
	string Action() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Argument()
	//
	// description	: This function returns the n-th argument of the current action
	//					word.
	//
	// parameters	: nArgument		index of arguments
	//
	// returns		: n-th argument of action word
	///////////////////////////////////////////////////////////////////////////////
	string Argument(int nArgument) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameter()
	//
	// description	: This function returns the n-th parameter of the current
	//				  action word; note that in standalone-mode this means the
	//				  (n+1)-th argument of the current test line, and in master-
	//				  mode the (n+2)-th argument of the current test line.
	//
	// parameters	: nParameter		parameter index
	//
	// returns		: n-th parameter of action word
	///////////////////////////////////////////////////////////////////////////////
	string GetParameter( int nParameter ) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetClusterFile()
	//
	// description	: This function returns the name of the current cluster file.
	//
	// parameters	: -
	//
	// returns		: name of the current cluster file
	///////////////////////////////////////////////////////////////////////////////
	string GetClusterFile();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTotalLine()
	//
	// description	: This function returns the total number of lines in the
	//					cluster file.
	//
	// parameters	: -
	//
	// returns		: total number of lines
	///////////////////////////////////////////////////////////////////////////////
	long int GetTotalLine() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: ArgumentCount()
	//
	// description	: This function returns the number of arguments of the current 
	//				  test line.
	//
	// parameters	: -
	//
	// returns		: number of arguments
	///////////////////////////////////////////////////////////////////////////////
	int ArgumentCount() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfParameters()
	//
	// description	: This function returns the number of parameters of the current 
	//				  action word.
	//
	// parameters	: -
	//
	// returns		: number of parameters
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfParameters() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: LineNumber()
	//
	// description	: This function returns the number of the current test line
	//
	// parameters	: -
	//
	// returns		: number of current test line
	///////////////////////////////////////////////////////////////////////////////
	long int LineNumber() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfErrors()
	//
	// description	: This function returns the number of errors found as of yet.
	//
	// parameters	: -
	//
	// returns		: number of errors found as of yet
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfErrors() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLatestError()
	//
	// description	: This function returns the latest error.
	//
	// parameters	: -
	//
	// returns		: string containing the latest error
	///////////////////////////////////////////////////////////////////////////////
	const string& GetLatestError() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetSection()
	//
	// description	: This function returns the name of the current section of the
	//					current cluster.
	//
	// parameters	: -
	//
	// returns		: name of the current section of the current cluster
	///////////////////////////////////////////////////////////////////////////////
	const string& GetSection() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetScenario()
	//
	// description	: This function returns the name of the current scenario of the
	//					current cluster.
	//
	// parameters	: -
	//
	// returns		: name of the current scenario of the current cluster
	///////////////////////////////////////////////////////////////////////////////
	const string& GetScenario() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestCase()
	//
	// description	: This function returns the name of the current test case of 
	//					the current cluster.
	//
	// parameters	: -
	//
	// returns		: name of the current test case of the current cluster
	///////////////////////////////////////////////////////////////////////////////
	const string& GetTestCase() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestCondition()
	//
	// description	: This function returns the name of the current test condition of 
	//					the current cluster.
	//
	// parameters	: -
	//
	// returns		: name of the current test condition of the current cluster
	///////////////////////////////////////////////////////////////////////////////
	const string& GetTestCondition() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: WriteLine()
	//
	// description	: This function appends a new line containing the string
	//					strLine to the active cluster file.
	//
	// parameters	: strLine		line to append to active file
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void WriteLine(const string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: KeepArgument
	//
	// description	: This function keeps an argument when index and value are 
	//				  are given.
	//				
	// parameters	: strValue		the value to keep
	//				  nIndex		keep variable index
	//
	// returns		: true			Keep ok
	//				  false			Keep not ok
	///////////////////////////////////////////////////////////////////////////////		
	bool KeepArgument(const string& strValue, const int nIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetArgumentDescription
	//
	// description	: This function return a part of the last stored comment line
	//				
	// parameters	: nIndex		argument index
	//
	// returns		: string		description
	///////////////////////////////////////////////////////////////////////////////		
	string GetArgumentDescription(const int nIndex) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameterDescription
	//
	// description	: This function returns the description of the specified
	//				  parameter
	//				
	// parameters	: nIndex		parameter index
	//
	// returns		: string		description of the specified parameter
	///////////////////////////////////////////////////////////////////////////////		
	string GetParameterDescription( int nIndex ) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfActiveClusters()
	//
	// description	: This function returns the number of active clusters, i.e. the
	//					size of the cluster vector.
	//				
	// parameters	: -
	//
	// returns		: number of active clusters
	///////////////////////////////////////////////////////////////////////////////		
	int GetNumberOfActiveClusters() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ReportError()
	//
	// description	:	This function reports to the ActionServer that an error
	//					with the specified text has been logged. It updates
	//					counters and sends a message to the GUI.
	//				
	// parameters	:	strError	Text of the error
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void ReportError( const string& strError );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ReportCheck()
	//
	// description	:	This function reports to the ActionServer that a check with
	//					the specified result has been logged. It updates counters
	//					and sends a message to the GUI.
	//				
	// parameters	:	bResult		Result of the check
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void ReportCheck( bool bResult );

// private member functions
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	FillActionMap()
	//
	// description	:	This function fills the action map with action types and
	//					associated member functions which handle the encounter of
	//					such an action word.
	//
	// parameters	:	-
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void FillActionMap();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	LineToBeProcessed()
	//
	// description	:	This function determines if the current line is to be
	//					processed by this Engine (in which case true is returned,)
	//					or by a Slave Engine (false is returned.)
	//
	// parameters	:	-
	//
	// returns		:	true	current line is to be processed
	//					false	current line is to be sent to a Slave
	///////////////////////////////////////////////////////////////////////////////
	bool LineToBeProcessed() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ProcessAction()
	//
	// description	:	This function determines the action type of the current
	//					test line, and takes the corresponding action.
	//
	// parameters	:	-
	//
	// returns		:	true	an extern action word is found
	//					false	a built-in, commment line or empty line is found
	//							and processed
	///////////////////////////////////////////////////////////////////////////////
	bool ProcessAction();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SendLineToSlave()
	//
	// description	:	This function sends the current cluster line to the Slave
	//					specified in it; if this Slave is invalid, an error is
	//					reported.
	//
	// parameters	:	-
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void SendLineToSlave();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HandleEndOfCluster()
	//
	// description	:	This function handles the end of a cluster
	//
	// parameters	:	-
	//
	// returns		:	true	the ended cluster was a subcluster or template
	//					false	the ended cluster was the main cluster
	///////////////////////////////////////////////////////////////////////////////
	bool HandleEndOfCluster();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InterpretLine()
	//
	// description	:	This function interprets all parameters of the current
	//					cluster line; if errors are found in the parameters, these
	//					are logged.
	//
	// parameters	:	-
	//
	// returns		:	true	no errors found in the current line
	//					false	errors found in the current line
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	LogInvalidActionWord()
	//
	// description	:	This function logs that the current cluster line contains
	//					an invalid action word.
	//
	// parameters	:	-
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void LogInvalidActionWord();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWordType()
	//
	// description	: This function returns the type of the current action word.
	//
	// parameters	: -
	//
	// returns		: action word type
	///////////////////////////////////////////////////////////////////////////////
	int GetActionWordType() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: WriteClusterError()
	//
	// description	: This function logs a specified error message as a cluster
	//				  error.
	//
	// parameters	: strError		cluster error message
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void WriteClusterError( const string& strError );
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: NameClusterFile()
	// description	: This function creates the name of the file for the specified
	//					cluster.
	//
	// parameters	: strClusterName	name of the cluster
	//
	// returns		: string containing name of corresponding cluster file
	///////////////////////////////////////////////////////////////////////////////
	string NameClusterFile(const string& strClusterName) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	NameReportFile()
	// description	:	This function creates the name of the file for the
	//					specified report.
	//
	// parameters	:	strReport	name of the report
	//
	// returns		:	string containing name of corresponding report file
	///////////////////////////////////////////////////////////////////////////////
	string NameReportFile( const string& strReport ) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: NameTemplateFile()
	// description	: This function creates the name of the file for the specified
	//					template. The file name is made up of TemplateName, the
	//					name found in the cluster, its spaces replaced by
	//					underscores, and added to the template directory
	//					TemplateDir.
	//
	// parameters	: strTemplateName	name of template as found in cluster
	//				  bAlreadyFile		states if name is already that of a file
	//
	// returns		: string containing name of corresponding template file
	///////////////////////////////////////////////////////////////////////////////
	string NameTemplateFile(const string& strTemplateName, bool bAlreadyFile) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWord()
	// description	: This function returns the index in the argument list of the
	//					action word on the current test line.
	//
	// parameters	: -
	//
	// returns		: index of the action word
	///////////////////////////////////////////////////////////////////////////////
	int GetActionWordIndex() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameters()
	//
	// description	: This function returns all interpreted parameters of the
	//				  current test line.
	//
	// parameters	: -
	//
	// returns		: vector containing interpreted parameters
	///////////////////////////////////////////////////////////////////////////////
	vector<string> GetParameters() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameters()
	//
	// description	: This function returns the interpreted parameters of the
	//				  current test line, after and including the one whose index
	//				  is specified.
	//
	// parameters	: nStart	parameter index from where to start
	//
	// returns		: vector containing interpreted parameters
	///////////////////////////////////////////////////////////////////////////////
	vector<string> GetParameters( int nStart ) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: CheckTemplateName()
	// description	: This function determines if the name found in template
	//					definition is valid to create a template for.
	//
	// parameters	: strTemplateName	name of template
	//
	// returns		: true		name can be used for template
	//				  false		name can not be used for template
	///////////////////////////////////////////////////////////////////////////////
	bool CheckTemplateName( const string& strTemplateName );

	///////////////////////////////////////////////////////////////////////////////
	// function		: CreateTemplate()
	// description	: This function reads lines from the current cluster and writes
	//					them to a new file (*.tpl) in the template directory until
	//					the interpreter finds an end of definition action word. It
	//					then registers it as an action word of type TEMPLATE.
	//
	// parameters	: strTemplateName			name of template
	//				  vstrTemplateParameters	vector of template parameters
	//
	// returns		: true		template successfully made
	//				  false		template could not be made
	///////////////////////////////////////////////////////////////////////////////
	bool CreateTemplate( const string& strTemplateName, 
						 const vector<string>& vstrTemplateParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTemplatePrototypeFromFile()
	// description	: This function checks if a File start with a template prototype.
	//					If so, strTemplateName and vstrParameters are filled with
	//					the name found in the prototype and its parameters 
	//					respectively.
	//
	// parameters	: strFileName			name of the file to check
	//				  OUT strTemplateName	to be filled with the found template name
	//				  OUT vstrParameters	to be filled with the found template 
	//											parameters
	//
	// returns		: true		file start with template prototype
	//				  false		file doesn't start with template prototype
	///////////////////////////////////////////////////////////////////////////////
	bool GetTemplatePrototypeFromFile(const string& strFileName, string& strTemplateName,
										vector<string>& vstrParameters);

	///////////////////////////////////////////////////////////////////////////////
	// function		: MaximumClustersOpen()
	//
	// description	: This function checks if the maximum allowed number of cluster
	//				  files (including templates) are currently open.
	//
	// parameters	: -
	//
	// returns		: true		maximum number of clusters open
	//				  false		number of clusters below maximum
	///////////////////////////////////////////////////////////////////////////////
	bool MaximumClustersOpen();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ClusterFileAlreadyOpen()
	// description	: This function checks if a cluster (or template) is already
	//					open, i.e. it is present in the vector of clusters.
	//
	// parameters	: strClusterFile	name of the cluster (or template) file
	//
	// returns		: true		cluster already open
	//				  false		cluster not open
	///////////////////////////////////////////////////////////////////////////////
	bool ClusterFileAlreadyOpen(const string& strClusterFile);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestLine()
	// description	: This function returns the current test line from the current
	//					cluster file, starting with the action word, i.e. if the
	//					engine is in Master/Slave mode, the slave argument is
	//					removed.
	//
	// parameters	: -
	//
	// returns		: string containing the current test line
	///////////////////////////////////////////////////////////////////////////////
	string GetTestLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetUninterpretedArguments()
	//
	// description	:	This function returns the current test line's uninterpreted
	//					arguments.
	//
	// parameters	:	-
	//
	// returns		:	vector containing uninterpreted arguments
	///////////////////////////////////////////////////////////////////////////////
	vector<string> GetUninterpretedArguments();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetUninterpretedParameters()
	//
	// description	:	This function returns the current test line's uninterpreted
	//					parameters (all arguments except slave name and action
	//					word).
	//
	// parameters	:	-
	//
	// returns		:	vector containing uninterpreted parameters
	///////////////////////////////////////////////////////////////////////////////
	vector<string> GetUninterpretedParameters();

	///////////////////////////////////////////////////////////////////////////////
	// function		: WriteLineToTemplateFile()
	// description	: This function write a specified string as a new line in the
	//					template file that is attached to a specied IOInterface
	//					pointer.
	//
	// parameters	: strLine			string to be written as line
	//				  pTemplateFile		IOInterface pointer to template file
	//
	// returns		: true		line successfully written to template file
	//				  false		line could not be written to template file
	///////////////////////////////////////////////////////////////////////////////
	bool WriteLineToTemplateFile(const string& strLine, IOInterface* pTemplateFile);

	///////////////////////////////////////////////////////////////////////////////
	// function		: EscapeRECharactersInLine()
	// description	: This function escapes all redundant escape characters in a
	//					specified line. These are the characters that are stored in
	//					the member variable m_strRedundantEscapeCharacters. This
	//					means that every  RE character is replaced by two same such
	//					characters in a row.
	//
	// parameters	: OUT strLine	line with RECs to be escape
	//
	// returns		: true		redundant escape characters in line escaped
	//				  false		no redundant escape characters in line found
	///////////////////////////////////////////////////////////////////////////////
	bool EscapeRECharactersInLine(string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleSelectionCondition()
	//
	// description	: This function handles the an if-statement from the line with
	//				  a condition; i.e., a line an 'if' or an 'else if' built-in.
	//
	// parameters	: -
	//
	// returns		: true		operation successful
	//				  false		errors found
	///////////////////////////////////////////////////////////////////////////////
	bool HandleSelectionCondition();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleSelectionAlternative()
	//
	// description	: This function 
	//
	// parameters	: -
	//
	// returns		: true		operation successful
	//				  false		errors found
	///////////////////////////////////////////////////////////////////////////////
	bool HandleSelectionAlternative();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GotoEndOfStruct()
	//
	// description	: This function goes to the end of a specified structure;
	//				  structures of the same type started from that point on are
	//				  tracked to determine if a found end really corresponds to the
	//				  point from which was started. If no corresponding end is
	//				  found, false is returned.
	//
	// parameters	: nBeginType	code for begin of structure
	//				  nEndType		code for end of structure
	//
	// returns		: true		end found
	//				  false		no corresponding end found in the cluster
	///////////////////////////////////////////////////////////////////////////////
	bool GotoEndOfStruct( int nBeginType, int nEndType );

///////////////////////////////////////////////////////////////////////////////
// Action processing functions

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleExternActionWord()
	//
	// description	: This function handles the encounter of an externally
	//				  registered, user-defined action word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleExternActionWord();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleExternHeaderWord()
	//
	// description	: This function handles the encounter of an externally
	//				  registered, user-defined header word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleExternHeaderWord();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleSubCluster()
	// description	: This function calls a subcluster. If successful, it lays the
	//					focus on this subcluster; if not, the error string will be
	//					filled.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleSubCluster();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleTemplate()
	// description	: This function calls a temlpate. If successfull, it lays the
	//					focus on this template; if not, the error string will be
	//					filled.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleTemplate();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleDefineTemplate()
	// description	: This function defines a template. It determines the prototype
	//					of this template, makes a template file and registers it. 
	//					This function is called when an action word of the type 
	//					BEGIN_DEFINITION is found.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleDefineTemplate();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleEndTemplate()
	//
	// description	: This function handles the 'end template' action word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleEndTemplate();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleTemplateProto()
	//
	// description	: This function handles the 'template prototype' action word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleTemplateProto();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleDeclareTemplate()
	// description	: This function declares a template, i.e. it registers a template
	//					that this is associated with a file, but only if this file
	//					starts with a correct template prototype declaration. This 
	//					function is called when an action word of the type 
	//					DECLARE_TEMPLATE is found.
	//
	// parameters	: -
	//
	// returns		: true		template successfully declared
	//				  false		template could not be declared
	///////////////////////////////////////////////////////////////////////////////
	void HandleDeclareTemplate();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleAuthor()
	//
	// description	: This function handles the 'author' header word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleAuthor();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleCluster()
	//
	// description	: This function handles the 'cluster' header word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleCluster();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleDate()
	//
	// description	: This function handles the 'date' header word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleDate();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleVersion()
	//
	// description	: This function handles the 'version' header word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleVersion();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleDocument()
	//
	// description	: This function handles the 'document' header word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleDocument();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleSheet()
	//
	// description	: This function handles the 'sheet' header word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleSheet();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleSection()
	//
	// description	: This function handles the start of a section.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleSection();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleScenario()
	//
	// description	: This function handles the start of a scenario.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleScenario();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleTestCase()
	//
	// description	: This function handles the start of a test case.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleTestCase();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleTestCondition()
	//
	// description	: This function handles the start of a test condition.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleTestCondition();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleExportToFile()
	//
	// description	: This function handles the encounter of an 'export variable'
	//				  action word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleExportToFile();

		///////////////////////////////////////////////////////////////////////////////
	// function		: HandleAllExportToFile()
	//
	// description	: This function that exports all known variables to a keep file
	//				 
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleExportAllToFile();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleImportFromFile()
	//
	// description	: This function handles the encounter of an 'import variable'
	//				  action word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleImportFromFile();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleConnectSlave()
	//
	// description	: This function handles the encounter of a 'connect slave'
	//				  action word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleConnectSlave();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleDisconnectSlave()
	//
	// description	: This function handles the encounter of a 'disconnect slave'
	//				  action word.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleDisconnectSlave();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleIf()
	//
	// description	: This function handles the encounter of an 'if' built-in by
	//				  starting a selection statement.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleIf();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleEndIf()
	//
	// description	: This function handles the encounter of an 'end if' built-in.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleEndIf();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleElse()
	//
	// description	: This function handles the encounter of an 'else' built-in.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleElse();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleElseIf()
	//
	// description	: This function handles the encounter of an 'else if' built-in.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleElseIf();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleRepeat()
	//
	// description	: This function handles the encounter of a 'repeat' built-in.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleRepeat();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleEndRepeat()
	//
	// description	: This function handles the encounter of an 'end repeat'
	//				  built-in.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleEndRepeat();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleWhile()
	//
	// description	: This function handles the encounter of a 'while' built-in.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleWhile();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleEndWhile()
	//
	// description	: This function handles the encounter of an 'end while'
	//				  built-in.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleEndWhile();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleEmptyLine()
	//
	// description	: This function handles the encounter of an empty line or 
	//				  comment line.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleEmptyLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleSet()
	//
	// description	: This function handles the encounter of a 'set' built-in.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void HandleSet();

// member variables
private:
	typedef void (ActionServer::*ActionFunction) ();
	typedef map<int, ActionFunction> ActionMap;

	ActionMap				m_mActions;			// map of action word types on
												// member functions handling these
	bool					m_bGood;			// states the ActionServer can be used
	bool					m_bReadNextLine;	// stating whether the next line should be read
	vector<Cluster*>		m_vpClusters;		// vector of pointers to Clusters
	vector<string>			m_vstrParDescr;		// vector of latest parameter descriptions
	Log*					m_pLog;				// pointer to current Log
	EngineSetting*			m_pSetting;			// pointer to Setting for ini-file
	Setting*				m_pKeepSetting;		// pointer to Setting for keep-file
	ComposedInterpreter*	m_pInterpreter;		// pointer to the Interpreter
	ActionWord*				m_pActionWord;		// pointer to ActionWord
	ErrorList*				m_pErrorList;		// pointer to ErrorList
	Template*				m_pTemplate;		// pointer to Template object
	UIHandler*				m_pUIHandler;		// pointer to UIHandler object
	MasterCommand*			m_pMasterCommand;	// pointer to MasterCommand
	Condition*				m_pCondition;		// pointer to Condition object
	string					m_strTemplateDir;	// template directory
	string					m_strClusterDir;	// cluster directory
	string					m_strReportDir;		// report directory
	string					m_strEngineVersion;	// version of the engine
	string					m_strEngineBuild;	// build number of the engine
	string					m_strLatestError;	// latest error
	string					m_strRedundantEscapeChars;	// redundant escape characters
	long int				m_nMainClusterLines;// number of lines in main cluster
	int						m_nErrors;			// number of reported errors
	int						m_nChecksPassed;	// number of passed checks
	int						m_nChecksFailed;	// number of failed checks
	int						m_nSlaveCommunicationMode;	// mode for slave communication
	bool					m_bMasterSlaveMode;	// Master/Slave mode
};

#endif  // !ACTIONSERVER_H