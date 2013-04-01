#include "polygon.h"
#include "polystepfactory.h"
#include "error.h"

void
Polygon::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PolyBegin") {
        m_polyBegin.rx() = getDoubleAttribute(xml, "PolyBegin", "x");
        m_polyBegin.ry() = getDoubleAttribute(xml, "PolyBegin", "y");
      }
      else if (isSubstitutionGroupPolyStep(xml.name())) {
        PolyStep *p = PolyStepFactory().create(xml.name());
        p->initialize(xml);
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
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform, PolygonType type)
{
  // island == POLYGON (must clockwise), hole == CUTOUT (must counter clockwise)
  file.featuresList().append(QString("S %1 0\n").arg(polarity));
  if ((type == POLYGON && isClockwise()) || 
      (type == CUTOUT && !isClockwise())) {
    odbOutputFeature(file, type);
  }
  else {
    odbOutputFeatureInv(file, type);
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
Polygon::calcPolygonEdges()
{
  QList<PolygonEdge> polygonEdges;
  for (int i = 0; i < m_polySteps.size(); ++i) {
    PolygonEdge edge;
    if (i == 0) {
      edge.m_startPoint = m_polyBegin;
    }
    else {
      edge.m_startPoint = m_polySteps[i - 1]->point();
    }
    m_polySteps[i]->setEdge(edge);
    polygonEdges.append(edge);
  }
  return polygonEdges;
}

void
Polygon::odbOutputFeature(OdbFeatureFile& file, PolygonType type)
{
  file.featuresList().append(QString("OB %1 %2 %3\n")
                              .arg(m_polyBegin.x())
                              .arg(m_polyBegin.y())
                              .arg(type == POLYGON? "I" : "H"));
  QList<PolygonEdge> polygonEdges = calcPolygonEdges();
  for (int i = 0; i < polygonEdges.size(); ++i) {
    if (polygonEdges[i].m_odbType == "OS") {
      file.featuresList().append(QString("OS %1 %2\n")
                          .arg(polygonEdges[i].m_endPoint.x())
                          .arg(polygonEdges[i].m_endPoint.y()));
    }
    else {
      file.featuresList().append(QString("OC %1 %2 %3 %4 %5\n")
                          .arg(polygonEdges[i].m_endPoint.x())
                          .arg(polygonEdges[i].m_endPoint.y())
                          .arg(polygonEdges[i].m_centerPoint.x())
                          .arg(polygonEdges[i].m_centerPoint.y())
                          .arg(polygonEdges[i].m_clockwise? "Y" : "N"));
    }
  }
  file.featuresList().append(QString("OE\n"));
}

void
Polygon::odbOutputFeatureInv(OdbFeatureFile& file, PolygonType type)
{
  file.featuresList().append(QString("OB %1 %2 %3\n")
                              .arg(m_polyBegin.x())
                              .arg(m_polyBegin.y())
                              .arg(type == POLYGON? "I" : "H"));
  QList<PolygonEdge> polygonEdges = calcPolygonEdges();
  for (int i = polygonEdges.size() - 1; i >= 0; --i) {
    if (polygonEdges[i].m_odbType == "OS") {
      file.featuresList().append(QString("OS %1 %2\n")
                          .arg(polygonEdges[i].m_startPoint.x())
                          .arg(polygonEdges[i].m_startPoint.y()));
    }
    else {
      file.featuresList().append(QString("OC %1 %2 %3 %4 %5\n")
                          .arg(polygonEdges[i].m_startPoint.x())
                          .arg(polygonEdges[i].m_startPoint.y())
                          .arg(polygonEdges[i].m_centerPoint.x())
                          .arg(polygonEdges[i].m_centerPoint.y())
                          .arg(polygonEdges[i].m_clockwise? "N" : "Y"));
    }
  }
  file.featuresList().append(QString("OE\n"));
}
