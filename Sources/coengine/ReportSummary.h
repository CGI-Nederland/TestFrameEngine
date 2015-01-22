/*****************************************************************************
 * $Workfile: ReportSummary.h $
 * $Revision: 1 $
 * $Modtime: 8/22/01 6:23p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef REPORTSUMMARY_H
#define REPORTSUMMARY_H

// Includes
#include <string>
#include <vector>

using namespace std;

// Forward declarations
class LogStructure;
class ReportList;
class ReportTag;

////////////////////////////////////////////////////////////////////////////////
// class ReportSummary

class ReportSummary
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor
	///////////////////////////////////////////////////////////////////////////////
	ReportSummary();

	///////////////////////////////////////////////////////////////////////////////
	// destructor
	///////////////////////////////////////////////////////////////////////////////
	~ReportSummary();

private:
	ReportSummary( const ReportSummary& src ){};	// Copy constructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Initialise()
	//
	// description	:	This function initialises the ReportSummary-object.
	//					
	//				
	// parameters	:	pReportList				ReportList object
	//					pReportTag				ReportTag object
	//					pStartStruct			LogStructure from which to start
	//											taking log entries to report
	//					sstrErrorLines			Vector of line numbers on which
	//											errors occurred
	//					sstrFailedCheckLines	Vector of line numbers on which
	//											checks failed
	//
	// returns		:	true	able to create a report summary
	//					false	unable to create a report summary
	///////////////////////////////////////////////////////////////////////////////	
	bool Initialise( ReportList* pReportList,
					 ReportTag* pReportTag,
					 LogStructure* pStartStruct,
					 const vector<string>& sstrErrorLines,
					 const vector<string>& sstrFailedCheckLines );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Good()
	//
	// description	:	This function specifies whether the ReportSummary-object
	//					is able to create a report summary.
	//				
	// parameters	:	-
	//
	// returns		:	true	able to create a report summary
	//					false	unable to create a report summary
	///////////////////////////////////////////////////////////////////////////////	
	bool Good() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetSummary()
	//
	// description	:	This function returns the vector of summary lines to print.
	//				
	// parameters	:	-
	//
	// returns		:	vector of summary lines to print
	///////////////////////////////////////////////////////////////////////////////	
	const vector<string>& GetSummary() const;

// Implementation		
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	CreateSummary()
	//
	// description	:	This function creates the vector of summary lines to print.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void CreateSummary();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetStatistics()
	//
	// description	:	This function gets all the statistical numbers from the
	//					LogStructures, and places them in members.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SetStatistics();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineOutline()
	//
	// description	:	This function determines what the outline position must be,
	//					based on which tags are to be printed, and what their
	//					lengths are.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void DetermineOutline();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	TestLineSection()
	//
	// description	:	This function creates the test line section of the summary.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void TestLineSection();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ErrorSection()
	//
	// description	:	This function creates the error section of the summary.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ErrorSection();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckSection()
	//
	// description	:	This function creates the check section of the summary.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void CheckSection();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	TimeSection()
	//
	// description	:	This function creates the time section of the summary.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void TimeSection();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	NumberOfTestLines()
	//
	// description	:	This function creates the summary line for the number of
	//					test lines.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void NumberOfTestLines();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SucceededTestLines()
	//
	// description	:	This function creates the summary line for the percentage
	//					of failed test lines.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void SucceededTestLines();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	NumberOfErrors()
	//
	// description	:	This function creates the summary line for the number of
	//					errors.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void NumberOfErrors();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Warning()
	//
	// description	:	This function creates the summary line for the number of
	//					errors of the type warning, but only if there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Warning();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Error()
	//
	// description	:	This function creates the summary line for the number of
	//					errors of the type error, but only if there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void Error();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckError()
	//
	// description	:	This function creates the summary line for the number of
	//					errors of the type check, but only if there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void CheckError();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	FatalError()
	//
	// description	:	This function creates the summary line for the number of
	//					errors of the type fatal, but only if there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void FatalError();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ClusterError()
	//
	// description	:	This function creates the summary line for the number of
	//					errors of the type cluster, but only if there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ClusterError();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InternalError()
	//
	// description	:	This function creates the summary line for the number of
	//					errors of the type internal, but only if there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void InternalError();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ErrorsOnLine()
	//
	// description	:	This function creates the summary line for the list of
	//					cluster line numbers on which errors occurred, but only if
	//					there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void ErrorsOnLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	NumberOfChecks()
	//
	// description	:	This function creates the summary line for the number of
	//					checks.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void NumberOfChecks();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	PassedChecks()
	//
	// description	:	This function creates the summary line for the number and
	//					percentage of passed checks, but only if there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void PassedChecks();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	FailedChecks()
	//
	// description	:	This function creates the summary line for the number and
	//					percentage of failed checks, but only if there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void FailedChecks();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	FailsOnLine()
	//
	// description	:	This function creates the summary line for the list of
	//					cluster line numbers on which checks failed, but only if
	//					there are any.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void FailsOnLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	StartTime()
	//
	// description	:	This function creates the summary line for the starting
	//					date and time of the cluster which started this report.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void StartTime();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	StopTime()
	//
	// description	:	This function creates the summary line for the end date
	//					and time of the cluster which started this report.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void StopTime();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	TimeUsed()
	//
	// description	:	This function creates the summary line for the time used
	//					(difference between start and end time) of the cluster
	//					which started this report.
	//				
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////	
	void TimeUsed();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Spaces()
	//
	// description	:	This function returns a string consisting of a specified
	//					number of spaces.
	//				
	// parameters	:	nSpaces		number of spaces
	//
	// returns		:	string of spaces
	///////////////////////////////////////////////////////////////////////////////	
	string Spaces( int nSpaces );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Percentage()
	//
	// description	:	This function calculate the percentage for a specified part
	//					of a specified total. The percentage is given as an integer
	//					(i.e. no fractional part); the values 0 and 100 are only
	//					returned if the part is equal to zero or the total resp.
	//				
	// parameters	:	nPart		part
	//					nTotal		total
	//
	// returns		:	percentage
	///////////////////////////////////////////////////////////////////////////////	
	int Percentage( int nPart, int nTotal );

// Member variables
private:
	vector<string> m_vstrSummary;		// Vector of summary lines to print
	
	ReportList* m_pReportList;			// Pointer to the ReportList object
	ReportTag* m_pReportTag;			// Pointer to the ReportTag object
	LogStructure* m_pStartStruct;		// LogStructure from which to start
	vector<string> m_vstrErrorLines;		// Vector of line number on which errors occurred
	vector<string> m_vstrFailedCheckLines;	// Vector of line number on which checks failed

	bool m_bGood;						// States whether ReportSummary is correctly initialised

	int m_nActionWords;					// Number of action words
	int m_nFailedActionWords;			// Number of failed action words
	int m_nErrors;						// Number of errors (of all types)
	int m_nErrWarning;					// Number of errors of type warning
	int m_nErrError;					// Number of errors of type error
	int m_nErrCheck;					// Number of errors of type check
	int m_nErrFatal;					// Number of errors of type fatal
	int m_nErrCluster;					// Number of errors of type cluster
	int m_nErrIntern;					// Number of errors of type internal
	int m_nChecks;						// Number of checks (passed and failed)
	int m_nChecksPassed;				// Number of passed checks
	int m_nChecksFailed;				// Number of failed checks

	int m_nOutline;						// Outline position on a report line
};

////////////////////////////////////////////////////////////////////////////////

#endif // !REPORTSUMMARY_H
