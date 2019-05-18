 #include       "hilevel/Event.h"
 #include       "hilevel/EvKeyb.h"
 #include       "hilevel/Terminal.h"
 #include       "lolevel/PcKeyb.h"
 #include       "lolevel/KbMakro.h"
 #include       "basics/MemAlloc.h"
 #include       "basics/Inifile.h"
 #include       "basics/Disk.h"
 #include       "defs/Ptrdefs.h"
 #include       "defs/Errordef.h"
 #include       "defs/Bitdefs.h"
 #include       <stdio.h>
 #include       <string.h>

 /* ----------- Interne Strukturen ---------------------------------------- */
 typedef        struct
 {
  INT           iKey;                            /* Gedrueckte Taste        */
  WORD          wState;                          /* Tastaturstatus beim druecken */
 } SEvKeyb;

 /* ----------- Interne Daten --------------------------------------------- */
 PRIVATE BYTE    bEvKeybHead;                     /* Anfang des Tasten-Puffers */
 PRIVATE BYTE    bEvKeybTail;                     /* Ende des Tasten-Puffers */
 PRIVATE SEvKeyb EvKeybQueue[EV_KEYB_QUEUESIZE];  /* Der Tastenpuffer        */
 PRIVATE INT     iEvKeybHandle;                   /* Handle der Multifunktion*/
 PRIVATE WORD    wEvKeybFlags;

 /* ----------- Interne Konstanten ---------------------------------------- */
 #define        EV_DOMAKRO      BIT0
 #define        EV_INMAKRO      BIT1

 /* ----------- Interne Prototypen ---------------------------------------- */
 PRIVATE VOID CDECL EvKeybMulti PARAM(( void ));  /* Tastatur-Multi-Schleife */

 VOID CDECL     EvKeybInit   ( void )
 {
  extern char** _argv;
  SIniDescr     cfg;
  CHAR          cTemp[101];
  CHAR          cFile[40];
  CHAR          cMakro[68];
  CHAR*         cp;
  BOOL          boLoad       = FALSE;
  bEvKeybHead   = 0;
  bEvKeybTail   = 0;
  wEvKeybFlags  = 0;
  MemFill( EvKeybQueue, 0, sizeof( EvKeybQueue ) );
  KeybInit();
  iEvKeybHandle = EvAddMulti( EvKeybMulti, 0L );
  #if( !defined UNIX )
  cp = strrchr( _argv[0], '\\' );
  if( !cp )
    sprintf( cFile, "DATA\\%s", _argv[0] );
  else
    sprintf( cFile, "DATA\\%s", cp+1 );
  cp = strrchr( cFile, '.' );
  if( cp!=NULL )
   strcpy( cp, ".INI" );
  else
   strcat( cFile, ".INI" );
  strcpy( cMakro, FILE_MAKRO );
  if( IniGetSect( &cfg, cFile, "[MAKRO]" ) == ERR_NONE )
  {
   if( IniGetEntry( &cfg, cFile, "Load=", cTemp ) == ERR_NONE )
   {
    if( IniYesNo( cTemp ) )
     boLoad = TRUE;
   }
   if( IniGetEntry( &cfg, cFile, "File=", cTemp ) == ERR_NONE )
   {
    cp = IniString( cTemp );
    if( (cp!=NULL) && DskFileExist(cp) )
    strcpy( cMakro, cp );
   }
  }
  #endif
  if( !boLoad )
   return;
  if( KbMakLoad( cMakro ) == ERR_NONE )
   wEvKeybFlags |= EV_DOMAKRO;
 }

 VOID CDECL     EvKeybDone   ( void )
 {
  EvDelMulti( iEvKeybHandle );
  KeybDone();
 }

 BOOL CDECL     EvKeybGetch  ( piKey )
 INT*           piKey;
 {
  if( (wEvKeybFlags&EV_INMAKRO) && (wEvKeybFlags&EV_DOMAKRO) )
   *piKey = KbMakNext();
  else
  {
   if( bEvKeybHead==bEvKeybTail ) return( FALSE );
   *piKey = EvKeybQueue[bEvKeybTail++].iKey;
   bEvKeybTail %= EV_KEYB_QUEUESIZE;
   if( wEvKeybFlags&EV_DOMAKRO )
   {
    *piKey = KbMakFirst(*piKey);
    if( *piKey>0 ) wEvKeybFlags |= EV_INMAKRO;
   }
  }
  if( *piKey<0 )
  {
   wEvKeybFlags &= ~EV_INMAKRO;
   *piKey = -*piKey;
  }
  return( TRUE );
 }

 WORD CDECL     EvKeybGetst  ( void )
 {
  if( bEvKeybTail==0 ) return( EvKeybQueue[EV_KEYB_QUEUESIZE-1].wState );
  return( EvKeybQueue[bEvKeybTail-1].wState );
 }

 VOID CDECL     EvKeybMulti  ( void )
 {
  if( KeybHit() )
  {
   EvKeybQueue[bEvKeybHead].iKey     = KeybGetch();
   EvKeybQueue[bEvKeybHead++].wState = KeybGetState();
   bEvKeybHead %= EV_KEYB_QUEUESIZE;
  }
 }

