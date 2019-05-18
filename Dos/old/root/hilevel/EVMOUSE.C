 #include       "hilevel/Event.h"
 #include       "hilevel/EvMouse.h"
 #include       "lolevel/PcMouse.h"
 #include       "basics/MemAlloc.h"
 #include       "defs/Keydefs.h"
 #include       <stdio.h>

 /* ----------- Interne Strukturen ---------------------------------------- */
 typedef        struct
 {
  INT           iWhat;                           /* Art des Ereignisses     */
  WORD          wX;                              /* X-Position der Maus     */
  WORD          wY;                              /* Y-Position der Maus     */
  WORD          wState;                          /* Status der Maustasten   */
 } SEvMou;

 /* ----------- Interne Daten --------------------------------------------- */
 PRIVATE BYTE   bEvMouHead;                      /* Kopf des Maus-Puffers   */
 PRIVATE BYTE   bEvMouTail;                      /* Ende des Maus-Puffers   */
 PRIVATE SEvMou EvMouQueue[EV_MOU_QUEUESIZE];    /* Der Maus-Puffer         */
 PRIVATE INT    iEvMouHandle = -1;               /* Handle der Multifunktion*/
 PRIVATE WORD   wEvMouX;                         /* Aktuelle Maus-X-Position*/
 PRIVATE WORD   wEvMouY;                         /* Aktuelle Maus-Y-Position*/
 PRIVATE WORD   wEvMouState  = 0;                /* Aktueller Status der Maustasten */

 /* ----------- Interne Prototypen ---------------------------------------- */
 PRIVATE VOID CDECL EvMouMulti PARAM(( void ));  /* Maus-Multi-Schleife     */

 VOID CDECL     EvMouInit    ( void )
 {
  bEvMouHead   = 0;
  bEvMouTail   = 0;
  MemFill( EvMouQueue, 0, sizeof( EvMouQueue ) );
  if( MouInit()==0 ) return;
  MouGetPos( &wEvMouState, &wEvMouX, &wEvMouState );
  iEvMouHandle = EvAddMulti( EvMouMulti, 2L );
 }

 VOID CDECL     EvMouDone    ( void )
 {
  if( iEvMouHandle==-1 ) return;
  EvDelMulti( iEvMouHandle );
  MouDone();
 }

 BOOL CDECL     EvMouGetch   ( piKey )
 INT*           piKey;
 {
  if( bEvMouHead==bEvMouTail ) return( FALSE );
  *piKey = EvMouQueue[bEvMouTail++].iWhat;
  bEvMouTail %= EV_MOU_QUEUESIZE;
  return( TRUE );
 }

 PRIVATE VOID CDECL EvMouMulti   ( void )
 {
  WORD          wState;
  WORD          wX;
  WORD          wY;
  MouGetPos( &wState, &wX, &wY );
  if( ( wX!=wEvMouX ) || ( wY!=wEvMouY ) )
  {
   EvMouQueue[bEvMouHead].iWhat   = MOU_MOVED;
   EvMouQueue[bEvMouHead].wState  = wEvMouState = wState;
   EvMouQueue[bEvMouHead].wX      = wEvMouX     = wX;
   EvMouQueue[bEvMouHead].wY      = wEvMouY     = wY;
   bEvMouHead = (bEvMouHead+1)%EV_MOU_QUEUESIZE;
   return;
  }
  if( wState!=wEvMouState )
  {
   switch( wState )
   {
    case 1:
         EvMouQueue[bEvMouHead].iWhat   = MOU_LEFTPRESS;
         break;
    case 2:
         EvMouQueue[bEvMouHead].iWhat   = MOU_RIGHTPRESS;
         break;
    default:
         EvMouQueue[bEvMouHead].iWhat   = wState;
   }
   EvMouQueue[bEvMouHead].wState  = wEvMouState = wState;
   EvMouQueue[bEvMouHead].wX      = wEvMouX     = wX;
   EvMouQueue[bEvMouHead].wY      = wEvMouY     = wY;
   bEvMouHead = (bEvMouHead+1)%EV_MOU_QUEUESIZE;
  }
 }

 VOID CDECL     EvMouGetVal  ( pwX, pwY, pwState )
 WORD*          pwX;
 WORD*          pwY;
 WORD*          pwState;
 {
  INT           iIdx         = (bEvMouTail==0) ? EV_MOU_QUEUESIZE-1 : bEvMouTail-1;
  *pwX     = EvMouQueue[iIdx].wX;
  *pwY     = EvMouQueue[iIdx].wY;
  *pwState = EvMouQueue[iIdx].wState;
 }
