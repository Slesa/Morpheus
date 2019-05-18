#ifndef         _MSGWIN_

 #define        _MSGWIN_
 #include       "defs/Typedefs.h"

 /* ----------- Konstanten fuer den Darstellungsmodus --------------------- */
 #define        MSG_INFO    1
 #define        MSG_YESNO   2
 #define        MSG_YESNO2  3
 #define        MSG_DAUER   4
 #define        MSG_DAUER2  5
 #define        MSG_F1F2    6

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 INT  CDECL     WinMsg          PARAM(( WORD, WORD, CHAR*, INT ));
 INT  CDECL     WinMsgCenter    PARAM(( CHAR*, INT ));
 DECLEND

#endif

