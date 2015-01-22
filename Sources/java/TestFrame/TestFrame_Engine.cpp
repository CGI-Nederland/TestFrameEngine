/*****************************************************************************
 * $Workfile: TestFrame_Engine.cpp $
 * $Revision: 10 $
 * $Modtime: 01/26/2007 2:53p $
 * $Author: Lw, AH $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000-2013 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "TestFrame_Engine.h"	// Interface generated with Javah.exe
#include "Coengine.h"			// TestFrame Engine interface

// This DLL is used to provide the calling Java program access to the TestFrame
// ConTest Engine 6.0, which is written in C++. This is done through the Java Native
// Interface (JNI) from JDK 1.6.
//
// See the file Coengine.h for an explanation of the TestFrame interface functions.
// See The Java Tutorial for an explanation of the Java Native Interface.
// (http://java. sun.com/docs/books/tutorial/native1.1/)

///////////////////////////////////////////////////////////////////////////////
// ENGINE CONSTRUCTION AND DESTRUCTION UNIX USE ONLY

//JNIEXPORT void JNICALL Java_TestFrame_Engine_CreateEngine(JNIEnv* pEnv, jclass cl)
//{
//	// Call the C++ Engine
//	tfe_CreateEngine();
//}

//JNIEXPORT void JNICALL Java_TestFrame_Engine_DeleteEngine(JNIEnv* pEnv, jclass cl)
//{
//	// Call the C++ Engine
//	tfe_DeleteEngine();
//}

///////////////////////////////////////////////////////////////////////////////
//	ACTION WORD REGISTRATION

JNIEXPORT jint JNICALL Java_TestFrame_Engine_RegisterActionWord(JNIEnv* pEnv, jclass cl, jstring strActionWord, jstring strActionWordFunction)
{
	// Convert Java strings to char pointers
	const char* pszActionWord =			pEnv->GetStringUTFChars(strActionWord, 0);
	const char* pszActionWordFunction = pEnv->GetStringUTFChars(strActionWordFunction, 0);

	// Call the C++ Engine
	jint nResult = tfe_RegisterActionWord(pszActionWord, pszActionWordFunction);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strActionWord, pszActionWord);
	pEnv->ReleaseStringUTFChars(strActionWordFunction, pszActionWordFunction);

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_RegisterHeaderWord(JNIEnv* pEnv, jclass cl, jstring strHeaderWord, jstring strHeaderWordFunction)
{
	// Convert Java strings to char pointers
	const char* pszHeaderWord =			pEnv->GetStringUTFChars(strHeaderWord, 0);
	const char* pszHeaderWordFunction = pEnv->GetStringUTFChars(strHeaderWordFunction, 0);

	// Call the C++ Engine
	jint nResult = tfe_RegisterHeaderWord(pszHeaderWord, pszHeaderWordFunction);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strHeaderWord, pszHeaderWord);
	pEnv->ReleaseStringUTFChars(strHeaderWordFunction, pszHeaderWordFunction);

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_CreateActionWordSynonym(JNIEnv* pEnv, jclass cl, jstring strActionWord, jstring strSynonym)
{
	// Convert Java strings to char pointers
	const char* pszActionWord =			pEnv->GetStringUTFChars(strActionWord, 0);
	const char* pszSynonym =			pEnv->GetStringUTFChars(strSynonym, 0);

	// Call the C++ Engine
	jint nResult = tfe_CreateActionWordSynonym(pszActionWord, pszSynonym);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strActionWord, pszActionWord);
	pEnv->ReleaseStringUTFChars(strSynonym, pszSynonym);

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_UnregisterActionWord(JNIEnv* pEnv, jclass cl, jstring strActionWord)
{
	// Convert Java string to char pointer
	const char* pszActionWord =	pEnv->GetStringUTFChars(strActionWord, 0);

	// Call the C++ Engine
	jint nResult = tfe_UnregisterActionWord(pszActionWord);

	// Release Java string buffer allocated during conversion to char pointer
	pEnv->ReleaseStringUTFChars(strActionWord, pszActionWord);

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_UnRegisterHeaderWord(JNIEnv* pEnv, jclass cl, jstring strHeaderWord)
{
	// Convert Java string to char pointer
	const char* pszHeaderWord =	pEnv->GetStringUTFChars(strHeaderWord, 0);

	// Call the C++ Engine
	jint nResult = tfe_UnregisterHeaderWord(pszHeaderWord);

	// Release Java string buffer allocated during conversion to char pointer
	pEnv->ReleaseStringUTFChars(strHeaderWord, pszHeaderWord);

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_UnregisterAllActionWords(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine
	jint nResult = tfe_UnregisterAllActionWords();

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
//	STATE CONTROL
	
JNIEXPORT jint JNICALL Java_TestFrame_Engine_StartEngine(JNIEnv* pEnv, jclass cl, jstring strClusterFile, jstring strReportFile, jstring strIniFile)
{
	// Convert Java strings to char pointers
	const char* pszClusterFile =	pEnv->GetStringUTFChars(strClusterFile, 0);
	const char* pszReportFile =		pEnv->GetStringUTFChars(strReportFile, 0);
	const char* pszIniFile =		pEnv->GetStringUTFChars(strIniFile, 0);

	// Call the C++ Engine
	jint nResult = tfe_StartEngine(pszClusterFile, pszReportFile, pszIniFile);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strClusterFile, pszClusterFile);
	pEnv->ReleaseStringUTFChars(strReportFile, pszReportFile );
	pEnv->ReleaseStringUTFChars(strIniFile, pszIniFile);

	return nResult;
}


JNIEXPORT jint JNICALL Java_TestFrame_Engine_StopEngine(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine
	jint nResult = tfe_StopEngine();

	return nResult;
}


///////////////////////////////////////////////////////////////////////////////
//	REPORT GENERATING
JNIEXPORT jint JNICALL Java_TestFrame_Engine_GenerateReport(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine
	jint nResult = tfe_GenerateReport();

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_GenerateReportFromLog(JNIEnv* pEnv, jclass cl, jstring strLogFile, jstring strReportFile, jstring strIniFile)
{
	// Convert Java strings to char pointers

	const char* pszLogFile =		pEnv->GetStringUTFChars(strLogFile, 0);
	const char* pszReportFile =		pEnv->GetStringUTFChars(strReportFile, 0);
	const char* pszIniFile =		pEnv->GetStringUTFChars(strIniFile, 0);

	// Call the C++ Engine
	jint nResult = tfe_GenerateReportFromLog(pszLogFile, pszReportFile, pszIniFile);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strLogFile, pszLogFile);
	pEnv->ReleaseStringUTFChars(strReportFile, pszReportFile );
	pEnv->ReleaseStringUTFChars(strIniFile, pszIniFile);

	return nResult;
}
	
///////////////////////////////////////////////////////////////////////////////
//	TEST FLOW
JNIEXPORT jint JNICALL Java_TestFrame_Engine_ProcessNextLine(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine
	jint nResult = tfe_ProcessNextLine();

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
//	RUN TIME INFORMATION
JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetActionWord(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetActionWord());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetActionWordFunction(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetActionWordFunction());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetArgument(JNIEnv* pEnv, jclass cl, jint nIndex)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetArgument(nIndex));

	return strResult;
}
	
JNIEXPORT jint JNICALL Java_TestFrame_Engine_GetNumberOfArguments(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine 
	jint nResult = tfe_GetNumberOfArguments();

	return nResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetParameter(JNIEnv* pEnv, jclass cl, jint nIndex)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetParameter(nIndex));

	return strResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_GetNumberOfParameters(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine 
	jint nResult = tfe_GetNumberOfParameters();

	return nResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetTestCase(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetTestCase());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetTestCondition(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetTestCondition());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetSection(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetSection());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetScenario(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetScenario());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetClusterFile(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetClusterFile());

	return strResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_GetLineNumber(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine 
	jint nResult = tfe_GetLineNumber();

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_GetNumberOfErrors(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine 
	jint nResult = tfe_GetNumberOfErrors();

	return nResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetLatestError(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetLatestError());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetArgumentDescription(JNIEnv* pEnv, jclass cl, jint nIndex)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetArgumentDescription(nIndex));

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_ParameterDescription(JNIEnv* pEnv, jclass cl, jint nIndex)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetParameterDescription(nIndex));

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetCopyright(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetCopyright());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetVersion(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetVersion());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetBuild(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetBuild());

	return strResult;
}

JNIEXPORT jstring JNICALL Java_TestFrame_Engine_GetLogFile(JNIEnv* pEnv, jclass cl)
{
	// Call the C++ Engine and put the result in a new Java string that can be returned
	jstring strResult = pEnv->NewStringUTF(tfe_GetLogFile());

	return strResult;
}

///////////////////////////////////////////////////////////////////////////////
//	REPORTING
	
JNIEXPORT jint JNICALL Java_TestFrame_Engine_ReportComment(JNIEnv* pEnv, jclass cl, jstring strComment)
{
	// Convert Java string to char pointer
	const char* pszComment = pEnv->GetStringUTFChars(strComment, 0);

	// Call the C++ Engine
	jint nResult = tfe_ReportComment(pszComment);

	// Release Java string buffer allocated during conversion to char pointer
	pEnv->ReleaseStringUTFChars(strComment, pszComment);

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_ReportError(JNIEnv* pEnv, jclass cl, jstring strErrorText, jint nErrorTypeCode)
{
	// Convert Java string to char pointer
	const char* pszErrorText = pEnv->GetStringUTFChars(strErrorText, 0);

	// Call the C++ Engine
	jint nResult = tfe_ReportError(pszErrorText, nErrorTypeCode);

	// Release Java string buffer allocated during conversion to char pointer
	pEnv->ReleaseStringUTFChars(strErrorText, pszErrorText);

	return nResult;
}	
	
JNIEXPORT jint JNICALL Java_TestFrame_Engine_ReportCheck__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2I
	(JNIEnv* pEnv, jclass cl, jstring strDescription, jstring strExpected, jstring strRecorded, jint nCheckResult)
{
	// Convert Java strings to char pointers
	const char* pszDescription =	pEnv->GetStringUTFChars(strDescription, 0);
	const char* pszExpected =		pEnv->GetStringUTFChars(strExpected, 0);
	const char* pszRecorded =		pEnv->GetStringUTFChars(strRecorded, 0);

	// Call the C++ Engine
	jint nResult = tfe_ReportCheck(pszDescription, pszExpected, pszRecorded, nCheckResult);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strDescription, pszDescription);
	pEnv->ReleaseStringUTFChars(strExpected, pszExpected);
	pEnv->ReleaseStringUTFChars(strRecorded, pszRecorded);

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_ReportCheck__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2
	(JNIEnv* pEnv, jclass cl, jstring strDescription, jstring strExpected, jstring strRecorded)
{
	return Java_TestFrame_Engine_ReportCheck__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2I(pEnv,  cl,  strDescription,  strExpected,  strRecorded,1); //default pass report log line
}
	
///////////////////////////////////////////////////////////////////////////////
//	CHECKING

JNIEXPORT jint JNICALL Java_TestFrame_Engine_CheckString(JNIEnv* pEnv, jclass cl, jstring strDescription, jstring strExpected, jstring strRecorded)
{
	// Convert Java strings to char pointers
	const char* pszDescription =	pEnv->GetStringUTFChars(strDescription, 0);
	const char* pszExpected =		pEnv->GetStringUTFChars(strExpected, 0);
	const char* pszRecorded =		pEnv->GetStringUTFChars(strRecorded, 0);

	// Call the C++ Engine
	jint nResult = tfe_CheckString(pszDescription, pszExpected, pszRecorded);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strDescription, pszDescription);
	pEnv->ReleaseStringUTFChars(strExpected, pszExpected);
	pEnv->ReleaseStringUTFChars(strRecorded, pszRecorded);

	return nResult;
}
	
JNIEXPORT jint JNICALL Java_TestFrame_Engine_CheckArgument(JNIEnv* pEnv, jclass cl, jint nIndex, jstring strRecorded)
{
	// Convert Java strings to char pointers
	const char* pszRecorded =	pEnv->GetStringUTFChars(strRecorded, 0);

	// Call the C++ Engine
	jint nResult = tfe_CheckArgument(nIndex, pszRecorded);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strRecorded, pszRecorded);

	return nResult;
}
	
JNIEXPORT jint JNICALL Java_TestFrame_Engine_CheckParameter(JNIEnv* pEnv, jclass cl, jint nIndex, jstring strRecorded)
{
	// Convert Java strings to char pointers
	const char* pszRecorded =		pEnv->GetStringUTFChars(strRecorded, 0);

	// Call the C++ Engine
	jint nResult = tfe_CheckParameter(nIndex, pszRecorded);

	// Release Java string buffers allocated during conversion to char pointers
	pEnv->ReleaseStringUTFChars(strRecorded, pszRecorded);

	return nResult;
}
	
///////////////////////////////////////////////////////////////////////////////
//	Cluster Variables
JNIEXPORT jint JNICALL Java_TestFrame_Engine_KeepArgument(JNIEnv* pEnv, jclass cl, jint nIndex, jstring strValue)
{
	// Convert Java string to char pointer
	const char* pszValue =	pEnv->GetStringUTFChars(strValue, 0);

	// Call the C++ Engine
	jint nResult = tfe_KeepArgument(nIndex, pszValue);

	// Release Java string buffer allocated during conversion to char pointer
	pEnv->ReleaseStringUTFChars(strValue, pszValue);

	return nResult;
}

JNIEXPORT jint JNICALL Java_TestFrame_Engine_KeepParameter(JNIEnv* pEnv, jclass cl, jint nIndex, jstring strValue)
{
	// Convert Java string to char pointer
	const char* pszValue =	pEnv->GetStringUTFChars(strValue, 0);

	// Call the C++ Engine
	jint nResult = tfe_KeepParameter(nIndex, pszValue);

	// Release Java string buffer allocated during conversion to char pointer
	pEnv->ReleaseStringUTFChars(strValue, pszValue);

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
//	GUI
JNIEXPORT jint JNICALL Java_TestFrame_Engine_DisplayMessage(JNIEnv* pEnv, jclass cl, jstring strMessage)
{
	// Convert Java string to char pointer
	const char* pszMessage = pEnv->GetStringUTFChars(strMessage, 0);

	// Call the C++ Engine
	jint nResult = tfe_DisplayMessage(pszMessage);

	// Release Java string buffer allocated during conversion to char pointer
	pEnv->ReleaseStringUTFChars(strMessage, pszMessage);

	return nResult;
}
///////////////////////////////////////////////////////////////////////////////
