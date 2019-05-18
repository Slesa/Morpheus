/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgWarnton                     Datum: 31.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion kann der Anwender in einem      บ
  บ                    Dialogfeld festlegen, ob ein Warnton erklingen      บ
  บ                    soll oder nicht. Darberhinaus hat er die           บ
  บ                    M”glichkeit, die Dauer und Tonh”he des Warn-        บ
  บ                    tons festzulegen.                                   บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD    Fehlerinformation OK/ERROR                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  siehe Verzeichnis  bei Referenz                     บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SPA    9                                    /* Position und Ab-     */
#define ZEI    5                                    /* messungen der        */
#define BRE    55                                   /* Dialogbox            */
#define HOE    11

#define MARKER 7
#define Z_PFEIL_LINKS 27
#define Z_PFEIL_RECHTS 26
#define DAUER  0                                    /* Konstanten fr Ein-  */
#define FREQ   1                                    /* gabefokus            */
#define ANAUS  2

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                 GLOBALE VARIABLEN, REFERENZEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT  COLORSET  aCS_g[];
IMPORT  WORD      wCSInd_g;
IMPORT  WORD      wVioMode_g;
IMPORT  BOOL      boBeepen_g;
IMPORT  WORD      wBeepFreq_g;
IMPORT  WORD      wBeepDauer_g;
IMPORT  PSTR      pstrReturn_g;
IMPORT  PSTR      pstrEsc_g;
IMPORT  PSTR      pstrF1_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE FUNKTIONEN                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL VOID i_DlgTonZeichneScrollBar   (VOID);
MGLOBAL WORD i_DlgTonGetWerte           (VOID);
MGLOBAL VOID i_DlgTonWertAlsText        (VOID);
MGLOBAL VOID i_DlgTonChangeFokus        (WORD);
MGLOBAL VOID i_DlgTonNeuePos            (WORD);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL WORD wFarbe_m;
MGLOBAL BOOL boAltBeepen_m;
MGLOBAL WORD wAltFreq_m;
MGLOBAL WORD wAltDauer_m;
MGLOBAL WORD wFokus_m;

