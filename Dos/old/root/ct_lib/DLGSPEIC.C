/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgSpeichernUnter              Datum: 28.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR   pstrDateiName    Zeiger auf derzeitigen      บ
  บ                                            Dateinamen                  บ
  บ                                                                        บ
  บ                    WORD   wMaxLaenge       maximale Lnge des          บ
  บ                                            Dateinamens                 บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion k”nnen Sie dem Anwender er-     บ
  บ                    m”glichen, fr die aktuell bearbeitete Datei        บ
  บ                    einen neuen Namen festzulegen.                      บ
  บ                                                                        บ
  บ                    bergeben Sie der Funktion einen Zeiger auf         บ
  บ                    den derzeitigen Dateinamen und die maximale         บ
  บ                    Lnge, die der Dateiname haben darf. Die Lnge      บ
  บ                    des Dateinamens muแ mindestens 37 Zeichen (Wert der บ
  บ                    Konstanten TBB) sein.                               บ
  บ                                                                        บ
  บ                    Diese Funktion baut ein Dialogfeld auf, in dem      บ
  บ                    das aktuelle Verzeichnis ausgegeben wird. Der       บ
  บ                    derzeitige Dateiname erscheint in einem Textfeld,   บ
  บ                    das vom Anwender editiert werden kann, um den       บ
  บ                    Dateinamen zu ndern.                               บ
  บ                                                                        บ
  บ                    Das Dialogfeld besitzt drei Schaltflchen, die      บ
  บ                    folgende Wirkung haben:                             บ
  บ                    - Eingabe  kopiert den derzeitgen Namen der Datei   บ
  บ                               in den Speicherbereich, auf den          บ
  บ                               das Argument pstrDateiName zeigt.        บ
  บ                               Sie mssen dafr sorgen, daแ der         บ
  บ                               Speicherbereich groแ genug ist, um       บ
  บ                               wMaxlaenge Zeichen aufzunehmen.          บ
  บ                    - Esc      beendet das Dialogfeld                   บ
  บ                    - F1       zeigt ein Hilfefenster fr dieses        บ
  บ                               Dialogfeld an                            บ
  บ                                                                        บ
  บ                    Die Funktion fhrt eine berprfung durch, ob       บ
  บ                    der eingegebene Dateiname den DOS-Konventionen      บ
  บ                    entspricht. Das Dialogfeld kann erst dann mit       บ
  บ                    der Eingabe-Schaltflche verlassen werden, wenn     บ
  บ                    dieser Test erfolgreich war.                        บ
  บ                                                                        บ
  บ                    Die Funktion prft nicht, ob das eingebene Lauf-    บ
  บ                    werk oder Verzeichnis auch tatschlich existieren.  บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Wahl des Anwenders                            บ
  บ                          - DLG_RETURN  der Anwender hat die            บ
  บ                                        Eingabe-Schaltflche gewhlt    บ
  บ                                                                        บ
  บ                          - DLG_ESC     der Anwender hat die            บ
  บ                                        Esc-Schaltflche bettigt       บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - aCS_g[]      (R)                                 บ
  บ                     - wCSInd_g     (R)                                 บ
  บ                     - boBeepen_g   (R)                                 บ
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
#define SPA  9
#define ZEI  5
#define BRE 56
#define HOE 12

#define TBS SPA+16
#define TBZ ZEI+6
#define TBB BRE-19

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT COLORSET  aCS_g[];
IMPORT WORD      wCSInd_g;
IMPORT BOOL      boBeepen_g;
IMPORT WORD      wMausda_g;
IMPORT PSTR      pstrReturn_g;
IMPORT PSTR      pstrEsc_g;
IMPORT PSTR      pstrF1_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL PSTR pstrDTitel_m = "Speichern unter";
MGLOBAL PSTR pstrVerz_m   = "Verzeichnis:";
MGLOBAL PSTR pstrD_m      = "Dateiname:";
MGLOBAL PSTR apstrFalscherName_m[]=
{
    " Der eingegebene Dateiname ist ungltig.",
    NULL,
};

