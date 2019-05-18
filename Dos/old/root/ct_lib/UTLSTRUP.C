/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlStrupr                      Datum: 16.08.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR  pstrZeichenkette                              บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion arbeitet hnlich wie die Biblio-     บ
  บ                    theksfunktion strupr() der Laufzeitbibliothek.      บ
  บ                    Smtliche Kleinbuchstaben des bergebenen Strings   บ
  บ                    werden in Groแbuchstaben umgewandelt.               บ
  บ                    Im Gegensatz zu strupr() werden hier auch die       บ
  บ                    deutschen Umlaute bercksichtigt.                   บ
  บ                                                                        บ
  บ  Rckgabewert:     PSTR   Zeiger auf das erste Zeichen des umge-       บ
  บ                           wandelten Strings                            บ
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
#include <ctype.h>

#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_TYPEN_HEADER
#include <ctutl.h>
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
PSTR UtlStrupr(PSTR pstrZeichenkette)
{
    PSTR pstrTmp;

        for ( pstrTmp = pstrZeichenkette;
                    *pstrTmp;
                    pstrTmp++)
        {
                switch(*pstrTmp)
        {
                        case '':   *pstrTmp = 'A'; break;
                        case '”':   *pstrTmp = ''; break;
                        case '':   *pstrTmp = ''; break;
                        default:    *pstrTmp = toupper(*pstrTmp);
        }
        }
        return(pstrZeichenkette);
}
