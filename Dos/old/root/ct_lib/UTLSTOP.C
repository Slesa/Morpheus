/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlStopUhr                     Datum: 18.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD      wModus  UTL_START                         บ
  บ                                      UTL_STOP                          บ
  บ                                                                        บ
  บ  Beschreibung:     Diese "Stop-Uhr" verwendet den Timer-Baustein,      บ
  บ                    um Ihnen Zeitmessungen fr verschiedene Prozesse    บ
  บ                    zu erm”glichen. Der Parameter ฏUTL_STARTฎ veran-    บ
  บ                    laแt die Funktion ihre interne Uhrzeit auf ฏ0ฎ zu   บ
  บ                    setzten. Nach einem Aufruf mit ฏUTL_STOPฎ luft     บ
  บ                    die Zeit intern weiter, Sie k”nnen also auch Zwi-   บ
  บ                    schenzeiten nehmen.                                 บ
  บ                    Um die Timer-Ticks in Sekunden umzuwandeln,         บ
  บ                    k”nnen Sie das Makro "UtlTicksToSeks()" ver-        บ
  บ                    wenden.                                             บ
  บ                    Alle zeitkritischen C- und Assembler-Funktionen     บ
  บ                    der Toolbox wurden mit dieser Funktion auf          บ
  บ                    Geschwindigkeitkeit hin optimiert.                  บ
  บ                                                                        บ
  บ  Rckgabewert:     LONG      gemessene Zeit in Ticks der System-       บ
  บ                              uhr                                       บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
LONG UtlStopUhr (WORD wModus)
{
    STATIC LONG lStart = 0L;
    LONG lErgebnis, lJetzt;

    UtlGetUhrTicks(&lJetzt);

    switch (wModus)
    {
        case UTL_START:        lStart = lJetzt;
                               lErgebnis = 0L;
                               break;

        case UTL_STOP:         if (lJetzt < lStart)
                                   lJetzt += TICKS_PRO_TAG;
                               lErgebnis = lJetzt - lStart;
                               break;

    }
    return(lErgebnis);
}


