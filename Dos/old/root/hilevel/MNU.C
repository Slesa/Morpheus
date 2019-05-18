/****************************************************************************/
/* MNU.C                                                                    */
/* ------------------------------------------------------------------------ */
/* Funktionen zur Verwaltung von Menues.                                    */
/****************************************************************************/
 #include       "hilevel/Mnu.h"                  /* Eigene Headerdatei      */
 #include       "defs/Keydefs.h"                 /* Tastendefinitionen      */
 #include       "defs/Errordef.h"                /* Fehlerdefinitionen      */
 #include       "hilevel/Event.h"                /* Event-Handling          */
 #include       "hilevel/Palette.h"              /* Menu-Palette            */
 #include       "hilevel/Vio.h"                  /* Ausgaberoutinen         */
 #include       "hilevel/EvMouse.h"              /* Mausroutinen            */
 #include       "lolevel/PcMouse.h"              /* Mausroutinen            */
 #include       "basics/MemAlloc.h"              /* Speicherverwaltungsroutinen */
 #include       <string.h>                       /* Stringroutinen          */
 #include       <ctype.h>                        /* Wegen toupper()         */
 #include       <stdio.h>                        /* Standard-IO             */

 #define        __FUNC__     ERR_MNU_INIT
 SMnu* CDECL    MnuInit      ( bCount )
 BYTE           bCount;                          /* Anzahl zu reservierender Eintraege */
 {
  SMnu*         mnu          = MemAlloc( sizeof( SMnu ) );
  Assert( mnu!=NULL, ERR_MEM_ALLOC );
  mnu->Entry = MemAlloc( sizeof( SMnuEntry ) * bCount ); /* Speicher fuer Eintraege anfordern */
  Assert( mnu->Entry!=NULL, ERR_MEM_ALLOC );     /* Falls zu wenig Speicher: raus */
  mnu->bCount  = bCount;                         /* Anzahl verfuegbarer Eintraege merken */
  mnu->bActual = 0;                              /* Noch kein Eintrag da    */
  mnu->bCurrent= 0;                              /* Beim Handling bei 0 anfangen */
  mnu->Win     = NULL;
  return( mnu );                                 /* Kein Fehler aufgetreten */
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_MNU_DONE
 VOID CDECL     MnuDone      ( mnu )
 SMnu*          mnu;                             /* Aufzuloesendes Menue    */
 {
  Assert( mnu!=NULL, ERR_PTR );
  if( mnu->Win ) WinEntfernen( mnu->Win );       /* Fenster verwerfen       */
  MemFree( mnu->Entry, sizeof( SMnuEntry ) * mnu->bCount  ); /* Die Eintraege loeschen */
  MemFree( mnu, sizeof( SMnu ) );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_MNU_ADD
 VOID CDECL     MnuAdd       ( mnu, wX, wY, pcText, pcStatus )
 SMnu*          mnu;                             /* Zu bearbeitendes Menue  */
 WORD           wX;                              /* Spalte des Eintrags     */
 WORD           wY;                              /* Zeile des EIntrags      */
 CHAR*          pcText;                          /* Menue-Text              */
 CHAR*          pcStatus;                        /* Statuszeile beim Selektieren */
 {
  Assert( mnu!=NULL, ERR_PTR );                  /* Falls falscher Deskriptor: raus */
  if( mnu->bActual>=mnu->bCount ) return;        /* Falls zu viele Eintrage: raus */
  mnu->Entry[mnu->bActual].iHotkey = WinGetHotkey( pcText ); /* Die verschiedenen Werte zuordnen */
  mnu->Entry[mnu->bActual].pcText  = pcText;
  mnu->Entry[mnu->bActual].pcStatus= pcStatus;
  mnu->Entry[mnu->bActual].wX      = wX;
  mnu->Entry[mnu->bActual].wY      = wY;
  mnu->bActual++;                                /* Nummer des naechsten Eintrags anpassen */
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_MNU_HANDLE
 INT  CDECL     MnuHandle    ( mnu, pcTitel, wX, wY, piExit, help )
 SMnu*          mnu;                             /* Darzustellendes Menue   */
 CHAR*          pcTitel;                         /* Titel des Menues        */
 WORD           wX;                              /* Spalte des Fensters     */
 WORD           wY;                              /* Zeile des Fensters      */
 INT*           piExit;
 FMnuHelp       help;                            /* Hilfefunktion des Menues */
 {
  INT           i, n;                            /* Laufvariable            */
  INT           iCmd;                            /* Auszuwertende Taste     */
  WORD          wMouX;
  WORD          wMouY;
  WORD          wMouState;
  INT           iRet         = -1;               /* Return-Wert der Funktion */
  BOOL          boFertig     = FALSE;            /* Flag, ob Menue abgearbeitet */
  Assert( mnu!=NULL, ERR_PTR );
  if( mnu->Win==NULL )                           /* Wenn Fenster noch nicht da */
  {
   WORD         wHeight      = 0;
   WORD         wWidth       = 0;                /* Breite des Fensters     */
   /* --------- Hoehe ermitteln ------------------------------------------- */
   for( i=0; i<mnu->bActual; i++ )               /* Alle Eintraege durchlaufen */
   {
    if( mnu->Entry[i].wY>wHeight ) wHeight = mnu->Entry[i].wY;
   }
   /* --------- Breite ermitteln ------------------------------------------ */
   for( i=0; i<mnu->bActual; i++ )               /* Alle Eintraege durchlaufen */
   {
    if( ( mnu->Entry[i].wX + strlen(mnu->Entry[i].pcText) ) > wWidth )
     wWidth = mnu->Entry[i].wX + strlen( mnu->Entry[i].pcText );
   }
   mnu->Win = WinEinrichten( wX, wY, wWidth+2, wHeight+4 );
   Assert( mnu->Win!=NULL, ERR_MEM_ALLOC);
   WinSchattenEin( mnu->Win );                   /* Menues haben einen Schatten */
   WinSetRahmentyp( mnu->Win, WIN_FRAME_DOUBLE );/* und doppelten Rahmen    */
   WinSetTitel( mnu->Win, pcTitel, WIN_TITEL_OZ ); /* Den Titel setzen        */
   WinSetAttrib( mnu->Win, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_FRAME ), MnuGetPal( MNU_PAL_TITLE ) );
   WinCursor( WIN_CUR_HIDE );                    /* Attribute setzen und Cursor aus */
   MouSetRange( wX+2, wY+2, wX+wWidth-2, wY+wHeight+1 );
   MouSetPos( wX+2, wY+2 );
   WinAktivieren( mnu->Win );                    /* Jetzt erst Fenster aktivieren */
   WinCls();                                     /* Fensterinhalt loeschen wg Attributen */
   for( i=0; i<mnu->bActual; i++ )
    WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
  }
  else
  {
   MouSetRange( wX+2, wY+2, wX+mnu->Win->wWidth-3, wY+mnu->Win->wHeight-2 );
   WinAktivieren( mnu->Win );                    /* Jetzt erst Fenster aktivieren */
  }
  i=mnu->bCurrent;                              /* Eintraege darstellen und beim aktuellen Eintrag anfangen */
  while( !boFertig )                             /* (Dieser muss nicht mehr 0 sein) */
  {                                              /* Solange nicht ESC gedrueckt     */
   if( strlen( mnu->Entry[i].pcText ) > 0 )      /* Falls der Eintrag gueltig       */
   {
    WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_INVERS ), MnuGetPal( MNU_PAL_INVHOT ) );
    VioStatus( mnu->Entry[i].pcStatus, MnuGetPal( MNU_PAL_STATUS ), MnuGetPal( MNU_PAL_INVSTAT ) );
    iCmd = EvGetKey();                           /* Balken darstellen, Statuszeile updaten */
   }                                             /* und Taste holen         */
   if( piExit!=NULL )
   {
    for( n=0; piExit[n]!=0; n++ )
     if( piExit[n]==iCmd )
     {
      iRet     = iCmd;
      boFertig = TRUE;
     }
   }
   switch( iCmd )                                /* Falls Eintrag ungueltig: */
   {
    case MOU_MOVED:
         WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
         EvMouGetVal( &wMouX, &wMouY, &wMouState );
         wMouY -= wY+2;
          if( ( wMouY<mnu->bActual )
          && ( strlen( mnu->Entry[wMouY].pcText ) > 0 )/* Falls der Eintrag gueltig  */
           )
          i = (INT) wMouY;
         break;
    case MOU_LEFTPRESS:
         WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
         boFertig = TRUE;
         iRet = i;
         break;
    case T_RETURN:
         boFertig = TRUE;                        /* Bei RET sind wir fertig  */
         iRet     = i;                           /* Rueckgabewert ist aktueller Eintrag */
         mnu->bCurrent = (BYTE)iRet;             /* Aktuelle Menue-Position merken */
         break;
    case T_UP:                                   /* Balken wieder ausschalten */
         WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
         if( --i<0 ) i=mnu->bActual-1;           /* und neue Position berechnen */
         break;
    case T_DOWN:                                 /* Ebenso bei Cursor runter */
         WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
         if( ++i>=mnu->bActual ) i=0;            /* Neue Position berechnen */
         break;
    case MOU_RIGHTPRESS:
    case T_F1:                                   /* Falls eine Hilfefunktion angegeben */
         if( help )
         {
          help();                                /* diese aufrufen          */
          WinAktivieren( mnu->Win );
         }
         break;
    case T_ESC:
         boFertig = TRUE;                        /* Bei ESC sind wir auch fertig */
         iRet     = -1;                          /* Rueckgabewert negativ machen */
         mnu->bCurrent = (BYTE)i;                /* Aktuelle Menue-Position merken */
         break;
    default:
         iCmd = toupper( iCmd );                 /* Sonst nachsehen, ob es  */
         for( n=0; n<mnu->bActual; n++ )         /* vielleicht ein Hotkey ist */
          if( iCmd==mnu->Entry[n].iHotkey )      /* und entsprechenden      */
          {                                      /* Menuepunkt aktivieren   */
           WinHot( mnu->Entry[i].wX, mnu->Entry[i].wY, mnu->Entry[i].pcText, MnuGetPal( MNU_PAL_TEXT ), MnuGetPal( MNU_PAL_HOTKEY ) );
           iRet = n;
           boFertig = TRUE;
           mnu->bCurrent = (BYTE)iRet;           /* Aktuelle Menue-Position merken */
           WinHot( mnu->Entry[n].wX, mnu->Entry[n].wY, mnu->Entry[n].pcText, MnuGetPal( MNU_PAL_INVERS ), MnuGetPal( MNU_PAL_INVHOT ) );
          }
   }
  }
  MouSetRange( 0, 0, VioGetMaxCol()-1, VioGetMaxRow()-1 );
  return( iRet );                                /* und mit Rueckgabewert raus */
 }
 #undef         __FUNC__

