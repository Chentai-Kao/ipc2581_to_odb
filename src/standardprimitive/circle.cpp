#include "circle.h"

void
Circle::initialize(QXmlStreamReader& xml)
{
  m_diameter = getNonNegativeDoubleAttribute(xml, "Circle", "diameter");
}
