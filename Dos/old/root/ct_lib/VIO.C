/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                                                                        บ
  บ   Dateiname: vio.c                                                     บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ   Dieses Modul enthlt Routinen zur Untersttzung des Bildschirms      บ
  บ   im 80*25 Textmodus.                                                  บ
  บ                                                                        บ
  บ   Die Routinen greifen direkt auf den Bildschirmspeicher zu. Dadurch   บ
  บ   wird eine maximale Geschwindigkeit erreicht.                         บ
  บ                                                                        บ
  บ   Aus Geschwindigkeitsgrnden findet keinerlei berprfung der Koor-   บ
  บ   dinaten auf eine Bereichsberschreitung statt, eine berschreitung   บ
  บ   der Bildschirmgrenzen kann zu nicht voraussagbaren Ergebnissen       บ
  บ   fhren.                                                              บ
  บ                                                                        บ
  บ   Die Prototypen aller Funktionen und die symbolischen Konstanten      บ
  บ   finden Sie in der Deklarations-Datei ฏctvideo.hฎ.                    บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ


  ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                                                                        บ
  บ   Namensvergabe:  Vio(1)(2)(Parameter)                                 บ
  บ                                                                        บ
  บ                                                                        บ
  บ                  (1)  Legt die Zugriffsart fest:                       บ
  บ                       L  = lesen                                       บ
  บ                       S  = schreiben                                   บ
  บ                                                                        บ
  บ                  (2)  Legt das Element fest:                           บ
  บ                       z   = Zeichen                                    บ
  บ                       a   = Attribut                                   บ
  บ                       za  = Zeichen und Attribut                       บ
  บ                                                                        บ
  บ                       s   = String                                     บ
  บ                       sa  = String mit Attribut                        บ
  บ                                                                        บ
  บ                       pz  = kompletter Bildschirm (page) mit Zeichen   บ
  บ                       pa  = kompletter Bildschirm mit Attribut         บ
  บ                       pza = kompletter Bildschirm mit Zeichen          บ
  บ                                                   und Attribut         บ
  บ                                                                        บ
  บ                       wz  = Bildschirmfenster (window) mit Zeichen     บ
  บ                       wa  = Bildschirmfenster mit Attribut             บ
  บ                       wza = Bildschirmfenster mit Zeichen und Attribut บ
  บ                       b2w = Buffer nach Bildschirmfenster              บ
  บ                       w2b = Bildschirmfenster nach Buffer              บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
 
 
 
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          HEADER - DATEIEN                              บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <dos.h>
#include <TYPEDEFS.H>
#include <INTERRPT.H>
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_VIDEO_HEADER
#include <ctvio.h>
#endif

 
#pragma check_pointer(off)

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Modulglobale Variablen fr die Startadresse des Bildschirmspeichers   บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL WORD        wInit_m  = 0;                   /* Initial.-Flag        */
MGLOBAL WORD        wModus_m = 0;                   /* Grafik-Modus         */

MGLOBAL WORD        wZugriffsSeite_m = 0;           /* Schreib-Lese-Seite   */
MGLOBAL WORD        wAnzeigeSeite_m  = 0;           /* sichtbare Seite      */

