#ifndef __STANDARDSHAPE_H__
#define __STANDARDSHAPE_H__

#include <QtCore>
#include "utils.h"
#include "feature.h"

// Base class of "StandardShape":
// StandardPrimitive, StandardPrimitiveRef
class StandardShape : public Feature
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
  //virtual OdbFeatureRecord createFeatureRecord() = 0;
};

#endif
