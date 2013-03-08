#include "spthermal.h"

void
SpThermal::initialize(QXmlStreamReader& xml)
{
  // shape
  QString shape = getAttribute(xml, "shape");
  if (shape == "ROUND") {
    m_shape = SpThermal::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = SpThermal::SQUARE;
  }
  else if (shape == "HEXAGON") {
    m_shape = SpThermal::HEXAGON;
  }
  else if (shape == "OCTAGON") {
    m_shape = SpThermal::OCTAGON;
  }
  // others...
  m_outerDiameter = getDoubleAttribute(xml, "Thermal", "outerDiameter");
  m_innerDiameter = getDoubleAttribute(xml, "Thermal", "innerDiameter");
  if (xml.attributes().hasAttribute("spokeCount")) {
    m_spokeCount = getIntAttribute(xml, "Thermal", "spokeCount");
    if (!isValidSpokeCount()) {
      errorInvalidAttribute("Thermal", "spokeCount");
      exit(1);
    }
  }
  else {
    m_spokeCount = (m_shape == SpThermal::HEXAGON)? 3 : 4;
  }
  if (xml.attributes().hasAttribute("gap")) {
    m_gap = getNonNegativeDoubleAttribute(xml, "Thermal", "gap");
  }
  else {
    m_gap = m_outerDiameter - m_innerDiameter;
  }
  m_spokeStartAngle = getDoubleAttribute(xml, "Thermal", "spokeStartAngle");
}

bool
SpThermal::isValidSpokeCount()
{
  switch (m_shape) {
    case SpThermal::ROUND :
      return (m_spokeCount == 0 || m_spokeCount == 2 ||
              m_spokeCount == 3 || m_spokeCount == 4);
    case SpThermal::SQUARE :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 4);
    case SpThermal::HEXAGON :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 3);
    case SpThermal::OCTAGON :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 4);
    default :
      break;
  }
  return true;
}
