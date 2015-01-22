/*****************************************************************************
 * $Workfile: ErrorList.h $
 * $Revision: 16 $
 * $Modtime: 8/13/01 3:25p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ERRORLIST_H
#define ERRORLIST_H

#undef BASECLASS
#define BASECLASS BabelFish

#include <string>

using namespace std;

#include "BabelFish.h"			// Definition of baseclass

////////////////////////////////////////////////////////////////////////////////
// class ErrorList

class ErrorList : public BASECLASS
{
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of ErrorList
	//
	// parameters	: nLanguage		code for selected language
	///////////////////////////////////////////////////////////////////////////////
	ErrorList();
	
	///////////////////////////////////////////////////////////////////////////////
	// destructor of ErrorList
	///////////////////////////////////////////////////////////////////////////////	
	~ErrorList();

	// String IDs
	enum 
		{	
			ID_ERR_INTERNAL_ERROR = 0,

			// Parser errors
			ID_ERR_INVALID_STRING,
			ID_ERR_NUM_ONLY_DEC,
			ID_ERR_NUM_NO_EXP,
			ID_ERR_INVALID_TOKEN,
			ID_ERR_UNEXP_EOL,
			ID_ERR_UNEXP_TOKEN,
			ID_ERR_UNEXP_ISO_NUMVAR,
			ID_ERR_UNEXP_ISO_OP,
			ID_ERR_INVALID_VAR_NAME,
			ID_ERR_ASSIGN_NO_VAR,
			ID_ERR_SUB_NO_NUM,
			ID_ERR_MUL_NO_NUM,
			ID_ERR_DIV_NO_NUM,
			ID_ERR_DIV_BY_ZERO,

			ID_ERR_DATE_NO_FORMAT,
			ID_ERR_TIME_NO_FORMAT,

			// ActionServer errors
			ID_ERR_CLUS_INVALID_ACTIONWORD,
			ID_ERR_CLUS_INVALID_SLAVE_NAME,

			ID_ERR_MAX_CLUSTERS,
			ID_ERR_CLUSTER_NOT_OPEN,

			ID_ERR_TPT_NOT_OPEN,
			ID_ERR_TPT_NO_PROTOTYPE,
			ID_ERR_TPT_REGISTERED,
			ID_ERR_TPT_NO_END_DEF,
			ID_ERR_TPT_END_FOUND,
			ID_ERR_TPT_PROTOTYPE_FOUND,
			ID_ERR_TPT_INCORRECT_NUMBER_PARAMETERS,
			ID_ERR_TPT_DIFF_DECLARATION_AND_FILE,
			ID_ERR_TPT_NO_PROTOTYPE_IN_FILE,
			ID_ERR_TPT_NO_FILE,
			ID_ERR_TPT_DIFF_REGISTERED_AND_FILE,
			ID_ERR_EXPORT_INVALID_VARIABLE,
			ID_ERR_IMPORT_INVALID_VARIABLE,
			ID_ERR_NO_VARIABLES,

			ID_ERR_PARAM_REPEAT,
			ID_ERR_NO_END_LOOP,
			ID_ERR_UNEXP_BUILT_IN,
			ID_ERR_NO_END_IF,
			ID_ERR_UNCLOSED,

			ID_ERR_COND_NUM_ARG,
			ID_ERR_COND_INVALID_OP,

			// Command errors
			ID_ERR_KEEP_INVALID_INDEX,

			NTEXTS
		};

// Member variables
private:
	static const char* m_pszTexts[NLANGS * NTEXTS]; // Texts and translations
};

////////////////////////////////////////////////////////////////////////////////

#undef BASECLASS
#endif // !ERRORLIST_H
