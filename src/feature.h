#ifndef __FEATURE_H__
#define __FEATURE_H__

#include <QtCore>
#include "utils.h"

// Base class of "feature":
// StandardShape, UserShape
class Feature
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
