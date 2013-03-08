#include "sptriangle.h"

void
SpTriangle::initialize(QXmlStreamReader& xml)
{
  m_base = getNonNegativeDoubleAttribute(xml, "Triangle", "base");
  m_height = getNonNegativeDoubleAttribute(xml, "Triangle", "height");
}
