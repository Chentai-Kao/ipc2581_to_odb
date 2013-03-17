#include "donut.h"

void
Donut::initialize(QXmlStreamReader& xml)
{
  // shape
  QString shape = getStringAttribute(xml, "Donut", "shape");
  if (shape == "ROUND") {
    m_shape = Donut::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = Donut::SQUARE;
  }
  else if (shape == "HEXAGON") {
    m_shape = Donut::HEXAGON;
  }
  else if (shape == "OCTAGON") {
    m_shape = Donut::OCTAGON;
  }
  // outerDiameter/innerDiameter
  m_outerDiameter =
      getNonNegativeDoubleAttribute(xml, "Donut", "outerDiameter");
  m_innerDiameter =
      getNonNegativeDoubleAttribute(xml, "Donut", "innerDiameter");
}
