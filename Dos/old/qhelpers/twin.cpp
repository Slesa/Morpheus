#include			"hilevel/twin.h"
#include			<ncurses.h> 
#include			<QDebug>

static TWinList		g_Wins;

namespace Hilevel
{
	TWin::TWin(TVio& vio, int x, int y, int width, int height, const char* name)
	: m_Vio(vio)
	, m_Win(0)
	, m_Sub(0)
	, m_Frame(FrameNone)
	, m_FrameCol(TColors::MsgFrame)
	, m_TitlePos(TitleOZ)
	, m_TitleCol(TColors::MsgTitle)
	{
		setObjectName(name);
		if( x<1 ) x = 1;
		if( y<1 ) y = 1;
		if( x+width>vio.getMaxCol()-1 ) width = vio.getMaxCol()-1;
		if( y+height>vio.getMaxRow()-1 ) height = vio.getMaxRow()-1;
		m_Win = newwin(height+1, width+1, y-1, x-1);
		m_Sub = subwin(m_Win, height, width, y, x);
		showFrame();
	}
	
	TWin::~TWin()
	{
		if( m_Sub )
			delwin(m_Sub);
		if( m_Win )
			delwin(m_Win);
		hide();
	}
/*
	TWin* TWin::getCurrent()
	{
		return m_Current;
	}
*/
	int TWin::getX()
	{
		return m_Sub->_begx;
	}
	
	int TWin::getY()
	{
		return m_Sub->_begy;
	}
	
	int TWin::getMaxCol()
	{
		return m_Sub->_maxx;
	}
	
	int TWin::getMaxRow()
	{
		return m_Sub->_maxy;
	}

	void TWin::setFrame(FrameType frame, int col)
	{
		m_Frame = frame;
		m_FrameCol = col;
		showFrame();
		showTitle();
	}

	void TWin::setTitle(const QString& title, TitlePos pos, int col)
	{
		m_Title = title;
		m_TitlePos = pos;
		m_TitleCol = col;
		showFrame();
		showTitle();
	}

	bool TWin::isVisible()
	{
		bool ret = g_Wins.contains(this);
		TVio::debug(QString("TWin::isVisible %1: %2").arg(objectName()).arg(ret));
		return ret;
	}

	void TWin::show()
	{
		TVio::debug(QString("TWin::show, showing %1").arg(objectName()));
		g_Wins.append(this);
		update();
//		showWins();
	}

	void TWin::hide()
	{
		TVio::debug(QString("TWin::hide, hiding %1").arg(objectName()));
		::touchwin(stdscr);
		::refresh();
		g_Wins.removeOne(this);
		showWins();
/*
		if( m_Parent && m_Parent->m_Win ) {
//			TVio::debug("TWin::hide, touching parent");
			::touchwin(m_Parent->m_Win);
			::wrefresh(m_Parent->m_Win);
		} else {
//			TVio::debug("TWin::hide, touching screen");
			::touchwin(stdscr);
			::refresh();
		}
		m_Hidden = true;
*/
	}

	void TWin::setBackground(int col)
	{
		::wbkgd(m_Win, m_Vio.getColors().getUser(col));
		::wbkgd(m_Sub, m_Vio.getColors().getUser(col));
	}
	
	void TWin::update()
	{
		TVio::debug(QString("TWin::update, updating %1").arg(objectName()));
		::touchwin(m_Win);
		::wrefresh(m_Win);
		::touchwin(m_Sub);
		::wrefresh(m_Sub);
	}

	void TWin::clear()
	{
		::wclear(m_Sub);
		showFrame();
	}

	void TWin::sa(int x, int y, int col)
	{
	}

	void TWin::sz(int x, int y, char ch)
	{
		mvwaddch(m_Sub, y, x, ch);
	}
	
	void TWin::sza(int x, int y, char ch, int col)
	{
		wmove(m_Sub, y, x);
		wattrset(m_Sub, m_Vio.getColors().getUser(col));
		waddch(m_Sub, ch);
		wattroff(m_Sub, m_Vio.getColors().getUser(col));
	}

