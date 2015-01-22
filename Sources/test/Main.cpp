#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "coengine.h"

using namespace std;
void main()
{
	// register action words
	tfe_RegisterActionWord("doe iets","fa()");
	tfe_RegisterActionWord("doe niets","fb()");

	// declare cluster, report and ini file
	const char* pszCluster	= "c:\\TestFrame\\Cluster\\File.txt";
	const char* pszReport	= "c:\\TestFrame\\Report\\File_report.rtf";
	const char* pszIniFile	= "c:\\TestFrame\\engine5.ini";

	// start the Engine
	tfe_StartEngine(pszCluster, pszReport, pszIniFile);

	// process all lines of the cluster
	while (tfe_ProcessNextLine()) 
	{ 
		Sleep(500); 
	}

	// stop the Engine and generate a report
	tfe_GenerateReport();
	tfe_StopEngine();
}