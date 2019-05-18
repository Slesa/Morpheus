/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSetCursorTyp                Datum: 13.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD    wStart  Startscanzeile des Cursors          บ
  บ                    WORD    wStop   Stopscanzeile des Cursors           บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt den Typ, also die Gr”แe         บ
  บ                    des Cursors fr das aktive Fenster fest.            บ
  บ                                                                        บ
  บ                    Die neuen Werte werden in die Struktur WKB ein-     บ
  บ                    getragen. Wenn der Cursor zur Zeit sichbar ist,     บ        บ
  บ                    wird die Gr”แe des Cursors auf dem Bildschirm       บ
  บ                    gendert.                                           บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD    OK      kein Fehler aufgetreten             บ
  บ                            ERROR   Fehler aufgetreten                  บ
  บ                                    in wFehler_g:                       บ
  บ                                    WIN_FALSCHE_OPT                     บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g(W)                                        บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT  WORD    wFehler_g;
IMPORT  PWKB    apWkbSichtbar_g[16];                /* Array v. Zeigern auf */
                                                    /* WKB der sichtbaren W.*/
IMPORT  WORD    wAktWin_g;                          /* Index des aktiven W. */
                                                    /* in ฏapWkbSichtbar[]ฎ */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinSetCursorTyp(WORD wStart, WORD wStop)
{
    if (wStart > 14 || wStop > 14)                  /* Argumente berprfen */
    {
        wFehler_g= WIN_FALSCHE_OPT;                 /* Variable setzen      */
        return (ERROR);                             /* zurck an Aufrufer   */
    }

    apWkbSichtbar_g[wAktWin_g]->wCursorstart=wStart;/* neue Werte in WKB    */
    apWkbSichtbar_g[wAktWin_g]->wCursorstop =wStop; /* eintragen            */

                                                    /* wenn Cursor sichtbar */
    if (apWkbSichtbar_g[wAktWin_g]->winFlags.wCursorAn == 1)
        VioSetCursorTyp(wStart, wStop);             /* Cursor ndern        */

    return (OK);
}
