#ifndef         _VIOBIOS_

 #define        _VIOBIOS_
 #include       "defs/Typedefs.h"
 #include       "hilevel/Vio.h"

 DECLSTART
 VOID CDECL     VioBiosInit     PARAM(( SVio*, INT ));
 WORD CDECL     VioBiosLza      PARAM(( WORD, WORD ));
 VOID CDECL     VioBiosSa       PARAM(( WORD, WORD, WORD ));
 VOID CDECL     VioBiosSz       PARAM(( WORD, WORD, CHAR ));
 VOID CDECL     VioBiosSza      PARAM(( WORD, WORD, CHAR, WORD ));
 VOID CDECL     VioBiosSs       PARAM(( WORD, WORD, CHAR* ));
 VOID CDECL     VioBiosSsa      PARAM(( WORD, WORD, CHAR*, WORD ));
 VOID CDECL     VioBiosSwa      PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID CDECL     VioBiosSwz      PARAM(( WORD, WORD, WORD, WORD, BYTE ));
 VOID CDECL     VioBiosSwza     PARAM(( WORD, WORD, WORD, WORD, BYTE, WORD ));
 VOID CDECL     VioBiosSb2w     PARAM(( WORD, WORD, WORD, WORD, WORD* ));
 VOID CDECL     VioBiosSw2b     PARAM(( WORD, WORD, WORD, WORD, WORD* ));
 VOID CDECL     VioBiosScrUp    PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID CDECL     VioBiosScrDown  PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID CDECL     VioBiosClear    PARAM(( void ));
 WORD CDECL     VioBiosLa       PARAM(( WORD, WORD ));
 CHAR CDECL     VioBiosLz       PARAM(( WORD, WORD ));
 DECLEND

#endif
