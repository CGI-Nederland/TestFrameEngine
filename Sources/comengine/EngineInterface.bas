Attribute VB_Name = "EngineInterface"
'################################################################################
'#  ENGINE WRAPPER FOR VISUAL BASIC © 1999-2007 LogicaCMG NEDERLAND B.V.
'#
'#  Description     :   This file is the Engine wrapper for Visual Basic.
'#                      It declares the interface functions of Engine 6.0.58.
'#                      It contains the functions "ProcessCluster" and
'#                      "HandleInvalidEngineStart".
'#                      Some Engine interface functions return a char pointer
'#                      and since Visual Basic cannot deal with char pointers,
'#                      these functions' return values are placed in Longs.
'#                      The function GetStringFromAddress uses these return
'#                      values to obtain the strings from the stored addresses.
'#                      Aliases are then created of the char pointer returning
'#                      interface function so they can be called by their
'#                      original name but returning Visual Basic strings.
'#  Version         :   2.3
'#  Author          :   Edwin Torn Broers, Leon Wolters, Andre Hooijmans
'#  Created on      :   11-07-2000
'#  Last update on  :   02-11-2007
'################################################################################

'# Napi interface declaration
'############################

Declare Function napi_LoadLibrary Lib "NapiWrapper.dll" (ByVal strLibrary As String) As Integer
Declare Function napi_FreeLibrary Lib "NapiWrapper.dll" (ByVal strLibrary As String) As Integer
Declare Function napi_ExecuteActionWord Lib "NapiWrapper.dll" (ByVal strActionWord As String) As Integer

'# Declaration of kernel32 interface functions
'#############################################

Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

'# Declaration of Engine 6.0.58 interface functions
'###################################################

' Action Word Registration
Declare Function tfe_RegisterActionWord Lib "stdcoengine.dll" Alias "std_tfe_RegisterActionWord" (ByVal strActionWord As String, ByVal strActionWordFunction As String) As Integer
Declare Function tfe_RegisterHeaderWord Lib "stdcoengine.dll" Alias "std_tfe_RegisterHeaderWord" (ByVal strHeaderWord As String, ByVal strReportTag As String) As Integer
Declare Function tfe_CreateActionWordSynonym Lib "stdcoengine.dll" Alias "std_tfe_CreateActionWordSynonym" (ByVal strActionWord As String, ByVal strSynonym As String) As Integer
Declare Function tfe_UnregisterActionWord Lib "stdcoengine.dll" Alias "std_tfe_UnregisterActionWord" (ByVal strActionWord As String) As Integer
Declare Function tfe_UnregisterHeaderWord Lib "stdcoengine.dll" Alias "std_tfe_UnregisterHeaderWord" (ByVal strHeaderWord As String) As Integer
Declare Function tfe_UnregisterAllActionWords Lib "stdcoengine.dll" Alias "std_tfe_UnregisterAllActionWords" () As Integer

' State Control
Declare Function tfe_StartEngine Lib "stdcoengine.dll" Alias "std_tfe_StartEngine" (ByVal strClusterFilename As String, ByVal strReportFilename As String, ByVal strIniFile As String) As Integer
Declare Function tfe_StopEngine Lib "stdcoengine.dll" Alias "std_tfe_StopEngine" () As Integer
Declare Function tfe_ResetEngine Lib "stdcoengine.dll" Alias "std_tfe_ResetEngine" () As Integer

' Report Generating
Declare Function tfe_GenerateReport Lib "stdcoengine.dll" Alias "std_tfe_GenerateReport" () As Integer
Declare Function tfe_GenerateReportFromLog Lib "stdcoengine.dll" Alias "std_tfe_GenerateReportFromLog" (ByVal strLogFilename As String, ByVal strReportFilename As String, ByVal strIniFile As String) As Integer

' Test Flow
Declare Function tfe_ProcessNextLine Lib "stdcoengine.dll" Alias "std_tfe_ProcessNextLine" () As Integer

