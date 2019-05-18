#ifndef				_HILEVEL_LISTWIN_

#define				_HILEVEL_LISTWIN_
#include			"hilevel/Win.h"
#include			"hilevel/Palette.h"
#include			"qstring.h"
#include			"qlist.h"

namespace Hilevel
{
	struct	SLst;

	struct			SLstEntry
	{
		SLstEntry(long _num, const QString& _str)
		: num(_num)
		, str(_str)
		, marked(false)
		{
		}
		long		num;						//! Nummer des Eintrags
		QString		str;						//! Der Eintrags-Text
		bool		marked;						//! Flag, ob Eintrag markiert ist
	};

	class			TLstEntryList
	: public QList<SLstEntry>
	{
	public:
		TLstEntryList()
		: QList<SLstEntry>()
		{
		}
		TLstEntryList(const TLstEntryList& list)
		: QList<SLstEntry>(list)
		{
		}
	};

	class	TLst;
	typedef bool	(*FLstLess)(SLstEntry* entry1, SLstEntry* entry2);
	typedef void	(*FLstHelp)(TLst* lst);
	typedef void	(*FLstOnKey)(int key, TLst* lst);

	class			TLst
	{
	public:
		enum		Modes
		{
			modeInfo	= 0
		,	modeList	= 1
		,	modeMulti	= 2
		};
	public:
		TLst(int mode, int x, int y, int width, int height)
		: m_Mode(mode)
		, m_X(x)
		, m_Y(y)
		, m_Width(width)
		, m_Height(height)
		, Less(NULL)
		, OnKey(NULL)
		, m_Win(NULL)
		, winPos(0)
		, strPos(0)
		, noShadow(false)
		, strLen(0)
		, m_Selected(0)
		{
		}
		virtual ~TLst()
		{
			if( m_Win )
				WinEntfernen(m_Win);
		}
		SWin*		win()
		{
			return m_Win;
		}
		void		clear()
		{
			List.clear();
		}
		void		setSort(FLstLess less)
		{
			Less = less;
		}
		void		setOnKey(FLstOnKey onkey)
		{
			OnKey = onkey;
		}
		void		setShadow(bool flag)
		{
			noShadow = !flag;
		}
		long		getCount()
		{
			return List.count();
		}
		long		getSelectedCount() const
		{
			return m_Selected;
		}
		long		getNumber()
		{
			return start+winPos;
		}
		TLstEntryList	getSelected();
		SLstEntry*	getCurrent()
		{
			int pos = start+winPos;
			if( pos>=List.count() )
				return NULL;
			return List.at(pos);
		}
		QString		getString(long num)
		{
			SLstEntry* entry = searchNum(num);
			if( !entry )
				return QString();
			return entry->str;
		}
		void		insert(long num, const QString& str);
		void		change(long old, long num, const QString& str)
		{
			if( old!=num )
				remove(old);
			insert(num, str);
		}
		bool		remove(long num);
		SLstEntry*	first()
		{
			return List.first();
		}
		SLstEntry*	next()
		{
			return List.next();
		}
		SLstEntry*	prev()
		{
			return List.prev();
		}
		SLstEntry*	last()
		{
			return List.last();
		}
		void		move(int x, int y);
		void		draw(const QString& title, const QString& status);
		int			handle(const QString& title, const QString& status, FLstHelp help, const QArray<int>& exit=QArray<int>());
	protected:
		bool		handleKey(int& key, bool& fertig);
		void		drawPos(bool on)
		{
			if(m_Mode==modeInfo)
				return;
			SLstEntry* entry = List.at(start+winPos);
			if(entry && m_Mode==modeMulti)
			{
				WinSz(0, winPos, entry->marked?174:' ');
				WinSz(m_Win->wWidth-2, winPos, entry->marked?175:' ');
			}
			WORD attr;
			if( on )
				attr = LstGetPal(LST_PAL_INVERS);
			else
			{
				if( entry && entry->marked)
				{
					attr = LstGetPal(LST_PAL_MULTI);
					WinSz(0, winPos, 174);
					WinSz(m_Win->wWidth-2, winPos, 175);
				}
				else
				{
					attr = LstGetPal(LST_PAL_TEXT);
					WinSz(0, winPos, ' ');
					WinSz(m_Win->wWidth-2, winPos, ' ');
				}
			}
			WinSwa(0, winPos, m_Win->wWidth-1, 1, attr);
		}
		SLstEntry*	searchNum(long num);
		void		drawArrows()
		{
			char prev = start!=0 ? 0x18 : 'Ä';
			WinSz(m_Win->wWidth-4, m_Win->wHeight-1, prev);
			char next = end<List.count() ? 0x19 : 'Ä';
			WinSz(m_Win->wWidth-5, m_Win->wHeight-1, next);
			if( m_Mode==modeMulti && m_Win->wWidth>10 )
			{
				QString str;
				str.sprintf("%ld", m_Selected);
				str = str.leftJustify(7, 'Ä');
				WinSs(5, m_Win->wHeight-1, (CHAR*)(const char*)str);
			}
		}
		void		drawDown();
		void		drawEl(SLstEntry* entry, int line);
	protected:
		int			m_Mode;
		int			m_X;
		int			m_Y;
		int			m_Width;
		int			m_Height;
		long		m_Selected;
		QString		search;						//! Such-String der Liste
		FLstLess	Less;						//! Sortier-Funktion der Liste
		FLstOnKey	OnKey;						//! Funktion bei Taste losgelassen
		QList<SLstEntry>	List;
		SWin*		m_Win;						//! Ausgabefenster
		int			winPos;						//! Position des Scrollbalkens
		int			strPos;						//! Position vertikal
		bool		noShadow;
		int			strLen;
		int			start;
		int			end;
		int			searchPos;
		QString		searchStr;
	};

	/* DECLSTART
	long			lstGetNum(SLst* lst);
	bool			lstGoto(SLst* lst, long num);
	void			lstDraw(SLst* lst, int mode, int x, int y, int width, int height, const QString& title, const QString& status);
	int				lstHandle(SLst* lst, int mode, int x, int y, int width, int height, const QString& title, const QString& status, int* exit=NULL, FLstHelp help=NULL);
	DECLEND */
}

using namespace Hilevel;

#endif

