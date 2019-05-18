/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    UtlDateinameGueltig            Datum: 31.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR pstrDateiname    Dateiname, der berprft      บ
  บ                                          werden soll                   บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion berprft, ob der bergebene Datei-  บ
  บ                    name gltig oder nicht gltig ist.                  บ
  บ                                                                        บ
  บ  Hinweis:          Der bergebene String darf neben dem Datei- auch    บ
  บ                    den Pfadnamen enthalten. Wenn der Dateiname         บ
  บ                    den DOS-Konventionen entspricht, gibt die           บ
  บ                    Funktion den Wert der Konstanten DN_GUELTIG         บ
  บ                    zurck, sonst DN_UNGUELTIG.                         บ
  บ                                                                        บ
  บ                    Ein Laufwerksname alleine zhlt nicht als           บ
  บ                    gltiger Dateiname.                                 บ
  บ                                                                        บ
  บ  Rckgabewert:     WORD  DN_GUELTIG   == gltiger Dateiname            บ
  บ                          DN_UNGUELTIG == ungltiger Dateiname          บ
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
#ifndef CT_TYPEN_HEADER
#include <cttypen.h>                                /* Toolbox-Datentypen   */
#endif

#ifndef CT_UTIL_HEADER
#include <ctutl.h>                                  /* Prototyp dieser Fkt. */
#endif

#include <string.h>                                 /* fr str..-Funktionen */
#include <stdio.h>                                  /* fr NULL             */
#include <ctype.h>                                  /* fr isalpha()        */

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        KONSTANTEN UND MAKROS                           บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define UNGUELTIGE_ZEICHEN "\\/[]{}:|<>+=,;.\"?*"

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                        MODULGLOBALE FUNKTIONEN                         บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL BOOL i_ErlaubtesZeichen (CHAR);
MGLOBAL WORD i_TestN(PSTR, BOOL);

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ                          FUNKTIONS-DEFINITION                          บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
GLOBAL
BOOL UtlDateinameGueltig(PSTR pstrDateiname)
{
    REGISTER i;                                     /* Schleifenzhler      */
    PSTR pstrTmp;                                   /* lokaler Zeiger       */
    PSTR pstrAnfang;
    PSTR pstrEnde;
    BOOL boNameFertig = FALSCH;                     /* mit Dateinamen fert. */
    WORD wResult;

    pstrAnfang  = pstrDateiname;                    /* Zeiger auf Anfang    */
    for (i=0; *pstrAnfang==' '; i++)                /* fhrende Leerzeichen */
        pstrAnfang++;                               /* ausschneiden         */

    if (i > 0)                                      /* wenn Leerzeichen da, */
    {
        strcpy(pstrDateiname, pstrAnfang);          /*     verkrzten Namen */
        pstrAnfang = pstrDateiname;                 /*     kopieren         */
    }

    pstrTmp = pstrDateiname+strlen(pstrDateiname);  /* Zeiger auf Ende des  */
    pstrEnde = pstrTmp;                             /* Stringende merken    */                                                /* Strings              */

    if( *(pstrTmp-1) == '\\' ||                     /* wenn dort Backslash  */
        *(pstrTmp-1) == ':' )                       /* oder Doppelpunkt     */
        return(DN_UNGUELTIG);                       /* Name ungltig        */


    if (*(pstrAnfang+1) == ':')                     /* wenn Doppelpunkt     */
        if (!isalpha(*pstrAnfang))                  /* muแ Zeichen davor    */
            return(DN_UNGUELTIG);                   /* Buchstabe sein       */
        else
            pstrAnfang += 2;                        /* LW-Kennung berspri. */

    while (pstrTmp >= pstrAnfang)                   /* Dateinamen und evtl. */
    {                                               /* Verzeichnisnamen     */
        if (*pstrTmp == '\\')                       /* isolieren            */
            *pstrTmp = '\0';
        pstrTmp--;
    }

    pstrTmp = pstrEnde;                             /* Zeiger hinter letzt. */
                                                    /* Zeichen des Strings  */

    do
    {
        for (--pstrTmp;                             /* nchstes Teil holen  */
             *pstrTmp != '\0' && pstrTmp >= pstrAnfang;
             --pstrTmp)
            ;

        wResult = i_TestN(pstrTmp+1, boNameFertig); /* String berprfen    */
        boNameFertig = JA;                          /* Dateiname erledigt   */

    } while (pstrTmp > pstrAnfang && wResult == DN_GUELTIG);


    for (; pstrAnfang < pstrEnde; pstrAnfang++)     /* Dateinamen wieder in */
        if (*pstrAnfang == '\0')                    /* Form bringen         */
            *pstrAnfang = '\\';

    return(wResult);
}



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_TestN                        Datum: 31.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        PSTR pstrName      Name, der berprft werden soll  บ
  บ                    BOOL boNamefertig  Dateiname oder Verzeichnisname   บ
  บ                                                                        บ
  บ  Beschreibung:     .                                                   บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Rckgabewert:     .                                                   บ
  บ                                                                        บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  .                                                   บ
  บ                                                                        บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
