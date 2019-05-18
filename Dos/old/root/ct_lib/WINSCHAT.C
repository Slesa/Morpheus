/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSchattenEin                 Datum: 13.09.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB    pWkb   Zeiger auf Fensterkontrollblock      บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion k”nnen Sie festlegen, ob um     บ
  บ                    den Fensterrahmen ein Schatten angezeigt werden     บ
  บ                    soll. Dies muแ vor der ersten Aktivierung des       บ
  บ                    Windows festgelegt werden.                          บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD    OK    wenn kein Fehler auftrat              บ
  บ                            ERROR im Fehlerfall, wFehler_g erhlt       บ
  บ                                  eine der folgenden Fehlernummern:     บ
  บ                                  - WIN_KEIN_PWKB                       บ
  บ                                  - WIN_FALSCHE_OPT                     บ
  บ                                  - WIN_AUSSERHALB                      บ
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
#include <ctools.h>


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                  GLOBALE VARIABLEN, REFERENZEN                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinSchattenEin(PWKB pWkb)
{
    if (pWkb->wWkbsign != WKBSIGNATUR)              /* Test ob Zeiger noch  */
    {                                               /* auf WKB zeigt, wenn  */
        wFehler_g = WIN_KEIN_PWKB;                  /* nicht Variable setz. */
        return ERROR;                               /* und an aufr. Fkt.    */
    }

    if (pWkb->winFlags.wVersteckt == 1 ||           /* Schatten setzen nur  */
        pWkb->winFlags.wSichtbar  == 1 )            /* vor erstem Zeigen    */
    {                                               /* m”glich              */
        wFehler_g = WIN_FALSCHE_OPT;                /* Variable setzen      */
        return ERROR;                               /* zurck an Aufrufer   */
    }

    if (pWkb->wSpalte+pWkb->wBreite+1>= MAXSPALTEN  /* Test ob Schatten auf */
        || pWkb->wZeile+pWkb->wHoehe >= MAXZEILEN)  /* Bildschirm paแt      */
    {
        wFehler_g = WIN_AUSSERHALB;                 /* Variable setzen      */
        return ERROR;                               /* zurck an Aufrufer   */
    }

    pWkb->winFlags.wSchatten = 1;                   /* Schatten-Flag setzen */
    return (OK);
}
