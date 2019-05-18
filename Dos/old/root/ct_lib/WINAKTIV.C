/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinAktivieren                  Datum: 22.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB    pWkb   Zeiger auf den Kontrollblock des     บ
  บ                                   anzuzeigenden Windows.               บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion kann ein Window zum obersten,   บ
  บ                    also aktiven Window gemacht werden. Auf dem Bild-   บ
  บ                    schirm k”nnen 15 Windows gleichzeitig angezeigt     บ
  บ                    werden (1..15) der Bildschirm wird als Window Nr.0  บ
  บ                    betrachtet.                                         บ
  บ                    Die Vorgehensweise ist abhngig vom vorherigen      บ
  บ                    Zustand des Windows. Es wird zwischen 3 Zustnden   บ
  บ                    unterschieden:                                      บ
  บ                                                                        บ
  บ                      1. Das Window ist sichtbar,                       บ
  บ                      2. Das Window ist nicht sichtbar, aber versteckt  บ
  บ                      3. Das Window ist nicht sichtbar und nicht ver-   บ
  บ                         steckt                                         บ
  บ                                                                        บ
  บ                    zu 1)  Zuerst werden alle Windows, die das zu zei-  บ
  บ                           gende Window verdecken vom Bildschirm abge-  บ
  บ                           rumt. Das anzuzeigende Window wird dann     บ
  บ                           entfernt und die abgerumten Windows in der  บ
  บ                           alten Reihenfolge wieder auf den Bildschirm  บ
  บ                           gelegt. Zuletzt wird das zu zeigende Window  บ
  บ                           aufgelegt.                                   บ
  บ                                                                        บ
  บ                    zu 2)  Wenn die maximal erlaubte Anzahl von ange-   บ
  บ                           gezeigten Windows noch nicht erreicht ist,   บ
  บ                           wird das versteckte Fenster als oberstes     บ
  บ                           auf dem Bildschirm angezeigt.                บ
  บ                                                                        บ
  บ                    zu 3)  Wenn die maximale Windowanzahl noch nicht    บ
  บ                           erreicht ist, wird das Window als oberstes   บ
  บ                           auf dem Bildschirm angezeigt. Um den Unter-  บ
  บ                           grund zu sichern, wird vorher Speicherplatz  บ
  บ                           fr einen Buffer allokiert.                  บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformationen (OK/ERROR)                บ
  บ                          Im Fehlerfall erhlt ฏwFehler_gฎ eine der     บ
  บ                          folgenden Fehlernummern:                      บ
  บ                                                    - WIN_KEIN_PWKB     บ
  บ                                                    - WIN_LIMIT         บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wFehler_g (W)                                   บ
  บ                      - wAktWin_g (R/W)                                 บ
  บ                      - apWkbSichtbar_g[] (R/W)                         บ
  บ                      - fpwCopyBuffer_g (R/W)                           บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          HEADER - DATEIEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>

#define MemCopy( dst, src, si ) memmove( dst, src, si )

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define WIN_MAX 15                                  /* Anzahl der maximal   */
                                                    /* sichtbaren Windows.  */
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                       Modulglobale Variablen                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL WORD awBit_m[17] = {  0x0001, 0x0002, 0x0004, 0x0008,  /* Bitmasken */
                              0x0010, 0x0020, 0x0040, 0x0080,
                              0x0100, 0x0200, 0x0400, 0x0800,
                              0x1000, 0x2000, 0x4000, 0x8000  };

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          Globale Variablen                             บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

IMPORT  PWKB    apWkbSichtbar_g[16];                /* Array v. Zeigern auf */
                                                    /* WKB der sichtbaren W.*/
IMPORT  WORD    wAktWin_g;                          /* Index des aktiven W. */
                                                    /* in ฏapWkbSichtbar[]ฎ */
IMPORT  FPWORD  fpwCopyBuffer_g;                    /* Zeiger auf 4k-Buffer */

