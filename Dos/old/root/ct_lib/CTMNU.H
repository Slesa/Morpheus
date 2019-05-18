/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTMNU.H                        Datum: 16.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ    Diese Datei enthlt die symbolischen Konstanten, Struktur-          บ
  บ    Deklarationen und Funktions-Prototypen fr den                      บ
  บ    Men-Manager.                                                       บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_MENU_HEADER
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define HOTKEY          '#'          /* Zeichen zur Markierung des Hotkeys  */

#define RAHMENSPALTEN   5            /* zu lngstem Text add. = Menbreite  */
                                     /* 2 fr den Rahmen, je eine Leerzeile */
                                     /* rechts und links, ein Zeichen fr   */
                                     /* die Markierung "๛"                  */

#define RAHMENZEILEN    2            /* zu Anzahl der Optionen add. = H”he  */

#define MENUZEILE       0            /* Zeile fr Ausgabe der Menzeile     */
#define FENSTERZEILE      1          /* Zeile fr alle Menfenster          */

#define MENUSTARTSPALTE 1            /* Spalte des ersten Mentitel         */
#define MNU_LEERZEICHENSTART 2
#define MNU_ABSTAND_TITEL     2      /* Abstand der einzelnen Mentitel     */
#define HILFSZEILE      24           /* Zeile fr Hilfs-Informationen       */


#define MAXMENUES       10

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                    bergabe an i_MnuToBuffer()                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define MNU_INIT        0
#define MNU_AENDERN     1

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ               bergabe an i_MnuBalken() und i_MnuTitel()               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define EIN_REL  20
#define EIN_ABS  21



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                    bergabe an MnuSetPalette()                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define MNU_PAL_BLAU    0                           /* Farbpaletten und     */
#define MNU_PAL_WEISS   1                           /* deren Kennziffern    */
#define MNU_PAL_KOBALT  2
#define MNU_PAL_SCHWARZ 3
#define MNU_PAL_MONO    4

#define MKBSIGNATUR     0x4D4B       /* Testsignatur fr Menkontrollblock   */
#define COLORSIGNATUR   0x4353       /* Testsignatur fr Farbsets            */


#define MNU_TRENNER     {NULL, "TRENNER",  NULL }
#define MNU_ENDE        {NULL, NULL, NULL }
#define RECHTSBUENDIG    31000

#define I_FEHLER_MEM        0
#define I_FEHLER_MNHOEHE    2
#define I_FEHLER_MNLANG     3
#define I_FEHLER_ANZHTEXTE  4
#define I_FEHLER_ZEIGERWEG  5
#define I_FEHLER_INDEX      6
#define I_FEHLER_AKT_FKT    7

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Konstanten, deren Wert im Fehlerfalle nach wFehler_g geladen werden   บ
  บ  alle Fehlernummern fr das Mnu-Modul sind liegen im Berech 101..199   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define MNU_KEIN_FEHLER      0  /* kein Fehler aufgetreten                   */
#define MNU_KEIN_PMKB      101  /* kein gltiger Zeiger auf einen MKB        */
#define MNU_ZU_GROSS       102  /* Fensterdimensionen ungltig               */
#define MNU_KEIN_SPEICHER  103  /* Ihr Rechner kann sich nichts merken       */
#define MNU_FALSCHE_OPT    104  /* gewhlte Option nicht vorhanden           */
#define MNU_TITEL_LAENGE   105  /* Titel zu lang                             */
#define MNU_AUSSERHALB     106  /* Koordinaten liegen auแerhalb des Windows  */
#define MNU_LIMIT          107  /* Men zu groแ                              */
#define MNU_NICHT_SICHTBAR 108  /* Inaktive Fenster k”nnen nicht versteckt w.*/
#define MNU_NICHT_REG      109  /* Das W. ist nicht als sichtbar registriert */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ       Konstanten zur bergabe an MnuMarker() und MnuOption()           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define AUS             0
#define EIN             1
#define DREHEN          2
#define STATUS          3


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        STRUKTURDEKLARATIONEN                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
typedef struct
{
    WORD    wOption;
    PSTR    pstrText;
    PSTR    pstrHilfstext;
} ITEM;

