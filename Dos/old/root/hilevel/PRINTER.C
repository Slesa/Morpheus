 #include       <HILEVEL/PRINTER.H>
 #include       <LOLEVEL/PORTSER.H>
 #include       <LOLEVEL/PORTPAR.H>
 #include       <BASICS/MEMALLOC.H>
 #include       <BASICS/DISK.H>
 #include       <DEFS/ERRORDEF.H>
 #include       <string.h>
 #include       <bios.h>

 #define        __FUNC__     ERR_PRN_INIT
 VOID  CDECL    PrnInit      ( prn, iDev, iNum )
 SPrn*          prn;
 INT            iDev;
 INT            iNum;
 {
  Assert( prn!=NULL, ERR_PTR );
  Assert( (iDev>=PRN_NUL) && (iDev<=PRN_FILE), ERR_COUNT );
  MemFill( prn, 0, sizeof( SPrn ) );
  prn->iDevice = iDev;
  prn->iNum    = iNum;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_DONE
 VOID  CDECL    PrnDone      ( prn )
 SPrn*          prn;
 {
  INT           i;
  Assert( prn!=NULL, ERR_PTR );
  for( i=0; i<4; i++ ) PrnSetHdr( prn, i, NULL );
  PrnSetTranslate( prn, 0, NULL );
  for( i=0; i<PRN_SEQ_MAX; i++ ) PrnSetSeq( prn, i, 0, NULL );
  if( prn->fh!=NULL ) DskFileClose( prn->fh );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_PRINTINIT
 BOOL  CDECL    PrnPrintInit ( prn )
 SPrn*          prn;
 {
  INT           iLen;
  CHAR*         cp;
  Assert( prn!=NULL, ERR_PTR );
  prn->iPage = 0;
  prn->iLine = 0;
  if( prn->wFlag&PRN_TOFILE )
  {
   if( prn->pcSeq[0][0]!=0 )
    prn->fh = DskFileOpen( prn->pcSeq[0], "a+t" );
   else
    prn->fh = DskFileOpen( "DEFAULT.TXT", "a+t" );
   Assert( prn->fh!=NULL, ERR_DISK_OPEN );
  }
  cp = PrnGetSeq( prn, PRN_SEQ_INIT, &iLen );
  if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
  if( !PrnGuest( prn ) ) return( FALSE );
  if( !PrnPrintHdr( prn ) ) return( FALSE );
  return( TRUE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_GUEST
 BOOL  CDECL    PrnGuest     ( prn )
 SPrn*          prn;
 {
  INT           iLen;
  CHAR*         cp;
  if( !(prn->wFlag&PRN_GUEST) ) return( TRUE );
  cp = PrnGetSeq( prn, PRN_SEQ_LOAD, &iLen );
  if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
  return( TRUE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_PRINTCH
 BOOL  CDECL    PrnPrintCh   ( prn, ch )
 SPrn*          prn;
 CHAR           ch;
 {
  INT           iState;
  BOOL          boError;
  if( prn->iDevice==PRN_NUL ) return( TRUE );
  if( !(prn->wFlag&PRN_TOFILE) ) ch = PrnGetTranslate( prn, ch );
  switch( prn->iDevice )
  {
   case PRN_SERIAL:
//        iState = _bios_serialcom(_COM_SEND,prn->iNum,ch);
//        boError = iState & BIT15;
        SerPutc( prn->iNum, ch );
        boError = (SerGetState( prn->iNum ) & BIT15);
        break;
   case PRN_PARALLEL:
        ParPutc( prn->iNum, ch );
        iState  = ParGetState( prn->iNum );
        boError = !(iState&BIT4);
        if( !boError ) boError = iState&BIT5;
        break;
   case PRN_IMC:
//        ImcPutc( prn->iNum, ch );
        break;
   case PRN_FILE:
        Assert( prn->fh!=NULL, ERR_DISK_OPEN );
        boError = ( fputc( ch, prn->fh ) == EOF );
        break;
   default:
        SystemError( __FILE__, __FUNC__, __LINE__, ERR_COUNT );
  }
  if( (prn->iDelay!=0) && (ch=='\n') )
   //UtlPause( UTL_TICK, 8L )
   ;
  return( !boError );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_PRINTBUF
 BOOL  CDECL    PrnPrintBuf  ( prn, iLen, pcBuff )
 SPrn*          prn;
 INT            iLen;
 CHAR*          pcBuff;
 {
  INT           i;
  Assert( prn!=NULL, ERR_PTR );
  if( (pcBuff==NULL) || (iLen==NULL) ) return( TRUE );
  for( i=0; i<iLen; i++ )
   if( !PrnPrintCh( prn, pcBuff[i] ) ) return( FALSE );
  return( TRUE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_PRINTHDR
 BOOL  CDECL    PrnPrintHdr  ( prn )
 SPrn*          prn;
 {
  INT           i;
  INT           iAnz;
  INT           iLen;
  CHAR*         cp;
  Assert( prn!=NULL, ERR_PTR );
  iAnz = (prn->iPage==0) ? prn->iPgFstHeight : prn->iPgNxtHeight;
  if( prn->wFlag&PRN_LOAD )
  {
   cp = PrnGetSeq( prn, PRN_SEQ_LOAD, &iLen );
   PrnPrintBuf( prn, iLen, cp );
   prn->iLine += iAnz;
  }
  else
  {
   for( i=0; i<iAnz; i++ )
   {
    cp = PrnGetSeq( prn, PRN_SEQ_LF, &iLen );
    PrnPrintBuf( prn, iLen, cp );
    prn->iLine++;
   }
  }
  for(i=0;i<4;i++)
  {
   cp = NULL;
   if( prn->pcHdr[i][0]!='\0' )
   {
    cp=strstr( prn->pcHdr[i], "$$$");
    if( cp!=NULL ) sprintf( cp, "%03d", prn->iPage );
    if( !PrnPrintBuf( prn, strlen( prn->pcHdr[i] ), prn->pcHdr[i] ) ) return( FALSE );
    if( cp!=NULL ) sprintf( cp, "$$$" );
    cp = PrnGetSeq( prn, PRN_SEQ_LF, &iLen );
    if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
   }
  }
  if( ++prn->iPage>999 ) prn->iPage=1;
  return( TRUE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_PRINTPART
 BOOL  CDECL    PrnPrintPart ( prn, pcBuff )
 SPrn*          prn;
 CHAR*          pcBuff;
 {
  INT           i;
  INT           iCmd;
  INT           iLen;
  CHAR*         cp;
  #define       PRN_COL      BIT0
  #define       PRN_INV      BIT1
  #define       PRN_BLD      BIT2
  #define       PRN_GRF      BIT3
  WORD          wFlag        = 0;
  Assert( prn!=NULL, ERR_PTR );
  for( i=0; pcBuff[i]!=0; i++ )
  {
   switch( pcBuff[i] )
   {
    case PRN_CMD:
         switch( pcBuff[++i] )
         {
          case PRN_CMD_INIT:    iCmd = PRN_SEQ_INIT;    break;
          case PRN_CMD_DONE:    iCmd = PRN_SEQ_DONE;    break;
          case PRN_CMD_LF:      iCmd = PRN_SEQ_LF;      prn->iLine++;      break;
          case PRN_CMD_PF:      iCmd = PRN_SEQ_PF;      prn->iPage++;      break;
          case PRN_CMD_CUT:     iCmd = PRN_SEQ_CUT;     break;
          case PRN_CMD_PERF:    iCmd = PRN_SEQ_PERF;    break;
          case PRN_CMD_COLON:   iCmd = PRN_SEQ_COLON;   wFlag |= PRN_COL;  break;
          case PRN_CMD_COLOFF:  iCmd = PRN_SEQ_COLOFF;  wFlag &= !PRN_COL; break;
          case PRN_CMD_INVON:   iCmd = PRN_SEQ_INVON;   wFlag |= PRN_INV;  break;
          case PRN_CMD_INVOFF:  iCmd = PRN_SEQ_INVOFF;  wFlag &= !PRN_INV; break;
          case PRN_CMD_BOLDON:  iCmd = PRN_SEQ_BOLDON;  wFlag |= PRN_BLD;  break;
          case PRN_CMD_BOLDOFF: iCmd = PRN_SEQ_BOLDOFF; wFlag &= !PRN_BLD; break;
          case PRN_CMD_GRON:    iCmd = PRN_SEQ_GRON;    wFlag |= PRN_GRF;  break;
          case PRN_CMD_GROFF:   iCmd = PRN_SEQ_GROFF;   wFlag &= !PRN_GRF; break;
          default:              iCmd = -1;
	 }
         if( iCmd!=-1 )
         {
          cp = PrnGetSeq( prn, iCmd, &iLen );
          if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
         }
         if( (prn->wFlag&PRN_GUEST) && (iCmd==PRN_SEQ_CUT) )
         {
          cp = PrnGetSeq( prn, PRN_SEQ_CUT, &iLen );
          if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
          if( !PrnGuest( prn ) ) return( FALSE );
          prn->iLine = 0;
          if( !PrnPrintHdr( prn ) ) return( FALSE );
         }
         break;
    case '\n': // CR auch bercksichtigen
         cp = PrnGetSeq( prn, PRN_SEQ_LF, &iLen );
         if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
         prn->iLine++;
         break;
    default:
         if( prn->wFlag&PRN_SINGLE )
         {
          if( wFlag&PRN_BLD )
          {
           cp = PrnGetSeq( prn, PRN_SEQ_BOLDON, &iLen );
           if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
          }
          if( wFlag&PRN_INV )
          {
           cp = PrnGetSeq( prn, PRN_SEQ_INVON, &iLen );
           if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
          }
          if( wFlag&PRN_COL )
          {
           cp = PrnGetSeq( prn, PRN_SEQ_COLON, &iLen );
           if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
          }
          if( wFlag&PRN_GRF )
          {
           cp = PrnGetSeq( prn, PRN_SEQ_GRON, &iLen );
           if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
          }
         }
         if( !PrnPrintCh( prn, pcBuff[i] ) ) return( FALSE );
   }
   if( (PrnGetPageLen( prn )!=0 ) && (prn->iLine>PrnGetPageLen( prn )) )
   {
    cp = PrnGetSeq( prn, PRN_SEQ_CUT, &iLen );
    if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
    if( !PrnGuest( prn ) ) return( FALSE );
    prn->iLine=0;
    if( !PrnPrintHdr( prn ) ) return( FALSE );
   }
  }
  if( prn->iDelay!=0 )
   //UtlPause(UTL_TICKS,6)
   ;
  return( TRUE );
  #undef        PRN_COL
  #undef        PRN_INV
  #undef        PRN_BLD
  #undef        PRN_GRF
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_PRINTEND
 BOOL  CDECL    PrnPrintEnd  ( prn )
 SPrn*          prn;
 {
  INT           iLen;
  CHAR*         cp;
  Assert( prn!=NULL, ERR_PTR );
  cp = PrnGetSeq( prn, PRN_SEQ_DONE, &iLen );
  if( !PrnPrintBuf( prn, iLen, cp ) ) return( FALSE );
  if( prn->wFlag&PRN_TOFILE )
  {
   DskFileClose( prn->fh );
   prn->fh=NULL;
  }
  prn->iPage = 0;
  return( TRUE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_GETHDR
 CHAR* CDECL    PrnGetHdr    ( prn, iHdr )
 SPrn*          prn;
 INT            iHdr;
 {
  Assert( prn!=NULL, ERR_PTR );
  Assert( (iHdr>=0) && (iHdr<=3), ERR_COUNT );
  return( prn->pcHdr[iHdr] );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_GETFTR
 CHAR* CDECL    PrnGetFtr    ( prn, iFtr )
 SPrn*          prn;
 INT            iFtr;
 {
  Assert( prn!=NULL, ERR_PTR );
  Assert( (iFtr>=0) && (iFtr<=3), ERR_COUNT );
  return( prn->pcFtr[iFtr] );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_SETHDR
 VOID  CDECL    PrnSetHdr    ( prn, iHdr, pcHdr )
 SPrn*          prn;
 INT            iHdr;
 CHAR*          pcHdr;
 {
  Assert( prn!=NULL, ERR_PTR );
  Assert( (iHdr>=0) && (iHdr<=3), ERR_COUNT );
  if( prn->pcHdr[iHdr] ) MemFree( prn->pcHdr[iHdr], 0L );
  if( pcHdr!=NULL )
  {
   prn->pcHdr[iHdr] = strdup( pcHdr );
   Assert( prn->pcHdr[iHdr]!=NULL, ERR_MEM_ALLOC );
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_SETFTR
 VOID  CDECL    PrnSetFtr    ( prn, iFtr, pcFtr )
 SPrn*          prn;
 INT            iFtr;
 CHAR*          pcFtr;
 {
  Assert( prn!=NULL, ERR_PTR );
  Assert( (iFtr>=0) && (iFtr<=3), ERR_COUNT );
  if( prn->pcFtr[iFtr] ) MemFree( prn->pcFtr[iFtr], 0L );
  if( pcFtr!=NULL )
  {
   prn->pcFtr[iFtr] = strdup( pcFtr );
   Assert( prn->pcFtr[iFtr]!=NULL, ERR_MEM_ALLOC );
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_GETSEQ
 CHAR* CDECL    PrnGetSeq    ( prn, iSeq, piLen )
 SPrn*          prn;
 INT            iSeq;
 INT*           piLen;
 {
  Assert( prn!=NULL, ERR_PTR );
  Assert( (iSeq>=0)&&(iSeq<PRN_SEQ_MAX), ERR_COUNT );
  if( prn->pcSeq[iSeq]==NULL )
  {
   *piLen = 0;
   return( NULL );
  }
  *piLen = prn->pcSeq[iSeq][0];
  return( &prn->pcSeq[iSeq][1] );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_SETSEQ
 VOID  CDECL    PrnSetSeq    ( prn, iSeq, iLen, pcSeq )
 SPrn*          prn;
 INT            iSeq;
 INT            iLen;
 CHAR*          pcSeq;
 {
  Assert( prn!=NULL, ERR_PTR );
  Assert( (iSeq>=0)&&(iSeq<PRN_SEQ_MAX), ERR_COUNT );
  if( prn->pcSeq[iSeq]!=NULL ) MemFree( prn->pcSeq[iSeq], prn->pcSeq[iSeq][0] );
  if( pcSeq!=NULL )
  {
   prn->pcSeq[iSeq] = MemAlloc( iLen );
   Assert( prn->pcSeq!=NULL, ERR_MEM_ALLOC );
   prn->pcSeq[iSeq][0] = iLen;
   MemCopy( &prn->pcSeq[iSeq][1], pcSeq, iLen );
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_GETPAGELEN
 INT   CDECL    PrnGetPageLen( prn )
 SPrn*          prn;
 {
  Assert( prn!=NULL, ERR_PTR );
  if( prn->iPage==0 ) return( prn->iPgFstHeight );
  return( prn->iPgNxtHeight );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_SETPAGELEN
 VOID  CDECL    PrnSetPageLen( prn, iFst, iNxt )
 SPrn*          prn;
 INT            iFst;
 INT            iNxt;
 {
  Assert( prn!=NULL, ERR_PTR );
  prn->iPgFstHeight = iFst;
  prn->iPgNxtHeight = iNxt;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_GETTRANSLAT
 CHAR  CDECL    PrnGetTranslate( prn, ch )
 SPrn*          prn;
 CHAR           ch;
 {
  INT           i;
  Assert( prn!=NULL, ERR_PTR );
  if( prn->pwTranslate!=NULL )
  for( i=1; i<prn->pwTranslate[0]; i++ )
  {
   if( (prn->pwTranslate[i]&0xFF) == ch ) return( (prn->pwTranslate[i]>>8)&0xFF );
  }
  return( ch );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_SETTRANSLAT
 VOID  CDECL    PrnSetTranslate( prn, iCount, pwTrans )
 SPrn*          prn;
 INT            iCount;
 WORD*          pwTrans;
 {
  Assert( prn!=NULL, ERR_PTR );
  if( prn->pwTranslate!=NULL ) MemFree( prn->pwTranslate, (prn->pwTranslate[0]+1)*sizeof( WORD ) );
  if( iCount!=0 )
  {
   prn->pwTranslate = MemAlloc( sizeof( WORD ) * (iCount+1) );
   Assert( prn->pwTranslate!=NULL, ERR_MEM_ALLOC );
   prn->pwTranslate[0] = (WORD) iCount;
   MemCopy( &prn->pwTranslate[1], pwTrans, iCount*sizeof( WORD ) );
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_LOAD
 VOID  CDECL    PrnLoad      ( prn, pcFile )
 SPrn*          prn;
 CHAR*          pcFile;
 {
  SFile*        fh           = DskFileOpen( pcFile, "rb" );
  Assert( prn!=NULL, ERR_PTR );
  Assert( fh!=NULL, ERR_DISK_OPEN );
  Assert( DskFileRead( prn, sizeof( SPrn ), 1, fh ), ERR_DISK_READ );
  DskFileClose( fh );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_PRN_SAVE
 VOID  CDECL    PrnSave      ( prn, pcFile )
 SPrn*          prn;
 CHAR*          pcFile;
 {
  SFile*        fh           = DskFileOpen( pcFile, "w+b" );
  Assert( prn!=NULL, ERR_PTR );
  Assert( fh!=NULL, ERR_DISK_OPEN );
  Assert( DskFileWrite( prn, sizeof( SPrn ), 1, fh ), ERR_DISK_WRITE );
  DskFileClose( fh );
 }
 #undef         __FUNC__

#ifdef          _TEST_PRN_

 VOID           main         ( void )
 {
  SPrn          prn;
  CHAR          cCut[]       = { 0x1B, 0x6D };
  CHAR          cLf[]        = { 0x0A };
  CHAR          cBOn[]       = { 0x1B, 0x21, 0x20 };
  CHAR          cBOff[]      = { 0x1B, 0x21, 0x00 };
  SerInit( SER_COM2, 9600L, 8, SER_PAR_NONE, 1 );
  PrnInit( &prn, PRN_SERIAL, SER_COM2 );
  prn.iDelay = 10;
  PrnSetHdr( &prn, 0, "Erste  Zeile, Seite $$$" );
  PrnSetHdr( &prn, 1, "Zweite Zeile, Seite $$$" );
  PrnSetHdr( &prn, 2, "Dritte Zeile, Seite $$$" );
  PrnSetHdr( &prn, 3, "Vierte Zeile, Seite $$$" );
  PrnSetSeq( &prn, PRN_SEQ_CUT, 2, cCut );
  PrnSetSeq( &prn, PRN_SEQ_LF, 1, cLf );
  PrnSetSeq( &prn, PRN_SEQ_BOLDON, 3, cBOn );
  PrnSetSeq( &prn, PRN_SEQ_BOLDOFF, 3, cBOff );
  if( !PrnPrintInit( &prn ) ) printf( "Fehler: Init\n" );
  if( !PrnPrintPart( &prn, "\n\n!BEin Testdruck!b\n"
                           "-------------------\n"
                           "Nur zur Information\n\n\n\n\n!Y" ) ) printf( "Fehler: Part\n" );
  if( !PrnPrintEnd( &prn ) ) printf( "Fehler: Ende\n" );
  PrnDone( &prn );
 }
#endif
