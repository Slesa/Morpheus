/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_Beep                         Datum: 28.10.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        keine                                               บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion ruft die FUnktionen UtlTon()         บ
  บ                    und UtlPause() und das Makro UtlTon() auf,          บ
  บ                    um einen kurzen Warnton zu erzeugen.                บ
  บ                    Dieser Warnton wird bei allen Dialogfeldern         บ
  บ                    ausgegeben, wenn eine derzeit ungltige Aktion      บ
  บ                    ausgewhlt wurde.                                   บ
  บ                                                                        บ
  บ                    Die Frequenz und Dauer des Tons werden den          บ
  บ                    globalen Variablen wBeepFreq_g und wBeepDauer_g     บ
  บ                    entnommen.                                          บ
  บ                                                                        บ
  บ                    Wenn Sie in Ihr Programm die Funktion DlgWarnton()  บ
  บ                    aufnehmen, hat der Anwender die M”glichkeit,        บ
  บ                    die Dauer und die Frequenz einzustellen und         บ
  บ                    grundstzlich festzulegen, ob ein Warnton er-       บ
  บ                    klingen soll oder nicht.                            บ
  บ                                                                        บ
  บ                    weitere Informationen finden Sie in der Dokumen-    บ
  บ                    tation zu - DlgWarnton()                            บ
  บ                              - DlgGetOptionen()                        บ
  บ                              - DlgPutOptionen()                        บ
  บ                                                                        บ
  บ  Rckgabewert:     keine                                               บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  wBeepFreq_g, wBeepDauer_g (R)                       บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wBeepFreq_g;
IMPORT WORD wBeepDauer_g;

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID i_Beep(VOID)
{
    UtlTon(wBeepFreq_g);
    UtlPause(UTL_TICKS, wBeepDauer_g);
    UtlTonAus();
    return;
}
