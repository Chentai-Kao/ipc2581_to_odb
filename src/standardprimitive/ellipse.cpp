#include "ellipse.h"

void
Ellipse::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "Ellipse", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "Ellipse", "height");
}
