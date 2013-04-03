#include "rectcorner.h"

void
RectCorner::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_lowerLeftX = toMil(
      getDoubleAttribute(xml, "RectCorner", "lowerLeftX"), units);
  m_lowerLeftY = toMil(
      getDoubleAttribute(xml, "RectCorner", "lowerLeftY"), units);
  m_upperRightX = toMil(
      getDoubleAttribute(xml, "RectCorner", "upperRightX"), units);
  m_upperRightY = toMil(
      getDoubleAttribute(xml, "RectCorner", "upperRightY"), units);
}

void
RectCorner::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  // width and height
  qreal w = m_upperRightX - m_lowerLeftX;
  qreal h = m_upperRightY - m_lowerLeftY;
  QString symbol = QString("rect%1x%2").arg(w).arg(h);

  // convert the coordinate from MIL to INCH (because location is in INCH)
  int symNum = odbInsertSymbol(symbol, file.symbolsTable());
  QPointF newLocation = calcTransformedLocation(location, xform);
  int orient = odbDecideOrient(xform);
  file.featuresList().append(QString("P %1 %2 %3 %4 0 %5\n")
                    .arg(newLocation.x() + toInch(m_lowerLeftX + w * 0.5, MIL))
                    .arg(newLocation.y() + toInch(m_lowerLeftY + h * 0.5, MIL))
                    .arg(symNum)
                    .arg(polarity)
                    .arg(orient));
}
