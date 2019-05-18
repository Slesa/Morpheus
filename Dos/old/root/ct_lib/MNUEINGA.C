/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuEingabe                     Datum: 26.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        EVENT   pEvent   Zeiger auf Eventstruktur           บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ist das Hauptsteuermodul fr den     บ
  บ                    Menmanager. Sie fungiert wie ein Filter zwischen   บ
  บ                    der Eingabefunktion UtlEvent() und dem Pro-         บ
  บ                    grammierer. Alle Tastatur- und Mauseingaben         บ
  บ                    werden daraufhin berprft, ob der Anwender mit     บ
  บ                    seiner Eingabe die Menauswahl aktiviert hat.       บ
  บ                                                                        บ
  บ                    Ist dies der Fall bernimmt MnuEingabe() die        บ
  บ                    Verwaltung aller weiteren Anwendereingaben bis      บ
  บ                    entweder eine Option ausgewhlt oder die            บ
  บ                    Menauswahl vom Anwender beendet wurde.             บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     keiner                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  MS_g   (R)                                          บ
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
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SICHERN 400
#define RESTORE 401

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT MENUSTATUS MS_g;
IMPORT MENU aMenus_g[];
IMPORT WORD wAktMnu_g;
IMPORT BOOL boBeepen_g;
IMPORT WORD wMausda_g;
IMPORT FPWORD fpwAlteHZ_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE FUNKTIONEN                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL PMKB  i_MnuIsMenuHK       (WORD);
MGLOBAL SWORD i_MnuIsMFHK         (PMKB, WORD);
MGLOBAL VOID  i_MnuEvents         (PEVENT, PMKB*, BOOL);
MGLOBAL VOID  i_MnuClientStatus   (WORD);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MnuEingabe(PEVENT pEvent)
{
    STATIC BOOL boAnfang;
    STATIC PMKB pMkb;

    boAnfang = JA;
    pMkb = NULL;
    for (;;)
    {
        UtlEvent(pEvent);                           /* Eingaben einlesen    */
        if (MS_g.wAktiv == NEIN)
        {
            if (pEvent->wArt == EVENT_ALT_RELEASE )
                MS_g.wAktiv = JA;
            else if (pEvent->wArt == EVENT_TASTE)
            {
                if (pEvent->wTaste == T_F10 ||
                    (pMkb = i_MnuIsMenuHK(pEvent->wTaste)) != NULL)
                    MS_g.wAktiv = JA;
            }
            else if (pEvent->wArt == EVENT_L_PRESS &&
                     pEvent->wZeile == 0           &&
                     (pMkb = i_MnuAufMenutitel(pEvent)) != NULL)
                        MS_g.wAktiv = JA;
        }

        if (MS_g.wAktiv == JA)
        {
            if ( boAnfang == JA &&                  /* beim ersten Mal hier */
                 fpwAlteHZ_g != 0L)                 /* und Speicher da      */
                i_MnuClientStatus(SICHERN);

            if (pMkb == NULL)
                pMkb = aMenus_g[wAktMnu_g].pMkbStart;
            i_MnuEvents(pEvent, &pMkb, boAnfang);
            boAnfang = NEIN;
        }
        if (MS_g.wAktiv == NEIN)
        {
            if (boAnfang == NEIN)
                i_MnuClientStatus(RESTORE);
            return;
        }
    }
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuEvents                    Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PEVENT  pEvent      Zeiger auf Eventstruktur        บ
  บ                    PMKB    *ppMkb      Zeiger auf Zeiger MKB           บ
  บ                    BOOL    boEinstieg  erster Aufruf dieser Funktion   บ
  บ                                        innerhalb einer Auswahlrunde    บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion wertet nach der Aktivierung des      บ
  บ                    Menmanagers alle Events aus.                       บ
  บ                    Es wird hierbei zwischen verschiedenen Zustnden    บ
  บ                    unterschieden, in denen sich das Men befinden      บ
  บ                    kann:                                               บ
  บ                    - kein Fenster && kein Titel                        บ
  บ                    - kein Fenster &&      Titel                        บ
  บ                    -      Fenster && kein Titel                        บ
  บ                                                                        บ
  บ                    Je nach Zustand und eingelesenen Events wird        บ
  บ                    dann die entsprechende Aktion ausgefhrt.           บ
  บ                                                                        บ
  บ  Rckgabewert:     Adresse des aktuellen MKB ber ppMkb                บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - MS_g   (R)  Status des Menmanagers               บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_MnuEvents(PEVENT pEvent, PMKB *ppMkb, BOOL boEinstieg)
{
    STATIC BOOL boHotKey;
    STATIC PMKB pMkb;
    PMKB pMkbTmp;
    SWORD swIndex;

    if (boEinstieg == JA)                           /* beim ersten Aufruf   */
        pMkb = *ppMkb;                              /* pMkb Laden           */

    if (pEvent->wButton == MSM_L_DOWN)              /* Mausevents in eigener*/
    {                                               /* Funktion             */
        i_MnuMauswahl(pEvent, &pMkb);
        return;
    }


    else if (MS_g.wFenster == NEIN &&
             MS_g.wTitel   == NEIN)
    {
        if (pEvent->wTaste == T_F10 ||
            pEvent->wArt   == EVENT_ALT_RELEASE)
        {
            if (boHotKey == NEIN)
                i_MnuTitel(&pMkb, 0, EIN_ABS);
            else
                boHotKey = NEIN;
        }
        else                                        /* Hotkey eingegeben    */
        {
            i_MnuFenster(&pMkb, 0, EIN_ABS);
            i_MnuBalken(pMkb, FENSTERZEILE+1, EIN_ABS);
            boHotKey = JA;
        }
    }

    else if (MS_g.wFenster == NEIN &&
             MS_g.wTitel   == JA)
    {
        if (pEvent->wArt == EVENT_ALT_RELEASE)
        {
            i_MnuTitel(&pMkb, 0, AUS);
            MS_g.wAktiv = NEIN;
            pEvent->wArt == EVENT_NULL;
            return;
        }
        else
        switch(pEvent->wTaste)
        {
            case T_F10:
            case T_ESC:
                i_MnuTitel(&pMkb, 0, AUS);
                MS_g.wAktiv = NEIN;
                boHotKey = NEIN;
                pEvent->wArt == EVENT_NULL;
                return;

            case T_LEFT:
                i_MnuTitel(&pMkb, -1, EIN_REL);
                break;

            case T_RIGHT:
                i_MnuTitel(&pMkb, +1, EIN_REL);
                break;

            case T_UP:
                i_MnuTitel(&pMkb, 0, AUS);
                i_MnuFenster(&pMkb, 0, EIN_REL);
                i_MnuBalken(pMkb, pMkb->wItemAnzahl+FENSTERZEILE,
                            EIN_ABS);
                break;

            case T_DOWN:
            case T_RETURN:
                i_MnuTitel(&pMkb, 0, AUS);
                i_MnuFenster(&pMkb, 0, EIN_REL);
                i_MnuBalken(pMkb, FENSTERZEILE+1, EIN_ABS);
                break;

            default:
                if (pEvent->wTaste < 255)
                    pEvent->wTaste = UtlAltCode(pEvent->wTaste);
                pMkbTmp = i_MnuIsMenuHK(pEvent->wTaste);
                if (pMkbTmp != NULL)
                {
                    i_MnuTitel(&pMkb, 0, AUS);
                    pMkb = pMkbTmp;
                    i_MnuFenster(&pMkb, 0, EIN_REL);
                    i_MnuBalken(pMkb, FENSTERZEILE+1, EIN_ABS);
                    boHotKey = JA;
                }
                break;
        } /* end of switch */
    } /* end of if titel && kein fenster */

    else if (MS_g.wFenster == JA &&
             MS_g.wTitel   == NEIN)
    {
        if (pEvent->wArt == EVENT_ALT_RELEASE)
        {
            if (boHotKey == NEIN)
            {
                i_MnuFenster(&pMkb, 0, AUS);
                i_MnuTitel(&pMkb, 0, EIN_REL);
            }
            else
                boHotKey = NEIN;
        }
        else
        switch(pEvent->wTaste)
        {
            case T_ESC:
                i_MnuFenster(&pMkb, 0, AUS);
                MS_g.wAktiv = NEIN;
                boHotKey = NEIN;
                pEvent->wArt == EVENT_NULL;
                return;

            case T_F10:
                i_MnuFenster(&pMkb, 0, AUS);
                i_MnuTitel(&pMkb, 0, EIN_REL);
                break;

            case T_PGUP:
            case T_HOME:
                i_MnuBalken(pMkb, FENSTERZEILE+1, EIN_ABS);
                break;

            case T_PGDN:
            case T_END:
                i_MnuBalken(pMkb, pMkb->wItemAnzahl+FENSTERZEILE,
                            EIN_ABS);
                break;


            case T_LEFT:
                i_MnuFenster(&pMkb, -1, EIN_REL);
                i_MnuBalken(pMkb, FENSTERZEILE+1, EIN_ABS);
                break;

            case T_RIGHT:
                i_MnuFenster(&pMkb, +1, EIN_REL);
                i_MnuBalken(pMkb, FENSTERZEILE+1, EIN_ABS);
                break;

            case T_UP:
                i_MnuBalken(pMkb, -1, EIN_REL);
                break;

            case T_DOWN:
                 i_MnuBalken(pMkb, +1, EIN_REL);
                 break;

            case T_RETURN:
                if ( pMkb->pHotkeys[pMkb->wBalIndex].wAktiv == JA)
                {
                    i_MnuFenster(&pMkb, 0, AUS);
                    boHotKey = NEIN;
                    MS_g.wAktiv = NEIN;
                    pEvent->wArt = EVENT_WAHL;
                    pEvent->wOption = pMkb->pHotkeys[pMkb->wBalIndex].wOpt;
                    return;
                }
                else
                    if (boBeepen_g)
                        i_Beep();
                break;

            default:
                if( UtlIsUmlaut(pEvent->wTaste) == NEIN)
                    pEvent->wTaste = UtlAltCode(pEvent->wTaste);
                else
                    pEvent->wTaste = UtlGross(pEvent->wTaste);
                swIndex = i_MnuIsMFHK(pMkb, pEvent->wTaste);
                if (swIndex >= 0)
                {
                    i_MnuFenster(&pMkb, 0, AUS);
                    boHotKey = JA;
                    MS_g.wAktiv = NEIN;
                    pEvent->wArt = EVENT_WAHL;
                    pEvent->wOption = pMkb->pHotkeys[swIndex].wOpt;
                    return;
                }
                else
                    if (pEvent->wArt == EVENT_TASTE)
                        if (boBeepen_g)
                            i_Beep();
                break;
        } /* end of switch */
    } /* end of if fenster und kein titel */
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuIsMenuHK                  Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wTaste     zu berprfende Taste.             บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion berprft die bergebene Taste       บ
  บ                    daraufhin, ob mit ihr ein Men aktiviert werden     บ
  บ                    soll.                                               บ
  บ                                                                        บ
  บ  Rckgabewert:     PMKB    Zeiger auf den Menkontrollblock des        บ
  บ                            Mens, das aktiviert werden soll oder       บ
  บ                    NULL    wenn es sich bei der bergebenen Taste      บ
  บ                            nicht um einen Mnemonic handelt.            บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  aMenus_g   (R)                                      บ
  บ                    wAktMnu_g  (R)                                      บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
PMKB i_MnuIsMenuHK(WORD wTaste)
{
    PMKB pMkb = aMenus_g[wAktMnu_g].pMkbStart;      /* auf 1. MKB zeigen    */

    do                                              /* alle Elemente der    */
    {                                               /* Liste bearbeiten     */
        if (pMkb->wMkbsign != MKBSIGNATUR)          /* interner Zeigertest  */
            i_Fehler(I_FEHLER_SIGN, "i_MnuIsMenuHK",
                     __FILE__, __LINE__);

        if (wTaste == pMkb->wMzHotkey)              /* Taste Men-Hotkey    */
            return (pMkb);                          /* Adresse des MKB      */
        else                                        /* zurck               */
            pMkb = pMkb->pNaechster;                /* auf nchsten Block   */

    } while(pMkb != aMenus_g[wAktMnu_g].pMkbStart);

    return (NULL);                                  /* Taste kein Men-HK   */
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuAufMenutitel              Datum: 18.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PEVENT   pEvent     Zeiger auf EVENT-Struktur       บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion berprft, ob sich der Mauscursor    บ
  บ                    innerhalb eines Mentitels befindet.                บ
  บ                                                                        บ
  บ  Rckgabewert:     PMKB    Zeiger auf Menkontrollblock des Mens,     บ
  บ                            das aktiviert werden soll oder              บ
  บ                    NULL    wenn nicht auf einem Mentitel geklickt     บ
  บ                            wurde                                       บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  startmkb(R)                                         บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
PMKB i_MnuAufMenutitel(PEVENT pEvent)
{
    PMKB  pMkb = aMenus_g[wAktMnu_g].pMkbStart;     /* auf 1. MKB zeigen    */


    do                                              /* alle Elemente der    */
    {                                               /* Liste bearbeiten     */
        if (pMkb->wMkbsign != MKBSIGNATUR)          /* interner Zeigertest  */
            i_Fehler(I_FEHLER_SIGN,"i_MnuAufMenutitel",
                     __FILE__, __LINE__);

         if (pEvent->wSpalte >= pMkb->wTitelSpalte &&
             pEvent->wSpalte <  pMkb->wTitelSpalte+pMkb->wTitelBreite)
            return (pMkb);                          /* Adresse des MKB      */
        else                                        /* zurck               */
            pMkb = pMkb->pNaechster;                /* auf nchsten Block   */
    } while(pMkb != aMenus_g[wAktMnu_g].pMkbStart);

    return (NULL);
}






/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuIsMFHK                    Datum: 07.01.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PMKB  pMkb    Zeiger auf Menkontrollblock, der     บ
  บ                                  untersucht werden soll                บ
  บ                    WORD  wTaste  eingegebene Taste                     บ                                                  บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion berprft, ob die eingegebene        บ
  บ                    Taste ein Hotkey fr eine aktive Option im          บ
  บ                    Menfensterist, auf das pMkb zeigtt.                บ
  บ                                                                        บ
  บ                    Wenn ja, wird der Index auf pMkb->pHotkeys          บ
  บ                    zurckgegeben, sonst -1.                            บ
  บ                                                                        บ
  บ  Rckgabewert:     SWORD   -1   nicht gefunden oder nicht aktiv        บ
  บ                            >=0  Index auf pMkb->pHotkeys               บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
SWORD i_MnuIsMFHK( PMKB pMkb, WORD wTaste)
{
    REGISTER i;

    for (i=0; i<pMkb->wItemAnzahl; i++)
    {
        if (pMkb->pHotkeys[i].wKey == wTaste)
        {
            if (pMkb->pHotkeys[i].wAktiv == JA)
                return(( SWORD) i);
            else
                return(-1);
        }
    }
    return (-1);
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuClientStatus              Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wModus   SICHERN/RESTORE                     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion sichert beim Einstieg in den         บ
  บ                    Menmanager die Hilfezeile und den Hardware-        บ
  บ                    Cursor. Beim Verlassen wird beides wieder           บ
  บ                    restauriert.                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  fpwAlteMZ_g   (R/W)                                 บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL VOID i_MnuClientStatus(WORD wModus)
{
    STATIC WORD wSpalte, wZeile, wStart, wStop;
    WORD wMausStatus;

    if (wMausda_g)
        wMausStatus = MsmCursorOff();


    if (wModus == SICHERN)
    {
        if (aMenus_g[wAktMnu_g].wStatus.wHzeile == 1)   /* Hilfszeile sichern   */
            VioSw2b(0,24,80,1,fpwAlteHZ_g);
        VioGetCursor(&wSpalte, &wZeile, &wStart, &wStop);
        VioSetCursorTyp(0x20, 0);
    }
    else
    {
        if (aMenus_g[wAktMnu_g].wStatus.wHzeile == 1)
            VioSb2w(0,24,80,1, fpwAlteHZ_g);
        VioSetCursorPos(wSpalte, wZeile);
        VioSetCursorTyp(wStart, wStop);
    }

    if (wMausda_g && wMausStatus == MSM_WAR_AN)
        MsmCursorOn();

}
