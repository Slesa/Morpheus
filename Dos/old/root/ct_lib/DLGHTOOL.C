/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    DlgHilfeTools                  Datum:  1.11.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        WORD  wDialog    Kennnummer des Dialogfeldes,       บ
  บ                                     fr das die Hilfe ausgegeben       บ
  บ                                     werden soll                        บ
  บ                          - FARBPALETTE  Hilfe fr Funktion             บ
  บ                                         DlgFarbPalette()               บ
  บ                          - DOSSHELL     Hilfe fr Funktion             บ
  บ                                         UtlDosShell()                  บ
  บ                          - SPEICHERN    Hilfe fr Funktion             บ
  บ                                         DlgSpeichernUnter()            บ
  บ                          - LADEN        Hilfe fr Funktion             บ
  บ                                         DlgLaden()                     บ
  บ                          - WARNTON      Hilfe fr Funktion             บ
  บ                                         DlgWarnton()                   บ
  บ                          - MAUSTEMPO    Hilfe fr Funktion             บ
  บ                                         DlgMausTempo                   บ
  บ                          - DLGINDEX     Hilfe DlgHilfeIndex()          บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion baut das Hilfefenster fr die        บ
  บ                    bergebene Toolbox-Funktion auf.                    บ
  บ                                                                        บ
  บ  Rckgabewert:     keiner                                              บ
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
#include <stdio.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE VARIABLEN                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL PSTR pstrPalTitel_m = "Hilfe fr Farbpalette whlen";
MGLOBAL PSTR apstrPalText_m[]=
{
    " Benutzen Sie diese Dialog-Box um die Farben,",
    " mit denen das Men und die Dialog-Boxen auf",
    " dem Bildschirm dargestellt werden, festzulegen.",
    "",
    " Wenn an Ihrem Rechner ein Farbmonitor ange-",
    " schlossen ist, stehen Ihnen fnf Farbpaletten",
    " zur Verfgung. Bei einem Monochrom-Monitor",
    " ist immer die monochrome Palette aktiv.",
    "",
    " Sie whlen eine Palette aus, indem Sie",
    "  þ  die Tasten    und    bettigen oder",
    "  þ  einen der andersfarbigen Buchstaben",
    "     eingeben oder",
    "  þ  den Mauszeiger auf ein Optionsfeld bewegen",
    "     und dort die linke Maustaste drcken.",
    "",
    " Drcken Sie",
    "  þ  <ฤู   um die gewhlte Palette einzustellen",
    "  þ  Esc   um den Dialog abzubrechen und die",
    "           alte Palette wieder zu aktivieren.",
    NULL
};

MGLOBAL PSTR pstrSpeichernTitel_m = "Hilfe fr Speichern unter";
MGLOBAL PSTR apstrSpeichernText_m[] =
{
    "Mit dem Speichern unter... - Befehl k”nnen Sie",
    "aktuelle Datei unter einem neuen Namen auf",
    "dem Datentrger abspeichern.",
    "",
    "Das Dialogfeld besteht aus folgenden Anzeigen",
    "und Optionen:",
    " þ Verzeichnis:  Hier finden Sie die Angabe des",
    "                 aktuellen Pfades.",
    " þ Dateiname:    Geben Sie hier den Namen ein,",
    "                 unter dem die aktuelle Datei ",
    "                 gespeichert werden soll.",
    "",
    " Whlen Sie",
    "  þ <ฤู  um die Datei unter dem Namen abzuspeichern,",
    "         der im Textfeld ฏDateinameฎ angegeben ist.",
    "  þ Esc  um den Speichern unter... - Befehl ",
    "         abzubrechen.",
    "",
    " Folgende Zeichen drfen in einem Dateinamen nicht",
    " vorkommen: \\ / [] {} : | <> + = ; . \" ? * ",
    "",
    " Fr den Fall, daแ einer der Buchstaben Teil des",
    " Namens ist, gibt die Funktion folgende Meldung",
    " aus: \"Der eingegebene Dateiname ist ungltig.\" ",
    NULL
};

