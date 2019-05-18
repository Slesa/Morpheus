 #include       "hilevel/VioBios.h"
 #include       "hilevel/VioVesa.h"
 #include       "lolevel/ScrVesa.h"
 #include       "lolevel/ScrGraph.h"
 #include       "defs/Ptrdefs.h"
 #include       "defs/Errordef.h"
 #include       "defs/Bitdefs.h"

 PRIVATE SVesaInfo     VesaInfo;
 PRIVATE SVesaMode     VesaMode;
 VOID CDECL     VioVesaSza   ( WORD, WORD, CHAR, WORD );
 VOID CDECL     VioVesaPutp  ( WORD, WORD, LONG );
 VOID CDECL     VioVesaPutp16( WORD, WORD, LONG );
 BYTE bpPal[16][3];

 BOOL CDECL     VioVesaInit  ( descr, iMode )
 SVio*          descr;
 INT            iMode;
 {
  INT           i;
  if( ( iMode<0x100 ) || ( VesaQualify( &VesaInfo ) ) != ERR_NONE ) return( FALSE );
  for( i=0; VesaInfo.pwSupport[i]!=0xFFFF; i++ )
  {
   if( VesaInfo.pwSupport[i]==(WORD)iMode ) break;
  }
  if( VesaInfo.pwSupport[i]!=(WORD)iMode ) return( FALSE );
  VesaModeInfo( (WORD)iMode, &VesaMode );
  VgaGetAllPal( 0, 16, (BYTE*)bpPal );
  if( !VesaSetMode( (WORD)iMode ) ) return( FALSE );
  descr->wFlags = VIO_VESA;
  if( !(VesaMode.wModeFlag&BIT3) ) descr->wFlags |= VIO_MONO;
  if( VesaMode.wModeFlag&BIT2 ) descr->wFlags |= VIO_CANBIOS;
  if( VesaMode.wModeFlag&BIT4 )
  {
   descr->wFlags   |= VIO_GRAPH;
   descr->wMaxX     = VesaMode.wMaxX;
   descr->wMaxY     = VesaMode.wMaxY;
   descr->bChHeight = VesaMode.bCharHeight;
   descr->wMaxCol   = VesaMode.wMaxX/VesaMode.bCharWidth;
   descr->wMaxRow   = VesaMode.wMaxY/VesaMode.bCharHeight;
   descr->Sza       = VioVesaSza;
   switch( VesaMode.bBitPerPixel )
   {
    case 4:
         descr->Putpixel  = VioVesaPutp16;
         descr->wColors   = 16;
         break;
    case 8:
         descr->Putpixel  = VioVesaPutp;
         descr->wColors   = 256;
         break;
    case 15:
         descr->Putpixel  = VioVesaPutp;
         descr->wColors   = 32767;
         break;
    default:
         descr->Putpixel  = VioVesaPutp;
         descr->wColors   = 0xFFFF;
         break;
   }
   switch( VesaMode.bCharHeight )
   {
    case 8:
         ScrGrGetChars( SCR_8X8, &descr->bpChars );
         ScrGrGetChars( SCR_8X8+1, &descr->bpChars2 );
         break;
    case 14:
         ScrGrGetChars( SCR_8X14, &descr->bpChars );
         ScrGrGetChars( SCR_8X14+1, &descr->bpChars2 );
         break;
    case 16:
         ScrGrGetChars( SCR_8X16, &descr->bpChars );
         ScrGrGetChars( SCR_8X16+1, &descr->bpChars2 );
         break;
   }
  }
  else
  {
   descr->pbScreen  = MK_PTR( VesaMode.w1stAdress, 0x0000 );
   descr->wMaxCol   = VesaMode.wMaxX;
   descr->wMaxRow   = VesaMode.wMaxY;
   descr->wColors   = 16;
  }
  return( TRUE );
 }

 VOID CDECL     VioVesaSza   ( wX, wY, cCh, wAttr )
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

 VOID CDECL     VioVesaPutp  ( wX, wY, lCol )
 WORD           wX;
 WORD           wY;
 LONG           lCol;
 {
  BYTE*         VesaScreen;
  WORD          wBits        = (VesaMode.bBitPerPixel!=15)?VesaMode.bBitPerPixel/8:2;
  LONG          lSize        = (LONG) VesaMode.wFrameSize * 1024L;
//  LONG          lPos         = (((LONG) wY* (LONG) VesaMode.wLineSize ) + (LONG) wX ) * (LONG) wBits;
  LONG          lPos         = (((LONG) wY* (LONG) VesaMode.wMaxX ) + (LONG) wX ) * (LONG) wBits;
  INT           frame        = lPos / lSize;
  WORD          wPos         = (WORD)( lPos - (LONG) frame * lSize );
  /*
  WORD          wLines       = (WORD) ( ( (LONG)VesaMode.wFrameSize*1024L ) / (LONG) VesaMode.wLineSize );
  WORD          wPos         = wY%wLines;
  INT           frame        = ( wY * VesaMode.wFrameSize ) / (VesaMode.wGranularity* wLines);
  */
  BYTE          bR, bG, bB;
  VesaSetFrame( frame );
  VesaScreen = MK_PTR( VesaMode.w1stAdress, wPos );
//  VesaScreen = MK_PTR( VesaMode.w1stAdress, wPos*VesaMode.wLineSize+wX*wBits );
  switch( VesaMode.bBitPerPixel )
  {
   case 8:
        *(VesaScreen) = (BYTE)lCol;
        break;
   case 15:
        if( lCol>7 )
        {
         bR = bpPal[(INT)lCol-7][0]&31;
         bG = bpPal[(INT)lCol-7][1]&31;
         bB = bpPal[(INT)lCol-7][2]&31;
        }
        else
        {
         bR = bpPal[(INT)lCol][0]&31;
         bG = bpPal[(INT)lCol][1]&31;
         bB = bpPal[(INT)lCol][2]&31;
        }
        lCol = ((LONG)bR<<10L) + ((LONG)bG<<5L) + ((LONG)bB);
        *(WORD*)VesaScreen = (WORD) lCol;
        break;
   case 16:
//        VgaGetPal( (WORD) lCol, &bR, &bG, &bB );
        if( lCol>7 )
        {
         bR = (bpPal[(INT)lCol-7][0]<<1)&31;
         bG = (bpPal[(INT)lCol-7][1]<<1)&31;
         bB = (bpPal[(INT)lCol-7][2]<<1)&31;
        }
        else
        {
         bR = bpPal[(INT)lCol][0]&31;
         bG = bpPal[(INT)lCol][1]&31;
         bB = bpPal[(INT)lCol][2]&31;
        }
        lCol = ((LONG)bR<<10L) + ((LONG)bG<<5L) + ((LONG)bB);
        *(WORD*)VesaScreen = (WORD) lCol;
        break;
   case 24:
   case 32:
//        VgaGetPal( (WORD) lCol, &bR, &bG, &bB );
        bR = bpPal[(INT)lCol][0]<<2;
        bG = bpPal[(INT)lCol][1]<<2;
        bB = bpPal[(INT)lCol][2]<<2;
        *(VesaScreen++) = bR;
        *(VesaScreen++) = bG;
        *(VesaScreen)   = bB;
        break;
  }
 }

 VOID CDECL     VioVesaPutp16( wX, wY, lCol )
 WORD           wX;
 WORD           wY;
 LONG           lCol;
 {
  BYTE*         VesaScreen;
  LONG          lSize        = (LONG) VesaMode.wFrameSize * 1024L;
  LONG          lPos         = (((LONG) wY* (LONG) VesaMode.wLineSize ) + (LONG) wX ) / 2L;
  INT           frame        = lPos / lSize;
  WORD          wPos         = (WORD)( lPos - (LONG) frame * lSize );
  /*
  WORD          wLines       = (WORD) ( ( (LONG)VesaMode.wFrameSize*1024L ) / (LONG) VesaMode.wLineSize );
  WORD          wPos         = wY%wLines;
  INT           frame        = ( wY * VesaMode.wFrameSize ) / (VesaMode.wGranularity* wLines);
  */
  VesaSetFrame( frame );
  VesaScreen = MK_PTR( VesaMode.w1stAdress, wPos );
//  VesaScreen = MK_PTR( VesaMode.w1stAdress, wPos*VesaMode.wLineSize+wX*wBits );
  *(VesaScreen) = (BYTE)lCol;
 }

#ifdef          _TEST_VESA_

 #include       <conio.h>

 #define        MODE         VIO_GR80x60x256
 VOID           main         ( void )
 {
  WORD          wX, wY;
  LONG          l            = 0L;
  VesaModeInfo( MODE, &VesaMode );
  VesaSetMode( MODE );
  for( wY=0; wY<480; wY++ )
   for( wX=0; wX<640; wX++ )
    VioVesaPutp( wX, wY, (l++)/(64L*1024L)+1L );
  getch();
  ScrSetMode( 0x03 );
 }

#endif
