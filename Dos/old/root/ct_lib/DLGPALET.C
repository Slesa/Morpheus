/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgFarbPalette                 Datum: 04.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion stellt eine Dialogbox zur Ver-       บ
  บ                    fgung, in der der Programmanwender seine           บ
  บ                    Farbpalette auswhlen kann.                         บ
  บ                    Die ausgewhlte Farbpalette beeinfluแt die Dar-     บ
  บ                    stellung der Dialogfelder und der Elemente von      บ
  บ                    Mens.                                              บ
  บ                    Bei einem Monochrom-Monitor kann nur die            บ
  บ                    monochrome Palette ausgewhlt werden.               บ
  บ                    Eine genaue Beschreibung der Bedienung der          บ
  บ                    Dialogbox finden Sie im Referenzteil.               บ
  บ                                                                        บ
  บ  Rckgabewert:     DLG_ERROR    Dialog konnte nicht angezeigt werden   บ
  บ                    DLG_RETURN   Dialog wurde mit Schaltflche EINGABE  บ
  บ                                 beendet                                บ
  บ                    DLG_ESC      Dialog wurde mit Schaltflche ABBRUCH  บ
  บ                                 beendet                                บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - aCS_g          (R)                                บ
  บ                    - wCSInd_g       (R/W)                              บ
  บ                                                                        บ
  บ                    - boBeepen_g     (R)                                บ
  บ                    - wVioMode_g     (R)                                บ
  บ                                                                        บ
  บ                    - pstrReturn_g   (R)                                บ
  บ                    - pstrEsc_g      (R)                                บ
  บ                    - pstrF1_g       (R)                                บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ  (c) copyright 1988,1989 Markt & Technik Verlag AG, Haar bei Mnchen   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <stdio.h>
#include <string.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SPA  9              /* durch nderung dieser beiden Konstanten kann */
#define ZEI  5              /* die Dialog-Box neu positioniert werden, wei- */
                            /* tere nderungen sind nicht erforderlich      */

#define BRE 45              /* Breite und H”he der Dialog-Box: drfen       */
#define HOE 11              /* nicht gendert werden                        */

#define MARKER 7            /* Zeichen zum markieren der aktuellen Palette  */

#define INIT   1000         /* bergabe an i_ZeigePalette()             */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT MENU      aMenus_g[];                /* Array mit Mens              */

IMPORT COLORSET  aCS_g[];                   /* Farbpalette und Index auf    */
IMPORT WORD      wCSInd_g;                  /* Palette                      */

IMPORT PSTR      pstrReturn_g;              /* Texte der Schaltflchen      */
IMPORT PSTR      pstrEsc_g;
IMPORT PSTR      pstrF1_g;

IMPORT WORD      wVioMode_g;                /* aktueller Video-Modus        */
IMPORT BOOL      boBeepen_g;                /* soll Signalton erklingen ?   */

IMPORT WORD      wAktMnu_g;                 /* aktueller Index zu Menus_g   */
IMPORT WORD      wMausda_g;                 /* Maus im System aktiviert ?   */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL BOOL bWaehlen_m  = JA;                      /* Wahlm”glichkeiten ?  */
MGLOBAL PSTR pstrTitel_m  = "Farbpalette whlen";   /* Titelzeile           */

