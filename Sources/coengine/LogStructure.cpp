/*****************************************************************************
 * $Workfile: LogStructure.cpp $
 * $Revision: 2 $
 * $Modtime: 11/05/01 6:29p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "LogStructure.h"			// Class definition

#include <algorithm>		// Needed for find() function
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						==========================
						LogStructure::LogStructure
//						==========================
(
	TYPE				nType,
	LogStructure*		pParent,
	const string&		strReport
)
{
	// Set the type.
	m_nType = nType;

	// Set the parent.
	m_pParent = pParent;

	// Add itself to its parent as a child, and set the parent's last line
	// as this LogStructure's parent cluster line.
	if ( m_pParent != 0 )
	{
		m_pParent->AddChild( this );
		m_nParentClusterLine = m_pParent->GetLastClusterLine();
	}
	else
	{
		m_nParentClusterLine = 0;
	}

	// Determine if the specified report is empty.
	if ( strReport.empty() )
	{
		// State that it has no report of its own, and set the report
		// to be that of its parent.
		m_bOwnReport = false;
		m_strReport = m_pParent->GetReport();
	}
	else
	{
		// State that it has its own report, and set the report name.
		m_bOwnReport = true;
		m_strReport = strReport;
	}

	// Set time members to their defaults.
	m_bComplete = false;
	m_dtStart.Set( 1, 1, 1, 0, 0, 0, 0 );
	m_dtEnd.Set( 1, 1, 1, 0, 0, 0, 0 );

	// Set error-, and check counters to zero.
	m_mErrors[ERR_WARNING] = 0;
	m_mErrors[ERR_ERROR] = 0;
	m_mErrors[ERR_CHECK] = 0;
	m_mErrors[ERR_FATAL] = 0;
	m_mErrors[ERR_CLUSTER] = 0;
	m_mErrors[ERR_INTERNAL] = 0;
	m_nChecksPassed = 0;
	m_nChecksFailed = 0;

	// Set last cluster to zero.
	m_nLastClusterLine = 0;
}


//						===========================
						LogStructure::~LogStructure()
//						===========================
{
	// Delete all child LogStructures.
	set<LogStructure*>::iterator Iterator = m_spChildren.begin();
	for ( ; Iterator != m_spChildren.end(); Iterator++ )
	{
		delete *Iterator;
//TODO:		*Iterator=0;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=====================
LogStructure::TYPE		LogStructure::GetType() const
//						=====================
{
	return m_nType;
}


//						=======================
const string&			LogStructure::GetReport() const
//						=======================
{
	return m_strReport;
}


//						==========================
bool					LogStructure::HasOwnReport() const
//						==========================
{
	return m_bOwnReport;
}


//						======================
bool					LogStructure::AddChild
//						======================
(
	LogStructure*		pChild
)
{
	bool bResult = false;

	// Determine if the specified LogStructure is not already present
	// as a child.
	if ( m_spChildren.find( pChild ) == m_spChildren.end() )
	{
		m_spChildren.insert( pChild );
		bResult = true;
	}

	return bResult;
}


//						==========================
void					LogStructure::SetStartTime
//						==========================
(
	const DateTime&		dtStart
)
{
	m_dtStart = dtStart;
}


//						==========================
DateTime				LogStructure::GetStartTime() const
//						==========================
{
	return m_dtStart;
}


//						========================
void					LogStructure::SetEndTime
//						========================
(
	const DateTime&		dtEnd
)
{
	m_dtEnd = dtEnd;
}


//						========================
DateTime				LogStructure::GetEndTime() const
//						========================
{
	return m_dtEnd;
}


//						=========================
void					LogStructure::SetComplete()
//						=========================
{
	// State that the LogStructure is complete.
	m_bComplete = true;
}


//						========================
bool					LogStructure::IsComplete() const
//						========================
{
	return m_bComplete;
}


//						========================
void					LogStructure::AddLogLine
//						========================
(
	int					nLogLine,
	int					nClusterLine
)
{
	// Add the specified log line number to the vector; only if it
	// isn't already present.
	if ( FindInt( m_vnLogLines, nLogLine ) == m_vnLogLines.end() )
	{
		m_vnLogLines.push_back( nLogLine );
	}

	// Update the last cluster line number.
	m_nLastClusterLine = nClusterLine;
}


//						=========================
LogStructure*			LogStructure::FindLogLine
//						=========================
(
	int					nLine
)
{
	LogStructure* pLogStructWithLine = 0;

	// First, search for the log line in this LogStructure's vector.
	vector<int>::iterator lineItr = FindInt( m_vnLogLines, nLine );
	if ( lineItr != m_vnLogLines.end() )
	{
		// The LogStructure which contains the specified log line number,
		// is this one.
		pLogStructWithLine = this;
	}
	else
	{
		// The specified log line number is not present in this LogStructure;
		// search its children.
		set<LogStructure*>::iterator childItr = m_spChildren.begin();
		for ( ; childItr != m_spChildren.end() && pLogStructWithLine == 0; childItr++ )
		{
			pLogStructWithLine = (*childItr)->FindLogLine( nLine );
		}
	}

	return pLogStructWithLine;
}


//						=======================
LogStructure*			LogStructure::GetParent() const
//						=======================
{
	return m_pParent;
}


//						=========================
set<LogStructure*>		LogStructure::GetChildren() const
//						=========================
{
	return m_spChildren;
}

//						================================
int						LogStructure::GetLastClusterLine() const
//						================================
{
	return m_nLastClusterLine;
}


//						==================================
int						LogStructure::GetParentClusterLine() const
//						==================================
{
	return m_nParentClusterLine;
}


//						=============================
int						LogStructure::GetFirstLogLine() const
//						=============================
{
	// Initialise the first log line number to -1.
	int nLine = -1;

	// Get the first log line number.
	if ( !m_vnLogLines.empty() )
	{
		nLine = m_vnLogLines.front();
	}

	return nLine;
}


//						============================
int						LogStructure::GetLastLogLine() const
//						============================
{
	// Initialise the first log line number to -1.
	int nLine = -1;

	// Get the last log line number.
	if ( !m_vnLogLines.empty() )
	{
		nLine = m_vnLogLines.back();
	}

	return nLine;
}


//						======================
void					LogStructure::AddError
//						======================
(
	ERR_TYPE			nErrType,
	int					nClusterLine
)
{
	// Update the number of errors of the specified type.
	m_mErrors[nErrType]++;

	// Add the specified cluster line number to the set of those with errors.
	m_snErrorLines.insert( nClusterLine );

	// Determine if the specified cluster line is in the set of
	// action word lines.
	if ( m_snActionWordLines.find( nClusterLine ) != m_snActionWordLines.end() )
	{
		// Add this line to those of failed action word lines.
		m_snFailedActionWordLines.insert( nClusterLine );
	}

	// Determine if the error type is that of a cluster error.
	if ( nErrType == ERR_CLUSTER )
	{
		// Add the cluster line number to the set of those with cluster errors,
		// if it hasn't been added already.
		if ( !HasClusterError( m_nLogLineClusterLine ) )
		{
			m_snClusterErrorLines.insert( m_nLogLineClusterLine );
		}
	}
}


//						=============================
void					LogStructure::AddChecksPassed
//						=============================
(
	int					nClusterLine
)
{
	// Update the number of passed checks.
	m_nChecksPassed++;
}


//						=============================
void					LogStructure::AddChecksFailed
//						=============================
(
	int					nClusterLine
)
{
	// Update the number of failed checks.
	m_nChecksFailed++;

	// Add the specified cluster line number to the set of those with
	// failed checks.
	m_snCheckFailedLines.insert( nClusterLine );

	// Determine if the specified cluster line is in the set of
	// action word lines.
	if ( m_snActionWordLines.find( nClusterLine ) != m_snActionWordLines.end() )
	{
		// Add this line to those of failed action word lines.
		m_snFailedActionWordLines.insert( nClusterLine );
	}
}


//						===========================
void					LogStructure::AddActionWord
//						===========================
(
	int					nClusterLine,
	int					nLogLine
)
{
	// Add the specified cluster line number to the set of those with
	// action words.
	m_snActionWordLines.insert( nClusterLine );

	// Set the specified log line number to be the last one on which a cluster
	// line keyword occured.
	m_nLogLineClusterLine = nLogLine;
}


//						==============================
bool					LogStructure::RemoveActionWord
//						==============================
(
	int					nClusterLine
)
{
	bool bResult = false;
	
	// Remove the specified cluster line number from the set
	// of those with action words.
	if ( m_snActionWordLines.erase( nClusterLine ) > 0 )
	{
		bResult = true;
	}

	return bResult;
}


//						=======================
int						LogStructure::GetErrors
//						=======================
(
	ERR_TYPE			nErrType
)
{
	// Initialise the number of errors to zero.
	int nErrors = 0;

	// Find the specified error type in the map.
	map<ERR_TYPE, int>::iterator itrErr = m_mErrors.find( nErrType );
	if ( itrErr != m_mErrors.end() )
	{
		// Get the number of errors of this type.
		nErrors = itrErr->second;
	}

	return nErrors;
}


//						=============================
int						LogStructure::GetChecksPassed() const
//						=============================
{
	return m_nChecksPassed;
}


//						=============================
int						LogStructure::GetChecksFailed() const
//						=============================
{
	return m_nChecksFailed;
}


//						============================
int						LogStructure::GetActionWords()
//						============================
{
	int nActionWords = 0;

	// If there are any action word lines added to the set, get the number.
	if ( !m_snActionWordLines.empty() )
	{
		nActionWords = m_snActionWordLines.size();
	}
	
	return nActionWords;
}


//						==================================
int						LogStructure::GetFailedActionWords()
//						==================================
{
	int nFailedActionWords = 0;

	// If there are any failed action word lines added to the set,
	// get the number.
	if ( !m_snFailedActionWordLines.empty() )
	{
		nFailedActionWords = m_snFailedActionWordLines.size();
	}
	
	return nFailedActionWords;
}


//						==========================
int						LogStructure::GetAllErrors
//						==========================
(
	ERR_TYPE			nErrType,
	bool				bOnlySameReport
)
{
	// First, get its own errors of the specified type.
	int nErrors = GetErrors( nErrType );

	// Go passed all its children.
	set<LogStructure*>::iterator itrChild = m_spChildren.begin();
	for ( ; itrChild != m_spChildren.end(); itrChild++ )
	{
		bool bThisOne = true;

		// Determine if only children which have no report of their own
		// are to be considered, and if so, whether this one has its own
		// report.
		if ( bOnlySameReport && (*itrChild)->HasOwnReport() )
		{
			// This child-LogStructure should not be considered.
			bThisOne = false;
		}

		if ( bThisOne )
		{
			// Add the child's number of errors to the previous number.
			nErrors += (*itrChild)->GetAllErrors( nErrType, bOnlySameReport );
		}
	}

	return nErrors;
}


//						================================
int						LogStructure::GetAllChecksPassed
//						================================
(
	bool				bOnlySameReport
)
{
	// First, get its own number of passed checks.
	int nChecks = m_nChecksPassed;

	// Go passed all its children.
	set<LogStructure*>::iterator itrChild = m_spChildren.begin();
	for ( ; itrChild != m_spChildren.end(); itrChild++ )
	{
		bool bThisOne = true;

		// Determine if only children which have no report of their own
		// are to be considered, and if so, whether this one has its own
		// report.
		if ( bOnlySameReport && (*itrChild)->HasOwnReport() )
		{
			// This child-LogStructure should not be considered.
			bThisOne = false;
		}

		if ( bThisOne )
		{
			// Add the child's number of passed checks to the previous number.
			nChecks += (*itrChild)->GetAllChecksPassed( bOnlySameReport );
		}
	}

	return nChecks;
}


//						================================
int						LogStructure::GetAllChecksFailed
//						================================
(
	bool				bOnlySameReport
)
{
	// First, get its own number of failed checks.
	int nChecks = m_nChecksFailed;

	// Go passed all its children.
	set<LogStructure*>::iterator itrChild = m_spChildren.begin();
	for ( ; itrChild != m_spChildren.end(); itrChild++ )
	{
		bool bThisOne = true;

		// Determine if only children which have no report of their own
		// are to be considered, and if so, whether this one has its own
		// report.
		if ( bOnlySameReport && (*itrChild)->HasOwnReport() )
		{
			// This child-LogStructure should not be considered.
			bThisOne = false;
		}

		if ( bThisOne )
		{
			// Add the child's number of passed checks to the previous number.
			nChecks += (*itrChild)->GetAllChecksFailed( bOnlySameReport );
		}
	}

	return nChecks;
}


//						===============================
int						LogStructure::GetAllActionWords
//						===============================
(
	bool				bOnlySameReport
)
{
	// First, get its own number of action words.
	int nActionWords = GetActionWords();

	// Go passed all its children.
	set<LogStructure*>::iterator itrChild = m_spChildren.begin();
	for ( ; itrChild != m_spChildren.end(); itrChild++ )
	{
		bool bThisOne = true;

		// Determine if only children which have no report of their own
		// are to be considered, and if so, whether this one has its own
		// report.
		if ( bOnlySameReport && (*itrChild)->HasOwnReport() )
		{
			// This child-LogStructure should not be considered.
			bThisOne = false;
		}

		if ( bThisOne )
		{
			// Add the child's number of passed checks to the previous number.
			nActionWords += (*itrChild)->GetAllActionWords( bOnlySameReport );
		}
	}

	return nActionWords;
}


//						=====================================
int						LogStructure::GetAllFailedActionWords
//						=====================================
(
	bool				bOnlySameReport
)
{
	// First, get its own number of action words.
	int nFailedActionWords = GetFailedActionWords();

	// Go passed all its children.
	set<LogStructure*>::iterator itrChild = m_spChildren.begin();
	for ( ; itrChild != m_spChildren.end(); itrChild++ )
	{
		bool bThisOne = true;

		// Determine if only children which have no report of their own
		// are to be considered, and if so, whether this one has its own
		// report.
		if ( bOnlySameReport && (*itrChild)->HasOwnReport() )
		{
			// This child-LogStructure should not be considered.
			bThisOne = false;
		}

		if ( bThisOne )
		{
			// Add the child's number of passed checks to the previous number.
			nFailedActionWords += (*itrChild)->GetAllFailedActionWords( bOnlySameReport );
		}
	}

	return nFailedActionWords;
}


//						=============================
bool					LogStructure::HasClusterError
//						=============================
(
	int					nLogLine
)
{
	// Determine if the specified cluster line number is present in the set
	// of those with cluster errors.
	return (m_snClusterErrorLines.find( nLogLine ) != m_snClusterErrorLines.end());
}


//						=======================
void					LogStructure::AddHeader
//						=======================
(
	const string&		strTag,
	const string&		strParameter
)
{
	// Add the tag/parameter pair to the header-vector.
	m_vpstrHeader.push_back( make_pair( strTag, strParameter ) );
}


//										=======================
const vector<pair<string, string> >&	LogStructure::GetHeader() const
//										=======================
{
	return m_vpstrHeader;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						=====================
vector<int>::iterator	LogStructure::FindInt
//						=====================
(
	vector<int>&		vnVals,
	int					nVal
)
{
	return find( vnVals.begin(), vnVals.end(), nVal );
}

///////////////////////////////////////////////////////////////////////////////
