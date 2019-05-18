#include			"hilevel/tmsg.h"
#include			<ncurses.h> 
#include			<QStringList> 
#include			<QDebug>

namespace Hilevel
{
	TMsg::TMsg(TVio& vio)
	: m_Vio(vio)
	, m_Win(0)
	{
	}

	TMsg::~TMsg()
	{
		if( m_Win )
			delete m_Win;
	}
	
	int TMsg::show(int x, int y, const QString& text, Modes mode, const QString& status)
	{
		// Wenn mode=MELDUNG_DAUER2, dann einfach Fenster schließen und raus
		if( mode==Dauer2 ) {
			TVio::debug(QString("TMsg::show (%1), removing dauer-window").arg(text));
			if( m_Win )
				delete m_Win;
			return 0;
		}
		m_Vio.status(status, TColors::MsgStatusLine, TColors::MsgStatusLine);

		int width;
		int height;
		getWidhtHeight(text, width, height);
		m_Win = new TWin(m_Vio, x, y, width+6, height+4, "TMsg");
		m_Win->cursor(TWin::CurOff);						// Cursor abschalten
		m_Win->setBackground(TColors::MsgText);
		m_Win->setFrame(TWin::FrameSingle, TColors::MsgFrame);

		m_Win->print(text);
		m_Win->update();
		
		int ret = 0;
		// Die Modes handlen
		switch( mode )
		{
		case Dauer2:
		default:
			break;
		case Info:
			m_Win->setTitle(tr(" <Taste> "), TWin::TitleUR, TColors::MsgTitle);
			do {
				ret = getch();
				if( !ret )
					continue;
			} while( ret==ERR );
			break;
		case YesNo:
		case YesNo2:
			if( mode==YesNo )
				m_Win->setTitle(tr(" <Return>=JA <F10>=NEIN "), TWin::TitleUR, TColors::MsgTitle);
			do {
				ret = getch();
				if( ret==KEY_CANCEL || ret==KEY_F(10) )
					break;
			} while( ret!='\n' );
			break;
		case F1F2:
			do {
				ret = getch();
				if( ret==KEY_F(2) )
					break;
			} while( ret!=KEY_F(1) );
			break;
		case Dauer:
			return 0;										// Ohne Fenster zu schließen wieder raus
		}
		if( mode!=Dauer ) {
			TVio::debug(QString("TMsg::show (%1), removing my window").arg(text));
			delete m_Win;
		}
		return 0;
	}

 	int TMsg::center(const QString& text, Modes mode, const QString& status)
 	{
 		int width;
 		int height;
 		getWidhtHeight(text, width, height);
 		return show(m_Vio.centerCol(width), m_Vio.centerRow(height), text, mode, status);
 	}

	void TMsg::getWidhtHeight(const QString& text, int& width, int& height)
	{
		QStringList lines = text.split("\n");
		width = 0;
		foreach(QString line, lines) {
			if( line.length()>width )
				width = line.length();
		}
		height = lines.count();
		if( width>m_Vio.getMaxCol() )
			width = m_Vio.getMaxCol()-4;
		if( height>m_Vio.getMaxRow() )
			height = m_Vio.getMaxRow()-2;
	}
}

#if 0
 /***************************************************************************/
 /* WinMsg                                                                  */
 /* ----------------------------------------------------------------------- */
 /* Stellt die uebergebenen Informationen in einem Fenster dar und wartet   */
 /* auf die Abbruchbedingung.                                               */
 /***************************************************************************/
 INT CDECL      WinMsg       ( wX, wY, pcText, iMode )
 WORD           wX;
 WORD           wY;
 CHAR*          pcText;
 INT            iMode;
 {
  INT           iMaxlen      = 0;
  INT           iZeilenzahl  = 1;
  INT           iTaste;
  INT           iLen         = 0;
  CHAR*         cp;
#ifdef IPC
  CHAR          cBuf[100];
#endif
  WinCursor( FALSE );                            /* Cursor abschalten       */
  MsgSave = WinGetAktivPwkb();                   /* Aktuelles Fenster merken */
  /* Ermittle l�ngste Zeile                                                 */
/*  win = WinEinrichten( VioCenterX( iMaxlen+6 ), VioCenterY( iZeilenzahl+4 ), iMaxlen+6, iZeilenzahl+4 ); */
  MsgWin = WinEinrichten( wX, wY, iMaxlen+6, iZeilenzahl+4 );
  if( MsgWin==NULL ) return( 0 );
  WinSchattenEin( MsgWin );
  WinSetRahmentyp( MsgWin, WIN_FRAME_SINGLE );
  WinSetAttrib( MsgWin, MsgGetPal( MSG_PAL_TEXT ), MsgGetPal( MSG_PAL_FRAME ), MsgGetPal( MSG_PAL_TITLE ) );
  WinAktivieren( MsgWin );
  WinCls();
  pcText = cp;
  WinPrintf( "\n%s", pcText );
  /*
  while( *sCp )
  {
   WinPrintf( "%c", *sCp++ );
   if( *sCp=='\n' )
   {
    WinPrintf( "\n  " );
   }
  }
  */
  WinCursor( FALSE );
  return( iTaste );
 }
#endif
