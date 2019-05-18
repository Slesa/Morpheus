#ifndef         _DEVICES_

 #define        _DEVICES_
 #include       <DEFS/TYPEDEFS.H>

 /* ----------- Device seriell -------------------------------------------- */
 typedef        struct
 {
  WORD          wAdr;                            /* Port-Adresse            */
  BYTE          bData;                           /* Anzahl Datenbits        */
  BYTE          bStop;                           /* Anzahl Stopbits         */
  CHAR          cPari;                           /* Paritaet                */
  LONG          lBaud;                           /* Baudrate                */
  INT           iIrq;                            /* Interrupt verbiegen?    */
 } SDevSer;

 /* ----------- Device parallel ------------------------------------------- */
 typedef        struct
 {
  WORD          wAdr;                            /* Port-Adresse            */
 } SDevPar;

 /* ----------- Device IMC-Board ------------------------------------------ */
 typedef        struct
 {
  WORD          wAdr;                            /* Adresse zum Ansteuern   */
  INT           iBoard;                          /* Auf welchem IMC-Board?  */
 } SDevImc;

 /* ----------- Device Datei ---------------------------------------------- */
 typedef        struct
 {
  CHAR          cName[12];                       /* Ausgabedatei            */
 } SDevFile;

 /* ----------- Device-Deskriptor ----------------------------------------- */
 typedef        struct
 {
  INT           iNum;                            /* Interne Nummer          */
  INT           iSubNum;                         /* Nummer der Schnittstelle*/
  INT           iType;                           /* Art des Anschlusses     */
  union
  {
   SDevSer      ser;                             /* Seriell                 */
   SDevPar      par;                             /* Parallel                */
   SDevImc      imc;                             /* IMC-Board               */
   SDevFile     file;                            /* DAtei                   */
  } d;
 } SDev;

 #define        DEV_NUL         0
 #define        DEV_SER         1
 #define        DEV_PAR         2
 #define        DEV_FILE        3
 #define        DEV_IMC         4

 DECLSTART
 VOID  CDECL    DevInit         PARAM(( SDev* ));
 VOID  CDECL    DevDone         PARAM(( SDev* ));
 VOID  CDECL    DevLoad         PARAM(( SDev*, CHAR* ));
 VOID  CDECL    DevSave         PARAM(( SDev*, CHAR* ));
 DECLEND

#endif
