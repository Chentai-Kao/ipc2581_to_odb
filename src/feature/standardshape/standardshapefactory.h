#ifndef __STANDARDSHAPEFACTORY_H__
#define __STANDARDSHAPEFACTORY_H__

#include <QtCore>
#include "standardshape.h"

class StandardShapeFactory
{
public:
  StandardShape* create(QStringRef elementName);
};

#endif
