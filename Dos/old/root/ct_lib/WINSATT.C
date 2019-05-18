/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSetAttri                    Datum: 13.09.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB   pWkb      Zeiger auf Fensterkontrollblock    บ
  บ                    WORD   wTitel    Attribut fr Titel                 บ
  บ                    WORD   wRahmen   Attribut fr Rahmen                บ
  บ                    WORD   wInnen    Attribut fr Data-Area             บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion k”nnen die Attribute fr        บ
  บ                    ein Fenster gendert werden.                        บ
  บ                    Wenn pWkb auf das aktive Fenster zeigt, wird        บ
  บ                    die Attributnderung nach Funktionsaufruf ausge-    บ
  บ                    fhrt.                                              บ
  บ                    Anderenfalls werden die neuen Attribute nur in      บ
  บ                    die Struktur eingetragen. Die nderungen werden     บ
  บ                    dann bei der nchsten Aktivierung des Fensters      บ
  บ                    wirksam.                                            บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  OK    Funktion wurde erfolgreich ausgefhrt   บ
  บ                          ERROR Fehler aufgetreten, wFehler_g erhlt:   บ
  บ                                  - WIN_KEIN_PWKB                       บ
  บ                                  - WIN_FALSCHE_OPT                     บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g (W), wMausda_g (W)                        บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                    GLOBALE VARIABLEN, REFERENZEN                       บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */
IMPORT WORD wMausda_g;          /* Maus im System ?                         */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinSetAttri (PWKB pWkb, WORD wTitel, WORD wRahmen, WORD wInnen)
{
    WORD wMausstatus;

    if (pWkb->wWkbsign != WKBSIGNATUR)              /* Test ob Zeiger noch  */
    {                                               /* auf WKB zeigt, wenn  */
        wFehler_g = WIN_KEIN_PWKB;                  /* nicht Variable setz. */
        return (ERROR);                             /* und an aufr. Fkt.    */
    }


    if (wTitel  < 0 || wTitel  > 255 ||             /* wenn kein gltiges   */
        wRahmen < 0 || wRahmen > 255 ||             /* Funktionsargument    */
        wInnen  < 0 || wInnen  > 255 )
    {
        wFehler_g = WIN_FALSCHE_OPT;                /* Variable setzen und  */
        return (ERROR);                             /* an Aufrufer zurck   */
    }



    if (wRahmen != 0 || wTitel != 0)                /* wenn Rahmen- oder    */
    {                                               /* Attribut gendert    */
        if (wRahmen != 0)                           /* werden soll          */
            pWkb->wRahmenAttr = wRahmen;            /* neue Attribute ein-  */
        if (wTitel != 0)                            /* tragen               */
            pWkb->wTitelAttr = wTitel;
        if (WinIsAktiv(pWkb))                       /* wenn Fenster aktiv   */
        {
            if (wMausda_g)                          /* evtl. Mauszeiger aus */
                wMausstatus=MsmCursorOff();         /* vor Ausgabe          */
            UtlZeigeRahmen(pWkb->wSpalte,           /* neuen Rahmentyp      */
                    pWkb->wZeile,                   /* anzeigen             */
                    pWkb->wBreite,
                    pWkb->wHoehe,
                    pWkb->winFlags.wRahmentyp,
                    pWkb->wRahmenAttr);
            if (pWkb->pstrTitel != NULL)            /* wenn Titel vorhanden */
                i_WinZeigeTitel(pWkb);              /* neu anzeigen         */
            if (wMausda_g
                &&wMausstatus == MSM_WAR_AN)        /* Maus wieder ein      */
                MsmCursorOn();
        }
        else
            pWkb->winFlags.wTRaendern = 1;
    }

    if (wInnen != 0)                                /* wenn Attribut fr    */
    {                                               /* Data-Area gendert   */
        pWkb->wInnenAttr = wInnen;                  /* werden soll          */
        if (WinIsAktiv(pWkb))
        {
            if (wMausda_g)                          /* evtl. Mauszeiger aus */
                wMausstatus=MsmCursorOff();         /* vor Ausgabe          */
            VioSwa(pWkb->wSpalte+1,                 /* Fenster neu zeichnen */
                   pWkb->wZeile+1,
                   pWkb->wBreite-2,
                   pWkb->wHoehe-2,
                   pWkb->wInnenAttr);
            if (wMausda_g
                && wMausstatus == MSM_WAR_AN)       /* Maus wieder ein      */
                       MsmCursorOn();
        }
        else
            pWkb->winFlags.wDAaendern = 1;
    }
    return (OK);
}
