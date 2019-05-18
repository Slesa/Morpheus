/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinCursor                      Datum: 13.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD    wWahl  Cursor ein-/ausschalten              บ
  บ                                   EIN/AUS                              บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion k”nnen Sie fr das ber-        บ
  บ                    gebene Fenster festlegen, ob der Cursor sicht-      บ
  บ                    bar oder unsichtbar sein soll.                      บ
  บ                    Die Information wird in den WKB eingetragen und     บ
  บ                    beim aktiven Fenster zustzlich der Cursor in       บ
  บ                    den gewnschten Zustand versetzt.                   บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD    OK    kein Fehler                           บ
  บ                            ERROR Fehler bei der Ausfhrung der Fkt.    บ
  บ                                  Zustzlich wird die globale Variable  บ
  บ                                  wFehler_g mit der Fehlernummer        บ
  บ                                  geladen:                              บ
  บ                                  - WIN_FALSCHE_OPT                     บ
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
#include <ctools.h>


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                   GLOBALE VARIABLEN, REFERENZEN                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;                              /* Nr. des letzten auf- */
                                                    /* getretenen Fehlers   */

IMPORT PWKB apWkbSichtbar_g[16];                    /* Array v. Zeigern auf */
                                                    /* WKB der sichtbaren W.*/

IMPORT WORD wAktWin_g;                              /* Index des aktiven W. */
                                                    /* in ฏapWkbSichtbar[]ฎ */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinCursor(WORD wWahl)
{
    WORD wDummy;

    if ((wWahl != EIN) && (wWahl != AUS))
    {
        wFehler_g = WIN_FALSCHE_OPT;                /* falsche Option       */
        return (ERROR);                             /* zurck               */
    }

    apWkbSichtbar_g[wAktWin_g]->winFlags.wCursorAn  /* Wahl eintragen       */
            = wWahl;
    if (wWahl == EIN)                               /* und ausfhren        */
        VioSetCursorTyp(apWkbSichtbar_g[wAktWin_g]->wCursorstart,
                        apWkbSichtbar_g[wAktWin_g]->wCursorstop);
    else
    {
        VioGetCursor(&wDummy,
                     &wDummy,
                     &apWkbSichtbar_g[wAktWin_g]->wCursorstart,
                     &apWkbSichtbar_g[wAktWin_g]->wCursorstop);
        VioSetCursorTyp(0x20,0);
    }

    return (OK);
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinRestoreCursor             Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keinen                                              บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion setzt den Cursor des aktiven Windows.  บ
  บ                    Die Position und die Gr”แe des Cursors werden dem   บ
  บ                    WKB entnommen.                                      บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wAktWin_g (R)                                   บ
  บ                      - apWkbSichtbar_g[] (R)                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_WinRestoreCursor( VOID )
{
    PWKB pWkb = apWkbSichtbar_g[wAktWin_g];         /* Zeiger auf aktives W.*/

    WinSetCursorPos(pWkb->wCursorspalte,            /* Cursor positionieren */
                    pWkb->wCursorzeile);

    if (pWkb->winFlags.wCursorAn == 1)              /* Soll Cursor einge-   */
                                                    /* schaltet werden ?    */
        WinSetCursorTyp(pWkb->wCursorstart,         /* Cursortyp einstellen */
                        pWkb->wCursorstop);
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinSaveCursor                Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion bestimmt die Gr”แe und die Position    บ
  บ                    des Cursors im aktiven Window und trgt die Er-     บ
  บ                    gebnisse im WKB des Windows ein.                    บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wAktWin_g (R)                                   บ
  บ                      - apWkbSichtbar_g[] (R)                           บ
  บ                      - wS_g                                            บ
  บ                      - wZ_g                                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                   GLOBALE VARIABLEN, REFERENZEN                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT  WORD    wS_g;                               /* Linke obere Ecke der */
IMPORT  WORD    wZ_g;                               /* Data-Area            */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_WinSaveCursor(VOID)
{
    WORD wDummy;
    PWKB pWkb = apWkbSichtbar_g[wAktWin_g];         /* Zeiger initialisieren*/


    if (wAktWin_g == 0)                             /* Bildschimr-Cursor    */
        VioGetCursor(&pWkb->wCursorspalte,          /* absolute Koordinaten */
                     &pWkb->wCursorzeile,           /* ermitteln            */
                     &pWkb->wCursorstart,
                     &pWkb->wCursorstop);
    else
        VioGetCursor(&pWkb->wCursorspalte,           /* absolute Koordinaten */
                     &pWkb->wCursorzeile,            /* ermitteln            */
                     &wDummy,
                     &wDummy);

    pWkb->wCursorspalte -=  wS_g;                   /* und in relative      */
    pWkb->wCursorzeile  -=  wZ_g;                   /* umwandeln            */

    VioSetCursorTyp(0x20,0);                        /* Cursor ausschalten   */
}



