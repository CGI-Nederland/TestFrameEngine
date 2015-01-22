VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Example_lib"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False

'################################################################################
'#  EXAMPLE_LIB © 1999-2007 LogicaCMG NEDERLAND B.V.
'#
'#  Description     :   Library containing action word functions used in the
'#                      example.
'#  Version         :   6.0.58.0
'#  Author          :   Edwin Torn Broers, Leon Wolters, Andre Hooijmans
'#  Created on      :   11-07-2000
'#  Last update on  :   06-02-2007
'################################################################################

'******************************************************************************
'*  Procedure     :   print_some_numbers
'*
'*  Description   :   This function places the action word's first three
'*                    parameters as comment in the report.
'*
'*  AW parameters :   1   first number
'*                    2   second number
'*                    3   third number
'******************************************************************************
Sub print_some_numbers()

    ' Report parameters 1, 2, and 3 as comment.
    Call tfe_ReportComment(tfe_GetParameter(1))
    Call tfe_ReportComment(tfe_GetParameter(2))
    Call tfe_ReportComment(tfe_GetParameter(3))

End Sub

'******************************************************************************
'*  Procedure     :   perform_a_check
'*
'*  Description   :   This function checks the action word's first parameter
'*                    against the value of its second parameter.
'*
'*  AW parameters :   1   first message
'*                    2   second message
'******************************************************************************
Sub perform_a_check()

    Call tfe_CheckParameter(1, tfe_GetParameter(2))

End Sub

'******************************************************************************
'*  Procedure     :   print_an_error
'*
'*  Description   :   This function reports the value of its first parameter as
'*                    an error.
'*
'*  AW parameters :   1   error message
'******************************************************************************
Sub print_an_error()

    Call tfe_ReportError(tfe_GetParameter(1), codeERROR)

End Sub
