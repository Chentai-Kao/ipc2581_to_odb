#include "sprectcorner.h"

void
SpRectCorner::initialize(QXmlStreamReader& xml)
{
  m_lowerLeftX =
      getNonNegativeDoubleAttribute(xml, "SpRectCorner", "lowerLeftX");
  m_lowerLeftY =
      getNonNegativeDoubleAttribute(xml, "SpRectCorner", "lowerLeftY");
  m_upperRightX =
      getNonNegativeDoubleAttribute(xml, "SpRectCorner", "upperRightX");
  m_upperRightY =
      getNonNegativeDoubleAttribute(xml, "SpRectCorner", "upperRightY");
}
