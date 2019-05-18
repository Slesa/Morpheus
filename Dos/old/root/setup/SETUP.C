 #include       "gastro/Setup.h"                 // Eigene Headerdatei
 #include       "gastro/Artikel.h"               // Eigene Headerdatei
 #include       "hilevel/Win.h"
 #include       "hilevel/Vio.h"
 #include       "hilevel/Event.h"
 #include       "hilevel/EvSchon.h"
 #include       "hilevel/MsgWin.h"
 #include       "hilevel/Mnu.h"
 #include       "defs/Colordef.h"
 #include       "defs/Errordef.h"
 #include       <stdio.h>                        // Ausgabe mir printf
 #include       <string.h>                       // Stringfunktionen
 #include       <stdlib.h>                       // NULL-Definitionen
 #include       <ctype.h>                        // isalnum() etc

 #ifdef CAST
  #include <DEFS.H>
  #include <BASICS.H>
  #include <HILEVEL.H>
  #include <CAST.H>
 #endif


 // ----------- Menuefunktionen ----------------------------------------------
 PRIVATE VOID CDECL     SetupMainMenu ( void );          // Hauptmenue
 PRIVATE VOID CDECL     SetupMainHelp ( void );          // Hauptmenue, Hilfe

 // ----------- Modul Abrechnungsarten ---------------------------------------
 VOID CDECL     SetupAbrMenu  ( void );          // Menuepunkt Abrechnungsarten
 // ----------- Modul SetDruck -----------------------------------------------
 VOID CDECL     SetupDruckList( void );          // Menuepunkt Drucker einrichten
 BOOL CDECL     SetupDruckEdit( INT );           // Maske zum Editieren der Druckerdaten
 // ----------- Modul Layout -------------------------------------------------
 VOID CDECL     SetupLayMenu  ( INT );         // Menuepunkt Bonlayout
 // ----------- Modul Online -------------------------------------------------
 VOID CDECL     SetupOnlnEdit ( void );          // Menuepunkt Online-Journal
 // ----------- Modul Wohin drucken ------------------------------------------
 VOID CDECL     SetupWohinMenu( void );          // Menuepunkt Wohin drucken
 // ----------- Modul Terminals ----------------------------------------------
 VOID CDECL     TermsMain     ( void );
 // ----------- Modul Tischparameter -----------------------------------------
 VOID CDECL     TablesMain    ( void );
 // ----------- Hilfsfunktionen ----------------------------------------------
 PRIVATE VOID CDECL     SetupShowHelp ( CHAR* );         // Moegliche Parameter anzeigen
 PRIVATE INT  CDECL     SetupHandleArg( INT, CHAR*[] );  // Parameter auswerten
#ifndef IPC
 PRIVATE VOID CDECL     SetupKralle   ( void );          // Logofenster zeigen
#endif
#ifdef IPC80
 PRIVATE INT  CDECL     print_mahnung ( void );          // Erschlagen Sie Ihren Apotheker
#endif

 PRIVATE SWin*  Kralle       = NULL;
 #ifdef         LANGUAGE
 #define        FILE_LNG     "SETUP.LNG"
 CHAR**         __INTSTR;
 #endif

 // **************************************************************************
 // * main                                                                   *
 // * ---------------------------------------------------------------------- *
 // * Main-Funktion von SETUP                                                *
 // **************************************************************************