IMPORT  WORD    wS_g;                               /* Die Koordinaten be-  */
IMPORT  WORD    wZ_g;                               /* schreiben die Data-  */
IMPORT  WORD    wB_g;                               /* Area des aktuellen   */
IMPORT  WORD    wH_g;                               /* Windows.             */

IMPORT  WORD    wAttribut_g;                        /* Attribut des Fenster-*/
                                                    /* innneren.            */
IMPORT  WORD    wMausda_g;                          /* 0: keine Maus da     */
                                                    /* 1: Maus vorhanden    */
IMPORT  WORD    wFehler_g;                          /* Nr. des letzten auf- */
                                                    /* getretenen Fehlers   */
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ               Prototypen der modulglobalen Funktionen                  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD i_WinSchnitt(WORD);
WORD i_WinSchaufeln(PWKB);
WORD i_WinVersteckt(PWKB);
WORD i_WinNeu(PWKB);

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinAktivieren( PWKB pWkb )
{
    WORD wReturn, wStatus;

    if (pWkb->wWkbsign != WKBSIGNATUR)              /* Test ob Zeiger noch  */
    {                                               /* auf WKB zeigt.       */
        wFehler_g = WIN_KEIN_PWKB;                  /* Fehlernummer setzen  */
        return (ERROR);                             /* zurck an Aufrufer   */
    }

    if (pWkb == apWkbSichtbar_g[wAktWin_g] )        /* Window schon aktiv   */
        return (OK);

    if ( fpwCopyBuffer_g == 0L )                    /* Ist CopyBuffer schon */
    {                                               /* allokiert worden ?   */
        fpwCopyBuffer_g = UtlFmalloc(0x1000);       /* 4 kByte allokieren   */
        if ( fpwCopyBuffer_g == 0L)
           i_Fehler(I_FEHLER_MEM,                   /* Programm abbrechen   */
                    "WinAktivieren()",
                    __FILE__, __LINE__);
    }

    if (wMausda_g)                                  /* wenn Maus im System, */
        wStatus = MsmCursorOff();                   /* Maus ausschalten.    */
    if ( pWkb->winFlags.wSichtbar )                 /* Zustand 1 (s. o.)    */
            wReturn = i_WinSchaufeln(pWkb);         /* W. nach oben holen   */

    else if ( wAktWin_g < WIN_MAX )                 /* anzeigen m”glich ?   */

        if ( pWkb->winFlags.wVersteckt )            /* Zustand 2 (s. o.)    */
            wReturn = i_WinVersteckt(pWkb);         /* Verst. Window zeigen */
        else                                        /* Zustand 3 (s. o.)    */
            wReturn = i_WinNeu(pWkb);               /* Neues Window zeigen  */
    else                                            /* ฏWIN_MAXฎ erreicht   */
    {
        wFehler_g = WIN_LIMIT;                      /* Fehlernummer setzen  */
        return (ERROR);                             /* zurck an Aufrufer   */
    }
    if (wMausda_g && wStatus == MSM_WAR_AN)         /* wenn Maus sichtbar   */
        MsmCursorOn();                              /* war, Maus anzeigen   */

    return(wReturn);
}

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinSchaufeln                 Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB    pWkb   Zeiger auf den Kontrollblock des     บ
  บ                                   anzuzeigenden Windows.               บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion aktiviert ein sichtbares Window. Dazu  บ
  บ                    werden folgende Schritte abgearbeitet:              บ
  บ                                                                        บ
  บ                       - Index des pWkb fr apWkbSichtbar_g bestimmen   บ
  บ                       - Cursor des alten aktiven Windows sichern       บ
  บ                       - Bestimmung der abzurumenden Windows           บ
  บ                       - Abrumen der ermittelten Windows               บ
  บ                       - Verstecken des zu sichernden Windows           บ
  บ                       - Abgerumte Windows wieder anzeigen             บ
  บ                       - Verstecktes Window wieder sichtbar machen      บ
  บ                       - globale Variablen aktualisieren                บ
  บ                       - Schnittflchen berechnen                       บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation                             บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD i_WinSchaufeln( PWKB pWkb)
{
    REGISTER i,wTemp;
    WORD wIndex, wListe, wMaske;

    if (pWkb->wWkbsign != WKBSIGNATUR)              /* Test ob Zeiger noch  */
    {                                               /* auf WKB zeigt, wenn  */
        wFehler_g = WIN_KEIN_PWKB;                  /* nicht Variable setz. */
        return (ERROR);                             /* und an aufr. Fkt.    */
    }

    wIndex = wAktWin_g;                             /* Index bestimmen      */
    while ( pWkb != apWkbSichtbar_g[wIndex] &&
            wIndex > 0 )
        wIndex--;

    if ( wIndex == 0 )
    {
        wFehler_g = WIN_NICHT_SICHTBAR;
        return (ERROR);
    }

    i_WinSaveCursor();                              /* Cursor des zur Zeit  */
                                                    /* aktiven W. sichern   */

    wListe = awBit_m[wIndex];                       /* Abrumliste initial. */
    wMaske = awBit_m[wIndex+1];                     /* Bitmaske initial.    */
    for (i = wIndex+1; i <= wAktWin_g; i++)         /* nach oben abarbeiten */
    {
        if (wListe & apWkbSichtbar_g[i]->wSchnitte) /* exis. Schnittflche? */
            wListe |= wMaske;                       /* wListe erweitern     */
        wMaske <<= 1;
    }

    if (wListe != awBit_m[wIndex])                  /* exis. Schnittflche? */
    {
        wMaske = awBit_m[wAktWin_g];
        for (i = wAktWin_g; i >= wIndex; i--)       /* von oben abrumen    */
        {
            if (wListe & wMaske)                    /* Soll das Window ab-  */
                i_WinPop(i);                        /* gerumt werden ?     */
            wMaske >>= 1;
        }

        wMaske = awBit_m[wIndex+1];
        for (i = wIndex+1; i <= wAktWin_g; i++)     /* Windows auflegen     */
        {
            if (wListe & wMaske)                    /* Wurde das Window ab- */
                i_WinPush(i);                       /* gerumt ?            */
            wMaske <<= 1;
        }

        i_WinPush(wIndex);                          /* gewnschtes Window   */
    }

    if (pWkb->winFlags.wTRaendern)                  /* Titel o. Rahmen nd.?*/
    {
        UtlZeigeRahmen(pWkb->wSpalte, pWkb->wZeile, /* Rahmen neu anzeigen  */
                       pWkb->wBreite,pWkb->wHoehe,
                       pWkb->winFlags.wRahmentyp,
                       pWkb->wRahmenAttr);

        if (pWkb->pstrTitel != NULL)                /* falls vorhanden, den */
            i_WinZeigeTitel(pWkb);                  /* Titel neu anzeigen   */

        pWkb->winFlags.wTRaendern = 0;
    }

    i_WinInit( pWkb->wSpalte +1, pWkb->wZeile +1,   /* Data-Area des Win-   */
               pWkb->wBreite -2, pWkb->wHoehe -2,   /* dows festlegen       */
               pWkb->wInnenAttr);

    if (pWkb->winFlags.wDAaendern)                  /* Data-Area ndern ?   */
    {
        WinSwa( 0, 0,                               /* neues Attribut geben */
                pWkb->wBreite-2,
                pWkb->wHoehe-2,
                pWkb->wInnenAttr);
        pWkb->winFlags.wDAaendern = 0;
    }

    for (wMaske=i=0; i < wIndex; i++)               /* Maske zum Ausblenden */
         wMaske |= awBit_m[i];

    for (i=wIndex; i < wAktWin_g; i++)              /* Array aktualisieren  */
    {
        apWkbSichtbar_g[i] = apWkbSichtbar_g[i+1];
        wTemp = apWkbSichtbar_g[i]->wSchnitte;
        wTemp = (wTemp & wMaske) |
                ((wTemp>>1) & (~wMaske));
        apWkbSichtbar_g[i]->wSchnitte = wTemp;
    }

    apWkbSichtbar_g[wAktWin_g] = pWkb;              /* neues aktives Window */
    pWkb->wSchnitte = i_WinSchnitt(wAktWin_g);      /* Schnittflchen be-   */
                                                    /* rechnen              */

    i_WinRestoreCursor();                           /* Cursor an alte Pos.  */

    return (OK);
}

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinVersteckt                 Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB    pWkb   Zeiger auf den Kontrollblock des     บ
  บ                                   anzuzeigenden Windows.               บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion zeigt ein vorher verstecktes Window    บ
  บ                    auf dem Bildschirm an. Da sich versteckte Windows   บ
  บ                    im Hintergrund-Buffer (fpwBuffer) befinden, wird    บ
  บ                    der globale ฏCopy-Bufferฎ als Zwischenspeicher be-  บ
  บ                    nutzt. Damit ergibt sich fr die Funktion folgende  บ
  บ                    Vorgehensweise:                                     บ
  บ                                                                        บ
  บ                       - Cursor des alten aktiven Windows sichern       บ
  บ                       - Window in ฏCopy-Bufferฎ kopieren               บ
  บ                       - Hintergrund sichern                            บ
  บ                       - Window auf dem Bildschirm anzeigen             บ
  บ                       - globale Variablen aktualisieren                บ
  บ                       - Schnittflchen berechnen                       บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation                             บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD i_WinVersteckt( PWKB pWkb )

