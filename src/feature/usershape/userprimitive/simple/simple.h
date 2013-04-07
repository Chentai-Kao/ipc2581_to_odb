#ifndef __SIMPLE_H__
#define __SIMPLE_H__

#include <QtCore>
#include "utils.h"
#include "userprimitive.h"

// Base class of "Simple":
// Arc, Line, Outline, Polyline
class Simple : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units) = 0;
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform) = 0;
};

#endif
