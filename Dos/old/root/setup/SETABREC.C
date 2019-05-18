// ***************************************************************************
// * SETABRECH.C                                                             *
// * ----------------------------------------------------------------------- *
// * Implementierung der Funktionen zum Editieren der Abrechnungsarten.      *
// ***************************************************************************
 #include       "gastro/Setup.h"                 // Eigene Header-Datei
 #include       "gastro/Info.h"
 #include       "gastro/Waehrung.h"
 #include       "hilevel/MsgWin.h"
 #include       "hilevel/LstWin.h"
 #include       "hilevel/Vio.h"
 #include       "hilevel/Dlg.h"
 #include       "basics/Disk.h"
 #include       "basics/MemAlloc.h"
 #include       "defs/Keydefs.h"                 // Allgemeine Typdefinitionen
 #include       <stdlib.h>                       // NULL-Definition
 #include       <string.h>                       // String-Funktionen
 #include       <stdio.h>                        // Standard-Ausgabe

 // ----------- Interne Funktionen -------------------------------------------
 VOID CDECL     SetupAbrMenu  ( void );          // Menuepunkt Abrechnungsarten
 PRIVATE VOID CDECL     SetupAbrHelp  ( void );          // Hilfe zum Auswahlfenster Abrechnungsarten
 PRIVATE BOOL CDECL     SetupAbrEdit  ( INT  );          // Abrechnungsart editieren
 PRIVATE VOID CDECL     SetupAbrHilf  ( SDlg* );         // Hilfe zur Abrech-Maske
 PRIVATE BOOL CDECL     GetAbrText( CHAR*, INT );
 PRIVATE BOOL CDECL     EditAbrText( INT );
 PRIVATE VOID CDECL     GetTerminalNrHelp( SDlg* );

 void SetupAartInit();
 void SetupAartDone();
 void SetupAartSave();
 CHAR* SetupGetAartExternal( int, CHAR* );
 int   SetupSetAartExternal( int, CHAR* );
 int   SetupDelAartExtern( int );

 // **************************************************************************
 // * GetTerminalNrHelp                                                        *
 // * ---------------------------------------------------------------------- *
 // * Hilfe zur Eingabe der Terminal Nummer                                 *
 // **************************************************************************
 PRIVATE VOID CDECL     GetTerminalNrHelp( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Bitte geben Sie hier die Terminalnummer ein\n"
                "       Fr den Master bitte 0 eingeben        ",MSG_INFO);
 }

 // **************************************************************************
 // * GetAbrText                                                           *
 // * ---------------------------------------------------------------------- *
 // * Eingabe des Individuellen Abr. Textes                                *
 // **************************************************************************
 PRIVATE BOOL CDECL     GetAbrText( sTerminalNr, iAbrArt )
 CHAR*          sTerminalNr;
 INT            iAbrArt;
 {
  SDlg*         dlg;
  CHAR          cTemp[61];
  CHAR          cFile[51];
  CHAR          cStatus[100];
  SFile*        fh;
  BOOL          boRet;
  INT           i            = 0;
  if( (atoi( sTerminalNr ) ) != 0 )
  {
   sprintf( cFile,"config\\rtext%03s.%02hd", sTerminalNr, iAbrArt-1);
  }
  else
  {
   sprintf( cFile,"config\\rtext%03hd.%02hd", 999, iAbrArt-1);
  }
  dlg = DlgInit( 22 );
  if( DskFileExist( cFile ) )
  {
   fh = DskFileOpen( cFile, "rt" );
   while( fgets( cTemp, 60, fh ) )
   {
    cTemp[strlen(cTemp)-1] = 0;
    sprintf( cStatus, "Zeile %hd  ³ Geben Sie den Individuellen Abrechnungs Text ein", i+1 );
    DlgInitEntry( dlg, 1, DLG_INPUT, 1, i++, NULL, NULL, cStatus );
    DlgAddField ( dlg, 1, 0,  cTemp, DLG_FIELD_ALL, 60 );
    if( i>=22 )
    {
     WinMsgCenter( " Achtung: Der Rechnungstext ist zu groá, um in diesem\n"
                   " Dialog bearbeitet zu werden.", MSG_INFO);
     break;
    }
   }
   DskFileClose( fh );
  }
  for( ; i<22; i++ )
  {
   sprintf( cStatus, "Zeile %hd  ³ Geben Sie den Individuellen Abrechnungs Text ein", i+1 );
   DlgInitEntry( dlg, 1, DLG_INPUT, 1, i, NULL, NULL, cStatus );
   DlgAddField ( dlg, 1, 0,  NULL, DLG_FIELD_ALL, 60 );
  }
  boRet = ( DlgHandle( dlg, VioCenterCol( 66 ), VioCenterRow( 24 ), 66, 24, " Abrechnungstext Editieren ", NULL )==T_RETURN );
  if( !boRet )
  {
   DlgDone(dlg);
   return( FALSE );
  }
  fh    = DskFileOpen( cFile, "wt" );
  if( fh==NULL ) return( FALSE );
  for( i=0; i<22; i++ )
  {
   fprintf( fh, "%s\n", DlgGetText( dlg, i, 0 ) );
  }
  DskFileClose( fh );
  DlgDone( dlg );
  return( TRUE );
 }

 // **************************************************************************
 // * EditAbrText                                                            *
 // * ---------------------------------------------------------------------- *
 // * Individueller Abr. Text                                               *
 // **************************************************************************
 PRIVATE BOOL CDECL     EditAbrText( iAbrechArt )
 INT            iAbrechArt;
 {
  SDlg*         dlg;
  CHAR          cTermNr[4];
  BOOL          boRet        = FALSE;
  BOOL          boFertig     = FALSE;
  sprintf( cTermNr,"000");
  dlg = DlgInit( 1 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 1, "~T~erminal Nr... :", GetTerminalNrHelp, " ~F1~ Hilfe ³ Geben Sie die Terminal Nummer ein" );
  DlgAddField ( dlg, 18, 0, cTermNr, DLG_FIELD_NUM, 3 );
  while( !boFertig )
  {
   switch( DlgHandle( dlg, VioCenterCol( 38 ), VioCenterRow( 5 ), 38, 5, " Terminalnummer eingeben", NULL ) )
   {
    case T_ESC:
         boFertig = TRUE;
         break;
    case T_RETURN:
         boRet = boFertig = GetAbrText( DlgGetText( dlg, 0, 0 ), iAbrechArt );
         break;
   }
  }
  DlgDone( dlg );
  return( boRet );
 }

 // **************************************************************************
 // * SetupAbrHelp                                                           *
 // * ---------------------------------------------------------------------- *
 // * Hilfefunktion zum Auswahlfenster Abrechnungsarten.                     *
 // **************************************************************************
 PRIVATE VOID CDECL     SetupAbrHelp ( void )
 {
  WinMsgCenter( " W„hlen Sie aus dem Men die Abrechnungs-\n"
                " art aus, die Sie bearbeiten m”chten.\n"
                " Zus„tzlich k”nnen Sie mit [EINF] eine neue\n"
                " Abrechnungsart anlegen oder mit [ENTF] \n"
                " eine nicht mehr ben”tigte Abrechnungsart\n"
                " l”schen."
              , MSG_INFO
              );
 }

 // **************************************************************************
 // * SetupAbrMenu                                                           *
 // * ---------------------------------------------------------------------- *
 // * Richtet das Menue zum Auswaehlen der Abrechnungsart ein.               *
 // **************************************************************************
 VOID CDECL     SetupAbrMenu  ( void )
 {
  SLst*         lst;
  INT           AbrExit[]    = { /*T_INS,*/ T_DEL, 0 };
  BOOL          boFertig     = FALSE;
  INT           i;
  SetupAartInit();
  if( SetupGetAnzAart()==0 ) if( !SetupAbrEdit( -1 ) )
  {
   SetupAartDone();
   return;
  }
  lst = LstInit( 70 );
  for( i=0; i<SetupGetAnzAart(); i++ )
  {
   if( SetupAartExist(i) )
    LstInsert( lst, (LONG) i, "%2hd) %-30s %-14s  %s  %s   %c"
                  , i+1
                  , SetupGetAartName(i)
                  , SetupGetAartKurz(i)
                  , SetupGetAartGesFlag(i) ? "Ja  " : "Nein"
                  , SetupGetAartKassenFlag(i) ? "Ja  " : "Nein"
                  , SetupGetAartTyp(i)
           );
   else
    LstInsert( lst, (LONG) i, "%2hd) %-30s %-14s  %s  %s   %c"
                  , i+1
                  , "<Nicht belegt>"
                  , "<Nicht belegt>"
                  , "----"
                  , "----"
                  , '-'
           );
  }
  while( !boFertig )
  {
   switch( LstShow( lst, LST_LIST, VioCenterCol( 70 ), VioCenterRow( 17 ), 70, 17, "Nr Ä Name ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Kurzname ÄÄÄÄÄÄ Ges.  Kasse Typ", " ~F1~ Hilfe  ~ENTF~ L”schen ³ W„hlen Sie eine Abrechnungsart", AbrExit, SetupAbrHelp ) )
//   switch( ListShow( &AbrList, " Abrechnungsart ausw„hlen ", " [F1] Hilfe ³ W„hlen Sie die zu bearbeitende Abrechnungsart", NULL, SetupAbrHelp ) )
   {
    case T_ESC:
         boFertig = TRUE;
         break;
    case T_DEL:
         if( WinMsgCenter( "            ACHTUNG\n"
                           "  Sind Sie sicher, daá Sie diese\n"
                           "  Abrechnungsart l”schen m”chten?\n"
                           "    Bedenken Sie, daá in Ihrer\n"
                           "  Auswertung die entsprechenden\n"
                           "  Ums„tze nicht mehr auftauchen!"
                           , MSG_YESNO
                           ) != T_RETURN
           ) break;
         i = (INT) LstGetNum( lst );
         if( !SetupDelAartExtern(i) )
         {
          WinMsgCenter(" Fehler beim L”schen der Abrecnungsdaten", MSG_INFO );
          break;
         }
         LstChange( lst, (LONG) i, (LONG) i, "%2hd) %-30s %-14s  %s  %s   %c"
                       , i+1
                       , "<Nicht belegt>"
                       , "<Nicht belegt>"
                       , "----"
                       , "----"
                       , '-'
                );
         SetupSetAartName( i, "" );
         SetupSetAartKurz( i, "" );
         SetupSetAartTyp( i, ' ' );
         SetupSetAartGesFlag( i, FALSE );
         SetupSetAartKassenFlag( i, FALSE );
         SetupAartSave();
         break;
    case T_RETURN:
         i = LstGetNum( lst );
         if( SetupAbrEdit( i ) )
         {
          LstChange( lst, (LONG) i, (LONG) i, "%2hd) %-30s %-14s  %s  %s   %c"
                        , i+1
                        , SetupGetAartName(i)
                        , SetupGetAartKurz(i)
                        , SetupGetAartGesFlag(i) ? "Ja  " : "Nein"
                        , SetupGetAartKassenFlag(i) ? "Ja  " : "Nein"
                        , SetupGetAartTyp(i)
                 );
           SetupAartSave();
         }
         break;
   }
  }
  LstDone( lst );
  SetupAartDone();
 }

 // **************************************************************************
 // * SetupAbrEdit                                                           *
 // * ---------------------------------------------------------------------- *
 // * Richtet den Dialog Abrechnungsart ein und fuehrt ihn aus.              *
 // **************************************************************************
 BOOL CDECL     SetupAbrEdit ( iAbr )
 INT            iAbr;
 {
  extern SInfo  info;
  SDlg*         dlg;
  CHAR          abrTyp[2];
  CHAR          cTemp[15];
  CHAR          cAartExt[68];
  INT           iExitKeys[]  = { T_F2, 0 };
  BOOL          boRet        = FALSE;
  BOOL          boFertig     = FALSE;
  if( iAbr!=-1 )
   sprintf( abrTyp, "%c", SetupGetAartTyp( iAbr ) );
  else
  {
   abrTyp[0] = 0;
  }
  dlg = DlgInit( 7 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 1, "~N~ame.......... :", SetupAbrHilf, " ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ³ Der Name der Abrechnungsart" );
  DlgAddField ( dlg, 18, 0, SetupGetAartName(iAbr), DLG_FIELD_ALL, 30 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 2, "~K~urzbezeichnung:", SetupAbrHilf, " ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ³ Die Kurzbez. der Abrechnungsart" );
  DlgAddField ( dlg, 18, 0, SetupGetAartKurz(iAbr), DLG_FIELD_ALL, 13 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 3, "~T~yp............:", SetupAbrHilf, " ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ³ Der Typ der Abrechnungsart" );
  DlgAddField ( dlg, 18, 0, abrTyp , DLG_FIELD_ALL, 1 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 4, "~B~etraglimit....:", SetupAbrHilf, " ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ³ Limit der Abrechnungsart" );
  if( SetupGetAartLimit(iAbr)<0 ) SetupSetAartLimit(iAbr,0);
  WaehrSetLength( 8 );
  WaehrPreis( SetupGetAartLimit(iAbr), cTemp );
  WaehrSetLength( 7 );
  DlgAddField ( dlg, 18, 0, cTemp, (7-info.preis_nachkomma)*10+info.preis_nachkomma, (info.preis_nachkomma==0) ? 6 : 7 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 5, "~E~xternes Prog..:", SetupAbrHilf, " ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ³ Das externe Programm fr diese Abrech.art" );
  DlgAddField ( dlg, 18, 0, SetupGetAartExternal(iAbr, cAartExt), DLG_FIELD_ALL, 8 );
  DlgInitEntry( dlg, 2, DLG_CHECK, 1, 7, "Enthalten im...", SetupAbrHilf, " ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ³ Weitere Angaben zur Abrechnungsart" );
  DlgAddField ( dlg, 1, 1, "~G~esamtumsatz", SetupGetAartGesFlag( iAbr ), 0 );
  DlgAddField ( dlg, 1, 2, "K~a~ssenumsatz", SetupGetAartKassenFlag( iAbr ), 0 );
  DlgInitEntry( dlg, 4, DLG_CHECK, 1, 11, "Sonstige Flags.", SetupAbrHilf, " ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ³ Weitere Angaben zur Abrechnungsart" );
  DlgAddField ( dlg, 1, 1, "~K~eine Schublade", SetupAartNoDrawer( iAbr ), 0 );
  DlgAddField ( dlg, 1, 2, "~R~ckgeld fragen", SetupAartAskMoney( iAbr ), 0 );
  DlgAddField ( dlg, 21, 1,"T~i~p erfragen", SetupAartAskTip( iAbr ), 0 );
  DlgAddField ( dlg, 21, 2,"G„~s~te erfragen", SetupAartAskGuests( iAbr ), 0 );
  while( !boFertig )
  {
   switch( DlgHandle( dlg, VioCenterCol( 56 ), VioCenterRow( 17 ), 56, 17, " Abrechnungsart editieren ", iExitKeys ) )
   {
    case T_ESC:
         boFertig = TRUE;
         break;
    case T_RETURN:
         if( *DlgGetText( dlg, 0, 0 )==0 /*|| *DlgGetText( dlg, 1, 0 ) == 0*/ )
         {
            printf( "%c", 7 );
            break;
         }
         if( !SetupSetAartExternal(iAbr, DlgGetText(dlg, 4, 0)) )
         {
          WinMsgCenter(" Fehler beim Abspeichern der Abrechngsdaten", MSG_INFO);
          break;
         }
         SetupSetAartName( iAbr, DlgGetText( dlg, 0, 0 ) );
         SetupSetAartKurz( iAbr, DlgGetText( dlg, 1, 0 ) );
         strcpy( abrTyp, DlgGetText( dlg, 2, 0 ) );
         SetupSetAartTyp( iAbr, abrTyp[0] );
         SetupSetAartLimit( iAbr, WaehrGetLong( DlgGetText( dlg, 3, 0 ) ) );
         SetupSetAartGesFlag( iAbr, DlgIsMarked( dlg, 5, 0 ) );
         SetupSetAartKassenFlag( iAbr, DlgIsMarked( dlg, 5, 1 ) );
         SetupAartSetNoDrawer( iAbr, DlgIsMarked( dlg, 6, 0 ) );
         SetupAartSetAskMoney( iAbr, DlgIsMarked( dlg, 6, 1 ) );
         SetupAartSetAskTip( iAbr, DlgIsMarked( dlg, 6, 2 ) );
         SetupAartSetAskGuests( iAbr, DlgIsMarked( dlg, 6, 3 ) );
         boFertig = boRet = TRUE;
    break;
    case T_F2:
         EditAbrText( iAbr+1 );       // abr = Die AbrechnungsArt (pos der liste )
    break;
   }
  }
  DlgDone( dlg );
  return( boRet );
 }

 PRIVATE VOID CDECL          SetupAbrHilf  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
