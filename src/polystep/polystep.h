#ifndef __POLYSTEP_H__
#define __POLYSTEP_H__

#include <QtCore>
#include "utils.h"
#include "simple.h"
#include "linedescgroup.h"

class PolyStep
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units) = 0;
  QPointF& point() { return m_point; }
  virtual qreal calcLineIntegral(QPointF prevPoint) = 0;
  virtual void setEdge(PolygonEdge& edge, QPointF start, QPointF end) = 0;

  // convert PolyStepCurve to Arc, and PolyStepSegment to Line
  virtual Simple* toArcLine(const QPointF prev, LineDescGroup *lineDescGroup)=0;

protected:
  QPointF m_point; // (x, y)
};

#endif
