/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlDosShell                    Datum: 29.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wRand           0, wenn Bildschirm normal      บ
  บ                                         gel”scht werden soll           บ
  บ                                         sonst Farbe, mit der           บ
  บ                                         UtlClrRand aufgerufen wird     บ
  บ                                                                        บ
  บ                    PSTR pstrPrgName     Name des Programms, wenn er    บ
  บ                                         in der Dialogbox auftauchen    บ
  บ                                         soll, sonst NULL               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion startet aus einem laufenden Programm บ
  บ                    heraus eine weitere Kopie des DOS-Befehlsinterpre-  บ
  บ                    ters COMMAND.COM. Der komplette Bildschirm wird     บ
  บ                    von der Funktion gesichert und einschlieแlich der   บ
  บ                    Position und Gr”แe des Cursors wieder hergestellt,  บ
  บ                    wenn die Shell verlassen wird.                      บ
  บ                                                                        บ
  บ                    Vor Aufruf der Shell wird eine Dialogbox aufge-     บ
  บ                    baut, in der der Anwender den Hinweis bekommt,      บ
  บ                    wie er die Shell wieder verlassen kann. Mit den     บ
  บ                    Schaltflchen "OK" und "Abbruch" startet der An-    บ
  บ                    wender die Shell oder kehrt in das Programm zurck. บ
  บ                    Wenn die Shell nicht aktiviert werden konnte, wird  บ
  บ                    der Anwender darber in einer Message-Box           บ
  บ                    informiert.                                         บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  OK/ERROR liefert die Information, ob Shell    บ
  บ                                   gestartet werden konnte oder nicht   บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - wMausda_g (R)                                     บ
  บ                    - fpwCopyBuffer_g (W/R)                             บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>
#include <process.h>
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                    GLOBALE VARIABLEN, REFERENZEN                       บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD   wMausda_g;                            /* Maus da ?            */
IMPORT FPWORD fpwCopyBuffer_g;                      /* allg. 4K-Buffer      */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
STATIC WORD wZeile, wSpalte, wStop, wStart;
MGLOBAL PSTR apstrShellWarnung[] =
    {"Der DOS-Befehlsinterpreter konnte",
     "nicht geladen werden.",
     NULL};

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD UtlDosShell(WORD wRand, PSTR pstrPrgName)
{
    WORD wReturn;

    if (fpwCopyBuffer_g == 0L)
        if ((fpwCopyBuffer_g = UtlFmalloc(2000 * sizeof(WORD))) == 0)
            return (ERROR);


    VioGetCursor(&wSpalte, &wZeile,                 /* Cursortyp und Posi-  */
                 &wStart, &wStop);                  /* tion sichern         */

    wReturn = DlgShell(pstrPrgName);

    if (wReturn == DLG_ESC)
        return(OK);

    if (wMausda_g == JA)                            /* evtl. Maustreiber-   */
    {                                               /* status sichern       */
        MsmCursorOff();                             /* und Mauscursor aus-  */
        MsmTreiberSichern();                        /* schalten             */
    }

    VioSw2b(0,0,80,25,fpwCopyBuffer_g);             /* Bildschirm sichern   */
    if (wRand == 0)
        VioSpza(32,7);                              /* Bildschirm l”schen   */
    else
        UtlClearRandom(wRand);

    VioSetCursorPos(0,0);                           /* Cursor positionieren */

    if (VioGetMode() == MONOCHROM)                  /* Cursortyp je nach    */
        VioSetCursorTyp(11,12);                     /* Videomodus festlegen */
    else
        VioSetCursorTyp(6,7);


    if (system("command") == -1)                    /* COMMAND.COM starten  */
        wReturn = ERROR;                            /* und Rckgabewert     */
    else                                            /* festlegen            */
        wReturn = OK;

    VioSb2w(0,0,80,25,fpwCopyBuffer_g);             /* alten Zustand wieder */
    if (wMausda_g == JA)                            /* herstellen           */
    {
        MsmTreiberRestore();
        MsmCursorOn();
    }

    if (wReturn == ERROR)                           /* wenn Shell nicht ge- */
        DlgInfo(apstrShellWarnung, DLG_KRITISCH);   /* startet werden konnte*/

    VioSetCursorTyp(wStart, wStop);
    VioSetCursorPos(wSpalte, wZeile);

    return (wReturn);
}
