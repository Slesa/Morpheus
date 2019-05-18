/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgMausTempo                   Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion dient dazu in einem Dialogfeld       บ
  บ                    die Geschwindigkeit der Maus festzulegen.           บ
  บ                                                                        บ
  บ  Rckgabewert:     DLG_ERROR    Dialog konnte nicht angezeigt werden   บ
  บ                    DLG_RETURN   Dialog wurde mit Schaltflche EINGABE  บ
  บ                                 beendet                                บ
  บ                    DLG_ESC      Dialog wurde mit Schaltflche ABBRUCH  บ
  บ                                 beendet                                บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - aCS_g          (R)                                บ
  บ                    - wCSInd_g       (R)                                บ
  บ                                                                        บ
  บ                    - boBeepen_g     (R)                                บ
  บ                    - wVioMode_g     (R)                                บ
  บ                                                                        บ
  บ                    - pstrReturn_g   (R)                                บ
  บ                    - pstrEsc_g      (R)                                บ
  บ                    - pstrF1_g       (R)                                บ
  บ                                                                        บ
  บ                    - wMausSpeed_g   (R/W)                              บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SPA     9
#define ZEI     5
#define BRE    45
#define HOE    12

#define SCZE    5                                   /* Zeile der Scrollbar  */
#define SCSP   17                                   /* (Fensterkoordinaten) */

#define LINKS  1
#define RECHTS 2

#define Z_PFEIL_LINKS 27
#define Z_PFEIL_RECHTS 26

#define SCR_DELAY   2              /* Zeitverz”gerung fr Maus-Dauer-Scroll */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT  COLORSET aCS_g[];
IMPORT  WORD     wMausSpeed_g;
IMPORT  WORD     wCSInd_g;
IMPORT  WORD     wVioMode_g;
IMPORT  BOOL     boBeepen_g;

IMPORT PSTR      pstrReturn_g;
IMPORT PSTR      pstrEsc_g;
IMPORT PSTR      pstrF1_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE FUNKTIONEN                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL WORD i_ChangeSpeed(WORD wSpeed, WORD richtung);
MGLOBAL VOID i_DlgMausZeichneScrollBar(VOID);
MGLOBAL WORD i_DlgMausGetSpeed(WORD);
MGLOBAL WORD i_SetzeTempo(WORD wTempoAlt, WORD wPosition);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL WORD wFarbe_m;

