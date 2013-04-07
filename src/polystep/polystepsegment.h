#ifndef __POLYSTEPSEGMENT_H__
#define __POLYSTEPSEGMENT_H__

#include "polystep.h"
#include "utils.h"
#include "simple.h"
#include "line.h"
#include "linedescgroup.h"

class PolyStepSegment : public PolyStep
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual qreal calcLineIntegral(QPointF prevPoint);
  virtual void setEdge(PolygonEdge& edge, QPointF start, QPointF end);

  // given previous point, return Arc
  virtual Simple* toArcLine(const QPointF prev, LineDescGroup *lineDescGroup) {
    return new Line(prev, m_point, lineDescGroup);
  }

private:
  // m_point (x, y) inherited from PolyStep
};

#endif
