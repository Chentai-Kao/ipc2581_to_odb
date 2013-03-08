#include "spbutterfly.h"

void
SpButterfly::initialize(QXmlStreamReader& xml)
{
  // shape
  QString shape = getAttribute(xml, "shape");
  if (shape == "ROUND") {
    m_shape = SpButterfly::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = SpButterfly::SQUARE;
  }
  else {
    errorInvalidAttribute("Butterfly", "shape");
    exit(1);
  }
  // diameter and side
  if (m_shape == SpButterfly::ROUND) {
    m_diameter = getNonNegativeDoubleAttribute(xml, "Butterfly", "diameter");
  }
  else if (m_shape == SpButterfly::SQUARE) {
    m_side = getNonNegativeDoubleAttribute(xml, "Butterfly", "side");
  }
}
