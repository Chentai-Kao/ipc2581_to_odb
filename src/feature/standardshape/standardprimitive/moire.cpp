#include "moire.h"
#include "error.h"

void
Moire::initialize(QXmlStreamReader& xml)
{
  // required attributes
  m_diameter = getNonNegativeDoubleAttribute(xml, "Moire", "diameter");
  m_ringWidth = getNonNegativeDoubleAttribute(xml, "Moire", "ringWidth");
  m_ringGap = getNonNegativeDoubleAttribute(xml, "Moire", "ringGap");
  m_ringGap = getNonNegativeDoubleAttribute(xml, "Moire", "ringGap");
  m_ringNumber = getNonNegativeIntAttribute(xml, "Moire", "ringNumber");
  // optional attributes
  if (hasAttribute(xml, "lineWidth")) {
    m_lineWidth = getNonNegativeDoubleAttribute(xml, "Moire", "lineWidth");
  }
  if (hasAttribute(xml, "lineLength")) {
    m_lineLength = getNonNegativeDoubleAttribute(xml, "Moire", "lineLength");
  }
  if (hasAttribute(xml, "lineAngle")) {
    m_lineAngle = getNonNegativeDoubleAttribute(xml, "Moire", "lineAngle");
    if (m_lineAngle < 0 || m_lineAngle > 90) {
      throw new InvalidAttributeError("Moire", "lineAngle");
    }
  }
}

void
Moire::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("moire%1x%2x%3x%4x%5x%6")
                           .arg(m_ringWidth)
                           .arg(m_ringGap - m_ringWidth * 0.5) // different
                           .arg(m_ringNumber)
                           .arg(m_lineWidth)
                           .arg(m_lineLength)
                           .arg(m_lineAngle);
  symbol += odbRotationSuffix(xform);

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
