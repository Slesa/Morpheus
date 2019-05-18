/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTMSM.H                        Datum: 10.11.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ   Diese Datei enthlt die symbolischen Konstanten und Funktions-       บ
  บ   Prototypen fr die Grundfunktionen der Microsoft(TM)-Maus.           บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_MAUS_HEADER

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ       bergabewerte an MsmButtonPress() und MsmButtonRelease()         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define MSM_B_LINKS     0
#define MSM_B_RECHTS    1

#define MSM_L_DOWN      1           /* 0000 0001 b */
#define MSM_R_DOWN      2           /* 0000 0010 b */
#define MSM_B_DOWN      3           /* 0000 0011 b */

#define MSM_NO_DRIVER          255

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                     bergabewerte an MsmSetModus()                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define MSM_GRAF_MODUS 0
#define MSM_TEXT_MODUS 1


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ          Rckgabewerte von MsmCursorOn() und MsmCursorOff()            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define MSM_WAR_AN   0
#define MSM_WAR_AUS  1

typedef struct
{
  INT x,y;                   // Koordinaten des Zeichens
  INT x1,y1;                 // Anfangsbereich des Zeichens
  INT x2,y2;                 // Endbereich des Zeichens
  INT ret;                   // Tastencode des Zeichens
  CHAR text[8];              // Zeichen
}MAUS;

MAUS MsTest[41];

// Prototypen fuer den MAAS Touchcreen
GLOBAL BOOL  SetMaasTouchResulution( INT,INT );
GLOBAL VOID  GetMaasTouch          ( WORD*,WORD*,WORD* );
GLOBAL BOOL  SetMaasTouchMode      ( BYTE );
GLOBAL BOOL  ResetMaasTouchTreiber ( void );

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                      FUNKTIONS-PROTOTYPEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL WORD  MsmInit           (VOID);
GLOBAL WORD  MsmCursorOn       (VOID);
GLOBAL WORD  MsmCursorOff      (VOID);
GLOBAL VOID  MsmGetPosition    (PWORD, PWORD, PWORD);
GLOBAL VOID  MsmSetPosition    (WORD,  WORD);
GLOBAL VOID  MsmButtonPress    (WORD,  PWORD, PWORD, PWORD, PWORD);
GLOBAL VOID  MsmButtonRelease  (WORD,  PWORD, PWORD, PWORD, PWORD);
GLOBAL VOID  MsmHorMinMax      (WORD,  WORD);
GLOBAL VOID  MsmVerMinMax      (WORD,  WORD);
GLOBAL VOID  MsmSetSoftCursor  (WORD,  WORD);
GLOBAL VOID  MsmSetHardCursor  (WORD,  WORD);
GLOBAL VOID  MsmGetMickeys     (PWORD, PWORD);
GLOBAL VOID  MsmSetRatio       (WORD,  WORD);
GLOBAL VOID  MsmSetThreshold   (WORD);
//GLOBAL BOOL  MsmTreiberSave    (VOID);
//GLOBAL BOOL  MsmTreiberRest    (VOID);
GLOBAL VOID  MsmSetSeite       (WORD);
GLOBAL WORD  MsmGetSeite       (VOID);
GLOBAL WORD  MsmSetModus       (WORD);

#define CT_MAUS_HEADER 1
#endif
