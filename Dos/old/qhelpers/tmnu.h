#ifndef				HILEVEL_TMNU_H
#define				HILEVEL_TMNU_H
#include			"hilevel/twin.h"
#include			<QString>
#include			<QMap>
#include			<QPointer>

namespace Hilevel
{
	// Struktur eines Menu-Eintrags
	class			TMnuEntry
	{
	public:
		TMnuEntry();
		TMnuEntry(int x, int y, const QString& text, int hotkey=0, const QString& status=QString::null);
	public:
		int			m_X;									//! X-Position des Eintrags
		int			m_Y;									//! Y-Position des Eintrags
		int			m_Hotkey;								//! Hotkey des Eintrags
		QString		m_Text;									//! Menupunkt-Text
		QString		m_Status;								//! Statuszeile des Eintrags
	};

	class			TMnu
	{
	public:
		typedef QMap<int,TMnuEntry*>	TMnuEntries;
	public:
		TMnu(TVio& vio);
		~TMnu();
	public:
		void		add(TMnuEntry* entry);
		void		add(int x, int y, const QString& text, int hotkey=0, const QString& status=QString::null);
		int			handle(const QString& title, int x, int y, KeyCodes exits);
	private:
		TVio&		m_Vio;
		int			m_Current;								//! Beim Handling aktueller Eintrag
		int			m_MaxWidth;								//! Breitester String
		int			m_MaxHeight;							//! Höchster String
		TMnuEntries	m_Entries;								//! Liste der Einträge
		QPointer<TWin>	m_Win;								//! Ausgabe-Fenster
	};
}

using namespace Hilevel;

#endif
