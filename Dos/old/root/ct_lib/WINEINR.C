/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinEinrichten                  Datum: 13.09.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte   Startspalte des Fensters         บ
  บ                    WORD     wZeile    Startzeile des Fensters          บ
  บ                    WORD     wBreite   Breite des Fensters              บ
  บ                    WORD     wHoehe    H”he des Fensters                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion allokiert Speicher fr den           บ
  บ                    Kontrollblock eines neuen Fensters, wenn die Unter- บ
  บ                    suchung der bergebenen Parameter ergibt, daแ       บ
  บ                    das Fenster maximal die Gr”แe eines 80*25-Bild-     บ
  บ                    schirmes hat.                                       บ
  บ                                                                        บ
  บ                    Wenn kein Speicher zur Verfgung steht, wird        บ
  บ                    ein Null-Zeiger, sonst der Zeiger auf den           บ
  บ                    neuen WKB zurckgegeben.                            บ
  บ                    Als Default-Wert fr die Gr”แe des Cursors wird     บ
  บ                    die Gr”แe heim Einrichten des Fensters ange-        บ
  บ                    nommen. Alle Fenster erhalten ein Default-Attribut  บ
  บ                    fr die verschiedenen Fensterbereiche.              บ
  บ                                                                        บ
  บ                    Weitere Informationen ber die Default-Werte bei    บ
  บ                    der Strukturdeklaration von WKN in <ctwin.h>.       บ
  บ                                                                        บ
  บ  Rckgabewert:     PWKB  Zeiger auf neuen Fensterkontrollblock oder    บ
  บ                          Nullzeiger, wenn beim Einrichten des          บ
  บ                          des Fensters ein Fehler auftrat. In diesem    บ
  บ                          Fall erhlt die globale Variable wFehler_g    บ
  บ                          die Nummer des Fehlers:                       บ
  บ                          - WIN_ZU_GROSS                                บ
  บ                          - WIN_KEIN_SPEICHER                           บ
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

#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_WINDOW_HEADER
#include <ctwin.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif

#ifndef CT_VIDEO_HEADER
#include <ctvio.h>
#endif



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
PWKB WinEinrichten(WORD wSpalte, WORD wZeile, WORD wBreite, WORD wHoehe)
{
    PWKB  pWkb;

    if (wSpalte+wBreite  > MAXSPALTEN               /* Test auf Bereichs-   */
        || wZeile+wHoehe > MAXZEILEN)               /* berschreitung       */
    {
        wFehler_g = WIN_ZU_GROSS;
        return NULL;
    }


    if ((pWkb = UtlAlloc(WKB)) == NULL )            /* Speicher allokieren  */
    {
        wFehler_g = WIN_KEIN_SPEICHER;
        return NULL;
    }
    else
    {
        pWkb->wWkbsign  = WKBSIGNATUR;              /* Signatur eintragen   */
        pWkb->wSpalte   = wSpalte;                  /* und bergebene       */
        pWkb->wZeile    = wZeile;                   /* Abmessungen des      */
        pWkb->wBreite   = wBreite;                  /* neuen Fensters       */
        pWkb->wHoehe    = wHoehe;

        if (VioGetMode() == MONOCHROM)              /* Cursor Default-Werte */
        {                                           /* in Abhngigkeit vom  */
            pWkb->wCursorstart  = 11;               /* Grafikmodus ein-     */
            pWkb->wCursorstop   = 12;               /* tragen               */
            pWkb->wTitelAttr    = NORMAL;
            pWkb->wRahmenAttr   = NORMAL;
            pWkb->wInnenAttr    = NORMAL;
        }
        else
        {
            pWkb->wCursorstart  =  6;
            pWkb->wCursorstop   =  7;
            pWkb->wTitelAttr    = VH(BLAU,    WEISS);
            pWkb->wRahmenAttr   = VH(BLAU,    WEISS);
            pWkb->wInnenAttr    = VH(SCHWARZ, WEISS);
        }

        pWkb->pstrTitel     = NULL;
        pWkb->fpwBuffer     = NULL;
        pWkb->winFlags.wTitelPos = WIN_TITEL_OZ;
        return (pWkb);
    }
}