MGLOBAL FPWORD      fpwScreen_m = 0L;               /* fr Wort-Zugriffe    */
MGLOBAL FPWORD      fpwTmp_m    = 0L;
MGLOBAL FPCHAR      fpcScreen_m = 0L;               /* fr Char-Zugriffe    */
MGLOBAL FPCHAR      fpcTmp_m    = 0L;
MGLOBAL FPBYTE      fpbScreen_m = 0L;               /* fr Byte-Zugriffe    */
MGLOBAL FPBYTE      fpbTmp_m    = 0L;



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSeite                       Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wWahl       ANZEIGE / SCHREIB_LESE / INITIAL  บ
  บ                    WORD  wSeite      gewnschte Bildschirmseite        บ
  บ                                                                        บ
  บ  Beschreibung:     Bei bergabe von ฏANZEIGEฎ wird die gewnschte      บ
  บ                    Bildschirmseite angezeigt. M”gliche Seiten:         บ
  บ                                                                        บ
  บ                        Modus                Seiten                     บ
  บ                                                                        บ
  บ                         0,1                  0..7    (CGA)             บ
  บ                         2,3                  0..3    (CGA)             บ
  บ                                              0..7    (EGA)             บ
  บ                         4,5,6,7,8,9,A        keine                     บ
  บ                         D                    0..7    (EGA)             บ
  บ                         E                    0..3    (EGA)             บ
  บ                         F                    0..1    (EGA)             บ
  บ                         10h                  0..1    (EGA)             บ
  บ                                                                        บ
  บ                    Im Modus ฏSCHREIB_LESEฎ weist die Funktion den      บ
  บ                    modul-globalen Variablen                            บ
  บ                                                                        บ
  บ                          FPWORD    fpwScreen_m                         บ
  บ                          FPCHAR    fpcScreen_m                         บ
  บ                          FPBYTE    fpbScreen_m                         บ
  บ                                                                        บ
  บ                    die Anfangsadresse der gewnschten Bildschirmseite  บ
  บ                    zu. Bei bergabe von ฏINITIALฎ wird die gewnschte  บ
  บ                    Seite angezeigt und ihre Anfangsadresse den drei    บ
  บ                    Variablen zugewiesen.                               บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R/W)                                   บ
  บ                      - wModus_m (R/W)                                  บ
  บ                      - wZugriffsSeite_m (W)                            บ
  บ                      - fpcScreen_m (W)                                 บ
  บ                      - fpwScreen_m (W)                                 บ
  บ                      - fpbScreen_m (W)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSeite( WORD wWahl,
               WORD wSeite )
{
    union REGS regs;

    wAnzeigeSeite_m = wSeite;

    if ( (wWahl==ANZEIGE) || (wWahl==INITIAL) )
    {
        regs.h.ah = SEL_ACTIVE_PAGE;                /* Funktionsnummer      */
        regs.h.al = (BYTE) wAnzeigeSeite_m;
        Interrupt(0x10, &regs);                  /* Interrupt ausl”sen   */
    }

    if ( (wWahl==SCHREIB_LESE) || (wWahl==INITIAL) )
    {
        if (!wInit_m)
        {
            wModus_m = VioGetMode();                /* Modus ermitteln      */
            wInit_m  = 1;                           /* Flag setzen          */
        }
        wZugriffsSeite_m = wAnzeigeSeite_m;

        if (wModus_m == 7)                          /* Monochrom-Monitor    */
        {
//#ifdef NEVER
            fpwScreen_m =  (FPWORD) MK_PTR( MONO_SEG, 0x1000 * wAnzeigeSeite_m );
#ifdef NEVER
	    fpwScreen_m =  (FPWORD) MK_PTR( 0xB000, 0x0000 );
#endif
	    fpbScreen_m =  (FPBYTE) fpwScreen_m;
	    fpcScreen_m =  (FPCHAR) fpwScreen_m;
        }
        else                                        /* Farbmonitor          */
        {
            fpwScreen_m =  (FPWORD) MK_PTR( COLOR_SEG, 0x1000 * wAnzeigeSeite_m );
#ifdef NEVER
	    fpwScreen_m =  (BYTE*)MK_PTR( 0xB800, 0x0000 );
#endif
	    fpbScreen_m =  (FPBYTE) fpwScreen_m;
	    fpcScreen_m =  (FPCHAR) fpwScreen_m;
        }
    }
}

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSa                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                    WORD wAttr       gewnschtes Attribut               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ndert das Attribut fr das Zeichen, บ
  บ                    das durch die bergebenen Koordinaten festgelegt    บ
  บ                    wird. Das Zeichen wird nicht verndert.             บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpbScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSa( WORD wSpalte,
            WORD wZeile,
            WORD wAttr )
{

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    *(fpbScreen_m+((wZeile*80+wSpalte)<<1)+1) = (BYTE) wAttr;
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioLa                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespal             บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt das Attribut des Zeichens  บ
  บ                    an der bergebenen Bildschirmposition.              บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  ermitteltes Attribut                          บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpbScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD VioLa(WORD wSpalte,
           WORD wZeile )
{

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    return(*(fpbScreen_m+((wZeile*80+wSpalte)<<1)+1));
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSz                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                    CHAR cZeichen    gewnschtes Zeichen                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion schreibt ein Zeichen an die mit      บ
  บ                    wSpalte, wZeile bestimmte Position.                 บ
  บ                    Das aktuelle Attribut wird nicht verndert.         บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpcScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSz ( WORD wSpalte,
             WORD wZeile,
             CHAR cZeichen )
{

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    *(fpcScreen_m+((wZeile*80+wSpalte)<<1)) = cZeichen;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioLz                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt das Zeichen an der ber-   บ
  บ                    gebenen Bildschirmposition.                         บ
  บ                                                                        บ
  บ  Rckgabewert:     CHAR  ermitteltes Zeichen                           บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpcScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
CHAR VioLz ( WORD wSpalte,
             WORD wZeile )
{

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    return(*(fpcScreen_m+((wZeile*80+wSpalte)<<1)));
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSza                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte       gewnschte Ausgabespalte         บ
  บ                    WORD wZeile        gewnschte Ausgabezeile          บ
  บ                    CHAR cZeichen      gewnschtes Zeichen              บ
  บ                    WORD wAttr         gewnschtes Attribut             บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion schreibt ein Zeichen mit Attribut    บ
  บ                    an die mit wSpalte, wZeile bestimmte Bildschirm-    บ
  บ                    position.                                           บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpwScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSza ( WORD wSpalte,
              WORD wZeile,
              BYTE cZeichen,
              WORD wAttr )
{
    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    *(fpwScreen_m+wZeile*80+wSpalte) = (wAttr<<8) | cZeichen;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioLza                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt das Zeichen mit seinem     บ
  บ                    Attribut an der bergebenen Bildschirmposition.     บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  ermitteltes Attribut und Zeichen (High/Low)   บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpwScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD VioLza(WORD wSpalte,
            WORD wZeile )
{

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    return(*(fpwScreen_m+wZeile*80+wSpalte));
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSs                          Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte     gewnschte Ausgabespalte           บ
  บ                    WORD wZeile      gewnschte Ausgabezeile            บ
  บ                    PSTR pstrQuelle  Zeiger auf Ausgabestring           บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt eine Zeichenkette ab der mit    บ
  บ                    wSpalte, wZeile angegebenen Bildschirmposition aus. บ
  บ                    Die aktuellen Attribute werden bernommen.          บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpcScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSs ( WORD wSpalte,
             WORD wZeile,
             PSTR pstrQuelle )
{
 PSTR        cp = pstrQuelle;
    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */


    fpcTmp_m = fpcScreen_m
              + ((wZeile*80+wSpalte) << 1 );        /* Startadresse         */
    for (; *cp; fpcTmp_m += 2)              /* Ausgabe, solange     */
        *fpcTmp_m = *cp++;                  /* *pstrQuelle != '\0'  */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSsa                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wSpalte    gewnschte Ausgabespalte            บ
  บ                    WORD wZeile     gewnschte Ausgabezeile             บ
  บ                    PSTR pstrQuelle Zeiger auf Zeichenkette             บ
  บ                    WORD wAttr      gewnschtes Attribut                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion gibt einen String im bergebenen     บ
  บ                    Attribut an der mit wSpalte, wZeile bestimmten      บ
  บ                    Bildschirmposition aus.                             บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpcScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSsa ( WORD wSpalte,
              WORD wZeile,
              PSTR pstrQuelle,
              WORD wAttr )
{
 PSTR        cp = pstrQuelle;

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */


    fpcTmp_m = fpcScreen_m +
               ( (wZeile*80+wSpalte) << 1 );        /* Startadresse         */
    while (*cp)
    {
        *fpcTmp_m++ = *cp++;                /* Zeichen schreiben    */
        *fpcTmp_m++ = (CHAR) wAttr;                 /* Attribut schreiben   */
    }
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSpa                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD wAttr       gewnschtes Attribut               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fllt den kompletten Bildschirm-     บ
  บ                    speicher mit dem bergebenem Attribut.              บ
  บ                    Die im Speicher stehenden Zeichen werden nicht      บ
  บ                    verndert.                                          บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpbScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSpa( WORD wAttr)
{
    REGISTER i;

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    fpbTmp_m = fpbScreen_m +1;                      /* Startadresse         */
    for (i=2000; i>0; i--, fpbTmp_m += 2)           /* 2000 Attr. ausgeben  */
        *fpbTmp_m = (BYTE) wAttr;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSpz                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        CHAR cZeichen    gewnschtes Zeichen                บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion beschreibt den kompletten Bild-      บ
  บ                    schirmspeicher mit cZeichen. Die Attribute werden   บ
  บ                    nicht verndert.                                    บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpcScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSpz( CHAR cZeichen)
{
    REGISTER  i;

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */


    fpcTmp_m = fpcScreen_m;                         /* Startadresse         */
    for ( i=2000; i>0; i--, fpcTmp_m += 2)          /* 2000 Zeichen ausgeb. */
        *fpcTmp_m = cZeichen;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSpza                        Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        CHAR cZeichen  gewnschtes Zeichen                  บ
  บ                    WORD wAttr     gewnschtes Attribut                 บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fllt den kompletten Bildschirm-     บ
  บ                    speicher mit dem bergebenen Zeichen im ber-       บ
  บ                    gebenen Attribut.                                   บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpwScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSpza ( CHAR cZeichen,
               WORD wAttr )
{
    REGISTER i,wAundZ;

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    fpwTmp_m = fpwScreen_m;                         /* Startadresse         */
    wAundZ = (wAttr<<8) | cZeichen;                   /* A. und Z. mischen    */
    for (i=0; i<2000; i++)                          /* 2000-mal ausgeben    */
        *fpwTmp_m++ = wAundZ;
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSwa                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    WORD     wAttr           gewnschtes Attribut       บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fllt das komplette Fenster, das     บ
  บ                    durch die Koordinaten der linken oberen Ecke und    บ
  บ                    seiner Ausdehnung in horizontaler und vertikaler    บ
  บ                    Richtung festgelegt wird, mit dem bergebenen       บ
  บ                    Attribut.                                           บ
  บ                    Die im Speicher stehenden Zeichen werden nicht      บ
  บ                    verndert.                                          บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpbScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSwa( WORD wSpalte,
             WORD wZeile,
             WORD wBreite,
             WORD wHoehe,
             WORD wAttr)
{
    REGISTER b,wDelta;

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    wDelta = ( 80-wBreite ) << 1;                   /* Hilfsgr”แe           */
    fpbTmp_m = fpbScreen_m +                        /* Zeiger auf die linke */
                ((wZeile*80+wSpalte)<<1) + 1;       /* obere Ecke           */

    for (;wHoehe>0; wHoehe--, fpbTmp_m += wDelta)   /* Zeilen abarbeiten    */
        for(b=wBreite; b>0; b--, fpbTmp_m += 2)     /* Spalten abarbeiten   */
            *fpbTmp_m = (BYTE) wAttr;               /* Attribut schreiben   */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSwz                         Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    CHAR     cZeichen        gewnschtes Zeichen        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fllt das komplette Fenster, das     บ
  บ                    durch die Koordinaten der linken oberen Ecke und    บ
  บ                    seiner Ausdehnung in horizontaler und vertikaler    บ
  บ                    Richtung festgelegt wird, mit dem bergebenen       บ
  บ                    Zeichen.                                            บ
  บ                    Die im Speicher stehenden Attribute werden nicht    บ
  บ                    verndert.                                          บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpcScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSwz( WORD wSpalte,
             WORD wZeile,
             WORD wBreite,
             WORD wHoehe,
             CHAR cZeichen)
{
    REGISTER b,wDelta;

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    wDelta = (80 - wBreite) << 1;                   /* Hilfsgr”แe           */
    fpcTmp_m = fpcScreen_m +                        /* Zeiger auf die linke */
               ( (wZeile*80 + wSpalte)<<1 );        /* obere Ecke           */

    for (;wHoehe>0; wHoehe--, fpcTmp_m += wDelta)   /* Zeilen abarbeiten    */
        for(b=wBreite; b>0; b--, fpcTmp_m += 2)     /* Spalten abarbeiten   */
            *fpcTmp_m = cZeichen;                     /* Zeichen schreiben    */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSwza                        Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    CHAR     cZeichen        gewnschtes Zeichen        บ
  บ                    WORD     wAttr           gewnschtes Attribut       บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion fllt das komplette Fenster, das     บ
  บ                    durch die Koordinaten der linken oberen Ecke und    บ
  บ                    seiner Ausdehnung in horizontaler und vertikaler    บ
  บ                    Richtung festgelegt wird, mit dem bergebenen       บ
  บ                    Zeichen im bergebenen Attribut.                    บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpwScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSwza( WORD wSpalte,
              WORD wZeile,
              WORD wBreite,
              WORD wHoehe,
              CHAR cZeichen,
              WORD wAttr)
{
    REGISTER b,wDelta,wAundZ;


    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    wAundZ = (wAttr<<8) | (cZeichen&0xFF);                   /* A. und Z. mischen    */
    wDelta = 80 - wBreite;                          /* Hilfsgr”แe           */
    fpwTmp_m = fpwScreen_m + (wZeile*80) + wSpalte;   /* Zeiger auf die linke */
                                                    /* obere Ecke           */
    for (;wHoehe>0; wHoehe--, fpwTmp_m += wDelta)   /* Zeilen abarbeiten    */
        for(b=wBreite; b>0; b--)                    /* Spalten abarbeiten   */
            *fpwTmp_m++ = wAundZ;                   /* Z. und A. schreiben  */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSb2w                        Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    FPWORD   fpwQuelle       Zeiger auf Buffer          บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion schreibt den Inhalt des Buffers, auf   บ
  บ                    den der Zeiger ฏfpwQuelleฎ zeigt, in ein Fenster,   บ
  บ                    das durch die Koordinaten seiner linken oberen Ecke บ
  บ                    und seiner Ausdehnung in horizontaler und verti-    บ
  บ                    kaler Richtung festgelegt werden kann. Das Fenster  บ
  บ                    wird zeilenweise aus dem Buffer gelesen.            บ
  บ                    Der Benutzer muแ dafr sorgen, daแ der Buffer sinn- บ
  บ                    volle Daten enthlt.                                บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpwScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSb2w ( WORD     wSpalte,
               WORD     wZeile,
               WORD     wBreite,
               WORD     wHoehe,
               FPWORD   fpwQuelle)
{
    REGISTER b,wDelta;

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    wDelta = 80 - wBreite;                          /* Hilfsgr”แe           */
    fpwTmp_m = fpwScreen_m + wZeile*80 + wSpalte;   /* Zeiger auf die linke */
                                                    /* obere Ecke           */
    for (;wHoehe>0; wHoehe--, fpwTmp_m += wDelta)   /* Zeilen abarbeiten    */
        for(b=wBreite; b>0; b--)                    /* Spalten abarbeiten   */
            *fpwTmp_m++ = *fpwQuelle++;             /* Z. und A. in den     */
                                                    /* Bildschirm schreiben */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSw2b                        Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD     wSpalte         Spalte oben links          บ
  บ                    WORD     wZeile          Zeile oben links           บ
  บ                    WORD     wBreite         Breite des Fensters        บ
  บ                    WORD     wHoehe          H”he des Fensters          บ
  บ                    FPWORD   fpwZiel         Zeiger auf Buffer          บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion schreibt den Inhalt des Fensters, das  บ
  บ                    durch die Koordinaten seiner linken oberen Ecke und บ
  บ                    seiner Ausdehnung in horizontaler und vertikaler    บ
  บ                    Richtung festgelegt werden kann, in einen Buffer,   บ
  บ                    auf den der Zeiger ฏfpwZielฎ zeigt. Das Fenster     บ
  บ                    wird zeilenweise in dem Buffer abgelegt.            บ
  บ                    Der Benutzer muแ dafr sorgen, daแ der Buffer groแ  บ
  บ                    genug ist, um das Fenster aufzunehmen.              บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m (R)                                     บ
  บ                      - fpwScreen_m (R)                                 บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSw2b ( WORD     wSpalte,
               WORD     wZeile,
               WORD     wBreite,
               WORD     wHoehe,
               FPWORD   fpwZiel)
{
    REGISTER b,wDelta;

    if (!wInit_m)                                   /* Zeiger initial. ?    */
        VioSeite(INITIAL,0);                        /* Zeiger auf Seite ฏ0ฎ */

    wDelta = 80 - wBreite;                          /* Hilfsgr”แe           */
    fpwTmp_m = fpwScreen_m + wZeile*80 + wSpalte;   /* Zeiger auf die linke */
                                                    /* obere Ecke.          */
    for (;wHoehe>0; wHoehe--, fpwTmp_m += wDelta)   /* Zeilen abarbeiten    */
        for(b=wBreite; b>0; b--)                    /* Spalten abarbeiten   */
            *fpwZiel++ = *fpwTmp_m++;               /* Z. und A. in Buffer  */
                                                    /* schreiben.           */
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSetMode                     Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wWahlmodus   gewschter Bildschirmmodus      บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion legt mit einem Aufruf des INT 0x10   บ
  บ                    den Video-Modus fest.                               บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert.             บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wInit_m  (W)                                    บ
  บ                      - wModus_m (R)                                    บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSetMode (WORD wWahlmodus)
{
    union REGS regs;

    regs.h.ah = SET_VIDEO_MODE;                     /* Funktionsnummer      */
    regs.h.al = (BYTE) wWahlmodus;
    Interrupt(0x10, &regs);

    wModus_m  = wWahlmodus;                         /* neuen Modus speich.  */
    wInit_m = 0;                                    /* Screen-Zeiger mssen */
                                                    /* neu initial. werden  */
}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioGetMode                     Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt durch einen Aufruf des     บ
  บ                    INT 0x10 den aktuellen Video-Modus.                 บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD    aktueller Modus                             บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
WORD VioGetMode (VOID)
{
    union REGS regs;

    regs.h.ah = GET_VIDEO_MODE;                     /* Funktionsnummer      */
    Interrupt(0x10, &regs);

    return( (WORD) regs.h.al );
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSetCursorTyp                Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wStart     Startscanzeile des Cursors        บ
  บ                    WORD   wStop      Stopscanzeile des Cursors         บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion wird die Gr”แe des Cursors      บ
  บ                    festgelegt.                                         บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSetCursorTyp (WORD wStart,
                      WORD wStop)
{
    union REGS regs;

    regs.h.ah = SET_CURSOR_TYPE;                    /* Funktionsnummer      */
    regs.h.ch = (BYTE) wStart;
    regs.h.cl = (BYTE) wStop;
    Interrupt(0x10, &regs);
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioSetCursorPos                Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD   wSpalte      Bildschirmspalte                บ
  บ                    WORD   wZeile       Bildschirmzeile                 บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion positioniert den Cursor in der         บ
  บ                    angezeigten Bildschirmseite.                        บ
  บ                                                                        บ
  บ  Rckgabewert:     Diese Funktion hat keinen Rckgabewert              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    - wAnzeigeSeite_m (R)                             บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioSetCursorPos( WORD wSpalte,
                      WORD wZeile)
{
    union REGS regs;

    _POS_CURSOR(wSpalte,wZeile,wAnzeigeSeite_m);    /* Setzen per Makro     */
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    VioGetCursor                   Datum: 11.09.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PWORD  pwSpalte    Bildschirmspalte                 บ
  บ                    PWORD  pwZeile     Bildschirmzeile                  บ
  บ                    PWORD  pwStart     Startscanzeile des Cursor        บ
  บ                    PWORD  pwStop      Stopscanzeile des Cursor         บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ermittelt fr die angezeigte Seite   บ
  บ                    folgende Information ber den Cursor:               บ
  บ                                                                        บ
  บ                        Position    - Spalte                            บ
  บ                                    - Zeile                             บ
  บ                        Gr”แe       - Startscanzeile                    บ
  บ                                    - Stopscanzeile                     บ
  บ                                                                        บ
  บ  Rckgabewert:     Die ermittelten Werte werden an die von der         บ
  บ                    aufrufenden Funktion angegebenen Adressen ber-     บ
  บ                    geben.                                              บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):    -  wAnzeigeSeite_m (R)                            บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID VioGetCursor( PWORD  pwSpalte,
                   PWORD  pwZeile,
                   PWORD  pwStart,
                   PWORD  pwStop)
{
    union REGS regs;

    regs.h.ah = READ_CURSOR_POS;                    /* Funktionsnummer      */
    regs.h.bh = (BYTE) wAnzeigeSeite_m;
    Interrupt(0x10, &regs);

    *pwSpalte = regs.h.dl;
    *pwZeile  = regs.h.dh;
    *pwStart  = regs.h.ch;
    *pwStop   = regs.h.cl;
}

