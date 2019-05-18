 #include       "hilevel/Vio.h"
 #include       "hilevel/VioUnix.h"
 #include       "lolevel/ScrBios.h"
 #include       "lolevel/Curses.h"
 #include       "defs/Bitdefs.h"
 #include       "defs/Colordef.h"
 #include       <stdlib.h>

 #define        MAX_X        80
 #define        MAX_Y        25

 extern WINDOW* curswin;

 VOID CDECL     VioUnixInit  ( descr, iMode )
 SVio*          descr;
 INT            iMode;
 {
  CursInit();

  if( has_colors() )
  {
     VioDescr->wColors = 16;
     VioDescr->wFlags  |= VIO_VGA;
  }
  else
  {
    VioDescr->wFlags  |= VIO_MONO;
    VioDescr->wColors = 2;
  }

  VioDescr->wMaxCol = 80;
  VioDescr->wMaxX   = 25;
  VioDescr->iMode = iMode;
  VioDescr->Lza   = VioUnixLza;
  VioDescr->Sa    = VioUnixSa;
  VioDescr->Sz    = VioUnixSz;
  VioDescr->Sza   = VioUnixSza;
  VioDescr->Ss    = VioUnixSs;
  VioDescr->Ssa   = VioUnixSsa;
  VioDescr->Swa   = VioUnixSwa;
  VioDescr->Swz   = VioUnixSwz;
  VioDescr->Swza  = VioUnixSwza;
  VioDescr->Sb2w  = VioUnixSb2w;
  VioDescr->Sw2b  = VioUnixSw2b;
  VioDescr->Clear = VioUnixClear;
  VioDescr->Done  = NULL;
  VioDescr->ScrollUp = VioUnixScrUp;
  VioDescr->ScrollDown = VioUnixScrDown;
  VioDescr->Putpixel   = NULL;
  VioDescr->Getpixel   = NULL;
  VioDescr->pbScreen   = (BYTE*) MemAlloc(VioDescr->wMaxCol*2*VioDescr->wMaxRow*2);
 }

 VOID CDECL     VioUnixDone  ( void )
 {
  if(VioDescr->pbScreen)
   MemFree(VioDescr->pbScreen, VioDescr->wMaxCol*2*VioDescr->wMaxRow*2);
  CursDone();
 }

 VOID  CDECL    VioUnixBackgr( void )
 {
  #ifdef NEVER
  INT           i;                               /* Spaltenzaehler          */
  INT           n;                               /* Zeilenzaehler           */
  BOOL          boMouse      = MouHide();

  for( n=0; n < VioGetMaxRow(); n++ )
  {
   for( i=0; i < VioGetMaxCol(); i++ )
   {
    mvwaddch(curswin, n, i, '©');
   }
  }
  wrefresh(curswin);
  if( boMouse ) MouShow();
  #endif
 }

 /***************************************************************************/
 /* VioUnixSa                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt an Position x/y das Attribut attr durch direkten Bildschirmspei-  */
 /* cher-Zugriff. Das Zeichen dort wird nicht   geaendert.                  */
 /***************************************************************************/
 VOID CDECL     VioUnixSa    ( wX, wY, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wAttr;                           /* Attribut                */
 {
  VioDescr->pbScreen[ ( ( wY*VioGetMaxCol()+wX ) << 1 ) + 1 ] = wAttr;
  wmove(curswin,wY, wX);
  wattrset(curswin,wAttr);
  wstandend(curswin);
  wrefresh(curswin);
 }

 WORD CDECL     VioUnixLa    ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  BYTE          bAttr        = VioDescr->pbScreen[((wY*VioGetMaxCol()+wX)<<1)+1];
  return( (WORD) bAttr );
 }

 WORD CDECL     VioUnixLza   ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  WORD*         pwVioTemp    = (WORD*) VioDescr->pbScreen;
  WORD          wChAttr      = pwVioTemp[wY*VioGetMaxCol()+wX];
  return( wChAttr );
 }

 /***************************************************************************/
 /* VioUnixSz                                                               */
 /* ----------------------------------------------------------------------- */
 /* Setzt an Position x/y das Zeichen ch durch direkten Bildspeicherzu-     */
 /* griff. Das Attribut dort wird nicht geaendert.                          */
 /***************************************************************************/
 VOID CDECL     VioUnixSz    ( wX, wY, cCh )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR           cCh;                             /* Zeichen                 */
 {
  VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ] = cCh;  /* Direkter Bildschirmzugriff */
  mvwaddch(curswin, wY, wX, cCh);
  wrefresh(curswin);
 }

 CHAR CDECL     VioUnixLz    ( wX, wY )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 {
  WORD*         pwVioTemp     = (WORD*) VioDescr->pbScreen;
  WORD          ch            = pwVioTemp[ wY*VioGetMaxCol()+wX ];
//  BYTE          ch           = VioDescr->pbScreen[(wY*VioGetMaxCol()+wX)<<1];
  return( ch&0xFF );
 }

 /***************************************************************************/
 /* VioUnixSza                                                              */
 /* ----------------------------------------------------------------------- */
 /* Schreibt an Position x/y das Attribut attr und Zeichen ch durch direk-  */
 /* ten Bildschirmspeicherzugriff.                                          */
 /***************************************************************************/
 VOID CDECL     VioUnixSza   ( wX, wY, cCh, wAttr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR           cCh;                             /* Zeichen                 */
 WORD           wAttr;                           /* Attribut                */
 {
  WORD          wMax          = VioGetMaxCol();
  WORD*         pwVioTemp     = (WORD*) VioDescr->pbScreen;
  WORD          w             = (WORD) cCh;
  pwVioTemp[ wY*wMax+wX ] = (WORD)((wAttr<<8)&0xFF00) + (WORD)(w&0xFF);
  wmove(curswin,wY, wX);
  wattrset(curswin,wAttr);
  waddch(curswin, cCh);
  wstandend(curswin);
  wrefresh(curswin);
 }

 /***************************************************************************/
 /* VioUnixSs                                                               */
 /* ----------------------------------------------------------------------- */
 /* Schreibt einen String an Position x/y durch direkten Bildschirmspei-    */
 /* cherzugriff. Das Attribut wird nicht ge„ndert.                          */
 /***************************************************************************/
 VOID CDECL     VioUnixSs    ( wX, wY, pcStr )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 CHAR*          pcStr;                           /* Der String              */
 {
  BYTE*         pcTmpScreen   = &VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ];
  CHAR*         pc            = pcStr;
  for( ; *pc; pcTmpScreen += 2 ) *pcTmpScreen = *pc++;
//  move(wY,wX);
  mvwaddstr(curswin, wY, wX, pcStr);
  wrefresh(curswin);
 }

 /***************************************************************************/
 /* VioUnixSsa                                                              */
 /* ----------------------------------------------------------------------- */
 /* Schreibt einen String mit Attribut an Position x/y durch direkten       */
 /* Bildschirmspeicherzugriff.                                              */
 /***************************************************************************/
 VOID CDECL     VioUnixSsa   ( wX, wY, pcStr, wAttr )
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
//  move(wY, wX);
//  attrset(wAttr);
  mvwaddstr(curswin, wY, wX, pcStr);
  wrefresh(curswin);
 }

 /***************************************************************************/
 /* VioUnixSwa                                                              */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Attribut attr durch direkten Bildschirmspei- */
 /* cherzugriff. Die Zeichen in dem Fenster werden nicht beeinflusst.       */
 /***************************************************************************/
 VOID CDECL     VioUnixSwa   ( wX, wY, wWidth, wHeight, wAttr )
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
   {
    *pbTmpScreen = (BYTE) wAttr;
    wmove(curswin,wHeight,i);
    wattrset(curswin, wAttr);
   }
  wstandend(curswin);
  wrefresh(curswin);
 }

 /***************************************************************************/
 /* VioUnixSwz                                                              */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Zeichen ch durch direkten Bildschirmspei-    */
 /* cherzugriff. Die Attribute in dem Fenster werden nicht beeinflusst.     */
 /***************************************************************************/
 VOID CDECL     VioUnixSwz   ( wX, wY, wWidth, wHeight, bCh )
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
   {
    *pbTmpScreen = (BYTE) bCh;
    wmove(curswin,wHeight,i);
    waddch(curswin, bCh);
   }
  wrefresh(curswin);
 }

 /***************************************************************************/
 /* VioUnixSwza                                                             */
 /* ----------------------------------------------------------------------- */
 /* Fuellt ein Fenster mit dem Zeichen ch und dem Attribut attr durch di-   */
 /* rekten Bildschirmspeicherzugriff.                                       */
 /***************************************************************************/
 VOID CDECL     VioUnixSwza  ( wX, wY, wWidth, wHeight, cCh, wAttr )
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
   {
    *pwTmpScreen++ = wChattr;
    wmove(curswin,wHeight,i);
    wattrset(curswin, wAttr);
    waddch(curswin, cCh);
   }
  wrefresh(curswin);
 }

 /***************************************************************************/
 /* VioUnixSb2w                                                             */
 /* ----------------------------------------------------------------------- */
 /* Muellt einen Pufferinhalt durch direkten Bildschirmspeicherzugriff in   */
 /* ein Fenster.                                                            */
 /***************************************************************************/
 VOID CDECL     VioUnixSb2w  ( wX, wY, wWidth, wHeight, pwBuff )
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
   {
    wmove(curswin,wHeight,i);
    wattrset(curswin, (*pwBuff)&0xFF);
    waddch(curswin, (*pwBuff)>>8);
    *pwTmpScreen++ = *pwBuff++;
   }
  wrefresh(curswin);
 }

 /***************************************************************************/
 /* VioUnixSw2b                                                             */
 /* ----------------------------------------------------------------------- */
 /* Speichert einen Fensterinhalt durch direkten Bildschirmspeicherzugriff  */
 /* in einem Puffer.                                                        */
 /***************************************************************************/
 VOID CDECL     VioUnixSw2b  ( wX, wY, wWidth, wHeight, pwBuff )
 WORD           wX;                              /* Spalte                  */
 WORD           wY;                              /* Zeile                   */
 WORD           wWidth;                          /* Breite                  */
 WORD           wHeight;                         /* Hoehe                   */
 WORD*          pwBuff;                          /* Puffer                  */
 {
//  WORD*         pwTmpScreen  = (WORD*) &VioDescr->pbScreen[ ( wY*VioGetMaxCol()+wX ) << 1 ];
  //WORD          wDelta       = VioGetMaxCol()-wWidth;
  INT           i;
  for( ; wHeight>0; wHeight--/*, pwTmpScreen += wDelta*/ )
   for( i=wWidth; i>0; i-- )
    *pwBuff++ = VioLza(i, wHeight); //*pwTmpScreen++;
 }

 /***************************************************************************/
 /* VioUnixClear                                                            */
 /* ----------------------------------------------------------------------- */
 /* Bildschirm loeschen durch direkten Bildschirmspeicherzugriff.           */
 /***************************************************************************/
 VOID CDECL     VioUnixClear ( void )
 {
  WORD*         pwTmpScreen  = (WORD*) VioDescr->pbScreen;
  WORD          wChAttr      = (WORD)( VH( WEISS, SCHWARZ )<<8 ) | (WORD) ' ';
  INT           i;
  for( i=0; i<VioGetMaxCol()*VioGetMaxRow(); i++ )
   pwTmpScreen[ i ] = wChAttr;
  wclear(curswin);
 }

 VOID CDECL     VioUnixScrUp ( wX1, wY1, wX2, wY2, wAttr )
 WORD           wX1;
 WORD           wY1;
 WORD           wX2;
 WORD           wY2;
 WORD           wAttr;
 {
  ScrScrUp( 1, (BYTE)wX1, (BYTE)wY1, (BYTE)wX2, (BYTE)wY2, (BYTE)wAttr );
 }

 VOID CDECL     VioUnixScrDown( wX1, wY1, wX2, wY2, wAttr )
 WORD           wX1;
 WORD           wY1;
 WORD           wX2;
 WORD           wY2;
 WORD           wAttr;
 {
  ScrScrDown( 1, (BYTE)wX1, (BYTE)wY1, (BYTE)wX2, (BYTE)wY2, (BYTE)wAttr );
 }

