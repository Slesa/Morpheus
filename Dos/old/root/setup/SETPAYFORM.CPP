#include			"gf5map/Payform.h"
#include			"gf5map/Currency.h"
#include "/gastro/src/include/hilevel/MsgWin.h"
#include "/gastro/src/include/hilevel/LstWin.h"
#include "/gastro/src/include/hilevel/Vio.h"
#include "/gastro/src/include/hilevel/Dlg.h"
// #include       "basics/Disk.h"
//  #include       "basics/MemAlloc.h"
#include "/gastro/src/include/defs/Keydefs.h"
#include			<stdlib.h>
#include			<string.h>
#include			<stdio.h>

extern "C" void CDECL SetupAbrMenu();

static void CDECL GetTerminalNrHelp(SDlg* dlg);
static void CDECL SetupAbrHilf(SDlg* dlg);
static void CDECL SetupAbrHelp();
static void pay2List(SLst* lst, TPayform* pay, bool change=false);
static void empty2List(SLst* lst, int i, bool change=false);
static TPayform* SetupAbrEdit(int pay, TPayformList& pays);

 // ----------- Interne Funktionen -------------------------------------------
// PRIVATE BOOL CDECL     SetupAbrEdit  ( INT  );          // Abrechnungsart editieren
// PRIVATE BOOL CDECL     GetAbrText( CHAR*, INT );
// PRIVATE BOOL CDECL     EditAbrText( INT );

// void SetupAartInit();
// void SetupAartDone();
// void SetupAartSave();
// CHAR* SetupGetAartExternal( int, CHAR* );
// int   SetupSetAartExternal( int, CHAR* );
// int   SetupDelAartExtern( int );

