#ifndef         _VIOGRAPH_

 #define        _VIOGRAPH_
 #include       "defs/Typedefs.h"
 #include       "hilevel/Vio.h"

 DECLSTART
 BOOL CDECL     VioGraphInit    PARAM(( SVio*, INT ));
 VOID CDECL     VioGrDone       PARAM(( void ));
 VOID CDECL     VioGrSa         PARAM(( WORD, WORD, WORD ));
 VOID CDECL     VioGrSz         PARAM(( WORD, WORD, CHAR ));
 VOID CDECL     VioGrSza        PARAM(( WORD, WORD, CHAR, WORD ));
 VOID CDECL     VioGrSs         PARAM(( WORD, WORD, CHAR* ));
 VOID CDECL     VioGrSsa        PARAM(( WORD, WORD, CHAR*, WORD ));
 VOID CDECL     VioGrSwz        PARAM(( WORD, WORD, WORD, WORD, BYTE ));
 VOID CDECL     VioGrSwa        PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID CDECL     VioGrSwza       PARAM(( WORD, WORD, WORD, WORD, BYTE, WORD ));
 DECLEND

#endif
