#ifndef __SIMPLEFACTORY_H__
#define __SIMPLEFACTORY_H__

#include <QtCore>
#include "simple.h"

class SimpleFactory
{
public:
  Simple* create(QStringRef elementName);
};

#endif