' Run Time Information
Declare Function vb_GetActionWord Lib "stdcoengine.dll" Alias "std_tfe_GetActionWord" () As Long
Declare Function vb_GetActionWordFunction Lib "stdcoengine.dll" Alias "std_tfe_GetActionWordFunction" () As Long
Declare Function vb_GetArgument Lib "stdcoengine.dll" Alias "std_tfe_GetArgument" (ByVal nIndex As Long) As Long
Declare Function vb_GetParameter Lib "stdcoengine.dll" Alias "std_tfe_GetParameter" (ByVal nIndex As Long) As Long
Declare Function tfe_GetNumberOfArguments Lib "stdcoengine.dll" Alias "std_tfe_GetNumberOfArguments" () As Integer
Declare Function tfe_GetNumberOfParameters Lib "stdcoengine.dll" Alias "std_tfe_GetNumberOfParameters" () As Integer
Declare Function vb_GetTestCase Lib "stdcoengine.dll" Alias "std_tfe_GetTestCase" () As Long
Declare Function vb_GetTestCondition Lib "stdcoengine.dll" Alias "std_tfe_GetTestCondition" () As Long
Declare Function vb_GetSection Lib "stdcoengine.dll" Alias "std_tfe_GetSection" () As Long
Declare Function vb_GetScenario Lib "stdcoengine.dll" Alias "std_tfe_GetScenario" () As Long
Declare Function vb_GetClusterFile Lib "stdcoengine.dll" Alias "std_tfe_GetClusterFile" () As Long
Declare Function tfe_GetLineNumber Lib "stdcoengine.dll" Alias "std_tfe_GetLineNumber" () As Integer
Declare Function tfe_GetNumberOfErrors Lib "stdcoengine.dll" Alias "std_tfe_GetNumberOfErrors" () As Integer
Declare Function vb_GetLatestError Lib "stdcoengine.dll" Alias "std_tfe_GetLatestError" () As Long
Declare Function vb_GetArgumentDescription Lib "stdcoengine.dll" Alias "std_tfe_GetArgumentDescription" (ByVal nIndex As Long) As Long
Declare Function vb_GetParameterDescription Lib "stdcoengine.dll" Alias "std_tfe_GetParameterDescription" (ByVal nIndex As Long) As Long
Declare Function vb_GetCopyright Lib "stdcoengine.dll" Alias "std_tfe_GetCopyright" () As Long
Declare Function vb_GetVersion Lib "stdcoengine.dll" Alias "std_tfe_GetVersion" () As Long
Declare Function vb_GetBuild Lib "stdcoengine.dll" Alias "std_tfe_GetBuild" () As Long
Declare Function vb_GetLogFile Lib "stdcoengine.dll" Alias "std_tfe_GetLogFile" () As Long

' Reporting
Declare Function tfe_ReportComment Lib "stdcoengine.dll" Alias "std_tfe_ReportComment" (ByVal strComment As String) As Integer
Declare Function tfe_ReportError Lib "stdcoengine.dll" Alias "std_tfe_ReportError" (ByVal strErrorText As String, ByVal nErrorTypeCode As Long) As Integer
Declare Function tfe_ReportCheck Lib "stdcoengine.dll" Alias "std_tfe_ReportCheck" (ByVal strDescription As String, ByVal strExpected As String, ByVal strRecorded As String, ByVal nCheckResult As Long) As Integer

' Checking
Declare Function tfe_CheckString Lib "stdcoengine.dll" Alias "std_tfe_CheckString" (ByVal strDescription As String, ByVal strExpected As String, ByVal strRecorded As String) As Integer
Declare Function tfe_CheckArgument Lib "stdcoengine.dll" Alias "std_tfe_CheckArgument" (ByVal nIndex As Long, ByVal strRecorded As String) As Integer
Declare Function tfe_CheckParameter Lib "stdcoengine.dll" Alias "std_tfe_CheckParameter" (ByVal nIndex As Long, ByVal strRecorded As String) As Integer

' Cluster variables
Declare Function tfe_KeepArgument Lib "stdcoengine.dll" Alias "std_tfe_KeepArgument" (ByVal nArgument As Long, ByVal strKeepValue As String) As Integer
Declare Function tfe_KeepParameter Lib "stdcoengine.dll" Alias "std_tfe_KeepParameter" (ByVal nParameter As Long, ByVal strKeepValue As String) As Integer

' GUI
Declare Function tfe_DisplayMessage Lib "stdcoengine.dll" Alias "std_tfe_DisplayMessage" (ByVal strMessage As String) As Integer

'# Declaration of Engine 6.0.58 constants.
'##########################################

