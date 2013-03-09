#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <QtCore>
#include "polystep.h"
#include "polystepcurve.h"
#include "polystepsegment.h"

class Polygon
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  bool isClosedShape();

  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
};

#endif
