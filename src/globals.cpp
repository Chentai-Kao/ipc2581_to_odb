#include <QtCore>
#include "standardprimitive.h"
#include "userprimitive.h"
#include "linedesc.h"

QHash<QString, StandardPrimitive*> g_entryStandards;
QHash<QString, UserPrimitive*>     g_entryUsers;
QHash<QString, LineDesc>           g_entryLineDescs;
