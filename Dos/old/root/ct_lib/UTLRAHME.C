/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlZeigeRahmen                 Datum: 16.08.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wSpalte, wZeile        linke obere Ecke      บ
  บ                    WORD   wBreite, wHoehe,       Ausdehnung            บ
  บ                    WORD   wTyp,    wAttr         Rahmentyp, Attribut   บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion zeichnet einen Rahmen an der         บ
  บ                    bergebenen Position mit dem gewnschten Rahmen-    บ
  บ                    typ und Attribut.                                   บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  cRahmenzeichen_g(R)                                 บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>        /* Standard-Datentypen                          */
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>          /* Utility-Modul der Toolbox                    */
#endif

#ifndef CT_VIDEO_HEADER
#include <ctvio.h>          /* Funktionen zur Bildschirmausgabe             */
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT CHAR cRahmenzeichen_g[][8];

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define OL      0                           /* Position des Grafikzeichens  */
#define OR      1                           /* im Array ฏcRahmenzeichen_gฎ  */
#define UL      2                           /* fr den entsprechenden       */
#define UR      3                           /* Teil des Rahmens             */
#define WAAGEO  4
#define WAAGEU  5
#define SENKL   6
#define SENKR   7

#define RZ cRahmenzeichen_g


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlZeigeRahmen (WORD wSpalte, WORD wZeile, WORD wBreite,
                     WORD wHoehe,  WORD wTyp,   WORD wAttr)
{
    REGISTER i, wSp_r, wZe_u;

    wSp_r = wSpalte+wBreite-1;                          /* Daten einmal     */
    wZe_u = wZeile +wHoehe -1;                          /* berechnen        */

    VioSza(wSpalte, wZeile, RZ[wTyp][OL], wAttr);       /*  Ecken zeichnen  */
    VioSza(wSp_r,   wZeile, RZ[wTyp][OR], wAttr);
    VioSza(wSpalte, wZe_u,  RZ[wTyp][UL], wAttr);
    VioSza(wSp_r,   wZe_u,  RZ[wTyp][UR], wAttr);

    for (i=wSpalte+1; i < wSp_r; i++)
    {
        VioSza(i, wZeile, RZ[wTyp][WAAGEO], wAttr);     /* Zeile oben       */
        VioSza(i, wZe_u,  RZ[wTyp][WAAGEU], wAttr);     /* Zeile unten      */
    }

    for (i = wZeile+1; i < wZe_u; i++)
    {
        VioSza(wSpalte, i, RZ[wTyp][SENKL], wAttr);     /* Seite links      */
        VioSza(wSp_r,   i, RZ[wTyp][SENKR], wAttr);     /* Seite rechts     */
    }
    return;
}
