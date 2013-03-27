#include "butterfly.h"
#include "error.h"

void
Butterfly::initialize(QXmlStreamReader& xml)
{
  // shape
  QString shape = getStringAttribute(xml, "Butterfly", "shape");
  if (shape == "ROUND") {
    m_shape = Butterfly::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = Butterfly::SQUARE;
  }
  else {
    throw new InvalidAttributeError("Butterfly", "shape");
  }
  // diameter and side
  if (m_shape == Butterfly::ROUND) {
    m_diameter = getNonNegativeDoubleAttribute(xml, "Butterfly", "diameter");
  }
  else if (m_shape == Butterfly::SQUARE) {
    m_side = getNonNegativeDoubleAttribute(xml, "Butterfly", "side");
  }
}

void
Butterfly::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol;
  if (m_shape == ROUND) { // bfr<d>
    symbol = QString("bfr%1").arg(m_diameter);
  }
  else { // bfs<s>
    symbol = QString("bfs%1").arg(m_side);
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
