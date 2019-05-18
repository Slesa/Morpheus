#include			"hilevel/tmnu.h"
#include			<ncurses.h> 

namespace Hilevel
{
	TMnuEntry::TMnuEntry()
	: m_X(0)
	, m_Y(0)
	, m_Hotkey(0)
	{
	}

	TMnuEntry::TMnuEntry(int x, int y, const QString& text, int hotkey, const QString& status)
	: m_X(x)
	, m_Y(y)
	, m_Hotkey(hotkey)
	, m_Text(text)
	, m_Status(status)
	{
	}

	TMnu::TMnu(TVio& vio)
	: m_Vio(vio)
	, m_Current(0)
	, m_MaxWidth(0)
	, m_MaxHeight(0)
	, m_Win(0)
	{
	}
	
	TMnu::~TMnu()
	{
		qDeleteAll(m_Entries);
		if( m_Win )
			delete m_Win;
	}

	void TMnu::add(TMnuEntry* entry)
	{
		m_MaxWidth = qMax(entry->m_X+entry->m_Text.length(), m_MaxWidth);
		m_MaxHeight = qMax(entry->m_Y, m_MaxHeight);
		TVio::debug(QString("maxw=%1 | %2, maxh=%3 | %4")
			.arg(entry->m_X+entry->m_Text.length()).arg(m_MaxWidth).arg(entry->m_Y).arg(m_MaxHeight));
		m_Entries.insert(m_Entries.count(), entry);
	}
	
	void TMnu::add(int x, int y, const QString& text, int hotkey, const QString& status)
	{
		TMnuEntry* entry = new TMnuEntry(x, y, text, hotkey, status);
		add(entry);
	}

	int TMnu::handle(const QString& title, int x, int y, KeyCodes exits)
	{
		if( !m_Entries.count() )
			return -1;
		if( !m_Win ) {
			int height = m_MaxHeight+2;
			int width = m_MaxWidth+2;
			m_Win = new TWin(m_Vio, x, y, width, height, title.toLatin1());
			m_Win->cursor(TWin::CurOff);						// Cursor abschalten
			m_Win->setBackground(TColors::MnuText);
			m_Win->setFrame(TWin::FrameSingle, TColors::MnuFrame);
			m_Win->setTitle(title, TWin::TitleOZ, TColors::MnuTitle);
		}
		m_Win->clear();
		for(int i=0; i<m_Entries.count(); i++) {
			TMnuEntry* entry = m_Entries[i];
			if( !entry )
				continue;
			m_Win->hot(entry->m_X, entry->m_Y, entry->m_Text, TColors::MnuText, TColors::MnuHotkey);
		}
		int ret = 0;
		bool fertig = false;
		while( !fertig ) {
			TMnuEntry* entry = m_Entries[m_Current];
			m_Win->hot(entry->m_X, entry->m_Y, entry->m_Text, TColors::MnuInvers, TColors::MnuHotInvers);
			m_Vio.status(entry->m_Status, TColors::MnuStatusLine, TColors::MnuStatusInvers);
			m_Win->update();
			ret = getch();
			if( exits.contains(ret) )
				return ret;
			switch(ret)
			{
			case KEY_UP:
				m_Win->hot(entry->m_X, entry->m_Y, entry->m_Text, TColors::MnuText, TColors::MnuHotkey);
				if( --m_Current<0 ) m_Current = m_Entries.count()-1;
				break;
			case KEY_DOWN:
				m_Win->hot(entry->m_X, entry->m_Y, entry->m_Text, TColors::MnuText, TColors::MnuHotkey);
				if( ++m_Current>=m_Entries.count() ) m_Current = 0;
				break;
			case KEY_RETURN:
				return m_Current;
			case KEY_F(10):
				fertig = true;
				break;
			default: {
				for(int n=0; n<m_Entries.count(); n++) {
					if( m_Entries[n]->m_Hotkey==ret || m_Entries[n]->m_Hotkey==QChar(ret).toLower() ) {
						m_Current = n;
						TMnuEntry* entry = m_Entries[m_Current];
						m_Win->hot(entry->m_X, entry->m_Y, entry->m_Text, TColors::MnuInvers, TColors::MnuHotkey);
						fertig = true;
						break;
					}
				} }
			}
		}
		return m_Current;
	}
}