#ifdef CAST
INT SetupMain ( void )
{
 INT iSetupMultiHandle;

 setbuf( stdout, NULL );

#ifdef LANGUAGE
 __INTSTR = LngStrRead( FILE_LNG, LNG_FOREIGN );
#endif

 if( !GetSetupFile() ) return( 0 );

 EvDelMulti( GetCfgMultiHandle());
 iSetupMultiHandle = EvAddMulti( DisplaySetupFile,  10L );

 switch( SetupLoad() )
 {
  case ERR_MEM_ALLOC:
       WinMsgCenter( " Es steht nicht gengend Speicher zur\n"
                     " Ausfhrung des Setup-Programms zur\n"
                     " Verfgung."
                     , MSG_INFO );
       EvDelMulti( iSetupMultiHandle );
       return( -1 );

  case ERR_NONE: break;
  default: WinMsgCenter( " Fehler beim Laden der Setup-Datei", MSG_INFO );
 }

 if( DskFileExist( "CODES.DAT" ) ) ArtLoadInfo( "CODES.DAT" );

 SetupMainMenu();                               // Hauptmenue ausfuehren

 switch( SetupSave() )                          // Versuchen, Daten zu sichern
 {
  case ERR_NONE:                                // Datei wurde gesichert
       break;
  case ERR_DISK_CREATE:                         // Fehler beim Oeffnen der Datei
       WinMsgCenter( " Fehler beim Anlegen der Setup-Datei!", MSG_INFO );
       break;
  case ERR_DISK_WRITE:                          // Fehler beim Schreiben in die Datei
       WinMsgCenter( " Fehler beim Schreiben in Setup-Datei!", MSG_INFO );
       break;
 }
 EvDelMulti( iSetupMultiHandle );
 SetCfgMultiHandle( EvAddMulti( DisplayCfgFile,  10L ));
 return( 0 );                                   // Kein Fehler aufgetreten
}

#else
 int            main         ( argc, argv )
 INT            argc;                            // Anzahl Parameter
 CHAR*          argv[];                          // Parameterliste
 {
  INT           ret;                             // Rueckgabe von Funktionen merken
  setbuf( stdout, NULL );
  #ifdef LANGUAGE
  __INTSTR = LngStrRead( FILE_LNG, LNG_FOREIGN );
  #endif
  if( ( ret=SetupHandleArg( argc, argv ) ) != 0 )// Fehlerhafter Schalter?
  {
   if( ret==-1 )
   SetupShowHelp( (ret==-1) ? NULL : argv[ret] );// Diesen anzeigen lassen mit Hilfe
   return( -1 );                                 // Fehler melden fuer Batch etc
  }
  VioInit( VIO_NONE );                           // Bildschirm vorbereiten
  EvInit();
#ifdef IPC80
   if( print_mahnung() == T_ESC )                // Fressen Sie die Packungsbeilage
   {
    VioDone();
    return( 2 );
   }
#endif
  VioBackground();                               // Hintergrund malen
#if( !defined IPC )
#if( ( !defined IPCOFFICE ) && ( !defined IPC80 ) )
  VioSsa( VioGetMaxCol()-20, 1, SetupGetName(), INVERS );
#endif
  SetupKralle();                                 // Unser Logo, wie immer
#endif
#ifdef OMRON
  EvSchonSetText( "OMRON 7000" );
#else
  EvSchonSetText( "* GastroFix *" );
#endif
  if( ( ret = SetupLoad() ) != ERR_NONE )        // Versuchen, die Daten einzulesen
  {
   if( ret!=ERR_MEM_ALLOC )                      // Speichermangel?
#ifdef IPC80
   WinMsgCenter( " Fehler beim Laden der Setup-Datei.\n"
                 " Vergewissern Sie sich, daá die Datei\n"
                 " SETUP.DAT im aktuellen Verzeichnis\n"
                 " existiert. Ferner darf dieses Programm\n"
                 " nur durch den Bacth ZUSATZ.BAT aufgerufen\n"
                 " werden!"
                 , MSG_INFO
                 );
#else
    WinMsgCenter( " Fehler beim Laden der Setup-Datei", MSG_INFO );
#endif
   else                                          // Meldung, dass Speicher fehlt
   {
    WinMsgCenter( " Es steht nicht gengend Speicher zur\n"
                  " Ausfhrung des Setup-Programms zur\n"
                  " Verfgung."
                , MSG_INFO
                );
    EvDone();
    VioDone();
    return( -1 );
   }
  }
  if( DskFileExist( "CODES.DAT" ) ) ArtLoadInfo( "CODES.DAT" );
#ifndef IPC
  SetupMainMenu();                               // Hauptmenue ausfuehren
#else
  SetupDruckList();
#endif
  switch( SetupSave() )                          // Versuchen, Daten zu sichern
  {
   case ERR_NONE:                                // Datei wurde gesichert
        break;
   case ERR_DISK_CREATE:                         // Fehler beim Oeffnen der Datei
        WinMsgCenter( " Fehler beim Anlegen der Setup-Datei!", MSG_INFO );
        break;
   case ERR_DISK_WRITE:                          // Fehler beim Schreiben in die Datei
        WinMsgCenter( " Fehler beim Schreiben in Setup-Datei!", MSG_INFO );
        break;
  }
#if( !defined IPC )
  WinEntfernen( Kralle );                        // Unser Logo, wie immer
#endif
  EvDone();
  VioDone();                                     // Bildschirm restaurieren
  return( 0 );                                   // Kein Fehler aufgetreten
 }

