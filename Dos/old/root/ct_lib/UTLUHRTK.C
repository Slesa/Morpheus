/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlGetUhrTicks                 Datum: 16.08.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PLONG  plTicks    Zeiger, ber den die Anzahl       บ
  บ                                      der Ticks zurckgegeben werden    บ
  บ                                      soll.                             บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion liest mit einem Aufruf des INT       บ
  บ                    0x1A die Anzahl der Ticks der internen System-      บ
  บ                    uhr seit Mitternacht.                               บ
  บ                    Wenn beim Aufruf Mitternacht berschritten wird,    บ
  บ                    wird das Mitternachtssignal gesetzt.                บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   Mitternachtssignal  <> 0 wenn neuer Tag      บ
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
#include <INTERRPT.H>
#include <dos.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD UtlGetUhrTicks(PLONG plTicks)
{
    union REGS regs;

    regs.h.ah = 0;                                /* "ReadClockCount"     */
    Interrupt(0x1A, &regs);                 /* Interrupt ausl”sen   */

    *plTicks   = IntGetCX( regs );                      /* High-Word laden      */
    *plTicks <<= 16;                                /* und verschieben      */
    *plTicks  += IntGetDX( regs );                      /* Low-Word addieren    */

    return(regs.h.al);                           /* Mitternachtssignal   */
                                                    /* zurckgeben          */
}
