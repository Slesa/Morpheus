/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        imnuutil.c                     Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Die Funktionen dieser Datei dienen zur Untersttzung der internen     บ
  บ  Steuerung des Menmanagers.                                           บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ   (c) copyright 1988,1989 Markt & Technik Verlag AG, Haar bei Mnchen  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>
#include <string.h>
#include <ctools.h>


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                  BERGABEKONSTANTEN AN i_MnuBuffern()                  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define RESTORE 30
#define SICHERN 31
#define ZEIGEN  32

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MAKRO FR i_MnuBalken()                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/* i: rel. Fensterzeile */
#define IST_TRENNER(p,i) ( (p)->item[(i)].wOption == NULL  && \
                           (p)->item[(i)].pstrHilfstext == NULL && \
                           strcmp((p)->item[(i)].pstrText,"TRENNER") == 0 )

#define HZ_LOESCHEN()    VioSwza(0,24,80,1,' ',  \
                         aCS_g[aMenus_g[wAktMnu_g].wStatus.wPalette].wCs_hz)

#define HZ_SCHREIBEN(s)  VioSsa(0,24,s,  \
                         aCS_g[aMenus_g[wAktMnu_g].wStatus.wPalette].wCs_hz)

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT MENUSTATUS MS_g;               /* Zustand des Menmanagers           */
IMPORT COLORSET   aCS_g[];            /* Array der Farbpaletten             */
IMPORT WORD       wMausda_g;          /* Maus im System aktiviert           */
IMPORT MENU       aMenus_g[];         /* Array der MENU-Strukturen          */
IMPORT WORD       wAktMnu_g;          /* aktueller Index auf Men-Array     */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ               PROTOTYPEN MODULGLOBALE FUNKTIONEN                       บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL VOID i_MnuBuffern (PMKB, FPWORD, WORD );
MGLOBAL PMKB i_NeuerMkb   (PMKB, SWORD,  WORD );
MGLOBAL VOID i_Balken     (PMKB, WORD , WORD );
MGLOBAL VOID i_MnuTitelStriche  (PMKB);

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuBalken                    Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB   pMkb        Zeiger auf Menkontrollblock     บ
  บ                                                                        บ
  บ                    SWORD  swRichtung  steuert die Bewegungsrichtung    บ
  บ                                       <  0  nach oben                  บ
  บ                                       == 0  keine Bewegung             บ
  บ                                       >  0  nach unten                 บ
  บ                                                                        บ
  บ                    WORD   wModus      steuert die Sichtbarkeit         บ
  บ                                       AUS      Balken ausschalten      บ
  บ                                       EIN_REL  Balken relativ posit.   บ
  บ                                       EIN_ABS  Balken absolut posit.   บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion wird der Auswahlbalken inner-   บ
  บ                    halb eines Menfensters bewegt.                     บ
  บ                    Im Fenster befindliche Trenner werden ber-         บ
  บ                    sprungen.                                           บ
  บ                    Die genauere Wirkungsweise der Funktion hngt       บ
  บ                    davon ab, ob der Balken relativ oder absolut        บ
  บ                    positioniert werden soll.                           บ
  บ                    Bei relativer Positionierung gibt swRichtung        บ
  บ                    die Richtung und Entfernung an, in die der          บ
  บ                    Balken bewegt werden soll.                          บ
  บ                    Bei absoluter Positionierung wird die Bildschirm-   บ
  บ                    zeile bergeben.                                    บ
  บ                    Die Funktion bercksichtigt eine Maus im System.    บ
  บ                                                                        บ
  บ                    Die Funktion trgt die Position des Balkens in      บ
  บ                    das Strukturelement wBalPos des MKB ein.            บ
  บ                                                                        บ
  บ                    Bei der bergabe von AUS wird der Balken an der     บ
  บ                    alten Position gel”scht. Der Parameter swRichtung   บ
  บ                    bleibt dann wirkungslos.                            บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation                             บ
  บ                          0 == kein Fehler                              บ
  บ                          sonst Fehler                                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wMausda_g                                           บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD i_MnuBalken(PMKB pMkb, SWORD swRichtung, WORD wModus)
{
    if (pMkb->wMkbsign != MKBSIGNATUR)
        i_Fehler(I_FEHLER_SIGN,
                 "i_MnuBalken()", __FILE__, __LINE__);

    switch (wModus)
    {

        case AUS:
             if ( MS_g.wBalken == 1 )               /* Balken sichtbar      */
                i_Balken(pMkb,pMkb->wBalPos,AUS);   /* alten Balken aus     */
             else
                return(3);
             break;

        case EIN_REL:
             if (swRichtung==0 || MS_g.wBalken==0)
                 break;                             /* switch() verlassen   */

             i_Balken(pMkb,pMkb->wBalPos,AUS);      /* alten Balken aus     */

             if (swRichtung >0)                     /* nach unten bewegen   */
             {
                 if (swRichtung > pMkb->wItemAnzahl)/* maximal einmal rum   */
                     swRichtung = pMkb->wItemAnzahl;

                 do
                 {
                     pMkb->wBalPos++;
                     if (pMkb->wBalPos > pMkb->wItemAnzahl)
                         pMkb->wBalPos = 1;
                     if (IST_TRENNER(pMkb,pMkb->wBalPos))
                         ;
                     else
                         swRichtung--;

                 } while (swRichtung > 0);
             }
             if (swRichtung <0)                     /* nach oben bewegen    */
             {
                 if (-swRichtung>pMkb->wItemAnzahl) /* maximal einmal rum   */
                     swRichtung = -pMkb->wItemAnzahl;
                 do
                 {
                     pMkb->wBalPos--;
                     if (pMkb->wBalPos == 0)
                         pMkb->wBalPos = pMkb->wItemAnzahl;
                     if (IST_TRENNER(pMkb,pMkb->wBalPos))
                         ;
                     else
                         swRichtung++;

                 } while (swRichtung < 0);
             }

             i_Balken(pMkb,pMkb->wBalPos,EIN);      /* Balken einschalten   */
             break;

        case EIN_ABS:
             swRichtung -= FENSTERZEILE;            /* Angabe relat. machen */
             if (swRichtung <= 0 ||                 /* Bereichsberprfung  */
                 swRichtung > pMkb->wItemAnzahl)
                return(1);                          /* Zeile liegt nicht im */
                                                    /* Menfenster          */
             if (IST_TRENNER(pMkb,swRichtung))
                return(2);                          /* In der Zeile ist ein */
                                                    /* Trenner              */

             if (pMkb->wBalPos != 0)                /* Anfangszustand be-   */
                i_Balken(pMkb,pMkb->wBalPos,AUS);   /* rcksichtigen        */
             i_Balken(pMkb,swRichtung,EIN);         /* Balken einschalten   */

             break;
        default:
             break;
    }
    return(0);
}








