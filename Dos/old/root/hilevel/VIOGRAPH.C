 #include       "hilevel/VioGraph.h"
 #include       "hilevel/VioBios.h"
 #include       "hilevel/VioVesa.h"
 #include       "lolevel/ScrGraph.h"
 #include       "lolevel/ScrBios.h"
 #include       "lolevel/ScrGr16.h"
 #include       "lolevel/ScrGr256.h"
 #include       "lolevel/PcMouse.h"
 #include       "basics/MemAlloc.h"
 #include       "defs/Ptrdefs.h"
 #include       "defs/Bitdefs.h"
 #include       "defs/Typedefs.h"
 #include       <stdio.h>

 BOOL CDECL     VioGraphInit ( vio, iMode )
 SVio*          vio;
 INT            iMode;
 {
  switch( iMode )
  {
   case VIO_GR32x20x16:
        vio->wMaxX   = 320;
        vio->wMaxY   = 200;
        vio->wColors = 16;
//        if( !VioGr16Init( vio ) ) return( FALSE );
        break;
   case VIO_GR64x20x16:
        vio->wMaxX   = 640;
        vio->wMaxY   = 200;
        vio->wColors = 16;
//        if( !VioGr16Init( vio ) ) return( FALSE );
        break;
   case VIO_GR64x35x2:
        vio->wMaxX   = 640;
        vio->wMaxY   = 350;
        vio->wColors = 2;
        break;
   case VIO_GR64x35x16:
        vio->wMaxX   = 640;
        vio->wMaxY   = 350;
        vio->wColors = 16;
//        if( !VioGr16Init( vio ) ) return( FALSE );
        break;
   case VIO_GR64x48x2:
        vio->wMaxX   = 640;
        vio->wMaxY   = 480;
        vio->wColors = 2;
        break;
   case VIO_GR64x48x16:
        if( !Gr64x48x16Init() ) return( FALSE );
        vio->wMaxX    = 640;
        vio->wMaxY    = 480;
        vio->wColors  = 16;
        vio->Putpixel = ScrGrPutp16;
        break;
   case VIO_GR72x48x16:
        if( !Gr72x48x16Init() ) return( FALSE );
        vio->wMaxX    = 720;
        vio->wMaxY    = 480;
        vio->wColors  = 16;
        vio->Putpixel = ScrGrPutp16;
        break;
   case VIO_GR32x20x256:
        if( !ScrGrInit256( iMode ) ) return( FALSE );
        vio->wMaxX    = 320;
        vio->wMaxY    = 200;
        vio->wColors  = 256;
        vio->Putpixel = ScrGrPutp256;
        break;
   case VIO_GR32x24x256:
        if( !ScrGrInit256( iMode ) ) return( FALSE );
        vio->wMaxX    = 320;
        vio->wMaxY    = 240;
        vio->wColors  = 256;
        vio->Putpixel = ScrGrPutp256;
        break;
   case VIO_GR32x40x256:
        if( !ScrGrInit256( iMode ) ) return( FALSE );
        vio->wMaxX    = 320;
        vio->wMaxY    = 400;
        vio->wColors  = 256;
        vio->Putpixel = ScrGrPutp256;
        break;
   case VIO_GR36x48x256:
        if( !ScrGrInit256( iMode ) ) return( FALSE );
        vio->wMaxX   = 360;
        vio->wMaxY   = 480;
        vio->wColors = 256;
        vio->Putpixel = ScrGrPutp256;
        break;
   case VIO_GR64x40x256:
        if( !ScrGrInit256( iMode ) ) return( FALSE );
        vio->wMaxX   = 640;
        vio->wMaxY   = 400;
        vio->wColors = 256;
        vio->Putpixel = ScrGrPutp256;
        break;
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
        if( !VioVesaInit( VioDescr, iMode ) ) return( FALSE );
        break;
   default:
        return( FALSE );
  }
  if( !VioIsVesa() )
  {
  if( vio->wMaxX>=400 )
  {
   ScrGrGetChars( SCR_8X16, &vio->bpChars );
   ScrGrGetChars( 7, &vio->bpChars2 );
   vio->bChHeight= 16;
  }
  else
  {
   ScrGrGetChars( 3, &vio->bpChars );
   ScrGrGetChars( 2, &vio->bpChars2 );
   vio->bChHeight= 8;
  }
  vio->wMaxCol  = vio->wMaxX/8;
  vio->wMaxRow  = vio->wMaxY/vio->bChHeight;
  vio->Sza      = VioGrSza;
  }
  vio->pbScreen = MemAlloc( VioGetMaxCol()*VioGetMaxRow()*2 );
  if( vio->pbScreen==NULL ) return( FALSE );
  vio->iMode    = iMode;
  MouSetModus( TRUE, 8, vio->bChHeight );
  VioBiosClear();
  vio->wFlags   = VIO_GRAPH;
  vio->Sa       = VioGrSa;
  vio->Sz       = VioGrSz;
  vio->Ss       = VioGrSs;
  vio->Ssa      = VioGrSsa;
  vio->Swa      = VioGrSwa;
  vio->Swz      = VioGrSwz;
  vio->Swza     = VioGrSwza;
  vio->Done     = VioGrDone;
  if( ScrIsEga() )  vio->wFlags  |= VIO_EGA;
  if( ScrIsVga() )  vio->wFlags  |= VIO_VGA;
  if( ScrIsMono() ) vio->wFlags  |= VIO_MONO;
  return( TRUE );
 }

 VOID CDECL     VioGrDone    ( void )
 {
  MemFree( VioDescr->pbScreen, VioGetMaxCol()*VioGetMaxRow()*2 );
 }

 VOID CDECL     VioGrSa       ( wX, wY, wAttr )
 WORD           wX;
 WORD           wY;
 WORD           wAttr;
 {
  VioSza( wX, wY, VioBiosLz( wX, wY ), wAttr );
 }

 VOID CDECL     VioGrSz       ( wX, wY, cCh )
 WORD           wX;
 WORD           wY;
 CHAR           cCh;
 {
  VioSza( wX, wY, cCh, VioBiosLa( wX, wY ) );
 }

 VOID CDECL     VioGrSza      ( wX, wY, cCh, wAttr )
 WORD           wX;
 WORD           wY;
 CHAR           cCh;
 WORD           wAttr;
 {
  INT           bH;
  INT           bI;
  WORD          bVal;
  BYTE*         bpCh         = (cCh>0) ? VioDescr->bpChars : VioDescr->bpChars2;
  VioBiosSza( wX, wY, cCh, wAttr );
  wX *= 8;
  wY *= VioDescr->bChHeight;
  for( bH=0; bH<VioDescr->bChHeight; bH++ )
  {
   bVal = bpCh[(WORD)VioDescr->bChHeight*(WORD)cCh+(WORD)bH];
   for( bI=0; bI<8; bI++ )
    VioPutp( wX+(7-bI), wY+bH, bVal&(1<<bI) ? (LONG)(wAttr&0x0F) : (LONG) ((wAttr>>4)&0x0F) );
  }
 }

 VOID CDECL     VioGrSs      ( wX, wY, pcStr )
 WORD           wX;
 WORD           wY;
 CHAR*          pcStr;
 {
  WORD          w;
  for( w=0; pcStr[w]!=0; w++ ) VioSz( wX+w, wY, pcStr[w] );
 }

 VOID CDECL     VioGrSsa     ( wX, wY, pcStr, wAttr )
 WORD           wX;
 WORD           wY;
 CHAR*          pcStr;
 WORD           wAttr;
 {
  WORD          w;
  for( w=0; pcStr[w]!=0; w++ ) VioSza( wX+w, wY, pcStr[w], wAttr );
 }

 VOID CDECL     VioGrSwa      ( wX1, wY1, wX2, wY2, wAttr )
 WORD           wX1;
 WORD           wY1;
 WORD           wX2;
 WORD           wY2;
 WORD           wAttr;
 {
  WORD          w1;
  WORD          w2;
  for( w1=wY1; w1<wY1+wY2; w1++ )
   for( w2=wX1; w2<wX1+wX2; w2++ )
    VioSa( w2, w1, wAttr );
 }

 VOID CDECL     VioGrSwz     ( wX1, wY1, wX2, wY2, bCh )
 WORD           wX1;
 WORD           wY1;
 WORD           wX2;
 WORD           wY2;
 BYTE           bCh;
 {
  WORD          w1;
  WORD          w2;
  for( w1=wY1; w1<=wY1+wY2; w1++ )
   for( w2=wX1; w2<=wX1+wX2; w2++ )
    VioSz( w2, w1, bCh );
 }

 VOID CDECL     VioGrSwza    ( wX1, wY1, wX2, wY2, bCh, wAttr )
 WORD           wX1;
 WORD           wY1;
 WORD           wX2;
 WORD           wY2;
 BYTE           bCh;
 WORD           wAttr;
 {
  WORD          w1;
  WORD          w2;
  for( w1=wY1; w1<wY1+wY2; w1++ )
   for( w2=wX1; w2<wX1+wX2; w2++ )
    VioGrSza( w2, w1, bCh, wAttr );
 }

