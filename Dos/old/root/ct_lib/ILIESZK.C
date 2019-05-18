/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_DlgLiesZK                    Datum: 20.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        pTextBox      Zeiger auf die Struktur TEXTBOX       บ
  บ                    pEvent        Zeiger auf die Ereignisstruktur       บ
  บ                    wInit         interne Strukturen aktual.            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion dient zur Untersttzung der Text-    บ
  บ                    boxen in einem Dialogfeld. Sie stellt im wesent-    บ
  บ                    lichen einen zeilenorientierten Texteditor dar,     บ
  บ                    wobei die Textbearbeitung wahlweise mit Tastatur    บ
  บ                    oder Maus erfolgen kann.                            บ
  บ                                                                        บ
  บ                    Die Struktur ฏTEXTBOXฎ enthlt smtliche Infor-     บ
  บ                    mationen ber die Textbox (Gr”แe, Lage, Text). Zur  บ
  บ                    Bearbeitung wird der Text in einen Buffer kopiert.  บ
  บ                    Um die Ausgabegeschwindigkeit zu erh”hen, werden    บ
  บ                    die Zeichen zusammen mit ihrem Attribut in dem      บ
  บ                    Buffer abgelegt. Bevor die Funktion einen Text be-  บ
  บ                    arbeiten kann, muแ ein Aufruf erfolgen, bei dem dem บ
  บ                    Parameter ฏwInitฎ die Textkonstante AKT_BUFFER      บ
  บ                    bergeben werden muแ. Die beiden ersten Parameter   บ
  บ                    sind in diesem Fall bedeutungslos.                  บ
  บ                    Um den editierten Text wieder in die Textbox-Struk- บ
  บ                    tur zurckzuschreiben, muแ ein Aufruf erfolgen, bei บ
  บ                    dem fr den Parameter ฏwInitฎ die Textkonstante     บ
  บ                    AKT_TEXTBOX bergeben wird. Auch in diesem Fall     บ
  บ                    sind die beiden ersten Parameter bedeutungslos.     บ
  บ                                                                        บ
  บ                    Bei jeder Cursorbewegung wird die neue Position     บ
  บ                    in die Struktur eingetragen.                        บ
  บ                                                                        บ
  บ                    Die Funktion speichert den Zeiger auf die zu-       บ
  บ                    letzt bearbeitete Struktur und kann so erkennen,    บ
  บ                    ob der aktuelle Aufruf sich auf diese oder eine     บ
  บ                    neue Struktur bezieht.                              บ
  บ                    Bevor eine Textbox editiert werden kann muแ die     บ
  บ                    aufrufende Funktion den Text auf dem Bildschirm     บ
  บ                    ausgeben.                                           บ
  บ                                                                        บ
  บ                    Folgende Sondertasten werden untersttzt:           บ
  บ                                                                        บ
  บ                    <- , ->   bewegen den Cursor um eine Spalte         บ
  บ                    HOME      bewegt den Cursor an den Textanfang       บ
  บ                    END       bewegt den Cursor an das Textende         บ
  บ                    BACKSPACE l”scht das Zeichen links neben dem Cursor บ
  บ                    DELETE    l”scht das Zeichen unter dem Cursor       บ
  บ                    INSERT    schaltet Einfge-Modus ein oder aus       บ
  บ                                                                        บ
  บ  Rckgabewert:     Die Funktion hat keinen Rckgabewert                บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - wMausda_g (R)                                    บ
  บ                     - wVioMode_g (R)                                   บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <stdio.h>
#include <DEFS.H>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define LINKS   0
#define RECHTS  1
#define HOME    2
#define ENDE    3

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wMausda_g;
IMPORT WORD wVioMode_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL TEXTBOX* pTB_m;                             /* zeigt auf aktuelle   */
                                                    /* Struktur             */
MGLOBAL WORD     awBuffer_m[TB_MAX+1];              /* enthlt editierten   */
                                                    /* Text mit Attribut    */
MGLOBAL PWORD    pwBufferC_m;                       /* Zeigt auf aktuelle   */
                                                    /* Cursorpos. im Buffer */
MGLOBAL PWORD    pwBufferE_m;                       /* zeigt auf das letzte */
                                                    /* Zeichen im Buffer    */


