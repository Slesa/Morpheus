 #include       "hilevel/EvSchon.h"
 #include       "hilevel/Event.h"
 #include       "hilevel/Vio.h"
 #include       "lolevel/PcTimer.h"
 #include       "lolevel/PcSys.h"
 #include       "basics/MemAlloc.h"
 #include       "basics/Disk.h"
 #include       "basics/Inifile.h"
 #include       "defs/Intrdef.h"
 #include       "defs/Errordef.h"
 #include       "defs/Colordef.h"
 #include       "defs/Intrdef.h"
 #include       "defs/Ptrdefs.h"
 #include       "defs/Bitdefs.h"
 #include       <stdlib.h>
 #include       <time.h>
 #include       <string.h>
 #include       <stdio.h>

 /* ----------- Interne Typen --------------------------------------------- */
 typedef BOOL   (CDECL FSchon) ( void );
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  INT           iVersion;
  INT           iType;
  ULONG         ulCount;
  BYTE          bXor;
  INT           iXres;
  INT           iYres;
  INT           iStart;
  CHAR          cText[80];
  CHAR          cDummy[20];
  ULONG         ulIntern;
 } SEvImg;

 #define        EV_SCHON_ON     BIT0
 #define        EV_SCHON_GR     BIT1
 #define        EV_SCHON_CYCLE  BIT2
 #define        EV_SCHON_BACK   BIT3

 #define        EV_SCHONTEXT    BIT0

 /* ----------- Interne Daten --------------------------------------------- */
 PRIVATE WORD   wEvSchonFlags   = 0;
 PRIVATE INT    iSchonHandle;                    /* Handle fuer Event-Manager */
 PRIVATE LONG   lSchonDelay     = 500L;           /* Delay bis zum Start     */
 PRIVATE LONG   lSchonVerz      = 20L;
 PRIVATE INT    iSchonType      = TIMER_TICKS;
 PRIVATE STimer SchonTimer;                      /* Timer fuer den Schoner  */
 PRIVATE FSchon *Schoner        = NULL;          /* Schoner-Funktion        */
 PRIVATE WORD   wSchonFlg       = 0;             /* Flag, ob aktiv          */
 PRIVATE CHAR*  pcSchonText;                     /* Darzustellender Text  */
 PRIVATE BYTE   bRgbValue[16][3];

 /* ----------- Interne Prototypen ---------------------------------------- */
 PRIVATE BOOL CDECL SchonText       PARAM(( void ));
 #if( !defined UNIX )
 PRIVATE BOOL CDECL SchonOld        PARAM(( void ));
 PRIVATE BOOL CDECL SchonOldLoad    PARAM(( CHAR* ));
 PRIVATE BOOL CDECL SchonGraph      PARAM(( void ));
 PRIVATE BOOL CDECL SchonGraphLoad  PARAM(( CHAR* ));
 PRIVATE VOID CDECL SchonGraphCycle PARAM(( void ));
 #endif
 PRIVATE VOID CDECL EvSchonMulti    PARAM(( void ));

 VOID CDECL     EvSchonInit  ( void )
 {
  extern char** _argv;
  CHAR          cTemp[20];
  CHAR          cBuff[100];
  CHAR*         cp;
  SIniDescr     ini;
  pcSchonText = NULL;
  wEvSchonFlags = 0;
 #if( !defined UNIX )
  cp = strrchr( _argv[0], '\\' );
  if( cp )
    sprintf( cTemp, "DATA\\%s", cp+1);
  else
    sprintf( cTemp, "DATA\\%s", _argv[0] );
  cp = strrchr( cTemp, '.' );
  if( cp!=NULL )
   strcpy( cp, ".INI" );
  else
   strcat( cTemp, ".INI" );
  if( IniGetSect( &ini, cTemp, "[Saver]" ) == ERR_NONE )
  {
   if( IniGetEntry( &ini, cTemp, "Delay", cBuff ) == ERR_NONE )
   {
    cp = IniString( cBuff );
    if( cp ) sscanf( cp, "%ld", &lSchonDelay );
   }
   if( IniGetEntry( &ini, cTemp, "Text", cBuff ) == ERR_NONE )
   {
    cp = IniString( cBuff );
    if( cp ) pcSchonText = strdup( cp );
   }
   if( IniGetEntry( &ini, cTemp, "Small", cBuff ) == ERR_NONE )
   {
    if( IniYesNo( cBuff ) ) wEvSchonFlags |= EV_SCHONTEXT;
   }
  }
  #endif
#ifdef         __BORLANDC__
  randomize();
#endif
  if( pcSchonText==NULL ) pcSchonText = strdup( "* GastroFix *" );
  TimerInit();
  Schoner = SchonText;
  EvSchonReset();
#if( !defined UNIX )
  if( !wEvSchonFlags&EV_SCHONTEXT )
  {
   if( DskFileExist( "PICTURE\\CYCLE.DAT" ) || DskFileExist( "PICTURE\\MAIN.PIC" ) )
   {
    Schoner     = SchonGraph;
    iSchonType  = TIMER_SECS;
    lSchonVerz  = 1L*60L;
    if( !DskFileExist( "PICTURE\\CYCLE.DAT" ) ) wSchonFlg |= EV_SCHON_CYCLE;
   }
   else
   {
    if( DskFileExist( "PICTURE\\1.PIC" )  && DskFileExist( "PICTURE\\BASE.PIC" ) )
    {
     Schoner    = SchonOld;
     iSchonType = TIMER_SECS;
     lSchonVerz = 1L*60L;
    }
   }
  }
#endif
  iSchonHandle = EvAddMulti( EvSchonMulti, 0L );
 }

 VOID CDECL     EvSchonDone  ( void )
 {
  MemFree( pcSchonText, 0L );
  EvDelMulti( iSchonHandle );
  TimerDone();
 }

 VOID CDECL     EvSchonReset ( void )
 {
  TimerStart( TIMER_SECS, lSchonDelay, &SchonTimer );
 }

 VOID CDECL     EvSchonSetText( pcText )
 CHAR*          pcText;
 {
  MemFree( pcSchonText, 0L );
  if( pcText==NULL ) return;
  pcSchonText = strdup( pcText );
 }

 BOOL CDECL     EvSchoner    ( void )
 {
  return( wSchonFlg&EV_SCHON_ON );
 }

 #define        __FUNC__     ERR_SCHON_MULTI
 PRIVATE VOID CDECL     EvSchonMulti ( void )
 {
  WORD          wLength;
  BYTE          bPages;
  INT           iMode;
  INT           iAmod;
  WORD          wX, wY;
  BYTE          b1, b2;
  BYTE*         pbBuff;
#ifdef          _TEST_SCHON_
  CHAR          cTemp[20];
  sprintf( cTemp, "%ld", SchonTimer.lStop );
  VioSs( 70, 0, cTemp );
#endif
  if( (Schoner==NULL) || (lSchonDelay==0L) || !(TimerStop(&SchonTimer)) ) return;
  EvDelMulti( iSchonHandle );
#if( !defined UNIX )
  ScrGetInfo( &bPages, &wLength );
  Assert( (pbBuff = MemAlloc( wLength ))!=NULL, ERR_MEM_ALLOC );
  VioSw2b( 0, 0, VioGetMaxCol(), VioGetMaxRow(), (WORD*)pbBuff );
  iAmod = ScrGetMode();
  iMode = VioGetMode();
  ScrGetCurTyp( &b1, &b2 );
  ScrGetCurPos( &wX, &wY );
  ScrSetCurTyp( 1, 0 );
#endif
  VioClear();
  wSchonFlg |= EV_SCHON_ON;
  if( Schoner() )
  {
   TimerStart( iSchonType, lSchonVerz, &SchonTimer );
   while( EvGetKey()==0 )
   {
    if( TimerStop( &SchonTimer ) )
    {
     if( !Schoner() ) break;
     TimerStart( iSchonType, lSchonVerz, &SchonTimer );
    }
   }
  }
  wSchonFlg &= ~EV_SCHON_ON;
#if( !defined UNIX )
  ScrSetMode( iAmod );
#endif
  VioSetMode( iMode );
#if( !defined UNIX )
  ScrSetCurTyp( b1, b2 );
  ScrSetCurPos( wX, wY );
  VioSb2w( 0, 0, VioGetMaxCol(), VioGetMaxRow(), (WORD*)pbBuff );
  MemFree( pbBuff, wLength );
#endif
  iSchonHandle = EvAddMulti( EvSchonMulti, 0L );
  EvSchonReset();
 }
 #undef         __FUNC__

 VOID CDECL     EvSchonDelay ( lDelay )
 LONG           lDelay;
 {
  lSchonDelay = lDelay;
 }

 PRIVATE BOOL CDECL     SchonText    ( void )
 {
  STATIC INT    xp[4]   = { -1,-1,-1,-1 };
  STATIC INT    yp[4]   = { -1,-1,-1,-1 };
  INT           i,n;
  for( i=0; i<4; i++ )
  {
   if( xp[i]!=-1 )
    for( n=0; n<strlen(pcSchonText); n++ )
     VioSza( xp[i]+n, yp[i], ' ', NORMAL );
   xp[i] = rand() % (VioGetMaxCol()-strlen(pcSchonText));
   yp[i] = 4 + (rand() % 4) * (VioGetMaxRow()/4) - i;   /* Modulo 4, so daá nie 2 in selber Zeile */
   VioSsa(xp[i],yp[i],pcSchonText, NORMAL);
  }
  return( TRUE );
 }

