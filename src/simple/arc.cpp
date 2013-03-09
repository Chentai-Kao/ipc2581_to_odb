#include "arc.h"

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
  xml.readNextStartElement();
  if (xml.name() == "LineDesc") {
    m_lineDescGroup = new LineDesc();
  }
  else {
    m_lineDescGroup = new LineDescRef();
  }
  m_lineDescGroup->initialize(xml);
}
