/******************************************************************************
 * $Workfile: MessageCentreList.cpp $
 * $Revision: 7 $
 * $Modtime: 21-12-99 12:24 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <afxwin.h>
#include "MessageCentreList.h"	

// The texts
const char* MessageCentreList::m_pszTexts[] = 
	{	
		"Engine Message Centre",				// GB	ID_MESS_CENTER
		"Engine Nachrichten Zentrum",				// D
		"Centre de message du moteur",			// F
		"Engine Berichten Centrum",             // NL
		"Medium Nuntiorum Turboductoris",		// LT

		"Number of action words executed:",				// GB   ID_TXTLBL_NUMBER_ACTIONWORDS
		"Anzahl der ausgeführten Aktionswörter: ",	// D
		"Nombre de mots d'action exécutés",				// F
		"Aantal uitgevoerde actiewoorden: ",            // NL
		"Numerus verborum actionum exactorum: ",		// LT
	
		"%1 out of %2 (%3%)",					// GB   ID_TXT_NUMBER_ACTIONWORDS
		"%1 von %2 (%3%)",						// D
		"%1 de %2 (%3%)",						// F
		"%1 uit %2 (%3%)",						// NL
		"%1 ex %2 (%3%)",						// LT

		"&Pause Test",							// GB   ID_BTN_PAUSE
		"&Anhalten des Tests",							// D
		"&Pause Test",							// F
		"&Pauzeer Test",                        // NL
		"&Pausate Probatio",					// LT

		"&Resume Test",							// GB   ID_BTN_RESUME
		"&Fortfahren Test",						// D
		"&Redémarrage Test",					// F
		"He&rvat Test",                         // NL
		"&Resumate Probatio",					// LT

		"&Stop Test",							// GB   ID_BTN_STOP
		"&Stop Test",							// D
		"&Stop Test",						    // F
		"&Stop Test",                           // NL
		"&Finite Probatio",						// LT

		"&More Detail >>",						// GB   ID_BTN_DETAIL_MORE
		"&Mehr Details >>",							// D
		"&Détails >>",						    // F
		"&Meer Detail >>",                      // NL
		"Non factum",							// LT

		"&Less Detail <<",						// GB   ID_BTN_DETAIL_LESS
		"&Keine Details <<",					// D
		"Moins de Détai&ls  <<",				// F
		"Minder Detai&l <<",                       // NL
		"Non factum",							// LT

		"Checks",								// GB   ID_GRP_CHECKS
		"Prüfungen",							// D
		"Contrôles",						    // F
		"Checks",								// NL
		"Comparationes",						// LT
	
		"Number of checks passed:",				// GB   ID_TXTLBL_CHECKS_PASSED
		"Anzahl der erfolgreichen Prüfungen: ",	// D
		"Nombre de contrôles réussis: ",		// F
		"Aantal geslaagde checks: ",            // NL
		"Non factum",							// LT

		"Number of checks failed: ",				// GB   ID_TXTLBL_CHECKS_FAILED
		"Anzahl der fehlgeschlagenen Prüfungen: ",	// D
		"Nombre de contrôles échoués: ",			// F
		"Aantal gefaalde checks: ",                 // NL
		"Non factum",								// LT

		"Current Success rate:",				// GB   ID_TXTLBL_SUCCESS_RATE
		"Aktuelle Erfolgsrate:",				// D
		"Taux de réussite:",                    // F
		"Huidig slagingspercentage:",           // NL
		"Non factum",							// LT
	
		"Errors",								// GB   ID_GRP_ERRORS
		"Fehlerhinweise",						// D
		"Erreurs",								// F
		"Fouten",								// NL
		"Errata",								// LT

		"Last reported error:",						// GB   ID_TXTLBL_LAST_ERROR
		"Zuletzter eingetragener Fehlerhinweis:",	// D
		"Dernière erreur rapportée:",				// F
		"Laatst gerapporteerde fout:",				// NL
		"Non factum",								// LT
	
		"Number of errors found:",				// GB   ID_TXTLBL_ERRORS_FOUND
		"Anzahl der Fehlerhinweise:",		// D
		"Nombre d'erreurs trouvées:",           // F
		"Aantal gevonden fouten:",              // NL
		"Non factum",							// LT

		"Message:",								// GB   ID_TXTLBL_MESSAGE
		"Meldung:",								// D
		"Message:",								// F
		"Bericht:",                             // NL
		"Nuntius:",								// LT

		"Running cluster %1",					// GB   ID_TXT_MESSAGE_RUNNING
		"Aktuelles Cluster %1",					// D
		"Cluster en cours d'exécution %1",      // F
		"Bezig met cluster %1",                 // NL
		"Non factum",							// LT

		"Test paused, press 'Resume Test' button to continue testing.",					// GB   ID_TXT_MESSAGE_PAUSED
		"Test angehalten, für Fortfahren klicken Sie auf dem Button 'Fortfahren Test'.",	// D
		"Pause du Test, appuyer le bouton 'Redémarrage Test' pour continuer.",			// F
		"Test gepauzeerd, druk op de button 'Hervat Test' om verder te gaan.",			// NL
		"Non factum",																	// LT
		
		"Current action word running:",			// GB   ID_TXTLBL_CURRENT_ACTIONWORD
		"Aktuelles Aktionswort:",				// D
		"Mot d'action en cours d'exécution",    // F
		"Huidig actiewoord:",					// NL
		"Non factum",							// LT
		
		"TestFrame Message",					// GB	ID_MESSAGEBOX
		"TestFrame Nachricht",					// D
		"Message TestFrame",                    // F
		"TestFrame Bericht",					// NL
		"Non factum"							// LT
	};

////////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						====================================
						MessageCentreList::MessageCentreList()
//						====================================
{
	SetTextPointer(&m_pszTexts[0], NTEXTS);
}
	
//						=====================================
						MessageCentreList::~MessageCentreList()
//						=====================================
{
	// Nothing to destruct						
}

