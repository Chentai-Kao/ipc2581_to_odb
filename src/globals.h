#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <QtCore>
#include "standardprimitive.h"
#include "userprimitive.h"
#include "linedesc.h"
#include "component.h"
#include "odbfeaturefile.h"

// actual definition is in "globals.cpp"

/* Dictionaries for entryStandard, entryUser, and entryLineDesc. <id, type> */
extern QHash<QString, StandardPrimitive*> g_entryStandards;
extern QHash<QString, UserPrimitive*>     g_entryUsers;
extern QHash<QString, LineDesc>           g_entryLineDescs;

/* Dictionary for components (used when drawing TOP and BOTTOM layers */
extern QList<Component> g_components;

/* All feature files for output. <layerName, odbFeatureFile> */
extern QMap<QString, OdbFeatureFile> g_layerFeatureFiles;

/* Always overwrite the output path */
extern bool g_alwaysOverwrite;

#endif
