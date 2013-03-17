#ifndef __POLYSTEPFACTORY_H__
#define __POLYSTEPFACTORY_H__

#include <QtCore>
#include "polystep.h"

class PolyStepFactory
{
public:
  PolyStep* create(QStringRef elementName);
};

#endif
