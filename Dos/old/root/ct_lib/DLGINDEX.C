/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgHilfeIndex                  Datum: 12.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PHILFEINDEX pHilfeIndex   Zeiger auf Array aus      บ
  บ                                              Struktur vom Typ          บ
  บ                                              HILFEINDEX                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion baut ein Hilfe-Fenster auf, indem    บ
  บ                    der Anwender aus einem Hilfe-Index das Thema        บ
  บ                    auswhlen kann, zu dem er Hilfe anfordern           บ
  บ                    will.                                               บ
  บ                                                                        บ
  บ                    Die einzelnen Eintrge des Index k”nnen maximal     บ
  บ                    52 Zeichen lang sein. Wenn der Index mehr als       บ
  บ                    acht Zeilen umfaแt, stellt die Funktion dem         บ
  บ                    dem Anwender eine Scroll-M”glichkeit zur Verfgung. บ
  บ                                                                        บ
  บ                    Im unteren Bereich der Dialogbox befinden sich      บ
  บ                    drei Schaltflchen:                                 บ
  บ                    - Mit der Esc-Schaltflche kann der Anwender die    บ
  บ                      Hilfe beenden. Die Funktion gibt dann DLG_ESC     บ
  บ                      (definiert mit dem Wert 0) zurck.                บ
  บ                    - Mit der F1-Schaltflche kann Hilfe zur Bedienung  บ
  บ                      der Dialogbox angefordert werden. Diese Hilfe     บ
  บ                      wird von der Toolbox zur Verfgung gestellt.      บ
  บ                    - Mit der Eingabe-Schaltflche whlt der Anwender   บ
  บ                      das Thema unter dem Auswahl-Cursor aus. Rufen     บ
  บ                      Sie anschlieแend die Funktion DlgHilfe() auf,     บ
  บ                      um die angefeorderte Hilfe anzuzeigen.            บ
  บ                                                                        บ
  บ                    Eine aktive Maus wird automatisch untersttzt.      บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Auswahl   DLG_ESC == 0  Fkt. abgebrochen      บ
  บ                                    sonst Eintrag wRueckgabe fr        บ
  บ                                    selektiertes Thema                  บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - aCS_g[]    (R)           - pstrEsc_g   (R)        บ
  บ                    - wCSInd_g   (R)           - pstrF1_g    (R)        บ
  บ                    - wMausda_g  (R)           - boBeepen_g  (R)        บ
  บ                    - pstrReturn_g (R)                                  บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <stdio.h>
#include <string.h>


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT COLORSET aCS_g[];                            /* Farbpaletten-Array   */
IMPORT WORD     wCSInd_g;                           /* Index in Pal.-Array  */
IMPORT WORD     wMausda_g;                          /* Maus im System ?     */

IMPORT PSTR     pstrF1_g;                           /* Texte der Schalt-    */
IMPORT PSTR     pstrEsc_g;                          /* flchen              */
IMPORT PSTR     pstrReturn_g;
IMPORT BOOL     boBeepen_g;                         /* Warnton ein ?        */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL PSTR   pstrHI_m     = "Index der Hilfsbildschirme";
MGLOBAL WORD   wHilfsZeilen_m,
               wAktZeile_m,
               wIndex_m;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE FUNKTIONEN                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL VOID i_BalkenPlusEins       (PHILFEINDEX);
MGLOBAL VOID i_BalkenMinusEins      (PHILFEINDEX);
MGLOBAL VOID i_ZeichneScroller      (VOID);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SPA         9                               /* Spalte des Dialoges  */
#define ZEI         5                               /* Zeile des Dialoges   */
#define BRE        56                               /* Breite des Dialoges  */
#define HOE        14                               /* H”he des Dialoges    */
#define TEXTZEILEN  8                               /* Anzahl Hilfszeilen   */
#define MINZEILEN   5                               /* min. Anzahl Hilfsz.  */

#define DKLICK 6


