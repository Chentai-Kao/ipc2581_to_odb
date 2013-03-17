#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <QtCore>
#include "polystep.h"

class Polygon
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  // member function
  bool isClosedShape();

  // data member
  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
};

#endif
