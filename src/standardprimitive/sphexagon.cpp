#include "sphexagon.h"

void
SpHexagon::initialize(QXmlStreamReader& xml)
{
  m_length = getNonNegativeDoubleAttribute(xml, "Hexagon", "length");
}
