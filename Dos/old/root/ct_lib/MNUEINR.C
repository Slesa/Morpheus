/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuEinrichten                  Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wMenuNr          Nummer des Mens             บ
  บ                    PITEM pItem            Zeiger auf ITEM-Struktur     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion initialisiert ein Men fr die wei-  บ
  บ                    tere Verwendung durch den Men-Manager.             บ
  บ                                                                        บ
  บ                    Fr den Menkontrollblock des Menfensters wird     บ
  บ                    Speicherplatz allokiert, dieser Block in die Liste  บ
  บ                    eingefgt und anschlieแend die Standard- und berge-บ
  บ                    benen Werte eingetragen.                            บ
  บ                                                                        บ
  บ  Rckgabewert:     PMKB  Zeiger auf allokierten Menkontrollblock.     บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  g_max_menues (R)                                    บ
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
#include <stdlib.h>

#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT CHAR      cRahmenzeichen_g[][8];
IMPORT COLORSET  aCS_g[];
IMPORT WORD      wCSInd_g;
IMPORT MENU      aMenus_g[];
IMPORT WORD      wVioMode_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define RZ cRahmenzeichen_g
#define OL      0                           /* Position des Grafikzeichens  */
#define OR      1                           /* im Array ฏcRahmenzeichen_gฎ  */
#define UL      2                           /* fr den entsprechenden       */
#define UR      3                           /* Teil des Rahmens             */
#define WAAGEO  4
#define WAAGEU  5
#define SENKL   6
#define SENKR   7


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE FUNKTIONEN                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL BOOL   i_MnuHotkey  (PSTR);
MGLOBAL FPWORD i_MnuTrenner (PMKB, FPWORD, WORD );
MGLOBAL VOID   i_MnuInsList (WORD, PMKB);
MGLOBAL VOID   i_MnuSetzeZeiger(PMKB pMkbVoriger, PMKB pMkbNeu, PMKB pMkbNaechster);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                       MODULGLOBALE VARIABLEN                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL PSTR pstrFnEin_m = "MnuEinrichten()";


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
PMKB MnuEinrichten( WORD wMenuNr, PITEM pItem)
{
    PMKB     pMkb;                                  /* Zeiger auf MKB       */
    REGISTER wMaxLaenge;                            /* lngstes Men-Item   */

    PITEM    pItemTmp;

    if ((pMkb=(PMKB)UtlMalloc(sizeof(MKB)))==NULL)  /* Speicher fr MKB     */
        i_Fehler(MNU_KEIN_SPEICHER,                 /* allokieren           */
                 pstrFnEin_m,
                 __FILE__, __LINE__);

    i_InitVars();

    if (aMenus_g[wMenuNr].wStatus.wHzeile == 1)     /* Flag initialisieren  */
        ;                                           /* Hilfszeilen da, ja   */
    else                                            /* oder nein            */
        aMenus_g[wMenuNr].wStatus.wHzeile = 0;


    pMkb->wMkbsign     = MKBSIGNATUR;               /* Signatur eintragen   */
    pMkb->wFensterId   = pItem[0].wOption;          /* Id in MKB eintragen  */
    pMkb->item         = pItem;                     /* Adresse der Items    */

    pMkb->wTitelBreite = strlen(pItem->pstrText);   /* Lnge des Mentitels */
    if (i_MnuHotkey(pItem->pstrText))               /* berechnen und in MKB */
        pMkb->wTitelBreite--;                       /* eintragen            */

    pItemTmp = pMkb->item;

    if (pItemTmp->pstrHilfstext != NULL)            /* Test ob Hilfe fr    */
        aMenus_g[wMenuNr].wStatus.wHzeile = 1;      /* Mentitel            */

    pItemTmp = pMkb->item + 1;                      /* Text der 1. Option   */

    for( wMaxLaenge=pMkb->wItemAnzahl=0;            /* Anzahl der Items und */
         pItemTmp->pstrText != NULL;                /* Lnge der lngsten   */
         pItemTmp++)                                /* Option ermitteln     */
    {
        if (pItemTmp->pstrHilfstext != NULL)        /* Test ob Hilfe fr    */
            aMenus_g[wMenuNr].wStatus.wHzeile = 1;  /* Menoption           */

         pMkb->wItemAnzahl++;

         if ((strcmp(pItemTmp->pstrText,"TRENNER")) != 0)
         {
            if (strlen(pItemTmp->pstrText) > wMaxLaenge)
            {
                wMaxLaenge = strlen(pItemTmp->pstrText);
                if(i_MnuHotkey(pItemTmp->pstrText))
                     wMaxLaenge--;
            }
         }
    } /* end of for */


    i_MnuInsList(wMenuNr, pMkb);                    /* MKB in verkettete    */
                                                    /* Liste einfgen       */

    if (pMkb->wItemAnzahl == 0)                     /* Hoehe und Breite des */
        pMkb->wHoehe = pMkb->wBreite = 0;           /* Menfensters in MKB  */
    else                                            /* eintragen            */
    {
        pMkb->wHoehe  = pMkb->wItemAnzahl + RAHMENZEILEN;
        pMkb->wBreite = wMaxLaenge + RAHMENSPALTEN;
        if ((pMkb->pHotkeys = (struct tagHK*)UtlMalloc(
                    pMkb->wItemAnzahl * sizeof(struct tagHK))) == NULL)
                i_Fehler(MNU_KEIN_SPEICHER, pstrFnEin_m,
                        __FILE__, __LINE__);

        if ((pMkb->fpwBuffer = (FPWORD) UtlFmalloc(pMkb->wHoehe
                                * pMkb->wBreite
                                * sizeof(WORD))) == 0L)
                i_Fehler(MNU_KEIN_SPEICHER, pstrFnEin_m,
                         __FILE__, __LINE__);

        i_MnuToBuffer(pMkb, wMenuNr, MNU_INIT);     /* Menfenster aufbauen */
    }

    return(pMkb);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuHotkey                    Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR  pStr   String, der ausgewertet werden soll    บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion berprft, ob das Symbol fr         บ
  บ                    den Hotkey (#) im Teststring vorkommt.              บ
  บ                                                                        บ
  บ  Rckgabewert:     JA      wenn Hotkey-Symbol (#) in String vorkommt   บ
  บ                    NEIN    wenn Hotkey-Symbol (#) nicht in String      บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
WORD i_MnuHotkey(PSTR pStr)
{
    return((strchr(pStr, HOTKEY) == 0) ? (NEIN) : (JA));
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuToBuffer                  Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB   pMkb     Zeiger auf Menkontrollblock.       บ
  บ                    WORD   wMenunr  Men, zu dem MKB geh”rt             บ
  บ                    WORD   wModus   MNU_INIT    erster Aufbau des       บ
  บ                                                Menfensters            บ
  บ                                    MNU_AENDERN Menfenster ndern      บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt einen 1:1-Puffer fr ein        บ
  บ                    Men im Speicher ab. Dieser Puffer wird bei         บ
  บ                    Aktivierung eines Mens mit der Funktion            บ
  บ                    VioSb2w() auf den Bildschirm ausgegeben.            บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - cRahmenzeichen_g (R)                              บ
  บ                    - aCS_g (R)                                         บ
  บ                    - wCSInd_g (R)                                      บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_MnuToBuffer(PMKB pMkb, WORD wMenunr, WORD wModus)
{
    REGISTER  rest, temp, i;
    FPWORD    fpwTmpBuf;                            /* lok. Z. auf Puffer   */

    PITEM     pItemTmp;
    WORD      wFattn,                               /* Fensterattr. normal  */
              wFatth,                               /* Fensterattr. Hotkey  */
              wFatti;                               /* Farbe inaktive Opt.  */
    WORD      wPalInd;
    WORD      wRTyp;                                /* Rahmentyp            */
    PSTR      pstrOpt;                              /* lok. Zeiger auf Opt. */
    struct tagHK *pHK;                              /* lok. Zeiger auf Hotk.*/

    if (pMkb->wMkbsign != MKBSIGNATUR)              /* zeigt pMkb auf MKB ? */
        i_Fehler(I_FEHLER_SIGN, "i_MnuToBuffer",
            __FILE__, __LINE__);

    i_InitVars();

                                                    /* Var. initialisieren  */
    fpwTmpBuf = pMkb->fpwBuffer;                    /* Pufferadresse holen  */
    pHK       = pMkb->pHotkeys;                     /* Zg. auf Hotkeystring */
    wPalInd   = aMenus_g[wMenunr].wStatus.wPalette;

    wFattn    = aCS_g[wPalInd].wCs_mf    << 8;       /* Attribute berechnen  */
    wFatth    = aCS_g[wPalInd].wCs_mf_hk << 8;
    wFatti    = aCS_g[wPalInd].wCs_mf_ti << 8;

    switch(aMenus_g[wMenunr].wStatus.wRahmentyp)    /* Rahmentyp ermitteln  */
    {
        case 1:     wRTyp = RT_DDDD; break;
        default:    wRTyp = RT_EEEE; break;
    }

                                                    /* Ausgabeteil          */
    *fpwTmpBuf++ =  wFattn | RZ[wRTyp][OL];         /* linke obere Ecke     */
    temp      = wFattn | RZ[wRTyp][WAAGEO];         /* Zei./Att. berechnen  */
    for(i=pMkb->wBreite-2; i--; )                   /* obere Waagerechte    */
        *fpwTmpBuf++ = temp;                        /* wegschreiben         */
    *fpwTmpBuf++ = wFattn | RZ[wRTyp][OR];          /* rechte obere Ecke    */



    for( pItemTmp = pMkb->item +1;                  /* Optionen einzeln     */
         pItemTmp->pstrText != NULL;                /* ausgeben             */
         pItemTmp++ )
    {
        if (!strcmp(pItemTmp->pstrText,"TRENNER"))  /* ist es ein Trenner ? */
            fpwTmpBuf=i_MnuTrenner(pMkb,
                               fpwTmpBuf, wMenunr); /* Trennlinie einbauen  */

        else                                        /* Menoption einbauen  */
        {
            *fpwTmpBuf++ = wFattn|RZ[wRTyp][SENKL]; /* linker Rahmen        */

            if (wModus == MNU_INIT)                 /* beim ersten Aufruf   */
            {                                       /* Hotkeys-Strk. init.  */
                pHK->wMarker = NEIN;                /* Markierung aus       */
                pHK->wAktiv  = JA;                  /* Option ist aktiv     */
                pHK->wOpt    = pItemTmp->wOption;   /* Optionsnr. eintragen */
                *fpwTmpBuf++ = wFattn | BLANK;      /* ein Leerzeichen      */
            }
            else                                    /* sonst zweiter++      */
            {                                       /* Durchlauf            */
                if (pHK->wMarker == JA)             /* evtl. Marker eintra- */
                    *fpwTmpBuf++ = wFattn | '๛';    /* gen                  */
                else
                    *fpwTmpBuf++ = wFattn | BLANK;  /* ein Leerzeichen      */
            }
            *fpwTmpBuf++ = wFattn | BLANK;          /* zweites Leerzeichen  */
            rest = pMkb->wBreite - 3;               /* restliche Zeichen    */
                                                    /* der Menzeile        */

            pstrOpt = pItemTmp->pstrText;           /* Zeiger auf Mentext  */

            for (; rest>1;rest--)                   /* 1 Zeichen aufsparen  */
            {
                if (*pstrOpt)                       /* noch im Mentext ?   */
                {
                    if (*pstrOpt == HOTKEY)         /* Zeichen fr Hotkey ? */
                    {
                        pstrOpt++;                  /* Zeichen berspringen */
                        if (wModus != MNU_INIT)
                        {
                            if (pHK->wAktiv == NEIN)
                                *fpwTmpBuf++ = wFatti | *pstrOpt++;
                            else
                                *fpwTmpBuf++ = wFatth | *pstrOpt++;
                        }
                        else
                        {
                            *fpwTmpBuf++ = wFatth | *pstrOpt;
                            pHK->wKey = UtlGross(*pstrOpt);
                            if (UtlIsUmlaut(pHK->wKey) == NEIN)
                                pHK->wKey = UtlAltCode(pHK->wKey);
                            *pstrOpt++;
                        }

                    }
                    else
                    {
                        if (pHK->wAktiv == NEIN)
                            *fpwTmpBuf++ = wFatti| *pstrOpt++; /* norm. Zeichen  */
                        else
                            *fpwTmpBuf++ = wFattn| *pstrOpt++; /* norm. Zeichen  */
                    }
                }
                else                                       /* Rest Blanks    */
                    *fpwTmpBuf++ =  wFattn | BLANK;
            }
            *fpwTmpBuf++ = wFattn|RZ[wRTyp][SENKR]; /* rechter Rahmen        */
            pHK++;
        }                                           /* puh Fenster fertig !! */
    }                                               /* alle Items bearbeitet */

    *fpwTmpBuf++ = wFattn | RZ[wRTyp][UL];          /* linke untere Ecke     */
    temp         = wFattn | RZ[wRTyp][WAAGEU];      /* Zei./Att. berechnen   */
    for(i=pMkb->wBreite-2; i--; )                   /* untere Waagerechte    */
        *fpwTmpBuf++ = temp;                        /* wegschreiben          */
    *fpwTmpBuf = wFattn | RZ[wRTyp][UR];            /* rechte untere Ecke    */

    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuTrenner                    Datum: 25.10.88   ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ   Parameter:        MKB      *pm     Zeiger auf Menkontrollblock des  บ
  บ                                      Mens, fr das die Linie          บ
  บ                                      gezeichnet werden soll.           บ
  บ                                                                        บ
  บ                     FPWORD fpwPuffer Adresse des Puffers, ab der die   บ
  บ                                      Linie geschrieben werden soll.    บ
  บ                                                                        บ
  บ   Beschreibung:     MNLINIE schreibt ab der bergebenen Position des   บ
  บ                     Puffers eine Trennlinie und die zugeh”rigen        บ
  บ                     Rahmenzeichen.                                     บ
  บ                                                                        บ
  บ   Rckgabewert:     FPWORD  Zeiger auf nchste Schreibposition         บ
  บ                                                                        บ
  บ   Benutzte globale                                                     บ
  บ   Variablen (R/W):  - aCS_g (R)                                        บ
  บ                     - wCSInd_g (R)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
FPWORD i_MnuTrenner(PMKB pMkb, FPWORD fpwTmpBuf, WORD wMenuNr)
{
    REGISTER wFatt,          /* erhlt einmalige Berechnung des Attributes  */
             wAnz,           /* erhlt Anzahl der auszugebenden Zeichen     */
             wTmp;           /* erhlt einmalige Berechnung von Zei/Att     */
    CHAR acStriche[4];       /* erhlt ben”tigte Zeichen                    */

    switch(aMenus_g[wMenuNr].wStatus.wRahmentyp)    /* Rahmentyp auswerten  */
    {
        case 0:     strcpy(acStriche, "รฤด");       /* ben”tigte Zeichen    */
                    break;                          /* in Array acStriche   */
        case 1:     strcpy(acStriche, "วฤถ");       /* laden.               */
                    break;
    }

    wFatt
      = aCS_g[aMenus_g[wMenuNr].wStatus.wPalette].wCs_mf << 8;     /* Attribut ermitteln   */
    *fpwTmpBuf++ = wFatt | acStriche[0];            /* linker Rahmen        */
    wTmp         = wFatt | acStriche[1];            /* 1x Zeichen berechnen */
    for (wAnz=pMkb->wBreite-2; wAnz>0; wAnz--)      /* Trennlinie in Puffer */
        *fpwTmpBuf++ = wTmp;                        /* schreiben            */
    *fpwTmpBuf++ = wFatt | acStriche[2];            /* rechter Rahmen       */

    return((FPWORD) fpwTmpBuf);                     /* neue Schreibposition */
}                                                   /* zurckgeben          */








/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ Funktionsname:    i_MnuInsList                   Datum: 25.10.88       บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ Parameter:        MKB  *pm    Zeiger auf den Menkontrollblock, der    บ
  บ                               in die doppelt verkettete Liste auf-     บ
  บ                               genommen werden soll.                    บ
  บ                                                                        บ
  บ Beschreibung:     Diese Funktion fgt die neue Struktur vom Daten-     บ
  บ                   typ MKB in die doppelt verkettete Liste ein. Wenn    บ
  บ                   die Liste nicht existiert, wird sie neu angelegt.    บ
  บ                                                                        บ
  บ Rckgabewert:     Diese Funktion hat keinen Rckgabewert.              บ
  บ                                                                        บ
  บ Benutzte globale                                                       บ
  บ Variablen (R/W):  MKB  *startmkb (R/W)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ           Autoren: Rainer G. Haselier und Klaus Fahnenstich            บ
  บ    (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen      บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_MnuInsList(WORD wMenuNr, PMKB pMkbNeu)
{
    PMKB pMkbStart = aMenus_g[wMenuNr].pMkbStart;
    PMKB pMkbTmp;

    if (aMenus_g[wMenuNr].pMkbStart == NULL)        /* erstes Listenelement */
    {
        pMkbNeu->pNaechster = pMkbNeu;
        pMkbNeu->pVoriger   = pMkbNeu;
        aMenus_g[wMenuNr].pMkbStart = pMkbNeu;
        return;
    }

    if(pMkbNeu->wFensterId < pMkbStart->wFensterId) /* neues 1. Element ?   */
    {
        i_MnuSetzeZeiger(pMkbStart->pVoriger,       /* einfgen             */
                         pMkbNeu,
                         pMkbStart);
        aMenus_g[wMenuNr].pMkbStart = pMkbNeu;      /* und neues merken     */
    }

    else if (pMkbNeu->wFensterId >                  /* neues letztes Elem.? */
             pMkbStart->pVoriger->wFensterId)
        i_MnuSetzeZeiger(pMkbStart->pVoriger,       /* einfgen             */
                         pMkbNeu,
                         pMkbStart);
    else
    {

        pMkbTmp = pMkbStart;                        /* Position suchen      */
        do
        {
            if ( pMkbTmp->wFensterId == pMkbNeu->wFensterId)
                i_Fehler(I_FEHLER_DOPPEL_ID, pstrFnEin_m,
                         __FILE__, __LINE__);
            pMkbTmp = pMkbTmp->pNaechster;
        } while( pMkbTmp->wFensterId <= pMkbNeu->wFensterId );

        i_MnuSetzeZeiger(pMkbTmp->pVoriger,         /* einfgen             */
                         pMkbNeu,
                         pMkbTmp);
    }
    return;
}


MGLOBAL
VOID i_MnuSetzeZeiger(PMKB pMkbVoriger, PMKB pMkbNeu, PMKB pMkbNaechster)
{
    if ( pMkbVoriger->pNaechster != pMkbNaechster ||
         pMkbNaechster->pVoriger != pMkbVoriger )
        i_Fehler(I_FEHLER_KETTE_PUTT, pstrFnEin_m,
                 __FILE__, __LINE__);

    pMkbVoriger->pNaechster = pMkbNeu;
    pMkbNeu->pVoriger       = pMkbVoriger;
    pMkbNeu->pNaechster     = pMkbNaechster;
    pMkbNaechster->pVoriger = pMkbNeu;
}

