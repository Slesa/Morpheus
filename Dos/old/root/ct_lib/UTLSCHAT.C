/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlZeigeSchatten               Datum: 16.08.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wSpalte          Fensterspalte oben links     บ
  บ                    WORD  wZeile           Fensterzeile oben links      บ
  บ                    WORD  wBreite          Fensterbreite inkl. Rahmen   บ
  บ                    WORD  wHoehe           Fensterh”he inkl. Rahmen     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion zeichnet einen Schatten an ein       บ
  บ                    Fenster, dessen Koordinaten bergeben wurden.       บ
  บ                    Wenn die ermittelten Koordinaten des Fenster-       บ
  บ                    schattens gr”แer sind, als der tatschliche         บ
  บ                    Bildschirm, werden nur die sichbaren Teile des      บ
  บ                    Schattens ausgegeben.                               บ                     บ
  บ                    Die Funktion behandelt die Ausgabe eines Schattens  บ
  บ                    in Abhngigkeit vom aktuellen Video-Modus. Im       บ
  บ                    Monochrommodus wird das Zeichen ASCII SZ ausgege-   บ
  บ                    ben, in den Farbmodi wird um das Fenster das        บ
  บ                    Attribut GRAU ausgegeben.                           บ
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
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_VIDEO_HEADER
#include <ctvio.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL SWORD swVmode_m = -1;      /* funktionsinternes Flag fr Videomodus */
#define SZ 176

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlZeigeSchatten(WORD wSpalte, WORD wZeile, WORD wBreite, WORD wHoehe)
{
    REGISTER i;
    WORD wStart, wStop;
    if (swVmode_m == -1)                            /* Test ob Flag bereits */
        swVmode_m = VioGetMode();                   /* initialisiert        */

    if (swVmode_m == MONOCHROM)                     /* im Monochrom-Modus   */
    {                                               /* sieht der Schatten   */
        wStart = wSpalte+wBreite;                   /* so aus: ฑ            */
        if (wStart < MAXSPALTEN)
        {
            wStop  = wZeile+wHoehe;
            for (i=wZeile+1; i <= wStop && i<=MAXZEILEN; i++)
            {
                VioSza(wStart, i, SZ, NORMAL);      /* senkrechter Schatten */
                if (wStart < MAXSPALTEN -1)
                    VioSza(wStart+1, i, SZ, NORMAL);
            }
        }

        wStart = wZeile+wHoehe;                     /* waagrechter Schatten */
        if (wStart < MAXZEILEN)                     /* Koordinatenber-     */
        {                                           /* prfung              */
            wStop  = wSpalte+wBreite+1;
            for (i=wSpalte+2; i<wStop && i<= MAXSPALTEN; i++)
                VioSza(i, wStart, SZ, NORMAL);
        }

    } /* end if if(swVmode_m == MONOCHROM) */


    else                                            /* im Farbmode wird als */
    {                                               /* Schatten am rechten  */
        wStart = wSpalte+wBreite;                   /* und unteren Rand das */
        if (wStart < MAXSPALTEN)                    /* Attribut Grau        */
        {                                           /* ausgegeben           */
            wStop = wZeile+wHoehe;
            for (i=wZeile+1; i<=wStop && i<= MAXZEILEN; i++)
            {                                       /* senkr. Schatten      */
                VioSa(wStart, i, GRAU);             /* berprfung der      */
                if (wStart < MAXSPALTEN-1)         /* Koordinaten          */
                    VioSa(wStart+1, i, GRAU);
            }
        }
        wStart = wZeile+wHoehe;                     /* waagrechter Schatten */
        if (wStart < MAXZEILEN)
        {
            wStop = wSpalte+wBreite+1;
            for (i=wSpalte+2; i<wStop && i<= MAXSPALTEN; i++)
                VioSa(i, wStart, GRAU);
        }
    } /* end of else (swVmode_m != MONOCHROM) */
    return;
}
