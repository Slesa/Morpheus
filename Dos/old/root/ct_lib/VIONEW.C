 #include       <TYPEDEFS.H>
 #include       <INTERRPT.H>
 #include       <stdio.h>
 #include       <ctvio.h>
 
 BYTE*          pbVioScreen    = NULL;           /* Zeiger auf Bildschirm   */
 BYTE           bVioLastmode   = 0;              /* Modus vor Umschalten    */
 VOID           VioSetAdr    ( void );
 
 /***************************************************************************/
 /* VioInit                                                             */
 /* ----------------------------------------------------------------------- */
 /* Setzt, bMode unlgiech 0, den gewuenschten Modus und initialisert die    */
 /* noetigen Werte.                                                         */
 /***************************************************************************/
 VOID           VioInit  ( wMode )
 WORD           wMode;                           /* Gewuenschter (Text-)Modus */
 {
  bVioLastmode = VioGetMode();                   /* Alten Modus merken      */
//  VioSetMode( wMode );                          /* Aber nur, wenn kein VESA-Mode */
  VioSetAdr();                                   /* Neue Bildadressen berechnen */
 }

 /***************************************************************************/
 /* VioSa                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt an Position x/y das Attribut attr durch direkten Bildschirmspei-  */
 /* cher-Zugriff. Das Zeichen dort wird nicht   geaendert.                  */
 /***************************************************************************/
 VOID           VioSa    ( wX, wY, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wAttr;                           /* Attribut                */
 {
  if( pbVioScreen==NULL ) VioInit( 0 );
  pbVioScreen[ ( ( wY*80+wX ) << 1 ) + 1 ] = wAttr;
 }

 /***************************************************************************/
 /* VioSa                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt an Position x/y das Attribut attr durch direkten Bildschirmspei-  */
 /* cher-Zugriff. Das Zeichen dort wird nicht   geaendert.                  */
 /***************************************************************************/
 WORD           VioLa    ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  if( pbVioScreen==NULL ) VioInit( 0 );
  return( pbVioScreen[ ( ( wY*80+wX ) << 1 ) + 1 ] );
 }

 /***************************************************************************/
 /* VioSz                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt an Position x/y das Zeichen ch durch direkten Bildspeicherzu-     */
 /* griff. Das Attribut dort wird nicht geaendert.                          */
 /***************************************************************************/
 CHAR           VioLz    ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  if( pbVioScreen==NULL ) VioInit( 0 );
  return( pbVioScreen[ ( wY*80+wX ) << 1 ] );
 }

 /***************************************************************************/
 /* VioSz                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt an Position x/y das Zeichen ch durch direkten Bildspeicherzu-     */
 /* griff. Das Attribut dort wird nicht geaendert.                          */
 /***************************************************************************/
 VOID           VioSz    ( wX, wY, cCh )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR           cCh;                             /* Zeichen                 */
 {
  if( pbVioScreen==NULL ) VioInit( 0 );
  pbVioScreen[ ( wY*80+wX ) << 1 ] = cCh;  /* Direkter Bildschirmzugriff */
 }


 VOID           VioSza   ( wX, wY, cCh, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR           cCh;                             /* Zeichen                 */
 WORD           wAttr;                           /* Attribut                */
 {
  WORD*         pwVioTemp;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pwVioTemp     = (WORD*) pbVioScreen;
  pwVioTemp[ wY*80+wX ] = ( wAttr<<8 ) | (cCh&0xFF);
 }

 WORD           VioLza   ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  WORD*         pwVioTemp;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pwVioTemp     = (WORD*) pbVioScreen;
  return( pwVioTemp[ wY*80+wX ] );
 }

 /***************************************************************************/
 /* VioSs                                                               */
 /* ----------------------------------------------------------------------- */
 /* Schreibt einen String an Position x/y durch direkten Bildschirmspei-    */
 /* cherzugriff. Das Attribut wird nicht ge„ndert.                          */
 /***************************************************************************/
 VOID           VioSs    ( wX, wY, sStr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 STRING         sStr;                            /* Der String              */
 {
  BYTE*         pcTmpScreen;
  STRING        sCp           = sStr;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pcTmpScreen= &pbVioScreen[ ( wY*80+wX ) << 1 ];
  for( ; *sCp; pcTmpScreen += 2 ) *pcTmpScreen = *sCp++;
 }

 /***************************************************************************/
 /* VioSsa                                                              */
 /* ----------------------------------------------------------------------- */
 /* Schreibt einen String mit Attribut an Position x/y durch direkten       */
 /* Bildschirmspeicherzugriff.                                              */
 /***************************************************************************/
 VOID           VioSsa   ( wX, wY, sStr, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 STRING         sStr;                            /* Der String              */
 WORD           wAttr;                           /* Attribut des Strings    */
 {
  BYTE*         pcTmpScreen;
  STRING        sCp          = sStr;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pcTmpScreen = &pbVioScreen[ ( wY*80+wX ) << 1 ];
  while( *sCp )
  {
   *pcTmpScreen++ = *sCp++;
   *pcTmpScreen++ = (CHAR) wAttr;
  }
 }

 /***************************************************************************/
 /* VioSwa                                                              */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Attribut attr durch direkten Bildschirmspei- */
 /* cherzugriff. Die Zeichen in dem Fenster werden nicht beeinflusst.       */
 /***************************************************************************/
 VOID           VioSwa   ( wX, wY, wWidth, wHeight, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 WORD           wAttr;                           /* Attribut                */
 {
  BYTE*         pbTmpScreen;
  WORD          wDelta       = ( 80-wWidth ) << 1;
  INT           i;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pbTmpScreen = &pbVioScreen[ ( ( wY*80+wX ) << 1 ) + 1 ];
  for( ; wHeight>0; wHeight--, pbTmpScreen += wDelta )
   for( i=wWidth; i>0; i--, pbTmpScreen += 2 )
    *pbTmpScreen = (BYTE) wAttr;
 }

 /***************************************************************************/
 /* VioSwz                                                              */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Zeichen ch durch direkten Bildschirmspei-    */
 /* cherzugriff. Die Attribute in dem Fenster werden nicht beeinflusst.     */
 /***************************************************************************/
 VOID           VioSwz   ( wX, wY, wWidth, wHeight, bCh )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 BYTE           bCh;                             /* Zeichen                 */
 {
  BYTE*         pbTmpScreen;
  WORD          wDelta      = ( 80-wWidth ) << 1;
  INT           i;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pbTmpScreen = &pbVioScreen[ ( wY*80+wX ) << 1 ];
  for( ; wHeight>0; wHeight--, pbTmpScreen += wDelta )
   for( i=wWidth; i>0; i--, pbTmpScreen += 2 )
    *pbTmpScreen = (BYTE) bCh;
 }

 /***************************************************************************/
 /* VioSwza                                                             */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Zeichen ch und dem Attribut attr durch di-   */
 /* rekten Bildschirmspeicherzugriff.                                       */
 /***************************************************************************/
 VOID           VioSwza  ( wX, wY, wWidth, wHeight, cCh, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 CHAR           cCh;                             /* Zeichen                 */
 WORD           wAttr;                           /* Attribut                */
 {
  WORD*         pwTmpScreen;
  WORD          wDelta       = 80-wWidth;
  WORD          wChattr      = (WORD) ( ( wAttr<<8 ) | (cCh&0x0FF) );
  INT           i;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pwTmpScreen = (WORD*) &pbVioScreen[ ( wY*80+wX ) << 1 ];
  for( ; wHeight>0; wHeight--, pwTmpScreen += wDelta )
   for( i=wWidth; i>0; i-- )
    *pwTmpScreen++ = wChattr;
 }

 /***************************************************************************/
 /* VioSb2w                                                             */
 /* ----------------------------------------------------------------------- */
 /* Muellt einen Pufferinhalt durch direkten Bildschirmspeicherzugriff in   */
 /* ein Fenster.                                                            */
 /***************************************************************************/
 VOID           VioSb2w  ( wX, wY, wWidth, wHeight, pwBuff )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 WORD*          pwBuff;                          /* Puffer                  */
 {
  WORD*         pwTmpScreen;
  WORD          wDelta       = 80-wWidth;
  INT          i;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pwTmpScreen  = (WORD*) &pbVioScreen[ ( wY*80+wX ) << 1 ];
  for( ; wHeight>0; wHeight--, pwTmpScreen += wDelta )
   for( i=wWidth; i>0; i-- )
    *pwTmpScreen++ = *pwBuff++;
 }

 /***************************************************************************/
 /* VioSw2b                                                             */
 /* ----------------------------------------------------------------------- */
 /* Speichert einen Fensterinhalt durch direkten Bildschirmspeicherzugriff  */
 /* in einem Puffer.                                                        */
 /***************************************************************************/
 VOID           VioSw2b  ( wX, wY, wWidth, wHeight, pwBuff )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 WORD*          pwBuff;                          /* Puffer                  */
 {
  WORD*         pwTmpScreen;
  WORD          wDelta       = 80-wWidth;
  INT           i;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pwTmpScreen  = (WORD*) &pbVioScreen[ ( wY*80+wX ) << 1 ];
  for( ; wHeight>0; wHeight--, pwTmpScreen += wDelta )
   for( i=wWidth; i>0; i-- )
    *pwBuff++ = *pwTmpScreen++;
 }

 /***************************************************************************/
 /* VioClear                                                            */
 /* ----------------------------------------------------------------------- */
 /* Bildschirm loeschen durch direkten Bildschirmspeicherzugriff.           */
 /***************************************************************************/
 VOID           VioClear ( void )
 {
  WORD*         pwTmpScreen;
  INT           i;
  if( pbVioScreen==NULL ) VioInit( 0 );
  pwTmpScreen  = (WORD*) pbVioScreen;
  for( i=0; i<80*25; i+=2 )
   pwTmpScreen[ i ] = (WORD)( 7 << 8 ) | (WORD) ' ';
 }

 WORD           VioGetMode   ( void )
 {
#if( !defined UNIX )
  SRegs         regs;                            /* Register fuer Interrupt */
  IntSetAH( regs, 0x0F );                        /* Fkt 0: Modus lesen      */
  Interrupt( 0x10, &regs );                      /* BIOS-Aufruf             */
  return( IntGetAL( regs ) );                    /* Modus zurueckliefern    */
#endif
 }

 /***************************************************************************/
 /* VioSetAdr                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt die Startadressen des Bildschirms je nach Modus.                  */
 /***************************************************************************/
 VOID           VioSetAdr    ( void )
 {
  if( bVioLastmode == 7 )                         /* Monochromer Bildschirm? */
  {
//   wVioFlags |= VIO_MONOCHROM;                   /* Dann Flag setzen        */
   pbVioScreen = (BYTE*) MK_PTR( 0xB000, 0x0000 );/* Zeiger fuer Bytezugriff setzen */
  }
  else
   pbVioScreen = (BYTE*) MK_PTR( 0xB800, 0x0000 );/* Zeiger fuer Bytezugriff setzen */
 }

 /***************************************************************************/
 /* VioSetMode                                                              */
 /* ----------------------------------------------------------------------- */
 /* Setzt einen Videomodus.                                                 */
 /***************************************************************************/
 VOID           VioSetMode   ( bMode )
 BYTE           bMode;                           /* Gewuenschter Modus      */
 {
  SRegs         regs;                            /* Register fuer Interrupt */
  IntSetAH( regs, 0x00 );                        /* Fkt 0: Modus setzen     */
  IntSetAL( regs, bMode );                       /* AL = modus              */
  Interrupt( 0x10, &regs );                      /* BIOS-Aufruf             */
//  wVioFlags = 0;
 }

 /***************************************************************************/
 /* ScrSetCurTyp                                                            */
 /* ----------------------------------------------------------------------- */
 /* Cursor-Erscheinungsbild ueber Bios-Funktion setzen.                     */
 /***************************************************************************/
 VOID           VioSetCursorTyp ( bStart, bStop )
 BYTE           bStart;                          /* Startzeile des Cursors  */
 BYTE           bStop;                           /* Endzeile des Cursors    */
 {
#if( !defined UNIX )
  SRegs         regs;                            /* Registerinhalt fuer Interrupt */
  IntSetAH( regs, 1 );                           /* Fkt 1: Cursorbild setzen */
  IntSetCH( regs, bStart );                      /* Neue Startzeile         */
  IntSetCL( regs, bStop );                       /* Neue Endzeile           */
  Interrupt( 0x10, &regs );                      /* BIOS-Aufruf             */
#endif
 }

 /***************************************************************************/
 /* ScrSetCurPos                                                            */
 /* ----------------------------------------------------------------------- */
 /* Cursor uber Bios-Funktion positionieren.                                */
 /***************************************************************************/
 VOID           VioSetCursorPos ( wX, wY )
 WORD           wX;                               /* Spalte                 */
 WORD           wY;                               /* Zeile                  */
 {
#if( !defined UNIX )
  SRegs         regs;                             /* Registerzugriff        */
  IntSetAH( regs, 2 );                            /* Fkt 2: Cursorposition setzen */
  IntSetBH( regs, 0 );                            /* Auf Bildschirmseite 0  */
  IntSetDH( regs, (BYTE) wY );                    /* Neue Cursorspalte      */
  IntSetDL( regs, (BYTE) wX );                    /* Neue Cursorzeile       */
  Interrupt( 0x10, &regs );                       /* BIOS-Aufruf            */
#endif
 }

 /***************************************************************************/
 /* ScrGetCurPos                                                            */
 /* ----------------------------------------------------------------------- */
 /* Aktuelle Cursorposition ermitteln.                                      */
 /***************************************************************************/
 VOID           VioGetCursor ( wX, wY, wDummy, wDummy2 )
 WORD*          wX;                               /* Puffer fuer Spalte     */
 WORD*          wY;                               /* Puffer fuer Zeile      */
 WORD*          wDummy;
 WORD*          wDummy2;
 {
#if( !defined UNIX )
  SRegs         regs;                             /* Registerzugriff        */
  IntSetAH( regs, 3 );                            /* Fkt 3: Cursorposition ermitteln */
  IntSetBH( regs, 0 );                            /* Auf Bildschirmseite 0  */
  Interrupt( 0x10, &regs );                       /* BIOS-Aufruf            */
  *wX = (WORD) IntGetDL( regs );                  /* X-Position ermitteln   */
  *wY = (WORD) IntGetDH( regs );                  /* Y-Position ermitteln   */
#endif
 }


