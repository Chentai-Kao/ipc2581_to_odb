#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <QtCore>
#include "standardprimitive.h"
#include "userprimitive.h"
#include "linedesc.h"
#include "odbfeaturefile.h"
#include "layer.h"

#define COMP_TOP_NAME "comp_+_top"
#define COMP_BOT_NAME "comp_+_bot"

// actual definition is in "globals.cpp"

/* Dictionaries for entryStandard, entryUser, and entryLineDesc. <id, type> */
extern QHash<QString, StandardPrimitive*> g_entryStandards;
extern QHash<QString, UserPrimitive*>     g_entryUsers;
extern QHash<QString, LineDesc>           g_entryLineDescs;

/* All feature files for output. <layerName, odbFeatureFile> */
extern QMap<QString, OdbFeatureFile> g_layerFeatureFiles;

/* All layers */
extern QList<Layer> g_layers;

/* Always overwrite the output path */
extern bool g_alwaysOverwrite;

#endif
