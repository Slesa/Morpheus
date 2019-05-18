#ifndef         _LSTWIN_

 #define        _LSTWIN_
 #include       "defs/Typedefs.h"                /* Grundlegende Datentypen */
 #include       "basics/DList.h"                 /* Doppelt Verkettete Liste*/
 #include       "hilevel/Win.h"                  /* Fensterdefinitionen     */

 /* ----------- Struktur eines Listeneintrags ----------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct SLstEntry
 {
  LONG          lNum;                            /* Nummer des Eintrags     */
  CHAR*         pcStr;                           /* Der Eintrags-Text       */
 } SLstEntry;

 /* ----------- Funktionestypen ------------------------------------------- */
 struct SLst;
 typedef BOOL   (CDECL *FLstLess)  PARAM(( SLstEntry*, SLstEntry* ));
 typedef VOID   (CDECL *FLstHelp)  PARAM(( void ));
 typedef VOID   (CDECL *FLstOnKeyReleased) PARAM(( INT, struct SLst* ));

 /* ----------- Struktur einer Liste -------------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct SLst
 {
  CHAR          pcSearch[21];                    /* Such-String der Liste   */
  INT           iCount;
  FLstLess      Less;                            /* Sortier-Funktion der Liste */
  FLstOnKeyReleased OnKeyReleased;                       /* Funktion bei Taste losgelassen */
  SDLst*        List;                            /* Liste der Eintraege     */
  SWin*         Win;                             /* Ausgabefenster          */
  WORD          wStrLen;                         /* Maximal-Laenge eines Strings */
  INT           iWinPos;                         /* Position des Scrollbalkens */
  INT           iStrPos;                         /* Position vertikal */
  BOOL          boNoShadow;
  SDLstEntry*   Start;                           /* Erster Listeneintrag im Fenster */
  SDLstEntry*   End;                             /* Letzter Listeineintrag im Fenster */
 } SLst;

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 SLst*  CDECL   LstInit         PARAM(( WORD ));
 VOID   CDECL   LstDone         PARAM(( SLst* ));
 VOID   CDECL   LstSetSort      PARAM(( SLst*, FLstLess ));
 VOID   CDECL   LstSetOnKeyReleased PARAM(( SLst*, FLstOnKeyReleased ));
 ULONG  CDECL   LstGetCount     PARAM(( SLst* ));
 LONG   CDECL   LstGetNum       PARAM(( SLst* ));
 CHAR*  CDECL   LstGetStr       PARAM(( SLst*, LONG ));
 VOID   CDECL   LstGoto         PARAM(( SLst*, LONG ));
 VOID   CDECL   LstInsert       PARAM(( SLst*, LONG, CHAR*, CPPARGS ));
 VOID   CDECL   LstChange       PARAM(( SLst*, LONG, LONG, CHAR*, CPPARGS ));
 VOID   CDECL   LstDelete       PARAM(( SLst*, LONG ));
 VOID   CDECL   LstDraw         PARAM(( SLst*, INT, WORD, WORD, WORD, WORD, CHAR*, CHAR* ));
 INT    CDECL   LstShow         PARAM(( SLst*, INT, WORD, WORD, WORD, WORD, CHAR*, CHAR*, INT*, FLstHelp ));
 LONG   CDECL   LstFirst        PARAM(( SLst* ));
 LONG   CDECL   LstNext         PARAM(( SLst* ));
 VOID   CDECL   LstShadow       PARAM(( SLst*, BOOL ));
 DECLEND

 #define        LST_INFO        0
 #define        LST_LIST        1

#endif