	void TWin::ss(int x, int y, const QString& str)
	{
		mvwaddstr(m_Sub, y, x, str.toLocal8Bit());
	}

	void TWin::ssa(int x, int y, const QString& str, int col)
	{
		wmove(m_Sub, y, x);
		wattrset(m_Sub, m_Vio.getColors().getUser(col));
		waddstr(m_Sub, str.toLocal8Bit());
		wattroff(m_Sub, m_Vio.getColors().getUser(col));
	}

	void TWin::print(const QString& str)
	{
//		wattrset(m_Sub, m_Win->);
		waddstr(m_Sub, str.toLocal8Bit());
	}

	void TWin::cursor(Cursors mode)
	{
		curs_set(mode);
	}
 
	void TWin::setCursorPos(int x, int y)
	{
		wmove(m_Sub, y, x);
	}
		
	void TWin::getCursorPos(int& x, int& y)
	{
		getyx(m_Sub, y, x);
	}

	void TWin::showWins()
	{
		foreach(TWin* win, g_Wins)
			win->update();
	}

	void TWin::showFrame(bool refresh)
	{
		wattrset(m_Win, m_Vio.getColors().getUser(m_FrameCol));
		box(m_Win, 0, 0);
		wattroff(m_Win, m_Vio.getColors().getUser(m_FrameCol));
		if( m_Title.isEmpty() )
			showTitle(false);
		if( refresh )
			wrefresh(m_Win);
	}
	
	void TWin::showTitle(bool refresh)
	{
		int spalte = 0; 
		int zeile = m_TitlePos&1 ? m_Win->_maxy : 0;
		switch( m_TitlePos )
		{
		default:
		case TitleOL:
		case TitleUL:
			break;
		case TitleOR:
		case TitleUR:
			spalte = m_Win->_maxx-m_Title.length()-1;
			break;
		case TitleOZ:
		case TitleUZ:
			spalte = (m_Win->_maxx-m_Title.length())/2;
			break;
		}
		// Achtung, sa benutzt m_Sub, nicht m_Win!
		wmove(m_Win, zeile, spalte);
		wattrset(m_Win, m_Vio.getColors().getUser(m_TitleCol));
		waddstr(m_Win, m_Title.toLocal8Bit());
		wattroff(m_Win, m_Vio.getColors().getUser(m_TitleCol));
		if( refresh )
			wrefresh(m_Win);
/* PDCurses
  if( boMouse ) MouShow();
*/
	}

	void TWin::hot(int x, int y, const QString& str, int colnorm, int colinv)
	{
		int col = colnorm;
		int column = x;
		const char* cp = str.toLocal8Bit();
//	debug(QString("TVio::status, row %1 status(%2)").arg(row).arg(cp));
		for(int i=0; cp[i]!=0; i++) {
			if( cp[i]=='~' ) {
				col = (col==colnorm) ? colinv : colnorm;
				continue;
			}
//	debug(QString("TVio::status, cp[%1] = %2").arg(i).arg(cp[i]));
			sza(column++, y, cp[i], col);
		}
		::refresh();
	}
}

