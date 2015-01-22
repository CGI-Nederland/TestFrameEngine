/*****************************************************************************
 * $Workfile: ReportTag.h $
 * $Revision: 1 $
 * $Modtime: 7/05/01 1:26p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef REPORTTAG_H
#define REPORTTAG_H

#include <map>
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// class ReportTag
class ReportTag
{
// Constants
public:
	enum TYPE	{
					ASCII = 0,
					RTF
				};

	enum TAG	{
					UNDEF_TAG = 0,

					STARTDOC,
					ENDDOC,
					FONTTABLE,
					ARIAL,
					COURIERNEW,
					COLORTABLE,
					NORMAL,
					EOLN,
					TAB,
					BIG,
					NORMALSIZE,
					SMALL,
					BOLD,
					UNBOLD,
					ITALIC,
					UNITALIC,
					UNDERLINED,
					UNUNDERLINED,
					BLACK,
					RED,
					GREEN
				};

// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor
	//
	// parameters	:	nType	file type
	///////////////////////////////////////////////////////////////////////////////
	explicit ReportTag( TYPE nType );

	///////////////////////////////////////////////////////////////////////////////
	// destructor
	///////////////////////////////////////////////////////////////////////////////
	~ReportTag();

private:
	ReportTag( const ReportTag& src ){};	// Copy constructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetTag()
	//
	// description	:	This function returns the specified tag.
	//				  	
	// parameters	:	nTag	tag ID
	//
	// returns		:	string containing specified tag
	///////////////////////////////////////////////////////////////////////////////
	const string& GetTag( TAG nTag );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetType()
	//
	// description	:	This function returns the format type.
	//				  	
	// parameters	:	nTag	tag ID
	//
	// returns		:	string containing specified tag
	///////////////////////////////////////////////////////////////////////////////
	TYPE GetType() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	UseLogo()
	//
	// description	:	This function states whether or not a logo should be placed
	//					in the report - depending on the file type.
	//				  	
	// parameters	:	-
	//
	// returns		:	true	logo should be used
	//					false	logo should not be used
	///////////////////////////////////////////////////////////////////////////////
	bool UseLogo() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetEscapeTags()
	//
	// description	:	This function returns a vector of pairs of tags which are
	//					escaped and their replacements.
	//				  	
	// parameters	:	-
	//
	// returns		:	vector of tag/replacement pairs
	///////////////////////////////////////////////////////////////////////////////
	const vector<pair<string, string> >& GetEscapeTags() const;

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetTags()
	//
	// description	:	This function sets the values of all tags.
	//				  	
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void SetTags();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetRtfTags()
	//
	// description	:	This function sets the values of all tags to RTF-tags.
	//				  	
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void SetRtfTags();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetAsciiTags()
	//
	// description	:	This function sets the values of all tags to ASCII-tags.
	//				  	
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void SetAsciiTags();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetEscapeTags()
	//
	// description	:	This function sets the values of all escape tags and their
	//					replacements.
	//				  	
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void SetEscapeTags();

// Member variables
private:
	map<TAG, string> m_mTags;							// map of tags
	TYPE m_nType;										// file type ID
	vector<pair<string, string> > m_vprstrEscapeTags;	// vector of escape tags and
														// their replacements
};

#endif // !REPORTTAG_H
