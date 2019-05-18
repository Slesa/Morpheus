/****************************************************************************/
/* MNU.H                                                                    */
/* ------------------------------------------------------------------------ */
/* Definition der Funktionen zum Zugriff auf Menues.                        */
/****************************************************************************/
#ifndef         _WINMNU_

 #define        _WINMNU_
 #include       "hilevel/Win.h"

 /* ----------- Typdefinitionen ------------------------------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct                           /* Struktur eines Menu-Eintrags */
 {
  INT           iHotkey;                         /* Hotkey des Eintrags     */
  CHAR*         pcStatus;                        /* Statuszeile des Eintrags */
  CHAR*         pcText;                          /* Menupunkt-Text          */
  WORD          wX;                              /* X-Position des Eintrags */
  WORD          wY;                              /* Y-Position des Eintrags */
 } SMnuEntry;

 typedef VOID   (CDECL *FMnuHelp)  ( void );           /* Typ der Hilfe fuer ein Menue */

 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef        struct                           /* Struktur eines Menues   */
 {
  BYTE          bCount;                          /* Anzahl der Eintraege    */
  BYTE          bActual;                         /* Nummer des naechsten einzufuegenden Eintrags */
  BYTE          bCurrent;                        /* Beim Handling aktueller Eintrag */
  SMnuEntry*    Entry;                           /* Liste der Eintraege     */
  SWin*         Win;                             /* Ausgabe-Fenster         */
 } SMnu;

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 SMnu* CDECL    MnuInit         PARAM(( BYTE ));
 VOID  CDECL    MnuDone         PARAM(( SMnu* ));
 VOID  CDECL    MnuAdd          PARAM(( SMnu*, WORD, WORD, CHAR*, CHAR* ));
 INT   CDECL    MnuHandle       PARAM(( SMnu*, CHAR*, WORD, WORD, INT*, FMnuHelp ));
 DECLEND

#endif
