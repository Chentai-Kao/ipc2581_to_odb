#include "rectround.h"
#include "error.h"

void
RectRound::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = Length(
      getNonNegativeDoubleAttribute(xml, "RectRound", "width"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "RectRound", "height"), units);
  m_radius = Length(
      getNonNegativeDoubleAttribute(xml, "RectRound", "radius"), units);
  if (2 * m_radius.lengthMil() > m_width.lengthMil() ||
      2 * m_radius.lengthMil() > m_height.lengthMil()) {
    throw new InvalidAttributeError("RectRound", "radius");
  }
  m_upperRight = getBoolAttribute(xml, "upperRight");
  m_upperLeft = getBoolAttribute(xml, "upperLeft");
  m_lowerLeft = getBoolAttribute(xml, "lowerLeft");
  m_lowerRight = getBoolAttribute(xml, "lowerRight");
}

void
RectRound::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  QString corners = QString((m_upperRight)? "1" : "") +
                    QString((m_upperLeft)?  "2" : "") +
                    QString((m_lowerLeft)?  "3" : "") +
                    QString((m_lowerRight)? "4" : "");
  QString symbol = QString("rect%1x%2xr%3x%4")
                           .arg(m_width.lengthMil())
                           .arg(m_height.lengthMil())
                           .arg(m_radius.lengthMil())
                           .arg(corners);

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
