 #include       "hilevel/Terminal.h"
 #include       "basics/MemAlloc.h"
 #include       "defs/Errordef.h"
 #include       <stdlib.h>
 #include       <stdio.h>

#ifdef NEVER
 PRIVATE STerm  Terminal;

 #define        TERM_PRN     1
 #define        TERM_DEV     2

 PRIVATE INT CDECL TermGetFiles PARAM(( INT, INT ));
#endif

 INT  CDECL     TermGetNum   ( void )
 {
  INT           iNum;
  CHAR*         cp           = getenv( "GFTERM" );
  if( cp==NULL ) return( -1 );
  sscanf( cp, "%hd", &iNum );
  return( iNum );
 }

#ifdef NEVER

 #define        __FUNC__     ERR_TERM_INIT
 VOID CDECL     TermInit     ( void )
 {
  CHAR          cTemp[68];
  SFindT        find;
  INT           i;
  BOOL          boFertig;
  INT           iTerm        = TermGetNum();
  MemFill( &Terminal, 0, sizeof( STerm ) );
  if( iTerm==-1 ) return;
  Terminal.iPrnCount = TermGetFiles( TERM_PRN, iTerm );
  Terminal.iDevCount = TermGetFiles( TERM_DEV, iTerm );
  if( Terminal.iPrnCount!=0 )
  {
   Terminal.Prn = MemAlloc( Terminal.iPrnCount * sizeof( SPrn ) );
   Assert( Terminal.Prn!=NULL, ERR_MEM_ALLOC );
   sprintf( cTemp, "%s\\PRINTER.*", PATH_TERMDATA );
   i = 0;
   boFertig = DskFindFirst( cTemp, DSK_A_NORMAL, &find );
   while( !boFertig )
   {
    sprintf( cTemp, "%s\\%s", PATH_TERMDATA, find.name );
    PrnLoad( &Terminal.Prn[i], cTemp );
    if( ++i==Terminal.iPrnCount ) break;
    boFertig= DskFindNext( &find );
   }
  }
  if( Terminal.iDevCount!=0 )
  {
   Terminal.Dev = MemAlloc( Terminal.iDevCount * sizeof( SDev ) );
   Assert( Terminal.Dev!=NULL, ERR_MEM_ALLOC );
   sprintf( cTemp, "%s\\TERM%04hd\\DEVICE.*", PATH_TERMDATA, iTerm );
   i = 0;
   boFertig = DskFindFirst( cTemp, DSK_A_NORMAL, &find );
   while( !boFertig )
   {
    sprintf( cTemp, "%s\\TERM%04hd\\%s", PATH_TERMDATA, iTerm, find.name );
    DevLoad( &Terminal.Dev[i], cTemp );
    DevInit( &Terminal.Dev[i] );
    if( ++i==Terminal.iDevCount ) break;
    boFertig= DskFindNext( &find );
   }
  }
  atexit( (ATEXIT_T)TermDone );
 }
 #undef         __FUNC__

 VOID CDECL     TermDone     ( void )
 {
  INT           i;
  MemFree( Terminal.Prn, Terminal.iPrnCount * sizeof( SPrn ) );
  Terminal.iPrnCount = 0;
  Terminal.Prn       = NULL;
  for( i=0; i<Terminal.iDevCount; i++ ) DevDone( &Terminal.Dev[i] );
  MemFree( Terminal.Dev, Terminal.iDevCount * sizeof( SDev ) );
  Terminal.iDevCount = 0;
  Terminal.Dev       = NULL;
 }

 INT  CDECL     TermGetPrnCount( void )
 {
  return( Terminal.iPrnCount );
 }

 SPrn* CDECL    TermGetPrn   ( iNum )
 INT            iNum;
 {
  if( (iNum<0) || (iNum>=Terminal.iPrnCount) ) return( NULL );
  return( &Terminal.Prn[iNum] );
 }

 INT  CDECL     TermGetDevCount( void )
 {
  return( Terminal.iDevCount );
 }

 PRIVATE INT CDECL TermGetFiles( iWhat, iTerm )
 INT            iWhat;
 INT            iTerm;
 {
  SFindT        find;
  BOOL          boFertig;
  CHAR          cTemp[68];
  INT           iCount       = 0;
  switch( iWhat )
  {
   case TERM_PRN: sprintf( cTemp, "%s\\PRINTER.*", PATH_TERMDATA ); break;
   case TERM_DEV: sprintf( cTemp, "%s\\TERM%04d\\DEVICE.*", PATH_TERMDATA, iTerm ); break;
  }
  boFertig = DskFindFirst( cTemp, DSK_A_NORMAL, &find );
  while( !boFertig )
  {
   iCount++;
   boFertig = DskFindNext( &find );
  }
  return( iCount );
 }

#endif

 #ifdef         _TEST_TERM_

 VOID           main         ( void )
 {
  printf( "My terminal number is %d\n", TermGetNum() );
 }
 #endif


