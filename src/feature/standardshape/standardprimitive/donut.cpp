#include "donut.h"
#include "error.h"

void
Donut::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // shape
  QString shape = getStringAttribute(xml, "Donut", "shape");
  if (shape == "ROUND") {
    m_shape = Donut::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = Donut::SQUARE;
  }
  else if (shape == "HEXAGON") {
    m_shape = Donut::HEXAGON;
  }
  else if (shape == "OCTAGON") {
    m_shape = Donut::OCTAGON;
  }
  // outerDiameter/innerDiameter
  m_outerDiameter = toMil(
      getNonNegativeDoubleAttribute(xml, "Donut", "outerDiameter"), units);
  m_innerDiameter = toMil(
      getNonNegativeDoubleAttribute(xml, "Donut", "innerDiameter"), units);
}

void
Donut::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol;
  if (m_shape == ROUND) {
    symbol =
        QString("donut_r%1x%2").arg(m_outerDiameter).arg(m_innerDiameter);
  }
  else if (m_shape == SQUARE) {
    symbol =
        QString("donut_s%1x%2").arg(m_outerDiameter).arg(m_innerDiameter);
  }
  else if (m_shape == HEXAGON) {
// TODO skipped
    //throw new NonImplementedError("Donut::HEXAGON");
  }
  else if (m_shape == OCTAGON) {
// TODO skipped
    //throw new NonImplementedError("Donut::OCTAGON");
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
