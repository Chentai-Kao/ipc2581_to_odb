#include "arc.h"
#include "utils.h"

void
Arc::initialize(QXmlStreamReader& xml)
{
  m_start = QPointF(getDoubleAttribute(xml, "Arc", "startX"),
                    getDoubleAttribute(xml, "Arc", "startY"));
  m_end = QPointF(getDoubleAttribute(xml, "Arc", "endX"),
                  getDoubleAttribute(xml, "Arc", "endY"));
  m_center = QPointF(getDoubleAttribute(xml, "Arc", "centerX"),
                     getDoubleAttribute(xml, "Arc", "centerY"));
  m_clockwise = getBoolAttribute(xml, "clockwise");
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
    else if (isEndElementWithName(xml, "Arc")) { // </Arc>
      if (m_lineDescGroup == NULL) {
        throw new InvalidElementError("Arc");
      }
      return;
    }
  }
}

void
Arc::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol = QString("r%1").arg(m_lineDescGroup->lineWidth() * 0.5);
  int symNum = odbInsertSymbol(symbol, file.symbolsTable());
  QPointF newLocation = calcTransformedLocation(location, xform);
  QPointF newStart  = newLocation + calcTransformedLocation(m_start, xform);
  QPointF newEnd    = newLocation + calcTransformedLocation(m_end, xform);
  QPointF newCenter = newLocation + calcTransformedLocation(m_center, xform);
  file.featuresList().append(QString("A %1 %2 %3 %4 %5 %6 %7 %8 0 %9\n")
                             .arg(newStart.x())
                             .arg(newStart.y())
                             .arg(newEnd.x())
                             .arg(newEnd.y())
                             .arg(newCenter.x())
                             .arg(newCenter.y())
                             .arg(symNum)
                             .arg(polarity)
                             .arg(m_clockwise? "Y" : "N"));
}
