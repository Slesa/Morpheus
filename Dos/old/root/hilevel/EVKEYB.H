#ifndef         _EVKEYB_

 #define        _EVKEYB_
 #include       "defs/Typedefs.h"

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 VOID CDECL     EvKeybInit      PARAM(( void ));
 VOID CDECL     EvKeybDone      PARAM(( void ));
 BOOL CDECL     EvKeybGetch     PARAM(( INT* ));
 WORD CDECL     EvKeybGetst     PARAM(( void ));
 DECLEND

 #define        EV_KEYB_QUEUESIZE      16

 #define        FILE_MAKRO             "TASTATUR.TST"

#endif
