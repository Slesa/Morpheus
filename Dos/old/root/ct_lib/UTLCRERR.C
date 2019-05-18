/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        utlcrerr.c                     Datum: 12.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Diese Datei enthlt die Routinen zur Installation und Deinstallation  บ
  บ  eines Critical Error Handlers (Interrupt 0x24).                       บ
  บ  Diese Routinen werden von der Funktion DlgLaden() eingesetzt,         บ
  บ  k”nnen jedoch nach Modifizierung auch fr andere Programme            บ
  บ  benutzt werden.                                                       บ
  บ                                                                        บ
  บ  Sie sollten diese Routinen erst dann ndern, wenn Sie mit den         บ
  บ  internen Ablufen beim Auftreten eines Critical Errors vertraut sind, บ
  บ  um einen Crash des Systems zu vermeiden.                              บ
  บ                                                                        บ
  บ  Hinweis: Weitere Informationen ber Critical Error Handler finden     บ
  บ           Sie u.a. in:                                                 บ
  บ        þ  MS-DOS Programmierhandbuch, DOS 3.1, Seite 1-37 ff.,         บ
  บ                  Markt & Technik, 1986                                 บ
  บ        þ  Ray Duncan, Advanced MS-DOS, Seite 130 ff.,                  บ
  บ                  Microsoft Press, 1986                                 บ
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
#include <dos.h>
#include <string.h>
#include <DEFS.H>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define ZEI         7                               /* Zeile des Dialoges   */
#define SPA        11                               /* Spalte des Dialoges  */
#define BRE        57                               /* Breite des Dialoges  */
#define HOE        11                               /* H”he des Dialoges    */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT BOOL     boBeepen_g;
IMPORT PSTR     pstrRetry_g;
IMPORT PSTR     pstrEsc_g;
IMPORT PSTR     pstrF1_g;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ               MODULGLOBALE FUNKTIONEN - PROTOTYPEN                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
STATIC VOID interrupt far fpfnNeuerHandler
           (unsigned es, unsigned ds, unsigned di,
            unsigned si, unsigned bp, unsigned sp,
            unsigned bx, unsigned dx, unsigned cx,
            unsigned ax);
