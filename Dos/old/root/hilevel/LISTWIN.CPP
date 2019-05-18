#include			"hilevel/ListWin.h"
#include			"hilevel/Vio.h"
#include			"hilevel/Event.h"
#include			"hilevel/EvMouse.h"
#include			"lolevel/PcMouse.h"
#include			"basics/Log.h"
#include			"defs/ErrorDef.h"
#include			"defs/KeyDefs.h"
/*
 #include       <stdarg.h>
 #include       <stdio.h>
 #include       <string.h>
 #include       <ctype.h>
*/
#include "basics/Log.h"
namespace Hilevel
{
	TLstEntryList TLst::getSelected()
	{
		TLstEntryList list;
		SLstEntry* entry;
		for( entry=List.first(); entry; entry=List.next() )
		{
			if( entry->marked )
				list.append(entry);
		}
		return list;
	}

	void TLst::insert(long num, const QString& str)
	{
		SLstEntry* entry = new SLstEntry(num, str);
		if( Less )
			List.inSort(entry);
		else
			List.append(entry);
		if( str.length()>strLen )
			strLen = str.length();
	}

	bool TLst::remove(long num)
	{
		SLstEntry* entry = searchNum(num);
		if( entry )
		{
			List.remove(entry);
			delete entry;
			return true;
		}
		return false;
	}

	void TLst::move(int x, int y)
	{
		if( m_Win )
			WinEntfernen(m_Win);
		m_X += x;
		m_Y += y;
	}

	void TLst::draw(const QString& title, const QString& status)
	{
		if( m_Win==NULL )
		{
			m_Win = WinEinrichten(m_X, m_Y, m_Width, m_Height);
			WinSetAttrib(m_Win, LstGetPal(LST_PAL_TEXT), LstGetPal(LST_PAL_FRAME), LstGetPal(LST_PAL_TITLE));
			WinSetRahmentyp(m_Win, WIN_FRAME_SINGLE);
			if( !noShadow )
				WinSchattenEin(m_Win);
			WinSetTitel(m_Win, (CHAR*)(const char*)title, WIN_TITEL_OZ);

			winPos = 0;
			start = 0;
		}

		WinAktivieren(m_Win);
		WinCursor(WIN_CUR_HIDE);
		VioStatus((CHAR*)(const char*)status, LstGetPal(LST_PAL_STATUS), LstGetPal(LST_PAL_INVSTAT));
		MouSetRange(m_X+1, m_Y, m_X+m_Width-2, m_Y+m_Height-1);
		MouSetPos(m_X+1, m_Y+winPos+1);

		drawDown();
		drawPos(true);
	}

#include <conio.h>
	int TLst::handle(const QString& title, const QString& status, FLstHelp help, const QArray<int>& exit)
	{
		draw(title, status);

		searchStr = QString();
		searchPos = 0;
		int ret = 0;
		bool fertig = false;
		while( !fertig )
		{
			drawPos(true);
			drawArrows();
/*
{
QString tmp;
tmp.sprintf("start=%4d, end=%4d, winpos=%4d, height=%4d, count=%d, strpos=%d, strlen=%d", lst->start, lst->end, lst->winPos, height, lst->List.count(), lst->strPos, lst->strLen);
vioSs(0, 0, tmp);
}
*/
			if( OnKey!=NULL && ret!=0 )
				OnKey(ret,this);
			ret = EvGetKey();
			if( !exit.isEmpty() && exit.find(ret)>=0 )
			{
				fertig = true;
				break;
			}
			if( ret==MOU_RIGHTPRESS || ret==T_F1 )
			{
				if( help )
				{
					MouSetRange(0, 0, VioGetMaxCol()-1, VioGetMaxRow()-1);
					help(this);
					VioStatus((CHAR*)(const char*)status, LstGetPal(LST_PAL_STATUS), LstGetPal(LST_PAL_INVSTAT));
					WinAktivieren(m_Win);
					MouSetRange(m_X+1, m_Y, m_X+m_Width-2, m_Y+m_Height-1);
					MouSetPos(m_X+1, m_Y+winPos+1);
				}
			}
			else
				handleKey(ret, fertig);
		}
		return ret;
	}

