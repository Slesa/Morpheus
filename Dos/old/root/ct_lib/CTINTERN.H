/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTINTERN.H                     Datum: 10.11.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ     Diese Datei enthlt Konstanten, Makros und Funktions-              บ
  บ     Prototypen, die von der Toolbox intern genutzt werden.             บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_INTERN_HEADER

#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_WINDOW_HEADER
#include <ctwin.h>
#endif

#ifndef CT_MENU_HEADER
#include <ctmnu.h>
#endif

#ifndef CT_DIALOG_HEADER
#include <ctdlg.h>
#endif


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                 Strukturdeklaration des Typs COLORSET                  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
typedef struct
{
    WORD   wCs_ca;              /* Farbe des Arbeitsbereiches              */

    WORD   wCs_mz;              /* Farbattribut der Menzeile              */
    WORD   wCs_mz_c;            /* Farbattribut des Cursors in Menzeile   */
    WORD   wCs_mz_hk;           /* Vordergrundfarbe Hotkeys in Menzeile   */

    WORD   wCs_mf;              /* Farbattribut der Menfenster            */
    WORD   wCs_mf_ca;           /* Farbattribut Cursor auf aktiv. Option   */
    WORD   wCs_mf_ci;           /* Farbattribut Cursor auf inaktiv. Option */
    WORD   wCs_mf_ti;           /* Farbattribut Text inaktive Option       */
    WORD   wCs_mf_hk;           /* Vordergrundfarbe Hotkeys in Menfenster */

    WORD   wCs_hz;              /* Farbattribut der Hilfszeile             */

    WORD   wCs_dlg;             /* Farbattribut allgemeine Dialogfenster    */
    WORD   wCs_dlg_sf;          /* Farbe der Schaltflchen                  */
    WORD   wCs_dlg_tz;          /* Farbe der Titelzeile, Zeile 0 in DlgWin  */
    WORD   wCs_dlg_tt;          /* Farbe des Titeltextes in DlgWin          */
    WORD   wCs_dlg_sp;          /* Farbe der Scrollpfeile                   */

    WORD   wCs_dlg_hi;          /* hervorgehobene Buchstaben                */

    WORD   wCs_wdlg;            /* Farbattribut Warnungsfenster             */
    WORD   wCs_fdlg;            /* Farbattribut kritische Fehler            */
    WORD   wCs_wdlg_sf;         /* Farbattribut Schaltflchen in Warnungen  */
}COLORSET;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ        Konstanten zur bergabe der Fehlerart an i_Fehler()             บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define I_FEHLER_MEM        0
#define I_FEHLER_SIGN       1
#define I_FEHLER_MNHOEHE    2
#define I_FEHLER_MNLANG     3
#define I_FEHLER_ANZHTEXTE  4
#define I_FEHLER_ZEIGERWEG  5
#define I_FEHLER_INDEX      6
#define I_FEHLER_AKT_FKT    7
#define I_FEHLER_KETTE_PUTT 8
#define I_FEHLER_DOPPEL_ID  9




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                    FUNKTIONS-PROTOTYPEN                                บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL VOID  i_Fehler          (WORD, PSTR, PSTR, WORD);
GLOBAL VOID  i_InitVars        (VOID);
GLOBAL VOID  i_Beep            (VOID);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ       Prototypen der internen Funktionen des Dialog-Modules            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL VOID  i_DlgInit         (WORD, WORD, WORD, WORD,
                                     PSTR, PWKB, WORD, WORD);
GLOBAL VOID  i_DlgScroll       (WORD, WORD, WORD, WORD, BYTE);
GLOBAL VOID  i_DlgHilfeSchreibeText (PPSTR);
GLOBAL VOID  i_DlgHilfeFuerHilfe    (VOID);
GLOBAL VOID  i_DlgLiesZK(PTEXTBOX, PEVENT, WORD);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ       Prototypen der internen Funktionen des Men-Modules              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL VOID  i_MnuGenMenuZeile  (WORD);
GLOBAL VOID  i_MnuToBuffer      (PMKB, WORD, WORD);
GLOBAL PMKB  i_MnuFindeMkb      (PWORD, PWORD);
GLOBAL WORD  i_MnuBalken        (PMKB,  SWORD, WORD);
GLOBAL WORD  i_MnuTitel         (PMKB*, SWORD, WORD);
GLOBAL WORD  i_MnuFenster       (PMKB*, SWORD, WORD);
GLOBAL PMKB  i_MnuAufMenutitel  (PEVENT);
GLOBAL WORD  i_MnuMauswahl      (PEVENT, PMKB*);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ       Prototypen der internen Funktionen des Window-Modules            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL VOID  i_WinSaveCursor    (VOID);
GLOBAL VOID  i_WinRestoreCursor (VOID);
GLOBAL VOID  i_WinPop           (WORD);
GLOBAL VOID  i_WinPush          (WORD);
GLOBAL WORD  i_WinInit          (WORD, WORD, WORD, WORD, WORD);
GLOBAL VOID  i_WinZeigeTitel    (PWKB);

#define CT_INTERN_HEADER 1
#endif
