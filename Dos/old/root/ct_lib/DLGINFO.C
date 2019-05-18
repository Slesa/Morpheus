/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgInfo                        Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PPSTR ppstrText     Informationstext                บ
  บ                    WORD  wDlgTyp       Angabe ber Art des Dialog-     บ
  บ                                        feldes                          บ
  บ                                        - DLG_INFO                      บ
  บ                                        - DLG_WARNUNG                   บ
  บ                                        - DLG_KRITISCH                  บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion baut eine Info-Dialogbox auf.        บ
  บ                    Die Gr”แe der Dialogbox wird aus der Anzahl         บ
  บ                    und der Lnge der Textzeilen berechnet und die      บ
  บ                    Dialogbox zentriert auszugeben.                     บ
  บ                    Die Dialogbox kann maximal die gesamte Gr”แe des    บ
  บ                    Bildschirms einnehmen. Scrollen wird von dieser     บ
  บ                    Funktion nicht untersttzt.                         บ
  บ                                                                        บ
  บ                    Die Attribute der Dialogbox werden entsprechend     บ
  บ                    der SAA-Richtlinien aufgrund des Dialogtyps fest-   บ
  บ                    gelegt.                                             บ
  บ                                                                        บ
  บ                    Alle Dialogboxen erhalten eine Eingabe-Schalt-      บ
  บ                    flche. Das Dialogfeld bleibt solange aktiv, bis    บ
  บ                    der Anwender diese Schaltflche anwhlt.            บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation OK/ERROR                    บ
  บ                          - OK Dialogfeld wurde angezeigt und vom       บ
  บ                               Anwender besttigt.                      บ
  บ                          - ERROR Dialogfeld konnte nicht angezeigt     บ
  บ                                  werden                                บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  aCS_g, wCSInd_g, pstrReturn_g  (R)                  บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                      GLOBALE VARIABLEN, REFERENZEN                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT COLORSET aCS_g[];                            /* Farbpaletten-Array   */
IMPORT WORD     wCSInd_g;                           /* Index in Pal.-Array  */
IMPORT PSTR     pstrReturn_g;                       /* Schaltflchentext    */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgInfo(PPSTR ppstrText, WORD wDlgTyp)
{
    REGISTER i;                                     /* Zhlervariable       */

    WORD     wSpalte,                               /* Spalte des Dialoges  */
             wZeile,                                /* Zeile des Dialoges   */
             wAnzahl,                               /* Anzahl Textzeilen    */
             wLaenge,                               /* Lnge bearb. Text    */
             wMaxlaenge;                            /* lngste Textzeile    */

    PWKB     pWkbDlg;                               /* Dialog-Window        */
    PPSTR    ppstrTmp_m;                            /* lok. Zeiger Infotexte*/

    EVENT    Event;                                 /* Event-Struktur und   */
    PEVENT   pEvent;                                /* der Zeiger darauf    */


    ppstrTmp_m = ppstrText;
    pEvent = &Event;

    for (wAnzahl=0, wMaxlaenge=0;                   /* Anzahl der Text-     */
         *ppstrTmp_m != NULL;                       /* zeilen und Lnge des */
         wAnzahl++)                                 /* lngsten Textes er-  */
    {                                               /* mitteln              */
        wLaenge = strlen(*ppstrTmp_m);
        wMaxlaenge = max(wMaxlaenge, wLaenge);
        *ppstrTmp_m++;
    }

    ppstrTmp_m = ppstrText;                         /* Zeiger zurcksetzen  */

    wSpalte = (80 - wMaxlaenge)/2 - 2;              /* Position und Ab-     */
    wZeile  = (24 - wAnzahl)/2-2;                   /* messungen d. Dialog- */
    wMaxlaenge +=4;                                 /* feldes berechnen     */
    wAnzahl    +=6;

    if ((pWkbDlg = WinEinrichten(wSpalte,           /* Fenster einrichten   */
                                 wZeile,
                                 wMaxlaenge,
                                 wAnzahl)) == NULL)
        return (ERROR);


    i_InitVars();                                   /* glo. Var. initialis. */
    i_DlgInit(wSpalte, wZeile,
              wMaxlaenge, wAnzahl,
              NULL,
              pWkbDlg,
              SF_EINGABE,
              wDlgTyp);

    for (i = 1; *ppstrTmp_m != NULL;)               /* Info-Text ausgeben   */
        WinSs(1, i++, *ppstrTmp_m++);

    for(;;)                                         /* Eingaberoutine wartet*/
    {                                               /* auf Aktivierung der  */
        UtlEvent(pEvent);                           /* Eingabe-Schaltflche */
        switch(pEvent->wArt)
        {
            case EVENT_TASTE:                       /* auf Return-Schaltfl. */
                if (pEvent->wTaste == T_RETURN) /* warten               */
                {
                    WinEntfernen(pWkbDlg);
                    return(OK);
                }
                break;

            case EVENT_L_PRESS:
                if (pEvent->wZeile == wZeile+wAnzahl-2)
                {
                    if (pEvent->wSpalte >= wSpalte+3 &&
                        pEvent->wSpalte <= wSpalte+2+strlen(pstrReturn_g))
                    {
                        WinEntfernen(pWkbDlg);
                        return(OK);
                    }
                }
                break;
        }
    }
}