#endif
/* Erst bei REAL V6
 #define        SETUP_MNU_ABRECH      0
 #define        SETUP_MNU_SCHNITT     1
 #define        SETUP_MNU_DRUCKER     2
 #define        SETUP_MNU_LAYOUT      3
 #define        SETUP_MNU_ONLINE      4
 #define        SETUP_MNU_WOHIN       5
 #define        SETUP_MNU_ENDE        6
*/
#if( defined LIGHT )
 #define        SETUP_MNU_ABRECH      0
 #define        SETUP_MNU_DRUCKER     1
 #define        SETUP_MNU_LAYOUT      2
 #define        SETUP_MNU_ONLINE      3
 #ifndef OMRON
 #define        SETUP_MNU_ENDE        4
 #else
 #define        SETUP_MNU_WOHIN       4
 #define        SETUP_MNU_ENDE        5
 #endif
#elif( defined IPC80 )
 #define        SETUP_MNU_ABRECH      0
 #define        SETUP_MNU_LAYOUT      1
 #define        SETUP_MNU_WOHIN       3
 #define        SETUP_MNU_ENDE        4
#elif( defined IPCOFFICE )
 #define        SETUP_MNU_PFLEGE      0
 #define        SETUP_MNU_AUSWERT     1
#elif( defined DEMO )
 #define        SETUP_MNU_ABRECH      0
 #define        SETUP_MNU_DRUCKER     1
 #define        SETUP_MNU_LAYOUT      2
 #define        SETUP_MNU_ONLINE      3
 #define        SETUP_MNU_WOHIN       4
 #define        SETUP_MNU_TISCH       5
 #define        SETUP_MNU_ENDE        6
#else
 #define        SETUP_MNU_ABRECH      0
 #define        SETUP_MNU_DRUCKER     1
 #define        SETUP_MNU_LAYOUT      2
 #define        SETUP_MNU_ONLINE      3
 #define        SETUP_MNU_WOHIN       4
 #define        SETUP_MNU_TISCH       5
 #define        SETUP_MNU_TERMS       6
 #define        SETUP_MNU_ENDE        7
