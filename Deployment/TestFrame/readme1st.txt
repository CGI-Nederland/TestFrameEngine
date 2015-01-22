*******************************************************************************
*                                                                             *
*  TESTFRAME ENGINE 2008.04 BUILD 60 (Windows edition)                        *
*                                                                             *
*******************************************************************************
*  Copyright (C) 1999-2008 Logica Nederland B.V.                              *
*******************************************************************************

Welcome to the TestFrame Engine, Logica's tool for processing automated 
software tests designed using the TestFrame methodology.

The Engine is the heart of TestFrame's automated test environments, linking
together test specifications, test software, and test results.

*******************************************************************************

=========================
INSTALLATION INSTRUCTIONS
=========================

1. Read the installation guide (Installation Guide.pdf) carefully.
   (Note that you need Adobe Acrobat Reader to view this document; if you do
   not have Acrobat Reader installed on your machine, you can download this
   free software from www.adobe.com)
2. Uninstall any previously installed version of the TestFrame Engine.
3. Start setup.exe.
4. Follow the instructions from the installation wizard.

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
<                                                                             <
< NOTE 1: Installation on Windows 2k, Windows XP or Windows Vista 	      <
< 	  should be performed by a user with Administrator rights. 	      <
<                                                                             <
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
<                                                                             <
< NOTE 2: It is strongly advised to uninstall any previously installed        <
< 	  version of the ConTest Engine or TestFrame Engine.                  <
<                                                                             <
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
<                                                                             <
< NOTE 3: Remember to place your license.key in the newly created directory   <
< 	  and/or adjust in the engine.ini file the key Path in the section    <
<         [LICENSE] to point to the directory where you place this license.   <
<                                                                             <
<         If you do not already have a license.key file, you can request one  <
<         by sending an e-mail to ccctesting@logica.com                       <
<                                                                             <
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

==================================================================================
DIFFERENCES BETWEEN TESTFRAME ENGINE 2008.04 BUILD 60 AND TESTFRAME ENGINE 6.0 BUILD 58 
==================================================================================

All components
--------------
Rename LogicaCMG => Logica; copyright notices/logo, etc.

Engine GUI
----------
Removed yellow background color.

==================================================================================
DIFFERENCES BETWEEN TESTFRAME ENGINE 6.0 BUILD 58 AND TESTFRAME ENGINE 6.0 BUILD 1
==================================================================================

Engine GUI
----------
A new, working, updated Windows GUI is used for the Engine Message Centre.
All logos used have been updated.

Engine Message Center (EMC)
---------------------------
Has been fixed. It could lead to crashes when trying to close a GUI.

Engine source code
------------------
The source code and the development suite,have been updated, from Visual Studio 6 
to Visual studio 2005 SP1.

Engine execution speed
----------------------
Has been improved by 15-30% (Depending on how the engine is used).

Remote GUI monitoring
---------------------
Has been fixed. It didn't work in the previous engine version.

Engine installer
----------------
A new engine installer has been used for this version. The old installer
contained several bugs and the installer size was not acceptable.

Engine static source code analysis
----------------------------------
Fixed several security and programming issues.

Windows VISTA
-------------
The engine has been tested with VISTA (Ultimate edition).

Engine interface
----------------
Added missing Engine actionwords to the COM component.
Added a JAR file as java engine interface.

Engine documentation
--------------------
Has been updated.

=======================================================================
DIFFERENCES BETWEEN TESTFRAME ENGINE 6.0 BUILD 1 AND CONTEST ENGINE 5.5
=======================================================================

Engine GUI
----------
A new -- more stable -- Windows GUI is used for the Engine Message Centre.
All logos used are now LogicaCMG logos.

Built-in action words
---------------------
A new action word DateTime is added.

Windows system directory
------------------------
The following DLL's will be installed into the Windows system directory:
msvcp60.dll
msvcp71.dll
msvcr71.dll
msvcrt.dll


=====================================================
DIFFERENCES BETWEEN CONTEST ENGINE 5.5 BUILDS 1 AND 2
=====================================================

The differences between build 1 and 2 are differences in the engine itself
(coengine.dll), differences in the number of installed components in the Bin
directory (an extra dll: comengine.dll), and differences in the Rational Robot
example.

Differences in the engine
=========================
The differences between build 1 and 2 in the engine itself are all differences
in the engine's logging and reporting functionalities.

  Log file
  --------
The internal structure of log files has been completely revised. It is now
suitable for use in the ConTest Open Logging Architecture (OLA); results can
now be placed in a database using the OLA module (separately available, not
part of this installation) and custom-made reports can be created for these
results (using third-party report generators).

  New interface: tfe_GetLogFile
  -----------------------------
For compliancy with the OLA module the Engine has a new interface function:
tfe_GetLogFile. This function does not change any previous functionality.

  Report bugs
  -----------
Several bugs in the Engine's own report generator have been fixed.

