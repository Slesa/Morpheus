 #include       "hilevel/Vio.h"
 #include       "hilevel/VioBios.h"
 #include       "lolevel/ScrBios.h"
 #include       "defs/Bitdefs.h"
 #include       "defs/Colordef.h"
 #include       <stdlib.h>

 VOID CDECL     VioBiosInit  ( descr, iMode )
 SVio*          descr;
 INT            iMode;
 {
  switch( iMode )
  {
   case VIO_NONE:
        break;
   case VIO_80x28:
        ScrSetMode( 0x03 );
        VgaLoad8x14();
        break;
   case VIO_80x50:
        ScrSetMode( 0x03 );
        VgaLoad8x8();
        break;
   case VIO_80x25:
        ScrSetMode( 0x03 );
        if( ScrIsEga() )
        {
         if( ScrIsVga() ) VgaLoad8x16();
         else             VgaLoad8x14();
        }
        break;
   default:
        ScrSetMode( (BYTE) iMode );
  }
  descr->pbScreen = VioSetAdr();
  ScrGetRange( &descr->wMaxCol, &descr->wMaxRow );
  ScrGetRange( &descr->wMaxX, &descr->wMaxY );
  if( ScrIsEga() ) descr->wFlags  |= VIO_EGA;
  if( ScrIsVga() ) descr->wFlags  |= VIO_VGA;
  if( ScrIsMono() ) descr->wFlags |= VIO_MONO;
  descr->wFlags |= VIO_CANBIOS;
  VioDescr->wColors = 16;
  VioDescr->iMode = iMode;
  VioDescr->Lza   = VioBiosLza;
  VioDescr->Sa    = VioBiosSa;
  VioDescr->Sz    = VioBiosSz;
  VioDescr->Sza   = VioBiosSza;
  VioDescr->Ss    = VioBiosSs;
  VioDescr->Ssa   = VioBiosSsa;
  VioDescr->Swa   = VioBiosSwa;
  VioDescr->Swz   = VioBiosSwz;
  VioDescr->Swza  = VioBiosSwza;
  VioDescr->Sb2w  = VioBiosSb2w;
  VioDescr->Sw2b  = VioBiosSw2b;
  VioDescr->Clear = VioBiosClear;
  VioDescr->Done  = NULL;
  VioDescr->ScrollUp = VioBiosScrUp;
  VioDescr->ScrollDown = VioBiosScrDown;
  VioDescr->Putpixel   = NULL;
  VioDescr->Getpixel   = NULL;
 }

 /***************************************************************************/
 /* VioBiosSa                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt an Position x/y das Attribut attr durch direkten Bildschirmspei-  */
 /* cher-Zugriff. Das Zeichen dort wird nicht   geaendert.                  */
 /***************************************************************************/
 VOID CDECL     VioBiosSa    ( wX, wY, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wAttr;                           /* Attribut                */
 {
  VioDescr->pbScreen[ ( ( wY*VioGetMaxCol()+wX ) << 1 ) + 1 ] = wAttr;
 }

 WORD CDECL     VioBiosLa    ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  BYTE          bAttr        = VioDescr->pbScreen[((wY*VioGetMaxCol()+wX)<<1)+1];
  return( (WORD) bAttr );
 }

 WORD CDECL     VioBiosLza   ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  WORD*         pwVioTemp    = (WORD*) VioDescr->pbScreen;
  WORD          wChAttr      = pwVioTemp[wY*VioGetMaxCol()+wX];
  return( wChAttr );
 }

 /***************************************************************************/
 /* VioBiosSz                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt an Position x/y das Zeichen ch durch direkten Bildspeicherzu-     */
 /* griff. Das Attribut dort wird nicht geaendert.                          */
 /***************************************************************************/
 VOID CDECL     VioBiosSz    ( wX, wY, cCh )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR           cCh;                             /* Zeichen                 */
 {
  VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ] = cCh;  /* Direkter Bildschirmzugriff */
 }

 CHAR CDECL     VioBiosLz    ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  WORD*         pwVioTemp     = (WORD*) VioDescr->pbScreen;
  WORD          ch            = pwVioTemp[ wY*VioGetMaxCol()+wX ];
