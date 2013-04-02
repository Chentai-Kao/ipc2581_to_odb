#include "polystepsegment.h"

void
PolyStepSegment::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_point = QPointF(
      toInch(getDoubleAttribute(xml, "PolyStepSegment", "x"), units),
      toInch(getDoubleAttribute(xml, "PolyStepSegment", "y"), units));
}

qreal
PolyStepSegment::calcLineIntegral(QPointF prevPoint)
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
  QPointF& p1 = prevPoint;
  QPointF& p2 = m_point;
  return 0.5 * (p2.y() - p1.y()) * (p1.x() + p2.x());
}

void
PolyStepSegment::setEdge(PolygonEdge& edge)
{
  edge.m_endPoint = m_point;
  edge.m_odbType = "OS";
}
