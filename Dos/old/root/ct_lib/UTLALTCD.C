/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlAltCode                     Datum: 16.08.88    ๛ บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wBuchstabe   Zeichen, fr den der Scancode    บ
  บ                                       fr ALT+Buchstabe ermittelt      บ
  บ                                       werden soll.                     บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion liefert als Ergebnis den Scan-       บ
  บ                    code fr den Buchstaben, wenn er gemeinsam mit      บ
  บ                    der ALT-Taste gedrckt wird.                        บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  der Scancode des Buchstabens                  บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL WORD wAltTasten_m[]=
{
     (30 | ERW_CODE),         /* ALTA */  
     (48 | ERW_CODE),         /* ALTB */  
     (46 | ERW_CODE),         /* ALTC */  
     (32 | ERW_CODE),         /* ALTD */  
     (18 | ERW_CODE),         /* ALTE */  
     (33 | ERW_CODE),         /* ALTF */  
     (34 | ERW_CODE),         /* ALTG */  
     (35 | ERW_CODE),         /* ALTH */  
     (23 | ERW_CODE),         /* ALTI */  
     (36 | ERW_CODE),         /* ALTJ */  
     (37 | ERW_CODE),         /* ALTK */  
     (38 | ERW_CODE),         /* ALTL */  
     (50 | ERW_CODE),         /* ALTM */  
     (49 | ERW_CODE),         /* ALTN */  
     (24 | ERW_CODE),         /* ALTO */  
     (25 | ERW_CODE),         /* ALTP */  
     (16 | ERW_CODE),         /* ALTQ */  
     (19 | ERW_CODE),         /* ALTR */  
     (31 | ERW_CODE),         /* ALTS */  
     (20 | ERW_CODE),         /* ALTT */  
     (22 | ERW_CODE),         /* ALTU */  
     (47 | ERW_CODE),         /* ALTV */  
     (17 | ERW_CODE),         /* ALTW */  
     (45 | ERW_CODE),         /* ALTX */  
     (21 | ERW_CODE),         /* ALTY */  
     (44 | ERW_CODE),         /* ALTZ */  
};


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD UtlAltCode(WORD wBuchstabe)
{
    return(wAltTasten_m[(UtlGross(wBuchstabe))-65]);
}
