/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                                                                        บ
  บ   Dateiname: win.c                                                     บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ   Die Routinen in diesem Modul untersttzen die Bildschirmausgabe      บ
  บ   fr das aktuelle Window. Bezugspunkt fr Koordinatenangaben ist      บ
  บ   die linke obere Ecke des Windows (0,0). Wurde noch kein Window       บ
  บ   aktiviert, wird der gesamte Bildschirm als Window behandelt.         บ
  บ                                                                        บ
  บ   Die Funktionen basieren auf den Routinen des Moduls ฏvio.cฎ.         บ
  บ   Bei namensgleichen Funktionen (das Prfix ausgenommen) wird          บ
  บ   immer die gleiche Parameterliste benutzt.                            บ
  บ                                                                        บ
  บ   In allen Funktionen in denen Koordinaten benutzt werden, findet      บ
  บ   eine berprfung auf Bereichsberschreitung statt. Bei ungltigen    บ
  บ   Angaben findet keine Aktion statt.                                   บ
  บ                                                                        บ
  บ                                                                        บ
  บ   Die Prototypen aller Funktionen und die symbolischen Konstanten      บ
  บ   finden Sie in der Deklarations-Datei ฏctwin.hฎ.                      บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ


  ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                                                                        บ
  บ   Namensvergabe:  Win(1)(2)(Parameter)                                 บ
  บ                                                                        บ
  บ                                                                        บ
  บ                  (1)  Legt die Zugriffsart fest:                       บ
  บ                       L  = lesen                                       บ
  บ                       S  = schreiben                                   บ
  บ                                                                        บ
  บ                                                                        บ
  บ                  (2)  Legt das Element fest:                           บ
  บ                       z   = Zeichen                                    บ
  บ                       a   = Attribut                                   บ
  บ                       za  = Zeichen und Attribut                       บ
  บ                                                                        บ
  บ                       s   = String                                     บ
  บ                       sa  = String mit Attribut                        บ
  บ                                                                        บ
  บ                       wz  = Bildschirmfenster (window) mit Zeichen     บ
  บ                       wa  = Bildschirmfenster mit Attribut             บ
  บ                       wza = Bildschirmfenster mit Zeichen und Attribut บ
  บ                       b2w = Buffer nach Bildschirmfenster              บ
  บ                       w2b = Bildschirmfenster nach Buffer              บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
 
 

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          HEADER - DATEIEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <dos.h>

#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                  G l o b a l e   V a r i a b l e n                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT  WORD    wMausda_g;                          /* 0: keine Maus da     */
                                                    /* 1: Maus vorhanden    */
IMPORT  WORD    wFehler_g;                          /* Nr. des letzten auf- */
                                                    /* getretenen Fehlers   */

IMPORT  WORD    wS_g;                               /* Die Koordinaten be-  */
IMPORT  WORD    wZ_g;                               /* schreiben die Data-  */
IMPORT  WORD    wB_g;                               /* Area des aktuellen   */
IMPORT  WORD    wH_g;                               /* Windows.             */

