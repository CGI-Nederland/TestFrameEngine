/*****************************************************************************
 * $Workfile: LogStructure.h $
 * $Revision: 2 $
 * $Modtime: 11/07/01 4:11p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOGSTRUCTURE_H
#define LOGSTRUCTURE_H

// Includes
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"

////////////////////////////////////////////////////////////////////////////////
// class LogStructure

class LogStructure
{
public:
// Constants
	enum TYPE	{
					CLUSTER,
					TEMPLATE,
					STRUCTURE
				};

	enum ERR_TYPE	{
						ERR_WARNING,
						ERR_ERROR,
						ERR_CHECK,
						ERR_FATAL,
						ERR_CLUSTER,
						ERR_INTERNAL
					};

// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of LogStructure
	///////////////////////////////////////////////////////////////////////////////		
	LogStructure( TYPE nType, LogStructure* pParent, const string& strReport );

	///////////////////////////////////////////////////////////////////////////////
	// destructor of LogStructure
	///////////////////////////////////////////////////////////////////////////////		
	~LogStructure();

private:
	LogStructure( const LogStructure& src ){};	// Copy constructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetType()
	//
	// description	:	This function returns the type.
	//
	// parameters	:	-
	//
	// returns		:	integer (from TYPE enum) specifying type
	///////////////////////////////////////////////////////////////////////////////		
	TYPE GetType() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetReport()
	//
	// description	:	This function returns the report.
	//
	// parameters	:	-
	//
	// returns		:	string containing report name
	///////////////////////////////////////////////////////////////////////////////		
	const string& GetReport() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HasOwnReport()
	//
	// description	:	This function states whether this LogStructure has its own
	//					report, or whether its report is that of its parent.
	//
	// parameters	:	-
	//
	// returns		:	true	report is its own
	//					false	report is its parent's
	///////////////////////////////////////////////////////////////////////////////		
	bool HasOwnReport() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddChild()
	//
	// description	:	This function adds a specified LogStructure as a child. If
	//					it already is its child, nothing happens.
	//
	// parameters	:	-
	//
	// returns		:	true	child LogStructure added
	//					false	LogStructure was already a child
	///////////////////////////////////////////////////////////////////////////////		
	bool AddChild( LogStructure* pChild );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetStartTime()
	//
	// description	:	This function sets the starting time.
	//
	// parameters	:	dtStart		DateTime object with start time
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void SetStartTime( const DateTime& dtStart );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetStartTime()
	//
	// description	:	This function returns a DateTime object with the start
	//					date/time of the LogStructure.
	//
	// parameters	:	-
	//
	// returns		:	DateTime object with the start date/time
	///////////////////////////////////////////////////////////////////////////////		
	DateTime GetStartTime() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetEndTime()
	//
	// description	:	This function sets the end time.
	//
	// parameters	:	dtEnd		DateTime object with end time
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void SetEndTime( const DateTime& dtEnd );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetEndTime()
	//
	// description	:	This function returns a DateTime object with the end
	//					date/time of the LogStructure.
	//
	// parameters	:	-
	//
	// returns		:	DateTime object with the end date/time
	///////////////////////////////////////////////////////////////////////////////		
	DateTime GetEndTime() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetComplete()
	//
	// description	:	This function states that the LogStructure is completed
	//					by the correct tag.
	//
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void SetComplete();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	IsComplete()
	//
	// description	:	This function states whether the LogStructure is completed
	//					by the correct tag.
	//
	// parameters	:	-
	//
	// returns		:	true	completed correctly
	//					false	not completed correctly
	///////////////////////////////////////////////////////////////////////////////		
	bool IsComplete() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddLogLine()
	//
	// description	:	This function adds the specified log line number to its
	//					set, and updates the last cluster line number.
	//
	// parameters	:	nLogLine		log line number
	//					nClusterLine	log line's cluster line number
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void AddLogLine( int nLogLine, int nClusterLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	FindLogLine()
	//
	// description	:	This function determines if a specified log line belongs to
	//					this LogStructure or one of its children; if so, the
	//					pointer to the LogStructure in question is returned;
	//					if not, the null pointer.
	//
	// parameters	:	nLine		log line number to find
	//
	// returns		:	pointer to LogStructure in which log line is found
	///////////////////////////////////////////////////////////////////////////////		
	LogStructure* FindLogLine( int nLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetParent()
	//
	// description	:	This function returns the pointer to its parent-
	//					LogStructure.
	//
	// parameters	:	-
	//
	// returns		:	pointer to parent-LogStructure
	///////////////////////////////////////////////////////////////////////////////		
	LogStructure* GetParent() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetChildren()
	//
	// description	:	This function returns the set of pointers to its child-
	//					LogStructures.
	//
	// parameters	:	-
	//
	// returns		:	set of pointers to child-LogStructures
	///////////////////////////////////////////////////////////////////////////////		
	set<LogStructure*> GetChildren() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLastClusterLine()
	//
	// description	:	This function returns the last recorded cluster line
	//					number.
	//
	// parameters	:	-
	//
	// returns		:	last recorded cluster line number
	///////////////////////////////////////////////////////////////////////////////		
	int GetLastClusterLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetParentClusterLine()
	//
	// description	:	This function returns the cluster line number of its parent
	//					on which this LogStructure was started.
	//
	// parameters	:	-
	//
	// returns		:	parent cluster line number on which this one was started
	///////////////////////////////////////////////////////////////////////////////		
	int GetParentClusterLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetFirstLogLine()
	//
	// description	:	This function returns the number of its first log line.
	//
	// parameters	:	-
	//
	// returns		:	first log line number
	///////////////////////////////////////////////////////////////////////////////		
	int GetFirstLogLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLastLogLine()
	//
	// description	:	This function returns the number of its last log line.
	//
	// parameters	:	-
	//
	// returns		:	last log line number
	///////////////////////////////////////////////////////////////////////////////		
	int GetLastLogLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddError()
	//
	// description	:	This function adds an error of specified type to the
	//					LogStructure's statistics
	//
	// parameters	:	nErrType		error type
	//					nClusterLine	cluster line on which error occurred
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void AddError( ERR_TYPE nErrType, int nClusterLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddChecksPassed()
	//
	// description	:	This function adds a passed check to the LogStructure's
	//					statistics
	//
	// parameters	:	nClusterLine	cluster line on which check passed
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void AddChecksPassed( int nClusterLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddChecksFailed()
	//
	// description	:	This function adds a failed check to the LogStructure's
	//					statistics
	//
	// parameters	:	nClusterLine	cluster line on which check failed
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void AddChecksFailed( int nClusterLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddActionWord()
	//
	// description	:	This function adds an action word to the LogStructure's
	//					statistics.
	//
	// parameters	:	nClusterLine	cluster line of action word
	//					nLogLine		log line of action word
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void AddActionWord( int nClusterLine, int nLogLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	RemoveActionWord()
	//
	// description	:	This function removes an action word from the
	//					LogStructure's statistics
	//
	// parameters	:	nClusterLine	cluster line of action word
	//
	// returns		:	true	cluster line number successfully removed
	//					false	cluster line number could not be removed
	///////////////////////////////////////////////////////////////////////////////		
	bool RemoveActionWord( int nClusterLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetErrors()
	//
	// description	:	This function returns the number of errors of specified
	//					type for this LogStructure
	//
	// parameters	:	nErrType	error type
	//
	// returns		:	number of errors
	///////////////////////////////////////////////////////////////////////////////		
	int GetErrors( ERR_TYPE nErrType );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetChecksPassed()
	//
	// description	:	This function returns the number of passed checks for this
	//					LogStructure.
	//
	// parameters	:	-
	//
	// returns		:	number of passed checks
	///////////////////////////////////////////////////////////////////////////////		
	int GetChecksPassed() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetChecksFailed()
	//
	// description	:	This function returns the number of failed checks for this
	//					LogStructure.
	//
	// parameters	:	-
	//
	// returns		:	number of failed checks
	///////////////////////////////////////////////////////////////////////////////		
	int GetChecksFailed() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetActionWords()
	//
	// description	:	This function returns the number of user-defined action
	//					words for this LogStructure.
	//
	// parameters	:	-
	//
	// returns		:	number of user-defined action words
	///////////////////////////////////////////////////////////////////////////////		
	int GetActionWords();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetFailedActionWords()
	//
	// description	:	This function returns the number of user-defined action
	//					words for this LogStructure, in which an error occurred or
	//					a check failed.
	//
	// parameters	:	-
	//
	// returns		:	number of failed user-defined action words
	///////////////////////////////////////////////////////////////////////////////		
	int GetFailedActionWords();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetAllErrors()
	//
	// description	:	This function returns the number of errors of specified
	//					type for this LogStructure and its children.
	//
	// parameters	:	nErrType			error type
	//					bOnlySameReport		states whether only LogStructure with
	//										the same report as this one should be
	//										considered
	//
	// returns		:	number of errors
	///////////////////////////////////////////////////////////////////////////////		
	int GetAllErrors( ERR_TYPE nErrType, bool bOnlySameReport );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetAllChecksPassed()
	//
	// description	:	This function returns the number of passed checks for this
	//					LogStructure and its children.
	//
	// parameters	:	bOnlySameReport		states whether only LogStructure with
	//										the same report as this one should be
	//										considered
	//
	// returns		:	number of passed checks
	///////////////////////////////////////////////////////////////////////////////		
	int GetAllChecksPassed( bool bOnlySameReport );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetAllChecksFailed()
	//
	// description	:	This function returns the number of failed checks for this
	//					LogStructure and its children.
	//
	// parameters	:	bOnlySameReport		states whether only LogStructure with
	//										the same report as this one should be
	//										considered
	//
	// returns		:	number of failed checks
	///////////////////////////////////////////////////////////////////////////////		
	int GetAllChecksFailed( bool bOnlySameReport );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetAllActionWords()
	//
	// description	:	This function returns the number of user-defined action
	//					words for this LogStructure and its children.
	//
	// parameters	:	bOnlySameReport		states whether only LogStructure with
	//										the same report as this one should be
	//										considered
	//
	// returns		:	number of user-defined action words
	///////////////////////////////////////////////////////////////////////////////		
	int GetAllActionWords( bool bOnlySameReport );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetAllFailedActionWords()
	//
	// description	:	This function returns the number of user-defined action
	//					words for this LogStructure and its children, in which an
	//					error occurred or a check failed.
	//
	// parameters	:	-
	//
	// returns		:	number of failed user-defined action words
	///////////////////////////////////////////////////////////////////////////////		
	int GetAllFailedActionWords( bool bOnlySameReport );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	HasClusterError()
	//
	// description	:	This function states whether a cluster error has been found
	//					on the cluster line the specified log line number contains
	//					the 'cluster line' key of.
	//
	// parameters	:	nLogLine		log line number
	//
	// returns		:	true	cluster line contains one or more cluster errors
	//					false	cluster line contains no cluster errors
	///////////////////////////////////////////////////////////////////////////////		
	bool HasClusterError( int nClusterLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddHeader()
	//
	// description	:	This function adds a specified tag and parameter as a
	//					header pair to its vector of header pairs.
	//
	// parameters	:	strTag			header tag
	//					strParameter	corresponding parameter
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void AddHeader( const string& strTag, const string& strParameter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetHeader()
	//
	// description	:	This function returns its vector of header tag/parameter
	//					pairs.
	//
	// parameters	:	-
	//
	// returns		:	vector of header tag/parameter pairs
	///////////////////////////////////////////////////////////////////////////////		
	const vector<pair<string, string> >& GetHeader() const;

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	FindInt()
	//
	// description	:	This function finds a specified integer value in a vector
	//					of integers; the iterator to this element is returned. If
	//					the integer is absent, the 'end' iterator is returned.
	//
	// parameters	:	vnVals		vector of integers
	//					nVal		integer value to find
	//
	// returns		:	iterator to specified value in vector
	///////////////////////////////////////////////////////////////////////////////		
	vector<int>::iterator FindInt( vector<int>& vnVals, int nVal );

// Member variables
private:
	TYPE m_nType;						// Type

	LogStructure* m_pParent;			// Pointer to parent-LogStructure
	set<LogStructure*> m_spChildren;	// Set of child-LogStructures

	int m_nLastClusterLine;				// Last added cluster line
	int m_nParentClusterLine;			// Cluster line of parent at which this one was started
	
	string m_strReport;					// Report name for this LogStructure
	bool m_bOwnReport;					// States whether this LogStructure starts its own report

	bool m_bComplete;					// States whether this LogStructure is completed correctly
	DateTime m_dtStart;					// Start date/time
	DateTime m_dtEnd;					// End date/time

	map<ERR_TYPE, int> m_mErrors;		// Map of error types and their numbers
	int m_nChecksPassed;				// Number of passed checks
	int m_nChecksFailed;				// Number of failed checks

	int m_nLogLineClusterLine;			// Number of last log line on which the keyword for cluster line occured
	set<int> m_snClusterErrorLines;		// Set of log line numbers on which the keyword for cluster line occured for which cluster errors occurred

	set<int> m_snErrorLines;			// Set of cluster line numbers on which errors occurred
	set<int> m_snCheckFailedLines;		// Set of cluster line numbers on which checks failed
	set<int> m_snActionWordLines;		// Set of cluster line numbers with action words
	set<int> m_snFailedActionWordLines;	// Set of cluster line numbers with action words that failed

	vector<int> m_vnLogLines;			// Vector of log line numbers which belong to this LogStructure

	vector<pair<string, string> > m_vpstrHeader;	// Vector of header tag/parameter pairs
};

////////////////////////////////////////////////////////////////////////////////

#endif // !LOGSTRUCTURE_H
