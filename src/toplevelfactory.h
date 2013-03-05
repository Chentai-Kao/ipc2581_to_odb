#ifndef __TOPLEVELFACTORY_H__
#define __TOPLEVELFACTORY_H__

#include "handler.h"
#include "ipc2581ahandler.h"
#include "contenthandler.h"
#include "logisticheaderhandler.h"
#include "historyrecordhandler.h"
#include "bomhandler.h"
#include "ecadhandler.h"

class TopLevelFactory
{
public:
  Handler* create(QStringRef elementName);
};

#endif
