#include "oval.h"
#include "error.h"

void
Oval::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = Length(
      getNonNegativeDoubleAttribute(xml, "Oval", "width"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "Oval", "height"), units);
  if (m_height.lengthMil() > m_width.lengthMil()) {
    throw new InvalidAttributeError("Oval", "height");
  }
}

void
Oval::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("oval%1x%2")
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
