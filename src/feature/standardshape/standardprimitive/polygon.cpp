#include "polygon.h"
#include "polystepfactory.h"
#include "error.h"

void
Polygon::initialize(QXmlStreamReader& xml, UnitsType units)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PolyBegin") {
        m_polyBegin.rx() = toInch(
            getDoubleAttribute(xml, "PolyBegin", "x"), units);
        m_polyBegin.ry() = toInch(
            getDoubleAttribute(xml, "PolyBegin", "y"), units);
      }
      else if (isSubstitutionGroupPolyStep(xml.name())) {
        PolyStep *p = PolyStepFactory().create(xml.name());
        p->initialize(xml, units);
        m_polySteps.append(p);
      }
    }
    else if (isEndElementWithName(xml, "Polygon") || // </Polygon> the end
             isEndElementWithName(xml, "Cutout")) { // another possible name
      break;
    }
  }
  if (!isClosedShape()) {
    throw new InvalidElementError("Polygon");
  }
}

bool
Polygon::isClosedShape()
{
  return (m_polyBegin.x() == m_polySteps.last()->point().x() &&
          m_polyBegin.y() == m_polySteps.last()->point().y());
}

void
Polygon::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform, PolygonType type)
{
  // island == POLYGON (must clockwise), hole == CUTOUT (must counter clockwise)
  file.featuresList().append(QString("S %1 0\n").arg(polarity));
  if ((type == POLYGON &&  isClockwise()) || 
      (type == CUTOUT  && !isClockwise())) {
    odbOutputFeature(file, location, xform, type, FORWARD);
  }
  else {
    odbOutputFeature(file, location, xform, type, REVERSE);
  }
  file.featuresList().append(QString("SE\n"));
}

bool
Polygon::isClockwise()
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
  QPointF prevPoint = m_polyBegin;
  qreal integral = 0;
  for (int i = 0; i < m_polySteps.size(); ++i) {
    integral += m_polySteps[i]->calcLineIntegral(prevPoint);
    prevPoint = m_polySteps[i]->point();
  }
  return integral < 0;
}

QList<PolygonEdge>
Polygon::calcPolygonEdges(OutputOrder outputOrder)
{
  QList<PolygonEdge> polygonEdges;
  if (outputOrder == FORWARD) { // output as the edge's order
    for (int i = 0; i < m_polySteps.size(); ++i) {
      PolygonEdge edge;
      QPointF start = (i == 0)? m_polyBegin : m_polySteps[i - 1]->point();
      QPointF end = m_polySteps[i]->point();
      m_polySteps[i]->setEdge(edge, start, end);
      polygonEdges.append(edge);
    }
  }
  else { // output as reverse edge's order
    for (int i = m_polySteps.size() - 1; i >= 0; --i) {
      PolygonEdge edge;
      QPointF start = m_polySteps[i]->point();
      QPointF end = (i == 0)? m_polyBegin : m_polySteps[i - 1]->point();
      m_polySteps[i]->setEdge(edge, start, end);
      if (edge.m_odbType == "OC") {
        edge.m_clockwise = edge.m_clockwise? false : true; // reverse clockwise
      }
      polygonEdges.append(edge);
    }
  }
  return polygonEdges;
}

void
Polygon::odbOutputFeature(OdbFeatureFile& file, QPointF location,
    Xform *xform, PolygonType type, OutputOrder outputOrder)
{
  QPointF newLocation = calcTransformedLocation(location, xform);
  file.featuresList().append(QString("OB %1 %2 %3\n")
                             .arg(newLocation.x() + m_polyBegin.x())
                             .arg(newLocation.y() + m_polyBegin.y())
                             .arg(type == POLYGON? "I" : "H"));

  // PolygonEdge is used to handle clockwise/counter-clockwise print
  QList<PolygonEdge> polygonEdges = calcPolygonEdges(outputOrder);

  // output each edge
  for (int i = 0; i < polygonEdges.size(); ++i) {
    if (polygonEdges[i].m_odbType == "OS") {
      file.featuresList().append(QString("OS %1 %2\n")
                      .arg(newLocation.x() + polygonEdges[i].m_endPoint.x())
                      .arg(newLocation.y() + polygonEdges[i].m_endPoint.y()));
    }
    else {
      // output
      file.featuresList().append(QString("OC %1 %2 %3 %4 %5\n")
                      .arg(newLocation.x() + polygonEdges[i].m_endPoint.x())
                      .arg(newLocation.y() + polygonEdges[i].m_endPoint.y())
                      .arg(newLocation.x() + polygonEdges[i].m_centerPoint.x())
                      .arg(newLocation.y() + polygonEdges[i].m_centerPoint.y())
                      .arg(polygonEdges[i].m_clockwise? "Y" : "N"));
    }
  }
  file.featuresList().append(QString("OE\n"));
}

void
Polygon::toArcLine(QList<Simple*>& arcLineList, LineDescGroup *lineDescGroup)
{
  // save result in 'arcLineList'
  arcLineList.clear();
  QPointF prev = m_polyBegin;
  for (int i = 0; i < m_polySteps.size(); ++i) {
    Simple *s = m_polySteps[i]->toArcLine(prev, lineDescGroup);
    arcLineList.append(s);
    prev = m_polySteps[i]->point();
  }
}
