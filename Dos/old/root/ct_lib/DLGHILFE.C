/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgHilfe                       Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR   pstrTitel   Titel des Hilfe-Fensters         บ
  บ                    PPSTR  ppstrText   Hilfetext                        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion baut ein Dialog-Fenster fr          บ
  บ                    Hilfsinformationen auf. Das Fenster ist             บ
  บ                    14 Zeilen hoch und 56 Spalten breit.                บ
  บ                                                                        บ
  บ                    In Spalte 0 des Fensters wird der der Funktion      บ
  บ                    bergebene Parameter pstrTitel als Titel ausge-     บ
  บ                    gegeben.                                            บ
  บ                                                                        บ
  บ                    Der Bereich, in dem die Hilfsinformationen aus-     บ
  บ                    gegeben werden, ist 8 Zeilen hoch und 54 Spalten    บ
  บ                    breit. Eine Textzeile kann somit maximal 54         บ
  บ                    Zeichen beinhalten.                                 บ
  บ                    Wenn der Hilfe-Text mehr als acht Zeilen umfaแt,    บ
  บ                    stellt die Funktion dem Anwender eine Scroll-       บ
  บ                    M”glichkeit zur Verfgung.                          บ
  บ                                                                        บ
  บ                    Im unteren Bereich der Dialogbox befinden sich      บ
  บ                    zwei Schaltflchen. Mit der Esc-Schaltflche        บ
  บ                    kann der Anwender die Hilfe beenden. Mit der        บ
  บ                    F1-Schaltflche kann Hilfe zur Bedienung der        บ
  บ                    Dialogbox angefordert werden.                       บ
  บ                                                                        บ
  บ                    Eine aktive Maus wird automatisch untersttzt.      บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation OK/ERROR                    บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - aCS_g[]    (R)           - pstrEsc_g   (R)        บ
  บ                    - wCSInd_g   (R)           - pstrF1_g    (R)        บ
  บ                    - wMausda_g  (R)           - boBeepen_g  (R)        บ
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
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define ZEI   HILFEZEILE                            /* Zeile des Dialoges   */
#define SPA   HILFESPALTE                           /* Spalte des Dialoges  */
#define BRE        56                               /* Breite des Dialoges  */
#define HOE        14                               /* H”he des Dialoges    */
#define SCR_DELAY   1              /* Zeitverz”gerung fr Maus-Dauer-Scroll */

#define PFEILOBENAN()       WinSza(50,1,'',aCS_g[wCSInd_g].wCs_dlg_sp)
#define PFEILOBENAUS()      WinSza(50,1,'ฤ',aCS_g[wCSInd_g].wCs_dlg)

#define PFEILUNTENAN()      WinSza(52,1,'',aCS_g[wCSInd_g].wCs_dlg_sp)
#define PFEILUNTENAUS()     WinSza(52,1,'ฤ',aCS_g[wCSInd_g].wCs_dlg)

