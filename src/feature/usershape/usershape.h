#ifndef __USERSHAPE_H__
#define __USERSHAPE_H__

#include <QtCore>
#include "feature.h"
#include "odbfeaturefile.h"

// Base class of "StandardShape":
// StandardPrimitive, StandardPrimitiveRef
class UserShape : public Feature
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units) = 0;
  virtual QString refId() = 0; // used by UserPrimitiveRef
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform) = 0;
};

#endif
