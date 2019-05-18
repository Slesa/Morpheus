 #include       "hilevel/LstWin.h"
 #include       "hilevel/Palette.h"
 #include       "hilevel/Vio.h"
 #include       "hilevel/Event.h"
 #include       "hilevel/EvMouse.h"
 #include       "lolevel/PcMouse.h"
 #include       "basics/MemAlloc.h"
 #include       "defs/Errordef.h"
 #include       "defs/Keydefs.h"
 #include       <stdarg.h>
 #include       <stdio.h>
 #include       <string.h>
 #include       <ctype.h>

 /* ----------- Interne Prototypen ---------------------------------------- */
 PRIVATE CHAR*       CDECL stristr      PARAM(( CHAR*, CHAR* ));
 PRIVATE CHAR*       CDECL strichr      PARAM(( CHAR*, CHAR ));
 PRIVATE SLstEntry*  CDECL LstSearchNum PARAM(( SLst*, LONG ));
 PRIVATE SDLstEntry* CDECL LstDrawDn    PARAM(( SDLstEntry*, WORD, WORD, INT, INT* ));
 PRIVATE SDLstEntry* CDECL LstDrawUp    PARAM(( SDLstEntry*, WORD, WORD, INT, INT* ));
 PRIVATE VOID        CDECL LstDrawEl    PARAM((SLstEntry* Entry, INT x, INT y, INT wWidth, INT pos));
 #define LstDrawPos( mode ) if( iMode!=LST_INFO ) WinSwa( 0, lst->iWinPos, wWidth-2, 1, (mode==0) ? LstGetPal( LST_PAL_TEXT ) : LstGetPal( LST_PAL_INVERS ) )
 #define LstSetActual() { DLstSetActual( lst->List, lst->Start ); for( i=0; i<lst->iWinPos; i++ ) DLstNext( lst->List ); }

 PRIVATE VOID CDECL LstDrawEl(SLstEntry* Entry, INT x, INT y, INT wWidth, INT pos)
 {
   INT __count = 0;
   INT i;
   for( i=0; __count<wWidth-3; i++ )
   {
    if( Entry->pcStr[i+pos]==0 )
     break;
    if( (Entry->pcStr[i+pos]=='!')
     && (Entry->pcStr[i+pos+1]!=' ')
     && (Entry->pcStr[i+pos+1]!=0)
      )
    {
     i++; continue;
    }
    WinSz( x+__count, y, Entry->pcStr[i+pos] );
    __count++;
   }
 }
 #ifdef NEVER
 #define LstDrawEl( x, y, pos )                  \
 {                                               \
   INT __count = 0;                              \
   INT i;
   for( i=0; __count<wWidth-3; i++ )                   \
   {                                             \
    if( Entry->pcStr[i+pos]==0 )                 \
     break;                                      \
    if( (Entry->pcStr[i+pos]=='!')               \
     && (Entry->pcStr[i+pos+1]!=' ')             \
     && (Entry->pcStr[i+pos+1]!=0)               \
      )                                          \
    {                                            \
     i++; continue;                              \
    }                                            \
    WinSz( x+__count, y, Entry->pcStr[i+pos] );  \
    __count++;                                   \
   }                                             \
 }
 #endif

 #define        __FUNC__     ERR_LST_INIT
 SLst*  CDECL   LstInit      ( wStrLen )
 WORD           wStrLen;                         /* Maximal-Laenge der Strings */
 {
  SLst*         lst;                             /* Temporaerer Listen-Deskriptor */
  lst = MemAlloc( sizeof( SLst ) );              /* Reserviere Speicher fuer Liste */
  Assert( lst!=NULL, ERR_MEM_ALLOC );            /* Wenn keiner da: Fehler  */
  lst->pcSearch[0] = 0;                          /* Such-String resettieren */
  lst->iStrPos     = 0;
  lst->Less        = NULL;                       /* Keine Sortier-Funktion  */
  lst->OnKeyReleased = NULL;
  lst->Win         = NULL;                       /* Kein Ausgabefenster     */
  lst->wStrLen     = wStrLen;                    /* Maximal-Stringlaenge merken */
  lst->List        = DLstInit( sizeof( SLstEntry ) );
  lst->Start       = NULL;
  lst->End         = NULL;
  lst->boNoShadow  = FALSE;
  return( lst );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_DONE
 VOID CDECL     LstDone      ( lst )
 SLst*          lst;
 {
  SLstEntry*    Entry;
  Assert( lst!=NULL, ERR_PTR );
  DLstHome( lst->List );
  Entry = DLstGetData( lst->List );
  while( Entry!=NULL )
  {
   Entry = DLstGetData( lst->List );
   MemFree( Entry->pcStr, lst->wStrLen );
   if( !DLstNext( lst->List ) ) break;
   Entry = DLstGetData( lst->List );
  }
  if( lst->Win!=NULL ) WinEntfernen( lst->Win );
  DLstDone( lst->List );
//  MemFree( lst, sizeof( SLst ) );
 }
 #undef         __FUNC__

 VOID CDECL     LstShadow    ( lst, on )
 SLst*          lst;
 BOOL           on;
 {
  lst->boNoShadow = !on;
 }

 #define        __FUNC__     ERR_LST_SETSORT
 VOID  CDECL    LstSetSort   ( lst, less )
 SLst*          lst;
 FLstLess       less;
 {
  Assert( lst!=NULL, ERR_PTR );
  lst->Less = less;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_ONKEYRELEASED
 VOID   CDECL   LstSetOnKeyReleased( lst, onkey )
 SLst*          lst;
 FLstOnKeyReleased onkey;
 {
  Assert( lst!=NULL, ERR_PTR );
  lst->OnKeyReleased = onkey;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_GETCOUNT
 ULONG CDECL    LstGetCount  ( lst )
 SLst* lst;
 {
  Assert( lst!=NULL, ERR_PTR );
  return( DLstGetCount( lst->List ) );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_GETNUM
 LONG CDECL     LstGetNum    ( lst )
 SLst*          lst;
 {
  SLstEntry*    Entry;
  Assert( lst!=NULL, ERR_PTR );
  Entry = DLstGetData( lst->List );
  return( (Entry!=NULL) ? Entry->lNum : -1L );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_GOTO
 VOID CDECL     LstGoto      ( lst, lNum )
 SLst*          lst;
 LONG           lNum;
 {
  SLstEntry*    Temp;
  if( lNum==-1 ) return;
  Assert( lst!=NULL, ERR_PTR );
  DLstHome( lst->List );
  Temp = DLstGetData( lst->List );
  while( Temp->lNum!=lNum )
  {
   if( !DLstNext( lst->List ) ) break;
   Temp = DLstGetData( lst->List );
  }
  lst->Start = DLstGetActual( lst->List );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_GETSTR
 CHAR* CDECL    LstGetStr    ( lst, lNum )
 SLst*          lst;
 LONG           lNum;
 {
  SLstEntry*    Entry;
  Assert( lst!=NULL, ERR_PTR );
  Entry = LstSearchNum( lst, lNum );
  return( (Entry!=NULL) ? Entry->pcStr : NULL );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_INSERT
 VOID   CDECL   LstInsert    ( SLst* lst, LONG lNum, CHAR* pcForm, CPPARGS )
 {
  SLstEntry     Entry;
  va_list       args;
  BOOL          boBefore     = FALSE;
  /* ---------- Programmierfehler pruefen --------------------------------- */
  Assert( lst!=NULL, ERR_PTR );
  Assert( lst->wStrLen!=0, ERR_COUNT );
  /* ---------- Daten uebernehmen ----------------------------------------- */
  Entry.lNum = lNum;
  Entry.pcStr = MemAlloc( lst->wStrLen );
  Assert( Entry.pcStr!=NULL, ERR_MEM_ALLOC );
  va_start( args, pcForm );
  vsprintf( Entry.pcStr, pcForm, args );
  va_end( args );
  /* ---------- In Listen einfuegen --------------------------------------- */
  if( (lst->Less!=NULL) && (DLstGetData( lst->List)!=NULL) )
  {
   /* --------- Wenn aktuelles Element nicht kleiner ---------------------- */
   if( lst->Less( &Entry, DLstGetData( lst->List ) ) )
   {
    do
    {
     if( !DLstPrev( lst->List ) ) { break; }
    } while( lst->Less( &Entry, DLstGetData( lst->List ) ) );
   }
   else
   {
    while( !lst->Less( &Entry, DLstGetData( lst->List ) ) )
    {
     if( !DLstNext( lst->List ) ) break;
    }
   }
   boBefore = lst->Less( &Entry, DLstGetData( lst->List ) );
  }
  else
  {
   DLstEnd( lst->List );
  }
#ifdef NEVER
  if( ( (lst->Less!=NULL) && (DLstGetCount( lst->List )!=0L) )
   || ( ( DLstGetCount( lst->List )==1L) ) && ( !lst->Less( &Entry, DLstGetData( lst->List ) ) )
    )
  {
   DLstHome( lst->List );
   while( lst->Less( &Entry, DLstGetData( lst->List ) ) )
    if( !DLstNext( lst->List ) ) break;
  }
  else
  {
   DLstEnd( lst->List );
  }
#endif
  DLstInsert( lst->List, &Entry, boBefore );
  if( lst->Start==NULL ) lst->Start = lst->List->First;
  lst->iCount++;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_CHANGE
 VOID   CDECL   LstChange    ( SLst* lst, LONG lOld, LONG lNum, CHAR* pcForm, CPPARGS )
 {
  SLstEntry*    Entry;
  SLstEntry     Temp;
  va_list       args;
  BOOL          boBefore     = FALSE;
  Assert( lst!=NULL, ERR_PTR );
  Entry = LstSearchNum( lst, lOld );
  Assert( Entry!=NULL, ERR_PARAM );
  if( (lOld==lNum) && (lst->Less==NULL) )
  {
   MemFree( Entry->pcStr, 0L );
   Entry->pcStr = MemAlloc( lst->wStrLen );
   va_start( args, pcForm );
   vsprintf( Entry->pcStr, pcForm, args );
   va_end( args );
   return;
  }
  if( lst->Start->Data==Entry )
  {
   lst->Start = (lst->Start->Prev==NULL) ? lst->Start->Next : lst->Start->Prev;
   lst->End   = (lst->End->Prev==NULL ) ? lst->End->Next : lst->End->Prev;
  }
  DLstDelete( lst->List );
  Temp.pcStr = MemAlloc( lst->wStrLen );
  Assert( Temp.pcStr!=NULL, ERR_MEM_ALLOC );
  va_start( args, pcForm );
  vsprintf( Temp.pcStr, pcForm, args );
  va_end( args );
  Temp.lNum = lNum;
  /* ---------- In Listen einfuegen --------------------------------------- */
  if( (lst->Less!=NULL) && (DLstGetData( lst->List ) != NULL) )
  {
   if( lst->Less( &Temp, DLstGetData( lst->List ) ) )
   do
   {
    if( !DLstPrev( lst->List ) ) { boBefore = TRUE; lst->Start=NULL; break; }
   } while( lst->Less( &Temp, DLstGetData( lst->List ) ) );
   else
   while( lst->Less( &Temp, DLstGetData( lst->List ) ) )
   {
    if( !DLstNext( lst->List ) ) break;
   }
  }
  else
  {
   DLstEnd( lst->List );
  }
  DLstInsert( lst->List, &Temp, boBefore );
#ifdef NEVER
  if( ( (lst->Less!=NULL) && (DLstGetCount( lst->List )!=0L) )
   || ( ( DLstGetCount( lst->List )==1L) ) && ( !lst->Less( &Temp, DLstGetData( lst->List ) ) )
    )
  {
   DLstHome( lst->List );
   while( lst->Less( &Temp, DLstGetData( lst->List ) ) )
    if( !DLstNext( lst->List ) ) break;
  }
  else
  {
   DLstEnd( lst->List );
  }
  DLstInsert( lst->List, &Temp, FALSE );
#endif
  if( lst->Start==NULL ) lst->Start = lst->List->First;
//  lst->Start = lst->List->Actual;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_DELETE
 VOID   CDECL   LstDelete    ( lst, lNum )
 SLst*          lst;
 LONG           lNum;
 {
  SLstEntry*    Entry;
  BOOL          boAnpass1;
  BOOL          boAnpass2;
  LONG          Count;
  Assert( lst!=NULL, ERR_PTR );
  Entry = LstSearchNum( lst, lNum );
  boAnpass1 = (lst->Start==lst->List->First);
  boAnpass2 = (lst->End==lst->List->Last);
  Assert( Entry!=NULL, ERR_PARAM );
  MemFree( Entry->pcStr, lst->wStrLen );
  DLstDelete( lst->List );
  if( boAnpass1 )
    lst->Start = lst->List->First;
  if( boAnpass2 )
  {
    lst->End = lst->List->Last;
    if( lst->Start->Prev )
     lst->Start = lst->Start->Prev;
  }
  Count = DLstGetCount( lst->List );
  if( (lst->iWinPos >= Count) && (lst->iWinPos>0) )
    lst->iWinPos--;
  if( lst->Start==NULL ) WinCls();
  lst->iCount--;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_DRAW
 VOID           LstDraw      ( lst, iMode, wX, wY, wWidth, wHeight, pcTitle, pcStatus )
 SLst*          lst;
 INT            iMode;
 WORD           wX;
 WORD           wY;
 WORD           wWidth;
 WORD           wHeight;
 CHAR*          pcTitle;
 CHAR*          pcStatus;
 {
  INT           i;
  /* ---------- Auf Programmier-Fehler testen ----------------------------- */
  Assert( lst!=NULL, ERR_PTR );
  /* ---------- Bisher noch nicht aufgerufen? ----------------------------- */
  if( lst->Win==NULL )
  {
   /* --------- Listenfenster aufbauen ------------------------------------ */
   lst->Win = WinEinrichten( wX, wY, wWidth, wHeight );
   WinSetAttrib( lst->Win, LstGetPal( LST_PAL_TEXT ), LstGetPal( LST_PAL_FRAME ), LstGetPal( LST_PAL_TITLE ) );
   WinSetRahmentyp( lst->Win, WIN_FRAME_SINGLE );
   if( !lst->boNoShadow )
    WinSchattenEin( lst->Win );
   WinSetTitel( lst->Win, pcTitle, WIN_TITEL_OZ );
   /* --------- Listendaten vorbelegen ------------------------------------ */
   lst->iWinPos  = 0;
   DLstHome( lst->List );
   lst->Start = DLstGetActual( lst->List );
  }
  /* --------- Listenfenster aktivieren ---------------------------------- */
  WinAktivieren( lst->Win );
  WinCursor( WIN_CUR_HIDE );
  VioStatus( pcStatus, LstGetPal( LST_PAL_STATUS ), LstGetPal( LST_PAL_INVSTAT ) );
  MouSetRange( wX+1, wY+1, wX+wWidth-2, wY+wHeight-2 );
  MouSetPos( wX+1, wY+lst->iWinPos+1 );
  WinCls();
  lst->End = LstDrawDn( lst->Start, wWidth, wHeight, lst->iStrPos, NULL );
  LstSetActual();
  LstDrawPos( 1 );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_SHOW
 INT    CDECL   LstShow      ( lst, iMode, wX, wY, wWidth, wHeight, pcTitle, pcStatus, piExit, Help )
 SLst*          lst;
 INT            iMode;
 WORD           wX;
 WORD           wY;
 WORD           wWidth;
 WORD           wHeight;
 CHAR*          pcTitle;
 CHAR*          pcStatus;
 INT*           piExit;
 FLstHelp       Help;
 {
  SLstEntry*    Entry;
  SDLstEntry*   Actual;
  INT           i;
  INT           iRet = 0;
  WORD          wMouX, wMouY, wMouState;
  CHAR          cSearchStr[21];
  INT           iSearchPos   = 0;
  BOOL          boFertig     = FALSE;
  LstDraw(lst,iMode,wX,wY,wWidth,wHeight,pcTitle,pcStatus);
  while( !boFertig )
  {
   LstDrawPos( 1 );
   if( lst->OnKeyReleased!=NULL && iRet!=0 )
    lst->OnKeyReleased(iRet,lst);
   iRet = EvGetKey();
   if( piExit!=NULL ) for( i=0; piExit[i]!=0; i++ ) if( piExit[i]==iRet ) { boFertig = TRUE; break; }
   if( boFertig ) break;
 AGAIN:
   switch( iRet )
   {
    case MOU_RIGHTPRESS:                         /* Rechte Maustaste: F1    */
    case T_F1:                                   /* Vordefiniert: F1 ist Hilfe */
         if( Help!=NULL ) Help();                /* Falls Hilfefunktion existiert: ausfuehren */
         WinAktivieren( lst->Win );              /* Wieder unser Fenster aktiveren */
         break;
    case T_ESC:                                  /* ESC gedrueckt:          */
         boFertig = TRUE;                        /* Wir sind fertig         */
         break;
    case MOU_LEFTPRESS:                          /* Linke Maustaste: RETURN */
         iRet = T_RETURN;
    case T_RETURN:                               /* RET gedrueckt:          */
         boFertig = TRUE;                        /* ebenfalls fertig        */
         break;
    case T_HOME:
         LstDrawPos( 0 );
         DLstHome( lst->List );
         lst->Start   = DLstGetActual( lst->List );
         lst->End     = LstDrawDn( lst->Start, wWidth, wHeight, lst->iStrPos, &i );
         lst->iWinPos = 0;
         break;
    case T_END:
         LstDrawPos( 0 );
         if( lst->Start==NULL ) break;
         if( DLstGetCount( lst->List ) < (LONG)wHeight-2L  )
         {
          lst->iWinPos = (INT) DLstGetCount( lst->List ) - 1;
          break;
         }
         DLstEnd( lst->List );
         lst->End     = DLstGetActual( lst->List );
         lst->Start   = LstDrawUp( lst->End, wWidth, wHeight, lst->iStrPos, &i );
         lst->iWinPos = wHeight-3;
         break;
    case T_LEFT:
         if( lst->iStrPos>0 )
         {
          lst->iStrPos--;
          lst->End = LstDrawDn( lst->Start, wWidth, wHeight, lst->iStrPos, &i );
         }
         break;
    case T_RIGHT:
         if( lst->iStrPos<lst->wStrLen-wWidth )
         {
          lst->iStrPos++;
          lst->End = LstDrawDn( lst->Start, wWidth, wHeight, lst->iStrPos, &i );
         }
         break;
    case T_UP:
         LstDrawPos( 0 );
         if( (iMode!=LST_INFO) && (lst->iWinPos>0) ) { lst->iWinPos--; LstSetActual(); break; }
         if( (lst->Start!=NULL) && (lst->Start->Prev!=NULL) )
         {
          lst->Start = lst->Start->Prev;
          lst->End   = lst->End->Prev;
          WinScrollDown();
          WinSz( wWidth-4, wHeight-2, ( lst->Start->Prev!=NULL ) ? 0x18 : 'Ä' );
          WinSz( wWidth-5, wHeight-2, ( lst->End->Next!=NULL ) ? 0x19 : 'Ä' );
          DLstSetActual( lst->List, lst->Start );
          Entry = DLstGetData( lst->List );
          LstDrawEl( Entry, 1, 0, wWidth, lst->iStrPos);
//          LstDrawEl( 1, 0, lst->iStrPos );
         }
         break;
    case T_DOWN:
         if( lst->Start==NULL ) break;
         LstDrawPos( 0 );
         if( (iMode!=LST_INFO) && (lst->iWinPos<wHeight-3) )
         {
          Actual = DLstGetActual( lst->List );
          if( Actual->Next!=NULL ) lst->iWinPos++;
          LstSetActual();
//          DLstSetActual( lst->List, Actual );
          break;
         }
         if( lst->End->Next!=NULL )
         {
          lst->Start = lst->Start->Next;
          lst->End   = lst->End->Next;
          WinScrollUp();
          WinSz( wWidth-4, wHeight-2, ( lst->Start->Prev!=NULL ) ? 0x18 : 'Ä' );
          WinSz( wWidth-5, wHeight-2, ( lst->End->Next!=NULL ) ? 0x19 : 'Ä' );
          DLstSetActual( lst->List, lst->End );
          Entry = DLstGetData( lst->List );
          LstDrawEl( Entry, 1, wHeight-3, wWidth, lst->iStrPos);
         }
         break;                                  /* es wird nur der Scrollbalken angepasst */
    case T_PGUP:
         LstDrawPos( 0 );
         lst->End   = lst->Start;
         lst->Start = LstDrawUp( lst->End, wWidth, wHeight, lst->iStrPos, &i );
         if( i!=0 )
         {
          if( lst->Start->Prev==NULL )
           lst->End = LstDrawDn( lst->Start, wWidth, wHeight, lst->iStrPos, &i );
          lst->iWinPos = 0;
         }
         break;
    case T_PGDN:
         LstDrawPos( 0 );
         if( DLstGetCount( lst->List ) < (LONG) wHeight-3L ) { iRet = T_END; goto AGAIN; }
         if( lst->Start==NULL ) break;
         lst->Start = lst->End;
         lst->End   = LstDrawDn( lst->Start, wWidth, wHeight, lst->iStrPos, &i );
         if( i!=wHeight-2 )
         {
          if( lst->End->Next==NULL )
           lst->Start = LstDrawUp( lst->End, wWidth, wHeight, lst->iStrPos, &i );
          lst->iWinPos = wHeight-3;
         }
         break;
    case MOU_MOVED:
         LstDrawPos( 0 );
         if( lst->Start==NULL ) break;
         EvMouGetVal( &wMouX, &wMouY, &wMouState );
         if( wMouY < wY ) break;
         wMouY -= wY;
         if( (wMouY==wHeight-2) && (lst->End->Next!=NULL) )
         {
          iRet = T_DOWN;
          goto AGAIN;
         }
         if( (wMouY==1) && (lst->Start->Prev!=NULL) )
         {
          iRet = T_UP;
          goto AGAIN;
         }
         Actual = lst->Start;
         for( i=0; i<wMouY-1; i++ )
          if( (Actual = Actual->Next) == NULL ) break;
         lst->iWinPos = i;
         LstSetActual();
         break;
    case T_BACKSPACE:
         LstDrawPos( 0 );
         iSearchPos = 0;
         DLstHome( lst->List );
         lst->iWinPos = 0;
         lst->Start   = DLstGetActual( lst->List );
         lst->End     = LstDrawDn( lst->Start, wWidth, wHeight, lst->iStrPos, &i );
         break;
    default:                                     /* Irgendeine sonstige Taste */
         if( lst->iCount<=wHeight )
          break;
         if( (iSearchPos==20) || (lst->Start==NULL) ) break;
         if( iSearchPos==0 && iRet==T_SPACE ) break;
         cSearchStr[iSearchPos++] = iRet;
         cSearchStr[iSearchPos]   = 0;
         Actual = DLstGetActual( lst->List );
         Entry = DLstGetData( lst->List );
         while( Entry!=NULL )
         {
          if( stristr( Entry->pcStr, cSearchStr ) != NULL )
          {
           LstDrawPos( 0 );
           lst->Start = DLstGetActual( lst->List );
           lst->End   = LstDrawDn( lst->Start, wWidth, wHeight, lst->iStrPos, &i );
           break;
          }
          if( !DLstNext( lst->List ) ) { Entry=NULL; break; }
          Entry = DLstGetData( lst->List );
         }
         if( Entry==NULL )
         {
          DLstSetActual( lst->List, Actual );
          cSearchStr[--iSearchPos] = 0;
          printf( "%c", 7 );
         }
   }
  }
  LstSetActual();
  return( iRet );
 }
 #undef         __FUNC__

 PRIVATE SLstEntry* CDECL LstSearchNum( lst, lNum )
 SLst*          lst;
 LONG           lNum;
 {
  SLstEntry*    Temp;
  Temp = DLstGetData( lst->List );
  if( (lNum!=-1L) && (Temp->lNum!=lNum) )
  {
   DLstHome( lst->List );
   Temp = DLstGetData( lst->List );
   while( Temp->lNum!=lNum )
   {
    if( !DLstNext( lst->List ) ) { Temp=NULL; break; }
    Temp = DLstGetData( lst->List );
   }
  }
  return( Temp );
 }

 PRIVATE SDLstEntry* CDECL LstDrawDn( start, wWidth, wHeight, iStrPos, piPos )
 SDLstEntry*    start;
 WORD           wWidth;
 WORD           wHeight;
 INT            iStrPos;
 INT*           piPos;
 {
  SDLstEntry*   pos          = start;
  SLstEntry*    Entry;
  INT           p;
//  INT           i;
  BOOL          boPrev       = pos->Prev!=NULL;
  WinCls();
  if( pos==NULL ) return( NULL );
  for( p=0; p<wHeight-2; p++ )
  {
   Entry = pos->Data;
   LstDrawEl( Entry, 1, p, wWidth, iStrPos);
   if( pos->Next==NULL ) break;
   if( p!=wHeight-3 ) pos = pos->Next;
  }
  WinSz( wWidth-5, wHeight-2, ( pos->Next!=NULL ) ? 0x19 : 'Ä' );
  WinSz( wWidth-4, wHeight-2, ( boPrev ) ? 0x18 : 'Ä' );
  if( piPos!=NULL )
   *piPos = p;
  return( pos );
 }

 PRIVATE SDLstEntry* CDECL LstDrawUp( end, wWidth, wHeight, iStrPos, piPos )
 SDLstEntry*    end;
 WORD           wWidth;
 WORD           wHeight;
 INT            iStrPos;
 INT*           piPos;
 {
  SDLstEntry*   pos          = end;
  SLstEntry*    Entry;
  INT           p;
//  INT           i;
  BOOL          boNext       = pos->Next!=NULL;
  WinCls();
  if( pos==NULL ) return( NULL );
  for( p=wHeight-3; p>=0; p-- )
  {
   Entry = pos->Data;
   LstDrawEl( Entry, 1, p, wWidth, iStrPos);
   if( pos->Prev==NULL ) break;
   if( p!=0 ) pos = pos->Prev;
  }
  WinSz( wWidth-5, wHeight-2, ( boNext ) ? 0x19 : 'Ä' );
  WinSz( wWidth-4, wHeight-2, ( pos->Prev!=NULL ) ? 0x18 : 'Ä' );
  *piPos = p;
  return( pos );
 }

 PRIVATE CHAR* CDECL    strichr( st, ch )
 CHAR*         st;
 CHAR          ch;
 {
  CHAR*        cp;
  for( cp=st; *cp!=0; cp++ ) if( toupper(*cp)==toupper(ch) ) return( cp );
  return( NULL );
 }

 PRIVATE CHAR* CDECL    stristr( st1, st2 )
 CHAR*         st1;
 CHAR*         st2;
 {
  INT          i        = strlen( st2 );
  CHAR*        cp;
  cp = strichr( st1, st2[0] );
  while( cp!=NULL )
  {
  #if( !defined UNIX )
   if( memicmp( cp, st2, i ) == 0 )
  #else
   if( strncasecmp(cp, st2, i) == 0 )
  #endif
     return( cp );
   cp = strichr( cp+1, st2[0] );
  }
  return( NULL );
 }

 #define        __FUNC__     ERR_LST_FIRST
 LONG   CDECL   LstFirst     ( lst )
 SLst*          lst;
 {
  SLstEntry*    Entry;
  Assert( lst!=NULL, ERR_PTR );
  DLstHome( lst->List );
  Entry = DLstGetData( lst->List );
  return( (Entry!=NULL) ? Entry->lNum : -1L );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_LST_NEXT
 LONG   CDECL   LstNext      ( lst )
 SLst*          lst;
 {
  SLstEntry*    Entry;
  Assert( lst!=NULL, ERR_PTR );
  if( !DLstNext( lst->List ) ) return( -1L );
  Entry = DLstGetData( lst->List );
  return( (Entry!=NULL) ? Entry->lNum : -1L );
 }
 #undef         __FUNC__

#ifdef          _NEVER_LSTWIN_

 #include       <conio.h>
 #include       <stdlib.h>

 BOOL           Less         ( e1, e2 )
 SLstEntry*     e1;
 SLstEntry*     e2;
 {
  return( atol( e1->pcStr ) >= atol( e2->pcStr ) );
 }

 VOID           main         ( void )
 {
  SLst*         lst;
  INT           iRet;
  LONG          lReal        = 0L;
  LONG          lCount       = 0L;
  BOOL          boEnde       = FALSE;
  INT           iExit[]      = { T_INS, T_DEL, 0 };
//  VioInit( VIO_NONE );
//  directvideo=FALSE;
//  VioInit( VIO_GR72x48x16 );
//  VioInit( VIO_GR32x24x256 );
  VioInit( VIO_80x25 );
  VioBackground();
  EvInit();
  lst = LstInit( 40 );
  LstSetSort( lst, Less );
  while( !boEnde )
  {
   if( lReal==0L )
    iRet = T_INS;
   else
    iRet = LstShow( lst, LST_LIST, VioCenterCol( 20 ), VioCenterRow( 20 ), 20, 20, "Testliste", " ~F1~ Hilfe  ~INS~ Einfg  ~DEL~ Entf", iExit, NULL );
   switch( iRet )
   {
    case T_INS:
         LstInsert( lst, lCount, "%ld) Teststring", lCount++ );
         lReal++;
         break;
    case T_DEL:
         LstDelete( lst, -1L );
         lReal--;
         break;
    case T_RETURN:
         LstChange( lst, LstGetNum( lst ), lCount, "%ld) Teststring", lCount++ );
         break;
    case T_ESC:
         boEnde = TRUE;
         break;
   }
  }
  EvDone();
  VioDone();
 }

#endif

#ifdef          _TEST_LSTWIN_

 #include       <BASICS/DISK.H>

 VOID           main         ( void )
 {
  extern LONG   lMemAllocated;
  INT           n;
  LONG          l;
  SLst*         lst;
  BOOL          boFertig = FALSE;
  INT           Exit[] = { T_DEL, 0 };
  VioInit( VIO_80x25 );
  VioBackground();
  EvInit();
//  for( n=0; n<1000; n++ )
  {
   lst = LstInit( 40 );
   for( l=0L; l<10L; l++ )
   {
    LstInsert( lst, l, "Dies ist Zeile %ld", l );
   }
   while( !boFertig )
   {
    switch( LstShow( lst, LST_LIST, VioCenterCol(40), VioCenterRow(5), 40, 5, " Titel ", " Statuszeile", Exit, NULL ) )
    {
        case T_ESC:
             boFertig = TRUE;
             break;
        case T_DEL:
             LstDelete( lst, LstGetNum(lst) );
             break;
    }
   }
   LstDone( lst );
   if( (lMemAllocated!=0L) && (lMemAllocated!=4096L) ) { printf( "\nSau" ); }
  }
  EvDone();
  VioDone();
 }
#endif

#ifdef          NEVER

 #include       <BASICS/DISK.H>
 #include       <string.h>

 VOID CDECL     Help         ( void );
 BOOL CDECL     Less         ( SLstEntry*, SLstEntry* );

 VOID CDECL     Help         ( void )
 {
  SWin*         win          = WinEinrichten( VioCenterCol( 10 ), VioCenterRow( 10 ), 10, 10 );
  WinAktivieren( win );
  WinCls();
  WinPrintf( "This is the Help" );
  EvGetKey();
  WinEntfernen( win );
 }

 BOOL CDECL     Less         ( E1, E2 )
 SLstEntry*     E1;
 SLstEntry*     E2;
 {
  INT           i;
  INT           i1           = strlen( E1->pcStr );
  INT           i2           = strlen( E1->pcStr );
  INT           iSize        = (i1>i2) ? i2 : i1;
  for( i=0; i<iSize; i++ )
  {
   if( E1->pcStr[i] < E2->pcStr[i] ) return( FALSE );
   if( E1->pcStr[i] > E2->pcStr[i] ) return( TRUE );
  }
  return( i1 < i2 );
 }

 VOID           main         ( void )
 {
  SLst*         lst;
  LONG          lCount       = 0L;
  BOOL          boEnde       = FALSE;
  INT           iEbene       = 0;
  CHAR*         cp;
  INT           i,w;
  SFindT        find;
  BOOL          boFertig;
  CHAR          cPath[129];
  VioInit( VIO_NONE );
  EvInit();
  VioBackground();
  sprintf( cPath, "i:\\*.*" );
  while( !boEnde )
  {
   lst = LstInit( 40 );
   LstSetSort( lst, Less );
   boFertig = DskFindFirst( cPath, DSK_A_DIR, &find );
   while( !boFertig )
   {
    if( find.attrib&DSK_A_DIR )
     LstInsert( lst, lCount, "%-12.12s [DIR]", find.name );
    boFertig = DskFindNext( &find );
   }
   boFertig = DskFindFirst( cPath, DSK_A_NORMAL, &find );
   while( !boFertig )
   {
    LstInsert( lst, lCount, "%-12.12s", find.name );
    boFertig = DskFindNext( &find );
   }
   switch( LstShow( lst, LST_LIST, (iEbene+1), VioCenterRow( 20 ), 20, 20, "Dateien", " ~F1~ Hilfe", NULL, Help ) )
   {
    case T_RETURN:
         cp = LstGetStr( lst, -1L );
         if( (strstr( cp, "[DIR]" ) != NULL ) )
         {
          if( strstr( cp, ".." ) != NULL )
          {
           if( ( cp = strrchr( cPath, '\\' ) ) == NULL ) break;
           while( *(--cp)!='\\' );
           sprintf( cp, "\\*.*" );
           LstDone( lst );
           if( --iEbene==-1 ) boEnde = TRUE;
           break;
          }
          iEbene++;
          w=(LONG) strrchr( cPath, '\\' ) + 1L - (LONG) cPath;
          for( i=0; i<12; i++ ) cPath[w++]=cp[i];
          cPath[w] = 0;
          strcat( cPath, "\\*.*" );
          LstDone( lst );
         }
         break;
    case T_ESC:
         if( ( cp = strrchr( cPath, '\\' ) ) == NULL ) break;
         while( *(--cp)!='\\' );
         sprintf( cp, "\\*.*" );
         LstDone( lst );
         if( --iEbene==-1 ) boEnde = TRUE;
         break;
   }
  }
  EvDone();
  VioDone();
 }

#endif
