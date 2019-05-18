/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlTaste                       Datum: 16.08.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion liest mit einem Aufruf der           บ
  บ                    Funktion 0x08 des INT 0x21 die Tastatureingaben.    บ
  บ                    Wenn der Funktionsaufruf im AL-Register den         บ
  บ                    Wert '\0' zurckliefert, wird die Eingabe einer     บ
  บ                    Taste mit einem erweiterten Code signalisiert, und  บ
  บ                    die DOS-Funktion ein zweites Mal aufgerufen.        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD    die eingelesene Taste                       บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <DEFS.H>
#include <conio.h>            /* fr kbhit()                                */
#include <dos.h>
#include <process.h>
#include <stdio.h>
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>          /* Standard-Datentypen                        */
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif

#undef CTRL
#undef ALT
#include "LEDS.H"

// Dieser Flag ist TRUE = 1 , wenn eine MFS-Tastatur (normale PC-Tastatur)
// angeschlossen ist, sonst ist er FALSE

int Utl_MF_TASTATUR=1;
INT  ShiftEbenenStatus=0;

PRIVATE WORD Hole_Taste_Von_Scheiss_Siemens_Tastatur( void );
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

WORD AltUtlTaste (VOID)
{
    WORD wEingabe;
    static int DieNull=0;
    if( DieNull!=0 ) { DieNull=0;return( '0' ); }
    if (kbhit())
    {
      if((wEingabe=bdos(0x08,0,0)&LOWBYTE) != '\0')
         return(wEingabe);
      else
      {
       wEingabe =bdos(0x08,0,0)&LOWBYTE;
       if( wEingabe==242 ) { DieNull=1; return( '0' ); }
       return( wEingabe | ERW_CODE);
      }
    }
    return(0);
}

PRIVATE WORD Hole_Taste_Von_Scheiss_Wmf_Tastatur( void )
{
 INT  wert;
 WORD taste=0;
 wert=inp(0x300); // Status Pollen
 if((wert&0x80)!=0x80) // Wenn Kein Fehler
 {
  if((wert&0x04)==0x04) // Und Zeichen available
  {
   taste=inp(0x305);	// Taste holen
  }
 }
 if(taste!=0)
 {
  /* Taste auf WMF-Keyboard wurde gedrueckt */
  switch(taste)
  {
   /* Dies ist der obere Eingabeblock */
   case 89:	 taste=T_F1;	break;   /* 1. Zeile */
   case 90:	 taste=0;		break;
   case 91:	 taste=0;		break;
   case 92:  taste=T_F10;	break;			// F10	 Ende
   case 93:	 taste=T_F2;	break;   /* 2. Zeile */
   case 94:  taste=0;		break;
   case 95:  taste='&';		break;
   case 96:	 taste='$';		break;
   case 97:	 taste=T_F3;	break;   /* 3. Zeile */
   case 98:	 taste=0;		break;
   case 99:	 taste=0;		break;
   case 100: taste=T_F7;	break;
   case 101: taste=T_F4;	break;   /* 4. Zeile */
   case 102: taste=0;		break;
   case 103: taste=0;		break;
   case 104: taste=T_RIGHT;	break;
   case 105: taste=T_F5;	break;   /* 5. Zeile */
   case 106: taste=T_PGUP;  break;
   case 107: taste=T_UP;	break;
   case 108: taste=T_LEFT;  break;   /* 6. Zeile */  // Korrektur
   case 109: taste=T_F6;	break;			// Splitt
   case 110: taste=T_PGDN;  break;
   case 111: taste=T_DOWN;  break;
   case 112: taste=T_ESC;	break;			// Escape
   /* Dies ist der untere Eingabeblock */
   /* Die Shifttasten */
   case 116:  if(ShiftEbenenStatus==1)
   			     ShiftEbenenStatus=0;
   			  else
   			     ShiftEbenenStatus=1;
              taste=0;
   			     		    break;			// Shift Grün
   case 120:  if(ShiftEbenenStatus==2)
   			     ShiftEbenenStatus=0;
   			  else
   			     ShiftEbenenStatus=2;
              taste=0;
   			     		    break;			// Shift Rot
   /* Der Ziffernblock von 0-9 */
   case 126: taste='0'; 	break;
   case 121: taste='1'; 	break;
   case 122: taste='2'; 	break;
   case 123: taste='3'; 	break;
   case 117: taste='4'; 	break;
   case 118: taste='5'; 	break;
   case 119: taste='6'; 	break;
   case 113: taste='7'; 	break;
   case 114: taste='8'; 	break;
   case 115: taste='9'; 	break;
   case 125: taste=T_BACKSPACE;	break;		// CLR ist Backspace
   case 127: taste='.'; 	break;
   case 124:								// Anzahl ist gleich Return
   case 128: taste=T_RETURN; break;			// Die Return-Taste
   default: /* Schnelltaste */
//    if(ShiftEbenenStatus==0)
    {
     if((taste>=1)&&(taste<=26))
     {
      taste=taste-1+'a';
     }
     else
     {
      if((taste>=27)&&(taste<=52))
      {
       taste=taste-27+'A';
      }
      else
      {
       if(taste<=88)
       {
        taste=taste-53+128;
       }
      }
     } // End of else Schnelltaste Kleinbuchstaben
    }
#ifdef NEVER
    if(ShiftEbenenStatus==1)
    {
     if((taste>=1)&&(taste<=88))
     {
      taste=163+taste;			// Tastencodes von 128-162 sind Schnelltasten ohne Shift
     }
    }
    if(ShiftEbenenStatus==2)
    {
     if((taste>=1)&&(taste<=88))
     {
      taste=251+taste;          // Tastencodes von 163-251 sind Schnelltasten Shift grün ->
      							// codes von 252-339
     }
    }
#endif
   break;
  } // End of switch
  UtlPause(1,1);
 } // End of if(taste!=0)
 if(taste==0)
  taste=AltUtlTaste();
// if(taste!=0) printf("Tastencode: %d\n",taste);
 return(taste);
}

