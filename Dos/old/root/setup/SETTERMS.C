 #include       "gastro/Setup.h"
 #include       "gastro/SetTerm.h"
 #include       "gastro/Info.h"
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

 PRIVATE VOID CDECL     TermsInit    ( void );
 PRIVATE VOID CDECL     TermsDone    ( void );
 PRIVATE VOID CDECL     TermsHandle  ( void );
 PRIVATE LONG CDECL     TermsEdit    ( LONG );
 BOOL CDECL     SetupDrucker    ( INT*, BOOL );
 CHAR* CDECL    SetupGetTxtDruck( INT, CHAR* );
 PRIVATE BOOL CDECL     TermsMsgSave    ( INT );

 PRIVATE SLst*  lstTerms;
 PRIVATE LONG   lTermCount;

 VOID CDECL     TermsMain    ( void )
 {
  TermsInit();
  TermsHandle();
  TermsDone();
 }

 PRIVATE VOID CDECL     TermsInit    ( void )
 {
  #define       FIRST_MATCH  PATH_TERMINI "\\TERM*.INI"
  SFindT        find;
  BOOL          boFertig;
  LONG          lTerm;
  TermsChkCfg();
  lTermCount = 0L;
  lstTerms   = LstInit( 40 );
  boFertig   = DskFindFirst( FIRST_MATCH, DSK_A_NORMAL, &find );
  while( !boFertig )
  {
   sscanf( find.name, "TERM%ld.INI", &lTerm );
   LstInsert( lstTerms, lTerm, "Terminal %ld", lTerm );
   lTermCount++;
   boFertig = DskFindNext( &find );
  }
 }

 PRIVATE VOID CDECL     TermsDone    ( void )
 {
  LstDone( lstTerms );
 }

 PRIVATE VOID CDECL     TermsHandle  ( void )
 {
  INT            iRet;
  LONG           lNum;
  INT            iExit[]     = { T_INS, T_DEL, 0 };
  BOOL           boFertig    = FALSE;
  while( !boFertig )
  {
   if( lTermCount == 0L )
    iRet = T_INS;
   else
    iRet = LstShow( lstTerms, LST_LIST, VioCenterCol( 40 ), VioCenterRow( 14 ), 40, 14, " Terminals ", " ~INS~ Neu  ~DEL~ Lîschen ~RET~ Bearbeiten ~ESC~ Ende", iExit, NULL );
   switch( iRet )
   {
    case T_ESC:
         boFertig = TRUE;
         break;
    case T_RETURN:
         lNum = LstGetNum( lstTerms );
         if( TermsEdit( lNum ) > 0L )
          LstChange( lstTerms, lNum, lNum, "Terminal %ld", lNum );
         break;
    case T_INS:
         lNum = TermsEdit( -1L );
         if( lNum!=-1L )
         {
          LstInsert( lstTerms, lNum, "Terminal %ld", lNum );
          lTermCount++;
         }
         else
          if( lTermCount==0L ) boFertig = TRUE;
         break;
    case T_DEL:
         if( WinMsgCenter( " Die Einstellungen dieses Terminals\n wirklich lîschen?", MSG_YESNO ) == T_RETURN )
         {
          lNum = LstGetNum( lstTerms );
          if( !TermsRemCfg( lNum ) )
           WinMsgCenter( " Fehler beim Lîschen der\n"
                         " Terminalinformationen!", MSG_INFO );
          else
          {
           LstDelete( lstTerms, lNum );
           lTermCount--;
          }
         }
         break;
   }
  }
 }

 PRIVATE LONG CDECL     TermsEdit    ( lNum )
 LONG           lNum;
 {
  SDlg*         dlg;
  STermCfg      cfg;
  CHAR          cTemp[50];
  CHAR          cTmp2[20];
  LONG          lTerm;
  INT           iRet;
  BOOL          boFertig     = FALSE;
  INT           Exit[]       = { T_F2, T_F3, 0 };
  extern SInfo  info;
  TermsGetCfg( lNum, &cfg );
  dlg = DlgInit( 11 );
  sprintf( cTemp, "%4ld", (lNum>0L)?lNum:0L );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 0, "T~e~rminal...... :", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ≥ Die Nummer des Terminals" );
  DlgAddField ( dlg, 18, 0, cTemp, 40, 4 );
  if( lNum>0L ) DlgDisable( dlg, 0, 0 );
  sprintf( cTemp, "%2hd", cfg.iKellner );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 2, "~K~ellner....... :", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ≥ Fest einstellbarer Kellner" );
  DlgAddField ( dlg, 18, 0, cTemp, 20, 2 );
  sprintf( cTemp, "%5ld", cfg.lTable );
  DlgInitEntry( dlg, 5, DLG_INPUT, 1, 3, "~T~isch......... :", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ≥ Fest einstellbarer Tisch" );
  DlgAddField ( dlg, 18, 0, cTemp, 50, 5 );
  sprintf( cTemp, "%2hd", cfg.iAart+1 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 4, "A~b~rechnungsart :", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ≥ Geben Sie die zu erzwingende Abrechnungsart an" );
  DlgAddField ( dlg, 18, 0, cTemp, 20, 2 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 6, "~1~. Externes Prg:", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ≥ Programm, das bei jedem Bezahlen ausgefÅhrt wird" );
  DlgAddField ( dlg, 18, 0, cfg.cExtern1, DLG_FIELD_ALL, 12 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 7, "~2~. Externes Prg:", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ≥ Programm, das bei AArt-Typ E aufgerufen wird" );
  DlgAddField ( dlg, 18, 0, cfg.cExtern2, DLG_FIELD_ALL, 12 );
  DlgInitEntry( dlg, 3, DLG_RADIO,34, 0, "Mehrwertsteuer:", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ≥ Geben Sie den zu erzwingenden MWST-Satz an" );
  DlgAddField ( dlg, 1, 1, "~F~ragen    ", cfg.iMwst<0, 0 );
  DlgAddField ( dlg, 1, 2, "~I~m Haus   ", cfg.iMwst==0, 0 );
  DlgAddField ( dlg, 1, 3, "~A~u·er Haus", cfg.iMwst>0, 0 );
  DlgInitEntry( dlg, 5, DLG_CHECK,34, 5, "Parameter:", NULL, " ~F1~ Hilfe ~F2~ Bon ~F3~ Rechnung ≥ Allgemeine Parameter angeben" );
  DlgAddField ( dlg, 1, 1, "~P~OS-Modus aktiv       ", cfg.wFlags&TERM_POSMODE, 0 );
  DlgAddField ( dlg, 1, 2, "~R~echnung lesen erlaubt", cfg.wFlags&TERM_RECHLESEN, 0 );
  DlgAddField ( dlg, 1, 3, "Defa~u~lt Keine Rechnung", cfg.wFlags&TERM_RECHDEF, 0 );
  DlgAddField ( dlg, 1, 4, "Rechnungs~d~ruck EIN/AUS", cfg.wFlags&TERM_RECHTOGGLE, 0 );
  DlgAddField ( dlg, 1, 5, "Transponder deaktiv     ", cfg.wFlags&TERM_PONDERDEAKTIV, 0 );
  DlgInitEntry( dlg, 2, DLG_STATIC, 1, 9, "", NULL, "" );
  sprintf( cTemp, "Bondrucker.....:  %s", SetupGetTxtDruck( cfg.iBonDruck, cTmp2 ) );
  DlgAddField ( dlg, 0, 0, cTemp, 0, 0 );
  sprintf( cTemp, "Rechnungsdruck.:  %s", SetupGetTxtDruck( cfg.iRechDruck, cTmp2 )  );
  DlgAddField ( dlg, 0, 1, cTemp, 0, 0 );
  DlgInitEntry( dlg, 1, DLG_FRAME,32, 0, "", NULL, "" );
  DlgAddField ( dlg, 0, 0, "", 0,10);
  while( !boFertig )
  {
   switch( DlgHandle( dlg, VioCenterCol( 65 ), VioCenterRow( 13 ), 65, 13, " Terminal bearbeiten ", Exit ) )
   {
    case T_F2:
         if( SetupDrucker( &cfg.iBonDruck, FALSE ) )
         {
          sprintf( cTemp, "Bondrucker.....:  %s", SetupGetTxtDruck( cfg.iBonDruck, cTmp2 ) );
          DlgSetText( dlg, 8, 0, cTemp );
         }
         break;
    case T_F3:
         if( SetupDrucker( &cfg.iRechDruck, TRUE ) )
         {
          sprintf( cTemp, "Rechnungsdruck.:  %s", SetupGetTxtDruck( cfg.iRechDruck, cTmp2 )  );
          DlgSetText( dlg, 8, 1, cTemp );
         }
         break;
    case T_RETURN:
         lTerm = atol( DlgGetText( dlg, 0, 0 ) );
         if( lTerm==0 )
          continue;
         cfg.wFlags      = 0;
         cfg.iKellner    = atoi( DlgGetText( dlg, 1, 0 )  );
         if( cfg.iKellner>=0 )
         {
          if( info.kellner[cfg.iKellner-1][0]==0 )
          {
           WinMsgCenter( " Angegebener Kellner existiert nicht!", MSG_INFO );
           continue;
          }
         }
         cfg.lTable      = atol( DlgGetText( dlg, 2, 0 )  );
         cfg.iAart       = atoi( DlgGetText( dlg, 3, 0 )  )-1;
         if( cfg.iAart>=0 )
         {
          if( !SetupAartExist( cfg.iAart ) )
          {
           WinMsgCenter( " Angegebene Abrechnungsart existiert nicht!", MSG_INFO );
           continue;
          }
         }
         strcpy( cfg.cExtern1, DlgGetText( dlg, 4, 0 ) );
         strcpy( cfg.cExtern2, DlgGetText( dlg, 5, 0 ) );
         cfg.iMwst       = DlgGetSelect( dlg, 6 ) -1;
         if( DlgIsMarked( dlg, 7, 0 ) ) cfg.wFlags |= TERM_POSMODE;
         if( DlgIsMarked( dlg, 7, 1 ) ) cfg.wFlags |= TERM_RECHLESEN;
         if( DlgIsMarked( dlg, 7, 2 ) ) cfg.wFlags |= TERM_RECHDEF;
         if( DlgIsMarked( dlg, 7, 3 ) ) cfg.wFlags |= TERM_RECHTOGGLE;
         if( DlgIsMarked( dlg, 7, 4 ) ) cfg.wFlags |= TERM_PONDERDEAKTIV;
         if( lNum<0L )
         {
          sprintf( cTemp, "%s\\TERM%04ld.INI", PATH_TERMINI, lTerm );
          if( DskFileExist( cTemp ) )
          {
           if( WinMsgCenter( " Es existiert bereits eine Einstellungsdatei\n"
                             " fÅr dieses Terminal.\n"
                             " Mîchten Sie sie Åberschreiben?", MSG_YESNO ) == T_ESC )
            break;
           LstDelete( lstTerms, lNum );
          }
         }
         iRet  = TermsPutCfg( lTerm, &cfg );
         if( TermsMsgSave( iRet ) )
          boFertig = TRUE;
         break;
    case T_ESC:
         lTerm = -1L;
         boFertig = TRUE;
         break;
   }
  }
  DlgDone( dlg );
  return( lTerm );
 }

 BOOL CDECL SetupDrucker    ( piPrn, boRech )
 INT*           piPrn;
 BOOL           boRech;
 {
  BOOL          boRet        = FALSE;
  SDlg*         dlg          = DlgInit( 1 );
  DlgInitEntry( dlg,13, DLG_RADIO, 2, 1, "", NULL, (boRech) ? " Geben Sie den zu erzwingenden Rechnungsdrucker an": " Geben Sie den zu erzwingenden Bondrucker an" );
  DlgAddField ( dlg, 0, 0, "Unbestimmt        ", (*piPrn<0)||(*piPrn>11), 0 );
  DlgAddField ( dlg, 0, 1, "1. Bondrucker     ", *piPrn==0, 0 );
  DlgAddField ( dlg, 0, 2, "2. Bondrucker     ", *piPrn==1, 0 );
  DlgAddField ( dlg, 0, 3, "3. Bondrucker     ", *piPrn==2, 0 );
  DlgAddField ( dlg, 0, 4, "4. Bondrucker     ", *piPrn==3, 0 );
  DlgAddField ( dlg, 0, 5, "5. Bondrucker     ", *piPrn==4, 0 );
  DlgAddField ( dlg, 0, 6, "6. Bondrucker     ", *piPrn==5, 0 );
  DlgAddField ( dlg, 0, 7, "7. Bondrucker     ", *piPrn==6, 0 );
  DlgAddField ( dlg, 0, 8, "8. Bondrucker     ", *piPrn==7, 0 );
  DlgAddField ( dlg, 0, 9, "Rechnungsdrucker  ", *piPrn==8, 0 );
  DlgAddField ( dlg, 0,10, "Journaldrucker    ", *piPrn==9, 0 );
  DlgAddField ( dlg, 0,11, "Auswertungsdrucker", *piPrn==10, 0 );
  DlgAddField ( dlg, 0,12, "Pflegedrucker     ", *piPrn==11, 0 );
  if( DlgHandle( dlg, VioCenterCol( 30 ), VioCenterRow( 17 ), 30, 17, (boRech)?" Rechnungsdrucker":"Bondrucker", NULL ) == T_RETURN )
  {
   *piPrn = DlgGetSelect( dlg, 0 )-1;
   boRet = TRUE;
  }
  DlgDone( dlg );
  return( boRet );
 }

 CHAR*  CDECL SetupGetTxtDruck( iPrn, cBuf )
 INT            iPrn;
 CHAR*          cBuf;
 {
  *cBuf = 0;
  switch( iPrn )
  {
   case -1: strcpy( cBuf, "Unbestimmt" ); break;
   case 0:  strcpy( cBuf, "1. Bon" ); break;
   case 1:  strcpy( cBuf, "2. Bon" ); break;
   case 2:  strcpy( cBuf, "3. Bon" ); break;
   case 3:  strcpy( cBuf, "4. Bon" ); break;
   case 4:  strcpy( cBuf, "5. Bon" ); break;
   case 5:  strcpy( cBuf, "6. Bon" ); break;
   case 6:  strcpy( cBuf, "7. Bon" ); break;
   case 7:  strcpy( cBuf, "8. Bon" ); break;
   case 8:  strcpy( cBuf, "Rechnung" ); break;
   case 9:  strcpy( cBuf, "Journal" ); break;
   case 10: strcpy( cBuf, "Auswertung" ); break;
   case 11: strcpy( cBuf, "Pflege" ); break;
  }
  return( cBuf );
 }

 PRIVATE BOOL CDECL  TermsMsgSave    ( iErr )
 INT            iErr;
 {
  switch( iErr )
  {
   case ERR_NONE:
        return( TRUE );
   case ERR_COUNT:
        WinMsgCenter( "Sie haben eine ungÅltige Terminalnummer eingeben!", MSG_INFO );
        break;
   case ERR_DISK_CREATE:
        WinMsgCenter( "Fehler beim Abspeichern der Informationen", MSG_INFO );
        break;
  }
  return( FALSE );
 }
