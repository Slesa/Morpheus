/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTGLOBAL.C                     Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ    Diese Datei enthlt die Definition smtlicher globaler              บ
  บ    Variablen, die die Toolbox ben”tigt.                                บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ   (c) copyright 1988,1989 Markt & Technik Verlag AG, Haar bei Mnchen  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ               Globale Variablen fr das Dialog-Modul                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL WORD wMausSpeed_g=50;                        /* enthlt aktuelle     */
                                                    /* Geschwindigkeit der  */
                                                    /* Maus                 */

GLOBAL WORD wBeepFreq_g=200;                        /* enthlt Frequenz,    */
                                                    /* mit dem Warnton aus- */
                                                    /* gegeben wird         */

GLOBAL WORD wBeepDauer_g=2;                         /* enthlt Dauer des    */
                                                    /* Warntons in 18tel    */
                                                    /* Sekunden             */

GLOBAL BOOL boBeepen_g=JA;                          /* soll gebeept werden  */

GLOBAL PSTR pstrReturn_g = "<ฤู=Eingabe";           /* Texte fr Schalt-    */
GLOBAL PSTR pstrEsc_g    = "Esc=Abbruch";           /* flchen des Dialog-  */
GLOBAL PSTR pstrF1_g     = "F1=Hilfe";              /* moduls               */
GLOBAL PSTR pstrRetry_g  = "<ฤู=Wiederholen";


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ    Array cRahmenzeichen_g enthlt die Definition der Rahmentypen       บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
CHAR cRahmenzeichen_g[][8] =
{
    {'ฺ', 'ฟ', 'ภ', 'ู', 'ฤ', 'ฤ', 'ณ', 'ณ'},               /* RT_EEEE    0 */
    {'ึ', 'ฟ', 'ำ', 'ู', 'ฤ', 'ฤ', 'บ', 'ณ'},               /* RT_EEED    1 */
    {'ฺ', 'ฟ', 'ิ', 'พ', 'ฤ', 'อ', 'ณ', 'ณ'},               /* RT_EEDE    2 */
    {'ึ', 'ฟ', 'ศ', 'พ', 'ฤ', 'อ', 'บ', 'ณ'},               /* RT_EEDD    3 */

    {'ฺ', 'ท', 'ภ', 'ฝ', 'ฤ', 'ฤ', 'ณ', 'บ'},               /* RT_EDEE    4 */
    {'ึ', 'ท', 'ำ', 'ฝ', 'ฤ', 'ฤ', 'บ', 'บ'},               /* RT_EDED    5 */
    {'ฺ', 'ท', 'ิ', 'ผ', 'ฤ', 'อ', 'ณ', 'บ'},               /* RT_EDDE    6 */
    {'ึ', 'ท', 'ศ', 'ผ', 'ฤ', 'อ', 'บ', 'บ'},               /* RT_EDDD    7 */

    {'ี', 'ธ', 'ภ', 'ู', 'อ', 'ฤ', 'ณ', 'ณ'},               /* RT_DEEE    8 */
    {'ษ', 'ธ', 'ำ', 'ู', 'อ', 'ฤ', 'บ', 'ณ'},               /* RT_DEED    9 */
    {'ี', 'ธ', 'ิ', 'พ', 'อ', 'อ', 'ณ', 'ณ'},               /* RT_DEDE   10 */
    {'ษ', 'ธ', 'ศ', 'พ', 'อ', 'อ', 'บ', 'ณ'},               /* RT_DEDD   11 */

    {'ี', 'ป', 'ภ', 'ฝ', 'อ', 'ฤ', 'ณ', 'บ'},               /* RT_DDEE   12 */
    {'ษ', 'ป', 'ำ', 'ฝ', 'อ', 'ฤ', 'บ', 'บ'},               /* RT_DDED   13 */
    {'ี', 'ป', 'ิ', 'ผ', 'อ', 'อ', 'ณ', 'บ'},               /* RT_DDDE   14 */
    {'ษ', 'ป', 'ศ', 'ผ', 'อ', 'อ', 'บ', 'บ'},               /* RT_DDDD   15 */
};





