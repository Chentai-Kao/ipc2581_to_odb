#include "circle.h"

void
Circle::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_diameter = Length(
      getNonNegativeDoubleAttribute(xml, "Circle", "diameter"), units);
}

void
Circle::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("r%1").arg(m_diameter.lengthMil());
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
