 #include       "hilevel/VioBios.h"
 #include       "hilevel/VioMono.h"
 #include       "defs/Ptrdefs.h"
 #include       "defs/Bitdefs.h"

 VOID CDECL     VioMonoInit  ( descr )
 SVio*          descr;
 {
  descr->pbScreen = MK_PTR( 0xB000, 0x0000 );
  descr->wMaxCol  = 80;
  descr->wMaxRow  = 25;
  descr->wFlags  |= VIO_MONO;
 }

