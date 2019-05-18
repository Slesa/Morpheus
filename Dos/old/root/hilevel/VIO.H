/****************************************************************************/
/* VIO.H                                                                    */
/* ------------------------------------------------------------------------ */
/* Definition der Funktionen zum Zugriff auf den PC-Bildschirm.             */
/****************************************************************************/
#ifndef         _VIO_

 #define        _VIO_
 #include       "defs/Typedefs.h"                /* Grundlegende Datentypen */
 #include       "lolevel/ScrBios.h"              /* Standardfunktionen BIOS */
 #include       "lolevel/ScrVesa.h"              /* VESA-API                */
 #include       "lolevel/ScrVga.h"               /* VGA-Routinen            */

 /* ----------- Funktionstypen -------------------------------------------- */
 typedef VOID (CDECL *FVioSa)    PARAM(( WORD, WORD, WORD ));
 typedef VOID (CDECL *FVioSz)    PARAM(( WORD, WORD, CHAR ));
 typedef VOID (CDECL *FVioSza)   PARAM(( WORD, WORD, CHAR, WORD ));
 typedef WORD (CDECL *FVioLza)   PARAM(( WORD, WORD ));
 typedef VOID (CDECL *FVioSs)    PARAM(( WORD, WORD, CHAR* ));
 typedef VOID (CDECL *FVioSsa)   PARAM(( WORD, WORD, CHAR*, WORD ));
 typedef VOID (CDECL *FVioSwa)   PARAM(( WORD, WORD, WORD, WORD, WORD ));
 typedef VOID (CDECL *FVioSwz)   PARAM(( WORD, WORD, WORD, WORD, BYTE ));
 typedef VOID (CDECL *FVioSwza)  PARAM(( WORD, WORD, WORD, WORD, BYTE, WORD ));
 typedef VOID (CDECL *FVioCopy)  PARAM(( WORD, WORD, WORD, WORD, WORD* ));
 typedef VOID (CDECL *FVioClear) PARAM(( void ));
 typedef VOID (CDECL *FVioScroll)PARAM(( WORD, WORD, WORD, WORD, WORD ));
 typedef VOID (CDECL *FVioDone)  PARAM(( void ));
 typedef VOID (CDECL *FVioPutp)  PARAM(( WORD, WORD, LONG ));
 typedef LONG (CDECL *FVioGetp)  PARAM(( WORD, WORD ));
 typedef VOID (CDECL *FVioBackgr) PARAM(( void ));

 /* ----------- Bildschirmdeskriptor -------------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  INT           iMode;                           /* Aktueller Modus         */
  WORD          wMaxX;                           /* Grafik: X-Aufloesung    */
  WORD          wMaxY;                           /* Grafik: Y-Aufloesung    */
  BYTE*         bpChars;                         /* Grafik: Zeichentabelle  */
  BYTE*         bpChars2;                        /* Grafik: Zeichentabelle  */
  BYTE          bChHeight;                       /* Grafik: Zeichenhoehe    */
  WORD          wMaxCol;                         /* Anzahl Spalten          */
  WORD          wMaxRow;                         /* Anzahl Zeilen           */
  WORD          wFlags;                          /* Diverse Flags           */
  WORD          wColors;                         /* Anzahl Bits pro Farbe   */
  BYTE*         pbScreen;                        /* Bildschirmzeiger        */
  FVioLza       Lza;                             /* Zeichen/Attrib. lesen   */
  FVioSa        Sa;                              /* Attribut setzen         */
  FVioSz        Sz;                              /* Zeichen setzen          */
  FVioSza       Sza;                             /* Attribut mit Zeichen setzen */
  FVioSs        Ss;                              /* String schreiben        */
  FVioSsa       Ssa;                             /* String mit Attribut schreiben */
  FVioSwa       Swa;                             /* Fenster mit Attribut fuellen */
  FVioSwz       Swz;                             /* Fenster mit Zeichen fuellen */
  FVioSwza      Swza;                            /* Fenster mit Attribut und Zeichen fuellen */
  FVioCopy      Sb2w;                            /* Buffer auf Schirm schreiben */
  FVioCopy      Sw2b;                            /* Fensterinhalt speichern */
  FVioClear     Clear;                           /* Bildschirm loeschen     */
  FVioDone      Done;                            /* Aufloesungsfunktion     */
  FVioScroll    ScrollUp;                        /* Fensterinhalt nach oben scrollen */
  FVioScroll    ScrollDown;                      /* Fensterinhalt nach untern scrollen */
  FVioPutp      Putpixel;                        /* Grafik: Punkt setzen    */
  FVioGetp      Getpixel;                        /* Grafik: Punkt lesen     */
  FVioBackgr    Background;
 } SVio;

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 VOID  CDECL    VioInit         PARAM(( INT ));            /* Bildschirm initialisieren */
 VOID  CDECL    VioDone         PARAM(( void ));
 VOID  CDECL    VioSetMode      PARAM(( INT ));
 INT   CDECL    VioGetMode      PARAM(( void ));
 VOID  CDECL    VioStatus       PARAM(( CHAR*, WORD, WORD ));
 VOID  CDECL    VioBackground   PARAM(( void ));