#if 0
/****************************************************************************/
/* WIN.C                                                                    */
/* ------------------------------------------------------------------------ */
/* Funktionen zum Unterteilen des Bildschirms in Fenster.                   */
/****************************************************************************/
 #include       "hilevel/Win.h"                  /* Eigene Headerdatei      */
 #include       "basics/MemAlloc.h"              /* Speicherfunktionen      */
 #include       "hilevel/Vio.h"                  /* Bildschirmroutinen      */
 #include       "lolevel/PcMouse.h"              /* Mausroutinen            */
 #include       "defs/Colordef.h"                /* Farbdefinitionen        */
 #include       "defs/Bitdefs.h"                 /* Bitdefinitionen         */
 #include       "defs/Keydefs.h"                 /* Tastendefinitionen      */
 #include       <stdio.h>                        /* NULL-Definition         */
 #include       <stdarg.h>                       /* Variable Argumente benutzen */
 #include       <string.h>                       /* Stringfunktionen        */
 #include       <ctype.h>                        /* Fuer toupper            */

 /* ----------- Interne Daten --------------------------------------------- */
 PRIVATE SWin*  WinCurrent   = NULL;             /* Aktuelles Fenster       */

 /* ----------- Interne Prototypen ---------------------------------------- */
 PRIVATE VOID CDECL WinSave       PARAM(( SWin* ));
 PRIVATE VOID CDECL WinRestore    PARAM(( SWin* ));
 PRIVATE VOID CDECL WinShowShadow PARAM(( SWin* ));

 SWin* CDECL    WinEinrichten( wX, wY, wWidth, wHeight )
 WORD           wX;                              /* Spalte des Fensters     */
 WORD           wY;                              /* Zeile des Fensters      */
 WORD           wWidth;                          /* Breite des Fensters     */
 WORD           wHeight;                         /* Hoehe des Fensters      */
 {
  SWin*         temp         = NULL;             /* Hilfshandle fuers Fenster */
  temp   = (SWin*) MemAlloc( sizeof( SWin ) );   /* Speicher fuer Fenster anfordern */
  if( temp==NULL ) return( NULL );               /* Keiner mehr da?         */
  temp->wPosX     = wX+1;                        /* X-Position merken       */
  temp->wPosY     = wY+1;                        /* Y-Position merken       */
  temp->wWidth    = wWidth-1;                    /* Breite merken           */
  temp->wHeight   = wHeight-1;                   /* Hoehe merken            */
  temp->wCurX     = 0;                           /* Cursorpos X resettieren */
  temp->wCurY     = 0;                           /* Cursorpos Y resettieren */
  temp->wFlags    = 0;
  temp->pcTitle   = NULL;                        /* Standard: Kein Titel    */
  temp->pwBuffer  = NULL;                        /* Vorerst kein Puffer     */
  temp->iTitlePos = WIN_TITEL_OZ;                /* Titelposition: Oben zentriert */
  temp->iFrame    = WIN_FRAME_DOUBLE;            /* Standard: Kein Rahmen   */
  temp->pwBuffer  = MemAlloc( (temp->wWidth+3) * (temp->wHeight+2) * 2 );
  if( VioIsMono() )
  {
   temp->wAttrText   = NORMAL;
   temp->wAttrFrame  = INVERS;
   temp->wAttrTitle  = INVERS;
   temp->wAttrShadow = NORMAL;
  }
  else
  {
   temp->wAttrText   = VH( WEISS, BLAU );
   temp->wAttrFrame  = VH( WEISS, BLAU );
   temp->wAttrTitle  = VH( WEISS, BLAU );
   temp->wAttrShadow = GRAU;
  }
  return( temp );                                /* Fensterdeskriptor zurueckliefern */
 }

 VOID CDECL     WinEntfernen ( win )
 SWin*          win;                             /* Zu loeschendes Fenster  */
 {
  if( win==NULL ) return;                        /* Falsches Handle: Fehler melden */
  if( win->wFlags&WIN_FLG_SAVE )
  {
   WinRestore( win );                             /* Hintergrund restaurieren */
   MemFree( win->pwBuffer, (win->wWidth+3) * (win->wHeight+2) * 2 );  /* Speicher des Puffers freigeben */
  }
  if( win->pcTitle ) MemFree( win->pcTitle, 0L ); /*strlen( win->pcTitle ) );*/
  if( win==WinCurrent ) WinCurrent = NULL;
  MemFree( win, sizeof( SWin ) );                /* Speicher des Fensters freigeben */
 }

 VOID CDECL     WinAktivieren( win )
 SWin*          win;                             /* Zu aktivierendes Fenster */
 {
  if( win==NULL ) return;                        /* Falls ungueltiges handle: raus */
  if( !( win->wFlags&WIN_FLG_SAVE) ) WinSave( win ); /* Fensterinhalt sichern   */
  if( win->wFlags&WIN_FLG_SHADOW ) WinShowShadow( win );/* Evtl Schatten malen     */
  if( win->iFrame!=0 ) WinShowFrame( win );      /* Fensterrahmen malen     */
  if( win->pcTitle!=NULL ) WinShowTitle( win );  /* Evtl Titel anzeigen     */
  WinCurrent = win;                              /* Aktuelles Fenster anpassen */
  if( !( win->wFlags&WIN_FLG_1ST ) ) { WinCls(); win->wFlags|=WIN_FLG_1ST; }
 }

 VOID CDECL     WinVerstecken( win )
 SWin*          win;                             /* Zu versteckendes Fenster */
 {
  if( win==NULL ) return;                        /* Falsches Handle: Fehler melden */
  WinRestore( win );                             /* Hintergrund ueberbuegeln */
 }

 VOID CDECL     WinSchattenEin( win )
 SWin*          win;                             /* Das Fenster will Schatten */
 {
  if( win==NULL ) return;                        /* Falls Handle ungueltig, gibts gar nix */
  win->wFlags |= WIN_FLG_SHADOW;                 /* Schattenflag setzen     */
  if( win==WinCurrent ) WinShowShadow( win );    /* Schatten aktualisieren  */
 }

 VOID CDECL     WinSchattenAus( win )
 SWin*          win;                             /* Das Fenster will Schatten */
 {
  if( win==NULL ) return;                        /* Falls Handle ungueltig, gibts gar nix */
  win->wFlags &= !WIN_FLG_SHADOW;                 /* Schattenflag setzen     */
  if( win==WinCurrent ) WinShowShadow( win );    /* Schatten aktualisieren  */
 }

 VOID CDECL     WinSetRahmentyp( win, iTyp )
 SWin*          win;                             /* Zu aenderndes Fenster   */
 INT            iTyp;                            /* Neuer Rahemntyp         */
 {
  if( ( win==NULL ) || ( iTyp<WIN_FRAME_NONE ) || ( iTyp>WIN_FRAME_THICK ) ) return;
  win->iFrame = iTyp;                            /* Typ merken              */
  if( win==WinCurrent )
  {
   WinShowFrame( win );                          /* Rahmen aktualisieren    */
   if( win->pcTitle ) WinShowTitle( win );
  }
 }

 VOID CDECL     WinSetTitel  ( win, pcStr, iPos )
 SWin*          win;                             /* Zu bearbeitendes Fenster */
 CHAR*          pcStr;                           /* Neuer Titel des Fensters */
 INT            iPos;                            /* Position des Titels     */
 {
  if( ( win==NULL ) || ( iPos<WIN_TITEL_OL ) || ( iPos>WIN_TITEL_UR ) ) return;
  win->iTitlePos = iPos;                         /* Position merken          */
  if( win->pcTitle ) MemFree( win->pcTitle, 0L );
  if( pcStr!=NULL ) win->pcTitle   = strdup( pcStr );
  if( win==WinCurrent )
  {
   WinShowFrame( win );
   WinShowTitle( win );
  }
 }

 VOID CDECL     WinSetAttrib ( win, wText, wFrame, wTitle )
 SWin*          win;
 WORD           wText;
 WORD           wFrame;
 WORD           wTitle;
 {
  if( win==NULL ) return;
  win->wAttrText  = wText;
  win->wAttrFrame = wFrame;
  win->wAttrTitle = wTitle;
  if( win==WinCurrent )
  {
   WinSwa( 0, 0, win->wWidth, win->wHeight, win->wAttrText );
   WinShowFrame( win );
   WinShowTitle( win );
  }
 }

 SWin* CDECL    WinGetAktivPwkb( void )
 {
  return( WinCurrent );
 }

 VOID CDECL     WinSwa       ( wX, wY, wWidth, wHeight, wAttr )
 WORD           wX;                              /* X-Position des Bereiches */
 WORD           wY;                              /* Y-Position des Bereiches */
 WORD           wWidth;                          /* Breite des Bereiches    */
 WORD           wHeight;                         /* Hoehe des Bereiches     */
 WORD           wAttr;                           /* Fuellattribut           */
 {
  BOOL          boMouse      = MouHide();
  if( WinCurrent==NULL )                         /* Falls kein Fenster aktiv */
   VioSwa( wX, wY, wWidth, wHeight, wAttr );     /* Koordinaten relativ zum Bildschirm */
  else                                           /* Falls Fenster aktiv zum Fenster */
   VioSwa( WinCurrent->wPosX+wX, WinCurrent->wPosY+wY, wWidth, wHeight, wAttr );
  if( boMouse ) MouShow();
 }

 VOID CDECL     WinSwz       ( wX, wY, wWidth, wHeight, cCh )
 WORD           wX;                              /* X-Position des Bereiches */
 WORD           wY;                              /* Y-Position des Bereiches */
 WORD           wWidth;                          /* Breite des Bereiches    */
 WORD           wHeight;                         /* Hoehe des Bereiches     */
 CHAR           cCh;                             /* Fuellzeichen            */
 {
  BOOL          boMouse      = MouHide();
  if( WinCurrent==NULL )                         /* Falls kein Fenster aktiv  */
   VioSwz( wX, wY, wWidth, wHeight, cCh );       /* Koordinaten relativ zum Bildschirm */
  else                                           /* Falls Fenster aktiv zum Fenster */
   VioSwz( WinCurrent->wPosX+wX, WinCurrent->wPosY+wY, wWidth, wHeight, cCh );
  if( boMouse ) MouShow();
 }

 VOID CDECL     WinSwza      ( wX, wY, wWidth, wHeight, cCh, wAttr )
 WORD           wX;                              /* X-Position des Bereiches */
 WORD           wY;                              /* Y-Position des Bereiches */
 WORD           wWidth;                          /* Breite des Bereiches    */
 WORD           wHeight;                         /* Hoehe des Bereiches     */
 CHAR           cCh;                             /* Fuellzeichen            */
 WORD           wAttr;                           /* Fuellattribut           */
 {
  BOOL          boMouse      = MouHide();
  if( WinCurrent==NULL )                         /* Falls kein Fenster aktiv */
   VioSwza( wX, wY, wWidth, wHeight, cCh, wAttr ); /* Koordinaten relativ zum Bildschirm */
  else                                           /* Falls Fenster aktiv zum Fenster */
   VioSwza( WinCurrent->wPosX+wX, WinCurrent->wPosY+wY, wWidth, wHeight, cCh, wAttr );
  if( boMouse ) MouShow();
 }

 INT  CDECL     WinPrintf    ( CHAR* pcformat, CPPARGS )
 {
  INT           iRet;
  va_list       argptr;
  CHAR*         pcBuffer;
  CHAR*         pc;
  WORD          wMaxx;
  WORD          wMaxy;
  WORD          wSpalte      = WinCurrent->wCurX+WinCurrent->wPosX;
  WORD          wZeile       = WinCurrent->wCurY+WinCurrent->wPosY;
  BOOL          boMouse      = MouHide();
  if( WinCurrent==NULL )
  {
   wMaxx = VioGetMaxCol()-1;
   wMaxy = VioGetMaxRow()-1;
  }
  else
  {
   wMaxx = WinCurrent->wPosX+WinCurrent->wWidth-1;
   wMaxy = WinCurrent->wPosY+WinCurrent->wHeight-1;
  }
  pcBuffer = MemAlloc( (wMaxx+1)*(wMaxy+1 ) );
  if( pcBuffer==NULL ) return( 0 );
  va_start( argptr, pcformat );
  iRet = vsprintf( pcBuffer, pcformat, argptr );
  pc = pcBuffer;
  if( iRet>0 )
  {
   for( ; *pc; pc++ )
   {
    switch( *pc )
    {
     case '\b':
          wSpalte--;
          break;
     case '\r':
          wSpalte = ( WinCurrent==NULL ) ? 0 : WinCurrent->wPosX;
          break;
     case '\n':
          wSpalte = ( WinCurrent==NULL ) ? 0 : WinCurrent->wPosX;
          if( wZeile==wMaxy ) WinScrollUp();
          else wZeile++;
          break;
     case '\f':
     case '\v': break;
     default:
          VioSz( wSpalte, wZeile, *pc );
          if( ++wSpalte == wMaxx )
          {
           wSpalte = ( WinCurrent==NULL ) ? 0 : WinCurrent->wPosX;
           wZeile++;
           if( wZeile==wMaxy )
           {
            WinScrollUp();
            wZeile--;
           }
          }
    }
   }
  }
  WinCurrent->wCurX = wSpalte - WinCurrent->wPosX;
  WinCurrent->wCurY = wZeile - WinCurrent->wPosY;
  va_end( argptr );
  MemFree( pcBuffer, (wMaxx+1)*(wMaxy+1) );
  if( boMouse ) MouShow();
  return( iRet );
 }

 VOID CDECL     WinScrollUp  ( void )
 {
  BOOL          boMouse      = MouHide();
  if( WinCurrent==NULL )
  {
   ScrScrUp( 0, 0, (BYTE)(VioGetMaxCol()-1), (BYTE)(VioGetMaxRow()-1), 1, NORMAL );
  }
  else
  {
   VioScrUp( WinCurrent->wPosX, WinCurrent->wPosY, WinCurrent->wPosX+WinCurrent->wWidth-2, WinCurrent->wPosY+WinCurrent->wHeight-2, WinCurrent->wAttrText );
  }
  if( boMouse ) MouShow();
 }

 VOID CDECL     WinScrollDown( void )
 {
  BOOL          boMouse      = MouHide();
  if( WinCurrent==NULL )
  {
   ScrScrDown( 0, 0, (BYTE)(VioGetMaxCol()-1), (BYTE)(VioGetMaxRow()-1), 1, NORMAL );
  }
  else
  {
   VioScrDown( WinCurrent->wPosX, WinCurrent->wPosY, WinCurrent->wPosX+WinCurrent->wWidth-2, WinCurrent->wPosY+WinCurrent->wHeight-2, WinCurrent->wAttrText );
  }
  if( boMouse ) MouShow();
 }

 VOID CDECL     WinHot       ( wX, wY, pcText, wNorm, wHot )
 WORD           wX;
 WORD           wY;
 CHAR*          pcText;
 WORD           wNorm;
 WORD           wHot;
 {
  INT           i;
  INT           iPos         = 0;
  WORD          wAttr        = wNorm;
  for( i=0; i<strlen( pcText ); i++ )
   if( pcText[i]=='~' ) wAttr = ( wAttr==wNorm ) ? wHot : wNorm;
   else
    WinSza( wX+iPos++, wY, pcText[i], wAttr );
 }

 VOID CDECL     WinSave      ( win )
 SWin*          win;
 {
  if( ( win==NULL ) || ( win->pwBuffer==NULL ) ) return;
  VioSw2b( win->wPosX-1, win->wPosY-1, win->wWidth+3, win->wHeight+2, win->pwBuffer );
  win->wFlags |= WIN_FLG_SAVE;
 }

 VOID CDECL     WinRestore   ( win )
 SWin*          win;
 {
  BOOL          boMouse      = MouHide();
  if( ( win==NULL ) || ( win->pwBuffer==NULL ) ) /* Falsches Handle/Kein Puffer? */
   return;                                       /* ignorieren              */
  VioSb2w( win->wPosX-1, win->wPosY-1, win->wWidth+3, win->wHeight+2, win->pwBuffer );
  win->wFlags ^= WIN_FLG_SAVE;
  if( boMouse ) MouShow();
 }

 VOID CDECL     WinShowShadow( win )
 SWin*          win;
 {
  INT           i;                               /* Laufzaehler fuer Hoehe und Breite */
  WORD          wStop;                           /* Endpos fuer Schatten    */
  WORD          wStart         = win->wPosX+win->wWidth; /* Startpos fuer Schatten  */
  BOOL          boMouse      = MouHide();
  if( wStart < VioGetMaxCol() )                  /* Falls ueberhaupt sichtbar */
  {
   wStop  = win->wPosY+win->wHeight;             /* Ende des Schattens bestimmen */
   if( VioIsMono() )
   {
    for( i=win->wPosY+1; i<=wStop && i<VioGetMaxRow(); i++ )
    {
     VioSza( wStart, i, '', win->wAttrShadow );
     if( wStart<VioGetMaxCol()-1 )
      VioSza( wStart+1, i, '', win->wAttrShadow );
    }
    wStart = win->wPosY+win->wHeight;
    if( wStart < VioGetMaxRow() )
    {
     wStop  = win->wPosX+win->wWidth;
     for( i=win->wPosX+1; i<wStop && i< VioGetMaxCol(); i++ )
      VioSza( i, wStart, '', win->wAttrShadow );
    }
   }
   else
   {
    wStop  = win->wPosY+win->wHeight;
    for( i=win->wPosY+1; i<=wStop && i<VioGetMaxRow(); i++ )
    {
     VioSa( wStart, i, win->wAttrShadow );
     if( wStart<VioGetMaxCol()-1 )
      VioSa( wStart+1, i, win->wAttrShadow );
    }
    wStart = win->wPosY+win->wHeight;
    if( wStart < VioGetMaxRow() )
    {
     wStop  = win->wPosX+win->wWidth;
     for( i=win->wPosX+1; i<wStop && i< VioGetMaxCol(); i++ )
      VioSa( i, wStart, win->wAttrShadow );
    }
   }
  }
  if( boMouse ) MouShow();
 }

 VOID CDECL     WinShowTitle ( win )
 SWin*          win;
 {
  WORD          wLen;
  WORD          wSpalte;
  WORD          wZeile;
  BOOL          boMouse      = MouHide();
  wLen = strlen( win->pcTitle );
  if( win->iTitlePos < 3 )
   wZeile = win->wPosY - 1;
  else
   wZeile = win->wPosY + win->wHeight - 1;
  switch( win->iTitlePos )
  {
   case WIN_TITEL_OL:
   case WIN_TITEL_UL:
        wSpalte = win->wPosX;
        break;
   case WIN_TITEL_OR:
   case WIN_TITEL_UR:
        wSpalte = win->wPosX+win->wWidth-wLen-1;
        break;
   case WIN_TITEL_OZ:
   case WIN_TITEL_UZ:
        wSpalte = win->wPosX+(win->wWidth-wLen)/2;
        break;
  }
  VioSsa( wSpalte, wZeile, win->pcTitle, win->wAttrTitle );
  if( boMouse ) MouShow();
 }

 VOID CDECL     WinShowFrame ( win )
 SWin*          win;
 {
  INT           i;
  BOOL          boMouse      = MouHide();
  WORD          wBreite      = win->wPosX+win->wWidth-1;
  WORD          wHoehe       = win->wPosY+win->wHeight-1;
  WORD          wAttr        = win->wAttrFrame;
  BYTE          RZ[4][6]     = { { ' ', ' ', ' ', ' ', ' ', ' ' }
                               , { '', '', '', '', '', '' }
                               , { '', '', '', '', '', '' }
                               , { '', '', '', '', '', '' }
                               };
  VioSza( win->wPosX-1, win->wPosY-1, RZ[win->iFrame][0], wAttr );
  VioSza( wBreite, win->wPosY-1, RZ[win->iFrame][1], wAttr );
  VioSza( win->wPosX-1, wHoehe, RZ[win->iFrame][2], wAttr );
  VioSza( wBreite, wHoehe, RZ[win->iFrame][3], wAttr );
  for( i=win->wPosX; i<wBreite; i++ )
  {
   VioSza( i, win->wPosY-1, RZ[win->iFrame][4], wAttr);
   VioSza( i, wHoehe,     RZ[win->iFrame][4], wAttr);
  }
  for( i=win->wPosY; i<wHoehe; i++ )
  {
   VioSza( win->wPosX-1, i, RZ[win->iFrame][5], wAttr);
   VioSza( wBreite,    i, RZ[win->iFrame][5], wAttr);
  }
  if( boMouse ) MouShow();
 }

 INT   CDECL    WinGetHotkey    ( pcText )
 CHAR*          pcText;
 {
  INT           i;
  for( i=0; pcText[i]!=0; i++ )
  {
   if( pcText[i]=='~' )
   {
    if( pcText[i+2]=='~' ) return( toupper( pcText[i+1] ) );
    if( pcText[i+1]=='F' ) switch( pcText[i+2] )
    {
     case '1': switch( pcText[i+3] )
               {
                case '0': return( T_F10 );
                case '1': return( T_F11 );
                case '2': return( T_F12 );
               }
               return( T_F1 );
     case '2': return( T_F2 );
     case '3': return( T_F3 );
     case '4': return( T_F4 );
     case '5': return( T_F5 );
     case '6': return( T_F6 );
     case '7': return( T_F7 );
     case '8': return( T_F8 );
     case '9': return( T_F9 );
    }
   }
  }
  return( -1 );
 }

