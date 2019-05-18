/****************************************************************************/
/* COLORDEF.H                                                               */
/* ------------------------------------------------------------------------ */
/* Definition der Farben fuer die Fensterverwaltung.                        */
/****************************************************************************/
#ifndef			_COLORDEF_

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

 /* ----------- Textkonstanten fÅr alle Modi ------------------------------ */
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

 /* ----------- Textkonstanten fÅr alle Modi ------------------------------ */
	#define		BLINKEN				0x80

	#endif

#endif
