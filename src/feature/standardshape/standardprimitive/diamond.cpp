#include "diamond.h"

void
Diamond::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = Length(
      getNonNegativeDoubleAttribute(xml, "Diamond", "width"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "Diamond", "height"), units);
}

void
Diamond::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("di%1x%2")
                          .arg(m_width.lengthMil())
                          .arg(m_height.lengthMil());
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