/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_Balken                       Datum: 10.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB  pMkp     Zeiger auf den Menkontrollblock     บ
  บ                    WORD  wZeile   relative Fensterzeile                บ
  บ                    WORD  wModus   EIN / AUS                            บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion schaltet den Balkencursor in der       บ
  บ                    gewnschten Zeile ein oder aus.                     บ
  บ                    Anschlieแend wird der Zustand des Balkens in die    บ
  บ                    Variable MS_g.Balken eingetragen. Die Position      บ
  บ                    des Balkens wird in den MKB relativ zu der Text-    บ                                                                 บ
  บ                    konstanten FENSTERZEILE eingetragen. Das Struktur-  บ
  บ                    element wBalIndex wird aktualisiert.                บ
  บ                                                                        บ
  บ                    Die Funktion nimmt bei keinem Parameter eine Be-    บ
  บ                    reichsberprfung vor!!                             บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - MS_g      (R/W)                                   บ
  บ                    - aCS_g      (R)                                    บ
  บ                    - aMenus_g   (R)                                    บ
  บ                    - wAktMnu_g  (R)                                    บ
  บ                    - wMausda_g  (R)                                    บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_Balken( PMKB pMkb, WORD wZeile, WORD wModus)
{
    REGISTER z;
    WORD wAbsS, wAbsZ;                              /* absolute Koordinaten */
    WORD wAttrFenster,                              /* Attribute            */
         wAttrText,
         wAttrHotkey;
    WORD wIndex;                                    /* Index der Palette    */
    WORD wMausStatus;
    PSTR pstrTmp;
    struct tagHK *pHK;                              /* lok. Zeiger auf Hotk.*/

    wIndex = aMenus_g[wAktMnu_g].wStatus.wPalette;
    wAttrFenster = aCS_g[wIndex].wCs_mf;
    wAbsZ = wZeile + FENSTERZEILE;                  /* absol. Zeilenangabe  */

     if (wMausda_g)
        wMausStatus = MsmCursorOff();               /* Mauscursor aus       */

    if ( wModus == AUS )                            /* Balken l”schen ?     */
    {
        if(aMenus_g[wAktMnu_g].wStatus.wHzeile==1)  /* Hilfszeile l”schen   */
            HZ_LOESCHEN();

        pHK = pMkb->pHotkeys + pMkb->wBalIndex;
        if ( pHK->wAktiv == 1 )                     /* Option aktiv ?       */
        {
            wAttrText   = wAttrFenster;             /* Attribute festlegen  */
            wAttrHotkey = aCS_g[wIndex].wCs_mf_hk;
        }
        else
        {
            wAttrText   = aCS_g[wIndex].wCs_mf_ti;
            wAttrHotkey = wAttrText;
        }

        wAbsS = pMkb->wSpalte+1;

        VioSwa(wAbsS, wAbsZ, 2, 1, wAttrFenster);   /* Die ersten 2 Zeichen */
                                                    /* restaurieren         */
        for ( wAbsS+=2;
              wAbsS < pMkb->wSpalte+pMkb->wBreite-1;
              wAbsS++)
            if ( VioLz(wAbsS, wAbsZ) == ' ')        /* Blank gefunden ?     */
                VioSa(wAbsS, wAbsZ, wAttrFenster);
            else
                VioSa(wAbsS, wAbsZ, wAttrText);

        for ( wAbsS = pMkb->wSpalte+3,              /* Hotkey markieren     */
              pstrTmp=(pMkb->item+wZeile)->pstrText;
              *pstrTmp;
              wAbsS++, pstrTmp++)
            if (*pstrTmp == '#')                    /* Hotkey gefunden ?    */
                VioSa(wAbsS, wAbsZ, wAttrHotkey);

        MS_g.wBalken = 0;                           /* Statusflag l”schen   */
    }

    if (wModus == EIN)                              /* Einschalten geford.  */
    {
        for ( z=1, pMkb->wBalIndex=0;               /* Index des Items be-  */
              z < wZeile;                           /* stimmen              */
              z++)                                  /* ( auf pHotkeys )     */
            if ( IST_TRENNER(pMkb, z))
                ;
            else
                pMkb->wBalIndex++;

        pHK = pMkb->pHotkeys + pMkb->wBalIndex;

        if ( pHK->wAktiv == 1)                      /* Ist Option aktiv ?   */
            wAttrText   = aCS_g[wIndex].wCs_mf_ca;  /* Attribute festlegen  */
        else
            wAttrText   = aCS_g[wIndex].wCs_mf_ci;

        VioSwa(pMkb->wSpalte+1, wAbsZ,
               pMkb->wBreite-2, 1,
               wAttrText);

        pMkb->wBalPos = wZeile;                     /* markierte Zeile ein- */
                                                    /* tragen               */

        if ( aMenus_g[wAktMnu_g].wStatus.wHzeile == 1 &&
             pMkb->item[pMkb->wBalPos].pstrHilfstext != NULL)
            HZ_SCHREIBEN(pMkb->item[pMkb->wBalPos].pstrHilfstext);
        MS_g.wBalken = 1;                           /* Statusflag setzen    */
    }

    if (wMausda_g && wMausStatus == MSM_WAR_AN)
        MsmCursorOn();

    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuTitel                     Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB  *ppMkb       Zeiger auf Zeiger des            บ
  บ                                       Menkontrollblocks               บ
  บ                                                                        บ
  บ                    SWORD  swRichtung  steuert die Bewegungsrichtung    บ
  บ                                       <  0  nach oben                  บ
  บ                                       == 0  keine Bewegung             บ
  บ                                       >  0  nach unten                 บ
  บ                                                                        บ
  บ                    WORD   wModus      steuert die Sichtbarkeit         บ
  บ                                       AUS      Titel ausschalten       บ
  บ                                       EIN_REL  Titel relativ posit.    บ
  บ                                       EIN_ABS  Titel absolut posit.    บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion wird der Auswahlbalken inner-   บ
  บ                    halb der Menzeile bewegt.                          บ
  บ                    Die genauere Wirkungsweise der Funktion hngt       บ
  บ                    davon ab, ob der Balken relativ oder absolut        บ
  บ                    positioniert werden soll.                           บ
  บ                    Bei relativer Positionierung gibt swRichtung        บ
  บ                    die Richtung und Entfernung an, in die der          บ
  บ                    Balken bewegt werden soll.                          บ
  บ                    Bei absoluter Positionierung wird die Bildschirm-   บ
  บ                    spalte bergeben.                                   บ
  บ                    Die Funktion bercksichtigt eine Maus im System.    บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation                             บ
  บ                          0 == kein Fehler                              บ
  บ                          sonst Fehler                                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wMausda_g   (R)                                     บ
  บ                    wMS_g       (R/W)                                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD i_MnuTitel (PMKB *ppMkb, SWORD swRichtung, WORD wModus)
{
    PMKB pMkb;                                      /* Zeiger auf MKB       */
    WORD wMausStatus = MSM_WAR_AUS;                 /* Mauszeiger an/aus ?  */

    WORD wZeile,                                    /* Position Mauszeiger  */
         wDummy;                                    /* fr Aufruf MsmGet... */


    pMkb = *ppMkb;                                  /* lokalen Zeiger laden */

    if (pMkb->wMkbsign != MKBSIGNATUR)              /* MKB testen           */
        i_Fehler(I_FEHLER_SIGN,"i_MnuTitel()",      /* im Fehlerfalle       */
                 __FILE__, __LINE__);               /* abbrechen            */

    if (wMausda_g)                                  /* wenn Maus da         */
    {
        MsmGetPosition(&wDummy, &wDummy, &wZeile);  /* Position holen       */
        if (wZeile == 0)                            /* wenn in Menzeile    */
            wMausStatus = MsmCursorOff();           /* Mauszeiger aus       */
    }


    switch (wModus)
    {
        case AUS:
            VioSb2w(0,0,80,1,                       /* Titel l”schen        */
                    aMenus_g[wAktMnu_g].fpwMzBuffer);
            if (MS_g.wFenster == JA)
                i_MnuTitelStriche(pMkb);
            if (aMenus_g[wAktMnu_g].wStatus.wHzeile == 1)
                HZ_LOESCHEN();
            MS_g.wTitel = NEIN;                     /* Flag setzen          */
            break;

        case EIN_ABS:                               /* Markierung beliebig  */
        case EIN_REL:                               /* positionieren        */
            if (MS_g.wTitel == JA)                  /* wenn Titel da ist    */
                VioSb2w(0,0,80,1,                   /* Titel l”schen        */
                    aMenus_g[wAktMnu_g].fpwMzBuffer);

            if (aMenus_g[wAktMnu_g].wStatus.wHzeile == 1)
                HZ_LOESCHEN();

            if (swRichtung != 0)
                pMkb = i_NeuerMkb(pMkb,             /* neuen PMKB holen     */
                                  swRichtung,
                                  wModus);

            VioSwa(pMkb->wTitelSpalte, 0,           /* Markierung auf Titel */
                   pMkb->wTitelBreite, 1,           /* ausgeben             */
                   aCS_g[aMenus_g[wAktMnu_g].wStatus.wPalette].wCs_mz_c);
            if (aMenus_g[wAktMnu_g].wStatus.wHzeile == 1 &&
                pMkb->item->pstrHilfstext != NULL)
                    HZ_SCHREIBEN(pMkb->item->pstrHilfstext);

            MS_g.wTitel = JA;                       /* Flag setzen          */
            break;
    }

    if (wMausda_g && wMausStatus == MSM_WAR_AN)     /* wenn Maus da und     */
        MsmCursorOn();                              /* an war, Zeiger ein   */

    *ppMkb = pMkb;                                  /* neuen PMKB zurck    */
    return(0);
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuFenster                   Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB  *ppMkb       Zeiger auf Zeiger des            บ
  บ                                       Menkontrollblocks               บ
  บ                                                                        บ
  บ                    SWORD  swRichtung  steuert die Bewegungsrichtung    บ
  บ                                       <  0  nach oben                  บ
  บ                                       == 0  keine Bewegung             บ
  บ                                       >  0  nach unten                 บ
  บ                                                                        บ
  บ                    WORD   wModus      steuert die Sichtbarkeit         บ
  บ                                       AUS      Titel ausschalten       บ
  บ                                       EIN_REL  Titel relativ posit.    บ
  บ                                       EIN_ABS  Titel absolut posit.    บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion kann ein beliebiges Men-       บ
  บ                    fenster angezeigt werden.                           บ
  บ                    Die genauere Wirkungsweise der Funktion hngt       บ
  บ                    davon ab, ob die Information ber das anzuzeigende  บ
  บ                    Menfenster relativ oder absolut bergeben wird.    บ
  บ                                                                        บ
  บ                    ber den Zeiger ppMkb wird der neue Menkontroll-   บ
  บ                    block an die aufrufende Funktion zurckgegeben.     บ
  บ                                                                        บ
  บ                    Die Funktion bercksichtigt eine Maus im System.    บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation                             บ
  บ                          0 == kein Fehler                              บ
  บ                          sonst Fehler                                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wMausda_g  (R)                                      บ
  บ                    wMS_g      (R/W)                                    บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD i_MnuFenster(PMKB *ppMkb, SWORD swRichtung, WORD wModus)
{
    STATIC FPWORD fpwBuffer= 0L;                    /* Puffer fr alten     */
                                                    /* Bildschirnm          */
    WORD wMausStatus;                               /* Maus im System       */
    PMKB pMkb;                                      /* Zeiger auf MKB       */

    pMkb = *ppMkb;                                  /* lokalen Zeiger laden */

    if (pMkb->wMkbsign != MKBSIGNATUR)              /* MKB testen           */
        i_Fehler(I_FEHLER_SIGN, "i_MnuFenster()",   /* im Fehlerfalle       */
                 __FILE__, __LINE__);               /* abbrechen            */

    if (fpwBuffer == 0L)                            /* wenn kein Puffer da  */
    {
        fpwBuffer=UtlFmalloc(2000 * sizeof(WORD));  /* allokieren           */
        if (fpwBuffer == 0L)                        /* wenn kein Speicher   */
            i_Fehler(I_FEHLER_MEM, "i_MnuFenster",  /* mehr frei            */
                      __FILE__, __LINE__);          /* mehr frei            */
    }


    if (wMausda_g)                                  /* wenn Maus im System  */
        wMausStatus = MsmCursorOff();               /* Mauszeiger aus       */


    switch(wModus)                                  /* Modus auswerten      */
    {
        case AUS:
            if (MS_g.wFenster == JA)                /* wenn Fenster da      */
            {
                MS_g.wFenster = NEIN;               /* Flag zurcksetzen    */
                i_MnuTitel(&pMkb, 0, AUS);
                i_MnuBalken(pMkb, 0, AUS);
                i_MnuBuffern(pMkb,                  /* alten Bildschirm     */
                             fpwBuffer,             /* wieder herstellen    */
                             RESTORE);
            }
            break;

        case EIN_ABS:                               /* ein Fenster zeigen   */
        case EIN_REL:
            if (MS_g.wFenster == JA)                /* wenn anderes Fenster */
            {                                       /* da, zuerst           */
                i_MnuBalken(pMkb, 0, AUS);          /* Balken ausschalten   */
                i_MnuBuffern(pMkb,                  /* und Bildschirm       */
                             fpwBuffer,             /* restaurieren         */
							 RESTORE);
				MS_g.wFenster = NEIN;
            }
			i_MnuTitel(&pMkb, 0, AUS);

            if (swRichtung != 0)
            {
                pMkb = i_NeuerMkb(pMkb,             /* neuen PMKB holen     */
                                  swRichtung,
                                  wModus);
                *ppMkb = pMkb;                      /* neuen PMKB laden     */
            }
            i_MnuBuffern(pMkb, fpwBuffer,           /* Untergrund zuerst    */
                        SICHERN);                   /* sichern              */
            i_MnuBuffern(pMkb, 0L, ZEIGEN);         /* und Fenster zeigen   */
			MS_g.wFenster = JA;                     /* Flag setzen          */
            break;
    }

    if (wMausda_g && wMausStatus == MSM_WAR_AN)     /* wenn Maus da und an  */
        MsmCursorOn();                              /* war, Zeiger ein      */



    return(0);                                      /* und zrck           */
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuBuffern                   Datum: 07.01.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB   pMkb     Zeiger Menkontrollblock            บ
  บ                    FPWORD fpwBuf   Zeiger auf Sicherungsbuffer         บ
  บ                    WORD   wModus   ZEIGEN/RESTORE/SICHERN              บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ist eine Hilfsfunktion von           บ
  บ                    i_MnuFenster(). Hier werden die Bildschirmaus-      บ
  บ                    gaben und die Sicherung des Untergrundes durch-     บ
  บ                    gefhrt.                                            บ
  บ                                                                        บ
  บ                    ZEIGEN   Das Menfenster dessen MKB bergeben       บ
  บ                             wurde, wird angezeigt. Die Trennstriche    บ
  บ                             auf der Menzeile werden ausgegeben und    บ
  บ                             eventuell ein Schatten ausgegeben.         บ
  บ                    RESTORE  Der Untergrund unter einem Menfenster     บ
  บ                             wird wiederhergestellt und damit das       บ
  บ                             Menfenster vom Bildschirm genommen.       บ
  บ                    SICHERN  Der Untergrund, auf den ein neues          บ
  บ                             Fenster kommt, wird gesichert.             บ
  บ                                                                        บ
  บ  Rckgabewert:     keiner                                              บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - aMenus_g    (R)                                   บ
  บ                    - wAktMnu_g   (R)                                   บ
  บ                    - aCS_g       (R)                                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_MnuBuffern(PMKB pMkb, FPWORD fpwBuf, WORD wModus)
{

    WORD wBreite, wHoehe;

    if (wModus != ZEIGEN)                           /* wenn Fenster restau- */
    {                                               /* riert/gesichert      */
        wBreite = pMkb->wBreite;                    /* werden soll          */
        wHoehe  = pMkb->wHoehe;

        if (aMenus_g[wAktMnu_g].wStatus.wSchatten   /* evtl. Schatten       */
            == JA)                                  /* bercksichtigen      */
        {
            wBreite += 2;
            wHoehe  += 1;
        }
    }

    switch(wModus)
    {
        case RESTORE:                               /* Untergrund unter     */
            VioSb2w(pMkb->wSpalte, 1,               /* Menfenster wieder   */
                    wBreite,                        /* herstellen           */
                    wHoehe,
                    fpwBuf);
            break;

        case SICHERN:                               /* Untergrund unter     */
            VioSw2b(pMkb->wSpalte, 1,               /* Menfenster          */
                    wBreite,                        /* in Puffer kopieren   */
                    wHoehe,
                    fpwBuf);
            break;


        case ZEIGEN:
            VioSb2w(pMkb->wSpalte, 1,               /* Menfenster ausgeben */
                     pMkb->wBreite,
                     pMkb->wHoehe,
                     pMkb->fpwBuffer);
            i_MnuTitelStriche(pMkb);                /* Trennmarkierungen    */

                                                    /* wenn Schatten aktiv  */
            if (aMenus_g[wAktMnu_g].wStatus.wSchatten == JA)
                UtlZeigeSchatten(pMkb->wSpalte, 1,  /* den ausgeben         */
                                 pMkb->wBreite,
                                 pMkb->wHoehe);
            break;
    }

}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuTitelStriche              Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB pMkb Zeiger auf Menkontrollblock              บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt in Abhngigkeit von der         บ
  บ                    aktiven Farbpalette und dem fr das Men            บ
  บ                    festgelegten Rahmentyp Trennstriche neben dem       บ
  บ                    Mentitel und auf dem oberen Fensterrahmen aus.     บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  aMenus_g, aCS_g, wAktMnu_g  (R)                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_MnuTitelStriche(PMKB pMkb)
{
    STATIC CHAR acStriche[] = "มฯ";                 /* ben”tigte Zeichen     */
    WORD wSpalte, wRTyp, wAttr;                     /* Trennlinie auf Men- */
                                                    /* zeile und am oberen  */
                                                    /* Rahmen ergnzen      */
    wRTyp = aMenus_g[wAktMnu_g].wStatus.wRahmentyp;
    wSpalte = pMkb->wTitelSpalte+
              pMkb->wTitelBreite;

    wAttr = aCS_g[aMenus_g[wAktMnu_g].wStatus.wPalette].wCs_mz;
    VioSza( pMkb->wTitelSpalte-1, 0,'ณ', wAttr);
    VioSza( wSpalte, 0, 'ณ', wAttr);

    wAttr = aCS_g[aMenus_g[wAktMnu_g].wStatus.wPalette].wCs_mf;
    VioSza( pMkb->wTitelSpalte-1, 1, acStriche[wRTyp], wAttr);
    if (pMkb->item->wOption == RECHTSBUENDIG)
        VioSza( wSpalte, 1, 'ด', wAttr);
    else
        VioSza( wSpalte, 1, acStriche[wRTyp], wAttr);
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuNeuerMkb                  Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB    pMkb       Zeiger auf Zeiger des            บ
  บ                                       Menkontrollblocks               บ
  บ                                                                        บ
  บ                    SWORD  swRichtung  steuert die Bewegungsrichtung    บ
  บ                                       <  0  nach oben                  บ
  บ                                       == 0  keine Bewegung             บ
  บ                                       >  0  nach unten                 บ
  บ                                                                        บ
  บ                    WORD   wModus      steuert die Sichtbarkeit         บ
  บ                                       AUS      Titel ausschalten       บ
  บ                                       EIN_REL  Titel relativ posit.    บ
  บ                                       EIN_ABS  Titel absolut posit.    บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt fr i_MnuTitel() und       บ
  บ                    i_MnuFenster() aus den bergebenen Argumenten       บ
  บ                    fr welchen MKB das Fenster bzw. der Titel ange-    บ
  บ                    zeigt werden soll.                                  บ
  บ                                                                        บ
  บ  Rckgabewert:     PMKB  Zeiger auf neuen Menkontrollblock            บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - aMenus_g    (R)                                   บ
  บ                    - wAktMnu_g   (R)                                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
PMKB i_NeuerMkb(PMKB pMkb, SWORD swRichtung, WORD wModus)
{
    REGISTER i;                                     /* Schleifenvariable    */

    switch(wModus)
    {
        case EIN_ABS:                               /* absolute Position    */
            pMkb = aMenus_g[wAktMnu_g].pMkbStart;   /* beim ersten MKB      */
            swRichtung = abs(swRichtung);           /* anfangen             */
            for (i=0; i < swRichtung; i++)          /* und suchen           */
                pMkb = pMkb->pNaechster;
            break;

        case EIN:
        case EIN_REL:                               /* relative Position    */
            if (swRichtung > 0)                     /* nach vorne suchen    */
                for (i=0; i < swRichtung; i++)      /* verkettete Liste     */
                    pMkb = pMkb->pNaechster;        /* entlang hangeln      */

            else if (swRichtung < 0)                /* nach hinten suchen   */
            {
                swRichtung = abs(swRichtung);       /* in pos. Zahl umwand. */
                for (i=0; i < swRichtung; i++)      /* und suchen           */
                    pMkb = pMkb->pVoriger;
            }
        break;
    }
    return (pMkb);                                  /* gefund. PMKB retour  */
}
