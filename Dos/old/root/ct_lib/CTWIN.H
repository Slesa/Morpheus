/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTWIN.H                        Datum: 12.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ       Diese Datei enthlt die Bezeichner, Makros und                   บ
  บ       Funktions-Prototypen fr die Tools des                           บ
  บ       Window-Moduls.                                                   บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_WINDOW_HEADER                 /* wiederholtes Einlesen vermeiden */

#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                   VERSCHIEDENE KONSTANTEN UND MAKROS                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

#define WKBSIGNATUR   0x4B52      /* Testsignatur fr Windowkontrollblock   */

#define WinKoordInDA(s,z)   (   (s) >= 0       \
                             && (s) <= wB_g-1  \
                             && (z) >= 0       \
                             && (z) <= wH_g-1 )

#define WinZeileInDA(z)     ( ((z) >= 0) && ((z) <= wH_g -1) )

#define WinSpalteInDA(s)    ( ((s) >= 0) && ((s) <= wB_g -1) )

#define WinIncSpalte(s)     ( (s) == wB_g-1 ) ? 0 : (s)+1

#define WinIncZeile(z)      ( (z) == wH_g-1 ) ? 0 : (z)+1

#define WinDAexistiert()    ( (wB_g) && (wH_g) )


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        STRUKTURDEKLARATIONEN                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
typedef struct
{
    WORD    wRahmentyp  :5;          /* default:  0 == RT_EEEE              */
    WORD    wTitelPos   :3;          /* default:  1 == WIN_TITEL_OZ         */

    WORD    wSchatten   :1;          /* default:  0 == kein Schatten        */
    WORD    wCursorAn   :1;          /* default:  0 == Cursor aus           */
    WORD    wVersteckt  :1;          /* default:  0 == nicht versteckt      */
    WORD    wSichtbar   :1;          /* default:  0 == nicht sichtbar       */
    WORD    wDialogTyp  :1;          /* default:  0 == kein Dialogtyp       */
    WORD    wTRaendern  :1;          /* default:  0 == Titel + Rahmen nicht */
                                     /*                gendert             */
    WORD    wDAaendern  :1;          /* default:  0 == Data-Area unverndert*/
        WORD    dummy       :1;          /* zum Auffllen auf 16 Bit            */
}WIN_FLAGS;


typedef struct tagWKB
{
    WORD           wWkbsign;         /* Windowkontrollblock-Signatur        */

    WORD           wSpalte;          /* linke obere Spalte des Rahmens      */
    WORD           wZeile;           /* oberste Zeile des Rahmens           */
    WORD           wBreite;          /* Breite des Windows inkl. Rahmen     */
    WORD           wHoehe;           /* H”he des Windows inkl. Rahmen       */

    WORD           wCursorspalte;    /* default 0                           */
    WORD           wCursorzeile;     /* default 0                           */
    WORD           wCursorstart;     /* Monochrom 11, Farbe 6               */
    WORD           wCursorstop;      /* Monochrom 12, Farbe 7               */

    WORD           wTitelAttr;       /* nach SAA-Standard */
    WORD           wRahmenAttr;      /* nach SAA-Standard */
    WORD           wInnenAttr;       /* nach SAA-Standard */

    PSTR           pstrTitel;        /* default NULL                        */

    WORD           wSchnitte;        /* bitweise Information . gemeinsame  */
                                     /* Schnittflchen der sichtb. Fenster  */

    WIN_FLAGS      winFlags;         /* siehe Strukturdeklaration           */

    FPWORD         fpwBuffer;        /* erhlt alten Bildschirminhalt       */

} WKB;

