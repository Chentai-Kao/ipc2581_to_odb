#include "thermal.h"

void
Thermal::initialize(QXmlStreamReader& xml)
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
  m_outerDiameter = getDoubleAttribute(xml, "Thermal", "outerDiameter");
  m_innerDiameter = getDoubleAttribute(xml, "Thermal", "innerDiameter");
  if (hasAttribute(xml, "spokeCount")) {
    m_spokeCount = getIntAttribute(xml, "Thermal", "spokeCount");
    if (!isValidSpokeCount()) {
      errorInvalidAttribute("Thermal", "spokeCount");
      exit(1);
    }
  }
  else {
    m_spokeCount = (m_shape == Thermal::HEXAGON)? 3 : 4;
  }
  if (hasAttribute(xml, "gap")) {
    m_gap = getNonNegativeDoubleAttribute(xml, "Thermal", "gap");
  }
  else {
    m_gap = m_outerDiameter - m_innerDiameter;
  }
  m_spokeStartAngle = getDoubleAttribute(xml, "Thermal", "spokeStartAngle");
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
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
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
  }
  else if (m_shape == OCTAGON) {
    // TODO skipped
  }

  int symNum = odbInsertSymbol(symbol, symbolsTable);
  QPointF newLocation = odbDecideTransformedLocation(location, xform);
  int orient = odbDecideOrient(xform);
  featuresList.append(QString("P %1 %2 %3 %4 0 %5\n")
                              .arg(newLocation.x())
                              .arg(newLocation.y())
                              .arg(symNum)
                              .arg(polarity)
                              .arg(orient));
}