MGLOBAL PSTR apstrText_m[]=                         /* Text der Auswahl-    */
{                                                   /* liste                */
    "( )   blaue Palette",
    "( )   weisse Palette",
    "( )   kobalt Palette",
    "( )   schwarze Palette",
    "( )   monochrom Palette",
    NULL
};



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                     MODULGLOBALE FUNKTIONEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL VOID i_ZeigePalette   (PWKB, WORD, WORD);
MGLOBAL WORD i_PalettenEvent  (PWKB);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgFarbPalette(VOID)
{
    REGISTER i;

    PWKB    pWkbDialog;                             /* Zg. Window-Struktur  */
    PMKB    pMkb;

    WORD    wResult;                                /* fr Rckgabewert     */
    WORD    wMausStatus;                            /* Mauszeiger an ?      */
    WORD    wAltePalette;                           /* Inhalt wCSInd_g vor  */
                                                    /* Auswahl              */

    CHAR    **ppstr;


    if ((pWkbDialog=WinEinrichten(SPA,ZEI,BRE,HOE)) /* Fenster einrichten   */
        == NULL)
        return (DLG_ERROR);                         /* evtl. Abbruch        */

    i_InitVars();                                   /* Var. initialisieren  */

    wAltePalette = wCSInd_g;                        /* alte Palette sichern */


    if (wVioMode_g == MONOCHROM)                    /* bei Monochrom keine  */
        bWaehlen_m = NEIN;                          /* Wahlm”glichkeit      */

    i_ZeigePalette(pWkbDialog, INIT, wCSInd_g);     /* Dialog anzeigen      */

    ppstr = apstrText_m;                            /* Optionsfelder aus-   */
    for (i=2; *ppstr; i++)                          /* geben                */
        WinSs(9, i, *ppstr++);
    WinSz(10, wCSInd_g+2, MARKER);                  /* akt. Palette eintr.  */


    wResult = i_PalettenEvent(pWkbDialog);          /* der Anwender hat das */
                                                    /* Wort, bzw. die Taste */
    switch(wResult)
    {
        case DLG_ESC:                               /* abgebrochen          */
            wCSInd_g = wAltePalette;            /* alte Pal. herstellen */
            WinEntfernen(pWkbDialog);           /* Dialog entfernen     */
            break;

        case DLG_RETURN:                            /* Wahl getroffen       */
            WinEntfernen(pWkbDialog);               /* Dialog entfernen     */

            if (wAltePalette != wCSInd_g)           /* wenn nderung erfolgt*/
            {
                for (i=0; i < MAXMENUES; i++)       /* Palette fr Mens    */
                {
                    aMenus_g[i].wStatus.wPalette = wCSInd_g;

                    if ((pMkb = aMenus_g[i].pMkbStart) != NULL)
                    {
                        do
                        {
                            i_MnuToBuffer(pMkb,     /* Menfenster im       */
                                          i,       /* Puffer ndern lassen */
                                          MNU_AENDERN);
                            pMkb=pMkb->pNaechster;  /* nchsten holen       */
                        } while (pMkb != aMenus_g[i].pMkbStart);
                    }
                }
                if (wAktMnu_g != NICHT_INIT)        /* Menzeile des akt.   */
                {                                   /* Mens neu anzeigen   */
                    i_MnuGenMenuZeile(wAktMnu_g);   /* Menzeile generieren */
                    if (wMausda_g)                  /* wenn Maus da         */
                        wMausStatus=MsmCursorOff(); /* Zeiger ausschalten   */
                    VioSb2w(0,0,80,1,               /* Menzeile ausgeben   */
                        aMenus_g[wAktMnu_g].fpwMzBuffer);
                    if (wMausda_g && wMausStatus == MSM_WAR_AN)
                        MsmCursorOn();
                }
            }
            break;
    }
    return(wResult);
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_PalettenEvent                Datum: 04.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB   pWkb      Zeiger auf Window-Struktur         บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion bearbeitet alle Eingaben fr         บ
  บ                    die Dialog-Box.                                     บ
  บ                    Je nach Wahl des Anwenders wird von hieraus die     บ
  บ                    Dialog-Box in der aktuellen Farbpalette ange-       บ
  บ                    zeigt, die Markierung verschoben, das Hilfe-        บ
  บ                    Fenster angezeigt oder die Funktion verlassen.      บ
  บ                                                                        บ
  บ                    Zur Ausgabe wird die Hilfsfunktion                  บ
  บ                    i_ZeigePalette() aufgerufen.                        บ
  บ                                                                        บ
  บ  Rckgabewert:     DLG_RETURN   der Anwender hat die Eingabe-Schalt-   บ
  บ                                 flche ausgel”st                       บ
  บ                                                                        บ
  บ                    DLG_ESC      der Anwender hat die Abbruch-Schalt-   บ
  บ                                 flche ausgel”st                       บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wCSInd_g  (R/W)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
WORD i_PalettenEvent(PWKB pWkb)
{
  WORD    wAlt;                                     /* temp. Sichern alte   */
                                                    /* Palette              */

  PEVENT  pEvent;                                   /* Zg. Event-Struktur   */
  EVENT   Event;                                    /* Event-Struktur       */

  pEvent = &Event;

  for(;;)                                           /* Eingaberoutine       */
  {
    UtlEvent(pEvent);                               /* Event holen          */
    switch(pEvent->wArt)
    {
        case EVENT_TASTE:                           /* TASTENDRUCK          */
             switch(pEvent->wTaste)
             {
                case T_A_B:                         /* Hot-Key              */
                case 'b':
                case 'B':
                     if (bWaehlen_m)                /* wenn Wahl m”glich    */
                     {                              /* ausgewhlte Palette  */
                        wAlt = wCSInd_g;            /* einstellen           */
                        wCSInd_g = 0;
                        i_ZeigePalette(pWkb,        /* Hilfsfunktion aufr.  */
                                       wAlt,
                                       wCSInd_g);
                     }
                     break;


                case T_A_W:                         /* Hot-Key              */
                case 'w':
                case 'W':
                     if (bWaehlen_m)                /* wenn Wahl m”glich    */
                     {                              /* ausgewhlte Palette  */
                        wAlt = wCSInd_g;            /* einstellen           */
                        wCSInd_g = 1;
                        i_ZeigePalette(pWkb, wAlt, wCSInd_g);
                     }
                     break;

                case T_A_K:                         /* Hot-Key              */
                case 'k':
                case 'K':
                     if (bWaehlen_m)                /* wenn Wahl m”glich,   */
                     {                              /* ausgewhlte Palette  */
                        wAlt = wCSInd_g;            /* einstellen           */
                        wCSInd_g = 2;
                        i_ZeigePalette(pWkb, wAlt, wCSInd_g);
                     }
                     break;


                case T_A_S:                         /* Hot-Key              */
                case 's':
                case 'S':
                     if (bWaehlen_m)                /* wenn Wahl m”glich    */
                     {
                        wAlt = wCSInd_g;            /* alte Palette merken  */
                        wCSInd_g = 3;               /* Palette ndern       */
                        i_ZeigePalette(pWkb, wAlt,  /* Bildschirm ndern    */
                                       wCSInd_g);
                     }
                     break;



                case T_A_M:                         /* Hot-Key              */
                case 'm':                           /* monochrom immer      */
                case 'M':                           /* m”glich              */
                     wAlt = wCSInd_g;               /* ausgewhlte Palette  */
                     wCSInd_g = 4;                  /* einstellen           */
                     i_ZeigePalette(pWkb, wAlt,
                                    wCSInd_g);
                     break;


                case T_DOWN:                        /* nchste Palette      */
                case T_TAB:                         /* ausgewhlt           */
                     if (bWaehlen_m)                /* wenn Wahl m”glich    */
                     {
                         if (wCSInd_g < 4)          /* wenn nicht letzte    */
                         {                          /* Option               */
                            wCSInd_g++;             /* Palette inkrement.   */
                            i_ZeigePalette(pWkb,    /* Bildschirm ndern    */
                                           wCSInd_g-1,
                                           wCSInd_g);
                         }
                         else if( boBeepen_g)       /* wenn Warnton aktiv   */
                           i_Beep();                /* beepen               */
                     }
                     else if (boBeepen_g)           /* wenn Warnton aktiv   */
                        i_Beep();                   /* beepen               */
                     break;



                case T_SHIFT_TAB:                   /* vorherige Palette    */
                case T_UP:                          /* ausgewhlt           */
                     if (bWaehlen_m)                /* wenn Wahl m”glich    */
                     {
                        if (wCSInd_g > 0)           /* wenn nicht oberste   */
                        {                           /* Option               */
                          wCSInd_g--;               /* Palette dekrement.   */
                          i_ZeigePalette(pWkb,      /* Bildschirm ndern    */
                                          wCSInd_g+1,
                                          wCSInd_g);
                        }
                        else if (boBeepen_g)        /* wenn Warnton aktiv   */
                           i_Beep();                /* beepen               */
                     }
                     else if (boBeepen_g)           /* wenn Warnton aktiv   */
                       i_Beep();                    /* beepen               */
                break;

                case T_F1:                          /* Hilfe angefordert    */
                     DlgHilfeTools(FARBPALETTE);    /* Hilfe-Fenster zeig.  */
                     break;                         /* in Schleife bleiben  */

                case T_ESC:                         /* Funktion wird abgeb. */
                     return(DLG_ESC);               /* Aufrufer informieren */

                case T_RETURN:                      /* Wahl wurde getroffen */
                     return(DLG_RETURN);            /* Aufrufer informieren */

                default:                            /* nix anderes gltig   */
                    if (boBeepen_g)                 /* wenn Warnton aktiv   */
                        i_Beep();                   /* beepen               */
             }
             break;



        case EVENT_L_PRESS:                         /* MAUSEVENTS           */
             if (pEvent->wZeile == ZEI+9)           /* Test: Schalfl.-Zeile */
             {
                if (pEvent->wSpalte > SPA+2 &&      /* Eingabe-Schaltflche */
                      pEvent->wSpalte < SPA+3+strlen(pstrReturn_g))
                    return(DLG_RETURN);
                if (pEvent->wSpalte > SPA+17 &&     /* Abbruch-Schaltflche */
                      pEvent->wSpalte < SPA+17+strlen(pstrEsc_g))
                    return(DLG_ESC);
                if (pEvent->wSpalte > SPA+30 &&     /* Hilfe-Schaltflche   */
                      pEvent->wSpalte < SPA+31+strlen(pstrF1_g))
                    DlgHilfeTools(FARBPALETTE);
             }

             else if (bWaehlen_m)                   /* wenn Wahl m”glich    */
             {
                if (pEvent->wSpalte > SPA+9 &&      /* und Spalte irgendwo  */
                    pEvent->wSpalte < SPA+33)       /* in Auswahlliste      */
                {
                    if (pEvent->wZeile >=  ZEI+3 && /* und Zeile irgendwo   */
                        pEvent->wZeile <= ZEI+7)    /* in Auswahlliste      */
                    {
                        wAlt = wCSInd_g;            /* alte Palette merken  */
                        wCSInd_g =                  /* neue Pal. aus Klick- */
                            pEvent->wZeile-(ZEI+3); /* position ermitteln   */
                        i_ZeigePalette(pWkb,        /* Bildschirm ndern    */
                                       wAlt,
                                       wCSInd_g);
                    }
                    else if (boBeepen_g)            /* wenn Warnton aktiv   */
                        i_Beep();                   /* beepen               */
                }
             }
             else if (boBeepen_g)                   /* wenn Warnton aktiv   */
                i_Beep();                           /* beepen               */
             break;
    } /* end of switch(pEvent->wEventart) */
  } /* end of for */
} /* end of i_PalettenEvent() */





/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_ZeigePalette                 Datum: 04.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB  pWkb  Zeiger auf Window-Struktur              บ
  บ                    WORD  wAlt  Alter Paletten-Index                    บ
  บ                    WORD  wNeu  neuer Paletten-Index                    บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion zeigt die Dialogbox in den           บ
  บ                    Farben der neuen Palette an, wenn der Wert          บ
  บ                    wAlt ungleich wNeu ist.                             บ
  บ                    Auแerdem wird dann die alte Markierung gel”scht     บ
  บ                    und der Marker an die neue Position gesetzt.        บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - aCS_g     (R)                                     บ
  บ                    - wCSInd_g  (R)                                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_ZeigePalette(PWKB pWkb, WORD wAlt, WORD wNeu)
{
    REGISTER i;
    STATIC CHAR acHighLight[]="bwksm";              /* "Hot-Key" Array      */

    if (wAlt != wNeu)                               /* wenn neue Palette    */
    {
        if (wAlt != INIT)                           /* nicht beim erst. Mal */
            WinSz(10, wAlt+2, 32);                  /* alten Marker l”schen */

        i_DlgInit(SPA, ZEI, BRE, HOE,               /* Attribute der Dialog-*/
                  pstrTitel_m,                      /* box berschreiben    */
                  pWkb,                             /* lassen               */
                  SF_STANDARD,
                  DLG_INFO);

        for (i=0; i<=4; i++)                        /* Hot-Keys in Farbe d. */
            WinSza(15,2+i,                          /* neuen Palette aus-   */
                   acHighLight[i],                  /* geben                */
                   aCS_g[wCSInd_g].wCs_dlg_hi);

        WinSz(10, wNeu+2, MARKER);                 /* neuen Marker setzen   */
    }
    return;
}
