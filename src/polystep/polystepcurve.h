#ifndef __POLYSTEPCURVE_H__
#define __POLYSTEPCURVE_H__

#include "polystep.h"
#include "utils.h"

class PolyStepCurve : public PolyStep
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual qreal calcLineIntegral(QPointF prevPoint);
  virtual void setEdge(PolygonEdge& edge);

private:
  // m_point (x, y) inherited from PolyStep
  QPointF m_centerPoint; // (centerX, centerY)
  bool m_clockwise;
};

#endif