IMPORT  WORD    wAttribut_g;                        /* Attribut des Fenster-*/


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinInit()                      Datum: 11.09.88    บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Windows         บ
  บ                    WORD     wHoehe          H”he des Windows           บ
  บ                    WORD     wAttr           gewnschtes Attribut       บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion initialisiert smtliche globalen       บ
  บ                    Variablen die von den Window-Funktionen ben”tigt    บ
  บ                    werden. Nach Aufruf dieser Funktion beziehen sich   บ
  บ                    alle weiteren Koordinatenangaben auf das hier def-  บ
  บ                    inierte Window.                                     บ
  บ                    Dabei ist zu beachten, daแ die Parameter den be-    บ
  บ                    schreibbaren Bereich eines Windows festlegen. Ein   บ
  บ                    etwaiger Rahmen wird hier nicht bercksichtigt.     บ
  บ                    Wenn das gewnschte Window nicht vollstndig auf    บ
  บ                    dem Bildschirm liegt, wird die Funktion mit einer   บ
  บ                    Fehlermeldung abgebrochen.                          บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   OK  ??????????                               บ
  บ                           ERROR  ??????????                            บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wS_g (W)                                        บ
  บ                      - wZ_g (W)                                        บ
  บ                      - wH_g (W)                                        บ
  บ                      - wB_g (W)                                        บ
  บ                      - wAttribut_g (W)                                 บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD i_WinInit( WORD wSpalte,
                WORD wZeile,
                WORD wBreite,
                WORD wHoehe,
                WORD wAttr)
{
    if ( wSpalte >= 0  &&                           /* liegt das Window     */
         wZeile  >= 0  &&                           /* vollstndig auf dem  */
         (wSpalte + wBreite) <= MAXSPALTEN   &&     /* Bildschirm ?         */
         (wZeile  + wHoehe)  <= MAXZEILEN )
    {
        wS_g = wSpalte;
        wZ_g = wZeile;
        wB_g = wBreite;
        wH_g = wHoehe;
        wAttribut_g = wAttr;
        return(OK);
    }
    else
    {
        wFehler_g = WIN_ZU_GROSS;
        return(ERROR);
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSa                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                    WORD wAttr       gewnschtes Attribut               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ndert das Attribut fr das Zeichen, บ
  บ                    das durch die bergebenen Koordinaten festgelegt    บ
  บ                    wird. Das Zeichen wird nicht verndert.             บ
  บ                    Die bergebenen Koordinaten mssen im aktuellen     บ
  บ                    Window liegen. Andernfalls erfolgt keine Ausgabe.   บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSa( WORD wSpalte,
            WORD wZeile,
            WORD wAttr )
{
    WORD wStatus;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        VioSa(wS_g + wSpalte,                       /* Attribut schreiben   */
              wZ_g + wZeile,
              wAttr);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinLa                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespal             บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt das Attribut des Zeichens  บ
  บ                    an den bergebenen Koordinaten.                     บ
  บ                    Die bergebenen Koordinaten mssen im aktuellen     บ
  บ                    Window liegen. Andernfalls erfolgt keine Aktion.    บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  ermitteltes Attribut oder ฏ0ฎ wenn die        บ
  บ                          Koordinaten auแerhalb des Windows lagen.      บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD WinLa(WORD wSpalte,
           WORD wZeile )
{
    WORD wStatus,
         wReturn = 0;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        wReturn = VioLa(wS_g + wSpalte,             /* Attribut lesen       */
                        wZ_g + wZeile);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
    return(wReturn);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSz                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                    CHAR cZeichen    gewnschtes Zeichen                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion schreibt ein Zeichen an die mit      บ
  บ                    wSpalte, wZeile bestimmte Position. Das aktuelle    บ
  บ                    Attribut wird nicht verndert.                      บ
  บ                    Die bergebenen Koordinaten mssen im aktuellen     บ
  บ                    Window liegen. Andernfalls erfolgt keine Ausgabe.   บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSz ( WORD wSpalte,
             WORD wZeile,
             CHAR cZeichen )
{
    WORD wStatus;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        VioSz(wS_g + wSpalte,                       /* Zeichen schreiben    */
              wZ_g + wZeile,
              cZeichen);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinLz                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt das Zeichen an den ber-   บ
  บ                    gebenen Koordinaten.                                บ
  บ                    Die bergebenen Koordinaten mssen im aktuellen     บ
  บ                    Window liegen. Andernfalls erfolgt keine Aktion.    บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     CHAR  ermitteltes Zeichen oder ฏ0ฎ wenn die         บ
  บ                          Koordinaten auแerhalb des Windows lagen.      บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
CHAR WinLz ( WORD wSpalte,
             WORD wZeile )
{
    WORD wStatus;
    CHAR cReturn = '\0';


    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        cReturn = VioLz(wS_g + wSpalte,             /* Zeichen lesen        */
                        wZ_g + wZeile);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
    return(cReturn);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSza                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte       gewnschte Ausgabespalte         บ
  บ                    WORD wZeile        gewnschte Ausgabezeile          บ
  บ                    CHAR cZeichen      gewnschtes Zeichen              บ
  บ                    WORD wAttr         gewnschtes Attribut             บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion schreibt ein Zeichen mit Attribut    บ
  บ                    an die bergebene Position.                         บ
  บ                    Die bergebenen Koordinaten mssen im aktuellen     บ
  บ                    Window liegen. Andernfalls erfolgt keine Ausgabe.   บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSza ( WORD wSpalte,
              WORD wZeile,
              CHAR cZeichen,
              WORD wAttr )
{
    WORD wStatus;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        VioSza(wS_g + wSpalte,                      /* Z. und A. schreiben  */
               wZ_g + wZeile,
               cZeichen,
               wAttr);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinLza                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt das Zeichen mit seinem     บ
  บ                    Attribut an der bergebenen Windowposition.         บ
  บ                    Die bergebenen Koordinaten mssen im aktuellen     บ
  บ                    Window liegen. Andernfalls erfolgt keine Aktion.    บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  ermitteltes Attribut und Zeichen (High/Low)   บ
  บ                          oder ฏ0ฎ, wenn die Koordinaten auแerhalb      บ
  บ                          des aktuellen Windows lagen.                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD WinLza(WORD wSpalte,
            WORD wZeile )
{
    WORD wStatus,
         wReturn = 0;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        wReturn = VioLza(wS_g + wSpalte,            /* Z. und A. lesen      */
                         wZ_g + wZeile);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
    return(wReturn);
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSs                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                    PSTR pstrQuelle  Zeiger auf Ausgabestring           บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt eine Zeichenkette ab der mit    บ
  บ                    wSpalte, wZeile angegebenen Windowposition aus.     บ
  บ                    Die aktuellen Attribute werden bernommen.          บ
  บ                    Die bergebenen Koordinaten mssen im aktuellen     บ
  บ                    Window liegen. Andernfalls erfolgt keine Ausgabe.   บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                    Die Funktion fhrt automatisch einen Zeilenumbruch  บ
  บ                    durch. berschreitet der String das Window in der   บ
  บ                    rechten unteren Ecke, werden die berzhligen Zei-  บ
  บ                    chen ignoriert.                                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSs ( WORD wSpalte,
             WORD wZeile,
             PSTR pstrQuelle )
{
    WORD wStatus;
    BOOL boStop = NEIN;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        for (;*pstrQuelle && !boStop; pstrQuelle++) /* String abarbeiten    */
        {
            VioSz(wS_g + wSpalte,                   /* Zeichen schreiben    */
                  wZ_g + wZeile,
                  *pstrQuelle);

            wSpalte = WinIncSpalte(wSpalte);        /* Cursor weiterrcken  */
            if (!wSpalte)                           /* in nchste Zeile ?   */
                wZeile  = WinIncZeile(wZeile);

            if ( !wZeile && !wSpalte )              /* war Ecke unten rechts*/
                boStop = JA;                        /* schon erreicht ?     */

        }

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSsa                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte    gewnschte Ausgabespalte            บ
  บ                    WORD wZeile     gewnschte Ausgabezeile             บ
  บ                    PSTR pstrQuelle Zeiger auf Zeichenkette             บ
  บ                    WORD wAttr      gewnschtes Attribut                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt einen String im bergebenen     บ
  บ                    Attribut an der gewnschten Position aus.           บ
  บ                    Die bergebenen Koordinaten mssen im aktuellen     บ
  บ                    Window liegen. Andernfalls erfolgt keine Ausgabe.   บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                    Die Funktion fhrt automatisch einen Zeilenumbruch  บ
  บ                    durch. berschreitet der String das Window in der   บ
  บ                    rechten unteren Ecke, werden die berzhligen Zei-  บ
  บ                    chen ignoriert.                                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSsa ( WORD wSpalte,
              WORD wZeile,
              PSTR pstrQuelle,
              WORD wAttr )
{
    WORD wStatus;
    BOOL boStop = NEIN;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        for (;*pstrQuelle && !boStop; pstrQuelle++) /* String abarbeiten    */
        {
            VioSza(wS_g + wSpalte,                  /* Z. und A. schreiben  */
                   wZ_g + wZeile,
                   *pstrQuelle,
                   wAttr);

            wSpalte = WinIncSpalte(wSpalte);        /* Cursor weiterrcken  */
            if (!wSpalte)                           /* in nchste Zeile ?   */
                wZeile  = WinIncZeile(wZeile);

            if ( !wZeile && !wSpalte )              /* war Ecke unten rechts*/
                boStop = JA;                        /* schon erreicht ?     */
        }

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSwa                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    WORD     wAttr           gewnschtes Attribut       บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fllt das komplette Fenster, das     บ
  บ                    durch die Koordinaten der linken oberen Ecke und    บ
  บ                    seiner Ausdehnung in horizontaler und vertikaler    บ
  บ                    Richtung festgelegt wird, mit dem bergebenen       บ
  บ                    Attribut.                                           บ
  บ                    Wenn die linke obere Ecke des Fensters nicht im     บ
  บ                    aktuellen Window liegt, erfolgt keine Ausgabe.      บ
  บ                    ber das aktuelle Window hinausragende Flchen      บ
  บ                    werden nicht ausgegeben.                            บ
  บ                    Die im Speicher stehenden Zeichen werden nicht      บ
  บ                    verndert.                                          บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSwa( WORD wSpalte,
             WORD wZeile,
             WORD wBreite,
             WORD wHoehe,
             WORD wAttr)
{
    WORD wStatus;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        if ( wSpalte + wBreite > wB_g )             /* ฏwBreiteฎ zu groแ ?  */
            wBreite = wB_g - wSpalte;
        if ( wZeile + wHoehe > wH_g )               /* ฏwHoeheฎ zu groแ ?   */
            wHoehe = wH_g - wZeile;

        VioSwa(wS_g + wSpalte,                      /* Fenster ausgeben     */
               wZ_g + wZeile,
               wBreite,
               wHoehe,
               wAttr);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSwz                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    CHAR     cZeichen        gewnschtes Zeichen        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fllt das komplette Fenster, das     บ
  บ                    durch die Koordinaten der linken oberen Ecke und    บ
  บ                    seiner Ausdehnung in horizontaler und vertikaler    บ
  บ                    Richtung festgelegt wird, mit dem bergebenen       บ
  บ                    Zeichen.                                            บ
  บ                    Die im Speicher stehenden Attribute werden nicht    บ
  บ                    verndert.                                          บ
  บ                    Wenn die linke obere Ecke des Fensters nicht im     บ
  บ                    aktuellen Window liegt, erfolgt keine Ausgabe.      บ
  บ                    ber das aktuelle Window hinausragende Flchen      บ
  บ                    werden nicht ausgegeben.                            บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSwz( WORD wSpalte,
             WORD wZeile,
             WORD wBreite,
             WORD wHoehe,
             CHAR cZeichen)
{
    WORD wStatus;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        if ( wSpalte + wBreite > wB_g )             /* ฏwBreiteฎ zu groแ ?  */
            wBreite = wB_g - wSpalte;
        if ( wZeile + wHoehe > wH_g )               /* ฏwHoeheฎ zu groแ ?   */
            wHoehe = wH_g - wZeile;

        VioSwz(wS_g + wSpalte,                      /* Fenster ausgeben     */
               wZ_g + wZeile,
               wBreite,
               wHoehe,
               cZeichen);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSwza                        Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    CHAR     cZeichen        gewnschtes Zeichen        บ
  บ                    WORD     wAttr           gewnschtes Attribut       บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fllt das komplette Fenster, das     บ
  บ                    durch die Koordinaten der linken oberen Ecke und    บ
  บ                    seiner Ausdehnung in horizontaler und vertikaler    บ
  บ                    Richtung festgelegt wird, mit dem bergebenen       บ
  บ                    Zeichen im bergebenen Attribut.                    บ
  บ                    Wenn die linke obere Ecke des Fensters nicht im     บ
  บ                    aktuellen Window liegt, erfolgt keine Ausgabe.      บ
  บ                    ber das aktuelle Window hinausragende Flchen      บ
  บ                    werden nicht ausgegeben.                            บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSwza( WORD wSpalte,
              WORD wZeile,
              WORD wBreite,
              WORD wHoehe,
              CHAR cZeichen,
              WORD wAttr)
{
    WORD wStatus;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        if ( wSpalte + wBreite > wB_g )             /* ฏwBreiteฎ zu groแ ?  */
            wBreite = wB_g - wSpalte;
        if ( wZeile + wHoehe > wH_g )               /* ฏwHoeheฎ zu groแ ?   */
            wHoehe = wH_g - wZeile;

        VioSwza(wS_g + wSpalte,                     /* Fenster ausgeben     */
                wZ_g + wZeile,
                wBreite,
                wHoehe,
                cZeichen,
                wAttr);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSb2w                        Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    FPWORD   fpwQuelle       Zeiger auf Buffer          บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion schreibt den Inhalt des Buffers, auf   บ
  บ                    den der Zeiger ฏfpwQuelleฎ zeigt, in ein Fenster,   บ
  บ                    das durch die Koordinaten seiner linken oberen Ecke บ
  บ                    und seiner Ausdehnung in horizontaler und verti-    บ
  บ                    kaler Richtung festgelegt werden kann. Das Fenster  บ
  บ                    wird zeilenweise aus dem Buffer gelesen.            บ
  บ                    Wenn die linke obere Ecke des Fensters nicht im     บ
  บ                    aktuellen Window liegt, erfolgt keine Ausgabe.      บ
  บ                    Falls das Fenster nicht vollstndig im aktuellen    บ
  บ                    Window liegt, wird nur die gemeinsame Schnitt-      บ
  บ                    flche beschrieben.                                 บ
  บ                    Der Benutzer muแ dafr sorgen, daแ der Buffer sinn- บ
  บ                    volle Daten enthlt.                                บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSb2w ( WORD     wSpalte,
               WORD     wZeile,
               WORD     wBreite,
               WORD     wHoehe,
               FPWORD   fpwQuelle)
{
    WORD wStatus;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        if ( wSpalte + wBreite > wB_g )             /* ฏwBreiteฎ zu groแ ?  */
            wBreite = wB_g - wSpalte;
        if ( wZeile + wHoehe > wH_g )               /* ฏwHoeheฎ zu groแ ?   */
            wHoehe = wH_g - wZeile;

        VioSb2w(wS_g + wSpalte,                     /* Fenster ausgeben     */
                wZ_g + wZeile,
                wBreite,
                wHoehe,
                fpwQuelle);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSw2b                        Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    FPWORD   fpwZiel         Zeiger auf Buffer          บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion schreibt den Inhalt des Fensters, das  บ
  บ                    durch die Koordinaten seiner linken oberen Ecke und บ
  บ                    seiner Ausdehnung in horizontaler und vertikaler    บ
  บ                    Richtung festgelegt werden kann, in einen Buffer,   บ
  บ                    auf den der Zeiger ฏfpwZielฎ zeigt. Das Fenster     บ
  บ                    wird zeilenweise in dem Buffer abgelegt.            บ
  บ                    Wenn die linke obere Ecke des Fensters nicht im     บ
  บ                    aktuellen Window liegt, erfolgt keine Aktion.       บ
  บ                    Falls das Fenster nicht vollstndig im aktuellen    บ
  บ                    Window liegt, wird nur die Schnittflche in den     บ
  บ                    Buffer bertragen.                                  บ
  บ                    Der Benutzer muแ dafr sorgen, daแ der Buffer groแ  บ
  บ                    genug ist, um das Fenster aufzunehmen.              บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID WinSw2b ( WORD     wSpalte,
               WORD     wZeile,
               WORD     wBreite,
               WORD     wHoehe,
               FPWORD   fpwZiel)
{
    WORD wStatus;

    if ( WinKoordInDA(wSpalte,wZeile) )             /* Koordinaten innerhalb*/
    {                                               /* der Data-Area ?      */
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        if ( wSpalte + wBreite > wB_g )             /* ฏwBreiteฎ zu groแ ?  */
            wBreite = wB_g - wSpalte;
        if ( wZeile + wHoehe > wH_g )               /* ฏwHoeheฎ zu groแ ?   */
            wHoehe = wH_g - wZeile;

        VioSw2b(wS_g + wSpalte,                     /* Fenster ausgeben     */
                wZ_g + wZeile,
                wBreite,
                wHoehe,
                fpwZiel);

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }
}
