#include "octagon.h"

void
Octagon::initialize(QXmlStreamReader& xml)
{
  m_length = getNonNegativeDoubleAttribute(xml, "Octagon", "length");
}

void
Octagon::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  qreal r = m_length / qSqrt(8 + 4 * qSqrt(2));
  qreal w = r * (2 + qSqrt(2));
  qreal h = w;
  QString symbol = QString("oct%1x%2x%3").arg(w).arg(h).arg(r);
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