MGLOBAL WORD i_ProcessEvent(PTEXTBOX pT, PEVENT pE);

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgSpeichernUnter(PSTR pstrDateiName, WORD wMaxLaenge)
{
    PWKB     pWkbDialog;
    EVENT    Event;
    PEVENT   pEvent;
    TEXTBOX  TextBox;
    PTEXTBOX pTextBox;
    WORD     wResult,
             wMausStatus;
    CHAR     acPfadName[80];

    i_InitVars();                                   /* Var. initialisieren  */
    pEvent   = &Event;
    pTextBox = &TextBox;

    strcpy(pTextBox->acText, pstrDateiName);        /* TEXTBOX-Struktur     */
    pTextBox->wAttri = aCS_g[wCSInd_g].wCs_dlg;     /* initialisieren       */
    pTextBox->wFensterS = TBS;
    pTextBox->wFensterZ = TBZ;
    pTextBox->wFensterB = TBB;
    pTextBox->wCursorS  = TBS;
    pTextBox->wMaxL     = wMaxLaenge>TB_MAX ? TB_MAX : wMaxLaenge;
    pTextBox->boInsert  = WAHR;


    if ((pWkbDialog=WinEinrichten(SPA,ZEI,BRE,HOE)) /* Fenster einrichten   */
        == NULL)
            return (ERROR);                         /* evtl. Abbruch        */

    getcwd(acPfadName,80);                          /* aktuelles Verzeichnis*/
                                                    /* holen                */

    i_DlgInit(SPA, ZEI, BRE, HOE,                   /* Dialogbox initialis. */
                        pstrDTitel_m,
                        pWkbDialog,
                        SF_STANDARD,
                        DLG_INFO);

    WinSs(1,2,pstrVerz_m);                          /* Texte und aktuelles  */
    WinSs(15,2,acPfadName);                         /* Verzeichnis ausgeben */
    WinSs(1,5,pstrD_m);

    wMausStatus = MsmCursorOff();                   /* Maus vor Ausgabe aus */
    UtlZeigeRahmen(TBS-1, TBZ-1, TBB+2, 3,          /* Rahmen fr das Text- */
                                 RT_EEEE,           /* feld ausgeben        */
                                 aCS_g[wCSInd_g].wCs_dlg);
    if (wMausStatus == MSM_WAR_AN && wMausda_g)     /* wenn Maus an war,    */
        MsmCursorOn();                              /* wieder ein           */

    i_DlgLiesZK(pTextBox, pEvent, AKT_BUFFER);      /* Zeileneditor initial.*/

    WinSetCursorPos(TBS-SPA-1,TBZ-ZEI-1);
    WinCursor(EIN);

    for (;;)
    {
        wResult = i_ProcessEvent(pTextBox, pEvent);
        switch(wResult)
        {
            case DLG_ESC:
                WinEntfernen(pWkbDialog);
                return(DLG_ESC);

            case DLG_RETURN:
                 i_DlgLiesZK(pTextBox, pEvent, AKT_TEXTBOX);
                 if (UtlDateinameGueltig(pTextBox->acText) == DN_UNGUELTIG)
                 {
                    i_DlgLiesZK(pTextBox, pEvent, AKT_BUFFER);
                    DlgInfo(apstrFalscherName_m, DLG_WARNUNG);
                    break;
                 }
                 else
                 {
                    i_DlgLiesZK(pTextBox, pEvent, AKT_BUFFER);
                    if (strrchr(pTextBox->acText,'*') != NULL ||
                        strrchr(pTextBox->acText,'?') != NULL)
                    {
                        DlgInfo(apstrFalscherName_m, DLG_WARNUNG);
                        break;
                    }
                    else
                    {
                        WinEntfernen(pWkbDialog);
                        strcpy(pstrDateiName, pTextBox->acText);
                        return(DLG_RETURN);
                    }
                 }
                 break;
        } /* end of switch */
    } /* end of for */
} /* end of DlgSpeichernUnter() */




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_ProcessEvent                 Datum: 28.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PTEXTBOX pTextBox   Zeiger auf Textbox-Struktur     บ
  บ                    PEVENT   pEvent     Zeiger auf Event-Struktur       บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion wertet die Anwendereingaben aus,     บ
  บ                    zeigt nach Anforderung das Hilfefenster, und        บ
  บ                    kehrt zur aufrufenden Funktion zurck, wenn         บ
  บ                    entweder die Schaltflche ABBRUCH oder EINGABE      บ
  บ                    bettigt wurde.                                     บ
  บ                                                                        บ
  บ  Rckgabewert:     DLG_ESC     ABBRUCH-Schaltflche wurde ausgewhlt   บ
  บ                    DLG_RETURN  EINGABE-Schaltflche wurde ausgewhlt   บ
  บ                                                                        บ
  บ  Benutzte globale   - pstrReturn_g (R)                                 บ
  บ  Variablen (R/W):   - pstrEsc_g    (R)                                 บ
  บ                     - pstrF1_g     (R)                                 บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
WORD i_ProcessEvent(PTEXTBOX pT, PEVENT pE)
{
    for(;;)                                           /* Eingaberoutine       */
    {
        UtlEvent(pE);
        switch(pE->wArt)
        {
            case EVENT_TASTE:
                switch(pE->wTaste)
                {
                    case T_F1:
                        DlgHilfeTools(SPEICHERN);
                        break;

                    case T_ESC:
                        return(DLG_ESC);

                    case T_RETURN:
                        return(DLG_RETURN);
                }

            case EVENT_L_PRESS:
                if (pE->wZeile == ZEI+HOE-2)
                {
                    if (pE->wSpalte > SPA+2 &&      /* RETURN-Schaltflche  */
                        pE->wSpalte < SPA+3+strlen(pstrReturn_g))
                        return(DLG_RETURN);

                    if (pE->wSpalte > SPA+17 &&     /* ESC-Schaltflche     */
                        pE->wSpalte < SPA+18+strlen(pstrEsc_g))
                        return(DLG_ESC);

                    if (pE->wSpalte > SPA+30 &&     /* Hilfe-Schaltflche   */
                        pE->wSpalte < SPA+31+strlen(pstrF1_g))
                        DlgHilfeTools(SPEICHERN);
                    } /* end of if (pE->wZeile == ZEI+HOE-2) */
        } /* end of switch(pE->wEventart) */
    i_DlgLiesZK(pT, pE,AKT_GARNIX);
    } /* end of for */
}
