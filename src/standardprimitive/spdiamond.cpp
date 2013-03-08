#include "spdiamond.h"

void
SpDiamond::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "Diamond", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "Diamond", "height");
}
