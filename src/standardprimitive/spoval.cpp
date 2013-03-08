#include "spoval.h"

void
SpOval::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "Oval", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "Oval", "height");
  if (m_height > m_width) {
    errorInvalidAttribute("Oval", "height");
    exit(1);
  }
}
