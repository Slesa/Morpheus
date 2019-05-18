/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        idialog.c                      Datum: 31.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Diese Datei enthlt die Definitionen folgender interner Funktionen    บ
  บ  des Dialog-Moduls:                                                    บ
  บ                                                                        บ
  บ         - i_DlgInit()                Dialogbox initialsieren,          บ
  บ                                      Schaltflchen und Titel           บ
  บ         - i_DlgHilfeFuerHilfe()      allg. Hilfefenster                บ
  บ         - i_DlgHilfeSchreibeText()   Text ausgeben                     บ
  บ         - i_DlgScroll()              scrollen                          บ
  บ                                                                        บ
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
#include <dos.h>


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                   GLOBALE VARIABLEN, REFERENZEN                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT COLORSET  aCS_g[];
IMPORT WORD      wCSInd_g;
IMPORT BOOL      boBeepen_g;

IMPORT PSTR      pstrReturn_g;
IMPORT PSTR      pstrEsc_g;
IMPORT PSTR      pstrF1_g;
IMPORT PSTR      pstrRetry_g;

IMPORT WORD      wMausda_g;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define ZEI  (HILFEZEILE+2)                         /* Koordinaten und Aus- */
#define SPA  (HILFESPALTE+2)                        /* dehnung vom Hilfe-   */
#define BRE        56                               /* fr-Hilfe-Dialogfeld */
#define HOE        14


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

