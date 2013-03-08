#include "spdonut.h"

void
SpDonut::initialize(QXmlStreamReader& xml)
{
  // shape
  QString shape = getAttribute(xml, "shape");
  if (shape == "ROUND") {
    m_shape = SpDonut::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = SpDonut::SQUARE;
  }
  else if (shape == "HEXAGON") {
    m_shape = SpDonut::HEXAGON;
  }
  else if (shape == "OCTAGON") {
    m_shape = SpDonut::OCTAGON;
  }
  // outerDiameter/innerDiameter
  m_outerDiameter =
      getNonNegativeDoubleAttribute(xml, "Donut", "outerDiameter");
  m_innerDiameter =
      getNonNegativeDoubleAttribute(xml, "Donut", "innerDiameter");
}
