#include "line.h"

void
Line::initialize(QXmlStreamReader& xml)
{
  m_start = QPointF(getDoubleAttribute(xml, "Line", "startX"),
                    getDoubleAttribute(xml, "Line", "startY"));
  m_end = QPointF(getDoubleAttribute(xml, "Line", "endX"),
                  getDoubleAttribute(xml, "Line", "endY"));
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
