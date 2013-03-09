#include "polystepcurve.h"

void
PolyStepCurve::initialize(QXmlStreamReader& xml)
{
  m_point = QPointF(getDoubleAttribute(xml, "PolyStepCurve", "x"),
                    getDoubleAttribute(xml, "PolyStepCurve", "y"));
  m_centerPoint = QPointF(getDoubleAttribute(xml, "PolyStepCurve", "centerX"),
                          getDoubleAttribute(xml, "PolyStepCurve", "centerY"));
  m_clockwise = getBoolAttribute(xml, "clockwise");
}
