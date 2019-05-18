/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgGetOptionen                 Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR pstrPrgName   Dateiname des aktuellen          บ
  บ                                       jeweiligen Programms             บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion liest die vom Benutzer einstell-     บ
  บ                    baren Optionen aus einer Struktur, die beim         บ
  บ                    ersten Aufruf des Programms von dieser Funktion     บ
  บ                    an das Ende der Programmdatei angehngt wird.       บ
  บ                                                                        บ
  บ                    Beim zweiten Aufruf des Programms werden dieser     บ
  บ                    Struktur die beim letzten Verlassen des Programms   บ
  บ                    gespeicherten Werte entnommen fr                   บ
  บ                    - die Mausgeschwindigkeit                           บ
  บ                    - die Farbpalette                                   บ
  บ                    - die Dauer und Frequenz des Warntons               บ
  บ                    - die Information, ob ein Warnton erklingen soll    บ
  บ                      oder nicht                                        บ
  บ                    Mit diesen Werten werden die globalen Variablen     บ
  บ                    der Toolbox, die diese Werte enthalten,             บ
  บ                    initialisiert.                                      บ
  บ                                                                        บ
  บ                    Sie sollten diese Funktion als erste Funktion       บ
  บ                    in Ihrem Programm aufrufen.                         บ
  บ                                                                        บ
  บ                    Da die M”glichkeit besteht, daแ der Anwender        บ
  บ                    den Namen der Programmdatei ndert, sollten Sie     บ
  บ                    dieser Funktion als Argument argv[0] bergeben,     บ
  บ                    das ab DOS 3.xx den Dateinamen des gestarteten      บ
  บ                    Programms enthlt. Sie sollten in diesem Fall       บ
  บ                    vor dem Aufruf der Funktion berprfen, mit         บ
  บ                    welcher DOS-Version das System gefahren wird.       บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   Fehlerinformation OK/ERROR                   บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - wVioMode_g         (R)                            บ
  บ                    - wMausSpeed_g       (R)                            บ
  บ                    - wCSInd_g           (R)                            บ
  บ                    - wBeepFreq_g        (R)                            บ
  บ                    - wBeepDauer_g       (R)                            บ
  บ                    - boBeepen_g         (R)                            บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define OPTSIGNATUR "M&T QuickC-Toolbox"           /* Signatur fr Struktur */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wVioMode_g;
