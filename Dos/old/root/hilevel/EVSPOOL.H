#ifndef         _EVSPOOL_

 #define        _EVSPOOL_
 #include       "defs/Typedefs.h"

 /* ----------- Struktur eines Spoolers ----------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  INT           iHandle;                         /* Multi-Handle            */
  CHAR*         pcPath;                          /* Spool-Pfad              */
  LONG          lCount;                          /* Spool-Zaehler           */
  INT           iPrn;                            /* Aktueller Drucker       */
 } SEvSpl;

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 VOID CDECL     EvSplInit       PARAM(( void ));
 VOID CDECL     EvSplDone       PARAM(( void ));
 VOID CDECL     EvSplMulti      PARAM(( void ));
 VOID CDECL     EvSplSetParam   PARAM(( CHAR* ));
 LONG CDECL     EvSplGetCnt     PARAM(( void ));
 DECLEND

 #define        SPOOL_PATH      "JOBS"
 #define        SPOOL_INJOB     1
 #define        SPOOL_DELJOB    2

#endif