MGLOBAL PSTR apstrIkonMaus_m[]=
{   "  บ  ",
    "Û฿Û฿Û",
    "ÛÛÛÛÛ",
    "ÛÛÛÛÛ",
    NULL
};

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD DlgMausTempo(VOID)
{
    PWKB   pWkbDlg;

    REGISTER zeile;
    WORD     wSpeedTmp;
    CHAR     acZahl[4];
    CHAR     **pstrIkon;
                                                    /* Dialog einrichten    */
    if ((pWkbDlg = WinEinrichten(SPA, ZEI, BRE, HOE)) == NULL)
        return (DLG_ERROR);

    i_InitVars();                                   /* glo. Var. initialis  */
    i_DlgInit(SPA, ZEI, BRE, HOE,
              "Mausgeschwindigkeit",
              pWkbDlg,
              SF_STANDARD,
              DLG_INFO);

    UtlZeigeRahmen(SPA+3, ZEI+3, 9, 6,              /* Rahmen fr Maus-Ikon */
                   RT_EEEE,
                   aCS_g[wCSInd_g].wCs_dlg);

    pstrIkon = apstrIkonMaus_m;                     /* Maus-Ikon zeichnen   */
    for (zeile=3; *pstrIkon; zeile++)
        WinSs(4, zeile, *pstrIkon++);

    WinSs(SCSP+1,  SCZE-1, "langsam");              /* Texte ausgeben       */
    WinSs(SCSP+14, SCZE-1, "schnell");
    WinSs(SCSP,    SCZE-3, "aktuelles Tempo:");

    wSpeedTmp = wMausSpeed_g;                       /* akt. Tempo holen     */

    WinSs(SCSP+20, SCZE-3,                          /* aktuelles Tempo      */
          itoa(wMausSpeed_g, acZahl, 10));          /* als Zahl             */

    i_DlgMausZeichneScrollBar();                    /* Scrollbar zeichnen   */

    wSpeedTmp = i_DlgMausGetSpeed(wSpeedTmp);       /* Wahl einlesen        */

    if (wSpeedTmp == 0)                             /* Tempo nicht ndern   */
    {
        WinEntfernen(pWkbDlg);                      /* Dialog entfernen     */
        return(DLG_ESC);
    }
    else
    {
        wMausSpeed_g = wSpeedTmp;                   /* globale Var. ndern  */

        MsmSetRatio( (1495-14*wSpeedTmp)/95,        /* Geraden-Gleichung    */
                    ((1495-14*wSpeedTmp)/95)<<1);   /* durch (5,15):(100,1) */

        WinEntfernen(pWkbDlg);                      /* Dialog entfernen     */

        return(DLG_RETURN);                         /* zurck an Aufrufer   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgMausGetSpeed              Datum: 26.07.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion bearbeitet alle Eingaben der         บ
  บ                    Dialogbox.                                          บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  >0    gewhlte Geschwindigkeit                บ
  บ                          == 0  Funktion wurde mit ESC beendet          บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
WORD i_DlgMausGetSpeed(WORD wTempo)
{
    EVENT  Event;
    PEVENT pEvent;
    LONG   lScrollTicks;
    pEvent = &Event;                                /* Var. initialisieren  */

    for (;;)                                        /* Eingaberoutine       */
    {
        UtlEvent(pEvent);
        switch(pEvent->wArt)
        {
            case EVENT_TASTE:
            switch(pEvent->wTaste)
            {
                case T_LEFT:
                    wTempo = i_ChangeSpeed(wTempo, LINKS);
                    break;

                case T_RIGHT:
                    wTempo = i_ChangeSpeed(wTempo, RECHTS);
                    break;

                case T_F1:
                    DlgHilfeTools(MAUSTEMPO);
                    break;

                case T_RETURN:
                    return(wTempo);

                case T_ESC:
                    return(0);

                default:
                    if (boBeepen_g)
                        i_Beep();
            }
            break;

            case EVENT_L_PRESS:
                switch(pEvent->wZeile)
                {
                    case ZEI+SCZE+1:                       /* auf Scrollpfeilen    */
                        if (pEvent->wSpalte == SPA+SCSP+1)
                        {
                            lScrollTicks = pEvent->lTicks;
                            wTempo = i_ChangeSpeed(wTempo, LINKS);
                        }
                        else if (pEvent->wSpalte == SPA+SCSP+22)
                        {
                            lScrollTicks = pEvent->lTicks;
                            wTempo = i_ChangeSpeed(wTempo, RECHTS);
                        }
                        else if (pEvent->wSpalte > SPA+SCSP+1 &&
                                 pEvent->wSpalte < SPA+SCSP+22)
                            wTempo = i_SetzeTempo(wTempo,
                                                  pEvent->wSpalte-
                                                  SPA-SCSP-1);
                        else if (boBeepen_g)
                            i_Beep();
                        break;

                case ZEI+10:                        /* auf Schaltflchen    */
                    if (pEvent->wSpalte > SPA+2 &&
                        pEvent->wSpalte < SPA+3+strlen(pstrReturn_g))
                      return(wTempo);
                    else if (pEvent->wSpalte > SPA+16 &&
                             pEvent->wSpalte < SPA+17+strlen(pstrEsc_g))
                      return(0);
                    else if (pEvent->wSpalte > SPA + 30 &&
                             pEvent->wSpalte < SPA + 31+strlen(pstrF1_g))
                      DlgHilfeTools(MAUSTEMPO);
                    else if( boBeepen_g)
                      i_Beep();
                  break;

                default:
                    if (boBeepen_g)
                        i_Beep();
            }/* end of switch(pEvent->wZeile) */
            break;

            default:                                /* Dauerklicken unter-  */
                if (pEvent->wButton == MSM_L_DOWN &&/* sttzen              */
                    pEvent->lTicks-lScrollTicks >= SCR_DELAY &&
                    pEvent->wZeile == (ZEI+SCZE+1))
                {
                    if (pEvent->wSpalte == (SPA+SCSP+1))
                    {
                        lScrollTicks = pEvent->lTicks;
                        wTempo = i_ChangeSpeed(wTempo, LINKS);
                    }
                    else if (pEvent->wSpalte == (SPA+SCSP+22))
                    {
                        lScrollTicks = pEvent->lTicks;
                        wTempo = i_ChangeSpeed(wTempo, RECHTS);
                    }
                }
        } /* end of switch(pEvent->wEventart) */
  } /* end of for(;;) */
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_ChangeSpeed                  Datum: 19.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpeed     aktuelles Tempo                     บ
  บ                    WORD wRichtung  LINKS  == Tempo - 5                 บ
  บ                                    RECHTS == Tempo + 5                 บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fhrt die tatschliche nderung      บ
  บ                    des Tempos in der Variablen wSpeed durch.           บ
  บ                    Die nderungsrichtung ist vom Argument wRichtung    บ
  บ                    abhngig.                                           บ
  บ                    Die Funktion fhrt eine berprfung auf die         บ
  บ                    Grenzwerte durch. Sind diese noch nicht ber-       บ
  บ                    schritten, wird der Wert von wSpeed gendert.       บ
  บ                                                                        บ
  บ                    Im Falle einer nderung wird die Textausgabe des    บ
  บ                    aktuellen Wertes und die Markierung auf der         บ
  บ                    Rollleiste aktualisiert.                            บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD wSpeed  Geschwindigkeit nach Bearbeitung       บ
  บ                                 durch die Funktion                     บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boBeepen_g /(R)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
WORD i_ChangeSpeed(WORD wSpeed, WORD wRichtung)
{
    CHAR acZahl[4];
    if (wRichtung == LINKS)                         /* nach links ?         */
    {
        if (wSpeed > 5)                             /* verkleinern m”glich? */
        {
            WinSza(SCSP+(wSpeed/5), SCZE,           /* alte Marke l”schen   */
                   'ฐ', NORMAL);
            wSpeed -= 5;                            /* Tempo verkleinern    */
            WinSs(SCSP+20, SCZE-3,"   ");           /* alte Ausgabe l”schen */
            WinSs(SCSP+20, SCZE-3,                  /* neues Temp ausgeben  */
                  itoa(wSpeed, acZahl, 10));
            WinSza(SCSP+(wSpeed/5), SCZE,           /* neue Marke setzen    */
                   'ฒ', BLAU);
        }
        else if (boBeepen_g)
            i_Beep();
    }
    else if (wRichtung == RECHTS)                   /* nach rechts ?        */
    {
        if (wSpeed < 100)                           /* vergr”แern m”glich ? */
        {
            WinSza(SCSP+(wSpeed/5), SCZE,           /* alte Marke l”schen   */
                   'ฐ', NORMAL);
            wSpeed +=5;                             /* Tempo vergr”แern     */
            WinSs(SCSP+20, SCZE-3,"   ");           /* alte Ausgabe l”schen */
            WinSs(SCSP+20, SCZE-3,                  /* neues Tempo ausgeben */
                  itoa(wSpeed, acZahl, 10));
            WinSza(SCSP+(wSpeed/5), SCZE,           /* neue Marke setzen    */
                   'ฒ', BLAU);
        }
        else  if (boBeepen_g)
            i_Beep();
    }
    return(wSpeed);
}





/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgMausZeichneScrollBar      Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt nach Ermittlung des aktuellen   บ
  บ                    Grafikmodus die Scrollbar aus.                      บ
  บ                    In die Scrollbar wird der aktuelle Wert des         บ
  บ                    Maustempos eingetragen.                             บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - wVioMode_g  (R)                                   บ
  บ                    - wCSInd_g    (R)                                   บ
  บ                    modulglobale:  - wFarbe_m    (R/W)                  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_DlgMausZeichneScrollBar(VOID)
{
    REGISTER s;

    if ( wVioMode_g == MONOCHROM ||                 /* Farbattribute fest-  */
         wCSInd_g   == MNU_PAL_MONO)                /* setzen               */
        wFarbe_m = INVERS;
    else
        wFarbe_m = VH(BLAU, KOBALT);


    WinSza(SCSP, SCZE, Z_PFEIL_LINKS, wFarbe_m);    /* Pfeil links          */
    for (s=SCSP+1;s < SCSP+21;s++)                  /* Scrollbar            */
        WinSza(s, SCZE, 'ฐ', NORMAL);
    WinSza(s, SCZE, Z_PFEIL_RECHTS, wFarbe_m);      /* Pfeil rechts         */

    WinSza(SCSP+(wMausSpeed_g/5), SCZE, 'ฒ', BLAU); /* akt. Tempo mark.     */

    return;
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_SetzeTempo                   Datum: 25.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wTalt       altes Tempo                       บ
  บ                    WORD  wPosition   neue Position auf Scrollbar       บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion l”scht die Markierung auf der        บ
  บ                    Scrolleiste, berechnet anhang der bergebenen       บ
  บ                    Position das neue Tempo und markiert es auf der     บ
  บ                    Scrolleiste.                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   neues Tempo                                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
WORD i_SetzeTempo(WORD wTalt, WORD wPosition)
{
    WORD wTneu;
    CHAR acZahl[4];

    wTneu = wPosition * 5;

    WinSza(SCSP+(wTalt/5), SCZE, 'ฐ', NORMAL);      /* alte Marke l”schen   */
    WinSza(SCSP+(wTneu/5), SCZE, 'ฒ', BLAU);        /* neue Marke setzen    */

    WinSs(SCSP+20, SCZE-3,"   ");                   /* altes Tempo l”schen  */
    WinSs(SCSP+20, SCZE-3, itoa(wTneu,acZahl,10));  /* neues Tempo ausgeben */

    return(wTneu);
}