#ifdef NEVER
/*    VioSwz(3,3,10,9,'Y');
             fuellt den Bildschirmbereich 3,3;10,9 mit dem Zeichen 'Y' zu constanten Attributen */
void VioUnixSwz (WORD w1, WORD w2, WORD w3, WORD w4, CHAR a)
{
    int lv1, lv2;

    for (lv1=w1; lv1<=w3; lv1++)
        {
             for (lv2=w2; lv2<=w4; lv2++)
                 {
                     bcpuffer [lv1][lv2]= a;
                     move(lv1,lv2);
                     addch(a);
                     VioSz(lv1,lv2,bcpuffer[lv1][lv2]);
                 }
        }
    wrefresh(curswin);

}


/*    VioSwza(2,4,8,9,'X',VH(ROT,SCHWARZ));
             Fuellt den Bildschirm 2,4;8,9 mit Zeichen 'X' und Attribut VH(,)*/
void VioUnixSwza (WORD w1, WORD w2, WORD w3, WORD w4, char a, WORD w5)
{
    int lv1, lv2;

    for (lv1=w1; lv1<=w3; lv1++)
        {
            for (lv2=w2; lv2<=w4; lv2++);
                {
                    bapuffer[lv1][lv2] = w5;
                    bcpuffer[lv1][lv2]=a;
                    wmove(curswin,lv1,lv2);
                    wattrset(curswin,w5);
                    waddch(curswin,a);
                    VioSza(lv1,lv2,bcpuffer[lv1][lv2],bapuffer[lv1][lv2]);
                }
        }
    refresh();

}

