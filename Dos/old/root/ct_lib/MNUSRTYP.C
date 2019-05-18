/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuSetRahmenTyp                Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wMenuNr    Nummer des Mens                    บ
  บ                    WORD wTyp       RT_EEEE/RT_DDDD                     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt fr alle Menfenster eines      บ
  บ                    Mens fest, welchen Typ der Rahmen der Men-        บ
  บ                    fenster hat.                                        บ
  บ                    Alle eventuell bereits im Puffer stehenden          บ
  บ                    Menfenster werden aktualisiert und die             บ
  บ                    Statusinformation zu diesem Men wird gendert.     บ
  บ                    Diese Funktion kann zu jeder Zeit aufgerufen wer-   บ
  บ                    den. Es ist jedoch empfehlenswert, den Rahmentyp    บ
  บ                    vor dem Aufruf der Funktion MnuEinrichten() fest-   บ
  บ                    zulegen, um ein wiederholtes Beschreiben der        บ
  บ                    Buffer zu vermeiden.                                บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD Fehlerinformation OK/ERROR                     บ
  บ                         - MNU_FALSCHE_OPT   die gewhlte Option        บ
  บ                           fr wTyp war ungltig                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g   (W)                                     บ
  บ                    aMenus_g[]  (R)                                     บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */
IMPORT MENU aMenus_g[];          /* Array der Mens                          */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MnuSetRahmenTyp(WORD wMenuNr, WORD wTyp)
{
    PMKB pMkbLokal;
    BOOL boAendern = NEIN;

    if (wMenuNr >= MAXMENUES)                       /* maximale Anzahl der  */
    {                                               /* Mens berprfen     */
        wFehler_g = MNU_LIMIT;                      /* Fehlernummer laden   */
        return(ERROR);                              /* und zurck           */
    }


    switch(wTyp)                                    /* Argument wTyp ber-  */
    {                                               /* prfen               */
        case RT_EEEE:                               /* und eintragen        */
            if (aMenus_g[wMenuNr].wStatus.wRahmentyp != 0)
            {
                aMenus_g[wMenuNr].wStatus.wRahmentyp = 0;
                boAendern = JA;
            }
            break;

        case RT_DDDD:
            if (aMenus_g[wMenuNr].wStatus.wRahmentyp != 1)
            {
                aMenus_g[wMenuNr].wStatus.wRahmentyp = 1;
                boAendern = JA;
            }
            break;

        default:
            wFehler_g = MNU_FALSCHE_OPT;
            return (ERROR);
    } /* end of switch (wTyp) */


    pMkbLokal = aMenus_g[wMenuNr].pMkbStart;        /* ersten PMKB holen    */

    if (pMkbLokal != NULL && boAendern == JA )      /* Men-Puffer ndern,  */
    {                                               /* wenn Fenster einge-  */
        do                                          /* richtet              */
        {
            if (pMkbLokal->wMkbsign != MKBSIGNATUR) /* zeigt pMkb auf MKB ? */
                i_Fehler(I_FEHLER_SIGN, "MnuSetRahmenTyp()",
                         __FILE__, __LINE__);

            i_MnuToBuffer(pMkbLokal,                /* Menfenster im       */
                          wMenuNr,                  /* Puffer ndern lassen */
                          MNU_AENDERN);

            pMkbLokal = pMkbLokal->pNaechster;      /* nchsten holen       */

        } while (pMkbLokal != aMenus_g[wMenuNr].pMkbStart);
    } /* end of if */

    return (OK);
}
