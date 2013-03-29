#include "triangle.h"

void
Triangle::initialize(QXmlStreamReader& xml)
{
  m_base = getNonNegativeDoubleAttribute(xml, "Triangle", "base");
  m_height = getNonNegativeDoubleAttribute(xml, "Triangle", "height");
}

void
Triangle::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("tri%1x%2").arg(m_base).arg(m_height);
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
