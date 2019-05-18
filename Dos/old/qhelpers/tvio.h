#ifndef				HILEVEL_TVIO_H
#define				HILEVEL_TVIO_H
#include			"hilevel/tcolors.h"
#include			<QString>

namespace Hilevel
{
	#define			KEY_RETURN		10
	#define			KEY_ESC			27

	typedef			QList<int>	KeyCodes;

	class			TVio
	{
	public:	// ---- ctor/dtor -----------------------------------------------------------------------------------------
		TVio();
		~TVio();
		void		init();
		void		done();
	public:	// ---- Statische Funktionen ------------------------------------------------------------------------------
		static void	debug(const QString& str, bool newline=true);
		static void	beep();
		static void	flash();
		static void	sleep(int msecs);
		static bool	hasColors();
		static int	getMaxCol();
 		static int	getMaxRow();
		static int	getMaxColor();
	public:
		void		doBackground();
		TColors&	getColors()
		{
			return m_Colors;
		}
		int			centerCol(int len=0)
		{
			return (getMaxCol()-len) / 2;
		}
		int			centerRow(int height=0)
		{
			return (getMaxRow()-height) / 2;
		}
	public:
		/*!	Löscht den Bildschirm. Hierbei bleibt die Hintergrundfarbe unangetastet.
		*/
		void		clear();
		void		gotoxy(int x, int y);
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
		void		status(const QString& str, int colnorm, int colinv);
		void		statusOff();
	private:
		TColors		m_Colors;
		bool		m_Init;									//!< Flag, ob init schon aufgerufen war
	};	
}

using namespace Hilevel;

#endif

#if 0
/****************************************************************************/
/* VIO.H                                                                    */
/* ------------------------------------------------------------------------ */
/* Definition der Funktionen zum Zugriff auf den PC-Bildschirm.             */
/****************************************************************************/
#ifndef         _VIO_

 #define        _VIO_

 /* ----------- Funktionstypen -------------------------------------------- */
 typedef VOID (CDECL *FVioSza)   PARAM(( WORD, WORD, CHAR, WORD ));
 typedef WORD (CDECL *FVioLza)   PARAM(( WORD, WORD ));
 typedef VOID (CDECL *FVioSs)    PARAM(( WORD, WORD, CHAR* ));
 typedef VOID (CDECL *FVioSsa)   PARAM(( WORD, WORD, CHAR*, WORD ));
 typedef VOID (CDECL *FVioSwa)   PARAM(( WORD, WORD, WORD, WORD, WORD ));
 typedef VOID (CDECL *FVioSwz)   PARAM(( WORD, WORD, WORD, WORD, BYTE ));
 typedef VOID (CDECL *FVioSwza)  PARAM(( WORD, WORD, WORD, WORD, BYTE, WORD ));
 typedef VOID (CDECL *FVioCopy)  PARAM(( WORD, WORD, WORD, WORD, WORD* ));
 typedef VOID (CDECL *FVioClear) PARAM(( void ));
 typedef VOID (CDECL *FVioScroll)PARAM(( WORD, WORD, WORD, WORD, WORD ));
 typedef VOID (CDECL *FVioDone)  PARAM(( void ));
 typedef VOID (CDECL *FVioPutp)  PARAM(( WORD, WORD, LONG ));
 typedef LONG (CDECL *FVioGetp)  PARAM(( WORD, WORD ));
 typedef VOID (CDECL *FVioBackgr) PARAM(( void ));

 /* ----------- Bildschirmdeskriptor -------------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct
 {
  INT           iMode;                           /* Aktueller Modus         */
  WORD          wMaxX;                           /* Grafik: X-Aufloesung    */
  WORD          wMaxY;                           /* Grafik: Y-Aufloesung    */
  BYTE*         bpChars;                         /* Grafik: Zeichentabelle  */
  BYTE*         bpChars2;                        /* Grafik: Zeichentabelle  */
  BYTE          bChHeight;                       /* Grafik: Zeichenhoehe    */
  WORD          wMaxCol;                         /* Anzahl Spalten          */
  WORD          wMaxRow;                         /* Anzahl Zeilen           */
  WORD          wFlags;                          /* Diverse Flags           */
  WORD          wColors;                         /* Anzahl Bits pro Farbe   */
  BYTE*         pbScreen;                        /* Bildschirmzeiger        */
  FVioLza       Lza;                             /* Zeichen/Attrib. lesen   */
  FVioSa        Sa;                              /* Attribut setzen         */
  FVioSz        Sz;                              /* Zeichen setzen          */
  FVioSza       Sza;                             /* Attribut mit Zeichen setzen */
  FVioSs        Ss;                              /* String schreiben        */
  FVioSsa       Ssa;                             /* String mit Attribut schreiben */
  FVioSwa       Swa;                             /* Fenster mit Attribut fuellen */
  FVioSwz       Swz;                             /* Fenster mit Zeichen fuellen */
  FVioSwza      Swza;                            /* Fenster mit Attribut und Zeichen fuellen */
  FVioCopy      Sb2w;                            /* Buffer auf Schirm schreiben */
  FVioCopy      Sw2b;                            /* Fensterinhalt speichern */
  FVioClear     Clear;                           /* Bildschirm loeschen     */
  FVioDone      Done;                            /* Aufloesungsfunktion     */
  FVioScroll    ScrollUp;                        /* Fensterinhalt nach oben scrollen */
  FVioScroll    ScrollDown;                      /* Fensterinhalt nach untern scrollen */
  FVioPutp      Putpixel;                        /* Grafik: Punkt setzen    */
  FVioGetp      Getpixel;                        /* Grafik: Punkt lesen     */
  FVioBackgr    Background;
 } SVio;

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 VOID  CDECL    VioInit         PARAM(( INT ));            /* Bildschirm initialisieren */
 VOID  CDECL    VioDone         PARAM(( void ));
 VOID  CDECL    VioSetMode      PARAM(( INT ));
 INT   CDECL    VioGetMode      PARAM(( void ));
 VOID  CDECL    VioStatus       PARAM(( CHAR*, WORD, WORD ));
 VOID  CDECL    VioBackground   PARAM(( void ));