	bool TLst::handleKey(int& key, bool& fertig)
	{
		static bool inMouse = false;
		for( ;; )
		{
			switch(key)
			{
			case MOU_LEFTPRESS:
				key = T_RETURN;
			case T_RETURN:
			case T_ESC:
				fertig = TRUE;
				break;
			case T_SPACE:
				{
					if( m_Mode!=modeMulti )
						break;
					drawPos(false);
					SLstEntry* entry = List.at(start+winPos);
					if( !entry )
						break;
					entry->marked = !entry->marked;
					if(entry->marked)
						m_Selected++;
					else
						m_Selected--;
					drawPos(true);
					break;
				}
			case T_HOME:
				if( winPos==0 && start==0 )
					break;
				drawPos(false);
				winPos = start = 0;
				drawDown();
				break;
			case T_PGUP:
				drawPos(false);
				if( start>0 )
				{
					start -= m_Height-2;
					if( start<0 )
					{
						start = 0;
						winPos = 0;
					}
					drawDown();
					break;
				}
				winPos = 0;
				break;
			case T_UP:
				drawPos(false);
				if( (m_Mode!=modeInfo) && (winPos>0) )
				{
					winPos--;
					break;
				}
				if( start>0 )
				{
					WinScrollDown();
					start--;
					end--;
					drawDown();
					if( inMouse )
					{
						key = MOU_MOVED;
						continue;
					}
				}
				break;
			case T_DOWN:
				drawPos(false);
				if( (m_Mode!=modeInfo) && (winPos<m_Height-3) )
				{
					if( start+winPos+1<List.count() )
						winPos++;
					break;
				}
				if( end<List.count() )
				{
					WinScrollUp();
					start++;
					end++;
					drawDown();
					if( inMouse )
					{
						key = MOU_MOVED;
						continue;
					}
				}
				break;
			case T_PGDN:
				drawPos(false);

				if( end/*+height*/<List.count() )
				{
					start = end;
					drawDown();
					if( start+winPos>List.count() )
						winPos = List.count()-start-1;
					break;
				}
				winPos = List.count()-start-1;
				break;
			case T_END:
				drawPos(false);

				winPos = List.count()%(m_Height-2)-1;
				start = List.count()-winPos-1;
				drawDown();
				break;
			case T_LEFT:
				if( strPos>0 )
				{
					strPos--;
					drawDown();
				}
				break;
			case T_RIGHT:
				if( strPos<strLen-m_Width )
				{
					strPos++;
					drawDown();
				}
				break;
			case MOU_MOVED:
				{
					drawPos(false);
					INT moux, mouy;
					WORD state;
					EvMouGetVal((WORD*)&moux, (WORD*)&mouy, &state);
					mouy -= m_Y+1;

					if( (mouy==m_Height-2) /*&& (lst->winPos==height-1)*/ )
					{
						inMouse = true;
						key = T_DOWN;
						continue;
					}
					if( (mouy<0) && (winPos==0) )
					{
						inMouse = true;
						key = T_UP;
						continue;
					}
					inMouse = false;

					if( mouy<0 || mouy>=m_Height-1 )
						break;
					if( start+mouy>=List.count() )
						break;
					winPos = mouy;
				}
				break;
			case T_BACKSPACE:
				drawPos(false);
				searchPos = start = winPos = strPos = 0;
				searchStr = "";
				drawDown();
				break;
			default:
				searchStr += key;
VioSs(0, 0, (CHAR*)(const char*)searchStr);
QString tmp;
tmp.sprintf("%d - %d", searchPos, List.count());
VioSs(40, 0, (CHAR*)(const char*)tmp);
				for(int i=searchPos; i<List.count(); i++ )
				{
					SLstEntry* entry = List.at(i);
					if( !entry )
						break;
QString tmp2;
tmp2.sprintf( "\n%s ? %s", (const char*) entry->str, (const char*) searchStr); getch();
VioSs(60, 0, (CHAR*)(const char*)tmp2);
					if( entry->str.find(searchStr, 0, false)>=0 )
					{
						drawPos(false);
						winPos = 0;
						start = i;
						break;
					}
				}
				break;
/*
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
*/
			}
			break;
		}
		return true;
	}

#ifdef NEVER
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
#endif


	void TLst::drawDown()
	{
		WinCls();

		for(int i=0; i<m_Win->wHeight-1; i++ )
		{
			if( i+start>=List.count() )
				break;
			SLstEntry* entry = List.at(start+i);
			if( !entry )
				break;
			drawEl(entry, i);
		}
		end = start+i;
	}

