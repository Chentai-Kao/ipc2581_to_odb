#ifndef __FEATURE_H__
#define __FEATURE_H__

#include <QtCore>
#include "utils.h"
#include "odbfeaturefile.h"

// Base class of "feature":
// StandardShape, UserShape
class Feature
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
  virtual QString refId() = 0; // by StandardPrimitiveRef and UserPrimitiveRef
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform) = 0;
};

#endif
