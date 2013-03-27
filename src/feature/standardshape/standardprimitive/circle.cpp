#include "circle.h"

void
Circle::initialize(QXmlStreamReader& xml)
{
  m_diameter = getNonNegativeDoubleAttribute(xml, "Circle", "diameter");
}

void
Circle::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("r%1").arg(m_diameter);
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
