#ifndef         _DLGSTATIC_

 #define        _DLGSTATIC_
 #include       <DEFS/TYPEDEFS.H>

 extern struct  SDlgEntry;

 /* ----------- Struktur Statischer Text ---------------------------------- */
 typedef        struct
 {
  WORD          wX;                              /* X-Position des Textes   */
  WORD          wY;                              /* Y-Position des Textes   */
  CHAR*         pcText;                          /* Der Text                */
 } SDlgTxt;

 /* ----------- Struktur Statischer Rahmen -------------------------------- */
 typedef        struct
 {
  WORD          wX;                              /* X-Position des Rahmens  */
  WORD          wY;                              /* Y-Position des Rahmens  */
  CHAR*         pcTitle;                         /* Titel des Rahmens       */
  WORD          wWidth;                          /* Breite des Rahmens      */
  WORD          wHeight;                         /* Hoehe des Rahmens       */
 } SDlgFrm;

 /* ----------- Struktur Statische Bitmap --------------------------------- */
 typedef        struct
 {
  WORD          wX;                              /* X-Position der Bitmap   */
  WORD          wY;                              /* Y-Position der Bitmap   */
  CHAR*         pcFile;                          /* Dateinamen der Bitmap   */
  WORD          wWidth;                          /* Breite der Bitmap       */
  WORD          wHeight;                         /* Hoehe der Bitmap        */
  INT           iType;                           /* Art der Bitmap          */
 } SDlgBmp;

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 VOID* CDECL    DlgStatInit     PARAM(( WORD, WORD, CHAR* ));
 VOID  CDECL    DlgStatDone     PARAM(( struct SDlgEntry* ));
 VOID  CDECL    DlgStatDraw     PARAM(( VOID* ));
 VOID* CDECL    DlgFrmInit      PARAM(( WORD, WORD, WORD, WORD, CHAR* ));
 VOID  CDECL    DlgFrmDone      PARAM(( struct SDlgEntry* ));
 DECLEND

#endif
