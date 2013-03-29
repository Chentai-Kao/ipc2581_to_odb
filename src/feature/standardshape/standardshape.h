#ifndef __STANDARDSHAPE_H__
#define __STANDARDSHAPE_H__

#include <QtCore>
#include "utils.h"
#include "feature.h"
#include "xform.h"
#include "odbfeaturefile.h"

// Base class of "StandardShape":
// StandardPrimitive, StandardPrimitiveRef
class StandardShape : public Feature
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
  virtual QString refId() = 0; // used by StandardPrimitiveRef
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform) = 0;
};

#endif