MGLOBAL PSTR pstrTest_m = "F4=Test";
MGLOBAL PSTR pstrTitel_m = "Warnton einstellen";

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgWarnton(VOID)
{
    PWKB   pWkbDlg;
    WORD   wReturn;
                                                    /* Dialog einrichten    */
    if ((pWkbDlg = WinEinrichten(SPA, ZEI, BRE, HOE)) == NULL)
        return (ERROR);

    i_InitVars();                                   /* glo. Var. initialis. */
    i_DlgInit(SPA, ZEI, BRE, HOE,                   /* Standardelemente     */
              pstrTitel_m,                          /* ausgeben             */
              pWkbDlg,
              SF_STANDARD,
              DLG_INFO);

    WinSsa(41,8, pstrTest_m,                        /* F4-Schaltflche      */
           aCS_g[wCSInd_g].wCs_dlg_sf);

    WinSs(2,2,"Dauer:");                            /* Dialogbox-Texte aus  */
    WinSza(2,2,'D',aCS_g[wCSInd_g].wCs_dlg_hi);
    WinSs(2,4,"Frequenz:");                         /* geben                */
    WinSza(2,4,'F',aCS_g[wCSInd_g].wCs_dlg_hi);
    WinSs(43,2,"Sekunde");
    WinSs(43,4,"Hertz");
    WinSs(2,6,"Warnton:     ( ) Aus     ( ) Ein");
    WinSza(2,6,'W',aCS_g[wCSInd_g].wCs_dlg_hi);
    if (boBeepen_g)
        WinSz(28,6,MARKER);
    else
        WinSz(16,6,MARKER);

    WinCursor(EIN);                                 /* Cursor einschalten  */
    i_DlgTonZeichneScrollBar();                     /* Scrollbars zeichnen */
    i_DlgTonWertAlsText();                          /* akt. Werte ausgeben */
    i_DlgTonChangeFokus(DAUER);                     /* Fokus anzeigen      */

    boAltBeepen_m = boBeepen_g;                     /* Werte beim Eintritt */
    wAltFreq_m    = wBeepFreq_g;                    /* in Funktion sichern */
    wAltDauer_m   = wBeepDauer_g;

    wReturn = i_DlgTonGetWerte();                   /* Wahl einlesen       */

    if (wReturn == DLG_ESC)                         /* bei Abbbruch der    */
    {                                               /* Dialogbox werden    */
        boBeepen_g   = boAltBeepen_m;               /* die alten Werte     */
        wBeepFreq_g  = wAltFreq_m;                  /* wieder hergestellt  */
        wBeepDauer_g = wAltDauer_m;
    }
    WinEntfernen(pWkbDlg);                          /* Dialog entfernen    */
    return(OK);                                     /* zurck an Aufrufer  */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgTonGetWerte               Datum: 31.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion bearbeitet alle Eingaben der         บ
  บ                    Dialogbox.                                          บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Wahl des Anwenders DLG_ESC oder DLG_RETURN    บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
WORD i_DlgTonGetWerte(VOID)
{
    EVENT  Event;
    PEVENT pEvent;

    pEvent = &Event;                                /* Var. initialisieren */

    for (;;)                                        /* Eingaberoutine      */
    {
        UtlEvent(pEvent);
        switch(pEvent->wArt)
        {
            case EVENT_TASTE:
                switch(pEvent->wTaste)
                {
                    case 'D':
                    case 'd':
                    case T_A_D:
                        i_DlgTonChangeFokus(DAUER);
                        break;
                    case 'F':
                    case 'f':
                    case T_A_F:
                        i_DlgTonChangeFokus(FREQ);
                        break;

                    case 'w':
                    case 'W':
                    case T_A_W:
                        i_DlgTonChangeFokus(ANAUS);
                        break;

                    case T_TAB:
                        if (wFokus_m == ANAUS)
                            i_DlgTonChangeFokus(DAUER);
                        else
                            i_DlgTonChangeFokus(wFokus_m+1);
                        break;

                    case T_SHIFT_TAB:
                        if (wFokus_m == DAUER)
                            i_DlgTonChangeFokus(ANAUS);
                        else
                            i_DlgTonChangeFokus(wFokus_m-1);
                        break;

                    case T_LEFT:
                        if (wFokus_m == ANAUS && boBeepen_g == JA)
                        {
                            boBeepen_g = NEIN;
                            WinSz(28,6,' ');
                            WinSz(16,6,MARKER);
                        }
                        else if ( wFokus_m == FREQ &&
                                  wBeepFreq_g > 50)
                                i_DlgTonNeuePos(wBeepFreq_g/50-1);

                        else if ( wFokus_m == DAUER &&
                                  wBeepDauer_g > 1)
                                i_DlgTonNeuePos(wBeepDauer_g-1);
                        break;

                    case T_RIGHT:
                        if (wFokus_m == ANAUS &&
                            boBeepen_g == NEIN)
                        {
                            boBeepen_g = JA;
                            WinSz(28,6,MARKER);
                            WinSz(16,6,' ');
                        }
                        else if ( wFokus_m == FREQ &&
                                  wBeepFreq_g < 850)
                                i_DlgTonNeuePos(wBeepFreq_g/50+1);
                        else if ( wFokus_m == DAUER &&
                                  wBeepDauer_g < 17)
                                i_DlgTonNeuePos(wBeepDauer_g+1);
                        break;

                    case T_F1:
                        DlgHilfeTools(WARNTON);
                        break;

                    case T_F4:
                        i_Beep();
                        break;

                    case T_RETURN:
                        return(DLG_RETURN);

                    case T_ESC:
                        return(DLG_ESC);

                    default:
                        if (boBeepen_g)
                            i_Beep();

                }
                break;

        case EVENT_L_PRESS:
            switch(pEvent->wZeile)
            {
                case (ZEI+3):                       /* Scrollbar Dauer      */
                case (ZEI+5):                       /* Scrollbar Frequenz   */
                    if (pEvent->wZeile == (ZEI+3))
                        i_DlgTonChangeFokus(DAUER);
                    else
                        i_DlgTonChangeFokus(FREQ);

                    if ( pEvent->wZeile  == (ZEI+3)  &&
                         pEvent->wSpalte == (SPA+16) &&
                         wBeepDauer_g > 1)
                        i_DlgTonNeuePos(wBeepDauer_g-1);

                    else if ( pEvent->wZeile  == (ZEI+3)  &&
                              pEvent->wSpalte == (SPA+34) &&
                              wBeepDauer_g < 17)
                            i_DlgTonNeuePos(wBeepDauer_g+1);

                    else if ( pEvent->wZeile  == (ZEI+5)  &&
                              pEvent->wSpalte == (SPA+16) &&
                              wBeepFreq_g > 50)
                            i_DlgTonNeuePos(wBeepFreq_g/50-1);

                    else if ( pEvent->wZeile  == (ZEI+5)  &&
                              pEvent->wSpalte == (SPA+34) &&
                              wBeepFreq_g < 850)
                            i_DlgTonNeuePos(wBeepFreq_g/50+1);

                    else if ( pEvent->wSpalte > (SPA+16) &&
                              pEvent->wSpalte < (SPA+34) )
                            i_DlgTonNeuePos(pEvent->wSpalte-(SPA+16));

                break;

                case (ZEI+7):                       /* Optionsfelder        */
                    if (pEvent->wSpalte >= (SPA+17)  &&
                        pEvent->wSpalte <= (SPA+23) )
                    {
                        if (boBeepen_g == JA)
                        {
                            boBeepen_g = NEIN;
                            WinSz(28,6,' ');
                            WinSz(16,6,MARKER);
                        }
                    }
                    else if (pEvent->wSpalte >= (SPA+29) &&
                             pEvent->wSpalte <= (SPA+35))
                    {
                        if (boBeepen_g == NEIN)
                        {
                            boBeepen_g = JA;
                            WinSz(28,6,MARKER);
                            WinSz(16,6,' ');
                        }
                    }

                    else if (pEvent->wSpalte >= (SPA+3) &&
                             pEvent->wSpalte <= (SPA+10) )
                        i_DlgTonChangeFokus(ANAUS);

                    else if (boBeepen_g)
                        i_Beep();
                break;

                case (ZEI+9):
                    if (pEvent->wSpalte > SPA+2 &&
                        pEvent->wSpalte < SPA+3+strlen(pstrReturn_g))
                        return(DLG_RETURN);

                    else if (pEvent->wSpalte > SPA+16 &&
                             pEvent->wSpalte < SPA+17+strlen(pstrEsc_g))
                        return(DLG_ESC);

                    else if (pEvent->wSpalte > SPA + 30 &&
                             pEvent->wSpalte < SPA + 31+strlen(pstrF1_g))
                         DlgHilfeTools(WARNTON);

                    else if (pEvent->wSpalte > SPA + 41 &&
                             pEvent->wSpalte < SPA + 42+strlen(pstrTest_m))
                         i_Beep();

                    else if (boBeepen_g)
                         i_Beep();
                    break;

                default: if (boBeepen_g)
                            i_Beep();
            }/* end of switch(pEvent->wZeile) */
        } /* end of switch(pEvent->wEventart) */
    } /* end of for(;;) */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgTonZeichneScrollBar      Datum: 31.10.88       บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt nach Ermittlung des aktuellen   บ
  บ                    Grafikmodus die Scrollbars aus.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  modulglobale: - wVioMode_m  (R/W)                   บ
  บ                                  - wFarbe_m    (R/W)                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_DlgTonZeichneScrollBar(VOID)
{
    REGISTER sp;

    if (wVioMode_g == MONOCHROM)                    /* und Farben entspr.   */
        wFarbe_m = INVERS;                          /* festsetzen           */
    else
        wFarbe_m = VH(BLAU, KOBALT);


    sp = 15;                                        /* Scrollbar Dauer      */
    WinSza(sp, 2, Z_PFEIL_LINKS, wFarbe_m);         /* Pfeil links          */
    for (;sp < 15+18;)                              /* Scrollbar            */
        WinSza(++sp, 2, 176, NORMAL);               /* und                  */
    WinSza(sp, 2, Z_PFEIL_RECHTS, wFarbe_m);        /* Pfeil rechts         */

    sp = 15;                                        /* Scrollbar Frequenz   */
    WinSza(sp, 4, Z_PFEIL_LINKS, wFarbe_m);         /* Pfeil links          */
    for (;sp < 15+18;)                              /* Scrollbar            */
        WinSza(++sp, 4, 176, NORMAL);               /* und                  */
    WinSza(sp, 4, Z_PFEIL_RECHTS, wFarbe_m);        /* Pfeil rechts         */

    WinSza(15+wBeepDauer_g, 2, 178, BLAU);          /* akt. Dauer mark.     */
    WinSza(15+(wBeepFreq_g/50),4,178, BLAU);        /* akt. Freq. markieren */

    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgTonWertAlsText            Datum: 31.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt die aktuellen Werte             บ
  บ                    als Text im Dialogfeld aus.                         บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wBeepDauer_g, wBeepFreq_g (R)                       บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_DlgTonWertAlsText(VOID)
{
    CHAR acZahl[5];

    itoa(wBeepDauer_g, acZahl, 10);
    strcat(acZahl, "/18");
    WinSs( 36,2, "     ");
    WinSs( 36,2, acZahl);
    WinSs( 36,4, "   ");
    WinSs( 36,4, itoa(wBeepFreq_g, acZahl, 10));
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgTonChangeFokus            Datum: 31.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wWohin    gewnschter Fokus                    บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ndert den Eingabefokus auf          บ
  บ                    das bergebene Dialogfeld-Element.                  บ
  บ                                                                        บ
  บ  Rckgabewert:     keiner                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFokus_m (W)                                        บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_DlgTonChangeFokus(WORD wWohin)
{
    switch(wWohin)
    {
        case DAUER: wFokus_m = DAUER;
                    WinSetCursorPos(2,2);
                    break;

        case FREQ:  wFokus_m = FREQ;
                    WinSetCursorPos(2,4);
                    break;

        case ANAUS: wFokus_m = ANAUS;
                    WinSetCursorPos(2,6);
                    break;
    }

    return;
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgTonNeuePosition              Datum: 31.10.88   บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wPosition   neue Position auf der             บ
  บ                                      Scrolleiste (1-17)                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion setzt den Wert des aktiven           บ
  บ                    Scrollfeld auf den neuen, vom Anwender              บ
  บ                    gewhlten Wert.                                     บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFokus_m (R)                                        บ
  บ                    wBeepFreq_g, wBeepDauer_g (R/W)                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_DlgTonNeuePos(WORD wPosition)
{
    CHAR acZahl[5];

    switch(wFokus_m)
    {

        case DAUER:     WinSza(15+wBeepDauer_g, 2, 176,NORMAL);
                        wBeepDauer_g =  wPosition;
                        WinSza(15+wBeepDauer_g, 2, 178, BLAU);
                        itoa(wBeepDauer_g, acZahl, 10);
                        strcat(acZahl, "/18");
                        WinSs( 36,2, "     ");
                        WinSs( 36,2, acZahl);
                        break;

        case FREQ:      WinSza(15+(wBeepFreq_g/50),4,176, NORMAL);
                        wBeepFreq_g = wPosition*50;
                        WinSza(15+(wBeepFreq_g/50),4,178, BLAU);
                        WinSs( 36,4, "    ");
                        WinSs( 36,4, itoa(wBeepFreq_g, acZahl, 10));
                        break;
    }
    return;
}

