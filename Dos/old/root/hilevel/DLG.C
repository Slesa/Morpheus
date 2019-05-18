/****************************************************************************/
/* DLG.C                                                                    */
/* ------------------------------------------------------------------------ */
/* Verwaltung von Dialogen.                                                 */
/****************************************************************************/
 #include       "hilevel/Dlg.h"                  /* Eigene Headerdatei      */
 #include       "hilevel/Vio.h"
 #include       "hilevel/Event.h"
 #include       "hilevel/Palette.h"
 #include       "hilevel/EvMouse.h"
 #include       "hilevel/EvKeyb.h"
 #include       "lolevel/PcMouse.h"
 #include       "basics/MemAlloc.h"              /* Speicherverwaltungsroutinen */
 #include       "defs/Typedefs.h"                /* Allgemeine Typen        */
 #include       "defs/Errordef.h"                /* Fehlerdefinitionen      */
 #include       "defs/Keydefs.h"                 /* Tastendefinitionen      */
 #include       "defs/Bitdefs.h"
 #include       <stdlib.h>                       /* NULL-Definition         */
 #include       <string.h>                       /* Stringfunktionen        */
 #include       <ctype.h>                        /* Fuer toupper()          */
 #include       <stdio.h>                        /* Fuer sprintf            */

 /* ----------- Interne Prototypen ---------------------------------------- */
 #define        DLG_NONE     0
 #define        DLG_ENTRY    1
 #define        DLG_FIELD    2
 PRIVATE VOID CDECL     DlgSelect       PARAM(( SDlgEntry*, INT ));
 PRIVATE VOID CDECL     DlgDisplay      PARAM(( SDlg*, INT, INT, BOOL ));
 PRIVATE BOOL CDECL     DlgHandleKey    PARAM(( SDlg*, INT, INT, INT ));
 PRIVATE BOOL CDECL     DlgHandleHot    PARAM(( SDlg*, INT*, INT*, INT ));
 PRIVATE BOOL CDECL     DlgGetMouEnt    PARAM(( SDlg*, WORD, WORD, INT*, INT* ));
 PRIVATE BOOL CDECL     DlgGetPrev      PARAM(( SDlg*, INT*, INT*, INT ));
 PRIVATE BOOL CDECL     DlgGetNext      PARAM(( SDlg*, INT*, INT*, INT ));
 PRIVATE VOID CDECL     DlgComputePos   PARAM(( SDlgEntry* ));

 /***************************************************************************/
 /* DlgInit                                                                 */
 /* ----------------------------------------------------------------------- */
 /* Initialisiert die Struktur eines Dialogs. Es wird Platz fuer count      */
 /* Eintraege reserviert.                                                   */
 /***************************************************************************/
 #define        __FUNC__     ERR_DLG_INIT
 SDlg* CDECL    DlgInit      ( iCount )
 INT            iCount;                          /* Anzahl der Dialogeintraege */
 {
  SDlg*         dlg;                             /* Temporaerer Dialogpuffer*/
  dlg = MemAlloc( sizeof( SDlg ) );              /* Speicher fuer Dialog-Struktur anfordern */
  Assert( dlg!=NULL, ERR_MEM_ALLOC );            /* Test auf Speichermangel */
  /* ---------- Eintrag reservieren --------------------------------------- */
  dlg->Entry = MemAlloc( sizeof( SDlgEntry ) * iCount ); /* Speicher anfordern */
  Assert( dlg->Entry!=NULL, ERR_MEM_ALLOC );
  /* ---------- Parameter merken ------------------------------------------ */
  dlg->iEntCnt  = iCount;                        /* Anzahl der Eintrage merken */
  dlg->iEntAct  = -1;                            /* Naechster zu bearbeitender Eintrag */
  dlg->iEntCur  = 0;                             /* Beim Handling am Anfang anfangen */
  dlg->wFlags   = DLG_FLG_BLOCK;
  dlg->Win      = NULL;
  return( dlg );
 }
 #undef         __FUNC__

 /***************************************************************************/
 /* DlgDone                                                                 */
 /* ----------------------------------------------------------------------- */
 /* Gibt den von dlg belegten Speicher frei.                                */
 /***************************************************************************/
 #define        __FUNC__     ERR_DLG_DONE
 VOID CDECL     DlgDone      ( dlg )
 SDlg*          dlg;                             /* Zu loeschender Dialog   */
 {
  INT           i;
  Assert( dlg!=NULL, ERR_PTR );
  if( dlg->Win ) WinEntfernen( dlg->Win );
  for( i=0; i<=dlg->iEntAct; i++ )
   DlgDoneEntry( &dlg->Entry[i] );
  MemFree( dlg->Entry, sizeof( SDlgEntry ) * dlg->iEntCnt ); /* Speicher der Eintraege freigeben */
  MemFree( dlg, sizeof( SDlg ) );
 }
 #undef         __FUNC__

 /***************************************************************************/
 /* DlgInitEntry                                                            */
 /* ----------------------------------------------------------------------- */
 /* Initialisiert die Struktur eines Dialogeintrags. Es wird Platz fuer     */
 /* count Felder innerhalb des Eintrags reserviert.                         */
 /***************************************************************************/
 #define        __FUNC__     ERR_DLG_INITENTRY
 VOID CDECL     DlgInitEntry ( dlg, iCount, iTyp, wX, wY, pcText, help, pcStatus )
 SDlg*          dlg;                             /* Zu bearbeitender Dialog */
 INT            iCount;                          /* Anzahl der Felder       */
 WORD           wX;                              /* X-Position des Eintrags */
 WORD           wY;                              /* Y-Position des Eintrags */
 INT            iTyp;                            /* Art des Eintrags        */
 CHAR*          pcText;                          /* Eintragstext            */
 FDlgHelp       help;                            /* Hilfefunktion des Eintrags */
 CHAR*          pcStatus;                        /* Statuszeile             */
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( ++dlg->iEntAct<dlg->iEntCnt, ERR_COUNT )             /* Oder zu vielen Eintraegen */
  dlg->Entry[dlg->iEntAct].iTyp     = iTyp;    /* Art der Eintraege       */
  dlg->Entry[dlg->iEntAct].wX       = wX;      /* X-Position der Gruppe   */
  dlg->Entry[dlg->iEntAct].wY       = wY;      /* Y-Position der Gruppe   */
  dlg->Entry[dlg->iEntAct].pcText   = strdup( pcText );  /* Eintragstext der Gruppe */
  dlg->Entry[dlg->iEntAct].pcStatus = strdup( pcStatus );/* Statuszeile             */
  dlg->Entry[dlg->iEntAct].Help     = help;    /* Hilfefunktion           */
  dlg->Entry[dlg->iEntAct].iFldCnt  = iCount;  /* Anzahl der Felder merken */
  dlg->Entry[dlg->iEntAct].iFldAct  = -1;      /* Naechster zu bearbeitender Eintrag */
  dlg->Entry[dlg->iEntAct].iFldCur  = 0;       /* Beim Handling am Anfang anfangen */
  if( iCount!=0 )
  {
   dlg->Entry[dlg->iEntAct].Field = MemAlloc( sizeof( SDlgField ) * iCount );
   Assert( dlg->Entry[dlg->iEntAct].Field!=NULL, ERR_MEM_ALLOC );
  }
 }
 #undef         __FUNC__

 /***************************************************************************/
 /* DlgDoneEntry                                                            */
 /* ----------------------------------------------------------------------- */
 /* Loest die Struktur eines Dialogeintrags auf.                            */
 /***************************************************************************/
 VOID CDECL DlgDoneEntry ( entry )
 SDlgEntry*     entry;                           /* Zu bearbeitender Eintrag */
 {
  INT           i;
  if( entry->iFldCnt )
  {
   if( entry->iTyp==DLG_INPUT )
   {
    for( i=0; i<=entry->iFldAct; i++ )
    {
     MemFree( entry->Field[i].t.Input, sizeof( SDlgInput ) );
     MemFree( entry->Field[i].pcText, entry->Field[i].iLen+2 );
    }
   }
   else
   {
    for( i=0; i<=entry->iFldAct; i++ )
    {
     if( entry->Field[i].pcText!=0 )
      MemFree( entry->Field[i].pcText, 0L );
    }
   }
   MemFree( entry->Field, sizeof( SDlgField ) * entry->iFldCnt );
  }
  MemFree( entry->pcText, 0 );
  MemFree( entry->pcStatus, 0 );
 }

 #define        __FUNC__     ERR_DLG_ENABLE
 VOID CDECL     DlgEnable    ( dlg, iEntry, iField )
 SDlg*          dlg;
 INT            iEntry;
 INT            iField;
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( iEntry<=dlg->iEntAct, ERR_COUNT );
  dlg->Entry[iEntry].Field[iField].wFlags &= ~DLG_FLG_DISABLE;
  if( dlg->Win!=NULL ) DlgDisplay( dlg, iEntry, iField, FALSE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_DISABLE
 VOID CDECL     DlgDisable   ( dlg, iEntry, iField )
 SDlg*          dlg;
 INT            iEntry;
 INT            iField;
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( iEntry<=dlg->iEntAct, ERR_COUNT );
  dlg->Entry[iEntry].Field[iField].wFlags |= DLG_FLG_DISABLE;
  if( dlg->Win!=NULL ) DlgDisplay( dlg, iEntry, iField, FALSE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_ONINIT
 VOID CDECL     DlgOnInit    ( dlg, iEntry, iField, OnInit )
 SDlg*          dlg;
 INT            iEntry;
 INT            iField;
 FDlgOnInit     OnInit;
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( iEntry<=dlg->iEntAct, ERR_COUNT );
  dlg->Entry[iEntry].Field[iField].OnInit = OnInit;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_ONEXIT
 VOID CDECL     DlgOnExit    ( dlg, iEntry, iField, OnExit )
 SDlg*          dlg;
 INT            iEntry;
 INT            iField;
 FDlgOnExit     OnExit;
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( iEntry<=dlg->iEntAct, ERR_COUNT );
  dlg->Entry[iEntry].Field[iField].OnExit = OnExit;
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_SETMARKED
 VOID CDECL     DlgSetMarked ( dlg, iEntry, iWhich, boStatus )
 SDlg*          dlg;                             /* Zu bearbeitender Dialog */
 INT            iEntry;                          /* Nummer der Gruppe       */
 INT            iWhich;
 BOOL           boStatus;                        /* gesetzt oder nicht T/F  */
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( (iEntry<=dlg->iEntAct)&&(iWhich<=dlg->Entry[iEntry].iFldAct), ERR_COUNT );
  Assert( (dlg->Entry[iEntry].iTyp==DLG_CHECK), ERR_PARAM );
  if( boStatus ) dlg->Entry[iEntry].Field[iWhich].wFlags|=DLG_FLG_MARKED;
  else dlg->Entry[iEntry].Field[iWhich].wFlags&= ~DLG_FLG_MARKED;
  if( dlg->Win )
  {
   WinAktivieren( dlg->Win );
   DlgDisplay( dlg, iEntry, iWhich, FALSE );
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_ISMARKED
 BOOL CDECL     DlgIsMarked  ( dlg, iEntry, iWhich )
 SDlg*          dlg;                             /* Zu bearbeitender Dialog */
 INT            iEntry;                          /* Nummer der Gruppe       */
 INT            iWhich;
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( (iEntry<=dlg->iEntAct)&&(iWhich<=dlg->Entry[iEntry].iFldAct), ERR_COUNT );
  Assert( (dlg->Entry[iEntry].iTyp==DLG_CHECK), ERR_PARAM );
  if( dlg->Entry[iEntry].Field[iWhich].wFlags&DLG_FLG_MARKED ) return( TRUE );
  return( FALSE );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_GETMARKED
 LONG CDECL     DlgGetMarked ( dlg, iEntry )
 SDlg*          dlg;                             /* Zu bearbeitender Dialog */
 INT            iEntry;                          /* Nummer des Eintrags     */
 {
  INT           i;
  LONG          lSum         = 0L;
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( iEntry<=dlg->iEntAct, ERR_COUNT );
  Assert( (dlg->Entry[iEntry].iTyp==DLG_CHECK), ERR_PARAM );
  for( i=0; i<=dlg->Entry[iEntry].iFldAct; i++ )
  {
   if( dlg->Entry[iEntry].Field[i].wFlags&DLG_FLG_MARKED ) lSum |= (1L<<i);
  }
  return( lSum );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_SETSELECT
 VOID CDECL     DlgSetSelect ( dlg, iEntry, iField )
 SDlg*          dlg;
 INT            iEntry;
 INT            iField;
 {
  INT           i;
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( iEntry<=dlg->iEntAct, ERR_COUNT );
  Assert( iField<=dlg->Entry[iEntry].iFldAct, ERR_COUNT );
  Assert( (dlg->Entry[iEntry].iTyp==DLG_RADIO), ERR_PARAM );
  for( i=0; i<=dlg->Entry[iEntry].iFldAct; i++ )
   dlg->Entry[iEntry].Field[i].wFlags &= ~DLG_FLG_MARKED;
  dlg->Entry[iEntry].Field[iField].wFlags |= DLG_FLG_MARKED;
  if( dlg->Win )
  {
   WinAktivieren( dlg->Win );
   for( i=0; i<=dlg->Entry[iEntry].iFldAct; i++ )
    DlgDisplay( dlg, iEntry, i, FALSE );
  }
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_GETSELECT
 INT  CDECL     DlgGetSelect ( dlg, iEntry )
 SDlg*          dlg;
 INT            iEntry;
 {
  INT           i;
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( iEntry<=dlg->iEntAct, ERR_COUNT );
  Assert( (dlg->Entry[iEntry].iTyp==DLG_RADIO), ERR_PARAM );
  for( i=0; i<=dlg->Entry[iEntry].iFldAct; i++ )
   if( dlg->Entry[iEntry].Field[i].wFlags&DLG_FLG_MARKED ) return( i );
  return( 0 );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_GETTEXT
 CHAR* CDECL    DlgGetText   ( dlg, iEntry, iWhich )
 SDlg*          dlg;                             /* Zu bearbeitender Dialog */
 INT            iEntry;                          /* Nummer der Gruppe       */
 INT            iWhich;
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( (iEntry<=dlg->iEntAct)&&(iWhich<=dlg->Entry[iEntry].iFldAct), ERR_COUNT );
  Assert( (dlg->Entry[iEntry].iTyp==DLG_INPUT), ERR_PARAM );
  return( dlg->Entry[iEntry].Field[iWhich].pcText );
 }
 #undef         __FUNC__

 #define        __FUNC__     ERR_DLG_SETTEXT
 VOID  CDECL    DlgSetText   ( dlg, iEntry, iWhich, pcText )
 SDlg*          dlg;                             /* Zu bearbeitender Dialog */
 INT            iEntry;                          /* Nummer der Gruppe       */
 INT            iWhich;
 CHAR*          pcText;
 {
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( (iEntry<=dlg->iEntAct)&&(iWhich<=dlg->Entry[iEntry].iFldAct), ERR_COUNT );
  dlg->Entry[iEntry].Field[iWhich].pcText[0] = 0;
/*
  if( strlen(pcText) )
  {
   dlg->Entry[iEntry].Field[iWhich].pcText = strdup(pcText);
   Assert(dlg->Entry[iEntry].Field[iWhich].pcText,ERR_MEM_ALLOC);
   strcpy( dlg->Entry[iEntry].Field[iWhich].pcText, pcText );
  }
*/
  if( dlg->Entry[iEntry].iTyp!=DLG_INPUT )
  {
   if( dlg->Entry[iEntry].Field[iWhich].pcText!=0 )
    MemFree( dlg->Entry[iEntry].Field[iWhich].pcText, 0 );
   if( strlen(pcText) )
   {
    dlg->Entry[iEntry].Field[iWhich].pcText = strdup(pcText);
    Assert(dlg->Entry[iEntry].Field[iWhich].pcText,ERR_MEM_ALLOC);
   }
   dlg->Entry[iEntry].Field[iWhich].iLen = strlen( dlg->Entry[iEntry].Field[iWhich].pcText ) +2;
  }
  else
  {
   strncpy( dlg->Entry[iEntry].Field[iWhich].pcText, pcText, dlg->Entry[iEntry].Field[iWhich].iLen );
   dlg->Entry[iEntry].Field[iWhich].pcText[dlg->Entry[iEntry].Field[iWhich].iLen] = 0;
//   dlg->Entry[iEntry].Field[iWhich].t.Input->iPos =
   DlgComputePos(&dlg->Entry[iEntry]);
  }
  if( dlg->Win )
  {
   WinAktivieren( dlg->Win );
   DlgDisplay( dlg, iEntry, iWhich, FALSE );
  }
 }
 #undef         __FUNC__

 /***************************************************************************/
 /* DlgAddField                                                             */
 /* ----------------------------------------------------------------------- */
 /* Fuegt ein Feld in einen Dialogeintrag ein.                              */
 /***************************************************************************/
 #define        __FUNC__     ERR_DLG_ADDFIELD
 VOID CDECL     DlgAddField  ( dlg, wX, wY, pcText, iAllowed, iLen )
 SDlg*          dlg;                             /* Zu bearbeitender Dialog */
 WORD           wX;                              /* X-Position des Feldes   */
 WORD           wY;                              /* Y-Position des Feldes   */
 CHAR*          pcText;                          /* Feld-Text               */
 INT            iAllowed;                        /* Erlaubte Typen bei Eingabefeld */
 INT            iLen;                            /* Laenge des Feldes       */
 {
  SDlgEntry*    entry        = &dlg->Entry[dlg->iEntAct];
  Assert( (dlg!=NULL)&&(dlg->Entry!=NULL), ERR_PTR );
  Assert( ++entry->iFldAct<entry->iFldCnt, ERR_COUNT );
  entry->Field[entry->iFldAct].wX      = wX + entry->wX;  /* X-Position des Feldes */
  entry->Field[entry->iFldAct].wY      = wY + entry->wY;  /* Y-Position des Feldes */
  entry->Field[entry->iFldAct].wFlags  = 0;               /* Alle Flags auf AUS    */
  entry->Field[entry->iFldAct].iHotkey = -1; //WinGetHotkey( pcText ); /* Hotkey des Feldes    */
  if( entry->iTyp!=DLG_INPUT )
  {
   if( strchr( pcText, '~' ) != NULL )
    entry->Field[entry->iFldAct].iHotkey = WinGetHotkey( pcText ); /* Hotkey des Feldes    */
  }
  else
   if( entry->pcText!=NULL )
    entry->Field[entry->iFldAct].iHotkey = WinGetHotkey( entry->pcText ); /* Hotkey des Feldes    */
  entry->Field[entry->iFldAct].OnInit  = NULL; /* Handle-Funktion bei Endetasten */
  entry->Field[entry->iFldAct].OnExit  = NULL;
  if( iLen==0 ) iLen = strlen( pcText );
  if( entry->iTyp==DLG_FRAME )
   entry->Field[entry->iFldAct].pcText  = MemAlloc( sizeof(CHAR)*(strlen(pcText)+2) );
  else
   entry->Field[entry->iFldAct].pcText  = MemAlloc( sizeof(CHAR)*(iLen+2) );
  Assert( entry->Field[entry->iFldAct].pcText!=NULL, ERR_MEM_ALLOC );
  switch( entry->iTyp )
  {
   case DLG_STATIC:
        strcpy( entry->Field[entry->iFldAct].pcText, pcText );
        entry->Field[entry->iFldAct].iLen = strlen( pcText );
        break;
   case DLG_RADIO:
        strcpy( entry->Field[entry->iFldAct].pcText, pcText );
        if( iAllowed>0 ) DlgSelect( entry, entry->iFldAct );
        entry->Field[entry->iFldAct].iLen = strlen( pcText ) /* + 2 */;
        break;
   case DLG_CHECK:
        strcpy( entry->Field[entry->iFldAct].pcText, pcText );
        if( iAllowed>0 ) entry->Field[entry->iFldAct].wFlags |= DLG_FLG_MARKED;
        entry->Field[entry->iFldAct].iLen = strlen( pcText ) /* + 2 */;
        break;
   case DLG_FRAME:
        strcpy( entry->Field[entry->iFldAct].pcText, pcText );
        entry->Field[entry->iFldAct].iLen    = iAllowed;
        entry->Field[entry->iFldAct].t.iHeight = iLen;
        break;
   case DLG_PUSH:
        strcpy( entry->Field[entry->iFldAct].pcText, pcText );
        entry->Field[entry->iFldAct].iLen = strlen( pcText ) + 2;
        break;
   case DLG_INPUT:
        if( (iAllowed&127)<100 )
        {
         iLen = (iAllowed&127)/10;
         if( ((iAllowed&127)%10)!=0 )
         {
          iLen += (iAllowed&127)%10 + 1;
         }
        }
        if( iAllowed&DLG_FIELD_SIGN ) iLen++;
        entry->Field[entry->iFldAct].iLen = iLen;
        entry->Field[entry->iFldAct].t.Input = MemAlloc( sizeof( SDlgInput ) );
        Assert( entry->Field[entry->iFldAct].t.Input!=NULL, ERR_MEM_ALLOC );
        entry->Field[entry->iFldAct].wFlags |= DLG_FLG_MARKED;
        entry->Field[entry->iFldAct].t.Input->iAllowed = iAllowed;
        if( pcText )
        {
         strncpy( entry->Field[entry->iFldAct].pcText, pcText, iLen );
         entry->Field[entry->iFldAct].pcText[iLen+1] = 0;
        }
        DlgComputePos(entry);
//        entry->Field[entry->iFldAct].t.Input->iBlkStart = 0;
//        entry->Field[entry->iFldAct].t.Input->iBlkStop  = iLen;
        break;
   }
 }
 #undef         __FUNC__

 PRIVATE VOID CDECL     DlgComputePos( entry)
 SDlgEntry*     entry;
 {
        INT iAllowed = entry->Field[entry->iFldAct].t.Input->iAllowed;
        CHAR* cp;
        cp = NULL;
        if( (iAllowed&127)<100 )
        {
         cp = strchr( entry->Field[entry->iFldAct].pcText, '.' );
         if( cp==NULL ) cp = strchr( entry->Field[entry->iFldAct].pcText, ',' );
         if( cp!=NULL )
          entry->Field[entry->iFldAct].t.Input->iPos = (WORD)( (LONG)cp - (LONG) entry->Field[entry->iFldAct].pcText ) - 1;
        }
        if( cp==NULL )
        {
         if( (iAllowed&127)==DLG_FIELD_ALL )
         {
          entry->Field[entry->iFldAct].t.Input->iPos = 0;
         }
         else
         {
          cp = strrchr( entry->Field[entry->iFldAct].pcText, ' ' );
          if( cp!=NULL )
           entry->Field[entry->iFldAct].t.Input->iPos = (WORD)( (LONG)cp - (LONG) entry->Field[entry->iFldAct].pcText ) + 1;
          else
          {
           if( (((iAllowed&127)==DLG_FIELD_NUM) || ((iAllowed&127)==DLG_FIELD_HEX)) && (iAllowed&DLG_FIELD_SIGN) )
            entry->Field[entry->iFldAct].t.Input->iPos = 1;
           else
            entry->Field[entry->iFldAct].t.Input->iPos = 0;
          }
         }
        }
 }

 #define        __FUNC__     ERR_DLG_HANDLE
 INT  CDECL     DlgHandle    ( dlg, wX, wY, wWidth, wHeight, pcTitel, piExits )
 SDlg*          dlg;                             /* Auszufuehrender Dialog  */
 WORD           wX;                              /* X-Position des Fensters */
 WORD           wY;                              /* Y-Position des Fensters */
 WORD           wWidth;                          /* Breite des Fensters     */
 WORD           wHeight;                         /* Hoehe des Fensters      */
 CHAR*          pcTitel;                         /* Titel des Fensters      */
 INT*           piExits;                         /* Abbruchtasten           */
 {
  BOOL          boFertig     = FALSE;            /* Flag, ob abgearbeitet   */
  INT           iRet;                            /* Rueckgabewert der Funktion */
  INT           iEntry;                          /* Laufvariable            */
  INT           iField;
  INT           i;
  Assert( dlg!=NULL, ERR_PTR );
  if( dlg->Win==NULL )
  {
   dlg->Win = WinEinrichten( wX, wY, wWidth, wHeight );/* Fenster einrichten      */
   WinSchattenEin( dlg->Win );                         /* Dialoge haben Schatten  */
   WinSetRahmentyp( dlg->Win, 1 );                     /* Und Rahmentyp einfach   */
   WinSetTitel( dlg->Win, pcTitel, WIN_TITEL_OZ );      /* Titel setzen            */
   WinSetAttrib( dlg->Win, DlgGetPal(DLG_PAL_TEXT), DlgGetPal(DLG_PAL_TITLE), DlgGetPal(DLG_PAL_FRAME) );
  }
  WinCursor( FALSE );                            /* Attribute setzen, Cursor aus */
  WinAktivieren( dlg->Win );                     /* Fenster aktivieren      */
  WinCls();                                      /* und Inhalt loeschen     */
  MouSetRange( wX+1, wY+1, wX+wWidth-2, wY+wHeight-2 );
  for( iEntry=0; iEntry<=dlg->iEntAct; iEntry++ ) /* Alle Eintraege des Dialogs durchgehen */
  {
   if( strlen( dlg->Entry[iEntry].pcText ) > 0 ) /* Falls Eintrag Ueberschrift hat, darstellen */
    WinHot( dlg->Entry[iEntry].wX, dlg->Entry[iEntry].wY, dlg->Entry[iEntry].pcText, DlgGetPal(DLG_PAL_TEXT), DlgGetPal(DLG_PAL_HOTNORM) );
   for( iField=0; iField<=dlg->Entry[iEntry].iFldAct; iField++ )  /* Alle Feldtexte darstellen */
    DlgDisplay( dlg, iEntry, iField, FALSE );
  }
  iEntry = dlg->iEntCur;                         /* Aktuellen Eintrag merken */
  iField = dlg->Entry[iEntry].iFldCur;           /* Aktuelles Feld merken   */
  DlgGetPrev( dlg, &iEntry, &iField, DLG_NONE );
  DlgGetNext( dlg, &iEntry, &iField, DLG_NONE );
  while( !boFertig )                             /* Solange nicht ESC gedrueckt */
  {                                              /* Statuszeile darstellen  */
   dlg->iEntCur = iEntry;
   dlg->Entry[iEntry].iFldCur = iField;
   VioStatus( dlg->Entry[iEntry].pcStatus, DlgGetPal(DLG_PAL_STATNORM), DlgGetPal(DLG_PAL_STATINV) );
   if( dlg->Entry[iEntry].Field[iField].OnInit )
   {
    dlg->Entry[iEntry].Field[iField].OnInit( dlg );
    WinAktivieren( dlg->Win );
   }
   DlgDisplay( dlg, iEntry, iField, TRUE );      /* Aktuellen EIntrag markieren */
   iRet = EvGetKey();
   DlgDisplay( dlg, iEntry, iField, FALSE );
   if( dlg->Entry[iEntry].Field[iField].OnExit )
   {
    dlg->Entry[iEntry].Field[iField].OnExit( dlg );
    WinAktivieren( dlg->Win );
   }
   if( EvKeybGetst()&ALT )
   {
    if( DlgHandleHot( dlg, &iEntry, &iField, iRet ) )
     continue;
//    continue;
   }
   if( piExits!=NULL )
   {
    for( i=0; piExits[i]!=0; i++ ) if( piExits[i]==iRet )
    {
     boFertig=TRUE;
     break;
    }
   }
 ONCEMORE:
   if( !boFertig ) switch( iRet )
   {
    case T_ESC:
         boFertig = TRUE;
         break;
    case MOU_RIGHTPRESS:
    case T_F1:
         if( dlg->Entry[iEntry].Help )
         {
          dlg->Entry[iEntry].Help( dlg );
          WinAktivieren( dlg->Win );
         }
         break;
    case T_SPACE:
         if( dlg->Entry[iEntry].iTyp==DLG_PUSH )
         {
          boFertig = TRUE;
          iRet     = dlg->Entry[iEntry].Field[iField].iHotkey;
          break;
         }
         DlgHandleKey( dlg, iEntry, iField, T_SPACE );
         break;
    case T_SHIFT_TAB:
         dlg->Entry[iEntry].iFldCur = iField;
         DlgGetPrev( dlg, &iEntry, &iField, DLG_ENTRY );
         break;
    case MOU_LEFTPRESS:
         {
          WORD  wMouX;
          WORD  wMouY;
          WORD  wMouS;
          EvMouGetVal( &wMouS, &wMouX, &wMouY );
          if( !DlgGetMouEnt( dlg, wMouX-wX, wMouY-wY, &iEntry, &iField ) ) break;
          if( ( dlg->Entry[iEntry].iTyp==DLG_RADIO ) || ( dlg->Entry[iField].iTyp==DLG_CHECK ) || ( dlg->Entry[iField].iTyp==DLG_PUSH ) )
          {
           iRet = T_SPACE;
           goto ONCEMORE;
          }
          break;
         }
    case MOU_MOVED:
         break;
    case T_TAB:
         dlg->Entry[iEntry].iFldCur = iField;
         DlgGetNext( dlg, &iEntry, &iField, DLG_ENTRY );
         break;
    case T_UP:
         DlgGetPrev( dlg, &iEntry, &iField, DLG_FIELD );
         break;
    case T_DOWN:
         DlgGetNext( dlg, &iEntry, &iField, DLG_FIELD );
         break;
    case T_RETURN:
         if( dlg->Entry[iEntry].iTyp==DLG_PUSH )
         {
          iRet     = dlg->Entry[iEntry].Field[iField].iHotkey;
          boFertig = TRUE;
          break;
         }
         if( DlgGetNext( dlg, &iEntry, &iField, DLG_FIELD ) ) boFertig=TRUE;
         break;
    case T_CRETURN:
         boFertig = TRUE;
         iRet = T_RETURN;
         break;
    default:
         if( !DlgHandleKey( dlg, iEntry, iField, iRet ) )
         {
          if( DlgHandleHot( dlg, &iEntry, &iField, iRet ) )
           switch( dlg->Entry[iEntry].iTyp )
           {
            case DLG_PUSH:
                 boFertig = TRUE;
                 iRet = T_SPACE;
                 break;
            case DLG_RADIO:
            case DLG_CHECK:
                 DlgHandleKey( dlg, iEntry, iField, T_SPACE );
                 break;
           }
         }
   }
  }
  dlg->iEntCur = iEntry;
  return( iRet );
 }
 #undef         __FUNC__

 /***************************************************************************/
 /* DlgDisplay                                                              */
 /* ----------------------------------------------------------------------- */
 /* Darstellen eines Feldes in Abhaengigkeit des Typs und ob aktuell.       */
 /***************************************************************************/
 PRIVATE VOID CDECL DlgDisplay   ( dlg, iEntry, iField, boHigh )
 SDlg*          dlg;                             /* Betroffener Dialog      */
 INT            iEntry;                          /* Nummer des Eintrags     */
 INT            iField;                          /* Nummer des Feldes       */
 BOOL           boHigh ;                         /* Highlighten?            */
 {
  INT           i;
  WORD          wNormal;
  WORD          wInvers;
  WinCursor( FALSE );
  switch( dlg->Entry[iEntry].iTyp )
  {
   case DLG_INPUT:
        if( dlg->Entry[iEntry].Field[iField].wFlags & DLG_FLG_DISABLE )
        {
         wNormal = DlgGetPal( DLG_PAL_DISABLE );
         wInvers = DlgGetPal( DLG_PAL_DISABLE );
        }
        else
        {
         wNormal = DlgGetPal( DLG_PAL_TEXT );
         wInvers = DlgGetPal( DLG_PAL_EDIT );
        }
        break;
   case DLG_PUSH:
        if( dlg->Entry[iEntry].Field[iField].wFlags & DLG_FLG_DISABLE )
        {
         wNormal = DlgGetPal( DLG_PAL_PUSHDIS );
         wInvers = DlgGetPal( DLG_PAL_PUSHDIS );
        }
        else
        {
         if( boHigh )
         {
          wNormal = DlgGetPal( DLG_PAL_PUSHINVERS );
          wInvers = DlgGetPal( DLG_PAL_PUSHHOTINV );
         }
         else
         {
          wNormal = DlgGetPal( DLG_PAL_PUSHNORMAL );
          wInvers = DlgGetPal( DLG_PAL_PUSHHOTNORM );
         }
        }
        break;
   case DLG_RADIO:
   case DLG_CHECK:
        if( dlg->Entry[iEntry].Field[iField].wFlags & DLG_FLG_DISABLE )
        {
         wNormal = DlgGetPal( DLG_PAL_DISABLE );
         wInvers = DlgGetPal( DLG_PAL_DISABLE );
        }
        else
        {
         if( boHigh )
         {
          wNormal = DlgGetPal( DLG_PAL_INVERS );
          wInvers = DlgGetPal( DLG_PAL_HOTINV );
         }
         else
         {
          wNormal = DlgGetPal( DLG_PAL_TEXT );
          wInvers = DlgGetPal( DLG_PAL_HOTNORM );
         }
        }
        break;
   case DLG_FRAME:
        wNormal = DlgGetPal( DLG_PAL_TEXT );
        break;
   case DLG_STATIC:
        wNormal = DlgGetPal( DLG_PAL_TEXT );
        wInvers = DlgGetPal( DLG_PAL_HOTNORM );
        break;
  }
  switch( dlg->Entry[iEntry].iTyp )
  {
   case DLG_STATIC:
   case DLG_PUSH:
        WinHot( dlg->Entry[iEntry].Field[iField].wX
              , dlg->Entry[iEntry].Field[iField].wY
              , dlg->Entry[iEntry].Field[iField].pcText
              , wNormal
              , wInvers
              );
        break;
   case DLG_CHECK:
        WinSsa( dlg->Entry[iEntry].Field[iField].wX
              , dlg->Entry[iEntry].Field[iField].wY
              , ( dlg->Entry[iEntry].Field[iField].wFlags&DLG_FLG_MARKED ) ? "[X]" : "[ ]"
              , ( dlg->Entry[iEntry].Field[iField].wFlags&DLG_FLG_DISABLE ) ? wNormal : DlgGetPal( DLG_PAL_EDIT )
              );
        WinHot( dlg->Entry[iEntry].Field[iField].wX+4
              , dlg->Entry[iEntry].Field[iField].wY
              , dlg->Entry[iEntry].Field[iField].pcText
              , wNormal
              , wInvers
              );
        break;
   case DLG_RADIO:
        WinSsa( dlg->Entry[iEntry].Field[iField].wX
              , dlg->Entry[iEntry].Field[iField].wY
              , ( dlg->Entry[iEntry].Field[iField].wFlags&DLG_FLG_MARKED ) ? "(˛)" : "( )"
              , ( dlg->Entry[iEntry].Field[iField].wFlags&DLG_FLG_DISABLE ) ? wNormal: DlgGetPal( DLG_PAL_EDIT )
              );
        WinHot( dlg->Entry[iEntry].Field[iField].wX+4
              , dlg->Entry[iEntry].Field[iField].wY
              , dlg->Entry[iEntry].Field[iField].pcText
              , wNormal
              , wInvers
              );
        break;
   case DLG_FRAME:
        if( dlg->Entry[iEntry].Field[iField].iLen==0 )
        {
         if( dlg->Entry[iEntry].Field[iField].t.iHeight==0 ) break;
         for( i=0; i<=dlg->Entry[iEntry].Field[iField].t.iHeight; i++ )
          WinSza( dlg->Entry[iEntry].Field[iField].wX
                , dlg->Entry[iEntry].Field[iField].wY+i
                , '≥'
                , wNormal
                );
         break;
        }
        if( dlg->Entry[iEntry].Field[iField].t.iHeight==0 )
        {
         for( i=0; i<=dlg->Entry[iEntry].Field[iField].iLen; i++ )
          WinSza( dlg->Entry[iEntry].Field[iField].wX+i
                , dlg->Entry[iEntry].Field[iField].wY
                , 'ƒ'
                , wNormal
                );
         break;
        }
        WinSza( dlg->Entry[iEntry].Field[iField].wX
              , dlg->Entry[iEntry].Field[iField].wY
              , '⁄'
              , wNormal
              );
        WinSza( dlg->Entry[iEntry].Field[iField].wX+dlg->Entry[iEntry].Field[iField].iLen
              , dlg->Entry[iEntry].Field[iField].wY
              , 'ø'
              , wNormal
              );
        WinSza( dlg->Entry[iEntry].Field[iField].wX
              , dlg->Entry[iEntry].Field[iField].wY+dlg->Entry[iEntry].Field[iField].t.iHeight
              , '¿'
              , wNormal
              );
        WinSza( dlg->Entry[iEntry].Field[iField].wX+dlg->Entry[iEntry].Field[iField].iLen
              , dlg->Entry[iEntry].Field[iField].wY+dlg->Entry[iEntry].Field[iField].t.iHeight
              , 'Ÿ'
              , wNormal
              );
        for( i=1; i<=dlg->Entry[iEntry].Field[iField].iLen-1; i++ )
        {
         WinSza( dlg->Entry[iEntry].Field[iField].wX+i
               , dlg->Entry[iEntry].Field[iField].wY
               , 'ƒ'
               , wNormal
               );
         WinSza( dlg->Entry[iEntry].Field[iField].wX+i
               , dlg->Entry[iEntry].Field[iField].wY+dlg->Entry[iEntry].Field[iField].t.iHeight
               , 'ƒ'
               , wNormal
               );
        }
        for( i=1; i<=dlg->Entry[iEntry].Field[iField].t.iHeight-1; i++ )
        {
         WinSza( dlg->Entry[iEntry].Field[iField].wX
               , dlg->Entry[iEntry].Field[iField].wY+i
               , '≥'
               , wNormal
               );
         WinSza( dlg->Entry[iEntry].Field[iField].wX+dlg->Entry[iEntry].Field[iField].iLen
               , dlg->Entry[iEntry].Field[iField].wY+i
               , '≥'
               , wNormal
               );
        }
        WinSsa( dlg->Entry[iEntry].Field[iField].wX+1
              , dlg->Entry[iEntry].Field[iField].wY
              ,  dlg->Entry[iEntry].Field[iField].pcText
              , wNormal
              );
        break;
   case DLG_INPUT:
        {
         INT    iStart       = dlg->Entry[iEntry].Field[iField].t.Input->iBlkStart;
         INT    iStop        = dlg->Entry[iEntry].Field[iField].t.Input->iBlkStop;
         WinSwza( dlg->Entry[iEntry].Field[iField].wX
                , dlg->Entry[iEntry].Field[iField].wY
                , iStart
                , 1
                , ' '
                , wInvers
                );
         WinSwza( dlg->Entry[iEntry].Field[iField].wX+iStart
                , dlg->Entry[iEntry].Field[iField].wY
                , iStop-iStart
                , 1
                , ' '
                , DlgGetPal( DLG_PAL_EDITMARK )
                );
         WinSwza( dlg->Entry[iEntry].Field[iField].wX+iStop
                , dlg->Entry[iEntry].Field[iField].wY
                , dlg->Entry[iEntry].Field[iField].iLen-iStop
                , 1
                , ' '
                , wInvers
                );
         if( dlg->Entry[iEntry].Field[iField].t.Input->iAllowed & DLG_FIELD_PASSW )
          WinSwz( dlg->Entry[iEntry].Field[iField].wX
                , dlg->Entry[iEntry].Field[iField].wY
                , strlen( dlg->Entry[iEntry].Field[iField].pcText )
                , 1
                , '*'
                );
         else
          WinSs ( dlg->Entry[iEntry].Field[iField].wX
                , dlg->Entry[iEntry].Field[iField].wY
                , dlg->Entry[iEntry].Field[iField].pcText
                );
         WinSza( dlg->Entry[iEntry].Field[iField].wX-1
               , dlg->Entry[iEntry].Field[iField].wY
               , ( boHigh ) ? '>' : ' '
               , wNormal
               );
         WinSza( dlg->Entry[iEntry].Field[iField].wX+dlg->Entry[iEntry].Field[iField].iLen
               , dlg->Entry[iEntry].Field[iField].wY
               , ( boHigh ) ? '<' : ' '
               , wNormal
               );
         if( boHigh )
         {
          WinSetCursorPos( dlg->Entry[iEntry].Field[iField].t.Input->iPos
                         + dlg->Entry[iEntry].Field[iField].wX
                         , dlg->Entry[iEntry].Field[iField].wY
                         );
          if( dlg->wFlags&DLG_FLG_BLOCK )
           WinCursor( WIN_CUR_BLOCK );
          else
           WinCursor( WIN_CUR_LINE );
         }
        }
        break;
   }
 }

 PRIVATE BOOL CDECL DlgHandleHot ( dlg, piEntry, piField, iKey )
 SDlg*          dlg;
 INT*           piEntry;
 INT*           piField;
 INT            iKey;
 {
  INT           iEntry;
  INT           iField;
  iKey = toupper( iKey );
  for( iEntry=0; iEntry<=dlg->iEntAct; iEntry++ )
  {
   for( iField=0; iField<=dlg->Entry[iEntry].iFldAct; iField++ )
   {
    if( (dlg->Entry[iEntry].iTyp==DLG_STATIC) || (dlg->Entry[iEntry].iTyp==DLG_FRAME) )
     continue;
    if( (dlg->Entry[iEntry].Field[iField].iHotkey==iKey) && !(dlg->Entry[iEntry].Field[iField].wFlags&DLG_FLG_DISABLE) )
    {
     *piEntry = iEntry;
     *piField = iField;
     return( TRUE );
    }
   }
  }
  return( FALSE );
 }

 PRIVATE BOOL CDECL DlgHandleKey ( dlg, iEntry, iField, iKey )
 SDlg*          dlg;
 INT            iEntry;
 INT            iField;
 INT            iKey;
 {
  CHAR*         cp;
  SDlgInput*    inp;
  INT           i;
  INT           iPos;
  INT           iCur;
  BOOL          boShift;
  if( dlg->Entry[iEntry].Field[iField].wFlags&DLG_FLG_DISABLE ) return( FALSE );
  switch( dlg->Entry[iEntry].iTyp&127 )
  {
   case DLG_CHECK:
        if( iKey!=T_SPACE ) return( FALSE );
        dlg->Entry[iEntry].Field[iField].wFlags ^= DLG_FLG_MARKED;
        break;
   case DLG_RADIO:
        if( iKey!=T_SPACE ) return( FALSE );
        DlgSelect( &dlg->Entry[iEntry], /*dlg->Entry[iEntry].iFldCur*/iField );
        for( i=0; i<=dlg->Entry[iEntry].iFldAct; i++ )
         DlgDisplay( dlg, iEntry, i, FALSE );
        break;
   case DLG_INPUT:
        inp     = dlg->Entry[iEntry].Field[iField].t.Input;
        iCur    = inp->iPos;
//        boShift = dlg->Entry[iEntry].Field[iField].wFlags&DLG_FLG_SHIFT;
        switch( iKey )
        {
         /* --- Ueberschreibmodus ein/aus --------------------------------- */
         case T_INS:
              dlg->wFlags ^= DLG_FLG_BLOCK;
              break;
         /* --- An den Anfang des Feldes springen ------------------------- */
         case T_HOME:
              if( (inp->iAllowed&127)==DLG_FIELD_ALL )
              {
               iCur=0;
               break;
              }
              cp = strrchr( dlg->Entry[iEntry].Field[iField].pcText, ' ' );
              if( cp==NULL )
               iCur = (inp->iAllowed&DLG_FIELD_SIGN) ? 1 : 0;
              else
               iCur = (INT)( (LONG) cp - (LONG) dlg->Entry[iEntry].Field[iField].pcText ) + 1;
              break;
         /* --- An das Ende des Feldes springen --------------------------- */
         case T_END:
              iCur = strlen( dlg->Entry[iEntry].Field[iField].pcText );
              if( iCur>=dlg->Entry[iEntry].Field[iField].iLen ) iCur--;
              break;
         /* --- Ein Zeichen nach links springen --------------------------- */
         case T_LEFT:
              if( iCur==0 ) break;
              if( (iCur==1) && (inp->iAllowed&DLG_FIELD_SIGN) ) break;
              switch( inp->iAllowed&127 )
              {
               case DLG_FIELD_DATE:
                    if( dlg->Entry[iEntry].Field[iField].pcText[--iCur]=='.' ) iCur--;
                    if( dlg->Entry[iEntry].Field[iField].pcText[iCur]==',' ) iCur--;
                    break;
               case DLG_FIELD_TIME:
                    if( dlg->Entry[iEntry].Field[iField].pcText[--iCur]==':' ) iCur--;
                    break;
               case DLG_FIELD_ALL:
                    iCur--;
                    break;
               default:
                    if( dlg->Entry[iEntry].Field[iField].pcText[iCur-1]==' ' ) break;
                    iCur--;
                    if( ((inp->iAllowed&127)<100) && (dlg->Entry[iEntry].Field[iField].pcText[iCur]=='.') )
                     iCur--;
                    break;
              }
              break;
         /* --- Ein Wort nach links springen ------------------------------ */
         case T_C_LEFT:
              if( ((inp->iAllowed&127)!=DLG_FIELD_ALL) || (inp->iPos==0) )
               return( DlgHandleKey( dlg, iEntry, iField, T_HOME ) );
              i = inp->iPos-1;
              if( dlg->Entry[iEntry].Field[iField].pcText[inp->iPos-1]==' ' )
              {
               while( dlg->Entry[iEntry].Field[iField].pcText[i]==' ' ) if( --i<0 ) break;
              }
              if( i<0 ) break;
              for( ; i>=0; i-- ) if( dlg->Entry[iEntry].Field[iField].pcText[i]==' ' ) break;
              iCur = i+1;
              break;
         /* --- Ein Zeichen nach rechts springen -------------------------- */
         case T_RIGHT:
              if( iCur>=strlen( dlg->Entry[iEntry].Field[iField].pcText ) ) break;
              if( ((inp->iAllowed&127)<100) && (iCur>=strlen( dlg->Entry[iEntry].Field[iField].pcText)-1) ) break;
              switch( inp->iAllowed&127 )
              {
               case DLG_FIELD_DATE:
                    if( iCur>=strlen( dlg->Entry[iEntry].Field[iField].pcText )-1 ) break;
                    if( dlg->Entry[iEntry].Field[iField].pcText[++iCur]=='.' ) iCur++;
                    if( dlg->Entry[iEntry].Field[iField].pcText[iCur]==',' ) iCur++;
                    break;
               case DLG_FIELD_TIME:
                    if( iCur>=strlen( dlg->Entry[iEntry].Field[iField].pcText )-1 ) break;
                    if( dlg->Entry[iEntry].Field[iField].pcText[++iCur]==':' ) iCur++;
                    break;
               default:
                    if( iCur+1>dlg->Entry[iEntry].Field[iField].iLen-1 ) break;
                    iCur++;
                    if( ((inp->iAllowed&127)<100)
                     && ((dlg->Entry[iEntry].Field[iField].pcText[iCur]=='.')
                      || (dlg->Entry[iEntry].Field[iField].pcText[iCur]==',')
                        )
                      ) iCur++;
              }
              break;
         /* --- Ein Wort nach rechts springen ----------------------------- */
         case T_C_RIGHT:
              if( ((inp->iAllowed&127)!=DLG_FIELD_ALL) || (inp->iPos==strlen( dlg->Entry[iEntry].Field[iField].pcText )-1) )
               return( DlgHandleKey( dlg, iEntry, iField, T_END ) );
              i = inp->iPos;
              if( dlg->Entry[iEntry].Field[iField].pcText[i]!=' ' ) i++;
              while( dlg->Entry[iEntry].Field[iField].pcText[i]!=' ' ) if( ++i>strlen( dlg->Entry[iEntry].Field[iField].pcText ) ) break;
              if( i>=strlen( dlg->Entry[iEntry].Field[iField].pcText ) ) break;
              while( dlg->Entry[iEntry].Field[iField].pcText[i]==' ' ) if( ++i>strlen( dlg->Entry[iEntry].Field[iField].pcText ) ) break;
              if( i>=strlen( dlg->Entry[iEntry].Field[iField].pcText ) ) break;
              iCur = i;
              break;
         /* --- Ein Zeichen danach loeschen ------------------------------- */
         case T_DEL:
              switch( inp->iAllowed&127 )
              {
               case DLG_FIELD_TIME:
               case DLG_FIELD_DATE:
                    dlg->Entry[iEntry].Field[iField].pcText[iCur] = '0';
                    return( DlgHandleKey( dlg, iEntry, iField, T_RIGHT ) );
               default:
                    if( iCur>=strlen(dlg->Entry[iEntry].Field[iField].pcText) ) break;
                    if( ((inp->iAllowed&127)>=100) )
                    {
                     for( i=iCur; i<strlen(dlg->Entry[iEntry].Field[iField].pcText)-1; i++ )
                      dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i+1];
                     dlg->Entry[iEntry].Field[iField].pcText[i] = 0;
                     if( ((inp->iAllowed&127)==DLG_FIELD_NUM) || ((inp->iAllowed&127)==DLG_FIELD_HEX) )
                     {
                      if( inp->iAllowed&DLG_FIELD_SIGN )
                      {
                       if( dlg->Entry[iEntry].Field[iField].pcText[1]==0 )
                        dlg->Entry[iEntry].Field[iField].pcText[1]='0';
                      }
                      else
                      {
                       if( dlg->Entry[iEntry].Field[iField].pcText[0]==0 )
                        dlg->Entry[iEntry].Field[iField].pcText[0]='0';
                      }
                      if( dlg->Entry[iEntry].Field[iField].pcText[iCur]==0 )
                       return( DlgHandleKey( dlg, iEntry, iField, T_LEFT ) );
                     }
                     break;
                    }
                    iPos = (inp->iAllowed&127)/10;
                    if( iCur<=iPos )
                    {
                     if( inp->iAllowed&DLG_FIELD_SIGN )
                     {
                      for( i=iCur; i>1; i-- )
                       dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i-1];
                      dlg->Entry[iEntry].Field[iField].pcText[1] = ' ';
                      if( dlg->Entry[iEntry].Field[iField].pcText[iPos]==' ' )
                       dlg->Entry[iEntry].Field[iField].pcText[iPos]='0';
                     }
                     else
                     {
                      for( i=iCur; i>0; i-- )
                       dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i-1];
                      dlg->Entry[iEntry].Field[iField].pcText[0] = ' ';
                      if( (inp->iAllowed&127)%10 )
                      {
                       if( dlg->Entry[iEntry].Field[iField].pcText[iPos-1]==' ' )
                        dlg->Entry[iEntry].Field[iField].pcText[iPos-1]='0';
                      }
                      else
                      {
                       if( dlg->Entry[iEntry].Field[iField].pcText[iPos-1]==' ' )
                        dlg->Entry[iEntry].Field[iField].pcText[iPos-1]='0';
                      }
                     }
                     if( dlg->Entry[iEntry].Field[iField].pcText[iCur]==' ' )
                      return( DlgHandleKey( dlg, iEntry, iField, T_RIGHT ) );
                     break;
                    }
                    dlg->Entry[iEntry].Field[iField].pcText[iCur] = '0';
                    return( DlgHandleKey( dlg, iEntry, iField, T_RIGHT ) );
              }
              break;
         /* --- Ein Zeichen danach loeschen ------------------------------- */
         case T_BACKSPACE:
              switch( inp->iAllowed&127 )
              {
               case DLG_FIELD_DATE:
               case DLG_FIELD_TIME:
                    dlg->Entry[iEntry].Field[iField].pcText[iCur] = '0';
                    if( iCur>0 )
                     return( DlgHandleKey( dlg, iEntry, iField, T_LEFT ) );
                    break;
               default:
                    if( iCur==0 ) break;
                    if( (iCur==1) && (inp->iAllowed&DLG_FIELD_SIGN) ) break;
                    if( (inp->iAllowed&127)>=100 )
                    {
                     for( i=iCur-1; i<strlen( dlg->Entry[iEntry].Field[iField].pcText ); i++ )
                      dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i+1];
                     if( strlen( dlg->Entry[iEntry].Field[iField].pcText )>0 )
                      dlg->Entry[iEntry].Field[iField].pcText[i] = 0;
                     if( ((inp->iAllowed&127)==DLG_FIELD_NUM) || ((inp->iAllowed&127)==DLG_FIELD_HEX) )
                     {
                      if( inp->iAllowed&DLG_FIELD_SIGN )
                      {
                       if( dlg->Entry[iEntry].Field[iField].pcText[1]==0 )
                        dlg->Entry[iEntry].Field[iField].pcText[1]='0';
                      }
                      else
                      {
                       if( dlg->Entry[iEntry].Field[iField].pcText[0]==0 )
                        dlg->Entry[iEntry].Field[iField].pcText[0]='0';
                      }
                     }
                     if( iCur>0 ) return( DlgHandleKey( dlg, iEntry, iField, T_LEFT ) );
                     break;
                    }
                    iPos = (inp->iAllowed&127)/10;
                    if( (iCur<=iPos) && (dlg->Entry[iEntry].Field[iField].pcText[iPos-1]!=' ') )
                    {
                     if(inp->iAllowed&DLG_FIELD_SIGN)
                     {
                      for( i=iCur-1; i>1; i-- )
                       dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i-1];
                      dlg->Entry[iEntry].Field[iField].pcText[1] = ' ';
                      if( dlg->Entry[iEntry].Field[iField].pcText[iPos]==' ' )
                      {
                       iCur--;
                       dlg->Entry[iEntry].Field[iField].pcText[iPos] = '0';
                      }
                     }
                     else
                     {
                      if( ((inp->iAllowed&127)%10==0) && (dlg->Entry[iEntry].Field[iField].pcText[iPos-2]==' ') )
                       iCur++;
                      for( i=iCur-1; i>0; i-- )
                       dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i-1];
                      dlg->Entry[iEntry].Field[iField].pcText[0] = ' ';
                      if( ((inp->iAllowed&127)%10==0) && (dlg->Entry[iEntry].Field[iField].pcText[iPos-1]==' ') )
                      {
                       iCur--;
                       dlg->Entry[iEntry].Field[iField].pcText[iPos-1] = '0';
                      }
                     }
                     break;
                    }
                    dlg->Entry[iEntry].Field[iField].pcText[iCur] = '0';
                    return( DlgHandleKey( dlg, iEntry, iField, T_LEFT ) );
              }
              break;
         /* --- Zeicheneingabe -------------------------------------------- */
         default:
              switch( inp->iAllowed&127 )
              {
               /* Zeiteingabe --------------------------------------------- */
               case DLG_FIELD_TIME:
                    if( iKey==':' )
                    {
                     for( i=iCur+1; i<strlen( dlg->Entry[iEntry].Field[iField].pcText ); i++ )
                      if( dlg->Entry[iEntry].Field[iField].pcText[i]==':' ) break;
                     i++;
                     if( i<strlen( dlg->Entry[iEntry].Field[iField].pcText ) ) iCur=i;
                     break;
                    }
                    if( ( iKey>='0' ) && ( iKey<='9' ) )
                    {
                     switch( iCur )
                     {
                      case 0:
                           if( iKey>='3' ) return( FALSE );
                           if( ( iKey=='2' ) && ( dlg->Entry[iEntry].Field[iField].pcText[1] >= '4' ) ) return( FALSE );
                           break;
                      case 1:
                           if( ( iKey>='4' ) && ( dlg->Entry[iEntry].Field[iField].pcText[0] == '2' ) )
                            return( FALSE );
                           break;
                      case 3:
                      case 6:
                           if( iKey>='6' ) return( FALSE );
                     }
                     dlg->Entry[iEntry].Field[iField].pcText[iCur++] = iKey;
                     if( iCur>=dlg->Entry[iEntry].Field[iField].iLen ) iCur--;
                     if( dlg->Entry[iEntry].Field[iField].pcText[iCur] == ':' )
                      if( ++iCur>=dlg->Entry[iEntry].Field[iField].iLen ) iCur--;
                     break;
                    }
                    return( FALSE );
               case DLG_FIELD_DATE:
                    if( (iKey=='.') || (iKey==',') )
                    {
                     for( i=iCur+1; i<strlen( dlg->Entry[iEntry].Field[iField].pcText ); i++ )
                      if( dlg->Entry[iEntry].Field[iField].pcText[i]=='.' ) break;
                     i++;
                     if( i<strlen( dlg->Entry[iEntry].Field[iField].pcText ) ) iCur=i;
                     break;
                    }
                    if( ( iKey>='0' ) && ( iKey<='9' ) )
                    {
                     dlg->Entry[iEntry].Field[iField].pcText[iCur] = iKey;
                     return( DlgHandleKey( dlg, iEntry, iField, T_RIGHT ) );
                    }
                    break;
               case DLG_FIELD_HEX:
               case DLG_FIELD_NUM:
                    iKey = toupper( iKey );
                    if( ((iKey>='A') && (iKey<='F')) )
                    {
                     if( (inp->iAllowed&127)!=DLG_FIELD_HEX ) return( FALSE );
                    }
                    else
                    if( (iKey=='-') || (iKey=='+') )
                    {
                     if( !(inp->iAllowed&DLG_FIELD_SIGN) ) return( FALSE );
                    }
                    else
                    if( ((iKey<'0') || (iKey>'9')) /*&& ((inp->iAllowed&127)==DLG_FIELD_NUM)*/ ) return( FALSE );
                    if( (iKey!='-') && (iKey!='+') )
                    {
                     if( !(dlg->wFlags&DLG_FLG_BLOCK) )
                     {
                      if( dlg->Entry[iEntry].Field[iField].pcText[dlg->Entry[iEntry].Field[iField].iLen-1]!=0 ) return( TRUE );
                     }
                     if( inp->iAllowed&DLG_FIELD_SIGN )
                     {
                      if( !(dlg->wFlags&DLG_FLG_BLOCK) && ( (iCur!=1) || (dlg->Entry[iEntry].Field[iField].pcText[1]!='0') || (dlg->Entry[iEntry].Field[iField].pcText[2]!=0)) )
                      {
                       for( i=dlg->Entry[iEntry].Field[iField].iLen-1; i>=iCur; i-- )
                        dlg->Entry[iEntry].Field[iField].pcText[i+1] = dlg->Entry[iEntry].Field[iField].pcText[i];
                       dlg->Entry[iEntry].Field[iField].pcText[dlg->Entry[iEntry].Field[iField].iLen] = 0;
                      }
                     }
                     else
                     {
                      if( !(dlg->wFlags&DLG_FLG_BLOCK) && ( (iCur!=0) || (dlg->Entry[iEntry].Field[iField].pcText[0]!='0') || (dlg->Entry[iEntry].Field[iField].pcText[1]!=0)) )
                      {
                       for( i=dlg->Entry[iEntry].Field[iField].iLen-1; i>=iCur; i-- )
                        dlg->Entry[iEntry].Field[iField].pcText[i+1] = dlg->Entry[iEntry].Field[iField].pcText[i];
                       dlg->Entry[iEntry].Field[iField].pcText[dlg->Entry[iEntry].Field[iField].iLen] = 0;
                      }
                     }
                     dlg->Entry[iEntry].Field[iField].pcText[iCur] = iKey;
                     return( DlgHandleKey( dlg, iEntry, iField, T_RIGHT ) );
                    }
                    if( ((iKey=='-')||(iKey=='+'))&&(inp->iAllowed&DLG_FIELD_SIGN) )
                    {
                     if( ( dlg->Entry[iEntry].Field[iField].pcText[0]!=' ' )
                      && ( dlg->Entry[iEntry].Field[iField].pcText[0]!='-' )
                       )
                      for( i=strlen(dlg->Entry[iEntry].Field[iField].pcText); i>0; i-- )
                       dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i-1];
                     dlg->Entry[iEntry].Field[iField].pcText[0] = (iKey=='-') ? '-' : ' ';
                     break;
                    }
                    break;
               case DLG_FIELD_ALL:
                    if( ( iKey>255 ) || ( iKey<32 ) ) return( FALSE );
                    if( !(dlg->wFlags&DLG_FLG_BLOCK) )
                    {
                     if( dlg->Entry[iEntry].Field[iField].pcText[dlg->Entry[iEntry].Field[iField].iLen-1]!=0 ) return( TRUE );
                     for( i=dlg->Entry[iEntry].Field[iField].iLen-1; i>=iCur; i-- )
                      dlg->Entry[iEntry].Field[iField].pcText[i+1] = dlg->Entry[iEntry].Field[iField].pcText[i];
                     dlg->Entry[iEntry].Field[iField].pcText[dlg->Entry[iEntry].Field[iField].iLen] = 0;
                    }
                    dlg->Entry[iEntry].Field[iField].pcText[iCur] = iKey;
                    return( DlgHandleKey( dlg, iEntry, iField, T_RIGHT ) );
               /* Behandeln aller anderen Tasten fuer Felder mit Typ<100    */
               default:
                    /* Punkt / Komma                                        */
                    if( (iKey=='.') || (iKey==',') )
                    {
                     /* Das Feld hinter dem Punkt suchen                    */
                     for( i=iCur+1; i<strlen( dlg->Entry[iEntry].Field[iField].pcText ); i++ )
                      if( dlg->Entry[iEntry].Field[iField].pcText[i]=='.' ) break;
                     i++;
                     /* Wenn kein Punkt da, dann wieder zurueck             */
                     if( i<strlen( dlg->Entry[iEntry].Field[iField].pcText ) ) iCur=i;
                     break;
                    }
                    /* Minus / Plus bei signed-Feldern                      */
                    if( ( (iKey=='-')||(iKey=='+') ) && (inp->iAllowed&DLG_FIELD_SIGN ) )
                    {
                     /* Vorzeichen einfach togglen                           */
                     if( ( dlg->Entry[iEntry].Field[iField].pcText[0]!=' ' )
                      && ( dlg->Entry[iEntry].Field[iField].pcText[0]!='-' )
                       )
                      for( i=strlen(dlg->Entry[iEntry].Field[iField].pcText); i>0; i-- )
                       dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i-1];
                     dlg->Entry[iEntry].Field[iField].pcText[0] = (dlg->Entry[iEntry].Field[iField].pcText[0]=='-') ? ' ' : '-';
                     break;
                    }
                    /* Alle anderen Tasten                                  */
                    if( !(dlg->wFlags&DLG_FLG_BLOCK) )
                    {
                     /* Wenn das Feld voll ist und kein Block-Mode, dann raus */
                     if( (inp->iAllowed&DLG_FIELD_SIGN) && (dlg->Entry[iEntry].Field[iField].pcText[1]!=' ') ) return( TRUE );
                     if( !(inp->iAllowed&DLG_FIELD_SIGN) && (dlg->Entry[iEntry].Field[iField].pcText[0]!=' ') ) return( TRUE );
                    }
                    /* Wenn keine Zahl, dann raus                           */
                    if( ( iKey<'0' ) || ( iKey>'9' ) ) return( FALSE );
                    /* Stelle des Punktes suchen                            */
                    iPos = (inp->iAllowed&127)/10;
                    /* Wenn Cursor vor dem Punkt steht                      */
                    if( (iCur>0) && (iCur<=iPos) )
                    {
                     /* Wenn der Cursor 1 vor dem Punkt steht und die Ein-  */
                     /* gabe bis auf den Punkt leer ist, dann die 0 einfach */
                     /* ueberschreiben                                      */
                     if( ( (((inp->iAllowed&DLG_FIELD_SIGN)&&iCur==iPos))
                        || (!((inp->iAllowed&DLG_FIELD_SIGN)&&iCur==iPos-1))
                         )
                      && (dlg->Entry[iEntry].Field[iField].pcText[iCur-1]==' ')
                      && (dlg->Entry[iEntry].Field[iField].pcText[iCur]=='0')
                       )
                     {
                      dlg->Entry[iEntry].Field[iField].pcText[iCur] = iKey;
                      break;
                     }
                     /* Hier steht bereits was in der Eingabe               */
                     /* Wenn Insert-Modus aktiv oder der Cursor steht 1 vor */
                     /* dem Punkt und nach links ruecken ist aktiv, dann    */
                     /* Zeichen rechts anhaengen.                           */
/*
                     if( ( ( (((inp->iAllowed&DLG_FIELD_SIGN)&&iCur==iPos))
                          || (!((inp->iAllowed&DLG_FIELD_SIGN)&&iCur==iPos-1))
                           )
                        && ( boShift )
                         )
                      || (!(dlg->wFlags&DLG_FLG_BLOCK))
                       )
                     {
*/
//                     if( ((inp->iAllowed&DLG_FIELD_SIGN)&&(iCur<iPos))
//                      && (!((inp->iAllowed&DLG_FIELD_SIGN)&&iCur<(iPos-1)))
//                       )
                     {
                      /* Alle Zeichen nach links verschieben                */
                      for( i=(inp->iAllowed&DLG_FIELD_SIGN)?1:0; i<iCur; i++ )
                       dlg->Entry[iEntry].Field[iField].pcText[i] = dlg->Entry[iEntry].Field[iField].pcText[i+1];
                      /* Zeichen anhaengen und raus                         */
                      dlg->Entry[iEntry].Field[iField].pcText[i] = iKey;
                      break;
                     }
                    }
                    dlg->Entry[iEntry].Field[iField].pcText[iCur] = iKey;
                    if( ((inp->iAllowed&DLG_FIELD_SIGN)&&(iCur!=iPos))
                     || (!(inp->iAllowed&DLG_FIELD_SIGN)&&(iCur!=iPos-1))
                      )
                    {
//                     dlg->Entry[iEntry].Field[iField].wFlags &= ~DLG_FLG_SHIFT;
                     return( DlgHandleKey( dlg, iEntry, iField, T_RIGHT ) );
                    }
                    break;
              }
