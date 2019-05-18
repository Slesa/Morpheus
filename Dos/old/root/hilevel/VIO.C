/****************************************************************************/
/* VIO.C                                                                    */
/* ------------------------------------------------------------------------ */
/* Funktionen zum Zugriff auf den Bildschirm am PC.                         */
/****************************************************************************/
 #include       "hilevel/Vio.h"                  /* Typdefinitionen         */
#if( !defined UNIX )
 #include       "hilevel/VioBios.h"
 #include       "hilevel/VioMono.h"
 #include       "hilevel/VioVesa.h"
 #include       "hilevel/VioGraph.h"
#else
 #include       "hilevel/VioUnix.h"
#endif
 #include       "lolevel/PcMouse.h"
 #include       "lolevel/PcTimer.h"
 #include       "basics/MemAlloc.h"              /* Speicherverwaltung      */
 #include       "defs/Errordef.h"                /* Fehlerkonstanten        */
 #include       "defs/Colordef.h"
#if( !defined UNIX )
 #include       "defs/Ptrdefs.h"
#endif
 #include       "defs/Bitdefs.h"
 #include       <string.h>
 #include       <stdio.h>

 PRIVATE VOID  CDECL    VioStdBackground( void );

 /* ----------- Interne Daten --------------------------------------------- */
 SVio           VioDescriptor
                = { -1                           /* Aktueller Modus         */
                  , 80                           /* Grafik: X-Aufloesung    */
                  , 25                           /* Grafik: Y-Aufloesung    */
                  , NULL                         /* Grafik: Zeichensatz     */
                  , NULL                         /* Grafik: Zeichensatz     */
                  , 16                           /* Grafik: Zeichnehoehe    */
                  , 80                           /* Anzahl Spalten          */
                  , 25                           /* Anzahl Zeilen           */
                  , 0                            /* Flags                   */
                  , 4                            /* Anzahl Farben           */
#if( !defined UNIX )
                  , MK_PTR( 0xB800, 0x0000 )     /* Bildschirmzeiger        */
                  , VioBiosLza
                  , VioBiosSa                    /* Attribut setzen         */
                  , VioBiosSz                    /* Zeichen setzen          */
                  , VioBiosSza                   /* Attribut mit Zeichen setzen */
                  , VioBiosSs                    /* String schreiben        */
                  , VioBiosSsa                   /* String mit Attribut schreiben */
                  , VioBiosSwa                   /* Fenster mit Attribut fuellen */
                  , VioBiosSwz                   /* Fenster mit Zeichen fuellen */
                  , VioBiosSwza                  /* Fenster mit Attribut und Zeichen fuellen */
                  , VioBiosSb2w                  /* Buffer auf Schirm schreiben */
                  , VioBiosSw2b                  /* Fensterinhalt speichern */
                  , VioBiosClear                 /* Bildschirm loeschen     */
                  , NULL                         /* Aufloesungsfunktion     */
                  , VioBiosScrUp                 /* Fensterinhalt nach oben scrollen */
                  , VioBiosScrDown               /* Fensterinhalt nach untern scrollen */
                  , NULL                         /* Grafik: Putpixel        */
                  , NULL                         /* Grafik: Getpixel        */
                  , VioStdBackground             /* Background malen        */
#else
                  , NULL
                  , VioUnixLza
                  , VioUnixSa                    /* Attribut setzen         */
                  , VioUnixSz                    /* Zeichen setzen          */
                  , VioUnixSza                   /* Attribut mit Zeichen setzen */
                  , VioUnixSs                    /* String schreiben        */
                  , VioUnixSsa                   /* String mit Attribut schreiben */
                  , VioUnixSwa                   /* Fenster mit Attribut fuellen */
                  , VioUnixSwz                   /* Fenster mit Zeichen fuellen */
                  , VioUnixSwza                  /* Fenster mit Attribut und Zeichen fuellen */
                  , VioUnixSb2w                  /* Buffer auf Schirm schreiben */
                  , VioUnixSw2b                  /* Fensterinhalt speichern */
                  , VioUnixClear                 /* Bildschirm loeschen     */
                  , NULL                         /* Aufloesungsfunktion     */
                  , VioUnixScrUp                 /* Fensterinhalt nach oben scrollen */
                  , VioUnixScrDown               /* Fensterinhalt nach untern scrollen */
                  , NULL                         /* Grafik: Putpixel        */
                  , NULL                         /* Grafik: Getpixel        */
                  , VioUnixBackgr                /* Background malen        */
#endif
                  };
 SVio*          VioDescr     = &VioDescriptor;   /* Globaler Bildschirm-Deskriptor */
 PRIVATE BYTE*  pbSaveScr    = NULL;             /* Puffer, um Bildschirminhalt zu sichern */
 PRIVATE WORD   wOldX        = 0;                /* Gesicherte Cursorspalte */
 PRIVATE WORD   wOldY        = 0;                /* Gesicherte Cursorzeile  */
 PRIVATE BYTE   bLastmode    = 3;                /* Urspruenglicher Bildschirmmodus */
 BOOL           boVioFading  = TRUE;
 BOOL           boVioSaving  = TRUE;

 VOID  CDECL    VioInit      ( iMode )
 INT            iMode;                           /* Gewuenschter Modus      */
 {
#if( !defined UNIX )
  BYTE          bPages;                          /* Anzahl Seiten           */
  WORD          wLength;                         /* Groesse einer Bildseite */
  if( boVioSaving )
  {
   TimerInit();
   ScrGetInfo( &bPages, &wLength );               /* Anzahl Seiten und Bildgroesse ermitteln */
   ScrGetCurPos( &wOldX, &wOldY );                /* Alte Cursorposition merken */
   bLastmode = ScrGetMode();                      /* Alten Modus merken      */
   pbSaveScr = MemAlloc( sizeof( BYTE ) * wLength );
   if( pbSaveScr != NULL ) MemCopy( pbSaveScr, VioSetAdr(), wLength ); /* Bildschirminhalt sichern */
  }
#endif
  VioSetMode( iMode );
 }

 VOID  CDECL    VioDone      ( void )
 {
#if( !defined UNIX )
  BYTE          bPages;                          /* Anzahl Seiten           */
  WORD          wLength;                         /* Groesse einer Bildseite */
  BOOL          boFade       = (VioIsVga()) && (VioGetColors()==16) && (boVioFading==TRUE);
  if( !boVioSaving ) return;
  if( boFade )
  {
   VgaFadeDown();
   VgaSetTurning( VGA_TURN_MONITOR, TRUE );
   VgaSetTurning( VGA_TURN_PALETTE, TRUE );
  }
  if( VioDescr->Done!=NULL ) VioDescr->Done();
  ScrSetMode( bLastmode );                       /* Urspruenglichen Mode setzen */
  ScrGetInfo( &bPages, &wLength );               /* Anzahl Seiten und Bildgroesse ermitteln */
  if( pbSaveScr )                                /* Falls Bildschirm gesichert */
  {
   MemCopy( VioSetAdr(), pbSaveScr, wLength );   /* Inhalt wieder restaurieren */
   MemFree( pbSaveScr, wLength );
  }
  ScrSetCurPos( wOldX, wOldY );                  /* Alte Cursorposition restaurieren */
  if( boFade )
  {
   VgaSetTurning( VGA_TURN_MONITOR, FALSE );
   VgaSetTurning( VGA_TURN_PALETTE, FALSE );
   VgaFadeUp();
  }
  TimerDone();
#else
  VioUnixDone();
#endif
 }

 VOID  CDECL    VioSetMode   ( iMode )
 INT            iMode;
 {
#if( !defined UNIX )
  AGAIN:
  switch( iMode )
  {
   case VIO_NONE:
   case VIO_40x25x2:
   case VIO_40x25:
   case VIO_80x25x2:
   case VIO_80x25:
   case VIO_80x28:
   case VIO_80x50:
   case VIO_MONOCHROM:
        VioBiosInit( VioDescr, iMode );
        break;
   case VIO_MONO2:
        VioMonoInit( VioDescr );
        break;
   case VIO_GR32x20x16:
   case VIO_GR64x20x16:
   case VIO_GR64x35x2:
   case VIO_GR64x35x16:
   case VIO_GR64x48x2:
   case VIO_GR64x48x16:
   case VIO_GR72x48x16:
   case VIO_GR32x20x256:
   case VIO_GR32x24x256:
   case VIO_GR32x40x256:
   case VIO_GR36x48x256:
   case VIO_GR64x40x256:
   case VIO_GR64x48x256:
   case VIO_GR80x60x16:
   case VIO_GR80x60x256:
   case VIO_GR10x76x16:
   case VIO_GR10x76x256:
   case VIO_GR12x10x16:
   case VIO_GR12x10x256:
   case VIO_GR32x20x32K:
   case VIO_GR32x20x64K:
   case VIO_GR32x20x16M:
   case VIO_GR64x48x32K:
   case VIO_GR64x48x64K:
   case VIO_GR64x48x16M:
   case VIO_GR80x60x32K:
   case VIO_GR80x60x64K:
   case VIO_GR51x48x32K:
   case VIO_GR51x48x64K:
        if( !VioGraphInit( VioDescr, iMode ) ) { iMode = 3; goto AGAIN; }
        break;
   case VIO_80x60:
   case VIO_132x25:
   case VIO_132x43:
   case VIO_132x50:
   case VIO_132x60:
        if( !VioVesaInit( VioDescr, iMode ) ) { iMode=VIO_80x25; goto AGAIN; }
        break;
  }
#else
  VioUnixInit( VioDescr, iMode );
#endif
 }

 INT   CDECL    VioGetMode   ( void )
 {
  return( VioDescr->iMode );
 }

 VOID  CDECL    VioStatus    ( pcText, wNorm, wInvers )
 CHAR*          pcText;                          /* Darzustellender Text    */
 WORD           wNorm;                           /* Attribut fuer normalen Text */
 WORD           wInvers;                         /* Attribut fuer Hotkeys   */
 {
  INT           i;                               /* Schleifenzaehler        */
  INT           a            = 0;                /* Positionszaehler        */
  WORD          wAttr        = wNorm;            /* Anfangsattribut NORMAL  */
  for( i=0; pcText[i]!=0; i++ )                  /* Gesamten Text scannen   */
   if( pcText[i]=='~' )                          /* Hotkey-Farbe ein-/aus?  */
    wAttr = ( wAttr == wNorm ) ? wInvers : wNorm;/* Je nachdem Attribut aendern */
   else                                          /* Falls nich Text schreiben */
    VioDescr->Sza( a++, VioGetMaxRow()-1, pcText[i], wAttr );/* und Position erhoehen   */
  for( i=a; i < VioGetMaxCol(); i++ )            /* Rest der Statuszeile    */
   VioDescr->Sza( i, VioGetMaxRow()-1, ' ', wNorm );
 }

 PRIVATE VOID  CDECL    VioStdBackground( void )
 {
  INT           i;                               /* Spaltenzaehler          */
  INT           n;                               /* Zeilenzaehler           */
  BOOL          boMouse      = MouHide();

  for( n=0; n < VioGetMaxRow(); n++ )
  {
   for( i=0; i < VioGetMaxCol(); i++ )
   {
    VioSz( i, n, '²' );
    VioSa( i, n, KOBALT );
   }
  }
  /*
  for( n=0; n < VioGetMaxRow(); n++ )
   for( i=0; i < VioGetMaxCol(); i++ )
    VioDescr->Sza( i, n, '²', KOBALT );
  */
  if( boMouse ) MouShow();
 }
