#include "donut.h"
#include "error.h"
#include "line.h"
#include "linedesc.h"
#include "polygon.h"

void
Donut::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // shape
  QString shape = getStringAttribute(xml, "Donut", "shape");
  if (shape == "ROUND") {
    m_shape = ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = SQUARE;
  }
  else if (shape == "HEXAGON") {
    m_shape = HEXAGON;
  }
  else if (shape == "OCTAGON") {
    m_shape = OCTAGON;
  }
  // outerDiameter/innerDiameter
  m_outerDiameter = Length(
      getNonNegativeDoubleAttribute(xml, "Donut", "outerDiameter"), units);
  m_innerDiameter = Length(
      getNonNegativeDoubleAttribute(xml, "Donut", "innerDiameter"), units);
}

void
Donut::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol;
  if (m_shape == ROUND) {
    symbol = QString("donut_r%1x%2")
                    .arg(m_outerDiameter.lengthMil())
                    .arg(m_innerDiameter.lengthMil());
  }
  else if (m_shape == SQUARE) {
    symbol = QString("donut_s%1x%2")
                    .arg(m_outerDiameter.lengthMil())
                    .arg(m_innerDiameter.lengthMil());
  }
  else if (m_shape == HEXAGON) { // 6 segments, use polygon to draw each segment
    // the 4 point of a segment (first one is the top-left segment)
    QPointF p0(0, 0.5 * m_outerDiameter.lengthInch());
    QPointF p1(0, 0.5 * m_innerDiameter.lengthInch());
    QList<QPointF> points;
    points.append(p0);
    points.append(p1);
    points.append(rotatePoint(p1, 60));
    points.append(rotatePoint(p0, 60));
    points.append(p0);

    // start the Surface description
    file.featuresList().append(QString("S %1 0\n").arg(polarity));
    for (int i = 0; i < 6; ++i) {
      Polygon polygon;
      polygon.setPolygon(points);
      polygon.odbOutputLayerFeature(file, location, xform, POLYGON);
      // rotate points to the next segment (60-deg counter-clockwise)
      for (int j = 0; j < points.size(); ++j) {
        points[j] = rotatePoint(points[j], 60);
      }
    }
    file.featuresList().append(QString("SE\n"));
    return;
  }
  else if (m_shape == OCTAGON) { // 8 segments, use polygon to draw each segment
    // the 4 point of a segment (first one is the top-left segment)
    QPointF p0(0, 0.5 * m_outerDiameter.lengthInch());
    QPointF p1(0, 0.5 * m_innerDiameter.lengthInch());
    QList<QPointF> points;
    points.append(p0);
    points.append(p1);
    points.append(rotatePoint(p1, 45));
    points.append(rotatePoint(p0, 45));
    points.append(p0);

    // start the Surface description
    file.featuresList().append(QString("S %1 0\n").arg(polarity));
    for (int i = 0; i < 8; ++i) {
      Polygon polygon;
      polygon.setPolygon(points);
      polygon.odbOutputLayerFeature(file, location, xform, POLYGON);
      // rotate points to the next segment (60-deg counter-clockwise)
      for (int j = 0; j < points.size(); ++j) {
        points[j] = rotatePoint(points[j], 45);
      }
    }
    file.featuresList().append(QString("SE\n"));
    return;
  }

  int symNum = odbInsertSymbol(symbol, file.symbolsTable());
  QPointF newLocation = calcTransformedLocation(location, xform);
  int orient = odbDecideOrient(xform);
  file.featuresList().append(QString("P %1 %2 %3 %4 0 %5\n")
                              .arg(newLocation.x())
                              .arg(newLocation.y())
                              .arg(symNum)
                              .arg(polarity)
                              .arg(orient));
}
