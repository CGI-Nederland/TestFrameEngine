/*****************************************************************************
 *$Workfile: EngGui.cpp $
 *$Revision: 6 $
 *$Modtime: 21-12-99 16:58 $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <afxwin.h>
#include "EngGui.h"				// CEngGuiApp definition
#include "LocalMessageCentre.h"	// Local Engine Message Centre dialogue definition

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only MessageCentre object (ok, pointer to ...)

MessageCentre* g_pTheDlg;

/////////////////////////////////////////////////////////////////////////////
// CEngGuiApp

BEGIN_MESSAGE_MAP(CEngGuiApp, CWinApp)
	//{{AFX_MSG_MAP(CEngGuiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEngGuiApp construction

//						======================
						CEngGuiApp::CEngGuiApp()
//						======================
{ /* EMPTY */ }

/////////////////////////////////////////////////////////////////////////////
// Implementation

//						========================
BOOL					CEngGuiApp::InitInstance() 
//						========================
{
	// Clear pointer
	g_pTheDlg = 0;
	
	// Exit through the baseclass
	return CWinApp::InitInstance();
}

//						========================
int						CEngGuiApp::ExitInstance() 
//						========================
{
	// Free the memory
	if (g_pTheDlg != 0)
	{
		delete g_pTheDlg; 
		g_pTheDlg=0;
	}
	
	// Exit through the baseclass
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Exports

//						==================
extern "C" int			show_messagecenter()
//						==================
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] show_messagecenter\n");

		if (g_pTheDlg != 0)
		{
			g_pTheDlg->DoModeless();
			return TRUE;
		}
	}
	
	CATCH(CException, e)
	{
		TRACE("show_messagecenter\n");
	}
	END_CATCH

	return FALSE;
}

//						=============
extern "C" int			show_progress
//						=============
(
	int					nExecuted,	// Number of executed action words
	int					nTotal		// Total number of action words
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] show_progress\n");

		if (g_pTheDlg != 0)
		{
			g_pTheDlg->SetProgress(nExecuted, nTotal);
			
			// Successful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("show_progress\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						============								
extern "C" int			show_cluster
//						============
(
	const char*			pszCluster		// Name of the cluster
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] show_cluster\n");

		if ((g_pTheDlg != 0) && (pszCluster != 0))
		{ 
			string strCluster(pszCluster);
			g_pTheDlg->SetCurrentCluster(strCluster);
			
			// Successful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("show_cluster\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						===============
extern "C" int			show_actionword
//						===============
(
	const char*			pszActionWord	// Action word string
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] show_actionword\n");

		if ((g_pTheDlg != 0) && (pszActionWord != 0))
		{
			string strActionWord(pszActionWord);
			g_pTheDlg->SetCurrentActionWord(strActionWord);

			// Successful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("show_actionword\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						===========
extern "C" int			show_checks
//						===========
(
	int					nPassed,	// Number of passed checks
	int					nFailed		// Number of failed checks
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] show_checks\n");

		if (g_pTheDlg != 0)
		{
			g_pTheDlg->SetChecks(nPassed, nFailed);

			// Succesful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("show_checks\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						==========
extern "C" int			show_error
//						==========
(
	const char*			pszError,	// Error string
	int					nErrors		// Number of errors
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] show_error\n");

		if ((g_pTheDlg != 0) && (pszError != 0))
		{
			string strError(pszError);
			g_pTheDlg->SetError(strError, nErrors);

			// Successful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("show_error\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						============
extern "C" int			show_message
//						============
(
	const char*			pszMessage	// Message string
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] show_message\n");

		if ((g_pTheDlg != 0) && (pszMessage != 0))
		{
			string strMessage(pszMessage);
			g_pTheDlg->ShowMessage(strMessage);
			
			// Successful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("show_message\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						=============
extern "C" void			engine_paused()
//						=============
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] engine_paused\n");

		if (g_pTheDlg != 0)
		{ g_pTheDlg->Pause(); }
	}
	CATCH(CException, e)
	{
		TRACE("engine_paused\n");
	}
	END_CATCH
}

//						==============
extern "C" void			engine_resumed()
//						==============
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] engine_resumed\n");

		if (g_pTheDlg != 0)
		{ g_pTheDlg->Resume(); }
	}
	CATCH(CException, e)
	{
		TRACE("engine_resumed\n");
	}
	END_CATCH
}

//						=============
extern "C" int			register_stop
//						=============
(
	void (*pStop)(void)	// Pointer to stop function
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] register_stop\n");

		if ((g_pTheDlg != 0) && (pStop != 0))
		{
			g_pTheDlg->RegisterStop(pStop);
			
			// Successful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("register_stop\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						==============
extern "C" int			register_pause
//						==============
(
	void (*pPause)(void)	// Pointer to pause function
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] register_pause\n");

		if ((g_pTheDlg != 0) && (pPause != 0))
		{
			g_pTheDlg->RegisterPause(pPause);
			
			// Successful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("register_pause\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						===============
extern "C" int			register_resume
//						===============
(
	void (*pResume)(void)	// Pointer to resume function
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] register_resume\n");

		if ((g_pTheDlg != 0) && (pResume != 0))
		{
			g_pTheDlg->RegisterResume(pResume);
			
			// Successful
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		TRACE("register_resume\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

//						===========
extern "C" int			enggui_init
//						===========
(
 int					nDetail,
 const char*			pszLang,
 int					nOnTop,
 int					nPause
)
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] enggui_init\n");

		// Create the dialogue if this is not done already
		if ((g_pTheDlg == 0) && (pszLang != 0))
		{ 
			g_pTheDlg = new LocalMessageCentre((nDetail != 0), string(pszLang),
								(nOnTop != 0), (nPause != 0));
		}

		if (g_pTheDlg != 0)
		{ return TRUE; }
	}
	CATCH(CException, e)
	{
		TRACE("enggui_init\n");
	}
	END_CATCH


	// Not successful
	return FALSE;
}

//						===========
extern "C" int			enggui_exit()
//						===========
{
	// All exported functions should start with the AFX_MANAGE_STATE macro
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRY
	{
		OutputDebugString("[TFE6] enggui_exit\n");

		// Delete the dialog if this is not done already
		if (g_pTheDlg != 0)
		{ 
			g_pTheDlg->Exit();
			if (g_pTheDlg != 0) delete g_pTheDlg;
			g_pTheDlg = 0;
		}
		
		return TRUE;
	}
	CATCH(CException, e)
	{
		TRACE("enggui_exit\n");
	}
	END_CATCH

	// Not successful
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEngGuiApp object

CEngGuiApp g_theApp;

///////////////////////////////////////////////////////////////////////////////
