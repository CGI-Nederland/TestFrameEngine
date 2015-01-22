/******************************************************************************
 * $Workfile: ReportList.cpp $
 * $Revision: 35 $
 * $Modtime: 11/16/01 11:23a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2013 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "ReportList.h"	

// The texts
const char* ReportList::m_pszTexts[] = 
	{	
		// BRANDING_ID
		"TestFrame Test Execution Report",
		"TestFrame Test Durchführungsbericht",
		"TestFrame Test rapport d'exécution",
		"TestFrame Test Executie Rapport",
		"TestFrame Test izpildes ziņojums",


		/*
		// LICENSE_NAME_ID
		"Licensed to",			// GB
		"Lizenziert für",		// DE
		"Licence de",			// FR
		"Licentie van",			// NL
		"Licentia pro",			// LT

		// LICENSE_COMPANY_ID
		"Company",			// GB
		"Unternehmen",		// DE
		"Compagnie",		// FR
		"Bedrijf",			// NL
		"Consortio",		// LT

		// SERIAL_NUMBER_ID
		"Serial number",		// GB
		"Serienummer",			// DE
		"Numéro de série",		// FR
		"Serienummer",			// NL
		"Numerus licentiae",	// LT*/

		//USERNAME
		"Executed by",
		"Ausgefuerht durch",
		"Nom d'utilisateur",
		"Uitgevoerd door",
		"Lietotājvārds",

		//COMPUTERNAME
		"Executed on",
		"Ausgefuert auf",
		"Fait le",
		"Uitgevoerd op",
		"izpildīts",

		// CLUSTERNAME_ID
		"Cluster name",				// GB	
		"Cluster Name",				// DE
		"Nom du cluster",			// FR
		"Cluster naam",			    // NL
		"Nomen collectionis",		// LT

		// CLUSTERVERSION_ID
		"Cluster version",				// GB   
		"Cluster Version",				// DE
		"Version du cluster",			// FR
		"Cluster versie",			    // NL
		"Versus collectionis",			// LT

		// CLUSTERDATE_ID
		"Cluster date",					// GB   
		"Cluster Datum",				// DE
		"Date du cluster",				// FR
		"Cluster datum",				// NL
		"Tempus collectionis",			// LT

		// CLUSTERAUTHOR_ID
		"Cluster author",				// GB   
		"Cluster Autor",				// DE
		"Auteur du cluster",			// FR
		"Cluster auteur",				// NL
		"Scriptor collectionis",		// LT

		// DOCUMENT_ID
		"Document",				// GB
		"Dokument",				// DE
		"Document",				// FR
		"Document",				// NL
		"Tabellae",				// LT

		// SHEET_ID
		"Sheet",				// GB
		"Arbeitsblatt",			// DE
		"Feuille de calcul",	// FR
		"Blad",					// NL
		"Lammina",				// LT

		// REPORTNAME_ID
		"Report file",				// GB
		"Report-Datei",				// DE
		"Nom du rapport",			// FR
		"Rapport bestand",			// NL
		"Nomen relati",				// LT

		// ENGINEVERSION_ID
		"Engine version",				// GB
		"Engine-Version",				// DE
		"Version du moteur",			// FR
		"Engine versie",				// NL
		"Versus turboductoris",			// LT

		// ENGINEBUILD_ID
		"Engine build",					// GB
		"Engine-Build",					// DE
		"Build du moteur",				// FR
		"Engine build",					// NL
		"Constructum turboductoris",	// LT

		// CHECK_ID
		"Check of",						// GB
		"Check von",					// DE
		"Vérification de",				// FR
		"Check van",					// NL
		"Comparatio de",				// LT

		// SECTION_ID
		"Section",						// GB
		"Abschnitt",					// DE
		"Section",						// FR
		"Sectie",						// NL
		"Sectio",						// LT

		// SCENARIO_ID
		"Scenario",						// GB
		"Testszenario",					// DE
		"Scénario",						// FR
		"Scenario",						// NL
		"Scenario",						// LT

		// TESTCASE_ID
		"Test case",					// GB
		"Testfall",						// DE
		"Cas de test",					// FR
		"Testgeval",					// NL
		"Casus tentationis",			// LT

		// TESTCONDITION_ID
		"Test condition",				// GB
		"Testbedingung",				// DE
		"Condition de test",			// FR
		"Testconditie",					// NL
		"Conditio tentationis",			// LT

		// EXPECTED_ID
		"Expected",					// GB
		"Erwartet",					// DE
		"Attendu",					// FR
		"Verwacht",					// NL
		"Exspectatum",				// LT

		// RECORDED_ID
		"Recorded",					// GB
		"Aktuell",					// DE
		"Enregistré",				// FR
		"Gevonden",					// NL
		"Evestigatum",				// LT

		// RESULT_ID
		"Result",					// GB
		"Ergebnis",					// DE
		"Résultat",					// FR
		"Resultaat",				// NL
		"Effectus",					// LT

		// ERR_WARNING_ID
		"Warning",					// GB
		"Warnung",					// DE
		"Avertissement",			// FR
		"Waarschuwing",				// NL
		"Admonitio",				// LT

		// ERR_ERROR_ID
		"Error",					// GB
		"Fehler",					// DE
		"Erreur",					// FR
		"Fout",						// NL
		"Erratum",					// LT

		// ERR_CHECK_ID
		"Check error",				// GB
		"Fehler bei Prüfungen",		// DE
		"Erreur de contrôle",		// FR
		"Check fout",				// NL
		"Erratum comparatione",		// LT

		// ERR_FATAL_ID
		"Fatal error",				// GB
		"Fataler Fehler",			// DE
		"Erreur fatale",			// FR
		"Fatale fout",				// NL
		"Erratum fatalis",			// LT

		// ERR_CLUSTER_ID
		"Cluster error",			// GB
		"Cluster-Fehler",			// DE
		"Erreur de cluster",		// FR
		"Cluster fout",				// NL
		"Erratum collectionis",		// LT

		// ERR_INTERNAL_ID
		"Internal error",			// GB	
		"Interner Fehler",			// DE
		"Erreur interne",			// FR
		"Interne fout",				// NL
		"Erratum internum",			// LT

		// ERR_UNDEFINED_ID
		"Undefined error",			// GB
		"Unerwarteter Fehler",		// DE
		"Erreur indéfinie",			// FR
		"Ongedefiniëerde fout",		// NL
		"Erratum non definitum",	// LT

		// CHK_PASSED_ID
		"passed",					// GB
		"Erfolgreich",				// DE
		"OK",						// FR
		"geslaagd",					// NL
		"processum",				// LT

		// CHK_FAILED_ID
		"failed",					// GB
		"Fehlgeschlagen",			// DE
		"echec",					// FR
		"gefaald",					// NL
		"defectum",					// LT

		// NUMTESTLINES_ID
		"Number of test lines",			// GB
		"Anzahl der Testzeilen",		// DE
		"Nombre de lignes de test",		// FR
		"Aantal testregels",			// NL
		"Numerus versorum probando",	// LT

		// SUCC_LINES_ID
		"Succeeded test lines",			// GB
		"Erfolgreiche Testzeilen",		// DE
		"Taux de réussite",				// FR
		"Geslaagde testregels",			// NL
		"Numerus versorum processorum",	// LT

		// NUMERROR_ID
		"Number of errors",				// GB
		"Anzahl der Fehlerhinweise",	// DE
		"Nombre d'erreurs",				// FR
		"Aantal fouten",				// NL
		"Numerus erratorum",			// LT

		// ERROR_AT_LINE_ID
		"Errors were at lines",			// GB
		"Fehlerhinweise auf Zeilen",	// DE
		"Erreurs aux lignes",			// FR
		"Fouten op regels",				// NL
		"Versi erratorum",				// LT

		// NUMCHECK_ID
		"Number of checks",				// GB
		"Anzahl der Prüfungen",			// DE
		"Nombre de contrôles",			// FR
		"Aantal checks",				// NL
		"Numerus comparationum",		// LT

		// NUMPASSEDCHK_ID
		"Passed checks",						// GB
		"Erfolgreiche Prüfungen",				// DE
		"Nombre de contrôles réussis",			// FR
		"Geslaagde checks",						// NL
		"Numerus comparationum processorum",	// LT

		// NUMFAILEDCHK_ID
		"Failed checks",						// GB
		"Fehlgeschlagene Prüfungen",			// DE
		"Nombre de contrôles échoués",			// FR
		"Gefaalde checks",						// NL
		"Numerus comparationum defectorum",		// LT

		// FAIL_AT_LINE_ID
		"Fails were at lines",				// GB
		"Fehlgeschlagen auf Zeilen",		// DE
		"Echecs aux lignes",				// FR
		"Gefaald op regels",				// NL
		"Versi defectorum",					// LT

		// STARTTIME_ID
		"Start time",					// GB
		"Startzeit",					// DE
		"Heure de début",				// FR
		"Start tijd",					// NL
		"Tempus incipiendi",			// LT

		// STOPTIME_ID
		"Stop time",					// GB
		"Endzeit",						// DE
		"Heure de fin",					// FR
		"Stop tijd",					// NL
		"Tempus finiendi",				// LT

		// TIMEUSED_ID
		"Time used",					// GB
		"Ausführungszeit",				// DE
		"Temps écoulé",					// FR
		"Gebruikte tijd",				// NL
		"Tempus usus",					// LT

		// ENGINE_PAUSE_ID
		"Test paused at %1.",			// GB
		"Test angehalten um %1.",		// DE
		"Test pausé à %1.",				// FR
		"Test gepauzeerd om %1.",		// NL
		"Tentatio pausatus a %1.",		// LT

		// ENGINE_RESUME_ID
		"Test resumed at %1.",			// GB
		"Test fortgefahren um %1.",		// DE
		"Test redémarré à %1.",			// FR
		"Test hervat om %1.",			// NL
		"Tentatio resumatus a %1.",		// LT

		// EMC_STOP_ID
		"Stop button pressed at %1.",			// GB
		"Stop Button eingedrückt um %1.",		// DE
		"Stop bouton appuyer à %1.",			// FR
		"Stop knop ingedrukt om %1.",			// NL
		"Capulus finitus usus a %1.",			// LT

		// IF_ID
		"if",					// GB
		"if",					// DE
		"if",					// FR
		"if",					// NL
		"if",					// LT

		// ELSE_IF_ID
		"else if",				// GB
		"else if",				// DE
		"else if",				// FR
		"else if",				// NL
		"else if",				// LT

		// ELSE_ID
		"else",					// GB
		"else",					// DE
		"else",					// FR
		"else",					// NL
		"else",					// LT

		// END_IF_ID
		"end if",				// GB
		"end if",				// DE
		"end if",				// FR
		"end if",				// NL
		"end if",				// LT

		// REPEAT_ID
		"repeat",				// GB
		"repeat",				// DE
		"repeat",				// FR
		"repeat",				// NL
		"repeat",				// LT

		// END_REPEAT_ID
		"end repeat",			// GB
		"end repeat",			// DE
		"end repeat",			// FR
		"end repeat",			// NL
		"end repeat",			// LT

		// WHILE_ID
		"while",				// GB
		"while",				// DE
		"while",				// FR
		"while",				// NL
		"while",				// LT

		// END_WHILE_ID
		"end while",			// GB
		"end while",			// DE
		"end while",			// FR
		"end while",			// NL
		"end while",			// LT

		// CONDITION_ID
		"Condition",			// GB
		"Bedingung",			// DE
		"Condition",			// FR
		"Conditie ",			// NL
		"Conditio ",			// LT

		// TRUE_ID
		"true",					// GB
		"wahr",					// DE
		"vrai",					// FR
		"waar",					// NL
		"verus",				// LT

		// FALSE_ID
		"false",				// GB
		"falsch",				// DE
		"faux",					// FR
		"onwaar",				// NL
		"non verus",			// LT

		// ITERATION_ID
		"Iteration",			// GB
		"Wiederholung",			// DE
		"Itération",			// FR
		"Iteratie",				// NL
		"Iteratio",				// LT

		// SET_ID
		"set",			// GB
		"set",			// DE
		"set",			// FR
		"set",			// NL
		"set",			// LT

		// VARIABLE_EXPORTED_ID
		"Cluster variable \"%1\" with value \"%2\" exported to keep file.",								// GB
		"Cluster-Variable \"%1\" wird mit dem Wert \"%2\" in die Keep-Datei exportiert.",				// DE
		"La variable de cluster \"%1\" dont la valeur est \"%2\" est exportée dans le fichier keep.",	// FR
		"Cluster variabele \"%1\" met waarde \"%2\" geëxporteerd naar keep file.",						// NL
		"Signum varium \"%1\" repletum cum \"%2\" delatum datis 'keep'.",								// LT

		// VARIABLE_IMPORTED_ID
		"Cluster variable \"%1\" with value \"%2\" imported from keep file.",						// GB
		"Cluster-Variable \"%1\" wird mit dem Wert \"%2\" von der Keep-Datei importiert.",			// DE
		"La variable de cluster \"%1\" dont la valeur est \"%2\" est importée du fichier keep.",	// FR
		"Cluster variabele \"%1\" met waarde \"%2\" geïmporteerd uit keep file.",					// NL
		"Signum varium \"%1\" repletum cum \"%2\" delatum datis 'keep'.",							// LT

		// VARIABLE_KEPT_ID
		"Keep: cluster variable \"%1\" with value \"%2\".",					// GB
		"Keep: Clustervariable \"%1\" wurde mit dem Wert \"%2\" versorgt.",	// DE
		"Keep: variable du cluster \"%1\" prenant la valeur \"%2\".",		// FR
		"Keep: cluster variabele \"%1\" met waarde \"%2\".",				// NL
		"Keep: signum varium \"%1\" repletum cum \"%2\".",					// LT

		// VALUE_SNAPPED_ID
		"Snap (argument %1): value \"%2\" with key \"%3\".",			// GB
		"Snap (Argument %1): Wert \"%2\" mit dem Schlüssel \"%3\".",	// DE
		"Snap (argument %1): valeur \"%2\" avec clé \"%3\".",			// FR
		"Snap (argument %1): waarde \"%2\" met sleutel \"%3\".",		// NL
		"Snap (argumentum %1): \"%2\" cum clave \"%3\".",																// LT

		// TEMPLATE_DEFINED_ID
		"Template \"%1\" defined and exported to file \"%2\".",					// GB
		"Template \"%1\" definiert und exportiert in die Datei \"%2\".",		// DE
		"Le template \"%1\" est défini et exporté dans le fichier \"%2\".",		// FR
		"Template \"%1\" gedefiniëerd en geëxporteerd naar bestand \"%2\".",	// NL
		"Exemplum \"%1\" definitum et delatum a datis \"%2\".",					// LT

		// SUBCLUSTER_ID
		"Subcluster",			// GB
		"Subcluster",			// DE
		"Subcluster",			// FR
		"Subcluster",			// NL
		"Subcluster",			// LT

		// ENGINE_RESET_ID
		"Engine reset at %1.",					// GB
		"Engine wurde zurückgesetzt an %1.",	// DE
		"Le moteur est relancé à %1.",			// FR
		"Engine gereset om %1.",				// NL
		"Turboductor regeneratus a %1.",		// LT

		// SLAVE_CONNECTED_ID
		"Connection with slave \"%1\" at %2.",		// GB
		"Verbindung mit Slave \"%1\" an %2.",		// DE
		"Connection avec esclave \"%1\" à %2.",		// FR
		"Verbinding met slave \"%1\" om %2.",		// NL
		"Iunctio servo \"%1\" a %2.",				// LT

		// SLAVE_CONNECT_FAIL_ID
		"Connection with slave \"%1\" could not be established.",			// GB
		"Verbindung mit Slave \"%1\" konnte nicht hergestellt werden.",		// DE
		"Connection avec esclave \"%1\" ne peut être établie.",				// FR
		"Verbinding met slave \"%1\" kon niet gelegd worden.",				// NL
		"Servo \"%1\" iugere non potest.",									// LT

		// SLAVE_DISCONNECTED_ID
		"Slave \"%1\" disconnected at %2.",						// GB
		"Verbindung mit Slave \"%1\" wurde an %2 aufgelöst.",	// DE
		"Esclave \"%1\" déconnecté à %2.",						// FR
		"Verbinding met slave \"%1\" verbroken om %2.",			// NL
		"Iunctio servo \"%1\" terminatus a %2."					// LT
};

////////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						======================
						ReportList::ReportList()
//						======================
{
	SetTextPointer(&m_pszTexts[0], NTEXTS);
}
	
//						=======================
						ReportList::~ReportList()
//						=======================
{
	// Nothing to destruct						
}