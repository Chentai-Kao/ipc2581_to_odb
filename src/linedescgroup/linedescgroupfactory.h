#ifndef __LINEDESCGROUPFACTORY_H__
#define __LINEDESCGROUPFACTORY_H__

#include <QtCore>
#include "linedescgroup.h"

class LineDescGroupFactory
{
public:
  LineDescGroup* create(QStringRef elementName);
};

#endif
