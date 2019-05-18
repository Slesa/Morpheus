/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuOption                      Datum: 26.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wOption   Nummer der Option                   บ
  บ                    WORD  wModus    EIN      Option aktivieren          บ
  บ                                    AUS      Option deaktivieren        บ
  บ                                    DREHEN   Status toggeln             บ
  บ                                    STATUS   Status ermitteln           บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion erm”glicht es Ihnen, whrend des     บ
  บ                    Programmablaufes einzelne Menoptionen zu de-       บ
  บ                    aktivieren und wieder zu aktivieren.                บ
  บ                    Diese Statusvernderung einer Option beeinfluแt     บ
  บ                    das Attribut, mit dem der Optionstext im            บ
  บ                    Menfenster ausgegeben wird. Weiterhin kann         บ
  บ                    eine nicht aktive Option vom Anwender nicht         บ
  บ                    ausgewhlt werden.                                  บ
  บ                                                                        บ
  บ  Rckgabewert:     Status der Option nach dem Aufruf der Funktion      บ
  บ                    0 == Option nicht aktiv                             บ
  บ                    1 == Option aktiv                                   บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g (W)                                       บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ  (c) copyright 1988,1989 Markt & Technik Verlag AG, Haar bei Mnchen   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>                                 /* Toolbox-Deklaration. */
#include <stdio.h>                                  /* fr NULL             */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MnuOption(WORD wOption, WORD wModus)
{
    PMKB  pMkb;                                     /* MKB gefundenes Men  */
    WORD  wMenuNr;                                  /* Nummer gefund. Men  */

    pMkb = i_MnuFindeMkb(&wOption, &wMenuNr);       /* MKB fr Option find. */

    if (pMkb == NULL)                               /* MKB nicht gefunden   */
    {
        wFehler_g = MNU_FALSCHE_OPT;                /* Funktion beenden     */
        return (ERROR);
    }

    else if( pMkb->wMkbsign != MKBSIGNATUR)         /* zeigt pMkb auf MKB ? */
        i_Fehler(I_FEHLER_SIGN, "MnuOption()",
                 __FILE__, __LINE__);

    else
    {
        switch(wModus)                              /* Modus auswerten      */
        {
            case EIN:                               /* einschalten          */
                pMkb->pHotkeys[wOption].wAktiv = 1;
                i_MnuToBuffer(pMkb,wMenuNr, MNU_AENDERN);
                break;

            case AUS:                               /* ausschalten          */
                pMkb->pHotkeys[wOption].wAktiv = 0;
                i_MnuToBuffer(pMkb,wMenuNr, MNU_AENDERN);
                break;

            case DREHEN:                            /* toggeln              */
                pMkb->pHotkeys[wOption].wAktiv ^= 1;
                i_MnuToBuffer(pMkb,wMenuNr, MNU_AENDERN);
                break;

            case STATUS:                            /* nur return-Anweisung */
                break;                              /* ausfhren            */

            default:
                wFehler_g = MNU_FALSCHE_OPT;        /* ungltiger Wert fr  */
                return (ERROR);                     /* wModus               */
        }
        return(pMkb->pHotkeys[wOption].wAktiv);     /* Status zurckgeben   */
    }
}



