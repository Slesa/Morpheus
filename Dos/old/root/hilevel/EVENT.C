 #include       "hilevel/Event.h"
 #include       "hilevel/EvKeyb.h"
 #include       "hilevel/EvMouse.h"
// #include       "hilevel/EvSpool.h"
 #include       "hilevel/EvSchon.h"
 #include       "basics/MemAlloc.h"
 #include       <stdio.h>

 PRIVATE SEvMulti EvMulti[EV_QUEUESIZE];
 PRIVATE BOOL     boHideMouse = FALSE;
 PRIVATE BOOL     boNoWait    = FALSE;

 VOID CDECL     EvInit       ( void )
 {
  MemFill( EvMulti, 0, sizeof( EvMulti ) );
  EvKeybInit();
  EvMouInit();
  #if( !defined UNIX )
  EvSchonInit();
  #endif
//  EvSplInit();
 }

 VOID CDECL     EvDone       ( void )
 {
  EvMouDone();
  EvKeybDone();
  #if( !defined UNIX )
  EvSchonDone();
  #endif
//  EvSplDone();
 }

 VOID CDECL     EvDoMulti    ( void )
 {
   INT           i;
   for( i=0; i<EV_QUEUESIZE; i++ )
   {
    if( ( EvMulti[i].Multi ) && ( ++EvMulti[i].lCount>=EvMulti[i].lDelay ) )
    {
     EvMulti[i].Multi();
     EvMulti[i].lCount = 0L;
    }
   }
 }

 INT  CDECL     EvAddMulti   ( multi, lDelay )
 FEvMulti       multi;
 LONG           lDelay;
 {
  INT           i;
  for( i=0; i<EV_QUEUESIZE; i++ )
  {
   if( EvMulti[i].Multi==NULL )
   {
    EvMulti[i].Multi  = multi;
    EvMulti[i].lDelay = lDelay;
    EvMulti[i].lCount = 0L;
    return( i );
   }
  }
  return( -1 );
 }

 VOID CDECL     EvDelMulti   ( iWhich )
 INT            iWhich;
 {
  if( iWhich>=0 ) EvMulti[iWhich].Multi = NULL;
 }

 INT  CDECL     EvGetKey     ( void )
 {
  INT           iRet         = 0;
  BOOL          boFertig     = FALSE;
  while( !boFertig )
  {
   EvDoMulti();
   if( EvKeybGetch( &iRet ) ) { EvSchonReset(); break; }
   if( !boHideMouse )
    if( EvMouGetch( &iRet ) )  { EvSchonReset(); break; }
   if( EvSchoner() ) return( 0 );
   if( boNoWait )
    break;
  }
  return( iRet );
 }

 VOID CDECL     EvHideMouse   ( BOOL flag )
 {
  boHideMouse = flag;
 }

 VOID CDECL     EvNoWait      ( BOOL flag )
 {
  boNoWait = flag;
 }

#ifdef          _TEST_EVENT_

 #include       <conio.h>

#ifdef          __WATCOMC__
 VOID           gotoxy  ( INT, INT );
 VOID           gotoxy  ( x, y )
 INT            x;
 INT            y;
 {
  SRegs         regs;                             /* Registerzugriff        */
  IntSetAH( regs, 2 );                            /* Fkt 2: Cursorposition setzen */
  IntSetBH( regs, 0 );                            /* Auf Bildschirmseite 0  */
  IntSetDH( regs, (BYTE) y );                     /* Neue Cursorspalte      */
  IntSetDL( regs, (BYTE) x );                     /* Neue Cursorzeile       */
  Interrupt( 0x10, &regs );                       /* BIOS-Aufruf            */
 }
#endif

 CHAR           States[]     = { '\\', '³', '/', 'Ä' };

 VOID           Multi1       ( void )
 {
  static INT    i;
  gotoxy( 1, 1 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi2       ( void )
 {
  static INT    i;
  gotoxy( 80, 1 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi3       ( void )
 {
  static INT    i;
  gotoxy( 1, 3 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi4       ( void )
 {
  static INT    i;
  gotoxy( 80, 3 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi5       ( void )
 {
  static INT    i;
  gotoxy( 1, 5 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi6       ( void )
 {
  static INT    i;
  gotoxy( 80, 5 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi7       ( void )
 {
  static INT    i;
  gotoxy( 1, 7 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi8       ( void )
 {
  static INT    i;
  gotoxy( 80, 7 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi9       ( void )
 {
  static INT    i;
  gotoxy( 40, 1 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           Multi0       ( void )
 {
  static INT    i;
  gotoxy( 40, 25 ); printf( "%c", States[i++] );
  i %= 4;
 }

 VOID           main         ( void )
 {
  INT           iHandle[10];
  FEvMulti      Multi[10]    = { Multi0, Multi1, Multi2, Multi3, Multi4, Multi5, Multi6, Multi7, Multi8, Multi9 };
  INT           i;
  BOOL          boFertig     = FALSE;
  INT           iKey;
  setbuf( stdout, NULL );
  EvInit();
  for( i=0; i<10; i++ )iHandle[i] = EvAddMulti( Multi[i], 5L );
  while( !boFertig )
  {
   iKey = EvGetKey();
   if( iKey!=0 )
   {
    printf( "\n%4hX ³ %4hd ³ %c", iKey, iKey, iKey );
    if( iKey==27 ) boFertig = TRUE;
   }
//   gotoxy( 10, 10 ); printf( "Taste........: %4d", iKey );
//   switch( iKey )
//   {
/*
    case T_MOUMOVED:
         gotoxy( 10, 11 ); printf( "X......: %4d", Event.Cmd.Mou->wX );
         gotoxy( 10, 12 ); printf( "Y......: %4d", Event.Cmd.Mou->wY );
         gotoxy( 10, 13 ); printf( "State..: %4d", Event.Cmd.Mou->wState );
         break;
    default:
*/
/*
         gotoxy( 10, 11 ); printf( "Key....: %4d", iKey );
         gotoxy( 10, 12 ); printf( "State..: %4X", EvKeybGetst() );
         switch( iKey )
         {
          case 27 : boFertig = TRUE; break;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9': i = iKey - '0';
                    if( iHandle[i]!=-1 )
                    {
                     EvDelMulti( iHandle[i] );
                     iHandle[i] = -1;
                    }
                    else
                     iHandle[i] = EvAddMulti( Multi[i], 5L );
                    break;
         }
   }
*/
  }
  EvDone();
 }

#endif
