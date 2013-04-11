#include "moire.h"
#include "error.h"

void
Moire::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // required attributes
  m_diameter = Length(
      getNonNegativeDoubleAttribute(xml, "Moire", "diameter"), units);
  m_ringWidth = Length(
      getNonNegativeDoubleAttribute(xml, "Moire", "ringWidth"), units);
  m_ringGap = Length(
      getNonNegativeDoubleAttribute(xml, "Moire", "ringGap"), units);
  m_ringNumber = getNonNegativeIntAttribute(xml, "Moire", "ringNumber");
  // optional attributes
  m_lineWidth = Length(0, units);
  m_lineLength = Length(0, units);
  m_lineAngle = 0;
  if (hasAttribute(xml, "lineWidth")) {
    m_lineWidth = Length(
        getNonNegativeDoubleAttribute(xml, "Moire", "lineWidth"), units);
  }
  if (hasAttribute(xml, "lineLength")) {
    m_lineLength = Length(
      getNonNegativeDoubleAttribute(xml, "Moire", "lineLength"), units);
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
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("moire%1x%2x%3x%4x%5x%6")
               .arg(m_ringWidth.lengthMil())
               .arg(m_ringGap.lengthMil() - m_ringWidth.lengthMil() * 0.5f)
               .arg(m_ringNumber)
               .arg(m_lineWidth.lengthMil())
               .arg(m_lineLength.lengthMil())
               .arg(m_lineAngle);

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