/*    VioScrUp(2,4,8,9,VH(ROT,WEISS));
              Scrollt den Bildschirmbereich um eine Zeile nach oben
              die freie Zeile wird mit dem Attribut VH(,) gefuellt */
void VioUnixScrUp(WORD w1, WORD w2, WORD w3, WORD w4, WORD w5)
{
    int lv1, lv2, wh1;
    char wh2;

    for (lv1=w1+1; lv1<w3; lv1++)
        {
            for (lv2=w2; lv2<=w4; lv2++)
                {
                    wh1=bapuffer[lv1][lv2];
                    wh2=bcpuffer[lv1][lv2];
                    bapuffer[lv1-1][lv2]=wh1;
                    bcpuffer[lv1-1][lv2]=wh2;
                    wmove(curswin,lv1-1,lv2);
                    attrset(wh1);
                    addch(wh2);
                    VioSza(lv1-1,lv2,bcpuffer[lv1-1][lv2],bapuffer[lv1-1][lv2]);
                }
        }
    for (lv2=w2; lv2<=w4; lv2++)
        {
            bapuffer[w3][lv2]=w5;
            bcpuffer[w3][lv2]=' ';
            move(w3,lv2);
            attrset(w5);
            addch(' ');
            VioSza(w3,lv2,bcpuffer[w3][lv2],bapuffer[w3][lv2]);
        }
    refresh ();
}