#if( defined LIGHT )
  WinMsgCenter( " Hilfe zu den Abrechnungsarten\n\n"
                " Geben Sie die Namen der Abrechnungsarten an und ob diese im  Gesamt-\n"
                " umsatz und im Kassenbetrag der Kellner bercksichtigt werden sollen.\n\n"
                " Im Typ einer Abrechnungsart kann folgendes festgelegt werden:\n\n"
                " Typ = 'S': A.Art wird beim Finanzsplitting aufgefhrt\n"
                " Typ = 'T': Bei dieser A.Art wird der Tip (Trinkgeld) verwaltet\n"
                " Typ = 'K': Kombination aus 'S' und 'T' (Finanzspl. und Trinkgeld)\n"
                "\n Pseudo-Abrechnungsarten klein 's' und 't' siehe Handbuch!"
              , MSG_INFO
              );
#elif( defined IPC80 )
   WinMsgCenter( " Hilfe zu den Abrechnungsarten\n\n"
                 " Geben Sie die Namen der Abrechnungsarten an und ob diese im  Gesamt-\n"
                 " umsatz und im Kassenbetrag der Kellner bercksichtigt werden sollen.\n"
                 " Die  FDS 2900 kann maximal 13 A.Arten verwalten,  wenn Sie mehr ein-\n"
                 " geben, so werden diese ignoriert.\n\n"
                 " Im Typ einer Abrechnungsart kann folgendes festgelegt werden:\n\n"
                 " Typ = 'S': A.Art wird beim Finanzsplitting aufgefhrt\n"
                 " Typ = 'H': Diese A.Art dient zur Aktivierung der Hotel-Schnittstelle\n"
                 "            (diese muá kostenpflichtig erworben werden)\n"
                 " Typ = 'E': Startet externes Programm (z.B: Kundendatenbank)\n"
                 "            (diese muá kostenpflichtig erworben werden)\n"
                 "\n Benutzen Sie fr die FDS 2900 nur die oben angegebenen Typen!"
               , MSG_INFO
             );
#else
   WinMsgCenter( " Hilfe zu den Abrechnungsarten\n\n"
                 " Geben Sie die Namen der Abrechnungsarten an und ob diese im  Gesamt-\n"
                 " umsatz und im Kassenbetrag der Kellner bercksichtigt werden sollen.\n\n"
                 " Im Typ einer Abrechnungsart kann folgendes festgelegt werden:\n\n"
                 " Typ = 'S': A.Art wird beim Finanzsplitting aufgefhrt\n"
                 " Typ = 'T': Bei dieser A.Art wird der Tip (Trinkgeld) verwaltet\n"
                 " Typ = 'K': Kombination aus 'S' und 'T' (Finanzspl. und Trinkgeld)\n"
                 " Typ = 'H': Kennzeichnet A.Art als 'AUF ZIMMER' mit Online-Schnittst.\n"
                 "            (die Schnittstelle zus„tzlich per Schalter aktivieren!)\n"
                 " Typ = 'E': Startet externes Programm, das per Schalter def. wurde\n"
                 "\n Pseudo-Abrechnungsarten klein 's' und 't' siehe Handbuch!"
               , MSG_INFO
             );
#endif
 }
