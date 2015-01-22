/*****************************************************************************
 * $Workfile: Rtf.h $
 * $Revision: 6 $
 * $Modtime: 7/06/01 1:58p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef RTF_H
#define RTF_H

// Includes
#include <string>

using namespace std;

// Defines of Rtf-tags
// Note that the double backslashes mean an escaped backslash, since the
// backslash is a special character in Rtf (as are '{' and '}' ).
#define RTF_STARTDOC		string("{\\rtf1\\deflang1033 ")		// Open document, identify Rtf, and define language (US English)
#define RTF_ENDDOC			string("}")

#define RTF_FONTTABLE		string("{\\fonttbl{\\f0\\fswiss\\fprq2 Arial;}{\\f1\\fmodern\\fprq1 Courier New;}}")
#define RTF_ARIAL			string("\\f0 ")
#define RTF_COURIERNEW		string("\\f1 ")

#define RTF_COLORTABLE		string("{\\colortbl\\red0\\green0\\blue0;\\red255\\green0\\blue0;\\red63\\green204\\blue0;}")

#define RTF_NORMAL			string("\\plain\\pard\\f0\\fs20 ")

#define RTF_EOLN			string("\\par\n")	// the \n is here not an Rtf-tag

#define RTF_TAB				string("\\tab ")

#define RTF_BIG				string("\\fs24 ")
#define RTF_NORMALSIZE		string("\\fs20 ")
#define RTF_SMALL			string("\\fs16 ")

#define RTF_BOLD			string("\\b ")
#define RTF_UNBOLD			string("\\b0 ")
#define RTF_ITALIC			string("\\i ")
#define RTF_UNITALIC		string("\\i0 ")
#define RTF_UNDERLINED		string("\\ul ")
#define RTF_UNUNDERLINED	string("\\ul0 ")

#define RTF_BLACK			string("\\cf0 ")
#define RTF_RED				string("\\cf1 ")
#define RTF_GREEN			string("\\cf2 ")

#endif // !REPORT_H