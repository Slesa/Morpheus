/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ  Dateiname:        CTTYPEN.H                      Datum: 16.08.88      บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ                                                                        บ
  บ      Diese Datei enthlt die Bezeichner fr die in allen               บ
  บ      Modulen verwendeten Datentypen.                                   บ
  บ                                                                        บ
  วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
  บ            Autoren: Rainer G. Haselier und Klaus Fahnenstich           บ
  บ     (c) copyright 1988 Markt & Technik Verlag AG, Haar bei Mnchen     บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

//#ifndef IPC
//#define IPC 1
//#endif

#ifndef CT_TYPEN_HEADER

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
    บ             Konstanten fr Speicherklassen u. .                       บ
    ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define VOID            void

#define GLOBAL          /* */
#define STATIC          static
#define MGLOBAL         static
#define IMPORT          extern
#define STATIC          static
#define FAR             far

#ifndef INT
#define INT             signed short
#endif

/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
    บ        Datentypen der Toolbox, incl. Prfix vor Variablennamen         บ
    ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
typedef     signed char         SCHAR;     /*   sc      */
#ifndef CHAR
typedef     unsigned char       CHAR;      /*   c,str   */
#endif
typedef     signed char         SBYTE;     /*   sb      */
#ifndef BYTE
typedef     unsigned char       BYTE;      /*   b       */
#endif
typedef     signed short        SWORD;     /*   sw      */
#ifndef WORD
typedef     unsigned short      WORD;      /*   w       */
#endif
typedef     signed long         SLONG;     /*   sl      */
#ifndef LONG
typedef     unsigned long       LONG;      /*   l       */
#endif
typedef     short int           SSHORT;    /*   ss      */
typedef     unsigned short int  SHORT;     /*   s       */
#ifndef BOOL
typedef     unsigned short      BOOL;      /*   bo      */
#endif
#ifndef FLOAT
typedef     float               FLOAT;     /*   f       */
#endif
#ifndef DOUBLE
typedef     double              DOUBLE;    /*   d       */
#endif
typedef     SCHAR*              PSCHAR;   /*   psc      */
typedef     CHAR*               PCHAR;    /*   pc       */
typedef     CHAR*               PSTR;     /*   pstr     */
typedef     PSTR*               PPSTR;    /*   ppstr    */
typedef     SBYTE*              PSBYTE;   /*   psb      */
typedef     BYTE*               PBYTE;    /*   pb       */
typedef     SWORD*              PSWORD;   /*   psw      */
typedef     WORD*               PWORD;    /*   pw       */
typedef     SLONG*              PSLONG;   /*   psl      */
typedef     LONG*               PLONG;    /*   pl       */
typedef     SSHORT*             PSSHORT;  /*   pss      */
typedef     SHORT*              PSHORT;   /*   ps       */
typedef     FLOAT*              PFLOAT;   /*   pf       */
typedef     DOUBLE*             PDOUBLE;  /*   pd       */

typedef     CHAR FAR*           FPCHAR;   /*   fpc      */
typedef     CHAR FAR*           FPSTR;    /*   fpstr    */
typedef     BYTE FAR*           FPBYTE;   /*   fpb      */
typedef     WORD FAR*           FPWORD;   /*   fpw      */

#define REGISTER        register unsigned int



/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
    บ        verschiedene Konstanten, die Toolbox-weit gelten                บ
    ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/
#define NEIN            0
#define FALSCH          NEIN
#define WAHR            (!NEIN)
#define JA              (!NEIN)
#define OK              1
#define ERROR           0
#define AUS             0
#define EIN             1
#ifndef IPC
#define MAXZEILEN       25
#define MAXSPALTEN      80
#else
#define MAXZEILEN       6
#define MAXSPALTEN      40
#endif
#define NICHT_INIT      1000

#define CT_TYPEN_HEADER 1
#endif