MGLOBAL PSTR pstrMausTitel_m = "Maustempo festlegen";
MGLOBAL PSTR apstrMausText_m[]=
{
    " Benutzen Sie diese Dialog-Box um zu bestimmen,",
    " wie schnell sich der Mauszeiger auf dem Bild-",
    " schirm bewegen soll.",
    "",
    " Je kleiner die gewhlte Zahl, desto langsamer",
    " ist die Bewegung des Mauszeigers, und umge-",
    " kehrt. Der Standardwert fr die Mausgeschwindig-",
    " keit ist 50.",
    "",
    " Sie k”nnen die Markierung in der Scroll-Leiste ",
    " verschieben, indem Sie",
    " þ  die Tasten  <-  und  ->  bettigen oder",
    " þ  den Mauszeiger auf die Pfeile an der Scroll-",
    "    leiste bewegen, und dort die linke Maustaste",
    "    drcken,",
    " þ  den Mauszeiger auf die gewnschte Position auf",
    "    der Scrollleiste bewegen und dort die linke",
    "    Maustaste drcken",
    "",
    " Whlen Sie",
    " þ <ฤู   um das gewhlte Tempo einzustellen",
    " þ Esc   um den Dialog abzubrechen",
    NULL
};


MGLOBAL PSTR pstrTonTitel_m = "Hilfe fr Warnton einstellen";
MGLOBAL PSTR apstrTonText_m[]=
{
    " Benutzen Sie diese Dialog-Box um zu bestimmen,",
    " ob das Programm im Bedarfsfall einen Warnton ",
    " ausgibt oder nicht.",
    "",
    " Sie k”nnen auแerdem die Dauer und Frequenz des",
    " Warntons festlegen."
    "",
    " Sie k”nnen das Eingabefeld verndern, indem Sie",
    "  þ  Tab oder Umsch+Tab drcken.",
    "",
    " Unter dem Namen des aktiven Eingabefeldes blinkt",
    " der Cursor.",
    "",
    " Verschieben Sie die Markierung in den Rolleisten",
    " fr Dauer und Frequenz, indem Sie",
    " þ  die Tasten  <-  und  ->  bettigen oder",
    " þ  den Mauszeiger auf die Pfeile an der Scroll-",
    "    leiste bewegen, und dort die linke Maustaste",
    "    drcken.",
    "",
    " Drcken Sie",
    " þ <ฤู  um die gewhlten Werte einzustellen",
    " þ Esc  um den Dialog abzubrechen",
    " þ F4   um den eingestellten Ton probeweise zu h”ren",
    NULL
};

MGLOBAL PSTR pstrShellTitel_m = "Hilfe fr Betriebssystem-Befehl";
MGLOBAL PSTR apstrShellText_m[] =
{
    "Dieser Befehl erm”glicht es Ihnen, vorbergehend",
    "zur DOS-Ebene zurckzukehren."
    "",
    "Sie k”nnen dort andere Programme oder DOS-Befehle",
    "ausfhren.",
    "",
    "Um von der DOS-Ebene wieder in dieses Programm",
    "zurckzukehren, geben Sie den EXIT-Befehl ein",
    "und drcken die Eingabe-Taste.",
    "",
    "Wenn der DOS-Befehlsinterpreter nicht gestartet",
    "werden konnte, wird der Betriebssystem-Befehl mit",
    "einer Fehlermeldung abgebrochen.",
    NULL
};


