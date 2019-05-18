/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuMarker                      Datum: 26.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wOption   Nummer der Option                   บ
  บ                    WORD  wModus    EIN      Marker einschalten         บ
  บ                                    AUS      Marker ausschalten         บ
  บ                                    DREHEN   Marker toggeln             บ
  บ                                    STATUS   Marker-Status ermitteln    บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion k”nnen Sie fr die bergebene   บ
  บ                    Option festlegen, ob vor dem Text der Menoption    บ
  บ                    ein kleines Hkchen (๛=ASCII 251) angezeigt         บ
  บ                    werden soll oder nicht. Dieses Verfahren ist        บ
  บ                    fr den Anwender sinnvoll, da er mit einem          บ
  บ                    Blick auf das Menfenster erkennen kann, ob         บ
  บ                    eine Option zur Zeit ein- oder ausgeschaltet ist.   บ
  บ                    Sie kennen dieses Prinzip sicherlich vom Debug-     บ
  บ                    Men des QuickC-Compilers. Dort wird der Status     บ
  บ                    der Optionen ฏBildschirmwechsel einฎ und ฏVer-      บ
  บ                    folgen einฎ durch diese Markierungen angezeigt.     บ
  บ                                                                        บ
  บ                    Wegen des Komforts der Toolbox ist es natrlich     บ
  บ                    nicht notwendig, daแ Sie in den Strings der         บ
  บ                    Menoptionen Platz fr dieses Hkchen lassen.       บ
  บ                                                                        บ
  บ                    Die Wirkung der Funktion steuern Sie ber das       บ
  บ                    Argument wModus.                                    บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     Status der Markierung nach dem Aufruf der Funktion  บ
  บ                    0 == Markierung nicht gesetzt                       บ
  บ                    1 == Markierung gesetzt                             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g   (W)                                     บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>                                 /* Toolbox-Headers      */
#include <stdio.h>                                  /* fr NULL             */
#include <string.h>                                 /* fr strcmp()         */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */
IMPORT MENU aMenus_g[];         /* Array mit allen Mens                    */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MnuMarker(WORD wOption, WORD wModus)
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
        i_Fehler(I_FEHLER_SIGN, "MnuMarker()",
                 __FILE__, __LINE__);

    else
    {
        switch(wModus)                              /* Modus auswerten      */
        {
            case EIN:                               /* einschalten          */
                pMkb->pHotkeys[wOption].wMarker = 1;
                i_MnuToBuffer(pMkb,wMenuNr, MNU_AENDERN);
                break;

            case AUS:                               /* ausschalten          */
                pMkb->pHotkeys[wOption].wMarker = 0;
                i_MnuToBuffer(pMkb,wMenuNr, MNU_AENDERN);
                break;

            case DREHEN:                            /* toggeln              */
                pMkb->pHotkeys[wOption].wMarker ^= 1;
                i_MnuToBuffer(pMkb,wMenuNr, MNU_AENDERN);
                break;

            case STATUS:                            /* nur return-Anweisung */
                break;                              /* ausfhren            */

            default:
                wFehler_g = MNU_FALSCHE_OPT;        /* ungltiger Wert fr  */
                return (ERROR);                     /* wModus               */
        }
        return(pMkb->pHotkeys[wOption].wMarker);    /* Status zurckgeben   */
    }
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuFindeMkb                  Datum: 26.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWORD pwOption   hin    = gesuchte Option           บ
  บ                                     zurck = Index in pHotkeys         บ
  บ                    PWORD pwMenuNr   zurck = Nummer des Mens          บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ist eine Hilfsfunktion fr           บ
  บ                    MnuMarker() und MnuOption().                        บ
  บ                    Sie ermittelt die Nummer des Mens, den MKB und     บ
  บ                    den Index auf MKB->pHotkeys fr die im Argument     บ
  บ                    pwOption bergebene Option.                         บ
  บ                                                                        บ
  บ  Rckgabewert:     PMKB   Zeiger auf MKB, wenn Option gefunden wurde   บ
  บ                           oder NULL-Zeiger, wenn nicht                 บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):                                                      บ
  บ                    aMenus_g    (R)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
PMKB i_MnuFindeMkb(PWORD pwOption, PWORD pwMenuNr)
{
    REGISTER i,j;                                   /* Schleifenzhler      */
    PMKB     pMkbTmp;                               /* derzeit bearb. MKB   */

    for (i=0; i < MAXMENUES; i++)                   /* alle Mens werden    */
    {                                               /* durchsucht           */
        pMkbTmp = aMenus_g[i].pMkbStart;            /* Adresse erster MKB   */
        if (pMkbTmp != NULL)                        /* wenn MKB da          */
        {
            do                                      /* verkette Liste MKB's */
            {                                       /* abarbeiten           */
                for (j=0;                           /* alle Items abarb.    */
                     j < pMkbTmp->wItemAnzahl;
                     j++)
                {
                    if ((pMkbTmp->pHotkeys[j].wOpt) == *pwOption)
                    {
                        *pwOption = j;
                        *pwMenuNr = i;
                        return (pMkbTmp);
                    }
                }
            } while((pMkbTmp = pMkbTmp->pNaechster) != aMenus_g[i].pMkbStart);
        } /* end of if */
    } /* end of for */
    return (NULL);
}
