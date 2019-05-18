 #include       "gastro/Setup.h"
 #include       "hilevel/Vio.h"
 #include       "hilevel/Dlg.h"
 #include       "hilevel/LstWin.h"
 #include       "hilevel/MsgWin.h"
 #include       "basics/Disk.h"
 #include       "basics/MemAlloc.h"
 #include       "defs/Keydefs.h"
 #include       "defs/Errordef.h"
 #include       <string.h>
 #include       <stdio.h>
 #include       <stdlib.h>

 VOID CDECL     SetupLayMenu (INT device);

 VOID CDECL     SetupDruckList( void );          // Menuepunkt Drucker einrichten
 PRIVATE VOID CDECL     SetupDruckHelp( void );          // Hilfe zur Auswahlliste der Drucker
 PRIVATE VOID CDECL     SetupFiscalHelp( SDlg* );          // Hilfe zur Auswahlliste der Drucker
 PRIVATE VOID CDECL     SetupLayoutHelp( SDlg* );          // Hilfe zur Auswahlliste der Drucker
 BOOL CDECL             SetupDruckEdit( INT );           // Maske zum Editieren der Druckerdaten
 PRIVATE INT  CDECL     SetupSaveDev( INT, INT[11][10] );
 PRIVATE INT  CDECL     SetupLoadDev( INT );
 PRIVATE VOID CDECL     SetupTranslate( INT );
 PRIVATE VOID CDECL     SetupTransHelp( SDlg* );
 PRIVATE VOID CDECL     SetupLenHelp  ( SDlg* );
 PRIVATE VOID CDECL     SetupLeftHelp ( SDlg* );
 PRIVATE VOID CDECL     SetupFirstHelp( SDlg* );
 PRIVATE VOID CDECL     SetupNextHelp ( SDlg* );
 PRIVATE VOID CDECL     SetupGuestHelp( SDlg* );
 PRIVATE VOID CDECL     SetupConnectHelp( SDlg* );
 PRIVATE VOID CDECL     SetupSteuerHilf( SDlg* );
 PRIVATE VOID CDECL     GetSteuer( CHAR*, CHAR, INT, INT );

 PRIVATE VOID CDECL     SetupDruckHelp ( void )
 {
  WinMsgCenter( " WÑhlen Sie aus dieser Liste den Drucker\n"
                " aus, dessen Einstellungen Sie Åberarbeiten\n"
                " mîchten.\n"
              , MSG_INFO
              );
 }

 VOID CDECL     SetupDruckList( void )
 {
  SLst*         lst;
//  INT           DruckExit[]  = { T_INS, T_DEL, 0 };
  BOOL          boFertig     = FALSE;
  INT           i;
/*
  if( SetupGetDruckerCount()==0 )
   if( !SetupDruckEdit( -1 ) ) return;
*/
  lst = LstInit( 76 );
/*
  for( i=0; i<SetupGetDruckerCount(); i++ )
   ListInsert( &DruckList, SetupGetDruckerName( i ) );
*/                       //123456789012345678901
#ifndef LIGHT
  for( i=0; i<8; i++ )
   LstInsert( lst, (LONG) i, "  %hd. Bondrucker      (%-30s)", i+1, SetupGetDevName(i) );
#else
 #ifdef OMRON
  for( i=0; i<2; i++ )
   LstInsert( lst, (LONG) i, "  %hd. Bondrucker      (%-30s)", i+1, SetupGetDevName(i) );
 #else
   LstInsert( lst, (LONG) 0, "  %hd. Bondrucker      (%-30s)", 1, SetupGetDevName(0) );
 #endif
#endif
  LstInsert( lst, 8L, "  Rechnungsdrucker   (%-30s)", SetupGetDevName( 8) );
  LstInsert( lst, 9L, "  Journaldrucker     (%-30s)", SetupGetDevName( 9) );
  LstInsert( lst,10L, "  Auswertungsdrucker (%-30s)", SetupGetDevName(10) );
  LstInsert( lst,11L, "  Pflegedrucker      (%-30s)", SetupGetDevName(11) );
/*
  ListInsert( &DruckList, "   1. Bondrucker" );
  ListInsert( &DruckList, "   2. Bondrucker" );
  ListInsert( &DruckList, "   3. Bondrucker" );
  ListInsert( &DruckList, "   4. Bondrucker" );
  ListInsert( &DruckList, "   5. Bondrucker" );
  ListInsert( &DruckList, "   6. Bondrucker" );
  ListInsert( &DruckList, "   7. Bondrucker" );
  ListInsert( &DruckList, "   8. Bondrucker" );
  ListInsert( &DruckList, "   Rechnungsdrucker" );
  ListInsert( &DruckList, "   Journaldrucker" );
  ListInsert( &DruckList, "   Auswertung" );
  ListInsert( &DruckList, "   Pflege" );
*/
  while( !boFertig )
  {
//   switch( ListShow( &DruckList, "Drucker auswÑhlen", " [F1] Hilfe  [INS] Neuer Drucker  [DEL] Drucker lîschen", DruckExit ) )
 #if( !defined LIGHT )
   switch( LstShow( lst, LST_LIST, VioCenterCol( 60 ), VioCenterRow( 12 )+2, 60, 14, " Drucker auswÑhlen ", " ~F1~ Hilfe  ≥ WÑhlen Sie einen Drucker zum Bearbeiten aus", NULL, SetupDruckHelp ) )
 #else
  #ifdef OMRON
   switch( LstShow( lst, LST_LIST, VioCenterCol( 60 ), VioCenterRow( 6 )+2, 60, 8, " Drucker auswÑhlen ", " ~F1~ Hilfe  ≥ WÑhlen Sie einen Drucker zum Bearbeiten aus", NULL, SetupDruckHelp ) )
  #else
   switch( LstShow( lst, LST_LIST, VioCenterCol( 60 ), VioCenterRow( 6 )+2, 60, 7, " Drucker auswÑhlen ", " ~F1~ Hilfe  ≥ WÑhlen Sie einen Drucker zum Bearbeiten aus", NULL, SetupDruckHelp ) )
  #endif
 #endif
   {
    case T_ESC:
         boFertig = TRUE;
         break;
/*
    case T_INS:
         if( SetupDruckEdit( -1 ) )
          ListInsert( &DruckList, SetupGetDevName( SetupGetDruckerCount()-1 ) );
         break;
    case T_DEL:
         i = ListGetSelect( &DruckList );
         ListDelEntry( &DruckList, i );
         SetupDelDrucker( i );
         if( SetupGetDruckerCount() == 0 )
          if( !SetupDruckEdit( -1 ) ) fertig = TRUE;
         break;
*/
    case T_RETURN:
         i = (INT) LstGetNum( lst );
         if( SetupDruckEdit( i ) )
         {
          CHAR cTemp[80];
          strcpy( cTemp, LstGetStr( lst, i ) );
          sprintf( &cTemp[21], "(%-30s)", SetupGetDevName( i ) );
          LstChange( lst, (LONG) i, (LONG) i, cTemp );
         }
         break;
   }
  }
  LstDone( lst );
 }

 BOOL CDECL SetupDruckEdit ( iPrn )
 INT            iPrn;
 {
  SDlg*         dlg;
  CHAR          cTemp[100];
  CHAR          cTmp2[20];
  CHAR          cStatus[100];
//  CHAR          ComPort[3];
  INT           exits[]        = { T_F2, T_F3, T_F5, T_F10, 0 };
  INT           i;
  CHAR*         cp;
  INT           iLen;
  INT           steuer[11][10];
  BOOL          boFertig       = FALSE;
  BOOL          boRet          = FALSE;
  int           iMaxStatus = VioGetMaxCol();
  extern BOOL inSetup;
  inSetup = TRUE;
  if( iMaxStatus>sizeof(cStatus)-1 )
   iMaxStatus = sizeof(cStatus)-1;
#ifndef OMRON
  #define       MAX          16
#else
  #define       MAX          17
#endif
 AGAIN:
  cTmp2[2] = 0;
  strncpy( cStatus, " ~F1~ Hilfe  ~F2~ Laden  ~F3~ Sichern  ~F5~ Layout  ~F10~ öbersetzungstabelle", iMaxStatus );
  cStatus[iMaxStatus] = 0;
  dlg = DlgInit( ( iPrn>=LPT1 ) ? 22 : MAX );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 0, "Name des ~D~ruckers:", SetupSteuerHilf, cStatus );
  DlgAddField ( dlg, 21, 0, SetupGetDevName(iPrn), DLG_FIELD_ALL, 30 );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1, 2, "I~n~itfolge 1...:", SetupSteuerHilf, cStatus );
  iLen = SetupGetSteuercode( iPrn, STEUER_INIT, cTemp );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  DlgInitEntry( dlg, 10, DLG_INPUT, 1, 3, "Initf~o~lge 2...:", SetupSteuerHilf, cStatus );
  for( i=10; i<20; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*(i-10), 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  DlgInitEntry( dlg, 10, DLG_INPUT, 1, 4, "Initfol~g~e 3...:", SetupSteuerHilf, cStatus );
  for( i=20; i<30; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*(i-20), 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  iLen = SetupGetSteuercode( iPrn, STEUER_ENDE, cTemp );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1, 5, "Ende-Se~q~uenz..:", SetupSteuerHilf, cStatus );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  iLen = SetupGetSteuercode( iPrn, STEUER_CUT, cTemp );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1, 6, "Ab~s~chnitt/Rel.:", SetupSteuerHilf, cStatus );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  iLen = SetupGetSteuercode( iPrn, STEUER_PERF, cTemp );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1, 7, "~P~erforieren...:", SetupSteuerHilf, cStatus );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  iLen = SetupGetSteuercode( iPrn, STEUER_LF, cTemp );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1, 8, "Neue ~Z~eile....:", SetupSteuerHilf, cStatus );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  iLen = SetupGetSteuercode( iPrn, STEUER_BREIT_EIN, cTemp );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1, 9, "Breit e~i~n.....:", SetupSteuerHilf, cStatus );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  iLen = SetupGetSteuercode( iPrn, STEUER_BREIT_AUS, cTemp );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1,10, "B~r~eit aus.....:", SetupSteuerHilf, cStatus );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg, 18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  iLen = SetupGetSteuercode( iPrn, STEUER_FETT_EIN, cTemp );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1,11, "Fett~/~Farbe ein:", SetupSteuerHilf, cStatus );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg,18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }
  iLen = SetupGetSteuercode( iPrn, STEUER_FETT_AUS, cTemp );
  DlgInitEntry( dlg, 10, DLG_INPUT, 1,12, "Fe~t~t/Farbe aus:", SetupSteuerHilf, cStatus );
  for( i=0; i<10; i++ )
  {
   GetSteuer( cTmp2, cTemp[i], i, iLen );
   DlgAddField( dlg,18+4*i, 0, cTmp2, DLG_FIELD_ALL, 2 );
  }

  DlgInitEntry( dlg, 1, DLG_CHECK, 1,14, "", SetupLayoutHelp, cStatus );
  DlgAddField ( dlg, 0, 0, "Eigenes Layout", SetupPrnIsLayout( iPrn ), 0 );

  if( iPrn>=LPT1 )
  {
   DlgInitEntry( dlg, 1, DLG_CHECK, 1,15, "", SetupFiscalHelp, cStatus );
   DlgAddField ( dlg, 0, 0, "Fiscal ~h~andling", SetupPrnIsFiscal( iPrn ), 0 );
   sprintf( cTemp, "%2hd", SetupGetPageLen( iPrn ) );
   DlgInitEntry( dlg, 1, DLG_INPUT, 1,16, "SeitenlÑn~g~e.............:", SetupLenHelp, cStatus );
   DlgAddField ( dlg, 27, 0, cTemp, 20, 2 );
   sprintf( cTemp, "%2hd", SetupGetLinkerRand( iPrn/*-LPT1*/ ) );
   DlgInitEntry( dlg, 1, DLG_INPUT, 1,17, "Lin~k~er Rand.............:", SetupLeftHelp, cStatus );
   DlgAddField ( dlg, 27, 0, cTemp, 20, 2 );
   sprintf( cTemp, "%2hd", SetupGetKopflen1( iPrn ) );
   DlgInitEntry( dlg, 1, DLG_INPUT, 1,18, "~1~. Blatt, Leerzeilen....:", SetupFirstHelp, cStatus );
   DlgAddField ( dlg, 27, 0, cTemp, 20, 2 );
   sprintf( cTemp, "%2hd", SetupGetKopflen2( iPrn ) );
   DlgInitEntry( dlg, 1, DLG_INPUT, 1,19, "~F~olgeblÑtter, Leerzeilen:", SetupNextHelp, cStatus );
   DlgAddField ( dlg, 27, 0, cTemp, 20, 2 );
   DlgInitEntry( dlg, 1, DLG_CHECK, 1,20, "G~u~estcheck..............:", SetupGuestHelp, cStatus );
   DlgAddField ( dlg, 27, 0, "", SetupIsEinzelblatt( iPrn ), 0 );
   DlgInitEntry( dlg,10, DLG_RADIO,33,16, "Angeschlossen an:", SetupConnectHelp, cStatus );
   i = SetupGetZusatzDev( iPrn );
   DlgAddField ( dlg,  1, 1, "COM ~1~", i==BON1, 0 );
   DlgAddField ( dlg,  1, 2, "COM ~2~", i==BON2, 0 );
   DlgAddField ( dlg,  1, 3, "COM ~3~", i==BON3, 0 );
   DlgAddField ( dlg,  1, 4, "COM ~4~", i==BON4, 0 );
   DlgAddField ( dlg, 11, 1, "COM ~5~", i==BON5, 0 );
   DlgAddField ( dlg, 11, 2, "COM ~6~", i==BON6, 0 );
   DlgAddField ( dlg, 11, 3, "COM ~7~", i==BON7, 0 );
#ifndef OMRON
   DlgAddField ( dlg, 11, 4, "COM ~8~", i==BON8, 0 );
#else
   DlgAddField ( dlg, 11, 4, "IM~C~  ", i==BON8, 0 );
#endif
   DlgAddField ( dlg, 21, 1, "~L~PT 1", i==LPT1, 0 );
   DlgAddField ( dlg, 21, 2, "L~P~T 2", i==LPT2, 0 );
  }
