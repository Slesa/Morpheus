/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlEvent                       Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        EVENT  *event   Zeiger auf Eventstruktur            บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion berprft, ob der Anwender eine Ein-   บ
  บ                    gabe vorgenommen hat. Diese kann von der Tastatur   บ
  บ                    oder mit einer Maus erfolgen und wird im folgenden  บ
  บ                    als Event bezeichenet. Die Funktion untersttzt     บ
  บ                    zehn verschiedene Eventarten:                       บ
  บ                                                                        บ
  บ                      - EVENT_NULL         keine Eingabe erfolgt        บ
  บ                      - EVENT_MOUSE_MOVE   Maus wurde bewegt            บ
  บ                      - EVENT_L_PRESS      linker Button gedrckt       บ
  บ                      - EVENT_R_PRESS      rechter Button gedrckt      บ
  บ                      - EVENT_B_PRESS      beide Buttons gedrckt       บ
  บ                      - EVENT_L_RELEASE    linker Button losgelassen    บ
  บ                      - EVENT_R_RELEASE    rechter Button losgelassen   บ
  บ                      - EVENT_B_RELEASE    beide Buttons losgelassen    บ
  บ                      - EVENT_TASTE        Tastatureingabe              บ
  บ                      - EVENT_ALT_PRESS    Alt-Taste gedrckt           บ
  บ                      - EVENT_ALT_RELEASE  Alt-Taste losgelassen        บ
  บ                                                                        บ
  บ  Rckgabewert:     Die Funktion hat keinen Rckgabewert                บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):   - wMausda_g (R)                                    บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <conio.h>
#include <ctools.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT WORD wMausda_g;                              /* Systemkonfiguration  */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ               Prototypen der modulglobalen Funktionen                  บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL VOID i_TestMausStatus(EVENT*);

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
VOID UtlEvent(PEVENT pEvent)
{

    STATIC BOOL boSaveAlt;                          /* 1: gedrckt, 0: los  */


    pEvent->wArt = EVENT_NULL;                      /* alten Event l”schen  */
    pEvent->wTaste = 0;                             /* alte Taste l”schen   */
    pEvent->wOption = 0;                            /* alte Option l”schen  */

    UtlGetUhrTicks(&pEvent->lTicks);                /* Systemzeit eintragen */

    pEvent->wKbflags  = UtlKbFlags();               /* Zustand der Tastatur */

    if (wMausda_g)                                  /* Ist eine Maus da ?   */
    {
        i_TestMausStatus(pEvent);                   /* Zustand ermitteln    */
        if(pEvent->wArt != EVENT_NULL)
            return;                                 /* MAUS-EVENT aufgetr.  */
    }


    if ( (pEvent->wKbflags & BIT3) != boSaveAlt)    /* Alt-Event ?          */
    {
        boSaveAlt = pEvent->wKbflags & BIT3;        /* Zustand sichern      */
        if ( boSaveAlt )
            pEvent->wArt = EVENT_ALT_PRESS;
        else
            pEvent->wArt = EVENT_ALT_RELEASE;
        return;                                     /* ALT-EVENT aufgetret. */
    }


    if (kbhit())
    {
        pEvent->wArt = EVENT_TASTE;
        pEvent->wTaste = UtlTaste();
        return;                                     /* TASTATUR_EVENT aufg. */
    }

    return;                                         /* NULL-EVENT aufgetr.  */

}


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_TestMausStatus               Datum: 07.01.89      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        EVENT  *event   Zeiger auf Eventstruktur            บ
  บ                                                                        บ
  บ  Beschreibung:     Die Funktion trgt zuerst den aktuellen Zustand     บ
  บ                    der Mausbuttons und die Position des Mauscursors    บ
  บ                    in die Eventstruktur ein.                           บ
  บ                    Danach wird berprft, ob die Maus seit dem letzen  บ
  บ                    Aufruf der Funktion bewegt worden ist. In diesem    บ
  บ                    Fall wird die aktuelle Position gesichert und ein   บ
  บ                    EVENT_MOUSE_MOVE ausgel”st.                         บ
  บ                    Wenn die Maus nicht bewegt worden ist, untersucht   บ
  บ                    die Fuktion, ob sich der Zustand der Mausbuttons    บ
  บ                    seit dem letzten Aufruf der Funktion gendert hat.  บ
  บ                    In diesem Fall wird der entsprechende Event ausge-  บ
  บ                    l”st.                                               บ
  บ                                                                        บ
  บ  Rckgabewert:     Die Funktion hat keinen Rckgabewert                บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
VOID i_TestMausStatus(EVENT *pEvent)
{
    STATIC WORD wSaveButton,                        /* Letzter Status       */
                wSaveSpalte,
                wSaveZeile;


    MsmGetPosition(&pEvent->wButton,                /* neuen Buttonstatus   */
                   &pEvent->wSpalte,                /* und Mausposition in  */
                   &pEvent->wZeile);                /* die Struktur eintrag.*/


    if (pEvent->wButton==wSaveButton)               /* Button kein neuer    */
    {                                               /* Zustand              */
        if (wSaveSpalte != pEvent->wSpalte ||       /* Test, ob Maus bewegt */
            wSaveZeile  != pEvent->wZeile)
        {                                           /* wenn ja              */
            wSaveSpalte = pEvent->wSpalte;          /* neue Posit. sichern  */
            wSaveZeile  = pEvent->wZeile;
            pEvent->wArt = EVENT_MOUSE_MOVE;        /* Eventart eintragen   */
        }
        return;                                     /* kein Mausevent       */
    }

    if (wSaveButton == MSM_B_DOWN)                  /* waren beide gedr. ?  */
        pEvent->wArt = EVENT_B_RELEASE;

    else if (pEvent->wButton == MSM_B_DOWN)         /* sind beide gedrckt? */
        pEvent->wArt = EVENT_B_PRESS;

    else if (wSaveButton == 0)                      /* war keine gedrckt ? */
    {
        if (pEvent->wButton == MSM_L_DOWN)          /* ist links gedrckt ? */
            pEvent->wArt = EVENT_L_PRESS;
        else if (pEvent->wButton == MSM_R_DOWN)     /* ist recht gedrckt ? */
            pEvent->wArt = EVENT_R_PRESS;
    }

    else if (pEvent->wButton == 0)                  /* ist keine gedrckt ? */
    {
        if (wSaveButton == MSM_L_DOWN)              /* war links gedrckt ? */
            pEvent->wArt = EVENT_L_RELEASE;
        else if (wSaveButton == MSM_R_DOWN)         /* war rechts gedrckt? */
            pEvent->wArt = EVENT_R_RELEASE;
    }

    wSaveButton = pEvent->wButton;                  /* Buttonstatus sichern  */

    return;
}
