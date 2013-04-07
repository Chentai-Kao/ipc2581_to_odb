#ifndef __POLYSTEPCURVE_H__
#define __POLYSTEPCURVE_H__

#include "polystep.h"
#include "utils.h"
#include "simple.h"
#include "arc.h"
#include "linedescgroup.h"

class PolyStepCurve : public PolyStep
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual qreal calcLineIntegral(QPointF prevPoint);
  virtual void setEdge(PolygonEdge& edge, QPointF start, QPointF end);

  // given previous point, return Arc
  virtual Simple* toArcLine(const QPointF prev, LineDescGroup *lineDescGroup) {
    return new Arc(prev, m_point, m_centerPoint, m_clockwise, lineDescGroup);
  }

private:
  // m_point (x, y) inherited from PolyStep
  QPointF m_centerPoint; // (centerX, centerY)
  bool m_clockwise;
};

#endif
