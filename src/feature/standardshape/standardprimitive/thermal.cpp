#include "thermal.h"
#include "error.h"

void
Thermal::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // shape
  QString shape = getStringAttribute(xml, "Thermal", "shape");
  if (shape == "ROUND") {
    m_shape = Thermal::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = Thermal::SQUARE;
  }
  else if (shape == "HEXAGON") {
    m_shape = Thermal::HEXAGON;
  }
  else if (shape == "OCTAGON") {
    m_shape = Thermal::OCTAGON;
  }
  // others...
  m_outerDiameter = toMil(
      getDoubleAttribute(xml, "Thermal", "outerDiameter"), units);
  m_innerDiameter = toMil(
      getDoubleAttribute(xml, "Thermal", "innerDiameter"), units);
  if (hasAttribute(xml, "spokeCount")) {
    m_spokeCount = getIntAttribute(xml, "Thermal", "spokeCount");
    if (!isValidSpokeCount()) {
      throw new InvalidAttributeError("Thermal", "spokeCount");
    }
  }
  else {
    m_spokeCount = (m_shape == Thermal::HEXAGON)? 3 : 4;
  }
  if (hasAttribute(xml, "gap")) {
    m_gap = toMil(
        getNonNegativeDoubleAttribute(xml, "Thermal", "gap"), units);
  }
  else {
    m_gap = m_outerDiameter - m_innerDiameter;
  }
  m_spokeStartAngle = toMil(
      getDoubleAttribute(xml, "Thermal", "spokeStartAngle"), units);
}

bool
Thermal::isValidSpokeCount()
{
  switch (m_shape) {
    case Thermal::ROUND :
      return (m_spokeCount == 0 || m_spokeCount == 2 ||
              m_spokeCount == 3 || m_spokeCount == 4);
    case Thermal::SQUARE :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 4);
    case Thermal::HEXAGON :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 3);
    case Thermal::OCTAGON :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 4);
    default :
      break;
  }
  return true;
}

void
Thermal::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol;
  if (m_shape == ROUND) {
    symbol = QString("ths%1x%2x%3x%4x%5")
                     .arg(m_outerDiameter)
                     .arg(m_innerDiameter)
                     .arg(m_spokeStartAngle)
                     .arg(m_spokeCount)
                     .arg(m_gap);
  }
  else if (m_shape == SQUARE) {
    symbol = QString("s_ths%1x%2x%3x%4x%5")
                     .arg(m_outerDiameter)
                     .arg(m_innerDiameter)
                     .arg(m_spokeStartAngle)
                     .arg(m_spokeCount)
                     .arg(m_gap);
  }
  else if (m_shape == HEXAGON) {
// TODO skipped
    //throw new NonImplementedError("Thermal::HEXAGON");
  }
  else if (m_shape == OCTAGON) {
// TODO skipped
    //throw new NonImplementedError("Thermal::OCTAGON");
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
