#include "spcircle.h"

void
SpCircle::initialize(QXmlStreamReader& xml)
{
  m_diameter = getNonNegativeDoubleAttribute(xml, "Circle", "diameter");
}
