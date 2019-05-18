/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTUTL.H                        Datum: 10.11.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Diese Datei enthlt die symbolischen Konstanten, Makros und           บ
  บ  Funktionsprototypen fr die Utilities der Toolbox.                    บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_UTIL_HEADER

#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#include <malloc.h>
#include <conio.h>
#include <direct.h>
#include <stdlib.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ            Konstanten fr die Sondertasten des IBM-PC                  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define ERW_CODE        0x100
#define SONDER_TASTE    0x200

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DIE FUNKTIONSTASTEN                             บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifdef NEVER  
#define T_F1    ( 59 |  ERW_CODE)
#define T_F2    ( 60 |  ERW_CODE)
#define T_F3    ( 61 |  ERW_CODE)
#define T_F4    ( 62 |  ERW_CODE)
#define T_F5    ( 63 |  ERW_CODE)
#define T_F6    ( 64 |  ERW_CODE)
#define T_F7    ( 65 |  ERW_CODE)
#define T_F8    ( 66 |  ERW_CODE)
#define T_F9    ( 67 |  ERW_CODE)
#define T_F10   ( 68 |  ERW_CODE)

#define T_S_F1   ( 84 | ERW_CODE)
#define T_S_F2   ( 85 | ERW_CODE)
#define T_S_F3   ( 86 | ERW_CODE)
#define T_S_F4   ( 87 | ERW_CODE)
#define T_S_F5   ( 88 | ERW_CODE)
#define T_S_F6   ( 89 | ERW_CODE)
#define T_S_F7   ( 90 | ERW_CODE)
#define T_S_F8   ( 91 | ERW_CODE)
#define T_S_F9   ( 92 | ERW_CODE)
#define T_S_F10  ( 93 | ERW_CODE)

#define T_C_F1   ( 94 | ERW_CODE)
#define T_C_F2   ( 95 | ERW_CODE)
#define T_C_F3   ( 96 | ERW_CODE)
#define T_C_F4   ( 97 | ERW_CODE)
#define T_C_F5   ( 98 | ERW_CODE)
#define T_C_F6   ( 99 | ERW_CODE)
#define T_C_F7   (100 | ERW_CODE)
#define T_C_F8   (101 | ERW_CODE)
#define T_C_F9   (102 | ERW_CODE)
#define T_C_F10  (103 | ERW_CODE)

#define T_A_F1   (104 | ERW_CODE)
#define T_A_F2   (105 | ERW_CODE)
#define T_A_F3   (106 | ERW_CODE)
#define T_A_F4   (107 | ERW_CODE)
#define T_A_F5   (108 | ERW_CODE)
#define T_A_F6   (109 | ERW_CODE)
#define T_A_F7   (110 | ERW_CODE)
#define T_A_F8   (111 | ERW_CODE)
#define T_A_F9   (112 | ERW_CODE)
#define T_A_F10  (113 | ERW_CODE)


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                      DER ZIFFERN-BLOCK                                 บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

#define T_HOME     (71 | ERW_CODE)
#define T_END      (79 | ERW_CODE)
#define T_PGUP     (73 | ERW_CODE)
#define T_PGDN     (81 | ERW_CODE)
#define T_LEFT     (75 | ERW_CODE)
#define T_RIGHT    (77 | ERW_CODE)
#define T_UP       (72 | ERW_CODE)
#define T_DOWN     (80 | ERW_CODE)
#define T_INS      (82 | ERW_CODE)
#define T_DEL      (83 | ERW_CODE)

#define T_C_HOME  (119 | ERW_CODE)
#define T_C_END   (117 | ERW_CODE)
#define T_C_PGUP  (132 | ERW_CODE)
#define T_C_PGDN  (118 | ERW_CODE)
#define T_C_LEFT  (115 | ERW_CODE)
#define T_C_RIGHT (116 | ERW_CODE)



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                      DER SCHREIBMASCHINENBLOCK                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define T_C_A         1
#define T_C_B         2
#define T_C_C         3
#define T_C_D         4
#define T_C_E         5
#define T_C_F         6
#define T_C_G         7
#define T_C_H         8
#define T_C_I         9
#define T_C_J        10
#define T_C_K        11
#define T_C_L        12
#define T_C_M        13
#define T_C_N        14
#define T_C_O        15
#define T_C_P        16
#define T_C_Q        17
#define T_C_R        18
#define T_C_S        19
#define T_C_T        20
#define T_C_U        21
#define T_C_V        22
#define T_C_W        23
#define T_C_X        24
#define T_C_Y        25
#define T_C_Z        26

