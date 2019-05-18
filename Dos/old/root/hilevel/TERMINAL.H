#ifndef         _TERMINAL_

 #define        _TERMINAL_
 #include       "defs/Typedefs.h"
#ifdef NEVER
 #include       "hilevel/Printer.h"
 #include       "hilevel/Devices.h"
 /* ----------- Terminal-Beschreibung ------------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  INT           iKellner;                        /* Eingestellter Kellner   */
  INT           iPrnCount;                       /* Anzahl der Drucker      */
  SPrn*         Prn;                             /* Die installierten Drucker */
  INT           iDevCount;                       /* Anzahl der Schnittstellen */
  SDev*         Dev;                             /* Die installierten Schnittstelen */
 } STerm;
#endif
 DECLSTART
 INT   CDECL    TermGetNum      PARAM(( void ));
 VOID  CDECL    TermInit        PARAM(( void ));
 VOID  CDECL    TermDone        PARAM(( void ));
// INT   CDECL    TermGetPrnCount PARAM(( void ));
// SPrn* CDECL    TermGetPrn      PARAM(( INT ));
// INT   CDECL    TermGetDevCount PARAM(( void ));
// SDev* CDECL    TermGetDev      PARAM(( INT ));
 DECLEND

 #define        PATH_TERMDATA   "DATA"

#endif
