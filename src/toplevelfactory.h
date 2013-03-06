#ifndef __TOPLEVELFACTORY_H__
#define __TOPLEVELFACTORY_H__

#include "avlhandler.h"
#include "bomhandler.h"
#include "contenthandler.h"
#include "ecadhandler.h"
#include "handler.h"
#include "historyrecordhandler.h"
#include "logisticheaderhandler.h"

class TopLevelFactory
{
public:
  Handler* create(QStringRef elementName);
};

#endif
