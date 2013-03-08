#include "octagon.h"

void
Octagon::initialize(QXmlStreamReader& xml)
{
  m_length = getNonNegativeDoubleAttribute(xml, "Octagon", "length");
}
