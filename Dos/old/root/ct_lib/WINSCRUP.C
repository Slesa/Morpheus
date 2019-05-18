/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinScrollUp                    Datum: 15.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wAnzahl   Anzahl der zu scrollenden Zeilen    บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion scrollt den Inhalt des aktiven Win-    บ
  บ                    dows um die gewnschte Anzahl von Zeilen nach       บ
  บ                    oben. Die nachrckenden Zeilen werden mit Leer-     บ
  บ                    zeichen aufgefllt. Das Attribut der Leerzeichen    บ
  บ                    wird der Variablen ฏwAttribut_gฎ entnommen, die     บ
  บ                    eine Kopie der Variablen ฏwInnenAttrฎ aus der       บ
  บ                    Struktur WKB des aktuellen Windows enthlt.         บ
  บ                    Wird der Funktion eine ฏ0ฎ bergeben, wird das      บ
  บ                    komplette Window nach oben gescrollt.               บ
  บ                    Die Position des Cursors wird durch die Funktion    บ
  บ                    nicht verndert.                                    บ
  บ                                                                        บ
  บ  Rckgabewert:     Die Funktion hat keinen Rckgabewert.               บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  บ                      - wAttribut_g (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          HEADER - DATEIEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <dos.h>
#include <ctools.h>
#include <INTERRPT.H>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                  G l o b a l e   V a r i a b l e n                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT  WORD    wMausda_g;                          /* 0: keine Maus da     */
                                                    /* 1: Maus vorhanden    */

IMPORT  WORD    wS_g;                               /* Die Koordinaten be-  */
IMPORT  WORD    wZ_g;                               /* schreiben die Data-  */
IMPORT  WORD    wB_g;                               /* Area des aktuellen   */
IMPORT  WORD    wH_g;                               /* Windows.             */

IMPORT  WORD    wAttribut_g;                        /* Attribut des Fenster-*/
                                                    /* innneren.            */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID WinScrollUp (WORD wAnzahl)
{
    WORD wStatus;
    union REGS regs;

    if (wMausda_g)                                  /* wenn Maus im System, */
        wStatus = MsmCursorOff();                   /* Maus ausschalten.    */

    if ( WinDAexistiert() )                         /* Window groแ genug ?  */
    {
        regs.h.ah = SCROLL_UP;                      /* Funktionsnummer      */
        if ( wH_g > 1)                              /* Data-Area > 1 Zeile  */
            regs.h.al = (BYTE) wAnzahl;             /* Window scrollen      */
        else
            regs.h.al = 0;                          /* ganzes Wind. l”schen */
        regs.h.bh = (BYTE) wAttribut_g;             /* A. der Leerzeichen   */
        regs.h.ch = (BYTE) wZ_g;
        regs.h.cl = (BYTE) wS_g;
        regs.h.dh = (BYTE) wZ_g + wH_g -1;
        regs.h.dl = (BYTE) wS_g + wB_g -1;
        Interrupt(0x10, &regs);                  /* Interrupt ausl”sen   */
    }

    if (wMausda_g && wStatus == MSM_WAR_AN)         /* wenn Maus sichtbar   */
        MsmCursorOn();                              /* war, Maus anzeigen   */
}

