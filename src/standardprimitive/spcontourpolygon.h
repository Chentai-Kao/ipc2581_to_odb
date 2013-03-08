#ifndef __SPCONTOURPOLYGON_H__
#define __SPCONTOURPOLYGON_H__

#include <QtCore>
#include "polystep.h"

class SpContourPolygon
{
public:
  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
};

#endif
