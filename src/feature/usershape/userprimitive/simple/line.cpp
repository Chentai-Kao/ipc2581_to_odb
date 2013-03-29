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
  // TODO skipped
  // throw new NonImplementedError("Line::odbOutputLayerFeatre()");
}