#if( !defined UNIX )
 PRIVATE BOOL CDECL SchonOld ( void )
 {
  BYTE*         pbVideo      = (BYTE*) MK_PTR( 0xA000, 0x0000 );
  if( !(wSchonFlg&EV_SCHON_GR) )
  {
   ScrSetMode( 0x12 );
   if( (!SchonOldLoad( "PICTURE\\1.PIC" ))
    || (!SchonOldLoad( "PICTURE\\BASE.PIC" ))
     )
   {
    Schoner = SchonText;
    iSchonType = TIMER_TICKS;
    lSchonVerz = 10L;
    return( FALSE );
   }
   wSchonFlg |= EV_SCHON_GR;
  }
  else
  {
   LONG         l;
   LONG*        lp           = (LONG*) pbVideo;
   for( l=0L; l<38400L/4L; l++ ) *(lp++) = ~(*lp);
  }
  return( TRUE );
 }
#endif

#if( !defined UNIX )
 PRIVATE BOOL CDECL SchonOldLoad( pcFile )
 CHAR*          pcFile;
 {
  #define       RetErr()     { DskFileClose( fh ); return( FALSE ); }
  SFile*        fh;
  SEvImg        hdr;
  BYTE*         pbVideo      = (BYTE*) MK_PTR( 0xA000, 0x0000 );
  fh = DskFileOpen( pcFile, "rb" );
  if( fh==NULL ) return( FALSE );
  if( !DskFileRead( &hdr, sizeof( SEvImg ), 1, fh ) ) RetErr();
  if( (hdr.ulIntern!=hdr.iVersion+hdr.iType+hdr.ulCount+hdr.bXor+hdr.iXres+hdr.iYres+hdr.iStart ) )
   RetErr();
 #ifndef __WATCOMC__
  (LONG) pbVideo += (LONG)hdr.iStart*(LONG)(hdr.iXres/8);
 #else
  pbVideo += (LONG)hdr.iStart*(LONG)(hdr.iXres/8);
 #endif
  DskFileRead( pbVideo, hdr.iXres/8, hdr.iYres, fh );
  DskFileClose( fh );
  return( TRUE );
  #undef        RetErr
 }
