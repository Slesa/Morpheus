/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_Fehler                       Datum: 16.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wFehlerNr          Art des Fehlers            บ
  บ                    PSTR  pstrFunktion       Funktion, in der der       บ
  บ                                             Fehler                     บ
  บ                    PSTR  pstrDateiname      Dateiname der Funktion     บ
  บ                    WORD  wZeile             Zeilennummer im            บ
  บ                                             Source-Modul der Toolbox   บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion wird aufgerufen, wenn ein fataler    บ
  บ                    Fehler auftritt, der das Laufzeitverhalten des      บ
  บ                    Programmes erheblich beeinfluแt.                    บ
  บ                                                                        บ
  บ                    Das Programm wird abgebrochen und eine Fehler-      บ
  บ                    meldung ausgegeben, die die Art des Fehlers         บ
  บ                    angibt und die Funktion, in der der Fehler          บ
  บ                    auftrat.                                            บ
  บ                                                                        บ
  บ  Rckgabewert:     kein Rckgabewert                                   บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define SPA   3
#define ZEI   6
#define BRE  68
#define HOE  12


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        GLOBALE VARIABLEN                               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT COLORSET  aCS_g[];
IMPORT WORD      wCSInd_g;
IMPORT WORD      wVioMode_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
PSTR pstrErrorText_m[] =
{
/*00*/  "Speicherplatz konnte nicht allokiert werden.",
/*01*/  "Zeiger zeigt nicht mehr auf Struktur.",
/*02*/  "Initialisiertes Men ist in der H”he zu groแ.",
/*03*/  "Menoption ist zu lang.",
/*04*/  "Anzahl der Hilfstexte ist nicht identisch mit Anzahl Optionen.",
/*05*/  "Der erforderliche Zeiger war nicht mehr da.",
/*06*/  "Es konnte kein Index zugeordnet werden.",
/*07*/  "Zum angegebenen Index existiert keine Funktion",
/*08*/  "Verkettete Liste MKBs zerst”rt",
/*09*/  "Doppelte FensterID",
        NULL
};




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_Fehler(WORD wFehlerNr, PSTR pstrFunktion,
              PSTR pstrDateiname,  WORD wZeile)
{
    PWKB pWkbDlg;

    if ((pWkbDlg = WinEinrichten(SPA, ZEI, BRE, HOE)) == NULL)
    {
        printf("Schwerer Laufzeitfehler QuickC-Toolbox\n");
        printf("Programm wurde abgebrochen.\n");
        exit(1);
    }
    pstrDateiname = strrchr(pstrDateiname, '\\');
    pstrDateiname++;

    WinSetAttri(pWkbDlg, 0, aCS_g[wCSInd_g].wCs_fdlg,
                aCS_g[wCSInd_g].wCs_fdlg);

    WinSchattenEin(pWkbDlg);                        /* Schatten ein         */
    WinAktivieren(pWkbDlg);                         /* Dialog aktivieren    */

    WinSwa(0,0,BRE-2,1, VH(HELLWEISS, SCHWARZ));
    WinSwz(0,1,BRE,1,'ฤ');
    WinSs(20,0, "QuickC-Toolbox Laufzeitfehler");
    WinSetCursorPos(0,2);
    WinPrintf("  Position des Fehlers:\n");
    WinPrintf("    Funktion: %s in Datei: %s, Zeile: %d\n\n",
                pstrFunktion,
                pstrDateiname,
                wZeile);
    WinPrintf("  Ursache des Fehlers:\n    %s\n\n",
                *(pstrErrorText_m+wFehlerNr));
    WinPrintf("  Die Ausfhrung des Programms wurde beendet.");

    VioSetCursorPos(0,20);
    if (wVioMode_g == MONOCHROM)
        VioSetCursorTyp(12,13);
    else
        VioSetCursorTyp(6,7);
    exit(1);
}


