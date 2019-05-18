#include			"hilevel/tlst.h"
#include			<ncurses.h> 
#include			<QStringList> 
#include			<QDebug>

namespace Hilevel
{
	TLst::TLst(TVio& vio, Modes mode)
	: m_Vio(vio)
	, m_Win(0)
	, m_Mode(mode)
	, m_Sort(None)
	, m_Start(0)
	, m_End(0)
	, m_Current(0)
	, m_Column(0)
	, m_MaxCol(0)
	, m_MaxWidth(0)
	{
	}

	TLst::~TLst()
	{
		qDeleteAll(m_Entries);
		if( m_Win )
			delete m_Win;
	}

	void TLst::append(const QString& str, const QVariant& data)
	{
		TLstEntry* entry = new TLstEntry(str, data);
		m_Entries.append(entry);
		m_MaxWidth = qMax(m_MaxWidth, str.length());
	}

	int TLst::findEntry(const QString& str)
	{
		int count = getCount();
		for(int i=0; i<count; i++)  {
			if( m_Entries[i]->m_Str.contains(str) )
				return i;
		}
		return -1;
	}

	int TLst::findData(const QVariant& data)
	{
		int count = getCount();
		for(int i=0; i<count; i++)  {
			if( m_Entries[i]->m_Data==data )
				return i;
		}
		return -1;
	}

	void TLst::draw(int x, int y, int width, int height, const QString& title, const QString& status)
	{
		m_Vio.status(status, TColors::LstStatusLine, TColors::LstStatusInvers);
		if( !m_Win ) {
			m_Win = new TWin(m_Vio, x, y, width, height, "TLst");
			m_Win->cursor(TWin::CurOff);						// Cursor abschalten
			m_Win->setBackground(TColors::LstText);
			m_Win->setFrame(TWin::FrameSingle, TColors::LstFrame);
			m_Win->setTitle(title, TWin::TitleOZ, TColors::LstTitle);
			m_MaxCol = m_Win->getMaxCol()-1;
		}
		if( m_Start+m_Current>=getCount() ) {
			m_Start = 0;
		}
		drawDown();
	}