#ifdef OMRON
  else
  {
   DlgInitEntry( dlg, 1 , DLG_CHECK, 1,15, "", NULL, cStatus );
   DlgAddField ( dlg, 0 , 0, "~A~nsteuerung Åber IMC-Karte", SetupGetImcFlag( iPrn ), 0 );
  }
#endif
  while( !boFertig )
  {
   if( iPrn>=LPT1 )
    i = DlgHandle( dlg, VioCenterCol( 66 ), VioCenterRow( 23 )-1, 66, 23, " Drucker ", exits );
   else
    i = DlgHandle( dlg, VioCenterCol( 64 ), VioCenterRow( 18 ), 64, 18, " Drucker ", exits );
   switch( i )
   {
    case T_ESC:
         boFertig = TRUE;
         break;
    case T_F5:
         SetupLayMenu(iPrn);
         break;
    case T_RETURN:
         SetupSetDevName( iPrn, DlgGetText( dlg, 0, 0 ) );
/*
         for( iLen=0; iLen<11; iLen++ )
         {
          for( i=0; i<10; i++ )
          {
           cTemp[i] = -1;
           cp = DlgGetText( dlg, iLen+1, i );
           if( cp[0]!=0 )
           {
            if( sscanf( cp, "%hx", &steuer[0][0] ) != EOF )
             cTemp[i] = (CHAR) steuer[0][0];
           }
          }
          cTemp[10] = 0;
//          SetupSetSteuercode( iLen, i, cTemp );
          SetupSetSteuercode( iPrn, iLen, cTemp );
         }
//           SetupSetSteuercode( , iPrn, n, i );
*/
         SetupPrnSetLayout( iPrn, DlgIsMarked( dlg, 12, 0 ) );

         if( iPrn>=LPT1 )
         {
          SetupPrnSetFiscal( iPrn, DlgIsMarked( dlg, 13, 0 ) );
          SetupSetPageLen( iPrn, atoi( DlgGetText( dlg, 14, 0 ) ) );
          SetupSetLinkerRand( iPrn/*-LPT1*/, atoi( DlgGetText( dlg, 15, 0 ) ) );
          SetupSetKopflen1( iPrn, atoi( DlgGetText( dlg, 16, 0 ) ) );
          SetupSetKopflen2( iPrn, atoi( DlgGetText( dlg, 17, 0 ) ) );
          SetupSetEinzelblatt( iPrn, DlgIsMarked( dlg, 18, 0 ) );
          SetupSetZusatzDev( iPrn, DlgGetSelect( dlg, 19 ) );
         }
 #ifdef OMRON
         else
          SetupSetImcFlag( iPrn, DlgIsMarked( dlg, 13, 0 ) );
 #endif
         for( iLen=0; iLen<11; iLen++ )
         {
          for( i=0; i<10; i++ )
          {
           cTemp[i] = -1;
           cp = DlgGetText( dlg, iLen+1, i );
           if( cp[0]!=0 )
           {
            int p = sscanf( cp, "%hx", &steuer[0][0] );
            if( p != EOF  && p != 0 )
             cTemp[i] = (CHAR) steuer[0][0];
           }
          }
          cTemp[10] = 0;
//          SetupSetSteuercode( iLen, i, cTemp );
          SetupSetSteuercode( iPrn, iLen, cTemp );
         }
         boFertig = boRet = TRUE;
         break;
    case T_F2:
         switch( SetupLoadDev( iPrn ) )
         {
          case -1:
               break;
          case ERR_NONE:
               WinMsgCenter( " Die Einstellungen wurden geladen!", MSG_INFO );
               DlgDone( dlg );
               goto AGAIN;
          case ERR_DISK_OPEN:
               WinMsgCenter( " Fehler beim ôffnen der Datei!", MSG_INFO );
               break;
          case ERR_DISK_READ:
               WinMsgCenter( " Fehler beim Lesen aus der Datei!", MSG_INFO );
               break;
          default:
               WinMsgCenter( " Fehler beim Laden der Einstellungen!", MSG_INFO );
         }
         break;
    case T_F3:
         for( iLen=0; iLen<11; iLen++ )
         {
          MemFill( steuer[iLen], -1, 10*sizeof(INT) );
          for( i=0; i<10; i++ )
          {
           cp = DlgGetText( dlg, iLen+1, i );
           if( *cp==0 ) steuer[iLen][i] = -1;
           else
            sscanf( cp, "%x", &steuer[iLen][i] );
          }
/*
          cTemp[0] = 0;
          for( i=0; i<10; i++ ) strcat( cTemp, DlgGetText( dlg, iLen+1, i ) );
          for( i=0; i*2<strlen(cTemp); i++ ) sscanf( &cTemp[i<<1], "%2X", &steuer[iLen][i] ); //= cTemp[i];
*/
         }
         switch( SetupSaveDev( iPrn, steuer ) )
         {
          case -1:
               break;
          case ERR_NONE:
               WinMsgCenter( " Die Einstellungen wurden gesichert!", MSG_INFO );
               break;
          case ERR_DISK_CREATE:
               WinMsgCenter( " Fehler beim Erzeugen der Datei!", MSG_INFO );
               break;
          case ERR_DISK_WRITE:
               WinMsgCenter( " Fehler beim Schreiben in die Datei!", MSG_INFO );
               break;
          default:
               WinMsgCenter( " Fehler beim Sichern der Einstellungen!", MSG_INFO );
         }
         break;
    case T_F10:
         SetupTranslate( iPrn );
         break;
   }
  }
  DlgDone( dlg );
  return( boRet );
 }

 PRIVATE INT CDECL SetupSaveDev( device, steuer )
 INT            device;
 INT            steuer[11][10];
 {
  #define       RetErr( ret ) { DskFileClose( fh ); return( ret ); }
  extern SETUP  abrech;
  SFile*        fh;
  CHAR          path[100];
  SDlg*         dlg;
  BOOL          boWrite;
  INT           i;
  dlg = DlgInit( 1 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 3, 1, "Dateiname:", NULL, "Unter welchem Dateinamen sollen die Einstellungen gesichert werden ?" );
  DlgAddField ( dlg, 15, 0, NULL, DLG_FIELD_ALL, 8 );
  boWrite = ( DlgHandle( dlg, VioCenterCol( 29 ), VioCenterRow( 5 ), 29, 5, " Device sichern", NULL ) == T_RETURN );
  if( boWrite )
  {
   sprintf( path, "SETUP\\%s.DEV", DlgGetText( dlg, 0, 0 ) );
   if( ( fh = DskFileOpen( path, "r" ) ) != NULL )
   {
    DskFileClose( fh );
    if( WinMsgCenter( "          ACHTUNG!\n"
                      " Die angegebene Datei existiert\n"
                      " bereits. Daten Åberschreiben?"
                    , MSG_YESNO
                  ) != T_RETURN
      )
    {
     DlgDone( dlg );
     return( -1 );
    }
   }
   fh = DskFileOpen( path,"wb" );
   if( fh == NULL ) return( ERR_DISK_CREATE );
   if( !DskFileWrite( "GFV5", 4, sizeof( CHAR ) ,fh ) ) RetErr( ERR_DISK_WRITE );
   if( !DskFileWrite( abrech.druckertyp[device], sizeof( CHAR ), 30, fh ) ) RetErr( ERR_DISK_WRITE );
   for( i=0; i<11; i++ )
    if( !DskFileWrite( steuer[i], 10*sizeof( INT ), 1, fh ) ) RetErr( ERR_DISK_WRITE );
   if( !DskFileWrite( &abrech.translate[device], sizeof( TABELLE ), 1, fh ) ) RetErr( ERR_DISK_WRITE );
   DskFileClose( fh );
   DlgDone( dlg );
   return( ERR_NONE );
  }
  DlgDone( dlg );
  return( -1 );
  #undef RetErr
 }

 PRIVATE INT CDECL      SetupLoadDev( device )
 INT            device;
 {
  #define       RetErr( ret ) { LstDone( lst ); DskFileClose( fh ); return( ret ); }
  extern SETUP  abrech;
  SFile*        fh;
  SLst*         lst;
  SFindT        find;
  CHAR*         cp;
  CHAR          path[100];
  BOOL          boFertig;
  INT           i;
  LONG          lCount       = 0L;
  if( WinMsgCenter( "              ACHTUNG!\n"
                    " Beim Laden von Druckereinstellungen\n"
                    " werden die alten Werte Åberschrieben!"
                  , MSG_YESNO
                  ) == T_ESC
    ) return( -1 );
  lst = LstInit( 14 );
  boFertig = DskFindFirst( "SETUP\\*.DEV", DSK_A_NORMAL, &find );
  while( !boFertig )
  {
   cp = strchr( find.name, '.' );
   *cp = 0;
   LstInsert( lst, lCount++, "%-8.8s.%-3.3s", strupr(find.name), strupr(cp+1) );
   boFertig = DskFindNext( &find );
  }
  if( lCount==0L )
  {
   LstDone( lst );
   WinMsgCenter( " Es existieren keine Treiber.\n"
                 " Bitte ÅberprÅfen Sie die\n"
                 " Installation..."
               , MSG_INFO
               );
   return( -1 );
  }
  if( LstShow( lst, LST_LIST, VioGetMaxCol()-30,12, 15,12, "SETUP\\*.DEV", " WÑhlen Sie den zu ladenden Treiber", NULL, NULL ) == T_RETURN )
  {
   sprintf( path, "SETUP\\%s", LstGetStr( lst, LstGetNum( lst ) ) );
   fh = DskFileOpen( path, "rb" );
   if( fh==NULL ) return( ERR_DISK_OPEN );
   if( !DskFileRead( path, 4, sizeof( CHAR ), fh ) ) RetErr( ERR_DISK_READ );
   if( !DskFileRead( abrech.druckertyp[device], 30, sizeof( CHAR ), fh ) ) RetErr( ERR_DISK_READ );
   for( i=0; i<11; i++ )
    if( !DskFileRead( abrech.steuer[device][i], 10*sizeof( INT ), 1, fh ) ) RetErr( ERR_DISK_READ );
   if( !DskFileRead( &abrech.translate[device], sizeof( TABELLE ), 1, fh ) ) RetErr( ERR_DISK_READ );
  }
  RetErr( ERR_NONE );
  #undef RetErr
 }

 PRIVATE VOID CDECL     SetupTranslate( device )
 INT            device;
 {
  extern SETUP  abrech;
  SDlg*         dlg;
  CHAR          cOrig[5];
  CHAR          cTrans[5];
  INT           i;
  INT           wert;
  dlg = DlgInit( 15 );
  for( i=0; i<15; i++ )
  {
   DlgInitEntry( dlg, 2, DLG_INPUT, 2, i+1, "Original:      Ersetzung:", SetupTransHelp, " ~F1~ Hilfe ≥ öbersetzungstabelle fÅr Druckerzeichen" );
   sprintf( cOrig, "%hX", abrech.translate[device].orginal[i] & 0xff );
   sprintf( cTrans, "%hX", abrech.translate[device].ersetze[i] & 0xff );
   DlgAddField( dlg, 11, 0, cOrig, DLG_FIELD_HEX, 2 );
   DlgAddField( dlg, 27, 0, cTrans, DLG_FIELD_HEX, 2 );
  }
  if( DlgHandle( dlg, VioGetMaxCol()-37, 3, 34, 19, " öbersetzungstabelle ", NULL ) == T_RETURN )
  {
   for(i=0;i<15;i++)
   {
    sscanf( DlgGetText( dlg, i, 0 ), "%hx", &wert );
    abrech.translate[device].orginal[i] = (CHAR) wert;
    sscanf( DlgGetText( dlg, i, 1 ), "%hx", &wert );
    abrech.translate[device].ersetze[i] = (CHAR) wert;
   }
  }
  DlgDone( dlg );
 }

 PRIVATE VOID CDECL      SetupTransHelp( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie hier in hexadezimaler Notation die\n"
                " Zeichen an, die beim Ausdruck umgewandelt\n"
                " werden sollen.\n"
                " Dies ermîglicht es beispielsweise, Umlaute\n"
                " auf Druckern auszugeben, deren Zeichentabelle\n"
                " anders eingestellt ist als auf dem PC."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetupLenHelp ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie die LÑnge einer Seite\n"
                " in Zeichen an."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetupLeftHelp ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie die Anzahl der Zeichen an,\n"
                " um die der Ausdruck nach rechts\n"
                " verschoben werden soll."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL      SetupFirstHelp ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie die Anzahl der Zeilen an,\n"
                " die bei der ersten Seite eines\n"
                " Ausdrucks Åbersprungen werden."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetupNextHelp ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie die Anzahl der Zeilen an,\n"
                " die bei den folgenden Seiten eines\n"
                " Ausdrucks Åbersprungen werden."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL      SetupGuestHelp ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie an, ob der Drucker ein\n"
                " Guestcheck ist, d.h. bei jedem\n"
                " Ausdruck nach einer Seite verlangt\n"
                " werden soll."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL      SetupFiscalHelp ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie an, ob der Drucker ein\n"
                " Fiscal-Drucker ist, d.h. da· die\n"
                " zu druckenden Daten anhand der \n"
                " Tischdaten vom Drucker selbst\n"
                " ermittelt werden."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL      SetupLayoutHelp ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie an, ob der Drucker ein eigenes Layout\n"
                " beesitzt. Dieses wird in der Datei LAYOUTS.INI im\n"
                " Verzeichnis DATA gespeichert. Die EintrÑge werden\n"
                " in der dem Druckernamen entsprechenden Sektion\n"
                " abgelegt."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL      SetupConnectHelp ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie hier die Schnittstelle\n"
                " an, an der der Drucker angeschlos-\n"
                " sen ist."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL      SetupSteuerHilf( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
#ifndef LIGHT
  WinMsgCenter( " Hilfe zu den Steuerzeichen\n\n"
                " Hier kînnen Sie jedem der 8 seriellen und 2 parallelen Ports des\n"
                " Rechners einen individuellen Drucker zuordenen. Tragen Sie in die \n"
                " Felder hinter der Beschreibung die Steuerzeichen des angeschlossenen\n"
                " Druckers in HEXADEZIMALER Notation ein.\n\n"
                " Mit Taste [F2] kînnen auch fertige Druckereinstellungen laden.\n"
                " Mit Taste [F3] kînnen Sie Ihre eigenen Einstellungen sichern.\n\n"
                " Mit Taste [F10] kînnen Sie eine öbersetzungstabelle pflegen, die\n"
                " dann notwendig ist, wenn der Drucker keinen PC-Zeichensatz beherrscht.\n\n"
                " Eine genauere Beschreibung entnehmen Sie Ihrem Handbuch!"
              , MSG_INFO
              );
#else
#ifndef OMRON
  WinMsgCenter( " Hilfe zu den Steuerzeichen\n\n"
                " Hier kînnen Sie jeden Drucker, der an Ihrem PC angeschlossen ist,\n"
                " an GastroFix anpassen. Die Light-Version erlaubt nur einen Drucker!\n"
                " Tragen Sie in die Felder hinter der Beschreibung die Steuerzeichen\n"
                " des angeschlossenen Druckers in HEXADEZIMALER Notation ein.\n\n"
                " Mit Taste [F2] kînnen auch fertige Druckereinstellungen laden.\n"
                " Mit Taste [F3] kînnen Sie Ihre eigenen Einstellungen sichern.\n\n"
                " Mit Taste [F10] kînnen Sie eine öbersetzungstabelle pflegen, die\n"
                " dann notwendig ist, wenn der Drucker keinen PC-Zeichensatz beherrscht.\n\n"
                " Eine genauere Beschreibung entnehmen Sie Ihrem Handbuch!"
              , MSG_INFO
              );
#else
  WinMsgCenter( " Hilfe zu den Steuerzeichen\n\n"
                " Hier kînnen Sie jeden Drucker, der an Ihrem PC angeschlossen ist,\n"
                " an OMRON Gastro 7000 anpassen. Die Light-Version erlaubt maximal \n"
                " zwei Drucker!\n"
                " Tragen Sie in die Felder hinter der Beschreibung die Steuerzeichen\n"
                " des angeschlossenen Druckers in HEXADEZIMALER Notation ein.\n\n"
                " Mit Taste [F2] kînnen auch fertige Druckereinstellungen laden.\n"
                " Mit Taste [F3] kînnen Sie Ihre eigenen Einstellungen sichern.\n\n"
                " Mit Taste [F10] kînnen Sie eine öbersetzungstabelle pflegen, die\n"
                " dann notwendig ist, wenn der Drucker keinen PC-Zeichensatz beherrscht.\n\n"
                " Eine genauere Beschreibung entnehmen Sie Ihrem Handbuch!"
              , MSG_INFO
              );
#endif
#endif
 }

 PRIVATE VOID CDECL  GetSteuer( pcDest, cSrc, i, iLen )
 CHAR*          pcDest;
 CHAR           cSrc;
 INT            i;
 INT            iLen;
 {
  pcDest[0] = pcDest[1] = pcDest[2] = 0;
  if( i>=iLen ) return;
  if( ((INT)(cSrc&0xFF)==255) /*|| ((INT)(cSrc&0xFF)==32)*/ ) return;
  sprintf( pcDest, "%02hX", cSrc&0xFF );
 }

/*
 BOOL           SetupDruckEdit ( drucker )
 INT            drucker;
 {
  SDlg          DruckDlg;                        // Drucker-Dialog
  SDlgEntry*    Druck;
  #define       DruckName    0                   // Gruppe: Name des Druckers wird
  #define       DruckSeq     1                   // Gruppe: Name der Steuerdatei
  #define       DruckSeit    2                   // Gruppe: Laenge einer Seite
  #define       DruckZeil    3                   // Gruppe: Laenge einer Zeile
  #define       DruckLeft    4                   // Gruppe: Linker Rand
  #define       DruckEins    5                   // Gruppe: Linker Rand
  #define       DruckFolg    6                   // Gruppe: Linker Rand
  #define       DruckEinz    7                   // Gruppe: Linker Rand
  #define       DruckSchn    8                   // Gruppe: Linker Rand
  CHAR          name[41];
  CHAR          seq[9];
  CHAR          seite[4];
  CHAR          zeile[4];
  CHAR          links[4];
  CHAR          eins[4];
  CHAR          folge[4];
  CHAR          schnitt[3];
  BOOL          ret;
  if( ( Druck = MemAlloc( sizeof( SDlgEntry ) * 9 ) ) == NULL ) return( FALSE );
  if( DlgInit( &DruckDlg, 9 ) )
  {
   if( ( DlgInitEntry( &Druck[ DruckName ], 1, DLG_INPUT, 1, 1, "~N~ame des Druckers:", NULL, " ~F1~ Hilfe ≥ Name des Druckers" ) )
//    && ( DlgInitEntry( &Druck[ DruckSeq  ], 1, DLG_INPUT, 1, 2, "~S~teuerdatei......:", NULL, " ~F1~ Hilfe  [F2] Liste ≥ Name der Datei mit den Init-Squenzen" ) )
//    && ( DlgInitEntry( &Druck[ DruckZeil ], 1, DLG_INPUT, 1, 4, "~Z~eilenlÑnge.............:", NULL, " ~F1~ Hilfe ≥ LÑnge einer Druckerzeile in Zeichen" ) )
    && ( DlgInitEntry( &Druck[ DruckSeit ], 1, DLG_INPUT, 1, 5, "S~e~itenlÑnge.............:", NULL, " ~F1~ Hilfe ≥ LÑnge einer Druckerseite in Zeilen" ) )
    && ( DlgInitEntry( &Druck[ DruckLeft ], 1, DLG_INPUT, 1, 6, "~L~inker Rand.............:", NULL, " ~F1~ Hilfe ≥ Anzahl links einzufÅgender Leerzeichen" ) )
    && ( DlgInitEntry( &Druck[ DruckEins ], 1, DLG_INPUT, 1, 7, "~1~. Blatt, Leerzeilen....:", NULL, " ~F1~ Hilfe ≥ Anzahl der Leerzeilen beim ersten Blatt" ) )
    && ( DlgInitEntry( &Druck[ DruckFolg ], 1, DLG_INPUT, 1, 8, "~F~olgeblÑtter, Leerzeilen:", NULL, " ~F1~ Hilfe ≥ Anzahl der Leerzeilen bei FolgeblÑttern" ) )
    && ( DlgInitEntry( &Druck[ DruckEinz ], 1, DLG_CHECK, 1,10, "", NULL, " ~F1~ Hilfe ≥ Ist der Drucker ein Guestcheck?" ) )
    && ( DlgInitEntry( &Druck[ DruckSchn ], 1, DLG_INPUT, 1,12, "S~c~hnittstelle:", NULL, " ~F1~ Hilfe  [F2] Liste ≥ Mit dem Drucker verbundene Schnittstelle" ) )
     )
   {
    if( drucker==-1 )
    {
     strcpy( name, "<KEIN>" );
     seq[0] = 0;
     sprintf( seite, "0" );
     sprintf( zeile, "0" );
     sprintf( links, "0" );
     sprintf( eins, "0" );
     sprintf( folge, "0" );
     sprintf( schnitt, "0" );
    }
    else
    {
     strncpy( name, setup_get_druckername( drucker ), 40 );
//     sprintf( seq, "%-8.8s", SetupGetDruckerSeq( drucker ) );
     sprintf( seite, "%d", setup_get_pagelen( drucker ) );
//     sprintf( zeile, "%d", SetupGetDruckerZeile( drucker ) );
     sprintf( links, "%d", setup_get_linkerrand( drucker ) );
     sprintf( eins, "%d", setup_get_kopflen1( drucker ) );
     sprintf( folge, "%d", setup_get_kopflen2( drucker ) );
     sprintf( schnitt, "%d", setup_get_zusatz_dev( drucker ) );
    }
    DlgAddField( &Druck[ DruckEinz ], DLG_CHECK, 1,10, 'B', "Einzel~b~latt", setup_is_einzelblatt( drucker ), 0 );
    DlgAddField( &Druck[ DruckName ], DLG_INPUT,21, 1, 'N', name, DLG_FIELD_ALL, 30 );
//    DlgAddField( &Druck[ DruckSeq  ], DLG_INPUT,21, 2, 'S', seq, DLG_FIELD_ALL, 8 );
//    DlgAddField( &Druck[ DruckZeil ], DLG_INPUT,28, 4, 'Z', zeile, DLG_FIELD_NUM, 3 );
    DlgAddField( &Druck[ DruckSeit ], DLG_INPUT,28, 5, 'E', seite, DLG_FIELD_NUM, 3 );
    DlgAddField( &Druck[ DruckLeft ], DLG_INPUT,28, 6, 'L', links, DLG_FIELD_NUM, 3 );
    DlgAddField( &Druck[ DruckEins ], DLG_INPUT,28, 7, '1', eins, DLG_FIELD_NUM, 3 );
    DlgAddField( &Druck[ DruckFolg ], DLG_INPUT,28, 8, 'F', folge, DLG_FIELD_NUM, 3 );
    DlgAddField( &Druck[ DruckSchn ], DLG_INPUT,17,12, 'C', schnitt, DLG_FIELD_NUM, 2 );
    DlgAddEntry( &DruckDlg, &Druck[ DruckName ] );
//    DlgAddEntry( &DruckDlg, &Druck[ DruckSeq ] );
//    DlgAddEntry( &DruckDlg, &Druck[ DruckZeil ] );
    DlgAddEntry( &DruckDlg, &Druck[ DruckSeit ] );
    DlgAddEntry( &DruckDlg, &Druck[ DruckLeft ] );
    DlgAddEntry( &DruckDlg, &Druck[ DruckEins ] );
    DlgAddEntry( &DruckDlg, &Druck[ DruckFolg ] );
    DlgAddEntry( &DruckDlg, &Druck[ DruckEinz ] );
//    DlgAddEntry( &DruckDlg, &Druck[ DruckSchn ] );
    if( DlgHandle( &DruckDlg, VioCenterX( 60 ), VioCenterY( 16 ), 60, 16, " Drucker ", NULL ) == 1 )
    {
     if( drucker==-1 )
     {
//      drucker = SetupGetDruckerCount();
//      SetupIncDruckerCount();
     }
     SetupSetDruckerName( drucker, name );
     SetupSetDruckerSeq( drucker, seq );
     SetupSetDruckerSeite( drucker, atoi( seite ) );
     SetupSetDruckerZeile( drucker, atoi( zeile ) );
     SetupSetDruckerLinks( drucker, atoi( links ) );
     SetupSetDruckerErstleer( drucker, atoi( eins ) );
     SetupSetDruckerFolgeLeer( drucker, atoi( folge ) );
     SetupSetDruckerDevice( drucker, atoi( schnitt ) );
     ret = TRUE;
    }
    else
     ret = FALSE;
   }
  }
  DlgDone( &DruckDlg );
  MemFree( Druck );
  return( ret );
 }

*/
