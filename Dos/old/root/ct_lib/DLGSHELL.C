/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgShell                       Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR  pstrPrgName   Name des Programms, von dem aus บ
  บ                                        die DOS-Shell aufgerufen wird   บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion stellt eine Dialog-Box zur Ver-      บ
  บ                    fgung, mit der der Anwender entscheiden kann,      บ
  บ                    ob er eine DOS-Shell aktivieren will.               บ
  บ                                                                        บ
  บ                    Der Ausgabetext der Dialogbox erhlt einen Hin-     บ
  บ                    weis darauf, wie der Anwender zum Ursprungs-        บ
  บ                    programm zurckkehren kann.                         บ
  บ                                                                        บ
  บ                    Die Dialogbox hat drei Schaltflchen:               บ
  บ                          Eingabe, Abbruch und Hilfe                    บ
  บ                    Bei Auswhlen von Eingabe, wird das Betriebssystem  บ
  บ                    aufgerufen. Wird Abbruch ausgewhlt, wird sofort    บ
  บ                    zur aufrufenden Funktion zurckgekehrt.             บ
  บ                    Die Hilfe-Schaltflche stellt dem Anwender in       บ
  บ                    einer weiteren Dialog-Box Hilfsinformationen        บ
  บ                    zur Verfgung.                                      บ
  บ                                                                        บ
  บ                    Diese Funktion wird von UtlDosShell() aufgerufen.   บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD Fehlerinformation OK/ERROR                     บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  aCS_g         (R)                                   บ
  บ                    wCSInd_g      (R)                                   บ
  บ                    boBeepen_g    (R)                                   บ
  บ                    pstrReturn_g  (R)                                   บ
  บ                    pstrEsc_g     (R)                                   บ
  บ                    pstrF1_g      (R)                                   บ
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

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SPA   9
#define ZEI   5
#define BRE  60
#define HOE   8


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                   GLOBALE VARIABLEN, REFERENZEN                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT COLORSET  aCS_g[];
IMPORT WORD      wCSInd_g;
IMPORT BOOL      boBeepen_g;

IMPORT PSTR      pstrReturn_g;
IMPORT PSTR      pstrEsc_g;
IMPORT PSTR      pstrF1_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL PSTR pstrBSText_m = "Es wird das Betriebssystem aufgerufen.";
MGLOBAL PSTR pstrExit1_m  = "Geben Sie EXIT ein, um zum "
                            "Programm zurckzukehren.";
MGLOBAL PSTR pstrExit2_m  = "Geben Sie EXIT ein, um zu %s zurckzukehren.";


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgShell(PSTR pstrPrgName)
{
    PWKB    pWkbDialog;
    EVENT   Event;
    PEVENT  pEvent;

    i_InitVars();                                   /* Variablen            */
    pEvent = &Event;                                /* initialisieren       */

    if ((pWkbDialog = WinEinrichten(SPA, ZEI, BRE, HOE)) == NULL)
        return (ERROR);

    i_DlgInit(SPA, ZEI, BRE, HOE, "DOS-Shell",
             pWkbDialog, SF_STANDARD, DLG_INFO);

    WinSs(2,2,pstrBSText_m);                        /* Dialogtext ausgeben  */
    if (pstrPrgName == NULL)
        WinSs(2,3,pstrExit1_m);
    else
    {
        WinSetCursorPos(2,3);
        pstrPrgName = strrchr(pstrPrgName, '\\');
        pstrPrgName++;
        WinPrintf(pstrExit2_m, pstrPrgName);
    }

    for (;;)                                        /* Eingaberoutine       */
    {
        UtlEvent(pEvent);

        switch(pEvent->wArt)
        {
            case EVENT_TASTE:
                switch (pEvent->wTaste)
                {
                    case T_F1:      DlgHilfeTools(DOSSHELL);
                                    break;

                    case T_RETURN:  WinEntfernen(pWkbDialog);
                                    return(DLG_RETURN);

                    case T_ESC:     WinEntfernen(pWkbDialog);
                                    return(DLG_ESC);

                    default:        if (boBeepen_g)
                                        i_Beep();
                }
                break;

            case EVENT_L_PRESS:
                if (pEvent->wZeile == 6+ZEI)
                {
                    if (pEvent->wSpalte > SPA+2 &&
                        pEvent->wSpalte < SPA+3+strlen(pstrReturn_g))
                    {
                            WinEntfernen(pWkbDialog);
                            return(DLG_RETURN);

                    }
                    else if (pEvent->wSpalte > SPA+16 &&
                        pEvent->wSpalte < SPA+17+strlen(pstrEsc_g))
                    {
                            WinEntfernen(pWkbDialog);
                            return(DLG_ESC);

                    }
                    else if (pEvent->wSpalte > SPA+31 &&
                        pEvent->wSpalte < SPA+32+strlen(pstrF1_g))
                            DlgHilfeTools(DOSSHELL);

                    else if (boBeepen_g)
                        i_Beep();
                }
                break;
        } /* end of switch(pEvent->wEventart) */
    } /* end of for(;;) */
} /* end of DlgShell() */

