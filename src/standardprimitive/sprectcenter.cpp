#include "sprectcenter.h"

void
SpRectCenter::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "RectCenter", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "RectCenter", "height");
}