PRIVATE WORD Hole_Taste_Von_Scheiss_Siemens_Tastatur( void )
{
  SRegs         regs;
  INT           scan;
  INT           keyb;
  if( !kbhit() ) return( 0 );
  IntSetAH( regs, 0x10 );
  Interrupt( 0x16, &regs );
  scan = IntGetAH( regs );
  keyb = IntGetAL( regs );
  if( keyb=='!' )  return( '!' );
  if( keyb==0x00 ) return( scan|0x100 );
  if( keyb==0xE0 ) return( scan|0x200 );
  if( scan==0xE0 ) return( keyb|0x300 );

//   if( scan==0xE0) return( taste|ERW_CODE );
//   if( scan==0x00) return( taste|SONDER_TASTE );
//   wRet = scan&0xFF;
   return( scan );
}

WORD MyAltUtlTaste (VOID)
/* AltUtlTaste mit ganz langem Timeout */
{
    WORD wReturn;
    INT  iCount=0;
    do
    {
        wReturn=AltUtlTaste();
        if(((++iCount)%100)==0) UtlPause(UTL_TICKS,1);
    } while((wReturn==0) && (iCount<1000));
    return(wReturn);
}

#if( defined OMRON )
int OmronTastatur = -1; // Adresse einer(!) zuschaltbaren IMC-Tastatur
                        // Vorbelegung: Kein main aktiv -> Alle Tastendruecke annehemen
                        // bei 0 wird kein Tastendruck angenommen, bei jedem
                        // anderen Wert wird versucht, von dieser Adresse
                        // eine Taste zu lesen
#endif

VOID SetUtlTastenFlag(int flag)
{
   Utl_MF_TASTATUR=flag;
}

// EINGEFGT VON DIRK AUS FDS-LIBRARY
// ********************** Tastatur-Layout 1 *******************************
//   Layout fr erkannte Codes
// ------------------------------------------------------------------------

