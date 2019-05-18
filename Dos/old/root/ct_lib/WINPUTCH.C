/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinPutch                       Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        CHAR cZeichen    gewnschtes Zeichen                บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion schreibt ein Zeichen an die aktuelle   บ
  บ                    Cursorposition. Das zugeh”rige Attribut wird nicht  บ
  บ                    verndert.                                          บ
  บ                    Der Cursor muแ sich im aktiven Window befinden.     บ
  บ                    Andernfalls erfolgt keine Ausgabe.                  บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                    Der Cursor wird hinter das ausgegebene Zeichen      บ
  บ                    gesetzt. Wurde das letzte Zeichen einer Zeile       บ
  บ                    bearbeitet, wird der Cursor an den Anfang der       บ
  บ                    nchsten Zeile gesetzt. In dem Sonderfall, daแ      บ
  บ                    das letzte Zeichen der letzten Zeile bearbeitet     บ
  บ                    wurde, wird der Fensterinhalt eine Zeile nach       บ
  บ                    oben gescrollt. Der Cursor wird dann in Spalte      บ
  บ                    ฏ0ฎ der neuen Zeile gesetzt.                        บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          HEADER - DATEIEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <dos.h>

#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_VIDEO_HEADER
#include <ctvio.h>
#endif

#ifndef CT_WINDOW_HEADER
#include <ctwin.h>
#endif

#ifndef CT_MAUS_HEADER
#include <ctmsm.h>
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                  G l o b a l e   V a r i a b l e n                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT  WORD    wMausda_g;                          /* 0: keine Maus da     */
                                                    /* 1: Maus vorhanden    */

IMPORT  WORD    wS_g;                               /* Die Koordinaten be-  */
IMPORT  WORD    wZ_g;                               /* schreiben die Data-  */
IMPORT  WORD    wB_g;                               /* Area des aktuellen   */
IMPORT  WORD    wH_g;                               /* Windows.             */

IMPORT  WORD    wAttribut_g;                        /* Attribut des Fenster-*/
                                                    /* innneren.            */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID WinPutch ( CHAR cZeichen )
{
    WORD wStatus, wSpalte, wZeile, wDummy;

    VioGetCursor(&wSpalte,                          /* absol. Position des  */
                 &wZeile,                           /* Cursors bestimmen.   */
                 &wDummy,
                 &wDummy);

    wSpalte -= wS_g;                                /* relative Koordinaten */
    wZeile  -= wZ_g;                                /* errechnen.           */

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        VioSz(wS_g + wSpalte,                       /* Zeichen schreiben    */
              wZ_g + wZeile,
              cZeichen);

        wSpalte = WinIncSpalte(wSpalte);            /* Cursor weiterrcken  */
        if (!wSpalte)                               /* in nchste Zeile ?   */
            wZeile = WinIncZeile(wZeile);

        if ( !wZeile && !wSpalte )                  /* muแ gescollt werden ?*/
        {
            WinScrollUp(1);
            wZeile = wH_g -1;                       /* Cur. in letzte Zeile */
        }

        VioSetCursorPos(wS_g + wSpalte,
                        wZ_g + wZeile);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}


