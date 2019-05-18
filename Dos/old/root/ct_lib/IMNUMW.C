/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_MnuMauswahl                  Datum: 19.01.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PEVENT   pEvent   Zeiger auf Ereignis               บ
  บ                    PMKB     *ppMkb   Zeiger auf Zeiger des MKB         บ
  บ                                                                        บ
  บ  Beschreibung:     echt lekker                                         บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  Fehlerinformation                             บ
  บ                          0 == kein Fehler                              บ
  บ                          sonst Fehler                                  บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  - MS_g      (R)                                     บ
  บ                    - aMenus_g  (R)                                     บ
  บ                    - wAktMnu_g (R)                                     บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        DEKLARATIONS-DATEIEN                            บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#include <ctools.h>
#include <string.h>

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ             GLOBALE VARIABLEN, DEFINITION UND REFERENZEN               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
IMPORT MENUSTATUS MS_g;               /* Zustand des Menmanagers           */
IMPORT COLORSET   aCS_g[];            /* Array der Farbpaletten             */
IMPORT WORD       wMausda_g;          /* Maus im System aktiviert           */
IMPORT MENU       aMenus_g[];         /* Array der MENU-Strukturen          */
IMPORT BOOL       boBeepen_g;
IMPORT WORD       wAktMnu_g;


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

#define AUF_AKT_TITEL(s,z,p) ( (z) == 0 && \
                               (p)->wTitelSpalte <= (s) && \
                               (s) <= (p)->wTitelSpalte + (p)->wTitelBreite )

#define AUF_TITEL(s,z) ( (z) == 0 && \
                         (*(aMenus_g[wAktMnu_g].fpwMzBuffer+(s))&0xff) != ' ' )



#define IN_FENSTER(s,z,p)    ( (s) > (p)->wSpalte                    &&  \
                               (s) < (p)->wSpalte + (p)->wBreite -1  &&  \
                               (z) > FENSTERZEILE                    &&  \
                               (z) < FENSTERZEILE + (p)->wHoehe -1     ) \


#define AUF_AKT_OPTION(s,z,p) ( (z) == (p)->wBalPos + FENSTERZEILE && \
                                (s) >  (p)->wSpalte && \
                                (s) <  (p)->wSpalte + (p)->wBreite -1  )

#define AUF_RAHMEN_WAAG(s,z,p) ( \
         ( (p)->wSpalte <= (s) && (s) < (p)->wSpalte + (p)->wBreite   ) && \
         ( (z) == FENSTERZEILE || (z) == FENSTERZEILE + (p)->wHoehe-1 )    )

#define AUF_RAHMEN_SENK(s,z,p) ( \
         ( (s) == (p)->wSpalte || (s) == (p)->wSpalte + (p)->wBreite -1 ) && \
         ( FENSTERZEILE <= (z) && (z) < FENSTERZEILE + (p)->wHoehe      )    )


#define AUF_RAHMEN(s,z,p) (AUF_RAHMEN_WAAG(s,z,p) || AUF_RAHMEN_SENK(s,z,p))


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ    zu Makro AUF_TRENNER():                                             บ
  บ                                                                        บ
  บ    ฏzฎ muแ innerhalb des Fensters liegen !!!                           บ
  บ    Ansonsten wird nicht richtig auf den MKB zugegriffen.               บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define AUF_TRENNER(s,z,p) ( ( (s) >  (p)->wSpalte ) && \
                             ( (s) <  (p)->wSpalte + (p)->wBreite -1 ) && \
                             ( strcmp( (p)->item[z-FENSTERZEILE].pstrText, \
                                         "TRENNER") == 0 ) )