#ifdef          _TEST_MNU_

 #include       <DEFS/COLORDEF.H>
 #include       <stdio.h>
 #include       <string.h>

 VOID           MenuHelp     ( void )
 {
  static INT    count        = 0;
  VioSs( 0, count++, "Help was chosen" );
//  WinMeldung( 10, 10, "Dies ist eine Hilfe\nWeil das jeder will!.", MELDUNG_INFO );
 }

 VOID           main         ( void )
 {
  static INT    count        = 0;
  CHAR          cTemp[20];
  SMnu*         mnu;
  INT           ret;
  setbuf( stdout, NULL );
//  VioInit( VIO_GR64x48x16M );
  VioInit( VIO_80x28 );
  EvInit();
  VioBackground();
  mnu = MnuInit( 10 );
  MnuAdd( mnu, 1, 1, "Eintrag ~1~", " [~F1~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 2, "Eintrag ~2~", " [~F2~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 3, "Eintrag ~3~", " [~F3~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 4, "Eintrag ~4~", " [~F4~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 5, "Eintrag ~5~", " [~F5~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 6, "Eintrag ~6~", " [~F6~] Dies ist Eintrag 1" );
  MnuAdd( mnu, 1, 8, "Eintrag ~7~", " [~F7~] Dies ist Eintrag 1" );
  while( ( ret = MnuHandle( mnu, "Eintragswahl", VioCenterCol( 20 ), VioCenterRow( 11 ), MenuHelp ) ) != -1 )
  {
   sprintf( cTemp, "Wahl=%d", ret );
   VioSs( VioGetMaxCol()-strlen( cTemp ), count++, cTemp );
  }
  MnuDone( mnu );
  EvDone();
  VioDone();
 }

#endif