#if( !defined UNIX )
 BYTE* CDECL    VioSetAdr    ( void )
 {
  if( ScrIsMono() )                              /* Monochromer Bildschirm? */
   return( (BYTE*) MK_PTR( 0xB000, 0x0000 ) );   /* Zeiger fuer Bytezugriff setzen */
  return( (BYTE*) MK_PTR( 0xB800, 0x0000 ) );    /* Zeiger fuer Bytezugriff setzen */
 }
#endif

#ifdef          _TEST_VIO_

 #include       <DEFS/BITDEFS.H>
 #include       <conio.h>
 #include       <stdio.h>

 typedef        struct
 {
  WORD          wX;
  WORD          wY;
  INT           iMode;
  CHAR*         pcText;
  INT           iKey;
 } SInfo;

 SInfo          Info[44]
                = { { 1, 0, VIO_NONE,       "0) Keine Umschalt.", '0' }
                  /* -- Textmodi ------------------------------------------ */
                  , { 1, 1, VIO_40x25x2,    "1) Mono:  40 x 25 ", '1' }
                  , { 1, 2, VIO_40x25,      "2) Col.:  40 x 25 ", '2' }
                  , { 1, 3, VIO_80x25x2,    "3) Mono:  80 x 25 ", '3' }
                  , { 1, 4, VIO_80x25,      "4) Col :  80 x 25 ", '4' }
                  , { 1, 5, VIO_MONOCHROM,  "5) Mono Hercules  ", '5' }
                  , { 1, 6, VIO_MONO2,      "6) Mono Zweite K. ", '6' }
                  , { 1, 7, VIO_80x28,      "7) Vga.:  80 x 28 ", '7' }
                  , { 1, 8, VIO_80x50,      "8) Vga.:  80 x 50 ", '8' }
                  , { 1, 9, VIO_80x60,      "9) Vesa:  80 x 60 ", '9' }
                  , { 1,10, VIO_132x25,     "+) Vesa: 132 x 25 ", '+' }
                  , { 1,11, VIO_132x43,     "-) Vesa: 132 x 43 ", '-' }
                  , { 1,12, VIO_132x50,     "*) Vesa: 132 x 50 ", '*' }
                  , { 1,13, VIO_132x60,     "#) Vesa: 132 x 60 ", '#' }
                  /* -- 16 Farben ----------------------------------------- */
                  , {21, 0, VIO_GR64x48x16, "a) 640 x 480 x 16 ", 'a' }
                  , {21, 1, VIO_GR72x48x16 ,"b) 720 x 480 x 16 ", 'b' }
                  , {21, 2, VIO_GR80x60x16, "c) 800 x 600 x 16 ", 'c' }
                  , {21, 3, VIO_GR10x76x16, "d)1024 x 768 x 16 ", 'd' }
                  , {21, 4, VIO_GR12x10x16, "e)1280 x1024 x 16 ", 'e' }
                  /* -- 256 Farben ---------------------------------------- */
                  , {41, 0, VIO_GR32x20x256,"l) 320 x 200 x 256", 'l' }
                  , {41, 1, VIO_GR32x24x256,"m) 320 x 240 x 256", 'm' }
                  , {41, 2, VIO_GR32x40x256,"n) 320 x 400 x 256", 'n' }
                  , {41, 3, VIO_GR36x48x256,"o) 360 x 480 x 256", 'o' }
                  , {41, 4, VIO_GR64x40x256,"p) 640 x 400 x 256", 'p' }
                  , {41, 5, VIO_VE64x40x256,"q) 640 x 400 x 256", 'q' }
                  , {41, 6, VIO_GR64x48x256,"r) 640 x 480 x 256", 'r' }
                  , {41, 7, VIO_GR80x60x256,"s) 800 x 600 x 256", 's' }
                  , {41, 8, VIO_GR10x76x256,"t)1024 x 768 x 256", 't' }
                  , {41, 9, VIO_GR12x10x256,"u)1280 x1024 x 256", 'u' }
                  /* -- Mehr Farben --------------------------------------- */
                  , {21, 6, VIO_GR32x20x32K,"A) 320 x 200 x 32K  ", 'A' }
                  , {21, 7, VIO_GR32x20x64K,"B) 320 x 200 x 64K  ", 'B' }
                  , {21, 8, VIO_GR32x20x16M,"C) 320 x 200 x 16M  ", 'C' }
                  , {21, 9, VIO_GR64x48x32K,"D) 640 x 480 x 32K  ", 'D' }
                  , {21,10, VIO_GR64x48x64K,"E) 640 x 480 x 64K  ", 'E' }
                  , {21,11, VIO_GR64x48x16M,"F) 640 x 480 x 16M  ", 'F' }
                  , {21,12, VIO_GR80x60x32K,"G) 800 x 600 x 32K  ", 'G' }
                  , {21,13, VIO_GR80x60x64K,"H) 800 x 600 x 64K  ", 'H' }
                  , {21,14, VIO_GR51x48x32K,"I) 512 x 480 x 32K  ", 'I' }
                  , {21,15, VIO_GR51x48x64K,"J) 512 x 480 x 64K  ", 'J' }
                  , { 0, 0, -1             ,""                    , 0   }
                  };

 INT            Menu         ( SVio* );

 INT            Menu         ( vio )
 SVio*          vio;
 {
  INT           i            = 0;
  INT           iMax;
  CHAR          ch;
  while( Info[i].iKey!=0 )
  {
   vio->Ssa( Info[i].wX, Info[i].wY, Info[i].pcText, (i%15)+1 );
   i++;
  }
  iMax = i;
  while( 1 )
  {
   ch = getch();
   if( ch==27 ) return( -2 );
   for( i=0; i<iMax; i++ ) if( Info[i].iKey==ch ) return( Info[i].iMode );
  }
 }

 VOID           main         ( void )
 {
  #define       INFO_POS     61
  INT           iMode;
  CHAR          cTemp[100];
  BOOL          boFertig     = FALSE;
  setbuf( stdout, NULL );
  VioInit( VIO_NONE );
  VioClear();
  while( !boFertig )
  {
   VioStatus( " ~F1~ Please Select a driver", 112, 115 );
   if( ( iMode = Menu( VioDescr ) ) != -2 )
   {
    VioDone();
    VioInit( iMode );
    VioClear();
    sprintf( cTemp, "Max X.....: %d", VioGetMaxX() );
    VioSs( INFO_POS, 0, cTemp );
    sprintf( cTemp, "Max Y.....: %d", VioGetMaxY() );
    VioSs( INFO_POS, 1, cTemp );
    sprintf( cTemp, "Max Col...: %d", VioGetMaxCol() );
    VioSs( INFO_POS, 2, cTemp );
    sprintf( cTemp, "Max Row...: %d", VioGetMaxRow() );
    VioSs( INFO_POS, 3, cTemp );
    sprintf( cTemp, "Mono......: %s", VioIsMono() ? "Yes" : "No" );
    VioSs( INFO_POS, 4, cTemp );
    sprintf( cTemp, "Graphic...: %s", VioIsGraph() ? "Yes" : "No" );
    VioSs( INFO_POS, 5, cTemp );
    sprintf( cTemp, "Bios fnc..: %s", VioCanBios() ? "Yes" : "No" );
    VioSs( INFO_POS, 6, cTemp );
   }
   else
    boFertig = TRUE;
  }
  VioDone();
 }

#endif