//     1     2     3     4     5     6     7     8     9     10    11    12
//  ษอออออหอออออหอออออหอออออหอออออหอออออหอออออหอออออหอออออหอออออหอออออหอออออป
//  บ 001 บ     บ     บ     บ 073 บ 08F บ 074 บ 029 บ 02B บ 03A บ 045 บ 046 บ
//0!บ ENDEบ --- บ --- บ --- บ  "  บ  '  บ  `  บ  ~  บ  _  บ --- บ --- บ --- บ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 03B บ 03C บ 03D บ 03E บ 03F บ 040 บ 041 บ 042 บ 043 บ 044 บ 085 บ 086 บ
//1!บ  a  บ  b  บ  c  บ  d  บ  e  บ  f  บ  g  บ  h  บ  i  บ  j  บ  k  บ  l  บ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 054 บ 055 บ 056 บ 057 บ 058 บ 059 บ 05A บ 05B บ 05C บ 05D บ 087 บ 088 บ
//2!บ  m  บ  n  บ  o  บ  p  บ  q  บ  r  บ  s  บ  t  บ  u  บ  v  บ  w  บ  x  บ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 05E บ 05F บ 060 บ 061 บ 062 บ 063 บ 064 บ 065 บ 066 บ 067 บ 089 บ 08A บ
//3!บ  y  บ  z  บ  A  บ  B  บ  C  บ  D  บ  E  บ  F  บ  G  บ  H  บ  I  บ  J  บ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 002 บ 003 บ 004 บ 005 บ 006 บ 007 บ 008 บ 009 บ 00A บ 00B บ 00C บ 00D บ
//4!บ  K  บ  L  บ  M  บ  N  บ  O  บ  P  บ  Q  บ  R  บ  S  บ  T  บ  U  บ  V  บ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 010 บ 011 บ 012 บ 013 บ 014 บ 015 บ 016 บ 017 บ 018 บ 019 บ 01A บ 01B บ
//5!บ  W  บ  X  บ  Y  บ  Z  บ    บ  ”  บ    บ    บ    บ    บ  แ  บ  @  บ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 01E บ 01F บ 020 บ 021 บ 022 บ 023 บ 024 บ 025 บ 026 บ 027 บ 028 บ 00E บ
//6!บ  [  บ  ]  บ  {  บ  }  บ  (  บ  )  บ  ?  บ  F1 บ  F2 บ  F3 บ  F4 บ  F5 บ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 02C บ 02D บ 02E บ 02F บ 030 บ 031 บ 032 บ 033 บ 034 บ 035 บ 052 บ 053 บ
//7 บ  #  บ  /  บ  |  บ  \  บ  <  บ  >  บ  !  บ  F6 บ AUSWบBACKSบ  UP บ DOWNบ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 068 บ 069 บ 06A บ 06B บ 06C บ 047 บ 049 บ 047 บ 048 บ 049 บ 04A บ 04A บ
//8 บ  &  บ  *  บ  .  บ  ,  บ  +  บ HOMEบ PGUPบ  7  บ  8  บ  9  บ ESC บ ESC บ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 06D บ 06E บ 06F บ 070 บ 071 บ 04F บ 051 บ 04B บ 04C บ 04D บ 04E บ 04E บ
//9 บ  $  บ  %  บ  :  บ  ;  บ  -  บ END บ PGDNบ  4  บ  5  บ  6  บ KORRบ KORRบ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 01D บ 00F บ 08B บ 08C บ 077 บ 048 บ 08D บ 04F บ 050 บ 051 บ 037 บ 037 บ
//10บ --- บ  =  บ TAB บ TAB บ INS บ  UP บ DEL บ  1  บ  2  บ  3  บ HELPบ HELPบ
//  ฬอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออฮอออออน
//  บ 02A บ 038 บ 039 บ 084 บ 04B บ 050 บ 04D บ 052 บ 052 บ 053 บ 01C บ 01C บ
//11บ --- บ --- บSPACEบSPACEบRIGHTบ DOWNบ LEFTบ  0  บ  0  บ  .  บ RET บ RET บ
//  ศอออออสอออออสอออออสอออออสอออออสอออออสอออออสอออออสอออออสอออออสอออออสอออออผ

// Gastro-abhngige Tastatur-Codes
#define T_KORR        T_LEFT
#define T_HILFE       T_RIGHT
#define T_AUSWERT     '/'
#define T_ENDE        '*'
#define T_NONE        0xFFFF


