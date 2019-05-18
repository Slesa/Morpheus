 #include       "hilevel/EvSpool.h"
 #include       "hilevel/Event.h"
 #include       "hilevel/Terminal.h"
 #include       "hilevel/Printer.h"
 #include       "hilevel/PrnJob.h"
 #include       "basics/MemAlloc.h"
 #include       "basics/Disk.h"
 #include       "defs/Errordef.h"
 #include       <string.h>
 #include       <stdio.h>

 /* ----------- Interne Prototypen ---------------------------------------- */
 PRIVATE VOID CDECL     EvSplPrint      PARAM(( SJob*, SPrn* ));
 PRIVATE SPrn* CDECL    EvSplGetNext    PARAM(( void ));

 /* ----------- Interne Daten --------------------------------------------- */
 PRIVATE SEvSpl EvSpool         = { -1, NULL, 0L, -1 };

 VOID CDECL     EvSplInit    ( void )
 {
  TermInit();
  EvSplSetParam( SPOOL_PATH );
  EvSpool.iHandle = EvAddMulti( EvSplMulti, 5L );
 }

 VOID CDECL     EvSplDone    ( void )
 {
  EvDelMulti( EvSpool.iHandle );
 }

 #define        __FUNC__     ERR_SPOOL_PARAM
 VOID CDECL     EvSplSetParam( pcPath )
 CHAR*          pcPath;
 {
  if( EvSpool.pcPath!=NULL ) MemFree( EvSpool.pcPath, 0 );
  EvSpool.pcPath = strdup( pcPath );
  Assert( EvSpool.pcPath!=NULL, ERR_MEM_ALLOC );
  DskMkDir( pcPath );
 }
 #undef         __FUNC__

 VOID CDECL     EvSplMulti   ( void )
 {
  CHAR          cTemp[40];
  SFindT        find;
  SPrn*         prn;
  SJob          job;
  INT           iTerm        = TermGetNum();
  BOOL          boFertig     = FALSE;
  if( iTerm==-1 ) return;
  if( (prn = EvSplGetNext()) == NULL ) return;
  sprintf( cTemp, "%s\\*.%03hd", EvSpool.pcPath, prn->iNum );
  boFertig = DskFindFirst( cTemp, DSK_A_NORMAL, &find );
  while( !boFertig )
  {
   sprintf( cTemp, "%s\\%s", EvSpool.pcPath, find.name );
   if( JobOpen( &job, cTemp ) == ERR_NONE ) break;
   boFertig = DskFindNext( &find );
  }
  if( boFertig ) return;
  printf( "\nPrinting %s", cTemp );
  if( JobRead( &job ) == ERR_NONE )
   EvSplPrint( &job, prn );
  JobClose( &job );
  DskFileRemove( cTemp );
 }

 VOID CDECL     EvSplPrint   ( job, prn )
 SJob*          job;
 SPrn*          prn;
 {
  INT           i;
  if( prn==NULL ) return;
  if( JobHasHeader( job ) )
  {
   for( i=0; i<4; i++ )
    PrnSetHdr( prn, i, JobGetHeader( job, i ) );
  }
  if( JobHasFooter( job ) )
  {
   for( i=0; i<4; i++ )
    PrnSetFtr( prn, i, JobGetFooter( job, i ) );
  }
  PrnPrintHdr( prn );
  PrnPrintPart( prn, JobGetData( job ) );
  PrnPrintEnd( prn );
  if( JobHasHeader( job ) )
  {
   for( i=0; i<4; i++ )
    PrnSetHdr( prn, i, NULL );
  }
  if( JobHasFooter( job ) )
  {
   for( i=0; i<4; i++ )
    PrnSetFtr( prn, i, NULL );
  }
 }

 LONG CDECL     EvSplGetCnt  ( void )
 {
  LONG          lRet         = (LONG) TermGetNum() * 100000L + EvSpool.lCount++;
  if( lRet<0L ) lRet = EvSpool.lCount-1L;
  EvSpool.lCount %= 100000L;
  return( lRet );
 }

 SPrn* CDECL    EvSplGetNext ( void )
 {
  INT           i;
  SPrn*         prn          = NULL;
  INT           iTerm        = TermGetNum();
  for( i=EvSpool.iPrn+1; i!=EvSpool.iPrn; i++ )
  {
   if( i==TermGetPrnCount() ) i=0;
   prn = TermGetPrn( i );
   if( prn[i].iTerm==iTerm ) break;
  }
  return( prn );
 }