	int TLst::show(int x, int y, int width, int height, const QString& title, const QString& status, KeyCodes exits)
	{
		draw(x, y, width, height, title, status);
		int ret;
		bool fertig = false;
		while( !fertig ) {
//			TVio::debug(QString("TLst::show: start=%1, end=%2, current=%3, maxrow=%4, count=%5").arg(m_Start).arg(m_End).arg(m_Current).arg(m_Win->getMaxRow()).arg(getCount()));
			if( m_Mode!=Info )
				drawLine(m_Current, m_Start+m_Current, true);
			ret = getch();
			if( exits.contains(ret) )
				return ret;
			switch(ret)
			{
			case KEY_UP:
				// Versuche, die aktuelle Position um eins zu vermindern. Wenn der Balken schon auf 0 steht, muß m_Start
				// angepaßt werden
//				TVio::debug(QString("TLst::show [key_up]: start=%1, end=%2, current=%3, maxrow=%4, count=%5").arg(m_End).arg(m_Start).arg(m_Current).arg(m_Win->getMaxRow()).arg(getCount()));
				if( m_Mode==Info || m_Current==0 ) {
					// Balken steht auf 0. Wenn Start auch 0 ist, sind wir am Anfang
					if( m_Start==0 ) {
						TVio::beep();
					} else {
						// Wir haben noch Platz nach oben, also Start verschieben
						if( m_Mode!=Info )
							drawLine(m_Current, m_Start+m_Current, false);
						m_Start--;
						drawDown();
					}
					break;
				}
				// Standard-Fall, innerhalb des Fenster den Scrollbalken um eins nach oben verschieben
				if( m_Mode!=Info )
					drawLine(m_Current, m_Start+m_Current, false);
				m_Current--;
				break;
			case KEY_DOWN:
				// Versuche, die aktuelle Position um eins zu erhöhen. Wenn der Balken schon in der untersten Reihe steht,
				// muß m_Start angepaßt werden 
//				TVio::debug(QString("TLst::show [key_down]: start=%1, end=%2, current=%3, maxrow=%4, count=%5").arg(m_Start).arg(m_End).arg(m_Current).arg(m_Win->getMaxRow()).arg(getCount()));
				if( m_Mode==Info || m_Current>=m_Win->getMaxRow()-1 || m_Start+m_Current>=getCount()-1 ) {
					// Balken steht schon auf dem letzten Element der Liste
//					TVio::debug(QString("TLst::show [key_down]: bottom reached"));
					if( m_End==getCount()-1 ) {
						TVio::beep();
					} else {
//						TVio::debug(QString("TLst::show [key_down]: but we can scroll"));
						// Wir haben noch Platz nach unten, also Start verschieben
						if( m_Mode!=Info )
							drawLine(m_Current, m_Start+m_Current, false);
						m_Start++;
						drawDown();
					}
					break;
				}
				// Standard-Fall, innerhalb des Fenster den Scrollbalken um eins nach unten verschieben
				if( m_Mode!=Info )
					drawLine(m_Current, m_Start+m_Current, false);
				m_Current++;
				break;
			case KEY_LEFT:
				if( m_Column>0 ) {
					m_Column--;
					drawDown();
				}
				break;
			case KEY_RIGHT:
				if( m_Column<=m_MaxWidth-m_MaxCol ) {
					m_Column++;
					drawDown();
				}
				break;
			case KEY_HOME:
				// Versuche, auf das erste Element der Liste zu springen.
//				TVio::debug(QString("TLst::show [key_home]: start=%1, end=%2, current=%3, maxrow=%4, count=%5").arg(m_Start).arg(m_End).arg(m_Current).arg(m_Win->getMaxRow()).arg(getCount()));
				if( m_Start==0 && m_Current==0 ) {
					// Balken steht schon auf dem ersten Element der Liste
					TVio::beep();
					break;
				}
				// Standard-Fall, ganz nach oben im Fenster, m_Start ist erstes Element
				if( m_Mode!=Info )
					drawLine(m_Current, m_Start+m_Current, false);
				m_Current = 0;
				m_Start = 0;
				drawDown();
				break;
			case KEY_END:
				// Versuche, auf das letzte Element der Liste zu springen.
//				TVio::debug(QString("TLst::show [key_end]: start=%1, end=%2, current=%3, maxrow=%4, count=%5").arg(m_Start).arg(m_End).arg(m_Current).arg(m_Win->getMaxRow()).arg(getCount()));
				if( m_End==getCount()-1 && m_Start+m_Current==getCount()-1 ) {
					// Balken steht schon auf dem letzten Element der Liste
					TVio::beep();
					break;
				}
				// Standard-Fall, ganz nach unten im Fenster, m_End ist letztes Element
				if( m_Mode!=Info )
					drawLine(m_Current, m_Start+m_Current, false);
				m_End = getCount()-1;
				drawUp(true);
				break;
			case KEY_PPAGE:
				// Versuche, eine Seite höher zu springen. Das letzte Element ist das alte erste Element.
//				TVio::debug(QString("TLst::show [key_ppage]: start=%1, end=%2, current=%3, maxrow=%4, count=%5").arg(m_Start).arg(m_End).arg(m_Current).arg(m_Win->getMaxRow()).arg(getCount()));
				if( m_Start+m_Current<m_Win->getMaxCol()-1 ) {
					TVio::beep();
					break;
				}
				m_End = m_Start;
				drawUp(false);
				break;
			case KEY_NPAGE:
				// Versuche, eine Seite tiefer zu springen. Das erste Element ist das alte letzte Element.
//				TVio::debug(QString("TLst::show [key_npage]: start=%1, end=%2, current=%3, maxrow=%4, count=%5").arg(m_Start).arg(m_End).arg(m_Current).arg(m_Win->getMaxRow()).arg(getCount()));
				if( m_End==getCount()-1 ) {
					// Balken steht schon auf dem letzten Element der Liste
					TVio::beep();
					break;
				}
				if( m_Mode!=Info )
					drawLine(m_Current, m_Start+m_Current, false);
				m_Start = m_End;
				drawDown();
				break;
			case 'q':
			case KEY_ESC:
			case KEY_F(10):
			case KEY_RETURN:
				fertig = true;
				break;
			}
		}
		return ret;
	}

