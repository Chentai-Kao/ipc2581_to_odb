#ifndef __STANDARDPRIMITIVE_H__
#define __STANDARDPRIMITIVE_H__

#include <QtCore>
#include "utils.h"
#include "standardshape.h"
#include "length.h"

// Base class of "standard primitive":
// Butterfly, Circle, Contour, Diamond, Donut,
// Ellipse, Hexagon, Moire, Octagon, Oval,
// RectCenter, RectCham, RectRound, Thermal, Triangle
class StandardPrimitive : public StandardShape
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units) = 0;
  virtual QString refId() { return ""; }
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform) = 0;
};

#endif
