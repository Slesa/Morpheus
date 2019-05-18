 #include       "gastro/Setup.h"
 #include       "hilevel/Dlg.h"
 #include       "hilevel/Vio.h"
 #include       "hilevel/Mnu.h"
 #include       "hilevel/MsgWin.h"
 #include       "defs/Errordef.h"
 #include       "defs/Keydefs.h"
 #include       <string.h>

 VOID CDECL     SetupWohinMenu( void );          // Menuepunkt Wohin drucken
 PRIVATE VOID CDECL     SetupWohinEdit( INT );           // Wohin-Maske ausgeben
 PRIVATE VOID CDECL     SetupWohinHelp( SDlg* );         // Hilfe zur Wohin-Maske
 PRIVATE VOID CDECL     SetupWoHelp   ( void );          // Hilfe zum Wohin-Auswahlmenue

 // **************************************************************************
 // * SetupWohinMenu                                                         *
 // * ---------------------------------------------------------------------- *
 // * Richtet das Menue wohin drucken ein und fuehrt es aus.                 *
 // **************************************************************************
 VOID CDECL     SetupWohinMenu( void )
 {
 #if( defined OMRON && defined LIGHT )
  SetupWohinEdit( 0 );
 #else
  BOOL          flag         = TRUE;             // Flag, ob fertig mit Menue
  SMnu*         mnu;
  INT           ret;
  /*
  if( SetupGetDruckerCount()==0 )
  {
   WinMeldung( VioCenterX( 30 )
             , VioCenterY( 3 )
             , "Es wurden noch keine Drucker angelegt.\n"\
               "Bitte fhren Sie zun„chst den Menpunkt\n"\
               "\"Drucker einrichten\" im Hauptmen aus."
             , MELDUNG_INFO
             );
   return;
  }
  MenuInit( &WohinMenu, 5 );                     // Menue initialisieren
  MenuAdd( &WohinMenu, 3, 1, "  ~S~etup          ", 'S', "~[F1]~ Hilfe ³ Drucker des Setups ausw„hlen" );
  MenuAdd( &WohinMenu, 3, 2, "  ~P~flege         ", 'P', "~[F1]~ Hilfe ³ Drucker der Pflege ausw„hlen" );
  MenuAdd( &WohinMenu, 3, 3, "  ~A~uswertung     ", 'A', "~[F1]~ Hilfe ³ Drucker der Auswertung ausw„hlen" );
  MenuAdd( &WohinMenu, 3, 4, "  ~J~ournal        ", 'J', "~[F1]~ Hilfe ³ Drucker fr das Journal ausw„hlen" );
  MenuAdd( &WohinMenu, 3, 5, "  ~O~ffenst„nde    ", 'O', "~[F1]~ Hilfe ³ Drucker fr die Offenst„nde ausw„hlen" );
 */
  mnu = MnuInit( 3 );
  MnuAdd( mnu, 1, 1, "  ~R~echnungen     ", " ~F1~ Hilfe ³ Drucker des Setups ausw„hlen" );
  MnuAdd( mnu, 1, 2, "  ~A~uswertung     ", " ~F1~ Hilfe ³ Drucker der Auswertung ausw„hlen" );
  MnuAdd( mnu, 1, 3, "  ~O~ffenst„nde    ", " ~F1~ Hilfe ³ Drucker fr die Offenst„nde ausw„hlen" );
  while( flag )                                  // Solange kein ESC
  {
   switch( ( ret = MnuHandle( mnu, " Wohin drucken... ", VioCenterCol( 16 ), VioCenterRow( 6 ), NULL, SetupWoHelp ) ) )
   {
    case -1:
         flag=FALSE;
         break;
    default:
         SetupWohinEdit( ret );
         break;
   }
  }
  MnuDone( mnu );
 #endif
 }

 PRIVATE VOID CDECL     SetupWoHelp  ( void )
 {
#ifdef IPC80
  WinMsgCenter( " Hier k”nnen Sie einstellen, wo die drei wichtigsten Ausgaben des\n"
                " Bestellmodus (Rechnung, Auswertung, Offenst„nde) ausgedruckt werden.\n"
                " (Die Bonverwaltung, d.h. wohin die Artikel gedruckt werden, wird\n"
                " bereits in der Datenpflege pro Artikel festgelegt).\n\n"
                " Es sollte mindestens ein Feld auf 'ja' stehen. Steht nur ein Feld\n"
                " auf 'ja', so wird ohne weitere Nachfrage auf dem angegebenen Drucker\n"
                " ausgedruckt. Stehen mehrere Felder auf 'ja', so wird vor jedem Druck\n"
                " nachgefragt, wohin gedruckt werden soll. ACHTUNG: Mehr als 5 Drucker\n"
                " k”nnen bei der FDS nicht angegeben werden und werden ignoriert!\n\n"
                " Die Druckerbezeichnungen entsprechen genau den Druckern, welche Sie\n"
                " auf der FDS unter dem Menpunkt 'Druckereinstellung' finden, im\n"
                " Bestellmodus werden diese unter den Bezeichnungen Bondrucker 1-4 fr\n"
                " COM1 bis COM4 und Bondrucker 5 und 6 fr LPT1 und LPT2 aufgefhrt."
              ,MSG_INFO
              );
#else
  WinMsgCenter( " Hier k”nnen Sie einstellen, wo die drei wichtigsten Ausgaben des\n"
                " Bestellmodus (Rechnung, Auswertung, Offenst„nde) ausgedruckt werden.\n"
                " (Die Bonverwaltung, d.h. wohin die Artikel gedruckt werden, wird\n"
                " bereits in der Datenpflege pro Artikel festgelegt).\n\n"
                " Es sollte mindestens ein Feld auf 'ja' stehen. Steht nur ein Feld\n"
                " auf 'ja', so wird ohne weitere Nachfrage auf dem angegebenen Drucker\n"
                " ausgedruckt. Stehen mehrere Felder auf 'ja', so wird vor jedem Druck\n"
                " nachgefragt, wohin gedruckt werden soll."
              , MSG_INFO
              );
#endif
 }

 PRIVATE VOID CDECL     SetupWohinHelp( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie hier an, ob auf dem entsprechenden\n"
                " Drucker eine Ausgabe erfolgen soll ([X]) oder\n"
                " nicht ([ ])."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetupWohinEdit( dev )
 INT            dev;
 {
  SDlg*         dlg;
  INT           flag;
  CHAR          temp[70];
  INT           iCount       = 0;
  dlg = DlgInit( 1 );
  switch( dev )
  {
   case 0:
        strcpy( temp, " ~F1~ Hilfe ³ Wohin sollen die Rechnungen gedruckt werden" );
        break;
   case 1:
        strcpy( temp, " ~F1~ Hilfe ³ Wohin sollen die Auswertungen gedruckt werden" );
        break;
   case 2:
        strcpy( temp, " ~F1~ Hilfe ³ Wohin sollen die Offenst„nde gedruckt werden" );
        break;
  }
  DlgInitEntry( dlg, 10, DLG_CHECK, 1, 1, "", SetupWohinHelp, temp );
  switch( dev )
  {
   case 0:
        flag = SetupGetWohinRechnung();
        break;
   case 1:
        flag = SetupGetWohinAuswert();
        break;
   case 2:
        flag = SetupGetWohinOffen();
        break;
  }
#ifdef IPC80
  DlgAddField( dlg, 3, iCount++, "Anschluá COM~1~...", flag&1,0 );
  DlgAddField( dlg, 3, iCount++, "Anschluá COM~2~...", flag&2,0 );
  DlgAddField( dlg, 3, iCount++, "Anschluá COM~3~...", flag&4,0 );
  DlgAddField( dlg, 3, iCount++, "Anschluá COM~4~...", flag&8,0 );
  DlgAddField( dlg, 3, iCount++, "Anschluá ~L~PT1...", flag&16,0 );
  DlgAddField( dlg, 3, iCount++, "Anschluá L~P~T2...", flag&32,0 );
  DlgAddField( dlg, 3, iCount++, "-reserviert-    ", flag&64,0 );
  DlgAddField( dlg, 3, iCount++, "-reserviert-           ", (flag&128)>>7,0 );
  DlgAddField( dlg, 3, iCount++, "~R~echnungsdrucker", (flag&256)>>8,0 );
  DlgAddField( dlg, 3, iCount++, "-reserviert-           ", (flag&512)>>8,0 );
#else
  DlgAddField( dlg, 3, iCount++, "~1~. Bondrucker   ", flag&1,0 );
  DlgAddField( dlg, 3, iCount++, "~2~. Bondrucker   ", flag&2,0 );
 #if( !defined LIGHT )
  DlgAddField( dlg, 3, iCount++, "~3~. Bondrucker   ", flag&4,0 );
  DlgAddField( dlg, 3, iCount++, "~4~. Bondrucker   ", flag&8,0 );
  DlgAddField( dlg, 3, iCount++, "~5~. Bondrucker   ", flag&16,0 );
  DlgAddField( dlg, 3, iCount++, "~6~. Bondrucker   ", flag&32,0 );
  DlgAddField( dlg, 3, iCount++, "~7~. Bondrucker   ", flag&64,0 );
  DlgAddField( dlg, 3, iCount++, "~8~. Bondrucker   ", (flag&128)>>7,0 );
 #else
  DlgAddField( dlg, 3, iCount++, "-reserviert-    ", flag&4,0 );
  DlgDisable( dlg, 0, iCount-1 );
  DlgAddField( dlg, 3, iCount++, "-reserviert     ", flag&8,0 );
  DlgDisable( dlg, 0, iCount-1 );
  DlgAddField( dlg, 3, iCount++, "-reserviert-    ", flag&16,0 );
  DlgDisable( dlg, 0, iCount-1 );
  DlgAddField( dlg, 3, iCount++, "-reserviert-    ", flag&32,0 );
  DlgDisable( dlg, 0, iCount-1 );
  DlgAddField( dlg, 3, iCount++, "-reserviert-    ", flag&64,0 );
  DlgDisable( dlg, 0, iCount-1 );
  DlgAddField( dlg, 3, iCount++, "-reserviert-    ", (flag&128)>>7,0 );
  DlgDisable( dlg, 0, iCount-1 );
 #endif
  DlgAddField( dlg, 3, iCount++, "~R~echnungsdrucker", (flag&256)>>8,0 );
  DlgAddField( dlg, 3, iCount++, "~J~ournaldrucker  ", (flag&512)>>8,0 );
#endif
  if( DlgHandle( dlg, VioCenterCol( 30 ), VioCenterRow( iCount+4 ), 30, iCount+4, "  Wohin drucken ", NULL ) == T_RETURN )
  {
   flag = (INT) DlgGetMarked( dlg, 0 );
   switch( dev )
   {
    case 0:
         SetupSetWohinRechnung( flag );
         break;
    case 1:
         SetupSetWohinAuswert( flag );
         break;
    case 2:
         SetupSetWohinOffen( flag );
         break;
   }
  }
  DlgDone( dlg );
 }
