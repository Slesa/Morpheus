/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        MSMAUS.C                       Datum: 18.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Diese Datei enthlt die Grundfunktionen zur Untersttzung der         บ
  บ  Microsoft(TM)-Maus.                                                   บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>
#include <UTL.H>
#include <dos.h>
#include <INTERRPT.H>
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_MAUS_HEADER
#include <ctmsm.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif

// hier die konstatnten und funktionen fuer den MAAS Touchscreentreiber

#define MELDUNG_INFO           1

#define MAAS_TOUCH_ID          'T'     // kennung des Touchtreibers
#define MAAS_TOUCH_IRQ         0x60    // IRQ des Touchtreibers

#define MAAS_TOUCH_SETRESULT   0x12    // funktion zum setzen der Aufloesung
#define MAAS_TOUCH_GETPOS      0x06    // liefert xypos und buttonstatus
#define MAAS_TOUCH_SETMODE     0x13    // setzt den Touchscreen in div. Modi
#define MAAS_TOUCH_SETKEYCLICK 0x20    // klicken aus an
#define MAAS_TOUCH_RESET       0x00    // rsetiert den Treiber
#define MAAS_TOUCH_XRES        79
#define MAAS_TOUCH_YRES        24
#define MAAS_TOUCH_TRACKMODE   1
#define MAAS_TOUCH_ENTERMODE   2
#define MAAS_TOUCH_EXITMODE    3
#define MAAS_TOUCH_COMBINEMODE 4

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define MAUS_INT             0x33                  /* Interrupt-Nummer      */
#define MSM_RESET_STATUS     0x00                  /* verwendete Funktionen */
#define MSM_SHOW_CURSOR      0x01                  /*     des Maus-INT      */
#define MSM_HIDE_CURSOR      0x02
#define MSM_GET_B_STATUS_POS 0x03
#define MSM_SET_POSITION     0x04
#define MSM_GET_B_PRESS      0x05
#define MSM_GET_B_RELEASE    0x06
#define MSM_SET_MINMAX_HOR   0x07
#define MSM_SET_MINMAX_VER   0x08
#define MSM_SET_TXT_CURSOR   0x0A
#define MSM_GET_MOTION       0x0B
#define MSM_SET_RATIO        0x0F
#define MSM_SET_THRESHOLD    0x13
#define MSM_STORAGE_REQU     0x15
#define MSM_SAVE_DRIVER      0x16
#define MSM_RESTORE_DRIVER   0x17
#define MSM_SET_CRT_PAGE     0x1D
#define MSM_GET_CRT_PAGE     0x1E

#define MSM_SW_CURSOR           0
#define MSM_HW_CURSOR           1

BOOL boTouchscreenMain = 0;
BOOL boInTableOrArtikelTouch = FALSE;
BOOL boMaasTouchscreenOnline = FALSE;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL BOOL  boMausInitialisiert_m = 0;             /* Flags - initialisiert*/
MGLOBAL BOOL  boMsmTreiberda_m      = 0;             /*       - Treiber da   */
MGLOBAL BOOL  boTextMode_m          = MSM_TEXT_MODUS;/*       - Koord. Rckg.*/
MGLOBAL SWORD swKopieCursorFlag_m   = 0;             /* Kopie des Cursorflag */
MGLOBAL FPBYTE fpbBuffer_m          = 0L;


VOID MaasKeyClick( BOOL );

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        FUNKTIONS-DEFINITIONEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmInit                        Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion berprft, ob im System die Maus-    บ
  บ                    Hardware und Software vorhanden ist.                บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   MSM_NO_DRIVER wenn Maus Hard- und Software   บ
  บ                               nicht installiert                        บ
  บ                           >0  Anzahl der Mausbuttons                   บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m,            บ
  บ                    swKopieCursorFlag_m (W), wMausda_g (W)              บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

