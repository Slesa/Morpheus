/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTDLG.H                        Datum: 10.11.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ   Diese Datei enthlt die symbolichen Konstanten, Makros und           บ
  บ   Funktions-Prototypen fr das Dialog-Modul der Toolbox.               บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_DIALOG_HEADER     /* wiederholtes Einlesen der Datei verhindern  */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                     DEKLARATIONS-DATEIEN                               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                Konstanten fr Hilfsbildschirme                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define TEXTZEILEN   8                              /* Anzahl Hilfszeilen   */
#define MINZEILEN    5                              /* min. Anzahl Hilfsz.  */
#define HILFEZEILE   7                              /* Position der Hilfe-  */
#define HILFESPALTE 11                              /* fenster              */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ            Konstanten zur bergabe an i_DlgScroll()                    บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define UP 6                                        /* Parameter an         */
#define DOWN 7                                      /*  i_DlgHilfeScroll    */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  verschiedene Konstanten, Deklaration der TEXTBOX-Struktur i_LiesZk()  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define TB_MAX 128          /* maximale Lnge des zu editierenden Textes    */

typedef struct {
    CHAR acText[TB_MAX];    /* zu editierender Text                         */
    WORD wAttri;            /* Attribut der Textbox                         */
    WORD wFensterS;         /* Spalte auแen links, abs. Koordinaten         */
    WORD wFensterZ;         /* Zeile, absolute Koordinaten                  */
    WORD wFensterB;         /* Breite des sichtbaren editierten Textes      */
    WORD wCursorS;          /* aktuelle Spalte des Cursors                  */
    WORD wMaxL;             /* Lnge des Strings, der editiert werden soll  */
    BOOL boInsert;          /* Insertmodus default: WAHR                    */
} TEXTBOX;

typedef TEXTBOX* PTEXTBOX;  /* Zeiger auf TEXTBOX                           */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                 bergabekonstanten an i_DLgLiesZK()                    บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define AKT_BUFFER      0           /* Struktur der Fkt. initialisieren     */
#define AKT_TEXTBOX     1           /* Text in TEXTBOX-Struktur ndern      */
#define AKT_GARNIX      2           /* gar nichts init., Event bearbeiten   */



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ      Konstanten als Rckgabewerte einiger der Dlg..-Funktionen         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define DLG_ESC          0x00
#define DLG_RETURN       0x01
#define DLG_ERROR        0x02



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ        Information ber gewnschte Schaltflchen an i_DlgInit()        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SF_EINGABE            0x0001
#define SF_ABBRUCH            0x0002
#define SF_HILFE              0x0004
#define SF_STANDARD           (SF_EINGABE | SF_ABBRUCH | SF_HILFE)
#define SF_JANEIN             0x0008
#define SF_JANEINABBRUCH      0x0010
#define SF_RETRYCANCEL        0x0020
#define SF_ABORTRETRYIGNORE   0x0040


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                    bergabeparameter an DlgInfo()                      บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define DLG_INFO            0
#define DLG_WARNUNG         1
#define DLG_KRITISCH        2


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                bergabeparameter an DlgHilfeTools()                    บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define FARBPALETTE 500
#define DOSSHELL    501
#define WARNTON     502
#define MAUSTEMPO   503
#define SPEICHERN   504
#define LADEN       505
#define DLGINDEX    506


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ               Strukturdeklaration fr DlgHilfeIndex()                  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
typedef struct
{
    PSTR pstrText;
    WORD wRueckgabe;
} HILFEINDEX;

typedef HILFEINDEX* PHILFEINDEX;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                      FUNKTIONS-PROTOTYPEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL WORD  DlgMausTempo      (VOID);
GLOBAL WORD  DlgFarbPalette    (VOID);
GLOBAL WORD  DlgWarnton        (VOID);

GLOBAL WORD  DlgPutOptionen    (PSTR);
GLOBAL WORD  DlgGetOptionen    (PSTR);

GLOBAL WORD  DlgHilfe          (PSTR, PPSTR);
GLOBAL WORD  DlgHilfeIndex     (PHILFEINDEX);
GLOBAL VOID  DlgHilfeTools     (WORD);

GLOBAL WORD  DlgInfo           (PPSTR, WORD);
GLOBAL WORD  DlgNachricht      (PPSTR, WORD, WORD);

GLOBAL WORD  DlgSpeichernUnter (PSTR, WORD);
GLOBAL WORD  DlgLaden          (PSTR);
GLOBAL WORD  DlgShell          (PSTR);

#define CT_DIALOG_HEADER 1
#endif
