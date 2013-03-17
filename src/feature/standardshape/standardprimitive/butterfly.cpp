#include "butterfly.h"

void
Butterfly::initialize(QXmlStreamReader& xml)
{
  // shape
  QString shape = getStringAttribute(xml, "Butterfly", "shape");
  if (shape == "ROUND") {
    m_shape = Butterfly::ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = Butterfly::SQUARE;
  }
  else {
    errorInvalidAttribute("Butterfly", "shape");
    exit(1);
  }
  // diameter and side
  if (m_shape == Butterfly::ROUND) {
    m_diameter = getNonNegativeDoubleAttribute(xml, "Butterfly", "diameter");
  }
  else if (m_shape == Butterfly::SQUARE) {
    m_side = getNonNegativeDoubleAttribute(xml, "Butterfly", "side");
  }
}
