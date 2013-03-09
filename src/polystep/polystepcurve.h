#ifndef __POLYSTEPCURVE_H__
#define __POLYSTEPCURVE_H__

#include "polystep.h"
#include "utils.h"

class PolyStepCurve : public PolyStep
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  // m_point (x, y) inherited from PolyStep
  QPointF m_centerPoint; // (centerX, centerY)
  bool m_clockwise;
};

#endif
