/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuAktivieren                  Datum: 12.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wMenuNr    Nummer der gewnschtes Mens       บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion wird eines der von Ihnen        บ
  บ                    eingerichteten Mens aktiviert. Zeile 0, in         บ
  บ                    der die Menzeile ausgegeben wird, wird gesichert   บ
  บ                    und anschlieแend die Menzeile fr das bergebene   บ
  บ                    Men ausgegeben.                                    บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation OK/ERROR                    บ
  บ                          im Fehlerfall wird die globale Variable       บ
  บ                          wFehler_g mit der Fehlernummer geladen        บ
  บ                          - MNU_LIMIT                                   บ
  บ                          - MNU_NICHT_REG   kein Menfenster einger.    บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wVioMode_g (R(W)                                    บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ   (c) copyright 1988,1989 Markt & Technik Verlag AG, Haar bei Mnchen  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>
#include <ctools.h>
#include <string.h>
#include <dos.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD     wFehler_g;          /* Nummer des letzten Fehlers           */
IMPORT WORD     wVioMode_g;         /* aktueller Video-Modus                */
IMPORT WORD     wMausda_g;          /* Maus im System aktiviert             */
IMPORT COLORSET aCS_g[];            /* Array der Farbpaletten               */

IMPORT MENU     aMenus_g[];         /* Array der MENU-Strukturen            */
IMPORT WORD     wAktMnu_g;          /* aktueller Index auf Men-Array       */
IMPORT FPWORD   fpwAlteMZ_g;        /* Puffer mit altem Inhalt Zeile 0      */
IMPORT FPWORD   fpwAlteHZ_g;        /* Puffer alter Inhalt Hilfszeile       */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL PSTR pstrFnMZ_m  = "i_MnuGenMenuZeile()";


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MnuAktivieren(WORD wMenuNr)
{
    WORD wMausStatus;

    if (wMenuNr >= MAXMENUES)                       /* maximale Anzahl der  */
    {                                               /* Mens berprfen     */
        wFehler_g = MNU_LIMIT;                      /* Fehlernummer laden   */
        return(ERROR);                              /* und zurck           */
    }


    if (aMenus_g[wMenuNr].pMkbStart == NULL)        /* kein Menfenster     */
    {                                               /* eingerichtet         */
        wFehler_g = MNU_NICHT_REG;                  /* Fehlernummer laden   */
        return(ERROR);                              /* und zurck           */
    }


    if (wAktMnu_g != wMenuNr)                       /* neues Men aktivier. */
    {
        if (wAktMnu_g != NICHT_INIT)                /* wenn and. Mnu aktiv  */
            MnuDeaktivieren();                      /* dies zuerst deaktiv. */

        if (fpwAlteMZ_g == 0L)                      /* Puffer Menzeile     */
            fpwAlteMZ_g = (FPWORD) UtlFmalloc( MAXSPALTEN * sizeof(WORD));

        if (fpwAlteHZ_g == 0L &&                    /* Puffer Hilfszeile    */
            aMenus_g[wMenuNr].wStatus.wHzeile == 1)
            fpwAlteHZ_g = (FPWORD) UtlFmalloc( MAXSPALTEN * sizeof(WORD));


        wAktMnu_g = wMenuNr;                        /* glo. Var. laden      */

        i_MnuGenMenuZeile(wMenuNr);                 /* Menzeile generieren */

        if (wMausda_g)
            wMausStatus = MsmCursorOff();           /* Mauszeiger aus       */

        if (fpwAlteMZ_g != 0L)                      /* Menzeile sichern    */
            VioSw2b(0,0,80,1,fpwAlteMZ_g);

        VioSb2w(0,0,80,1,                           /* Menzeile anzeigen   */
                aMenus_g[wAktMnu_g].fpwMzBuffer);

        if (wMausda_g && wMausStatus == MSM_WAR_AN) /* wenn da und an war   */
            MsmCursorOn();                          /* Mauszeig. wieder ein */
    }
    return (OK);                                    /* das war's            */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuGenMenuZeile              Datum: 25.10.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD       wMenuNr Nummer des Mens, fr das die    บ
  บ                                       Menzeile generiert werden       บ
  บ                                       soll                             บ
  บ                                                                        บ
  บ  Beschreibung:     In dieser Funktion wird ein 1:1-Puffer der Men-    บ
  บ                    zeile generiert und im Speicher abgelegt.           บ
  บ                    Gleichzeitig wird der Tastaturcode, mit dem das     บ
  บ                    Men aktiviert werden kann, in den zum Men ge-     บ
  บ                    h”renden Menkontrollblock eingetragen.             บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  aCS_g[]  (R)                                        บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_MnuGenMenuZeile(WORD wMenuNr)
{
	REGISTER wSpace,                                /* Leerzeichen mit Attr */
             wMzAttn,                               /* normales Attribut    */
			 wMzAtth;                               /* Attribut fr Hotkeys */

    PMKB     pMkbLokal;                             /* lokaler Zeiger auf   */
                                                    /* Liste der MKB's      */

    FPWORD   fpwTmpMzBuf;                           /* lokaler Zeiger auf   */
                                                    /* Menzeile            */

    WORD     wPalInd;
    WORD     wMaxlaenge;                            /* geschriebene Zeichen */
    WORD     wAktSpalte;                            /* aktuelle Spalte      */
    PSTR     pstrTitel;                             /* lokaler Z. auf Titel */
    CHAR     c;

    if (aMenus_g[wMenuNr].fpwMzBuffer == 0L)        /* eventuell Puffer an- */
         if ((aMenus_g[wMenuNr].fpwMzBuffer         /* legen                */
                = (FPWORD) UtlFmalloc (MAXSPALTEN*sizeof(WORD))) == 0L )
                    i_Fehler(MNU_KEIN_SPEICHER, pstrFnMZ_m,
                             __FILE__, __LINE__);

                                                    /* ersten PMKB holen    */
    if ((pMkbLokal = aMenus_g[wMenuNr].pMkbStart) == NULL)
        return;

                                                    /* Var. initialisieren  */
    fpwTmpMzBuf = aMenus_g[wMenuNr].fpwMzBuffer;    /* Pufferadresse holen  */

    wMaxlaenge  = MAXSPALTEN;                       /* maximale Zeilenlnge */
    wAktSpalte  = 0;                                /* akt. Schreibspalte   */

    wPalInd   = aMenus_g[wMenuNr].wStatus.wPalette; /* Palettenindex holen  */
    wMzAttn   = aCS_g[wPalInd].wCs_mz    <<8;       /* normales Attribut    */
    wMzAtth   = aCS_g[wPalInd].wCs_mz_hk <<8;       /* Hotkey Attribut      */
    wSpace    = wMzAttn | BLANK;                    /* Leerzeichen mit Att. */


                                                    /* Ausgabeteil          */
	*fpwTmpMzBuf++ = wSpace;                        /* Leerzeichen am Anfang*/
	*fpwTmpMzBuf++ = wSpace;                        /* in den               */
	wMaxlaenge -=2;                                 /* Buffer schreiben     */
	wAktSpalte +=2;



    do                                              /* Mentitel in Puffer  */
    {
        pstrTitel = pMkbLokal->item->pstrText;

        pMkbLokal->wTitelBreite = strlen(pstrTitel);
        if( strrchr(pstrTitel,'#') != NULL)
            pMkbLokal->wTitelBreite--;

        if (pMkbLokal->item->wOption == RECHTSBUENDIG)
        {
            while( wAktSpalte++ < (77-pMkbLokal->wTitelBreite))
            {
                wMaxlaenge--;
                *fpwTmpMzBuf++ = wSpace;        /* Leerzeichen          */
            }
        }
        if ((wAktSpalte+pMkbLokal->wBreite+2) < 80) /* Startspalte des Men-*/
            pMkbLokal->wSpalte = wAktSpalte-2;      /* fensters berechnen   */
        else
            pMkbLokal->wSpalte=80-2-pMkbLokal->wBreite;

        pMkbLokal->wTitelSpalte = wAktSpalte;
        if (pMkbLokal->item->wOption == RECHTSBUENDIG)
            pMkbLokal->wTitelSpalte--;

        while (*pstrTitel)                          /* noch im Mentext ?   */
        {
            if (*pstrTitel == HOTKEY)               /* Zeichen fr Hotkey ? */
            {
                pstrTitel++;                        /* Zeichen berspringen */
                *fpwTmpMzBuf++ =wMzAtth|*pstrTitel; /* nchst. Z. in Puffer */
                c = *pstrTitel;
                                                    /* Hotkey zur Menaktiv.*/
                pMkbLokal->wMzHotkey= UtlAltCode(c);/* in Alt-Code umwand.  */
                                                    /* und ablegen          */
            }
            else                                    /* sonst Buchstaben     */
                *fpwTmpMzBuf++ = wMzAttn | *pstrTitel;   /* in Buffer       */
            wMaxlaenge--;                           /* Lnge mithalten      */
            wAktSpalte++;                           /* akt. Spalte mithalten*/
            pstrTitel++;                            /* nchstes Zeichen     */
        } /* end of while */


		*fpwTmpMzBuf++ = wSpace;                    /* Men-Titel in den    */
		*fpwTmpMzBuf++ = wSpace;                    /* Men-Titel in den    */
		wMaxlaenge -=2;                               /* Buffer schreiben     */
		wAktSpalte +=2;


        pMkbLokal = pMkbLokal->pNaechster;          /* auf nchsten MKB     */
        if (pMkbLokal->wMkbsign != MKBSIGNATUR)     /* Test ob Zeiger nach  */
             i_Fehler(I_FEHLER_SIGN,                /*   MKB zeigt          */
                       pstrFnMZ_m,
                       __FILE__, __LINE__);
    } while (pMkbLokal != aMenus_g[wMenuNr].pMkbStart);

    while ((wMaxlaenge--) > 0)                      /* fr Rest der Zeile   */
        *fpwTmpMzBuf++ = wSpace;                    /* Leerzeichen          */

    return;
}
