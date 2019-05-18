/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlClearRandom                 Datum: 19.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wAttr  Attribut, mit dem der Bildschirm       บ
  บ                                 gel”scht werden soll                   บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion l”scht den Bildschirm indem sie ihn    บ
  บ                    mit einzelnen Leerzeichen beschreibt, deren Posi-   บ
  บ                    tion mit einem Pseudozufallsgenerator bestimmt      บ
  บ                    wird. Mit dem Parameter ฏwAttrฎ k”nnen Sie bestim-  บ
  บ                    men, ob die Bildschirmattribute bernommen oder     บ
  บ                    verndert werden sollen. Eine ฏ0ฎ lแt die Attri-   บ
  บ                    bute unverndert, andere Werte werden als das neue  บ
  บ                    Attribut interpretiert.                             บ
  บ                                                                        บ
  บ                    Um zu gewhrleisten, daแ jede Position des Bild-    บ
  บ                    schirms mit einem Blank berschrieben wird, be-     บ
  บ                    nutzt die Funktion einen Generator, der exakt 2047  บ
  บ                    verschiedene Zahlen erzeugt (1..2047). Es handelt   บ
  บ                    sich dabei um die Softwarerealisation eines elf-    บ
  บ                    stufigen rckgekoppelten Schieberegisters. Die      บ
  บ                    volle Periodenlnge von 2047 wird durch die Wahl    บ
  บ                    der Rckkopplungslogik erreicht. Der Anfangszu-     บ
  บ                    stand ist in den Grenzen 1..2047 frei whlbar.      บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
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
#include <conio.h>
#include <stdlib.h>

#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlClearRandom(WORD wAttr)
{
    WORD wZufall = 0x0123,                          /* Startwert des Gener. */
         wZurueck;                                  /* Maske zur Rckkoppl. */
    REGISTER i,j;

    for (i=0; i<16; i++)                            /* insg. 2048 erzeugen  */
    {
        for (j=0; j<128; j++)
        {
            wZurueck = wZufall & 0x0005;            /* Die Ausgnge 11 und  */
                                                    /* 9 werden rckgekopp. */

            wZufall >>= 1;                          /* nach rechts schieben */

            if ((wZurueck==1) || (wZurueck==4))     /* XOR-Verknpfung der  */
                wZufall |= 0x0400;                  /* Ausgnge 9 und 11    */
                                                    /* auf den Eingang geben*/
                                                    /* (Ausgang 1 = Bit 10) */

            if (wZufall<=2000)                      /* Position auf Bilds.? */
                if (wAttr == 0)                     /* Leerzeichen schreiben*/
                    VioSz(wZufall%80,wZufall/80,32);
                else
                    VioSza(wZufall%80,wZufall/80,32,
                           wAttr);
        }

        if (wAttr == 0)                             /* Position ฏ0ฎ kann    */
            VioSz(0,0, ' ');                        /* nicht erzeugt werden */
        else
            VioSza(0,0, ' ', wAttr);

        UtlPause(UTL_TICKS,1);                      /* etwas warten         */
    }
}
