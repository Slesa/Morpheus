/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinPrintf                      Datum: 13.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        const PCHAR     pcFormat[[,Argument]]...            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion arbeitet hnlich wie die Funktion    บ
  บ                    printf() der Laufzeitbibliothek. Mit ihr wird       บ
  บ                    eine formatierte Ausgabe in einem Fenster erm”g-    บ
  บ                    licht, wobei das Argument ฏpcFormatฎ dieselbe Form  บ
  บ                    und Bedeutung hat wie ฏformatฎ bei der printf()-    บ
  บ                    Funktion (siehe Referenzteil).                      บ
  บ                    Die Zeichenkette kann bis zu 512 Zeichen lang       บ
  บ                    sein.                                               บ
  บ                    Die Ausgabe beginnt bei der aktuellen Position des  บ
  บ                    Cursors im aktiven Fenster. Die Funktion fhrt bei  บ
  บ                    Bedarf einen Zeilenumbruch aus. Ein Zeilenumbruch   บ
  บ                    in der letzten Zeile l”st ein Scrollen des Windows  บ
  บ                    aus.                                                บ
  บ                    Wenn sich im System eine Maus befindet und der      บ
  บ                    Mauscursor sichtbar ist, wird er fr die Dauer      บ
  บ                    der IO-Operation ausgeschaltet.                     บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD     Die Anzahl der geschriebenen Zeichen       บ
  บ                             ohne '\0' oder ein negativer Wert,         บ
  บ                             wenn ein Fehler auftritt.                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wMausda_g (R)                                   บ
  บ                      - wS_g (R)                                        บ
  บ                      - wZ_g (R)                                        บ
  บ                      - wH_g (R)                                        บ
  บ                      - wB_g (R)                                        บ
  บ                      - wTabs_m (R)                                     บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <stdio.h>            /* fr vsprintf()                             */
#include <stdarg.h>           /* ANSI-C Standard fr va_start(), va_end()   */
#include <conio.h>            /* fr putch()                                */

#include <ctools.h>           /* Einbinden aller Toolbox Header-Dateien     */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          GLOBALE VARIABLEN                             บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT  WORD    wMausda_g;                          /* 0: keine Maus da     */

