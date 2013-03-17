#ifndef __STANDARDPRIMITIVEFACTORY_H__
#define __STANDARDPRIMITIVEFACTORY_H__

#include <QtCore>
#include "standardprimitive.h"

class StandardPrimitiveFactory
{
public:
  StandardPrimitive* create(QStringRef elementName);
};

#endif
