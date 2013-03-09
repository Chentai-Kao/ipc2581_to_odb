#ifndef __USERPRIMITIVEFACTORY_H__
#define __USERPRIMITIVEFACTORY_H__

#include <QtCore>
#include "userprimitive.h"

class UserPrimitiveFactory
{
public:
  UserPrimitive* create(QXmlStreamReader& xml);
};

#endif
