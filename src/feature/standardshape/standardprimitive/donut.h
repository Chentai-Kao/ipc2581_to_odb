#ifndef __DONUT_H__
#define __DONUT_H__

#include "standardprimitive.h"


class Donut : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  enum DonutShape { ROUND, SQUARE, HEXAGON, OCTAGON };
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  DonutShape m_shape;
  qreal m_outerDiameter;
  qreal m_innerDiameter;
};

#endif
