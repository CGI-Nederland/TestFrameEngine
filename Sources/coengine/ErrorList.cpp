/******************************************************************************
 * $Workfile: ErrorList.cpp $
 * $Revision: 23 $
 * $Modtime: 11/14/01 3:23p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "ErrorList.h"	

// The texts
const char* ErrorList::m_pszTexts[] = 
	{	
		// ID_ERR_INTERNAL_ERROR
		"Internal error.",						// GB	
		"Interner Fehler.",						// DE
		"Erreur interne.",						// FR
		"Interne fout.",				        // NL
		"Erratum internum.",					// LT

		// ID_ERR_INVALID_STRING
		"A closing \" is missing.",				// GB 
		"Abschließende Hochkommata fehlen.",	// DE
		"Absense d'un \" de fermeture.",		// FR
		"Een afsluitend \" ontbreekt.",			// NL
		"Expletus \" absens.",					// LT

		// ID_ERR_NUM_ONLY_DEC
		"A number without integer or fractional part.",			// GB 
		"Eine ganze Zahl oder Bruchteil vorhanden.",			// DE
		"Nombre sans partie entière ou partie fractionnelle.",	// FR
		"Een nummer zonder integraal- of breukdeel.",			// NL
		"Numerus sine parte integre aut fracto.",				// LT

		// ID_ERR_NUM_NO_EXP
		"A number without exponent after E or e.",			// GB 
		"Eine Zahl ohne Exponent nach E oder e.",			// DE
		"Nombre sans exposant après E ou e.",				// FR
		"Een nummer zonder exponent achter E of e.",		// NL
		"Numerus sine exponens post E aut e.",				// LT

		// ID_ERR_INVALID_TOKEN
		"Invalid token found: \"%1\".",			// GB 
		"Ungültiger Ausdruck \"%1\" gefunden.",	// DE
		"Touche invalide trouvée: \"%1\".",		// FR
		"Ongeldig teken gevonden: \"%1\".",		// NL
		"Signum non valens: \"%1\".",			// LT

		// ID_ERR_UNEXP_EOL
		"Unexpected end of expression encountered, instead of a constant or a variable.",		// GB
		"Unerwartetes Ende eines Ausdrucks gefunden, statt einer Konstanten oder Variablen.",	// DE
		"Fin d'expression inattendue rencontrée, au lieu d'une constante ou d'une variable.",	// FR
		"Onverwacht einde van expressie gevonden i.p.v. een constante of een variabele.",		// NL
		"Finis subitus expressionis pro signo constante aut vario.",							// LT

		// ID_ERR_UNEXP_TOKEN
		"Unexpected '%1' encountered.",		// GB
		"'%1' unerwartet gefunden.",		// DE
		"'%1' inattendu rencontré.",		// FR
		"Onverwacht '%1' gevonden.",		// NL
		"Insperatus '%1'.",					// LT

		// ID_ERR_UNEXP_ISO_NUMVAR,
		"Unexpected '%1' encountered, instead of a constant or a variable.",	// GB
		"'%1' unerwartet gefunden, statt einer Konstanten oder Variablen.",		// DE
		"'%1' inattendu rencontré, au lieu d'une constante ou d'une variable.",	// FR
		"Onverwacht '%1' gevonden i.p.v. een constante of een variabele.",		// NL
		"Insperatus '%1' pro signo constante aut vario.",						// LT

		// ID_ERR_UNEXP_ISO_OP
		"Unexpected '%1' encountered, instead of '%2'.",	// GB
		"'%1' unerwartet gefunden, statt '%2'.",			// DE
		"'%1' inattendu rencontré, au lieu de '%2'.",		// FR
		"Onverwacht '%1' gevonden i.p.v.'%2'.",				// NL
		"Insperatus '%1' pro '%2'.",						// LT

		// ID_ERR_INVALID_VAR_NAME
		"'%1' is an invalid variable name.",					// GB
		"'%1' ist ein unzulässiger Name für eine Variable.",	// DE
		"'%1' est un nom de variable invalide.",				// FR
		"'%1' is een ongeldige variabelenaam.",					// NL
		"'%1' nomen signi varii non valens.",					// LT

		// ID_ERR_ASSIGN_NO_VAR
		"The left operand of an assignment must be a variable.",			// GB
		"Der linke Operand einer Zuweisung muß eine Variable sein.",		// DE
		"L'opérande gauche d'une affectation doit être une variable.",		// FR
		"The linker operand van een toekenning moet een variabele zijn.",	// NL
		"Oportet ut signum sinister operationis tributarii varius.",		// LT

		// ID_ERR_SUB_NO_NUM
		"Both operands of a subtraction must be numbers.",					// GB
		"Beide Operanden einer Subtraktion müssen echte Zahlen sein.",		// DE
		"Les deux opérandes d'une soustraction doivent être des nombres.",	// FR
		"Beide operanden van een aftrekking moeten nummers zijn.",			// NL
		"Oportet ut uterque signum operationis redigentis numerus.",		// LT

		// ID_ERR_MUL_NO_NUM
		"Both operands of a multiplication must be numbers.",				// GB
		"Beide Operanden einer Multiplikation müssen echte Zahlen sein.",	// DE
		"Les deux opérandes d'une multiplication doivent être des nombres.",// FR
		"Beide operanden van een vermenigvuldiging moeten nummers zijn.",	// NL
		"Oportet ut uterque signum operationis multiplicati numerus.",		// LT

		// ID_ERR_DIV_NO_NUM
		"Both operands of a division must be numbers.",					// GB
		"Beide Operanden einer Division müssen echte Zahlen sein.",		// DE
		"Les deux opérandes d'une division doivent être des nombres.",	// FR
		"Beide operanden van een deling moeten nummers zijn.",			// NL
		"Oportet ut uterque signum operationis divortii numerus.",		// LT

		// ID_ERR_DIV_BY_ZERO
		"Division by zero.",		// GB
		"Division mit Null.",		// DE
		"Division par zéro.",		// FR
		"Deling door nul.",			// NL
		"Divortium nullo.",			// LT

		// ID_ERR_DATE_NO_FORMAT
		"No date format is specified.",				// GB
		"Kein Datum-Format spezifiziert.",			// DE
		"Aucun format de date n'est pas spécifié.",	// FR
		"Geen datumformaat gespecificeerd.",		// NL
		"Formatura temporis absens.",				// LT

		// ID_ERR_TIME_NO_FORMAT
		"No time format is specified.",				// GB
		"Kein Zeit-Format spezifiziert.",			// DE
		"Aucun format de date n'est pas spécifié.",	// FR
		"Geen tijdformaat gespecificeerd.",			// NL
		"Formatura temporis absens.",				// LT

		// ID_ERR_CLUS_INVALID_ACTIONWORD
		"\"%1\" is an invalid action word.",		// GB
		"\"%1\" ist ein unzulässiges Aktionswort.",	// DE
		"\"%1\" est un mot d'action invalide.",		// FR
		"\"%1\" is een ongeldig actiewoord.",		// NL
		"\"%1\" verbum actionis non valens.",		// LT

		// ID_ERR_CLUS_INVALID_SLAVE_NAME
		"\"%1\" is an invalid slave name.",						// GB
		"\"%1\" ist ein unzulässiger Name für einen Slave.",	// DE
		"\"%1\" est un nom secondaire invalide.",				// FR
		"\"%1\" is een ongeldige naam van een slave.",			// NL
		"\"%1\" nomen servi non valens.",						// LT

		// ID_ERR_MAX_CLUSTERS
		"It is not possible to have more than %1 clusters or templates open simultaneously.",	// GB
		"Es können nicht mehr als %1 Cluster oder Templates gleichzeitig geöffnet sein.",		// DE
		"Il n'est pas possible d'ouvrir simultanément plus d'%1 cluster ou template.",			// FR
		"Het is niet mogelijk meer dan %1 clusters of templates tegelijk open te hebben.",		// NL
		"Oportet ut non praeter %1 apertae pariter collectiones aut explempla.",				// LT

		// ID_ERR_CLUSTER_NOT_OPEN
		"Cluster \"%1\" could not be opened.",			// GB
		"Cluster \"%1\" konnte nicht geöffnet werden.",	// DE
		"Le cluster \"%1\" n'a pas pu être ouvert.",	// FR
		"Cluster \"%1\" kon niet worden geopend.",		// NL
		"Collectio \"%1\" apertus non potest.",			// LT

		// ID_ERR_TPT_NOT_OPEN
		"Template \"%1\" could not be opened.",			// GB
		"Template \"%1\" konnte nicht geöffnet werden.",// DE
		"Le template \"%1\" n'a pas pu être ouvert.",	// FR
		"Template \"%1\" kon niet worden geopend.",		// NL
		"Exemplum \"%1\" apertus non potest.",			// LT

		// ID_ERR_TPT_NO_PROTOTYPE
		"No template name specified.",					// GB
		"Kein Template-Name spezifiziert.",				// DE
		"Le nom de template n'est pas spécifié.",		// FR
		"Geen template naam gespecificeerd.",			// NL
		"Non nomen exempli datus.",						// LT

		// ID_ERR_TPT_REGISTERED
		"Template \"%1\" already registered as type other than template.",			// GB
		"Template \"%1\" bereits als ein anderer Typ registriert.",					// DE
		"Le template \"%1\" est déjà enregistré dans un type autre que template.",	// FR
		"Template \"%1\" al geregistreerd als ander type dan template.",			// NL
		"Exemplum \"%1\" cognitum aliter atque exemplum.",							// LT

		// ID_ERR_TPT_NO_END_DEF
		"No end of definition found for template \"%1\".",				// GB
		"Template Definitionsende für Template \"%1\" nicht gefunden.",	// DE
		"Pas de définition de fin pour le template \"%1\".",			// FR
		"Geen einde van de definitie gevonden voor template \"%1\".",	// NL
		"Non finis definitionis exempli \"%1\".",						// LT

		// ID_ERR_TPT_END_FOUND
		"End of template definition found without preceding definition.",			// GB
		"Template Definitionsende ohne vorhergehenden Beginn gefunden.",			// DE
		"Fin de template rencontré sans définition préalable.",						// FR
		"Einde van een template definitie gevonden zonder voorafgaande definitie.",	// NL
		"Finis definitionis exempli sine definitione praecessa.",					// LT

		// ID_ERR_TPT_PROTOTYPE_FOUND
		"Template prototype declaration found, but not at beginning of template file.",					// GB
		"Template-Prototyp gefunden, aber nicht am Anfang der Template-Datei.",							// DE
		"Déclaration prototype de template rencontrée, mais pas au début du fichier template.",			// FR
		"Declaratie van template prototype gevonden echter niet aan het begin van een template file.",	// NL
		"Declaratio exemplaris exempli, sed non origo datorum exempli.",								// LT

		// ID_ERR_TPT_INCORRECT_NUMBER_PARAMETERS
		"Incorrect number of parameters when calling template \"%1\": %2 expected, %3 given.",				// GB
		"Template-Parameteranzahl fehlerhaft beim Aufruf von Template \"%1\": %2 erwartet, %3 erhalten.",	// DE
		"Nombre incorrect de paramètres dans l'appel du template \"%1\": %2 attendu, %3 fourni.",			// FR
		"Incorrect aantal parameters bij aanroep van template \"%1\": %2 verwacht, %3 gegeven.",			// NL
		"Numerus additorum non valens invocatione exempli \"%1\": %2 exspectata, %3 addita.",				// LT

		// ID_ERR_TPT_DIF_DECLARATION_AND_FILE
		"Difference in template names; \"%1\" in declaration, \"%2\" found in associated file.",			// GB
		"Template-Namen unterschiedlich: \"%1\" in der Deklaration, \"%2\" in der verbundenen Datei.",		// DE
		"Noms de templates différents,\"%1\" dans la déclaration, \"%2\" trouvé dans le fichier associé.",	// FR
		"Verschil in template namen; \"%1\" in declaratie, \"%2\" gevonden in bijbehorend bestand.",		// NL
		"Discrimen nomine exemplorum: \"%1\" declaratione, \"%2\" datis attributis.",						// LT

		// ID_ERR_TPT_NO_PROTOTYPE_IN_FILE
		"File associated with template \"%1\" has incorrect or no template prototype.",				// GB
		"Datei verbunden mit dem Template \"%1\" hat keinen oder unkorrekten Template-Prototyp.",	// DE
		"Le fichier associé au template n'a pas de prototype, ou bien il est incorrect.",			// FR
		"Bestand behorend bij template \"%1\" heeft geen of incorrect template prototype.",			// NL
		"Datis attributis exempli \"%1\" exemplar nullus aut non valens est.",						// LT

		// ID_ERR_TPT_NO_FILE
		"No file associated with template \"%1\"",			// GB
		"Keine Datei mit Template \"%1\" verbunden.",		// DE
		"Aucun fichier n'est associé au template \"%1\"",	// FR
		"Geen bestand behorend bij template \"%1\"",		// NL
		"Nullae data attibutae exemplo \"%1\" est.",		// LT

		// ID_ERR_TPT_DIFF_REGISTERED_AND_FILE
		"Difference in template prototypes; \"%1\" registered, \"%2\" found in associated file.",					// GB
		"Template-Prototypen unterschiedlich: \"%1\" registriert, \"%2\" in verbundener Datei gefunden.",			// DE
		"Les prototypes de templates sont différents: \"%1\" enregistré, \"%2\" trouvé dans le fichier associé.",	// FR
		"Verschil in template prototypes; \"%1\" geregistreerd, \"%2\" gevonden in bijbehorend bestand.",			// NL
		"Discrimen exemplarorum exemplorum: \"%1\" desciptus, \"%2\" datis attributis.",							// LT

		// ID_ERR_EXPORT_INVALID_VARIABLE
		"Cluster variable \"%1\" is invalid and could therefore not be exported.",			// GB
		"Cluster-Variable \"%1\" ist ungültig und kann daher nicht exportiert werden.",		// DE
		"La variable de cluster \"%1\" est invalide et ne peut donc pas être exportée.",	// FR
		"Cluster variabele \"%1\" is ongeldig en kan derhalve niet worden geëxporteerd.",	// NL
		"Signum varium \"%1\" non valens igitur non delatum.",								// LT

		// ID_ERR_IMPORT_INVALID_VARIABLE
		"Variable \"%1\" is not present in keep file and could therefore not be imported.",					// GB
		"Variable \"%1\" ist in der Keep-Datei nicht vorhanden und kann daher nicht importiert werden.",	// DE
		"La variable \"%1\" est absente du fichier keep, elle ne peut donc pas être importée.",				// FR
		"Variabele \"%1\" is niet aanwezig in de keep file en kan derhalve niet worden geïmporteerd.",		// NL
		"Signum varium \"%1\" absens datis 'keep' igitur non illatum.",									// LT

		// ID_ERR_NO_VARIABLES
		"%1: no variable specified.",					// GB
		"%1: keine Variable spezifiziert.",				// DE
		"%1: aucune variable n'est pas spécifiée.",		// FR
		"%1: geen variable gespecificeerd.",			// NL
		"%1: nullum signum varium datum.",				// LT

		// ID_ERR_PARAM_REPEAT
		"The parameter of %1 must be a non-negative integer.",			// GB
		"Die Parameter von %1 dürfen keine negative ganze Zahl sein.",	// DE
		"Le paramètre de %1 doit être un nombre entier non négatif.",	// FR
		"De parameter van %1 moet een niet-negatieve integer zijn.",	// NL
		"Oporet ut parameter de %1 integer non minor nullo.",			// LT

		// ID_ERR_NO_END_LOOP
		"No end found for %1.",			// GB
		"Kein Ende gefunden für %1.",	// DE
		"Absense de fin pour %1.",		// FR
		"Geen einde gevonden voor %1.",	// NL
		"Non datus finis pro %1.",		// LT

		// ID_ERR_UNEXP_BUILT_IN
		"Unexpected %1 found.",			// GB
		"%1 unerwartet gefunden.",		// DE
		"%1 inattendu trouvé.",			// FR
		"Onverwachte %1 gevonden.",		// NL
		"Insperatus %1.",				// LT

		// ID_ERR_NO_END_IF
		"No end found for if-statement.",			// GB
		"Kein Ende für If-Statement gefunden.",		// DE
		"Absense de fin pour le bloc-si.",			// FR
		"Geen einde gevonden voor if-statement.",	// NL
		"Nullus finis editioni 'if'.",				// LT

		// ID_ERR_UNCLOSED
		"Unclosed loop or if-statement found at end of cluster.",					// GB
		"Offener Loop oder If-Statement am Ende des Clusters gefunden.",			// DE
		"Boucle ou bloc-si non fermé à la fin du cluster.",							// FR
		"Ongesloten lus of if-statement gevonden aan het einde van het cluster.",	// NL
		"Orbis aut editio 'if' inapertus finito collectionis.",						// LT

		// ID_ERR_COND_NUM_ARG
		"The condition contains an incorrect number of arguments.",		// GB
		"Die Bedingung enthält eine inkorrekte Anzahl an Argumenten.",	// DE
		"La condition contient un nombre incorrect d'arguments.",		// FR
		"De conditie bevat een incorrect aantal argumenten.",			// NL
		"Conditioni numerus argumentorum nonvalens.",					// LT

		// ID_ERR_COND_INVALID_OP
		"The condition contains an invalid operator: %1.",		// GB
		"Die Bedingung enthält einen ungültigen Operanden: %1.",// DE
		"La condition contient un opérateur invalide: %1.",		// FR
		"De conditie bevat een ongeldige operator: %1.",		// NL
		"Conditioni operator non valens: %1.",					// LT

		// ID_ERR_KEEP_INVALID_INDEX
		"Invalid keep index [%1] for value [%2].",				// GB
		"Keep-Index ungültig: [%1] für den Wert [%2].",			// DE
		"L'index de keep [%1] invalide pour la valeur [%2].",	// FR
		"Ongeldige keep index [%1] voor waarde [%2].",			// NL
		"Index de 'keep' [%1] pro [%2] non valens."				// LT
	};

////////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						====================
						ErrorList::ErrorList()
//						====================
{
	SetTextPointer(&m_pszTexts[0], NTEXTS);
}
	
//						=====================
						ErrorList::~ErrorList()
//						=====================
{
	// Nothing to destruct						
}

