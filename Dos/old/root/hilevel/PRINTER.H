#ifndef         _PRINTER_

 #define        _PRINTER_
 #include       <DEFS/TYPEDEFS.H>
 #include       <DEFS/BITDEFS.H>
 #include       <BASICS/DISK.H>

 /* ----------- Device-Flags ---------------------------------------------- */
 #define        PRN_NUL         0
 #define        PRN_SERIAL      1
 #define        PRN_PARALLEL    2
 #define        PRN_IMC         3
 #define        PRN_FILE        4

 /* ----------- Drucker-Flags --------------------------------------------- */
 #define        PRN_GUEST       BIT0             /* Einzelblatt             */
 #define        PRN_SINGLE      BIT1             /* Steuerseq. einzeln schicken */
 #define        PRN_TOFILE      BIT2             /* Umleitung in Datei      */
 #define        PRN_LOAD        BIT3             /* Seiteneinzug aktiv      */

 /* ----------- Steuersequenzen ------------------------------------------- */
 #define        PRN_SEQ_MAX     15               /* Anzahl Steuersequenzen  */
 #define        PRN_SEQ_INIT    0                /* Initialisierung         */
 #define        PRN_SEQ_DONE    1                /* Aufloesung              */
 #define        PRN_SEQ_PERF    2                /* Perforieren             */
 #define        PRN_SEQ_CUT     3                /* Cutten                  */
 #define        PRN_SEQ_LF      4                /* Linefeed                */
 #define        PRN_SEQ_PF      5                /* Pagefeed                */
 #define        PRN_SEQ_COLON   6                /* Farbe an                */
 #define        PRN_SEQ_COLOFF  7                /* Farbe aus               */
 #define        PRN_SEQ_BOLDON  8                /* Fett an                 */
 #define        PRN_SEQ_BOLDOFF 9                /* Fett aus                */
 #define        PRN_SEQ_INVON   10               /* Kursiv an               */
 #define        PRN_SEQ_INVOFF  11               /* Kursiv aus              */
 #define        PRN_SEQ_GRON    12               /* Grafik an               */
 #define        PRN_SEQ_GROFF   13               /* Grafik aus              */
 #define        PRN_SEQ_LOAD    PRN_SEQ_PERF     /* Seite einziehen         */

 /* ----------- Drucker-Kommandos ----------------------------------------- */
 #define        PRN_CMD         '!'
 #define        PRN_CMD_INIT    'A'              /* Initialisierung         */
 #define        PRN_CMD_DONE    'Z'              /* Aufloesung              */
 #define        PRN_CMD_LF      'L'              /* Linefeed                */
 #define        PRN_CMD_PF      'X'              /* Pagefeed                */
 #define        PRN_CMD_CUT     'Y'              /* Cutten                  */
 #define        PRN_CMD_PERF    'P'              /* Perforieren             */
 #define        PRN_CMD_COLON   'C'              /* Farbe an                */
 #define        PRN_CMD_COLOFF  'c'              /* Farbe aus               */
 #define        PRN_CMD_INVON   'I'              /* Kursiv an               */
 #define        PRN_CMD_INVOFF  'i'              /* Kursiv aus              */
 #define        PRN_CMD_BOLDON  'B'              /* Fett an                 */
 #define        PRN_CMD_BOLDOFF 'b'              /* Fett aus                */
 #define        PRN_CMD_GRON    'G'              /* Grafik an               */
 #define        PRN_CMD_GROFF   'g'              /* Grafik aus              */

 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  /* ---------- Namen und Dateien ----------------------------------------- */
  CHAR          cDevName[21];                    /* Name des Geraetes       */
  CHAR          cName[21];                       /* Name des Druckers       */
  CHAR          cLayout[9];                      /* Name der Layout-Datei   */
  /* ---------- Anschlusseinstellungen ------------------------------------ */
  INT           iNum;                            /* Interne Nummer          */
  INT           iTerm;                           /* An welchem Terminal     */
  INT           iDevice;                         /* Nummer des Anschlusses  */
  INT           iDelay;                          /* Druckverzoegerung       */
  WORD          wFlag;                           /* Diverse Flags           */
  /* ---------- Seiteneinstellungen --------------------------------------- */
  INT           iLine;                           /* Aktuelle Zeile          */
  INT           iPage;                           /* Aktuelle Seite          */
  INT           iPgFstHeight;                    /* Hoehe 1. Seite          */
  INT           iPgFstAbove;                     /* Oberer Rand 1. Seite    */
  INT           iPgNxtHeight;                    /* Hoehe naechste Seite    */
  INT           iPgNxtAbove;                     /* Oberer Rand naechste S. */
  INT           iPgWidth;                        /* Breite einer Seite      */
  INT           iPgLeft;                         /* Linker Rand             */
  /* ---------- Uebersetzungstabelle -------------------------------------- */
  WORD*         pwTranslate;                     /* Zeichenersetzung        */
  CHAR*         pcSeq[PRN_SEQ_MAX];              /* Die Steuersequenzen     */
  CHAR*         pcHdr[4];                        /* Die Kopfzeilen          */
  CHAR*         pcFtr[4];                        /* Die Fusszeilen          */
  SFile*        fh;
 } SPrn;

 DECLSTART
 VOID  CDECL    PrnInit         PARAM(( SPrn*, INT, INT ));
 VOID  CDECL    PrnDone         PARAM(( SPrn* ));
 VOID  CDECL    PrnLoad         PARAM(( SPrn*, CHAR* ));
 VOID  CDECL    PrnSave         PARAM(( SPrn*, CHAR* ));
 BOOL  CDECL    PrnGuest        PARAM(( SPrn* ));
 BOOL  CDECL    PrnPrintCh      PARAM(( SPrn*, CHAR ));
 BOOL  CDECL    PrnPrintBuf     PARAM(( SPrn*, INT, CHAR* ));
 BOOL  CDECL    PrnPrintInit    PARAM(( SPrn* ));
 BOOL  CDECL    PrnPrintHdr     PARAM(( SPrn* ));
 BOOL  CDECL    PrnPrintPart    PARAM(( SPrn*, CHAR* ));
 BOOL  CDECL    PrnPrintEnd     PARAM(( SPrn* ));
 CHAR* CDECL    PrnGetHdr       PARAM(( SPrn*, INT ));
 VOID  CDECL    PrnSetHdr       PARAM(( SPrn*, INT, CHAR* ));
 CHAR* CDECL    PrnGetFtr       PARAM(( SPrn*, INT ));
 VOID  CDECL    PrnSetFtr       PARAM(( SPrn*, INT, CHAR* ));
 CHAR* CDECL    PrnGetSeq       PARAM(( SPrn*, INT, INT* ));
 VOID  CDECL    PrnSetSeq       PARAM(( SPrn*, INT, INT, CHAR* ));
 INT   CDECL    PrnGetPageLen   PARAM(( SPrn* ));
 VOID  CDECL    PrnSetPageLen   PARAM(( SPrn*, INT, INT ));
 CHAR  CDECL    PrnGetTranslate PARAM(( SPrn*, CHAR ));
 VOID  CDECL    PrnSetTranslate PARAM(( SPrn*, INT, WORD* ));
 DECLEND

#endif
