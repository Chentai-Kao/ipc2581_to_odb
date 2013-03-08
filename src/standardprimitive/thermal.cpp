#include "thermal.h"

void
Thermal::initialize(QXmlStreamReader& xml)
{
  // shape
  QString shape = getAttribute(xml, "shape");
  if (shape == "ROUND") {
    m_shape = Thermal::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = Thermal::SQUARE;
  }
  else if (shape == "HEXAGON") {
    m_shape = Thermal::HEXAGON;
  }
  else if (shape == "OCTAGON") {
    m_shape = Thermal::OCTAGON;
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
    m_spokeCount = (m_shape == Thermal::HEXAGON)? 3 : 4;
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
Thermal::isValidSpokeCount()
{
  switch (m_shape) {
    case Thermal::ROUND :
      return (m_spokeCount == 0 || m_spokeCount == 2 ||
              m_spokeCount == 3 || m_spokeCount == 4);
    case Thermal::SQUARE :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 4);
    case Thermal::HEXAGON :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 3);
    case Thermal::OCTAGON :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 4);
    default :
      break;
  }
  return true;
}
