#include "line.h"

void
Line::initialize(QXmlStreamReader& xml)
{
  m_start = QPointF(getDoubleAttribute(xml, "Line", "startX"),
                    getDoubleAttribute(xml, "Line", "startY"));
  m_end = QPointF(getDoubleAttribute(xml, "Line", "endX"),
                  getDoubleAttribute(xml, "Line", "endY"));
  // LineDescGroup
  m_lineDescGroup = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "LineDesc") {
        m_lineDescGroup = new LineDesc();
        m_lineDescGroup->initialize(xml);
      }
      else if (xml.name() == "LineDescRef") {
        m_lineDescGroup = new LineDescRef();
        m_lineDescGroup->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "Line")) { // </Line>
      if (m_lineDescGroup == NULL) {
        throw new InvalidElementError("Line");
      }
      return;
    }
  }
}

void
Line::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("%1%2")
                           .arg(m_lineDescGroup->endType())
                           .arg(m_lineDescGroup->lineWidth() * 0.5);
  int symNum = odbInsertSymbol(symbol, file.symbolsTable());
  QPointF newLocation = calcTransformedLocation(location, xform);
  QPointF newStart  = newLocation + calcTransformedLocation(m_start, xform);
  QPointF newEnd    = newLocation + calcTransformedLocation(m_end, xform);
  file.featuresList().append(QString("L %1 %2 %3 %4 %5 %6 0\n")
                             .arg(newStart.x())
                             .arg(newStart.y())
                             .arg(newEnd.x())
                             .arg(newEnd.y())
                             .arg(symNum)
                             .arg(polarity));
}
