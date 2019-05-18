/****************************************************************************/
/* PALETTE.H                                                                */
/* ------------------------------------------------------------------------ */
/* Definitionen der Farbpaletten fuer Menues, Listen, Dialoge...            */
/****************************************************************************/
#ifndef         _PALETTE_

 #define        _PALETTE_
 #include       "defs/Typedefs.h"                /* Grundlegende Datentypen */

 /* ----------- Typdefintionen: Palette eines Menues ---------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef WORD   SMnuPal[8];
 #define        MNU_PAL             0            /* Konstante fuer Menues   */
 #define        MNU_PAL_FRAME       0            /* Attribut des Rahmens    */
 #define        MNU_PAL_TITLE       1            /* Attribut des Titels     */
 #define        MNU_PAL_TEXT        2            /* Attribut des Textes     */
 #define        MNU_PAL_INVERS      3            /* Attribut des inversen Textes */
 #define        MNU_PAL_HOTKEY      4            /* Attribut des Hotkeys    */
 #define        MNU_PAL_INVHOT      5            /* Attribut des inversen Hotkeys */
 #define        MNU_PAL_STATUS      6            /* Attribut der Statuszeile*/
 #define        MNU_PAL_INVSTAT     7            /* Attribut der inversen Statuszeile */

 /* ----------- Typdefintionen: Palette einer Liste ----------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef WORD   SLstPal[6];
 #define        LST_PAL             1            /* Konstante fuer Listen   */
 #define        LST_PAL_FRAME       0            /* Attribut des Rahmens    */
 #define        LST_PAL_TITLE       1            /* Attribut des Titels     */
 #define        LST_PAL_TEXT        2            /* Attribut des Textes     */
 #define        LST_PAL_INVERS      3            /* Attribut des inversen Textes */
 #define        LST_PAL_STATUS      4            /* Attribut der Statuszeile*/
 #define        LST_PAL_INVSTAT     5            /* Attribut der inversen Statuszeile */

 /* ----------- Typdefinitionen: Palette einer Nachricht ------------------ */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef WORD   SMsgPal[3];
 #define        MSG_PAL             2            /* Konstante fuer Listen   */
 #define        MSG_PAL_FRAME       0            /* Attribut des Rahmens    */
 #define        MSG_PAL_TITLE       1            /* Attribut des Titels     */
 #define        MSG_PAL_TEXT        2            /* Attribut des Textes     */

 /* ----------- Typdefinitionen: Palette eines Dialoges ------------------- */
 #ifndef UNIX
 #pragma        pack(1)
 #endif
 typedef WORD   SDlgPal[17];
 #define        DLG_PAL             3            /* Konstante fuer Listen   */
 #define        DLG_PAL_FRAME       0            /* Attribut des Rahmens    */
 #define        DLG_PAL_TITLE       1            /* Attribut des Titels     */
 #define        DLG_PAL_TEXT        2            /* Attribut des Textes     */
 #define        DLG_PAL_INVERS      3            /* Inverser Text           */
 #define        DLG_PAL_HOTNORM     4            /* Hotkey normaler Text    */
 #define        DLG_PAL_HOTINV      5            /* Hotkey inverser Text    */
 #define        DLG_PAL_STATNORM    6            /* Statuszeile normal      */
 #define        DLG_PAL_STATINV     7            /* Statuszeile invers      */
 #define        DLG_PAL_DISABLE     8            /* Disableter Eintrag      */
 #define        DLG_PAL_PUSHDIS     9            /* Push-Button, disabled   */
 #define        DLG_PAL_PUSHNORMAL  10
 #define        DLG_PAL_PUSHINVERS  11
 #define        DLG_PAL_PUSHHOTNORM 12
 #define        DLG_PAL_PUSHHOTINV  13
 #define        DLG_PAL_EDIT        14
 #define        DLG_PAL_EDITMARK    15

 /* ----------- Prototypen ------------------------------------------------ */
 DECLSTART
 WORD CDECL     PalGetVal       PARAM(( INT, INT ));
 VOID CDECL     PalSetVal       PARAM(( INT, INT, WORD, WORD ));
 DECLEND
 #define        MnuGetPal( x )      PalGetVal( MNU_PAL, x )
 #define        MnuSetPal( x, y, z )   PalSetVal( MNU_PAL, x, y, z )
 #define        LstGetPal( x )      PalGetVal( LST_PAL, x )
 #define        LstSetPal( x, y, z )   PalSetVal( LST_PAL, x, y, z )
 #define        MsgGetPal( x )      PalGetVal( MSG_PAL, x )
 #define        MsgSetPal( x, y, z )   PalSetVal( MSG_PAL, x, y, z )
 #define        DlgGetPal( x )      PalGetVal( DLG_PAL, x )
 #define        DlgSetPal( x, y, z )   PalSetVal( DLG_PAL, x, y, z )

#endif
