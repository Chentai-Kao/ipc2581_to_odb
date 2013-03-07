#ifndef __SPCONTOURPOLYGON_H__
#define __SPCONTOURPOLYGON_H__

#include <QtCore>

class PolyStep
{
public:
  enum PolyStepType { SEGMENT, CURVE } m_polyStepType;
  QPointF m_finalPoint; // (x, y)
  QPointF m_centerPoint; // for CURVE (centerX, centerY)
  bool m_clockwise; // for CURVE
};

class SpContourPolygonOrCutout
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  QPointF m_polyBegin;
  QList<PolyStep> m_polySteps;
};

#endif