' Error codes
Global Const codeWARN = 0
Global Const codeERROR = 1
Global Const codeCHCK = 2
Global Const codeFATAL = 3

'# Null-terminated string retrieval functions
'############################################

'******************************************************************************************
'*  Function    :   GetCharFromAddress
'*
'*  Description :   This function returns the character that is stored in a specified
'*                  memory address.
'*
'*  Parameters  :   lAddress    long containing memory address
'*
'*  Return      :   string containing char at address
'******************************************************************************************
Function GetCharFromAddress _
( _
                lAddress As Long _
) As String

    Dim nBuf As Integer     ' buffer to store byte in

    ' copy one byte from specified address to buffer
    Call CopyMemory(nBuf, ByVal lAddress, 1)
    
    ' convert buffered char code to vbBasic string
    GetCharFromAddress = Chr$(nBuf)
    
End Function

'******************************************************************************************
'*  Function    :   GetStringFromAddress
'*
'*  Description :   This function returns the string that is stored in a specified
'*                  memory address.
'*
'*  Parameters  :   lAddress    long containing memory address
'*
'*  Return      :   string at address
'******************************************************************************************
Function GetStringFromAddress _
( _
                lAddress As Long _
) As String

    Dim lPointer As Long        ' address of next char
    Dim strTempChar As String   ' next char
    Dim strTempString As String ' retrieved string as of yet
    
    ' initialise variables
    lPointer = lAddress
    strTempChar = ""
    strTempString = ""
    
    ' get next character of string at specified address until the null
    ' character (signifying end of string) is found
    Do
        ' get next character
        strTempChar = GetCharFromAddress(lPointer)

        ' check if found character is not null character
        If strTempChar <> Chr$(0) Then
            ' add character to string
            strTempString = strTempString + strTempChar
            ' update the address of the next char
            lPointer = lPointer + 1
        End If
    
    Loop Until strTempChar = Chr$(0)

    ' return string
    GetStringFromAddress = strTempString

End Function

Function tfe_GetActionWord() As String
    tfe_GetActionWord = GetStringFromAddress(vb_GetActionWord)
End Function

Function tfe_GetActionWordFunction() As String
    tfe_GetActionWordFunction = GetStringFromAddress(vb_GetActionWordFunction)
End Function

Function tfe_GetArgument(nIndex As Integer) As String
    tfe_GetArgument = GetStringFromAddress(vb_GetArgument(nIndex))
End Function

Function tfe_GetParameter(nIndex As Integer) As String
    tfe_GetParameter = GetStringFromAddress(vb_GetParameter(nIndex))
End Function

Function tfe_GetTestCase() As String
    tfe_GetTestCase = GetStringFromAddress(vb_GetTestCase)
End Function

Function tfe_GetTestCondition() As String
    tfe_GetTestCondition = GetStringFromAddress(vb_GetTestCondition)
End Function
Function tfe_GetSection() As String
    tfe_GetSection = GetStringFromAddress(vb_GetSection)
End Function

Function tfe_GetScenario() As String
    tfe_GetScenario = GetStringFromAddress(vb_GetScenario)
End Function

Function tfe_GetClusterFile() As String
    tfe_GetClusterFile = GetStringFromAddress(vb_GetClusterFile)
End Function

Function tfe_GetLatestError() As String
    tfe_GetLatestError = GetStringFromAddress(vb_GetLatestError)
End Function

Function tfe_GetArgumentDescription(nIndex As Integer) As String
    tfe_GetArgumentDescription = GetStringFromAddress(vb_GetArgumentDescription(nIndex))
End Function


Function tfe_GetParameterDescription(nIndex As Integer) As String
    tfe_GetParameterDescription = GetStringFromAddress(vb_GetParameterDescription(nIndex))
End Function

Function tfe_GetCopyright() As String
    tfe_GetCopyright = GetStringFromAddress(vb_GetCopyright)
End Function

Function tfe_GetVersion() As String
    tfe_GetVersion = GetStringFromAddress(vb_GetVersion)
End Function

Function tfe_GetBuild() As String
    tfe_GetBuild = GetStringFromAddress(vb_GetBuild)
End Function

Function tfe_GetLogFile() As String
    tfe_GetLogFile = GetStringFromAddress(vb_GetLogFile)
End Function

