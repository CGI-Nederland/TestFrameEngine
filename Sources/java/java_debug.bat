rem Build a debug version of the Java Wrapper and example

rem Compile the Java classes
javac TestFrame.java

rem Create a C/C++ header file and copy it to the right directory
javah -jni TestFrame.Engine
copy TestFrame_Engine.h TestFrame

rem Copy the right Coengine.lib
copy c:\engine5\source\output\debug\coengine.lib TestFrame

rem Compile the JNI dll
msdev c:\engine5\source\java\TestFrame\TestFrame.dsw /MAKE "TestFrame - Win32 Debug" /REBUILD

rem Create the Java documentation
javadoc -version -author -d doc TestFrame