typedef WKB* PWKB;



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ         bergabe-Parameter fr Titel-Position an WinSetTitel()         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define WIN_TITEL_OL    0      /*  oben, linksbndig                        */
#define WIN_TITEL_OZ    1      /*  oben, zentriert                          */
#define WIN_TITEL_OR    2      /*  oben, rechtsbndig                       */
#define WIN_TITEL_UL    3      /*  unten, linksbndig                       */
#define WIN_TITEL_UZ    4      /*  unten, zentriert                         */
#define WIN_TITEL_UR    5      /*  unten, rechtsbndig                      */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ          M”gliche Werte von wFehler_g nach Funktionsaufrufen           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define WIN_KEIN_FEHLER     0  /* kein Fehler aufgetreten                   */
#define WIN_KEIN_PWKB       1  /* kein gltiger Zeiger auf einen WKB        */
#define WIN_ZU_GROSS        2  /* Fensterdimensionen ungltig               */
#define WIN_KEIN_SPEICHER   3  /* Ihr Rechner kann sich nichts merken       */
#define WIN_FALSCHE_OPT     4  /* gewhlte Option nicht vorhanden           */
#define WIN_TITEL_LAENGE    5  /* Titel zu lang                             */
#define WIN_AUSSERHALB      6  /* Koordinaten liegen auแerhalb des Windows  */
#define WIN_LIMIT           7  /* zu viele Fenster sichtbar                 */
#define WIN_NICHT_SICHTBAR  8  /* Inaktive Fenster k”nnen nicht versteckt w.*/
#define WIN_NICHT_REG       9  /* Das W. ist nicht als sichtbar registriert */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                      FUNKTIONS-PROTOTYPEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL PWKB    WinEinrichten  (WORD, WORD, WORD, WORD);
GLOBAL WORD    WinAktivieren  (PWKB);
GLOBAL WORD    WinVerstecken  (PWKB);
GLOBAL WORD    WinEntfernen   (PWKB);

GLOBAL WORD    WinSetRahmentyp (PWKB, WORD);
GLOBAL WORD    WinSetTitel     (PWKB, PSTR, WORD);
GLOBAL WORD    WinSetAttri     (PWKB, WORD, WORD, WORD);
GLOBAL WORD    WinSchattenEin  (PWKB );

GLOBAL WORD    WinSetCursorTyp (WORD, WORD);
GLOBAL WORD    WinSetCursorPos (WORD, WORD);
GLOBAL VOID    WinGetCursor    (PWORD, PWORD, PWORD, PWORD, PWORD);
GLOBAL WORD    WinCursor       (WORD);

GLOBAL VOID    WinSa    (WORD, WORD, WORD);
GLOBAL WORD    WinLa    (WORD, WORD);
GLOBAL VOID    WinSz    (WORD, WORD, CHAR);
GLOBAL CHAR    WinLz    (WORD, WORD);
GLOBAL VOID    WinSza   (WORD, WORD, CHAR, WORD);
GLOBAL WORD    WinLza   (WORD, WORD);

GLOBAL VOID    WinSs    (WORD, WORD, PSTR);
GLOBAL VOID    WinSsa   (WORD, WORD, PSTR, WORD);

GLOBAL VOID    WinSwa   (WORD, WORD, WORD, WORD, WORD);
GLOBAL VOID    WinSwz   (WORD, WORD, WORD, WORD, CHAR);
GLOBAL VOID    WinSwza  (WORD, WORD, WORD, WORD, CHAR, WORD);
GLOBAL VOID    WinSb2w  (WORD, WORD, WORD, WORD, FPWORD);
GLOBAL VOID    WinSw2b  (WORD, WORD, WORD, WORD, FPWORD);

GLOBAL SWORD   WinPrintf(const PCHAR pcFormat,...);
GLOBAL WORD    WinTabsAbstand(WORD);
GLOBAL VOID    WinPutch (CHAR);
GLOBAL VOID    WinCputs (PSTR);

GLOBAL VOID    WinScrollUp       (WORD);
GLOBAL VOID    WinScrollDown     (WORD);
GLOBAL VOID    WinCls            (VOID);
GLOBAL VOID    WinZeileLoeschen  (WORD);
GLOBAL VOID    WinZeileEinfuegen (WORD);

GLOBAL BOOL    WinIsAktiv(PWKB);
GLOBAL PWKB    WinGetAktivPwkb(VOID);

//#ifndef WINSAVEBACK
//extern WORD WinSaveBack;
//#endif

#define CT_WINDOW_HEADER 1
#endif