//              dlg->Entry[iEntry].Field[iField].wFlags &= ~DLG_FLG_SHIFT;
        }
        inp->iPos = iCur;
        break;
  }
  return( TRUE );
 }

 PRIVATE BOOL CDECL DlgGetMouEnt ( dlg, wMouX, wMouY, piX, piY )
 SDlg*          dlg;
 WORD           wMouX;
 WORD           wMouY;
 INT*           piX;
 INT*           piY;
 {
  INT           iEntry;
  INT           iField;
  for( iEntry=0; iEntry<=dlg->iEntAct; iEntry++ )
  {
   for( iField=0; iField<=dlg->Entry[iEntry].iFldAct; iField++ )
   {
    if( (dlg->Entry[iEntry].iTyp==DLG_STATIC) || (dlg->Entry[iEntry].iTyp==DLG_FRAME) ) continue;
    if( dlg->Entry[iEntry].Field[iField].wFlags&DLG_FLG_DISABLE ) continue;
    if( ( wMouX>=dlg->Entry[iEntry].wX )
     && ( wMouY==dlg->Entry[iEntry].Field[iField].wY+1 )
     && ( wMouX<=dlg->Entry[iEntry].wX+dlg->Entry[iEntry].Field[iField].wX+(WORD)dlg->Entry[iEntry].Field[iField].iLen )
      )
    {
     *piX = iEntry;
     *piY = iField;
      return( TRUE );
    }
   }
  }
  return( FALSE );
 }

 PRIVATE BOOL CDECL     DlgGetPrev( dlg, piEntry, piField, iType )
 SDlg*          dlg;
 INT*           piEntry;
 INT*           piField;
 INT            iType;
 {
  BOOL          boRet        = FALSE;
  do
  {
   if( iType!=DLG_ENTRY )
   {
    if( --(*piField) < 0 )
    {
     if( --(*piEntry) < 0 )
     {
      boRet = TRUE;
      *piEntry = dlg->iEntAct;
     }
     *piField = dlg->Entry[*piEntry].iFldAct;
    }
   }
   if( iType==DLG_ENTRY )
   {
    if( --(*piEntry) < 0 )
    {
     boRet = TRUE;
     *piEntry = dlg->iEntAct;
    }
    *piField = dlg->Entry[*piEntry].iFldCur;
    iType = DLG_NONE;
   }
   if( *piField<0 ) *piField = 0;
   if( *piEntry<0 ) *piEntry = 0;
   if( !(dlg->Entry[*piEntry].Field[*piField].wFlags&DLG_FLG_DISABLE)
    && (dlg->Entry[*piEntry].iTyp!=DLG_STATIC)
    && (dlg->Entry[*piEntry].iTyp!=DLG_FRAME)
     )
     break;
  } while( 1 );
  if( ((dlg->Entry[*piEntry].iTyp&127)==DLG_INPUT) && ((dlg->Entry[*piEntry].Field[*piField].t.Input->iAllowed&127)>=100) )
  {
//    printf( "%d", dlg->Entry[*piEntry].Field[*piField].t.Input->iAllowed&127 );
//    getch();
    dlg->Entry[*piEntry].Field[*piField].t.Input->iPos = 0;
  }
  return( boRet );
 }

 PRIVATE BOOL CDECL     DlgGetNext( dlg, piEntry, piField, iType )
 SDlg*          dlg;
 INT*           piEntry;
 INT*           piField;
 INT            iType;
 {
  BOOL          boRet        = FALSE;
  do
  {
   if( iType!=DLG_ENTRY )
   {
    if( ++(*piField) > dlg->Entry[*piEntry].iFldAct )
    {
     if( ++(*piEntry) > dlg->iEntAct )
     {
      boRet = TRUE;
      *piEntry = 0;
     }
     *piField = 0;
    }
   }
   if( iType==DLG_ENTRY )
   {
    if( ++(*piEntry) > dlg->iEntAct )
    {
     boRet = TRUE;
     *piEntry = 0;
    }
    *piField = dlg->Entry[*piEntry].iFldCur;
    iType = DLG_NONE;
   }
   if( !(dlg->Entry[*piEntry].Field[*piField].wFlags&DLG_FLG_DISABLE)
    && (dlg->Entry[*piEntry].iTyp!=DLG_STATIC)
    && (dlg->Entry[*piEntry].iTyp!=DLG_FRAME)
     )
     break;
  } while( 1 );
  if( ((dlg->Entry[*piEntry].iTyp&127)==DLG_INPUT) && ((dlg->Entry[*piEntry].Field[*piField].t.Input->iAllowed&127)>=100) )
  {
//    printf( "%d", dlg->Entry[*piEntry].Field[*piField].t.Input->iAllowed&127 );
//    getch();
   dlg->Entry[*piEntry].Field[*piField].t.Input->iPos = 0;
  }
  return( boRet );
 }

 VOID CDECL     DlgSelect    ( entry, iMark )
 SDlgEntry*     entry;
 INT            iMark;
 {
  INT           i;
  for( i=0; i<=entry->iFldAct; i++ )
   entry->Field[i].wFlags &= ~DLG_FLG_MARKED;
  entry->Field[iMark].wFlags |= DLG_FLG_MARKED;
 }

