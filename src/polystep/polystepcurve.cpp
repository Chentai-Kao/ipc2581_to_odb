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

qreal
PolyStepCurve::calcLineIntegral(QPointF prevPoint)
{
  /* Determine whether the direction of all steps is clockwise.
   * Based on Green's theory, area equals to the integral around the outline.
   * If the integral > 0, it's counter clockwise, return false.
   * If the integral < 0, it's clockwise, return true.
   * For segment: integral = 0.5 * (y2 - y1) * (x1 + x2)
   *              where the segment starts at p1(x1, y1), ends at p2(x2, y2)
   * For curve  : integral = x0 * r * (y2 - y1)
   *                         + 0.5 * r^2 * (theta2 - theta1)
   *                         + 0.25 * r^2 * (sin(2 * theta2) - sin(2 * theta1))
   *              where the curve is (x0 + r * cos(theta), y0 + r * sin(theta))
   *              and the center point is p0(x0, y0)
   *              and the curve starts at p1(x1, y1), ends at p2(x2, y2)
   */
  QPointF& p0 = m_centerPoint;
  QPointF& p1 = prevPoint;
  QPointF& p2 = m_point;
  qreal r = qSqrt(SQR(p0.x() - p1.x()) + SQR(p0.y() - p1.y()));
  qreal theta1 = calcCorrectAngle(p0, p1);
  qreal theta2 = calcCorrectAngle(p0, p2);

  return p0.x() * r * (qSin(theta2) - qSin(theta1))
         + 0.5 * SQR(r) * (theta2 - theta1)
         + 0.25 * SQR(r) * (qSin(2 * theta2) - qSin(2 * theta1));
}

void
PolyStepCurve::setEdge(PolygonEdge& edge)
{
  edge.m_endPoint = m_point;
  edge.m_centerPoint = m_centerPoint;
  edge.m_clockwise = m_clockwise;
  edge.m_odbType = "OC";
}