/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                Globale Variablen fr das Window-Modul                  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL  WORD    wS_g=0;                             /* Die Koordinaten be-  */
GLOBAL  WORD    wZ_g=0;                             /* schreiben die Data-  */
GLOBAL  WORD    wB_g=MAXSPALTEN;                    /* Area des aktuellen   */
GLOBAL  WORD    wH_g=MAXZEILEN;                     /* Windows.             */

GLOBAL  WORD    wAttribut_g=0x07;                   /* Attribut des Fenster-*/

GLOBAL  WORD    wAktWin_g = 0;                      /* Index des aktiven W. */
                                                    /* in ฏapWkbSichtbar[]ฎ */

GLOBAL  FPWORD  fpwCopyBuffer_g = 0L;               /* Zeiger auf 4K-Buffer */

WKB WkbScreen = { WKBSIGNATUR,                      /* Screen WKB initiali- */
                  (WORD)-1, (WORD) -1, 82, 27,      /* sieren, Gr”แe        */
                   0, 0, 0, 0,                      /* Cursor               */
                   0, 0, 7,                         /* Attribute            */
                   NULL,                            /* Pointer auf Titel    */
                   0,                               /* keine Schnittflche  */
                   {0,0, 0,1,0,1,0,0,0,0},          /* winFlags             */
                   0L};                             /* Puffer               */


GLOBAL PWKB apWkbSichtbar_g[16] = {&WkbScreen};     /* Array v. Zeigern auf */
                                                    /* WKB der sichtbaren W.*/
                                                    /* innneren.            */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ            Globale Variablen fr das Men-Modul                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL MENU aMenus_g[MAXMENUES];                    /* Array aus MAXMENUES  */
                                                    /* Elementen vom Struk- */
                                                    /* turtyp MENU          */

GLOBAL WORD wAktMnu_g = NICHT_INIT;                 /* Index auf aMenus_g   */
                                                    /* Nummer des aktiven   */
                                                    /* Mens                */

GLOBAL FPWORD fpwAlteMZ_g;                          /* Zeiger auf Puffer,   */
                                                    /* Bildschirminh. unter */
                                                    /* aktuellen Menzeile  */
                                                    /* enthlt              */

GLOBAL FPWORD fpwAlteHZ_g;                          /* Zeiger auf Puffer,   */
                                                    /* Bildschirminh. unter */
                                                    /* Hilfszeile (24)      */

GLOBAL MENUSTATUS MS_g;                             /* Status Menmanager   */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  wFehler_g enthlt immer die Nummer des letzten aufgetretenen Fehlers  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL WORD wFehler_g=0;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ   Statusinformationen ber die Hardware, in der das Programm luft     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL WORD wMausda_g=NEIN;                         /* enthlt JA wenn Maus */
                                                    /* erfolgreich initia-  */
                                                    /* lisiert wurden       */

