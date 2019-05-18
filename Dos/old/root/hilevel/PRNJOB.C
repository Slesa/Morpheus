 #include       <HILEVEL/PRNJOB.H>
 #include       <HILEVEL/TERMINAL.H>
 #include       <HILEVEL/EVSPOOL.H>
 #include       <BASICS/DISK.H>
 #include       <BASICS/MEMALLOC.H>
 #include       <DEFS/ERRORDEF.H>
 #include       <stdarg.h>
 #include       <string.h>

 #define        __FUNC__     ERR_JOB_INIT
 VOID CDECL     JobInit      ( job, iPrn )
 SJob*          job;
 INT            iPrn;
 {
  CHAR          cTemp[68];
  Assert( job!=NULL, ERR_PTR );
  MemFill( job, 0, sizeof( SJob ) );
  do
  {
   sprintf( cTemp, "JOBS\\%08ld.%03hd", EvSplGetCnt(), iPrn );
  } while( DskFileExist( cTemp ) );
  job->hdr.iTermFrom = TermGetNum();
  job->hdr.lPos      = sizeof( SJobHdr ) + 8*40;
  job->fh = DskFileOpen( cTemp, "w+b" );
  Assert( job->fh!=NULL, ERR_DISK_CREATE );
  Assert( DskFileWrite( &job->hdr, sizeof( SJobHdr ), 1, job->fh ), ERR_DISK_WRITE );
  DskFileSeek( job->fh, 40L*8L, DSK_SEEK_CUR );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_JOB_INIT
 VOID CDECL     JobDone      ( job )
 SJob*          job;
 {
  INT           i;
  Assert( job!=NULL, ERR_PTR );
  Assert( job->fh!=NULL, ERR_DISK_OPEN );
  DskFileSeek( job->fh, 0L, DSK_SEEK_SET );
  Assert( DskFileWrite( &job->hdr, sizeof( SJobHdr ), 1, job->fh ), ERR_DISK_WRITE );
  DskFileClose( job->fh );
  if( job->hdr.wFlags&JOB_HEADERS ) for( i=0; i<4; i++ ) MemFree( job->pcHeader[i], 41 );
  if( job->hdr.wFlags&JOB_FOOTERS ) for( i=0; i<4; i++ ) MemFree( job->pcFooter[i], 41 );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_JOB_PRINT
 VOID CDECL     JobPrint     ( SJob* job, CHAR* pcStr, CPPARGS )
 {
  va_list       args;
  Assert( (job!=NULL)&&(pcStr!=NULL), ERR_PTR );
  Assert( job->fh!=NULL, ERR_DISK_OPEN );
  va_start( args, pcStr );
  job->hdr.lSize += vfprintf( job->fh, pcStr, args );
  va_end( args );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_JOB_SETHDR
 VOID CDECL     JobSetHeader ( job, pcHdr )
 SJob*          job;
 CHAR*          pcHdr[4];
 {
  INT           i;
  LONG          lPos;
  Assert( job!=NULL, ERR_PTR );
  Assert( job->fh!=NULL, ERR_DISK_OPEN );
  lPos = DskFileTell( job->fh );
  DskFileSeek( job->fh, sizeof( SJobHdr ), DSK_SEEK_SET );
  for( i=0; i<4; i++ )
  {
   if( pcHdr[i] )
    Assert( DskFileWrite( pcHdr[i], 40, sizeof( CHAR ), job->fh ), ERR_DISK_WRITE );
  }
  DskFileSeek( job->fh, lPos, DSK_SEEK_SET );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_JOB_SETFTR
 VOID CDECL     JobSetFooter ( job, pcFtr )
 SJob*          job;
 CHAR*          pcFtr[4];
 {
  INT           i;
  LONG          lPos;
  Assert( job!=NULL, ERR_PTR );
  Assert( job->fh!=NULL, ERR_DISK_OPEN );
  lPos = DskFileTell( job->fh );
  DskFileSeek( job->fh, sizeof( SJobHdr )+4*40L, DSK_SEEK_SET );
  for( i=0; i<4; i++ )
  {
   if( pcFtr[i] )
    Assert( DskFileWrite( pcFtr[i], 40, sizeof( CHAR ), job->fh ), ERR_DISK_WRITE );
  }
  DskFileSeek( job->fh, lPos, DSK_SEEK_SET );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_JOB_OPEN
 INT  CDECL     JobOpen      ( job, pcFile )
 SJob*          job;
 CHAR*          pcFile;
 {
  Assert( (job!=NULL)&&(pcFile!=NULL), ERR_PTR );
  job->fh = DskFileOpen( pcFile, "rb" );
  if( job->fh==NULL ) return( ERR_DISK_OPEN );
  if( !DskFileRead( &job->hdr, sizeof( SJobHdr ), 1, job->fh ) )
  {
   DskFileClose( job->fh );
   return( ERR_DISK_READ );
  }
  return( ERR_NONE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_JOB_CLOSE
 VOID CDECL     JobClose     ( job )
 SJob*          job;
 {
  INT           i;
  Assert( job!=NULL, ERR_PTR );
  Assert( job->fh!=NULL, ERR_DISK_OPEN );
  DskFileClose( job->fh );
  if( job->hdr.wFlags&JOB_HEADERS ) for( i=0; i<4; i++ ) MemFree( job->pcHeader[i], 0L );
  if( job->hdr.wFlags&JOB_FOOTERS ) for( i=0; i<4; i++ ) MemFree( job->pcFooter[i], 0L );
  MemFree( job->pcData, (SIZE_T)job->hdr.lSize );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_JOB_READ
 INT  CDECL     JobRead      ( job )
 SJob*          job;
 {
  INT           i;
  Assert( job!=NULL, ERR_PTR );
  Assert( job->fh!=NULL, ERR_DISK_OPEN );
  if( job->hdr.lSize==0L ) return( ERR_COUNT );
  if( job->hdr.wFlags&JOB_HEADERS )
  {
   DskFileSeek( job->fh, sizeof( SJobHdr ), DSK_SEEK_SET );
   for( i=0; i<4; i++ )
   {
    job->pcHeader[i] = MemAlloc( 41 );
    Assert( job->pcHeader[i]!=NULL, ERR_MEM_ALLOC );
    Assert( DskFileRead( job->pcHeader[i], sizeof( CHAR ), 40, job->fh ), ERR_DISK_READ );
   }
  }
  if( job->hdr.wFlags&JOB_FOOTERS )
  {
   DskFileSeek( job->fh, sizeof( SJobHdr )+4*40, DSK_SEEK_SET );
   for( i=0; i<4; i++ )
   {
    job->pcFooter[i] = MemAlloc( 41 );
    Assert( job->pcFooter[i]!=NULL, ERR_MEM_ALLOC );
    Assert( DskFileRead( job->pcFooter[i], sizeof( CHAR ), 40, job->fh ), ERR_DISK_READ );
   }
  }
  job->pcData = MemAlloc( (SIZE_T)job->hdr.lSize );
  Assert( job->pcData!=NULL, ERR_MEM_ALLOC );
  DskFileSeek( job->fh, job->hdr.lPos, DSK_SEEK_SET );
  Assert( DskFileRead( job->pcData, job->hdr.lSize, 1, job->fh ), ERR_DISK_READ );
  return( ERR_NONE );
 }
 #undef         __FUNC__
