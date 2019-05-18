/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlZeigeLinie                  Datum: 17.08.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wSpalte        Ausgabespalte                 บ
  บ                    WORD   wZeile         Ausgabezeile                  บ
  บ                    WORD   wBreite        Lnge der Linie               บ
  บ                    WORD   wHoehe         Lnge der Linie               บ
  บ                    WORD   wAttr          Attribut der Linie            บ
  บ                    WORD   wRT                                          บ
  บ                    WORD   wLT            EINFACH, DOPPELT              บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion teilt einen Rahmen mit einem         บ
  บ                    beliebigen Typ durch eine waagerechte oder          บ
  บ                    senkrechte einfache oder doppelte Linie.            บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
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
#include <string.h>

#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_WINDOW_HEADER
#include <ctwin.h>
#endif


#ifndef CT_VIDEO_HEADER
#include <ctvio.h>
#endif                        /* einf. Rahmen  , doppelter Rahmen     */

CHAR acEnde[2][2][4] = {
                          { "ยดมร", "ัถฯว" },        /* einfacher Linientyp  */
                          { "าตะฦ", "หนสฬ" }         /* doppelter Linietyp   */
                       };

CHAR acLinie[2][2] = {
                        "ฤณ",                       /* einfacher Linietyp   */
                        "อบ"                        /* doppelter Linietyp   */
                     };

#define  MASKE_L   0x01                             /* Obere Rahmenkante    */
#define  MASKE_U   0x02                             /* Rechte Rahmenkante   */
#define  MASKE_R   0x04                             /* Untere Rahmenkante   */
#define  MASKE_O   0x08                             /* Linke Rahmenkante    */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlZeigeLinie(WORD wSpalte, WORD wZeile,
                   WORD wBreite, WORD wHoehe,
                   WORD wAttr,
                   WORD wRT, WORD wLT )
{
    WORD wStaerke;

    if ( wBreite != 0  &&  wHoehe == 0 )            /* waagrechte Linie     */
    {
        wStaerke = (wRT & MASKE_L) ? 1:0;           /* Strichstrke des Rah.*/
        VioSza(wSpalte++, wZeile,
               acEnde[wLT][wStaerke][3], wAttr);

        while (--wBreite > 1)
            VioSza(wSpalte++, wZeile,
                   acLinie[wLT][0], wAttr);

        wStaerke = (wRT & MASKE_R) ? 1:0;           /* Strichstrke des Rah.*/
        VioSza(wSpalte, wZeile,
               acEnde[wLT][wStaerke][1], wAttr);
    }

    else if ( wBreite == 0  &&  wHoehe != 0 )       /* senkrechte Linie     */
    {
        wStaerke = (wRT & MASKE_O) ? 1:0;           /* Strichstrke des Rah.*/
        VioSza(wSpalte, wZeile++,
               acEnde[wLT][wStaerke][0], wAttr);

        while (--wHoehe > 1)
            VioSza(wSpalte, wZeile++,
                   acLinie[wLT][1], wAttr);

        wStaerke = (wRT & MASKE_U) ? 1:0;           /* Strichstrke des Rah.*/
        VioSza(wSpalte, wZeile,
               acEnde[wLT][wStaerke][2], wAttr);

    }
}

