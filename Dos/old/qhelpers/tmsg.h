#ifndef				HILEVEL_TMSG_H
#define				HILEVEL_TMSG_H
#include			"hilevel/tvio.h"
#include			"hilevel/twin.h"
#include			<QString>
#include			<QObject>
#include			<QPointer>

//struct WINDOW;
struct _win_st;

namespace Hilevel
{
	class			TMsg
	: public QObject
	{
	public:
		// --------- Konstanten fuer den Darstellungsmodus -----------------------------------------------------------
		enum		Modes
		{
			Info		= 1
		,	YesNo		= 2
		,	YesNo2		= 3
		,	Dauer		= 4
		,	Dauer2		= 5
		,	F1F2		= 6
		};
	public:	// ---- ctor/dtor -----------------------------------------------------------------------------------------
 		TMsg(TVio& vio);
 		~TMsg();
		/*! Stellt die übergebenen Informationen in einem Fenster dar und wartet auf die Abbruchbedingung.
		*/
 		int			show(int x, int y, const QString& text, Modes mode, const QString& status=QString::null);
 		int			center(const QString& text, Modes mode, const QString& status=QString::null);
	private:
		void		getWidhtHeight(const QString& text, int& width, int& height);
	private:
		TVio&		m_Vio;
		QPointer<TWin>	m_Win;
	};	
}

using namespace Hilevel;

#endif

#if 0
#endif