MGLOBAL PSTR pstrLadenTitel_m = "Hilfe fr Datei laden";
MGLOBAL PSTR apstrLadenText_m[] =
{
    " Mit dem Dialogfeld ฏLadenฎ k”nnen Sie auf ver-",
    " schiedene Arten bestimmen, welche Datei als",
    " nchstes zur Bearbeitung geladen werden soll.",
    "",
    " Das Dialogfeld besteht neben den Schaltflchen",
    " aus folgenden Elementen:",
    "",
    " þ Textfeld: Im Textfeld k”nnen Sie einen Datei-",
    "      namen eingeben, eine neue Suchmaske, oder",
    "      ein Laufwerk oder Verzeichnis, in dem",
    "      nach Dateien gesucht werden soll.",
    "",
    " þ Angabe aktuelles Verzeichnis: Unter dem Textfeld",
    "      wird das Laufwerk und Verzeichnis ausgegeben,",
    "      in dem die Dialogbox derzeit nach Dateien",
    "      sucht.",
    "",
    " þ Verzeichnisfeld: Im Verzeichnisfeld werden alle",
    "      Dateinamen ausgegeben, die der im Textfeld ",
    "      ausgegebenen Suchmaske entsprechen. Die Ver-",
    "      zeichnisse und die Dateinamen sind getrennt",
    "      sortiert.",
    "      Das bergeordnete Verzeichnis wird durch [..]",
    "      symbolisiert, die Unterverzeichnisse werden in",
    "      Groแbuchstaben und in eckigen Klammern einge-",
    "      schlossen ausgegeben.",
    "",
    " Folgende Tasten sind immer aktiv:",
    "",
    "     Tab oder Umsch+Tab",
    "              verndert den Fokus",
    "     Esc      bricht die Funktion ab",
    "     Eingabe  bernimmt die angezeigte Zeichen-",
    "              kette und beendet die Funktion",
    "     F1       zeigt diesen Hilfe-Bildschirm",
    "",
    " Sondertasten im Textfeld:",
    "",
    "     \x1B \x1A        bewegen den Cursor um ein Zeichen",
    "     Pos1       setzt Cursor auf erstes Zeichen",
    "     Ende       setzt Cursor hinter letztes Zeichen",
    "     Entf       l”scht Zeichen unter dem Cursor",
    "     Umsch+Entf l”scht komplettes Textfeld",
    "     Rck       l”scht Zeichen links vom Cursor",
    "     Einfg      schaltet Einfgemodus ein/aus",
    "",
    "     Das Textfeld akzeptiert nur Zeichen die fr",
    "     Dateinamen zugelassen sind.",
    "",
    " Sondertasten im Verzeichnisfeld:",
    "",
    "           bewegen den Balken um einen Eintrag",
    "     Bild  bewegen den Balken um eine Seite",
    "     Pos1    bewegt den Balken auf ersten Eintrag",
    "     Ende    bewegt den Balken auf letzten Eintrag",
    "",
    "     Durch die Eingabe eines Anfangs-Buchstabens",
    "     k”nnen Sie direkt zu einem Eintrag springen.",
    "     Der gefundene Dateiname erscheint immer in der",
    "     ersten Zeile des Verzeichnisfeldes.",
    NULL
};

MGLOBAL PSTR pstrIndexTitel_m = "Hilfe fr Index der Hilfsbildschirme";
MGLOBAL PSTR apstrIndexText_m[] =
{
    " Whlen Sie in diesem Dialogfeld ein Thema aus, zu",
    " dem Sie Hilfe anfordern wollen.",
    "",
    " Bewegen Sie den Auswahlbalken auf das Thema, zu dem",
    " Sie Hilfe anfordern wollen. Der Balken wird bewegt,",
    " indem Sie",
    " þ  die Tasten    und    bettigen oder",
    " þ  mit dem Mauszeiger auf das Thema zeigen und die",
    "    linke Maustaste bettigen, oder",
    " þ  mit dem Mauszeiger auf die Rollpfeile zeigen, und",
    "    die linke Maustaste drcken.",
    "",
    " Sie aktivieren ein Thema, indem Sie",
    " þ  die Eingabe-Schaltflche bettigen,",
    " þ  auf einem Thema mit der Maus doppelklicken.",
    "",
    " Mit der Esc-Schaltflche k”nnen Sie die Auswahl",
    " abbrechen.",
    NULL
};



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID DlgHilfeTools(WORD wDialog)
{
    switch(wDialog)
    {
        case FARBPALETTE:   DlgHilfe(pstrPalTitel_m,
                                     apstrPalText_m);
                            break;

        case SPEICHERN:     DlgHilfe(pstrSpeichernTitel_m,
                                     apstrSpeichernText_m);
                            break;

        case MAUSTEMPO:     DlgHilfe(pstrMausTitel_m,
                                     apstrMausText_m);
                            break;

        case DOSSHELL:      DlgHilfe(pstrShellTitel_m,
                                     apstrShellText_m);
                            break;

        case WARNTON:       DlgHilfe(pstrTonTitel_m,
                                     apstrTonText_m);
                            break;

        case LADEN:         DlgHilfe(pstrLadenTitel_m,
                                     apstrLadenText_m);
                            break;
        case DLGINDEX:      DlgHilfe(pstrIndexTitel_m,
                                     apstrIndexText_m);
                            break;

    }
    return;
}


