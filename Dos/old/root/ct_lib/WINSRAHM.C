/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinSetRahmentyp                Datum: 13.09.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWKB   pWkb   Zeiger auf Fensterkontrollblock       บ
  บ                    WORD   wTyp   Bezeichner fr Rahmentyp              บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt fr ein Window den Rahmentyp    บ
  บ                    fest. Eine gltige Option wird in den WKB ein-      บ
  บ                    getragen. Wenn pWkb der Zeiger auf das zur Zeit     บ
  บ                    aktive Fenster ist, wird der Rahmen neu gezeich-    บ
  บ                    net. Anderenfalls wird die nderung erst dann be-   บ
  บ                    arbeitet, wenn das Fenster zum aktiven Windos       บ
  บ                    gemacht wird.                                       บ
  บ                                                                        บ
  บ                    Fr den Parameter wTyp k”nnen die Konstanten        บ
  บ                    verwendet werden, die in der Datei ctutl.h          บ
  บ                    definiert sind. Diese Bezeichner beginnen mit       บ
  บ                    dem Prfix RT_, gefolgt von einer Nachsilbe aus     บ
  บ                    vier Buchstaben, die den Linientyp fr jede Seite   บ
  บ                    des Rahmens definiert. Eine doppelte Linie wird     บ
  บ                    durch den Buchstaben D, eine einfache durch E       บ
  บ                    symbolisert. Der erste Buchstabe gibt den Typ fr   บ
  บ                    die obere Waagerechte an, der zweite fr die        บ
  บ                    nchste Seite im Uhrzeigersinn.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  OK     wenn Rahmentyp erfolgreich gendert    บ
  บ                          ERROR  wenn Fehler aufgetreten ist            บ
  บ                                 dann erhlt die globale Variable die   บ
  บ                                 Fehlernummer:                          บ
  บ                                 WIN_KEIN_PWKB                          บ
  บ                                 WIN_FALSCHE_OPT                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g (W)                                       บ
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
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;
IMPORT WORD wMausda_g;
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinSetRahmentyp(PWKB pWkb, WORD wTyp)
{

    WORD wMausstatus;

    if (pWkb->wWkbsign != WKBSIGNATUR)              /* Test ob Zeiger noch  */
    {                                               /* auf WKB zeigt, wenn  */
        wFehler_g = WIN_KEIN_PWKB;                  /* nicht Variable setz. */
        return (ERROR);                             /* und an aufr. Fkt.    */
    }

    if (wTyp < 0 || wTyp > 17)                      /* wenn kein gltiges   */
    {                                               /* Funktionsargument    */
        wFehler_g = WIN_FALSCHE_OPT;                /* Variable setzen und  */
        return (ERROR);                             /* an Aufrufer          */
    }

    pWkb->winFlags.wRahmentyp = wTyp;               /* neuen Typ eintragen  */

    if ( WinIsAktiv(pWkb) )                         /* wenn aktives Fenster */
    {
        if (wMausda_g)                              /* evtl. Mauszeiger aus */
            wMausstatus = MsmCursorOff();           /* vor Ausgabe          */
        UtlZeigeRahmen( pWkb->wSpalte,              /* neuen Rahmentyp      */
                        pWkb->wZeile,               /* anzeigen             */
                        pWkb->wBreite,
                        pWkb->wHoehe,
                        pWkb->winFlags.wRahmentyp,
                        pWkb->wRahmenAttr);

        if (pWkb->pstrTitel != NULL)                /* wenn Titel vorhanden */
            i_WinZeigeTitel(pWkb);                  /* neu anzeigen         */

        if (wMausda_g && wMausstatus == MSM_WAR_AN) /* Maus wieder ein      */
            MsmCursorOn();
    }
    else
        pWkb->winFlags.wTRaendern = 1;

    return (OK);
}

