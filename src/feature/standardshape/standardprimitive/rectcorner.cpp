#include "rectcorner.h"

void
RectCorner::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_lowerLeftX = Length(
      getDoubleAttribute(xml, "RectCorner", "lowerLeftX"), units);
  m_lowerLeftY = Length(
      getDoubleAttribute(xml, "RectCorner", "lowerLeftY"), units);
  m_upperRightX = Length(
      getDoubleAttribute(xml, "RectCorner", "upperRightX"), units);
  m_upperRightY = Length(
      getDoubleAttribute(xml, "RectCorner", "upperRightY"), units);
}

void
RectCorner::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  // width and height
  QString symbol = QString("rect%1x%2")
      .arg(m_upperRightX.lengthMil() - m_lowerLeftX.lengthMil())
      .arg(m_upperRightY.lengthMil() - m_lowerLeftY.lengthMil());

  // convert the coordinate from MIL to INCH (because location is in INCH)
  int symNum = odbInsertSymbol(symbol, file.symbolsTable());
  QPointF newLocation = calcTransformedLocation(location, xform);
  int orient = odbDecideOrient(xform);
  file.featuresList().append(QString("P %1 %2 %3 %4 0 %5\n")
      .arg(newLocation.x() + m_lowerLeftX.lengthInch() +
           0.5 * (m_upperRightX.lengthInch() - m_lowerLeftX.lengthInch()))
      .arg(newLocation.y() + m_lowerLeftY.lengthInch() +
           0.5 * (m_upperRightY.lengthInch() - m_lowerLeftY.lengthInch()))
      .arg(symNum)
      .arg(polarity)
      .arg(orient));
}