static unsigned int IPC_TASTEN[0x75]
       = {
           T_NONE,          // Diesen Code gibt's nicht
           T_ENDE,          // 001   01B   ESC
           'K',             // 002   031   1
           'L',             // 003   032   2
           'M',             // 004   033   3
           'N',             // 005   034   4
           'O',             // 006   035   5
           'P',             // 007   036   6
           'Q',             // 008   037   7
           'R',             // 009   038   8
           'S',             // 00A   039   9
           'T',             // 00B   030   0
           'U',             // 00C   02D   -
           'V',             // 00D   03D   =
           T_F5,            // 00E   008   BACK SPACE
           '=',             // 00F   009   TAB
           'W',             // 010   071   q
           'X',             // 011   077   w
           'Y',             // 012   065   e
           'Z',             // 013   072   r
           '',             // 014   074   t
           '”',             // 015   079   y
           '',             // 016   075   u
           '',             // 017   069   i
           '',             // 018   06F   o
           '',             // 019   070   p
           'แ',             // 01A   05B   [
           '@',             // 01B   05D   ]
           T_RETURN,        // 01C   00D   RETURN
           T_NONE,          // 01D   ---   CTRL
           '[',             // 01E   061   a
           ']',             // 01F   073   s
           '{',             // 020   064   d
           '}',             // 021   066   f
           '(',             // 022   067   g
           ')',             // 023   068   h
           '?',             // 024   06A   j
           T_F1,            // 025   06B   k
           T_F2,            // 026   06C   l
           T_F3,            // 027   03B   ;
           T_F4,            // 028   027   ,
           '^',             // 029   060   '
           T_NONE,          // 02A   ---   SHIFT
           '_',             // 02B   05C   QUERSTRICH
           '#',             // 02C   07A   z
           '/',             // 02D   078   x
           '|',             // 02E   063   c
           '\\',            // 02F   076   v
           '<',             // 030   062   b
           '>',             // 031   06E   n
           '!',             // 032   06D   m
           T_F6,            // 033   02C   ,
           T_AUSWERT,       // 034   02E   .
           8,               // 035   02F   /
           T_NONE,          // 036   ---   FEHLT
           T_HILFE,         // 037   02A   =
           T_NONE,          // 038   ---   ALT
           T_SPACE,         // 039   020   SPACE
           T_NONE,          // 03A   ---   CAPS-LOCK
           'a',             // 03B   000   F1
           'b',             // 03C   000   F2
           'c',             // 03D   000   F3
           'd',             // 03E   000   F4
           'e',             // 03F   000   F5
           'f',             // 040   000   F6
           'g',             // 041   000   F7
           'h',             // 042   000   F8
           'i',             // 043   000   F9
           'j',             // 044   000   F10
           T_NONE,          // 045   ---   NUM-LOCK
           T_NONE,          // 046   ---   SCROLL-LOCK
           T_HOME,          // 047   000   HOME
//         '7',             // 047   037   7
           T_UP,            // 048   000   CURSOR UP
//         '8',             // 048   038   8
           T_PGUP,          // 049   000   PAGE UP
//         '9',             // 049   039   9
           T_ESC,           // 04A   02D   -
           T_LEFT,          // 04B   000   CURSOR LEFT
//         '4',             // 04B   034   4
           '5',             // 04C   035   bzw 000 (NUM)
           T_RIGHT,         // 04D   000   CURSOR RIGHT
//         '6',             // 04D   036   6
           T_KORR,          // 04E   02B   +
           T_END,           // 04F   000   END
//         '1',             // 04F   031   1
           T_DOWN,          // 050   032   CURSOR DOWN
//         '2',             // 050   032   2
           T_PGDN,          // 051   000   PAGE DOWN
//         '3',             // 051   033   3
           T_UP,            // 052   000   INSERT
//         '0',             // 052   030   0
           T_DOWN,          // 053   000   DELETE
//         '.',             // 053   02E   .
           'm',             // 054   000   SHIFT F1
           'n',             // 055   000   SHIFT F2
           'o',             // 056   000   SHIFT F3
           'p',             // 057   000   SHIFT F4
           'q',             // 058   000   SHIFT F5
           'r',             // 059   000   SHIFT F6
           's',             // 05A   000   SHIFT F7
           't',             // 05B   000   SHIFT F8
           'u',             // 05C   000   SHIFT F9
           'v',             // 05D   000   SHIFT F10
           'y',             // 05E   000   CTRL  F1
           'z',             // 05F   000   CTRL  F2
           'A',             // 060   000   CTRL  F3
           'B',             // 061   000   CTRL  F4
           'C',             // 062   000   CTRL  F5
           'D',             // 063   000   CTRL  F6
           'E',             // 064   000   CTRL  F7
           'F',             // 065   000   CTRL  F8
           'G',             // 066   000   CTRL  F9
           'H',             // 067   000   CTRL  F10
           '&',             // 068   000   ALT   F1
           '*',             // 069   000   ALT   F2
           '.',             // 06A   000   ALT   F3
           ',',             // 06B   000   ALT   F4
           '+',             // 06C   000   ALT   F5
           '$',             // 06D   000   ALT   F6
           '%',             // 06E   000   ALT   F7
           ':',             // 06F   000   ALT   F8
           ';',             // 070   000   ALT   F9
           '-',             // 071   000   ALT   F10
           T_NONE,          // 072         FEHLT
           '\"',             // 073   000   CTRL  4
           '`',             // 074   000   CTRL  6
        };