#if( !defined UNIX )
 BYTE* CDECL    VioSetAdr       PARAM(( void ));           /* Bildadresse setzen      */
#endif
 DECLEND

 /* ----------- Mappings fuer Default-Fall -------------------------------- */
 #define        VioClear()                          VioDescr->Clear()
 #define        VioLza( x, y )                      VioDescr->Lza( x, y )
 #define        VioSa( x, y, attr )                 VioDescr->Sa( x, y, attr )
 #define        VioSz( x, y, ch )                   VioDescr->Sz( x, y, ch )
 #define        VioSza( x, y, ch, attr )            VioDescr->Sza( x, y, ch, attr )
 #define        VioSs( x, y, str )                  VioDescr->Ss( x, y, str )
 #define        VioSsa( x, y, str, attr )           VioDescr->Ssa( x, y, str, attr )
 #define        VioSwa( x1, y1, x2, y2, attr )      VioDescr->Swa( x1, y1, x2, y2, attr )
 #define        VioSwz( x1, y1, x2, y2, ch )        VioDescr->Swz( x1, y1, x2, y2, ch )
 #define        VioSwza( x1, y1, x2, y2, ch, attr ) VioDescr->Swza( x1, y1, x2, y2, ch, attr )
 #define        VioSb2w( x1, y1, x2, y2, buff )     VioDescr->Sb2w( x1, y1, x2, y2, buff )
 #define        VioSw2b( x1, y1, x2, y2, buff )     VioDescr->Sw2b( x1, y1, x2, y2, buff )
 #define        VioClear()                          VioDescr->Clear()
 #define        VioScrUp( x1, y1, x2, y2, attr )    VioDescr->ScrollUp( x1, y1, x2, y2, attr )
 #define        VioScrDown( x1, y1, x2, y2, attr )  VioDescr->ScrollDown( x1, y1, x2, y2, attr )
 #define        VioPutp( x, y, col )                VioDescr->Putpixel( x, y, col )
 #define        VioGetp( x, y )                     VioDescr->Getpixel( x, y )
 #define        VioBackground()                     VioDescr->Background()

 #define        VioGetMaxX()                        VioDescr->wMaxX
 #define        VioGetMaxY()                        VioDescr->wMaxY
 #define        VioGetMaxCol()                      VioDescr->wMaxCol
 #define        VioGetMaxRow()                      VioDescr->wMaxRow
 #define        VioGetColors()                      VioDescr->wColors
 #define        VioCenterX( wLen )                  ( ( VioGetMaxX()-wLen ) / 2 )
 #define        VioCenterY( wHeight )               ( ( VioGetMaxY()-wHeight ) / 2 )
 #define        VioCenterCol( wLen )                ( ( VioGetMaxCol()-wLen ) / 2 )
 #define        VioCenterRow( wHeight )             ( ( VioGetMaxRow()-wHeight ) / 2 )

 #define        VioIsMono()                         ( VioDescr->wFlags&VIO_MONO )
 #define        VioIsEga()                          ( VioDescr->wFlags&VIO_EGA )
 #define        VioIsVga()                          ( VioDescr->wFlags&VIO_VGA )
 #define        VioIsGraph()                        ( VioDescr->wFlags&VIO_GRAPH )
 #define        VioCanBios()                        ( VioDescr->wFlags&VIO_CANBIOS )
 #define        VioIsVesa()                         ( VioDescr->wFlags&VIO_VESA )
 #define        VioIsBlock()                        ( VioDescr->wFlags&VIO_BLOCKMODE )

 /* ----------- Moegliche Flags fuer den Bildschirm ----------------------- */
 #define        VIO_MONO        BIT0             /* Bildschirm ist S/W      */
 #define        VIO_EGA         BIT1
 #define        VIO_VGA         BIT2
 #define        VIO_GRAPH       BIT3             /* Bildschirm ist im Grafikmodus */
 #define        VIO_VESA        BIT4             /* Vesamodus aktiv         */
 #define        VIO_CANBIOS     BIT5             /* Bios-Fkt unterstuetzt?  */
 #define        VIO_BLOCKMODE   BIT6             /* Bildschirm ist Display  */

 /* ----------- Moegliche Bildschirm-Modi --------------------------------- */
 #define        VIO_NONE        -1               /* Keine Modusumschaltung  : OKAY */
 #define        VIO_40x25x2     SCR_BW40x25      /* 40 x 25 S/W             : OKAY */
 #define        VIO_40x25       SCR_CO40x25      /* 40 x 25 x 16            : OKAY */
 #define        VIO_80x25x2     SCR_BW80x25      /* 80 x 25 S/W             : OKAY */
 #define        VIO_80x25       SCR_CO80x25      /* 80 x 25 x 16            : OKAY */
 #define        VIO_GR32x20x4   SCR_GR32x20x4    /* Graph: 320 x 200 x   4  */
 #define        VIO_GR32x20x2   SCR_GR32x20x2    /* Graph: 320 x 200 S/W    */
 #define        VIO_GR64x20x2   SCR_GR64x20x2    /* Graph: 640 x 200 S/W    */
 #define        VIO_MONOCHROM   SCR_MONO         /* Monochrom-Karte         */
 #define        VIO_GR32x20x16  SCR_GR32x20x16   /* Graph: 320 x 200 x  16  */
 #define        VIO_GR64x20x16  SCR_GR64x20x16   /* Graph: 640 x 200 x  16  */
 #define        VIO_GR64x35x2   SCR_GR64x35x2    /* Graph: 640 x 350 S/W    */
 #define        VIO_GR64x35x16  SCR_GR64x35x16   /* Graph: 640 x 350 x  16  */
 #define        VIO_GR64x48x2   SCR_GR64x48x2    /* Graph: 640 x 480 x   2  */
 #define        VIO_GR64x48x16  SCR_GR64x48x16   /* Graph: 640 x 480 x  16  : OKAY */
 #define        VIO_GR32x20x256 SCR_GR32x20x256  /* Graph: 320 x 200 x 256  : OKAY */

 /* ----------- Extra-Modi ------------------------------------------------ */
 #define        VIO_MONO2       0x200            /* Zweiter Bildschirm      : OKAY */
 #define        VIO_80x28       0x201            /* Vga: 80 x 28 x 16       : OKAY */
 #define        VIO_80x50       0x202            /* Vga: 80 x 50 x 16       : OKAY */
 #define        VIO_GR32x24x256 SCR_GR32x24x256  /* Graph: 320 x  240 x 256 : OKAY */
 #define        VIO_GR32x40x256 SCR_GR32x40x256  /* Graph: 320 x  400 x 256 : OKAY */
 #define        VIO_GR36x48x256 SCR_GR36x48x256  /* Graph: 360 x  480 x 256 : OKAY */
 #define        VIO_GR64x40x256 SCR_GR64x40x256  /* Graph: 640 x  400 x 256 */
 #define        VIO_GR72x48x16  SCR_GR72x48x16   /* Graph: 720 x 400 x  16  : OKAY */

 /* ----------- Vesa-Modi ------------------------------------------------- */
 #define        VIO_80x60       VESA_80x60       /*  80 x 60 x 16           */
 #define        VIO_132x25      VESA_132x25      /* 132 x 25 x 16           */
 #define        VIO_132x43      VESA_132x43      /* 132 x 43 x 16           */
 #define        VIO_132x50      VESA_132x50      /* 132 x 50 x 16           */
 #define        VIO_132x60      VESA_132x60      /* 132 x 60 x 16           */
 #define        VIO_GR80x60x16  VESA_GR_80x60x16 /* Graph: 800 x  600 x  16 */
 #define        VIO_GR10x76x16  VESA_GR_10x76x16 /* Graph:1024 x  768 x  16 */
 #define        VIO_GR12x10x16  VESA_GR_12x10x16 /* Graph:1280 x 1024 x  16 */
 #define        VIO_VE64x40x256 VESA_GR_64x40x256/* Graph: 640 x  400 x 256 */
 #define        VIO_GR64x48x256 VESA_GR_64x48x256/* Graph: 640 x  480 x 256 : OKAY */
 #define        VIO_GR80x60x256 VESA_GR_80x60x256/* Graph: 800 x  600 x 256 : OKAY */
 #define        VIO_GR10x76x256 VESA_GR_10x76x256/* Graph:1024 x  768 x 256 : OKAY */
 #define        VIO_GR12x10x256 VESA_GR_12x10x256/* Graph:1280 x 1024 x 256 : OKAY */
 #define        VIO_GR32x20x32K VESA_GR_32x20x32K/* Graph: 320 x  200 x 32K */
 #define        VIO_GR64x48x32K VESA_GR_64x48x32K/* Graph: 640 x  400 x 32K */
 #define        VIO_GR80x60x32K VESA_GR_80x60x32K/* Graph: 800 x  600 x 32K */
 #define        VIO_GR51x48x32K VESA_GR_51x48x32K/* Graph: 512 x  480 x 32K */
 #define        VIO_GR32x20x64K VESA_GR_32x20x64K/* Graph: 320 x  200 x 64K */
 #define        VIO_GR64x48x64K VESA_GR_64x48x64K/* Graph: 640 x  480 x 64K */
 #define        VIO_GR80x60x64K VESA_GR_80x60x64K/* Graph: 800 x  600 x 64K */
 #define        VIO_GR51x48x64K VESA_GR_51x48x64K/* Graph: 512 x  480 x 64K */
 #define        VIO_GR32x20x16M VESA_GR_32x20x16M/* Graph: 320 x  200 x 16M */
 #define        VIO_GR64x48x16M VESA_GR_64x48x16M/* Graph: 640 x  480 x 16M */

 /* ----------- Der Hauptbildschirm --------------------------------------- */
 DECLSTART
 extern         SVio*        VioDescr;
 DECLEND

#endif
