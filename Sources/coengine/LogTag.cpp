/*****************************************************************************
 * $Workfile: LogTag.cpp $
 * $Revision: 1 $
 * $Modtime: 6/26/01 2:08p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "LogTag.h"		// Class definition

#include <map>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						==============
						LogTag::LogTag()
//						==============
{
	SetTags();
}


//						===============
						LogTag::~LogTag()
//						===============
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						==============
const string&			LogTag::GetTag
//						==============
(
	TAG					nTag
)
{
	// Create an iterator for the map of tags; initialise it to point to
	// the specified tag in the map.
	map<TAG, string>::iterator Iterator = m_mTags.find( nTag );

	// Determine if the specified tag was found; if not, make the iterator
	// point to the UNDEF_TAG element.
	if ( Iterator == m_mTags.end() )
	{
		Iterator = m_mTags.find( UNDEF_TAG );
	}
	
	// Return the string from the map to which the iterator points.
	return Iterator->second;
}


//						=================
const string&			LogTag::GetArgTag
//						=================
(
	ARGTAG				nArgTag
)
{
	// Create an iterator for the map of argument-tags; initialise it to
	// point to the specified argument-tag in the map.
	map<ARGTAG, string>::iterator Iterator = m_mArgTags.find( nArgTag );

	// Determine if the specified argument-tag was found; if not, make the
	// iterator point to the UNDEF_ARGTAG element.
	if ( Iterator == m_mArgTags.end() )
	{
		Iterator = m_mArgTags.find( UNDEF_ARGTAG );
	}
	
	// Return the string from the map to which the iterator points.
	return Iterator->second;
}


//						================
LogTag::TAG				LogTag::GetTagID
//						================
(
	const string&		strTag
)
{
	TAG nTagID = UNDEF_TAG;

	// Create an iterator for the map of tags; initialise it to point to
	// the first tag in the map.
	map<TAG, string>::iterator Iterator = m_mTags.begin();

	// Go through all elements of the map until the specified tag is found or
	// until there are no more elements left
	bool bFound = false;
	for ( ; !bFound && Iterator != m_mTags.end(); Iterator++ )
	{
		// Determine if the tag from the map equals the one specified.
		if ( Iterator->second == strTag )
		{
			// Get the tag ID.
			nTagID = Iterator->first;
			bFound = true;
		}
	}

	return nTagID;
}


//						===================
LogTag::ARGTAG			LogTag::GetArgTagID
//						===================
(
	const string&		strArgTag
)
{
	ARGTAG nArgTagID = UNDEF_ARGTAG;

	// Create an iterator for the map of argument-tags; initialise it to point
	// to the first tag in the map.
	map<ARGTAG, string>::iterator Iterator = m_mArgTags.begin();

	// Go through all elements of the map until the specified argument-tag is
	// found or until there are no more elements left
	bool bFound = false;
	for ( ; !bFound && Iterator != m_mArgTags.end(); Iterator++ )
	{
		// Determine if the argument-tag from the map equals the one specified.
		if ( Iterator->second == strArgTag )
		{
			// Get the argument-tag ID.
			nArgTagID = Iterator->first;
			bFound = true;
		}
	}

	return nArgTagID;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						===============
void					LogTag::SetTags()
//						===============
{
	m_mTags[UNDEF_TAG]					= "";
	m_mTags[ACTIONWORD]					= "[ACTIONWORD]";
	m_mTags[ACTIONWORD_SYNONYM]			= "[ACTIONWORD_SYNONYM]";
	m_mTags[CHECK]						= "[CHECK]";
	m_mTags[CLUSTER_BEGIN]				= "[CLUSTER_BEGIN]";
	m_mTags[CLUSTER_END]				= "[CLUSTER_END]";
	m_mTags[CLUSTER_ERROR]				= "[CLUSTER_ERROR]";
	m_mTags[CLUSTER_LINE]				= "[CLUSTER_LINE]";
	m_mTags[COMMENT_LINE]				= "[COMMENT_LINE]";
	m_mTags[CONNECT_SLAVE]				= "[CONNECT_SLAVE]";
	m_mTags[COPYRIGHT]					= "[COPYRIGHT]";
	m_mTags[DECLARE_TEMPLATE]			= "[DECLARE_TEMPLATE]";
	m_mTags[DEFINE_TEMPLATE]			= "[DEFINE_TEMPLATE]";
	m_mTags[DISCONNECT_SLAVE]			= "[DISCONNECT_SLAVE]";
	m_mTags[DISPLAY_MESSAGE]			= "[DISPLAY_MESSAGE]";
	m_mTags[DO_CLUSTER]					= "[DO_CLUSTER]";
	m_mTags[ELSE]						= "[ELSE]";
	m_mTags[ELSE_IF]					= "[ELSE_IF]";
	m_mTags[EMC_PAUSE]					= "[EMC_PAUSE]";
	m_mTags[EMC_RESUME]					= "[EMC_RESUME]";
	m_mTags[EMC_STOP]					= "[EMC_STOP]";
	m_mTags[EMPTY_LINE]					= "[EMPTY_LINE]";
	m_mTags[END_DEFINE_TEMPLATE]		= "[END_DEFINE_TEMPLATE]";
	m_mTags[END_IF]						= "[END_IF]";
	m_mTags[END_REPEAT]					= "[END_REPEAT]";
	m_mTags[END_WHILE]					= "[END_WHILE]";
	m_mTags[ENGINE_BUILD_NUMBER]		= "[ENGINE_BUILD_NUMBER]";
	m_mTags[ENGINE_PAUSE]				= "[ENGINE_PAUSE]";
	m_mTags[ENGINE_RESET]				= "[ENGINE_RESET]";
	m_mTags[ENGINE_RESUME]				= "[ENGINE_RESUME]";
	m_mTags[ENGINE_START]				= "[ENGINE_START]";
	m_mTags[ENGINE_STOP]				= "[ENGINE_STOP]";
	m_mTags[ENGINE_VERSION]				= "[ENGINE_VERSION]";
	m_mTags[EXPORT_VARIABLE]			= "[EXPORT_VARIABLE]";
	m_mTags[HEADER_AUTHOR]				= "[HEADER_AUTHOR]";
	m_mTags[HEADER_CLUSTER]				= "[HEADER_CLUSTER]";
	m_mTags[HEADER_DATE]				= "[HEADER_DATE]";
	m_mTags[HEADER_DOCUMENT]			= "[HEADER_DOCUMENT]";
	m_mTags[HEADER_SHEET]				= "[HEADER_SHEET]";
	m_mTags[HEADER_VERSION]				= "[HEADER_VERSION]";
	m_mTags[HEADERWORD]					= "[HEADERWORD]";
	m_mTags[IF]							= "[IF]";
	m_mTags[IMPORT_VARIABLE]			= "[IMPORT_VARIABLE]";
	m_mTags[INIFILE]					= "[INIFILE]";
	m_mTags[INTERNAL_ERROR]				= "[INTERNAL_ERROR]";
	m_mTags[KEEP]						= "[KEEP]";
	m_mTags[LABEL]						= "[LABEL]";
	m_mTags[LICENSE]					= "[LICENSE]";
	m_mTags[LINE_TO_TEMPLATE]			= "[LINE_TO_TEMPLATE]";
	m_mTags[REGISTER_ACTIONWORD]		= "[REGISTER_ACTIONWORD]";
	m_mTags[REGISTER_HEADERWORD]		= "[REGISTER_HEADERWORD]";
	m_mTags[REGISTER_TEMPLATE]			= "[REGISTER_TEMPLATE]";
	m_mTags[REPEAT]						= "[REPEAT]";
	m_mTags[REPORT_COMMENT]				= "[REPORT_COMMENT]";
	m_mTags[REPORT_ERROR]				= "[REPORT_ERROR]";
	m_mTags[SET]						= "[SET]";
	m_mTags[SKIP]						= "[SKIP]";
	m_mTags[SLAVE_CONNECTED]			= "[SLAVE_CONNECTED]";
	m_mTags[SLAVE_DISCONNECTED]			= "[SLAVE_DISCONNECTED]";
	m_mTags[SLAVE_LINE]					= "[SLAVE_LINE]";
	m_mTags[SNAP]						= "[SNAP]";
	m_mTags[STRUCTURE_BEGIN]			= "[STRUCTURE_BEGIN]";
	m_mTags[STRUCTURE_END]				= "[STRUCTURE_END]";
	m_mTags[TEMPLATE_CALL]				= "[TEMPLATE_CALL]";
	m_mTags[TEMPLATE_DEFINED]			= "[TEMPLATE_DEFINED]";
	m_mTags[TEMPLATE_END]				= "[TEMPLATE_END]";
	m_mTags[TEMPLATE_PROTOTYPE]			= "[TEMPLATE_PROTOTYPE]";
	m_mTags[TEMPLATE_BEGIN]				= "[TEMPLATE_BEGIN]";
	m_mTags[UNREGISTER_ACTIONWORD]		= "[UNREGISTER_ACTIONWORD]";
	m_mTags[UNREGISTER_ALL_ACTIONWORDS]	= "[UNREGISTER_ALL_ACTIONWORDS]";
	m_mTags[UNREGISTER_HEADERWORD]		= "[UNREGISTER_HEADERWORD]";
	m_mTags[WHILE]						= "[WHILE]";

	m_mArgTags[UNDEF_ARGTAG]	= "";
	m_mArgTags[ANYTHING]		= "[ANYTHING]";
	m_mArgTags[CH_ARGUMENT]		= "[ARGUMENT]";
	m_mArgTags[CH_PARAMETER]	= "[PARAMETER]";
	m_mArgTags[CH_REPORT]		= "[REPORT]";
	m_mArgTags[CH_STRING]		= "[STRING]";
	m_mArgTags[EMPTY]			= "[EMPTY]";
	m_mArgTags[ERR_CHECK]		= "[CHECK]";
	m_mArgTags[ERR_ERROR]		= "[ERROR]";
	m_mArgTags[ERR_FATAL]		= "[FATAL]";
	m_mArgTags[ERR_WARNING]		= "[WARNING]";
	m_mArgTags[FAILED]			= "[FAILED]";
	m_mArgTags[IS_FALSE]		= "[FALSE]";
	m_mArgTags[IS_TRUE]			= "[TRUE]";
	m_mArgTags[NOT_EMPTY]		= "[NOT_EMPTY]";
	m_mArgTags[OK]				= "[OK]";
	m_mArgTags[PASSED]			= "[PASSED]";
	m_mArgTags[TIMEOUT]			= "[TIMEOUT]";
}
