#ifndef         _EVENT_

 #define        _EVENT_
 #include       "defs/Typedefs.h"

 typedef VOID   (CDECL *FEvMulti)  PARAM(( void ));

 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef struct
 {
  FEvMulti      Multi;
  LONG          lDelay;
  LONG          lCount;
 } SEvMulti;

 DECLSTART
 VOID CDECL     EvInit          PARAM(( void ));
 VOID CDECL     EvDone          PARAM(( void ));
 VOID CDECL     EvDoMulti       PARAM(( void ));
 INT  CDECL     EvAddMulti      PARAM(( FEvMulti, LONG ));
 VOID CDECL     EvDelMulti      PARAM(( INT ));
 INT  CDECL     EvGetKey        PARAM(( void ));
 VOID CDECL     EvHideMouse     PARAM(( BOOL ));
 VOID CDECL     EvNoWait        PARAM(( BOOL ));
 DECLEND

 #define        EV_QUEUESIZE 16

#endif