#endif

#if( !defined UNIX )
 PRIVATE BOOL CDECL SchonGraph( void )
 {
  SFile*        fh;
  CHAR          cFile[68];
  CHAR          cTemp[25];
  STATIC LONG   lPos         = 0L;
  if( wSchonFlg&EV_SCHON_CYCLE )
  {
   if( !(wSchonFlg&EV_SCHON_GR) )
   {
    ScrSetMode( 0x12 );
    sprintf( cFile, "PICTURE\\MAIN.PIC" );
    wSchonFlg |= EV_SCHON_GR;
   }
   else
   {
    SchonGraphCycle();
    return( TRUE );
   }
  }
  else
  {
   fh = DskFileOpen( "PICTURE\\CYCLE.DAT", "rt" );
   if( fh==NULL )
   {
    Schoner=SchonText;
    iSchonType = TIMER_TICKS;
    lSchonVerz = 10L;
    return( FALSE );
   }
   DskFileSeek( fh, lPos, DSK_SEEK_SET );
   if( !fgets( cTemp, 20, fh ) )
   {
    DskFileSeek( fh, lPos=0L, DSK_SEEK_SET );
    fgets( cTemp, 20, fh );
   }
   lPos = DskFileTell( fh );
   DskFileClose( fh );
   cTemp[strlen(cTemp)-1] = 0;
   sprintf( cFile, "PICTURE\\%s", cTemp );
   if( strchr( cFile, '.' ) == NULL ) strcat( cFile, ".PIC" );
   ScrSetMode( 0x12 );
  }
  if( !SchonGraphLoad( cFile ) )
  {
   Schoner = SchonText;
   iSchonType = TIMER_TICKS;
   lSchonVerz = 10L;
   return( FALSE );
  }
  return( TRUE );
 }
