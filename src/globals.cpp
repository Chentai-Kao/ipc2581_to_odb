#include <QtCore>
#include "standardprimitive.h"
#include "userprimitive.h"
#include "linedesc.h"
#include "odbfeaturefile.h"
#include "layer.h"

QHash<QString, StandardPrimitive*> g_entryStandards;
QHash<QString, UserPrimitive*>     g_entryUsers;
QHash<QString, LineDesc>           g_entryLineDescs;

QMap<QString, OdbFeatureFile> g_layerFeatureFiles;

QList<Layer> g_layers;