	int TLst::center(const QString& _title, const QString& status, KeyCodes exits)
	{
//	TVio::debug(QString("TLst::center, title=%1, status=%2").arg(_title).arg(status));
		QString title = _title;
		if( title.length()>m_Vio.getMaxCol()-10 )
			title = title.left(m_Vio.getMaxCol()-10);
		int width = /*qMin*/(title.length(), m_MaxWidth+4>m_Vio.getMaxCol() ? m_Vio.getMaxCol()-4 : m_MaxWidth+4);
		int height = getCount()+2>m_Vio.getMaxRow() ? m_Vio.getMaxRow()-4 : getCount()+2;
//	TVio::debug(QString("TLst::center, width=%1, height=%2, maxcol=%3, maxrow=%4").arg(width).arg(height).arg(m_Vio.getMaxCol()).arg(m_Vio.getMaxRow()));
		return show(m_Vio.centerCol(width), m_Vio.centerRow(height), width, height, title, status, exits);
	}

	void TLst::drawLine(int line, int element, bool selected)
	{
		int col = selected ? TColors::LstInvers : TColors::LstText;
		m_Win->ssa(1, line, m_Entries[element]->m_Str.mid(m_Column, m_MaxCol-1).leftJustified(m_MaxCol-1), col);
		if( selected )
			m_Win->update();
	}

	void TLst::drawUp(bool current)
	{
		m_Win->clear();
		int count = getCount();
		int row = count>m_Win->getMaxRow()-1 ? m_Win->getMaxRow()-1 : count-1;
		if( current )
			m_Current = row;
		int idx = m_End;
		for( ; idx>=0; idx--) {
			if( row<0 )
				break;
			drawLine(row--, idx);
		}
		m_Win->update();
		m_Start = idx+1;
		if( m_Start+m_Current>=count )
			m_Current = 0;
//	TVio::debug(QString("TLst::drawUp, count=%1, start=%2, end=%3, current=%4").arg(count).arg(m_Start).arg(m_End).arg(m_Current));
		if( m_End!=count-1 )
			m_Win->sz(m_MaxCol-5, m_Win->getMaxRow(), ACS_DARROW);
		if( m_Start )
			m_Win->sz(m_MaxCol-4, m_Win->getMaxRow(), ACS_UARROW);
	}
	
	void TLst::drawDown()
	{
		m_Win->clear();
		int row = 0;
		int idx = m_Start;
		int count = getCount();
		for( ; idx<count; idx++) {
			if( row>=m_Win->getMaxRow() )
				break;
			drawLine(row++, idx);
		}
		m_Win->update();
		m_End = idx-1;
		if( m_Start+m_Current>=count ) {
//			TVio::debug(QString("TLst::drawDown, adjusting current"));
			m_Current = row-1;
		}
		if( m_End!=count-1 )
			m_Win->sz(m_MaxCol-5, m_Win->getMaxRow(), ACS_DARROW);
		if( m_Start )
			m_Win->sz(m_MaxCol-4, m_Win->getMaxRow(), ACS_UARROW);
//	TVio::debug(QString("TLst::drawDown, count=%1, start=%2, end=%3, current=%4").arg(count).arg(m_Start).arg(m_End).arg(m_Current));
	}
}

#if 0
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
  WinSz( wWidth-5, wHeight-2, ( boNext ) ? 0x19 : '�' );
  WinSz( wWidth-4, wHeight-2, ( pos->Prev!=NULL ) ? 0x18 : '�' );
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

#endif
