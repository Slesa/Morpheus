#ifndef				HILEVEL_TWIN_H
#define				HILEVEL_TWIN_H
#include			"hilevel/tvio.h"
#include			<QObject>
#include			<QString>

//struct WINDOW;
struct _win_st;

namespace Hilevel
{
	class	TWin;
	typedef QList<TWin*>	TWinList;

	class			TWin
	: public QObject
	{
	public:
		// -------- Konstanten fuer die Titelposition -----------------------------------------------------------------
		enum		TitlePos
		{
			TitleOL			= 0								//! oben, linksbündig
		,	TitleUL			= 1								//! unten, linksbündig
		,	TitleOZ			= 2								//! oben, zentriert
		,	TitleUZ			= 3								//! unten, zentriert
		,	TitleOR			= 4								//! oben, rechtsbündig
		,	TitleUR			= 5								//! unten, rechtsbündig
		};
		// -------- Konstanten fuer die Rahmenart ---------------------------------------------------------------------
		enum		FrameType
		{
			FrameNone		= 0								//! Kein Rahmen
		,	FrameSingle		= 1								//! Einfacher Rahmen
		,	FrameDouble		= 2								//! Doppelter Rahmen
		,	FrameThick		= 3								//! Dicker Rahmen
		};
		enum		Cursors
		{
			CurOff			= 0								//!< Cursor ausschalten
		,	CurLine			= 1								//!< Cursor ist auf Linie
		,	CurBlock		= 2								//!< Cursor ist auf Block
		};
	public:	// ---- ctor/dtor -----------------------------------------------------------------------------------------
		TWin(TVio& vio, int x, int y, int width, int height, const char* name);
		~TWin();
	public:
		/*!	\return Liefert die Spalte des Fensters.
			\brief X-Position ermitteln.
		*/
		int			getX();
		/*!	\return Liefert die Zeile des Fensters.
			\brief Y-Position ermitteln.
		*/
		int			getY();
		/*!	\return Liefert die Anzahl der Spalten des Fensters.
			\brief Breite ermitteln.
		*/
		int			getMaxCol();
		/*!	\return Liefert die Anzahl der Zeilen des Fensters.
			\brief Höhe ermitteln.
		*/
		int			getMaxRow();
		int			centerCol(int len=0)
		{
			return (getMaxCol()-len) / 2;
		}
		int			centerRow(int height=0)
		{
			return (getMaxRow()-height) / 2;
		}
		void		setFrame(FrameType frame, int col);
		void		setTitle(const QString& title, TitlePos pos, int col);
	public:
		bool		isVisible();
		void		show();
		void		hide();
		void		setBackground(int col);
		void		update();
		/*!	Löscht den Fensterinhalt. Hierbei bleibt die Hintergrundfarbe unangetastet.
		*/
		void		clear();
		/*!	Setzte die Farbe mit dem Farbenindex col an der Position (x,y). Das Zeichen wird dabei nicht geändert.
			\brief Attribut setzen
		*/
		void		sa(int x, int y, int col);
		/*! Setzt das Zeichen ch an die Position (x,y). Das Attribut wird dabei nicht geändert.
			\brief Zeichen setzen
		*/
		void		sz(int x, int y, char ch);
		/*! Setzt das Zeichen ch mit dem Farbenindex col an die Position (x,y).
			\brief Zeichen und Attribut setzen
		*/
		void		sza(int x, int y, char ch, int col);
		/*! Schreibt den String str an die Position (x,y). Die Attribute werden dabei nicht geändert.
			\brief String schreiben
		*/
		void		ss(int x, int y, const QString& str);
		/*! Schreibt den String str mit dem Farbenindex col an die Position (x,y)
			\brief String und Attribut schreiben
		*/
		void		ssa(int x, int y, const QString& str, int col);
		void		print(const QString& str);
		void		hot(int x, int y, const QString& str, int colnorm, int colinv);
	public:	// ---- Cursor-Funktionen ---------------------------------------------------------------------------------
 		void		cursor(Cursors mode);
		void		setCursorPos(int x, int y);
		void		getCursorPos(int& x, int& y);
	private:
		void		showWins();
		void		showFrame(bool refresh=true);
		void		showTitle(bool refresh=true);
	private:
		TVio&		m_Vio;
		_win_st*	m_Win;									//! Das Fenster-Handle
		_win_st*	m_Sub;									//! Das innere Fenster wegen Rahmen
		FrameType	m_Frame;
		int			m_FrameCol;
		QString		m_Title;
		TitlePos	m_TitlePos;
		int			m_TitleCol;
	};	
}

