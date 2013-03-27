#include "donut.h"

void
Donut::initialize(QXmlStreamReader& xml)
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
  m_outerDiameter =
      getNonNegativeDoubleAttribute(xml, "Donut", "outerDiameter");
  m_innerDiameter =
      getNonNegativeDoubleAttribute(xml, "Donut", "innerDiameter");
}

void
Donut::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
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
