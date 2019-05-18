#ifndef         _PRNJOB_

 #define        _PRNJOB_
 #include       <DEFS/TYPEDEFS.H>
 #include       <BASICS/DISK.H>

 /* ----------- Struktur des Job-Headers ---------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  INT           iTermFrom;                       /* Von welchem Terminal    */
  WORD          wFlags;                          /* Diverse Flags           */
  LONG          lSize;                           /* Groesse der Druckdaten  */
  LONG          lPos;                            /* Position der Druckdaten */
 } SJobHdr;

 /* ----------- Struktur des Jobs-Deskriptors ----------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  SJobHdr       hdr;
  SFile*        fh;
  CHAR*         pcHeader[4];
  CHAR*         pcFooter[4];
  CHAR*         pcData;
 } SJob;

 #define        JOB_HEADERS     BIT0             /* Job definiert Kopfzeilen*/
 #define        JOB_FOOTERS     BIT1             /* Job definiert Fusszeilen*/

 DECLSTART
 /* ----------- Zur aeusseren Anwendung ----------------------------------- */
 VOID CDECL     JobInit         PARAM(( SJob*, INT ));
 VOID CDECL     JobDone         PARAM(( SJob* ));
 VOID CDECL     JobPrint        PARAM(( SJob* job, CHAR* pcStr, CPPARGS ));
 VOID CDECL     JobSetHeader    PARAM(( SJob*, CHAR*[4] ));
 VOID CDECL     JobSetFooter    PARAM(( SJob*, CHAR*[4] ));
 /* ----------- Nur fuer EvSpool ------------------------------------------ */
 INT  CDECL     JobOpen         PARAM(( SJob*, CHAR* ));
 VOID CDECL     JobClose        PARAM(( SJob* ));
 INT  CDECL     JobRead         PARAM(( SJob* ));
 #define        JobGetHeader( job, i ) ( job->pcHeader[i] )
 #define        JobGetFooter( job, i ) ( job->pcFooter[i] )
 #define        JobGetPrn( job )    ( job->hdr.iPrn )
 #define        JobGetData( job )   ( job->pcData )
 #define        JobHasHeader( job ) ( job->hdr.wFlags&JOB_HEADERS )
 #define        JobHasFooter( job ) ( job->hdr.wFlags&JOB_FOOTERS )
 DECLEND

#endif