#endif

 // **************************************************************************
 // * SetupMainMenu                                                          *
 // * ---------------------------------------------------------------------- *
 // * Richtet das Hauptmenue ein und fuehrt es aus.                          *
 // **************************************************************************
 PRIVATE VOID CDECL     SetupMainMenu ( void )           // Hauptmenue
 {
  BOOL          flag=TRUE;                       // Flag, ob fertig mit Menue
  SMnu*         mnu;                             // Das Hauptmenue selbst
/* Erst bei REAL V6
  MenuInit( &MainMenu, 7 );                      // Menue initialisieren
  MenuAdd( &MainMenu, 3, 1, "~A~brechnungsarten       ", 'A', "~F1~ Hilfe ³ Verwaltung der Abrechnungsarten" );
  MenuAdd( &MainMenu, 3, 2, "~S~chnittstellenparameter", 'S', "~F1~ Hilfe ³ Einrichten der Schnittstellen" );
  MenuAdd( &MainMenu, 3, 3, "~D~rucker einrichten     ", 'D', "~F1~ Hilfe ³ Einrichten der verschiedenen Drucker" );
  MenuAdd( &MainMenu, 3, 4, "~B~on & Rechnungslayout  ", 'B', "~F1~ Hilfe ³ Angaben zu den Druck-Layouts" );
  MenuAdd( &MainMenu, 3, 5, "~O~nline-Journal         ", 'O', "~F1~ Hilfe ³ Angaben zu Informationen in der Journaldatei" );
  MenuAdd( &MainMenu, 3, 6, "~W~ohin drucken          ", 'W', "~F1~ Hilfe ³ Umlenken der Druckausgaben von Rechnungen, Auswertung, Offenst„nde" );
  MenuAdd( &MainMenu, 3, 7, "~E~nde                   ", 'E', "~F1~ Hilfe ³ Žnderungen sichern und Programm beenden" );
*/
#if( defined LIGHT )
  mnu = MnuInit( 6 );
  MnuAdd( mnu, 1, 1, "~A~brechnungsarten     ", " ~F1~ Hilfe ³ Verwaltung der Abrechnungsarten" );
  MnuAdd( mnu, 1, 2, "~D~rucker einrichten   ", " ~F1~ Hilfe ³ Einrichten der verschiedenen Drucker" );
  MnuAdd( mnu, 1, 3, "~B~on & Rechnungslayout", " ~F1~ Hilfe ³ Angaben zu den Druck-Layouts" );
  MnuAdd( mnu, 1, 4, "~O~nline-Journal       ", " ~F1~ Hilfe ³ Angaben zu Informationen in der Journaldatei" );
 #ifndef OMRON
  MnuAdd( mnu, 1, 5, "~E~nde                 ", " ~F1~ Hilfe ³ Žnderungen sichern und Programm beenden" );
 #else
  MnuAdd( mnu, 1, 5, "~W~ohin drucken        ", " ~F1~ Hilfe ³ Umlenken der Druckausgaben von Rechnungen" );
  MnuAdd( mnu, 1, 6, "~E~nde                 ", " ~F1~ Hilfe ³ Žnderungen sichern und Programm beenden" );
 #endif
#elif( defined IPC80 )
  mnu = MnuInit( 6 );                      // Menue initialisieren
  MnuAdd( mnu, 1, 1, "~A~brechnungsarten     ", " ~F1~ Hilfe ³ Verwaltung der Abrechnungsarten" );
  MnuAdd( mnu, 1, 2, "~B~on & Rechnungslayout", " ~F1~ Hilfe ³ Angaben zu den Druck-Layouts" );
  MnuAdd( mnu, 1, 3, "~W~ohin drucken        ", " ~F1~ Hilfe ³ Umlenken der Druckausgaben von Rechnungen, Auswertung, Offenst„nde" );
  MnuAdd( mnu, 1, 4, "~E~nde                 ", " ~F1~ Hilfe ³ Žnderungen sichern und Programm beenden" );
#elif( defined IPCOFFICE )
  mnu = MnuInit( 2 );                      // Menue initialisieren
  MnuAdd( mnu, 1, 1, "Druckertreiber fr ~D~atenpflege", "~F1~ Hilfe ³ Verwaltung der Abrechnungsarten" );
  MnuAdd( mnu, 1, 2, "Druckertreiber fr ~A~uswertung ", "~F1~ Hilfe ³ Angaben zu den Druck-Layouts" );
#elif( defined DEMO )
  mnu = MnuInit( 7 );                      // Menue initialisieren
  MnuAdd( mnu, 1, 1, "~A~brechnungsarten     ", " ~F1~ Hilfe ³ Verwaltung der Abrechnungsarten" );
  MnuAdd( mnu, 1, 2, "~D~rucker einrichten   ", " ~F1~ Hilfe ³ Einrichten der verschiedenen Drucker" );
  MnuAdd( mnu, 1, 3, "~B~on & Rechnungslayout", " ~F1~ Hilfe ³ Angaben zu den Druck-Layouts" );
  MnuAdd( mnu, 1, 4, "~O~nline-Journal       ", " ~F1~ Hilfe ³ Angaben zu Informationen in der Journaldatei" );
  MnuAdd( mnu, 1, 5, "~W~ohin drucken        ", " ~F1~ Hilfe ³ Umlenken der Druckausgaben von Rechnungen, Auswertung, Offenst„nde" );
  MnuAdd( mnu, 1, 6, "~T~isch-Parameter      ", " ~F1~ Hilfe ³ Spezielle Tisch-Parameter einstellen" );
  MnuAdd( mnu, 1, 7, "~E~nde                 ", " ~F1~ Hilfe ³ Žnderungen sichern und Programm beenden" );
#else
  mnu = MnuInit( 8 );                      // Menue initialisieren
  MnuAdd( mnu, 1, 1, "~A~brechnungsarten     ", " ~F1~ Hilfe ³ Verwaltung der Abrechnungsarten" );
  MnuAdd( mnu, 1, 2, "~D~rucker einrichten   ", " ~F1~ Hilfe ³ Einrichten der verschiedenen Drucker" );
  MnuAdd( mnu, 1, 3, "~B~on & Rechnungslayout", " ~F1~ Hilfe ³ Angaben zu den Druck-Layouts" );
  MnuAdd( mnu, 1, 4, "~O~nline-Journal       ", " ~F1~ Hilfe ³ Angaben zu Informationen in der Journaldatei" );
  MnuAdd( mnu, 1, 5, "~W~ohin drucken        ", " ~F1~ Hilfe ³ Umlenken der Druckausgaben von Rechnungen, Auswertung, Offenst„nde" );
  MnuAdd( mnu, 1, 6, "~T~isch-Parameter      ", " ~F1~ Hilfe ³ Spezielle Tisch-Parameter einstellen" );
  MnuAdd( mnu, 1, 7, "~Z~us. Terminals       ", " ~F1~ Hilfe ³ Einstellungen von zus„tzlichen Terminals" );
//  MenuAdd( &MainMenu, 1, 6, "~G~r”áe der Speisekarte", 'G', " ~F1~ Hilfe ³ Žndert die Anzahl der Artikel in der Speisekarte" );
  MnuAdd( mnu, 1, 8, "~E~nde                 ", " ~F1~ Hilfe ³ Žnderungen sichern und Programm beenden" );
#endif
  while( flag )                                  // Solange kein ESC
  {
   switch( MnuHandle( mnu, " Hauptmen ", VioCenterCol( 26 ), VioCenterRow( 8 ), NULL, SetupMainHelp ) )
   {
    case -1:                                     // Hier wurde ESC gedrueckt
#ifndef  IPCOFFICE
    case SETUP_MNU_ENDE:                         // oder Ende gewaehlt
         flag = FALSE;                           // Dann sind wir fertig
         break;
    case SETUP_MNU_ABRECH:                       // Menuepunkt Abrechnungsarten
         SetupAbrMenu();
         break;
/* Erst bei REAL V6
    case SETUP_MNU_SCHNITT:                      // Menuepunkt Schnittstellen einrichten
         break;
*/
    case SETUP_MNU_DRUCKER:                      // Menuepunkt Drucker einrichten
         SetupDruckList();
         break;
    case SETUP_MNU_LAYOUT:                       // Menuepunkt Bonlayout
         SetupLayMenu(-1);
         break;
    case SETUP_MNU_ONLINE:                       // Menuepunkt Online-Journal
         SetupOnlnEdit();
         break;
#if( !defined LIGHT || defined OMRON )
    case SETUP_MNU_WOHIN:                        // Menuepunkt Wohin drucken
         SetupWohinMenu();
         break;
#endif
#if( !defined LIGHT )
    case SETUP_MNU_TISCH:
         TablesMain();
         break;
#endif
#if( (!defined DEMO) && (!defined LIGHT))
    case SETUP_MNU_TERMS:
         TermsMain();
         break;
#endif
/*
    case SETUP_MNU_SPEISE:                       // Menuepunkt Groesse Speisekarte
         SetupSpeisekarte();
         break;
*/
#else
         flag = FALSE;
         break;
    case SETUP_MNU_PFLEGE:
         SetupDruckEdit( DEV_PFLEGE );
         break;
    case SETUP_MNU_AUSWERT:
         SetupDruckEdit( DEV_AUSWERT );
         break;
#endif
   }
  }
  MnuDone( mnu );
 }

 PRIVATE VOID CDECL     SetupMainHelp( void )
 {
#ifndef IPC80
  WinMsgCenter(
#if( defined LIGHT )
 #if( !defined OMRON )
              " Willkommen im Setup von GastroFix Light!\n\n"
              " In diesem Programm sind folgende Punkte enthalten:\n"
              " - Abrechnungsarten:\n"
              "   Erstellen von neuen und Editieren der bereits\n"
              "   angelegten Abrechnungsarten.\n"
              " - Drucker:\n"
              "   Laden, Bearbeiten und Sichern von Drucker-\n"
              "   treibern inklusive šbersetzungstabelle fr\n"
              "   acht Bondrucker, zwei Rechnungsdrucker, sowie\n"
              "   den Druckern fr die Auswertung und die Pflege.\n"
              " - Layout:\n"
              "   Ver„ndern des Layouts der Bons, Stornobons und\n"
              "   Rechnungen.\n"
 #else
              " Willkommen im Setup von OMRON Gastro 7000 Light!\n\n"
              " In diesem Programm sind folgende Punkte enthalten:\n"
              " - Abrechnungsarten:\n"
              "   Erstellen von neuen und Editieren der bereits\n"
              "   angelegten Abrechnungsarten.\n"
              " - Drucker:\n"
              "   Laden, Bearbeiten und Sichern von Drucker-\n"
              "   treibern inklusive šbersetzungstabelle fr\n"
              "   acht Bondrucker, zwei Rechnungsdrucker, sowie\n"
              "   den Druckern fr die Auswertung und die Pflege.\n"
              " - Layout:\n"
              "   Ver„ndern des Layouts der Bons, Stornobons und\n"
              "   Rechnungen.\n"
 #endif
#elif( defined IPCOFFICE )
              " Willkommen im Setup von IPC-FDS 2900 Office!\n\n"
              " In diesem Programm sind folgende Punkte enthalten:\n"
#elif( defined IPC80 )
              " Willkommen im Setup von IPC-Bistro!\n\n"
              " In diesem Programm sind folgende Punkte enthalten:\n"
              " - Abrechnungsarten:\n"
              "   Erstellen von neuen und Editieren der bereits\n"
              "   angelegten Abrechnungsarten.\n"
              " - Layout:\n"
              "   Ver„ndern des Layouts der Bons, Stornobons und\n"
              "   Rechnungen.\n"
              " - Wohin drucken:\n"
              "   Ausw„hlen des Druckers fr Rechnungen, Auswertung\n\n"
              "   und Offenst„nde."
#else
#ifndef OMRON
              " Willkommen im Setup von GastroFix!\n\n"
              " In diesem Programm sind folgende Punkte enthalten:\n"
              " - Abrechnungsarten:\n"
              "   Erstellen von neuen und Editieren der bereits angelegten\n"
              "   Abrechnungsarten.\n"
              " - Drucker:\n"
              "   Laden, Bearbeiten und Sichern von Druckertreiber inklusive\n"
              "   šbersetzungstabelle fr acht Bondrucker, zwei Rechnungs-\n"
              "   drucker, sowie den Druckern fr die Auswertungen und die\n"
              "   Pflege.\n"
              " - Layout:\n"
              "   Ver„ndern des Layouts der Bons, Stornobons und Rechnungen.\n"
              " - Online-Journal:\n"
              "   Einstellungen „ndern, welche Vorg„nge mitprotokolliert werden.\n"
              " - Wohin drucken:\n"
              "   Ausw„hlen des Druckers fr Rechnungen, Auswertung und Offen-\n"
              "   st„nde.\n"
              " - Tisch-Parameter:\n"
              "   Einstellen der Tisch-Parameter „ndern."
#else
              " Willkommen im Setup von OMRON Gastro 7000!\n\n"
              " In diesem Programm sind folgende Punkte enthalten:\n"
              " - Abrechnungsarten:\n"
              "   Erstellen von neuen und Editieren der bereits angelegten\n"
              "   Abrechnungsarten.\n"
              " - Drucker:\n"
              "   Laden, Bearbeiten und Sichern von Druckertreiber inklusive\n"
              "   šbersetzungstabelle fr acht Bondrucker, zwei Rechnungs-\n"
              "   drucker, sowie den Druckern fr die Auswertungen und die\n"
              "   Pflege.\n"
              " - Layout:\n"
              "   Ver„ndern des Layouts der Bons, Stornobons und Rechnungen.\n"
              " - Online-Journal:\n"
              "   Einstellungen „ndern, welche Vorg„nge mitprotokolliert werden.\n"
              " - Wohin drucken:\n"
              "   Ausw„hlen des Druckers fr Rechnungen, Auswertung und Offen-\n"
              "   st„nde.\n"
              " - Tisch-Parameter:\n"
              "   Einstellen der Tisch-Parameter „ndern."
#endif
#endif
            , MSG_INFO
            );
#else
  print_mahnung();
#endif
 }


 // **************************************************************************
 // * SetupShowHelp                                                          *
 // * ---------------------------------------------------------------------- *
 // * Gibt eine Liste der moeglichen Parameter aus. Falls argv!=NULL, wird   *
 // * der fehlerhafte Schalter angezeigt.                                    *
 // **************************************************************************
 PRIVATE VOID CDECL     SetupShowHelp( argv )
 CHAR*          argv;
 {
#if( defined LIGHT )
  printf( "  GastroFix-Light Setup V%hd.%02hd: (c) by GastroFix AG\n", VER_SETUP/100, VER_SETUP%100 );
#elif( defined IPCOFFICE )
  printf( "  IPC-FDS 2900 Office Setup: (c) by GastroFix AG\n" );
#elif( defined IP2 )
  printf( "  IPC-Bistro Setup V%hd.%02hd: (c) by GastroFix AG\n", VER_SETUP/100, VER_SETUP%100 );
#elif( defined IPC80 )
  printf( "  IPC Setup, V%hd.%02hd\n", VER_SETUP/100, VER_SETUP%100 );
#elif( defined OMRON )
  printf( "  OMRON Gastro 7000 Setup V%hd.%02hd\n", VER_SETUP/100, VER_SETUP%100 );
#else
  printf( "  GastroFix-Setup V%hd.%02hd: (c) by GastroFix AG\n", VER_SETUP/100, VER_SETUP%100 );
#endif
  if( argv!=NULL )
  {
   printf( "\n ÄÄ> Falscher oder fehlerhafter Schalter: <ÄÄ" );
   printf( "\n     %s\n", argv );
  }
  printf("\nSyntax: SETUP  [Setup-Datei]");
  printf("\n        Die Angabe der Setup-Datei ist optional. Standardm„áig");
  printf("\n        wird die Datei SETUP.DAT benutzt\n\n" );
 }

 // **************************************************************************
 // * SetupHandleArg                                                         *
 // * ---------------------------------------------------------------------- *
 // * Ueberprueft die uebergebenen Parameter und setzt entsprechende Schalter*
 // **************************************************************************
 PRIVATE INT CDECL      SetupHandleArg( argc, argv )
 INT            argc;
 CHAR*          argv[];
 {
  CHAR*         cp;
  if( argc==2 )
  {
   cp = argv[1];
   while( ( *cp=='-' ) || ( *cp=='/' ) || ( *cp==' ' ) ) cp++;
   if( !isalnum( *cp ) ) return( *cp=='?' ? -1 : 1 );
   if( *cp=='H' ) return( -1 );
   SetupChangeName( argv[1] );
  }
  else
   if( argc!=1 ) return( -1 );
  return( 0 );
 }

