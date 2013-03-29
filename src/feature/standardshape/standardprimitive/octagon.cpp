#include "octagon.h"

void
Octagon::initialize(QXmlStreamReader& xml)
{
  m_length = getNonNegativeDoubleAttribute(xml, "Octagon", "length");
}

void
Octagon::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  qreal r = m_length / qSqrt(8 + 4 * qSqrt(2));
  qreal w = r * (2 + qSqrt(2));
  qreal h = w;
  QString symbol = QString("oct%1x%2x%3").arg(w).arg(h).arg(r);
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
