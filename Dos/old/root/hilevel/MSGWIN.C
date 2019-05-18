/****************************************************************************/
/* WINMSG.C                                                                 */
/* ------------------------------------------------------------------------ */
/* Implementierung eines Fensters, das Informationen bis zu einer Ende-Be-  */
/* dingung darstellt.                                                       */
/****************************************************************************/
 #include       "hilevel/MsgWin.h"               /* Eigene Headerdatei      */
 #include       "hilevel/Win.h"                  /* Fensterroutinen         */
 #include       "hilevel/Vio.h"                  /* Vio-Funktionen          */
 #include       "hilevel/Event.h"                /* Tastaturroutinen        */
 #include       "hilevel/Palette.h"
 #include       "defs/Colordef.h"                /* Farbdefinitionen        */
 #include       "defs/Keydefs.h"                 /* Tastendefinitionen      */
 #include       <stdlib.h>                       /* NULL-Definition         */

 /* ------------ Interne Daten -------------------------------------------- */
 SWin*          MsgWin       = NULL;             /* Informationsfenster     */
 SWin*          MsgSave      = NULL;             /* Urspr. aktuelles Fenster*/

 /***************************************************************************/
 /* WinMsg                                                                  */
 /* ----------------------------------------------------------------------- */
 /* Stellt die uebergebenen Informationen in einem Fenster dar und wartet   */
 /* auf die Abbruchbedingung.                                               */
 /***************************************************************************/
 INT CDECL      WinMsg       ( wX, wY, pcText, iMode )
 WORD           wX;
 WORD           wY;
 CHAR*          pcText;
 INT            iMode;
 {
  INT           iMaxlen      = 0;
  INT           iZeilenzahl  = 1;
  INT           iTaste;
  INT           iLen         = 0;
  CHAR*         cp;
#ifdef IPC
  CHAR          cBuf[100];
#endif
#ifdef AUTO_TEST
  return( T_RETURN );
#endif
  /* Wenn mode=MELDUNG_DAUER2, dann einfach Fenster schlieáen und raus      */
  if( ( iMode==MSG_DAUER2 ) && ( MsgWin!=NULL ) )
  {
   WinEntfernen( MsgWin ); MsgWin = NULL;        /* Info-Fenster schliessen */
   WinAktivieren( MsgSave ); MsgSave=NULL;       /* urspr Fenster aktivieren */
   return( 0 );                                  /* und raus                */
  }
  WinCursor( FALSE );                            /* Cursor abschalten       */
  MsgSave = WinGetAktivPwkb();                   /* Aktuelles Fenster merken */
  /* Ermittle l„ngste Zeile                                                 */
  cp   = pcText;
  iLen = 0;
  while( *pcText )
  {
   iLen++;
   if( *pcText++=='\n' )
   {
    if( iLen>iMaxlen ) iMaxlen=iLen;
    iLen=0;
    iZeilenzahl++;
   }
  }
  if( iLen>iMaxlen ) iMaxlen=iLen;
/*  win = WinEinrichten( VioCenterX( iMaxlen+6 ), VioCenterY( iZeilenzahl+4 ), iMaxlen+6, iZeilenzahl+4 ); */
  MsgWin = WinEinrichten( wX, wY, iMaxlen+6, iZeilenzahl+4 );
  if( MsgWin==NULL ) return( 0 );
  WinSchattenEin( MsgWin );
  WinSetRahmentyp( MsgWin, WIN_FRAME_SINGLE );
  WinSetAttrib( MsgWin, MsgGetPal( MSG_PAL_TEXT ), MsgGetPal( MSG_PAL_FRAME ), MsgGetPal( MSG_PAL_TITLE ) );
  WinAktivieren( MsgWin );
  WinCls();
  pcText = cp;
  WinPrintf( "\n%s", pcText );
  /*
  while( *sCp )
  {
   WinPrintf( "%c", *sCp++ );
   if( *sCp=='\n' )
   {
    WinPrintf( "\n  " );
   }
  }
  */
  /* Die Modes handlen                                                      */
  switch( iMode )
  {
   case MSG_INFO:
#ifndef IPC
        WinSetTitel( MsgWin, " <Taste> ", WIN_TITEL_UR );
#else
        WinSsa( 15, iZeilenzahl, "<Taste drcken>", INVERS );
#endif
        do
        {
         iTaste=EvGetKey();
        } while( ( iTaste==0 ) || ( iTaste==MOU_MOVED ) );
        break;
   case MSG_YESNO:
   case MSG_YESNO2:
        if( iMode==MSG_YESNO )
#ifndef IPC
         WinSetTitel( MsgWin, " <Return>=JA <ESC>=NEIN ", WIN_TITEL_UR );
#else
         WinSsa( 5, iZeilenzahl, " <Return>=JA <ESC>=NEIN ", INVERS );
#endif
        while( TRUE )
        {
         iTaste=EvGetKey();
         if( ( iTaste==T_ESC ) || ( iTaste==T_RETURN ) ) break;
        }
        break;
   case MSG_F1F2:
        while( TRUE )
        {
         iTaste=EvGetKey();
         if( ( iTaste==T_F1 ) || ( iTaste==T_F2 ) ) break;
        }
        break;
   case MSG_DAUER:
        return( 0 );                             /* Ohne Fenster zu schlieáen wieder raus */
  }
  if( iMode!=MSG_DAUER )
  {
   WinEntfernen( MsgWin );
   WinAktivieren( MsgSave );
   MsgSave=NULL;
  }
  WinCursor( FALSE );
  return( iTaste );
 }

 INT CDECL      WinMsgCenter ( pcText, iMode )
 CHAR*          pcText;
 INT            iMode;
 {
  WORD          wMaxWidth    = 0;
  WORD          wWidth       = 5;
  WORD          wHeight      = 4;
  INT           i;
  for( i=0; pcText[i]!=0; i++ )
  {
   if( pcText[i]=='\n' )
   {
    if( ++wWidth>wMaxWidth ) wMaxWidth = wWidth;
    wWidth = 5;
    wHeight++;
   }
   wWidth += 1;
  }
  if( wWidth>wMaxWidth ) wMaxWidth = wWidth;
  return( WinMsg( VioCenterCol( wMaxWidth ), VioCenterRow( wHeight ), pcText, iMode ) );
 }
