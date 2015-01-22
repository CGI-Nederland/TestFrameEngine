Attribute VB_Name = "Example_main"
'###############################################################################
'#  EXAMPLE_MAIN © 1999-2007 LogicaCMG NEDERLAND B.V.
'#
'#  Description     :   Main script for the example
'#  Version         :   6.0.58.0
'#  Author          :   Leon Wolters, Andre Hooijmans
'#  Created on      :   13-07-2000
'#  Last update on  :   06-02-2007
'###############################################################################

' Declare constants
Global Const TFPath = "C:\TestFrame\"

'*******************************************************************************
'*  Procedure   :   RegisterActionWords
'*
'*  Description :   This procedure registers the action words used in the test.
'*                  Include the registration of your own action words here.
'*
'*  Parameters  :   none
'*******************************************************************************
Sub RegisterActionWords()
        
    Call tfe_RegisterActionWord("print some numbers", "print_some_numbers")
    Call tfe_RegisterActionWord("perform a check", "perform_a_check")
    Call tfe_RegisterActionWord("print an error", "print_an_error")
    
End Sub

'*******************************************************************************
'*  Procedure   :   Main
'*
'*  Description :   Main procedure of the test.
'*******************************************************************************
Sub Main()

    Dim strClusterFile As String    ' name and path of cluster file
    Dim strReportFile As String     ' name and path of report file
    Dim strIniFile As String        ' name and path of ini file
    
    ' Instanciate navigation.
    Dim oNavigation As New Example_lib

    ' Reset the Engine in case previous scripts were ended abnormally.
    Call tfe_ResetEngine

    ' Register action words.
    RegisterActionWords

    ' Define cluster, report, and ini file.
    strClusterFile = TFPath + "Cluster\Example.txt"
    strReportFile = TFPath + "Report\ExampleReport.rtf"
    strIniFile = TFPath + "engine.ini"
    
    ' Start processing the cluster; call the function ProcessCluster from the wrapper.
    Call ProcessCluster(strClusterFile, strReportFile, strIniFile, oNavigation)

    ' Call report - include the correct application to view the report
    ' and the correct report file
    Call Shell("C:\Program Files\Windows NT\Accessories\WORDPAD.EXE " + strReportFile, vbMaximizedFocus)
    
End Sub