/*    VioScrDown(2,4,8,9,VH(ROT,WEISS));
                scrollt den Bildschirmbereich 2,4;8,9 um eine Zeile nach unten
                die leere obere Zeile wird mit dem Attribut aufgefuellt. */
void VioUnixScrDown(WORD w1, WORD w2, WORD w3, WORD w4, WORD w5)
{
    int lv1, lv2, wh1;
    char wh2;

    for (lv1=w3; lv1<w1; lv1--)
        {
            for (lv2=w2; lv2<=w4; lv2++)
                {
                    wh1=bapuffer[lv1][lv2];
                    wh2=bcpuffer[lv1][lv2];
                    bapuffer[lv1-1][lv2]=wh1;
                    bcpuffer[lv1-1][lv2]=wh2;
                    move(lv1-1,lv2);
                    attrset(wh1);
                    addch(wh2);
                    VioSza(lv1-1,lv2,bcpuffer[lv1-1][lv2],bapuffer[lv1-1][lv2]);
                }
        }
    for (lv2=w2; lv2<=w4; lv2++)
        {
            bapuffer[w1][lv2]=w5;
            bcpuffer[w1][lv2]=' ';
            move(1,lv2);
            attrset(w5);
            addch(' ');
            VioSza(w1,lv2,bcpuffer[w1][lv2],bapuffer[w1][lv2]);
        }
    refresh ();
}


