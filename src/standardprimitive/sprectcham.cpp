#include "sprectcham.h"

void
SpRectCham::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "RectCham", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "RectCham", "height");
  m_chamfer = getNonNegativeDoubleAttribute(xml, "RectCham", "chamfer");
  if (2 * m_chamfer > m_width || 2 * m_chamfer > m_height) {
    errorInvalidAttribute("RectCham", "chamfer");
    exit(1);
  }
  m_upperRight = getBoolAttribute(xml, "upperRight");
  m_upperLeft = getBoolAttribute(xml, "upperLeft");
  m_lowerLeft = getBoolAttribute(xml, "lowerLeft");
  m_lowerRight = getBoolAttribute(xml, "lowerRight");
}