#define ZEICHNEBALKEN(z)    WinSwa(1,z+2, 52,1,aCS_g[wCSInd_g].wCs_mf_ca)
#define LOESCHEBALKEN(z)    WinSwa(1,z+2, 52,1,aCS_g[wCSInd_g].wCs_dlg)



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL WORD   wStartzeile_m;
MGLOBAL WORD   wHilfsZeilen_m;
MGLOBAL WORD   wAktZeile_m=0;
MGLOBAL PPSTR  ppstrTmp_m;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE FUNKTIONEN                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL VOID i_EineZeileHoch        (VOID);
MGLOBAL VOID i_EineZeileRunter      (PPSTR);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgHilfe(PSTR pstrTitel, PPSTR ppstrTxt)
{
    PWKB    pWkbDialog;
    EVENT   Event;
    PEVENT  pEvent;
    LONG    lPfeilTicks;

    i_InitVars();                                   /* glo. Var. init.      */

    if ((pWkbDialog=WinEinrichten(SPA,ZEI,BRE,HOE)) /* Fenster einrichten   */
        == NULL)
        return (ERROR);                             /* evtl. Abbruch        */

    i_DlgInit(SPA, ZEI, BRE, HOE,
              pstrTitel,
              pWkbDialog,
              SF_ABBRUCH|SF_HILFE,
              DLG_INFO);

    pEvent = &Event;                                /* Var. initialisieren  */
    ppstrTmp_m = ppstrTxt;
    wStartzeile_m = 0;

    for (wHilfsZeilen_m=0;                          /* Anzahl der Hilfs-    */
         *ppstrTmp_m++ != NULL;                     /* zeilen ermitteln     */
         wHilfsZeilen_m++);
    ppstrTmp_m = ppstrTxt;                          /* Zeiger zurcksetzen  */

    if (wHilfsZeilen_m > TEXTZEILEN)                /* evtl. Scrollpfeil    */
        PFEILUNTENAN();                             /* einschalten          */

    i_DlgHilfeSchreibeText(ppstrTmp_m);             /* Hilfstext ausgeben   */

    for(;;)                                         /* Eingaberoutine       */
    {
        UtlEvent(pEvent);
        switch(pEvent->wArt)
        {
           case EVENT_TASTE:
              switch(pEvent->wTaste)
              {
               case T_PGUP:
                  if (wStartzeile_m != 0)
                  {
                     ppstrTmp_m = ppstrTxt;
                     wStartzeile_m = 0;
                     WinSwz(0,2,54,8,32);
                     i_DlgHilfeSchreibeText(ppstrTmp_m);
                     if (wHilfsZeilen_m > TEXTZEILEN)
                     {
                        PFEILUNTENAN();
                        PFEILOBENAUS();
                     }
                  }
                  break;

               case T_PGDN:
                  if (wStartzeile_m != wHilfsZeilen_m-MINZEILEN)
                  {
                     wStartzeile_m = wHilfsZeilen_m - MINZEILEN;
                     ppstrTmp_m    = ppstrTxt+wStartzeile_m;
                     WinSwz(0,2,54,8,32);
                     i_DlgHilfeSchreibeText(ppstrTmp_m);

                     if (wHilfsZeilen_m > TEXTZEILEN)
                     {
                        PFEILUNTENAUS();
                        PFEILOBENAN();
                     }
                  }
                  break;

               case T_DOWN:
                  i_EineZeileHoch();
                  break;

               case T_UP:
                  i_EineZeileRunter(ppstrTxt);
                  break;

               case T_F1:
                  i_DlgHilfeFuerHilfe();
                  break;

               case T_ESC:
                  WinEntfernen(pWkbDialog);
                  return(OK);

               default:
                  if (boBeepen_g)
                     i_Beep();
              } /* end of switch(pEvent->wTaste) */
              break;

           case EVENT_L_PRESS:
              if (pEvent->wZeile == (ZEI+2))
              {
                  if (pEvent->wSpalte == (SPA+51))
                  {
                      lPfeilTicks = pEvent->lTicks;
                      i_EineZeileRunter(ppstrTxt);
                  }
                  else if (pEvent->wSpalte == (SPA+53))
                  {
                      lPfeilTicks = pEvent->lTicks;
                      i_EineZeileHoch();
                  }
              }

              else if (pEvent->wZeile == (ZEI+12))
              {
                 if (pEvent->wSpalte > SPA+2 &&
                     pEvent->wSpalte < SPA+3+strlen(pstrEsc_g))
                 {
                    WinEntfernen(pWkbDialog);
                    return(OK);
                 }
                 else if (pEvent->wSpalte > SPA+16 &&
                       pEvent->wSpalte < SPA+17+strlen(pstrF1_g))
                 {
                    i_DlgHilfeFuerHilfe();
                }
             }
              else if (boBeepen_g)
                 i_Beep();
             break;

           default:
             if (pEvent->wButton == MSM_L_DOWN &&
                 pEvent->lTicks-lPfeilTicks >= SCR_DELAY &&
                 pEvent->wZeile == (ZEI+2))
             {
                if (pEvent->wSpalte == (SPA+51))
                {
                    lPfeilTicks = pEvent->lTicks;
                    i_EineZeileRunter(ppstrTxt);
                }
                else if (pEvent->wSpalte == (SPA+53))
                {
                    lPfeilTicks = pEvent->lTicks;
                    i_EineZeileHoch();
                }
             }

        } /* end of switch(pEvent->wArt) */
    } /* end of for */
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_EineZeileHoch                Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion steuert das Scrollen und die  Neu-   บ
  บ                    ausgabe des Hilfstextes bei DlgHilfe().             บ
  บ                    Eine Aktion wird erst dann ausgefhrt, wenn         บ
  บ                    mehr als die in der Konstante MINZEILEN angegebenen บ
  บ                    Zeilen noch im Fenster stehen.                      บ
  บ                    In diesem Fall wird der im Fenster stehende         บ
  บ                    Text gescrollt, der neue Text ausgegeben und        บ
  บ                    die Scroll-Pfeile an die nach dem Scrollen ent-     บ
  บ                    standene Situation angepaแt.                        บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  modulglobale Variablen:                             บ
  บ                    - wHilfsZeilen_m (R)                                บ
  บ                    - wStartzeile_m  (R/W)                              บ
  บ                    - ppstrTmp_m     (R)                                บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_EineZeileHoch(VOID)
{
    if (wHilfsZeilen_m > TEXTZEILEN)
    {
        if (wStartzeile_m < (wHilfsZeilen_m - MINZEILEN) )
        {
            i_DlgScroll((SPA+1),(ZEI+3),(BRE+SPA-2),(ZEI+10),UP);

            i_DlgHilfeSchreibeText(ppstrTmp_m+=1);
            wStartzeile_m++;
            if(wStartzeile_m != 0)
                PFEILOBENAN();
            if (wStartzeile_m == wHilfsZeilen_m - MINZEILEN)
                PFEILUNTENAUS();
        }
        else if (boBeepen_g)
            i_Beep();
    }

    return;
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_EineZeileRunter              Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PPSTR ppstrTxt  Zeiger auf erste Zeile der          บ
  บ                                    Hilfstexte                          บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion steuert das Scrollen und die  Neu-   บ
  บ                    ausgabe des Hilfstextes bei DlgHilfe().             บ
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
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_EineZeileRunter(PPSTR ppstrTxt)
{
    if (wHilfsZeilen_m > TEXTZEILEN)
    {
        if (ppstrTmp_m != ppstrTxt)
        {
            i_DlgScroll((SPA+1),(ZEI+3),(BRE+SPA-2),(ZEI+10),DOWN);
            i_DlgHilfeSchreibeText(ppstrTmp_m-=1);
            wStartzeile_m--;
            if (wStartzeile_m != wHilfsZeilen_m - MINZEILEN)
                PFEILUNTENAN();
            if (wStartzeile_m == 0)
                PFEILOBENAUS();
        }
        else if (boBeepen_g)
            i_Beep();
    }
    return;
}







