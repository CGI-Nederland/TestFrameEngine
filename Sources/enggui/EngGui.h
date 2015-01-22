/*****************************************************************************
 *$Workfile: EngGui.h $
 *$Revision: 1 $
 *$Modtime: 12-10-99 0:29 $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ENGGUI_H
#define ENGGUI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>         // MFC core and standard components
#include "resource.h"		// Main symbols

/////////////////////////////////////////////////////////////////////////////
// class CEngGuiApp
//
class CEngGuiApp : public CWinApp
{
public:
	CEngGuiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEngGuiApp)
	public:
	virtual int ExitInstance();
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEngGuiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !ENGGUI_H