#ifdef IPC80
 PRIVATE INT CDECL      print_mahnung( void )
 {
  return( WinMeldung( 2,
                      2,
                      " FDS 2900 Einstellung zus„tzlicher Parameter\n"
                      " (c) by GastroFix AG\n\n"
                      " Dieses Dienstprogramm  dient zur Einstellung von zus„tzlichen  Para-\n"
                      " metern auf der FDS 2900. Es ist ausschlieálich fr den autorisierten\n"
                      " Fachhandel bestimmt und wird kostenlos zur Verfgung gestellt!\n\n"
                      " Warnung!  Bei unsachgem„áem  Gebrauch dieses Programmes kann es zu\n"
                      " Beeintr„chtigungen der Funktionalit„t der FDS kommen.   Sie k”nnen\n"
                      " solche Probleme in jedem Fall wieder beheben,  indem Sie die Datei\n"
                      " SETUP.DAT von der Orginal-Installationsdiskette in das Verzeichnis\n"
                      " c:\\gastro der FDS kopieren.\n\n"
                      " Fr Probleme, welche sich aus dem Gebrauch dieses Programmes\n"
                      " ergeben k”nnten, kann leider kein Support gew„hrt werden.\n\n"
                      "                         Bitte drcken sie Return um fortzufahren,\n"
                      "                                      oder ESC um abzubrechen ..."
                      , MELDUNG_JANEIN2
                      )
        );
 }
