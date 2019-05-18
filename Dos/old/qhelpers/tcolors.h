#ifndef				HILEVEL_TCOLORS_H
#define				HILEVEL_TCOLORS_H
#include			<QMap>
namespace Hilevel
{
	class			TColors
	{
	public:	// ---- Aufzählungen --------------------------------------------------------------------------------------
		typedef QMap<int,int>	TAttributes;
		enum		Colors
		{
			Background		= 1								//!< Hintergrund des Programms
		,	MsgFrame		= 2								//!< Nachricht, Rahmen
		,	MsgTitle		= 3								//!< Nachricht, Titel
		,	MsgText			= 4								//!< Nachricht, Normaler Text
		,	MsgStatusLine	= 5 							//!< Nachricht, Normaler Text der Statuszeile
		,	LstFrame		= 6								//!< Liste, Rahmen
		,	LstTitle		= 7								//!< Liste, Titel
		,	LstText			= 8								//!< Liste, Normaler Text
		,	LstInvers		= 9								//!< Liste, Inverser Text
		,	LstStatusLine	= 10							//!< Liste, Normaler Text der Statuszeile
		,	LstStatusInvers	= 11							//!< Liste, Inverser Text der Statuszeile
		,	MnuFrame		= 12							//!< Menü, Rahmen
		,	MnuTitle		= 13							//!< Menü, Titel
		,	MnuText			= 14							//!< Menü, Normaler Text
		,	MnuInvers		= 15							//!< Menü, Inverser Text
		,	MnuHotkey		= 16							//!< Menü, Normaler Text bei Hotkeys
		,	MnuHotInvers	= 17							//!< Menü, Inverser Text bei Hotkeys
		,	MnuStatusLine	= 18							//!< Menü, Normaler Text der Statuszeile
		,	MnuStatusInvers	= 19							//!< Menü, Inverser Text der Statuszeile
		,	UserColor		= 20							//!< Erste benutzderfinierte Farbkombination
		};
	/*	enum		Colors
		{
			cBlack			= 1
		,	cBlue			= 2
		,	cGreen			= 3
		,	cCyan			= 4
		,	cRed			= 5
		,	cViolet			= 6
		,	cBrown			= 7
		,	cWhite			= 8
		,	cGrey			= 9
		,	cLightBlue		= 10
		,	cLightGreen		= 11
		,	cLightCyan		= 12
		,	cLightRed		= 13
		,	cLightViolet	= 14
		,	cYellow			= 15
		,	cLightWhite		= 16
		};*/
	public:
		TColors();
		void		configure();
	public:
		int			getBackground();
		int			getUser(int idx);
		int			addUser(int fore, int back, int attr=0);
	private:
		TAttributes	m_Attrs;
		int			m_Current;								//!< Aktuelle Benutzerfarbe beim manuellen hinzufügen
	};
}

using namespace Hilevel;

#endif

#if 0
	#define		_COLORDEF_

	#if( !defined UNIX )

	/* --------- Funktion, die ein Attribut bastelt ------------------------ */
	#define		VH(vorne,hinten)	((hinten<<4)|(vorne))

	/* --------- Textkonstanten fuer die Monochrom-Modi, VGA-Version ------- */
	#define		NORMAL				0x07
	#define		UNTER				0x01
	#define		HELL				0x0F
	#define		HELL_UNTER			0x09
	#define		INVERS				0x70
	#define		MATT_INVERS			0x78

	/* --------- Textkonstanten fuer die Farbmodi, VGA-Version ------------- */
	#define		SCHWARZ				0x00
	#define		BLAU				0x01
	#define		GRUEN				0x02
	#define		KOBALT				0x03
	#define		ROT					0x04
	#define		VIOLETT				0x05
	#define		BRAUN				0x06
	#define		WEISS				0x07
	#define		GRAU				0x08
	#define		HELLBLAU			0x09
	#define		HELLGRUEN			0x0a
	#define		HELLKOBALT			0x0b
	#define		HELLROT				0x0c
	#define		HELLVIOLETT			0x0d
	#define		GELB				0x0e
	#define		HELLWEISS			0x0f

 /* ----------- Textkonstanten f�r alle Modi ------------------------------ */
	#define		BLINKEN				0x80

	#else
	#include	<curses.h>

	#define		VH(vorne,hinten)	(vorne)

	/* --------- Textkonstanten fuer die Monochrom-Modi, VGA-Version ------- */
	#define		NORMAL				A_NORMAL
	#define		UNTER				A_UNDERLINE
	#define		HELL				A_BOLD
	#define		HELL_UNTER			A_BOLD
	#define		INVERS				A_REVERSE
	#define		MATT_INVERS			A_BOLD|A_REVERSE

	/* --------- Textkonstanten fuer die Farbmodi, VGA-Version ------------- */
	#define		SCHWARZ				COLOR_PAIR(COLOR_BLACK)
	#define		BLAU				COLOR_PAIR(COLOR_BLUE)
	#define		GRUEN				COLOR_PAIR(COLOR_GREEN)
	#define		KOBALT				COLOR_PAIR(COLOR_CYAN)
	#define		ROT					COLOR_PAIR(COLOR_RED)
	#define		VIOLETT				COLOR_PAIR(COLOR_MAGENTA)
	#define		BRAUN				COLOR_PAIR(COLOR_YELLOW)
	#define		WEISS				COLOR_PAIR(COLOR_WHITE)
	#define		GRAU				COLOR_PAIR(COLOR_BLACK)|A_BOLD
	#define		HELLBLAU			COLOR_PAIR(COLOR_BLUE)|A_BOLD
	#define		HELLGRUEN			COLOR_PAIR(COLOR_GREEN)|A_BOLD
	#define		HELLKOBALT			COLOR_PAIR(COLOR_CYAN)|A_BOLD
	#define		HELLROT				COLOR_PAIR(COLOR_RED)|A_BOLD
	#define		HELLVIOLETT			COLOR_PAIR(COLOR_MAGENTA)|A_BOLD
	#define		GELB				COLOR_PAIR(COLOR_YELLOW)|A_BOLD
	#define		HELLWEISS			COLOR_PAIR(COLOR_WHITE)|A_BOLD

 /* ----------- Textkonstanten f�r alle Modi ------------------------------ */
	#define		BLINKEN				0x80

	#endif

#endif
