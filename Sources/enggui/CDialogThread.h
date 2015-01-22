/*****************************************************************************
 *$Workfile: CDialogThread.h $
 *$Revision: 4 $
 *$Modtime: 29-10-99 15:43 $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CDIALOGTHREAD_H
#define CDIALOGTHREAD_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// class CDialogThread

class CDialogThread : public CWinThread
{
	DECLARE_DYNCREATE(CDialogThread)
public:
	CDialogThread();
	virtual ~CDialogThread();
// Attributes
public:

	bool isThreadRunning();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetDlg
	// Description: This function sets the member variable that points to the MFC
	//				dialog
	//
	// Parameters:	pDlg			Pointer to a CDialog
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	void SetDlg(CDialog* pDlg);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Member variables
private:
	// The MFC dialog
	CDialog* m_pDlg;

	// Bart Beumer CHANGE: hier slaan we in op of de thread actief is ja/nee
	bool m_bThreadIsRunning;
};

///////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !CDIALOGTHREAD