GLOBAL
WORD MsmInit(VOID)
{
 IMPORT WORD wMausda_g;
 union  REGS mausregs;

 if( boMausInitialisiert_m != 1 )
 {
  boMausInitialisiert_m = 1;                  /* Flag setzen,Funktion */
                                                 /*     wurde aufgerufen */
  if( boMaasTouchscreenOnline )  // mat schalter aktiv
  {
   if( !ResetMaasTouchTreiber())
   {
    wMausda_g = NEIN;
    return( MSM_NO_DRIVER );
   }

   MaasKeyClick( FALSE );

   if( !SetMaasTouchResulution( MAAS_TOUCH_XRES,MAAS_TOUCH_YRES) )
   {
    wMausda_g = NEIN;
    return( MSM_NO_DRIVER );
   }

   if( SetMaasTouchMode( MAAS_TOUCH_COMBINEMODE ) )
   {
    boMsmTreiberda_m =  1;                  // Toolbox-Flag setzen
    swKopieCursorFlag_m = -1;               // Treiber-Cursor-Flag mithalten
    wMausda_g = JA;                         // globale Var. setzen
    return( 1 );
   }
   else
   {
    wMausda_g = NEIN;                       // globale Var. setzen
    return( MSM_NO_DRIVER );
   }
  }
  else
  {
   IntSetAX( mausregs, MSM_RESET_STATUS );           /* Funktionsnummer      */
   Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */

   if( IntGetAX( mausregs ) == 0)                     /* wenn AX == Null, ist */
   {
    wMausda_g = NEIN;                       /* globale Var. setzen  */
    return (MSM_NO_DRIVER);                 /* kein Maustreiber da  */
   }
   else
   {
    boMsmTreiberda_m =  1;                  /* Toolbox-Flag setzen  */
    swKopieCursorFlag_m = -1;               /* Treiber-Cursor-Flag  */
                                                   /*   mithalten          */
    wMausda_g = JA;                         /* globale Var. setzen  */
    return ( IntGetBX( mausregs ) );                 /* Anzahl Maus-Buttons  */
   }
  }
 }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmCursorOn                    Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion inkrementiert das interne Mauscur-   บ
  บ                    sorflag und zeigt den Cursor an, wenn das Flag      บ
  บ                    den Wert 0 hat.                                     บ
  บ                    Nach dem Aufruf von MsmInit() hat das Flag          บ
  บ                    den Wert -1.                                        บ
  บ                                                                        บ
  บ                    Diese Funktion verwendet eine Kopie dieses Flags    บ
  บ                    damit der Cursor nur eingeschaltet werden kann,     บ
  บ                    wenn er nicht sichtbar ist.                         บ
  บ                                                                        บ
  บ  Rckgabewert:     Status des Mauszeigers beim Funktionsaufruf         บ
  บ                                                                        บ
  บ                    WORD      - MSM_WAR_AN    Cursor war an             บ
  บ                              - MSM_WAR_AUS   Cursor war aus            บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m,            บ
  บ                    swKopieCursorFlag_m (R/W)                           บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MsmCursorOn (VOID)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m                            /* wenn Maus im System  */
        && (swKopieCursorFlag_m==-1))               /*      und Cursor aus  */
    {
        swKopieCursorFlag_m = 0;
        IntSetAX( mausregs,  MSM_SHOW_CURSOR );            /* Funktionsnummer      */
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */
        return(MSM_WAR_AUS);
    }
    return (MSM_WAR_AN);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmCursorOff                   Datum: 16.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion dekrementiert das interne Mauscur-   บ
  บ                    sorflag und entfernt den Cursor vom Bildschirm.     บ
  บ                    Die Bewegungen der Maus werden weiter registriert.  บ
  บ                                                                        บ
  บ                    Diese Funktion verwendet eine Kopie dieses Flags    บ
  บ                    damit der Cursor nur ausgeschaltet werden kann,     บ
  บ                    wenn er sichtbar ist.                               บ
  บ                                                                        บ
  บ  Rckgabewert:     Status des Mauszeigers beim Funktionsaufruf         บ
  บ                                                                        บ
  บ                    WORD      - MSM_WAR_AN    Cursor war an             บ
  บ                              - MSM_WAR_AUS   Cursor war aus            บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                    swKopieCursorFlag_m (R/W)                           บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MsmCursorOff (VOID)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m                            /* wenn Maus im System  */
        && (swKopieCursorFlag_m==0))                /*       und Cursor an  */
    {
        swKopieCursorFlag_m = -1;
        IntSetAX( mausregs, MSM_HIDE_CURSOR );            /* Funktionsnummer      */
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */
        return(MSM_WAR_AN);
    }
    return(MSM_WAR_AUS);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmGetPosition                 Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWORD  pwButton     erhlt - Buttonstatus           บ
  บ                    PWORD  pwHor               - horiz. Position        บ
  บ                    PWORD  pwVer               - vert. Position         บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt die aktuelle Position des  บ
  บ                    Mauscursors und den Status der Mausbuttons.         บ
  บ                                                                        บ
  บ                    Das Format der Rckgabewerte von "ver" und "hor"    บ
  บ                    kann ber die Funktion "MsmSetModus" gesteuert      บ
  บ                    werden. Defaultmแig werden die Grafikkoordinaten   บ
  บ                    in Textkoordinaten umgerechnet.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     ermittelte Werte werden ber bergebene Zeiger      บ
  บ                    zurckgegeben.                                      บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                    boTextMode_m(R)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmGetPosition(PWORD pwButton, PWORD pwHor, PWORD pwVer)
{
 union REGS mausregs;
 INT x1b;
 INT x2b;
 INT y1b;
 INT y2b;
 INT m = 0;
 WORD wBut;
 WORD wXP;
 WORD wYP;
 static INT iAnz;
 static WORD wMerkBut;
 static WORD wMerkx;
 static WORD wMerky;

 if (!boMausInitialisiert_m)                // Test ob Maus bereits initialisiert
   MsmInit(); // Normale Maus initialisieren

 if( boMsmTreiberda_m )                        // wenn Maus im System
 {
  if( !boMaasTouchscreenOnline )              // kein Maas touchscreen aktiv ( MAT SCHALTER )
  {
   IntSetAX( mausregs, MSM_GET_B_STATUS_POS ); // Funktionsnummer
   IntSetBX( mausregs, 0 );                    // BX-Register loeschen
   Interrupt(MAUS_INT, &mausregs);             // Interrupt ausloesen
   *pwButton = IntGetBX( mausregs );           // ermittelte Werte in

   if (boTextMode_m)                           // uebergebene Variablen in text laden
   {
    *pwHor   = IntGetCX( mausregs ) >>3;
    *pwVer   = IntGetDX( mausregs ) >>3;
   }
   else                                        // oder grafik koordinaten lassen
   {
    *pwHor   = IntGetCX( mausregs );
    *pwVer   = IntGetDX( mausregs );
   }
  }
  else
  {
   IntSetAH( mausregs,MAAS_TOUCH_ID );
   IntSetAL( mausregs, MAAS_TOUCH_GETPOS);
   IntSetDI( mausregs, 1 );
   Interrupt(MAAS_TOUCH_IRQ, &mausregs);

   if( IntGetAH( mausregs ) == 1 ) *pwButton = 0; // queue empty
   else
   {
    *pwButton = IntGetBL( mausregs );
    *pwHor = IntGetCX( mausregs );
    *pwVer = IntGetDX( mausregs );
   }
  }

 if( !boInTableOrArtikelTouch )
  if( boTouchscreenMain )
  {
   if( *pwButton )
   {
    if(( *pwHor>=41) && (*pwVer>=10) )
    {
     if( !boMaasTouchscreenOnline )
      while( *pwButton ) // entprell 10erblock
      {
       IntSetAX( mausregs, MSM_GET_B_STATUS_POS );
       IntSetBX( mausregs, 0 );
       Interrupt(MAUS_INT, &mausregs);
       *pwButton = IntGetBX( mausregs );
      }
     else
     {
      while( *pwButton )
      {
       IntSetAH( mausregs,MAAS_TOUCH_ID );
       IntSetAL( mausregs, MAAS_TOUCH_GETPOS);
       IntSetDI( mausregs, 1 );
       Interrupt(MAAS_TOUCH_IRQ, &mausregs);

       *pwButton = IntGetBL( mausregs );
       *pwHor = IntGetCX( mausregs );
       *pwVer = IntGetDX( mausregs );
      }
     }

     while( MsTest[m].x!=0)
     {
      x1b = 41 + MsTest[m].x1 ;
      x2b = 41 + MsTest[m].x2 ;
      y1b = 10 + MsTest[m].y1 ;
      y2b = 10 + MsTest[m].y2 ;

      if(((*pwHor >= x1b) && (*pwHor <= x2b)) && ((*pwVer >= y1b) && (*pwVer <= y2b)))
      {
       switch( MsTest[m].ret )
       {
        case T_F1:
        case T_F2:
        case T_F3:
        case T_F4:
        case T_F5:
        case T_F6:
        case T_F7:
        case T_F8:
        case T_F9:
        case T_F10:
        case T_UP:
        case T_LEFT:
        case T_RIGHT:
        case T_DOWN:
             KbdInsert(0,MsTest[m].ret );
             break;
        default: KbdInsert(MsTest[m].ret ,0);
       }

       *pwButton = *pwHor = *pwVer = 0;
       return;
      }
      m++;
     }
     *pwButton = *pwHor = *pwVer = 0;
    }
    wMerkBut = *pwButton;          // also, fuer den IBM MAAS Touchscreen in der
    wMerkx = *pwHor;               // touch Main variante wechslen sich zum
    wMerky = *pwVer;               // zeitpubkt der Menuauswahl 2 msmgetpositions ab, die sich
    iAnz = 0;                      // u.U den Touch 'klauen'. um dies zu verhindern
   }                               // schicken wir den Touch mit koordinaten
   else                            // mehrmals an die aufrufende Instanz zurueck
   {                               // sodass die Instanz auf jedenfall ihren Touch
    if( iAnz < 10 )                // mitbekommt. Alles Klar?  Ist irgenwie krank
    {                              // mehrere Handlings gleichzeitig fuer ein Ding
     *pwButton = wMerkBut;         // zu benutzen aber ...
     *pwHor = wMerkx;
     *pwVer = wMerky;
     iAnz++;
    }
   }
  }
 }
 return;
}

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmSetPosition                 Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wHor       horizontale Position des Cursors   บ
  บ                    WORD  wVer       vertikale Position des Cursors     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion positioniert den Maus-Cursor an      บ
  บ                    der durch wHor/wVer bergebenen Position.           บ
  บ                                                                        บ
  บ                    Defaultmแig werden die bergebenen Koordinaten     บ
  บ                    als Textkoordinaten interpretiert und vor dem       บ
  บ                    Aufruf der Interrupt-Routine in die internen        บ
  บ                    Grafik-Koordinaten des Maustreibers umgewandelt.    บ
  บ                                                                        บ
  บ                    Diese Umwandlung kann ber die Funktion             บ
  บ                    "MsmSetModus" gesteuert werden.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                    boTextMode_m(R)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmSetPosition(WORD wHor, WORD wVer)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        if (boTextMode_m)                           /* evtl. Umwandlung der */
        {                                           /* Koordinaten          */
            IntSetCX( mausregs, wHor <<3 );              /* Hor. Koord. nach CX  */
            IntSetDX( mausregs, wVer <<3 );              /* Ver. Koord. nach DX  */
        }
        else
        {
            IntSetCX( mausregs, wHor );                   /* Hor. Koord. nach CX  */
            IntSetDX( mausregs, wVer );                   /* Ver. Koord. nach DX  */
        }

        IntSetAX( mausregs, MSM_SET_POSITION );           /* Funktionsnummer      */
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */
    }
    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmButtonPress                 Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD      wButton        MSM_B_LINKS, MSM_B_RECHTS  บ
  บ                    PWORD     pwStatus       derzeitiger Buttonstatus   บ
  บ                    PWORD     pwKlicks       Anzahl der Klicks          บ
  บ                    PWORD     pwHor          horizontale Position       บ
  บ                    PWORD     pwVer          vertikale Position         บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion liefert als Ergebnis Informationen   บ
  บ                    ber die Position des Mauszeigers beim letzten      บ
  บ                    Klicken, die Anzahl der Klicks und den              บ
  บ                    aktuellen Status der Maustasten.                    บ
  บ                                                                        บ
  บ                    Die Position wird defaultmแig in Textkoordinaten   บ
  บ                    bergeben. Wird die bergabe in Grafikkoordinaten   บ
  บ                    gewnscht, kann dies ber die Funktion              บ
  บ                    "MsmSetModus()" gesteuert werden.                   บ
  บ                                                                        บ
  บ  Rckgabewert:     ermittelte Werte werden ber bergebene Zeiger      บ
  บ                    zurckgegeben.                                      บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m,            บ
  บ                    boTextMode_m(R)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmButtonPress(WORD  wButton,
                    PWORD pwStatus, PWORD pwKlicks,
                    PWORD pwHor,    PWORD pwVer)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        IntSetAX( mausregs, MSM_GET_B_PRESS );            /* Funktionsnummer      */
        IntSetBX( mausregs, wButton );                    /* Taste nach BX        */
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */

        *pwStatus     = IntGetAX( mausregs );              /* ermittelte Daten in  */
        *pwKlicks     = IntGetBX( mausregs );              /* bergebene Variablen */
        if (boTextMode_m)                           /* laden                */
        {
            *pwHor    = IntGetCX( mausregs ) >>3;          /* Umwandlung der Koord.*/
            *pwVer    = IntGetDX( mausregs ) >>3;          /*    im Textmodus      */
        }
        else
        {
            *pwHor    = IntGetCX( mausregs );
            *pwVer    = IntGetDX( mausregs );
        }
    }
    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmButtonRelease               Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD      wButton       MSM_B_LINKS, MSM_B_RECHTS   บ
  บ                    PWORD     pwStatus      derzeitiger Buttonstatus    บ
  บ                    PWORD     pwLos         Anzahl der Freigaben        บ
  บ                    PWORD     pwHor         horizontale Position        บ
  บ                    PWORD     pwVer         vertikale Position          บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion liefert als Ergebnis Informationen   บ
  บ                    ber Position des Mauszeigers beim letzten          บ
  บ                    Loslassen, wie oft die Taste losgelassen wurde und  บ
  บ                    den aktuellen Status der Maustasten.                บ
  บ                                                                        บ
  บ                    Die Position wird defaultmแig in Textkoordinaten   บ
  บ                    bergeben. Wird die bergabe in Grafikkoordinaten   บ
  บ                    gewnscht, kann dies mit der Funktion               บ
  บ                    "MsmSetModus()" gesteuert werden.                   บ
  บ                                                                        บ
  บ  Rckgabewert:     ermittelte Werte werden ber bergebene Zeiger      บ
  บ                    zurckgegeben (siehe Paramater).                    บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                    boTextMode_m  (R)                                   บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmButtonRelease(WORD  wButton,
                      PWORD pwStatus, PWORD pwLos,
                      PWORD pwHor,    PWORD pwVer)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        IntSetAX( mausregs, MSM_GET_B_RELEASE );          /* Funktionsnummer      */
        IntSetBX( mausregs, wButton );                    /* Taste nach BX        */
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */

        *pwStatus     = IntGetAX( mausregs );              /* ermittelte Werte in  */
        *pwLos        = IntGetBX( mausregs );              /* bergebene Variablen */
        if (boTextMode_m)                           /* laden                */
        {
            *pwHor      = IntGetCX( mausregs ) >>3;         /* im Textmodus Koord.  */
            *pwVer      = IntGetDX( mausregs ) >>3;         /* umrechnen            */
        }
        else
        {
            *pwHor      = IntGetCX( mausregs );
            *pwVer      = IntGetDX( mausregs );
        }
    }
    return;
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmHorMinMax                   Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wMin   minimale Cursorkoordinaten            บ
  บ                    WORD   wMax   maximale Cursorkoordinaten            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt die minimale und maximale       บ
  บ                    Koordinate in der Horizontalen fest, innerhalb      บ
  บ                    derer sich der Mauscursor bewegen lแt.             บ
  บ                                                                        บ
  บ                    Defaultmแig werden die bergebenen Koordinaten     บ
  บ                    als Textkoordinaten interpretiert und vor dem       บ
  บ                    Aufruf der Interrupt-Routine in die internen        บ
  บ                    Grafik-Koordinaten des Maustreibers umgewandelt.    บ
  บ                                                                        บ
  บ                    Diese Umwandlung kann ber die Funktion             บ
  บ                    "MsmSetModus" gesteuert werden.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                    boTextMode_m(R)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmHorMinMax(WORD wMin, WORD wMax)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        if (boTextMode_m)                           /* im Textmodus werden  */
        {                                           /* die Koordinaten beim */
            IntSetCX( mausregs, wMin <<3 );               /* Laden in die Regs    */
            IntSetDX( mausregs, wMax <<3 );               /* umgewandelt          */
        }
        else
        {
            IntSetCX( mausregs, wMin );                   /* min. Pos. nach CX    */
            IntSetDX( mausregs, wMax );                   /* max. Pos. nach DX    */
        }
       IntSetAX(  mausregs, MSM_SET_MINMAX_HOR );         /* Funktionsnummer      */
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */
    }
    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmVerMinMax                   Datum: 14.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wMin   minimale Cursorkoordinaten            บ
  บ                    WORD   wMax   maximale Cursorkoordinaten            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt die minimale und maximale       บ
  บ                    Koordinate in der Vertikalen fest, innerhalb derer  บ
  บ                    der Cursor bewegt werden kann.                      บ
  บ                                                                        บ
  บ                    Defaultmแig werden die bergebenen Koordinaten     บ
  บ                    als Textkoordinaten interpretiert und vor dem       บ
  บ                    Aufruf der Interrupt-Routine in die internen        บ
  บ                    Grafik-Koordinaten des Maustreibers umgewandelt.    บ
  บ                                                                        บ
  บ                    Diese Umwandlung kann ber die Funktion             บ
  บ                    "MsmSetModus()" gesteuert werden.                   บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmVerMinMax(WORD wMin, WORD wMax)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        if (boTextMode_m)                           /* im Textmodus werden  */
        {                                           /* die Koordinaten beim */
            IntSetCX( mausregs, wMin <<3 );               /* Laden in die Regs    */
            IntSetDX( mausregs, wMax <<3 );               /* umgewandelt          */
        }
        else
        {
            IntSetCX( mausregs, wMin );                   /* min. Pos. nach CX    */
            IntSetDX( mausregs, wMax );                   /* max. Pos. nach DX    */
        }

        IntSetAX( mausregs, MSM_SET_MINMAX_VER );         /* Funktionsnummer      */
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */
    }
    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmSetSoftCursor                 Datum: 17.08.88    บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wScreenmask    Screenmask des SW-Cursors     บ
  บ                    WORD   wCursormask    Cursormask des SW-Cursors     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt Screen- und Cursormask des      บ
  บ                    Software-Cursors fest.                              บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmSetSoftCursor(WORD wScreenmask,
                      WORD wCursormask)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        IntSetAX( mausregs, MSM_SET_TXT_CURSOR );         /* Funktionsnummer      */
        IntSetBX( mausregs, MSM_SW_CURSOR );              /* SW-Curs. selektieren */
        IntSetCX( mausregs, wScreenmask );                /* Parameter laden      */
        IntSetDX( mausregs, wCursormask );
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */
    }
    return;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmSetHardCursor               Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wStartscan   Startscanzeile des HW-Cursors   บ
  บ                    WORD   wStopscan    Stopscanzeile des HW-Cursors    บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt die Gr”แe des Hardware-Text-    บ
  บ                    Cursors fest. Die Parameter fr die Angabe der      บ
  บ                    Zeilen sind von der verwendeten Grafikkarte         บ
  บ                    abhngig.                                           บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmSetHardCursor(WORD wStartscan,
                      WORD wStopscan)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        IntSetAX( mausregs, MSM_SET_TXT_CURSOR );         /* Funktionsnummer      */
        IntSetBX( mausregs, MSM_HW_CURSOR );              /* HW-Curs. selektieren */
        IntSetCX( mausregs, wStartscan );                 /* Parameter laden      */
        IntSetDX( mausregs, wStopscan );
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */
    }
    return;
}
//-------------------------------------------------------------------------------------------
//NAME:
//TYP :
//PARAMETER:
//FUNKTION:
//-------------------------------------------------------------------------------------------
GLOBAL
BOOL SetMaasTouchResulution( INT iXRes,INT iYRes )
{
 SRegs regs;

 IntSetAH( regs,MAAS_TOUCH_ID );          // Id fuer den Touchtreiber
 IntSetAL( regs,MAAS_TOUCH_SETRESULT );   // Funktionnummer setzen
 IntSetDI( regs,1 );                      // Screennumber setzen
 IntSetCX( regs,iXRes );                  // Xres setzen
 IntSetDX( regs,iYRes );                  // Xres setzen

 Interrupt(MAAS_TOUCH_IRQ, &regs);

 if( IntGetAX( regs )  == 0 ) return( TRUE );
 return( FALSE );
}
//-------------------------------------------------------------------------------------------
//NAME:
//TYP :
//PARAMETER:
//FUNKTION:
//-------------------------------------------------------------------------------------------
GLOBAL
BOOL SetMaasTouchMode( BYTE bMode )
{
 SRegs regs;

 IntSetAH( regs, MAAS_TOUCH_ID );
 IntSetAL( regs, MAAS_TOUCH_SETMODE );
 IntSetDI( regs, 1 );
 IntSetBL( regs, bMode );

 Interrupt(MAAS_TOUCH_IRQ, &regs);

 if( IntGetAX( regs ) == 0 ) return( TRUE );
 return( FALSE );
}
//-------------------------------------------------------------------------------------------
//NAME:
//TYP :
//PARAMETER:
//FUNKTION:
//-------------------------------------------------------------------------------------------
VOID MaasKeyClick( BOOL boMode )
{
 SRegs regs;

 IntSetAH( regs, MAAS_TOUCH_ID );
 IntSetAL( regs, MAAS_TOUCH_SETKEYCLICK );
 IntSetDI( regs, 1 );
 IntSetBH( regs, boMode );

 Interrupt(MAAS_TOUCH_IRQ, &regs);
}
//-------------------------------------------------------------------------------------------
//NAME:
//TYP :
//PARAMETER:
//FUNKTION:
//-------------------------------------------------------------------------------------------
BOOL ResetMaasTouchTreiber( void )
{
 SRegs regs;

 IntSetAH( regs,MAAS_TOUCH_ID );
 IntSetAL( regs, MAAS_TOUCH_RESET);
 IntSetDI( regs, 1);

 Interrupt(MAAS_TOUCH_IRQ, &regs);

 if( IntGetAX(regs ) == 0 )  return( TRUE ); // alles ok
 return( FALSE );
}
//-------------------------------------------------------------------------------------------
//NAME:
//TYP :
//PARAMETER:
//FUNKTION:
//-------------------------------------------------------------------------------------------
BOOL SoftResetMaasTouchTreiber( void )
{
 SRegs regs;

 IntSetAH( regs,MAAS_TOUCH_ID );
 IntSetAL( regs, 1);
 IntSetDI( regs, 1);

 Interrupt(MAAS_TOUCH_IRQ, &regs);

 if( IntGetAX(regs ) == 0 )  return( TRUE ); // alles ok
 return( FALSE );
}