#if 0
 #define        __FUNC__     ERR_MNU_HANDLE
 INT  CDECL     MnuHandle    ( mnu, pcTitel, wX, wY, piExit, help )
 SMnu*          mnu;                             /* Darzustellendes Menue   */
 CHAR*          pcTitel;                         /* Titel des Menues        */
 WORD           wX;                              /* Spalte des Fensters     */
 WORD           wY;                              /* Zeile des Fensters      */
 INT*           piExit;
 FMnuHelp       help;                            /* Hilfefunktion des Menues */
 {
  INT           i, n;                            /* Laufvariable            */
  INT           iCmd;                            /* Auszuwertende Taste     */
  WORD          wMouX;
  WORD          wMouY;
  WORD          wMouState;
  INT           iRet         = -1;               /* Return-Wert der Funktion */
  BOOL          boFertig     = FALSE;            /* Flag, ob Menue abgearbeitet */
  Assert( mnu!=NULL, ERR_PTR );
  if( mnu->Win==NULL )                           /* Wenn Fenster noch nicht da */
  {
   WORD         wHeight      = 0;
   WORD         wWidth       = 0;                /* Breite des Fensters     */
   /* --------- Hoehe ermitteln ------------------------------------------- */
   for( i=0; i<mnu->bActual; i++ )               /* Alle Eintraege durchlaufen */
   {
    if( mnu->Entry[i].wY>wHeight ) wHeight = mnu->Entry[i].wY;
   }
   /* --------- Breite ermitteln ------------------------------------------ */
   for( i=0; i<mnu->bActual; i++ )               /* Alle Eintraege durchlaufen */
   {
    if( ( mnu->Entry[i].wX + strlen(mnu->Entry[i].pcText) ) > wWidth )
     wWidth = mnu->Entry[i].wX + strlen( mnu->Entry[i].pcText );
   }
   mnu->Win = WinEinrichten( wX, wY, wWidth+2, wHeight+4 );
   Assert( mnu->Win!=NULL, ERR_MEM_ALLOC);
   WinSchattenEin( mnu->Win );                   /* Menues haben einen Schatten */
   WinSetRahmentyp( mnu->Win, WIN_FRAME_DOUBLE );/* und doppelten Rahmen    */
   WinSetTitel( mnu->Win, pcTitel, WIN_TITEL_OZ ); /* Den Titel setzen        */
   WinSetAttrib( mnu->Win, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_FRAME ), MnuGetPal( MNU_PAL_TITLE ) );
   WinCursor( WIN_CUR_HIDE );                    /* Attribute setzen und Cursor aus */
   MouSetRange( wX+2, wY+2, wX+wWidth-2, wY+wHeight+1 );
   MouSetPos( wX+2, wY+2 );
   WinAktivieren( mnu->Win );                    /* Jetzt erst Fenster aktivieren */
   WinCls();                                     /* Fensterinhalt loeschen wg Attributen */
   for( i=0; i<mnu->bActual; i++ )
    WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
  }
  else
  {
   MouSetRange( wX+2, wY+2, wX+mnu->Win->wWidth-3, wY+mnu->Win->wHeight-2 );
   WinAktivieren( mnu->Win );                    /* Jetzt erst Fenster aktivieren */
  }
  i=mnu->bCurrent;                              /* Eintraege darstellen und beim aktuellen Eintrag anfangen */
  while( !boFertig )                             /* (Dieser muss nicht mehr 0 sein) */
  {                                              /* Solange nicht ESC gedrueckt     */
   if( strlen( mnu->Entry[i].pcText ) > 0 )      /* Falls der Eintrag gueltig       */
   {
    WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_INVERS ), MnuGetPal( MNU_PAL_INVHOT ) );
    VioStatus( mnu->Entry[i].pcStatus, MnuGetPal( MNU_PAL_STATUS ), MnuGetPal( MNU_PAL_INVSTAT ) );
    iCmd = EvGetKey();                           /* Balken darstellen, Statuszeile updaten */
   }                                             /* und Taste holen         */
   if( piExit!=NULL )
   {
    for( n=0; piExit[n]!=0; n++ )
     if( piExit[n]==iCmd )
     {
      iRet     = iCmd;
      boFertig = TRUE;
     }
   }
   switch( iCmd )                                /* Falls Eintrag ungueltig: */
   {
    case MOU_MOVED:
         WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
         EvMouGetVal( &wMouX, &wMouY, &wMouState );
         wMouY -= wY+2;
          if( ( wMouY<mnu->bActual )
          && ( strlen( mnu->Entry[wMouY].pcText ) > 0 )/* Falls der Eintrag gueltig  */
           )
          i = (INT) wMouY;
         break;
    case MOU_LEFTPRESS:
         WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
         boFertig = TRUE;
         iRet = i;
         break;
    case T_RETURN:
         boFertig = TRUE;                        /* Bei RET sind wir fertig  */
         iRet     = i;                           /* Rueckgabewert ist aktueller Eintrag */
         mnu->bCurrent = (BYTE)iRet;             /* Aktuelle Menue-Position merken */
         break;
    case MOU_RIGHTPRESS:
    case T_F1:                                   /* Falls eine Hilfefunktion angegeben */
         if( help )
         {
          help();                                /* diese aufrufen          */
          WinAktivieren( mnu->Win );
         }
         break;
    case T_ESC:
         boFertig = TRUE;                        /* Bei ESC sind wir auch fertig */
         iRet     = -1;                          /* Rueckgabewert negativ machen */
         mnu->bCurrent = (BYTE)i;                /* Aktuelle Menue-Position merken */
         break;
    default:
         iCmd = toupper( iCmd );                 /* Sonst nachsehen, ob es  */
         for( n=0; n<mnu->bActual; n++ )         /* vielleicht ein Hotkey ist */
          if( iCmd==mnu->Entry[n].iHotkey )      /* und entsprechenden      */
          {                                      /* Menuepunkt aktivieren   */
           WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
           iRet = n;
           boFertig = TRUE;
           mnu->bCurrent = (BYTE)iRet;           /* Aktuelle Menue-Position merken */
           WinHot( mnu->Entry[n].wX, mnu->Entry[n].wY, mnu->Entry[n].pcText, MnuGetPal( MNU_PAL_INVERS ), MnuGetPal( MNU_PAL_INVHOT ) );
          }
   }
  }
  MouSetRange( 0, 0, VioGetMaxCol()-1, VioGetMaxRow()-1 );
  return( iRet );                                /* und mit Rueckgabewert raus */
 }
 #undef         __FUNC__