#define T_A_A        (30 | ERW_CODE)
#define T_A_B        (48 | ERW_CODE)
#define T_A_C        (46 | ERW_CODE)
#define T_A_D        (32 | ERW_CODE)
#define T_A_E        (18 | ERW_CODE)
#define T_A_F        (33 | ERW_CODE)
#define T_A_G        (34 | ERW_CODE)
#define T_A_H        (35 | ERW_CODE)
#define T_A_I        (23 | ERW_CODE)
#define T_A_J        (36 | ERW_CODE)
#define T_A_K        (37 | ERW_CODE)
#define T_A_L        (38 | ERW_CODE)
#define T_A_M        (50 | ERW_CODE)
#define T_A_N        (49 | ERW_CODE)
#define T_A_O        (24 | ERW_CODE)
#define T_A_P        (25 | ERW_CODE)
#define T_A_Q        (16 | ERW_CODE)
#define T_A_R        (19 | ERW_CODE)
#define T_A_S        (31 | ERW_CODE)
#define T_A_T        (20 | ERW_CODE)
#define T_A_U        (22 | ERW_CODE)
#define T_A_V        (47 | ERW_CODE)
#define T_A_W        (17 | ERW_CODE)
#define T_A_X        (45 | ERW_CODE)
#define T_A_Y        (21 | ERW_CODE)
#define T_A_Z        (44 | ERW_CODE)

#define T_A_1         (120 | ERW_CODE)
#define T_A_2         (121 | ERW_CODE)
#define T_A_3         (122 | ERW_CODE)
#define T_A_4         (123 | ERW_CODE)
#define T_A_5         (124 | ERW_CODE)
#define T_A_6         (125 | ERW_CODE)
#define T_A_7         (126 | ERW_CODE)
#define T_A_8         (127 | ERW_CODE)
#define T_A_9         (128 | ERW_CODE)
#define T_A_10        (129 | ERW_CODE)
#define T_A_DASH      (130 | ERW_CODE)
#define T_A_GLEICH    (131 | ERW_CODE)

#define T_ESC           27
#define T_SPACE         32
#define T_TAB           T_C_I
#define T_SHIFT_TAB     (15 | ERW_CODE)
#define T_BACKSPACE     T_C_H
#define T_C_BACKSPACE   127
#define T_CTRL_PTRSC   (114 | ERW_CODE)
#define T_RETURN        13
#define T_SRETURN       13
#define T_CRETURN       10

#define T_RIGHT_SHIFT   (0x01 | SONDER_TASTE)
#define T_LEFT_SHIFT    (0x02 | SONDER_TASTE)
#define T_CTRL          (0x04 | SONDER_TASTE)
#define T_ALT           (0x08 | SONDER_TASTE)


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ            Konstanten um Rckgabe von UtlKbFlags() zu testen           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define RIGHT_SHIFT   0x01    /* 0000 0001 b */
#define LEFT_SHIFT    0x02    /* 0000 0010 b */
#define CTRL          0x04    /* 0000 0100 b */
#define ALT           0x08    /* 0000 1000 b */
#define SCROLL_LOCK   0x10    /* 0001 0000 b */
#define NUM_LOCK      0x20    /* 0010 0000 b */
#define CAPS_LOCK     0x40    /* 0100 0000 b */
#define INSERT_ON     0x80    /* 1000 0000 b */
#endif


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ          Parameter und Funktionsbestimmung fr UtlStopUhr()            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define UTL_START           0
#define UTL_STOP            1

#define TICKS_PRO_TAG       1573040
#define TICKS_PRO_SEK       18.20648267


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ   Konstanten Rahmentypen fr UtlZeigeRahmen(), UtlZeigeLinie() u.a.    บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define RT_EEEE     0x00
#define RT_EEED     0x01
#define RT_EEDE     0x02
#define RT_EEDD     0x03

#define RT_EDEE     0x04
#define RT_EDED     0x05
#define RT_EDDE     0x06
#define RT_EDDD     0x07

#define RT_DEEE     0x08
#define RT_DEED     0x09
#define RT_DEDE     0x0A
#define RT_DEDD     0x0B

#define RT_DDEE     0x0C
#define RT_DDED     0x0D
#define RT_DDDE     0x0E
#define RT_DDDD     0x0F

#define EINFACH     0
#define DOPPELT     1


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ              Rckgabewerte von UtlDateinameGueltig()                   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define DN_GUELTIG     0
#define DN_UNGUELTIG   1


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ              Makros und Konstanten fr die Tonerzeugung                บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define UTL_SEKUNDEN    0                           /* fr Zeitangaben in s.*/
#define UTL_TICKS       1                           /* fr Zeitangaben in t.*/

#define UtlTonAus()     UtlTon(0)

#define UtlSoundSek(wFrequenz,wDauer)   UtlTon(wFrequenz), \
                                        UtlPause(UTL_SEKUNDEN, wDauer), \
                                        UtlTonAus(),


#define UtlSoundTicks(wFrequenz,wDauer) UtlTon(wFrequenz), \
                                        UtlPause(UTL_TICKS, wDauer), \
                                        UtlTonAus()


#define UtlBeep()       UtlSoundTicks(200,2)




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ          Deklarationen im Kontext der Eventbearbeitung                 บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
typedef struct
{
    WORD    wArt;                                   /* Eventart             */
    WORD    wTaste;                                 /* gedrckte Taste      */
    WORD    wKbflags;                               /* Zustand der Tastatur */
    WORD    wButton;                                /* Zustand der Buttons  */
    WORD    wSpalte;                                /* Position des Maus-   */
    WORD    wZeile;                                 /* cursors              */
    WORD    wOption;                                /* Option bei Menman.  */
    LONG    lTicks;                                 /* Ticks zum Zeitpunkt  */
                                                    /* des Ereignisses      */
} EVENT;