MGLOBAL VOID i_ZeichenEinfuegen    (WORD);
MGLOBAL VOID i_BufferAkt           (VOID);
MGLOBAL VOID i_StrukturAkt         (VOID);
MGLOBAL VOID i_TextboxAkt          (WORD, PWORD);
MGLOBAL VOID i_SchiebeTextsegment  (SWORD);
MGLOBAL VOID i_BewegeCursor        (SWORD);
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_DlgLiesZK( TEXTBOX* pTextBox, EVENT* pEvent, WORD wInit)
{
    pTB_m = pTextBox;                               /* modulglobalen Zeiger */
                                                    /* initialisieren       */

    if (wInit == AKT_TEXTBOX)                       /* Struktur aktual. ?   */
    {
      i_StrukturAkt();
      return;
    }

    if (wInit == AKT_BUFFER)
    {
      i_BufferAkt();                                /* Buffer neu laden     */
      i_TextboxAkt(pTB_m->wFensterS,                /* Text ausgeben        */
                   awBuffer_m);
      i_BewegeCursor(HOME);                         /* Cursor an Textanfang */
      return;
    }

    switch (pEvent->wArt)
    {
      case EVENT_TASTE:

        if ( pEvent->wTaste == ',' &&                       /* DEL-Taste    */
             pEvent->wKbflags & (RSHIFT|LSHIFT) && /* auf dem Zif- */
             !(pEvent->wKbflags & NUMLOCK) )               /* fernblock    */
            pEvent->wTaste = T_DEL;                         /* untersttzen */

        switch (pEvent->wTaste)
        {
          case T_DEL:
            if ( pEvent->wKbflags & 0x03 )          /* Shift-Taste gedrckt */
            {
              pTB_m->acText[0] = '\0';              /* Text l”schen         */
              i_BufferAkt();                        /* Buffer neu laden     */
              i_TextboxAkt(pTB_m->wFensterS,        /* Text ausgeben        */
                           awBuffer_m);
              i_BewegeCursor(HOME);                 /* Cursor an Textanfang */
            }
            else if (pwBufferC_m <= pwBufferE_m)    /* Cursor im Text ?     */
            {
              i_SchiebeTextsegment(LINKS);          /* eine Spalte nach     */
                                                    /* links schieben       */
              i_TextboxAkt(pTB_m->wCursorS,
                           pwBufferC_m);
            }
            else
              UtlBeep();
            break;

          case T_BACKSPACE:
            if (pwBufferC_m > awBuffer_m)           /* Cursor im Text ?     */
            {
              i_BewegeCursor(LINKS);
              i_SchiebeTextsegment(LINKS);
              i_TextboxAkt(pTB_m->wCursorS,
                           pwBufferC_m);
            }
            else
              UtlBeep();
            break;


          case T_RIGHT:
            i_BewegeCursor(RECHTS);                 /* Cursor nach rechts   */
            break;


          case T_LEFT:
            i_BewegeCursor(LINKS);                  /* Cursor nach links    */
            break;


          case T_HOME:
            i_BewegeCursor(HOME);                   /* Cursor an Textanfang */
            break;


          case T_END:
            i_BewegeCursor(ENDE);                   /* Cursor an Textende   */
            break;


          case T_INS:
            if (pTB_m->boInsert)                    /* Einfge-Modus ein ?  */
            {
              pTB_m->boInsert = NEIN;

              if (wVioMode_g == MONOCHROM)
                VioSetCursorTyp(0,12);              /* Block-Cursor         */
              else
                VioSetCursorTyp(0,7);
            }
            else
            {
              pTB_m->boInsert = JA;

              if (wVioMode_g == MONOCHROM)
                VioSetCursorTyp(11,12);             /* Linien-Cursor        */
              else
                VioSetCursorTyp(6,7);
            }
            break;

          case T_RETURN:                            /* Tasten abfangen,     */
          case T_TAB:                               /* die zur Steuerung    */
          case T_SHIFT_TAB:                         /* der Dialogbox be-    */
          case T_ESC:                               /* n”tigt werden        */
            break;

          default:
            if (pEvent->wTaste <= 255 &&            /* erlaubtes Zeichen ?  */
                pEvent->wTaste >= 32  &&
                pwBufferC_m < awBuffer_m +          /* steht der Cursor im  */
                              pTB_m->wMaxL )        /* Buffer ?             */
              i_ZeichenEinfuegen(pEvent->wTaste);
            else
              UtlBeep();
        }
        break;


      case EVENT_L_PRESS:
        if (pEvent->wZeile  == pTB_m->wFensterZ &&  /* Koordinaten ber- */
            pEvent->wSpalte >= pTB_m->wFensterS &&  /* prfen            */
            pEvent->wSpalte <  pTB_m->wFensterS +
                               pTB_m->wFensterB )
          {
            VioSetCursorPos( pEvent->wSpalte,       /* Cursor positionieren */
                             pEvent->wZeile);
            pwBufferC_m += pEvent->wSpalte -        /* Zeiger aktualisieren */
                           pTB_m->wCursorS;
            pTB_m->wCursorS = pEvent->wSpalte;
          }
        break;


      default:
        ;                                           /* andere Events werden */
                                                    /* nicht untersttzt    */
    }

    return;                                         /* fertig!              */
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_ZeichenEinfuegen             Datum: 24.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wZeichen    einzufgendes Zeichen          บ
  บ                                                                        บ
  บ  Beschreibung:     Das Verhalten der Funktion ist von dem aktuellen    บ
  บ                    Stand der Variablen ฏpTBakt->boInsertฎ abhngig.    บ
  บ                    Bei eingeschaltetem Einfge-Modus untersucht die    บ
  บ                    Funktion zunchst, ob der Buffer ein weiteres       บ
  บ                    Zeichen aufnehmen kann und fgt dann das Zeichen    บ
  บ                    an der Cursorposition in den Buffer ein.            บ
  บ                    Bei ausgeschaltetem Einfge-Modus wird das Zeichen  บ
  บ                    an der aktuellen Cursorposition berschrieben.      บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - awBuffer_m (W)                                   บ
  บ                     - pwBufferC_m (W)                                  บ
  บ                     - pwBufferE_m (W)                                  บ
  บ                     - pTB_m (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_ZeichenEinfuegen( WORD wZeichen )
{
    if (pTB_m->boInsert)                            /* Insert-Modus ein ?   */
    {
        if (pwBufferE_m < awBuffer_m +              /* noch Platz ?         */
                          pTB_m->wMaxL -1)
        {
            if (pwBufferC_m > pwBufferE_m)          /* Cursor hinter dem    */
                                                    /* letzten Zeichen ?    */
                pwBufferE_m = pwBufferC_m;          /* Zeiger aktualisieren */
            else
                i_SchiebeTextsegment(RECHTS);       /* eine Spalte nach     */
                                                    /* rechts schieben      */

            *pwBufferC_m = wZeichen |               /* Zeichen einfgen     */
                           pTB_m->wAttri << 8;

            i_TextboxAkt(pTB_m->wCursorS,
                         pwBufferC_m);

            i_BewegeCursor(RECHTS);
        }
        else                                        /* kein Platz mehr      */
            UtlBeep();
    }
    else                                            /* Insert-Modus aus ?   */
    {
        if (pwBufferC_m > pwBufferE_m)              /* Cursor hinter dem    */
            pwBufferE_m = pwBufferC_m;              /* letzten Zeichen ?    */
                                                    /* Zeiger aktualisieren */

        *pwBufferC_m = wZeichen |                   /* Zeichen einfgen     */
                      pTB_m->wAttri << 8;

        i_TextboxAkt(pTB_m->wCursorS,
                     pwBufferC_m);

        i_BewegeCursor(RECHTS);
    }
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_BufferAkt                    Datum: 24.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion kopiert den auszugebenden Text in      บ
  บ                    den Buffer ฏawBuffer_mฎ. Dabei wird jedes Zeichen   บ
  บ                    direkt mit seinem Attribut abgelegt. Wenn n”tig,    บ
  บ                    wird der Buffer mit Leerzeichen aufgefllt.         บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - awBuffer_m (W)                                   บ
  บ                     - pwBufferC_m (W)                                  บ
  บ                     - pwBufferE_m (W)                                  บ
  บ                     - pTB_m (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_BufferAkt(VOID)
{
    WORD  wAttri   = pTB_m->wAttri << 8;            /* Textattribut         */
    PSTR  pstrText = pTB_m->acText;                 /* zu editierender Text */


    pwBufferC_m = awBuffer_m;                       /* Zeiger auf Buffer    */

    while ( (*pwBufferC_m++ = *pstrText++ | wAttri) != wAttri )
        ;                                           /* Text in den Buffer   */
                                                    /* kopieren             */
    pwBufferE_m = pwBufferC_m -2;                   /* zeigt auf das letzte */
                                                    /* Textzeichen          */

    wAttri |= ' ';                                  /* Attribut mit Leer-   */
                                                    /* zeichen verknpfen   */

    for ( pwBufferC_m--;                            /* Rest des Buffers mit */
          pwBufferC_m<=awBuffer_m+pTB_m->wMaxL;     /* Leerzeichen fllen   */
          *pwBufferC_m++ = wAttri)
       ;

    pwBufferC_m = awBuffer_m;                       /* Zeiger auf Buffer-   */
                                                    /* anfang setzen        */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_StrukturAkt                  Datum: 24.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion bertrgt die Zeichen des Buffers      บ
  บ                    ฏawBuffer_mฎ in die TEXTBOX-Struktur des zuletzt    บ
  บ                    genderten Textes.                                  บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - awBuffer_m (R)                                   บ
  บ                     - pTBold_m (R)                                     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_StrukturAkt(VOID)
{
    PCHAR pcZiel   = pTB_m->acText;                 /* Hilfszeiger          */
    PWORD pwQuelle = awBuffer_m;

    for (; pwQuelle <= pwBufferE_m;)
        *pcZiel++ = (CHAR) *pwQuelle++;             /* Text in die Struktur */
                                                    /* eintragen            */

    *pcZiel = '\0';                                 /* Zeichenkette mit '\0'*/
                                                    /* abschlieแen          */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_TextboxAkt                   Datum: 24.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wSpalte   Absolute Startspalte               บ
  บ                    PWORD  pwFirst   Zeiger auf erstes auszugebendes    บ
  บ                                     Zeichen                            บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion aktualisiert den Inhalt der Textbox    บ
  บ                    auf dem Bildschirm. Sie gibt dazu ab der durch      บ
  บ                    ฏwSpalteฎ bestimmten Position Zeichen des Editier-  บ
  บ                    buffers ฏawBuffer_m[]ฎ in dem Textfenster aus.      บ
  บ                    Die Funktion beendet die Ausgabe wenn sie den       บ
  บ                    rechten Rand der Textbox erreicht hat.              บ
  บ                    Die aufrufende Funktion muแ sicherstellen, daแ      บ
  บ                    der Buffer nicht ber sein Ende hinaus ausgegeben   บ
  บ                    wird.                                               บ
  บ                                                                        บ
  บ  Rckgabewert:     Die Funktion hat keinen Rckgabewert.               บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - awBuffer_m[]  (R)                                บ
  บ                     - pTB_m (W)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_TextboxAkt( WORD wSpalte, PWORD pwFirst)
{
    WORD  wStatus;

    wStatus = MsmCursorOff();

    VioSb2w(wSpalte,
            pTB_m->wFensterZ,
            pTB_m->wFensterB-(wSpalte-pTB_m->wFensterS),
            1,
            pwFirst);

    if (wStatus == MSM_WAR_AN && wMausda_g)
        MsmCursorOn();
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_SchiebeTextsegment           Datum: 19.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        SWORD  wRichtung  Richtung in die geschoben werden  บ
  บ                                      soll:                             บ
  บ                                                                        บ
  บ                                        RECHTS: nach rechts schieben    บ
  บ                                        LINKS:  nach links schieben     บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion verschiebt den Textbereich von         บ
  บ                    der aktuellen Cursorposition bis zum Textende.      บ
  บ                    Die Bewegungsrichtung wird durch das Vorzeichen     บ
  บ                    des Parameters ฏwRichtungฎ gewhlt.                 บ
  บ                    Wenn der Textbereich nach rechts geschoben wird,    บ
  บ                    lแt die Funktion das Zeichen an der aktuellen      บ
  บ                    Cursorposition unverndert. Der Textbereich kann    บ
  บ                    das Ende des Buffers nicht berschreiten.           บ
  บ                    Beim Linksschieben werden die Zeichen an der ak-    บ
  บ                    tuellen Cursorposition verschluckt.                 บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - awBuffer_m (W)                                   บ
  บ                     - pwBufferC_m (W)                                  บ
  บ                     - pwBufferE_m (W)                                  บ
  บ                     - pTB_m (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_SchiebeTextsegment( SWORD wRichtung )
{
    PWORD pwTemp = NULL;                            /* Hilfszeiger          */
    WORD  wAttri   = pTB_m->wAttri << 8;            /* Textattribut         */

    if ( wRichtung == RECHTS &&                     /* nach rechts schieben */
         pwBufferC_m <= pwBufferE_m &&
         pwBufferE_m - awBuffer_m < pTB_m->wMaxL )
    {
        pwBufferE_m++;                              /* Zeiger aktualisieren */

        for ( pwTemp = pwBufferE_m;
              pwTemp > pwBufferC_m;
              pwTemp-- )
            *pwTemp = *(pwTemp -1);                 /* Text verschieben     */

    }
    if ( wRichtung == LINKS &&                      /* nach links schieben  */
         pwBufferC_m <= pwBufferE_m )
    {
        for ( pwTemp = pwBufferC_m;
              pwTemp < pwBufferE_m;
              pwTemp++)
            *pwTemp = *(pwTemp + 1);                /* Text verschieben     */

        *pwTemp = wAttri |= ' ';                    /* Leerzeichen anhngen */

        pwBufferE_m--;                              /* Zeiger aktualisieren */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_BewegeCursor                 Datum: 24.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        SWORD  wRichtung  Richtung in die der Cursor be-    บ
  บ                                      wegt werden soll:                 บ
  บ                                        RECHTS : nach rechts bewegen    บ
  บ                                        LINKS  : nach links bewegen     บ
  บ                                        HOME   : Textanfang             บ
  บ                                        ENDE   : Textende               บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion bewegt den Cursor innerhalb der Text-  บ
  บ                    box. Die Bewegungsrichtung wird durch den Parameter บ
  บ                    ฏwRichtungฎ gewhlt.                                บ
  บ                    Wenn sich der Cursor an einem der Rnder der Box    บ
  บ                    befindet, wird der Text gescollt.                   บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - awBuffer_m (W)                                   บ
  บ                     - pwBufferC_m (W)                                  บ
  บ                     - pwBufferE_m (W)                                  บ
  บ                     - pTB_m (R)                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_BewegeCursor( SWORD wRichtung )
{
  if (wRichtung == RECHTS)
  {
    if (pTB_m->wCursorS < pTB_m->wFensterS          /* kann der Cursor in   */
                           + pTB_m->wFensterB       /* der Textbox bewegt   */
                           - 1)                     /* werden ?             */
    {
      pwBufferC_m++;
      VioSetCursorPos(++pTB_m->wCursorS,            /* Cursor nach rechts   */
                      pTB_m->wFensterZ);            /* bewegen              */
    }
    else if (pwBufferC_m < awBuffer_m +             /* scrollen m”glich?    */
                           pTB_m->wMaxL)
    {
      pwBufferC_m++;
      i_TextboxAkt( pTB_m->wFensterS,
                    pwBufferC_m-pTB_m->wFensterB+1 );
    }
  }
  if (wRichtung == LINKS)
  {
    if (pTB_m->wCursorS > pTB_m->wFensterS)
    {
      pwBufferC_m--;
      VioSetCursorPos(--pTB_m->wCursorS,            /* Cursor nach links    */
                      pTB_m->wFensterZ);            /* bewegen              */
    }
    else if (pwBufferC_m >awBuffer_m)               /* scrollen m”glich ?   */
    {
      pwBufferC_m--;
      i_TextboxAkt( pTB_m->wFensterS,
                    pwBufferC_m );
    }
  }
  if (wRichtung == HOME)
  {
    pwBufferC_m = awBuffer_m;                       /* Cursor an Bufferan   */
    pTB_m->wCursorS = pTB_m->wFensterS;             /* fang setzen          */

    VioSetCursorPos(pTB_m->wCursorS,                /* und positionieren    */
                    pTB_m->wFensterZ);

    i_TextboxAkt( pTB_m->wFensterS,
                  pwBufferC_m );
  }
  if (wRichtung == ENDE)
  {
    pwBufferC_m = pwBufferE_m +1;                   /* Cursor an Bufferende */

    if ( pwBufferE_m - awBuffer_m >                 /* Ist der Text gr”แer  */
         pTB_m->wFensterB )                         /* als das Textfenster? */
    {
      pTB_m->wCursorS = pTB_m->wFensterS +          /* Cursor ans Fenster-  */
                           pTB_m->wFensterB -1;     /* ende setzen          */

      i_TextboxAkt( pTB_m->wFensterS,
                    pwBufferC_m-pTB_m->wFensterB+1 );
    }
    else
    {
      pTB_m->wCursorS = pTB_m->wFensterS +          /* Cursor ans Textende  */
                           pwBufferE_m -            /* setzen               */
                           awBuffer_m +1;

      i_TextboxAkt( pTB_m->wFensterS,
                    awBuffer_m );
    }

    VioSetCursorPos(pTB_m->wCursorS,                /* Cursor positionieren   */
                    pTB_m->wFensterZ);
  }
}
