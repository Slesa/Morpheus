 #include       <HILEVEL/DLGWIN.H>
 #include       <HILEVEL/PALETTE.H>
 #include       <BASICS/MEMALLOC.H>
 #include       <DEFS/ERRORDEF.H>
 #include       <string.h>

 #define        __FUNC__     ERR_DLG_INIT
 SDlg*  CDECL   DlgInit      ( iCount )
 INT            iCount;                          /* Anzahl Eintraege im Dialog */
 {
  SDlg*         dlg          = MemAlloc( sizeof( SDlg ) );
  Assert( dlg!=NULL, ERR_MEM_ALLOC );
  dlg->Entry     = MemAlloc( sizeof( SDlgEntry ) * iCount );
  Assert( dlg->Entry!=NULL, ERR_MEM_ALLOC );
  dlg->win       = NULL;                         /* Noch keine Ausgabe erfolgt */
  dlg->iEntries  = iCount;                       /* Anzahl Eintraege merken */
  dlg->iNext     = 0;
  dlg->iActual   = -1;
  return( dlg );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_DONE
 VOID CDECL     DlgDone      ( dlg )
 SDlg*          dlg;
 {
  INT           i;
  INT           n;
  Assert( dlg!=NULL, ERR_PTR );
  if( dlg->win!=NULL ) WinEntfernen( dlg->win );
  for( i=0; i<dlg->iEntries; i++ )
  {
   for( n=0; n<dlg->Entry[i].iFields; n++ ) MemFree( dlg->Entry[i].Field[n].pcText, 0 );
   MemFree( dlg->Entry[i].pcText, 0 );
   MemFree( dlg->Entry[i].pcStatus, 0 );
   MemFree( dlg->Entry[i].Field, sizeof( SDlgFld ) * dlg->Entry[i].iFields );
  }
  MemFree( dlg->Entry, sizeof( SDlgEntry ) * dlg->iEntries );
  MemFree( dlg, sizeof( SDlg ) );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_ENTINIT
 INT    CDECL   DlgEntInit   ( dlg, iCount, iType, wX, wY, pcText, help, pcStatus )
 SDlg*          dlg;
 INT            iCount;
 INT            iType;
 WORD           wX;
 WORD           wY;
 CHAR*          pcText;
 FDlgHelp       help;
 CHAR*          pcStatus;
 {
  INT           iEntry       = ++dlg->iActual;
  Assert( ((dlg!=NULL)&&(dlg->Entry!=NULL)), ERR_PTR );
  Assert( iEntry<dlg->iEntries, ERR_COUNT );
  dlg->Entry[iEntry].iFields = iCount;           /* Anzahl Felder merken    */
  if( iCount!=0 )
  {
   dlg->Entry[iEntry].Field = MemAlloc( sizeof( SDlgFld ) * iCount );
   Assert( dlg->Entry[iEntry].Field!=NULL, ERR_MEM_ALLOC );
   dlg->Entry[iEntry].iFields = iCount;           /* Anzahl Felder merken    */
   dlg->Entry[iEntry].iNext   = 0;
   dlg->Entry[iEntry].iActual = 0;
   dlg->Entry[iEntry].wX      = wX;
   dlg->Entry[iEntry].wY      = wY;
   dlg->Entry[iEntry].pcText  = strdup( pcText );
   dlg->Entry[iEntry].pcStatus= strdup( pcStatus );
   dlg->Entry[iEntry].iType   = iType;
   dlg->Entry[iEntry].wFlag   = 0;
   dlg->Entry[iEntry].Help    = help;
   dlg->iActual += 1;
  }
  return( iEntry );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_ENTABLE
 VOID CDECL     DlgEntAble   ( dlg, iEntry, iEn, iVis )
 SDlg*          dlg;
 INT            iEntry;
 INT            iEn;
 INT            iVis;
 {
  Assert( ((dlg!=NULL)&&(dlg->Entry!=NULL)), ERR_PTR );
  Assert( iEntry<dlg->iEntries, ERR_COUNT );
  switch( iEn )
  {
   case TRUE:  dlg->Entry[iEntry].wFlag &= !DLG_DISABLE; break;
   case FALSE: dlg->Entry[iEntry].wFlag |=  DLG_DISABLE; break;
  }
  switch( iVis )
  {
   case TRUE:  dlg->Entry[iEntry].wFlag &= !DLG_HIDDEN; break;
   case FALSE: dlg->Entry[iEntry].wFlag |=  DLG_HIDDEN; break;
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_ADDFIELD
 VOID   CDECL   DlgAddField  ( dlg, wX, wY, pvInfo )
 SDlg*          dlg;
 WORD           wX;
 WORD           wY;
 VOID*          pvInfo;
 {
  INT           iEntry       = dlg->iNext-1;
  INT           iField       = dlg->Entry[iEntry].iNext;
  Assert( ((dlg!=NULL)&&(dlg->Entry!=NULL)), ERR_PTR );
  Assert( iField<dlg->Entry[iEntry].iFields, ERR_COUNT );
  dlg->Entry[iEntry].Field[iField].wX     = wX;
  dlg->Entry[iEntry].Field[iField].wY     = wY;
  dlg->Entry[iEntry].Field[iField].pvInfo = pvInfo;
  dlg->Entry[iEntry].Field[iField].OnInit = NULL;
  dlg->Entry[iEntry].Field[iField].OnExit = NULL;
  dlg->Entry[iEntry].Field[iField].OnKey  = NULL;
  dlg->Entry[iEntry].iNext += 1;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_HANDLE
 INT CDECL      DlgHandle    ( dlg, wX, wY, wW, wH, pcTitle )
 SDlg*          dlg;
 WORD           wX;
 WORD           wY;
 WORD           wW;
 WORD           wH;
 CHAR*          pcTitle;
 {
  INT           iRet;                            /* Rueckgabewert           */
  BOOL          boFertig     = FALSE;            /* Falg, ob fertig         */
  /* ---------- Programmierfehler abfangen -------------------------------- */
  Assert( dlg!=NULL, ERR_PTR );
  /* ---------- Ausgabe-Fenster verwalten --------------------------------- */
  if( dlg->Win==NULL )
  {
   dlg->Win = WinEinrichten( wX, wY, wW, wH );
   WinSetAttrib( dlg->Win, DlgGetPal( DLG_PAL_TEXT ), DlgGetPal( DLG_PAL_FRAME ), DlgGetPal( DLG_PAL_TITLE ) );
   WinSetRahmentyp( dlg->Win, WIN_FRAME_SINGLE );
   WinSchattenEin( dlg->Win );
   WinSetTitel( dlg->Win, pcTitle, WIN_TITEL_OZ );
  }
  WinAktivieren( dlg->Win );
  WinCursor( WIN_CUR_HIDE );
  WinCls();
  while( !boFertig )
  {
  }
 }
 #undef         __FUNC__


#ifdef          _TEST_DLGWIN_

 #include       <HILEVEL/EVENT.H>
 #include       <HILEVEL/VIO.H>

 VOID           main         ( void )
 {
  SDlg*         dlg;
  VioInit( VIO_NONE );
  VioBackground();
  EvInit();
  dlg = DlgInit( 4 );
  DlgInitEntry( dlg, 0, DLG_STATIC, 1, 1, "Statischer Text", NULL, NULL );
  DlgInitEntry( dlg, 1, DLG_FRAME, 1, 1, "Statischer Rahmen", NULL, NULL );
  DlgInitEntry( dlg, 2, DLG_BITMAP, 1, 1, "BITMAP.BMP", NULL, NULL );
// VOID   CDECL   DlgInitEntry ( dlg, iCount, iType, wX, wY, pcText, help, pcStatus )
  DlgDone( dlg );
  EvDone();
  VioDone();
 }

#endif
