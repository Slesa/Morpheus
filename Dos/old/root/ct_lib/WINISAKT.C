/*ﾉﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｻ
  ｺ  Funktionsname:    WinIsAktiv                     Datum: 21.09.88      ｺ
  ﾇﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄｶ
  ｺ                                                                        ｺ
  ｺ  Parameter:        PWKB  pWkb   Zeiger auf Fensterkontrollblock        ｺ
  ｺ                                                                        ｺ
  ｺ  Beschreibung:     Diese Funktion testet, ob der der ｜ergebene        ｺ
  ｺ                    Zeiger auf den Fensterkontrollblock des derzeit     ｺ
  ｺ                    aktiven Windows zeigt.                              ｺ
  ｺ                                                                        ｺ
  ｺ  R…kgabewert:     BOOL    JA/NEIN                                     ｺ
  ｺ                                                                        ｺ
  ｺ                                                                        ｺ
  ｺ  Benutzte globale                                                      ｺ
  ｺ  Variablen (R/W):  - apWkbSichtbar_g[16] (R)                           ｺ
  ｺ                    - wAktWin_g (R)                                     ｺ
  ﾇﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄｶ
  ｺ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           ｺ
  ｺ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei M］chen     ｺ
  ﾈﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｼ*/
/*ﾉﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｻ
  ｺ                        DEKLARATIONS-DATEIEN                            ｺ
  ﾈﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｼ*/
#include <stdio.h>
#include <ctools.h>

/*ﾉﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｻ
  ｺ                    GLOBALE VARIABLEN, REFERENZEN                       ｺ
  ﾈﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｼ*/
IMPORT  PWKB    apWkbSichtbar_g[16];                /* Array v. Zeigern auf */
                                                    /* WKB der sichtbaren W.*/
IMPORT  WORD    wAktWin_g;                          /* Index des aktiven W. */
                                                    /* in ｯapWkbSichtbar[]ｮ */
/*ﾉﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｻ
  ｺ                          FUNKTIONS-DEFINITION                          ｺ
  ﾈﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｼ*/
GLOBAL
BOOL WinIsAktiv( PWKB pWkb)
{
    if (wAktWin_g == 0)
        return (NEIN);
    else
        return((pWkb == apWkbSichtbar_g[wAktWin_g]) ? JA : NEIN );
}




/*ﾉﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｻ
  ｺ  Funktionsname:    WinGetAktivPwkb                Datum: 21.09.88      ｺ
  ﾇﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄｶ
  ｺ                                                                        ｺ
  ｺ  Parameter:        keine                                               ｺ
  ｺ                                                                        ｺ
  ｺ  Beschreibung:     Diese Funktion liefert als Ergebnis den Zeiger      ｺ
  ｺ                    auf den Fensterkontrollblock des derzeit            ｺ
  ｺ                    aktiven Windows.                                    ｺ
  ｺ                                                                        ｺ
  ｺ  R…kgabewert:     PWKB    Zeiger auf Fensterkontrollblock oder NULL,  ｺ
  ｺ                            wenn kein Window aktiv                      ｺ
  ｺ                                                                        ｺ
  ｺ  Benutzte globale                                                      ｺ
  ｺ  Variablen (R/W):  - apWkbSichtbar_g[16] (R)                           ｺ
  ｺ                    - wAktWin_g (R)                                     ｺ
  ﾈﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍﾍｼ*/
GLOBAL
PWKB WinGetAktivPwkb(VOID)
{
    if (wAktWin_g == 0)                             /* wenn Fenster 0 aktiv */
        return (NULL);                              /* Zeiger intern halten */
    else
        return(apWkbSichtbar_g[wAktWin_g]);         /* sonst Zeiger zur…k  */
}

