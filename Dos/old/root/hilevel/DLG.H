/****************************************************************************/
/* DLG.C                                                                    */
/* ------------------------------------------------------------------------ */
/* Funktionen zur Verwaltung von Dialogen.                                  */
/****************************************************************************/
#ifndef         _DIALOG_

 #define        _DIALOG_
 #include       "hilevel/Win.h"
 #include       "defs/Typedefs.h"

 struct SDlg;
 typedef VOID   (CDECL *FDlgOnInit)( struct SDlg* );   /* Typ der Initfunktion bei Eintragen */
 typedef VOID   (CDECL *FDlgOnExit)( struct SDlg* );   /* Typ der Exitfunktion bei Eintraegen */
 typedef VOID   (CDECL *FDlgHelp)  ( struct SDlg* );   /* Typ der Hilfefunktion eines Dialoges */

 /* ----------- Struktur eines Eingabefeldes ------------------------------ */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  INT           iPos;                            /* Position im Eingabefeldes */
  INT           iAllowed;                        /* Erlaubte Eingaben       */
  INT           iBlkStart;                       /* Anfang der Markierung   */
  INT           iBlkStop;                        /* Ende der Markierung     */
 } SDlgInput;

 /* ----------- Struktur eines Dialogfeldes ------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct SDlgField
 {
  WORD          wX;                              /* X-Position des Feldes   */
  WORD          wY;                              /* Y-Position des Feldes   */
  CHAR*         pcText;                          /* Text des Eintrags / Puffer bei Eingabe */
  WORD          wFlags;                          /* Diverse Flags           */
  INT           iHotkey;                         /* Hotkey des Feldes       */
  INT           iLen;                            /* Laenge des Feldes       */
  FDlgOnInit    OnInit;                          /* Init-Funktion des Eintrags */
  FDlgOnExit    OnExit;                          /* Exit-Funktion des Eintrags */
  union
  {
   SDlgInput*   Input;                           /* Eingabefeld             */
   INT          iHeight;                         /* Rahmen                  */
  } t;
 } SDlgField;

 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct                           /* Struktur eines Dialogeintrags */
 {
  INT           iTyp;                            /* Art des Eintrags        */
  WORD          wX;                              /* X-Position des Eintrags */
  WORD          wY;                              /* Y-Position des Eintrags */
  CHAR*         pcText;                          /* Eintragstext            */
  CHAR*         pcStatus;                        /* Statuszeile beim selektieren */
  FDlgHelp      Help;                            /* Hilfefunktion des Eintrags */
  INT           iFldCnt;                         /* Anzahl der Felder im Dialogeintrag */
  INT           iFldAct;                         /* Naechstes einzufuegendes Feld */
  INT           iFldCur;                         /* Beim Handling aktuelles Feld  */
  SDlgField*    Field;                           /* Die einzelnen Felder dieses Eintrags */
 } SDlgEntry;

 /* ----------- Struktur des Dialog-Deskriptors --------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct SDlg
 {
  WORD          wFlags;                          /* Diverse Flags           */
  INT           iEntCnt;                         /* Anzahl der Eintraege im Dialog */
  INT           iEntAct;                         /* Naechster einzufuegender Eintrag */
  INT           iEntCur;                         /* Beim Handling aktueller Eintrag */
  SDlgEntry*    Entry;                           /* Liste der Eintraege     */
  SWin*         Win;                             /* Ausgabefenster des Dialogs */
 } SDlg;

 /* ----------- Erlaubte Feld-Typen --------------------------------------- */
 #define        DLG_STATIC   0                   /* Statischer Text         */
 #define        DLG_INPUT    1                   /* Eingabefeld             */
 #define        DLG_RADIO    2                   /* Radiobutton             */
 #define        DLG_CHECK    3                   /* Checkbox                */
 #define        DLG_PUSH     4                   /* Push-Button             */
 #define        DLG_FRAME    5

 /* ----------- Erlaubte Eingabe-Typen ------------------------------------ */
 #define        DLG_FIELD_NUM   100              /* Nummern-Eingabe         */
 #define        DLG_FIELD_HEX   101              /* Hexadezimaleingabe      */
 #define        DLG_FIELD_ALL   102              /* Alle Zeichen erlauben   */
 #define        DLG_FIELD_TIME  103              /* Zeiteingabe             */
 #define        DLG_FIELD_DATE  104              /* Datumseingabe           */
 #define        DLG_FIELD_SIGN  BIT14            /* Vorzeichen erlauben     */
 #define        DLG_FIELD_PASSW BIT15            /* Eingabe nicht anzeigen  */

 /* ----------- Flags der Eintragsfelder ---------------------------------- */
 #define        DLG_FLG_DISABLE BIT0             /* Feld nicht erreichbar   */
 #define        DLG_FLG_MARKED  BIT1             /* Feld ist markiert       */
 #define        DLG_FLG_BLOCK   BIT2             /* Block-Cursor            */
 #define        DLG_FLG_SHIFT   BIT3

 DECLSTART
 SDlg* CDECL    DlgInit         PARAM(( INT ));
 VOID  CDECL    DlgDone         PARAM(( SDlg* ));
 VOID  CDECL    DlgInitEntry    PARAM(( SDlg*, INT, INT, WORD, WORD, CHAR*, FDlgHelp, CHAR* ));
 VOID  CDECL    DlgDoneEntry    PARAM(( SDlgEntry* ));
 VOID  CDECL    DlgEnable       PARAM(( SDlg*, INT, INT ));
 VOID  CDECL    DlgDisable      PARAM(( SDlg*, INT, INT ));
 VOID  CDECL    DlgOnInit       PARAM(( SDlg*, INT, INT, FDlgOnInit ));
 VOID  CDECL    DlgOnExit       PARAM(( SDlg*, INT, INT, FDlgOnExit ));
 BOOL  CDECL    DlgIsMarked     PARAM(( SDlg*, INT, INT ));
 VOID  CDECL    DlgSetMarked    PARAM(( SDlg*, INT, INT, BOOL ));
 LONG  CDECL    DlgGetMarked    PARAM(( SDlg*, INT ));
 VOID  CDECL    DlgSetSelect    PARAM(( SDlg*, INT, INT ));
 INT   CDECL    DlgGetSelect    PARAM(( SDlg*, INT ));
 CHAR* CDECL    DlgGetText      PARAM(( SDlg*, INT, INT ));
 VOID  CDECL    DlgSetText      PARAM(( SDlg*, INT, INT, CHAR* ));
 VOID  CDECL    DlgAddField     PARAM(( SDlg*, WORD, WORD, CHAR*, INT, INT ));
 INT   CDECL    DlgHandle       PARAM(( SDlg*, WORD, WORD, WORD, WORD, CHAR*, INT* ));
 DECLEND

#endif

