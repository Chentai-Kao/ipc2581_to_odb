#include "hexagon.h"

void
Hexagon::initialize(QXmlStreamReader& xml)
{
  m_length = getNonNegativeDoubleAttribute(xml, "Hexagon", "length");
}

void
Hexagon::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("hex_s%1x%2x%3")
                           .arg(m_length * 0.5 * qSqrt(3))
                           .arg(m_length)
                           .arg(m_length * 0.25);
  symbol += odbRotationSuffix(xform);
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
