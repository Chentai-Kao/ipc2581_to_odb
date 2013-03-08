#ifndef __CONTOURPOLYGON_H__
#define __CONTOURPOLYGON_H__

#include <QtCore>
#include "polystep.h"

class ContourPolygon
{
public:
  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
};

#endif
