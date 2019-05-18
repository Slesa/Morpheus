 #include       "gastro/Setup.h"
 #include       "hilevel/Dlg.h"
 #include       "hilevel/Vio.h"
 #include       "hilevel/MsgWin.h"
 #include       "defs/Keydefs.h"
 #include       <stdio.h>

 VOID CDECL     SetupOnlnEdit ( void );          // Menuepunkt Online-Journal
 PRIVATE VOID CDECL     SetupOnlnSize ( SDlg* );         // Hilfe zum Journalpunkt Journalgroesse
 PRIVATE VOID CDECL     SetupOnlnWhat ( SDlg* );         // Hilfe zum Journalpunkt Was soll gedruckt werden

 PRIVATE VOID CDECL     SetupOnlnSize ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Geben Sie in diesem Feld an, wie gro· die \n"
                " Journal maximal werden darf.\n"
                " Die Grî·enangabe bezieht sich auf KByte\n"
                " (1024 Bytes)."
                " Die Eingabe von 0 bedeutet, da· keine \n"
                " Journaldatei erzeugt wird, bei einer Angabe von\n"
                " 9999 wird die Grî·e der Datei nicht ÅberprÅft."
              , MSG_INFO
              );
 }

 PRIVATE VOID CDECL     SetupOnlnWhat ( dlg )
 SDlg*          dlg;
 {
  dlg = dlg;
  WinMsgCenter( " Hier kînnen Sie auswÑhlen, welche Aktionen\n"
                " in der Journaldatei protokolliert werden soll."
              , MSG_INFO
            );
 }

 // **************************************************************************
 // * SetupOnlnEdit                                                          *
 // * ---------------------------------------------------------------------- *
 // * Richtet den Dialog Online-Journal ein und fuehrt ihn aus.              *
 // **************************************************************************
 VOID CDECL     SetupOnlnEdit ( void )
 {
  SDlg*         dlg;                             // Online-Journal-Dialog
  CHAR          JouInpSize[5];                   // String zum Editieren der Journalgroesse
  INT           iLen;                            // Zum Auslesen der Variablen
  extern SETUP  abrech;
  sprintf( JouInpSize, "%hd",  SetupGetJournalLen() );
  dlg = DlgInit( 3 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 1, "~J~ournalgrî·e        KB maximal", SetupOnlnSize, " ~F1~ Hilfe ≥ Angabe der maximalen Journalgrî·e in KByte" );
  DlgAddField ( dlg,15, 0, JouInpSize, DLG_FIELD_NUM, 4 );
  DlgInitEntry( dlg,11, DLG_CHECK, 1, 3, "In Journal aufnehmen:", SetupOnlnWhat, " ~F1~ Hilfe ≥ Was soll in das Journal geschrieben werden?" );
  DlgAddField ( dlg, 3, 1, "~B~estellen           ", SetupGetJournal( SETUP_ONL_BESTELL ), 0 );
  DlgAddField ( dlg, 3, 2, "~S~tornieren          ", SetupGetJournal( SETUP_ONL_STORNO ), 0 );
  DlgAddField ( dlg, 3, 3, "B~e~zahlen ", SetupGetJournal( SETUP_ONL_BEZAHLEN ), 0 );
  DlgAddField ( dlg,17, 3, "A~r~tikelgenau ", abrech.Flags&SETUP_PROTOALL, 0 );
  DlgAddField ( dlg, 3, 4, "S~p~litten            ", SetupGetJournal( SETUP_ONL_SPLITTEN ), 0 );
  DlgAddField ( dlg, 3, 5, "~T~ischwechsel        ", SetupGetJournal( SETUP_ONL_WECHSEL ), 0 );
  DlgAddField ( dlg, 3, 6, "Spe~z~ial-Funktionen  ", SetupGetJournal( SETUP_ONL_SPEZIAL ), 0 );
  DlgAddField ( dlg, 3, 7, "~C~hef-Funktionen     ", SetupGetJournal( SETUP_ONL_CHEF ), 0 );
  DlgAddField ( dlg, 3, 8, "S~y~stem-Meldungen    ", SetupGetJournal( SETUP_ONL_SYSTEM ), 0 );
  DlgAddField ( dlg, 3, 9, "~A~uswertung          ", SetupGetJournal( SETUP_ONL_AUSWERT ), 0 );
  DlgAddField ( dlg, 3,10, "~D~atenpflege         ", SetupGetJournal( SETUP_ONL_PFLEGE ), 0 );
  DlgInitEntry( dlg, 1, DLG_CHECK, 1, 16, "", NULL, " ~F1~ Hilfe ≥ Ausgabe auf Journal-Drucker?" );
  DlgAddField ( dlg, 1, 0, "A~u~sgabe auf Drucker ", SetupGetJournalPrn(), 0 );
  if( DlgHandle( dlg, VioCenterCol( 38 ), VioCenterRow( 20 ), 38, 20, " Journal ", NULL ) == T_RETURN )
  {
   abrech.Flags = 0;
   if( DlgIsMarked( dlg, 1, 3 ) ) abrech.Flags |= SETUP_PROTOALL;
   sscanf( DlgGetText( dlg, 0, 0 ), "%hd", &iLen );
   SetupSetJournalLen( iLen );
   SetupSetJournal( SETUP_ONL_BESTELL, DlgIsMarked( dlg, 1, 0 ) );
   SetupSetJournal( SETUP_ONL_STORNO , DlgIsMarked( dlg, 1, 1 ) );
   SetupSetJournal( SETUP_ONL_BEZAHLEN, DlgIsMarked( dlg, 1, 2 ) );
   SetupSetJournal( SETUP_ONL_SPLITTEN, DlgIsMarked( dlg, 1, 4 ) );
   SetupSetJournal( SETUP_ONL_WECHSEL, DlgIsMarked( dlg, 1, 5 ) );
   SetupSetJournal( SETUP_ONL_SPEZIAL, DlgIsMarked( dlg, 1, 6 ) );
   SetupSetJournal( SETUP_ONL_CHEF, DlgIsMarked( dlg, 1, 7 ) );
   SetupSetJournal( SETUP_ONL_SYSTEM, DlgIsMarked( dlg, 1, 8 ) );
   SetupSetJournal( SETUP_ONL_AUSWERT, DlgIsMarked( dlg, 1, 9 ) );
   SetupSetJournal( SETUP_ONL_PFLEGE, DlgIsMarked( dlg, 1,  10 ) );
   SetupSetJournalPrn( DlgIsMarked( dlg, 2, 0 ) );
  }
  DlgDone( dlg );
  if(iLen>200)
  {
   WinMsgCenter( " ! HINWEIS !\n\n"
                 " Sie haben Journalgrî·e grî·er 200KB gewÑhlt!\n"
                 " Wenn Sie diese Einstellung Åber lÑngere Zeit\n"
                 " so lassen, kann  die maximale KapazitÑt  des\n"
                 " Programmes Journal Åberschritten werden, die\n"
                 " Journal-Datei mu·  dann  mit  einem  anderen\n"
                 " Editor bearbeitet werden !"
               , MSG_INFO
               );
  }
 }

