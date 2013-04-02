#ifndef __POLYSTEPSEGMENT_H__
#define __POLYSTEPSEGMENT_H__

#include "polystep.h"
#include "utils.h"

class PolyStepSegment : public PolyStep
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual qreal calcLineIntegral(QPointF prevPoint);
  virtual void setEdge(PolygonEdge& edge);

private:
  // m_point (x, y) inherited from PolyStep
};

#endif
