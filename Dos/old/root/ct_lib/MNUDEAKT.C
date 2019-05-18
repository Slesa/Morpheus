/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuDeaktivieren                Datum: 12.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion deaktiviert das derzeit aktive       บ
  บ                    Men. Der beim Aufruf von MnuAktivieren()           บ
  บ                    gesicherte Inhalt der von Zeile 0 wird wieder       บ
  บ                    auf den Bildschirm ausgegeben und damit die         บ
  บ                    Menzeile berschrieben.                            บ
  บ                    Alle Puffer fr die Menfenster und die Men-       บ
  บ                    zeile werden von dieser Funktion nicht gendert.    บ
  บ                    Sie k”nnen mit einem erneuten Aufruf von            บ
  บ                    MnuAktivieren() die Menzeile wieder anzeigen       บ
  บ                    lassen.                                             บ
  บ                    Rufen Sie nach der Aktivierung die Funktion         บ
  บ                    MnuEingabe() auf, um den Menmanager zu starten     บ
  บ                    und damit dem Anwender die M”glichkeit der          บ
  บ                    Eingabe zu geben.                                   บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  OK/ERROR   OK:    Men wurde deaktiviert      บ
  บ                                     ERROR: derzeit kein Men aktiv     บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - wFehler_g      (W)                                บ
  บ                    - wAktMnu_g      (W/R)                              บ
  บ                    - fawAlteMZ_g[]  (R)                                บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ   (c) copyright 1988,1989 Markt & Technik Verlag AG, Haar bei Mnchen  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <stdio.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD   wFehler_g;        /* Nummer des letzten aufgetretenen Fehlers */
IMPORT WORD   wAktMnu_g;        /* aktueller Index auf Men-Array           */
IMPORT WORD   wMausda_g;        /* Maus im System aktiviert                 */
IMPORT FPWORD fpwAlteMZ_g;      /* Puffer mit altem Inhalt Zeile 0          */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MnuDeaktivieren(VOID)
{
    WORD wMausStatus;

    if (wAktMnu_g == NICHT_INIT)                    /* kein Men aktiv      */
        return(ERROR);

    if (fpwAlteMZ_g != NULL)
    {
        if ( wMausda_g)                             /* wenn Maus aktiv      */
             wMausStatus = MsmCursorOff();          /* Zeiger ausschalten   */

        VioSb2w( 0, 0, 80, 1, fpwAlteMZ_g );        /* alten Inhalt zeigen  */

        if ( wMausda_g &&                           /* wenn Maus da und     */
             wMausStatus == MSM_WAR_AN)             /* Zeiger an war,       */
            MsmCursorOn();                          /* wieder einschalten   */
    }

    wAktMnu_g = NICHT_INIT;                         /* Index neu setzen     */
    return(OK);
}