// ***************************************************************************
// * Funktion Tastenlayout der IPC-Tastatur abbilden                         *
// * ----------------------------------------------------------------------- *
// * Gendert 26.05.94 zur Anpassung an IPC (Auba)                           *
// ***************************************************************************

WORD Hole_Taste_Von_Scheiss_IPC_Tastatur ( void )
{
  // --------------------- ACHTUNG --------------------------------------
  // Wir umgehen smtliche Tcken des DOS-Tastaturtreiber-Gespanns,
  // wenn wir uns eine Ebene Tiefer in die Katakomben des BIOS begeben.
  // Das liefert nmlich Scan-Codes und die sind (fast) eindeutig!
  // --------------------------------------------------------------------

  unsigned char taste;               // ASCII-Codierung der Taste
  unsigned char scan;                // Scan-Code der Taste
  unsigned int  ret;                 // Rckgabewert der Funktion

    ClrFlag( NUMLOCK );     // NUM-LOCK aus!

    // ber BIOS testen, ob Zeichen da und Codes einlesen
    _asm { mov ah,0x11               // Funktion 11: Erw. Zeichen vorhanden ?
           int 0x16                  // des Tastatur-Interrupts
            jnz YES
        }
    return 0;                        // Nein
   YES:                              // Hier ist ein Zeichen da

      _asm { mov ah,0x10             // Funktion 10: Erweitertes Zeichen auslesen
             int 0x16                // des Tastatur-Interrupts
             mov scan,ah             // Scan-Code der Taste
             mov taste,al            // ASCII-Wert (0xE0 bei Sonderzeichen)
           }

      if( scan>=0x77 )               // Tabelle kleiner machen
      {
        switch( scan )
        {                            // Umschalten der Tastaturen
          case 0xE0: Utl_MF_TASTATUR=1; return 0;
          case 0x77: return T_INS;   // INSERT
          case 0x84: return T_SPACE; // CTRL-F9
          case 0x85: return 'k';     // F11
          case 0x86: return 'l';     // F12
          case 0x87: return 'w';     // SHift F11
          case 0x88: return 'x';     // Shift F12
          case 0x89: return 'I';     // CTRL  F11
          case 0x8A: return 'J';     // CTRL  F12
          case 0x8B: return T_TAB;   // ALT   F11
          case 0x8C: return T_TAB;   // ALT   F12
          case 0x8D: return T_DEL;   // CTRL 8
          case 0x8F: return '๏';     // CTRL 5
          default:   return 0;       // Nicht belegt
        }
      }

      switch( scan )                 // Doppelte Scan-Codes rausfiltern
      {                              // Bei Taste=0 ist's Sonderzeichen
        case 0x47:  ret = (taste==0) ? ('7') : (IPC_TASTEN[scan]); break;
        case 0x48:  ret = (taste==0) ? ('8') : (IPC_TASTEN[scan]); break;
        case 0x49:  ret = (taste==0) ? ('9') : (IPC_TASTEN[scan]); break;
        case 0x4B:  ret = (taste==0) ? ('4') : (IPC_TASTEN[scan]); break;
        case 0x4D:  ret = (taste==0) ? ('6') : (IPC_TASTEN[scan]); break;
        case 0x4F:  ret = (taste==0) ? ('1') : (IPC_TASTEN[scan]); break;
        case 0x50:  ret = (taste==0) ? ('2') : (IPC_TASTEN[scan]); break;
        case 0x51:  ret = (taste==0) ? ('3') : (IPC_TASTEN[scan]); break;
        case 0x52:  ret = (taste==0) ? ('0') : (IPC_TASTEN[scan]); break;
        case 0x53:  ret = (taste==0) ? ('.') : (IPC_TASTEN[scan]); break;
        default:    if( scan<=0x74 )   // Zugriff auf's Nirvana?
                    {
                      ret = (IPC_TASTEN[scan]);
                    }
                    else               // wird nicht untersttzt
                      ret = T_NONE;
                    break;
      }

      if( ret!=T_NONE ) return ret;   // Taste definiert ?
      else return 0;                  // Nein -> Keine Taste
}
// BIS HIER EINGEFGT VON DIRK AUS FDS-LIBRARY
BOOL UtlKeyboardKeylock = FALSE;
CHAR UtlKeyboardHeader = 2;
CHAR UtlKeyboardTrailer = 4;
LONG UtlKeyboardKey = -1L;
//BOOL UtlKeyboardNull = FALSE;
BOOL UtlInKeylock = FALSE;
INT  UtlKeyStart  = 0;

