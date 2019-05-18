/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSetCursorPos                Datum: 13.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD    wSpalte   Spalte, in die Cursor soll        บ
  บ                    WORD    wZeile    Zeile, in die Cursor soll         บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion k”nnen Sie die Position         บ
  บ                    des Cursors fr das aktive Fenster festlegen.       บ
  บ                    Der Cursor wird nur dann an die neue Position ge-   บ
  บ                    setzt, wenn die Koordinaten innerhalb der Data-     บ
  บ                    Area des Fensters liegen.                           บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  OK    Funktion wurde erfolgreich ausgefhrt   บ
  บ                          ERROR Fehler aufgetreten, wFehler_g erhlt:   บ
  บ                                  - WIN_AUSSERHALB                      บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g (W)                                       บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_WINDOW_HEADER
#include <ctwin.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif

#ifndef CT_VIDEO_HEADER
#include <ctvio.h>
#endif



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */
IMPORT WORD wS_g;               /* Die Koordinaten der Data-Area des        */
IMPORT WORD wZ_g;               /* aktiven Fensters                         */
IMPORT WORD wB_g;
IMPORT WORD wH_g;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinSetCursorPos (WORD wSpalte,
                      WORD wZeile)
{
    if (WinKoordInDA(wSpalte, wZeile))              /* Bereichsberprfung  */
    {                                               /* der Argumente        */
        VioSetCursorPos(wS_g+wSpalte, wZ_g+wZeile); /* Cursor positionieren */
        return (OK);
    }
    else
    {
        wFehler_g = WIN_AUSSERHALB;                 /* globale Var. setzen  */
        return (ERROR);
    }
}