using namespace Hilevel;

#endif

#if 0
/****************************************************************************/
/* WIN.H                                                                    */
/* ------------------------------------------------------------------------ */
/* Definition der Fensterstruktur und der Funktionen zum Zugriff auf diese. */
/****************************************************************************/
 #include       "defs/Typedefs.h"                /* Grundlegende Datentypen */

 /* ----------- Typdefinition: ein Fenster -------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct                           /* Struktur eines Fensters */
 {
  WORD          wPosX;                           /* X-Position des Fensters (Links) */
  WORD          wPosY;                           /* Y-Position des Fenster (Oben) */
  WORD          wWidth;                          /* Breite des Fensters     */
  WORD          wHeight;                         /* Hoehe des Fensters      */
  WORD          wCurX;                           /* X-Position des Cursors  */
  WORD          wCurY;                           /* Y-Position des Cursors  */
  WORD*         pwBuffer;                        /* Puffer fuer den Hintergrund */
  CHAR*         pcTitle;                         /* Titel des Fensters      */
  INT           iTitlePos;                       /* Position des Titels     */
  INT           iFrame;                          /* Art des Rahmens         */
  WORD          wFlags;                          /* Die Fenster-Flags       */
  WORD          wAttrText;                       /* Attribut von normalem Text */
  WORD          wAttrFrame;                      /* Attribut des Fensterrahmens */
  WORD          wAttrTitle;                      /* Attribut des Fenstertitels */
  WORD          wAttrShadow;                     /* Attribut des Fensterschattens */
 } SWin;

 /* ----------- Konstanten fuer die Fensterflags -------------------------- */
 #define        WIN_FLG_SHADOW   BIT0            /* Schatten ist an         */
 #define        WIN_FLG_SAVE     BIT1            /* Hintergrund gesichert   */
 #define        WIN_FLG_ATTRIB   BIT4            /* User-Defined Attribute  */
 #define        WIN_FLG_1ST      BIT5            /* Fenster zum ersten Mal aktiviert */

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 SWin* CDECL    WinEinrichten   PARAM(( WORD, WORD, WORD, WORD ));
 VOID  CDECL    WinEntfernen    PARAM(( SWin* ));
 VOID  CDECL    WinAktivieren   PARAM(( SWin* ));
 VOID  CDECL    WinVerstecken   PARAM(( SWin* ));
 VOID  CDECL    WinSchattenEin  PARAM(( SWin* ));
 VOID  CDECL    WinSchattenAus  PARAM(( SWin* ));
 VOID  CDECL    WinSetAttrib    PARAM(( SWin*, WORD, WORD, WORD ));

 /* ----------- Funktionen fuer aktuelles Fenster ------------------------- */
 SWin* CDECL    WinGetAktivPwkb PARAM(( void ));
 VOID  CDECL    WinSwa          PARAM(( WORD, WORD, WORD, WORD, WORD ));
 VOID  CDECL    WinSwz          PARAM(( WORD, WORD, WORD, WORD, CHAR ));
 VOID  CDECL    WinSwza         PARAM(( WORD, WORD, WORD, WORD, CHAR, WORD ));
 INT   CDECL    WinPrintf       PARAM(( CHAR* pcFormat, CPPARGS ));
 VOID  CDECL    WinScrollUp     PARAM(( void ));
 VOID  CDECL    WinScrollDown   PARAM(( void ));

 VOID  CDECL    WinHot          PARAM(( WORD, WORD, CHAR*, WORD, WORD ));
 INT   CDECL    WinGetHotkey    PARAM(( CHAR* ));
 DECLEND

#endif