	void TLst::drawEl(SLstEntry* entry, int line)
	{
		if( !entry )
			return;
//stdlog.setLoglevel(TLog::logAll);
//stdlog << TLog::logDebug << (const char*) entry->str;
#ifdef sau
		QString str = entry->str;
		int found = 0;
		while((found=str.find('!', found))>=0 )
		{
			if( found!=str.length() && str[found+1]!=' ' )
				str = str.left(found) + str.right(str.length()-found-1);
		}

		if( str.length()>strPos )
			str = str.right(strLen/*str.length()*/-strPos);
		else
			str = "";
//		if( str.length()>lst->win->iWidth-2 )
//			str = str.left(lst->win->iWidth-2);
//		str = str.mid(lst->strPos, lst->win->iWidth-2);
#endif
		WinSs(1, line, (CHAR*)(const char*)entry->str);
		if( m_Mode==modeMulti )
		{
			WORD attr = entry->marked ? LstGetPal(LST_PAL_MULTI):LstGetPal(LST_PAL_TEXT);
			WinSwa(0, line, m_Win->wWidth-1, 1, attr);
			WinSz(0, line, entry->marked?174:' ');
			WinSz(m_Win->wWidth-2, line, entry->marked?175:' ');
		}
	}

	SLstEntry* TLst::searchNum(long num)
	{
		SLstEntry* entry = List.current();
		if( !entry || (num!=-1L && entry->num!=num) )
		{
			for( entry=first(); entry; entry=next() )
			{
				if( entry->num==num )
					break;
			}
		}
		return entry;
	}
}

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


#ifdef				_TEST_LSTWIN_
#include			"hilevel/Application.h"
#include			"hilevel/Mnu.h"
#include			"hilevel/MsgWin.h"
#include			"qdatetime.h"
#include			"qdir.h"
#include			"qfileinfo.h"
#include			<conio.h>
#include			<stdio.h>

class				TApp
: public TApplication
{
public:
	TApp()
	{
	}
	virtual void	init()
	{
		TApplication::init();
		addTranslator("lstwin");
	}
	virtual int		run();
private:
	void			minimal();
	void			speed();
	void			dir();
	void			infodir();
	void			multi();
};

TProgram* createProgram()
{
	return new TApp();
}

int TApp::run()
{
	SMnu* mnu = mnuInit(5);
	mnuAdd(mnu, 1, 1, tr("~M~inimal-test"), tr(" Test von insert und delete Funktionen"));
	mnuAdd(mnu, 1, 2, tr("~G~eschwindigkeit"), tr("Einfügen von großen Datenmengen"));
	mnuAdd(mnu, 1, 3, tr("~V~erzeichnis"), tr("Stellt das Verzeichnis von C:\\ dar"));
	mnuAdd(mnu, 1, 4, tr("~I~nfo-Verz"), tr("Stellt das Verzeichnis von C:\\ dar (nur Info-Liste)"));
	mnuAdd(mnu, 1, 5, tr("M~u~ltiselect"), tr("Testen der Multi-Selekt-Funktionen"));
	bool fertig = false;
	while( !fertig )
	{
		int ret = mnuHandle(mnu, vio->centerCol(20), vio->centerRow(6), tr(" Listentest "));
		switch( ret )
		{
		case -1:
			fertig = true;
			break;
		case 0:
			minimal();
			break;
		case 1:
			speed();
			break;
		case 2:
			dir();
			break;
		case 3:
			infodir();
			break;
		case 4:
			multi();
			break;
		}
	}
	mnuDone(mnu);

	return 0;
}

void TApp::minimal()
{
	SWin* win = winEinrichten(vio->centerCol(40), vio->centerRow(22), 40, 22);
	winAktivieren(win);

	TLst* lst = new TLst(TLst::modeInfo, 0, 0, 0, 0);
	for(long l=0L; l<10L; l++ )
	{
		lst->insert(l, QString("Dies ist Zeile %1").arg(l));
	}
	winPrintf(tr("%1 Element in Liste:\n").arg(lst->getCount()));
	for( SLstEntry* entry=lst->first(); entry; entry=lst->next() )
	{
		winPrintf(tr("Eintrag %1 = \"%2\"\n").arg(entry->num).arg((const char*) entry->str)); //lstGetStr(lst, l)));
	}
	winPrintf(tr("\nESC weiter..."));
	while( evGetKey()!=T_ESC );

	for(long k=0L; k<10L; k+=2 )
	{
		lst->remove(k);
	}
	winPrintf(tr("\n%1 Element in Liste:\n").arg(lst->getCount()));
	for( entry=lst->first(); entry; entry=lst->next() )
	{
		winPrintf(tr("Eintrag %1 = \"%2\"\n").arg(entry->num).arg((const char*) entry->str)); //lstGetStr(lst, l)));
	}
	winPrintf(tr("\nESC weiter..."));
	while( evGetKey()!=T_ESC );

	delete lst;
	winEntfernen(win);
}