IMPORT WORD wCSInd_g;
IMPORT WORD wMausSpeed_g;
IMPORT WORD wBeepFreq_g;
IMPORT WORD wBeepDauer_g;
IMPORT BOOL boBeepen_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
struct options
{
    CHAR acSignatur[sizeof(OPTSIGNATUR)];
    WORD wMausTempo;
    WORD wPalette;
    WORD wFreq;
    WORD wDauer;
    WORD boBeepen;
}Optionen;



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgGetOptionen(PSTR pstrPrgName)
{
    BOOL     boDasErsteMal;
    SWORD    swFileHandle;


    if ( (swFileHandle=open(pstrPrgName,            /* Datei ”ffnen         */
                           O_RDWR|O_BINARY)) == -1)
        return (ERROR);

    lseek(swFileHandle,                             /* Dateizeiger an       */
          0L - sizeof(Optionen),                    /* Offset der Struktur  */
          SEEK_END);                                /* positionieren        */

    if (read(swFileHandle,                          /* Struktur lesen       */
             (char*) &Optionen,
             sizeof(Optionen)) != sizeof(Optionen))
        return (ERROR);

    if (strcmp(OPTSIGNATUR,                         /* wenn Struktur nicht  */
               Optionen.acSignatur) != 0)           /* vorhanden, wird      */
    {                                               /* hier die Struktur    */
        memset(&Optionen, 0, sizeof(Optionen));     /* an das Ende der      */
        strcpy(Optionen.acSignatur, OPTSIGNATUR);   /* Datei angehngt      */
        lseek(swFileHandle, 0L, SEEK_END);
        boDasErsteMal = JA;
        if (write(swFileHandle,
                  (char*) &Optionen,
                  sizeof(Optionen)) != sizeof(Optionen))
        {
            close(swFileHandle);                        /* Datei schlieแen      */
            return (ERROR);
        }
        close(swFileHandle);
    }
    else
        boDasErsteMal = NEIN;

    if (boDasErsteMal == NEIN)
    {
        wMausSpeed_g = Optionen.wMausTempo;         /* gloable Variablen    */
        boBeepen_g   = Optionen.boBeepen;           /* mit Werten aus der   */
        wBeepFreq_g  = Optionen.wFreq;              /* Struktur laden       */
        wBeepDauer_g = Optionen.wDauer;
        wCSInd_g     = Optionen.wPalette;
    }
    if (wVioMode_g == MONOCHROM &&                  /* Palette berprfen   */
        wCSInd_g   != MNU_PAL_MONO)
            wCSInd_g = MNU_PAL_MONO;


    return (OK);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgPutOptionen                 Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR pstrPrgName   Dateiname des aktuellen          บ
  บ                                       jeweiligen Programms             บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion liest die vom Anwender mit ver-      บ
  บ                    schiedenen Dialogfeldern einstellbaren Optionen     บ
  บ                    aus globalen Variablen in eine Struktur, die        บ
  บ                    sich innerhalb der .EXE-Datei befindet, und         บ
  บ                    beschreibt diesen Teil der Datei mit den beim       บ
  บ                    Aufruf dieser Funktion aktuellen Werten.            บ
  บ                                                                        บ
  บ                    Im einzelnen handelt es sich um folgende Daten:     บ
  บ                                                                        บ
  บ                    - die Mausgeschwindigkeit                           บ
  บ                    - die Farbpalette                                   บ
  บ                    - die Dauer und Frequenz des Warntons               บ
  บ                    - die Information, ob ein Warnton erklingen soll    บ
  บ                      oder nicht                                        บ
  บ                                                                        บ
  บ                    Beim nchsten Programmstart k”nnen durch einen      บ
  บ                    Aufruf der Funktion DlgGetOptionen() die vom        บ
  บ                    Anwender festgelegten Werte wieder initialisiert    บ
  บ                    werden.                                             บ
  บ                                                                        บ
  บ                    Da die M”glichkeit besteht, daแ der Anwender        บ
  บ                    den Namen der Programmdatei ndert, sollten Sie     บ
  บ                    dieser Funktion als Argument argv[0] bergeben,     บ
  บ                    das ab DOS 3.xx den Dateinamen des gestarteten      บ
  บ                    Programms enthlt. Sie sollten in diesem Fall       บ
  บ                    vor dem Aufruf der Funktion berprfen, mit         บ
  บ                    welcher DOS-Version das System gefahren wird.       บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation OK/ERROR                    บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - wCSInd_g           (R)                            บ
  บ                    - wMausSpeed_g       (R)                            บ
  บ                    - wBeepFreq_g        (R)                            บ
  บ                    - wBeepDauer_g       (R)                            บ
  บ                    - boBeepen_g         (R)                            บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgPutOptionen(PSTR pstrPrgName)
{
    SWORD    swFileHandle;
    WORD     wReturn;

    if ((swFileHandle = open(pstrPrgName,           /* Datei ”ffnen         */
                        O_RDWR | O_BINARY)) == -1)
        return(ERROR);

    Optionen.wPalette   = wCSInd_g;                 /* Daten aus den glo-   */
    Optionen.wMausTempo = wMausSpeed_g;             /* balen Variablen in   */
    Optionen.boBeepen   = boBeepen_g;               /* Struktur einlesen    */
    Optionen.wFreq      = wBeepFreq_g;
    Optionen.wDauer     = wBeepDauer_g;

    lseek( swFileHandle,                            /* Dateizeiger auf      */
           0L - sizeof(Optionen),                   /* Struktur position.   */
           SEEK_END);

    if( write(swFileHandle,                         /* neue Daten ber alte */
              (char*) &Optionen,                    /* Struktur schreiben   */
              sizeof(Optionen)) != sizeof(Optionen))
         wReturn = ERROR;
    else
        wReturn = OK;

    close(swFileHandle);                            /* Datei schlieแen      */

    return (wReturn);                               /* und zurck           */
}