WORD UtlTaste (VOID)
{
  // --------------------- ACHTUNG --------------------------------------
  // Wir umgehen smtliche Tcken des DOS-Tastaturtreiber-Gespanns,
  // wenn wir uns eine Ebene Tiefer in die Katakomben des BIOS begeben.
  // Das liefert nmlich Scan-Codes und die sind (fast) eindeutig!
  // --------------------------------------------------------------------
  INT ret;
  if( Utl_MF_TASTATUR==1 )
  {
     ret = AltUtlTaste();
  }

  // Hier ist der Wert != 1
  if( Utl_MF_TASTATUR==2 )
  {
      ret = Hole_Taste_Von_Scheiss_IPC_Tastatur();
  }

  if( Utl_MF_TASTATUR==3 )
  {
      ret=Hole_Taste_Von_Scheiss_Siemens_Tastatur();
  }
  if( Utl_MF_TASTATUR==4 )
  {
      ret=Hole_Taste_Von_Scheiss_Wmf_Tastatur();
  }
  if( !UtlInKeylock && UtlKeyboardKeylock && (ret==UtlKeyboardHeader) )
  {
   char temp[20];
   int count = 0;
   int ret = 0;
   UtlInKeylock = TRUE;
   for( ;; )
   {
    ret = UtlTaste();
    if( ret==0 || (ret=='0' && count<2) )
     continue;
    if( ret==UtlKeyboardTrailer )
     break;
//    if( UtlKeyboardNull && ret=='0' )
//     continue;
    if( count<10 )
     temp[count++] = ret;
   }
   temp[count] = 0;
   if( count )
    sscanf( temp+UtlKeyStart, "%lx", &UtlKeyboardKey);
   else
    UtlKeyboardKey = -1L;
   if( UtlKeyboardKey==0 )
    UtlKeyboardKey = -1L;
   UtlInKeylock = FALSE;
   return 0;
  }
  return ret;
}

#ifdef NEVER
#include <stdio.h>
void main()
{
  int ch=0;

  SetUtlTastenFlag(0);

  while( ( ch = UtlTaste() ) != T_ESC )
  {
    /* switch( ch )
    {
      case T_F1: printf("F1 "); break;
      case T_UP: printf("UP "); break;
    }
     */

    if( ch!=0 ) printf("%x %c\n", ch, ch );
  }
}
#endif