#ifdef NEVER
/*
  ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmGetMickeys                  Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWORD   pwHorMickeys                                บ
  บ                    PWORD   pwVerMickeys                                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt die letzten Bewegungen     บ
  บ                    der Maus in Mickeys seit dem letzten Aufruf der     บ
  บ                    Funktion. Die zurckgegebenen Werte mssen          บ
  บ                    folgendermaแen interpretiert werden:                บ
  บ                    pwHorMickeys  negativ  Bewegung nach links          บ
  บ                                  positiv  Bewegung nach rechts         บ
  บ                    pwVerMickeys  negativ  Bewegung nach oben           บ
  บ                                  positiv  Bewegung nach unten          บ
  บ                                                                        บ
  บ                    1 Mickey entspricht 1/200 inch                      บ
  บ                                                                        บ
  บ  Rckgabewert:     ermittelte Werte werden ber bergebene Zeiger      บ
  บ                    zurckgegeben.                                      บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmGetMickeys(PWORD pwHorMickeys, PWORD pwVerMickeys)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        mausregs.x.ax = MSM_GET_MOTION;             /* Funktionsnummer      */
        Interrupt(MAUS_INT, &mausregs);      /* Interrupt ausl”sen   */
        *pwHorMickeys = mausregs.x.cx;              /* ermittelte Werte     */
        *pwVerMickeys = mausregs.x.dx;              /* laden                */
    }
    return;
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmSetRatio                    Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wHorRatio                                    บ
  บ                    WORD   wVerRatio                                    บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt das Verhltnis von Mickeys      บ
  บ                    zu Pixeln fr die horizontale und vertikale Bewe-   บ
  บ                    gung der Maus fest.                                 บ
  บ                    Mit diesem Wert wird die Anzahl von Mickeys pro     บ
  บ                    Pixel festgelegt. Die bergabewerte mssen im       บ
  บ                    Bereich zwischen 1..32767 liegen.                   บ
  บ                                                                        บ
  บ                    Der Default-Wert nach Aufruf von MsmInit() betrgt  บ
  บ                        - horizontal:  8 Mickeys pro 8 Pixel            บ
  บ                        - vertikal:   16 Mickeys pro 8 Pixel            บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmSetRatio(WORD wHorRatio, WORD wVerRatio)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        mausregs.x.ax = MSM_SET_RATIO;              /* Funktionsnummer      */
        mausregs.x.cx = wHorRatio;                  /* Parameter laden      */
        mausregs.x.dx = wVerRatio;
        int86(MAUS_INT, &mausregs, &mausregs);      /* Interrupt ausl”sen   */
    }
    return;
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmSetThreshold                Datum: 14.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wSpeed                                       บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion wird die Bewegungsgeschwindig-  บ
  บ                    keit der Maus festgelegt, ab der die Bewegung des   บ
  บ                    Maus-Cursors auf dem Bildschirm verdoppelt wird.    บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmSetThreshold(WORD wSpeed)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        mausregs.x.ax = MSM_SET_THRESHOLD;          /* Funktionsnummer      */
        mausregs.x.dx = wSpeed;                     /* neue Geschwindigkeit */
        int86(MAUS_INT, &mausregs, &mausregs);      /* Interrupt ausl”sen   */
    }
    return;
}






