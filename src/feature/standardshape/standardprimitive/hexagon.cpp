#include "hexagon.h"

void
Hexagon::initialize(QXmlStreamReader& xml)
{
  m_length = getNonNegativeDoubleAttribute(xml, "Hexagon", "length");
}
