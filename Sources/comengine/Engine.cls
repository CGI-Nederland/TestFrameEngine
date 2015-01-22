VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "engine"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'################################################################################
'#  TestFrame Engine COM interface © 1999-2007 LogicaCMG NEDERLAND B.V.
'#
'#  Description     :   This file wraps the engine interface function in class
'#                      module methods. Class module methods are COM object
'#                      methods when the project is compiled as an ActiveX dll.
'#
'#  Version         :   1.3
'#  Author          :   Edwin Torn Broers, Andre Hooijmans
'#  Created on      :   01-11-2001
'#  Last update on  :   02-11-2007
'################################################################################

' Action Word Registration
Function RegisterActionWord(ByVal strActionWord As String, ByVal strActionWordFunction As String) As Integer

    RegisterActionWord = tfe_RegisterActionWord(strActionWord, strActionWordFunction)
    
End Function

Function RegisterHeaderWord(ByVal strHeaderWord As String, ByVal strReportTag As String) As Integer

    RegisterHeaderWord = tfe_RegisterHeaderWord(strHeaderWord, strReportTag)

End Function

Function CreateActionWordSynonym(ByVal strActionWord As String, ByVal strSynonym As String) As Integer

    CreateActionWordSynonym = tfe_CreateActionWordSynonym(strActionWord, strSynonym)
    
End Function

Function UnregisterActionWord(ByVal strActionWord As String) As Integer

    UnregisterActionWord = tfe_UnregisterActionWord(strActionWord)

End Function

Function UnregisterHeaderWord(ByVal strHeaderWord As String) As Integer

    UnregisterHeaderWord = tfe_UnregisterHeaderWord(strHeaderWord)

End Function

Function UnregisterAllActionWords() As Integer

    UnregisterAllActionWords = tfe_UnregisterAllActionWords()

End Function

' State Control
Function StartEngine(ByVal strClusterFilename As String, ByVal strReportFilename As String, ByVal strIniFile As String) As Integer

    ' Check engine version And Build number
    If (GetVersion() = "6.1") And (GetBuild() = "60") Then
    
        ' Correct version, start engine
        StartEngine = tfe_StartEngine(strClusterFilename, strReportFilename, strIniFile)
    Else
        ' No, no TestFrame engine 6.0.58 only
        MsgBox ("Incorrect engine version or build, expected: 6.1 build 60, found: " + GetVersion() + " build " + GetBuild())
        
        ' Do not start engine
        StartEngine = 0
    End If
    
End Function

Function StopEngine() As Integer

    StopEngine = tfe_StopEngine
    
End Function

Function ResetEngine() As Integer

    ResetEngine = tfe_ResetEngine
    
End Function

' Report Generating
Function GenerateReport() As Integer

    GenerateReport = tfe_GenerateReport
    
End Function

Function GenerateReportFromLog(ByVal strLogFilename As String, ByVal strReportFilename As String, ByVal strIniFile As String) As Integer

    GenerateReportFromLog = tfe_GenerateReportFromLog(strLogFilename, strReportFilename, strIniFile)
    
End Function

' Test Flow
Function ProcessNextLine() As Integer

    ProcessNextLine = tfe_ProcessNextLine

End Function

' Run Time Information
Function GetActionWord() As String

    GetActionWord = tfe_GetActionWord
    
End Function

Function GetActionWordFunction() As String

    GetActionWordFunction = tfe_GetActionWordFunction
    
End Function
Function GetArgument(nIndex As Integer) As String

    GetArgument = tfe_GetArgument(nIndex)
    
End Function

Function GetParameter(nIndex As Integer) As String

    GetParameter = tfe_GetParameter(nIndex)

End Function

Function GetNumberOfArguments() As Integer

    GetNumberOfArguments = tfe_GetNumberOfArguments
    
End Function

Function GetNumberOfParameters() As Integer

    GetNumberOfParameters = tfe_GetNumberOfParameters
    
End Function

Function GetTestCase() As String

    GetTestCase = tfe_GetTestCase()
 
End Function

Function GetTestCondition() As String

    GetTestCondition = tfe_GetTestCondition()
 
End Function

Function GetSection() As String

    GetSection = tfe_GetSection()

End Function

Function GetScenario() As String

    GetScenario = tfe_GetScenario()

End Function

Function GetClusterFile() As String

    GetClusterFile = tfe_GetClusterFile

End Function

Function GetLineNumber() As Integer

    GetLineNumber = tfe_GetLineNumber()
 
End Function

Function GetNumberOfErrors() As Integer

    GetNumberOfErrors = tfe_GetNumberOfErrors()
 
End Function

Function GetLatestError() As String

    GetLatestError = tfe_GetLatestError()
    
End Function

Function GetArgumentDescription(nIndex As Integer) As String

    GetArgumentDescription = tfe_GetArgumentDescription(nIndex)

End Function

Function GetParameterDescription(nIndex As Integer) As String

    GetParameterDescription = tfe_GetParameterDescription(nIndex)

End Function

Function GetCopyright() As String

    GetCopyright = tfe_GetCopyright()
 
End Function

Function GetVersion() As String

    GetVersion = tfe_GetVersion()

End Function

Function GetBuild() As String

    GetBuild = tfe_GetBuild()

End Function

Function GetLogFile() As String

    GetLogFile = tfe_GetLogFile()

End Function

' Reporting

Function ReportComment(ByVal strComment As String) As Integer
 
    ReportComment = tfe_ReportComment(strComment)
 
End Function

Function ReportError(ByVal strErrorText As String, nErrorTypeCode As Integer) As Integer

    ReportError = tfe_ReportError(strErrorText, nErrorTypeCode)
 
End Function

Function ReportCheck(ByVal strDescription As String, ByVal strExpected As String, ByVal strRecorded As String, nCheckResult As Integer) As Integer

    ReportCheck = tfe_ReportCheck(strDescription, strExpected, strRecorded, nCheckResult)

End Function

' Checking
Function CheckString(ByVal strDescription As String, ByVal strExpected As String, ByVal strRecorded As String) As Integer

    CheckString = tfe_CheckString(strDescription, strExpected, strRecorded)

End Function

Function CheckArgument(nIndex As Long, ByVal strRecorded As String) As Integer

    CheckArgument = tfe_CheckArgument(nIndex, strRecorded)

End Function

Function CheckParameter(nIndex As Integer, ByVal strRecorded As String) As Integer

    CheckParameter = tfe_CheckParameter(nIndex, strRecorded)
    
End Function

' Cluster variables
Function KeepArgument(nArgument As Integer, ByVal strKeepValue As String) As Integer

    KeepArgument = tfe_KeepArgument(nArgument, strKeepValue)

End Function

Function KeepParameter(nArgument As Integer, ByVal strKeepValue As String) As Integer

    KeepParameter = tfe_KeepParameter(nArgument, strKeepValue)

End Function

' GUI
Function DisplayMessage(ByVal strMessage As String) As Integer

    ' PATCH, tfe_DisplayMessage DOES NOT WORK IN VERSION 5.5 BUILD 1
    ' DisplayMessage = tfe_DisplayMessage(strMessage)
    ' Let's show our own message
    MsgBox (strMessage)
    
End Function

