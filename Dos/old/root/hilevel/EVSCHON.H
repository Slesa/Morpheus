#ifndef         _EVSCHON_

 #define        _EVSCHON_
 #include       "defs/Typedefs.h"

 DECLSTART
 VOID CDECL     EvSchonInit     PARAM(( void ));
 VOID CDECL     EvSchonDone     PARAM(( void ));
 VOID CDECL     EvSchonReset    PARAM(( void ));
 VOID CDECL     EvSchonDelay    PARAM(( LONG ));
 BOOL CDECL     EvSchoner       PARAM(( void ));
 VOID CDECL     EvSchonSetText  PARAM(( CHAR* ));
 DECLEND
 #define        EvSchonOff()    EvSchonDelay( 0L )

#endif
