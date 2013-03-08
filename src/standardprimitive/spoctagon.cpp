#include "spoctagon.h"

void
SpOctagon::initialize(QXmlStreamReader& xml)
{
  m_length = getNonNegativeDoubleAttribute(xml, "Octagon", "length");
}
