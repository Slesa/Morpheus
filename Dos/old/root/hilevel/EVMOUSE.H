#ifndef         _EVMOUSE_

 #define        _EVMOUSE_
 #include       "defs/Typedefs.h"

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 VOID CDECL     EvMouInit       PARAM(( void ));
 VOID CDECL     EvMouDone       PARAM(( void ));
 BOOL CDECL     EvMouGetch      PARAM(( INT* ));
 VOID CDECL     EvMouGetVal     PARAM(( WORD*, WORD*, WORD* ));
 DECLEND

 #define        EV_MOU_QUEUESIZE       16

#endif
