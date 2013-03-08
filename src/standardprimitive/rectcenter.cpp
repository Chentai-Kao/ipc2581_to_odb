#include "rectcenter.h"

void
RectCenter::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "RectCenter", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "RectCenter", "height");
}
