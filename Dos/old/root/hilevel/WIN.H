/****************************************************************************/
/* WIN.H                                                                    */
/* ------------------------------------------------------------------------ */
/* Definition der Fensterstruktur und der Funktionen zum Zugriff auf diese. */
/****************************************************************************/
#ifndef         _WIN_

 #define        _WIN_
 #include       "defs/Typedefs.h"                /* Grundlegende Datentypen */

 /* ----------- Typdefinition: ein Fenster -------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct                           /* Struktur eines Fensters */
 {
  WORD          wPosX;                           /* X-Position des Fensters (Links) */
  WORD          wPosY;                           /* Y-Position des Fenster (Oben) */
  WORD          wWidth;                          /* Breite des Fensters     */
  WORD          wHeight;                         /* Hoehe des Fensters      */
  WORD          wCurX;                           /* X-Position des Cursors  */
  WORD          wCurY;                           /* Y-Position des Cursors  */
  WORD*         pwBuffer;                        /* Puffer fuer den Hintergrund */
  CHAR*         pcTitle;                         /* Titel des Fensters      */
  INT           iTitlePos;                       /* Position des Titels     */
  INT           iFrame;                          /* Art des Rahmens         */
  WORD          wFlags;                          /* Die Fenster-Flags       */
  WORD          wAttrText;                       /* Attribut von normalem Text */
  WORD          wAttrFrame;                      /* Attribut des Fensterrahmens */
  WORD          wAttrTitle;                      /* Attribut des Fenstertitels */
  WORD          wAttrShadow;                     /* Attribut des Fensterschattens */
 } SWin;

 /* ----------- Konstanten fuer die Titelposition ------------------------- */
 #define        WIN_TITEL_OL   0                 /* oben, linksbuendig      */
 #define        WIN_TITEL_OZ   1                 /* oben, zentriert         */
 #define        WIN_TITEL_OR   2                 /* oben, rechtsbuendig     */
 #define        WIN_TITEL_UL   3                 /* unten, linksbuendig     */
 #define        WIN_TITEL_UZ   4                 /* unten, zentriert        */
 #define        WIN_TITEL_UR   5                 /* unten, rechtsbuendig    */

 /* ----------- Konstanten fuer die Rahmenart ----------------------------- */
 #define        WIN_FRAME_NONE   0               /* Kein Rahmen             */
 #define        WIN_FRAME_SINGLE 1               /* Einfacher Rahmen        */
 #define        WIN_FRAME_DOUBLE 2               /* Doppelter Rahmen        */
 #define        WIN_FRAME_THICK  3               /* Dicker Rahmen           */

 /* ----------- Konstanten fuer die Fensterflags -------------------------- */
 #define        WIN_FLG_SHADOW   BIT0            /* Schatten ist an         */
 #define        WIN_FLG_SAVE     BIT1            /* Hintergrund gesichert   */
 #define        WIN_FLG_CURLINE  BIT2            /* Cursor ist auf Linie    */
 #define        WIN_FLG_CURBLOCK BIT3            /* Cursor ist auf Block    */
 #define        WIN_FLG_ATTRIB   BIT4            /* User-Defined Attribute  */
 #define        WIN_FLG_1ST      BIT5            /* Fenster zum ersten Mal aktiviert */

 /* ----------- Konmstanten fuer den Fenstercursor ------------------------ */
 #define        WIN_CUR_HIDE    0                /* Cursor verstecken       */
 #define        WIN_CUR_LINE    1                /* Linien-Cursor           */
 #define        WIN_CUR_BLOCK   2                /* Block-Cursor            */

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 SWin* CDECL    WinEinrichten   PARAM(( WORD, WORD, WORD, WORD ));
 VOID  CDECL    WinEntfernen    PARAM(( SWin* ));
 VOID  CDECL    WinAktivieren   PARAM(( SWin* ));
 VOID  CDECL    WinVerstecken   PARAM(( SWin* ));
 VOID  CDECL    WinSchattenEin  PARAM(( SWin* ));
 VOID  CDECL    WinSchattenAus  PARAM(( SWin* ));
 VOID  CDECL    WinSetRahmentyp PARAM(( SWin*, INT ));
 VOID  CDECL    WinSetTitel     PARAM(( SWin*, CHAR*, INT ));
 VOID  CDECL    WinSetAttrib    PARAM(( SWin*, WORD, WORD, WORD ));

 /* ----------- Funktionen fuer aktuelles Fenster ------------------------- */
 SWin* CDECL    WinGetAktivPwkb PARAM(( void ));
 VOID  CDECL    WinCls          PARAM(( void ));
 VOID  CDECL    WinSa           PARAM(( WORD, WORD, WORD ));
 VOID  CDECL    WinSz           PARAM(( WORD, WORD, CHAR ));
 VOID  CDECL    WinSza          PARAM(( WORD, WORD, CHAR, WORD ));
 VOID  CDECL    WinSs           PARAM(( WORD, WORD, CHAR* ));
 VOID  CDECL    WinSsa          PARAM(( WORD, WORD, CHAR*, WORD ));
 VOID  CDECL    WinSwa          PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID  CDECL    WinSwz          PARAM(( WORD, WORD, WORD, WORD, CHAR ));
 VOID  CDECL    WinSwza         PARAM(( WORD, WORD, WORD, WORD, CHAR, WORD ));
 INT   CDECL    WinPrintf       PARAM(( CHAR* pcFormat, CPPARGS ));
 VOID  CDECL    WinScrollUp     PARAM(( void ));
 VOID  CDECL    WinScrollDown   PARAM(( void ));

 VOID  CDECL    WinCursor       PARAM(( INT ));
 VOID  CDECL    WinSetCursorPos PARAM(( WORD, WORD ));
 VOID  CDECL    WinGetCursorPos PARAM(( WORD*, WORD* ));
 VOID  CDECL    WinHot          PARAM(( WORD, WORD, CHAR*, WORD, WORD ));
 INT   CDECL    WinGetHotkey    PARAM(( CHAR* ));
 DECLEND

#endif