#ifdef          _TEST_DLG_

 #include       <BASICS/TIME.H>
 #include       <stdio.h>
 #include       <process.h>

 VOID           DoDlg        ( void );

 VOID           DoDlg        ( void )
 {
  SDlg*         dlg;
  CHAR          cTemp[80];
  INT           iCount       = 0;
  INT           iAnz         = 0;
  dlg = DlgInit( 50 );
  /* ---------- Linien ---------------------------------------------------- */
  DlgInitEntry( dlg, 2, DLG_FRAME,24, 0       , "", NULL, "" );
  DlgAddField ( dlg, 0, 0, NULL, 0, 10 );
  DlgAddField ( dlg,24, 0, NULL, 0, 10 ); iAnz++;
  DlgInitEntry( dlg, 3, DLG_FRAME, 0, 0       , "", NULL, "" );
  DlgAddField ( dlg, 1,11, NULL,74,  0 );
  DlgAddField ( dlg, 1,16, NULL,74,  0 );
  DlgAddField ( dlg,36,12, NULL, 0,  3 ); iAnz++;
  /* ---------- Datum und Uhrzeit ----------------------------------------- */
  TimeGetDateStr( cTemp, TRUE );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~a~) Datum.:", NULL, " ~Eingabefeld Datum~" );
  DlgAddField ( dlg, 12, 0, cTemp, DLG_FIELD_DATE, 10 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Datum.:", NULL, "" );
  DlgAddField ( dlg, 12, 0, cTemp, DLG_FIELD_DATE, 10 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~b~) Datum.:", NULL, " ~Eingabefeld Datum~ als Pa·wort" );
  DlgAddField ( dlg, 12, 0, cTemp, DLG_FIELD_DATE|DLG_FIELD_PASSW, 10 ); iAnz++;
  TimeGetTimeStr( cTemp );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~c~) Zeit..:", NULL, " ~Eingabefeld Uhrzeit~" );
  DlgAddField ( dlg, 12, 0, cTemp, DLG_FIELD_TIME, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Zeit..:", NULL, "" );
  DlgAddField ( dlg, 12, 0, cTemp, DLG_FIELD_TIME, 8 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~d~) Zeit..:", NULL, " ~Eingabefeld Uhrzeit~ als Pa·wort" );
  DlgAddField ( dlg, 12, 0, cTemp, DLG_FIELD_TIME|DLG_FIELD_PASSW, 8 ); iAnz++;
  /* ---------- Text ------------------------------------------------------ */
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~e~) Text..:", NULL, " ~Eingabefeld Text~" );
  DlgAddField ( dlg, 12, 0, "Text", DLG_FIELD_ALL, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Text..:", NULL, "" );
  DlgAddField ( dlg, 12, 0, "Text", DLG_FIELD_ALL, 8 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~f~) Text..:", NULL, " ~Eingabefeld Text~ als Pa·wort" );
  DlgAddField ( dlg, 12, 0, "Text", DLG_FIELD_ALL|DLG_FIELD_PASSW, 8 ); iAnz++;
  /* ---------- Zahlen ohne Vorzeichen ------------------------------------ */
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~g~) Nummer:", NULL, " ~Eingabefeld Dezimal-Zahl~ linksbÅndig (unsigned)" );
  DlgAddField ( dlg, 12, 0, "0", DLG_FIELD_NUM, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Nummer:", NULL, "" );
  DlgAddField ( dlg, 12, 0, "0", DLG_FIELD_NUM, 8 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~h~) Nummer:", NULL, " ~Eingabefeld Dezimal-Zahl~ linksbÅndig (unsigned) als Pa·wort" );
  DlgAddField ( dlg, 12, 0, "0", DLG_FIELD_NUM|DLG_FIELD_PASSW, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~i~) Hexa..:", NULL, " ~Eingabefeld Hexadezimal-Zahl~ linksbÅndig (unsigned)" );
  DlgAddField ( dlg, 12, 0, "A0", DLG_FIELD_HEX, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Hexa..:", NULL, "" );
  DlgAddField ( dlg, 12, 0, "A0", DLG_FIELD_HEX, 8 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~j~) Hexa..:", NULL, " ~Eingabefeld Hexadezimal-Zahl~ linksbÅndig als Pa·wort (unsigned)" );
  DlgAddField ( dlg, 12, 0, "A0", DLG_FIELD_HEX|DLG_FIELD_PASSW, 8 ); iAnz++;
  /* ---------- Zahlen mit Vorzeichen ------------------------------------- */
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~k~) Nummer:", NULL, " ~Eingabefeld Dezimal-Zahl~ linksbÅndig (signed)" );
  DlgAddField ( dlg, 12, 0, " 0", DLG_FIELD_NUM|DLG_FIELD_SIGN, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Nummer:", NULL, "" );
  DlgAddField ( dlg, 12, 0, " 0", DLG_FIELD_NUM, 8 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~l~) Nummer:", NULL, " ~Eingabefeld Dezimal-Zahl~ linksbÅndig (signed) als Pa·wort" );
  DlgAddField ( dlg, 12, 0, " 0", DLG_FIELD_NUM|DLG_FIELD_SIGN|DLG_FIELD_PASSW, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~m~) Hexa..:", NULL, " ~Eingabefeld Hexadezimal-Zahl~ linksbÅndig (signed)" );
  DlgAddField ( dlg, 12, 0, " A0", DLG_FIELD_HEX|DLG_FIELD_SIGN, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Hexa..:", NULL, "" );
  DlgAddField ( dlg, 12, 0, " A0", DLG_FIELD_HEX|DLG_FIELD_SIGN, 8 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~n~) Hexa..:", NULL, " ~Eingabefeld Hexadezimal-Zahl~ linksbÅndig (signed) als Pa·wort" );
  DlgAddField ( dlg, 12, 0, " A0", DLG_FIELD_HEX|DLG_FIELD_SIGN|DLG_FIELD_PASSW, 8 ); iAnz++;
  /* ---------- Floats ohne Vorzeichen ------------------------------------ */
  sprintf( cTemp, "%5hd.%02hd", 7, 89 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~o~) Float0:", NULL, " ~Zahl mit 2 Nachkommastellen~ rechtsbÅndig (unsigned)" );
  DlgAddField ( dlg, 12, 0, cTemp, 52, 10 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Float0:", NULL, "" );
  DlgAddField ( dlg, 12,25, cTemp, 52, 10 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~p~) Float0:", NULL, " ~Zahl mit 2 Nachkommastellen~ rechtsbÅndig (unsigned)" );
  DlgAddField ( dlg, 12, 0, cTemp, 52|DLG_FIELD_PASSW, 10 ); iAnz++;
  /* ---------- Floats mit Vorzeichen ------------------------------------- */
  sprintf( cTemp, "-%5hd.%02hd", 7, 89 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~q~) Float2:", NULL, " ~Zahl mit 2 Nachkommastellen~ rechtsbÅndig (signed)" );
  DlgAddField ( dlg, 12, 0, cTemp, 52|DLG_FIELD_SIGN, 8 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Float2:", NULL, "" );
  DlgAddField ( dlg, 12,25, cTemp, 52|DLG_FIELD_SIGN, 8 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~r~) Float2:", NULL, " ~Zahl mit 2 Nachkommastellen~ rechtsbÅndig (signed)" );
  DlgAddField ( dlg, 12, 0, cTemp, 52|DLG_FIELD_SIGN|DLG_FIELD_PASSW, 8 ); iAnz++;
  /* ---------- Floats ohne Vorzeichen, 0 Nachkommastellen ---------------- */
  sprintf( cTemp, "%7hd", 123 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~s~) Float0:", NULL, " ~Zahl mit 0 Nachkommastellen~ rechtsbÅndig (unsigned)" );
  DlgAddField ( dlg, 12, 0, cTemp, 70, 7 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Float0:", NULL, "" );
  DlgAddField ( dlg, 12,25, cTemp, 70, 7 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~t~) Float0:", NULL, " ~Zahl mit 0 Nachkommastellen~ rechtsbÅndig als Pa·wort (unsigned)" );
  DlgAddField ( dlg, 12, 0, cTemp, 70|DLG_FIELD_PASSW, 7 ); iAnz++;
  /* ---------- Floats mit Vorzeichen, 0 Nachkommastellen ----------------- */
  sprintf( cTemp, "-%7hd", 123 );
  DlgInitEntry( dlg, 1, DLG_INPUT, 1, iCount  , "~u~) Float2:", NULL, " ~Zahl mit 0 Nachkommastellen~ rechtsbÅndig (signed)" );
  DlgAddField ( dlg, 12, 0, cTemp, 70|DLG_FIELD_SIGN, 7 ); iAnz++;
  DlgInitEntry( dlg, 1, DLG_INPUT,25, iCount  , "-) Float2:", NULL, "" );
  DlgAddField ( dlg, 12,25, cTemp, 70|DLG_FIELD_SIGN, 7 ); DlgDisable( dlg, iAnz++, 0 );
  DlgInitEntry( dlg, 1, DLG_INPUT,50, iCount++, "~v~) Float2:", NULL, " ~Zahl mit 0 Nachkommastellen~ rechtsbÅndig als Pa·wort (signed)");
  DlgAddField ( dlg, 12, 0, cTemp, 70|DLG_FIELD_SIGN|DLG_FIELD_PASSW, 7 ); iAnz++;
  /* ---------- Check-Boxes ----------------------------------------------- */
  DlgInitEntry( dlg, 5, DLG_CHECK, 1, iCount+1, "Checkboxes:", NULL, " ~Check-Boxen~ als Flag-Indikator" );
  DlgAddField ( dlg, 2, 1, "~0~) Checkbox", 1, 0 );
  DlgAddField ( dlg, 2, 2, "~1~) Checkbox", 0, 0 );
  DlgAddField ( dlg, 2, 3, "~2~) Checkbox", 1, 0 );
  DlgAddField ( dlg,18, 1, "~3~) Checkbox", 0, 0 );
  DlgAddField ( dlg,18, 2, "~4~) Checkbox", 1, 0 ); iAnz++;
  /* ---------- Radio-Buttons --------------------------------------------- */
  DlgInitEntry( dlg, 5, DLG_RADIO,38, iCount+1, "Radio-Buttons:", NULL, " ~Radio-Buttons~ als Auswahlmîglichkeit" );
  DlgAddField ( dlg, 2, 1, "~5~) Radio   ", 0, 0 );
  DlgAddField ( dlg, 2, 2, "~6~) Radio   ", 0, 0 );
  DlgAddField ( dlg, 2, 3, "~7~) Radio   ", 1, 0 );
  DlgAddField ( dlg,18, 1, "~8~) Radio   ", 0, 0 );
  DlgAddField ( dlg,18, 2, "~9~) Radio   ", 0, 0 ); iAnz++;
  /* ---------- Push-Buttons ---------------------------------------------- */
  DlgInitEntry( dlg, 5, DLG_PUSH, 1, iCount+6, "", NULL, " ~Push-Buttons~ als sichtbare Exit-Keys" );
  DlgAddField ( dlg, 1, 1, " ~w~) PUSH 1 ",10,15 );
  DlgAddField ( dlg,16, 1, " ~x~) PUSH 2 ",10, 5 );
  DlgAddField ( dlg,32, 1, " ~y~) PUSH 3 ",10, 5 );
  DlgAddField ( dlg,48, 1, " ~z~) PUSH 4 ",10, 5 );
  if( DlgHandle( dlg, VioCenterCol( 78 ), VioCenterRow( 22 ), 78, 22, "Testdialog", NULL )!=T_ESC )
  {
  }
  DlgDone( dlg );
 }

 VOID           main         ( void )
 {
  VioInit( VIO_NONE );
  VioBackground();
  EvInit();
//  EvSchonDelay( 10L );
  DoDlg();
  EvDone();
  VioDone();
 }

#endif
