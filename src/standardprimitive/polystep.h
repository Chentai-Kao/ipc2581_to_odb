#ifndef __POLYSTEP_H__
#define __POLYSTEP_H__

#include <QtCore>

class PolyStep
{
public:
  PolyStep(qreal x, qreal y) : m_point(x, y) {}
  virtual void setClockwise(bool) {} // inherited by PolyStepCurve

  QPointF m_point; // (x, y)
};

class PolyStepCurve : public PolyStep
{
public:
  PolyStepCurve(qreal x, qreal y, qreal cx, qreal cy) :
      PolyStep(x, y), m_centerPoint(cx, cy), m_clockwise(false) {}
  void setClockwise(bool clockwise) { m_clockwise = clockwise; }

  QPointF m_centerPoint; // (centerX, centerY)
  bool m_clockwise;
};

class PolyStepSegment : public PolyStep
{
public:
  PolyStepSegment(qreal x, qreal y) : PolyStep(x, y) {}
};

#endif
