#include        "files/CfgFile.h"
#include        "gastro/Setup.h"
#include        "gastro/Pathdefs.h"
#include        "basics/MemAlloc.h"
#include        "basics/String.h"
#include        "defs/Errordef.h"
#include        <stdio.h>
#include        <string.h>

 static const char entryBonHeader[]    = "BonHeader";
 static const char entryBonTrailer[]   = "BonTrailer";
 static const char entryBonLine[]      = "BonLine";
 static const char entryBonHinw[]      = "BonHinw";
 static const char entryVoid[]         = "Void";
 static const char entryBillHeader[]   = "BillHeader";
 static const char entryBillTrailer[]  = "BillTrailer";
 static const char entryBillLine[]     = "BillLine";
 static const char entryBillHinw[]     = "BillHinw";
// static const char entryAartExtern[]   = "Extern";

// static SCfgFile cfgPayforms;
// static BOOL     chgPayforms;
/*
 VOID CDECL     SetupAartInit();
 VOID CDECL     SetupAartDone();
 VOID CDECL     SetupAartSave();
 CHAR* CDECL    SetupGetAartExternal( INT, CHAR* );
 BOOL CDECL     SetupSetAartExternal( INT, CHAR* );
 BOOL CDECL     SetupDelAartExtern( INT );
*/
 VOID CDECL     SetupGetLibDatLayout( INT, CHAR[5][60] );
 VOID CDECL     SetupSetLibDatLayout( INT, CHAR[5][60] );

 VOID CDECL     SetupSetExtLayout( iWhat, buff, dev )
 INT            iWhat;
 CHAR           buff[5][60];
 INT            dev;
 {
  SCfgFile      cfg;
  CHAR          cTemp[100];
  INT           i;
  if( dev==-1 )
  {
   SetupSetLibDatLayout(iWhat, buff);
   return;
  }
  CfgInit(&cfg);
  CfgLoad(&cfg, PathGetLayout());
  switch( iWhat )
  {
   case SETUP_LAYOUT_KOPF:
        sprintf( cTemp, "%hd_%s", dev, entryBonHeader);
        break;
   case SETUP_LAYOUT_ENDE:
        sprintf( cTemp, "%hd_%s", dev, entryBonTrailer);
        break;
   case SETUP_LAYOUT_BEST:
        sprintf( cTemp, "%hd_%s", dev, entryBonLine);
        break;
   case SETUP_LAYOUT_STOR:
        sprintf( cTemp, "%hd_%s", dev, entryVoid);
        break;
   case SETUP_LAYOUT_HINW:
        sprintf( cTemp, "%hd_%s", dev, entryBonHinw);
        break;
   case SETUP_LAYOUT_RECHKOPF:
        sprintf( cTemp, "%hd_%s", dev, entryBillHeader);
        break;
   case SETUP_LAYOUT_RECHENDE:
        sprintf( cTemp, "%hd_%s", dev, entryBillTrailer);
        break;
   case SETUP_LAYOUT_RECHPOST:
        sprintf( cTemp, "%hd_%s", dev, entryBillLine);
        break;
   case SETUP_LAYOUT_RECHHINW:
        sprintf( cTemp, "%hd_%s", dev, entryBillHinw);
        break;
  }
  CfgDeleteSection(&cfg, cTemp);
  for( i=0; i<5; i++ )
  {
   CfgSetEntry(&cfg, TRUE, cTemp, "Line", buff[i] );
  }
  CfgSave(&cfg, PathGetLayout());
  CfgDone(&cfg);
 }

 VOID CDECL     SetupGetLibLayout( iWhat, buff, dev )
 INT            iWhat;
 CHAR           buff[5][60];
 INT            dev;
 {
  SCfgFile      cfg;
  INT           i;
  INT           data;
  CHAR          cTemp[100];
  CHAR          cTmp2[101];
  for( i=0; i<5; i++ )
   MemFill(buff[i], 0, 60);
  if( dev==-1 )
  {
   SetupGetLibDatLayout(iWhat, buff);
   return;
  }
  switch( iWhat )
  {
   case SETUP_LAYOUT_KOPF:
        sprintf( cTemp, "%hd_%s", dev, entryBonHeader);
        break;
   case SETUP_LAYOUT_ENDE:
        sprintf( cTemp, "%hd_%s", dev, entryBonTrailer);
        break;
   case SETUP_LAYOUT_BEST:
        sprintf( cTemp, "%hd_%s", dev, entryBonLine);
        break;
   case SETUP_LAYOUT_STOR:
        sprintf( cTemp, "%hd_%s", dev, entryVoid);
        break;
   case SETUP_LAYOUT_HINW:
        sprintf( cTemp, "%hd_%s", dev, entryBonHinw);
        break;
   case SETUP_LAYOUT_RECHKOPF:
        sprintf( cTemp, "%hd_%s", dev, entryBillHeader);
        break;
   case SETUP_LAYOUT_RECHENDE:
        sprintf( cTemp, "%hd_%s", dev, entryBillTrailer);
        break;
   case SETUP_LAYOUT_RECHPOST:
        sprintf( cTemp, "%hd_%s", dev, entryBillLine);
        break;
   case SETUP_LAYOUT_RECHHINW:
        sprintf( cTemp, "%hd_%s", dev, entryBillHinw);
        break;
  }
  CfgInit(&cfg);
  CfgLoad(&cfg, PathGetLayout());
  if( CfgFindSection(&cfg, cTemp) != ERR_NONE )
   return;
  i=0;
  for( data=CfgFirstEntry(&cfg, cTmp2); data==ERR_NONE; data=CfgNextEntry(&cfg, cTmp2) )
  {
   CfgGetValue(cTmp2,buff[i++]);
   if( i>=5 )
    break;
  }
  CfgDone(&cfg);
 }

 VOID CDECL     SetupGetLibDatLayout( iWhat, buff )
 INT            iWhat;
 CHAR           buff[5][60];
 {
  extern  SETUP  abrech;
  extern SSetup sSetup;
  INT           i;
  for( i=0; i<5; i++ )
   MemFill(buff[i], 0, 60);
  switch( iWhat )
  {
   case SETUP_LAYOUT_KOPF:
        for(i=0;i<5;i++)
         strcpy(buff[i],abrech.kopf.layout[i]);
        break;
   case SETUP_LAYOUT_ENDE:
        for(i=0;i<5;i++)
         strcpy(buff[i],sSetup.bon_ende.layout[i]);
        break;
   case SETUP_LAYOUT_BEST:
        for(i=0;i<5;i++)
         strcpy(buff[i],abrech.best.layout[i]);
        break;
   case SETUP_LAYOUT_STOR:
        for(i=0;i<5;i++)
         strcpy(buff[i],abrech.stor.layout[i]);
        break;
   case SETUP_LAYOUT_HINW:
        for(i=0;i<5;i++)
         strcpy(buff[i],abrech.hinw.layout[i]);
        break;
   case SETUP_LAYOUT_RECHKOPF:
        for(i=0;i<5;i++)
         strcpy(buff[i],abrech.rechnung_kopf.layout[i]);
        break;
   case SETUP_LAYOUT_RECHENDE:
        for(i=0;i<5;i++)
         strcpy(buff[i],abrech.rechnung_ende.layout[i]);
        break;
   case SETUP_LAYOUT_RECHPOST:
        for(i=0;i<5;i++)
         strcpy(buff[i],abrech.rechnung_posten.layout[i]);
        break;
   case SETUP_LAYOUT_RECHHINW:
        for(i=0;i<5;i++)
         strcpy(buff[i],abrech.rechnung_hinw.layout[i]);
        break;
  }
 }

 VOID CDECL     SetupSetLibDatLayout( iWhat, buff )
 INT            iWhat;
 CHAR           buff[5][60];
 {
  extern  SETUP  abrech;
  extern SSetup sSetup;
  INT           i;
  switch( iWhat )
  {
   case SETUP_LAYOUT_KOPF:
        for(i=0;i<5;i++)
         strcpy(abrech.kopf.layout[i],buff[i]);
        break;
   case SETUP_LAYOUT_ENDE:
        for(i=0;i<5;i++)
         strcpy(sSetup.bon_ende.layout[i],buff[i]);
        break;
   case SETUP_LAYOUT_BEST:
        for(i=0;i<5;i++)
         strcpy(abrech.best.layout[i],buff[i]);
        break;
   case SETUP_LAYOUT_STOR:
        for(i=0;i<5;i++)
         strcpy(abrech.stor.layout[i],buff[i]);
        break;
   case SETUP_LAYOUT_HINW:
        for(i=0;i<5;i++)
         strcpy(abrech.hinw.layout[i],buff[i]);
        break;
   case SETUP_LAYOUT_RECHKOPF:
        for(i=0;i<5;i++)
         strcpy(abrech.rechnung_kopf.layout[i],buff[i]);
        break;
   case SETUP_LAYOUT_RECHENDE:
        for(i=0;i<5;i++)
         strcpy(abrech.rechnung_ende.layout[i],buff[i]);
        break;
   case SETUP_LAYOUT_RECHPOST:
        for(i=0;i<5;i++)
         strcpy(abrech.rechnung_posten.layout[i],buff[i]);
        break;
   case SETUP_LAYOUT_RECHHINW:
        for(i=0;i<5;i++)
         strcpy(abrech.rechnung_hinw.layout[i],buff[i]);
        break;
  }
 }
