#include "spellipse.h"

void
SpEllipse::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "Ellipse", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "Ellipse", "height");
}
