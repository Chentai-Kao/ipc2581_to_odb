#include "rectround.h"

void
RectRound::initialize(QXmlStreamReader& xml)
{
  m_width = getNonNegativeDoubleAttribute(xml, "RectRound", "width");
  m_height = getNonNegativeDoubleAttribute(xml, "RectRound", "height");
  m_radius = getNonNegativeDoubleAttribute(xml, "RectRound", "radius");
  if (2 * m_radius > m_width || 2 * m_radius > m_height) {
    errorInvalidAttribute("RectRound", "radius");
    exit(1);
  }
  m_upperRight = getBoolAttribute(xml, "upperRight");
  m_upperLeft = getBoolAttribute(xml, "upperLeft");
  m_lowerLeft = getBoolAttribute(xml, "lowerLeft");
  m_lowerRight = getBoolAttribute(xml, "lowerRight");
}
