#include "hole.h"
#include "utils.h"
#include "error.h"

void
Hole::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "Hole", "name");
  m_diameter = getNonNegativeDoubleAttribute(xml, "Hole", "diameter");
  QString platingStatus = getStringAttribute(xml, "Hole", "platingStatus");
  if (platingStatus == "PLATED") {
    m_platingStatus = Hole::PLATED;
  }
  else if (platingStatus == "NONPLATED") {
    m_platingStatus = Hole::NONPLATED;
  }
  else if (platingStatus == "VIA") {
    m_platingStatus = Hole::VIA;
  }
  else {
    throw new InvalidAttributeError("Hole", "platingStatus");
  }
  m_plusTol = getNonNegativeDoubleAttribute(xml, "Hole", "plusTol");
  m_minusTol = getNonNegativeDoubleAttribute(xml, "Hole", "minusTol");
  m_location = QPointF(getDoubleAttribute(xml, "Hole", "x"),
                       getDoubleAttribute(xml, "Hole", "y"));
}
