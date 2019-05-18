#ifndef         _DLGWIN_

 #define        _DLGWIN_
 #include       <DEFS/TYPEDEFS.H>
 #include       <DEFS/BITDEFS.H>
 #include       <HILEVEL/WIN.H>
 #include       <HILEVEL/DLGSTAT.H>
 #include       <string.h>

 /* ----------- Funktionstypen -------------------------------------------- */
 typedef VOID   (CDECL *FDlgHelp  ) PARAM(( void ));
 typedef VOID   (CDECL *FDlgOnInit) PARAM(( struct SDlg* ));
 typedef VOID   (CDECL *FDlgOnExit) PARAM(( struct SDlg* ));
 typedef VOID   (CDECL *FDlgOnKey ) PARAM(( struct SDlg*, INT ));
 typedef VOID   (CDECL *FDlgDraw  ) PARAM(( struct SDlgFld* ));
 typedef VOID   (CDECL *FDlgHandle) PARAM(( INT ));

 /* ----------- Struktur eines Dialogfeldes ------------------------------- */
 typedef        struct SDlgFld
 {
  INT           iHot;                            /* Hotkey                  */
  WORD          wX;                              /* X-Position rel. zum Dialogeintrag */
  WORD          wY;                              /* Y-Position rel. zum Dialogeintrag */
  WORD          wWidth;                          /* Breite (bei Rahmen etc) */
  WORD          wHeight;                         /* Hoehe (dito)            */
  WORD          wFlag;                           /* Diverse Flags           */
  CHAR*         pcText;                          /* Eintragstext            */
  FDlgOnInit    OnInit;                          /* Init-Funktion des Eintrags */
  FDlgOnExit    OnExit;                          /* Exit-Funktion des Eintrags */
  FDlgOnKey     OnKey;                           /* Tastefunktion des Eintrags */
 } SDlgFld;

 /* ----------- Struktur eines Dialogeintrags ----------------------------- */
 typedef        struct
 {
  INT           iType;                           /* Typ des Eintrags        */
  WORD          wX;                              /* X-Position rel. zum Ausgabefenster */
  WORD          wY;                              /* Y-Position rel. zum Ausgabefenster */
  WORD          wFlag;                           /* Diverse Flags           */
  INT           iActual;                         /* Aktuelles Feld des Eintrags */
  INT           iNext;                           /* Naechstes einzufuegendes Feld */
  INT           iFields;                         /* Maximalanzahl Felder    */
  CHAR*         pcText;                          /* Text des Eintrags       */
  CHAR*         pcStatus;                        /* Statuszeile des Eintrags*/
  SDlgFld*      Field;                           /* Die einzelnen Felder    */
  FDlgHelp      Help;                            /* Hilfefunktion           */
  FDlgOnInit    OnInit;                          /* Initialisierungsfunktion*/
  FDlgOnExit    OnExit;                          /* Aufloesungsfunktion     */
  FDlgOnKey     OnKey;                           /* Tastenfunktion          */
 } SDlgEntry;

 /* ----------- Struktur eines Dialoges ----------------------------------- */
 typedef        struct SDlg
 {
  INT           iActual;                         /* Aktueller Eintrag       */
  INT           iNext;                           /* Naechster einzufuegender Eintrag */
  INT           iEntries;                        /* Maximalanzahl Eintraege */
  SDlgEntry*    Entry;                           /* Die Eintraege           */
  SWin*         win;                             /* Ausgabefenster          */
 } SDlg;

 /* ----------- Konstanten fuer die Dialogtypen --------------------------- */
 #define        DLG_STATIC      1                /* Statischer Text         */
 #define        DLG_FRAME       2                /* Statischer Rahmen       */
 #define        DLG_BITMAP      3                /* Statische Bitmap        */
 #define        DLG_PUSH        4                /* Push-Button             */
 #define        DLG_ICON        5                /* Push-Icon               */
 #define        DLG_CHECK       6                /* Check-Boxes             */
 #define        DLG_RADIO       7                /* Radio-Buttons           */
 #define        DLG_DROP        8                /* Drop-Down-List          */
 #define        DLG_LIST        9                /* Listenfenster           */
 #define        DLG_INPUT       10               /* Eingabezeile            */
 #define        DLG_EDIT        11               /* Eingabefenster          */

 /* ----------- Konstanten fuer die Eintrags/Feld-Flags ------------------- */
 #define        DLG_DISABLE     BIT0             /* Eintrag/Feld disabled   */
 #define        DLG_HIDDEN      BIT1             /* Eintrag/Feld versteckt  */
 #define        DLG_INSERT      BIT2             /* Insert aktiv            */
 #define        DLG_ACTIVE      BIT3             /* Aktiviert               */

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 SDlg*  CDECL   DlgInit         PARAM(( INT ));
 VOID   CDECL   DlgDone         PARAM(( SDlg* ));
 INT    CDECL   DlgEntInit      PARAM(( SDlg*, INT, INT, WORD, WORD, CHAR*, FDlgHelp, CHAR* ));
 VOID   CDECL   DlgEntAble      PARAM(( SDlg*, INT, INT, INT ));
 VOID   CDECL   DlgAddField     PARAM(( SDlg*, WORD, WORD, INT, WORD, WORD, CHAR* ));

 INT    CDECL   DlgHandle       PARAM(( SDlg*, WORD, WORD, WORD, WORD, CHAR* ));
 VOID   CDECL   DlgInitEntry    PARAM(( SDlg*, INT, INT, WORD, WORD, CHAR*, FDlgHelp, CHAR* ));
 VOID   CDECL   DlgDoneEntry    PARAM(( SDlg*, INT ));
 VOID   CDECL   DlgAddField     PARAM(( SDlg*, WORD, WORD, VOID* ));
 DECLEND
 #define        DlgEntEnable( dlg, iEnt )  DlgEntAble( dlg, iEnt, TRUE, -1 )
 #define        DlgEntDisable( dlg, iEnt ) DlgEntAble( dlg, iEnt, FALSE, -1 )
 #define        DlgEntHide( dlg, iEnt )    DlgEntAble( dlg, iEnt, -1, FALSE )
 #define        DlgEntShow( dlg, iEnt )    DlgEntAble( dlg, iEnt, -1, TRUE )
 #define        DlgAddStat( dlg, wX, wY, pcText )           DlgAddField( dlg, wX, wY, -1, strlen( pcText ), 1, pcText )
 #define        DlgAddFrame( dlg, wX, wY, wW, wH, pcTitle ) DlgAddField( dlg, wX, wY, -1, wW, wH, pcTitle )
 #define        DlgAddBmp( dlg, wX, wY, pcFile )            DlgAddField( dlg, wX, wY, -1, 0, 0, pcFile )
 #define        DlgAddPush( dlg, wX, wY, wW, wH, pcText )   DlgAddField( dlg, wX, wY, WinGetHot( pcText ), wW, wH, pcText )
 #define        DlgAddIcon( dlg, wX, wY, iHot, pcFile )     DlgAddField( dlg, wX, wY, iHot, 0, 0, pcFile )

#endif