#endif
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmTreiberSichern              Datum: 14.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion sichert den Status des Maustreibers  บ
  บ                    in einem modulglobalen Puffer.                      บ
  บ                    Sie k”nnen so ein Programm unterbrechen, das die    บ
  บ                    Maus benutzt und ein anderes Programm starten, das  บ
  บ                    ebenfalls die Maus verwendet.                       บ
  บ                                                                        บ
  บ                    s. a. MsmTreiberRestore()                           บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   OK     wenn Treiber gesichert wurde          บ
  บ                           ERROR  wenn kein Maustreiber installiert     บ
  บ                                  oder kein Speicher fr den Maus-      บ
  บ                                  treiber allokiert werden konnte       บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                    fpbBuffer_m(R/W)                                    บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MsmTreiberSave(VOID)
{
    WORD   wGroesse;
    WORD   wReturn;

    union  REGS mausregs;
    struct SREGS sregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        mausregs.x.ax = MSM_STORAGE_REQU;           /* Funktionsnummer      */
        int86(MAUS_INT, &mausregs, &mausregs);      /* Interrupt ausl”sen   */
        wGroesse = mausregs.x.bx;                   /* Gr”sse merken        */
        if ((fpbBuffer_m=(FPBYTE)UtlFmalloc(wGroesse*sizeof(BYTE))) == 0L)
            wReturn = ERROR;
        mausregs.x.ax = MSM_SAVE_DRIVER;            /* Funktionsnummer      */
        mausregs.x.dx = FP_OFF(fpbBuffer_m);        /* Adresse des Puffers  */
        sregs.es      = FP_SEG(fpbBuffer_m);
        int86x(MAUS_INT, &mausregs, &mausregs, &sregs);
        wReturn = OK;
    }
    else
        wReturn = ERROR;
    return (wReturn);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmTreiberRestore              Datum: 14.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ldt den mit MsmTreiberSichern()     บ
  บ                    gesicherten Status des Maustreibers.                บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   OK     wenn alter Maustreiberstatus geladen  บ
  บ                                  wurde                                 บ
  บ                           ERROR  wenn ein Null-Zeiger auf den Speicher บ
  บ                                  des alten Maustreibers zeigt          บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MsmTreiberRest(VOID)
{
    WORD   wReturn;
    union  REGS mausregs;
    struct SREGS sregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        if (fpbBuffer_m == 0L)
            wReturn = ERROR;
        else
        {
            mausregs.x.ax = MSM_RESTORE_DRIVER;     /* Funktionsnummer      */
            sregs.es      =  FP_SEG (fpbBuffer_m);  /* Adresse des Puffers  */
            mausregs.x.dx =  FP_OFF (fpbBuffer_m);  /* Interrupt ausl”sen   */
            int86x(MAUS_INT, &mausregs, &mausregs, &sregs);
            UtlFfree(fpbBuffer_m);
            fpbBuffer_m = 0L;
            wReturn = OK;
        }
    }
    return (wReturn);
}