WORD i_TestN(PSTR pstrName, BOOL boNameFertig)

{
    REGISTER i;
    BOOL boPktGef;                                  /* Punkt gefunden       */
    WORD wMaxI = 8;                                 /* Grenzwert fr i      */

    if (pstrName == NULL)
        return(DN_UNGUELTIG);

    for (i=0, boPktGef=FALSCH;
         i<=wMaxI && *pstrName != '\0';
         pstrName++)
    {
        if (i_ErlaubtesZeichen(*pstrName))
            i++;                                    /* weitermachen         */
        else
            switch(*pstrName)
            {
                case '.':   if (boPktGef)           /* zweiter Punkt        */
                                i=wMaxI+1;          /* for-Schleife beenden */
                            else
                            {
                                boPktGef = WAHR;    /* Flag setzen          */
                                i = 0;              /* Zhler init.         */
                                wMaxI = 3;          /* MaxZeichen Extension */
                            }
                            break;

                case '*':
                case '?':   if (boNameFertig)
                                i=wMaxI+1;          /* for-Schleife beenden */
                            else
                                i++;                /* weitermachen         */
                            break;

                default:    i=wMaxI+1;              /* for-Schleife beenden */
            } /* end of switch */
    } /* end of for */

    if (i>wMaxI)
        return(DN_UNGUELTIG);
    else
        return(DN_GUELTIG);
}




/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Funktionsname:    i_ErlaubtesZeichen             Datum: 12.12.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ  Parameter:        CHAR cZeichen       Zeichen, das berprft werden   บ
  บ                                        soll                            บ
  บ                                                                        บ
  บ  Beschreibung:     Diese Funktion berprft, ob das bergebene         บ
  บ                    Zeichen in einem DOS-Dateinamen vorkommen           บ
  บ                    darf.                                               บ
  บ                                                                        บ
  บ                    Die Zeichen, die das Ergebnis FALSCH liefern,       บ
  บ                    sind in der Konstante UNGUELTIGE_ZEICHEN            บ
  บ                    definiert.                                          บ
  บ                                                                        บ
  บ  Rckgabewert:     BOOL   WAHR   gltiges Zeichen                      บ
  บ                           FALSCH ungltiges Zeichen                    บ
  บ                                                                        บ
  บ  Benutzte globale                                                      บ
  บ  Variablen (R/W):  keine                                               บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
MGLOBAL
BOOL i_ErlaubtesZeichen (CHAR cZeichen)
{
    PCHAR pcTmp;

    if (cZeichen <= ' ')                            /* auf Leerzeichen      */
        return (FALSCH);                            /* testen               */

     for (pcTmp = UNGUELTIGE_ZEICHEN; *pcTmp != '\0'; pcTmp++)
        if (*pcTmp == cZeichen)
            return(FALSCH);

    return(WAHR);
}
