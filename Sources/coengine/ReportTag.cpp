/*****************************************************************************
 * $Workfile: ReportTag.cpp $
 * $Revision: 1 $
 * $Modtime: 8/22/01 6:26p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "ReportTag.h"		// Class definition

#include <map>
#include <string>
#include <vector>

using namespace std;

#include "Rtf.h"			// Used for defines of Rtf-tags

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						====================
						ReportTag::ReportTag
//						====================
(
	TYPE				nType
)
{
	m_nType = nType;
	SetTags();
	SetEscapeTags();
}


//						===============
						ReportTag::~ReportTag()
//						===============
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=================
const string&			ReportTag::GetTag
//						=================
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


//						==================
ReportTag::TYPE			ReportTag::GetType() const
//						==================
{
	return m_nType;
}


//						==================
bool					ReportTag::UseLogo() const
//						==================
{
	bool bResult = false;

	// Only if the type is RTF should a logo be used.
	if ( m_nType == RTF )
	{
		bResult= true;
	}

	return bResult;
}


//										========================
const vector<pair<string, string> >&	ReportTag::GetEscapeTags() const
//										========================
{
	return m_vprstrEscapeTags;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						==================
void					ReportTag::SetTags()
//						==================
{
	m_mTags[UNDEF_TAG] = "";

	// Determine the file type and set the corresponding tags.
	switch ( m_nType )
	{
		case RTF:
		{
			SetRtfTags();
			break;
		}

		case ASCII:
		default:		// As default is taken the case ASCII.
		{
			SetAsciiTags();
			break;
		}
	}
}


//						=====================
void					ReportTag::SetRtfTags()
//						=====================
{
	// Use as Rtf-tags the defines from the header file Rtf.h.
	m_mTags[STARTDOC]		= RTF_STARTDOC;
	m_mTags[ENDDOC]			= RTF_ENDDOC;
	m_mTags[FONTTABLE]		= RTF_FONTTABLE;
	m_mTags[ARIAL]			= RTF_ARIAL;
	m_mTags[COURIERNEW]		= RTF_COURIERNEW;
	m_mTags[COLORTABLE]		= RTF_COLORTABLE;
	m_mTags[NORMAL]			= RTF_NORMAL;
	m_mTags[EOLN]			= RTF_EOLN;
	m_mTags[TAB]			= RTF_TAB;
	m_mTags[BIG]			= RTF_BIG;
	m_mTags[NORMALSIZE]		= RTF_NORMALSIZE;
	m_mTags[SMALL]			= RTF_SMALL;
	m_mTags[BOLD]			= RTF_BOLD;
	m_mTags[UNBOLD]			= RTF_UNBOLD;
	m_mTags[ITALIC]			= RTF_ITALIC;
	m_mTags[UNITALIC]		= RTF_UNITALIC;
	m_mTags[UNDERLINED]		= RTF_UNDERLINED;
	m_mTags[UNUNDERLINED]	= RTF_UNUNDERLINED;
	m_mTags[BLACK]			= RTF_BLACK;
	m_mTags[RED]			= RTF_RED;
	m_mTags[GREEN]			= RTF_GREEN;
}


//						=======================
void					ReportTag::SetAsciiTags()
//						=======================
{
	m_mTags[STARTDOC]		= "";
	m_mTags[ENDDOC]			= "";
	m_mTags[FONTTABLE]		= "";
	m_mTags[ARIAL]			= "";
	m_mTags[COURIERNEW]		= "";
	m_mTags[COLORTABLE]		= "";
	m_mTags[NORMAL]			= "";
	m_mTags[EOLN]			= "\n";
	m_mTags[TAB]			= "\t";
	m_mTags[BIG]			= "";
	m_mTags[NORMALSIZE]		= "";
	m_mTags[SMALL]			= "";
	m_mTags[BOLD]			= "";
	m_mTags[UNBOLD]			= "";
	m_mTags[ITALIC]			= "";
	m_mTags[UNITALIC]		= "";
	m_mTags[UNDERLINED]		= "";
	m_mTags[UNUNDERLINED]	= "";
	m_mTags[BLACK]			= "";
	m_mTags[RED]			= "";
	m_mTags[GREEN]			= "";
}


//						========================
void					ReportTag::SetEscapeTags()
//						========================
{
	// Determine the file type and set the corresponding tags.
	switch ( m_nType )
	{
		case RTF:
		{
			// Add the pairs of tags to escape and their replacements.
			// Note that the order in which they are placed in the vector
			// matters! The '\' must be replaced by '\\' before e.g. '{'
			// is replaced by '\{'.
			m_vprstrEscapeTags.push_back( make_pair( string("\\"), string("\\\\") ) );
			m_vprstrEscapeTags.push_back( make_pair( string("{"), string("\\{") ) );
			m_vprstrEscapeTags.push_back( make_pair( string("}"), string("\\}") ) );
			break;
		}

		case ASCII:
		default:		// As default is taken the case ASCII.
		{
			// No escape tags.
			break;
		}
	}

}
