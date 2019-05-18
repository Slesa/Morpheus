/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuSetPalette                  Datum: 26.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wMenuNr    Nummer des Mens                   บ
  บ                    WORD  wPalette   Nummer der gewnschten Palette     บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion k”nnen Sie eine der fnf        บ
  บ                    Farbpaletten auswhlen, in der die Attribute        บ
  บ                    fr die Mens und die Dialoge festgelegt sind.      บ
  บ                                                                        บ
  บ                    Im Monochrom-Modus kann nur die monochrome          บ
  บ                    Palette ausgewhlt werden, in einem der Farbmodi    บ
  บ                    stehen Ihnen alle Farbpaletten zur Verfgung.       บ
  บ                                                                        บ
  บ                    Der Aufruf der Funktion kann an jeder beliebigen    บ
  บ                    Stelle des Programms erfolgen. Alle Puffer fr      บ
  บ                    die Menfenster und die Menzeilen werden neu       บ
  บ                    angelegt.                                           บ
  บ                    Wenn ein Men aktiv ist, wird die Menzeile neu     บ
  บ                    angezeigt.                                          บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation OK/ERROR                    บ
  บ                          im Fehlerfall wird die globale Variable       บ
  บ                          wFehler_g mit der Fehlernummer geladen        บ
  บ                          - MNU_FALSCHE_OPT                             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - wVioMode_g (R(W)                                  บ
  บ                    - wFehler_g  (R)                                    บ
  บ                    - wAktMnu_g  (R)                                    บ
  บ                    - aMenus_g   (R)                                    บ
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
IMPORT WORD wVioMode_g;         /* aktueller Video-Modus                    */
IMPORT MENU aMenus_g[];         /* Array der MENU-Strukturen                */
IMPORT WORD wAktMnu_g;          /* aktueller Index zu Menus_g               */
IMPORT WORD wMausda_g;          /* Maus im System aktiviert ?               */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MnuSetPalette(WORD wMenuNr, WORD wPalette)
{
    PMKB pMkb;
    WORD wMausStatus;
    BOOL boAendern = NEIN;

    if (wMenuNr >= MAXMENUES)                       /* maximale Anzahl der  */
    {                                               /* Mens berprfen     */
        wFehler_g = MNU_LIMIT;                      /* Fehlernummer laden   */
        return(ERROR);                              /* und zurck           */
    }

    i_InitVars();                                   /* glo. Var initialis.  */


    switch( wPalette )                              /* Palette untersuchen  */
    {                                               /* wenn erforderlich,   */
        case MNU_PAL_BLAU:                          /* in MENU-Struktur ein-*/
        case MNU_PAL_WEISS:                         /* tragen, Aender-Flag  */
        case MNU_PAL_KOBALT:                        /* setzen               */
        case MNU_PAL_SCHWARZ:
            if (wVioMode_g == MONOCHROM)            /* im Monochrom-Modus   */
            {                                       /* ist eine farbige     */
                wFehler_g = MNU_FALSCHE_OPT;        /* Palette nicht er-    */
                return (ERROR);                     /* laubt                */
            }
            else if ( aMenus_g[wMenuNr].wStatus.wPalette != wPalette)
            {
                aMenus_g[wMenuNr].wStatus.wPalette = wPalette;
                boAendern = JA;
            }
            break;

        case MNU_PAL_MONO:
            if ( aMenus_g[wMenuNr].wStatus.wPalette != wPalette)
            {
                aMenus_g[wMenuNr].wStatus.wPalette = wPalette;
                boAendern = JA;
            }
            break;

        default:
            wFehler_g = MNU_FALSCHE_OPT;
            return (ERROR);
    }



    if (boAendern == JA  &&                         /* Test ob schon aktiv  */
        aMenus_g[wMenuNr].pMkbStart != NULL)        /* wenn Men initial.   */
    {
        i_MnuGenMenuZeile(wMenuNr) ;                /* Menzeile generieren */

        pMkb = aMenus_g[wMenuNr].pMkbStart;         /* alle Menfenster neu */
        do                                          /* aufbauen             */
        {
            i_MnuToBuffer(pMkb, wMenuNr, MNU_AENDERN);
            pMkb = pMkb->pNaechster;
            if (pMkb->wMkbsign != MKBSIGNATUR)
                i_Fehler(I_FEHLER_SIGN, "MnuSetPalette()",
                         __FILE__, __LINE__);
        } while ( pMkb != aMenus_g[wMenuNr].pMkbStart);


        if (wAktMnu_g == wMenuNr)                   /* Menzeile des akt.   */
        {                                           /* Mens neu anzeigen   */
            if (wMausda_g)                          /* wenn Maus da         */
                wMausStatus = MsmCursorOff();       /* Zeiger ausschalten   */
            VioSb2w(0,0,80,1,                       /* Menzeile ausgeben   */
                aMenus_g[wAktMnu_g].fpwMzBuffer);
            if (wMausda_g && wMausStatus == MSM_WAR_AN)
                MsmCursorOn();
        }
    }
    return (OK);
}

