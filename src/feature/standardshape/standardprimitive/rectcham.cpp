#include "rectcham.h"

void
RectCham::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "RectCham", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "RectCham", "height");
  m_chamfer = getNonNegativeDoubleAttribute(xml, "RectCham", "chamfer");
  if (2 * m_chamfer > m_width || 2 * m_chamfer > m_height) {
    errorInvalidAttribute("RectCham", "chamfer");
    exit(1);
  }
  m_upperRight = getBoolAttribute(xml, "upperRight");
  m_upperLeft = getBoolAttribute(xml, "upperLeft");
  m_lowerLeft = getBoolAttribute(xml, "lowerLeft");
  m_lowerRight = getBoolAttribute(xml, "lowerRight");
}

void
RectCham::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
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
