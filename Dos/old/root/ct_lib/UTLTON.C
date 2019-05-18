/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlTon                          Datum: 16.08.88   ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wFrequenz    Frequenz des Tons oder          บ
  บ                                        0 um den Lautsprecher ab-       บ
  บ                                        zuschalten.                     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion aktiviert den Lautsprecher durch     บ
  บ                    Laden der entsprechenden Werte an den programmier-  บ
  บ                    baren Interrupt-Timer-Chip (8253).                  บ
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
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define PPI_PORT             97           /* Port des PPI-Chips 8255        */
#define PIT_ZAEHLER          66           /* Register fr Zhler im 8253    */
#define PIT_BEFEHL           67           /* Befehlsregister des 8253       */
#define ZAEHLER_KOMMT       182           /* 8253 bereitmachen fr Aufnahme */
                                          /* des Zhlers.                   */
#define CLOCKSPEED     1193180L           /* Frequenz der Systemuhr         */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlTon(WORD wFrequenz)
{
    WORD  wZaehler;

    if (wFrequenz)                                  /* Ton an               */
    {
        UtlOutpb(PPI_PORT, UtlInpb(PPI_PORT) | 3);  /* Bits 0 und 1 setzen  */
        UtlOutpb(PIT_BEFEHL, ZAEHLER_KOMMT);        /* 8253 mitteilen das   */
                                                    /* Zhler geladen wird  */

        wZaehler = (WORD) (CLOCKSPEED / wFrequenz); /* Zhler berechnen     */

        UtlOutpb(PIT_ZAEHLER, UtlLowByte(wZaehler)); /* und  an den 8253    */
        UtlOutpb(PIT_ZAEHLER, UtlHighByte(wZaehler));

    }
    else                                            /* Ton aus              */
        UtlOutpb(PPI_PORT, UtlInpb(PPI_PORT) & ~3); /* Bits 0 und 1 l”schen */
}
