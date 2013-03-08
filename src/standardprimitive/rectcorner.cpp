#include "rectcorner.h"

void
RectCorner::initialize(QXmlStreamReader& xml)
{
  m_lowerLeftX =
      getNonNegativeDoubleAttribute(xml, "RectCorner", "lowerLeftX");
  m_lowerLeftY =
      getNonNegativeDoubleAttribute(xml, "RectCorner", "lowerLeftY");
  m_upperRightX =
      getNonNegativeDoubleAttribute(xml, "RectCorner", "upperRightX");
  m_upperRightY =
      getNonNegativeDoubleAttribute(xml, "RectCorner", "upperRightY");
}