/*
 VOID CDECL     SetupAartInit()
 {
  CfgInit(&cfgPayforms);
  CfgLoad(&cfgPayforms, PathGetPayforms());
  chgPayforms = FALSE;
 }

 VOID CDECL     SetupAartDone()
 {
  SetupAartSave();
  CfgDone(&cfgPayforms);
 }

 VOID CDECL     SetupAartSave()
 {
  if( chgPayforms )
   CfgSave(&cfgPayforms, PathGetLayout());
  chgPayforms = FALSE;
 }

 CHAR* CDECL    SetupGetAartExternal( iAart, pcExtern )
 INT            iAart;
 CHAR*          pcExtern;
 {
  CHAR          cSect[40];
  CHAR          cTemp[100];
  sprintf( cSect, "Payform%hd", iAart);
  CfgGetString(&cfgPayforms, cSect, (CHAR*) entryAartExtern, "", cTemp);
  if( *cTemp )
  {
   CHAR* cp = strchr(cTemp, '.');
   if( cp )
    *cp = 0;
  }
  StrTrim(cTemp, pcExtern);
  return pcExtern;
 }

 BOOL CDECL     SetupSetAartExternal( iAart, pcExtern )
 INT            iAart;
 CHAR*          pcExtern;
 {
  CHAR          cSect[40];
  CHAR          cExt[100];
  if( pcExtern==NULL || *pcExtern==0 )
   SetupDelAartExtern(iAart);
  sprintf( cSect, "Payform%d", iAart);
  StrTrim(pcExtern, cExt);
  strcat(cExt, ".EXE");
  if( CfgSetEntry(&cfgPayforms, FALSE, cSect, (CHAR*) entryAartExtern, cExt) != ERR_NONE )
   return FALSE;
  chgPayforms = TRUE;
  return TRUE;
 }

 BOOL CDECL     SetupDelAartExtern( iAart )
 INT            iAart;
 {
  CHAR          cSect[40];
  sprintf( cSect, "Payform%d", iAart);
  if( CfgFindSection(&cfgPayforms, cSect) != ERR_NONE )
   return TRUE;
  if( CfgDeleteEntry(&cfgPayforms, (CHAR*) entryAartExtern) != ERR_NONE )
   return FALSE;
  chgPayforms = TRUE;
  return TRUE;
 }


*/

