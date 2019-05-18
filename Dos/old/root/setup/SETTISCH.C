 #include       "gastro/Setup.h"
 #include       "gastro/SetTable.h"
 #include       "gastro/Info.h"
 #include       "gastro/Waehrung.h"
 #include       "hilevel/Dlg.h"
 #include       "hilevel/Vio.h"
 #include       "hilevel/LstWin.h"
 #include       "hilevel/MsgWin.h"
 #include       "basics/Inifile.h"
 #include       "basics/Disk.h"
 #include       "basics/MemAlloc.h"
 #include       "defs/Keydefs.h"
 #include       "defs/Errordef.h"
 #include       <stdlib.h>
 #include       <string.h>

 PRIVATE VOID CDECL     TablesInit    ( void );
 PRIVATE VOID CDECL     TablesDone    ( void );
 PRIVATE VOID CDECL     TablesHandle  ( void );
 PRIVATE LONG CDECL     TablesEdit    ( LONG );
 BOOL CDECL     SetupDrucker    ( INT*, BOOL );
 CHAR* CDECL    SetupGetTxtDruck( INT, CHAR* );

 PRIVATE VOID CDECL     SetTableNumHelp   ( SDlg* );
 PRIVATE VOID CDECL     SetTableNameHelp  ( SDlg* );
 PRIVATE VOID CDECL     SetTableKellHelp  ( SDlg* );
 PRIVATE VOID CDECL     SetTableAbrHelp   ( SDlg* );
 PRIVATE VOID CDECL     SetTableMwstHelp  ( SDlg* );
 PRIVATE VOID CDECL     SetTableEx1Help   ( SDlg* );
 PRIVATE VOID CDECL     SetTableEx2Help   ( SDlg* );
 PRIVATE VOID CDECL     SetTableEbnHelp   ( SDlg* );
 PRIVATE VOID CDECL     SetTableKstHelp   ( SDlg* );
 PRIVATE VOID CDECL     SetTableRDrHelp   ( SDlg* );

 PRIVATE SLst*  lstTables;
 PRIVATE LONG   lTableCount;

 VOID CDECL     TablesMain   ( void )
 {
  TablesInit();
  TablesHandle();
  TablesDone();
 }

 PRIVATE VOID CDECL     TablesInit    ( void )
 {
  #define FIRST_MATCH PATH_TBLINFO "\\TABLE*.INI"
  SFindT        find;
  BOOL          boFertig;
  LONG          lTisch;
  CHAR          cName[40];
  TableChkInfo();
  lstTables = LstInit( 50 );
  boFertig = DskFindFirst( FIRST_MATCH, DSK_A_NORMAL, &find );
  while( !boFertig )
  {
   sscanf( find.name, "TABLE%ld", &lTisch );
   if( !TableGetName( lTisch*100L, cName ) )
    cName[0] = 0;
   lTableCount++;
   LstInsert( lstTables, lTisch, "Tisch %3ld  %s", lTisch, cName );
   boFertig = DskFindNext( &find );
  }
 }

 PRIVATE VOID CDECL     TablesDone   ( void )
 {
  LstDone( lstTables );
 }

 PRIVATE VOID CDECL     TablesHandle  ( void )
 {
  INT            iRet;
  LONG           lNum;
  INT            Exit[]      = { T_INS, T_DEL, 0 };
  BOOL           boFertig    = FALSE;
  CHAR          cName[40];
  while( !boFertig )
  {
   if( lTableCount!=0 )
    iRet = LstShow( lstTables, LST_LIST, VioCenterCol( 42 ), VioCenterRow( 14 ), 42, 14, " Tischbersicht ", " ~F1~ Hilfe  ~RET~ Bearbeiten  ~EINF~ Einfgen  ~ENTF~ L”schen", Exit, NULL );
   else
    iRet = T_INS;
   switch( iRet )
   {
    case T_ESC:
         boFertig = TRUE;
         break;
    case T_RETURN:
         lNum = LstGetNum( lstTables );
         if( TablesEdit( lNum ) > 0L )
         {
          if( !TableGetName( lNum*100L, cName ) )
           cName[0] = 0;
          LstChange( lstTables, lNum, lNum, "Tisch %3ld  %s", lNum, cName );
         }
         break;
    case T_INS:
         lNum = TablesEdit( -1L );
         if( lNum!=-1L )
         {
          if( !TableGetName( lNum*100L, cName ) )
           cName[0] = 0;
          LstInsert( lstTables, lNum, "Tisch %3ld  %s", lNum, cName );
          lTableCount++;
         }
         else
          if( lTableCount==0L ) boFertig = TRUE;
         break;
    case T_DEL:
         if( WinMsgCenter( "           !!! Achtung !!!\n"
                           " Tischinformationen wirklich l”schen?"
                         , MSG_YESNO
                         ) == T_RETURN )
         {
          lNum = LstGetNum( lstTables );
          if( !TableRemInfo( lNum*100L ) )
           WinMsgCenter( " Fehler beim L”schen der\n"
                         " Tischinformationen", MSG_INFO );
          else
          {
           LstDelete( lstTables, lNum );
           lTableCount--;
          }
         }
         break;
   }
  }
 }

 PRIVATE LONG CDECL     TablesEdit    ( lNum )
 LONG           lNum;
 {
  extern SInfo  info;
  SDlg*         dlg;
  STableInfo    cfg;
  CHAR          cTemp[50];
  CHAR          cTmp2[30];
  LONG          lTable;
  BOOL          boFertig     = FALSE;
  INT           Exit[]       = { T_F2, T_F3, 0 };
  TableGetInfo( lNum*100L, &cfg );
  dlg = DlgInit( 14 );
  sprintf( cTemp, "%3ld", lNum>0 ? lNum : 0L );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 0, "~N~ummer........ :", SetTableNumHelp, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Geben Sie die Tischnummer an" );
  DlgAddField ( dlg, 18, 0, cTemp, 30, 3 );
  if( lNum>0 ) DlgDisable( dlg, 0, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 1, "~T~ischname..... :", SetTableNameHelp, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Geben Sie den Namen des Tisches an" );
  DlgAddField ( dlg, 18, 0, cfg.cName, DLG_FIELD_ALL, TABLES_MAXNAMELEN );
  sprintf( cTemp, "%2hd", cfg.iKellner );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 2, "~K~ellner....... :", SetTableKellHelp, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Geben Sie den zu erzwingenden Kellner an" );
  DlgAddField ( dlg, 18, 0, cTemp, 20, 2 );
  sprintf( cTemp, "%2hd", cfg.iAart );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 3, "~A~brechnungsart :", SetTableAbrHelp, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Geben Sie die zu erzwingende Abrechnungsart an" );
  DlgAddField ( dlg, 18, 0, cTemp, 20, 2 );
  sprintf( cTemp, "%2hd", cfg.iPrEbene );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 4, "~P~reisebene.... :", SetTableEbnHelp, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Geben Sie die zu erzwingende Preisebene an" );
  DlgAddField ( dlg, 18, 0, cTemp, 20, 2 );
  sprintf( cTemp, "%3hd", cfg.iKostenStelle );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 5, "~K~ostenstelle.. :", SetTableKstHelp, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Geben Sie die zu erzwingende Preisebene an" );
  DlgAddField ( dlg, 18, 0, cTemp, 30, 3 );
  DlgInitEntry( dlg, 3, DLG_RADIO, 1, 6, "Mehrwertsteuer:", SetTableMwstHelp, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Geben Sie den zu erzwingenden MWST-Satz an" );
  DlgAddField ( dlg, 1, 1, "~F~ragen    ", cfg.iMwst<0, 0 );
  DlgAddField ( dlg, 1, 2, "~I~m Haus   ", cfg.iMwst==0, 0 );
  DlgAddField ( dlg, 1, 3, "~A~uáer Haus", cfg.iMwst>0, 0 );
  DlgInitEntry( dlg, 2, DLG_CHECK,20, 6, "Rechnungsdruck:", SetTableRDrHelp, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Die Parameter fr den Rechnungsdruck" );
  DlgAddField ( dlg, 1, 1, "Aus~d~ruck    ", cfg.boDruck, 0 );
  DlgAddField ( dlg, 1, 2, "~W~ahl m”glich", cfg.boDruckWahl, 0 );
  DlgInitEntry( dlg, 3, DLG_CHECK,43, 6, "Parameter:", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Allgemeine Parameter angeben" );
  DlgAddField ( dlg, 1, 1, "Anzahl ~G~„ste ", cfg.boGaesteAnz, 0 );
  DlgAddField ( dlg, 1, 2, "Na~m~e erfragen", cfg.boGastName, 0 );
  DlgAddField ( dlg, 1, 3, "~S~chubladenzwang", cfg.boSchublade, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1,11, "~1~. Externes Prg:", SetTableEx1Help, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung³ Programm, das bei jedem Bezahlen ausgefhrt wird" );
  DlgAddField ( dlg, 18, 0, cfg.cExtern1, DLG_FIELD_ALL, 19 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1,12, "~2~. Externes Prg:", SetTableEx2Help, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Programm, das bei AArt-Typ E aufgerufen wird" );
  DlgAddField ( dlg, 18, 0, cfg.cExtern2, DLG_FIELD_ALL, 19 );
  DlgInitEntry( dlg, 2, DLG_STATIC, 1,14, "", NULL, "" );
  sprintf( cTemp, "Bondrucker.....:  %s", SetupGetTxtDruck( cfg.iBonDruck, cTmp2 ) );
  DlgAddField ( dlg, 0, 0, cTemp, 0, 0 );
  sprintf( cTemp, "Rechnungsdruck.:  %s", SetupGetTxtDruck( cfg.iRechDruck, cTmp2 )  );
  DlgAddField ( dlg, 0, 1, cTemp, 0, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1,17, "Mindestverzehr:", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ³ Der Mindestverzehr fr diesen Tisch" );
  WaehrPreis(cfg.lMindest, cTemp);
  sprintf( cTmp2, "% *s", info.preis_nachkomma>0 ? WaehrGetLength()+1 : WaehrGetLength(), cTemp);
//  DlgAddField ( dlg, 20, 0, cTemp, (8-info.preis_nachkomma)*10+info.preis_nachkomma|DLG_FIELD_SIGN, (info.preis_nachkomma==0) ? 12:12); //8 : 9 );
  DlgAddField ( dlg, 18, 0, cTmp2, (WaehrGetLength()-info.preis_nachkomma)*10+info.preis_nachkomma/*|DLG_FIELD_SIGN*/, WaehrGetLength()+1 );

  while( !boFertig )
  {
   switch( DlgHandle( dlg, VioCenterCol( 65 ), VioCenterRow( 22 ), 65, 22, " Tischinfo editieren ", Exit ) )
   {
    case T_F2:
         if( SetupDrucker( &cfg.iBonDruck, FALSE ) )
         {
          sprintf( cTemp, "Bondrucker.....:  %s", SetupGetTxtDruck( cfg.iBonDruck, cTmp2 ) );
          DlgSetText( dlg, 11, 0, cTemp );
         }
         break;
    case T_F3:
         if( SetupDrucker( &cfg.iRechDruck, TRUE ) )
         {
          sprintf( cTemp, "Rechnungsdruck.:  %s", SetupGetTxtDruck( cfg.iRechDruck, cTmp2 )  );
          DlgSetText( dlg, 11, 1, cTemp );
         }
         break;
    case T_RETURN:
         lTable = atol(DlgGetText( dlg, 0, 0 ));
         if( lTable==0L ) continue;
         strcpy( cfg.cName, DlgGetText( dlg, 1, 0 ) );
         cfg.iKellner    = atoi( DlgGetText( dlg, 2, 0 )  );
         if( cfg.iKellner>=0 )
         {
          if( info.kellner[cfg.iKellner][0]==0 )
          {
           WinMsgCenter( " Angegebener Kellner existiert nicht!", MSG_INFO );
          }
         }
         cfg.iAart       = atoi( DlgGetText( dlg, 3, 0 )  );
         if( cfg.iAart>=0 )
         {
          if( !SetupAartExist( cfg.iAart-1 ) )
          {
           WinMsgCenter( " Angegebene Abrechnungsart existiert nicht!", MSG_INFO );
          }
         }
         cfg.iPrEbene = atoi( DlgGetText( dlg, 4, 0 ) );
         cfg.iKostenStelle = atoi( DlgGetText( dlg, 5, 0 ) );
         cfg.iMwst       = DlgGetSelect( dlg, 6 ) -1;
         cfg.boDruck     = DlgIsMarked( dlg, 7, 0 );
         cfg.boDruckWahl = DlgIsMarked( dlg, 7, 1 );
         cfg.boGaesteAnz = DlgIsMarked( dlg, 8, 0 );
         cfg.boGastName  = DlgIsMarked( dlg, 8, 1 );
         cfg.boSchublade = DlgIsMarked( dlg, 8, 2 );
         strcpy( cfg.cExtern1, DlgGetText( dlg, 9, 0 ) );
         strcpy( cfg.cExtern2, DlgGetText( dlg, 10, 0 ) );
         cfg.lMindest = WaehrGetLong( DlgGetText(dlg, 12, 0) );

         if( lNum<0L )
         {
          sprintf( cTemp, "%s\\TABLE%03ld.INI", PATH_TBLINFO, lTable );
          if( DskFileExist( cTemp ) )
          {
           if( WinMsgCenter( " Es existiert bereits eine Einstellungsdatei\n"
                             " fr diesen Tisch.\n"
                             " M”chten Sie sie berschreiben?", MSG_YESNO ) == T_ESC )
            break;
           LstDelete( lstTables, lTable );
          }
         }
         if( !TablePutInfo( lTable*100L, &cfg ) )
          WinMsgCenter( " Fehler beim Abspeichern der Tischinformationen ", MSG_INFO );
         else
          boFertig = TRUE;
         break;
    case T_ESC:
         lTable = -1L;
         boFertig = TRUE;
   }
  }
  DlgDone( dlg );
  return( lTable );
 }

 PRIVATE VOID CDECL     SetTableNumHelp  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie die Nummer des Tisches an\n"
                " dessen Daten Sie editieren m”chten.\n"
                " Die angegebenen Werte gelten fr alle\n"
                " Parteien dieses Tisches."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableNameHelp  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie den Namen des Tisches an.\n"
                " Dieser wird auf den Bons und Rechnungen\n"
                " ausgegeben, sofern ein entsprechender\n"
                " Platzhalter im Layout eingetragen wurde."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableKellHelp  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie den erzwungenen Kellner diese\n"
                " Tisches an. Auf diesen Kellner werden\n"
                " die Ums„tze gebucht"
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableAbrHelp   ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie die erzwungene Abrechnungsart\n"
                " an. Diese gilt fr diesen Tisch beim\n"
                " Bezahlen als fest eingestellt."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableMwstHelp  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie den erzwungenen Mehrwertsteuer-\n"
                " satz an. Diese gilt fr den Tisch als\n"
                " fest eingestellt."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableEx1Help  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie den Namen des ersten externen\n"
                " Programms an. Dieses wird unabh„ngig von \n"
                " der Abrechnungsart beim Bezahlen dieses\n"
                " Tisches aufgerufen."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableEx2Help  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie den Namen des zweiten externen\n"
                " Programms an. Dieses wird beim Bezahlen  \n"
                " auf eine Abrechnungsart vom Typ 'E'\n"
                " aufgerufen."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableEbnHelp  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie die Preisebene an, die fr\n"
                " diesen Tisch erzwungen werden soll."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableKstHelp  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie die Kostenstelle an, die fr\n"
                "   diesen Tisch erzwungen werden soll."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetTableRDrHelp  ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Folgende Einstellungen sind „nderbar:\n\n"
                " - Ausdruck:     Geben Sie an, ob beim Bezahlen\n"
                "                 dieses Tisches eine Rechnung\n"
                "                 gedruckt werden soll oder nicht\n"
                " - Wahl m”glich: Falls dieses Feld nicht aktiviert\n"
                "                 ist, ist auch kein Umschalten von\n"
                "                 Druck an/aus m”glich."
              , MSG_INFO
              );
 }