#define ZEICHNEBALKEN(z)    WinSwa(1,z+2, 52,1,aCS_g[wCSInd_g].wCs_mf_ca)
#define LOESCHEBALKEN(z)    WinSwa(1,z+2, 52,1,aCS_g[wCSInd_g].wCs_dlg)


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgHilfeIndex(PHILFEINDEX pHilfeIndex)
{
    REGISTER    i;
    PWKB        pWkbDialog;

    EVENT       Event;                              /* Zeiger fr Event     */
    PEVENT      pEvent;
    PHILFEINDEX pHILokal;                           /* lokaler Zeiger Texte */
    LONG        lTicksEins;                         /* zur Erkennung Doppel-*/
                                                    /*    klick             */

    i_InitVars();                                   /* glo. Var. init.      */
    pEvent = &Event;                                /* Var. initialisieren  */

    pHILokal = pHilfeIndex;
    for (wHilfsZeilen_m=0;                          /* Anzahl der Hilfs-    */
         pHILokal->pstrText != NULL;                /* zeilen ermitteln     */
         wHilfsZeilen_m++, pHILokal++);
    pHILokal = pHilfeIndex;                         /* Zeiger zurcksetzen  */

    wAktZeile_m = 0;
    wIndex_m    = 0;

    if ((pWkbDialog=WinEinrichten(SPA,ZEI,BRE,HOE)) /* Fenster einrichten   */
        == NULL)
        return (ERROR);                             /* eventuell Abbruch    */

    i_DlgInit(SPA, ZEI, BRE, HOE,                   /* Fenster anzeigen     */
              pstrHI_m,
              pWkbDialog,
              SF_STANDARD,
              DLG_INFO);

    if (wHilfsZeilen_m >= TEXTZEILEN)
       wHilfsZeilen_m = TEXTZEILEN;

    for (i = 0;i < wHilfsZeilen_m; pHILokal++, i++)     /* Text ausgeben        */
        WinSs(1, i+2, pHILokal->pstrText);

    ZEICHNEBALKEN(wAktZeile_m);                     /* Auswahlcursor        */
    i_ZeichneScroller();                            /* Scrollpfeile         */


    for(;;)                                         /* Eingaberoutine       */
    {
        UtlEvent(pEvent);
        switch(pEvent->wArt)
        {
            case EVENT_TASTE:
                switch(pEvent->wTaste)
                {
                    case T_DOWN:
                        i_BalkenPlusEins(pHilfeIndex);
                        break;

                    case T_UP:
                         i_BalkenMinusEins(pHilfeIndex);
                         break;

                    case T_F1:
                        DlgHilfeTools(DLGINDEX);
                        break;

                    case T_ESC:
                        WinEntfernen(pWkbDialog);
                        return(DLG_ESC);

                    case T_RETURN:
                        WinEntfernen(pWkbDialog);
                        pHILokal = pHilfeIndex+wIndex_m;
                        return(pHILokal->wRueckgabe);
                    default:
                        if (boBeepen_g)
                            i_Beep();
                }
                break;


            case EVENT_L_PRESS:
                if (pEvent->wZeile == (ZEI+2) )
                {
                    if (pEvent->wSpalte == (SPA+51))
                        i_BalkenMinusEins(pHilfeIndex);
                    else if (pEvent->wSpalte == (SPA+53))
                        i_BalkenPlusEins(pHilfeIndex);
                }

                else if (pEvent->wZeile == (ZEI+12))
                {
                    if (pEvent->wSpalte > SPA+2 &&
                            pEvent->wSpalte < SPA+3+strlen(pstrReturn_g))
                        {
                            WinEntfernen(pWkbDialog);
                            pHILokal = pHilfeIndex+wIndex_m;
                            return(pHILokal->wRueckgabe);
                        }

                    else if (pEvent->wSpalte > SPA+16 &&
                            pEvent->wSpalte < SPA+17+strlen(pstrEsc_g))
                        {
                            WinEntfernen(pWkbDialog);
                            return(DLG_ESC);
                        }

                    else if (pEvent->wSpalte > SPA+30 &&
                            pEvent->wSpalte < SPA+31+strlen(pstrF1_g))
                                 DlgHilfeTools(DLGINDEX);
                }

                                                    /* Klick im Themen-      */
                                                    /* bereich ?             */
                else if( pEvent->wZeile  >= (ZEI+3)  &&
                         pEvent->wZeile  <= (ZEI+10) &&
                         pEvent->wSpalte >= (SPA+2)  &&
                         pEvent->wSpalte <= (SPA+BRE-3) )
                {
                                                    /* Doppelklick testen   */
                    if (pEvent->wZeile - (ZEI+3) == wAktZeile_m &&
                        pEvent->lTicks - lTicksEins < DKLICK )
                        {
                            WinEntfernen(pWkbDialog);
                            pHILokal = pHilfeIndex+wIndex_m;
                            return(pHILokal->wRueckgabe);
                    }

                    if (pEvent->wZeile-(ZEI+3) >= 0  &&  /* kein Doppelklick   */
                        pEvent->wZeile-(ZEI+3) < wHilfsZeilen_m)
                    {
                        lTicksEins = pEvent->lTicks;
                        if (wAktZeile_m != pEvent->wZeile-(ZEI+3))
                        {
                            LOESCHEBALKEN(wAktZeile_m);
                            if (wAktZeile_m == wIndex_m)
                                wIndex_m =
                                    wAktZeile_m= pEvent->wZeile - (ZEI+3);
                            else
                            {
                                wIndex_m = wIndex_m - wAktZeile_m;
                                wAktZeile_m = pEvent->wZeile-(ZEI+3);
                                wIndex_m += wAktZeile_m;
                            }
                            ZEICHNEBALKEN(wAktZeile_m);
                            i_ZeichneScroller();
                        }
                    }
                }
                else if (boBeepen_g)
                    i_Beep();
                break;
        } /* end of switch(pEvent->wArt) */
    } /* end of for */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_BalkenPlusEins               Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion steuert das Scrollen und die Neu-    บ
  บ                    ausgabe des Hilfstextes bei DlgHilfeIndex().        บ
  บ                    In diesem Fall wird der im Fenster stehende         บ
  บ                    Text gescrollt, der neue Text ausgegeben und        บ
  บ                    die Scroll-Pfeile an die nach dem Scrollen ent-     บ
  บ                    standene Situation angepaแt.                        บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  modulglobale Variablen:                             บ
  บ                    - wHilfsZeilen_m (R)                                บ
  บ                    - wStartzeile_m  (R/W)                              บ
  บ                    - ppstrTmp_m     (R)                                บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_BalkenPlusEins(PHILFEINDEX pHI)
{
    PHILFEINDEX pHILokal;
    pHILokal = pHI;

    if (wAktZeile_m == TEXTZEILEN-1 &&              /* wenn Balken in Zeile */
        wIndex_m < wHilfsZeilen_m-1)                /* 8, Fenster scrollen  */
    {
        LOESCHEBALKEN(wAktZeile_m);
        i_DlgScroll((SPA+1),(ZEI+3),(BRE+SPA-2),(ZEI+10),UP);
        wIndex_m++;
        pHILokal += wIndex_m;
        WinSs(1,9, pHILokal->pstrText);
        ZEICHNEBALKEN(wAktZeile_m);
    }

    else if (wAktZeile_m < TEXTZEILEN &&            /* bis Zeile 8 nur den  */
        wIndex_m < wHilfsZeilen_m-1)                /* Balken verschieben   */
    {
        LOESCHEBALKEN(wAktZeile_m);
        wIndex_m++;
        wAktZeile_m++;
        ZEICHNEBALKEN(wAktZeile_m);
    }
    else if (boBeepen_g)
        i_Beep();
    i_ZeichneScroller();

    return;
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_BalkenMinusEins              Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PPSTR ppstrTxt  Zeiger auf erste Zeile der          บ
  บ                                    Hilfstexte                          บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion steuert das Scrollen und die  Neu-   บ
  บ                    ausgabe des Hilfstextes.                            บ
  บ                    Eine Aktion wird erst dann ausgefhrt, wenn         บ
  บ                    mehr als die in der Konstante MINZEILEN angegebenen บ
  บ                    Zeilen noch im Fenster stehen.                      บ
  บ                    In diesem Fall wird der im Fenster stehende         บ
  บ                    Text gescrollt, der neue Text ausgegeben und        บ
  บ                    die Scroll-Pfeile an die nach dem Scrollen ent-     บ
  บ                    standene Situation angepaแt.                        บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  modulglobale Variablen:                             บ
  บ                    - wHilfsZeilen_m (R)                                บ
  บ                    - wStartzeile_m  (R/W)                              บ
  บ                    - ppstrTmp_m     (R)                                บ
  บ                    - wIndex_m       (R/W)                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_BalkenMinusEins(PHILFEINDEX pHI)
{
    PHILFEINDEX pHILokal;

    if (wAktZeile_m == 0 &&                         /* wenn Balken in Zeile */
        wIndex_m    != 0)                           /* 0, Fenster scrollen  */
    {
        LOESCHEBALKEN(wAktZeile_m);
        i_DlgScroll((SPA+1),(ZEI+3),(BRE+SPA-2),(ZEI+10),DOWN);
        wIndex_m--;
        pHILokal = pHI;
        pHILokal += wIndex_m;
        WinSs(1,2, pHILokal->pstrText);
        ZEICHNEBALKEN(wAktZeile_m);
    }

    else if (wAktZeile_m > 0 &&                   /* sonst nur den Auswahl- */
        wIndex_m < wHilfsZeilen_m)                /* Balken verschieben     */
    {
        LOESCHEBALKEN(wAktZeile_m);
        wIndex_m--;
        wAktZeile_m--;
        ZEICHNEBALKEN(wAktZeile_m);
    }

    else if(boBeepen_g)
        i_Beep();

    i_ZeichneScroller();

    return;
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_ZeichneScroller              Datum: 31.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion testet die Bedingungen fr           บ
  บ                    die Anzeige der Scrollpfeile und gibt die           บ
  บ                    Pfeile entsprechend aus.                            บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  modulglobale:                                       บ
  บ                    - wAktZeile_m      (R)                              บ
  บ                    - wIndex_m         (R)                              บ
  บ                    - wHilfsZeilen_m   (R)                              บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_ZeichneScroller(VOID)
{
    if( wIndex_m == wHilfsZeilen_m-1)
        WinSza(52,1,'ฤ',aCS_g[wCSInd_g].wCs_dlg);
    else
        WinSza(52,1,'',aCS_g[wCSInd_g].wCs_dlg_sp);

    if( wIndex_m == 0)
        WinSza(50,1,'ฤ',aCS_g[wCSInd_g].wCs_dlg);
    else
        WinSza(50,1,'',aCS_g[wCSInd_g].wCs_dlg_sp);

    return;
}


