#ifndef				HILEVEL_TLST_H
#define				HILEVEL_TLST_H
#include			"hilevel/tvio.h"
#include			"hilevel/twin.h"
#include			<QString>
#include			<QObject>
#include			<QVariant>
#include			<QPointer>

namespace Hilevel
{
	class			TLst
	: public QObject
	{
		/*!	Ein Listenelement
		*/
		struct			TLstEntry
		{
			QString	m_Str;									//!< Der Eintrags-Text
			QVariant	m_Data;								//!< Zugehörige Eintragsdaten
			TLstEntry(const QString& str, const QVariant& data)
			: m_Str(str)
			, m_Data(data)
			{
			}
		};
		typedef QList<TLstEntry*>			TLstEntries;
		typedef QList<TLstEntry*>::Iterator	TLstEntryIt;
	public:
		// --------- Konstanten fuer den Darstellungsmodus -----------------------------------------------------------
		enum		Modes
		{
			Info		= 1									//!< Liste dient nur zur Info
		,	Select		= 2									//!< Liste dient zur Element-Auswahl
		};
		enum		Sorts
		{
			None		= 1									//!< Unsortierte Liste
		,	Id			= 2									//!< Nach ID sortieren
		,	Text		= 3									//!< Nach String sortieren
		};
	public:	// ---- ctor/dtor -----------------------------------------------------------------------------------------
 		TLst(TVio& vio, Modes mode=Info);
 		virtual ~TLst();
	public:
		int			getCount() const
		{
			return m_Entries.count();
		}
		int			getMaxWidth() const
		{
			return m_MaxWidth;
		}
		void		removeLast()
		{
			m_Entries.removeLast();
			if( m_End>getCount() )
				m_End--;
			if( m_Start+m_Current>getCount() )
				m_Current--;
		}
	public:
		void		append(const QString& str, const QVariant& data=QVariant());
		QVariant	getEntry()
		{
			return getEntry(getCurrent());
		}
		QVariant	getEntry(int idx)
		{
			TLstEntry* entry = m_Entries[idx];
			if( entry )
				return entry->m_Data;
			return QVariant();
		}
		int			findEntry(const QString& str);
		int			findData(const QVariant& data);
		int			getCurrent()
		{
			return m_Start+m_Current;
		}
		void		setCurrent(int idx)
		{
			if( idx>=0 ) {	
				m_Start = idx;
				m_Current = 0;
			}
		}
		void		setCurrent(const QString& str)
		{
			int idx = findEntry(str);
			if( idx>=0 ) {
				m_Start = idx;
				m_Current = 0;
			}
		}
		void		setCurrent(const QVariant& data)
		{
			int idx = findData(data);
			if( idx>=0 ) {
				m_Start = idx;
				m_Current = 0;
			}
		}
		void		draw(int x, int y, int width, int height, const QString& title, const QString& status);
		int			show(int x, int y, int width, int height, const QString& title, const QString& status, KeyCodes exits=KeyCodes());
 		int			center(const QString& title, const QString& status=QString::null, KeyCodes exits=KeyCodes());
	private:
		void		drawLine(int line, int element, bool selected=false);
		void		drawUp(bool current);
		/*!	Beginnt bei m_Start und gibt so viele Element aus, wie in das Fenster passen. Wenn alle Element in das
			Fenster passen, ist m_End danach m_Start+Fensterhöhe, sonst der Index des letzten Elements.
			Sofern m_Start + m_Current größer als der Index wird, wird m_Current auf die letzte Zeile gesetzt.
		*/
		void		drawDown();
	private:
		TVio&		m_Vio;
		QPointer<TWin>	m_Win;
		TLstEntries	m_Entries;								//!< Die Eintragsliste
		int			m_Mode;									//!< Art der Darstellung laut Modes
		int			m_Sort;									//!< Art der Sortierung laut Sorts

		int			m_Start;								//!< Die ID erste angezeigte Eintrag
		int			m_End;									//!< Die ID letzte angezeigte Eintrag
		int			m_Current;								//!< Die Position des Scrollbalkens
		QString		m_Search;								//!< Such-String der Liste
		int			m_Column;								//!< Position innerhalb der Zeile
		int			m_MaxCol;
		int			m_MaxWidth;								//!< Länge des längsten Strings
	};	
}

using namespace Hilevel;

#endif

#if 0
 /* ----------- Struktur eines Listeneintrags ----------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif

 /* ----------- Funktionestypen ------------------------------------------- */
 struct SLst;
 typedef BOOL   (CDECL *FLstLess)  PARAM(( SLstEntry*, SLstEntry* ));
 typedef VOID   (CDECL *FLstHelp)  PARAM(( void ));
 typedef VOID   (CDECL *FLstOnKeyReleased) PARAM(( INT, struct SLst* ));

 /* ----------- Struktur einer Liste -------------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct SLst
 {
  CHAR          pcSearch[21];                    
  INT           iCount;
  FLstLess      Less;                            /* Sortier-Funktion der Liste */
  FLstOnKeyReleased OnKeyReleased;                       /* Funktion bei Taste losgelassen */
  SDLst*        List;                            /* Liste der Eintraege     */
  SWin*         Win;                             /* Ausgabefenster          */
  WORD          wStrLen;                         /* Maximal-Laenge eines Strings */
  INT           iWinPos;                         /* Position des Scrollbalkens */
  INT           iStrPos;                         /* Position vertikal */
  BOOL          boNoShadow;
  SDLstEntry*   Start;                           /* Erster Listeneintrag im Fenster */
  SDLstEntry*   End;                             /* Letzter Listeineintrag im Fenster */
 } SLst;

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 SLst*  CDECL   LstInit         PARAM(( WORD ));
 VOID   CDECL   LstDone         PARAM(( SLst* ));
 VOID   CDECL   LstSetSort      PARAM(( SLst*, FLstLess ));
 VOID   CDECL   LstSetOnKeyReleased PARAM(( SLst*, FLstOnKeyReleased ));
 ULONG  CDECL   LstGetCount     PARAM(( SLst* ));
 LONG   CDECL   LstGetNum       PARAM(( SLst* ));
 CHAR*  CDECL   LstGetStr       PARAM(( SLst*, LONG ));
 VOID   CDECL   LstInsert       PARAM(( SLst*, LONG, CHAR*, CPPARGS ));
 VOID   CDECL   LstChange       PARAM(( SLst*, LONG, LONG, CHAR*, CPPARGS ));
 VOID   CDECL   LstDelete       PARAM(( SLst*, LONG ));
 VOID   CDECL   LstDraw         PARAM(( SLst*, INT, WORD, WORD, WORD, WORD, CHAR*, CHAR* ));
 INT    CDECL   LstShow         PARAM(( SLst*, INT, WORD, WORD, WORD, WORD, CHAR*, CHAR*, INT*, FLstHelp ));
 LONG   CDECL   LstFirst        PARAM(( SLst* ));
 LONG   CDECL   LstNext         PARAM(( SLst* ));
 VOID   CDECL   LstShadow       PARAM(( SLst*, BOOL ));
 DECLEND

 #define        LST_INFO        0
 #define        LST_LIST        1
#endif