STATIC WORD LadenFehler(WORD, WORD, WORD, WORD);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                    MODULGLOBALE VARIABLEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
STATIC VOID (interrupt far *fpfnAlterHandler_m) (VOID);
STATIC WORD (*routine) (WORD, WORD, WORD, WORD);
STATIC CHAR *icon_ausruf[]=
{   "ฺฤฤฤฤฤฤฤฟ",
    "ณ  Û Û  ณ",
    "ณ  Û Û  ณ",
    "ณ  Ü Ü  ณ",
    "ภฤฤฤฤฤฤฤู",
    NULL
};


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlSetErrorHandler             Datum: 12.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wWelcher      Routine, die installiert werden บ
  บ                                        soll                            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion sichert den aktuellen Vektor auf     บ
  บ                    die Behandlungsroutine, legt aufgrund des           บ
  บ                    Parameters wWelcher die neue Routine fest und       บ
  บ                    trgt diese in die Interruptvektor-Tabelle ein.     บ
  บ                                                                        บ
  บ  Rckgabewert:     keiner                                              บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  fpfnAlterHandler   (W), routine (W)                 บ
  บ                    fpfnNeuerHandler                (R)                 บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlSetNeuErrorHandler(WORD wWofuer)
{
    fpfnAlterHandler_m = _dos_getvect(0x24);        /* Interrupt-Vektor    */
                                                    /* sichern             */
    switch(wWofuer)                                 /* neue Adresse der    */
    {                                               /* Routine festlegen   */
        case LADEN:     routine = LadenFehler;
                        break;
    }
    _dos_setvect(0x24,fpfnNeuerHandler);            /* und in Int-Vektor-  */
                                                    /* Tabelle eintragen   */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlSetAltErrorHandler          Datum: 12.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion restauriert die ursprngliche        บ
  บ                    Routine zur Behandlung der kritischen Fehler.       บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  fpfnAlterHandler_m   Zeiger auf Interrupt-Routine   บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlSetAltErrorHandler(VOID)
{
    if (fpfnAlterHandler_m != 0)
        _dos_setvect(0x24, fpfnAlterHandler_m);
}





/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    fpfnNeuerHandler               Datum: 12.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        die fr eine Interrupt-Routine ben”tigten           บ
  บ                    Register (der Compiler erkennt nur die Reihenfolge  บ
  บ                    der Argumente, nicht deren Namen)                   บ
  บ                                                                        บ
  บ  Beschreibung:     Von dieser Funktion aus wird die Behandlungs-       บ
  บ                    routine fr den kritischen Fehler angesprungen.     บ
  บ                    Die Funktion erhlt aus                             บ
  บ                                                                        บ
  บ                    DI  den von MS-DOS zur Verfgung gestellten         บ
  บ                        Fehlercode (niederwertiges Byte)                บ
  บ                    AX  Informationen ber Gertefehler                 บ
  บ                        AX > 0  Diskettenfehler                         บ
  บ                                AX & 0xFF ergibt Nummer des Laufwerks   บ
  บ                                          (1=A, 2=B usw.)               บ
  บ                           < 0  sonstiger Fehler                        บ
  บ                    BP:SI zeigt auf den Kopf des Gertetreibers         บ
  บ                                                                        บ
  บ  Rckgabewert:     Wert im AX-Register als Information fr DOS         บ
  บ                                                                        บ
  บ  Hinweis:          Weitere Informationen ber den Modifizierer         บ
  บ                    interrupt finden Sie im Handbuch Ihres Compilers.   บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  routine  Enthlt die Adresse der Routine, die       บ
  บ                             bei einem Fehler angesprungen wird         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
STATIC
VOID interrupt far fpfnNeuerHandler
        (unsigned es, unsigned ds, unsigned di,
         unsigned si, unsigned bp, unsigned sp,
         unsigned bx, unsigned dx, unsigned cx,
         unsigned ax)
{
    ax = (*routine) (di&0x00FF, ax, bp, si);
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    LadenFehler                    Datum: 12.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wFehler       siehe Beschreibung zu           บ
  บ                    WORD  ax            fpfnNeuerHandler                บ
  บ                    WORD  bp                                            บ
  บ                    WORD  si                                            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Routine wird von fpfnNeuerHandler ange-       บ
  บ                    sprungen, wenn der kritische Fehler whrend         บ
  บ                    der Dialogbox DlgLaden() auftritt.                  บ
  บ                    Wegen des Kontexts kann es sich hierbei nur         บ
  บ                    um einen Lesefehler bei einem Laufwerk handeln.     บ
  บ                    Aus diesem Grunde werden nicht alle der Funktion    บ
  บ                    bergebenen Argumente ausgewertet.                  บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  0 = ignorieren, bzw. Abbrechen                บ
  บ                          1 = miแglckte Operation noch einmal          บ
  บ                              versuchen                                 บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boBeepen_g, pstrRetry_g, pstrEsc_g   (W)            บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
STATIC
WORD LadenFehler(WORD wFehler, WORD ax, WORD bp, WORD si)
{
    REGISTER    i;
    PWKB        pWkbDialog;
    EVENT       Event;
    PEVENT      pEvent;
    PPSTR       ppstrTmp;

    if ((pWkbDialog=WinEinrichten(SPA,ZEI,BRE,HOE)) /* Fenster einrichten   */
        == NULL)
    {
        i_Beep();                                   /* Warnton ausgeben     */
        return (0);                                 /* evtl. Abbruch        */
    }

    i_DlgInit(SPA, ZEI, BRE, HOE,                   /* Fenster initialis.   */
              "Systemfehler",
              pWkbDialog,
              SF_RETRYCANCEL,
              DLG_KRITISCH);

    for (ppstrTmp=icon_ausruf, i=2;                 /* Icon ausgeben        */
         *ppstrTmp != NULL;
         i++)
        WinSs(3,i,*ppstrTmp++);

    WinSetCursorPos(14,3);                          /* Text ausgeben        */
    WinPrintf("Lesen von Laufwerk %c: ist nicht m”glich.", 'A'+ ax&0x00FF);
    WinSs(14,4,"Bitte whlen Sie die gewnschte Aktion.");

    pEvent = &Event;                                /* Var. initialisieren  */

    ax &= 0xFF00;                                   /* AL-Register l”schen  */
    for(;;)                                         /* Eingaberoutine       */
    {
        UtlEvent(pEvent);
        switch(pEvent->wArt)
        {
           case EVENT_TASTE:
              switch(pEvent->wTaste)
              {
               case T_ESC:
                    WinEntfernen(pWkbDialog);
                    return(ax+0);

               case T_RETURN:
                    WinEntfernen(pWkbDialog);
                    return(ax+1);

               default:
                    if (boBeepen_g)
                        i_Beep();
              } /* end of switch(pEvent->wTaste) */
              break;

           case EVENT_L_PRESS:
              if (pEvent->wZeile == 16)
              {
                 if (pEvent->wSpalte > SPA+2 &&
                     pEvent->wSpalte < SPA+3+strlen(pstrRetry_g))
                 {
                    WinEntfernen(pWkbDialog);
                    return(ax+1);
                 }
                 else if (pEvent->wSpalte > SPA+20 &&
                       pEvent->wSpalte < SPA+17+strlen(pstrEsc_g))
                 {
                    WinEntfernen(pWkbDialog);
                    return(ax+0);
                }
             }
              else if (boBeepen_g)
                 i_Beep();
             break;
        } /* end of switch(pEvent->wArt) */
    } /* end of for */
}