#endif
#ifndef IPC
 PRIVATE VOID CDECL     SetupKralle  ( void )
 {
  CHAR          temp[80];
  Kralle = WinEinrichten( 3, 1, 35,4 );
#if( defined LIGHT )
  sprintf( temp, "  GastroFix-Light Setup V%hd.%02hd      (c) by GastroFix AG", VER_SETUP/100, VER_SETUP%100 );
#elif( defined IPCOFFICE )
  sprintf( temp, "  IPC-FDS 2900 Office Setup        (c) by GastroFix AG" );
#elif( defined IP2 )
  sprintf( temp, "  IPC-Bistro Setup V%hd.%02hd          (c) by GastroFix AG", VER_SETUP/100, VER_SETUP%100 );
#elif( defined IPC80 )
  sprintf( temp, "  [F1]=Hilfe                                                      [ESC]=Zurck  " );
#elif( defined OMRON )
  sprintf( temp, "  OMRON Gastro 7000 Setup V%hd.%02hd                                  [ESC]=Zurck  ", VER_SETUP/100, VER_SETUP%100 );
#else
  sprintf( temp, "  GastroFix-Setup V%hd.%02hd           (c) by GastroFix AG", VER_SETUP/100, VER_SETUP%100 );
#endif
  VioStatus( temp, NORMAL, INVERS );
  if( Kralle == NULL ) return;
  WinSetAttrib( Kralle, VH( KOBALT,BLAU ), VH( KOBALT,BLAU ), VH( KOBALT,BLAU ) );
  WinSetRahmentyp( Kralle, WIN_FRAME_DOUBLE );
  WinAktivieren( Kralle );
  WinCls();
  WinSsa( 2, 1,"(c) 2000 by GastroFix AG",VH( KOBALT,BLAU ) );
#ifdef IPCOFFICE
  sprintf( temp, "   IPC-FDS 2900 Setup V%hd.%02hd", VER_SETUP/100, VER_SETUP%100 );
  WinSsa( 2, 0, temp, VH( KOBALT,BLAU ) );
#elif defined IP2
  sprintf( temp, "   IPC - Bistro Setup V%hd.%02hd", VER_SETUP/100, VER_SETUP%100 );
  WinSsa( 2, 0, temp, VH( KOBALT,BLAU ) );
#elif defined IPC80
  WinSsa( 2, 0,"FDS 2900 Zusatzeinstellung",VH( KOBALT,BLAU ) );
#elif defined OMRON
  WinSsa( 2, 0,"   OMRON Gastro 7000 Setup  ",VH( KOBALT,BLAU ) );
  WinSsa( 1, 1,"(c) 1999 by OMRON GmbH, Hamburg",VH( KOBALT,BLAU ) );
#else
  sprintf( temp, "   GastroFix  Setup  V%hd.%02hd", VER_SETUP/100, VER_SETUP%100 );
  WinSsa( 2, 0, temp, VH( KOBALT,BLAU ) );
#endif
 }
#endif

