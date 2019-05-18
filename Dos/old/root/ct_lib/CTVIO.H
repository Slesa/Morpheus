/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTVIO.H                        Datum: 12.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ   Header-Datei fr die Funktionen zur Bildschirmausgabe                บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_VIDEO_HEADER

//#ifdef NEVER
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif
//#endif
//#include <TYPEDEFS.H>

#define MONO_SEG        0xB000                      /* Monochrom-Adapter    */
#define COLOR_SEG       0xB800                      /* Farb-Adapter CGA/EGA */

#define ANZEIGE         0                           /* Sichtbare Seite      */
#define SCHREIB_LESE    1                           /* Vernderbare Seite   */
#define INITIAL         2                           /* Initialisierung      */

#define MONOCHROM       7

#define VIA_BIOS        0                           /* IO ber BIOS-Funkt.  */
#define VIA_VRAM        1                           /* IO mit direktem Zu-  */
                                                    /* griff auf Videoram   */

#define VIDEOINT        0x10                        /* Video-Interruptvekor */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                                                                        บ
  บ             F U N K T I O N E N   D E S   INT  0x10                    บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SET_VIDEO_MODE      0x00
#define SET_CURSOR_TYPE     0x01
#define SET_CURSOR_POS      0x02
#define READ_CURSOR_POS     0x03
#define SEL_ACTIVE_PAGE     0x05
#define SCROLL_UP           0x06
#define SCROLL_DOWN         0x07
#define READ_CHAR_ATT       0x08
#define WRITE_CHAR_ATT      0x09
#define WRITE_CHAR          0x0A
#define GET_VIDEO_MODE      0x0F


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                                                                        บ
  บ             B I L D S C H I R M - A T T R I B U T E                    บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

#ifdef  IPC

/*              Textkonstanten fr den Monochrom-Modus                      */
#define INVERS          0x00
#define NORMAL          0x01
#define BLINK           0x02    /* CURRENTLY NOT SUPPORTED */
#define HELL            0x03    /* CURRENTLY NOT SUPPORTED */
#define UNTER           0x04                        /* unterstr. Zeichen    */
                                                    /* intens. Darstellung  */
#define MATT_INVERS     0x78                        /* matt invers          */

/*                 Textkonstanten fr die Farb-Modi                         */

#define WEISS           0x00
#define SCHWARZ         0x01
#define BLAU            0x01
#define GRUEN           0x01
#define KOBALT          0x01
#define ROT             0x01
#define VIOLETT         0x01
#define BRAUN           0x01
#define GRAU            0x01
#define HELLBLAU        0x01
#define HELLGRUEN       0x01
#define HELLKOBALT      0x01
#define HELLROT         0x01
#define HELLVIOLETT     0x01
#define GELB            0x01
#define HELLWEISS       0x01

#else //IPC

#define NORMAL          0x07                        /* Normal Darstellung   */
#define UNTER           0x01                        /* unterstr. Zeichen    */
#define HELL            0x0F                        /* Intens. Darstellung  */
#define HELL_UNTER      0x09                        /* unterstr. Zeichen in */
                                                    /* intens. Darstellung  */
#define INVERS          0x70                        /* Inverse Darstellung  */
#define MATT_INVERS     0x78                        /* matt invers          */

#define SCHWARZ         0x00
#define BLAU            0x01
#define GRUEN           0x02
#define KOBALT          0x03
#define ROT             0x04
#define VIOLETT         0x05
#define BRAUN           0x06
#define WEISS           0x07
#define GRAU            0x08
#define HELLBLAU        0x09
#define HELLGRUEN       0x0a
#define HELLKOBALT      0x0b
#define HELLROT         0x0c
#define HELLVIOLETT     0x0d
#define GELB            0x0e
#define HELLWEISS       0x0f
#endif

/*                   Textkonstanten fr alle Modi                           */

#define BLINKEN         0x80                        /* blinkendes Zeichen   */

#define BLANK           0x20
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                                                                        บ
  บ             F U N K T I O N S  -  P R O T O T Y P E N                  บ
  บ                                                                        บ
  บ     Die Dokumentation der Namensvergabe befindet sich in ฏvideo.cฎ     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSeite    ( WORD, WORD );
VOID     VioSa    ( WORD, WORD, WORD );
WORD     VioLa    ( WORD, WORD );
VOID     VioSz    ( WORD, WORD, CHAR );
CHAR     VioLz    ( WORD, WORD );
VOID     VioSza   ( WORD, WORD, BYTE, WORD );
WORD     VioLza   ( WORD, WORD );
VOID     VioSs    ( WORD, WORD, PSTR );
VOID     VioSsa   ( WORD, WORD, PSTR, WORD );
VOID     VioSpa   ( WORD );
VOID     VioSpz   ( CHAR );
VOID     VioSpza  ( CHAR, WORD );

VOID     VioSwa   ( WORD, WORD, WORD, WORD, WORD);
VOID     VioSwz   ( WORD, WORD, WORD, WORD, CHAR);
VOID     VioSwza  ( WORD, WORD, WORD, WORD, CHAR, WORD);
VOID     VioSb2w  ( WORD, WORD, WORD, WORD, WORD* );
VOID     VioSw2b  ( WORD, WORD, WORD, WORD, WORD* );

VOID     VioSetMode       (WORD);
WORD     VioGetMode       (VOID);

VOID     VioGetCursor( WORD*, WORD*, WORD*, WORD* );
VOID     VioSetCursorTyp  (WORD, WORD);
VOID     VioSetCursorPos  (WORD, WORD);
//VOID     VioGetCursorPos  (WORD*, WORD* );



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                                                                        บ
  บ                            M A K R O S                                 บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

#ifdef IPC
#define _POS_CURSOR(spalte,zeile,seite)   fSetCursor( (spalte), (zeile) )
#else
#ifndef __386__
#define _POS_CURSOR(spalte,zeile,seite)   { regs.h.ah = SET_CURSOR_POS; \
                                            regs.h.bh = (BYTE) seite; \
                                            regs.h.dh = (BYTE) zeile; \
                                            regs.h.dl = (BYTE) spalte;\
                                           int86(0x10, &regs, &regs);   }
#else
#define _POS_CURSOR(spalte,zeile,seite)   { regs.h.ah = SET_CURSOR_POS; \
                                            regs.h.bh = (BYTE) seite; \
                                            regs.h.dh = (BYTE) zeile; \
                                            regs.h.dl = (BYTE) spalte;\
                                           int386(0x10, &regs, &regs);   }
#endif
#endif

#ifdef IPC
  #define VH(vorne,hinten)    ((vorne))
#else
  #define VH(vorne,hinten)    ((hinten<<4)|(vorne))
#endif

#endif

#define         VIO_INITIALIZED    1
#define         VIO_MONOCHROM      2

#define CT_VIDEO_HEADER 1
