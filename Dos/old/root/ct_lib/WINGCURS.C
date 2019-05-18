/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinGetCursor                   Datum: 13.09.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWORD  pwSpalte    erhlt aktuelle Spalte           บ
  บ                    PWORD  pwZeile     erhlt aktuelle Zeile            บ
  บ                    PWORD  pwStart     erhlt Startscanzeile            บ
  บ                    PWORD  pwStop      erhlt Stopscanzeile             บ
  บ                    PWORD  pwSichtbar  erhlt Sichtbarkeit des Cursors  บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt fr das bergebene         บ
  บ                    Fenster Status-Informationen ber den               บ
  บ                    Cursor.                                             บ
  บ                    Die Werte werden ber die der Funktion ber-        บ
  บ                    gebenen Zeiger zurckgegeben.                       บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - wZ_g (R), wS_g (R)                                บ
  บ                    - apWkbSichtbar_g[] (R)                             บ
  บ                    - wAktWin_g (R)                                     บ
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

#ifndef CT_VIDEO_HEADER
#include <ctvio.h>
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                GLOBALE VARIABLEN, REFERENZEN                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wS_g;                                   /* Startkoordinaten der */
IMPORT WORD wZ_g;                                   /* aktuellen  Data-Area */

IMPORT PWKB apWkbSichtbar_g[16];                    /* Array v. Zeigern auf */
                                                    /* WKB der sichtbaren W.*/

IMPORT WORD wAktWin_g;                              /* Index des aktiven W. */
                                                    /* in ฏapWkbSichtbar[]ฎ */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID WinGetCursor(PWORD pwSpalte, PWORD pwZeile,
                  PWORD pwStart,  PWORD pwStop,
                  PWORD pwSichtbar)
{
    WORD wDummy;

    VioGetCursor(pwSpalte, pwZeile,                 /* absolute Koordinaten */
                 &wDummy, &wDummy);                 /* ermitteln            */
    *pwSpalte -=  wS_g;                             /* und in relative      */
    *pwZeile  -=  wZ_g;                             /* umwandeln            */

    *pwStart    =  apWkbSichtbar_g[wAktWin_g]->wCursorstart;
    *pwStop     =  apWkbSichtbar_g[wAktWin_g]->wCursorstop;
    *pwSichtbar =  apWkbSichtbar_g[wAktWin_g]->winFlags.wCursorAn;

    return;
}
