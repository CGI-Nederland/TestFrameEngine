/*****************************************************************************
 * $Workfile: Report.h $
 * $Revision: 28 $
 * $Modtime: 11/02/01 2:05p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef REPORT_H
#define REPORT_H

// Includes
#include <map>
#include <string>
#include <vector>

using namespace std;

#undef BASECLASS
#define BASECLASS Result

#include "Result.h"			// Baseclass definition

// Forward declarations
class EngineSetting;
class LogParser;
class LogStructure;
class LogTag;
class ReportList;
class ReportTag;

////////////////////////////////////////////////////////////////////////////////
// class Report

class Report : public BASECLASS
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor
	///////////////////////////////////////////////////////////////////////////////
	Report();

	Report(Report&);
	Report& operator=(Report&);

	///////////////////////////////////////////////////////////////////////////////
	// destructor
	///////////////////////////////////////////////////////////////////////////////
	~Report();

private:
	Report( const Report& src ){};	// Copy constructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Initialise()
	//
	// description	:	This function initialises the Report-object with the
	//					report- and log-settings it needs to be able to create a
	//					report.
	//				
	// parameters	:	strLogFile			log file from which to take the data
	//					pStartStruct		LogStructure from which to start taking
	//										log entries to report
	//					bPrintParameters	states whether action parameters should
	//										be printed
	//					bOverwrite			states whether an existing report file
	//										may be overwitten
	//
	// returns		:	true	able to create a report
	//					false	unable to create a report
	///////////////////////////////////////////////////////////////////////////////	
	bool Initialise( const string& strLogFile, LogStructure* pStartStruct,
					 EngineSetting* pSetting );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Good()
	//
	// description	:	This function specifies whether the Report-object is able
	//					to create a report.
	//				
	// parameters	:	-
	//
	// returns		:	true	able to create a report
	//					false	unable to create a report
	///////////////////////////////////////////////////////////////////////////////	
	bool Good() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CreateReport()
	//
	// description	:	This function creates the specified report from its
	//					initialised settings.
	//				
	// parameters	:	strFile			report file to create
	//					strOriginal		original report file
	//
	// returns		:	true	report created
	//					false	report could not be created
	///////////////////////////////////////////////////////////////////////////////	
	bool CreateReport( const string& strFile, const string& strOriginal );

// Implementation		
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	FillActionMap()
	//
	// description	:	This function maps LogTag keyword IDs onto Report member
	//					functions.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void FillActionMap();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetCheckTags()
	//
	// description	:	This function gets the check tags (CHECK_ID, EXPECTED_ID,
	//					RECORDED_ID, and RESULT_ID) from the ReportList object,
	//					and, if necessary, pads them with spaces to line them out
	//					with each other; these new values are then stored in
	//					members.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SetCheckTags();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetFlowControlTags()
	//
	// description	:	This function gets the flow control tags (CONDITION_ID,
	//					RESULT_ID, and ITERATION_ID) from the ReportList object,
	//					and, if necessary, pads them with spaces to line them out
	//					with each other; these new values are then stored in
	//					members.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SetFlowControlTags();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetSubclusterTags()
	//
	// description	:	This function gets the subcluster tags (SUBCLUSTER_ID
	//					and REPORTNAME_ID) from the ReportList object, and, if
	//					necessary, pads them with spaces to line them out with each
	//					other; these new values are then stored in members.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SetSubclusterTags();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CreateBackup()
	//
	// description	:	This function creates a backup file for the report file if
	//					setting this report file already exists and if it is
	//					specified that a report may not be overwritten.
	//				
	// parameters	:	-
	//
	// returns		:	true	backup report created
	//					false	no backup report created
	///////////////////////////////////////////////////////////////////////////////	
	bool CreateBackup();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Stripe()
	//
	// description	:	This function returns a stripe made of a specified
	//					character.
	//				
	// parameters	:	strChar		character from which to make the stripe
	//					nLength		length of stripe
	//
	// returns		:	string containing stripe
	///////////////////////////////////////////////////////////////////////////////	
	string Stripe( const string& strChar, int nLength );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteEoln()
	//
	// description	:	This function places an 'end of line'-tag in the report
	//					file.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void WriteEoln();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteTab()
	//
	// description	:	This function places a tab-tag in the report file.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void WriteTab();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetParameter()
	//
	// description	:	This function get the specified parameter from the current
	//					log line, formats it, and returns it.
	//				
	// parameters	:	nIndex		parameter index
	//
	// returns		:	string containing formatted parameter
	///////////////////////////////////////////////////////////////////////////////	
	string GetParameter( int nIndex );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetParameters()
	//
	// description	:	This function gets all parameters from the current log
	//					line, formats them, and returns them as a vector.
	//				
	// parameters	:	-
	//
	// returns		:	vector containing formatted parameters
	///////////////////////////////////////////////////////////////////////////////	
	vector<string> GetParameters();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	FormatString()
	//
	// description	:	This function formats the referenced string by escaping all
	//					tags specified for the chosen report format.
	//				
	// parameters	:	strInput	string to format
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void FormatString( string& strInput );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteReport()
	//
	// description	:	This function writes the report file.
	//				
	// parameters	:	-
	//
	// returns		:	true	report file created
	//					false	report file could not be created
	///////////////////////////////////////////////////////////////////////////////	
	bool WriteReport();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteHeader()
	//
	// description	:	This function writes the report header in the report file.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void WriteHeader();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Ungarble()
	//
	// description	:	This function ungarbles a garbled string; i.e., all its
	//					characters (except the space) is changed to the next one in
	//					the ASCII set.
	//				
	// parameters	:	strInput	string to ungarble
	//
	// returns		:	ungarbled string
	///////////////////////////////////////////////////////////////////////////////	
	string Ungarble( const string& strInput );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	PlaceLogo()
	//
	// description	:	This function places the logo in the report file.
	//				
	// parameters	:	-
	//
	// returns		:	true	logo placed in report
	//					false	logo could not be placed in report
	///////////////////////////////////////////////////////////////////////////////	
	bool PlaceLogo();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteHeaderTags()
	//
	// description	:	This function writes the tag lines in the report header.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void WriteHeaderTags();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteTagParameterLine()
	//
	// description	:	This function writes a tag/parameter line, as specified by
	//					the tag/parameter pair, in the report file; the specified
	//					outline determines where on the line the parameter is
	//					placed.
	//				
	// parameters	:	prstrTagPar		tag/parameter pair
	//					nOutline		ouline position on line
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void WriteTagParameterLine( const pair<string, string>& prstrTagPar,
								int nOutLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteBody()
	//
	// description	:	This function creates the body of the report.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void WriteBody();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineLineNumber()
	//
	// description	:	This function returns the composite cluster line number.
	//					The current line number is taken and it is prefixed by the
	//					line numbers of its lineage of parents; however, only of
	//					parents which are of type CLUSTER or TEMPLATE.
	//				
	// parameters	:	pLogStruct		current LogStructure from which to look
	//									back for its lineage of parents
	//
	// returns		:	string containing composite line number
	///////////////////////////////////////////////////////////////////////////////	
	string DetermineLineNumber( LogStructure* pLogStruct );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ProcessLine()
	//
	// description	:	This function processes a log line by identifying its
	//					keyword and calling the member function associated with it.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ProcessLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLineNum()
	//
	// description	:	This function returns a string to place in (front of) a
	//					report line, denoting the cluster line number; only if the
	//					number is not already printed will it be returned in this
	//					string, otherwise the string is one of spaces the same
	//					length as the number (plus colon).
	//				
	// parameters	:	-
	//
	// returns		:	string containing line number to print
	///////////////////////////////////////////////////////////////////////////////	
	string GetLineNum();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetResultString()
	//
	// description	:	This function interprets the specified string as a log-
	//					argument-keyword, determines if it is the one either for
	//					TRUE or FALSE, fills the specified boolean accordingly,
	//					and returns the corresponding report-tag.
	//				
	// parameters	:	strResultKeyword	log-argument-keyword
	//					OUT bResult			to be filled with value of keyword
	//
	// returns		:	string containing report-tag for TRUE or FALSE
	///////////////////////////////////////////////////////////////////////////////	
	string GetResultString( const string& strResultKeyword, bool& bResult );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetResultString()
	//
	// description	:	This function is an overloaded version of the two-parameter
	//					GetResultString; it does the same, only there is no boolean
	//					parameter which get filled.
	//				
	// parameters	:	strResultKeyword	log-argument-keyword
	//
	// returns		:	string containing report-tag for TRUE or FALSE
	///////////////////////////////////////////////////////////////////////////////	
	string GetResultString( const string& strResultKeyword );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChildStartedOnCurrLine()
	//
	// description	:	This function determines if a child-LogStructure is started
	//					on the current cluster; if so, the pointer to it is
	//					returned; if not, the null pointer.
	//				
	// parameters	:	-
	//
	// returns		:	pointer to child-LogStructure
	///////////////////////////////////////////////////////////////////////////////	
	LogStructure* ChildStartedOnCurrLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteFooter()
	//
	// description	:	This function writes the report footer in the report file.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void WriteFooter();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddErrorLine()
	//
	// description	:	This function adds the current cluster line to the vector
	//					of those on which errors occurred; however, only if it has
	//					not already been added.
	//				
	// parameters	:	-
	//
	// returns		:	true	line added
	//					false	line was already added
	///////////////////////////////////////////////////////////////////////////////	
	bool AddErrorLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddFailedCheckLine()
	//
	// description	:	This function adds the current cluster line to the vector
	//					of those on which checks failed; however, only if it has
	//					not already been added.
	//				
	// parameters	:	-
	//
	// returns		:	true	line added
	//					false	line was already added
	///////////////////////////////////////////////////////////////////////////////	
	bool AddFailedCheckLine();

// Keyword action functions

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Default()
	//
	// description	:	This keyword action function handles the keywords which
	//					have no functions of their own; what is does, is ignoring
	//					them.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Default();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Actionword()
	//
	// description	:	This keyword action function handles the keyword
	//					ACTIONWORD.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Actionword();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Check()
	//
	// description	:	This keyword action function handles the keyword CHECK.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Check();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_ClusterError()
	//
	// description	:	This keyword action function handles the keyword
	//					CLUSTER_ERROR.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_ClusterError();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_ClusterLine()
	//
	// description	:	This keyword action function handles the keyword
	//					CLUSTER_LINE.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_ClusterLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Comment()
	//
	// description	:	This keyword action function handles the keyword
	//					REPORT_COMMENT.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Comment();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_DoCluster()
	//
	// description	:	This keyword action function handles the keyword
	//					DO_CLUSTER.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_DoCluster();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Else()
	//
	// description	:	This keyword action function handles the keyword ELSE
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Else();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_ElseIf()
	//
	// description	:	This keyword action function handles the keyword ELSE_IF.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_ElseIf();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_EMCStop()
	//
	// description	:	This keyword action function handles the keyword EMC_STOP.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_EMCStop();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_EndIf()
	//
	// description	:	This keyword action function handles the keyword END_IF.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_EndIf();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_EndRepeat()
	//
	// description	:	This keyword action function handles the keyword
	//					END_REPEAT.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_EndRepeat();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_EndWhile()
	//
	// description	:	This keyword action function handles the keyword
	//					END_WHILE.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_EndWhile();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_EnginePause()
	//
	// description	:	This keyword action function handles the keyword
	//					ENGINE_PAUSE.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_EnginePause();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_EngineReset()
	//
	// description	:	This keyword action function handles the keyword
	//					ENGINE_RESET.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_EngineReset();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_EngineResume()
	//
	// description	:	This keyword action function handles the keyword
	//					ENGINE_RESUME.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_EngineResume();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Error()
	//
	// description	:	This keyword action function handles the keyword
	//					REPORT_ERROR.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Error();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_ExportVariable()
	//
	// description	:	This keyword action function handles the keyword
	//					EXPORT_VARIABLE.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_ExportVariable();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_If()
	//
	// description	:	This keyword action function handles the keyword IF.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_If();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_ImportVariable()
	//
	// description	:	This keyword action function handles the keyword
	//					IMPORT_VARIABLE.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_ImportVariable();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_InternalError()
	//
	// description	:	This keyword action function handles the keyword
	//					INTERNAL_ERROR.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_InternalError();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Keep()
	//
	// description	:	This keyword action function handles the keyword KEEP.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Keep();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Label()
	//
	// description	:	This keyword action function handles the keyword LABEL.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Label();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Repeat()
	//
	// description	:	This keyword action function handles the keyword REPEAT.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Repeat();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Set()
	//
	// description	:	This keyword action function handles the keyword SET.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Set();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_SlaveConnected()
	//
	// description	:	This keyword action function handles the keyword
	//					SLAVE_CONNECTED.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_SlaveConnected();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_SlaveDisconnected()
	//
	// description	:	This keyword action function handles the keyword
	//					SLAVE_DISCONNECTED.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_SlaveDisconnected();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_Snap()
	//
	// description	:	This keyword action function handles the keyword SNAP.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_Snap();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_TemplateCall()
	//
	// description	:	This keyword action function handles the keyword
	//					TEMPLATE_CALL.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_TemplateCall();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_TemplateDefined()
	//
	// description	:	This keyword action function handles the keyword
	//					TEMPLATE_DEFINED.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_TemplateDefined();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Action_While()
	//
	// description	:	This keyword action function handles the keyword WHILE.
	///////////////////////////////////////////////////////////////////////////////	
	void Action_While();

// Member variables
private:
	typedef void (Report::*ActionFunction) ();
	typedef map<int, ActionFunction> ActionMap;
	ActionMap m_mAction;				// Map linking log-keywords to member functions

	LogParser* m_pLogParser;			// Pointer to the LogParser object
	LogTag* m_pLogTag;					// Pointer to the LogTag object
	ReportList* m_pReportList;			// Pointer to the ReportList object
	ReportTag* m_pReportTag;			// Pointer to the ReportTag object

	bool m_bGood;						// States whether Report is correctly initialised

	bool m_bPrintParameters;			// Setting: whether action word parameters are to be printed
	bool m_bOverwrite;					// Setting: whether a report file may be overwritten
	string m_strLogo;					// Setting: name and path of the logo-file
	string m_strEngineVersion;			// Setting: engine version
	string m_strEngineBuild;			// Setting: engine build number
	string m_strUserName;
	string m_strComputerName;
	string m_strLicenseName;			// Setting: license name
	string m_strLicenseCompany;			// Setting: license company
	string m_strLicenseNumber;			// Setting: license number

	string m_strReportFile;				// Name of the report file
	string m_strOriginalReport;			// Name of original report file
	
	string m_strLogFile;				// Name of the log file to be reported
	LogStructure* m_pStartStruct;		// LogStructure from which to start

	LogStructure* m_pCurrStruct;		// LogStructure which has the current focus
	string m_strCurrLineNum;			// Current (composite) line number
	string m_strLastReportedLine;		// Last reported (composite) line number

	string m_strDescrTag;				// Outlined tag of check description
	string m_strExpectedTag;			// Outlined tag of expected check value
	string m_strRecordedTag;			// Outlined tag of recorded check value
	string m_strResultTag;				// Outlined tag of check result

	string m_strConditionTag;			// Outlined tag of condition
	string m_strCondResultTag;			// Outlined tag of condition result
	string m_strIterationTag;			// Outlined tag of iteration

	string m_strSubclusterTag;			// Outlined tag of subcluster
	string m_strSubReportTag;			// Outlined tag of subcluster report

	vector<pair<string, string> > m_vprstrTags;	// Pairs of tags to be escaped before
												// printing, and their replacements

	vector<string> m_vstrErrorLines;		// Vector of line number on which errors occurred
	vector<string> m_vstrFailedCheckLines;	// Vector of line number on which checks failed
};

////////////////////////////////////////////////////////////////////////////////

#endif // !REPORT_H