/*    VioSw2b(3,2,10,7,pwbuff);
             speichert den Bildschirminhalt 3,2;10,7 in pwbuff */
void VioUnixSw2b (WORD w1, WORD w2, WORD w3, WORD w4, WORD* pwbuff)
{
    int lv1, lv2, lv3, wh1;
    char wh2;

    lv3=1;
    for (lv1=w1; lv1<=w3; lv1++)
        {
            for (lv2=w2; lv2<=w4; lv2++)
                {
                    wh2=bcpuffer[lv1][lv2];
                    wh1=bapuffer[lv1][lv2];
                    pwbuff[lv3]=wh1;
                    lv3=lv3+1;
                    pwbuff[lv3]=wh2;
                    lv3=lv3+1;
                }
        }
}


/*     VioSb2w(3,2,10,7,pwbuff);
              stellt den in pwbuff gespeicherten Inhalt in Bild 3,2;10,7 dar */
void VioUnixSb2w (WORD w1, WORD w2, WORD w3, WORD w4, WORD* pwbuff)
{
    int lv1, lv2, lv3, wh1;
    char wh2;

    lv3=1;
    for (lv1=w1; lv1<=w3; lv1++)
        {
            for (lv2=w2; lv2<=w4; lv2++)
                {
                    wh1=pwbuff[lv3];
                    lv3=lv3+1;
                    wh2=pwbuff[lv3];
                    lv3=lv3+1;
                    bcpuffer[lv1][lv2]=wh1;
                    bapuffer[lv1][lv2]=wh2;
                    move(lv1,lv2);
                    attrset(wh2);
                    addch(wh1);
                    VioSza(lv1,lv2,bcpuffer[lv1][lv2],bapuffer[lv1][lv2]);
                }
        }
    refresh();
}


#endif

#ifdef _TEST_UNIX_

#include "defs/Colordef.h"
#include <curses.h>
extern WINDOW* curswin;
WORD stack[2000];

int main()
{
  INT i;
  VioInit(VIO_NONE);
//  VioBackground();

//  for( i=0; i<20; i++ ) VioSz(0,i,'A'+i);

//  for( i=0; i<20; i++ ) VioSza(2,i,'A'+i, COLOR_BLUE);

  for( i=1; i<64; i++ ) VioSza(i,1, i, COLOR_PAIR(COLOR_GREEN));
  for( i=64; i<128; i++ ) VioSz(i-64,2, i); //, COLOR_PAIR(COLOR_RED));
  for( i=128; i<192; i++ ) VioSza(i-128,3, i-128, COLOR_PAIR(COLOR_YELLOW));
  for( i=192; i<256; i++ ) VioSz(i-192,4, i);

  while( !wgetch(curswin) )
   ;

  VioUnixSw2b( 12, 12, VioGetMaxCol()-4, VioGetMaxRow()-2, stack );
  VioUnixSwza( 12, 12, VioGetMaxCol()-4, VioGetMaxRow()-2, '!', KOBALT );

  while( !wgetch(curswin) )
   ;

  VioUnixSb2w( 12, 12, VioGetMaxCol()-4, VioGetMaxRow()-2, stack );
//  VioSs(5, 0, "VioSs");
//  VioSs(5, 2, "VioSsa", COLOR_RED);

  while( !wgetch(curswin) )
   ;
  VioDone();
  return 0;
}

#endif

