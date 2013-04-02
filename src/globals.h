#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <QtCore>
#include "standardprimitive.h"
#include "userprimitive.h"
#include "linedesc.h"

// actual definition is in "globals.cpp"

/* Dictionaries for entryStandard, entryUser, and entryLineDesc. <id, type> */
extern QHash<QString, StandardPrimitive*> g_entryStandards;
extern QHash<QString, UserPrimitive*>     g_entryUsers;
extern QHash<QString, LineDesc>           g_entryLineDescs;

#endif