#ifdef          _TEST_MNU_

 #include       <DEFS/COLORDEF.H>
 #include       <stdio.h>
 #include       <string.h>

 VOID           MenuHelp     ( void )
 {
  static INT    count        = 0;
  VioSs( 0, count++, "Help was chosen" );
//  WinMeldung( 10, 10, "Dies ist eine Hilfe\nWeil das jeder will!.", MELDUNG_INFO );
 }

 VOID           main         ( void )
 {
  static INT    count        = 0;
  CHAR          cTemp[20];
  SMnu*         mnu;
  INT           ret;
  setbuf( stdout, NULL );
//  VioInit( VIO_GR64x48x16M );
  VioInit( VIO_80x28 );
  EvInit();
  VioBackground();
  mnu = MnuInit( 10 );
  MnuAdd( mnu, 1, 1, "Eintrag ~1~", " [~F1~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 2, "Eintrag ~2~", " [~F2~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 3, "Eintrag ~3~", " [~F3~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 4, "Eintrag ~4~", " [~F4~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 5, "Eintrag ~5~", " [~F5~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 6, "Eintrag ~6~", " [~F6~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 8, "Eintrag ~7~", " [~F7~] Dies ist Eintrag 1" );
  while( ( ret = MnuHandle( mnu, "Eintragswahl", VioCenterCol( 20 ), VioCenterRow( 11 ), MenuHelp ) ) != -1 )
  {
   sprintf( cTemp, "Wahl=%d", ret );
   VioSs( VioGetMaxCol()-strlen( cTemp ), count++, cTemp );
  }
  MnuDone( mnu );
  EvDone();
  VioDone();
 }

#endif
#endif