#endif

#if( !defined UNIX )
 PRIVATE BOOL CDECL SchonGraphLoad( cFile )
 CHAR*          cFile;
 {
  #define       RetErr()     { DskFileClose( fh ); return( FALSE ); }
  BYTE          bRgb[3];
  SFile*        fh;
  BYTE          bCheck;
  INT           i,n;
  BYTE*         pbVideo;
  SRegs         regs;
  fh = DskFileOpen( cFile, "rb" );
  if( fh==NULL ) return( FALSE );
  if( DskFileSize( fh ) != 153668L ) RetErr();
  if( !DskFileRead( &bCheck, sizeof( BYTE ), 1, fh ) ) RetErr();
  if( bCheck!=42 ) RetErr();
  DskFileSeek( fh, 20L, DSK_SEEK_SET );  // Skip haeder
  VgaSetTurning( VGA_TURN_MONITOR, TRUE );
  for( i=0; i<16; i++ )
  {
   if( !DskFileRead( bRgb, sizeof( BYTE ), 3, fh ) ) RetErr();
   VgaSetPal( i, bRgb[0], bRgb[1], bRgb[2] );
   bRgbValue[i][0] = bRgb[0];
   bRgbValue[i][1] = bRgb[1];
   bRgbValue[i][2] = bRgb[2];
  }
  for( i=0; i<16; i++ )
  {
   IntSetAX( regs, 0x1000 );
   IntSetBH( regs, (BYTE)i );
   IntSetBL( regs, (BYTE)i );
   Interrupt( 0x10, &regs );
  }
  for( i=0; i<4; i++ )
  {
   n = 1<<i;
   pbVideo = MK_PTR( 0xA000, 0x0000 );
   SysPortOut( 0x3C4, 0x02 );
   SysPortOut( 0x3C5, n );
   for( n=0; n<480; n++ )
   {
    DskFileRead( pbVideo, 80, 1, fh );
    pbVideo += 80;
   }
  }
  VgaSetTurning( VGA_TURN_MONITOR, FALSE );
  DskFileClose( fh );
  return( TRUE );
  #undef        RetErr
 }
#endif

#if( !defined UNIX )
 PRIVATE VOID CDECL SchonGraphCycle( void )
 {
  INT           i;
  if( !(wSchonFlg&EV_SCHON_BACK) )
  {
   for( i=0; i<16; i++ )
   {
    VgaSetPal( i, 255-bRgbValue[i][0], 255-bRgbValue[i][1], 255-bRgbValue[i][2] );
   }
   wSchonFlg |= EV_SCHON_BACK;
  }
  else
  {
   for( i=0; i<16; i++ )
   {
    VgaSetPal( i, bRgbValue[i][0], bRgbValue[i][1], bRgbValue[i][2] );
   }
   wSchonFlg ^= EV_SCHON_BACK;
  }
 }
#endif

#ifdef          _TEST_EVSCHON_

 #include       <DEFS/KEYDEFS.H>
 #include       <stdio.h>

 VOID CDECL     Test         ( void );

 VOID CDECL     Test         ( void )
 {
  static INT    iPosX        = 0;
  static INT    iPosY        = 0;
  static WORD   wSave        = 0xFFFF;
  if( wSave!=0xFFFF ) VioSza( iPosX, iPosY, wSave&0xFF, wSave>>8 );
  if( EvSchoner() ) return;
  iPosX = rand() % VioGetMaxCol();
  iPosY = rand() % VioGetMaxRow();
  wSave = VioLza( iPosX, iPosY );
  VioSza( iPosX, iPosY, 1, NORMAL );
 }

 VOID           main         ( void )
 {
  INT           iHandle;
  VioInit( VIO_NONE );
  VioBackground();
  EvInit();
  EvSchonDelay( 5 );
  EvSchonSetText( "* GastroFix V7.00 *" );
  iHandle = EvAddMulti( Test, 180L );
  while( EvGetKey()!= T_ESC );
  EvDelMulti( iHandle );
  EvDone();
  VioDone();
 }

#endif
