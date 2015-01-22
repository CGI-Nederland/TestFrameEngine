/*****************************************************************************
 *$Workfile: CMessageCentre.h $
 *$Revision: 8 $
 *$Modtime: 6/22/00 3:38p $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CMESSAGECENTRE_H
#define CMESSAGECENTRE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>			// MFC core and standard components
#include <afxcmn.h>			// MFC common controls (CProgressCtrl)
#include "resource.h"		// Main symbols

// Forward declarations
class LocalMessageCentre;

#undef BASECLASS
#define BASECLASS CDialog

/////////////////////////////////////////////////////////////////////////////
// class CMessageCentre

class CMessageCentre : public CDialog
{

// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////
	// Function:	Constructor
	// Description: Constructs this MFC dialog
	//
	// Parameters:	pDlg			Non MFC equivalent dialog
	//				hThread			Parent thread
	//				bAlwaysOnTop	Should we be always on top?
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	CMessageCentre(LocalMessageCentre* pDlg, HANDLE hThread, bool bAlwaysOnTop);
	CMessageCentre();
	~CMessageCentre();
// Attributes and operations
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetWindowTitle
	// Description: This function sets the title of this MFC dialogue
	//
	// Parameters:	pszWindowTitle	New title of window
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetWindowTitle(const char* pszWindowTitle);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetNumberOfActionWordsText
	// Description: This function sets the text label belonging to the number
	//				of action words control
	//
	// Parameters:	pszText			New text for control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfActionWordsText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetNumberOfActionWordsText
	// Description: This function sets the text in the number of action words
	//				control
	//
	// Parameters:	pszActionWords			New text for control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfActionWords(const char* pszActionWords);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetButtonPauseText
	// Description: This function sets the text label on the pause button
	//
	// Parameters:	pszText			New text for pause button
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetButtonPauseText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetButtonStopText
	// Description: This function sets the text label on the stop button
	//
	// Parameters:	pszText			New text for stop button
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetButtonStopText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetButtonDetailText
	// Description: This function sets the text label on the detail button
	//
	// Parameters:	pszText			New text for detail button
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetButtonDetailText(const char* pszText);
		
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetGroupChecksText
	// Description: This function sets the text label of the checks group
	//
	// Parameters:	pszText			New text for checks group
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetGroupChecksText(const char* pszText);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetNumberOfPassedChecksText
	// Description: This function sets the text label of the number of passed 
	//				checks control
	//
	// Parameters:	pszText			New text for checks control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfPassedChecksText(const char* pszText);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetNumberOfPassedChecks
	// Description: This function sets the number of passed checks
	//
	// Parameters:	pszPassedChecks		New text for checks control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfPassedChecks(const char* pszPassedChecks);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetNumberOfFailedChecksText
	// Description: This function sets the text label of the number of failed
	//				checks control
	//
	// Parameters:	pszText			New text for checks control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfFailedChecksText(const char* pszText);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetNumberOfPassedChecks
	// Description: This function sets the number of passed checks
	//
	// Parameters:	pszFailedChecks		New text for checks control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfFailedChecks(const char* pszFailedChecks);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetSuccessRateText
	// Description: This function sets the text label of the success rate 
	//				control
	//
	// Parameters:	pszText			New text for success rate control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetSuccessRateText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetSuccessRate
	// Description: This function sets the success rate
	//
	// Parameters:	pszSuccessRate	New success rate
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetSuccessRate(const char* pszSuccesRate);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetGroupErrorsText
	// Description: This function sets the text label of the errors group 
	//				control
	//
	// Parameters:	pszText			New text for group error control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetGroupErrorsText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetLastErrorText
	// Description: This function sets the text label of the last error control
	//
	// Parameters:	pszText			New text for last error control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetLastErrorText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetLastError
	// Description: This function sets the last error
	//
	// Parameters:	pszLastError	New last error
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetLastError(const char* pszLastError);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetNumberOfErrorsText
	// Description: This function sets the text label of the number of errors
	//				control
	//
	// Parameters:	pszText			New text for number of errors control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfErrorsText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetNumberOfErrors
	// Description: This function sets the number of errors
	//
	// Parameters:	pszErrors		New number of errors
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfErrors(const char* pszErrors);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetMessageText
	// Description: This function sets the text label of the message control
	//
	// Parameters:	pszText			New text for number of errors control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetMessageText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetMessage
	// Description: This function sets the message
	//
	// Parameters:	pszMessage		New message
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetMessage(const char* pszMessage);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetCurrentActionWordText
	// Description: This function sets the text label of the current action
	//				word control
	//
	// Parameters:	pszText			New text for current action word control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetCurrentActionWordText(const char* pszText);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetCurrentActionWord
	// Description: This function sets the current action word
	//
	// Parameters:	pszActionWord	New action word
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetCurrentActionWord(const char* pszActionWord);

	///////////////////////////////////////////////////////////////////////////
	// Function:	ShowMoreDetail
	// Description: This function makes the complete dialogue visible
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void ShowMoreDetail();

	///////////////////////////////////////////////////////////////////////////
	// Function:	ShowMoreDetail
	// Description: This function hides the detailed part of the dialogue
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void ShowLessDetail();
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetProgress
	// Description: This function sets the progress indicator
	//
	// Parameters:	nPermillage			Progress out of thousand
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetProgress(int nPermillage);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	ShowMessage
	// Description: This function show a message box with a message and a title
	//
	// Parameters:	pszMessage			Message string
	//				pszTitle			Title string
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void ShowMessage(const char* pszMessage, const char* pszTitle);

	///////////////////////////////////////////////////////////////////////////
	// Function:	Show
	// Description: This function makes the complete dialogue visible
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void Show();

	///////////////////////////////////////////////////////////////////////////
	// Function:	Hide
	// Description: This function makes the complete dialogue invisible
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void Hide();

// Dialog Data
	//{{AFX_DATA(CMessageCentre)
	enum { IDD = IDD_MESS_CENTER };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageCentre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	HICON                m_hIcon;
//	CBitmap              m_bmpDialog;

	// Generated message map functions
	//{{AFX_MSG(CMessageCentre)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetControlText
	// Description: This function sets the text of a control
	//
	// Parameters:	nControlID		ID of the dialog control
	//				pszText			New text for control
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////
	void SetControlText(int nControlID, const char* pszText);

// Member variables
private:
	// Difference in height between a detailed and a small dialog
	int m_nHeightDifference;
	
	// Pointer to the non-MFC equivalent dialog
	LocalMessageCentre* m_pDlg;

	// Remember if we should always be on top of other dialogues or not
	bool m_bAlwaysOnTop;

	// Brush to change dialog color
	CBrush	m_brush;

	// Handle to our parent thread
	HANDLE m_hThread;

//public:
//	afx_msg void OnStnClickedBmpName();
//	afx_msg void OnStnClickedBmpCompany();
//	afx_msg void OnStnClickedBmpCname();
//	afx_msg void OnStnClickedBmpTf();
//	afx_msg void OnStnClickedTxtlblChecksFailed();

private:
	CButton m_button_pauze;
	CButton m_button_stop;
	CButton m_button_detail;
public:
	afx_msg void OnBtnDetail();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnStop();
	afx_msg void OnPaint();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnNMCustomdrawProgress(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}

///////////////////////////////////////////////////////////////////////////////

#undef BASECLASS
#endif // !CMESSAGECENTRE_H