GLOBAL WORD wVioMode_g=NICHT_INIT;                  /* enthlt aktuellen    */
                                                    /* Video-Modus          */



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ           Farbpaletten, Initialisierung des Arrays aCS_g[]             บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
COLORSET aCS_g[5]=
{
    { /* ษออออออออออออออออออออออออออออออออออออออออออออออออออออออป
         บ                 BLAUE  PALETTE                       บ
         ศออออออออออออออออออออออออออออออออออออออออออออออออออออออผ */
        VH(SCHWARZ,KOBALT),         /* Farbe des Arbeitsbereiches           */

                                    /* Menzeile                            */
        VH(SCHWARZ,WEISS),          /*   normaler Text                      */
        VH(HELLWEISS,BLAU),         /*   Auswahlcursor                      */
        VH(BLAU, WEISS),            /*   Hotkeys                            */

                                    /* Menfenster */
        VH(SCHWARZ, WEISS),         /*   Rahmen, Innen, normaler Text       */
        VH(HELLWEISS, ROT),         /*   Auswahlcursor auf aktiver Option   */
        VH(WEISS, BLAU),            /*   Auswahlcursor auf inaktiver Option */
        VH(GRAU, WEISS),            /*   Farbattribut Text inaktive Option  */
        VH(BLAU, WEISS),            /*   Hotkeys                            */

        VH(BLAU, WEISS),            /* Hilfszeile                           */

        VH(WEISS, BLAU),            /* Dialogfenster                        */
        VH(BRAUN, SCHWARZ),         /*    Schaltflchen                     */
        VH(SCHWARZ, WEISS),         /*    Titelzeile                        */
        VH(WEISS, SCHWARZ),         /*    Titeltext                         */
        VH(HELLROT, BLAU),          /*    Scrollpfeile                      */
        VH(HELLWEISS, BLAU),        /*    Hervorhebungen                    */

        VH(SCHWARZ, BRAUN),         /* Warnungsfenster                      */
        VH(HELLWEISS, ROT),         /*    kritische Fehler                  */
        VH(HELLWEISS, BLAU),        /*    Schaltflchen bei Warnungen und   */
                                    /*    kritischen Fehlern                */

    },


    { /* ษออออออออออออออออออออออออออออออออออออออออออออออออออออออป
         บ                 WEISSE PALETTE                       บ
         ศออออออออออออออออออออออออออออออออออออออออออออออออออออออผ */
        VH(SCHWARZ,WEISS),          /* Farbe des Arbeitsbereiches           */

                                    /* Menzeile                            */
        VH(SCHWARZ,WEISS),          /*   normaler Text                      */
        VH(HELLWEISS, SCHWARZ),     /*   Auswahlcursor                      */
        VH(ROT,WEISS),              /*   Hotkeys                            */

                                    /* Menfenster                          */
        VH(SCHWARZ, WEISS),         /*   Rahmen, Innen, normaler Text       */
        VH(HELLWEISS, SCHWARZ),     /*   Auswahlcursor auf aktiver Option   */
        VH(WEISS, SCHWARZ),         /*   Auswahlcursor auf inaktiver Option */
        VH(GRAU, WEISS),            /*   Farbattribut Text inaktive Option  */
        VH(ROT, WEISS),             /*   Hotkeys                            */

        VH(WEISS,SCHWARZ),          /* Hilfszeile                           */

        VH(SCHWARZ, WEISS),         /* Dialogfenster                        */
        VH(WEISS, BLAU),            /*   Schaltflchen                      */
        VH(SCHWARZ, WEISS),         /*   Titelzeile                         */
        VH(SCHWARZ, WEISS),         /*   Titeltext                          */
        VH(SCHWARZ, WEISS),         /*   Scrollpfeile                       */
        VH(ROT, WEISS),             /*   Hervorhebungen                     */

        VH(SCHWARZ, BRAUN),         /* Warnungsfenster                      */
        VH(HELLWEISS, ROT),         /*   kritische Fehler                   */
        VH(HELLWEISS, BLAU),        /*   Schaltflchen bei Warnungen und    */
                                    /*   kritischen Fehlern                 */

    },


    { /* ษออออออออออออออออออออออออออออออออออออออออออออออออออออออป
         บ                 KOBALT PALETTE                       บ
         ศออออออออออออออออออออออออออออออออออออออออออออออออออออออผ */
        VH(SCHWARZ,BLAU),           /* Farbe des Arbeitsbereiches           */

                                    /* Menzeile                            */
        VH(SCHWARZ,KOBALT),         /*   normaler Text                      */
        VH(HELLWEISS, ROT),         /*   Auswahlcursor                      */
        VH(ROT,KOBALT),             /*   Hotkeys                            */

                                    /* Menfenster                          */
        VH(SCHWARZ, KOBALT),        /*   Rahmen, Innen, normaler Text       */
        VH(HELLWEISS, ROT),         /*   Auswahlcursor auf aktiver Option   */
        VH(WEISS, SCHWARZ),         /*   Auswahlcursor auf inaktiver Option */
        VH(GRAU, KOBALT),           /*   Farbattribut Text inaktive Option  */
        VH(ROT,KOBALT),             /*   Hotkeys                            */

        VH(SCHWARZ,KOBALT),         /* Hilfszeile                           */

        VH(SCHWARZ, WEISS),         /* Dialogfenster                        */
        VH(SCHWARZ, KOBALT),        /*   Schaltflchen                      */
        VH(SCHWARZ, WEISS),         /*   Titelzeile                         */
        VH(SCHWARZ, KOBALT),        /*   Titeltext                          */
        VH(BLAU, WEISS),            /*   Scrollpfeile                       */
        VH(BLAU, WEISS),            /*   Hervorhebungen                     */

        VH(SCHWARZ, BRAUN),         /* Warnungsfenster                      */
        VH(HELLWEISS, ROT),         /* kritische Fehler                     */
        VH(HELLWEISS, BLAU),        /* Schaltflchen bei Warnungen und      */
                                    /* kritischen Fehlern                   */

    },


    { /* ษออออออออออออออออออออออออออออออออออออออออออออออออออออออป
         บ                 SCHWARZE PALETTE                     บ
         ศออออออออออออออออออออออออออออออออออออออออออออออออออออออผ */
        VH(SCHWARZ,WEISS),          /* Farbe des Arbeitsbereiches           */

                                    /* Menzeile                            */
        VH(SCHWARZ,WEISS),          /*   normaler Text                      */
        VH(WEISS, SCHWARZ),         /*   Auswahlcursor                      */
        VH(BLAU,WEISS),             /*   Hotkeys                            */

                                    /* Menfenster                          */
        VH(SCHWARZ, WEISS),         /*   Rahmen, Innen, normaler Text       */
        VH(HELLWEISS, SCHWARZ),     /*   Auswahlcursor auf aktiver Option   */
        VH(WEISS, SCHWARZ),         /*   Auswahlcursor auf inaktiver Option */
        VH(GRAU, WEISS),            /*   Farbattribut Text inaktive Option  */
        VH(BLAU,WEISS),             /*   Hotkeys                            */

        VH(SCHWARZ,WEISS),          /* Hilfszeile                           */

        VH(SCHWARZ, WEISS),         /* Dialogfenster                        */
        VH(HELLWEISS, SCHWARZ),     /*   Schaltflchen                      */
        VH(SCHWARZ, WEISS),         /*   Titelzeile                         */
        VH(HELLWEISS, SCHWARZ),     /*   Titeltext                          */
        VH(ROT, WEISS),             /*   Scrollpfeile                       */
        VH(ROT, WEISS),             /*   Hervorhebungen                     */

        VH(SCHWARZ, BRAUN),         /* Warnungsfenster                      */
        VH(HELLWEISS, ROT),         /*   kritische Fehler                   */
        VH(HELLWEISS, BLAU),        /*   Schaltflchen bei Warnungen und    */
                                    /*   kritischen Fehlern                 */
    },

    { /* ษออออออออออออออออออออออออออออออออออออออออออออออออออออออป
         บ              MONOCHROME PALETTE                      บ
         ศออออออออออออออออออออออออออออออออออออออออออออออออออออออผ */
        NORMAL,                     /* Farbe des Arbeitsbereiches           */

                                    /* Menzeile                            */
        INVERS,                     /*   normaler Text                      */
        NORMAL,                     /*   Auswahlcursor                      */
        MATT_INVERS,                /*   Hotkeys                            */

                                    /* Menfenster                          */
        NORMAL,                     /*   Rahmen, Innen, normaler Text       */
        INVERS,                     /*   Auswahlcursor auf aktiver Option   */
        MATT_INVERS,                /*   Auswahlcursor auf inaktiver Option */
        NORMAL,                     /*   Farbattribut Text inaktive Option  */
        HELL,                       /*   Hotkeys                            */

        INVERS,                     /* Hilfszeile                           */

        NORMAL,                     /* Dialogfenster                        */
        NORMAL,                     /*   Schaltflchen                      */
        INVERS,                     /*   Titelzeile                         */
        INVERS,                     /*   Titeltext                          */
        HELL,                       /*   Scrollpfeile                       */
        HELL,                       /*   Hervorhebungen                     */

        MATT_INVERS,                /* Warnungsfenster                      */
        INVERS,                     /*   kritische Fehler                   */
        HELL,                       /*   Schaltflchen bei Warnungen und    */
                                    /*   kritischen Fehlern                 */
    },
};


GLOBAL WORD wCSInd_g=NICHT_INIT;                    /* Index auf aCS_g,     */
                                                    /* enthlt Nummer der   */
                                                    /* aktive Farbpalette   */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                       Ende der Datei                                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