typedef ITEM* PITEM;

typedef struct tagHK
{
    unsigned wKey    : 14;           /* Hotkey fr Option                   */
    unsigned wMarker : 1;            /* Marker vor Text: 0=nein, 1=ja       */
    unsigned wAktiv  : 1;            /* Option aktiv:    0=nein, 1=ja       */
    unsigned wOpt;                   /* Optionsnummer fr diese Taste       */
};

typedef struct
{
    WORD     wAktiv   : 1;           /* Menmanager aktiv   0=nein, 1=ja    */
    WORD     wTitel   : 1;           /* Titel markiert      0=nein, 1=ja    */
    WORD     wFenster : 1;           /* Fenster sichtbar    0=nein, 1=ja    */
    WORD     wBalken  : 1;           /* Balken sichtbar     0=nein, 1=ja    */
    WORD     wDummy   : 12;          /* zum Auffllen auf 16 Bit            */
}MENUSTATUS;


typedef struct tagMKB
{
    WORD           wMkbsign;         /* Menfensterkontrollblock-Signatur   */
    WORD           wFensterId;       /* Identifikationsnr. des Menfensters */
    WORD           wTitelSpalte;     /* Startspalte und Breite der Schalt-  */
    WORD           wTitelBreite;     /*   flche zum Aktivieren per Maus    */
    WORD           wSpalte;          /* linke obere Spalte des Menfensters */
    WORD           wBreite;          /* Breite des Menfensters ink. Rahmen */
    WORD           wHoehe;           /* H”he des Menfensters inkl. Rahmen  */
    WORD           wBalPos;          /* Nummer der markierten Option        */
    WORD           wBalIndex;        /* Index der akt. Option auf pHotkeys  */
    ITEM           *item;            /* Zeiger auf ITEM Struktur            */
    WORD           wItemAnzahl;      /* Anzahl der Menitems                */
    WORD           wMzHotkey;        /* Taste zur Aktivierung des Fensters  */
    FPWORD         fpwBuffer;        /* Puffer mit 1:1 - Menfenster        */
    struct tagHK   *pHotkeys;        /* Zeiger auf Hotkeys                  */
    struct tagMKB  *pVoriger;        /* Zeiger auf das vorige Element       */
    struct tagMKB  *pNaechster;      /* Zeiger auf das nchste Element      */
} MKB;

typedef MKB* PMKB;

typedef struct
{
    WORD        wSchatten    :1;     /* Schatten   : Nein=0, Ja=1           */
    WORD        wRahmentyp   :1;     /* Rahmentyp  : Einfach=0, Doppelt=1   */
    WORD        wPalette     :3;     /* Farbpalette: 0..4                   */
    WORD        wHzeile      :1;     /* Hilfstexte da       0=nein, 1=ja    */
    WORD        wDummy       :10;    /* auf WORD-Gr”แe auffllen            */
} MKB_STATUS;

typedef struct
{
    MKB         *pMkbStart;          /* Zeiger auf MKB des 1. Menfensters  */
    MKB_STATUS  wStatus;             /* Status dieses Mens                 */
    FPWORD      fpwMzBuffer;         /* enthlt die komplette Menzeile     */
} MENU;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        FUNKTIONS-PROTOTYPEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL PMKB  MnuEinrichten  (WORD, ITEM *);
GLOBAL WORD  MnuAktivieren  (WORD);
GLOBAL WORD  MnuDeaktivieren(VOID);
GLOBAL WORD  MnuEntfernen   (WORD);
GLOBAL VOID  MnuEingabe     (PEVENT);

GLOBAL WORD  MnuSetPalette  (WORD, WORD);
GLOBAL WORD  MnuSetRahmenTyp(WORD, WORD);
GLOBAL WORD  MnuSetSchatten (WORD, WORD);

GLOBAL WORD  MnuOption      (WORD, WORD);
GLOBAL WORD  MnuMarker      (WORD, WORD);

#define CT_MENU_HEADER 1
#endif
