 #include       "hilevel/Dlg.h"
 #include       "hilevel/Mnu.h"
 #include       "hilevel/Vio.h"
 #include       "hilevel/LstWin.h"
 #include       "hilevel/MsgWin.h"
 #include       "hilevel/Event.h"
 #include       "gastro/Setup.h"
 #include       "gastro/Info.h"
 #include       "gastro/Waehrung.h"
 #include       "basics/MemAlloc.h"
 #include       "defs/Keydefs.h"
 #include       "defs/Colordef.h"
 #include       <stdlib.h>
 #include       <string.h>

 VOID CDECL     SetupGetLibLayout( INT, CHAR[5][60], INT);
 PRIVATE VOID CDECL     SetupLayEdit ( INT, INT, CHAR* );
 VOID CDECL     SetupLayMenu ( INT );          // Menuepunkt Bonlayout
 PRIVATE VOID CDECL     SetupLayHelp ( void );          // Hilfe zum Bonlayout-Menue
 PRIVATE VOID CDECL     SetupLayShow ( SWin*, CHAR* );
 PRIVATE BOOL CDECL     SetupGetInh  ( CHAR, CHAR* );
 PRIVATE VOID CDECL     SetupInhHelp ( SDlg* );
 PRIVATE VOID CDECL     SetupStruktur( void );

 PRIVATE VOID CDECL     SetupLayHelp ( void )
 {
  WinMsgCenter( " Hier kînnen Sie das Aussehen der Bons und Rechnungen  nahezu beliebig\n"
                " einstellen.  énderungen sollten Sie  immer im Bezug auf den Standard-\n"
                " Layout vornehmen. ACHTUNG: Wenn Sie diese Einstellungen zu stark ver-\n"
                " Ñndern, kann dies zur Folge haben,  da· Bons oder Rechnungen nur noch\n"
                " fehlerhaft oder Åberhauptnicht ausgedruckt werden. Beachten Sie auch,\n"
                " da· manche Drucker (z.B. Olivetti PR45) blockieren,  wenn eine Druck-\n"
                " zeile zu lang wird.\n\n"
                " Das Layoutfeld 'Struktur' steuert das Abschneiden der Bons und sollte\n"
                " nicht verÑndert werden! (FÅr Speziallîsungen reserviert.)\n\n"
                " Das Layoutfeld fÅr Rechnungshinweise ist normalerweise leer, da null-\n"
                " preisige Artikel nicht gedruckt werden sollen."
              , MSG_INFO
              );
 }

 // **************************************************************************
 // * SetupLayMenu                                                           *
 // * ---------------------------------------------------------------------- *
 // * Richtet das Menue zum Auswaehlen des Layouts ein und fuehrt es aus.    *
 // **************************************************************************
 VOID CDECL     SetupLayMenu ( dev )
 INT            dev;
 {
  INT           count        = 1;
  BOOL          boFertig     = FALSE;
  INT           Exit[]       = { 0, 0 };
  CHAR          cStatus[100];
  SMnu*         mnu;
  INT           iRet;
  if( dev!=-1 )
  {
   Exit[0] = T_F3;
   strcpy( cStatus, "~F1~ Hilfe ~F3~ Layout ≥ Aussehen des Bons und der Rechnung verÑndern");
  }
  else
   strcpy( cStatus, "~F1~ Hilfe ≥ Aussehen des Bons und der Rechnung verÑndern");
  mnu = MnuInit( 11 );
  MnuAdd( mnu, 1, count++, "~K~opf     - Layout der Bons     ", cStatus );
  MnuAdd( mnu, 1, count++, "~B~estell  - Layout der Bons     ", cStatus );
  MnuAdd( mnu, 1, count++, "Bonen~d~e  - Layout der Bons     ", cStatus );
  MnuAdd( mnu, 1, count++, "~S~torno   - Layout der Bons     ", cStatus );
  MnuAdd( mnu, 1, count++, "~H~inweise - Layout der Bons     ", cStatus );
  if( dev==-1 )
   MnuAdd( mnu, 1, count++, "S~t~ruktur - Layout der Bons     ", cStatus );
  MnuAdd( mnu, 1, count++, "", NULL );
  MnuAdd( mnu, 1, count++, "K~o~pf     - Layout der Rechnung ", cStatus );
  MnuAdd( mnu, 1, count++, "~P~osten   - Layout der Rechnung ", cStatus );
  MnuAdd( mnu, 1, count++, "~E~nde     - Layout der Rechnung ", cStatus );
  MnuAdd( mnu, 1, count++, "H~i~nweis  - Layout der Rechnung ", cStatus );
  while( !boFertig )
  {
   iRet = MnuHandle( mnu, " Layout-MenÅ ", VioCenterCol( 30 ), VioCenterRow( count ), Exit, SetupLayHelp );
   switch( iRet )
   {
    case T_F3:
         if( WinMsgCenter( " Achtung!\n"
                           " Dadurch werden alle EintrÑge des Setup-\n"
                           " Layouts fÅr diesen Drucker Åbernommen!\n\n"
                           " Alle EintrÑge Åberschreiben und die\n"
                           " bestehenden Daten des Setup-Layouts\n"
                           " Åbernehmen?", MSG_YESNO ) == T_ESC )
          break;
         {
         CHAR          cTemp[5][60];
         SetupGetLibLayout(SETUP_LAYOUT_KOPF, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_KOPF, cTemp, dev);
         SetupGetLibLayout(SETUP_LAYOUT_BEST, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_BEST, cTemp, dev);
         SetupGetLibLayout(SETUP_LAYOUT_ENDE, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_ENDE, cTemp, dev);
         SetupGetLibLayout(SETUP_LAYOUT_STOR, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_STOR, cTemp, dev);
         SetupGetLibLayout(SETUP_LAYOUT_HINW, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_HINW, cTemp, dev);
         SetupGetLibLayout(SETUP_LAYOUT_RECHKOPF, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_RECHKOPF, cTemp, dev);
         SetupGetLibLayout(SETUP_LAYOUT_RECHPOST, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_RECHPOST, cTemp, dev);
         SetupGetLibLayout(SETUP_LAYOUT_RECHENDE, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_RECHENDE, cTemp, dev);
         SetupGetLibLayout(SETUP_LAYOUT_RECHHINW, cTemp, -1);
         SetupSetExtLayout(SETUP_LAYOUT_RECHHINW, cTemp, dev);
         }
         break;
    case -1:
         boFertig = TRUE;
         break;
    case 0:
         SetupLayEdit( dev, SETUP_LAYOUT_KOPF, " Bonlayout - Kopf " );
         break;
    case 1:
         SetupLayEdit( dev, SETUP_LAYOUT_BEST, " Bonlayout - Bestellung " );
         break;
    case 2:
         SetupLayEdit( dev, SETUP_LAYOUT_ENDE, " Bonlayout - Ende " );
         break;
    case 3:
         SetupLayEdit( dev, SETUP_LAYOUT_STOR, " Bonlayout - Stornierung " );
         break;
    case 4:
         SetupLayEdit( dev, SETUP_LAYOUT_HINW, " Bonlayout - Hinweise " );
         break;
    case 5:
         if( dev==-1 )
          SetupStruktur();
         break;
    case 6:
         if( dev!=-1 )
          SetupLayEdit( dev, SETUP_LAYOUT_RECHKOPF, " Rechnungslayout - Kopf " );
         break;
    case 7:
         if( dev==-1 )
          SetupLayEdit( dev, SETUP_LAYOUT_RECHKOPF, " Rechnungslayout - Kopf " );
         else
          SetupLayEdit( dev, SETUP_LAYOUT_RECHPOST, " Rechnungslayout - Posten " );
         break;
    case 8:
         if( dev==-1 )
          SetupLayEdit( dev, SETUP_LAYOUT_RECHPOST, " Rechnungslayout - Posten " );
         else
          SetupLayEdit( dev, SETUP_LAYOUT_RECHENDE, " Rechnungslayout - Ende " );
         break;
    case 9:
         if( dev==-1 )
          SetupLayEdit( dev, SETUP_LAYOUT_RECHENDE, " Rechnungslayout - Ende " );
         else
          SetupLayEdit( dev, SETUP_LAYOUT_RECHHINW, " Rechnungslayout - Hinweise " );
         break;
    case 10:
         SetupLayEdit( dev, SETUP_LAYOUT_RECHHINW, " Rechnungslayout - Hinweise " );
         break;
   }
  }
  MnuDone( mnu );
 }

 PRIVATE VOID CDECL     SetupLayEdit ( dev, what, titel )
 INT            dev;
 INT            what;
 CHAR*          titel;
 {
  extern SSetup sSetup;
  extern SETUP  abrech;
  SDlg*         dlg;
  INT           i;
  CHAR          cTemp[5][60];
  CHAR          cShow[5*60+5];
  CHAR          cStatus[100];
//  LAYOUT*       lay;
  SWin*         Preview       = NULL;
  INT           exits[]       = { T_F2, 0, 0 };
  BOOL          boFertig      = FALSE;
  if( dev!=-1 )
  {
   exits[1] = T_F3;
   strcpy( cStatus, " ~F1~ Hilfe  ~F2~ Vorschau  ~F3~ Import" );
  }
  else
   strcpy( cStatus, " ~F1~ Hilfe  ~F2~ Vorschau " );
  if( ( Preview = WinEinrichten( 1, 1, 78, 12 ) ) == NULL )
   return;
  WinSetAttrib( Preview, INVERS, INVERS, INVERS );
  WinSetTitel( Preview," Vorschau: So sieht der Ausdruck aus ", WIN_TITEL_OZ );
  WinSetRahmentyp( Preview, WIN_FRAME_DOUBLE );
  for( i=0; i<5; i++ )
   MemFill( cTemp[i], 0, 60 );
  SetupGetLibLayout(what,cTemp,dev);
 AGAIN:
  *cShow = 0;
  for( i=0; i<5; i++ ) strcat( cShow, cTemp[i] );
  SetupLayShow( Preview, cShow );
  dlg = DlgInit( 5 );
  for( i=0; i<5; i++ )
  {
   DlgInitEntry( dlg, 1, DLG_INPUT, 1, 1, "", SetupInhHelp, cStatus );
   DlgAddField( dlg, 3, i, cTemp[i], DLG_FIELD_ALL, 60 );
  }
  while( !boFertig )
  {
   switch( DlgHandle( dlg, VioCenterCol( 69 ), 14, 69, 9, titel, exits ) )
   {
    case T_F2:
         *cShow = 0;
         for( i=0; i<5; i++ ) strcat( cShow, DlgGetText( dlg, i, 0 ) );
         SetupLayShow( Preview, cShow );
         break;
    case T_F3:
         if( WinMsgCenter( " Achtung!\n"
                           " Alle EintrÑge Åberschreiben und die\n"
                           " bestehenden Daten des Setup-Layouts\n"
                           " Åbernehmen?", MSG_YESNO ) == T_ESC )
          break;
         SetupGetLibLayout(what, cTemp, -1);
         DlgDone(dlg);
         goto AGAIN;
    case T_ESC:
         boFertig = TRUE;
         break;
    case T_RETURN:
         for( i=0; i<5; i++ ) strcpy( cTemp[i], DlgGetText( dlg, i, 0 ) );
         SetupSetExtLayout(what,cTemp,dev);
         boFertig = TRUE;
         break;
   }
  }
  DlgDone( dlg );
  WinEntfernen( Preview );
 }

 PRIVATE VOID CDECL     SetupLayShow ( win, buffer )
 SWin*          win;
 CHAR*          buffer;
 {
  BOOL          breit        = FALSE;
  BOOL          farbe        = FALSE;
  BOOL          cr           = FALSE;
  INT           n;
  INT           k;
  CHAR          temp[70];
  WORD          spalte       = 0;
  WORD          zeile        = 0;
  WinAktivieren( win );
  WinCls();
  for( n=0; n<strlen( buffer ); n++ )
  {
   if( buffer[n]=='@')
   {
    n++;
    if( !SetupGetInh( buffer[n], temp ) )
    {
     n-=2;
     cr = TRUE;
    }
    if( breit )
    {
     for( k=0; k<strlen( temp ); k++ )
     {
      WinSza( spalte, zeile, temp[k], (farbe) ? VH( ROT, WEISS ) : VH( SCHWARZ, WEISS ) );
      spalte+=2;
     }
    }
    else
    {
     WinSsa( spalte, zeile, temp, (farbe) ? VH( ROT, WEISS ) : VH( SCHWARZ, WEISS ) );
     spalte+= strlen( temp );
    }
    if( cr ) { zeile++; spalte=0; cr=FALSE; }
   }
   else
   if( buffer[n]=='!')
   {
    n++;
    switch( buffer[n] )
    {
     case 'F': farbe = TRUE;  break;
     case 'f': farbe = FALSE; break;
     case 'B': breit = TRUE;  break;
     case 'b': breit = FALSE; break;
     case 'C': WinSsa( spalte, zeile, "<CUT>", VH( BLAU, WEISS ) ); spalte+=5; break;
     case 'P': WinSsa( spalte, zeile, "<PERF>", VH( BLAU, WEISS ) ); spalte+=6; break;
     case 'L': spalte = 0; zeile++; break;
     default:  n--;
    }
   }
   else
   {
    WinSza( spalte, zeile, buffer[n], (farbe) ? VH( ROT, WEISS ) : VH( SCHWARZ, WEISS ) );
    spalte++;
    if( breit ) spalte++;
   }
  }
 }

 PRIVATE BOOL CDECL     SetupGetInh  ( inh, buff )
 CHAR           inh;
 CHAR*          buff;
 {
  extern SInfo  info;
  static INT    pos          = 0;
  *buff = 0;
  switch( inh )
  {
   // V5.5: WÑhrungsbezeichner
   case 'W': strcpy( buff, info.waehrungsbezeichner ); break;
   case 'T': strcpy( buff, "025" ); break;
   case 't': strcpy( buff, "01" ); break;
   case 'B': strcpy( buff, "451" ); break;
   case 'Z': strcpy( buff, "16:45:02" ); break;
   case 'D': strcpy( buff, "29.07.1993" ); break;
   case 'K': strcpy( buff, "Herr TestLangenName" ); break;
   case 'k': strcpy( buff, "17" ); break;

   case 'V': strcpy( buff, "200 gr" ); break;

   case 'N': strcpy( buff, "10" ); break;
   case 'A': strcpy( buff, "Hummer-Rum. Kombin." ); break;
   case 'a': strcpy( buff, "1650" ); break;
   case 'P': WaehrPreis(12000,buff); break;
   case 'G': WaehrPreis(1200000L,buff); break;

      /* Rechnungsbeispiele */
   case 'r': strcpy( buff, "2.50" ); break;
   case 'g': strcpy( buff, "10.00" ); break;
   case 'R': strcpy( buff, "4711" ); break;
   case 'E': strcpy( buff, "4250.00" ); break;
   case 'M': switch( pos++ )
             {
              case 0: strcpy( buff, "Incl. 7.00%% MWSt: 152.40 DM" );
                      return( FALSE );
              case 1: strcpy( buff, "Incl.16.00%% MWSt: 322.20 DM" );
                      pos = 0;
                      break;
             }
             break;
   case 'O': strcpy( buff, "Bar" ); break;
   case 'X': switch( pos++ )
             {
              case 0: strcpy( buff, "Bar       : 20.00 DM" );
                      return( FALSE );
              case 1: strcpy( buff, "Eurocard  : 12.50 DM" );
                      return( FALSE );
              case 2: strcpy( buff, "Scheck    : 34.00 DM" );
                      pos=0; break;
             }
             break;
   case 'x': strcpy( buff, "Bar: 20.00; Eurocard: 12.50; Scheck: 34.00" ); break;
   case 'Y': strcpy( buff, "Trinkgeld: 5.40 DM" ); break;
  }
  return( TRUE );
 }

 PRIVATE VOID CDECL     SetupInhHelp ( dlg )
 SDlg*          dlg;
 {
  SWin*         win          = WinEinrichten( 1, 1, 78, 23 );
  dlg = dlg;
  if( win == NULL ) return;
  WinSchattenEin( win );
  WinSetAttrib( win, VH(WEISS,BLAU), VH( WEISS,BLAU ), VH( WEISS,BLAU ));
  WinSetTitel( win," LAYOUT - HILFE ",WIN_TITEL_OZ );
  WinSetRahmentyp( win, 1 );
  WinAktivieren( win );
  WinCls();
  WinSsa( 1,1,"Steuerzeichen :",VH( HELLWEISS,BLAU ) );
  WinSwza( 1,2,74,4,' ',VH( GELB,KOBALT) );
  WinSsa( 3,3,"!C = Cut",VH( GELB,KOBALT) );
  WinSsa( 3,4,"!P = Perforieren",VH( GELB,KOBALT) );
  WinSsa( 3,5,"!G = Grafik",VH( GELB,KOBALT) );
  WinSsa( 23,3,"!B = Breit ein",VH( GELB,KOBALT) );
  WinSsa( 23,4,"!b = Breit aus",VH( GELB,KOBALT) );
  WinSsa( 41,3,"!F = Farbe ein",VH( GELB,KOBALT) );
  WinSsa( 41,4,"!f = Farbe aus",VH( GELB,KOBALT) );
  WinSsa( 59,3,"!L = Neue Zeile",VH( GELB,KOBALT) );
  WinSsa( 59,4,"!I = Init-Code",VH( GELB,KOBALT) );

  WinSsa( 1,8,"Kopf :",VH( HELLWEISS,BLAU ) );
  WinSwza( 1,9,21,9,' ',VH( GELB,KOBALT) );
  WinSsa( 3,10,"@T = Tischnummer",VH(GELB,KOBALT) );
  WinSsa( 3,11,"@t = Parteinummer",VH(GELB,KOBALT) );
  WinSsa( 3,12,"@B = Bonnummer",VH( GELB,KOBALT) );
  WinSsa( 3,13,"@Z = Zeit",VH(GELB,KOBALT) );
  WinSsa( 3,14,"@D = Datum",VH(GELB,KOBALT) );
  WinSsa( 3,15,"@K = Kellner",VH(GELB,KOBALT) );
  WinSsa( 3,16,"@k = Kellnernummer",VH(GELB,KOBALT) );
  WinSsa( 3,17,"@W = WÑhrungsbez.",VH(GELB,KOBALT) );


  WinSsa( 25,9,"Artikel :",VH( HELLWEISS,BLAU ) );
  WinSwza( 25,10,24,8,' ',VH( GELB,KOBALT ) );
  WinSsa( 27,10,"@V = Gramm/Anzahl",VH(GELB,KOBALT) );
  WinSsa( 27,11,"@N = Anzahl",VH(GELB,KOBALT) );
  WinSsa( 27,12,"@A = Artikelname",VH(GELB,KOBALT) );
  WinSsa( 27,13,"@a = Artikelnummer",VH(GELB,KOBALT) );
  WinSsa( 27,14,"@P = Einzelpreis",VH(GELB,KOBALT) );
  WinSsa( 27,15,"@G = Ein.preis * Anz.",VH(GELB,KOBALT) );
  WinSsa( 27,16,"@S = Kurzbezeichnung",VH(GELB,KOBALT) );
  WinSsa( 27,17,"@n = Anz. Posten/Bon",VH(GELB,KOBALT) );

  WinSsa( 52,9,"Rechnung :",VH(HELLWEISS,BLAU ) );
  WinSwza( 52,10,23,8,' ',VH( GELB,KOBALT ) );
  WinSsa( 54,10,"@r = RÅckgeld",VH(GELB,KOBALT) );
  WinSsa( 54,11,"@R = Rechnungsnummer",VH(GELB,KOBALT) );
  WinSsa( 54,12,"@E = Endbetrag",VH(GELB,KOBALT) );
  WinSsa( 54,13,"@M = Steuerbetrag",VH(GELB,KOBALT) );
  WinSsa( 54,14,"@O = Abr. Art",VH(GELB,KOBALT) );
  WinSsa( 54,15,"@X = Wie @O v. Spl.",VH(GELB,KOBALT) );
  WinSsa( 54,16,"@x = Wie @O h. Spl.",VH(GELB,KOBALT) );
  WinSsa( 54,17,"@Y = fÅhrt Tip aus",VH(GELB,KOBALT) );

  WinSsa( 1,20," Taste = Abbruch ",VH( BRAUN,SCHWARZ ) );
  EvGetKey();
  WinEntfernen(win);
 }

 PRIVATE VOID CDECL     SetupStruktur( void )
 {
  SDlg*         dlg;
  INT           i;
  dlg = DlgInit( 10 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 1, "~I~nit..........:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetHinweisInit(), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 2, "~E~nde..........:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetHinweisEnd(), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 4, "Hinweis auf F~1~:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetHinweisText(0), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 5, "Hinweis auf F~2~:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetHinweisText(1), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 6, "Hinweis auf F~3~:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetHinweisText(2), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 7, "Hinweis auf F~4~:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetHinweisText(3), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 9, "~Z~wischenfolge.:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetHinweisZwischen(), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1,11, "~T~alon-Kennung.:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetTalon(), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1,12, "~D~oppelbon-Kenn:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetDoppelbon(), DLG_FIELD_ALL, 40 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1,13, "Ti~p~-Text......:", SetupInhHelp, " ~F1~ Hilfe ≥ Die Hinweise, Tip, Talon, Doppelbon-Kennzeichnung " );
  DlgAddField ( dlg, 17, 0, SetupGetTip(), DLG_FIELD_ALL, 40 );
  if( DlgHandle( dlg, VioCenterCol( 69 ) , VioCenterRow( 17 ), 69, 17, " Bonstruktur ", NULL ) == T_RETURN )
  {
   SetupSetHinweisInit( DlgGetText( dlg, 0, 0 ) );
   SetupSetHinweisEnd ( DlgGetText( dlg, 1, 0 ) );
   for( i=0; i<4; i++ )
    SetupSetHinweisText( i, DlgGetText( dlg, 2+i, 0 ) );
   SetupSetHinweisZwischen( DlgGetText( dlg, 6, 0 ) );
   SetupSetTalon( DlgGetText( dlg, 7, 0 ) );
   SetupSetDoppelbon( DlgGetText( dlg, 8, 0 ) );
   SetupSetTip( DlgGetText( dlg, 9, 0 ) );
  }
  DlgDone( dlg );
 }

