/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        utltts.c                       Datum: 22.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  In dieser Datei befinden sich die Definitionen der Funktionen         บ
  บ                                                                        บ
  บ          - UtlTypeString() und                                         บ
  บ          - UtlTypeStringAtt()                                          บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif

#ifndef CT_VIDEO_HEADER
#include <ctvio.h>
#endif



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlTypeString                  Datum: 22.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD        wSpalte       Ausgabespalte             บ
  บ                    WORD        wZeile        Ausgabezeile              บ
  บ                    PSTR        pstrQuelle    Zeiger auf auszugebenden  บ
  บ                                              String                    บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt eine Zeichenkette im            บ
  บ                    "Schreibmaschinenmodus" aus. Nach jedem Buch-       บ
  บ                    staben findet eine kurze Zeitverz”gerung statt.     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlTypeString(WORD wSpalte, WORD wZeile, PSTR pstrQuelle)
{

    VioSetCursorPos(wSpalte, wZeile);               /* Cursor in Anfangs-   */
                                                    /* position             */

    while (*pstrQuelle)                             /* String ausgeben      */
    {
        VioSz(wSpalte++, wZeile, *pstrQuelle++);    /* Zeichen einzeln      */
        VioSetCursorPos(wSpalte, wZeile);           /* Cursor mitbewegen    */
        UtlPause(UTL_TICKS, 1);                     /* Zeitverz”gerung      */
    }
    return;                                         /* zurck an Aufrufer   */
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlTypeStringAtt               Datum: 22.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD        wSpalte          Ausgabespalte          บ
  บ                    WORD        wZeile           Ausgabezeile           บ
  บ                    PSTR        pstrQuelle       Zeiger auf String      บ
  บ                    WORD        wAttr            Attribut               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion arbeitet genau wie die Funktion      บ
  บ                    UtlTypeString(), nur das hier zustzlich ein        บ
  บ                    Attribut mit ausgegeben wird.                       บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlTypeStringAtt(WORD wSpalte, WORD wZeile, PSTR pstrQuelle, WORD wAttr)
{
    VioSetCursorPos(wSpalte, wZeile);               /* Cursor in Anfangs-   */
                                                    /* position             */

    while (*pstrQuelle)                             /* String ausgeben      */
    {
      VioSza(wSpalte++,wZeile,*pstrQuelle++,wAttr); /* Zeichen einzeln      */
      VioSetCursorPos(wSpalte, wZeile);             /* Cursor mithalten     */
      UtlPause(UTL_TICKS, 1);                       /* Zeitverz”gerung      */
    }

    return;                                         /* zurck an Aufrufer   */
}


