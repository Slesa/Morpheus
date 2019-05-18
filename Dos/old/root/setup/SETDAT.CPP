#include			"basics/Inifile.h"
#include			"gastro/Pathdefs.h"
#include <conio.h>
static const char	entryAartExtern[]	= "Extern";

static TInifile*	cfgPayforms;
static bool			chgPayforms;

extern "C" {
void				SetupAartInit();
void				SetupAartDone();
void				SetupAartSave();
CHAR*				SetupGetAartExternal(int iAart, CHAR* pcExtern);
int					SetupSetAartExternal(int iAart, CHAR* pcExtern);
int					SetupDelAartExtern(int iAart);
}

void				SetupAartInit()
{
	cfgPayforms = new TInifile((char*)PathGetPayforms());
//	Assert(cfgPayforms, ERR_MEMORY);
	chgPayforms = false;
}

void				SetupAartDone()
{
	SetupAartSave();
	delete cfgPayforms;
}

void				SetupAartSave()
{
	if( chgPayforms )
		cfgPayforms->save();
	chgPayforms = false;
}

CHAR*				SetupGetAartExternal(int iAart, CHAR* pcExtern)
{
	QString sect;
	sect.sprintf("Payform%d", iAart);
	QString entry = cfgPayforms->getString(sect, entryAartExtern);
	int pos = entry.find('.');
	if( pos>=0 )
		entry = entry.left(pos);
	entry.simplifyWhiteSpace();
	strcpy((char*)pcExtern, (const char*) entry);
	return pcExtern;
}

int					SetupSetAartExternal(int iAart, CHAR* pcExtern)
{
	QString sect;
	sect.sprintf("Payform%d", iAart);
	QString tmp = (char*) pcExtern;
	tmp += ".EXE";
	cfgPayforms->setValue(tmp, sect, entryAartExtern);
	chgPayforms = true;
	return 1;
}

int					SetupDelAartExtern(int iAart)
{
	QString sect;
	sect.sprintf("Payform%d", iAart);
	TInifile::TGroup* group = cfgPayforms->findGroup(sect);
	if( !group )
		return 1;
	group->delEntry(entryAartExtern);
	chgPayforms = true;
	return 1;
}


