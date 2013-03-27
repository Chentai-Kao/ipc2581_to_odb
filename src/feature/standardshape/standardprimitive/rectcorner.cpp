#include "rectcorner.h"

void
RectCorner::initialize(QXmlStreamReader& xml)
{
  m_lowerLeftX = getDoubleAttribute(xml, "RectCorner", "lowerLeftX");
  m_lowerLeftY = getDoubleAttribute(xml, "RectCorner", "lowerLeftY");
  m_upperRightX = getDoubleAttribute(xml, "RectCorner", "upperRightX");
  m_upperRightY = getDoubleAttribute(xml, "RectCorner", "upperRightY");
}

void
RectCorner::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  qreal w = m_upperRightX - m_lowerLeftX;
  qreal h = m_upperRightY - m_lowerLeftY;
  QString symbol = QString("rect%1x%2").arg(w).arg(h);
  symbol += odbRotationSuffix(xform);

  int symNum = odbInsertSymbol(symbol, symbolsTable);
  QPointF newLocation = odbDecideTransformedLocation(location, xform);
  int orient = odbDecideOrient(xform);
  featuresList.append(QString("P %1 %2 %3 %4 0 %5\n")
                              .arg(newLocation.x() + m_lowerLeftX + w * 0.5)
                              .arg(newLocation.y() + m_lowerLeftY + h * 0.5)
                              .arg(symNum)
                              .arg(polarity)
                              .arg(orient));
}
