#ifndef __ATTRIBUTEFACTORY_H__
#define __ATTRIBUTEFACTORY_H__

#include <QtCore>
#include "attribute.h"

class AttributeFactory
{
public:
  Attribute* create(QStringRef elementName);
};

#endif
