/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgNachricht                   Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PPSTR ppstrText     Informationstext                บ
  บ                    WORD  wSpalte       Spalte oben links des Dialoges  บ
  บ                    WORD  wZeile        Zeile oben links des Dialoges   บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion baut eine Nachrich-Dialogbox auf.    บ
  บ                    Die Gr”แe der Dialogbox wird aus der Anzahl         บ
  บ                    und der Lnge der Textzeilen berechnet. Die Dialog- บ
  บ                    box wird an der bergebenen Position ausgegeben.    บ
  บ                                                                        บ
  บ                    Die Argumente wSpalte und wZeile werden korrigiert, บ
  บ                    wenn die Box mit diesen Werten nicht ganz auf       บ
  บ                    den Bildschirm passen wrde.                        บ
  บ                                                                        บ
  บ                    Die Dialogbox kann maximal die gesamte Gr”แe des    บ
  บ                    Bildschirms einnehmen. Scrollen wird von dieser     บ
  บ                    Funktion nicht untersttzt.                         บ
  บ                                                                        บ
  บ                    Die Attribute der Dialogbox werden entsprechend     บ
  บ                    der SAA-Richtlinien aufgrund des Dialogtyps fest-   บ
  บ                    gelegt.                                             บ
  บ                                                                        บ
  บ                    Die Nachrichten-Dialogboxen erhalten keine          บ
  บ                    Schaltflchen. Sie dienen dazu, den Anwender        บ
  บ                    ber den aktuellen Zustand des Programms zu         บ
  บ                    informieren. Der Anwender braucht auf diese         บ
  บ                    Nachrichten-Dialoge nicht zu reagieren.             บ
  บ                                                                        บ
  บ                    Sie k”nnen den Anwender beipsielsweise mit dem      บ
  บ                    Informationstext "Bitte warten" darber infor-      บ
  บ                    mieren, daแ der Anwender keine Eingaben eingeben    บ
  บ                    kann, da lngere Programmaufgaben erledigt werden.  บ
  บ                                                                        บ
  บ                    Wenn Sie der Funktion als Argument NULL bergeben,  บ
  บ                    wird das derzeit aktive Nachrichten-Dialogfeld      บ
  บ                    entfernt. Es kann immer nur eine Nachrichten-       บ
  บ                    box mit dieser Funktion angezeigt werden.           บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation OK/ERROR                    บ
  บ                          - OK    Dialogfeld wurde angezeigt/entfernt   บ
  บ                          - ERROR Dialogfeld konnte nicht angezeigt     บ
  บ                                  werden                                บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  aCS_g, wCSInd_g                                     บ
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



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
STATIC BOOL boAktiv_m = NEIN;                       /* derzeit Dialogfeld   */
                                                    /* aktiv                */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgNachricht(PPSTR ppstrText, WORD wSpalte, WORD wZeile)
{
    REGISTER i;                                     /* Zhlervariable       */
    STATIC PWKB  pWkbDlg;                           /* Dialog-Window        */

    WORD     wSp,                                   /* Spalte des Dialoges  */
             wZe,                                   /* Zeile des Dialoges   */
             wAnzahl,                               /* Anzahl Textzeilen    */
             wLaenge,                               /* Lnge bearb. Text    */
             wMaxlaenge;                            /* lngste Textzeile    */

    PPSTR    ppstrTmp_m;                            /* lok. Zeiger Texte    */

    ppstrTmp_m = ppstrText;

    if (ppstrTmp_m == NULL)                         /* Box entfernen ?      */
    {
        if (boAktiv_m == JA)                        /* Box aktiv ?          */
        {
            WinEntfernen(pWkbDlg);                  /* dann entfernen       */
            boAktiv_m = NEIN;                       /* Flag setzen          */
            return(OK);                             /* und zurck           */
        }
        else
            return (ERROR);
    }
    else                                            /* Box anzeigen         */
    {
        for (wAnzahl=0, wMaxlaenge=0;               /* Anzahl der Text-     */
             *ppstrTmp_m != NULL;                   /* zeilen und Lnge des */
            wAnzahl++)                              /* lngsten Textes er-  */
        {                                           /* mitteln              */
            wLaenge = strlen(*ppstrTmp_m);
            wMaxlaenge = max(wMaxlaenge, wLaenge);
            *ppstrTmp_m++;
        }
        ppstrTmp_m = ppstrText;                     /* Zeiger zurcksetzen  */
        wSpalte = abs(wSpalte);                     /* negative Argumente   */
        wZeile  = abs(wZeile);                      /* korrigieren          */
        wSp = min(wSpalte,(80-wMaxlaenge-8));       /* Position und Ab-     */
        wZe = min(wZeile, (24-wAnzahl-4));          /* messungen d. Dialog- */
        wMaxlaenge +=6;                             /* feldes berechnen     */
        wAnzahl    +=4;

        if ((pWkbDlg = WinEinrichten(wSp,           /* Fenster einrichten   */
                                     wZe,
                                     wMaxlaenge,
                                     wAnzahl)) == NULL)
            return (ERROR);

        i_InitVars();                               /* glo. Var. initialis. */
        WinSetAttri(pWkbDlg, 0,                     /* Attribute festlegen  */
                    aCS_g[wCSInd_g].wCs_dlg,
                    aCS_g[wCSInd_g].wCs_dlg);
        WinSchattenEin(pWkbDlg);                    /* Schatten ein         */
        WinAktivieren(pWkbDlg);                     /* Dialog aktivieren    */
        for (i = 1; *ppstrTmp_m != NULL;)           /* Text ausgeben        */
            WinSs(2, i++, *ppstrTmp_m++);
        boAktiv_m = JA;                             /* Flag setzen          */
        return (OK);                                /* und zurck           */
    }
}