IMPORT  WORD    wS_g;                               /* Die Koordinaten be-  */
IMPORT  WORD    wZ_g;                               /* schreiben die Data-  */
IMPORT  WORD    wB_g;                               /* Area des aktuellen   */
IMPORT  WORD    wH_g;                               /* Windows.             */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL CHAR  acBuffer_m[512];
MGLOBAL WORD  wTabs_m = 4;                          /* Tabulator-Abstand    */
MGLOBAL VOID  i_WinPrintfFilter(PSTR);


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
SWORD WinPrintf(const PCHAR pcFormat,...)
{
    SWORD    wReturn;
    WORD     wSpalte, wZeile, wStatus, wDummy;
    va_list  arg_zeiger;

    VioGetCursor(&wSpalte, &wZeile,                 /* absol. Position des  */
                 &wDummy, &wDummy);                 /* Cursors bestimmen.   */

    wSpalte -= wS_g;                                /* in relative Koordi-  */
    wZeile  -= wZ_g;                                /* naten umwandeln      */

    if ( !WinKoordInDA(wSpalte,wZeile) )            /* Koord. auแerhalb ?   */
        return (-1);                                /* zurck an aufr. Fkt. */

    va_start(arg_zeiger, pcFormat);                 /* Arg.-zeiger setzen   */

    wReturn = vsprintf(acBuffer_m,pcFormat,         /* Ausgabe in Buffer    */
                       arg_zeiger);                 /* vornehmen            */

    if (wReturn > 0)                                /* Zeichen in Buffer ?  */
    {
        if (wMausda_g)                              /* wenn Maus im System, */
            wStatus = MsmCursorOff();               /* Maus ausschalten.    */

        i_WinPrintfFilter(acBuffer_m);              /* ฏacBuffer_mฎ ausgeb. */

        if (wMausda_g && wStatus == MSM_WAR_AN)     /* wenn Maus sichtbar   */
            MsmCursorOn();                          /* war, Maus anzeigen   */
    }

    va_end(arg_zeiger);                             /* Zeiger auf NULL      */
    acBuffer_m[0] = '\0';                           /* Buffer l”schen       */

    return (wReturn);                               /* Zeichenanzahl zurck */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_WinPrintfFilter              Datum: 13.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR  pstrBuffer   Zeiger auf eine Zeichenkette     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion bernimmt die Ausgabe der Zeichen-   บ
  บ                    kette.                                              บ
  บ                                                                        บ
  บ  Rckgabewert:     keinen                                              บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
VOID i_WinPrintfFilter( PSTR pstrBuffer )
{
    REGISTER i;
    WORD     wSpalteAbs, wZeileAbs, wDummy;

    VioGetCursor(&wSpalteAbs, &wZeileAbs,           /* absol. Position des  */
                 &wDummy, &wDummy);                 /* Cursors bestimmen.   */

    for (; *pstrBuffer; pstrBuffer++)               /* Ausgabe der Zeichenk.*/
    {
        switch(*pstrBuffer)
        {
            case '\a':
                UtlBeep();
                break;

            case '\b':
                if (wSpalteAbs > wS_g)              /* wenn Cursor nicht in */
                    VioSetCursorPos(--wSpalteAbs,   /* Spalte 0, Cursor     */
                                      wZeileAbs);   /* eins nach links      */
                break;

            case '\r':
                wSpalteAbs = wS_g;
                VioSetCursorPos(wSpalteAbs,         /* Cursor in Spalte ฏ0ฎ */
                                wZeileAbs);
                break;

            case '\t':
                for (i = wTabs_m; i > 0; i--)
                        WinPutch(' ');              /* Leerzeichen ausgeben */
                VioGetCursor(&wSpalteAbs,           /* absol. Position des  */
                             &wZeileAbs,            /* Cursors bestimmen.   */
                             &wDummy, &wDummy);
                break;

            case '\n':
                wSpalteAbs = wS_g;
                if (wZeileAbs == wZ_g + wH_g -1)    /* C. in letzter Zeile? */
                    WinScrollUp(1);
                else
                    wZeileAbs++;
                VioSetCursorPos(wSpalteAbs,
                                wZeileAbs);
                break;

            case '\f':
            case '\v':
                break;                              /* Zeichen rausfiltern  */

            default:
                VioSz(wSpalteAbs, wZeileAbs,        /* Zeichen schreiben    */
                      *pstrBuffer);

                if ( ++wSpalteAbs == wS_g+wB_g )    /* rech. Rand erreicht? */
                {
                    wSpalteAbs = wS_g;
                    wZeileAbs++;
                }
                if ( wZeileAbs == wZ_g+wH_g )       /* letzte Z. erreicht?  */
                {
                    WinScrollUp(1);                 /* nach oben scrollen   */
                    wZeileAbs--;                    /* Cursor korrigieren   */
                }
                break;

        } /* end of switch */
    } /* end of for */

    VioSetCursorPos(wSpalteAbs, wZeileAbs);         /* Cursor positionieren */

} /* end of i_WinPrintfFilter */




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    WinTabsAbstand                 Datum: 19.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wTababstand                                  บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion wird die Anzahl der Leer-       บ
  บ                    zeichen festgelegt, die bei der Funktion            บ
  บ                    WinPrintf() fr die Escape-Sequenz '\t' ersetzt     บ
  บ                    wird.                                               บ
  บ                                                                        บ
  บ                    Wenn der Funktion eine Null bergeben wird,         บ
  บ                    bleibt der aktuelle Tabulatorschritt erhalten. Die  บ
  บ                    Funktion gibt dann nur den aktuellen Wert zurck.   บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD   aktueller Tabulatorabstand                   บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wTabs_m (R/W)                                       บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD WinTabsAbstand(WORD wTababstand)
{
    if (wTababstand != 0)
        wTabs_m = wTababstand;
    return(wTabs_m);
}