/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
WORD i_MnuMauswahl (PEVENT pEvent, PMKB *ppMkb )
{
  WORD wS,wZ;                                       /* Koordinaten der Maus */
  WORD wButton;                                     /* Buttonstatus         */

  do
  {
    MsmGetPosition( &wButton, &wS, &wZ );           /* Position der Maus u. */
                                                    /* Buttonstatus holen   */

    if ( !MS_g.wTitel &&                            /* kein Titel markiert  */
         !MS_g.wFenster &&                          /* kein Fenster sichtb. */
         !MS_g.wBalken &&                           /* keine Option markier.*/
         AUF_TITEL(wS,wZ) )
    {
        pEvent->wSpalte = wS;
        *ppMkb = i_MnuAufMenutitel(pEvent);         /* neuen MKB ermitteln  */
        i_MnuTitel(ppMkb,0,EIN_ABS);                /* Titel markieren      */
        i_MnuFenster(ppMkb,0,EIN_ABS);              /* Fenster anzeigen     */
    }
    else if ( MS_g.wTitel &&                        /* Titel markiert       */
             !MS_g.wFenster &&                      /* kein Fenster sichtb. */
             !MS_g.wBalken )                        /* keine Option markier.*/
        i_MnuTitel(ppMkb,0,AUS);                    /* Titel l”schen        */


    else if ( !MS_g.wTitel &&                       /* kein Titel markiert  */
               MS_g.wFenster )                      /* Fenster sichtbar     */
    {
        if (MS_g.wBalken)                           /* Balkencursor ein     */
        {
            if ( AUF_AKT_OPTION(wS,wZ,*ppMkb) )     /* auf aktueller Option */
                ;                                   /* keine Aktion         */
            else if ( IN_FENSTER(wS,wZ,*ppMkb) )    /* auf einer anderen    */
            {                                       /* Option               */
                if ( !AUF_TRENNER(wS, wZ,*ppMkb) )
                    i_MnuBalken(*ppMkb,wZ,EIN_ABS); /* Balken bewegen       */
                else                                /* auf Fensterrahmen    */
                    i_MnuBalken(*ppMkb,0,AUS);      /* Balken l”schen       */
            }
            else
                i_MnuBalken(*ppMkb,0,AUS);          /* Balken l”schen       */

        }
        else                                        /* kein Balken          */
        {
            if ( AUF_AKT_TITEL(wS,wZ,*ppMkb) )      /* auf aktuellem Titel  */
                i_MnuTitel(ppMkb,0,EIN_ABS);        /* Titel anzeigen       */
            else if ( AUF_TITEL(wS,wZ) )            /* auf anderem Titel    */
            {
                pEvent->wSpalte = wS;               /* Event aktualisieren  */
                i_MnuFenster(ppMkb,0,AUS);          /* altes Fenster entf.  *7/
                *ppMkb = i_MnuAufMenutitel(pEvent); /* neuen MKB ermitteln  */
                i_MnuFenster(ppMkb,0,EIN_ABS);          /* neues Fenster anzeig.*/
                i_MnuTitel(ppMkb,0,EIN_ABS);        /* neuen Titel anzeigen */
            }
            else if ( IN_FENSTER(wS,wZ,*ppMkb) )    /* auf einer anderen    */
                if ( !AUF_TRENNER(wS,wZ,*ppMkb) )   /* Option               */
                    i_MnuBalken(*ppMkb,wZ,EIN_ABS); /* Balken setzen        */
            else
                ;                                   /* keine Aktion         */
        }
    }
    else if ( MS_g.wTitel &&                        /* Titel markiert       */
              MS_g.wFenster &&                      /* Fenster sichtbar     */
             !MS_g.wBalken)                         /* Balkencursor aus     */
    {
        if ( AUF_AKT_TITEL(wS,wZ,*ppMkb))           /* auf aktuellem Titel  */
            ;                                       /* keine Aktion         */
        else if ( AUF_TITEL(wS,wZ) )                /* auf anderem Titel    */
        {
            pEvent->wSpalte = wS;                   /* Eventstruktur akt.   */
            i_MnuFenster(ppMkb,0,AUS);              /* altes Fenster entf.  */
            *ppMkb = i_MnuAufMenutitel(pEvent);     /* neuen MKB ermitteln  */
            i_MnuFenster(ppMkb,0,EIN_ABS);          /* neues Fenster anzeig.*/
            i_MnuTitel(ppMkb,0,EIN_ABS);            /* neuen Titel anzeigen */
        }
        else if ( AUF_RAHMEN(wS,wZ,*ppMkb) ||       /* auf Rahmen oder      */
                  AUF_TRENNER(wS,wZ,*ppMkb) )       /* auf Trenner          */
            ;                                       /* keine Aktion         */
        else if ( IN_FENSTER(wS,wZ,*ppMkb) )        /* auf einer anderen    */
        {                                           /* Option               */
            if ( !AUF_TRENNER(wS,wZ,*ppMkb) )       /* nicht auf Trenner    */
            {
                i_MnuTitel(ppMkb,0,AUS);            /* Titel l”schen        */
                i_MnuBalken(*ppMkb,wZ,EIN_ABS);     /* Balken setzen        */
            }
        }
        else                                        /* auแerhalb            */
        {
            i_MnuTitel(ppMkb,0,AUS);                /* Titel l”schen        */
            i_MnuFenster(ppMkb,0,AUS);              /* Fenster l”schen      */
        }
    }
  } while ( wButton == MSM_L_DOWN);                 /* solange linke Taste  */
                                                    /* gedrckt bleibt.     */


  UtlEvent(pEvent);                                 /* Event-Strukt. l”sch. */
  pEvent->wSpalte = wS;                             /* Zustand der Maus in  */
  pEvent->wZeile  = wZ;                             /* die Eventstruktur    */
  pEvent->wButton = wButton;                        /* eintragen            */


  if ( !MS_g.wTitel &&                              /* kein Titel markiert  */
       !MS_g.wFenster &&                            /* kein Fenster sichtb. */
       !MS_g.wBalken )                              /* keine Option markier.*/
  {
      MS_g.wAktiv = 0;                              /* Manager deaktivieren */
      pEvent->wArt = EVENT_NULL;                    /* Eventart korrigieren */
  }
  else if ( !MS_g.wTitel && MS_g.wFenster )         /* kein Titel markiert  */
  {                                                 /* Fenster sichtbar     */
      if ( MS_g.wBalken )                           /* Balken ist sichtbar  */
      {
          if ((*ppMkb)->pHotkeys[(*ppMkb)->wBalIndex].wAktiv) /* glt. Opt. */
          {
              i_MnuFenster(ppMkb,0,AUS);            /* Fenster l”schen      */
              MS_g.wAktiv = 0;                      /* Manager deaktivieren */
              pEvent->wOption =
                    (*ppMkb)->pHotkeys[(*ppMkb)->wBalIndex].wOpt;
              pEvent->wArt = EVENT_WAHL;            /* Eventart korrigieren */
          }
          else                                      /* auf ungltiger Opt.  */
          {
              if (boBeepen_g)
                  i_Beep();                         /* evtl. Warnton        */
              pEvent->wArt = EVENT_NULL;
          }
      }
      else                                          /* Balken nicht sichtb. */
      {
          if ( AUF_RAHMEN(wS,wZ,*ppMkb) ||          /* auf Rahmen oder      */
               AUF_TRENNER(wS,wZ,*ppMkb) )          /* auf Trenner          */
          {
              i_MnuBalken(*ppMkb,FENSTERZEILE+1,
                          EIN_ABS);                 /* erste Option markier.*/
              pEvent->wArt = EVENT_NULL;
          }
          else
          {
              i_MnuFenster(ppMkb,0,AUS);            /* Fenster l”schen      */
              MS_g.wAktiv = 0;                      /* Manager deaktivieren */
              pEvent->wArt = EVENT_NULL;
          }

      } /* end of else (Balken sichtbar) */
  } /* end of ( kein Titel und Fenster) */

  else if ( MS_g.wTitel &&                          /* Titel ist markiert   */
            MS_g.wFenster &&                        /* Fenster ist sichtbar */
           !MS_g.wBalken )                          /* keine Option markier.*/
  {
      i_MnuTitel(ppMkb,0,AUS);                      /* Titel l”schen        */
      i_MnuBalken(*ppMkb,FENSTERZEILE+1,
                  EIN_ABS);                         /* erste Option markier.*/
      pEvent->wArt = EVENT_NULL;
  }

  return(0);                                        /* Funktion beenden     */

}
