/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_InitVars                     Datum: 31.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion initialsiert, sofern noch nicht      บ
  บ                    geschehen, folgende globale Variablen:              บ
  บ                                                                        บ
  บ                      - wVioMode_g      (aktiver Video-Modus)           บ
  บ                      - wCSInd_g        (Index auf die Farbpalette)     บ
  บ                                                                        บ
  บ  Rckgabewert:     Die Funktion hat keinen Rckgabewert                บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - wVioMode_g (W)                                   บ
  บ                     - wCSInd_g   (W)                                   บ
  บ                     - aMenus_g   (W)                                   บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <stdio.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wCSInd_g;
IMPORT WORD wVioMode_g;
IMPORT MENU aMenus_g[];

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
BOOL bInit_m = NEIN;                                /* Flag                 */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_InitVars(VOID)
{

    REGISTER i;

    if (!bInit_m)
    {
        wVioMode_g = VioGetMode();                  /* Videomodus bestimmen */

        if (wCSInd_g == NICHT_INIT)                 /* Ist schon eine Farb- */
        {                                           /* palette initial. ?   */
            if (wVioMode_g == MONOCHROM)            /* Standardpalette fr  */
                wCSInd_g = MNU_PAL_MONO;            /* Monochrom-Modus      */
            else                                    /* Standardpalette fr  */
                wCSInd_g = MNU_PAL_BLAU;            /* alle anderen Modi    */

        }
        for (i=0; i < MAXMENUES; i++)               /* Palette fr Mens    */
            aMenus_g[i].wStatus.wPalette            /* festlegen            */
                        = wCSInd_g;


        bInit_m = JA;                               /* Flag setzen          */
    }
    return;
}