void CDECL SetupAbrMenu()
{
	SLst*		lst;
	TPayformList	pays;
	pays.load();

	if( pays.count()==0 && !SetupAbrEdit(0, pays) )
	{
		return;
	}

	lst = LstInit(70);
	for(int i=1; i<=pays.count(); i++ )
	{
		TPayform* pay = (TPayform*) pays.find(i);
		if( pay )
			pay2List(lst, pay);
		else
			empty2List(lst, i+1);
	}

	INT AbrExit[] = { /*T_INS,*/ T_DEL, 0 };
	bool boFertig = false;
	while( !boFertig )
	{
		int ret = LstShow(lst, LST_LIST, VioCenterCol( 70 ), VioCenterRow( 17 ), 70, 17, (CHAR*)"Nr ƒ Name ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ Kurzname ƒƒƒƒƒƒ Ges.  Kasse Typ", (CHAR*)" ~F1~ Hilfe  ~ENTF~ Lîschen ≥ WÑhlen Sie eine Abrechnungsart", AbrExit, SetupAbrHelp);
		switch( ret )
//   switch( ListShow( &AbrList, " Abrechnungsart auswÑhlen ", " [F1] Hilfe ≥ WÑhlen Sie die zu bearbeitende Abrechnungsart", NULL, SetupAbrHelp ) )
		{
		case T_ESC:
			boFertig = true;
			break;
		case T_DEL:
			if( WinMsgCenter((CHAR*)
					"            ACHTUNG\n"
					"  Sind Sie sicher, da· Sie diese\n"
					"  Abrechnungsart lîschen mîchten?\n"
					"    Bedenken Sie, da· in Ihrer\n"
					"  Auswertung die entsprechenden\n"
					"  UmsÑtze nicht mehr auftauchen!"
					, MSG_YESNO) != T_RETURN )
				break;
			i = (int) LstGetNum( lst );
			pays.remove(i);
			empty2List(lst, i, true);
			break;
		case T_RETURN:
			i = LstGetNum(lst);
			TPayform* pay = SetupAbrEdit(i, pays);
			if( pay )
			{
				pay2List(lst, pay, true);
				pays.save();
			}
			break;
		}
	}
	LstDone( lst );
}
#include <conio.h>
TPayform* SetupAbrEdit(int abr, TPayformList& pays)
{
	TCurrencyList	currs;
	currs.load();

	bool created = false;
	TPayform* pay = (TPayform*) pays.find(abr);
	if( !pay )
	{
		pay = new TPayform(abr);
		created = true;
	}

	SDlg* dlg = DlgInit(7);
	DlgInitEntry(dlg, 1, DLG_INPUT, 1, 1, (CHAR*)"~N~ame.......... :", SetupAbrHilf, (CHAR*)" ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ≥ Der Name der Abrechnungsart");
	DlgAddField (dlg, 18, 0, (CHAR*)(const char*)pay->getName(), DLG_FIELD_ALL, 30 );
	DlgInitEntry(dlg, 1, DLG_INPUT, 1, 2, (CHAR*)"~K~urzbezeichnung:", SetupAbrHilf, (CHAR*)" ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ≥ Die Kurzbez. der Abrechnungsart" );
	DlgAddField (dlg, 18, 0, (CHAR*)(const char*)pay->getShortname(), DLG_FIELD_ALL, 13 );
	char tmpType[2];
	sprintf(tmpType, "%c", pay->getType());
	DlgInitEntry(dlg, 1, DLG_INPUT, 1, 3, (CHAR*)"~T~yp............:", SetupAbrHilf, (CHAR*)" ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ≥ Der Typ der Abrechnungsart" );
	DlgAddField (dlg, 18, 0, (CHAR*)tmpType, DLG_FIELD_ALL, 1);
	TCurrency* curr = currs.sysCurrency();
	QString tmpLim = currs.format(pay->getMaxLimit(), 7, curr);

	int pos = 7;
	int cnt = 70;
	if( curr )
	{
		pos = (7-curr->getDecPos())*10+curr->getDecPos();
		cnt = curr->getDecPos() ? 7 : 6;
	}
	DlgInitEntry(dlg, 1, DLG_INPUT, 1, 4, (CHAR*)"~B~etraglimit....:", SetupAbrHilf, (CHAR*)" ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ≥ Limit der Abrechnungsart" );
	DlgAddField (dlg, 18, 0, (CHAR*)(const char*)tmpLim, pos, cnt);
/*
  CHAR          cTemp[15];
  CHAR          cAartExt[68];
  INT           iExitKeys[]  = { T_F2, 0 };
  BOOL          boRet        = FALSE;
  BOOL          boFertig     = FALSE;
  if( SetupGetAartLimit(iAbr)<0 ) SetupSetAartLimit(iAbr,0);
  WaehrSetLength( 8 );
  WaehrPreis( SetupGetAartLimit(iAbr), cTemp );
  WaehrSetLength( 7 );
*/
	DlgInitEntry(dlg, 1, DLG_INPUT, 1, 5, (CHAR*)"~E~xternes Prog..:", SetupAbrHilf, (CHAR*)" ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ≥ Das externe Programm fÅr diese Abrech.art");
	DlgAddField (dlg, 18, 0, (CHAR*)(const char*)pay->getExtern(), DLG_FIELD_ALL, 8);
	DlgInitEntry(dlg, 2, DLG_CHECK, 1, 7, (CHAR*)"Enthalten im...", SetupAbrHilf, (CHAR*)" ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ≥ Weitere Angaben zur Abrechnungsart");
	DlgAddField (dlg, 1, 1, (CHAR*)"~G~esamtumsatz", pay->isInSummary(), 0);
	DlgAddField (dlg, 1, 2, (CHAR*)"K~a~ssenumsatz", pay->isInTermSummary(), 0);
	DlgInitEntry(dlg, 4, DLG_CHECK, 1, 11, (CHAR*)"Sonstige Flags.", SetupAbrHilf, (CHAR*)" ~F1~ Hilfe  ~F2~ Abrechnungstext editieren ≥ Weitere Angaben zur Abrechnungsart");
	DlgAddField (dlg, 1, 1, (CHAR*)"~K~eine Schublade", !pay->isOpenDrawer(), 0);
	DlgAddField (dlg, 1, 2, (CHAR*)"~R~Åckgeld fragen", pay->isAskMoney(), 0);
	DlgAddField (dlg, 21, 1,(CHAR*)"T~i~p erfragen", pay->isAskTip(), 0);
	DlgAddField (dlg, 21, 2,(CHAR*)"GÑ~s~te erfragen", pay->isAskGuestCount(), 0);

	INT iExitKeys[] = { T_F2, 0 };
	bool fertig = false;
	QString tmp;
	while( !fertig )
	{
		int ret = DlgHandle( dlg, VioCenterCol( 56 ), VioCenterRow( 17 ), 56, 17, (CHAR*)" Abrechnungsart editieren ", iExitKeys);
		switch( ret )
		{
		case T_ESC:
			fertig = true;
			if( created )
			{
				delete pay;
				pay = NULL;
			}
			break;
		case T_RETURN:
			tmp = (char*)DlgGetText(dlg, 0, 0);
			if( tmp.isEmpty() )
			{
				printf( "%c", 7 );
				break;
			}
/*
         if( !SetupSetAartExternal(iAbr, DlgGetText(dlg, 4, 0)) )
         {
          WinMsgCenter(" Fehler beim Abspeichern der Abrechngsdaten", MSG_INFO);
          break;
         }
*/
			pay->setName((char*)DlgGetText(dlg, 0, 0));
			pay->setShortname((char*)DlgGetText(dlg, 1, 0));
			strcpy(tmpType, (char*)DlgGetText(dlg, 2, 0));
			pay->setType(tmpType[0]);

			pay->setMaxLimit(currs.scan((char*)DlgGetText(dlg,3,0), curr));
			pay->setInSummary(DlgIsMarked(dlg, 5, 0));
			pay->setInTermSummary(DlgIsMarked( dlg, 5, 1));
			pay->setOpenDrawer(!DlgIsMarked( dlg, 6, 0));
			pay->setAskMoney(DlgIsMarked( dlg, 6, 1));
			pay->setAskTip(DlgIsMarked( dlg, 6, 2));
			pay->setAskGuestCount(DlgIsMarked(dlg, 6, 3));
			fertig = true;
			break;
		case T_F2:
//			EditAbrText( iAbr+1 );
			break;
		}
	}
	DlgDone(dlg);
	return pay;
}