New: COM interface
==================
New to the installation of the ConTest Engine is the comengine.dll; during
installation it is placed in the Bin directory. It provides access to the
Engine as a Component Object Module (COM) object.

Differences in the Rational Robot example
=========================================
The Rational Robot example has been revised; it now accesses the Engine through
its COM interface. This solves previous problems of the combination of the
ConTest Engine and Rational Robot (see also below: limitations).
  The differences in the example are as follows: (i) the wrapper has been
changed from an SQABasic file to a Project Header File; (ii) the Engine is now
accessed through its COM interface instead of directly through its interface
functions.


===============================================================
DIFFERENCES BETWEEN CONTEST ENGINE 5.5 AND TESTFRAME ENGINE 5.0
===============================================================

For users of ConTest Engine 5.5 migrating from TestFrame Engine 5.0, below a
list is printed stating the differences in the test environment between
ConTest Engine 5.5.0.2 and TestFrame Engine 5.0.0.8.

Engine interface functions
--------------------------
ConTest Engine 5.5 contains all the interface functions of TestFrame
Engine 5.0.0.8; added to these are seven new interface functions in ConTest
Engine 5.5; these are (in alphabetical order):
  tfe_CheckParameter
  tfe_GetBuild
  tfe_GetLogFile
  tfe_GetNumberOfParameters
  tfe_GetParameter
  tfe_GetParameterDescription
  tfe_KeepParameter

Built-in action words
---------------------
ConTest Engine 5.5 contains all the built-in action words of TestFrame
Engine 5.0.0.8; added to these are nine new built-ins in ConTest Engine 5.5;
these are (in alphabetical order):
  else
  else if
  end if
  end repeat
  end while
  if
  repeat
  set
  while

Ini file settings
-----------------
There are three differences between the ini file settings of ConTest
Engine 5.5 and TestFrame Engine 5.0.0.8; from the ini file of Engine 5.5
two setting are removed, and two are added.
The removed settings are both in the section [SYSTEM]; these are:
  InterpreterMode
  NumberOfDecimals
The two new settings are both in the section [SYSTEM]; these are:
  EngineBuild
  Precision
The setting NumberOfDecimals has effectively been replaced by the setting
Precision.

Bin directory contents
----------------------
The new Engine Message Centre and the new COM interface for the Engine cause
changes to the contents of the Bin directory. Removed from the Bin directory
are the files:
  Enggui.dll
  enginegui.exe
Four new files are added to the Bin directory:
  comengine.dll
  emc.exe
  MessageCentre.dll
  qt223.dll

Windows system directory
------------------------
The installation of ConTest Engine 5.5 no longer installs mfc42.dll in the
Windows system directory.


=======================================
KNOWN LIMITATIONS OF THE CONTEST ENGINE
=======================================

1. The functionality of the interface function tfe_DisplayMessage -- the
   appearance of a message box containing a specified text whilst pausing the
   test -- has been disabled for now due to incorrect functioning.
   ------------
   Work-arounds:
   ------------
   a. When using the COM interface (as does the new Rational Robot example)
      a work-around has already been provided. So, when calling the method
      DisplayMessage of a ConTest Engine object, the proper functionality is
      provided.
   b. In other cases similar functionality can often be obtained by using
      functions from the programming language of the test environment of choice
      instead.
      So, if we want to display the text placed in the variable strMessage,
      we can:
      - in WinRunner's TSL use the call: 
           Pause( strMessage );
      - in QARun's Language use the call:
           MsgBox( "TestFrame Message", strMessage )
      - in Visual Basic use the call:
           MsgBox ( strMessage )

2. The combination of Rational Robot 2001 and ConTest Engine can cause the
   system to lock if a Robot script is interrupted during playback.
   ----
   Note: This limitation only occurs for Rational Robot version 2001; previous
   ----  versions of Robot do not show this restriction when the COM interface
         is used.

*******************************************************************************

Copyright (C) 1999-2007 by LogicaCMG Nederland B.V.

All rights reserved. No part of this publication may be reproduced, or stored
in a retrieval system, or transmitted, in any form, or by any other means,
electronic, mechanical, photocopying, recording, or otherwise, without the
prior consent of the copyright holder.

TestFrame is a trademark of LogicaCMG.

This document also contains registered trademarks and trademarks which are
owned by their respective companies or organizations. LogicaCMG disclaims any
responsibility for specifying which marks are owned by which companies or
organizations.

While every precaution has been taken in the preparation of this document,
LogicaCMG assumes no responsibility for errors or omissions, or for damages
resulting from the use of the information contained herein.

For more information on LogicaCMG and TestFrame visit:
http://www.logicacmg.com
http://www.testframe.com

For more information on the ConTest Engine write to:
engine5@logicacmg.nl

LogicaCMG Pubblic sector
Public Sector Technical Competence (PSTC)
P.O. Box 3190
2280 GD Rijswijk
The Netherlands
Telephone:	+31 (0)70 375 6000
Telefax:	+31 (0)70 375 6710

*******************************************************************************