typedef EVENT* PEVENT;

#define EVENT_NULL         0              /* m”gliche Werte im Element wArt */
#define EVENT_MOUSE_MOVE   1
#define EVENT_L_PRESS      2
#define EVENT_R_PRESS      3
#define EVENT_B_PRESS      4
#define EVENT_L_RELEASE    5
#define EVENT_R_RELEASE    6
#define EVENT_B_RELEASE    7
#define EVENT_TASTE        8
#define EVENT_ALT_PRESS    9
#define EVENT_ALT_RELEASE 10
#define EVENT_WAHL        11


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ           Makros und Konstanten fr Operationen auf Bit-Ebene          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define BIT0    0x0001
#define BIT1    0x0002
#define BIT2    0x0004
#define BIT3    0x0008
#define BIT4    0x0010
#define BIT5    0x0020
#define BIT6    0x0040
#define BIT7    0x0080
#define BIT8    0x0100
#define BIT9    0x0200
#define BIT10   0x0400
#define BIT11   0x0800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000

#define UtlBitTest(wVar,wBitmask)     ( ((wVar)&(wBitmask))==(wBitmask) )
#define UtlBitSet(wVar,wBitmask)      ( (wVar) |= (wBitmask) )
#define UtlBitDel(wVar,wBitmask)      ( (wVar) &= (~(wBitmask)) )

#define HIGHBYTE        0xFF00
#define LOWBYTE         0x00FF

#define UtlHighByte(wVar)       ((wVar) >> 8)       /* H”herwertiges Byte   */
#define UtlLowByte(wVar)        ((wVar) & 0x00FF)   /* Niederwertiges Byte  */




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                      verschiedene Makros                               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef __386__
#define UtlFmalloc(groesse)          _fmalloc(groesse)
#define UtlFfree(pointer)            _ffree(pointer)
#else
#define UtlFmalloc(groesse)          malloc(groesse)
#define UtlFfree(pointer)            free(pointer)
#endif
#define UtlMalloc(groesse)           malloc(groesse)
#define UtlFree(zeiger)              free(zeiger)
#ifndef __386__
#define UtlAlloc(typ)                ((typ *) calloc(1,sizeof(typ)))
#else
#define UtlAlloc(typ)                ((typ *) malloc(sizeof(typ)))
#endif
#define UtlOutpb(port,byte)          outp((port),(byte))
#define UtlOutpw(port,word)          outpw((port),(word))
#define UtlInpb(port)                inp((port))
#define UtlInpw(port)                inpw((port))
#define UtlTeileName(p,l,v,d,e)      _splitpath(p,l,v,d,e)
#define UtlIsUmlaut(c)  ( (c)=='' || (c)=='”' || (c)=='' ||   \
                          (c)=='A' || (c)=='' || (c)==''  )

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        FUNKTIONS-PROTOTYPEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL WORD  UtlAltCode        (WORD);
GLOBAL WORD  UtlTaste          (VOID);
GLOBAL WORD  UtlKbFlags        (VOID);
GLOBAL VOID  UtlEvent          (PEVENT);

GLOBAL WORD  UtlGross          (WORD);
GLOBAL WORD  UtlKlein          (WORD);
GLOBAL PSTR  UtlStrlwr         (PSTR);
GLOBAL PSTR  UtlStrupr         (PSTR);

GLOBAL VOID  UtlTon            (WORD);
GLOBAL VOID  UtlPause          (WORD, WORD);
GLOBAL WORD  UtlGetUhrTicks    (PLONG);
GLOBAL LONG  UtlStopUhr        (WORD);

GLOBAL VOID  UtlTypeString     (WORD, WORD, PSTR);
GLOBAL VOID  UtlTypeStringAtt  (WORD, WORD, PSTR, WORD);

GLOBAL VOID  UtlHWCursorOff    (VOID);
GLOBAL VOID  UtlHWCursorOn     (VOID);

GLOBAL VOID  UtlZeigeRahmen    (WORD, WORD, WORD, WORD, WORD, WORD);
GLOBAL VOID  UtlZeigeSchatten  (WORD, WORD, WORD, WORD);
GLOBAL VOID  UtlZeigeLinie     (WORD, WORD, WORD, WORD,
                                     WORD, WORD, WORD);

GLOBAL VOID  UtlClearRandom    (WORD);

GLOBAL WORD  UtlDosShell       (WORD, PSTR);

GLOBAL WORD  UtlGetDrive       (VOID);
GLOBAL VOID  UtlSetDrive       (WORD);

GLOBAL VOID  UtlSetNeuErrorHandler(WORD);
GLOBAL VOID  UtlSetAltErrorHandler(VOID);

GLOBAL BOOL  UtlDateinameGueltig  (PSTR);


#define CT_UTIL_HEADER 1
#endif /* von #ifndef CT_UTIL_HEADER */

