#ifndef __SPTHERMAL_H__
#define __SPTHERMAL_H__

#include "standardprimitive.h"

class SpThermal : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  enum ThermalShape { ROUND, SQUARE, HEXAGON, OCTAGON } m_shape;
  qreal m_outerDiameter;
  qreal m_innerDiameter;
  int   m_spokeCount;
  qreal m_gap;
  qreal m_spokeStartAngle;
};

#endif
