#include "polystepsegment.h"

void
PolyStepSegment::initialize(QXmlStreamReader& xml)
{
  m_point = QPointF(getDoubleAttribute(xml, "PolyStepSegment", "x"),
                    getDoubleAttribute(xml, "PolyStepSegment", "y"));
}