#ifdef          _TEST_WIN_

 #include       <conio.h>

 VOID           main         ( void )
 {
  CHAR          ch;
  SWin*         win;
  SWin*         win1;
  SWin*         win2;
  SWin*         win3;
  SWin*         win4;
  SWin*         winm;
  SWin*         winold       = NULL;
  BOOL          boFertig     = FALSE;
  VioInit( VIO_132x25 );
  VioBackground();
  VioStatus( " ~[F1]~ Fenstertest ~[F2]~ Test des Fensters", VH( BLAU, WEISS ), VH( ROT, WEISS ) );
  if( ( win1 = WinEinrichten( 1, 1, 14, 4 ) ) == NULL )
  {
   printf( "Failed WinEinrichten\n" );
   return;
  }
  WinCursor( WIN_CUR_HIDE );
  WinSetRahmentyp( win1, WIN_FRAME_SINGLE );
  WinSchattenEin( win1 );
  if( ( win2 = WinEinrichten( VioGetMaxCol()-17, 1, 14, 4 ) ) == NULL )
  {
   printf( "Failed WinEinrichten\n" );
   return;
  }
  WinCursor( WIN_CUR_HIDE );
  WinSetRahmentyp( win2, WIN_FRAME_SINGLE );
  WinSchattenEin( win2 );
  if( ( win3 = WinEinrichten( 1, VioGetMaxRow()-7, 14, 4 ) ) == NULL )
  {
   printf( "Failed WinEinrichten\n" );
   return;
  }
  WinCursor( WIN_CUR_HIDE );
  WinSetRahmentyp( win3, WIN_FRAME_SINGLE );
  WinSchattenEin( win3 );
  if( ( win4 = WinEinrichten( VioGetMaxCol()-17, VioGetMaxRow()-7, 14, 4 ) ) == NULL )
  {
   printf( "Failed WinEinrichten\n" );
   return;
  }
  WinCursor( WIN_CUR_HIDE );
  WinSetRahmentyp( win4, WIN_FRAME_SINGLE );
  WinSchattenEin( win4 );
  if( ( winm = WinEinrichten( VioCenterCol( 20 ), VioCenterRow( 5 ), 20, 5 ) ) == NULL )
  {
   printf( "Failed 2\n" );
   return;
  }
  WinAktivieren( winm );
  WinCls();
  WinSetTitel( winm, " Mittiges Fenster", WIN_TITEL_OZ );
  WinAktivieren( winm );
  WinPrintf( "Videomodus: %d\n", ScrGetMode() );
  WinPrintf( "Spalten...: %d\n", VioGetMaxCol() );
  WinPrintf( "Zeilen....: %d", VioGetMaxRow() );
  while( !boFertig )
  {
   switch( ch = getch() )
   {
    case '1': win = win1; break;
    case '2': win = win2; break;
    case '3': win = win3; break;
    case '4': win = win4; break;
    case 27: boFertig = TRUE;
   }
   if( winold ) WinVerstecken( winold );
   if( boFertig ) break;
   winold = win;
   WinAktivieren( win );
   WinCls();
   WinPrintf( " Dies ist Fenster %c", ch );
  }
  WinPrintf( "Dies ist Fenster Eins\n" );
  WinEntfernen( winm );
  WinEntfernen( win1 );
  WinEntfernen( win2 );
  WinEntfernen( win3 );
  WinEntfernen( win4 );
  VioDone();
 }

#endif
#endif
