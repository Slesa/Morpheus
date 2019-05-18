/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinZeileEinfuegen              Datum: 15.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wZeile    einzufgende Zeile des Windows      บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion fgt an der gewnschten Position eine  บ
  บ                    Zeile ein, indem sie den Fensterinhalt unterhalb    บ
  บ                    der Zeile nach unten scrollt.                       บ
  บ                    Die neue Zeile wird mit Leerzeichen aufgefllt.     บ
  บ                    Das Attribut der Leerzeichen wird der Variablen     บ
  บ                    ฏwAttribut_gฎ entnommen, die eine Kopie der Va-     บ
  บ                    riablen ฏwInnenAttrฎ aus der WKB-Struktur des       บ
  บ                    aktuellen Windows enthlt.                          บ
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
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          HEADER - DATEIEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <dos.h>
#include <ctools.h>

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
VOID WinZeileEinfuegen (WORD wZeile)
{
    WORD wStatus;
    union REGS regs;

    if (wMausda_g)                                  /* wenn Maus im System, */
        wStatus = MsmCursorOff();                   /* Maus ausschalten.    */

    if ( WinDAexistiert() &&                        /* Window groแ genug,   */
         WinZeileInDA(wZeile) )                     /* und Zeile im Fenster?*/
    {
        regs.h.ah = SCROLL_DOWN;                    /* Funktionsnummer      */
        if ( wZeile == wH_g -1)                     /* letzte Zeile einfg.?*/
            regs.h.al = 0;                          /* Zeile l”schen        */
        else
            regs.h.al = 1;                          /* Eine Zeile scrollen  */
        regs.h.bh = (BYTE) wAttribut_g;             /* A. der Leerzeichen   */
        regs.h.ch = (BYTE) wZ_g + wZeile;
        regs.h.cl = (BYTE) wS_g;
        regs.h.dh = (BYTE) wZ_g + wH_g -1;
        regs.h.dl = (BYTE) wS_g + wB_g -1;
        int86(0x10, &regs, &regs);                  /* Interrupt ausl”sen   */
    }

    if (wMausda_g && wStatus == MSM_WAR_AN)         /* wenn Maus sichtbar   */
        MsmCursorOn();                              /* war, Maus anzeigen   */
}