#if(0)
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
    sprintf( cStatus, "Zeile %hd  ≥ Geben Sie den Individuellen Abrechnungs Text ein", i+1 );
    DlgInitEntry( dlg, 1, DLG_INPUT, 1, i++, NULL, NULL, cStatus );
    DlgAddField ( dlg, 1, 0,  cTemp, DLG_FIELD_ALL, 60 );
    if( i>=22 )
    {
     WinMsgCenter( " Achtung: Der Rechnungstext ist zu gro·, um in diesem\n"
                   " Dialog bearbeitet zu werden.", MSG_INFO);
     break;
    }
   }
   DskFileClose( fh );
  }
  for( ; i<22; i++ )
  {
   sprintf( cStatus, "Zeile %hd  ≥ Geben Sie den Individuellen Abrechnungs Text ein", i+1 );
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
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, 1, "~T~erminal Nr... :", GetTerminalNrHelp, " ~F1~ Hilfe ≥ Geben Sie die Terminal Nummer ein" );
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
#endif

static void pay2List(SLst* lst, TPayform* pay, bool change)
{
	if( !change )
		LstInsert(lst, (LONG) pay->getNumber(), (CHAR*)"%2hd) %-30s %-14s  %s  %s   %c"
			, pay->getNumber()
			, (const char*) pay->getName()
			, (const char*) pay->getShortname()
			, pay->isInSummary() ? "Ja  " : "Nein"
			, pay->isInTermSummary() ? "Ja  " : "Nein"
			, pay->getType()
			);
	else
		LstChange(lst, (LONG) pay->getNumber(), (LONG) pay->getNumber(), (CHAR*)"%2hd) %-30s %-14s  %s  %s   %c"
			, pay->getNumber()
			, (const char*) pay->getName()
			, (const char*) pay->getShortname()
			, pay->isInSummary() ? "Ja  " : "Nein"
			, pay->isInTermSummary() ? "Ja  " : "Nein"
			, pay->getType()
			);
}

