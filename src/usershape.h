#ifndef __USERSHAPE_H__
#define __USERSHAPE_H__

#include <QtCore>
#include "feature.h"

// Base class of "StandardShape":
// StandardPrimitive, StandardPrimitiveRef
class UserShape : public Feature
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
