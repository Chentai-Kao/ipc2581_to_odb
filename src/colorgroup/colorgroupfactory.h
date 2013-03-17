#ifndef __COLORGROUPFACTORY_H__
#define __COLORGROUPFACTORY_H__

#include <QtCore>
#include "colorgroup.h"

class ColorGroupFactory
{
public:
  ColorGroup* create(QStringRef elementName);
};

#endif