#ifdef NEVER

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmSetSeite                    Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   seite                                        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt die Anzeigeseite fest, auf      บ
  บ                    der der Cursor angezeigt wird.                      บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID MsmSetSeite(WORD wSeite)
{
    union REGS mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        mausregs.x.ax = MSM_SET_CRT_PAGE;           /* Funktionsnummer      */
        mausregs.x.bx = wSeite;                     /* gewnschte Seite     */
        int86(MAUS_INT, &mausregs, &mausregs);      /* Interrupt ausl”sen   */
    }
    return;
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmGetSeite                    Datum: 18.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt die Anzeigeseite, auf      บ
  บ                    der der Mauscursor angezeigt wird.                  บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  == MSM_NO_DRIVER  kein Maustreiber vorhanden  บ
  บ                          => 0            Anzeigeseite                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MsmGetSeite(VOID)
{
    WORD        wSeite;
    union REGS  mausregs;

    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
    {
        mausregs.x.ax = MSM_GET_CRT_PAGE;           /* Funktionsnummer      */
        int86(MAUS_INT, &mausregs, &mausregs);      /* Interrupt ausl”sen   */
        wSeite = mausregs.x.bx;                     /* ermittelte Seite     */
    }
    else                                            /* sonst 255 zurck     */
        wSeite = MSM_NO_DRIVER;

    return (wSeite);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MsmSetModus                    Datum: 17.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wModus         MSM_GRAF_MODUS                 บ
  บ                                         MSM_TEXT_MODUS                 บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt fest, ob die Rckgabewerte      บ
  บ                    der Funktionen, die sich auf Bildschirmpositionen   บ
  บ                    beziehen, im Grafik- oder Textmodus zurckgegeben   บ
  บ                    werden.                                             บ
  บ                    Der Maustreiber arbeitet nur in Grafikkoordina-     บ
  บ                    ten (0..639, 0..239). Wenn mit dieser Funktion      บ
  บ                    der Textmodus selektiert wird, werden die           บ
  บ                    Rckgabewerte in Textkoordinaten (0..79, 0..24)     บ
  บ                    umgerechnet.                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD    der aktuelle Modus                          บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  boTextMode_m(R/W)                                   บ
  บ                    boMausInitialisiert_m, boMsmTreiberda_m (R)         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MsmSetModus(WORD wModus)
{
    if (!boMausInitialisiert_m)                     /* Test ob Maus bereits */
        MsmInit();                                  /* initialisiert        */

    if (boMsmTreiberda_m)                           /* wenn Maus im System  */
        switch (wModus)                             /* Modus auswerten      */
        {
            case MSM_TEXT_MODUS:
                 if (!boTextMode_m)
                    boTextMode_m=MSM_TEXT_MODUS;
                 break;

            case MSM_GRAF_MODUS:
                 if (boTextMode_m)
                     boTextMode_m=MSM_GRAF_MODUS;
                 break;
        }
    return(boTextMode_m);
}
#endif
