#include "rectcenter.h"

void
RectCenter::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "RectCenter", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "RectCenter", "height");
}

void
RectCenter::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("rect%1x%2").arg(m_width).arg(m_height);
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
