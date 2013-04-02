#ifndef __POLYSTEP_H__
#define __POLYSTEP_H__

#include <QtCore>
#include "utils.h"

class PolyStep
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units) = 0;
  QPointF& point() { return m_point; }
  virtual qreal calcLineIntegral(QPointF prevPoint) = 0;
  virtual void setEdge(PolygonEdge& edge) = 0;

protected:
  QPointF m_point; // (x, y)
};

#endif