//  BYTE          ch           = VioDescr->pbScreen[(wY*VioGetMaxCol()+wX)<<1];
  return( ch&0xFF );
 }

 /***************************************************************************/
 /* VioBiosSza                                                              */
 /* ----------------------------------------------------------------------- */
 /* Schreibt an Position x/y das Attribut attr und Zeichen ch durch direk-  */
 /* ten Bildschirmspeicherzugriff.                                          */
 /***************************************************************************/
#include <stdio.h>
 VOID CDECL     VioBiosSza   ( wX, wY, cCh, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR           cCh;                             /* Zeichen                 */
 WORD           wAttr;                           /* Attribut                */
 {
 #ifndef        __BORLANDC__
  WORD          wMax          = VioGetMaxCol();
  WORD*         pwVioTemp     = (WORD*) VioDescr->pbScreen;
  WORD          w             = (WORD) cCh;
  pwVioTemp[ wY*wMax+wX ] = (WORD)((wAttr<<8)&0xFF00) + (WORD)(w&0xFF);
 #else
  VioSz( wX, wY, cCh );
  VioSa( wX, wY, wAttr );
 #endif
 }

 /***************************************************************************/
 /* VioBiosSs                                                               */
 /* ----------------------------------------------------------------------- */
 /* Schreibt einen String an Position x/y durch direkten Bildschirmspei-    */
 /* cherzugriff. Das Attribut wird nicht ge„ndert.                          */
 /***************************************************************************/
 VOID CDECL     VioBiosSs    ( wX, wY, pcStr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR*          pcStr;                           /* Der String              */
 {
  BYTE*         pcTmpScreen   = &VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ];
  CHAR*         pc            = pcStr;
  for( ; *pc; pcTmpScreen += 2 ) *pcTmpScreen = *pc++;
 }

 /***************************************************************************/
 /* VioBiosSsa                                                              */
 /* ----------------------------------------------------------------------- */
 /* Schreibt einen String mit Attribut an Position x/y durch direkten       */
 /* Bildschirmspeicherzugriff.                                              */
 /***************************************************************************/
 VOID CDECL     VioBiosSsa   ( wX, wY, pcStr, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR*          pcStr;                           /* Der String              */
 WORD           wAttr;                           /* Attribut des Strings    */
 {
  BYTE*         pcTmpScreen  = &VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ];
  CHAR*         pc           = pcStr;
  while( *pc )
  {
   *pcTmpScreen++ = *pc++;
   *pcTmpScreen++ = (CHAR) wAttr;
  }
 }

 /***************************************************************************/
 /* VioBiosSwa                                                              */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Attribut attr durch direkten Bildschirmspei- */
 /* cherzugriff. Die Zeichen in dem Fenster werden nicht beeinflusst.       */
 /***************************************************************************/
 VOID CDECL     VioBiosSwa   ( wX, wY, wWidth, wHeight, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 WORD           wAttr;                           /* Attribut                */
 {
  BYTE*         pbTmpScreen  = &VioDescr->pbScreen[ ( ( wY*VioGetMaxCol()+wX ) << 1 ) + 1 ];
  WORD          wDelta       = ( VioGetMaxCol()-wWidth ) << 1;
  INT           i;
  for( ; wHeight>0; wHeight--, pbTmpScreen += wDelta )
   for( i=wWidth; i>0; i--, pbTmpScreen += 2 )
    *pbTmpScreen = (BYTE) wAttr;
 }

 /***************************************************************************/
 /* VioBiosSwz                                                              */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Zeichen ch durch direkten Bildschirmspei-    */
 /* cherzugriff. Die Attribute in dem Fenster werden nicht beeinflusst.     */
 /***************************************************************************/
 VOID CDECL     VioBiosSwz   ( wX, wY, wWidth, wHeight, bCh )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 BYTE           bCh;                             /* Zeichen                 */
 {
  BYTE*         pbTmpScreen = &VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ];
  WORD          wDelta      = ( VioGetMaxCol()-wWidth ) << 1;
  INT           i;
  for( ; wHeight>0; wHeight--, pbTmpScreen += wDelta )
   for( i=wWidth; i>0; i--, pbTmpScreen += 2 )
    *pbTmpScreen = (BYTE) bCh;
 }

 /***************************************************************************/
 /* VioBiosSwza                                                             */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Zeichen ch und dem Attribut attr durch di-   */
 /* rekten Bildschirmspeicherzugriff.                                       */
 /***************************************************************************/
 VOID CDECL     VioBiosSwza  ( wX, wY, wWidth, wHeight, cCh, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 BYTE           cCh;                             /* Zeichen                 */
 WORD           wAttr;                           /* Attribut                */
 {
  WORD*         pwTmpScreen  = (WORD*) &VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ];
  WORD          wDelta       = VioGetMaxCol()-wWidth;
  WORD          wChattr      = (WORD) ( ( wAttr<<8 ) | (cCh&0x0FF) );
  INT           i;
  for( ; wHeight>0; wHeight--, pwTmpScreen += wDelta )
   for( i=wWidth; i>0; i-- )
    *pwTmpScreen++ = wChattr;
 }

 /***************************************************************************/
 /* VioBiosSb2w                                                             */
 /* ----------------------------------------------------------------------- */
 /* Muellt einen Pufferinhalt durch direkten Bildschirmspeicherzugriff in   */
 /* ein Fenster.                                                            */
 /***************************************************************************/
 VOID CDECL     VioBiosSb2w  ( wX, wY, wWidth, wHeight, pwBuff )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 WORD*          pwBuff;                          /* Puffer                  */
 {
  WORD*         pwTmpScreen  = (WORD*) &VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ];
  WORD          wDelta       = VioGetMaxCol()-wWidth;
  INT           i;
  for( ; wHeight>0; wHeight--, pwTmpScreen += wDelta )
   for( i=wWidth; i>0; i-- )
    *pwTmpScreen++ = *pwBuff++;
 }

 /***************************************************************************/
 /* VioBiosSw2b                                                             */
 /* ----------------------------------------------------------------------- */
 /* Speichert einen Fensterinhalt durch direkten Bildschirmspeicherzugriff  */
 /* in einem Puffer.                                                        */
 /***************************************************************************/
 VOID CDECL     VioBiosSw2b  ( wX, wY, wWidth, wHeight, pwBuff )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 WORD*          pwBuff;                          /* Puffer                  */
 {
  WORD*         pwTmpScreen  = (WORD*) &VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ];
  WORD          wDelta       = VioGetMaxCol()-wWidth;
  INT           i;
  for( ; wHeight>0; wHeight--, pwTmpScreen += wDelta )
   for( i=wWidth; i>0; i-- )
    *pwBuff++ = *pwTmpScreen++;
 }

 /***************************************************************************/
 /* VioBiosClear                                                            */
 /* ----------------------------------------------------------------------- */
 /* Bildschirm loeschen durch direkten Bildschirmspeicherzugriff.           */
 /***************************************************************************/
 VOID CDECL     VioBiosClear ( void )
 {
  WORD*         pwTmpScreen  = (WORD*) VioDescr->pbScreen;
  WORD          wChAttr      = (WORD)( VH( WEISS, SCHWARZ )<<8 ) | (WORD) ' ';
  INT           i;
  for( i=0; i<VioGetMaxCol()*VioGetMaxRow(); i++ )
   pwTmpScreen[ i ] = wChAttr;
 }

 VOID CDECL     VioBiosScrUp ( wX1, wY1, wX2, wY2, wAttr )
 WORD           wX1;
 WORD           wY1;
 WORD           wX2;
 WORD           wY2;
 WORD           wAttr;
 {
  ScrScrUp( 1, (BYTE)wX1, (BYTE)wY1, (BYTE)wX2, (BYTE)wY2, (BYTE)wAttr );
 }

 VOID CDECL     VioBiosScrDown( wX1, wY1, wX2, wY2, wAttr )
 WORD           wX1;
 WORD           wY1;
 WORD           wX2;
 WORD           wY2;
 WORD           wAttr;
 {
  ScrScrDown( 1, (BYTE)wX1, (BYTE)wY1, (BYTE)wX2, (BYTE)wY2, (BYTE)wAttr );
 }
