/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinEntfernen                   Datum: 21.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB    pWkb   Zeiger auf den Kontrollblock des     บ
  บ                                   anzuzeigenden Windows.               บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion gibt fr das gewnschte Window den     บ
  บ                    allokierten Speicherplatz frei. Wenn das Window     บ
  บ                    sichtbar ist, wird es vorher vom Bildschirm ent-    บ
  บ                    fernt.                                              บ
  บ                    Anschlieแend wird das nun zuoberst liegende Win-    บ
  บ                    dow aktiviert.                                      บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformationen (OK/ERROR)                บ
  บ                          Im Fehlerfall erhlt ฏwFehler_gฎ eine der     บ
  บ                          folgenden Fehlernummern:                      บ
  บ                                                                        บ
  บ                                          - WIN_KEIN_PWKB               บ
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
#include <stdio.h>
#include <ctools.h>
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                       Modulglobale Variablen                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL WORD awBit_m[17] = {  0x0001, 0x0002, 0x0004, 0x0008,  /* Bitmasken */
                              0x0010, 0x0020, 0x0040, 0x0080,
                              0x0100, 0x0200, 0x0400, 0x0800,
                              0x1000, 0x2000, 0x4000, 0x8000  };

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                  G l o b a l e   V a r i a b l e n                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

IMPORT  PWKB    apWkbSichtbar_g[16];                /* Array v. Zeigern auf */
                                                    /* WKB der sichtbaren W.*/
IMPORT  WORD    wAktWin_g;                          /* Index des aktiven W. */
                                                    /* in ฏapWkbSichtbar[]ฎ */
IMPORT  FPWORD  fpwCopyBuffer_g;                    /* Zeiger auf 4k-Buffer */

IMPORT  WORD    wMausda_g;                          /* 0: keine Maus da     */
                                                    /* 1: Maus vorhanden    */
IMPORT  WORD    wFehler_g;                          /* Nr. des letzten auf- */
                                                    /* getretenen Fehlers   */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinEntfernen (PWKB pWkb)
{
    REGISTER i;
    WORD wStatus, wIndex,
         wListe, wMaske, wTemp;
    PWKB pWkbTemp;

    if (pWkb->wWkbsign != WKBSIGNATUR)              /* Test ob Zeiger noch  */
    {                                               /* auf WKB zeigt, wenn  */
        wFehler_g = WIN_KEIN_PWKB;                  /* nicht Variable setz. */
        return (ERROR);                             /* und an aufr. Fkt.    */
    }

    wIndex = wAktWin_g;                             /* Index bestimmen      */
    while ( pWkb != apWkbSichtbar_g[wIndex] &&
            wIndex > 0 )
        wIndex--;

    if ( wIndex != 0 )                              /* Ist das W. sichtbar? */
    {
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        i_WinSaveCursor();                          /* Cursor des zur Zeit  */
                                                    /* aktiven W. sichern   */

        wListe = awBit_m[wIndex];                   /* Abrumliste initial. */
        wMaske = awBit_m[wIndex+1];                 /* Bitmaske initial.    */

        for (i = wIndex+1; i <= wAktWin_g; i++)     /* nach oben abarbeiten */
        {
            if ( apWkbSichtbar_g[i]->wSchnitte &    /* exis. Schnittflche? */
                 wListe)
                wListe |= wMaske;                   /* wListe erweitern     */
            wMaske <<= 1;
        }

        if (wListe != awBit_m[wIndex])              /* exis. Schnittflche? */
        {
            wMaske = awBit_m[wAktWin_g];
            for (i = wAktWin_g; i >= wIndex; i--)   /* von oben abrumen    */
            {
                if (wListe & wMaske)                /* Soll das Window ab-  */
                    i_WinPop(i);                    /* gerumt werden ?     */
                wMaske >>= 1;
            }

            wMaske = awBit_m[wIndex+1];
            for (i=wIndex+1; i<=wAktWin_g; i++)     /* Windows auflegen     */
            {
                if (wListe & wMaske)                /* Wurde das Window ab- */
                    i_WinPush(i);                   /* gerumt ?            */
                wMaske <<= 1;
            }

        }
        else                                        /* keine Schnittflchen */
            i_WinPop(wIndex);                       /* Window entfernen     */

        for (wMaske=i=0; i < wIndex; i++)           /* Maske zum Ausblenden */
             wMaske |= awBit_m[i];

        for (i=wIndex; i < wAktWin_g; i++)          /* Array aktualisieren  */
        {
            apWkbSichtbar_g[i]=apWkbSichtbar_g[i+1];
            wTemp = apWkbSichtbar_g[i]->wSchnitte;
            wTemp = (wTemp & wMaske) |
                    ((wTemp>>1) & (~wMaske));
            apWkbSichtbar_g[i]->wSchnitte = wTemp;
        }
        apWkbSichtbar_g[wAktWin_g] = 0L;            /* oberst. Zeiger l”sch.*/

        pWkbTemp = apWkbSichtbar_g[--wAktWin_g];    /* neues aktives Window */

        i_WinInit( pWkbTemp->wSpalte +1,            /* Data-Area des Win-   */
                   pWkbTemp->wZeile +1,             /* dows festlegen       */
                   pWkbTemp->wBreite -2,
                   pWkbTemp->wHoehe -2,
                   pWkbTemp->wInnenAttr);

        if (pWkbTemp->winFlags.wTRaendern)          /* Titel o. Rahmen nd.?*/
        {
            UtlZeigeRahmen(pWkbTemp->wSpalte,       /* Rahmen neu anzeigen  */
                           pWkbTemp->wZeile,
                           pWkbTemp->wBreite,
                           pWkbTemp->wHoehe,
                           pWkbTemp->winFlags.wRahmentyp,
                           pWkbTemp->wRahmenAttr);

            if (pWkbTemp->pstrTitel != NULL)        /* falls vorhanden, den */
                i_WinZeigeTitel(pWkbTemp);          /* Titel neu anzeigen   */

            pWkbTemp->winFlags.wTRaendern = 0;
        }

        if (pWkbTemp->winFlags.wDAaendern)          /* Data-Area ndern ?   */
        {
            WinSwa( 0, 0,                           /* neues Attribut geben */
                    pWkbTemp->wBreite-2,
                    pWkbTemp->wHoehe-2,
                    pWkbTemp->wInnenAttr);
            pWkbTemp->winFlags.wDAaendern = 0;
        }


        i_WinRestoreCursor();                       /* Cursor an alte Pos.  */

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */

    }
						    /* V5.11: DIRK: FEHLER !!     */
						    /* DAS HAT IN ORG.LIB GEFEHLT */
    if (pWkb->pstrTitel != NULL)                    /* Speicher des alten   */
	free(pWkb->pstrTitel);                      /* Titels freigeben     */

    if (pWkb->fpwBuffer != 0L)
        UtlFfree(pWkb->fpwBuffer);                  /* Buffer freigeben     */

    UtlFree(pWkb);                                  /* Struktur freigeben   */

    return(OK);
}
