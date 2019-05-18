 #include       <HILEVEL/EVENT.H>
 #include       <HILEVEL/VIO.H>
 #include       <HILEVEL/EDITWIN.H>
 #include       <HILEVEL/PALETTE.H>
 #include       <BASICS/MEMALLOC.H>
 #include       <BASICS/DISK.H>
 #include       <DEFS/ERRORDEF.H>
 #include       <DEFS/KEYDEFS.H>
 #include       <DEFS/COLORDEF.H>
 #include       <string.h>

 #define        __FUNC__     ERR_ED_INIT
 SEdit* CDECL   EdInit       ( iMaxLen, lMaxCount )
 INT            iMaxLen;
 LONG           lMaxCount;
 {
  SEdit*        edit         = MemAlloc( sizeof( SEdit ) );
  Assert( edit!=NULL, ERR_MEM_ALLOC );
  edit->lstStart       = DLstInit( sizeof( CHAR* ) );
  edit->info.iMaxLen   = (iMaxLen<=0 ) ? 255 : iMaxLen;
  edit->info.lMaxCount = (lMaxCount<=0L ) ? 0L : lMaxCount;
  edit->keys.iSave     = T_F2;
  edit->keys.iLoad     = T_F3;
  edit->keys.iPrint    = T_F5;
  edit->pcBuff         = MemAlloc( edit->info.iMaxLen+1 );
  edit->search.pcBuff  = MemAlloc( edit->info.iMaxLen+1 );
  Assert( (edit->pcBuff!=NULL)&&(edit->search.pcBuff!=NULL), ERR_MEM_ALLOC );
  return( edit );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_ED_DONE
 VOID   CDECL   EdDone       ( edit )
 SEdit*         edit;
 {
  Assert( edit!=NULL, ERR_PTR );
  if( edit->win!=NULL ) WinEntfernen( edit->win );
  DLstDone( edit->lstStart );
  MemFree( edit->pcAblage, strlen( edit->pcAblage ) );
  MemFree( edit->pcBuff, edit->info.iMaxLen+1 );
  MemFree( edit->search.pcBuff, edit->info.iMaxLen+1 );
  MemFree( edit, sizeof( SEdit ) );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_ED_LOAD
 INT    CDECL   EdLoad       ( edit, pcFile )
 SEdit*         edit;
 CHAR*          pcFile;
 {
  SFile*        fh;
  CHAR*         cp;
  Assert( (edit!=NULL)&&(pcFile!=NULL), ERR_PTR );
  DLstDone( edit->lstStart );
  edit->lstStart = DLstInit( sizeof( CHAR* ) );
  fh = DskFileOpen( pcFile, "rt" );
  if( fh==NULL ) return( ERR_DISK_OPEN );
  while( !DskFileEof( fh ) )
  {
   if( fgets( edit->pcBuff, edit->info.iMaxLen, fh ) == NULL ) break;
   edit->pcBuff[strlen(edit->pcBuff)-1] = 0;
   cp = MemAlloc( strlen(edit->pcBuff) );
   Assert( cp!=NULL, ERR_MEM_ALLOC )
   strncpy( cp, edit->pcBuff, edit->info.iMaxLen );
   DLstInsert( edit->lstStart, cp, FALSE );
  }
  DskFileClose( fh );
  return( ERR_NONE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_ED_SAVE
 INT    CDECL   EdSave       ( edit, pcFile )
 SEdit*         edit;
 CHAR*          pcFile;
 {
  SFile*        fh;
  SDLstEntry*   ent;
  Assert( (edit!=NULL)&&(pcFile!=NULL), ERR_PTR );
  fh = DskFileOpen( pcFile, "w+t" );
  if( fh==NULL ) return( ERR_DISK_OPEN );
  DLstHome( edit->lstStart );
  ent = DLstGetData( edit->lstStart );
  while( ent!=NULL )
  {
   if( fputs( ent->Data, fh ) == NULL ) break;
   if( !DLstNext( edit->lstStart ) ) break;
   ent = DLstGetData( edit->lstStart );
  }
  DskFileClose( fh );
  return( ERR_NONE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_ED_PRINT
 INT    CDECL   EdPrint         PARAM(( SEdit*, INT ));
 #undef         __FUNC__
 #define        __FUNC__     ERR_ED_HANDLE
 INT    CDECL   EdHandle     ( edit, wX, wY, wWidth, wHeight, pcTitle, pcStatus, piExit, help )
 SEdit*         edit;
 WORD           wX;
 WORD           wY;
 WORD           wWidth;
 WORD           wHeight;
 CHAR*          pcTitle;
 CHAR*          pcStatus;
 INT*           piExit;
 FEdHelp        help;
 {
  INT           iKey;
  INT           iRet;
  INT           i;
  LONG          lLine;
  INT           iPos;
  BOOL          boFertig     = FALSE;
  Assert( edit!=NULL, ERR_PTR );
  if( edit->win==NULL )
  {
   edit->win= WinEinrichten( wX, wY, wWidth, wHeight );
   WinSetTitel( edit->win, pcTitle, WIN_TITEL_OZ );
   WinSetAttrib( edit->win, EdGetPal( ED_PAL_TEXT ), EdGetPal( ED_PAL_FRAME ), EdGetPal( ED_PAL_TITLE ) );
  }
  WinAktivieren( edit->win );
  WinCls();
  iPos        = edit->cursor.iPos;
  lLine       = edit->cursor.lLine;
  VioStatus( (pcStatus!=NULL)?pcStatus:"", VH( SCHWARZ, WEISS ), VH( ROT, WEISS ) );
  while( !boFertig )
  {
   WinSetCursorPos( iPos, lLine );
   iKey = EvGetKey();
   if( piExit!=NULL ) for( i=0; piExit[i]!=0; i++ ) if( piExit[i]==iKey ) { boFertig = TRUE; break; }
   if( !boFertig ) switch( iKey )
   {
    case T_F1:
         if( help!=NULL ) help();
         WinAktivieren( edit->win );
         VioStatus( pcStatus, VH( ROT, WEISS ), VH( SCHWARZ, WEISS ) );
         break;
    case T_ESC:
         boFertig = TRUE;
         break;
    case T_HOME:
         iPos = 0;
         break;
    case T_END:
         iPos = strlen( edit->pcBuff );
         break;
    case T_C_HOME:
         iPos  = 0;
         lLine = 0L;
         break;
    case MOU_MOVED:
         break;
    case T_LEFT:
         if( iPos>0 ) iPos--;
         break;
    case T_RIGHT:
         if( iPos<strlen(edit->pcBuff) ) iPos++;
         break;
    case T_DEL:
         for( i=iPos; i<strlen(edit->pcBuff)-1; i++ ) edit->pcBuff[i] = edit->pcBuff[i+1];
         edit->pcBuff[i] = 0;
         WinSz( i, lLine, ' ' );
         WinSs( 0, lLine, edit->pcBuff );
         break;
    case T_BACKSPACE:
         if( iPos==0 ) break;
         for( i=--iPos; i<strlen(edit->pcBuff)-1; i++ ) edit->pcBuff[i] = edit->pcBuff[i+1];
         edit->pcBuff[i] = 0;
         WinSz( i, lLine, ' ' );
         WinSs( 0, lLine, edit->pcBuff );
         break;
    default:
         edit->pcBuff[iPos] = iKey;
         WinSz( iPos++, lLine, iKey );
   }
  }
  return( iKey );
 }
 #undef         __FUNC__

 #ifdef         _TEST_EDITWIN_

 VOID           main         ( void )
 {
  SEdit*        edit;
  VioInit( VIO_NONE );
  VioBackground();
  EvInit();
  edit = EdInit( -1, 0L );
  EdHandle( edit, 1, 1, VioGetMaxCol()-2, VioGetMaxRow()-4, " Edit ", " Edit it!", NULL, NULL );
  EdDone( edit );
  EvDone();
  VioDone();
 }

 #endif
