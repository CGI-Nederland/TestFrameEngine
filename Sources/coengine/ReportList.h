/*****************************************************************************
 * $Workfile: ReportList.h $
 * $Revision: 16 $
 * $Modtime: 7/05/01 5:02p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/


#ifndef REPORTLIST_H
#define REPORTLIST_H

#undef BASECLASS
#define BASECLASS BabelFish

#include <string>

using namespace std;

#include "BabelFish.h"			// Definition of superclass

////////////////////////////////////////////////////////////////////////////////
// class ReportList

class ReportList : public BASECLASS
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of ReportList
	//
	// parameters	: nLanguage		code for selected language
	///////////////////////////////////////////////////////////////////////////////
	ReportList();
	
	///////////////////////////////////////////////////////////////////////////////
	// destructor of ReportList
	///////////////////////////////////////////////////////////////////////////////	
	~ReportList();

	// String IDs
	enum 
		{	
			BRANDING_ID = 0,

			//LICENSE_NAME_ID,
			//LICENSE_COMPANY_ID,
			//SERIAL_NUMBER_ID,
			USER_NAME,
			COMPUTER_NAME,

			CLUSTERNAME_ID,
			CLUSTERVERSION_ID,
			CLUSTERDATE_ID,
			CLUSTERAUTHOR_ID,
			DOCUMENT_ID,
			SHEET_ID,

			REPORTNAME_ID,
			ENGINEVERSION_ID,
			ENGINEBUILD_ID,
			
			CHECK_ID,
			
			SECTION_ID,
			SCENARIO_ID,
			TESTCASE_ID,
			TESTCONDITION_ID,

			EXPECTED_ID,
			RECORDED_ID,
			RESULT_ID,

			ERR_WARNING_ID,
			ERR_ERROR_ID,
			ERR_CHECK_ID,
			ERR_FATAL_ID,
			ERR_CLUSTER_ID,
			ERR_INTERNAL_ID,
			ERR_UNDEFINED_ID,

			CHK_PASSED_ID,
			CHK_FAILED_ID,

			NUMTESTLINES_ID,
			SUCC_LINES_ID,
			NUMERROR_ID,
			ERROR_AT_LINE_ID,
			NUMCHECK_ID,
			NUMPASSEDCHK_ID,
			NUMFAILEDCHK_ID,
			FAIL_AT_LINE_ID,
			STARTTIME_ID,
			STOPTIME_ID,
			TIMEUSED_ID,

			ENGINE_PAUSE_ID,
			ENGINE_RESUME_ID,
			EMC_STOP_ID,

			IF_ID,
			ELSE_IF_ID,
			ELSE_ID,
			END_IF_ID,
			REPEAT_ID,
			END_REPEAT_ID,
			WHILE_ID,
			END_WHILE_ID,

			CONDITION_ID,

			TRUE_ID,
			FALSE_ID,
			ITERATION_ID,

			SET_ID,
			VARIABLE_EXPORTED_ID,
			VARIABLE_IMPORTED_ID,
			VARIABLE_KEPT_ID,
			VALUE_SNAPPED_ID,
			TEMPLATE_DEFINED_ID,
			SUBCLUSTER_ID,
			ENGINE_RESET_ID,
			SLAVE_CONNECTED_ID,
			SLAVE_CONNECT_FAIL_ID,
			SLAVE_DISCONNECTED_ID,

			NTEXTS
		};

// Member variables
private:
	static const char* m_pszTexts[NLANGS * NTEXTS]; // Texts and translations
};

////////////////////////////////////////////////////////////////////////////////

#undef BASECLASS
#endif // !REPORTLIST_H
