#ifndef         _VIOUNIX_

 #define        _VIOUNIX_
 #include       "defs/Typedefs.h"
 #include       "hilevel/Vio.h"

 DECLSTART
 VOID CDECL     VioUnixInit     PARAM(( SVio*, INT ));
 VOID CDECL     VioUnixDone     PARAM(( void ));
 VOID  CDECL    VioUnixBackgr   PARAM(( void ));
 WORD CDECL     VioUnixLza      PARAM(( WORD, WORD ));
 VOID CDECL     VioUnixSa       PARAM(( WORD, WORD, WORD ));
 VOID CDECL     VioUnixSz       PARAM(( WORD, WORD, CHAR ));
 VOID CDECL     VioUnixSza      PARAM(( WORD, WORD, CHAR, WORD ));
 VOID CDECL     VioUnixSs       PARAM(( WORD, WORD, CHAR* ));
 VOID CDECL     VioUnixSsa      PARAM(( WORD, WORD, CHAR*, WORD ));
 VOID CDECL     VioUnixSwa      PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID CDECL     VioUnixSwz      PARAM(( WORD, WORD, WORD, WORD, BYTE ));
 VOID CDECL     VioUnixSwza     PARAM(( WORD, WORD, WORD, WORD, BYTE, WORD ));
 VOID CDECL     VioUnixSb2w     PARAM(( WORD, WORD, WORD, WORD, WORD* ));
 VOID CDECL     VioUnixSw2b     PARAM(( WORD, WORD, WORD, WORD, WORD* ));
 VOID CDECL     VioUnixScrUp    PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID CDECL     VioUnixScrDown  PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID CDECL     VioUnixClear    PARAM(( void ));
 WORD CDECL     VioUnixLa       PARAM(( WORD, WORD ));
 CHAR CDECL     VioUnixLz       PARAM(( WORD, WORD ));
 DECLEND

#endif
