;--------------------------------------------------------------------------------------------
; Install script for the TestFrame Engine
; (c) Copyright 2008-2013 - CGI Nederland BV
;--------------------------------------------------------------------------------------------

; Note: Make sure the Inno Setup Pre Processor is installed.
       
                                    
#define TF_Engine_Version "2013.05"
#define TF_Engine_Build   "68"
#define configuration "release"     

[Setup]
AppName=TestFrame Engine
AppVerName=TestFrame Engine v{#TF_Engine_Version} (Build {#TF_Engine_Build})
AppPublisher=CGI, Nederland BV 
AppCopyright=Copyright (C) 1997-2015 CGI, Nederland BV 
AppPublisherURL=http://www.nl.cgi.com/ 
AppSupportURL=http://www.nl.cgi.com/       
AppSupportPhone=+31(0)88 56 45360 
OutputDir=..         
OutputBaseFilename=TestFrame Engine v{#TF_Engine_Version}
DefaultDirName=C:\TestFrame
SourceDir=TestFrame
DisableDirPage=no
DefaultGroupName=CGI\TestFrame Engine
DisableProgramGroupPage=yes       
LicenseFile=License.txt                         
Compression=lzma
SolidCompression=yes


; No administrator rights are needed
PrivilegesRequired=none
       
; Needed for correctly applying the path environment variable
AlwaysRestart=yes
      
; Branding
WizardImageFile=..\Left column.bmp
WizardSmallImageFile=..\LOGICA_LOGO_SMALL.bmp
SetupIconFile=..\TF.ico


[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"

[CustomMessages]

[Dirs]
Name: "{app}\Log"
Name: "{app}\Template\Sheet"
Name: "{app}\Report\Template"

[Files]
; Base
Source: "engine.ini"; DestDir: "{app}";   Flags: ignoreversion
Source: "EULA.rtf"; DestDir: "{app}";   Flags: ignoreversion
Source: "readme1st.txt"; DestDir: "{app}";   Flags: ignoreversion
                                  
; Files for the Bin folder
; these are libraries and exectutables generated by the Engine6.sln project
Source: "..\..\Sources\output\{#configuration}\emc.exe"; DestDir: "{app}\Bin";   Flags: ignoreversion
Source: "..\..\Sources\java\TestFrame\Debug\JavaEngine.dll"; DestDir: "{app}\Bin";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\Coengine.dll"; DestDir: "{app}\Bin";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\Enggui.dll"; DestDir: "{app}\Bin";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\MessageCentre.dll"; DestDir: "{app}\Bin";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\Napiwrapper.dll"; DestDir: "{app}\Bin";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\stdcoengine.dll"; DestDir: "{app}\Bin";   Flags: ignoreversion
; ActiveX component, for use with Visual Basic 6
;Source: "..\..\Sources\output\{#configuration}\comengine.dll"; DestDir: "{app}\Bin";   Flags: ignoreversion regserver

; Cluster
; --------
Source: "Cluster\Example.xls"; DestDir: "{app}\Cluster";   Flags: ignoreversion
Source: "Cluster\Example.txt"; DestDir: "{app}\Cluster";   Flags: ignoreversion

; Documentation
; -------------
Source: "Doc\TestFrame Engine - Installation Guide.pdf"; DestDir: "{app}\Doc";   Flags: ignoreversion
Source: "Doc\TestFrame Engine - User Manual.pdf"; DestDir: "{app}\Doc";   Flags: ignoreversion

; Include           
; -------
Source: "..\..\Sources\Coengine\Coengine.h"; DestDir: "{app}\Include";   Flags: ignoreversion
Source: "..\..\Sources\Napi\Navigation\Napi.h"; DestDir: "{app}\Include\Napi";   Flags: ignoreversion
Source: "..\..\Sources\Napi\Wrapper\NapiWrapper.h"; DestDir: "{app}\Include\Napi";   Flags: ignoreversion

; Keep / Snap
; ----
Source: "Keep\keep.ini"; DestDir: "{app}\Keep";   Flags: ignoreversion
Source: "Snap\snap.ini"; DestDir: "{app}\Snap";   Flags: ignoreversion

; Libraries
; ---------
Source: "..\..\Sources\output\{#configuration}\Coengine.lib"; DestDir: "{app}\Lib";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\Navigation.lib"; DestDir: "{app}\Lib\Napi";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\NapiWrapper.lib"; DestDir: "{app}\Lib\Napi";   Flags: ignoreversion

; Report template
; ---------------
Source: "Report\Template\logo.tpl"; DestDir: "{app}\Report\Template";   Flags: ignoreversion


;----------------------------
; Scripts

; C++
Source: "Scripts\C++\Navigation\*"; DestDir: "{app}\Scripts\C++\Navigation";   Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Scripts\C++\Wrapper\*"; DestDir: "{app}\Scripts\C++\Wrapper";   Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Scripts\C++\Example start.lnk"; DestDir: "{app}\Scripts\C++";   Flags: ignoreversion
Source: "Scripts\C++\Example.bat"; DestDir: "{app}\Scripts\C++";   Flags: ignoreversion
;Source: "Scripts\C++\Example.ini"; DestDir: "{app}\Scripts\C++";   Flags: ignoreversion
Source: "Scripts\C++\README.1ST"; DestDir: "{app}\Scripts\C++";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\Example.dll"; DestDir: "{app}\Scripts\C++";   Flags: ignoreversion
Source: "..\..\Sources\output\{#configuration}\TestFrame.exe"; DestDir: "{app}\Scripts\C++";   Flags: ignoreversion

; Others
Source: "Scripts\Java\*"; DestDir: "{app}\Scripts\Java";   Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Scripts\QARun\*"; DestDir: "{app}\Scripts\QARun";   Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Scripts\Rational Robot\*"; DestDir: "{app}\Scripts\Rational Robot";   Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Scripts\Visual Basic\*"; DestDir: "{app}\Scripts\Visual Basic";   Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Scripts\WinRunner\*"; DestDir: "{app}\Scripts\WinRunner";   Flags: ignoreversion recursesubdirs createallsubdirs

[INI]
Filename: "{app}\engine.ini"; Section: "CLUSTER"; Key: "FileName"; String: "Example.txt"
Filename: "{app}\engine.ini"; Section: "CLUSTER"; Key: "Path"; String: "{app}\Cluster\"
Filename: "{app}\engine.ini"; Section: "KEEP"; Key: "Path"; String: "{app}\Keep\"
Filename: "{app}\engine.ini"; Section: "LICENSE"; Key: "Path"; String: "{app}"
Filename: "{app}\engine.ini"; Section: "LOG"; Key: "Path"; String: "{app}\Log\"
Filename: "{app}\engine.ini"; Section: "REPORT"; Key: "Path"; String: "{app}\Report\"
Filename: "{app}\engine.ini"; Section: "REPORT"; Key: "TemplatePath"; String: "{app}\Report\Template\"
Filename: "{app}\engine.ini"; Section: "SNAP"; Key: "Path"; String: "{app}\Snap\"
Filename: "{app}\engine.ini"; Section: "TEMPLATE"; Key: "Path"; String: "{app}\Template\"   

Filename: "{app}\Scripts\C++\Example.ini"; Section: "TestFrame"; Key: "Cluster"; String: "{app}\Cluster\example.txt"
Filename: "{app}\Scripts\C++\Example.ini"; Section: "TestFrame"; Key: "Report"; String: "{app}\Report\ExampleReport.rtf"
Filename: "{app}\Scripts\C++\Example.ini"; Section: "TestFrame"; Key: "IniFile"; String: "{app}\engine.ini"
Filename: "{app}\Scripts\C++\Example.ini"; Section: "TestFrame"; Key: "Library"; String: "{app}\Scripts\C++\example.dll"  
           
[Registry]
; Set the path  : HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment
Root: "HKLM"; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: expandsz; ValueName: "Path"; ValueData: "{reg:HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment,Path};{app}\Bin"

[Code]
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
S, SS: String;
begin
    if CurUninstallStep = usDone then
    begin
        RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', S);

        StringChangeEx(S, ';{app}\Bin', '', True);

        RegWriteExpandStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', S );
    end;
end;
