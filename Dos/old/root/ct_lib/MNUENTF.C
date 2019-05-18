/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    MnuEntfernen                   Datum: 26.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wMenuNr    Nummer des Mens                   บ
  บ                                                                        บ
  บ  Beschreibung:     Mit dieser Funktion wird ein beliebiges Men        บ
  บ                    entfernt. Sie sollten diese Funktion aufrufen,      บ
  บ                    bevor Sie Ihr Programm beenden.                     บ
  บ                    Durch die Funktion wird smtlicher allokierter      บ
  บ                    Speicherplatz fr die Strukturen und die Puffer     บ
  บ                    fr die Menfenster und Menzeile freigegeben.      บ
  บ                    Wenn wMenuNr die Nummer des derzeit aktiven Mens   บ
  บ                    ist, wird zustzlich die Funktion MnuDeaktivieren() บ
  บ                    aufgerufen, um den vollstndigen Bildschirm wieder  บ
  บ                    in seinen Ursprungszustand zu versetzen.            บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation OK/ERROR                    บ
  บ                          im Fehlerfall wird die globale Variable       บ
  บ                          wFehler_g mit der Fehlernummer geladen        บ
  บ                          MNU_NICHT_REG  ein Men mit dieser Nummer     บ
  บ                                         existiert nicht                บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wFehler_g   (W)                                     บ
  บ                    aMenus_g    (R/W)                                   บ
  บ                    wAktMnu_g   (R)                                     บ
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

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wFehler_g;          /* Nummer des letzten aufgetretenen Fehlers */
IMPORT WORD wAktMnu_g;          /* aktueller Index auf Men-Array           */
IMPORT MENU aMenus_g[];         /* Array auf alle Mens                     */


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD MnuEntfernen(WORD wMenuNr)
{
    PMKB pMkbTmp;

    if (aMenus_g[wMenuNr].pMkbStart == NULL)        /* kein Menfenster     */
    {                                               /* eingerichtet         */
        wFehler_g = MNU_NICHT_REG;                  /* Fehlernummer laden   */
        return(ERROR);                              /* und zurck           */
    }

    if (wMenuNr == wAktMnu_g)                       /* Men aktiv ?         */
        MnuDeaktivieren();                          /* dann deaktivieren    */

    UtlFfree(aMenus_g[wMenuNr].fpwMzBuffer);        /* Menzeilen-Puffer    */
                                                    /* freigeben            */

    pMkbTmp = aMenus_g[wMenuNr].pMkbStart;          /* Adresse erster MKB   */
                                                    /* dieses Mens         */

    do
    {
        if (pMkbTmp->wMkbsign != MKBSIGNATUR)       /* zeigt pMkb auf MKB ? */
            i_Fehler(I_FEHLER_SIGN, "MnuEntfernen()",
                     __FILE__, __LINE__);

        UtlFree( pMkbTmp->pHotkeys );               /* Speicher freigeben,  */
        UtlFfree( pMkbTmp->fpwBuffer );             /* deren Zeiger in MKB  */
        pMkbTmp = pMkbTmp->pNaechster;              /* nchsten holen       */
        UtlFree( pMkbTmp->pVoriger );               /* vorigen freigeben    */
    } while (pMkbTmp != aMenus_g[wMenuNr].pMkbStart);

    aMenus_g[wMenuNr].pMkbStart = NULL;             /* aMenus_g wieder auf  */
                                                    /* NULL setzen          */
    return(OK);
}
