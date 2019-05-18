/****************************************************************************/
/* PALETTE.C                                                                */
/* ------------------------------------------------------------------------ */
/* Verwalten der Palette fuer Menues, Listen, Dialoge...                    */
/****************************************************************************/
 #include       "hilevel/Palette.h"              /* Eigene Headerdatei      */
 #include       "hilevel/Vio.h"                  /* Fuer VioIsMono          */
 #include       "defs/Colordef.h"                /* Farbdefinitionen        */
 #include       "defs/Bitdefs.h"                 /* Bitdefinitionen         */

 PRIVATE SMnuPal MnuPalColor = { VH( SCHWARZ, WEISS )  /* Rahmenattribut       */
                               , VH( SCHWARZ, WEISS )  /* Titelattribut        */
                               , VH( SCHWARZ, WEISS )  /* Normaler Text        */
                               , VH( HELLWEISS, BLAU ) /* Inverser Text        */
                               , VH( ROT, WEISS )      /* Normaler Text bei Hotkeys */
                               , VH( HELLROT, BLAU )   /* Inverser Text bei Hotkeys */
                               , VH( SCHWARZ, WEISS )  /* Normaler Text der Statuszeile */
                               , VH( ROT, WEISS )      /* Inverser Text der Statuszeile */
                               };
 PRIVATE SMnuPal MnuPalMono  = { NORMAL                /* Rahmenattribut       */
                               , INVERS                /* Titelattribut        */
                               , NORMAL                /* Normaler Text        */
                               , INVERS                /* Inverser Text        */
                               , INVERS                /* Normaler Text bei Hotkeys */
                               , NORMAL                /* Inverser Text bei Hotkeys */
                               , NORMAL                /* Normaler Text der Statuszeile */
                               , NORMAL                /* Inverser Text der Statuszeile */
                               };
 PRIVATE SLstPal LstPalColor = { VH( SCHWARZ, WEISS )  /* Rahmenattribut       */
                               , VH( SCHWARZ, WEISS )  /* Titelattribut        */
                               , VH( SCHWARZ, WEISS )  /* Normaler Text        */
                               , VH( HELLWEISS, BLAU ) /* Inverser Text        */
                               , VH( SCHWARZ, WEISS )  /* Normaler Text der Statuszeile */
                               , VH( ROT, WEISS )      /* Inverser Text der Statuszeile */
                               };
 PRIVATE SLstPal LstPalMono  = { NORMAL                /* Rahmenattribut       */
                               , INVERS                /* Titelattribut        */
                               , NORMAL                /* Normaler Text        */
                               , INVERS                /* Inverser Text        */
                               , NORMAL                /* Normaler Text der Statuszeile */
                               , NORMAL                /* Inverser Text der Statuszeile */
                               };

 PRIVATE SMsgPal MsgPalColor = { VH( WEISS, BLAU )     /* Rahmenattribut    */
                               , VH( WEISS, BLAU )     /* Titelattribut     */
                               , VH( WEISS, BLAU )     /* Normaler Text     */
                               };
 PRIVATE SMsgPal MsgPalMono  = { INVERS                /* Rahmenattribut    */
                               , INVERS                /* Titelattribut     */
                               , INVERS                /* Normaler Text     */
                               };
 PRIVATE SDlgPal DlgPalColor = { VH( SCHWARZ, WEISS )  /* Rahmenattribut    */
                               , VH( SCHWARZ, WEISS )  /* Titelattribut     */
                               , VH( SCHWARZ, WEISS )  /* Normaler Text     */
                               , VH( HELLWEISS, BLAU ) /* Inverser Text     */
                               , VH( ROT, WEISS )      /* Normaler Text der Hotkeys */
                               , VH( HELLROT, BLAU )   /* Inverser Text der Hotkeys */
                               , VH( SCHWARZ, WEISS )  /* Normaler Text der Statuszeile */
                               , VH( ROT, WEISS )      /* Inverser Text der Statuszeile */
                               , VH( SCHWARZ, WEISS )  /* Attribut eines nicht aktiven Eintrags */
                               , VH( GRAU, GRUEN )     /* Attribut eines nicht aktiven Push-Buttons */
                               , VH( ROT, GRUEN )      /* Attribut des Hotkeys eines Push-Buttons */
                               , VH( WEISS, GRUEN )    /* Attribut eines aktiven Push-Buttons */
                               , VH( GELB, BLAU )      /* Attribut eines aktiven Push-Buttons */
                               , VH( HELLROT, BLAU )   /* Attribut des Hotkeys eines Push-Buttons */
                               , VH( SCHWARZ, KOBALT ) /* Attribut des Editierfeldes */
                               , VH( BLAU, GELB )      /* Attribut des Markierten Textes */
                               };
 PRIVATE SDlgPal DlgPalMono  = { INVERS                /* Rahmenattribut    */
                               , INVERS                /* Titelattribut     */
                               , NORMAL                /* Normaler Text     */
                               , INVERS                /* Inverser Text     */
                               , NORMAL                /* Normaler Text der Hotkeys */
                               , NORMAL                /* Inverser Text der Hotkeys */
                               , INVERS                /* Normaler Text der Statuszeile */
                               , NORMAL                /* Inverser Text der Statuszeile */
                               , NORMAL                /* Attribut eines nicht aktiven Eintrags */
                               , NORMAL                /* Attribut eines nicht aktiven Push-Buttons */
                               , NORMAL                /* Attribut eines inaktiven Push-Buttons */
                               , INVERS                /* Attribut des Hotkeys eines aktiven Push-Buttons */
                               , NORMAL                /* Attribut eines aktiven Push-Buttons */
                               , INVERS                /* Attribut des Hotkeys eines inaktiven Push-Buttons */
                               , NORMAL                /* Attribut des Editierfeldes */
                               , INVERS                /* Attribut des Markierten Textes */
                               };

 WORD CDECL     PalGetVal    ( iPal, iEntry )
 INT            iPal;
 INT            iEntry;
 {
  switch( iPal )
  {
   case MNU_PAL: return( VioIsMono() ? MnuPalMono[iEntry] : MnuPalColor[iEntry] );
   case LST_PAL: return( VioIsMono() ? LstPalMono[iEntry] : LstPalColor[iEntry] );
   case MSG_PAL: return( VioIsMono() ? MsgPalMono[iEntry] : MsgPalColor[iEntry] );
   case DLG_PAL: return( VioIsMono() ? DlgPalMono[iEntry] : DlgPalColor[iEntry] );
  }
  return( 0 );
 }

 VOID CDECL     PalSetVal    ( iPal, iEntry, wColor, wMono )
 INT            iPal;
 INT            iEntry;
 WORD           wColor;
 WORD           wMono;
 {
  switch( iPal )
  {
   case MNU_PAL:
        MnuPalMono[iEntry] = wMono;
        MnuPalColor[iEntry] = wColor;
        break;
   case LST_PAL:
        LstPalMono[iEntry] = wMono;
        LstPalColor[iEntry] = wColor;
        break;
   case MSG_PAL:
        MsgPalMono[iEntry] = wMono;
        MsgPalColor[iEntry] = wColor;
        break;
   case DLG_PAL:
        DlgPalMono[iEntry] = wMono;
        DlgPalColor[iEntry] = wColor;
        break;
  }
 }