void TApp::speed()
{
	SWin* win = winEinrichten(vio->centerCol(40), vio->centerRow(12), 40, 12);
	winAktivieren(win);

	TLst* lst = new TLst(TLst::modeInfo, 0, 0, 0, 0);
	winPrintf(tr("Erzeuge Liste..."));
	QTime time1a = QTime::currentTime();
	for( long l=0L; l<20000L; l++ )
		lst->insert(l, tr("Dies ist Zeile %1").arg(l));
	QTime time1b = QTime::currentTime();
	winPrintf(tr(" fertig in %1 ms\n").arg(time1a.msecsTo(time1b)));
	winPrintf(tr("%1 Elemente in Liste\n").arg(lst->getCount()));

	winPrintf("Lösche Liste...");
	long missed = 0L;
	QTime time2a = QTime::currentTime();
	for( long k=0L; k<20000L; k++ )
	{
		if( !lst->remove(k) )
			missed++;
	}
	QTime time2b = QTime::currentTime();
	if( missed )
		winPrintf(tr("%1 Elemente nicht gefunden\n").arg(missed));
	winPrintf(tr(" fertig in %1 ms\n").arg(time2a.msecsTo(time2b)));
	winPrintf(tr("%1 Elemente in Liste\n").arg(lst->getCount()));

	winPrintf(tr("\nESC weiter..."));
	delete lst;
	while( evGetKey()!=T_ESC );
	winEntfernen(win);
}

void dirHelp(TLst*)
{
	winMsgCenter("A help for the list", MSG_INFO);
}

void TApp::dir()
{

	bool fertig = false;
	QString path;
	path = "c:/winnt";

	while( !fertig )
	{
		TLst* lst = new TLst(TLst::modeList,vio->centerCol(40), vio->centerRow(22), 40, 22);
debug( "\nstr=%s", (const char*) path);
		QDir dir(path);

		for( int i=0; i<dir.count(); i++ )
		{
			QString name = dir[i];
			QFileInfo info(path+name);
			if( info.isDir() )
				lst->insert(i, QString("[%1]").arg(name));
			else
				lst->insert(i, QString("%1").arg(name));
		}
		for( ;; )
		{
			int ret = lst->handle(/*path*/"", "", dirHelp);
			if( ret==T_ESC )
			{
				fertig = true;
				break;
			}
			SLstEntry* entry = lst->getCurrent();
			if( !entry )
				break;
			if( entry->str.left(1)=="[" )
			{
				QString tmp = path + entry->str.right(entry->str.length()-1);
				tmp = tmp.left(tmp.length()-1);
				tmp += "/";
				path = tmp;
printf( "\nstr=%s", (const char*) tmp);
printf( "\nstr=%s", (const char*) path);
				break;
			}
			winMsgCenter(entry->str, MSG_INFO);
		}
		delete lst;
	}

/*
  SLst*         lst;
  LONG          lCount       = 0L;
  BOOL          boEnde       = FALSE;
  INT           iEbene       = 0;
  CHAR*         cp;
  INT           i,w;
  SFindT        find;
  BOOL          boFertig;
  CHAR          cPath[129];
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
*/
}

void TApp::infodir()
{

	bool fertig = false;
	QString path;
	path = "c:/winnt";

	TLst* lst = new TLst(TLst::modeInfo,vio->centerCol(40), vio->centerRow(22), 40, 22);
	QDir dir(path);

	for( int i=0; i<dir.count(); i++ )
	{
		QString name = dir[i];
		QFileInfo info(path+name);
		if( info.isDir() )
			lst->insert(i, QString("[%1]").arg(name));
		else
			lst->insert(i, QString("%1").arg(name));
	}
	lst->handle(/*path*/"", "", dirHelp);
	delete lst;
}

void TApp::multi()
{

	bool fertig = false;
	QString path;
	path = "c:/winnt";

	TLst* lst = new TLst(TLst::modeMulti,vio->centerCol(40), vio->centerRow(22), 40, 22);
	QDir dir(path);

	for( int i=0; i<dir.count(); i++ )
	{
		QString name = dir[i];
		QFileInfo info(path+name);
		if( info.isDir() )
			lst->insert(i, QString("[%1]").arg(name));
		else
			lst->insert(i, QString("%1").arg(name));
	}
	lst->handle(/*path*/"", "", dirHelp);
	TLstEntryList list = lst->getSelected();

	SWin* win = winEinrichten(vio->centerCol(40), vio->centerRow(12), 40, 12);
	winAktivieren(win);
	winPrintf(QString("%1 selected:\n").arg(lst->getSelectedCount()));
	for( SLstEntry* entry=list.first(); entry; entry=list.next() )
		winPrintf(QString("%1) %2\n").arg(entry->num).arg(entry->str));
	evGetKey();
	winEntfernen(win);
	delete lst;
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

