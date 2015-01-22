/*****************************************************************************
 * $Workfile: LogTag.h $
 * $Revision: 1 $
 * $Modtime: 6/26/01 3:11p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOGTAG_H
#define LOGTAG_H

#include <map>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// class LogTag
class LogTag
{
// Constants
public:
	enum TAG	{
					UNDEF_TAG = 0,
					
					ACTIONWORD,
					ACTIONWORD_SYNONYM,
					CHECK,
					CLUSTER_BEGIN,
					CLUSTER_END,
					CLUSTER_ERROR,
					CLUSTER_LINE,
					COMMENT_LINE,
					COMPUTER_NAME,										
					CONNECT_SLAVE,
					COPYRIGHT,
					DECLARE_TEMPLATE,
					DEFINE_TEMPLATE,
					DISCONNECT_SLAVE,
					DISPLAY_MESSAGE,
					DO_CLUSTER,
					ELSE,
					ELSE_IF,
					EMC_PAUSE,
					EMC_RESUME,
					EMC_STOP,
					EMPTY_LINE,
					END_DEFINE_TEMPLATE,
					END_IF,
					END_REPEAT,
					END_WHILE,
					ENGINE_BUILD_NUMBER,
					ENGINE_PAUSE,
					ENGINE_RESET,
					ENGINE_RESUME,
					ENGINE_START,
					ENGINE_STOP,
					ENGINE_VERSION,
					EXPORT_VARIABLE,
					HEADER_AUTHOR,
					HEADER_CLUSTER,
					HEADER_DATE,
					HEADER_DOCUMENT,
					HEADER_SHEET,
					HEADER_VERSION,
					HEADERWORD,
					IF,
					IMPORT_VARIABLE,
					INIFILE,
					INTERNAL_ERROR,
					KEEP,
					LABEL,
					LICENSE,
					LINE_TO_TEMPLATE,
					REGISTER_ACTIONWORD,
					REGISTER_HEADERWORD,
					REGISTER_TEMPLATE,
					REPEAT,
					REPORT_COMMENT,
					REPORT_ERROR,
					SET,
					SKIP,
					SLAVE_CONNECTED,
					SLAVE_DISCONNECTED,
					SLAVE_LINE,
					SNAP,
					STRUCTURE_BEGIN,
					STRUCTURE_END,
					TEMPLATE_BEGIN,
					TEMPLATE_CALL,
					TEMPLATE_DEFINED,
					TEMPLATE_END,
					TEMPLATE_PROTOTYPE,
					UNREGISTER_ACTIONWORD,
					UNREGISTER_ALL_ACTIONWORDS,
					UNREGISTER_HEADERWORD,
					USER_NAME,
					WHILE
				};

	enum ARGTAG	{
					UNDEF_ARGTAG = 100,

					ANYTHING,
					CH_ARGUMENT,
					CH_PARAMETER,
					CH_REPORT,
					CH_STRING,
					ERR_CHECK,
					ERR_ERROR,
					ERR_FATAL,
					ERR_WARNING,
					EMPTY,
					FAILED,
					IS_FALSE,
					IS_TRUE,
					NOT_EMPTY,
					OK,
					PASSED,
					TIMEOUT
				};

// Construction and destruction
public:
	LogTag();

	~LogTag();

private:
	LogTag( const LogTag& src ){};			// Copy constructor

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
	// function		:	GetArgTag()
	//
	// description	:	This function returns the specified argument-tag.
	//				  	
	// parameters	:	nArgTag		argument-tag ID
	//
	// returns		:	string containing specified argument-tag
	///////////////////////////////////////////////////////////////////////////////
	const string& GetArgTag( ARGTAG nArgTag );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetTagID()
	//
	// description	:	This function returns the ID for a specified tag.
	//				  	
	// parameters	:	strTag		tag to get ID for
	//
	// returns		:	tag ID (from TAG enum)
	///////////////////////////////////////////////////////////////////////////////
	TAG GetTagID( const string& strTag );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetArgTagID()
	//
	// description	:	This function returns the ID for a specified argument-tag.
	//				  	
	// parameters	:	strArgTag		argument-tag to get ID for
	//
	// returns		:	argument-tag ID (from ARGTAG enum)
	///////////////////////////////////////////////////////////////////////////////
	ARGTAG GetArgTagID( const string& strArgTag );

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetTags()
	//
	// description	:	This function set the values of all tags and argument-tags.
	//				  	
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void SetTags();

// Member variables
private:
	map<TAG, string> m_mTags;		// map of tags
	map<ARGTAG, string> m_mArgTags;	// map of argument-tags
};

#endif // !LOGTAG_H
