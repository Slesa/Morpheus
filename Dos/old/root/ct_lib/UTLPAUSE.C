/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlPause                       Datum: 16.08.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wModus         UTL_SEKUNDEN, UTL_TICKS       บ
  บ                    WORD   wDauer         Dauer der Pause               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion unterbricht fr die bergebene       บ
  บ                    Zeit die Arbeit des Rechners. Die Zeit wird         บ
  บ                    durch Aufruf der Funktion "Read Clock Count"        บ
  บ                    des INT 0x1A gemessen. Dadurch ist diese Funk-      บ
  บ                    tion hardware-unabhngig und die Pausendauer        บ
  บ                    wird sehr genau erreicht.                           บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
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
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlPause(WORD wModus, WORD wDauer)
{
    LONG    lPause,                          /* Dauer der Pause in Ticks    */
            lStart,                          /* Ticks beim Beginn der Pause */
            lStop,                           /* Ticks beim Ende der Pause   */
            lJetzt;                          /* Aktuelle Ticks-Anzahl       */

    if (wDauer != 0)
    {
        lPause = wDauer;                            /* Pausendauer laden    */
        if (wModus == UTL_SEKUNDEN)
            lPause *= TICKS_PRO_SEK;                /* Sekunden umrechnen   */

        UtlGetUhrTicks(&lStart);                    /* Startticks holen     */

        lStop = lStart + lPause;                    /* Stopzeit bestimmen   */

        if (lPause > TICKS_PRO_TAG)                  /* bis morgen warten ?  */
        {
            lStop -= TICKS_PRO_TAG;
            while (UtlGetUhrTicks(&lJetzt)==0)      /* erstmal bis Mitter-  */
                ;                                   /* nacht warten         */
        }

        do                                          /* warten, bis die er-  */
        {                                           /* rechnete Zeit um ist */
            UtlGetUhrTicks(&lJetzt);

        } while (lJetzt < lStop);

    }
    return;
}
