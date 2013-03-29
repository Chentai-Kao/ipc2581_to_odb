#ifndef __THERMAL_H__
#define __THERMAL_H__

#include "standardprimitive.h"


class Thermal : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  bool isValidSpokeCount();
  enum ThermalShape { ROUND, SQUARE, HEXAGON, OCTAGON };
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  ThermalShape m_shape;
  qreal m_outerDiameter;
  qreal m_innerDiameter;
  int   m_spokeCount;
  qreal m_gap;
  qreal m_spokeStartAngle;
};

#endif