MGLOBAL PSTR   apstrHFH_m[]=
{
    "    Folgende Tasten stehen zu Ihrer Verfgung:",
    "",
    "     þ       scrollt Text eine Zeile nach oben",
    "     þ       scrollt Text eine Zeile nach unten",
    "     þ Pos1   geht an den Anfang des Hilfstextes",
    "     þ Ende   geht an das Ende des Hilfstextes",
    "",
    "     þ Esc    Hilfe beenden",
    "",
    "Markieren Sie im Hilfeindex das Thema, zu dem Sie",
    "Hilfe wnschen, und drcken Sie anschlieแend die ",
    "<ฤู - Taste.",
    NULL
};



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgInit                      Datum: 31.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte       Position und Ausdehnung          บ
  บ                    WORD wZeile             der Dialogbox               บ
  บ                    WORD wBreite                                        บ
  บ                    WORD wHoehe                                         บ
  บ                    PSTR pstrTitel     Zeiger auf Titel oder NULL       บ
  บ                    PWKB pWkb          Zeiger auf Windowkontrollblock   บ
  บ                    WORD wSchalt       Information ber Schaltflchen   บ
  บ                    WORD wDlgTyp       Dialogtyp zur Bestimmung der     บ
  บ                                       Attribute                        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion initialisiert eine Dialogbox         บ
  บ                    in den Standard-Farben. Die Attribute werden        บ
  บ                    gesetzt, ein evtl. vorhandener Titel ausgegeben,    บ
  บ                    die erforderlichen Trennlinien gezeichnet und       บ
  บ                    und die angeforderten Schaltflchen plaziert.       บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - aCS_g[]  (R)                                     บ
  บ                     - wCSInd_g   (R)                                   บ
  บ                     - pstrReturn_g  (R)                                บ
  บ                     - pstrEsc_g   (R)                                  บ
  บ                     - pstrF1_g   (R)                                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_DlgInit(WORD wSpalte, WORD wZeile,
               WORD wBreite, WORD wHoehe,
               PSTR pstrTitel,
               PWKB pWkb,
               WORD wSchalt,
               WORD wDlgTyp)
{

    WORD wLaenge;
    WORD wSpalteSF;
    WORD wFarbeSF;


    switch (wDlgTyp)                                /* Attribute festlegen  */
    {
        case DLG_WARNUNG:
                WinSetAttri(pWkb, 0,
                            aCS_g[wCSInd_g].wCs_wdlg,
                            aCS_g[wCSInd_g].wCs_wdlg);
                wFarbeSF = aCS_g[wCSInd_g].wCs_wdlg_sf;
                break;

        case DLG_KRITISCH:
                WinSetAttri(pWkb, 0,
                            aCS_g[wCSInd_g].wCs_fdlg,
                            aCS_g[wCSInd_g].wCs_fdlg);
                wFarbeSF = aCS_g[wCSInd_g].wCs_wdlg_sf;
                break;

        default:
                WinSetAttri(pWkb, 0,
                            aCS_g[wCSInd_g].wCs_dlg,
                            aCS_g[wCSInd_g].wCs_dlg);
                wFarbeSF = aCS_g[wCSInd_g].wCs_dlg_sf;
                break;
    }

    WinSchattenEin(pWkb);                           /* Schatten aktivieren  */

    WinAktivieren(pWkb);                            /* Fenster anzeigen     */


    if ( (wLaenge=strlen(pstrTitel)) != 0)          /* wenn Titel vorhanden */
    {
        WinSwza(0, 0, wBreite-2, 1, ' ',            /* Titelzeile hervor-   */
                aCS_g[wCSInd_g].wCs_dlg_tz);        /* heben                */
        WinSsa((wBreite-wLaenge)/2, 0,              /* Titel zentriert aus- */
                pstrTitel,                          /* geben                */
                aCS_g[wCSInd_g].wCs_dlg_tt);
        WinSza((wBreite-wLaenge)/2-1, 0,
               ' ', aCS_g[wCSInd_g].wCs_dlg_tt);
        WinSza((wBreite+wLaenge)/2, 0,
               ' ', aCS_g[wCSInd_g].wCs_dlg_tt);
        WinSwz(0, 1, wBreite-2, 1, 'ฤ');            /* Trennlinie zeichnen  */
    }

    WinSwz(0, wHoehe-4, wBreite-2, 1, 'ฤ');         /* untere Trennlinie    */

    wSpalteSF = 2;

    if (UtlBitTest(wSchalt, SF_EINGABE))            /* wahlweise Schaltfl.  */
    {
        WinSsa(wSpalteSF, wHoehe-3,
               pstrReturn_g, wFarbeSF);
        wSpalteSF += ( strlen(pstrReturn_g) +3);
    }

    if (UtlBitTest(wSchalt, SF_ABBRUCH))            /* wahlweise Schaltfl.  */
    {
        WinSsa(wSpalteSF, wHoehe-3,
               pstrEsc_g, wFarbeSF);
        wSpalteSF += ( strlen(pstrEsc_g) +3);
    }

    if ( !(UtlBitTest(wSchalt, SF_EINGABE)) &&      /* nur wenn EINGABE und */
         !(UtlBitTest(wSchalt, SF_ABBRUCH)) )       /* ABBRUCH noch nicht   */
    {                                               /* gewhlt wurden       */

        if (UtlBitTest(wSchalt, SF_RETRYCANCEL))
        {
            WinSsa(wSpalteSF, wHoehe-3,
                   pstrRetry_g, wFarbeSF);
            wSpalteSF += ( strlen(pstrRetry_g) +3);
            WinSsa(wSpalteSF, wHoehe-3, pstrEsc_g,
                   wFarbeSF);
        }

    /*  Dieser Teil ist fr sptere Erweiterungen reserviert.
     *
     *  else if (UtlBitTest(wSchalt, SF_JANEIN))
     *      ;
     *  else if (UtlBitTest(wSchalt, SF_JANEINABBRUCH))
     *      ;
     *  else if (UtlBitTest(wSchalt, SF_ABORTRETRYIGNORE))
     *      ;
     */

    }

    if (UtlBitTest(wSchalt, SF_HILFE))              /* wahlweise Schaltfl.  */
    {                                               /* (muแ rechts stehen!) */
        WinSsa(wSpalteSF, wHoehe-3,
               pstrF1_g, wFarbeSF);
    }

    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_HilfeFuerHilfe               Datum: 31.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion liefert Informationen ber die       บ
  บ                    Tasten zur Bedienung des Hilfedialoges.             บ
  บ                    Das Fenster bleibt solange aktiv, bis auf die       บ
  บ                    Eingabeschaltflche geklickt wird oder              บ
  บ                    die Enter-Taste bettigt wird.                      บ
  บ                                                                        บ
  บ  Rckgabewert:     keiner                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  modulglobale:               globale:                บ
  บ                    - pstrReturn_m   (R)        - aCS_g   (R)           บ
  บ                    - apstrHFH_m     (R)        - wCSInd_g (R)          บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_DlgHilfeFuerHilfe(VOID)
{
    EVENT   Event;
    PEVENT  pEvent;
    PWKB    pWkbDialog;

    pEvent = &Event;                                /* Zeiger initial.      */

    if ((pWkbDialog=WinEinrichten(SPA,ZEI,BRE,HOE)) /* Fenster einrichten   */
        == NULL)
    {
        i_Beep();                                   /* Warnton ausgeben     */
        return;                                     /* Abbruch              */
    }

    i_DlgInit(SPA, ZEI, BRE, HOE,
              "Hilfe fr Hilfe",
              pWkbDialog,
              SF_ABBRUCH,
              DLG_INFO);

    i_DlgHilfeSchreibeText(apstrHFH_m);             /* Hilfstext ausgeben   */

    for (;;)                                        /* Eingaberoutine       */
    {
        UtlEvent(pEvent);
        switch(pEvent->wArt)
        {
            case EVENT_TASTE:
                    if (pEvent->wTaste == T_ESC)
                    {
                        WinEntfernen(pWkbDialog);
                        return;
                    }
                    else if (boBeepen_g)
                        i_Beep();
                    break;

            case EVENT_L_PRESS:
                    if (pEvent->wZeile == ZEI+12)
                    {
                        if (pEvent->wSpalte > SPA+2 &&
                            pEvent->wSpalte < SPA+3+strlen(pstrEsc_g))
                            {
                                WinEntfernen(pWkbDialog);
                                return;
                            }
                    }
                    else if (boBeepen_g)
                        i_Beep();
                    break;
        }
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgHilfeSchreibeText         Datum: 31.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PPSTR  ppstrT            Ausgabetext                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt ab der Zeile 2 des              บ
  บ                    Dialogfensters den bergebenen Text fr die         บ
  บ                    Funktion DlgHilfe() aus.                            บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_DlgHilfeSchreibeText(PPSTR ppstrT)
{
    REGISTER i, wZeile;

    for( i=0, wZeile=2;
         i<TEXTZEILEN && *ppstrT != NULL;
         wZeile++,i++)
             WinSs(1,wZeile, *ppstrT++);            /* Zeile ausgeben       */
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgScroll                    Datum: 31.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        BYTE   byRichtung     Richtung, in der gescrollt    บ
  บ                                          werden soll                   บ
  บ                                          UP/DOWN                       บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion scrollt den Hilfetext im             บ
  บ                    Dialogfenster um eine Zeile in die bergebene       บ
  บ                    Richtung.                                           บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - aCS_g[]  (R)                                      บ
  บ                    - wCSInd_g (R)                                      บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_DlgScroll(WORD wSpOl, WORD wZeOl,
                 WORD wSpUr, WORD wZeUr,
                 BYTE byRichtung)
{
    union REGS regs;
    WORD wStatus;
    if (wMausda_g)
        wStatus = MsmCursorOff();

    regs.h.ah = byRichtung;                         /* Richtung             */
    regs.h.al = 1;                                  /* Anzahl Zeilen        */
    regs.h.bh = (unsigned char)
                UtlLowByte(aCS_g[wCSInd_g].wCs_dlg);/* Attribut             */
    regs.h.cl = (BYTE) wSpOl;                       /* Spalte oben links    */
    regs.h.ch = (BYTE) wZeOl;                       /* Zeile oben links     */
    regs.h.dl = (BYTE) wSpUr;                       /* Spalte unten rechts  */
    regs.h.dh = (BYTE) wZeUr;                       /* Zeile unten rechts   */


    int86(0x10, &regs, &regs);                      /* Interrupt ausl”sen   */
    if (wMausda_g && wStatus == MSM_WAR_AN)
        wStatus = MsmCursorOn();

    return;                                         /* das war's            */
}

