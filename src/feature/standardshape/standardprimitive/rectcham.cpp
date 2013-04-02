#include "rectcham.h"
#include "error.h"

void
RectCham::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = toMil(
      getNonNegativeDoubleAttribute(xml, "RectCham", "width"), units);
  m_height = toMil(
      getNonNegativeDoubleAttribute(xml, "RectCham", "height"), units);
  m_chamfer = toMil(
      getNonNegativeDoubleAttribute(xml, "RectCham", "chamfer"), units);
  if (2 * m_chamfer > m_width || 2 * m_chamfer > m_height) {
    throw new InvalidAttributeError("RectCham", "chamfer");
  }
  m_upperRight = getBoolAttribute(xml, "upperRight");
  m_upperLeft = getBoolAttribute(xml, "upperLeft");
  m_lowerLeft = getBoolAttribute(xml, "lowerLeft");
  m_lowerRight = getBoolAttribute(xml, "lowerRight");
}

void
RectCham::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString corners = QString((m_upperRight)? "1" : "") +
                    QString((m_upperLeft)?  "2" : "") +
                    QString((m_lowerLeft)?  "3" : "") +
                    QString((m_lowerRight)? "4" : "");
  QString symbol = QString("rect%1x%2xc%3x%4")
                           .arg(m_width)
                           .arg(m_height)
                           .arg(m_chamfer)
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