static void empty2List(SLst* lst, int i, bool change)
{
	if( !change )
		LstInsert(lst, (LONG) i, (CHAR*)"%2hd) %-30s %-14s  %s  %s   %c"
			, i+1
			, "<Nicht belegt>"
			, "<Nicht belegt>"
			, "----"
			, "----"
			, '-'
			);
	else
		LstChange(lst, (LONG) i, (LONG) i, (CHAR*)"%2hd) %-30s %-14s  %s  %s   %c"
			, i
			, "<Nicht belegt>"
			, "<Nicht belegt>"
			, "----"
			, "----"
			, '-');
}

static void CDECL SetupAbrHilf(SDlg* dlg)
{
	dlg = dlg;
#if( defined LIGHT )
	WinMsgCenter((CHAR*)
		 " Hilfe zu den Abrechnungsarten\n\n"
		" Geben Sie die Namen der Abrechnungsarten an und ob diese im  Gesamt-\n"
		" umsatz und im Kassenbetrag der Kellner berÅcksichtigt werden sollen.\n\n"
		" Im Typ einer Abrechnungsart kann folgendes festgelegt werden:\n\n"
		" Typ = 'S': A.Art wird beim Finanzsplitting aufgefÅhrt\n"
		" Typ = 'T': Bei dieser A.Art wird der Tip (Trinkgeld) verwaltet\n"
		" Typ = 'K': Kombination aus 'S' und 'T' (Finanzspl. und Trinkgeld)\n"
		"\n Pseudo-Abrechnungsarten klein 's' und 't' siehe Handbuch!"
		, MSG_INFO);
#else
	WinMsgCenter((CHAR*)
		" Hilfe zu den Abrechnungsarten\n\n"
		" Geben Sie die Namen der Abrechnungsarten an und ob diese im  Gesamt-\n"
		" umsatz und im Kassenbetrag der Kellner berÅcksichtigt werden sollen.\n\n"
		" Im Typ einer Abrechnungsart kann folgendes festgelegt werden:\n\n"
		" Typ = 'S': A.Art wird beim Finanzsplitting aufgefÅhrt\n"
		" Typ = 'T': Bei dieser A.Art wird der Tip (Trinkgeld) verwaltet\n"
		" Typ = 'K': Kombination aus 'S' und 'T' (Finanzspl. und Trinkgeld)\n"
		" Typ = 'H': Kennzeichnet A.Art als 'AUF ZIMMER' mit Online-Schnittst.\n"
		"            (die Schnittstelle zusÑtzlich per Schalter aktivieren!)\n"
		" Typ = 'E': Startet externes Programm, das per Schalter def. wurde\n"
		"\n Pseudo-Abrechnungsarten klein 's' und 't' siehe Handbuch!"
		, MSG_INFO);
#endif
}

static void CDECL SetupAbrHelp()
{
	WinMsgCenter((CHAR*)
		" WÑhlen Sie aus dem MenÅ die Abrechnungs-\n"
		" art aus, die Sie bearbeiten mîchten.\n"
		" ZusÑtzlich kînnen Sie mit [EINF] eine neue\n"
		" Abrechnungsart anlegen oder mit [ENTF] \n"
		" eine nicht mehr benîtigte Abrechnungsart\n"
		" lîschen."
		, MSG_INFO);
}

static void CDECL GetTerminalNrHelp(SDlg* dlg)
{
	dlg = dlg;
	WinMsgCenter((CHAR*)
		" Bitte geben Sie hier die Terminalnummer ein\n"
		"       FÅr den Master bitte 0 eingeben        ",MSG_INFO);
}


