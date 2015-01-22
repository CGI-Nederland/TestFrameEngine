/*****************************************************************************
 * $Workfile: ReportGenerator.h $
 * $Revision: 1 $
 * $Modtime: 7/13/01 4:17p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

// Includes
#include <map>
#include <string>

using namespace std;

// Forward declarations
class EngineSetting;
class LogProcessor;
class LogStructure;
class Report;
class ReportList;

////////////////////////////////////////////////////////////////////////////////
// class ReportGenerator

class ReportGenerator
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor
	///////////////////////////////////////////////////////////////////////////////
	ReportGenerator();

	ReportGenerator(ReportGenerator&);
	ReportGenerator& operator=(ReportGenerator&);

	///////////////////////////////////////////////////////////////////////////////
	// destructor
	///////////////////////////////////////////////////////////////////////////////
	~ReportGenerator();

private:
	ReportGenerator( const ReportGenerator& src ){};	// Copy constructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Start()
	//
	// description	:	This function processes the specified log file, and
	//					generates the report(s) it specifies.
	//				
	// parameters	:	strLog			log file from which to generate the report(s)
	//					pSetting		pointer to EngineSetting object to use
	//					strMainReport	name to give to main report file
	//
	// returns		:	true	all reports specified in log generated
	//					false	not all reports specified in log could be generated
	///////////////////////////////////////////////////////////////////////////////	
	bool Start( const string& strLog, EngineSetting* pSetting,
				const string& strMainReport );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Start()
	//
	// description	:	This function is the same as the overloaded variant; only
	//					herein the name to give to main report file is not forced,
	//					taken as specified in the log file.
	//				
	// parameters	:	strLog		log file from which to generate the report(s)
	//					pSetting	pointer to EngineSetting object to use
	//
	// returns		:	true	all reports specified in log generated
	//					false	not all reports specified in log could be generated
	///////////////////////////////////////////////////////////////////////////////	
	bool Start( const string& strLog, EngineSetting* pSetting );
	
// Implementation		
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	CreateReports()
	//
	// description	:	This function generates a report for all the reports in the
	//					map; if a report can not be created, a substitute report
	//					is created in its place.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void CreateReports();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CreateSubstituteReport()
	//
	// description	:	This function creates a substitute report for a specified
	//					report file.
	//				
	// parameters	:	strReport		report file to create substitute for
	//
	// returns		:	true	substitute report created
	//					false	substitute report could not be created
	///////////////////////////////////////////////////////////////////////////////	
	bool CreateSubstituteReport( const string& strReport );

// Member variables
private:
	LogProcessor* m_pLogProcessor;			// Pointer to the LogProcessor object
	ReportList* m_pReportList;				// Pointer to the ReportList object
	Report* m_pReport;						// Pointer to the Report object

	string m_strLogFile;					// Log file
	EngineSetting* m_pSetting;				// Pointer to the EngineSetting object
	LogStructure* m_pMainCluster;			// LogStructure of main cluster

	map<string, LogStructure*> m_mReports;	// Map of report files with their
											// starting LogStructures
	string m_strMainReport;					// Forced name of the file to which to
											// write the main report
	int m_nReports;							// Number of (original) reports generated
	int m_nSubstitutes;						// Number of substitute reports generated
};

////////////////////////////////////////////////////////////////////////////////

#endif // !REPORTGENERATOR_H
 