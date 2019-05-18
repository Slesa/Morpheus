/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSetTitel                    Datum: 13.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB     pWkb    Zeiger auf Fensterkontrollblock    บ
  บ                    PSTR     pStr    Zeiger auf Titelstring             บ
  บ                    WORD     wPos    Position des Titels auf dem        บ
  บ                                     Rahmen                             บ
  บ                                     - WIN_TITEL_OL  oben, linksbndig  บ             บ
  บ                                     - WIN_TITEL_OZ  oben, zentriert    บ
  บ                                     - WIN_TITEL_OR  oben, rechtsbndig บ
  บ                                     - WIN_TITEL_UL  unten, linksbndig บ
  บ                                     - WIN_TITEL_UZ  unten, zentriert   บ
  บ                                     - WIN_TITEL_UR  unten, rechtsbndigบ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion kann fr ein Fenster der        บ
  บ                    Text und die Position eines Titels festgelegt       บ
  บ                    werden.                                             บ
  บ                    Die Funktion legt eine Kopie des Titelstrings       บ
  บ                    an und trgt einen Zeiger auf den Titel und         บ
  บ                    die bergebene Position in den WKB ein.             บ
  บ                    Bei einem aktiven Fenster wird der neue             บ
  บ                    Titel ausgegeben. Sonst werden die nderungen       บ
  บ                    erst beim Aktivieren des Fensters sichtbar.         บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD    OK     kein Fehler aufgetreten              บ
  บ                            ERROR  wenn Fehler auftritt und globale     บ
  บ                                   Variable wFehler_g erhlt die        บ
  บ                                   Fehlernummer                         บ
  บ                                   - WIN_KEIN_PWKB                      บ
  บ                                   - WIN_KEIN_SPEICHER                  บ
  บ                                   - WIN_TITEL_LAENGE                   บ
  บ                                   - WIN_FALSCHE_OPT                    บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g (W)                                       บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>
#include <string.h>

#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */
IMPORT WORD wMausda_g;          /* Maus vorhanden ?                         */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinSetTitel(PWKB pWkb, PSTR pStr, WORD wPos)
{
    WORD wMausstatus;

    if (pWkb->wWkbsign != WKBSIGNATUR)              /* Test ob Zeiger noch  */
    {                                               /* auf WKB zeigt, wenn  */
        wFehler_g = WIN_KEIN_PWKB;                  /* nicht Variable setz. */
        return (ERROR);                             /* und an aufr. Fkt.    */
    }


    if (wPos < WIN_TITEL_OL
        || wPos > WIN_TITEL_UR)                     /* wenn kein gltiges   */
    {                                               /* Funktionsargument    */
        wFehler_g = WIN_FALSCHE_OPT;                /* Variable setzen und  */
        return (ERROR);                             /* an Aufrufer          */
    }


    if ((strlen(pStr)) > pWkb->wBreite-4)           /* Titel darf nicht     */
    {                                               /* lnger sein als      */
        wFehler_g = WIN_TITEL_LAENGE;               /* Fensterbreite - 4    */
        return (ERROR);
    }

    if (pWkb->pstrTitel != NULL)                    /* Speicher des alten   */
        free(pWkb->pstrTitel);                      /* Titels freigeben     */

    if (( pWkb->pstrTitel=strdup(pStr)) == NULL)    /* Kopie von Titelstr.  */
    {                                               /* anlegen, und Fehler  */
        wFehler_g = WIN_KEIN_SPEICHER;              /* behandeln            */
        return (ERROR);
    }


                                                    /* ab hier gab's keine  */
                                                    /* Fehler               */
    pWkb->winFlags.wTitelPos = wPos;                /* neuen Typ eintragen  */

    if ( WinIsAktiv(pWkb) )                         /* wenn Fenster aktiv   */
    {
        if (wMausda_g)                              /* evtl. Mauszeiger aus */
            wMausstatus = MsmCursorOff();           /* vor Ausgabe          */
        UtlZeigeRahmen( pWkb->wSpalte,              /* neuen Rahmentyp      */
                        pWkb->wZeile,               /* anzeigen             */
                        pWkb->wBreite,
                        pWkb->wHoehe,
                        pWkb->winFlags.wRahmentyp,
                        pWkb->wRahmenAttr);

        i_WinZeigeTitel(pWkb);                      /* neuen Titel zeigen   */

        if (wMausda_g && wMausstatus == MSM_WAR_AN) /* Maus wieder ein      */
            MsmCursorOn();
    }
    else
        pWkb->winFlags.wTRaendern = 1;              /* Flag setzen, damit   */
                                                    /* bei nchster Aktiv.  */
                                                    /* bercksichtigt werden*/
    return OK;
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinZeigeTitel                Datum: 19.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB   Zeiger auf Fensterkontrollblock              บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion schreibt einen Window-Titel an       บ
  บ                    die in der Struktur festgelegte Position im         บ
  บ                    festgelegten Attribut.                              บ
  บ                                                                        บ
  บ                    Aufrufer: WinSetTitel(), WinZeigen(), WinSetAtt()   บ
  บ                    Diese Funktion zeichnen ggf. den Rahmen neu.        บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_WinZeigeTitel(PWKB pWkb)
{
    WORD wStrLaenge;
    WORD wTitelSpalte, wTitelZeile;

    if ( (pWkb->wWkbsign != WKBSIGNATUR) ||
         (pWkb->pstrTitel == NULL)       ||
         !(WinIsAktiv(pWkb))  )
       return;

    wStrLaenge = strlen(pWkb->pstrTitel);

    if (pWkb->winFlags.wTitelPos < 3)
        wTitelZeile = pWkb->wZeile;
    else
        wTitelZeile = pWkb->wZeile + pWkb->wHoehe -1;

    switch(pWkb->winFlags.wTitelPos)
    {
        case WIN_TITEL_OL:
        case WIN_TITEL_UL:
                wTitelSpalte = pWkb->wSpalte+2;
                break;
        case WIN_TITEL_OR:
        case WIN_TITEL_UR:
                wTitelSpalte = pWkb->wSpalte+pWkb->wBreite-2-wStrLaenge;
                break;
        case WIN_TITEL_OZ:
        case WIN_TITEL_UZ:
                wTitelSpalte = pWkb->wSpalte+ (pWkb->wBreite-wStrLaenge)/2;
                break;
    }
    VioSsa(wTitelSpalte, wTitelZeile,
           pWkb->pstrTitel, pWkb->wTitelAttr);

    return;
}