{
    if (pWkb->wWkbsign != WKBSIGNATUR)              /* Test ob Zeiger noch  */
    {                                               /* auf WKB zeigt, wenn  */
        wFehler_g = WIN_KEIN_PWKB;                  /* nicht Variable setz. */
        return (ERROR);                             /* und an aufr. Fkt.    */
    }

    i_WinSaveCursor();                              /* Cursor des zur Zeit  */
                                                    /* aktiven W. sichern   */
    MemCopy( fpwCopyBuffer_g, pWkb->fpwBuffer, 2 * pWkb->wBreite * pWkb->wHoehe );
#ifdef NEVER
    movedata(FP_SEG(pWkb->fpwBuffer),               /* Window zwischen-     */
             FP_OFF(pWkb->fpwBuffer),               /* speichern            */
             FP_SEG(fpwCopyBuffer_g),
             FP_OFF(fpwCopyBuffer_g),
             2 * pWkb->wBreite * pWkb->wHoehe);
#endif

    if (pWkb->winFlags.wSchatten )                  /* Hintergrund sichern  */
        VioSw2b (pWkb->wSpalte, pWkb->wZeile,
                 pWkb->wBreite+2, pWkb->wHoehe+1,
                 pWkb->fpwBuffer);
    else
        VioSw2b (pWkb->wSpalte, pWkb->wZeile,
                 pWkb->wBreite, pWkb->wHoehe,
                 pWkb->fpwBuffer);

    VioSb2w (pWkb->wSpalte, pWkb->wZeile,           /* Window auf dem Bild- */
             pWkb->wBreite, pWkb->wHoehe,           /* schirm anzeigen      */
             fpwCopyBuffer_g);

    if (pWkb->winFlags.wTRaendern)                  /* Titel o. Rahmen nd.?*/
    {
        UtlZeigeRahmen(pWkb->wSpalte, pWkb->wZeile, /* Rahmen neu anzeigen  */
                       pWkb->wBreite,pWkb->wHoehe,
                       pWkb->winFlags.wRahmentyp,
                       pWkb->wRahmenAttr);

        if (pWkb->pstrTitel != NULL)                /* falls vorhanden, den */
            i_WinZeigeTitel(pWkb);                  /* Titel neu anzeigen   */

        pWkb->winFlags.wTRaendern = 0;
    }

    i_WinInit( pWkb->wSpalte +1, pWkb->wZeile +1,   /* Data-Area des Win-   */
               pWkb->wBreite -2, pWkb->wHoehe -2,   /* dows festlegen       */
               pWkb->wInnenAttr);

    if (pWkb->winFlags.wDAaendern)                  /* Data-Area ndern ?   */
    {
        WinSwa( 0, 0,                               /* neues Attribut geben */
                pWkb->wBreite-2,
                pWkb->wHoehe-2,
                pWkb->wInnenAttr);
        pWkb->winFlags.wDAaendern = 0;
    }


    if (pWkb->winFlags.wSchatten)                   /* Window mit Schatten? */
        UtlZeigeSchatten( pWkb->wSpalte,
                          pWkb->wZeile,
                          pWkb->wBreite,
                          pWkb->wHoehe);



    pWkb->winFlags.wSichtbar  = 1;                  /* WKB aktualisieren    */
    pWkb->winFlags.wVersteckt = 0;
    pWkb->winFlags.wTRaendern = 0;
    pWkb->winFlags.wDAaendern = 0;

    apWkbSichtbar_g[++wAktWin_g] = pWkb;            /* neues aktives Window */
    pWkb->wSchnitte = i_WinSchnitt(wAktWin_g);      /* Schnittflchen be-   */
                                                    /* rechnen              */


    i_WinRestoreCursor();                           /* Cursor an alte Pos.  */

    return (OK);

}

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinNeu                       Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB    pWkb   Zeiger auf den Kontrollblock des     บ
  บ                                   anzuzeigenden Windows.               บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion schreibt ein Window auf den Bild-      บ
  บ                    schirm. Dazu werden folgende Schritte abgear-       บ
  บ                    beitet:                                             บ
  บ                                                                        บ
  บ                      - Buffer allokieren  (evtl. Fehlermeldung)        บ
  บ                      - Cursor des alten aktiven Windows sichern        บ
  บ                      - globale Variablen aktualisieren                 บ
  บ                      - Hintergrund sichern                             บ
  บ                      - Bild aufbauen (Rahmen, Titel, leerer Innenraum) บ
  บ                      - Schnittflchen berechnen                        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation                             บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD i_WinNeu( PWKB pWkb )
{
    WORD wBreite, wHoehe;

    if (pWkb->winFlags.wSchatten)                   /* Window mit Schatten? */
    {
        wBreite = pWkb->wBreite +2;
        wHoehe  = pWkb->wHoehe +1;
    }
    else
    {
        wBreite = pWkb->wBreite;
        wHoehe  = pWkb->wHoehe;
    }

    pWkb->fpwBuffer = UtlFmalloc(2*wBreite*wHoehe); /* Buffer allokieren    */

    if ( pWkb->fpwBuffer == 0L)
    {
        wFehler_g = WIN_KEIN_SPEICHER;
        return (ERROR);
    }

    i_WinSaveCursor();                              /* Cursor des zur Zeit  */
                                                    /* aktiven W. sichern   */

    wAktWin_g++;                                    /* Index inkrementieren */
    apWkbSichtbar_g[wAktWin_g] = pWkb;              /* pWkb ins Array laden */
    VioSw2b( pWkb->wSpalte, pWkb->wZeile,           /* Hintergrund sichern  */
             wBreite, wHoehe,
             pWkb->fpwBuffer);
    UtlZeigeRahmen( pWkb->wSpalte, pWkb->wZeile,    /* Rahmen anzeigen      */
                    pWkb->wBreite,pWkb->wHoehe,
                    pWkb->winFlags.wRahmentyp,
                    pWkb->wRahmenAttr);

    if (pWkb->pstrTitel != NULL)                    /* falls vorhanden, den */
        i_WinZeigeTitel(pWkb);                      /* Titel anzeigen       */

    if (pWkb->winFlags.wSchatten)                   /* Window mit Schatten? */
        UtlZeigeSchatten( pWkb->wSpalte,
                          pWkb->wZeile,
                          pWkb->wBreite,
                          pWkb->wHoehe);

    i_WinInit( pWkb->wSpalte +1, pWkb->wZeile +1,   /* Data-Area des Win-   */
               pWkb->wBreite -2, pWkb->wHoehe -2,   /* dows festlegen       */
               pWkb->wInnenAttr);

    WinCls();                                       /* Window l”schen       */

    pWkb->winFlags.wSichtbar  = 1;                  /* Window ist sichtbar  */
    pWkb->winFlags.wVersteckt = 0;
    pWkb->winFlags.wTRaendern = 0;                  /* nderungen sind be-  */
    pWkb->winFlags.wDAaendern = 0;                  /* rcksichtigt         */

    pWkb->wSchnitte = i_WinSchnitt(wAktWin_g);      /* Schnittflchen be-   */
                                                    /* rechnen              */
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinSchnitt                   Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wIndex     Index des abdeckenden Windows      บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion erstellt fr das angegebene Window   บ
  บ                    eine Bitmaske, in der die Informationen ber die    บ
  บ                    Schnittflchen mit tiefer gelegenen Windows abge-   บ
  บ                    legt sind.                                          บ
  บ                    Jedem Bit in dieser Maske ist ein sichtbares Win-   บ
  บ                    dow zugeordnet. Dem untersten Window ist das Bit    บ
  บ                    0 zugeordnet, dem nchsten Bit 1 usw.. Da maximal   บ
  บ                    16 Windows erlaubt sind (wobei der Bildschirm als   บ
  บ                    Window Nr. 0 betrachtet wird), ist die Bitmaske     บ
  บ                    2 Byte (1 Word) lang.                               บ
  บ                    Ein Bit in der Maske wird immer dann gesetzt, wenn  บ
  บ                    das korrespondierende Window vom aktuellen Window   บ
  บ                    ganz oder teilweise berdeckt wird.                 บ
  บ                                                                        บ
  บ                    Beispiel:  Das aktuelle Window berdeckt die Win-   บ
  บ                               dows 3,6,9 und 11. Die Bitmaske lautet   บ
  บ                               dann:                                    บ
  บ                                      0000 1010 0100 1000  (0x0A48)     บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   Ergebnis der Schnittstellen-Berechnung       บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD i_WinSchnitt(WORD wIndex)
{
    REGISTER i;
    WORD wMaske  = 0x0002,                          /* bei Bit 1 beginnen   */
         wReturn = 0x0001,                          /* Bit 0 immer gesetzt! */
         wSl,wSr,wZo,wZu;                           /* Beschreibung des ab- */
                                                    /* deckenden Windows    */
    PWKB t;                                         /* zu testendes Window  */
    PWKB a = apWkbSichtbar_g[wIndex];               /* zeigt auf abdecken-  */
                                                    /* des Window           */
    wSl = a->wSpalte;
    wZo = a->wZeile;
    if (a->winFlags.wSchatten)                      /* Window mit Schatten? */
    {
        wSr = wSl + a->wBreite +1;
        wZu = wZo + a->wHoehe;
    }
    else                                            /* Window hat keinen    */
    {                                               /* Schatten             */
        wSr = wSl + a->wBreite -1;
        wZu = wZo + a->wHoehe -1;
    }


    for (i=1; i<wIndex; i++,wMaske<<=1)             /* tiefere Windows alle */
    {                                               /* testen               */
        t = apWkbSichtbar_g[i];
        if (t->winFlags.wSchatten)
            if ((wSl > t->wSpalte + t->wBreite +1)  /* a(ktiv) rechts von t */
             || (wZo > t->wZeile  + t->wHoehe )     /* a unter t(est)       */
             || (t->wSpalte > wSr)                  /* a links von t        */
             || (t->wZeile  > wZu ))                /* a ber t             */
            ;                                       /* -> keine berlappung */
            else                                    /* berlappende Windows */
                wReturn |= wMaske;                  /* entspr. Bit setzen   */
        else
            if ((wSl > t->wSpalte + t->wBreite -1)  /* a(ktiv) rechts von t */
             || (wZo > t->wZeile  + t->wHoehe -1)   /* a unter t(est)       */
             || (t->wSpalte > wSr)                  /* a links von t        */
             || (t->wZeile  > wZu ))                /* a ber t             */
            ;                                       /* -> keine berlappung */
            else                                    /* berlappende Windows */
                wReturn |= wMaske;                  /* entspr. Bit setzen   */

    }
    return(wReturn);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinPop                       Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wIndex   Index des zu entfernenden Windows    บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion entfernt das gewnschte Window vom     บ
  บ                    Bildschirm und sichert es im Hintergrund-Buffer.    บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_WinPop( WORD wIndex )
{
    PWKB pWkb = apWkbSichtbar_g[wIndex];            /* Zeiger auf den WKB   */

    VioSw2b (pWkb->wSpalte, pWkb->wZeile,           /* W. zwischenspeichern */
             pWkb->wBreite, pWkb->wHoehe,
             fpwCopyBuffer_g);

    if (pWkb->winFlags.wSchatten)                   /* alten Hintergrund    */
        VioSb2w (pWkb->wSpalte, pWkb->wZeile,       /* wiederherstellen     */
                 pWkb->wBreite+2, pWkb->wHoehe+1,
                 pWkb->fpwBuffer);
    else
        VioSb2w (pWkb->wSpalte, pWkb->wZeile,
                 pWkb->wBreite, pWkb->wHoehe,
                 pWkb->fpwBuffer);
    MemCopy( pWkb->fpwBuffer, fpwCopyBuffer_g, 2 * pWkb->wBreite * pWkb->wHoehe);
#ifdef NEVER
    movedata(FP_SEG(fpwCopyBuffer_g),               /* zwischengespeicher-  */
             FP_OFF(fpwCopyBuffer_g),               /* tes Window im Buffer */
             FP_SEG(pWkb->fpwBuffer),               /* ablegen              */
             FP_OFF(pWkb->fpwBuffer),
             2 * pWkb->wBreite * pWkb->wHoehe);
#endif
}

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinPush                      Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wIndex   Index des aufzulegenden Windows      บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion holt das gewnschte Window aus dem     บ
  บ                    Hintergrund-Buffer und legt es auf den Bildschirm.  บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_WinPush( WORD wIndex )
{
    PWKB pWkb = apWkbSichtbar_g[wIndex];            /* Zeiger auf den WKB   */
    MemCopy( fpwCopyBuffer_g, pWkb->fpwBuffer, 2 * pWkb->wBreite * pWkb->wHoehe );
#ifdef NEVER
    movedata(FP_SEG(pWkb->fpwBuffer),               /* Window zwischen-     */
             FP_OFF(pWkb->fpwBuffer),               /* speichern            */
             FP_SEG(fpwCopyBuffer_g),
             FP_OFF(fpwCopyBuffer_g),
             2 * pWkb->wBreite * pWkb->wHoehe);
#endif
    if (pWkb->winFlags.wSchatten )                  /* Hintergrund sichern  */
        VioSw2b (pWkb->wSpalte, pWkb->wZeile,
                 pWkb->wBreite+2, pWkb->wHoehe+1,
                 pWkb->fpwBuffer);
    else
        VioSw2b (pWkb->wSpalte, pWkb->wZeile,
                 pWkb->wBreite, pWkb->wHoehe,
                 pWkb->fpwBuffer);

    VioSb2w (pWkb->wSpalte, pWkb->wZeile,           /* Window auf dem Bild- */
             pWkb->wBreite, pWkb->wHoehe,           /* schirm anzeigen      */
             fpwCopyBuffer_g);

    if (pWkb->winFlags.wSchatten)                   /* Window mit Schatten? */
        UtlZeigeSchatten( pWkb->wSpalte,
                          pWkb->wZeile,
                          pWkb->wBreite,
                          pWkb->wHoehe);
}