#if( !defined UNIX )
 BYTE* CDECL    VioSetAdr       PARAM(( void ));           /* Bildadresse setzen      */
#endif
 DECLEND

 /* ----------- Mappings fuer Default-Fall -------------------------------- */
 #define        VioClear()                          VioDescr->Clear()
 #define        VioLza( x, y )                      VioDescr->Lza( x, y )
 #define        VioSa( x, y, attr )                 VioDescr->Sa( x, y, attr )
 #define        VioSz( x, y, ch )                   VioDescr->Sz( x, y, ch )
 #define        VioSza( x, y, ch, attr )            VioDescr->Sza( x, y, ch, attr )
 #define        VioSs( x, y, str )                  VioDescr->Ss( x, y, str )
 #define        VioSsa( x, y, str, attr )           VioDescr->Ssa( x, y, str, attr )
 #define        VioSwa( x1, y1, x2, y2, attr )      VioDescr->Swa( x1, y1, x2, y2, attr )
 #define        VioSwz( x1, y1, x2, y2, ch )        VioDescr->Swz( x1, y1, x2, y2, ch )
 #define        VioSwza( x1, y1, x2, y2, ch, attr ) VioDescr->Swza( x1, y1, x2, y2, ch, attr )
 #define        VioSb2w( x1, y1, x2, y2, buff )     VioDescr->Sb2w( x1, y1, x2, y2, buff )
 #define        VioSw2b( x1, y1, x2, y2, buff )     VioDescr->Sw2b( x1, y1, x2, y2, buff )
 #define        VioClear()                          VioDescr->Clear()
 #define        VioScrUp( x1, y1, x2, y2, attr )    VioDescr->ScrollUp( x1, y1, x2, y2, attr )
 #define        VioScrDown( x1, y1, x2, y2, attr )  VioDescr->ScrollDown( x1, y1, x2, y2, attr )
 #define        VioPutp( x, y, col )                VioDescr->Putpixel( x, y, col )
 #define        VioGetp( x, y )                     VioDescr->Getpixel( x, y )
 #define        VioBackground()                     VioDescr->Background()



#endif

#endif
