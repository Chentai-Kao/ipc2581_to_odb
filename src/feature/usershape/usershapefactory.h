#ifndef __USERSHAPEFACTORY_H__
#define __USERSHAPEFACTORY_H__

#include <QtCore>
#include "usershape.h"

class UserShapeFactory
{
public:
  UserShape* create(QStringRef elementName);
};

#endif
